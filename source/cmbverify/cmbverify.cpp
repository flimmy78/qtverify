/***********************************************
**  文件名:     cmbverify.cpp
**  功能:       组合检定主界面
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/5/6
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2015/05 第一版
**  内容包含:
**  说明:		
**  更新记录:   
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QtSql/QSqlTableModel>
#include <QtGui/QFileDialog>
#include <QtCore/QSignalMapper>
#include <math.h>
#include "qtexdb.h"
#include "report.h"
#include "cmbverify.h"

CmbVerifyDlg::CmbVerifyDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	m_metercount = 0;
}

CmbVerifyDlg::~CmbVerifyDlg()
{
}

void CmbVerifyDlg::showEvent(QShowEvent *)
{
	m_CmbParamDlg = NULL;
	m_sendTimer = NULL;
	m_timer = new QTimer();
	m_countdown = 0;
	m_tempObj = NULL;
	ui.label_hint->setText(tr("Please set the Install position, Unit, and minimum temperature difference correctly"));

	m_param_config = new QSettings(getFullIniFileName("cmbparam.ini"), QSettings::IniFormat);
	
	m_metercount = m_param_config->value("diff/metercount").toUInt();
	m_vol0_is_read = new bool[m_metercount];
	m_eng0_is_read = new bool[m_metercount];
	for (int i=0;i<m_metercount;i++)
	{
		m_vol0_is_read[i] = false;
		m_eng0_is_read[i] = false;
	}

	m_algo = new CAlgorithm;
	m_readComConfig = new ReadComConfig();

	m_pos_selected = false;
	m_unit_selected = false;
	m_min_tempdiff_set = false;
	m_delta_temp_achieved = false;

	initUi();
	connect(this, SIGNAL(verifyCanStart(void)), this, SLOT(startVerifySlot(void)));

	connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_countdown_timerout()));

	m_meterObj = NULL;
	initMeterCom();
}

void CmbVerifyDlg::closeEvent( QCloseEvent * event)
{
	if(NULL != m_CmbParamDlg)
	{
		delete m_CmbParamDlg;
		m_CmbParamDlg = NULL;
	}

	if (NULL != m_param_config)
	{
		delete m_param_config;
		m_param_config = NULL;
	}

	if (NULL != m_algo)
	{
		delete m_algo;
		m_algo = NULL;
	}

	if (NULL != m_readComConfig)
	{
		delete m_readComConfig;
		m_readComConfig = NULL;
	}

	//热量表通讯
	if (m_meterObj)
	{
		delete []m_meterObj;
		m_meterObj = NULL;

		for (int i=0; i<m_metercount; i++)
		{
			m_meterThread[i].exit();
		}
	}

	clearTempComObjs();

	if (NULL != m_timer)
	{
		if (m_timer->isActive())
		{
			m_timer->stop();
		}

		delete m_timer;
		m_timer = NULL;
	}
}

void CmbVerifyDlg::resizeEvent(QResizeEvent * event)
{
	qDebug()<<"resizeEvent...";

	int th = ui.tableWidget->size().height();
	int tw = ui.tableWidget->size().width();
	int hh = ui.tableWidget->horizontalHeader()->size().height();
	int vw = ui.tableWidget->verticalHeader()->size().width();
	int vSize = (int)((th-hh-10)/(m_metercount<=0 ? 12 : m_metercount));
	int hSize = (int)((tw-vw-20)/COL_COUNT);
	ui.tableWidget->verticalHeader()->setDefaultSectionSize(vSize);
	ui.tableWidget->horizontalHeader()->setDefaultSectionSize(hSize);
}

void CmbVerifyDlg::initUi()
{
	m_btnGroup_unit = new QButtonGroup(ui.gbox_unit); //计量单位
	m_btnGroup_unit->addButton(ui.rbtn_unit_kwh, UNIT_KWH);
	m_btnGroup_unit->addButton(ui.rbtn_unit_mj, UNIT_MJ);
	connect(m_btnGroup_unit, SIGNAL(buttonClicked(int)), this, SLOT(slot_btnGroup_unit_clicked(int)));

	m_btnGroup_pos = new QButtonGroup(ui.gbox_install_pos);//安装位置
	m_btnGroup_pos->addButton(ui.rbtn_pos_in, INSTALLPOS_IN);
	m_btnGroup_pos->addButton(ui.rbtn_pos_out, INSTALLPOS_OUT);
	connect(m_btnGroup_pos, SIGNAL(buttonClicked(int)), this, SLOT(slot_btnGroup_pos_clicked(int)));

	initTbl();

	connect(m_CmbParamDlg, SIGNAL(saveSuccessfully()), this, SLOT(freshCmbParam()));

	on_btn_collection_clicked();
}

void CmbVerifyDlg::initTbl()
{
	ui.tableWidget->setRowCount(m_metercount);
	QSignalMapper *signalMapper = new QSignalMapper();
	disconnect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
	for(int row=0; row<ui.tableWidget->rowCount(); row++)
	{
		for (int col=0; col < ui.tableWidget->columnCount(); col++)
		{
			ui.tableWidget->setItem(row, col, new QTableWidgetItem(QString("")));
			if( (col==COL_DELTA_V) || (col==COL_DELTA_E) || (col==COL_STD_E) || (col==COL_ERR) || (col==COL_STD_ERR) )
			{
				ui.tableWidget->item(row, col)->setFlags(Qt::NoItemFlags);
			}
		}

		ui.tableWidget->item(row, COL_E0)->setText("0");
		ui.tableWidget->item(row, COL_V0)->setText("0");

		QPushButton *btn_read_data = new QPushButton(tr("Read Data"));
		ui.tableWidget->setCellWidget(row, COL_READ_DATA, btn_read_data);
		signalMapper->setMapping(btn_read_data, row);
		connect(btn_read_data, SIGNAL(clicked()), signalMapper, SLOT(map()));
	}

	connect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
	connect(signalMapper, SIGNAL(mapped(const int &)), this, SLOT(slotReadData(const int &)));

// 	ui.tableWidget->resizeColumnsToContents();
}

void CmbVerifyDlg::slotReadData(const int &row)
{
	m_meterObj[row].askReadMeterData();
}

//自动读取表号成功 显示表号
void CmbVerifyDlg::slotSetMeterNumber(const QString& comName, const QString& meterNo)
{
	int meterPos = m_readComConfig->getMeterPosByComName(comName);
	if (meterPos < 1)
	{
		return;
	}
	ui.tableWidget->item(meterPos-1, COL_SN)->setText(meterNo.right(8)); //表号
}

void CmbVerifyDlg::slotSetMeterFlow(const QString& comName, const QString& flow)
{
	int meterPos = m_readComConfig->getMeterPosByComName(comName);
	if (meterPos < 1)
	{
		return;
	}
	if (!m_vol0_is_read[meterPos-1]) //初值
	{
		ui.tableWidget->item(meterPos - 1, COL_V0)->setText(flow);
	}
	else //终值
	{
		ui.tableWidget->item(meterPos - 1, COL_V1)->setText(flow);
	}
}

void CmbVerifyDlg::slotSetMeterHeat(const QString& portName, const QString& heat)
{
	int meterPos = m_readComConfig->getMeterPosByComName(portName);
	if (meterPos < 1)
	{
		return;
	}

	if (!m_eng0_is_read[meterPos - 1]) //初值
	{
		ui.tableWidget->item(meterPos - 1, COL_E0)->setText(heat);
	}
	else //终值
	{
		ui.tableWidget->item(meterPos - 1, COL_E1)->setText(heat);
	}
}

void CmbVerifyDlg::slotSetMeterTemp(const QString& portName, const QString& tempIn, const QString& tempOut)
{
	int meterPos = m_readComConfig->getMeterPosByComName(portName);
	if (meterPos < 1)
	{
		return;
	}
}

void CmbVerifyDlg::initMeterCom()
{
	if (NULL != m_meterObj)
	{
		delete []m_meterObj;
		m_meterObj = NULL;

		for (int i=0; i < m_metercount; i++)
		{
			m_meterThread[i].exit();
		}
	}

	m_meterThread = new ComThread[m_metercount];
	m_meterObj = new MeterComObject[m_metercount];
	int meter_type = m_param_config->value("common/manu").toInt();
	for (int i=0; i<m_metercount; i++)
	{
		m_meterObj[i].moveToThread(&m_meterThread[i]);
		m_meterObj[i].setProtocolVersion(meter_type); //设置表协议类型
		m_meterThread[i].start();
		m_meterObj[i].openMeterCom(&m_readComConfig->ReadMeterConfigByNum(i+1));

		connect(&m_meterObj[i], SIGNAL(readMeterNoIsOK(const QString&, const QString&)), this, SLOT(slotSetMeterNumber(const QString&, const QString&)));
		connect(&m_meterObj[i], SIGNAL(readMeterFlowIsOK(const QString&, const QString&)), this, SLOT(slotSetMeterFlow(const QString&, const QString&)));
		connect(&m_meterObj[i], SIGNAL(readMeterHeatIsOK(const QString&, const QString&)), this, SLOT(slotSetMeterHeat(const QString&, const QString&)));
		connect(&m_meterObj[i], SIGNAL(readMeterTemperIsOK(const QString&, const QString&, const QString&)), this, SLOT(slotSetMeterTemp(const QString&, const QString&, const QString&)));
	}
}

void CmbVerifyDlg::on_tableWidget_cellChanged(int row, int col)
{
	int row_count = ui.tableWidget->rowCount();
	//if ( (row == (row_count -1)) && (col == COL_SN))//最后一行的序列号列
	//{
	//	//必须先解除此信号-槽, 否则陷入死循环
	//	disconnect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
	//	addNewTblRow();
	//	connect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
	//}

	float v0, v1, e0, e1, stdE, deltaE, err, vol, energy;
	float disp_err;
	bool deltaE_OK = false;
	bool stdE_OK = false;
	bool is_valid = false;
	switch(col)
	{
		case COL_E0:
			m_eng0_is_read[row] = true;
			break;
		case COL_V0:
			m_vol0_is_read[row] = true;
			break;
		case COL_V1:
			//calcDeltaV
			v0 = ui.tableWidget->item(row, COL_V0)->text().trimmed().toFloat();
			v1 = ui.tableWidget->item(row, COL_V1)->text().trimmed().toFloat();
			ui.tableWidget->item(row, COL_DELTA_V)->setText(QString::number(v1-v0));
			break;
		case COL_E1:
			//calcDeltaE
			e0 = ui.tableWidget->item(row, COL_E0)->text().trimmed().toFloat();
			e1 = ui.tableWidget->item(row, COL_E1)->text().trimmed().toFloat();
			ui.tableWidget->item(row, COL_DELTA_E)->setText(QString::number(e1-e0));
			break;
		case COL_DELTA_V:
			//calcStdE
			vol = ui.tableWidget->item(row, COL_DELTA_V)->text().trimmed().toFloat();
			energy = getStdEnergy(vol);
			ui.tableWidget->item(row, COL_STD_E)->setText(QString::number(energy));
			ui.tableWidget->item(row, COL_STD_ERR)->setText("±" + QString::number(m_stdErrLmtByGrade));
			break;
		case COL_DELTA_E:
			//calcErr
			stdE  = ui.tableWidget->item(row, COL_STD_E)->text().trimmed().toFloat(&stdE_OK);
			if (!stdE_OK)
			{
				return;
			}
			deltaE = ui.tableWidget->item(row, COL_DELTA_E)->text().trimmed().toFloat();
// 			err = qAbs(deltaE - stdE)/stdE;
			err = (deltaE - stdE)/stdE;
			ui.tableWidget->item(row, COL_ERR)->setText(QString::number(err*100));
			break;
		case COL_STD_E:
			//calcErr
			deltaE = ui.tableWidget->item(row, COL_DELTA_E)->text().trimmed().toFloat(&deltaE_OK);
			if (!deltaE_OK)
			{
				return;
			}
			stdE = ui.tableWidget->item(row, COL_STD_E)->text().trimmed().toFloat();
			err = (deltaE - stdE)/stdE;
			ui.tableWidget->item(row, COL_ERR)->setText(QString::number(err*100));
			break;
		case COL_ERR:
			disp_err = qAbs(ui.tableWidget->item(row, COL_ERR)->text().toFloat());
			is_valid = disp_err <= m_stdErrLmtByGrade;//检测合格
			ui.tableWidget->item(row, COL_ERR)->setTextColor(is_valid ? QColor(0,0,0) : QColor(250,0,0));//合格显示黑色，不合格显示红色
			break;
		default:
			break;
	}
	ui.tableWidget->setCurrentCell(row+1, col);
}

void CmbVerifyDlg::slot_countdown_timerout()
{
	if (m_countdown <= 0)
	{
		m_timer->stop();
		ui.btnStart->setEnabled(true);
		ui.btnSave->setEnabled(true);
		ui.label_hint->setText(tr("please input meter V1 and E1, then click \"Save\" button!"));
		ui.tableWidget->setCurrentCell(0, COL_V1);
		return;
	}
	ui.label_hint->setText(tr("analog flow <font color=DarkGreen size=6><b>%1</b></font> m3/h, please wait for about <font color=DarkGreen size=6><b>%2</b></font> seconds")\
		.arg(IMITATION_FLOW_RATE).arg(m_countdown--));
}

void CmbVerifyDlg::slot_btnGroup_unit_clicked(int id)
{
	m_current_unit = id;
	m_unit_selected = true;
	QTableWidgetItem *item;
	if (m_current_unit == UNIT_KWH)
	{
		ui.tableWidget->horizontalHeaderItem(COL_E0)->setText(tr(HEAHER_E0_KWH));
		ui.tableWidget->horizontalHeaderItem(COL_E1)->setText(tr(HEAHER_E1_KWH));
		ui.tableWidget->horizontalHeaderItem(COL_DELTA_E)->setText(QApplication::translate("CmbVerifyClass", HEAHER_DELTAE_KWH, 0, QApplication::UnicodeUTF8));
		ui.tableWidget->horizontalHeaderItem(COL_STD_E)->setText(tr("StdE(kWh)"));
	}
	else if (m_current_unit == UNIT_MJ)
	{
		ui.tableWidget->horizontalHeaderItem(COL_E0)->setText(tr(HEAHER_E0_MJ));
		ui.tableWidget->horizontalHeaderItem(COL_E1)->setText(tr(HEAHER_E1_MJ));
		ui.tableWidget->horizontalHeaderItem(COL_DELTA_E)->setText(QApplication::translate("CmbVerifyClass", HEAHER_DELTAE_MJ, 0, QApplication::UnicodeUTF8));
		ui.tableWidget->horizontalHeaderItem(COL_STD_E)->setText(tr("StdE(MJ)"));
	}
	
	chkIfCanStartVerify();
}

void CmbVerifyDlg::slot_btnGroup_pos_clicked(int id)
{
	m_current_pos = id;
	m_pos_selected = true;
	chkIfCanStartVerify();
}

void CmbVerifyDlg::on_btnPara_clicked()
{
	if (NULL == m_CmbParamDlg)
	{
		m_CmbParamDlg = new CmbParamDlg();
	}
	else
	{
		delete m_CmbParamDlg;
		m_CmbParamDlg = new CmbParamDlg();
	}
	m_CmbParamDlg->show();
}

void CmbVerifyDlg::freshCmbParam()
{
	
}

void CmbVerifyDlg::on_btnStart_clicked()
{
	ui.btnStart->setEnabled(false);
	ui.btnSave->setEnabled(false);
	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //记录时间戳

	//if 初值回零
	for (int i=0; i<ui.tableWidget->rowCount(); i++)
	{
		ui.tableWidget->item(i, COL_V1)->setText("");
		ui.tableWidget->item(i, COL_E1)->setText("");
		ui.tableWidget->item(i, COL_DELTA_V)->setText("");
		ui.tableWidget->item(i, COL_DELTA_E)->setText("");
		ui.tableWidget->item(i, COL_STD_E)->setText("");
		ui.tableWidget->item(i, COL_ERR)->setText("");
	}

	int grade = m_param_config->value("common/grade").toInt();
	float min_temp_diff = ui.lineEdit_min_theta->text().toFloat();
	float set_tem_diff = m_param_config->value("diff/temp_deff").toFloat();
	float flow_rate = IMITATION_FLOW_RATE;
	float dn_flow_rate = m_param_config->value("common/dnflow").toFloat();
	m_stdErrLmtByGrade = qAbs(getMeterGradeErrLmt(grade, min_temp_diff, set_tem_diff, dn_flow_rate, flow_rate));

	int quantity = m_param_config->value("diff/quantity").toFloat();
	m_countdown = 3.6*quantity/flow_rate;

	m_timer->start(1000);
}

void CmbVerifyDlg::on_btnSave_clicked()
{
	if (saveVerifyRecords())
	{
		exportReport();//保存数据成功后立即导出报告
		ui.label_hint->setText(tr("save database and Excel successfully!"));
	}
	else
	{
		QMessageBox::information(this, tr("Hint"), tr("save database failed!"));
	}
}

void CmbVerifyDlg::exportReport()
{
	QString sqlCondition = QString("F_TimeStamp=\'%1\' and F_MethodFlag = 0").arg(m_timeStamp);
	QString xlsname = QDateTime::fromString(m_timeStamp, "yyyy-MM-dd HH:mm:ss.zzz").toString("yyyy-MM-dd_hh-mm-ss") + ".xls";
	try
	{
		QString defaultPath = QProcessEnvironment::systemEnvironment().value("ADEHOME") + "\\report\\cmb\\";
		CReport rpt(sqlCondition);
		rpt.setIniName("rptconfig_cmb.ini");
		rpt.writeRpt();
		rpt.saveTo(defaultPath + xlsname);
	}
	catch (QString e)
	{
		QMessageBox::warning(this, tr("Error"), e);
	}
}

int CmbVerifyDlg::saveVerifyRecords()
{
	int ret = 0;
	bool ok;
	float dispErr;
	int rowNum = ui.tableWidget->rowCount();
	int columnNum = ui.tableWidget->columnCount();
	
	for (int i=0; i < rowNum; i++)
	{
		if (ui.tableWidget->item(i, COL_ERR)->text().isEmpty())
		{
			continue;
		}
		dispErr = ui.tableWidget->item(i, COL_ERR)->text().toFloat(&ok);
		if (ok)
		{
			m_recPtr = new Cmb_Verify_Record_STR;
			memset(m_recPtr, 0, sizeof(Calc_Verify_Record_STR));
			strncpy_s(m_recPtr->F_TimeStamp, m_timeStamp.toAscii(), TIMESTAMP_LEN);
			strcpy_s(m_recPtr->F_MeterNo, ui.tableWidget->item(i, COL_SN)->text().trimmed().toAscii());
			m_recPtr->F_Standard = m_param_config->value("common/stand").toInt();
			m_recPtr->F_Model = m_param_config->value("common/model").toInt();
			m_recPtr->F_Grade = m_param_config->value("common/grade").toInt();
			m_recPtr->F_ManufactDept = m_param_config->value("common/manu").toInt();
			m_recPtr->F_VerifyDept = m_param_config->value("common/inst").toInt();
			m_recPtr->F_VerifyPerson = m_param_config->value("common/chk").toInt();
			m_recPtr->F_PickCode = m_param_config->value("common/collcode").toInt();
			
			m_recPtr->F_VerifyVolume = ui.tableWidget->item(i, COL_DELTA_V)->text().toFloat();
			m_recPtr->F_DeltaTempMin = m_min_tempdiff;
			m_recPtr->F_InstallPos = m_current_pos;
			m_recPtr->F_HeatUnit = m_current_unit;
			m_recPtr->F_StdTempIn = ui.lineEdit_std_in_t->text().toFloat();
			m_recPtr->F_StdTempOut = ui.lineEdit_std_out_t->text().toFloat();
			m_recPtr->F_DeltaTemp = m_param_config->value("diff/temp_deff").toFloat();

			m_recPtr->F_StdResistIn = ui.lineEdit_std_in_r->text().toFloat();
			m_recPtr->F_StdResistOut = ui.lineEdit_std_out_r->text().toFloat();
			m_recPtr->F_Kcoe = getKCoeByTemper(m_recPtr->F_StdTempIn, m_recPtr->F_StdTempOut);
			m_recPtr->F_StdValue = ui.tableWidget->item(i, COL_STD_E)->text().toFloat();
			m_recPtr->F_MeterV0 = ui.tableWidget->item(i, COL_V0)->text().toFloat();
			m_recPtr->F_MeterV1 = ui.tableWidget->item(i, COL_V1)->text().toFloat();
			m_recPtr->F_MeterE0 = ui.tableWidget->item(i, COL_E0)->text().toFloat();
			m_recPtr->F_MeterE1 = ui.tableWidget->item(i, COL_E1)->text().toFloat();
			m_recPtr->F_DispError = ui.tableWidget->item(i, COL_ERR)->text().toFloat();
			m_recPtr->F_StdError = m_stdErrLmtByGrade;
			m_recPtr->F_Result = qAbs(m_recPtr->F_DispError) <= qAbs(m_recPtr->F_StdError) ? 1 : 0;

			ret += insertCmbVerifyRec(m_recPtr, 1);
		}
	}

	return ret;
}

void CmbVerifyDlg::on_btnExit_clicked()
{
	this->close();
}

void CmbVerifyDlg::on_lineEdit_min_theta_textChanged(const QString & text)
{
	m_min_tempdiff = text.toFloat();
	m_min_tempdiff_set = true;
	chkIfCanStartVerify();
}

void CmbVerifyDlg::stdTempChanged()
{
	float in_t = ui.lineEdit_std_in_t->text().toFloat();
	float out_t = ui.lineEdit_std_out_t->text().toFloat();
	float delta_t = in_t - out_t;
	float set_temp_diff = m_param_config->value("diff/temp_deff").toFloat();
	m_delta_temp_achieved = (qAbs(delta_t) >= qAbs(set_temp_diff)) && (qAbs(delta_t) >= qAbs(m_min_tempdiff));
// 	chkIfCanStartVerify();
}

void CmbVerifyDlg::on_lineEdit_std_in_t_textChanged(const QString & text)
{
	stdTempChanged();
}

void CmbVerifyDlg::on_lineEdit_std_out_t_textChanged(const QString & text)
{
	stdTempChanged();
}

void CmbVerifyDlg::on_lineEdit_std_in_r_textChanged(const QString & text)
{
	float resis = text.toFloat();
	float temp = calcTemperByResis(resis);
	ui.lineEdit_std_in_t->setText(QString::number(temp));
}

void CmbVerifyDlg::on_lineEdit_std_out_r_textChanged(const QString & text)
{
	float resis = text.toFloat();
	float temp = calcTemperByResis(resis);
	ui.lineEdit_std_out_t->setText(QString::number(temp));
}

void CmbVerifyDlg::chkIfCanStartVerify()
{
	if (m_min_tempdiff_set && m_pos_selected && m_unit_selected && m_delta_temp_achieved)
	{
		emit verifyCanStart();
	}
}

void CmbVerifyDlg::startVerifySlot(void)
{
	ui.btnStart->setEnabled(true);
	ui.tableWidget->setEnabled(true);
	ui.label_hint->setText(tr("please input meter number, then click \"Start\" button!"));
	ui.tableWidget->setCurrentCell(0, COL_SN);
}

void CmbVerifyDlg::on_btn_collection_clicked()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadStdTempConfig();

	clearTempComObjs();
	m_sendTimer = new QTimer();
	m_tempObj = new StdTempComObject();
	QSettings stdconfig(getFullIniFileName("stdplasensor.ini"), QSettings::IniFormat);
	int ver = stdconfig.value("in_use/model").toInt();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	m_tempObj->setStdTempVersion(ver);
	connect(m_tempObj,SIGNAL(temperatureIsReady(const QString&)), this, SLOT(setStdTempUi(const QString&)));

	m_StdCommand = stdTempR1;

	connect(m_sendTimer, SIGNAL(timeout()), this, SLOT(sendCommands()));
	m_sendTimer->start(TIMEOUT_STD_TEMPER);
}

void CmbVerifyDlg::on_btn_stop_clicked()
{
	ui.lineEdit_std_in_t->setText("");
	ui.lineEdit_std_in_r->setText("");
	ui.lineEdit_std_out_t->setText("");
	ui.lineEdit_std_out_r->setText("");
	clearTempComObjs();
}

void CmbVerifyDlg::sendCommands()
{
	m_tempObj->writeStdTempComBuffer(m_StdCommand);
}

void CmbVerifyDlg::setStdTempUi(const QString &tempStr)
{
	switch(m_StdCommand)
	{
// 		case stdTempT1:
// 			ui.lineEdit_std_in_t->setText(tempStr);
// 			m_StdCommand = stdTempT2;
// 			break;
// 		case stdTempT2:
// 			ui.lineEdit_std_out_t->setText(tempStr);
// 			m_StdCommand = stdTempR1;
// 			break;
		case stdTempR1:
			ui.lineEdit_std_in_r->setText(tempStr);
			m_StdCommand = stdTempR2;
			break;
		case stdTempR2:
			ui.lineEdit_std_out_r->setText(tempStr);
			m_StdCommand = stdTempR1;
			break;
	}
}

void CmbVerifyDlg::clearTempComObjs()
{
	if (m_sendTimer != NULL)
	{
		if (m_sendTimer->isActive())
		{
			m_sendTimer->stop();
		}

		delete m_sendTimer;
		m_sendTimer = NULL;
	}

	if (m_tempObj != NULL)
	{
		delete m_tempObj;
		m_tempObj = NULL;

		m_tempThread.exit();
	}
}

float CmbVerifyDlg::getStdEnergy(float analogV)
{
	float in_t = ui.lineEdit_std_in_t->text().toFloat();
	float out_t = ui.lineEdit_std_out_t->text().toFloat();
	float delta_t = qAbs(in_t-out_t);
	float min_delta_t = qAbs(ui.lineEdit_min_theta->text().trimmed().toFloat());
	if (delta_t<min_delta_t)
	{
		QMessageBox::information(this, tr("Hint"), tr("current temperature different is less than min Δθ!"));
		return -1;
	}
	return m_algo->calcEnergyByEnthalpy(in_t, out_t, analogV, m_current_pos, m_current_unit);
}

/*
** 考虑能量单位，返回值单位：kWh/m3℃
** 
*/
float CmbVerifyDlg::getKCoeByTemper(float inTemper, float outTemper)
{
	float kCoe = m_algo->calcKCoeOfWater(inTemper, outTemper, m_current_pos, NORMAL_PRESSURE); //默认K系数单位MJ/m3℃
	if (m_current_unit==UNIT_KWH) //单位 kWh
	{
		kCoe /= 3.6; //由MJ/m3℃转换单位kWh/m3℃
	}

	return kCoe;
}