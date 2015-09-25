/***********************************************
**  文件名:     totalweight.cpp
**  功能:       总量检定(质量法)主界面
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/3/2
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2015/03 第一版
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
#include <QCloseEvent>
#include <math.h>

#include "totalstandard.h"
#include "commondefine.h"
#include "algorithm.h"
#include "qtexdb.h"
#include "parasetdlg.h"
#include "readcomconfig.h"
#include "report.h"

TotalStandardDlg::TotalStandardDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"TotalStandardDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);
	m_stdParam = new QSettings(getFullIniFileName("stdmtrparaset.ini"), QSettings::IniFormat);
	//不同等级的热量表对应的标准误差,单位%
	m_gradeErrA[1] = 2.00f;
	m_gradeErrA[2] = 3.00f;
	m_gradeErrA[3] = 4.00f;

	m_gradeErrB[1] = 0.01f;
	m_gradeErrB[2] = 0.02f;
	m_gradeErrB[3] = 0.05f;

	m_mapNormalFlow[0] = 1.5f; //DN15常用流量 1.5
	m_mapNormalFlow[1] = 2.5f; //DN20常用流量 2.5
	m_mapNormalFlow[2] = 3.5f; //DN25常用流量 3.5

	///////////////////////////////// 原showEvent()函数的内容 begin 
	//否则每次最小化再显示时，会调用showEvent函数，导致内容清空等现象
	ui.btnReCalc->hide();
	ui.btnExhaust->hide();
	ui.btnGoOn->hide();

	if (!getPortSetIni(&m_portsetinfo)) //获取下位机端口号配置信息
	{
		QMessageBox::warning(this, tr("Warning"), tr("Warning:get port set info failed!"));
	}

	m_readComConfig = new ReadComConfig(); //读串口设置接口（必须在initBalanceCom前调用）

	m_instantFlowCom = NULL;
	m_instSTDMeterTimer = NULL;
	initInstStdCom();//初始化瞬时流量串口

	m_accumulateFlowCom = NULL;
	m_accumSTDMeterTimer = NULL;
	initAccumStdCom();//初始化累积流量串口

	m_tempObj = NULL;
	m_tempTimer = NULL;
	initTemperatureCom();	//初始化温度采集串口

	m_stdTempObj = NULL;
	m_stdTempTimer = NULL;
	initStdTemperatureCom(); //初始化标准温度采集串口

	m_controlObj = NULL;
	initControlCom();		//初始化控制串口

	m_meterObj = NULL;      //热量表通讯
	m_recPtr = NULL;        //流量检测结果

	btnGroupEnergyUnit = new QButtonGroup(ui.groupBoxEnergyUnit); //能量单位
	btnGroupEnergyUnit->addButton(ui.radioButtonMJ, UNIT_MJ);
	btnGroupEnergyUnit->addButton(ui.radioButtonKwh, UNIT_KWH);
	connect(btnGroupEnergyUnit, SIGNAL(buttonClicked(int)), this, SLOT(slot_btnGroupEnergyUnit_clicked(int)));
	ui.radioButtonKwh->setChecked(true); //默认单位:kWh
	m_unit = UNIT_KWH;

	btnGroupInstallPos = new QButtonGroup(ui.groupBoxInstallPos); //安装位置
	btnGroupInstallPos->addButton(ui.radioButtonPosIn, INSTALLPOS_IN);
	btnGroupInstallPos->addButton(ui.radioButtonPosOut, INSTALLPOS_OUT);
	connect(btnGroupInstallPos, SIGNAL(buttonClicked(int)), this, SLOT(slot_btnGroupInstallPos_clicked(int)));
	ui.radioButtonPosIn->setChecked(true); //默认入口安装
	m_installPos = INSTALLPOS_IN;

	m_minDeltaT = 3.0; //最小温差
	ui.lnEditMinDeltaT->setText(QString::number(m_minDeltaT));

	//计算类接口
	m_chkAlg = new CAlgorithm();

	//映射关系；初始化阀门状态	
	initValveStatus();

	m_exaustTimer = new QTimer(this); //排气定时器
	connect(m_exaustTimer, SIGNAL(timeout()), this, SLOT(slotExaustFinished()));

	m_stopFlag = true; //停止检测标志（退出界面后，不再检查天平容量）

	m_avgTFCount = 1; //计算平均温度用的累加计数器
	m_nowOrder = 0;  //当前进行的检定序号

	m_nowParams = NULL;
	m_continueVerify = true; //连续检定
	m_resetZero = false;     //初值回零
	m_autopick = false;      //自动采集
	m_flowPointNum = 0;      //流量点个数
	m_maxMeterNum = 0;       //某规格表最多支持的检表个数
	m_oldMaxMeterNum = 0;
	m_validMeterNum = 0;     //实际检表个数
	m_exaustSecond = 45;     //默认排气时间45秒
	m_pickcode = PROTOCOL_VER_DELU; //采集代码 默认德鲁
	m_totalSC = 1.0;			 //总量安全系数，默认1.0
	m_meterStartValue = NULL;
	m_meterEndValue = NULL;
	m_meterTemper = NULL;
	m_meterDensity = NULL;
	m_meterStdValue = NULL;
	m_meterError = NULL;
	m_meterErr = NULL;
	m_meterResult = NULL;
	m_stdStartVol = 0;
	m_stdEndVol = 0;
	m_StdStartMass = 0;
	m_StdEndMass = 0;
	m_timeStamp = "";
	m_nowDate = "";
	m_validDate = "";

	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable("T_Meter_Standard");  
	model->select();  
	m_meterStdMapper = new QDataWidgetMapper(this);
	m_meterStdMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	m_meterStdMapper->setModel(model);
	m_meterStdMapper->addMapping(ui.lnEditStandard, 1); //映射表"T_Meter_Standard"的第二个字段

	m_paraSetDlg = NULL;    //参数设置对话框
	m_paraSetReader = new ParaSetReader(); //读参数设置接口
	if (!readNowParaConfig()) //获取当前检定参数
	{
		qWarning()<<"读取参数配置文件失败!";
	}

	if (!isComAndPortNormal())
	{
		qWarning()<<"串口、端口设置错误!";
	}

	///////////////////////////////// 原showEvent()函数的内容 end
}

TotalStandardDlg::~TotalStandardDlg()
{
	qDebug()<<"TotalStandardDlg::showEvent";
}

void TotalStandardDlg::showEvent(QShowEvent * event)
{
}

void TotalStandardDlg::closeEvent(QCloseEvent * event)
{
	qDebug()<<"^^^^^TotalStandardDlg::closeEvent";
	int button = QMessageBox::question(this, tr("Question"), tr("Exit Really ?"), \
		QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape);
	if (button == QMessageBox::No)
	{
		return event->ignore();
	}
	else
	{
		event->accept();
	}

	if (!m_stopFlag)
	{
		m_stopFlag = true;
		closeAllValveAndPumpOpenOutValve();
	 	wait(CYCLE_TIME);
	}
	openWaterOutValve();
	ui.labelHintPoint->clear();
	ui.labelHintProcess->setText(tr("release pipe pressure..."));
	openValve(m_portsetinfo.bigNo); //打开大流量点阀门，释放管路压力
 	wait(RELEASE_PRESS_TIME); //等待2秒，释放管路压力
	closeValve(m_portsetinfo.bigNo);
	ui.labelHintProcess->clear();
	ui.btnStart->setEnabled(true);

	if (m_paraSetReader) //读检定参数
	{
		delete m_paraSetReader;
		m_paraSetReader = NULL;
	}

	if (m_paraSetDlg)    //参数设置对话框
	{
		delete m_paraSetDlg;
		m_paraSetDlg = NULL;
	}

	if (m_readComConfig) //读串口设置
	{
		delete m_readComConfig;
		m_readComConfig = NULL;
	}

	if (m_tempObj)  // 温度采集
	{
		delete m_tempObj;
		m_tempObj = NULL;

		m_tempThread.exit(); //否则日志中会有警告"QThread: Destroyed while thread is still running"
	}

	if (m_tempTimer) //采集温度计时器
	{
		if (m_tempTimer->isActive())
		{
			m_tempTimer->stop();
		}
		delete m_tempTimer;
		m_tempTimer = NULL;
	}

	if (m_stdTempTimer) //标准温度采集计时器, 必须先于串口对象停掉
	{
		if (m_stdTempTimer->isActive())
		{
			m_stdTempTimer->stop();
		}
		delete m_stdTempTimer;
		m_stdTempTimer = NULL;
	}

	if (m_stdTempObj)  // 标准温度采集
	{
		delete m_stdTempObj;
		m_stdTempObj = NULL;

		m_stdTempThread.exit();
	}	

	if (m_controlObj)  //阀门控制
	{
		delete m_controlObj;
		m_controlObj = NULL;

		m_valveThread.exit();
	}

	if (m_chkAlg)//计算类
	{
		delete m_chkAlg;
		m_chkAlg = NULL;
	}

	//热量表通讯
	if (m_meterObj)
	{
		delete []m_meterObj;
		m_meterObj = NULL;

		for (int i=0; i<m_oldMaxMeterNum; i++)
		{
			m_meterThread[i].exit();
		}
	}

	if (m_exaustTimer) //排气计时器
	{
		if (m_exaustTimer->isActive())
		{
			m_exaustTimer->stop();
		}
		delete m_exaustTimer;
		m_exaustTimer = NULL;
	}

	if (m_instSTDMeterTimer)
	{
		if (m_instSTDMeterTimer->isActive())
		{
			m_instSTDMeterTimer->stop();
		}

		delete m_instSTDMeterTimer;
		m_instSTDMeterTimer = NULL;
	}

	if (m_instantFlowCom)
	{
		m_instantFlowThread.exit();
		delete m_instantFlowCom;
		m_instantFlowCom = NULL;
	}

	if (m_accumSTDMeterTimer)
	{
		if (m_accumSTDMeterTimer->isActive())
		{
			m_accumSTDMeterTimer->stop();
		}
		delete m_accumSTDMeterTimer;
		m_accumSTDMeterTimer = NULL;
	}

	if (m_accumulateFlowCom)
	{
		m_accumFlowThread.exit();
		delete m_accumulateFlowCom;
		m_accumulateFlowCom = NULL;
	}

	emit signalClosed();
}

void TotalStandardDlg::resizeEvent(QResizeEvent * event)
{
	qDebug()<<"resizeEvent...";

	int th = ui.tableWidget->size().height();
	int tw = ui.tableWidget->size().width();
	int hh = ui.tableWidget->horizontalHeader()->size().height();
	int vw = ui.tableWidget->verticalHeader()->size().width();
	int vSize = (int)((th-hh-10)/(m_maxMeterNum<=0 ? 12 : m_maxMeterNum));
	int hSize = (int)((tw-vw-10)/COLUMN_TOTAL_COUNT);
	ui.tableWidget->verticalHeader()->setDefaultSectionSize(vSize);
	ui.tableWidget->horizontalHeader()->setDefaultSectionSize(hSize);
}

//瞬时流量采集串口, 上位机直接采集
void TotalStandardDlg::initInstStdCom()
{
	ComInfoStruct InstStdCom = m_readComConfig->ReadInstStdConfig();
	m_instantFlowCom = new lcModRtuComObject();
	m_instantFlowCom->moveToThread(&m_instantFlowThread);
	m_instantFlowThread.start();
	m_instantFlowCom->openLcModCom(&InstStdCom);

	connect(m_instantFlowCom, SIGNAL(lcModValueIsReady(const QByteArray &)), this, SLOT(slotGetInstStdMeterPulse(const QByteArray &)));

	if (m_instSTDMeterTimer == NULL)
		m_instSTDMeterTimer = new QTimer();

	connect(m_instSTDMeterTimer, SIGNAL(timeout()), this, SLOT(slotAskInstPulse()));
	m_instSTDMeterTimer->start(TIMEOUT_STD_INST);
}
//累计流量采集串口, 上位机直接采集
void TotalStandardDlg::initAccumStdCom()
{
	ComInfoStruct AccumStdCom = m_readComConfig->ReadAccumStdConfig();
	m_accumulateFlowCom = new lcModRtuComObject();
	m_accumulateFlowCom->moveToThread(&m_accumFlowThread);
	m_accumFlowThread.start();
	m_accumulateFlowCom->openLcModCom(&AccumStdCom);

	connect(m_accumulateFlowCom, SIGNAL(lcModValueIsReady(const QByteArray &)), this, SLOT(slotGetAccumStdMeterPulse(const QByteArray &)));

	if (m_accumSTDMeterTimer == NULL)
		m_accumSTDMeterTimer = new QTimer();

	connect(m_accumSTDMeterTimer, SIGNAL(timeout()), this, SLOT(slotAskAccumPulse()));
	m_accumSTDMeterTimer->start(TIMEOUT_STD_ACCUM);
}

void TotalStandardDlg::slotAskInstPulse()
{
	bool ok;
	uchar address = (uchar)m_stdParam->value("DevNo./InstDevNo").toString().toInt(&ok, 16);
	m_instantFlowCom->ask901712RoutesCmd(address);
}

void TotalStandardDlg::slotAskAccumPulse()
{
	bool ok;
	uchar address = (uchar)m_stdParam->value("DevNo./AccumDevNo").toString().toInt(&ok, 16);
	m_accumulateFlowCom->ask9150A16RoutesCmd(address);
}

/*
** 温度采集串口 上位机直接采集
** 周期请求
*/
void TotalStandardDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadTempConfig();
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer();
	connect(m_tempTimer, SIGNAL(timeout()), this, SLOT(slotAskPipeTemperature()));
	
	m_tempTimer->start(TIMEOUT_PIPE_TEMPER); //周期请求温度
}

void TotalStandardDlg::slotAskPipeTemperature()
{
	m_tempObj->writeTemperatureComBuffer();
}

/*
** 开辟一个新线程，打开标准温度采集串口
*/
void TotalStandardDlg::initStdTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadStdTempConfig();
	m_stdTempObj = new StdTempComObject();
	QSettings stdconfig(getFullIniFileName("stdplasensor.ini"), QSettings::IniFormat);
	m_stdTempObj->moveToThread(&m_stdTempThread);
	m_stdTempThread.start();
	m_stdTempObj->openTemperatureCom(&tempStruct);
	m_stdTempObj->setStdTempVersion(stdconfig.value("in_use/model").toInt());
	connect(m_stdTempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshStdTempValue(const QString &)));

	m_stdTempCommand = stdTempR1;
	m_stdTempTimer = new QTimer();
	connect(m_stdTempTimer, SIGNAL(timeout()), this, SLOT(slotAskStdTemperature()));
	
 	m_stdTempTimer->start(TIMEOUT_STD_TEMPER);
}

void TotalStandardDlg::slotAskStdTemperature()
{
	m_stdTempObj->writeStdTempComBuffer(m_stdTempCommand);
}

//控制板通讯串口
void TotalStandardDlg::initControlCom()
{
	ComInfoStruct valveStruct = m_readComConfig->ReadValveConfig();
	m_controlObj = new ControlComObject();
	m_controlObj->setProtocolVersion(m_portsetinfo.version);
	m_controlObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_controlObj->openControlCom(&valveStruct);

	connect(m_controlObj, SIGNAL(controlRelayIsOk(const UINT8 &, const bool &)), this, SLOT(slotSetValveBtnStatus(const UINT8 &, const bool &)));
	connect(m_controlObj, SIGNAL(controlRegulateIsOk()), this, SLOT(slotSetRegulateOk()));
}

//热量表通讯串口
void TotalStandardDlg::initMeterCom()
{
	if (m_meterObj)
	{
		delete []m_meterObj;
		m_meterObj = NULL;

		for (int i=0; i<m_oldMaxMeterNum; i++)
		{
			m_meterThread[i].exit();
		}
	}
	if (m_maxMeterNum <= 0)
	{
		return;
	}

	m_oldMaxMeterNum = m_maxMeterNum;
	m_meterThread = new ComThread[m_maxMeterNum];

	m_meterObj = new MeterComObject[m_maxMeterNum];
	int i=0;
	for (i=0; i<m_maxMeterNum; i++)
	{
		m_meterObj[i].moveToThread(&m_meterThread[i]);
		m_meterObj[i].setProtocolVersion(m_pickcode); //设置表协议类型
		m_meterThread[i].start();
		m_meterObj[i].openMeterCom(&m_readComConfig->ReadMeterConfigByNum(i+1));
		
		connect(&m_meterObj[i], SIGNAL(readMeterNoIsOK(const QString&, const QString&)), this, SLOT(slotSetMeterNumber(const QString&, const QString&)));
		connect(&m_meterObj[i], SIGNAL(readMeterHeatIsOK(const QString&, const QString&)), this, SLOT(slotSetMeterEnergy(const QString&, const QString&)));
	}
}

/*
** 端口号-阀门映射关系；初始化阀门状态（默认阀门初始状态全部为关闭,水泵初始状态为关闭）
** 需要改进得更加灵活
*/
void TotalStandardDlg::initValveStatus()
{
	m_nowPortNo = 0;

	//端口号-阀门按钮 映射关系
	m_valveBtn[m_portsetinfo.bigNo] = ui.btnValveBig;
	m_valveBtn[m_portsetinfo.smallNo] = ui.btnValveSmall;
	m_valveBtn[m_portsetinfo.middle1No] = ui.btnValveMiddle1;
	m_valveBtn[m_portsetinfo.middle2No] = ui.btnValveMiddle2;
	m_valveBtn[m_portsetinfo.waterInNo] = ui.btnWaterIn;
	m_valveBtn[m_portsetinfo.waterOutNo] = ui.btnWaterOut;
	m_valveBtn[m_portsetinfo.pumpNo] = ui.btnWaterPump; //水泵

	//初始化：放水阀为打开，其他阀门为关闭状态
	m_valveStatus[m_portsetinfo.bigNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.smallNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle1No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle2No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterOutNo] = VALVE_OPEN;
	m_valveStatus[m_portsetinfo.pumpNo] = VALVE_CLOSE; //水泵

	setValveBtnBackColor(m_valveBtn[m_portsetinfo.bigNo], m_valveStatus[m_portsetinfo.bigNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.smallNo], m_valveStatus[m_portsetinfo.smallNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle1No], m_valveStatus[m_portsetinfo.middle1No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle2No], m_valveStatus[m_portsetinfo.middle2No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterInNo], m_valveStatus[m_portsetinfo.waterInNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterOutNo], m_valveStatus[m_portsetinfo.waterOutNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.pumpNo], m_valveStatus[m_portsetinfo.pumpNo]);
}

//在界面刷新入口温度和出口温度值
void TotalStandardDlg::slotFreshComTempValue(const QString& tempStr)
{
	ui.lcdInTemper->display(tempStr.left(TEMPER_DATA_WIDTH));   //入口温度 PV
	ui.lcdOutTemper->display(tempStr.right(TEMPER_DATA_WIDTH)); //出口温度 SV
}

//刷新标准温度
void TotalStandardDlg::slotFreshStdTempValue(const QString& stdTempStr)
{
// 	qDebug()<<"stdTempStr ="<<stdTempStr<<"; m_stdTempCommand ="<<m_stdTempCommand;
	switch (m_stdTempCommand)
	{
// 	case stdTempT1: 
// 		ui.lnEditOutStdResist->setText(stdTempStr);
// 		break;
// 	case stdTempT2: 
// 		ui.lnEditInStdTemp->setText(stdTempStr);
// 		break;
	case stdTempR1: 
		ui.lnEditInStdResist->setText(stdTempStr);
		m_stdTempCommand = stdTempR2;
		break;
	case stdTempR2: 
		ui.lnEditOutStdResist->setText(stdTempStr);
		m_stdTempCommand = stdTempR1;
		break;
	default:
		break;
	}
}

//采集标准温度
void TotalStandardDlg::on_btnStdTempCollect_clicked()
{
	ui.lnEditInStdResist->clear();
	ui.lnEditOutStdResist->clear();
	ui.lnEditInStdTemp->clear();
	ui.lnEditOutStdTemp->clear();
	m_stdTempTimer->start(TIMEOUT_STD_TEMPER);
}

//停止采集标准温度
void TotalStandardDlg::on_btnStdTempStop_clicked()
{
	m_stdTempTimer->stop();
}

void TotalStandardDlg::on_lnEditInStdResist_textChanged(const QString & text)
{
	float resis = text.toFloat();
	float temp = calcTemperByResis(resis);
	ui.lnEditInStdTemp->setText(QString::number(temp));
}

void TotalStandardDlg::on_lnEditOutStdResist_textChanged(const QString & text)
{
	float resis = text.toFloat();
	float temp = calcTemperByResis(resis);
	ui.lnEditOutStdTemp->setText(QString::number(temp));
}

void TotalStandardDlg::slot_btnGroupEnergyUnit_clicked(int id)
{
	m_unit = btnGroupEnergyUnit->checkedId();
	if (m_unit==UNIT_KWH) 
	{
		ui.tableWidget->setHorizontalHeaderItem(COLUMN_METER_START, new QTableWidgetItem(QObject::tr("MeterValue0(kWh)")));
		ui.tableWidget->setHorizontalHeaderItem(COLUMN_METER_END, new QTableWidgetItem(QObject::tr("MeterValue1(kWh)")));
		ui.tableWidget->setHorizontalHeaderItem(COLUMN_STD_VALUE, new QTableWidgetItem(QObject::tr("StdValue(kWh)")));
	}
	else
	{
		ui.tableWidget->setHorizontalHeaderItem(COLUMN_METER_START, new QTableWidgetItem(QObject::tr("MeterValue0(MJ)")));
		ui.tableWidget->setHorizontalHeaderItem(COLUMN_METER_END, new QTableWidgetItem(QObject::tr("MeterValue1(MJ)")));
		ui.tableWidget->setHorizontalHeaderItem(COLUMN_STD_VALUE, new QTableWidgetItem(QObject::tr("StdValue(MJ)")));
	}
}

void TotalStandardDlg::slot_btnGroupInstallPos_clicked(int id)
{
	m_installPos = btnGroupInstallPos->checkedId();
}

//检测串口、端口设置是否正确
int TotalStandardDlg::isComAndPortNormal()
{
	return true;
}

//获取当前检定参数;初始化表格控件；显示关键参数；初始化热量表通讯串口
int TotalStandardDlg::readNowParaConfig()
{
	if (NULL == m_paraSetReader)
	{
		return false;
	}

	if (!m_stopFlag)
	{
// 		QMessageBox::warning(this, tr("Warning"), tr("Verify...\nParaSet will work next time!"));
		return false;
	}

	m_state = STATE_INIT;

	m_nowParams = m_paraSetReader->getParams();
	m_continueVerify = m_nowParams->bo_converify; //连续检定
	m_resetZero = m_nowParams->bo_resetzero; //初值回零
	m_autopick = m_nowParams->bo_autopick;   //自动采集
	m_flowPointNum = m_nowParams->total_fp;  //有效流量点的个数 
	m_exaustSecond = m_nowParams->ex_time;   //排气时间
	m_standard = m_nowParams->m_stand;       //表规格
	m_model = m_nowParams->m_model;   //表型号
	m_maxMeterNum = m_nowParams->m_maxMeters;//不同表规格对应的最大检表数量
	m_pickcode = m_nowParams->m_pickcode; //采集代码
	m_numPrefix = getNumPrefixOfManufac(m_pickcode); //表号前缀
	m_totalSC = m_nowParams->sc_thermal;  //总量安全系数

	initTableWidget();
	showNowKeyParaConfig();
	initMeterCom();

	return true;
}

//初始化表格控件
void TotalStandardDlg::initTableWidget()
{
	if (m_maxMeterNum <= 0)
	{
		return;
	}
	ui.tableWidget->setRowCount(m_maxMeterNum); //设置表格行数

	QSignalMapper *signalMapper3 = new QSignalMapper();
	QSignalMapper *signalMapper4 = new QSignalMapper();
	QSignalMapper *signalMapper5 = new QSignalMapper();

	QStringList vLabels;
	for (int i=0; i< ui.tableWidget->rowCount(); i++)
	{
		vLabels<<QString(QObject::tr("meterPosNo%1").arg(i+1));

		for (int j=0; j<ui.tableWidget->columnCount(); j++)
		{
			ui.tableWidget->setItem(i, j, new QTableWidgetItem(QString("")));
			ui.tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
		}

		//设为只读
		ui.tableWidget->item(i, COLUMN_FLOW_POINT)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_BAL_START)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_BAL_END)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_TEMPER)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_DENSITY)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_STD_VALUE)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_DISP_ERROR)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_STD_ERROR)->setFlags(Qt::NoItemFlags);

		//设置按钮
		QPushButton *btnReadData = new QPushButton(QObject::tr("(%1)").arg(i+1) + tr("ReadData"));
		ui.tableWidget->setCellWidget(i, COLUMN_READ_DATA, btnReadData);
		signalMapper3->setMapping(btnReadData, i);
		connect(btnReadData, SIGNAL(clicked()), signalMapper3, SLOT(map()));

		QPushButton *btnVerifySt = new QPushButton(QObject::tr("(%1)").arg(i+1) + tr("VerifySt"));
		ui.tableWidget->setCellWidget(i, COLUMN_VERIFY_STATUS, btnVerifySt);
		signalMapper4->setMapping(btnVerifySt, i);
		connect(btnVerifySt, SIGNAL(clicked()), signalMapper4, SLOT(map()));

		QPushButton *btnReadNO = new QPushButton(QObject::tr("(%1)").arg(i+1) + tr("ReadNO"));
		ui.tableWidget->setCellWidget(i, COLUMN_READ_NO, btnReadNO);
		signalMapper5->setMapping(btnReadNO, i);
		connect(btnReadNO, SIGNAL(clicked()), signalMapper5, SLOT(map()));
	}
	connect(signalMapper3, SIGNAL(mapped(const int &)),this, SLOT(slotReadData(const int &)));
	connect(signalMapper4, SIGNAL(mapped(const int &)),this, SLOT(slotVerifyStatus(const int &)));
	connect(signalMapper5, SIGNAL(mapped(const int &)),this, SLOT(slotReadNO(const int &)));

	ui.tableWidget->setVerticalHeaderLabels(vLabels);
	ui.tableWidget->setFont(QFont("Times", 15, QFont::DemiBold, true));
// 	ui.tableWidget->resizeColumnsToContents();
// 	ui.tableWidget->setColumnWidth(COLUMN_METER_NUMBER, 125);
}

//显示当前关键参数设置信息
void TotalStandardDlg::showNowKeyParaConfig()
{
	if (NULL == m_nowParams)
	{
		return;
	}

	ui.cmbAutoPick->setCurrentIndex(m_nowParams->bo_autopick);
	ui.cmbContinue->setCurrentIndex(m_nowParams->bo_converify);
	ui.cmbResetZero->setCurrentIndex(m_nowParams->bo_resetzero);
	m_meterStdMapper->setCurrentIndex(m_nowParams->m_stand);
}

//检查数据采集是否正常，包括天平、温度、电磁流量计
int TotalStandardDlg::isDataCollectNormal()
{
	return true;
}

/*
** 开始排气倒计时
*/
int TotalStandardDlg::startExhaustCountDown()
{
	if (!isDataCollectNormal())
	{
		qWarning()<<"数据采集错误，请检查";
		QMessageBox::warning(this, tr("Warning"), tr("data acquisition error, please check!"));
		return false;
	}
	m_controlObj->askSetDriverFreq(m_nowParams->fp_info[0].fp_freq);
	if (!openAllValveAndPump())
	{
		qWarning()<<"打开所有阀门和水泵 失败!";
		QMessageBox::warning(this, tr("Warning"), tr("exhaust air failed!"));
		return false;
	}
	m_stopFlag = false;
	m_exaustSecond = m_nowParams->ex_time;
	m_exaustTimer->start(CYCLE_TIME);//开始排气倒计时
	ui.labelHintProcess->setText(tr("Exhaust countdown: <font color=DarkGreen size=6><b>%1</b></font> second").arg(m_exaustSecond));
	ui.labelHintPoint->clear();
	qDebug()<<"排气倒计时:"<<m_exaustSecond<<"秒";

	return true;
}

/*
** 排气定时器响应函数
*/
void TotalStandardDlg::slotExaustFinished()
{
	if (m_stopFlag)
	{
		return;
	}

	m_exaustSecond --;
	ui.labelHintProcess->setText(tr("Exhaust countdown: <font color=DarkGreen size=6><b>%1</b></font> second").arg(m_exaustSecond));
	qDebug()<<"排气倒计时:"<<m_exaustSecond<<"秒";
	if (m_exaustSecond > 1)
	{
		return;
	}

	m_exaustTimer->stop(); //停止排气计时
	ui.labelHintProcess->setText(tr("Exhaust countdown finished!"));
	ui.labelHintProcess->clear();
	if (!closeAllFlowPointValves()) //关闭所有流量点阀门 失败
	{
		if (!closeAllFlowPointValves()) //再尝试关闭一次
		{
			qWarning()<<"关闭所有流量点阀门失败，检定结束";
			return;
		}
	}

	if (setAllMeterVerifyStatus()) //设置检定状态成功
	{
		startVerify();
	}
}

//设置所有热量表进入检定状态
int TotalStandardDlg::setAllMeterVerifyStatus()
{
	ui.labelHintPoint->setText(tr("setting verify status ..."));
	on_btnAllVerifyStatus_clicked();
	wait(CYCLE_TIME);
	on_btnAllVerifyStatus_clicked();
	return true;
}

//打开所有阀门和水泵
int TotalStandardDlg::openAllValveAndPump()
{
	openWaterOutValve();
	openValve(m_portsetinfo.waterInNo);
	openWaterPump();//打开水泵
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.smallNo);
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.middle1No);
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.middle2No);
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.bigNo);

	return true;
}

//关闭所有阀门和水泵
int TotalStandardDlg::closeAllValveAndPumpOpenOutValve()
{
	openWaterOutValve(); //退出时打开放水阀
	wait(CYCLE_TIME);
	closeWaterPump();    //退出时关闭水泵
	closeAllFlowPointValves();//关闭所有流量点阀门
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.waterInNo);//关闭进水阀

	return true;
}

//关闭所有流量点阀门
int TotalStandardDlg::closeAllFlowPointValves()
{
	closeValve(m_portsetinfo.bigNo);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.middle2No);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.middle1No);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.smallNo);

	return true;
}

//关闭放水阀门
int TotalStandardDlg::closeWaterOutValve()
{
	closeValve(m_portsetinfo.waterOutNo);
	return true;
}

//打开放水阀门
int TotalStandardDlg::openWaterOutValve()
{
	openValve(m_portsetinfo.waterOutNo);
	return true;
}

/*
** 功能：判断天平重量是否达到要求的检定量；计算检定过程的平均温度和平均流量(m3/h)
*/
int TotalStandardDlg::judgeTartgetVolAndCalcAvgTemperAndFlow(float initV, float verifyV)
{
	float targetV = initV + verifyV;
	ui.tableWidget->setEnabled(false);
	ui.btnAllReadNO->setEnabled(false);
	ui.btnAllReadData->setEnabled(false);
	ui.btnAllVerifyStatus->setEnabled(false);
	QDateTime startTime = QDateTime::currentDateTime();
	int second          = 0;
	float nowFlow       = m_paraSetReader->getFpBySeq(m_nowOrder).fp_verify;
	float nowVol        = initV;
	while (!m_stopFlag && (nowVol < targetV))
	{
		qDebug()<<"当前流水量 ="<<nowVol<<", 小于目标体积 "<<targetV;
		m_avgTFCount++;
		m_pipeInTemper += ui.lcdInTemper->value();
		m_pipeOutTemper += ui.lcdOutTemper->value();
		m_stdInTemper += ui.lnEditInStdTemp->text().toFloat();
		m_stdOutTemper += ui.lnEditOutStdTemp->text().toFloat();
		second = 3.6*(targetV - nowVol)/nowFlow;
		ui.labelHintPoint->setText(tr("NO. <font color=DarkGreen size=6><b>%1</b></font> flow point: <font color=DarkGreen size=6><b>%2</b></font> m3/h")\
			.arg(m_nowOrder).arg(nowFlow));
		ui.labelHintProcess->setText(tr("Verifying...Please wait for about <font color=DarkGreen size=6><b>%1</b></font> second").arg(second));
		wait(CYCLE_TIME);
		nowVol = ui.lcdAccumStdMeter->value();
	}

	m_pipeInTemper = m_pipeInTemper/m_avgTFCount;   //入口平均温度
	m_pipeOutTemper = m_pipeOutTemper/m_avgTFCount; //出口平均温度
	m_stdInTemper = m_stdInTemper/m_avgTFCount;     //入口标准温度平均值
	m_stdOutTemper = m_stdOutTemper/m_avgTFCount;   //出口标准温度平均值

	QDateTime endTime = QDateTime::currentDateTime();
	int tt = startTime.secsTo(endTime);
	if (NULL==m_paraSetReader || m_stopFlag)
	{
		return false;
	}
	m_realFlow = 3.6*(m_paraSetReader->getFpBySeq(m_nowOrder).fp_quantity + ui.lcdAccumStdMeter->value() - targetV)/tt;
	ui.labelHintPoint->setText(tr("NO. <font color=DarkGreen size=6><b>%1</b></font> flow point: <font color=DarkGreen size=6><b>%2</b></font> m3/h")\
		.arg(m_nowOrder).arg(nowFlow));
	ui.labelHintProcess->setText(tr("NO. <font color=DarkGreen size=6><b>%1</b></font> flow point: Verify Finished!").arg(m_nowOrder));
	//if (m_nowOrder == m_flowPointNum)
	//{
	//	ui.labelHintProcess->setText(tr("All flow points has verified!"));
	//	ui.btnNext->hide();
	//}
	int ret = !m_stopFlag && (ui.lcdAccumStdMeter->value() >= targetV);
	return ret;
}

//清空表格，第一列除外("表号"列)
void TotalStandardDlg::clearTableContents()
{
	for (int i=0; i<m_maxMeterNum; i++)
	{
		for (int j=1; j<ui.tableWidget->columnCount(); j++) //从第二列开始
		{
			if (ui.tableWidget->item(i,j) == 0)
			{
				continue;
			}
			ui.tableWidget->item(i,j)->setText("");
		}
	}
// 	ui.tableWidget->clearContents(); //清空表格
}

//点击"开始"按钮
void TotalStandardDlg::on_btnStart_clicked()
{
	//判断是否输入了最小温差
	bool ok;
	m_minDeltaT = ui.lnEditMinDeltaT->text().toFloat(&ok);
	if (!ok || ui.lnEditMinDeltaT->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("please input minimum delta temperature!"));
		ui.lnEditMinDeltaT->setFocus();
		return;
	}
	bool ok1, ok2;
	float stdInTemp = ui.lnEditInStdTemp->text().toFloat(&ok1);
	float stdOutTemp = ui.lnEditOutStdTemp->text().toFloat(&ok2);
	if ( !ok1 || !ok2 || (stdInTemp-stdOutTemp)<=0 )
	{
		QMessageBox::warning(this, tr("Warning"), tr("std temperature is error, please check!"));
		return;
	}

	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //记录时间戳
	m_nowDate = QDateTime::currentDateTime().toString("yyyy-MM-dd"); //当前日期'2014-08-07'
	m_validDate = QDateTime::currentDateTime().addYears(VALID_YEAR).addDays(-1).toString("yyyy-MM-dd"); //有效期

	ui.btnStart->setEnabled(false);
	ui.btnGoOn->hide();
	ui.labelHintPoint->clear();
	ui.labelHintProcess->clear();
	ui.tableWidget->setEnabled(true);
	ui.btnAllReadNO->setEnabled(true);
	ui.btnAllReadData->setEnabled(true);
	ui.btnAllVerifyStatus->setEnabled(true);
	
	m_stopFlag = false;
	m_state = STATE_INIT;
	m_validMeterNum = 0;

	for (int i=0; i<ui.tableWidget->rowCount(); i++)
	{
		ui.tableWidget->item(i,COLUMN_METER_NUMBER)->setText("");
		ui.tableWidget->item(i, COLUMN_METER_NUMBER)->setForeground(QBrush());
		ui.tableWidget->item(i, COLUMN_DISP_ERROR)->setForeground(QBrush());
	}
	clearTableContents();

	if (!startExhaustCountDown())
	{
		return;
	}
	
	if (m_autopick) //自动读表
	{
		on_btnAllReadNO_clicked();
	}
	else //手动读表
	{
		ui.labelHintPoint->setText(tr("Please input meter number!"));
		ui.tableWidget->setCurrentCell(0, COLUMN_METER_NUMBER);
	}

	return;
}

/*
** 点击"排气"按钮
*/
void TotalStandardDlg::on_btnExhaust_clicked()
{

}

//点击"继续"按钮 处理表号获取异常
void TotalStandardDlg::on_btnGoOn_clicked()
{
	ui.btnGoOn->hide();
	startVerify();
}

//点击"重新计算"按钮
void TotalStandardDlg::on_btnReCalc_clicked()
{
}

//点击"终止检测"按钮
void TotalStandardDlg::on_btnStop_clicked()
{
	int button = QMessageBox::question(this, tr("Question"), tr("Stop Really ?"), \
		QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape);
	if (button == QMessageBox::No)
	{
		return;
	}

	stopVerify();
}

void TotalStandardDlg::on_btnExit_clicked()
{
	this->close();
}

//停止检定
void TotalStandardDlg::stopVerify()
{
	ui.labelHintPoint->clear();
	if (!m_stopFlag)
	{
		ui.labelHintProcess->setText(tr("stopping verify...please wait a minute"));
		m_stopFlag = true; //不再检查天平质量
		m_exaustTimer->stop();//停止排气定时器
		closeAllValveAndPumpOpenOutValve();
	}
	ui.labelHintProcess->setText(tr("Verify has Stoped!"));
	m_state = STATE_INIT; //重置初始状态

	ui.tableWidget->setEnabled(true);
	ui.btnAllReadNO->setEnabled(true);
	ui.btnAllReadData->setEnabled(true);
	ui.btnAllVerifyStatus->setEnabled(true);
	ui.btnStart->setEnabled(true);
}

//开始检定
void TotalStandardDlg::startVerify()
{
	//释放内存
	if (m_meterErr != NULL)
	{
		for (int m=0; m<m_validMeterNum; m++)
		{
			delete []m_meterErr[m];
		}
		delete []m_meterErr;
		m_meterErr = NULL;
	}

	getValidMeterNum(); //获取实际检表的个数(根据获取到的表号个数)
	if (m_validMeterNum <= 0)
	{
		ui.labelHintPoint->setText(tr("Please input meter number!\n then click \"GoOn\" button!"));
		QMessageBox::warning(this, tr("Error"), tr("Error: meter count is zero !\nPlease input meter number, then click \"GoOn\" button!"));//请输入表号！
		ui.tableWidget->setCurrentCell(0, COLUMN_METER_NUMBER);
		ui.btnGoOn->show();
		return;
	}
	if (m_validMeterNum != m_maxMeterNum)
	{
		ui.labelHintPoint->clear();
		QMessageBox *messageBox = new QMessageBox(QMessageBox::Question, tr("Question"), \
			tr("meter count maybe error ! read meter number again?\nclick \'Yes\' to read meter again;or click \'No\' to continue verify"), \
			QMessageBox::Yes|QMessageBox::No, this);
		messageBox->setDefaultButton(QMessageBox::No); //默认继续检定
		QTimer timer;
		connect(&timer, SIGNAL(timeout()), messageBox, SLOT(close()));
		timer.start(8000);
		if (messageBox->exec()==QMessageBox::Yes)
		{
			ui.labelHintPoint->setText(tr("Please input meter number!\n then click \"GoOn\" button!"));
			ui.btnGoOn->show();
			return;
		}
	}

	if (m_recPtr != NULL)
	{
		delete []m_recPtr;
		m_recPtr = NULL;
	}
	m_recPtr = new Total_Verify_Record_STR[m_validMeterNum];
	memset(m_recPtr, 0, sizeof(Total_Verify_Record_STR)*m_validMeterNum);

	m_state = STATE_INIT; //初始状态

	//表初值
	if (m_meterStartValue != NULL)
	{
		delete []m_meterStartValue;
		m_meterStartValue = NULL;
	}
	m_meterStartValue = new float[m_validMeterNum];
	memset(m_meterStartValue, 0, sizeof(float)*m_validMeterNum);

	//表终值
	if (m_meterEndValue != NULL)
	{
		delete []m_meterEndValue;
		m_meterEndValue = NULL;
	}
	m_meterEndValue = new float[m_validMeterNum];   
	memset(m_meterEndValue, 0, sizeof(float)*m_validMeterNum);
	
	//表温度
	if (m_meterTemper != NULL)
	{
		delete []m_meterTemper;
		m_meterTemper = NULL;
	}
	m_meterTemper = new float[m_validMeterNum];     
	memset(m_meterTemper, 0, sizeof(float)*m_validMeterNum);

	//表密度	
	if (m_meterDensity != NULL)
	{
		delete []m_meterDensity;
		m_meterDensity = NULL;
	}
	m_meterDensity = new float[m_validMeterNum];    
	memset(m_meterDensity, 0, sizeof(float)*m_validMeterNum);

	//被检表的标准值
	if (m_meterStdValue != NULL)
	{
		delete []m_meterStdValue;
		m_meterStdValue = NULL;
	}
	m_meterStdValue = new float[m_validMeterNum];   
	memset(m_meterStdValue, 0, sizeof(float)*m_validMeterNum);

    //被检表的误差(不同表、当前流量点)	
	if (m_meterError != NULL)
	{
		delete []m_meterError;
		m_meterError = NULL;
	}
	m_meterError = new float[m_validMeterNum];      
	memset(m_meterError, 0, sizeof(float)*m_validMeterNum);

	//被检表的误差(不同表、不同流量点)
	m_meterErr = new float*[m_validMeterNum];    
	for (int i=0; i<m_validMeterNum; i++)
	{
		m_meterErr[i] = new float[VERIFY_POINTS];
		memset(m_meterErr[i], 0, sizeof(float)*VERIFY_POINTS);
	}

	//所有流量点是否都合格
	if (m_meterResult != NULL)
	{
		delete []m_meterResult;
		m_meterResult = NULL;
	}
	m_meterResult = new int[m_validMeterNum];
	for (int p=0; p<m_validMeterNum; p++)
	{
		m_meterResult[p] = 1;
	}

	if (m_continueVerify) //连续检定
	{
		wait(BALANCE_STABLE_TIME); //等待3秒钟(等待水流稳定)
	}

	m_nowOrder = 1;
	prepareVerifyFlowPoint(m_nowOrder); //第一个流量点检定
}

//获取有效检表个数,并生成映射关系（被检表下标-表位号）
int TotalStandardDlg::getValidMeterNum()
{
	//匹配表号是否为数字; 
	//前一个'\'是转义字符, "\\"就相当于'\', "\\d"相当于'\d', 匹配一个数字, '+'是数字的正闭包;
	//本模式也可以写成 "[0-9]+"
	QRegExp rx("\\d+");

	m_validMeterNum = 0; //先清零
	QString meterNum;//表号
	for (int i=0; i<m_maxMeterNum; i++)
	{
		if (NULL == ui.tableWidget->item(i, COLUMN_METER_NUMBER)) //"表号"单元格为空
		{
			continue;
		}
		meterNum = ui.tableWidget->item(i, COLUMN_METER_NUMBER)->text();
		if (!rx.exactMatch(meterNum))
		{
			continue;
		}

		m_meterPosMap[m_validMeterNum] = i+1; //表位号从1开始
		m_validMeterNum++;
	}
	return m_validMeterNum;
}

/*
** 判断表位号是否有效(该表位是否需要检表)
输入:meterPos(表位号)，从1开始
返回:被检表下标，从0开始
*/
int TotalStandardDlg::isMeterPosValid(int meterPos)
{
	for (int i=0; i<m_validMeterNum; i++)
	{
		if (m_meterPosMap[i] == meterPos)
		{
			return i;
		}
	}
	return -1;
}

/*
** 准备单个流量点的检定，进行必要的检查
** 注意：order从1开始
*/
int TotalStandardDlg::prepareVerifyFlowPoint(int order)
{
	if (order < 1 || order > m_flowPointNum || m_stopFlag)
	{
		return false;
	}

	if (!m_continueVerify)
	{
		wait(BALANCE_STABLE_TIME);   //等待3秒钟，等待水流稳定
	}

	int i=0;
	if (m_resetZero) //初值回零
	{
		ui.labelHintPoint->setText(tr("Reset Zero"));
		while (i < RESET_ZERO_TIME && !m_stopFlag) //等待被检表初值回零
		{
			ui.labelHintProcess->setText(tr("please wait <font color=DarkGreen size=4><b>%1</b></font> seconds for reset zero").arg(RESET_ZERO_TIME-i));
			i++;
			wait(CYCLE_TIME); 
		}
	}
	getMeterStartValue(); //获取表初值

	return true;
}

//进行单个流量点的检定
int TotalStandardDlg::startVerifyFlowPoint(int order)
{
	if (m_stopFlag)
	{
		return false;
	}

	//判断初值是否全部读取成功
	bool ok;
	int row = 0;
	for (int p=0; p<m_validMeterNum; p++)
	{
		row = m_meterPosMap[p]-1;
		ui.tableWidget->item(row, COLUMN_METER_START)->text().toFloat(&ok);
		if (!ok || ui.tableWidget->item(row, COLUMN_METER_START)->text().isEmpty())
		{
			// 			QMessageBox::information(this, tr("Hint"), tr("please input start value of heat meter"));//请输入热量表初值！
			ui.labelHintProcess->setText(tr("please input start value of heat meter"));
			ui.tableWidget->setCurrentCell(row, COLUMN_METER_START); //定位到需要输入初值的地方
			return false;
		}
	}

	m_realFlow = ui.lcdFlowRate->value();
	m_avgTFCount = 1;

	//直接使用标准温度计的温度即可， 因为恒温槽的温度波动很小，不必要使用平均温度
	m_stdInTemper = ui.lnEditInStdTemp->text().toFloat();
	m_stdOutTemper = ui.lnEditOutStdTemp->text().toFloat();

	int portNo = m_paraSetReader->getFpBySeq(order).fp_valve;  //order对应的阀门端口号
	flow_rate_wdg wdgIdx = (flow_rate_wdg)m_paraSetReader->getBigSmallBySeq(order);//获取大流量还是小流量点 
	float verifyQuantity = m_paraSetReader->getFpBySeq(order).fp_quantity; //第order次检定对应的检定量
	float frequence = m_paraSetReader->getFpBySeq(order).fp_freq; //order对应的频率
	m_controlObj->askSetDriverFreq(frequence);

	m_stdStartVol = getAccumFLowVolume(wdgIdx);//记录标准表初始体积(L)
	qDebug() << "start volumn: " << m_stdStartVol;
	float stdStartDen = m_chkAlg->getDensityByQuery(m_stdInTemper);//体积参数为检定管路中的，温度参数为恒温槽的
	if (stdStartDen<0)
	{
		return -1;
	}
	m_StdStartMass = stdStartDen*m_stdStartVol;//质量为虚拟的，不是检定管路中真实的

	if (openValve(portNo)) //打开阀门，开始跑流量
	{
		if (judgeTartgetVolAndCalcAvgTemperAndFlow(m_stdStartVol, verifyQuantity)) //跑完检定量并计算此过程的平均温度和平均流量
		{
			ui.tableWidget->setEnabled(true);
			ui.btnAllReadNO->setEnabled(true);
			ui.btnAllReadData->setEnabled(true);
			ui.btnAllVerifyStatus->setEnabled(true);
			closeValve(portNo); //关闭order对应的阀门
			wait(BALANCE_STABLE_TIME); //等待3秒钟，让天平数值稳定

			m_stdEndVol = getAccumFLowVolume(wdgIdx);//记录标准表最终体积(L)
			float stdEndDen = m_chkAlg->getDensityByQuery(m_stdOutTemper);//标准表最终平均密度(kg/L)
			qDebug() << "end volumn: " << m_stdEndVol;
			if(stdEndDen<0)
			{
				return -1;
			}
			m_StdEndMass = m_stdEndVol*stdEndDen;
			if (!m_resetZero && m_nowOrder>=2)
			{
				m_state = STATE_END_VALUE;
				makeStartValueByLastEndValue();
			}
			for (int m=0; m<m_validMeterNum; m++) //
			{
				m_meterTemper[m] = m_chkAlg->getMeterTempByPos(m_pipeInTemper, m_pipeOutTemper, m_meterPosMap[m]);//计算每个被检表的温度
				m_meterDensity[m] = m_chkAlg->getDensityByQuery(m_meterTemper[m]);//计算每个被检表的密度

				//计算每个被检表的热量标准值, 如果按照jjg-2010, 需要用质量守恒法将标准表的质量计算到表位上。如果按照jjg-2001则直接计算即可
				m_meterStdValue[m] = m_chkAlg->calcStdEnergyByEnthalpy(m_stdInTemper, m_stdOutTemper, m_StdEndMass-m_StdStartMass, m_unit); 

				ui.tableWidget->item(m_meterPosMap[m]-1, COLUMN_FLOW_POINT)->setText(QString::number(m_realFlow, 'f', 3));//流量点
				ui.tableWidget->item(m_meterPosMap[m]-1, COLUMN_METER_END)->setText("");//表终值
				ui.tableWidget->item(m_meterPosMap[m]-1, COLUMN_BAL_START)->setText(QString::number(m_StdStartMass, 'f', 3));//初值
				ui.tableWidget->item(m_meterPosMap[m]-1, COLUMN_BAL_END)->setText(QString::number(m_StdEndMass, 'f', 3));    //终值
				ui.tableWidget->item(m_meterPosMap[m]-1, COLUMN_TEMPER)->setText(QString::number(m_meterTemper[m], 'f', 2));  //温度
				ui.tableWidget->item(m_meterPosMap[m]-1, COLUMN_DENSITY)->setText(QString::number(m_meterDensity[m], 'f', 3));//密度
				ui.tableWidget->item(m_meterPosMap[m]-1, COLUMN_STD_VALUE)->setText(QString::number(m_meterStdValue[m], 'f', 3));//标准值
				ui.tableWidget->item(m_meterPosMap[m]-1, COLUMN_DISP_ERROR)->setText("");//示值误差
				ui.tableWidget->item(m_meterPosMap[m]-1, COLUMN_DISP_ERROR)->setForeground(QBrush());//示值误差
			}
			getMeterEndValue();
		}//跑完检定量
	}

	return true;
}

/*
** 计算所有被检表的误差
*/
int TotalStandardDlg::calcAllMeterError()
{
	for (int i=0; i<m_validMeterNum; i++)
	{
		if (calcMeterError(i) == 0)
		{
			return 0;
		}
	}
	return 1; 
}

/*
** 计算某个被检表的误差
** 输入参数：
**     idx:被检表数组的索引
*/
int TotalStandardDlg::calcMeterError(int idx)
{
	bool ok;
	int row = m_meterPosMap[idx] - 1;
	ui.tableWidget->item(row, COLUMN_METER_END)->text().toFloat(&ok);
	if (/*m_meterEndValue[idx] <= 0 ||*/ ui.tableWidget->item(row, COLUMN_METER_END)->text().isEmpty() || !ok)
	{
		ui.tableWidget->setCurrentCell(row, COLUMN_METER_END);
		return 0;
	}
	m_meterError[idx] = 100*(m_meterEndValue[idx] - m_meterStartValue[idx] - m_meterStdValue[idx])/m_meterStdValue[idx];//计算某个表的误差
	int valveIdx = m_paraSetReader->getFpBySeq(m_nowOrder).fp_valve_idx; //0:大 1:中二 2:中一 3:小
	m_meterErr[idx][valveIdx] = m_meterError[idx];
	ui.tableWidget->item(row, COLUMN_DISP_ERROR)->setText(QString::number(m_meterError[idx], 'f', 4)); //示值误差
	float stdError = m_totalSC*(m_gradeErrA[m_nowParams->m_grade] + 4*m_minDeltaT/(m_stdInTemper-m_stdOutTemper) + m_gradeErrB[m_nowParams->m_grade]*m_mapNormalFlow[m_standard]/m_realFlow); //标准误差=规程要求误差*总量安全系数
	ui.tableWidget->item(row, COLUMN_STD_ERROR)->setText("±" + QString::number(stdError, 'f', 4)); //标准误差
	if (fabs(m_meterError[idx]) > stdError)
	{
		ui.tableWidget->item(row, COLUMN_DISP_ERROR)->setForeground(QBrush(Qt::red));
		ui.tableWidget->item(row, COLUMN_METER_NUMBER)->setForeground(QBrush(Qt::red));
	}
	QString meterNoStr = m_numPrefix + QString("%1").arg(ui.tableWidget->item(row, 0)->text(), 8, '0');

	strncpy_s(m_recPtr[idx].timestamp, m_timeStamp.toAscii(), TIMESTAMP_LEN);
	m_recPtr[idx].flowPoint = m_realFlow;
	strcpy_s(m_recPtr[idx].meterNo, meterNoStr.toAscii());
	m_recPtr[idx].flowPointIdx = m_nowOrder; //
	m_recPtr[idx].methodFlag = STANDARD_METHOD; //标准表法
	m_recPtr[idx].meterValue0 = m_meterStartValue[idx];
	m_recPtr[idx].meterValue1 = m_meterEndValue[idx];
	m_recPtr[idx].balWeight0 = m_StdStartMass;
	m_recPtr[idx].balWeight1 = m_StdEndMass;
	m_recPtr[idx].stdMeterV0 = m_stdStartVol;
	m_recPtr[idx].stdMeterV1 = m_stdEndVol;
	m_recPtr[idx].pipeTemper = m_meterTemper[idx]; 
	m_recPtr[idx].density = m_meterDensity[idx];
	m_recPtr[idx].stdValue = m_meterStdValue[idx];
	m_recPtr[idx].dispError = m_meterError[idx];
	m_recPtr[idx].grade = m_nowParams->m_grade;
	m_recPtr[idx].stdError = stdError; //表的标准误差
	m_recPtr[idx].result = (fabs(m_recPtr[idx].dispError) <= fabs(m_recPtr[idx].stdError)) ? 1 : 0;
	m_meterResult[idx] *= m_recPtr[idx].result;
	m_recPtr[idx].meterPosNo = m_meterPosMap[idx];
	m_recPtr[idx].standard = m_standard;
	m_recPtr[idx].model = m_model;
	m_recPtr[idx].pickcode = m_pickcode; //采集代码
	m_recPtr[idx].manufactDept = m_nowParams->m_manufac;
	m_recPtr[idx].verifyDept = m_nowParams->m_vcomp;
	m_recPtr[idx].verifyPerson = m_nowParams->m_vperson;
	m_recPtr[idx].checkPerson = m_nowParams->m_cperson;
	strncpy_s(m_recPtr[idx].verifyDate, m_nowDate.toAscii(), DATE_LEN);
	strncpy_s(m_recPtr[idx].validDate, m_validDate.toAscii(), DATE_LEN);
	m_recPtr[idx].airPress = m_nowParams->m_airpress.toFloat();
	m_recPtr[idx].envTemper = m_nowParams->m_temper.toFloat();
	m_recPtr[idx].envHumidity = m_nowParams->m_humidity.toFloat();
	m_recPtr[idx].totalcoe = m_nowParams->sc_thermal;
	m_recPtr[idx].inSlotTemper = ui.lnEditInStdTemp->text().toFloat();
	m_recPtr[idx].outSlotTemper = ui.lnEditOutStdTemp->text().toFloat();

	return 1; 
}

//输完热量表终值后，计算检定结果
int TotalStandardDlg::calcVerifyResult()
{
	int ret = 0;
	ret = calcAllMeterError();

	if (ret) //读表流量都成功（终值）
	{
		saveAllVerifyRecords();
		ui.labelHintProcess->setText(tr("save database successfully!"));
		if (m_nowOrder>=m_flowPointNum) //最后一个流量点
		{
			stopVerify(); //停止检定
			exportReport();
		}
		else //不是最后一个流量点
		{
			prepareVerifyFlowPoint(++m_nowOrder);
		}
	}
	else //有读表流量失败的（终值）
	{
		ui.labelHintProcess->setText(tr("please input end value of heat meter"));
		ui.tableWidget->setCurrentCell(m_meterPosMap[0]-1, COLUMN_METER_END); //定位到第一个需要输入终值的地方
	}

	return true;
}


void TotalStandardDlg::exportReport()
{
	QString sqlCondition = QString("F_TimeStamp=\'%1\' and F_MethodFlag = 1").arg(m_timeStamp);
	QString xlsname = QDateTime::fromString(m_timeStamp, "yyyy-MM-dd HH:mm:ss.zzz").toString("yyyy-MM-dd_hh-mm-ss") + ".xls";
	try
	{
		QString defaultPath = QProcessEnvironment::systemEnvironment().value("ADEHOME") + "\\report\\total\\";
		CReport rpt(sqlCondition);
		rpt.setIniName("rptconfig_total.ini");
		rpt.writeRpt();
		rpt.saveTo(defaultPath + xlsname);
		ui.labelHintProcess->setText(tr("Verify has Stoped!") + "\n" + tr("export excel file successful!"));
	}
	catch (QString e)
	{
		QMessageBox::warning(this, tr("Error"), e);
	}
}

//打开阀门
int TotalStandardDlg::openValve(UINT8 portno)
{
	if (NULL == m_controlObj)
	{
		return false;
	}
	m_controlObj->askControlRelay(portno, VALVE_OPEN);

	if (m_portsetinfo.version==OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(portno, VALVE_OPEN);
	}
	return true;
}

//关闭阀门
int TotalStandardDlg::closeValve(UINT8 portno)
{
	if (NULL == m_controlObj)
	{
		return false;
	}
	m_controlObj->askControlRelay(portno, VALVE_CLOSE);

	if (m_portsetinfo.version==OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(portno, VALVE_CLOSE);
	}
	return true;
}

//操作阀门：打开或者关闭
int TotalStandardDlg::operateValve(UINT8 portno)
{
	m_valveStatus[portno] ? closeValve(portno) : openValve(portno);
	return true;
}

//打开水泵
int TotalStandardDlg::openWaterPump()
{
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->askControlWaterPump(m_nowPortNo, VALVE_OPEN);
	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, VALVE_OPEN);
	}
	return true;
}

//关闭水泵
int TotalStandardDlg::closeWaterPump()
{
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->askControlWaterPump(m_nowPortNo, VALVE_CLOSE);
	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, VALVE_CLOSE);
	}
	return true;
}

//操作水泵 打开或者关闭
int TotalStandardDlg::operateWaterPump()
{
	if (m_valveStatus[m_portsetinfo.pumpNo]==VALVE_OPEN) //水泵原来是打开状态
	{
		closeWaterPump();
	}
	else //水泵原来是关闭状态
	{
		openWaterPump();
	}
	return true;
}

//响应阀门状态设置成功
void TotalStandardDlg::slotSetValveBtnStatus(const UINT8 &portno, const bool &status)
{
	m_valveStatus[portno] = status;
	setValveBtnBackColor(m_valveBtn[portno], m_valveStatus[portno]);
}

//响应调节阀调节成功
void TotalStandardDlg::slotSetRegulateOk()
{
// 	setRegBtnBackColor(m_regBtn[m_nowRegIdx], true);
}


//自动读取表号成功 显示表号
void TotalStandardDlg::slotSetMeterNumber(const QString& comName, const QString& meterNo)
{
	int meterPos = m_readComConfig->getMeterPosByComName(comName);
	if (meterPos < 1)
	{
		return;
	}
	if (m_state == STATE_INIT)
	{
		ui.tableWidget->item(meterPos-1, COLUMN_METER_NUMBER)->setText(meterNo.right(8)); //表号
	}
}

/*
** 自动读取表热量成功 显示表热量
*/
void TotalStandardDlg::slotSetMeterEnergy(const QString& comName, const QString& energy)
{
	int meterPos = m_readComConfig->getMeterPosByComName(comName);
	if (meterPos < 1)
	{
		return;
	}

	int idx = isMeterPosValid(meterPos);
  if (idx < 0) //该表位不检表，当然也不需要读表数据
	{
		return;
	}
	bool ok;
	energy.toFloat(&ok);
	if (m_state == STATE_START_VALUE) //初值
	{
		ui.tableWidget->item(meterPos - 1, COLUMN_METER_START)->setText(energy);
	}
	else if (m_state == STATE_END_VALUE) //终值
	{
  		ui.tableWidget->item(meterPos - 1, COLUMN_METER_END)->setText(energy);

	}
}

//设置阀门按钮背景色
void TotalStandardDlg::setValveBtnBackColor(QToolButton *btn, bool status)
{
	if (NULL == btn)
	{
		return;
	}
	if (status) //阀门打开 绿色
	{
		btn->setStyleSheet("background-color:rgb(0,255,0);border:0px;border-radius:10px;");
// 		btn->setStyleSheet("border-image:url(:/weightmethod/images/btncheckon.png)");
	}
	else //阀门关闭 红色
	{
		btn->setStyleSheet("background-color:rgb(255,0,0);border:0px;border-radius:10px;");
// 		btn->setStyleSheet("border-image:url(:/weightmethod/images/btncheckoff.png)");
	}
}

//设置调节阀按钮背景色
void TotalStandardDlg::setRegBtnBackColor(QPushButton *btn, bool status)
{
	if (NULL == btn)
	{
		return;
	}
	if (status) //调节成功
	{
		btn->setStyleSheet("background:blue;border:0px;");
	}
	else //调节失败
	{
		btn->setStyleSheet("");
	}
}

//参数设置
void TotalStandardDlg::on_btnParaSet_clicked()
{
	if (NULL == m_paraSetDlg)
	{
		m_paraSetDlg = new ParaSetDlg();
	}
	else
	{
		delete m_paraSetDlg;
		m_paraSetDlg = new ParaSetDlg();
	}
	connect(m_paraSetDlg, SIGNAL(saveSuccessSignal()), this, SLOT(readNowParaConfig()));
	m_paraSetDlg->show();
}

/*
** 控制继电器开断
*/
void TotalStandardDlg::on_btnWaterIn_clicked() //进水阀
{
	m_nowPortNo = m_portsetinfo.waterInNo;
	operateValve(m_nowPortNo);
}

void TotalStandardDlg::on_btnWaterOut_clicked() //放水阀
{
	m_nowPortNo = m_portsetinfo.waterOutNo;
	operateValve(m_nowPortNo);
}

void TotalStandardDlg::on_btnValveBig_clicked() //大流量阀
{
	m_nowPortNo = m_portsetinfo.bigNo;
	operateValve(m_nowPortNo);
}

void TotalStandardDlg::on_btnValveMiddle1_clicked() //中流一阀
{
	m_nowPortNo = m_portsetinfo.middle1No;
	operateValve(m_nowPortNo);
}

void TotalStandardDlg::on_btnValveMiddle2_clicked() //中流二阀
{
	m_nowPortNo = m_portsetinfo.middle2No;
	operateValve(m_nowPortNo);
}

void TotalStandardDlg::on_btnValveSmall_clicked() //小流量阀
{
	m_nowPortNo = m_portsetinfo.smallNo;
	operateValve(m_nowPortNo);
}

/*
** 控制水泵开关
*/
void TotalStandardDlg::on_btnWaterPump_clicked()
{
/*	if (ui.spinBoxFrequency->value() <= 0)
	{
		QMessageBox::warning(this, tr("Warning"), tr("please input frequency of transducer"));//请设置变频器频率！
		ui.spinBoxFrequency->setFocus();
	}
 	m_controlObj->askControlRegulate(m_portsetinfo.pumpNo, ui.spinBoxFrequency->value());
*/
	m_nowPortNo = m_portsetinfo.pumpNo;
	operateWaterPump();
}

/*
** 设置变频器频率
*/
void TotalStandardDlg::on_btnSetFreq_clicked()
{
	m_controlObj->askSetDriverFreq(ui.spinBoxFreq->value());
}

//获取表初值
int TotalStandardDlg::getMeterStartValue()
{
	if (m_stopFlag)
	{
		return false;
	}

	float nowFlow = m_paraSetReader->getFpBySeq(m_nowOrder).fp_verify;
	ui.labelHintPoint->setText(tr("NO. <font color=DarkGreen size=6><b>%1</b></font> flow point: <font color=DarkGreen size=6><b>%2</b></font> m3/h")\
		.arg(m_nowOrder).arg(nowFlow));
	m_state = STATE_START_VALUE;
	if (m_resetZero) //初值回零
	{
		memset(m_meterStartValue, 0, sizeof(float)*m_validMeterNum);
		for (int j=0; j<m_validMeterNum; j++)
		{
			ui.tableWidget->item(m_meterPosMap[j]-1, COLUMN_METER_START)->setText(""); //清空初值列
			ui.tableWidget->item(m_meterPosMap[j]-1, COLUMN_METER_START)->setText(QString("%1").arg(m_meterStartValue[j]));
		}
	}
	else //初值不回零
	{
		if (m_nowOrder <= 1)
		{
			if (m_autopick) //自动采集
			{
				wait(WAIT_COM_TIME); //需要等待，否则热表来不及响应通讯
				ui.labelHintProcess->setText(tr("please input start value of heat meter"));
				on_btnAllReadData_clicked();
//	 			sleep(500); //等待串口返回数据
			}
			else //手动输入
			{
				ui.labelHintProcess->setText(tr("please input start value of heat meter"));
				ui.tableWidget->setCurrentCell(m_meterPosMap[0]-1, COLUMN_METER_START); //定位到第一个需要输入初值的地方
				return false;
			}
		}
		else //m_nowOrder >= 2
		{
// 			makeStartValueByLastEndValue();
			startVerifyFlowPoint(m_nowOrder);
		}
	}
	return true;
}

//获取表终值
int TotalStandardDlg::getMeterEndValue()
{
	if (m_stopFlag)
	{
		return false;
	}
		
	ui.labelHintProcess->setText(tr("please input end value of heat meter"));
	m_state = STATE_END_VALUE;

	if (m_autopick) //自动采集
	{
		on_btnAllReadData_clicked();
		//sleep(BALANCE_STABLE_TIME); //等待串口返回数据
	}
	else //手动输入
	{
		ui.tableWidget->setCurrentCell(m_meterPosMap[0]-1, COLUMN_METER_END); //定位到第一个需要输入终值的地方
		return false;
	}
	return true;
}

//上一次的终值作为本次的初值
void TotalStandardDlg::makeStartValueByLastEndValue()
{
// 	clearTableContents();
	for (int i=0; i<m_validMeterNum; i++)
	{
// 		m_meterStartValue[i] = m_meterEndValue[i];
		m_meterStartValue[i] = m_recPtr[i].meterValue1;
		ui.tableWidget->item(m_meterPosMap[i]-1, COLUMN_METER_START)->setText(QString("%1").arg(m_meterStartValue[i]));
	}
}
/*
** 响应处理用户输入完表初值、表终值
   输入参数：
      row：行数，从0开始
	  column：列数，从0开始
*/
void TotalStandardDlg::on_tableWidget_cellChanged(int row, int column)
{
	if (!m_autopick && column==COLUMN_METER_NUMBER && m_state==STATE_INIT) //手动输入 表号列 初始状态
	{
		ui.tableWidget->setCurrentCell(row+1, column);
	}

	if (NULL==ui.tableWidget->item(row,  column) || NULL==m_meterStartValue || NULL==m_meterEndValue)
	{
		return;
	}

	int meterPos = row + 1; //表位号
	int idx = isMeterPosValid(meterPos);
	if (idx < 0)
	{
		return;
	}

	bool ok;
	if (column==COLUMN_METER_START && m_state==STATE_START_VALUE) //表初值列 且 允许输入初值
	{
		m_meterStartValue[idx] = ui.tableWidget->item(row, column)->text().toFloat(&ok);
		if (!ok)
		{
// 			QMessageBox::warning(this, tr("Warning"), tr("Error: please input digits"));//输入错误！请输入数字
			return;
		}
		startVerifyFlowPoint(m_nowOrder);
	}

	if (column==COLUMN_METER_END && m_state==STATE_END_VALUE) //表终值列 且 允许输入终值
	{
		m_meterEndValue[idx] = ui.tableWidget->item(row, column)->text().toFloat(&ok);
		if (!ok)
		{
// 			QMessageBox::warning(this, tr("Warning"), tr("Error: please input digits"));//输入错误！请输入数字
			return;
		}
		calcVerifyResult();
	}
}

/*
** 保存所有被检表的检定记录
*/
int TotalStandardDlg::saveAllVerifyRecords()
{
 	insertTotalVerifyRec(m_recPtr, m_validMeterNum);
	return true;
}

//请求读表号（所有表、广播地址读表）
void TotalStandardDlg::on_btnAllReadNO_clicked()
{
	qDebug()<<"on_btnAllReadNO_clicked...";
	int idx = -1;
	for (int j=0; j<m_maxMeterNum; j++)
	{
		idx = isMeterPosValid(j+1);
		if (m_state == STATE_START_VALUE)
		{
			ui.tableWidget->item(j, COLUMN_METER_START)->setText("");
			if (idx >= 0)
			{
				m_meterStartValue[idx] = 0;
			}
		}
		else if (m_state == STATE_END_VALUE)
		{
			ui.tableWidget->item(j, COLUMN_METER_END)->setText("");
			if (idx >= 0)
			{
				m_meterEndValue[idx] = 0;
			}
		}
		slotReadNO(j);
	}
}

//请求读表数据（所有表、广播地址读表）
void TotalStandardDlg::on_btnAllReadData_clicked()
{
	qDebug()<<"on_btnAllReadData_clicked...";
	int idx = -1;
	for (int j=0; j<m_maxMeterNum; j++)
	{
		idx = isMeterPosValid(j+1);
		if (m_state == STATE_START_VALUE)
		{
			ui.tableWidget->item(j, COLUMN_METER_START)->setText("");
			if (idx >= 0)
			{
				m_meterStartValue[idx] = 0;
			}
		}
		else if (m_state == STATE_END_VALUE)
		{
			ui.tableWidget->item(j, COLUMN_METER_END)->setText("");
			if (idx >= 0)
			{
				m_meterEndValue[idx] = 0;
			}
		}
		slotReadData(j);
	}
}

//设置检定状态（所有表）
void TotalStandardDlg::on_btnAllVerifyStatus_clicked()
{
	for (int i=0; i<m_maxMeterNum; i++)
	{
		slotVerifyStatus(i);
	}
}

/*
** 读取表号
** 输入参数：
	row:行号，由row可以知道当前热表对应的串口、表号、误差等等
*/
void TotalStandardDlg::slotReadNO(const int &row)
{
	qDebug()<<"slotReadNO row ="<<row;
	m_meterObj[row].askReadMeterNO();
}

/*
** 读表数据
** 输入参数：
	row:行号，由row可以知道当前热表对应的串口、表号、误差等等
*/
void TotalStandardDlg::slotReadData(const int &row)
{
	qDebug()<<"slotReadData row ="<<row;
	m_meterObj[row].askReadMeterData();
}

/*
** 检定状态
** 输入参数：
	row:行号，由row可以知道当前热表对应的串口、表号、误差等等
*/
void TotalStandardDlg::slotVerifyStatus(const int &row)
{
	qDebug()<<"slotVerifyStatus row ="<<row;
	m_meterObj[row].askSetVerifyStatus(VTYPE_HEAT);
}

void TotalStandardDlg::slotGetInstStdMeterPulse(const QByteArray & valueArray)
{
	m_instStdPulse = valueArray;
	freshInstStdMeter();
	float instValue = 0.0;//瞬时流量
	m_instRouteIsRead.clear();//每次采集前, 清空通道队列
	if (m_valveStatus[m_portsetinfo.bigNo])
	{
		instValue += getFlowValueByValve(FLOW_RATE_BIG, INST_FLOW_VALUE);
	}
	if (m_valveStatus[m_portsetinfo.middle2No])
	{
		instValue += getFlowValueByValve(FLOW_RATE_MID_2, INST_FLOW_VALUE);
	}
	if (m_valveStatus[m_portsetinfo.middle1No])
	{
		instValue += getFlowValueByValve(FLOW_RATE_MID_1, INST_FLOW_VALUE);
	}
	if (m_valveStatus[m_portsetinfo.smallNo])
	{
		instValue += getFlowValueByValve(FLOW_RATE_SMALL, INST_FLOW_VALUE);
	}

	ui.lcdFlowRate->display(instValue);
}

float TotalStandardDlg::getFlowValueByValve(flow_rate_wdg wdgIdx, flow_type fType)
{
	int route		= getRouteByWdg(wdgIdx, fType);//标准表接到力创模块的通道号
	int count		= 0;//电流/脉冲信号	
	float pulse		= 0.0f;//脉冲当量
	float upperFlow = 0.0f;//上限流量
	float retValue  = 0.0f;//瞬时流量

	switch (fType)
	{
	case INST_FLOW_VALUE:		
		if (m_instRouteIsRead.contains(route))//如果前面已经读取过此通道, 则直接返回0	
			return 0.0f;		
		else
			m_instRouteIsRead.append(route);//如果前面没有读取过此通道, 则加入队列

		count = get9017RouteI(route, m_instStdPulse);
		upperFlow = getStdUpperFlow(wdgIdx);
		retValue = getInstStdValue(count, upperFlow);
		break;
	case ACCUM_FLOW_VALUE:
		if (m_accumRouteIsRead.contains(route))//如果前面已经读取过此通道, 则直接返回0	
			return 0.0f;		
		else
			m_accumRouteIsRead.append(route);//如果前面没有读取过此通道, 则加入队列

		count = get9150ARouteI(route, m_accumStdPulse);
		pulse = getStdPulse(wdgIdx);
		retValue = count*pulse;
		break;
	default:
		break;
	}	
	return retValue;
}

int TotalStandardDlg::getRouteByWdg(flow_rate_wdg wdgIdx, flow_type fType)
{
	int route = -1;
	m_stdParam->beginReadArray("Route");
	m_stdParam->setArrayIndex(wdgIdx);
	switch(fType)
	{
	case INST_FLOW_VALUE:
		route = m_stdParam->value("InstRoute").toInt();
		break;
	case ACCUM_FLOW_VALUE:
		route = m_stdParam->value("AccumRoute").toInt();
		break;
	default:
		break;
	}	
	m_stdParam->endArray();
	return route;
}

float TotalStandardDlg::getStdUpperFlow(flow_rate_wdg wdgIdx)
{
	float upperFlow = 0.0f;

	m_stdParam->beginReadArray("Route");
	m_stdParam->setArrayIndex(wdgIdx);
	int diamWdg = m_stdParam->value("Diameter").toInt();//读取管径的部件号
	m_stdParam->endArray();

	m_stdParam->beginReadArray("FlowRate");
	m_stdParam->setArrayIndex(diamWdg);
	upperFlow = m_stdParam->value("UpperFlow").toFloat();
	m_stdParam->endArray();
	return upperFlow;
}

float TotalStandardDlg::getStdPulse(flow_rate_wdg wdgIdx)
{
	float pulse = 0.0f;
	m_stdParam->beginReadArray("Route");
	m_stdParam->setArrayIndex(wdgIdx);
	int diamWdg = m_stdParam->value("Diameter").toInt();//读取管径的部件号
	m_stdParam->endArray();

	m_stdParam->beginReadArray("Pulse");
	m_stdParam->setArrayIndex(diamWdg);
	pulse = m_stdParam->value("Pulse").toFloat();
	m_stdParam->endArray();
	return pulse;
}

void TotalStandardDlg::slotGetAccumStdMeterPulse(const QByteArray & valueArray)
{
	m_accumStdPulse = valueArray;
	freshAccumStdMeter();
	float accumValue = 0.0;//累积流量
	m_accumRouteIsRead.clear();//每次采集前, 清空通道队列
	if (m_valveStatus[m_portsetinfo.bigNo])
	{
		accumValue += getFlowValueByValve(FLOW_RATE_BIG, ACCUM_FLOW_VALUE);
	}
	if (m_valveStatus[m_portsetinfo.middle2No])
	{
		accumValue += getFlowValueByValve(FLOW_RATE_MID_2, ACCUM_FLOW_VALUE);
	}
	if (m_valveStatus[m_portsetinfo.middle1No])
	{
		accumValue += getFlowValueByValve(FLOW_RATE_MID_1, ACCUM_FLOW_VALUE);
	}
	if (m_valveStatus[m_portsetinfo.smallNo])
	{
		accumValue += getFlowValueByValve(FLOW_RATE_SMALL, ACCUM_FLOW_VALUE);
	}
	ui.lcdAccumStdMeter->display(accumValue);	
}

void TotalStandardDlg::freshInstStdMeter()
{
	ui.lcdInstStdMeter_25->display(getInstFlowRate(FLOW_RATE_BIG));
	ui.lcdInstStdMeter_10->display(getInstFlowRate(FLOW_RATE_MID_2));
	ui.lcdInstStdMeter_3->display(getInstFlowRate(FLOW_RATE_SMALL));
}

void TotalStandardDlg::freshAccumStdMeter()
{
	ui.lcdAccumStdMeter_25->display(getAccumFLowVolume(FLOW_RATE_BIG));
	ui.lcdAccumStdMeter_10->display(getAccumFLowVolume(FLOW_RATE_MID_2));
	ui.lcdAccumStdMeter_3->display(getAccumFLowVolume(FLOW_RATE_SMALL));
}

float TotalStandardDlg::getInstFlowRate(flow_rate_wdg idx)
{
	int route = getRouteByWdg(idx, INST_FLOW_VALUE);
	int count = get9017RouteI(route, m_instStdPulse);
	float upperFlow = getStdUpperFlow(idx);
	return getInstStdValue(count, upperFlow);
}

float TotalStandardDlg::getAccumFLowVolume(flow_rate_wdg idx)
{
	int route = getRouteByWdg(idx, ACCUM_FLOW_VALUE);
	int count = get9150ARouteI(route, m_accumStdPulse);
	float pulse = getStdPulse(idx);
	return count*pulse;
}