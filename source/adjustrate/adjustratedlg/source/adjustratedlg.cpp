/***********************************************
**  文件名:     datatestdlg.cpp
**  功能:       采集与控制测试程序
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/12
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/06 第一版
**  内容包含:
**  说明:		只用于测试采集与控制，不作为质量法检定的主界面(2014-07-15备注)
**  更新记录:   
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>

#include "adjustratedlg.h"
#include "commondefine.h"
#include "parasetdlg.h"
#include "readcomconfig.h"
#include "algorithm.h"

AdjustRateDlg::AdjustRateDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	m_stdParam = new QSettings(getFullIniFileName("stdmtrparaset.ini"), QSettings::IniFormat);
	m_rx.setPattern("\\d+(\\.\\d+)?");
}

AdjustRateDlg::~AdjustRateDlg()
{
}

void AdjustRateDlg::showEvent(QShowEvent *event)
{
	qDebug()<<"AdjustRateDlg showEvent thread:"<<QThread::currentThreadId();
	//获取下位机端口配置信息
	if (!getPortSetIni(&m_portsetinfo))
	{
		QMessageBox::warning(this, tr("Warning"), tr("get port set info failed!"));//获取下位机端口配置信息失败!请重新设置！
	}

	initValveStatus();      //初始化阀门状态
	initRegulateStatus();   //初始化调节阀状态

	m_paraSetDlg = NULL;
	m_paraSetReader = new ParaSetReader(); //读参数设置接口

	m_readComConfig = NULL;
	m_readComConfig = new ReadComConfig();

	m_controlObj = NULL;
	initControlCom();		//初始化控制串口

	/********************************************/
	m_instantFlowCom = NULL;
	m_instSTDMeterTimer = NULL;
	initInstStdCom();//初始化瞬时流量串口

	m_accumulateFlowCom = NULL;
	m_accumSTDMeterTimer = NULL;
	initAccumStdCom();//初始化累积流量串口
	/*********************************************/
}

void AdjustRateDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^AdjustRateDlg::closeEvent";

	if (m_paraSetReader) //读检定参数
	{
		delete m_paraSetReader;
		m_paraSetReader = NULL;
	}

	if (m_paraSetDlg) //参数设置对话框
	{
		delete m_paraSetDlg;
		m_paraSetDlg = NULL;
	}

	if (m_readComConfig)  //读串口设置
	{
		delete m_readComConfig;
		m_readComConfig = NULL;
	}

	if (m_controlObj)  //阀门控制
	{
		on_btnSopSet_clicked();//退出时, 关闭水泵
		delete m_controlObj;
		m_controlObj = NULL;

		m_valveThread.exit();
	}
	/*****************************************************/
	if (m_instSTDMeterTimer)
	{
		if (m_instSTDMeterTimer->isActive())
		{
			m_instSTDMeterTimer->stop();
		}

		delete m_instSTDMeterTimer;
		m_instSTDMeterTimer = NULL;
	}

	if (m_instantFlowThread.isRunning())
	{
		m_instantFlowThread.exit();
		if (m_instantFlowCom)
		{
			delete m_instantFlowCom;
			m_instantFlowCom = NULL;
		}
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

	if (m_accumFlowThread.isRunning())
	{
		m_accumFlowThread.exit();
		if (m_accumulateFlowCom)
		{
			delete m_accumulateFlowCom;
			m_accumulateFlowCom = NULL;
		}
	}
	/*****************************************************/
	if (m_pidDataPtr)
	{
		delete m_pidDataPtr;
		m_pidDataPtr = NULL;
	}

	if (m_setRegularTimer) //自动调整流量计时器
	{
		if (m_setRegularTimer->isActive())
		{
			m_setRegularTimer->stop();
		}
		delete m_setRegularTimer;
		m_setRegularTimer = NULL;
	}
	savePidParams();

	if (m_btnGroupValve)
	{
		delete m_btnGroupValve;
		m_btnGroupValve = NULL;
	}
	/*****************************************************/
}

//瞬时流量采集串口, 上位机直接采集
void AdjustRateDlg::initInstStdCom()
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
void AdjustRateDlg::initAccumStdCom()
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

void AdjustRateDlg::slotAskInstPulse()
{
	bool ok;
	uchar address = (uchar)m_stdParam->value("DevNo./InstDevNo").toString().toInt(&ok, 16);
	m_instantFlowCom->ask901712RoutesCmd(address);
}

void AdjustRateDlg::slotAskAccumPulse()
{
	bool ok;
	uchar address = (uchar)m_stdParam->value("DevNo./AccumDevNo").toString().toInt(&ok, 16);
	m_accumulateFlowCom->ask9150A16RoutesCmd(address);
}

/*
** 开辟一个新线程，打开控制板通讯串口
*/
void AdjustRateDlg::initControlCom()
{
	ComInfoStruct valveStruct = m_readComConfig->ReadValveConfig();
	m_controlObj = new ControlComObject();
	m_controlObj->setProtocolVersion(m_portsetinfo.version); //设置协议版本
	m_controlObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_controlObj->openControlCom(&valveStruct);

	connect(m_controlObj, SIGNAL(controlRelayIsOk(const UINT8 &, const bool &)), this, SLOT(slotSetValveBtnStatus(const UINT8 &, const bool &)));
	connect(m_controlObj, SIGNAL(controlRegulateIsOk()), this, SLOT(slotSetRegulateOk()));
	 
	/*****************************************************************************************************/
	m_openRegulateTimes = 0;
	m_pidDataPtr = new PIDDataStr;
	m_pre_error = 0.0;
	m_integral = 0.0;
	ui.lnEditTargetRate_big->setReadOnly(false);
	ui.lnEditTargetRate_mid->setReadOnly(false);
	installPidParams();
	initLineEdits();
	m_btnGroupValve = NULL;
	initBtnGroup();
	m_setRegularTimer = new QTimer;
	connect(m_setRegularTimer, SIGNAL(timeout()), this, SLOT(slotSetRegulate()));
	/*****************************************************************************************************/
}

void AdjustRateDlg::initLineEdits()
{
	QValidator *validator = new QRegExpValidator(m_rx);
	ui.lnEditKp_big->setValidator(validator);
	ui.lnEditKi_big->setValidator(validator);
	ui.lnEditKd_big->setValidator(validator);
	ui.lnEditCycleTime_big->setValidator(validator);
	ui.lnEditMaxRate_big->setValidator(validator);
	ui.lnEditTargetRate_big->setValidator(validator);

	ui.lnEditKp_mid->setValidator(validator);
	ui.lnEditKi_mid->setValidator(validator);
	ui.lnEditKd_mid->setValidator(validator);
	ui.lnEditCycleTime_mid->setValidator(validator);
	ui.lnEditMaxRate_mid->setValidator(validator);
	ui.lnEditTargetRate_mid->setValidator(validator);
}

void AdjustRateDlg::savePidParams()
{
	QSettings pidConfig(getFullIniFileName("pidParameter.ini"), QSettings::IniFormat);

	pidConfig.setValue("Kp_big",ui.lnEditKp_big->text());
	pidConfig.setValue("Ki_big",ui.lnEditKi_big->text());
	pidConfig.setValue("Kd_big",ui.lnEditKd_big->text());
	pidConfig.setValue("CycleTime_big",ui.lnEditCycleTime_big->text());
	pidConfig.setValue("maxrate_big", ui.lnEditMaxRate_big->text());
	pidConfig.setValue("targetrate_big", ui.lnEditTargetRate_big->text());

	pidConfig.setValue("Kp_mid",ui.lnEditKp_mid->text());
	pidConfig.setValue("Ki_mid",ui.lnEditKi_mid->text());
	pidConfig.setValue("Kd_mid",ui.lnEditKd_mid->text());
	pidConfig.setValue("CycleTime_mid",ui.lnEditCycleTime_mid->text());
	pidConfig.setValue("maxrate_mid", ui.lnEditMaxRate_mid->text());
	pidConfig.setValue("targetrate_mid", ui.lnEditTargetRate_mid->text());

	pidConfig.setValue("pumpFreq", ui.spinBoxFreq->value());

	pidConfig.setValue("nowRegNo", m_nowRegNo);
	pidConfig.setValue("valve_big", ui.rBtn_big->isChecked());
	pidConfig.setValue("valve_mid", ui.rBtn_mid->isChecked());
}

void AdjustRateDlg::installPidParams()
{
   QSettings pidConfig(getFullIniFileName("pidParameter.ini"), QSettings::IniFormat);

	ui.lnEditKp_big->setText(pidConfig.value("Kp_big").toString());
	ui.lnEditKi_big->setText(pidConfig.value("Ki_big").toString());
	ui.lnEditKd_big->setText(pidConfig.value("Kd_big").toString());
	ui.lnEditCycleTime_big->setText(pidConfig.value("CycleTime_big").toString());
	ui.lnEditMaxRate_big->setText(pidConfig.value("maxrate_big").toString());
	ui.lnEditTargetRate_big->setText(pidConfig.value("targetrate_big").toString());

	ui.lnEditKp_mid->setText(pidConfig.value("Kp_mid").toString());
	ui.lnEditKi_mid->setText(pidConfig.value("Ki_mid").toString());
	ui.lnEditKd_mid->setText(pidConfig.value("Kd_mid").toString());
	ui.lnEditCycleTime_mid->setText(pidConfig.value("CycleTime_mid").toString());
	ui.lnEditMaxRate_mid->setText(pidConfig.value("maxrate_mid").toString());
	ui.lnEditTargetRate_mid->setText(pidConfig.value("targetrate_mid").toString());

	m_pumpFreq = pidConfig.value("pumpFreq").toInt();
	ui.spinBoxFreq->setValue(m_pumpFreq);

	m_nowRegNo = pidConfig.value("nowRegNo").toInt();
	ui.rBtn_big->setChecked(pidConfig.value("valve_big").toBool());
	ui.rBtn_mid->setChecked(pidConfig.value("valve_mid").toBool());
}

void AdjustRateDlg::initBtnGroup()
{
	m_btnGroupValve = new QButtonGroup(this); //计量单位
	m_btnGroupValve->addButton(ui.rBtn_big, BIG_RBTN);
	m_btnGroupValve->addButton(ui.rBtn_mid, MID_RBTN);
	connect(m_btnGroupValve, SIGNAL(buttonClicked(int)), this, SLOT(slotValveClicked(int)));
}
void AdjustRateDlg::slotValveClicked(int idx)
{
	switch(idx)
	{
	case BIG_RBTN:
		m_nowRegNo = m_portsetinfo.regflow1No;
		m_Kp = ui.lnEditKp_big->text().toFloat();
		m_Ki = ui.lnEditKi_big->text().toFloat();
		m_Kd = ui.lnEditKd_big->text().toFloat();
		m_pickCycleTime = ui.lnEditCycleTime_big->text().toInt();
		m_maxRate = ui.lnEditMaxRate_big->text().toFloat();
		m_targetRate = ui.lnEditTargetRate_big->text().toFloat();
		break;
	case MID_RBTN:
		m_nowRegNo = m_portsetinfo.regflow2No;
		m_Kp = ui.lnEditKp_mid->text().toFloat();
		m_Ki = ui.lnEditKi_mid->text().toFloat();
		m_Kd = ui.lnEditKd_mid->text().toFloat();
		m_pickCycleTime = ui.lnEditCycleTime_mid->text().toInt();
		m_maxRate = ui.lnEditMaxRate_mid->text().toFloat();
		m_targetRate = ui.lnEditTargetRate_mid->text().toFloat();
		break;
	default:
		break;
	}
}

void AdjustRateDlg::on_btnStartSet_clicked()
{
	stopSetRegularTimer();
	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //记录时间戳
	if(m_nowRegNo == m_portsetinfo.regflow1No)
		operateBigPidVales();
	else if( m_nowRegNo == m_portsetinfo.regflow2No)
		operateMidPidVales();

	openPump();//打开水泵
	qDebug() <<"$$$$$$$$$$$$$$$$$$$ starting m_setRegularTimer $$$$$$$$$$$$$$$$$$$";
	slotSetRegulate();//设定后立即调整一次
	m_elapsetime.start();//开启调速计时
	m_setRegularTimer->start(m_pickCycleTime);
}

void AdjustRateDlg::slotSetRegulate()
{
	this->setRegulate(ui.lcdStdMeterFlowRate->value(), m_targetRate);
}

void AdjustRateDlg::setRegulate(float currentRate, float targetRate)
{
	qDebug() << "+++++++++++++++++new set+++++++++++++++++";
	float deltaV = qAbs(targetRate - currentRate);
	m_degree =degreeGet(currentRate, targetRate);
	qDebug() << "current degree: " << m_degree;
	m_controlObj->askControlRegulate(m_nowRegNo, m_degree);
	m_ifGainTargetRate = false;
	if (deltaV <= PRECISION)
	{
		qDebug() << "######################gain target rate######################";
		m_ifGainTargetRate = true;
	}

	m_pidDataPtr->pid_timestamp    = m_timeStamp;
	m_pidDataPtr->pid_maxRate	   = m_maxRate;
	m_pidDataPtr->pid_currentRate  = currentRate;
	m_pidDataPtr->pid_targetRate   = targetRate;
	m_pidDataPtr->pid_currentError = currentRate - targetRate;
	m_pidDataPtr->pid_regularNo	   = m_nowRegNo;
	m_pidDataPtr->pid_waitTime	   = m_pickCycleTime;
	m_pidDataPtr->pid_currentDegree= m_degree;
	m_pidDataPtr->pid_gainTargetRate = 	m_ifGainTargetRate;
	m_pidDataPtr->pid_nowErrorPercent = ((currentRate - targetRate)/targetRate)*100;
	m_pidDataPtr->pid_pumpFreq = m_pumpFreq;
	insertPidRec(m_pidDataPtr);
	qDebug() << "+++++++++++++++++new set end+++++++++++++++++";
}

int AdjustRateDlg::degreeGet(float currentRate, float targetRate)
{
	int watSencond = (m_pickCycleTime/1000);
	m_curr_error = targetRate - currentRate;
	m_integral += m_curr_error*watSencond;
	float derivative = (m_curr_error - m_pre_error)/watSencond;
	float output = m_Kp*m_curr_error + m_Ki*m_integral + m_Kd*derivative;
	qDebug() << "P:--" <<m_Kp*m_curr_error<<" I:--"<<m_Ki*m_integral<<" D:--"<<m_Kd*derivative;
	qDebug() << "oooooutput: " << output;
	m_pre_error = m_curr_error;
	int outdegree =  (int)(output>0 ? output: 0);
	if (outdegree > 99)
	{
		outdegree = 99;
	}
	m_pidDataPtr->pid_Kp = m_Kp;
	m_pidDataPtr->pid_Ki = m_Ki;
	m_pidDataPtr->pid_Kd = m_Kd;
	m_pidDataPtr->pid_P = m_Kp*m_curr_error;
	m_pidDataPtr->pid_I = m_Ki*m_integral;
	m_pidDataPtr->pid_D = m_Kd*derivative;

	return outdegree;
}

void AdjustRateDlg::stopSetRegularTimer()
{
	if (m_setRegularTimer->isActive())
	{
		m_setRegularTimer->stop();
		qDebug() << "m_setRegularTimer stoped";
	}
}

//初始化阀门状态
void AdjustRateDlg::initValveStatus()
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

	//端口号-阀门状态 全部阀门状态为关闭
	m_valveStatus[m_portsetinfo.bigNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.smallNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle1No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle2No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterOutNo] = VALVE_CLOSE;
	//端口号-水泵状态 初始为关闭
	m_valveStatus[m_portsetinfo.pumpNo] = VALVE_CLOSE;

	setValveBtnBackColor(m_valveBtn[m_portsetinfo.bigNo], m_valveStatus[m_portsetinfo.bigNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.smallNo], m_valveStatus[m_portsetinfo.smallNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle1No], m_valveStatus[m_portsetinfo.middle1No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle2No], m_valveStatus[m_portsetinfo.middle2No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterInNo], m_valveStatus[m_portsetinfo.waterInNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterOutNo], m_valveStatus[m_portsetinfo.waterOutNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.pumpNo], m_valveStatus[m_portsetinfo.pumpNo]); //水泵
}

//初始化调节阀状态
void AdjustRateDlg::initRegulateStatus()
{
	m_nowRegNo = 0;

	//端口号-调节阀按钮 映射关系
	m_regBtn[m_portsetinfo.regflow1No] = ui.btnRegulate1;

	//调节阀初始状态
	m_regStatus[m_portsetinfo.regflow1No] = REG_SUCCESS;

	setRegBtnBackColor(m_regBtn[m_portsetinfo.regflow1No], m_regStatus[m_portsetinfo.regflow1No]);
}

/*
** 控制继电器开断
*/
void AdjustRateDlg::on_btnWaterIn_clicked() //进水阀
{
	m_nowPortNo = m_portsetinfo.waterInNo;
	m_controlObj->askControlRelay(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
}

void AdjustRateDlg::on_btnWaterOut_clicked() //出水阀
{
	m_nowPortNo = m_portsetinfo.waterOutNo;
	m_controlObj->askControlRelay(m_nowPortNo, m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
}

void AdjustRateDlg::on_btnValveBig_clicked() //大流量阀
{
	m_nowPortNo = m_portsetinfo.bigNo;
	m_controlObj->askControlRelay(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
	m_nowRegNo = m_portsetinfo.regflow1No;
}

void AdjustRateDlg::on_btnValveMiddle1_clicked() //中流一阀
{
	m_nowPortNo = m_portsetinfo.middle1No;
	m_controlObj->askControlRelay(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
	m_nowRegNo = m_portsetinfo.regflow2No;
}

void AdjustRateDlg::on_btnValveMiddle2_clicked() //中流二阀
{
	m_nowPortNo = m_portsetinfo.middle2No;
	m_controlObj->askControlRelay(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
}

void AdjustRateDlg::on_btnValveSmall_clicked() //小流量阀
{
	m_nowPortNo = m_portsetinfo.smallNo;
	m_controlObj->askControlRelay(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
}

/*
** 控制水泵开关
*/
void AdjustRateDlg::on_btnWaterPump_clicked() //水泵
{
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->askControlWaterPump(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
}

void AdjustRateDlg::openPump()
{
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->askSetDriverFreq(m_pumpFreq);
	m_controlObj->askControlWaterPump(m_nowPortNo, true);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, true);
	}
}

void AdjustRateDlg::closePump()
{
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->askControlWaterPump(m_nowPortNo, false);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, false);
	}
}

void AdjustRateDlg::operateBigPidVales()
{
	openValve(m_portsetinfo.waterInNo);
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.waterOutNo);//防水阀接反, 反向调用
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.bigNo);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.smallNo);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.middle1No);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.middle2No);
}

void AdjustRateDlg::operateMidPidVales()
{
	openValve(m_portsetinfo.waterInNo);
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.waterOutNo);//防水阀接反, 反向调用
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.middle1No);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.smallNo);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.middle2No);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.bigNo);
}

//打开阀门
int AdjustRateDlg::openValve(UINT8 portno)
{
	if (NULL == m_controlObj)
	{
		return false;
	}
	if (portno == m_portsetinfo.waterOutNo)
	{
		m_controlObj->askControlRelay(portno, VALVE_CLOSE);
	}
	else
		m_controlObj->askControlRelay(portno, VALVE_OPEN);

	if (m_portsetinfo.version==OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(portno, VALVE_OPEN);
	}
	return true;
}

//关闭阀门
int AdjustRateDlg::closeValve(UINT8 portno)
{
	if (NULL == m_controlObj)
	{
		return false;
	}
	if (portno == m_portsetinfo.waterOutNo)
	{
		 m_controlObj->askControlRelay(portno, VALVE_OPEN);
	}
	else
		m_controlObj->askControlRelay(portno, VALVE_CLOSE);
	
	if (m_portsetinfo.version==OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(portno, VALVE_CLOSE);
	}
	return true;
}

void AdjustRateDlg::on_btnSopSet_clicked()
{
	stopSetRegularTimer();
	closePump();
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.waterInNo);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.smallNo);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.middle1No);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.middle2No);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.bigNo);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.waterOutNo);
}

//设置频率
void AdjustRateDlg::on_btnSetFreq_clicked()
{
	m_pumpFreq = ui.spinBoxFreq->value();
	m_controlObj->askSetDriverFreq(ui.spinBoxFreq->value());
}

//调节阀
void AdjustRateDlg::on_btnRegulate1_clicked() //调节阀1
{
	stopSetRegularTimer();
	m_nowRegNo = m_portsetinfo.regflow1No;
	setRegBtnBackColor(m_regBtn[m_nowRegNo], false); //初始化调节阀背景色
	m_controlObj->askControlRegulate(m_nowRegNo, ui.spinBoxValveOpening->value());
}

void AdjustRateDlg::on_btnRegulate2_clicked() //调节阀2
{
	stopSetRegularTimer();
	m_nowRegNo = m_portsetinfo.regflow2No;
	setRegBtnBackColor(m_regBtn[m_nowRegNo], false); //初始化调节阀背景色
	m_controlObj->askControlRegulate(m_nowRegNo, ui.spinBoxValveOpening2->value());
}

//参数设置
void AdjustRateDlg::on_btnParaSet_clicked()
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
	m_paraSetDlg->show();
}

void AdjustRateDlg::on_btnExit_clicked()
{
	this->close();
}

//响应阀门状态设置成功
void AdjustRateDlg::slotSetValveBtnStatus(const UINT8 &portno, const bool &status)
{
	m_valveStatus[portno] = status;
	setValveBtnBackColor(m_valveBtn[portno], m_valveStatus[portno]);
}

//响应调节阀调节成功
void AdjustRateDlg::slotSetRegulateOk()
{
	setRegBtnBackColor(m_regBtn[m_nowRegNo], REG_SUCCESS);
}

//设置阀门按钮背景色
void AdjustRateDlg::setValveBtnBackColor(QPushButton *btn, bool status)
{
	if (NULL == btn)
	{
		return;
	}
	if (status) //阀门打开 绿色
	{
		btn->setStyleSheet("background-color:rgb(0,255,0);"); 
	}
	else //阀门关闭 红色
	{
		btn->setStyleSheet("background-color:rgb(255,0,0);border:0px;border-image: url(:/datatestdlg/images/close.png);"); 
	}
}

//设置调节阀按钮背景色
void AdjustRateDlg::setRegBtnBackColor(QPushButton *btn, bool status)
{
	if (NULL == btn)
	{
		return;
	}
}

void AdjustRateDlg::slotGetInstStdMeterPulse(const QByteArray & valueArray)
{
	m_instStdPulse = valueArray;
	freshInstStdMeter();
	float instValue = 0.0;//瞬时流量	
	instValue = ui.lcdInstStdMeter_3->value()+ui.lcdInstStdMeter_10->value()+ui.lcdInstStdMeter_25->value();
	ui.lcdStdMeterFlowRate->display(instValue);
}

int AdjustRateDlg::getRouteByWdg(flow_rate_wdg wdgIdx, flow_type fType)
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

float AdjustRateDlg::getStdUpperFlow(flow_rate_wdg wdgIdx)
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

double AdjustRateDlg::getStdPulse(flow_rate_wdg wdgIdx)
{
	double pulse = 0.0f;
	m_stdParam->beginReadArray("Route");
	m_stdParam->setArrayIndex(wdgIdx);
	int diamWdg = m_stdParam->value("Diameter").toInt();//读取管径的部件号
	m_stdParam->endArray();

	m_stdParam->beginReadArray("Pulse");
	m_stdParam->setArrayIndex(diamWdg);
	pulse = m_stdParam->value("Pulse").toDouble();
	m_stdParam->endArray();
	return pulse;
}

void AdjustRateDlg::slotGetAccumStdMeterPulse(const QByteArray & valueArray)
{
	m_accumStdPulse = valueArray;
	freshAccumStdMeter();
	float accumValue = 0.0;//累积流量	
	accumValue = ui.lcdAccumStdMeter_3->value()+ui.lcdAccumStdMeter_10->value()+ui.lcdAccumStdMeter_25->value();
	ui.lcdAccumStdMeter->display(accumValue);	
}

void AdjustRateDlg::freshInstStdMeter()
{
	ui.lcdInstStdMeter_25->display(getInstFlowRate(FLOW_RATE_BIG));
	ui.lcdInstStdMeter_10->display(getInstFlowRate(FLOW_RATE_MID_1));
	ui.lcdInstStdMeter_3->display(getInstFlowRate(FLOW_RATE_SMALL));
}

void AdjustRateDlg::freshAccumStdMeter()
{
	ui.lcdAccumStdMeter_25->display(getAccumFLowVolume(FLOW_RATE_BIG));
	ui.lcdAccumStdMeter_10->display(getAccumFLowVolume(FLOW_RATE_MID_1));
	ui.lcdAccumStdMeter_3->display(getAccumFLowVolume(FLOW_RATE_SMALL));
}

float AdjustRateDlg::getInstFlowRate(flow_rate_wdg idx)
{
	int route = getRouteByWdg(idx, INST_FLOW_VALUE);
	int count = get9017RouteI(route, m_instStdPulse);
	float upperFlow = getStdUpperFlow(idx);
	//qDebug() <<"valve:--"<<idx<<" count:--"<<count<<" upperFlow:--"<<upperFlow;
	return getInstStdValue(count, upperFlow);
}

float AdjustRateDlg::getAccumFLowVolume(flow_rate_wdg idx)
{
	int route = getRouteByWdg(idx, ACCUM_FLOW_VALUE);
	int count = get9150ARouteI(route, m_accumStdPulse);
	double pulse = getStdPulse(idx);
	//qDebug() <<"valve:--"<<idx<<" count:--"<<count<<" pulse:--"<<pulse;
	return count*pulse;
}