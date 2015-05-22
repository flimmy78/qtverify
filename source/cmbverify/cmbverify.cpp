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
#include <QTest>
#include <QtSql/QSqlTableModel>
#include <QtGui/QFileDialog>
#include <QtCore/QSignalMapper>
#include <math.h>
#include "qtexdb.h"
#include "cmbverify.h"

CmbVerifyDlg::CmbVerifyDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
}

CmbVerifyDlg::~CmbVerifyDlg()
{
}

void CmbVerifyDlg::showEvent(QShowEvent *)
{
	m_CmbParamDlg = NULL;
	m_sendTimer = NULL;
	m_tempObj = NULL;
	
	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //记录时间戳
	m_param_config = new QSettings(getFullIniFileName("cmbparam.ini"), QSettings::IniFormat);
	m_algo = new CAlgorithm;
	m_readComConfig = new ReadComConfig();

	m_pos_selected = false;
	m_unit_selected = false;
	m_min_tempdiff_set = false;
	m_delta_temp_achieved = false;

	initUi();
	connect(this, SIGNAL(vefifyCanStart(void)), this, SLOT(startVefifySlot(void)));

	m_meterObj = NULL;
	for (int i=0;i<MAX_METER_NUM;i++)
	{
		m_val0_is_read[i] = false;
	}
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

		for (int i=0; i<MAX_METER_NUM; i++)
		{
			m_meterThread[i].exit();
		}
	}
	clearTempComObjs();
}

void CmbVerifyDlg::initUi()
{
	
	m_btnGroup_unit = new QButtonGroup(ui.gbox_unit); //计量单位
	m_btnGroup_unit->addButton(ui.rbtn_unit_kwh, UNIT_KWH);
	m_btnGroup_unit->addButton(ui.rbtn_unit_mj, UNIT_MJ);
	connect(m_btnGroup_unit, SIGNAL(buttonClicked(int)), this, SLOT(on_btnGroup_unit_clicked(int)));

	m_btnGroup_pos = new QButtonGroup(ui.gbox_install_pos);//安装位置
	m_btnGroup_pos->addButton(ui.rbtn_pos_in, INSTALLPOS_IN);
	m_btnGroup_pos->addButton(ui.rbtn_pos_out, INSTALLPOS_OUT);
	connect(m_btnGroup_pos, SIGNAL(buttonClicked(int)), this, SLOT(on_btnGroup_pos_clicked(int)));

	initTbl();

	connect(m_CmbParamDlg, SIGNAL(saveSuccessfully(void)), this, SLOT(freshCmbParam(void)));

	on_btn_collection_clicked();
}

void CmbVerifyDlg::initTbl()
{
	ui.tableWidget->setRowCount(MAX_METER_NUM);
	QSignalMapper *m_signalMapper = new QSignalMapper();
	disconnect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
	for(int row=0;row<MAX_METER_NUM;row++)
	{
		for (int col=0; col < COL_NUM; col++)
		{

			if( (col==COL_IN_T) || (col==COL_OUT_T) || (col==COL_DELTA_E) || (col==COL_DELTA_V) || (col==COL_STD_E) || (col==COL_ERR) )
			{
				QTableWidgetItem* item = new QTableWidgetItem();
				item->setFlags(Qt::NoItemFlags);
				ui.tableWidget->setItem(row, col, item);
			}
			else if( (col==COL_SN) || (col==COL_E0) || (col==COL_V0) || (col==COL_V1) || (col==COL_E1) )
			{
				QTableWidgetItem* item = new QTableWidgetItem();
				item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
				ui.tableWidget->setItem(row, col, item);
			}
			else if (col==COL_READ_DATA)
			{
				QPushButton *btn_read_data = new QPushButton(tr("Read Data"));
				ui.tableWidget->setCellWidget(row, COL_READ_DATA, btn_read_data);
				m_signalMapper->setMapping(btn_read_data, row);
				connect(btn_read_data, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
			}
		}
	}
	connect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));

	connect(m_signalMapper, SIGNAL(mapped(const int &)), this, SLOT(slotReadData(const int &)));

	ui.tableWidget->resizeColumnsToContents();
}

void CmbVerifyDlg::slotReadData(const int &row)
{
	m_meterObj[row].askReadMeter();
}

//自动读取表号成功 显示表号
void CmbVerifyDlg::slotSetMeterNumber(const QString& comName, const QString& meterNo)
{
	int meterPos = m_readComConfig->getMeterPosByComName(comName);
	if (meterPos < 1)
	{
		return;
	}
	ui.tableWidget->setItem(meterPos-1, COL_SN, new QTableWidgetItem(meterNo.right(8))); //表号
}

void CmbVerifyDlg::slotSetMeterFlow(const QString& comName, const float& flow)
{
	int meterPos = m_readComConfig->getMeterPosByComName(comName);
	if (meterPos < 1)
	{
		return;
	}
	if (!m_val0_is_read[meterPos-1]) //初值
	{
		ui.tableWidget->setItem(meterPos - 1, COL_V0, new QTableWidgetItem(QString::number(flow)));
	}
	else //终值
	{
		ui.tableWidget->setItem(meterPos - 1, COL_V1, new QTableWidgetItem(QString::number(flow)));
	}
}

void CmbVerifyDlg::slotSetMeterHeat(const QString& portName, const QString& heat)
{
	int meterPos = m_readComConfig->getMeterPosByComName(portName);
	if (meterPos < 1)
	{
		return;
	}

	if (!m_val0_is_read[meterPos-1]) //初值
	{
		ui.tableWidget->setItem(meterPos - 1, COL_E0, new QTableWidgetItem(heat));
	}
	else //终值
	{
		ui.tableWidget->setItem(meterPos - 1, COL_E1, new QTableWidgetItem(heat));
	}
}

void CmbVerifyDlg::slotSetMeterTemp(const QString& portName, const QString& tempIn, const QString& tempOut)
{
	int meterPos = m_readComConfig->getMeterPosByComName(portName);
	if (meterPos < 1)
	{
		return;
	}

	ui.tableWidget->setItem(meterPos - 1, COL_IN_T, new QTableWidgetItem(tempIn));
	ui.tableWidget->setItem(meterPos - 1, COL_OUT_T, new QTableWidgetItem(tempOut));
}

void CmbVerifyDlg::initMeterCom()
{
	if (NULL != m_meterObj)
	{
		delete []m_meterObj;
		m_meterObj = NULL;

		for (int i=0; i < MAX_METER_NUM; i++)
		{
			m_meterThread[i].exit();
		}
	}

	m_meterThread = new ComThread[MAX_METER_NUM];
	m_meterObj = new MeterComObject[MAX_METER_NUM];
	int meter_type = m_param_config->value("common/manu").toInt();
	for (int i=0; i<MAX_METER_NUM; i++)
	{
		m_meterObj[i].moveToThread(&m_meterThread[i]);
		m_meterObj[i].setProtocolVersion(meter_type); //设置表协议类型
		m_meterThread[i].start();
		m_meterObj[i].openMeterCom(&m_readComConfig->ReadMeterConfigByNum(QString("%1").arg(i+1)));

		connect(&m_meterObj[i], SIGNAL(readMeterNoIsOK(const QString&, const QString&)), this, SLOT(slotSetMeterNumber(const QString&, const QString&)));
		connect(&m_meterObj[i], SIGNAL(readMeterFlowIsOK(const QString&, const float&)), this, SLOT(slotSetMeterFlow(const QString&, const float&)));

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

	ui.tableWidget->setCurrentCell(row, col+1);
	QString sn;
	float v0, v1, e0, e1, stdE, deltaE, err, vol, energy;
	switch(col)
	{
		case COL_SN:

			ui.tableWidget->setCurrentCell(row+1, COL_SN);
			break;
		case COL_E0:
			m_val0_is_read[row] = true;
			ui.tableWidget->setCurrentCell(row, COL_V0);
			break;
		case COL_V0:
			m_val0_is_read[row] = true;
			sn = ui.tableWidget->item(row+1, COL_SN)->text();
			if (row < ui.tableWidget->rowCount() && !sn.isEmpty() && !sn.isNull())
			{
				ui.tableWidget->setCurrentCell(row+1, COL_V1);
			}
			break;
		case COL_V1:
			//calcDeltaV
			v0 = ui.tableWidget->item(row, COL_V0)->text().trimmed().toFloat();
			v1 = ui.tableWidget->item(row, COL_V1)->text().trimmed().toFloat();
			ui.tableWidget->item(row, COL_DELTA_V)->setText(QString::number(v1-v0));
			ui.tableWidget->setCurrentCell(row, COL_E1);
			break;
		case COL_E1:
			//calcDeltaE
			e0 = ui.tableWidget->item(row, COL_E0)->text().trimmed().toFloat();
			e1 = ui.tableWidget->item(row, COL_E1)->text().trimmed().toFloat();
			ui.tableWidget->item(row, COL_DELTA_E)->setText(QString::number(e1-e0));
			break;
		case COL_DELTA_E:
			//calcErr
			stdE   = ui.tableWidget->item(row, COL_STD_E)->text().trimmed().toFloat();
			deltaE = ui.tableWidget->item(row, COL_DELTA_E)->text().trimmed().toFloat();
			err = qAbs(deltaE - stdE)/stdE;
			ui.tableWidget->item(row, COL_ERR)->setText(QString::number(err*100));
			break;
		case COL_DELTA_V:
			//calcStdE
			vol = ui.tableWidget->item(row, COL_DELTA_V)->text().trimmed().toFloat();
			energy = getStdEnergy(vol);
			ui.tableWidget->item(row, COL_STD_E)->setText(QString::number(energy));
			break;
		case COL_STD_E:
			break;
		default:
			break;
	}
}
//
//void CmbVerifyDlg::addNewTblRow(QSignalMapper *m_signalMapper)
//{
//	int old_rows = ui.tableWidget->rowCount();
//	int new_rows =  old_rows + 1;
//	if (new_rows > MAX_METER_NUM)
//	{
//		return;
//	}
//
//	ui.tableWidget->setRowCount(new_rows);
//	
//	for (int col=0; col < COL_NUM; col++)
//	{
//		
//		if( (col==COL_IN_T) || (col==COL_OUT_T) || (col==COL_DELTA_E) || (col==COL_DELTA_V) || (col==COL_STD_E) || (col==COL_ERR) )
//		{
//			QTableWidgetItem* item = new QTableWidgetItem();
//			item->setFlags(Qt::NoItemFlags);
//			ui.tableWidget->setItem(old_rows, col, item);
//		}
//		else if( (col==COL_SN) || (col==COL_E0) || (col==COL_V0) || (col==COL_V1) || (col==COL_E1) )
//		{
//			QTableWidgetItem* item = new QTableWidgetItem();
//			item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
//			ui.tableWidget->setItem(old_rows, col, item);
//		}
//		else if (col==COL_READ_SN)
//		{
//			QPushButton *btn_read_sn = new QPushButton(tr("Read Serial"));
//			ui.tableWidget->setCellWidget(old_rows, COL_READ_SN, btn_read_sn);
//			m_signalMapper[0].setMapping(btn_read_sn, old_rows);
//			connect(btn_read_sn, SIGNAL(clicked()), &m_signalMapper[0], SLOT(map()));
//		}
//		else if (col==COL_READ_DATA)
//		{
//			QPushButton *btn_read_data = new QPushButton(tr("Read Data"));
//			ui.tableWidget->setCellWidget(old_rows, COL_READ_DATA, btn_read_data);
//			m_signalMapper[1].setMapping(btn_read_data, old_rows);
//			connect(btn_read_data, SIGNAL(clicked()), &m_signalMapper[1], SLOT(map()));
//		}
//		else if (col==COL_READ_TEMP)
//		{
//			QPushButton *btn_read_temp = new QPushButton(tr("Read Temp"));
//			ui.tableWidget->setCellWidget(old_rows, COL_READ_TEMP, btn_read_temp);
//			m_signalMapper[2].setMapping(btn_read_temp, old_rows);
//			connect(btn_read_temp, SIGNAL(clicked()), &m_signalMapper[2], SLOT(map()));
//		}
//		
//	}
//}

void CmbVerifyDlg::on_btnGroup_unit_clicked(int id)
{
	m_current_unit = id;
	m_unit_selected = true;
	chkIfCanStartVerify();
}

void CmbVerifyDlg::on_btnGroup_pos_clicked(int id)
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
	connect(m_CmbParamDlg, SIGNAL(saveSuccessfully()), this, SLOT(freshCmbParam()));
	m_CmbParamDlg->show();
}

void CmbVerifyDlg::freshCmbParam(void)
{
	
}

void CmbVerifyDlg::on_btnStart_clicked()
{
	ui.tableWidget->setEnabled(true);
	ui.btn_collection->setEnabled(true);
	ui.btn_stop->setEnabled(true);
	ui.btnSave->setEnabled(true);
}

void CmbVerifyDlg::on_btnSave_clicked()
{
	startdb();
	if (saveVerifyRecords())
	{
		QMessageBox::information(this, tr("Hint"), tr("save database successful !"));
	}
	else
	{
		QMessageBox::information(this, tr("Hint"), tr("save database failed !"));
	}
	closedb();
}

int CmbVerifyDlg::saveVerifyRecords()
{
	int ret = 0;
	bool ok;
	float dispErr;
	int rowNum = ui.tableWidget->rowCount();
	int columnNum = ui.tableWidget->columnCount();
	int grade = m_param_config->value("common/grade").toInt();
	float flow_rate = IMITATION_FLOW_RATE;
	float dn_flow_rate = m_param_config->value("common/dnflow").toFloat();
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
			//m_recPtr->deltaTidx = mapIdx[i];
			m_recPtr->F_Standard = m_param_config->value("common/stand").toInt();
			m_recPtr->F_Model = m_param_config->value("common/model").toInt();
			m_recPtr->F_Grade = m_param_config->value("common/grade").toInt();
			m_recPtr->F_ManufactDept = m_param_config->value("common/manu").toInt();
			m_recPtr->F_VerifyDept = m_param_config->value("common/inst").toInt();
			m_recPtr->F_VerifyPerson = m_param_config->value("common/chk").toInt();
			
			m_recPtr->F_VerifyVolume = ui.tableWidget->item(i, COL_DELTA_V)->text().toFloat();
			m_recPtr->F_DeltaTempMin = m_min_tempdiff;
			m_recPtr->F_InstallPos = m_current_pos;
			m_recPtr->F_HeatUnit = m_current_unit;
			m_recPtr->F_StdTempIn = ui.lineEdit_std_in_t->text().toFloat();
			m_recPtr->F_StdTempOut = ui.lineEdit_std_out_t->text().toFloat();
			m_recPtr->F_DeltaTemp = m_recPtr->F_StdTempIn - m_recPtr->F_StdTempOut;

			m_recPtr->F_StdResistIn = ui.lineEdit_std_in_r->text().toFloat();
			m_recPtr->F_StdResistOut = ui.lineEdit_std_out_r->text().toFloat();
			m_recPtr->F_Kcoe = getKCoeByTemper(m_recPtr->F_StdTempIn, m_recPtr->F_StdTempOut);
			m_recPtr->F_StdValue = ui.tableWidget->item(i, COL_STD_E)->text().toFloat();
			m_recPtr->F_MeterV0 = ui.tableWidget->item(i, COL_V0)->text().toFloat();
			m_recPtr->F_MeterV1 = ui.tableWidget->item(i, COL_V1)->text().toFloat();
			m_recPtr->F_MeterE0 = ui.tableWidget->item(i, COL_E0)->text().toFloat();
			m_recPtr->F_MeterE1 = ui.tableWidget->item(i, COL_E1)->text().toFloat();
			m_recPtr->F_DispError = ui.tableWidget->item(i, COL_ERR)->text().toFloat();
			m_recPtr->F_StdError = getMeterGradeErrLmt(grade, m_min_tempdiff, m_recPtr->F_DeltaTemp, dn_flow_rate, flow_rate);
			m_recPtr->F_Result = m_recPtr->F_StdError <= m_recPtr->F_DispError ? 1 : 0;

			ret += insertCmbVerifyRec(m_recPtr, 1);
		}
	}

	return ret;
}

void CmbVerifyDlg::on_btnExit_clicked()
{
	this->close();
}

void CmbVerifyDlg::on_lineEdit_min_theta_textEdited(const QString & text)
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
	m_delta_temp_achieved = (qAbs(delta_t) >= qAbs(set_temp_diff));
	chkIfCanStartVerify();
}

void CmbVerifyDlg::on_lineEdit_std_in_t_textChanged(const QString & text)
{
	stdTempChanged();
}

void CmbVerifyDlg::on_lineEdit_std_out_t_textChanged(const QString & text)
{
	stdTempChanged();
}

void CmbVerifyDlg::chkIfCanStartVerify()
{
	if (m_min_tempdiff_set && m_pos_selected && m_unit_selected && m_delta_temp_achieved)
	{
		emit vefifyCanStart();
	}
}

void CmbVerifyDlg::startVefifySlot(void)
{
	ui.btnStart->setEnabled(true);
	
}

void CmbVerifyDlg::on_btn_collection_clicked()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadStdTempConfig();

	clearTempComObjs();
	m_sendTimer = new QTimer();
	m_tempObj = new Sti1062aComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj,SIGNAL(temperatureIsReady(const QString&)), this, SLOT(setStdTempUi(const QString&)));

	m_StdCommand = sti1062aT1;
	connect(m_sendTimer, SIGNAL(timeout()), this, SLOT(sendCommands()));
	m_sendTimer->start(READ_STI1062A_TIMEOUT);
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
	m_tempObj->writeTemperatureComBuffer(m_StdCommand);
}

void CmbVerifyDlg::setStdTempUi(const QString &tempStr)
{
	switch(m_StdCommand)
	{
		case sti1062aT1:
			ui.lineEdit_std_in_t->setText(tempStr);
			m_StdCommand = sti1062aT2;
			break;
		case sti1062aT2:
			ui.lineEdit_std_out_t->setText(tempStr);
			m_StdCommand = sti1062aR1;
			break;
		case sti1062aR1:
			ui.lineEdit_std_in_r->setText(tempStr);
			m_StdCommand = sti1062aR2;
			break;
		case sti1062aR2:
			ui.lineEdit_std_out_r->setText(tempStr);
			m_StdCommand = sti1062aT1;
			break;
	}
}

void CmbVerifyDlg::clearTempComObjs()
{
	if (NULL != m_sendTimer)
	{
		if (m_sendTimer->isActive())
		{
			m_sendTimer->stop();
		}

		delete m_sendTimer;
		m_sendTimer = NULL;
	}

	if (NULL != m_tempObj)
	{
		m_tempObj->close();
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
	return getEnergyByEnthalpy(analogV, in_t, out_t);
}

float CmbVerifyDlg::getEnergyByEnthalpy(float analogV, float inTemper, float outTemper)
{
	float energy = 0.0;
	float density = 0.0;

	float diffEnthalpy = getEnthalpyDiffByTemper(inTemper, outTemper);
	if (m_current_pos==INSTALLPOS_IN) //安装位置：进口
	{
		density = m_algo->getDensityByQuery(inTemper);
	}
	else if (m_current_pos==INSTALLPOS_OUT) //安装位置：出口
	{
		density = m_algo->getDensityByQuery(outTemper);
	}

	float mass = analogV*density;//物体质量, kg
	energy = mass*diffEnthalpy;//kJ

	if (m_current_unit == UNIT_KWH)
	{
		energy = energy/3600;//单位转换，kJ->kwh
	}
	else if (m_current_unit == UNIT_MJ)
	{
		energy = energy/1000;
	}
	return energy;
}

float CmbVerifyDlg::getEnthalpyDiffByTemper(float inT, float outT)
{
	float inEnthalpy = m_algo->getEnthalpyByQuery(inT); //焓值，单位kJ/kg
	float outEnthalpy = m_algo->getEnthalpyByQuery(outT);

	return inEnthalpy-outEnthalpy;
}

/*
** 考虑能量单位，返回值单位：kWh/m3℃
** 
*/
float CmbVerifyDlg::getKCoeByTemper(float inTemper, float outTemper)
{
	float kCoe = m_algo->CalcKCoeOfWater(inTemper, outTemper, m_current_pos, NORMAL_PRESSURE); //默认K系数单位MJ/m3℃
	if (m_current_unit==UNIT_KWH) //单位 kWh
	{
		kCoe /= 3.6; //由MJ/m3℃转换单位kWh/m3℃
	}

	return kCoe;
}