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
	
	m_param_config = new QSettings(getFullIniFileName("cmbparam.ini"), QSettings::IniFormat);
	m_algo = new CAlgorithm;
	m_readComConfig = new ReadComConfig();

	m_pos_selected = false;
	m_unit_selected = false;
	m_min_tempdiff_set = false;
	initUi();

	connect(this, SIGNAL(vefifyCanStart(void)), this, SLOT(startVefifySlot(void)));
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

	clearTempComObjs();
}

void CmbVerifyDlg::initUi()
{
	m_btnGroup_unit = new QButtonGroup(ui.gbox_unit); //计量单位
	m_btnGroup_unit->addButton(ui.rbtn_unit_kwh, UNIT_KWH);
	m_btnGroup_unit->addButton(ui.rbtn_unit_mj, UNIT_MJ);
	connect(m_btnGroup_unit, SIGNAL(buttonClicked(int)), this, SLOT(on_btnGroup_unit_clicked(int)));

	m_btnGroup_pos = new QButtonGroup(ui.gbox_install_pos);//安装位置
	m_btnGroup_pos->addButton(ui.rbtn_pos_in, POS_IN);
	m_btnGroup_pos->addButton(ui.rbtn_pos_out, POS_OUT);
	connect(m_btnGroup_pos, SIGNAL(buttonClicked(int)), this, SLOT(on_btnGroup_pos_clicked(int)));

	ui.tableWidget->item(0, COL_IN_T)->setFlags(Qt::NoItemFlags);
	ui.tableWidget->item(0, COL_OUT_T)->setFlags(Qt::NoItemFlags);
	ui.tableWidget->item(0, COL_ERR)->setFlags(Qt::NoItemFlags);
	ui.tableWidget->item(0, COL_DELTA_E)->setFlags(Qt::NoItemFlags);
	ui.tableWidget->item(0, COL_DELTA_V)->setFlags(Qt::NoItemFlags);
	ui.tableWidget->item(0, COL_STD_E)->setFlags(Qt::NoItemFlags);
}

void CmbVerifyDlg::on_tableWidget_cellChanged(int row, int col)
{
	int row_count = ui.tableWidget->rowCount();
	if ( (row == (row_count -1)) && (col == COL_SN))//最后一行的序列号列
	{
		//必须先解除此信号-槽, 否则陷入死循环
		disconnect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
		addNewTblRow();
		connect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
	}

	ui.tableWidget->setCurrentCell(row, col+1);
	QString sn;
	float v0, v1, e0, e1, stdE, deltaE, err, vol, energy;
	switch(col)
	{
		case COL_SN:

			ui.tableWidget->setCurrentCell(row+1, COL_SN);
			break;
		case COL_E0:

			ui.tableWidget->setCurrentCell(row, COL_V0);
			break;
		case COL_V0:
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

void CmbVerifyDlg::addNewTblRow()
{
	int old_rows = ui.tableWidget->rowCount();
	int new_rows =  old_rows + 1;
	if (new_rows > MAX_METER_NUM)
	{
		return;
	}

	ui.tableWidget->setRowCount(new_rows);

	for (int col=0; col < COL_NUM; col++)
	{
		QTableWidgetItem* item = new QTableWidgetItem();
		if( (col!=COL_IN_T) && (col!=COL_OUT_T) && (col!=COL_ERR) && (col!=COL_DELTA_E) && (col!=COL_DELTA_V) && (col!=COL_STD_E) )
			item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
		else
			item->setFlags(Qt::NoItemFlags);
		ui.tableWidget->setItem(old_rows, col, item);
	}
}

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

}

void CmbVerifyDlg::on_btnSave_clicked()
{

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

void CmbVerifyDlg::chkIfCanStartVerify()
{
	if (m_min_tempdiff_set && m_pos_selected && m_unit_selected)
	{
		emit vefifyCanStart();
	}
}

void CmbVerifyDlg::startVefifySlot(void)
{
	ui.btnStart->setEnabled(true);
	ui.tableWidget->setEnabled(true);
	ui.btn_collection->setEnabled(true);
	ui.btn_stop->setEnabled(true);
	on_btn_collection_clicked();
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
	if (m_current_pos==POS_IN) //安装位置：进口
	{
		density = m_algo->getDensityByQuery(inTemper);
	}
	else if (m_current_pos==POS_OUT) //安装位置：出口
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