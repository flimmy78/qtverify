/***********************************************
**  文件名:     qualitydlg.cpp
**  功能:       质量法-分量检定-主界面
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/12
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/06 第一版
**  内容包含:
**  说明:
**  更新记录:
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>

#include "qualitydlg.h"

QualityDlg::QualityDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"QualityDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	m_paraset = NULL;
	m_paraset = new ParaSetDlg();

	m_readComConfig = NULL;
	m_readComConfig = new ReadComConfig();

	m_tempObj = NULL;
	m_tempTimer = NULL;
// 	initTemperatureCom();	//初始化温度采集串口

	m_controlObj = NULL;
	initControlCom();		//初始化控制串口

	initValveStatus();      //初始化阀门状态

	m_balanceObj = NULL;
// 	initBalanceCom();		//初始化天平串口

	m_meterObj1 = NULL;
// 	initHeatMeterCom1();	//初始化热量表1串口

	m_flowcount = 0;
	m_flow1 = 0.0;
	m_flow2 = 0.0;

	getPortSetIni(&m_portsetinfo); //获取下位机端口配置信息
	getParaSetIni(&m_parasetinfo); //获取参数设置信息
	qDebug()<<"metertype:"<<m_parasetinfo.metertype;
}

QualityDlg::~QualityDlg()
{
}

void QualityDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^QualityDlg::closeEvent";

	if (m_paraset)  //参数设置
	{
		delete m_paraset;
		m_paraset = NULL;
	}

	if (m_readComConfig)  //读串口设置
	{
		delete m_readComConfig;
		m_readComConfig = NULL;
	}

	if (m_tempObj)  // 温度采集
	{
		delete m_tempObj;
		m_tempObj = NULL;
	}

	if (m_controlObj)  //阀门控制
	{
		delete m_controlObj;
		m_controlObj = NULL;
	}

	if (m_balanceObj)  //天平采集
	{
		delete m_balanceObj;
		m_balanceObj = NULL;
	}
	
	if (m_meterObj1)  //热量表1串口通讯
	{
		delete m_meterObj1;
		m_meterObj1 = NULL;
	}
}

/***************************************
	温度采集
	周期请求
****************************************/
void QualityDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadTempConfig();
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer(this);
	connect(m_tempTimer, SIGNAL(timeout()), m_tempObj, SLOT(writeTemperatureComBuffer()));
	connect(m_tempTimer, SIGNAL(timeout()), this, SLOT(slotFreshFlow()));
	
	m_tempTimer->start(TIMEOUT_TEMPER); //周期请求温度
}

//控制板通讯串口
void QualityDlg::initControlCom()
{
	ComInfoStruct valveStruct = m_readComConfig->ReadValveConfig();
	m_controlObj = new ControlComObject();
	m_controlObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_controlObj->openControlCom(&valveStruct);

	connect(m_controlObj, SIGNAL(controlRelayIsOk()), this, SLOT(slotSetValveBtnStatus()));
	connect(m_controlObj, SIGNAL(controlRegulateIsOk()), this, SLOT(slotSetRegulateOk()));
}

//初始化阀门状态
void QualityDlg::initValveStatus()
{
	m_nowPortNo = 0;
	m_nowPortIdx = 0;

	for(int i=0; i<VALVE_NUM; i++)
	{
		m_valveStatus[i] = VALVE_CLOSE;
	}
	m_valveBtn[VALVE_IN_IDX] = ui.btnWaterIn;
	m_valveBtn[VALVE_BIG_IDX] = ui.btnValveBig;
	m_valveBtn[VALVE_MID1_IDX] = ui.btnValveMiddle1;
	m_valveBtn[VALVE_MID2_IDX] = ui.btnValveMiddle2;
	m_valveBtn[VALVE_SMALL_IDX] = ui.btnValveSmall;
	m_valveBtn[VALVE_OUT_IDX] = ui.btnWaterOut;
	m_valveBtn[VALVE_PUMP_IDX] = ui.btnWaterPump;

	for(int i=0; i<VALVE_NUM; i++)
	{
		setBtnBackColor(m_valveBtn[i], m_valveStatus[i]);
	}

	
/*	m_waterInStatus = VALVE_CLOSE;//进水阀门状态 
	setBtnBackColor(ui.btnWaterIn, m_waterInStatus);

	m_waterOutStatus = VALVE_CLOSE;//放水阀门状态  
	setBtnBackColor(ui.btnWaterOut, m_waterOutStatus);

	m_valveBigStatus = VALVE_CLOSE; //大流量点阀门状态
	setBtnBackColor(ui.btnValveBig, m_valveBigStatus);

	m_valveMiddle1Status = VALVE_CLOSE;//中流一阀门状态  
	setBtnBackColor(ui.btnValveMiddle1, m_valveMiddle1Status);

	m_valveMiddle2Status = VALVE_CLOSE; //中流二阀门状态
	setBtnBackColor(ui.btnValveMiddle2, m_valveMiddle1Status);

	m_valveSmallStatus = VALVE_CLOSE; //小流量点阀门状态
	setBtnBackColor(ui.btnValveSmall, m_valveSmallStatus);

	m_valvePumpStatus = VALVE_CLOSE; //水泵状态
	setBtnBackColor(ui.btnWaterPump, m_valvePumpStatus);*/
}

//天平采集串口
void QualityDlg::initBalanceCom()
{
	ComInfoStruct balanceStruct = m_readComConfig->ReadBalanceConfig();
	m_balanceObj = new BalanceComObject();
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

 	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const QString &)), this, SLOT(slotFreshBalanceValue(const QString &)));
}

//热量表1串口通讯
void QualityDlg::initHeatMeterCom1()
{
	ComInfoStruct comStruct = m_readComConfig->ReadMeterConfigByNum("1");
	m_meterObj1 = new MeterComObject();
	m_meterObj1->moveToThread(&m_meterThread1);
	m_meterThread1.start();
	m_meterObj1->openMeterCom1(&comStruct);

// 	connect(m_meterObj1, SIGNAL(balanceValueIsReady(const QString &)), this, SLOT(slotFreshBalanceValue(const QString &)));
}

/*
**	控制继电器开断
*/
void QualityDlg::on_btnWaterIn_clicked() //进水阀
{
	m_nowPortIdx = VALVE_IN_IDX;
	m_nowPortNo = m_portsetinfo.waterInNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);
}

void QualityDlg::on_btnWaterOut_clicked() //出水阀
{
	m_nowPortIdx = VALVE_OUT_IDX;
	m_nowPortNo = m_portsetinfo.waterOutNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);

// 	m_balanceObj->writeBalanceComBuffer(); //临时调试用(模拟天平连续发送数据) 写天平串口缓冲区
}

void QualityDlg::on_btnValveBig_clicked() //大流量阀
{
	m_nowPortIdx = VALVE_BIG_IDX;
	m_nowPortNo = m_portsetinfo.bigNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);
}

void QualityDlg::on_btnValveMiddle1_clicked() //中流一阀
{
	m_nowPortIdx = VALVE_MID1_IDX;
	m_nowPortNo = m_portsetinfo.middle1No;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);

}

void QualityDlg::on_btnValveMiddle2_clicked() //中流二阀
{
	m_nowPortIdx = VALVE_MID2_IDX;
	m_nowPortNo = m_portsetinfo.middle2No;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);

}

void QualityDlg::on_btnValveSmall_clicked() //小流量阀
{
	m_nowPortIdx = VALVE_SMALL_IDX;
	m_nowPortNo = m_portsetinfo.smallNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);
}

void QualityDlg::on_btnWaterPump_clicked() //水泵
{
	m_nowPortIdx = VALVE_PUMP_IDX;
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);
}


/*
**	调节阀开度
*/
void QualityDlg::on_btnRegulate1_clicked() //调节阀1
{
// 	ui.btnRegulate1->setStyleSheet("background:light;border:0px;");  
	UINT8 portno = m_portsetinfo.regflow1No;
	m_controlObj->makeRegulateSendBuf(portno, ui.spinBox1->value());
}

//查询从机状态
void QualityDlg::on_btnQueryStatus_clicked()
{
	m_controlObj->makeQuerySendBuf();
}

void QualityDlg::on_btnParaSet_clicked()
{
	m_paraset->show();
}

void QualityDlg::on_btnStart_clicked()
{
	m_balanceObj->setSendContinue(false); //临时调试用(模拟天平连续发送数据) 停止连续发送
}

void QualityDlg::on_btnExit_clicked()
{
	this->close();
}

void QualityDlg::slotFreshComTempValue(const QString& tempStr)
{
	ui.lnEditTempIn->setText(tempStr.right(DATA_WIDTH)); //入口温度 PV
	ui.lnEditTempOut->setText(tempStr.left(DATA_WIDTH)); //出口温度 SV
}

void QualityDlg::slotFreshBalanceValue(const QString& Str)
{
	ui.lnEditBigBalance->setText(Str);
	double v = ui.lnEditBigBalance->text().toDouble();
	ui.lnEditSmallBalance->setText(QString("%1").arg(v, 9, 'f', 4));
}

void QualityDlg::slotSetValveBtnStatus()
{
	m_valveStatus[m_nowPortIdx] = !m_valveStatus[m_nowPortIdx];
	setBtnBackColor(m_valveBtn[m_nowPortIdx], m_valveStatus[m_nowPortIdx]);
}

void QualityDlg::slotSetRegulateOk()
{
	setBtnBackColor(ui.btnRegulate1, true);
}

void QualityDlg::setBtnBackColor(QPushButton *btn, bool status)
{
	if (status) //阀门打开 绿色
	{
		btn->setStyleSheet("background:green;border:0px;");  
		btn->setIcon(QIcon("open.png"));
	}
	else //阀门关闭 红色
	{
		btn->setStyleSheet("background:lightgray;border:0px;");  
		btn->setIcon(QIcon("close.png"));
	}
}

//计算瞬时流量
void QualityDlg::slotFreshFlow()
{
	float flowValue = 0.0;
	if (m_flowcount == 0)
	{
		m_flow1 = ui.lnEditBigBalance->text().toFloat();
	}
	m_flowcount ++;
	if (m_flowcount == 20) //20*TIMEOUT_TEMPER
	{
		m_flow2 = ui.lnEditBigBalance->text().toFloat();
		m_flowcount = 0;
		flowValue = 3.6*(m_flow2 - m_flow1)/(20*TIMEOUT_TEMPER);
		ui.lnEditFlow->setText(QString("%1").arg(flowValue));
	}
}

//读取表号
void QualityDlg::on_btnReadMeterNo_clicked()
{
// 	m_meterObj1->writeMeterCom1Buffer(); //请求表号
}


