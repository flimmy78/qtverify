/***********************************************
**  文件名:     flowstandard50.cpp
**  功能:       流量检定(标准表法）主界面-DN50，双天平、双控制板
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/11/27
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2015/11 第一版
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

#include "stdmtrcoecorrect.h"
#include "commondefine.h"
#include "algorithm.h"
#include "qtexdb.h"
#include "parasetdlg.h"
#include "readcomconfig.h"
#include "report.h"
#include "readstdmeter.h"

StdMtrCoeCorrect::StdMtrCoeCorrect(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"StdMtrCoeCorrect thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	if (!getPortSetIni(&m_portsetinfo)) //获取下位机端口号配置信息
	{
		QMessageBox::warning(this, tr("Warning"), tr("Warning:get port set info failed!"));
	}

	m_readComConfig = NULL;
	m_readComConfig = new ReadComConfig(); //读串口设置接口（必须在initBalanceCom前调用）

	m_balanceObj = NULL;
	initBalanceCom();		//初始化天平串口

	m_balanceObj2 = NULL;
	initBalanceCom2();		//初始化天平串口2

	m_tempObj = NULL;
	m_tempTimer = NULL;
	m_avgTFCount = 0;
	m_tempPipeOut = 0.0;
	initTemperatureCom();	//初始化温度采集串口

	m_controlObj = NULL;
	initControlCom();		//初始化控制串口

	m_controlObj2 = NULL;
	initControlCom2();		//初始化控制串口2

	//计算类接口
	m_chkAlg = NULL;
	m_chkAlg = new CAlgorithm();
	//标准表的配置文件
	m_stdMeterConfig = NULL;
	m_stdMeterConfig = new QSettings(getFullIniFileName("stdmtrparaset.ini"), QSettings::IniFormat);

	//映射关系；初始化阀门状态	
	initValveStatus();      
	initRegulateStatus();
	initTableWdg();//初始化表格
	m_exaustTimer = NULL;
	m_exaustTimer = new QTimer(this); //排气定时器
	connect(m_exaustTimer, SIGNAL(timeout()), this, SLOT(slotExaustFinished()));

	QSqlTableModel *model = new QSqlTableModel(this, g_defaultdb);  
	model->setTable("T_Meter_Standard");  
	model->select();  

	ui.lcdInTemper->display(50);
	ui.lcdOutTemper->display(50);

	m_curStdMeter = -1;//初始化, 用户未选中任何标准表
	/***************标准流量计***********************/
	m_stdMeterReader = NULL;
	m_stdMeterReader = new CStdMeterReader;

	m_stdMeterReader->startReadMeter();
	/***************标准流量计end********************/
}

StdMtrCoeCorrect::~StdMtrCoeCorrect()
{
}

void StdMtrCoeCorrect::showEvent(QShowEvent * event)
{
	qDebug()<<"StdMtrCoeCorrect::showEvent";
}

void StdMtrCoeCorrect::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^StdMtrCoeCorrect::closeEvent";
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

	openValve(m_portsetinfo.bigWaterOutNo);
	openValve(m_portsetinfo.bigNo); //打开大流量点阀门，释放管路压力
 	wait(RELEASE_PRESS_TIME); //等待2秒，释放管路压力
	closeValve(m_portsetinfo.bigNo);

	RELEASE_PTR(m_readComConfig)//读串口设置
	RELEASE_PTR(m_chkAlg)//计算类

	EXIT_THREAD(m_tempThread)// 温度采集
	RELEASE_PTR(m_tempObj)
	
	//天平采集
	EXIT_THREAD(m_balanceThread)
	RELEASE_PTR(m_balanceObj)
	EXIT_THREAD(m_balanceThread2)
	RELEASE_PTR(m_balanceObj2)

	RELEASE_TIMER(m_tempTimer)//采集温度计时器
	EXIT_THREAD(m_tempThread) //温度采集线程
	RELEASE_PTR(m_tempObj)

	EXIT_THREAD(m_valveThread);
	RELEASE_PTR(m_controlObj)  //阀门控制
	EXIT_THREAD(m_valveThread2);	
	RELEASE_PTR(m_controlObj2)  //阀门控制2
	RELEASE_TIMER(m_exaustTimer) //排气计时器
	//计时器，用于动态显示调节阀开度
	RELEASE_TIMER(m_regSmallTimer)
	RELEASE_TIMER(m_regMid1Timer)
	RELEASE_TIMER(m_regMid2Timer)
	RELEASE_TIMER(m_regBigTimer)

	RELEASE_PTR(m_stdMeterReader)//标准表读取
	m_curStdMeter = -1;
	RELEASE_PTR(m_stdMeterConfig)//标准表的配置文件
	emit signalClosed();
}

void StdMtrCoeCorrect::resizeEvent(QResizeEvent * event)
{
	qDebug()<<"StdMtrCoeCorrect::resizeEvent...";

	int th = ui.tableWidget->size().height();
	int tw = ui.tableWidget->size().width();
	int hh = ui.tableWidget->horizontalHeader()->size().height();
	int vw = ui.tableWidget->verticalHeader()->size().width();
	int vSize = (int)((th-hh-10)/ui.tableWidget->rowCount());
	int hSize = (int)((tw-vw-10)/ui.tableWidget->columnCount());
	ui.tableWidget->verticalHeader()->setDefaultSectionSize(vSize);
	ui.tableWidget->horizontalHeader()->setDefaultSectionSize(hSize);
}

void StdMtrCoeCorrect::slotFreshInstFlow(const flow_rate_wdg& idx, const float& value)
{

}

void StdMtrCoeCorrect::slotFreshAccumFlow(const flow_rate_wdg& idx, const float& value)
{

}

void StdMtrCoeCorrect::slotFreshTolInst(const float& value)
{

}

void StdMtrCoeCorrect::slotFreshTolAccum(const float& value)
{

}

void StdMtrCoeCorrect::initTableWdg()
{
	disconnect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
	ui.tableWidget->setRowCount(FLOW_POINTS*CHK_CNTS);
	ui.tableWidget->setColumnCount(COL_CNTS);
	ui.tableWidget->verticalHeader()->setVisible(false);
	QStringList header;
	header<<tr("Flow Point\n(m3/h)")
		  <<tr("balance V0\n(kg)")
		  <<tr("balance V1\n(kg)")
		  <<tr("balance value\n(kg)")
		  <<tr("density\n(kg/L)")
		  <<tr("Actual Value\n(L)")
		  <<tr("Stand Meter Value0\n(L)")
		  <<tr("Stand Meter Value1\n(L)")
		  <<tr("Stand Meter DispValue\n(L)")
		  <<tr("Meter Coe")
		  <<tr("AVG Meter Coe")
		  <<tr("repetitiveness\n(%)");
	ui.tableWidget->setHorizontalHeaderLabels(header);

	for (int i=0; i<ui.tableWidget->rowCount(); i++)
	{
		for (int j=0; j<ui.tableWidget->columnCount(); j++)
		{
			ui.tableWidget->setItem(i, j, new QTableWidgetItem(QString("")));
		}
	}

	for (int i=0; i<ui.tableWidget->rowCount(); i+=CHK_CNTS)
	{
		ui.tableWidget->setSpan(i, COL_FLOW_POINT, CHK_CNTS, 1);
		ui.tableWidget->setSpan(i, COL_STDERR_AVR, CHK_CNTS, 1);
		ui.tableWidget->setSpan(i, COL_STDREP, CHK_CNTS, 1);
	}
	connect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
}

//天平采集串口 上位机直接采集
void StdMtrCoeCorrect::initBalanceCom()
{
	ComInfoStruct balanceStruct = m_readComConfig->ReadBalanceConfig();
	m_balanceObj = new BalanceComObject();
	int type = m_readComConfig->getBalanceType();
	m_balanceObj->setBalanceType(type);
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

	//天平数值由上位机直接通过天平串口采集
	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const float &)), this, SLOT(slotFreshBigBalanceValue(const float &)));
}

//天平采集串口2 上位机直接采集
void StdMtrCoeCorrect::initBalanceCom2()
{
	ComInfoStruct balanceStruct2 = m_readComConfig->ReadBalanceConfig2();
	m_balanceObj2 = new BalanceComObject();
	int type = m_readComConfig->getBalanceType2();
	m_balanceObj2->setBalanceType(type);
	m_balanceObj2->moveToThread(&m_balanceThread2);
	m_balanceThread2.start();
	m_balanceObj2->openBalanceCom(&balanceStruct2);

	//天平数值由上位机直接通过天平串口采集
	connect(m_balanceObj2, SIGNAL(balanceValueIsReady(const float &)), this, SLOT(slotFreshSmallBalanceValue(const float &)));
}

/*
** 温度采集串口 上位机直接采集
** 周期请求
*/
void StdMtrCoeCorrect::initTemperatureCom()
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

void StdMtrCoeCorrect::slotAskPipeTemperature()
{
	m_tempObj->writeTemperatureComBuffer();
}

//控制板通讯串口
void StdMtrCoeCorrect::initControlCom()
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

//控制板通讯串口2
void StdMtrCoeCorrect::initControlCom2()
{
	ComInfoStruct valveStruct2 = m_readComConfig->ReadValveConfig2();
	m_controlObj2 = new ControlComObject();
	m_controlObj2->setProtocolVersion(m_portsetinfo.version);
	m_controlObj2->moveToThread(&m_valveThread2);
	m_valveThread2.start();
	m_controlObj2->openControlCom(&valveStruct2);

	connect(m_controlObj2, SIGNAL(controlRelayIsOk(const UINT8 &, const bool &)), this, SLOT(slotSetValveBtnStatus(const UINT8 &, const bool &)));
	connect(m_controlObj2, SIGNAL(controlRegulateIsOk()), this, SLOT(slotSetRegulateOk()));
}

/*
** 端口号-阀门映射关系；初始化阀门状态（默认阀门初始状态全部为关闭,水泵初始状态为关闭）
** 需要改进得更加灵活
*/
void StdMtrCoeCorrect::initValveStatus()
{
	m_nowPortNo = 0;

	//端口号-阀门按钮 映射关系
	m_valveBtn[m_portsetinfo.bigNo] = ui.btnValveBig;
	m_valveBtn[m_portsetinfo.smallNo] = ui.btnValveSmall;
	m_valveBtn[m_portsetinfo.middle1No] = ui.btnValveMiddle1;
	m_valveBtn[m_portsetinfo.middle2No] = ui.btnValveMiddle2;
	m_valveBtn[m_portsetinfo.waterInNo] = ui.btnWaterIn;
	m_valveBtn[m_portsetinfo.bigWaterInNo] = ui.btnBigWaterIn;
	m_valveBtn[m_portsetinfo.bigWaterOutNo] = ui.btnBigWaterOut;
	m_valveBtn[m_portsetinfo.smallWaterInNo] = ui.btnSmallWaterIn;
	m_valveBtn[m_portsetinfo.smallWaterOutNo] = ui.btnSmallWaterOut;
	m_valveBtn[m_portsetinfo.pumpNo] = ui.btnWaterPump; //水泵

	//初始化：放水阀为打开，其他阀门为关闭状态
	m_valveStatus[m_portsetinfo.bigNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.smallNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle1No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle2No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.bigWaterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.bigWaterOutNo] = VALVE_OPEN;
	m_valveStatus[m_portsetinfo.smallWaterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.smallWaterOutNo] = VALVE_OPEN;
	m_valveStatus[m_portsetinfo.pumpNo] = VALVE_CLOSE; //水泵

	setValveBtnBackColor(m_valveBtn[m_portsetinfo.bigNo], m_valveStatus[m_portsetinfo.bigNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.smallNo], m_valveStatus[m_portsetinfo.smallNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle1No], m_valveStatus[m_portsetinfo.middle1No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle2No], m_valveStatus[m_portsetinfo.middle2No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterInNo], m_valveStatus[m_portsetinfo.waterInNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.bigWaterInNo], m_valveStatus[m_portsetinfo.bigWaterInNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.bigWaterOutNo], m_valveStatus[m_portsetinfo.bigWaterOutNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.smallWaterInNo], m_valveStatus[m_portsetinfo.smallWaterInNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.smallWaterOutNo], m_valveStatus[m_portsetinfo.smallWaterOutNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.pumpNo], m_valveStatus[m_portsetinfo.pumpNo]);
}

void StdMtrCoeCorrect::initRegulateStatus()
{
	//端口号-阀门按钮 映射关系
	m_RegLineEdit[m_portsetinfo.regSmallNo] = ui.lineEditOpeningSmall;
	m_RegLineEdit[m_portsetinfo.regMid1No] = ui.lineEditOpeningMid1;
	m_RegLineEdit[m_portsetinfo.regMid2No] = ui.lineEditOpeningMid2;
	m_RegLineEdit[m_portsetinfo.regBigNo] = ui.lineEditOpeningBig;

	m_RegSpinBox[m_portsetinfo.regSmallNo] = ui.spinBoxOpeningSmall;
	m_RegSpinBox[m_portsetinfo.regMid1No] = ui.spinBoxOpeningMid1;
	m_RegSpinBox[m_portsetinfo.regMid2No] = ui.spinBoxOpeningMid2;
	m_RegSpinBox[m_portsetinfo.regBigNo] = ui.spinBoxOpeningBig;

	//计时器，动态显示调节阀开度
	m_smallOpening = 0;
	m_regSmallTimer = NULL;
	m_regSmallTimer = new QTimer();
	connect(m_regSmallTimer, SIGNAL(timeout()), this, SLOT(slotFreshSmallRegOpening()));

	m_mid1Opening = 0;
	m_regMid1Timer = NULL;
	m_regMid1Timer = new QTimer();
	connect(m_regMid1Timer, SIGNAL(timeout()), this, SLOT(slotFreshMid1RegOpening()));

	m_mid2Opening = 0;
	m_regMid2Timer = NULL;
	m_regMid2Timer = new QTimer();
	connect(m_regMid2Timer, SIGNAL(timeout()), this, SLOT(slotFreshMid2RegOpening()));

	m_bigOpening = 0;
	m_regBigTimer = NULL;
	m_regBigTimer = new QTimer();
	connect(m_regBigTimer, SIGNAL(timeout()), this, SLOT(slotFreshBigRegOpening()));
}

//在界面刷新入口温度和出口温度值
void StdMtrCoeCorrect::slotFreshComTempValue(const QString& tempStr)
{
	ui.lcdInTemper->display(tempStr.left(TEMPER_DATA_WIDTH));   //入口温度 PV
	ui.lcdOutTemper->display(tempStr.right(TEMPER_DATA_WIDTH)); //出口温度 SV
	m_avgTFCount++;
	m_tempPipeOut += ui.lcdOutTemper->value();
	m_tempPipeOut /= m_avgTFCount;
}

/*
** 打开所有阀门和水泵（关闭大、小天平进水阀，因为标准表法不需要使用天平）
*/
int StdMtrCoeCorrect::openAllValveAndPump()
{
	openValve(m_portsetinfo.bigWaterOutNo); //大天平放水阀
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.smallWaterOutNo);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.bigWaterInNo);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.smallWaterInNo);
	wait(CYCLE_TIME);
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
int StdMtrCoeCorrect::closeAllValveAndPumpOpenOutValve()
{
	openValve(m_portsetinfo.bigWaterOutNo); //打开大天平放水阀
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.bigWaterInNo);  //关闭大天平进水阀
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.smallWaterOutNo);//打开小天平放水阀
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.smallWaterInNo);//关闭小天平进水阀
	wait(CYCLE_TIME);
	closeWaterPump();    //退出时关闭水泵
	closeAllFlowPointValves();//关闭所有流量点阀门
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.waterInNo);//关闭进水阀

	return true;
}

//关闭所有流量点阀门
int StdMtrCoeCorrect::closeAllFlowPointValves()
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

//清空表格，第一列除外("流量点"列)
void StdMtrCoeCorrect::clearTableContents()
{
	for (int i=0; i<18; i++)
	{
		for (int j=1; j<ui.tableWidget->columnCount(); j++) //从第二列开始
		{
			if (ui.tableWidget->item(i,j) == NULL)
				continue;

			ui.tableWidget->item(i,j)->setText("");
		}
	}
}

void StdMtrCoeCorrect::on_btnExit_clicked()
{
	this->close();
}

//打开阀门
int StdMtrCoeCorrect::openValve(UINT8 portno)
{	
	if (portno <= 8)
	{
		if (m_controlObj)
			m_controlObj->askControlRelay(portno, VALVE_OPEN);
		else
			return false;
	}
	else
	{
		if (m_controlObj2)
			m_controlObj2->askControlRelay(portno-8, VALVE_OPEN);
		else
			return false;
	}
	if (m_portsetinfo.version==OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(portno, VALVE_OPEN);
	}
	return true;
}

//关闭阀门
int StdMtrCoeCorrect::closeValve(UINT8 portno)
{
	if (portno <= 8)
	{
		if (m_controlObj)
			m_controlObj->askControlRelay(portno, VALVE_CLOSE);
		else
			return false;
	}
	else
	{
		if (m_controlObj2)
			m_controlObj2->askControlRelay(portno-8, VALVE_CLOSE);
		else
			return false;
	}
	if (m_portsetinfo.version==OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(portno, VALVE_CLOSE);
	}
	return true;
}

//操作阀门：打开或者关闭
int StdMtrCoeCorrect::operateValve(UINT8 portno)
{
	if (m_valveStatus[portno]==VALVE_OPEN) //阀门原来是打开状态
	{
		closeValve(portno);
	}
	else //阀门原来是关闭状态
	{
		openValve(portno);
	}
	return true;
}

//打开水泵
int StdMtrCoeCorrect::openWaterPump()
{
	if (NULL == m_controlObj)
	{
		return false;
	}
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->askControlWaterPump(m_nowPortNo, VALVE_OPEN);
	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, VALVE_OPEN);
	}
	return true;
}

//关闭水泵
int StdMtrCoeCorrect::closeWaterPump()
{
	if (NULL == m_controlObj)
	{
		return false;
	}
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->askControlWaterPump(m_nowPortNo, VALVE_CLOSE);
	if (m_portsetinfo.version == OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(m_nowPortNo, VALVE_CLOSE);
	}
	return true;
}

//操作水泵 打开或者关闭
int StdMtrCoeCorrect::operateWaterPump()
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
void StdMtrCoeCorrect::slotSetValveBtnStatus(const UINT8 &portno, const bool &status)
{
	m_valveStatus[portno] = status;
	setValveBtnBackColor(m_valveBtn[portno], m_valveStatus[portno]);
}

//响应调节阀调节成功
void StdMtrCoeCorrect::slotSetRegulateOk()
{
}

//设置阀门按钮背景色
void StdMtrCoeCorrect::setValveBtnBackColor(QToolButton *btn, bool status)
{
	if (NULL == btn)
	{
		return;
	}
	if (status) //阀门打开 绿色
	{
		btn->setStyleSheet("background-color:rgb(0,255,0);border:0px;border-radius:10px;");
	}
	else //阀门关闭 红色
	{
		btn->setStyleSheet("background-color:rgb(255,0,0);border:0px;border-radius:10px;");
	}
}

//设置调节阀按钮背景色
void StdMtrCoeCorrect::setRegBtnBackColor(QPushButton *btn, bool status)
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

/*
** 控制继电器开断
*/
void StdMtrCoeCorrect::on_btnWaterIn_clicked() //进水阀
{
	m_nowPortNo = m_portsetinfo.waterInNo;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnBigWaterIn_clicked() //大天平进水阀
{
	m_nowPortNo = m_portsetinfo.bigWaterInNo;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnBigWaterOut_clicked() //大天平放水阀
{
	m_nowPortNo = m_portsetinfo.bigWaterOutNo;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnSmallWaterIn_clicked() //小天平进水阀
{
	m_nowPortNo = m_portsetinfo.smallWaterInNo;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnSmallWaterOut_clicked() //小天平放水阀
{
	m_nowPortNo = m_portsetinfo.smallWaterOutNo;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnValveBig_clicked() //大流量阀
{
	m_nowPortNo = m_portsetinfo.bigNo;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnValveMiddle1_clicked() //中流一阀
{
	m_nowPortNo = m_portsetinfo.middle1No;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnValveMiddle2_clicked() //中流二阀
{
	m_nowPortNo = m_portsetinfo.middle2No;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnValveSmall_clicked() //小流量阀
{
	m_nowPortNo = m_portsetinfo.smallNo;
	operateValve(m_nowPortNo);
}

/*
** 控制水泵开关
*/
void StdMtrCoeCorrect::on_btnWaterPump_clicked()
{
	m_nowPortNo = m_portsetinfo.pumpNo;
	operateWaterPump();
}

/*
** 设置变频器频率
*/
void StdMtrCoeCorrect::on_btnSetFreq_clicked()
{
	if (m_controlObj)
		m_controlObj->askSetDriverFreq(ui.spinBoxFreq->value());
}

void StdMtrCoeCorrect::on_btnStdMeterV0_clicked()
{

}

void StdMtrCoeCorrect::on_btnStdMeterV1_clicked()
{

}

/*
** 响应处理用户输入完表初值、表终值
   输入参数：
      row：行数，从0开始
	  column：列数，从0开始
*/
void StdMtrCoeCorrect::on_tableWidget_cellChanged(int row, int column)
{
	bool ok;
	float value0=0.0, value1=0.0;
	float avr = 0.0;
	float rep = 0.0;
	float density=0.0;
	float balDisp=0.0;
	int notEmpty = 0;
	int startRow = 0;
	int endRow   = 0;

	switch (column)
	{
	case COL_BALV0:
		if (!ui.tableWidget->item(row,COL_BALV1)->text().isEmpty())
		{
			value0 = ui.tableWidget->item(row,COL_BALV0)->text().toFloat(&ok);
			if (ok)
			{
				value1 = ui.tableWidget->item(row,COL_BALV1)->text().toFloat(&ok);
				if (ok)
					ui.tableWidget->item(row,COL_BALVD)->setText(QString::number(value1-value0));
			}
		}
	case COL_BALV1:
		if (!ui.tableWidget->item(row,COL_BALV0)->text().isEmpty())
		{
			value1 = ui.tableWidget->item(row,COL_BALV1)->text().toFloat(&ok);
			if (ok)
			{
				value0 = ui.tableWidget->item(row,COL_BALV0)->text().toFloat(&ok);
				if (ok)
					ui.tableWidget->item(row,COL_BALVD)->setText(QString::number(value1-value0));
			}
		}
		break;
	case COL_BALVD:
		density = m_chkAlg->getDensityByQuery(m_tempPipeOut);
		ui.tableWidget->item(row,COL_DEN)->setText(QString::number(density));
		break;
	case COL_DEN:
		balDisp = ui.tableWidget->item(row, COL_BALVD)->text().toFloat(&ok);	
		density = ui.tableWidget->item(row, COL_DEN)->text().toFloat(&ok);	
		ui.tableWidget->item(row,COL_BALVC)->setText(QString::number(balDisp/density));
		break;
	case COL_STDV0:
		if (!ui.tableWidget->item(row,COL_STDV1)->text().isEmpty())
		{
			value0 = ui.tableWidget->item(row,COL_STDV0)->text().toFloat(&ok);
			if (ok)
			{
				value1 = ui.tableWidget->item(row,COL_STDV1)->text().toFloat(&ok);
				if (ok)
					ui.tableWidget->item(row,COL_STDVD)->setText(QString::number(value1-value0));		
			}
		}
		break;
	case COL_STDV1:
		if (!ui.tableWidget->item(row,COL_STDV0)->text().isEmpty())
		{
			value1 = ui.tableWidget->item(row,COL_STDV1)->text().toFloat(&ok);
			if (ok)
			{
				value0 = ui.tableWidget->item(row,COL_STDV0)->text().toFloat(&ok);
				if (ok)
					ui.tableWidget->item(row,COL_STDVD)->setText(QString::number(value1-value0));		
			}
		}
		break;
	case COL_STDVD:
		if (!ui.tableWidget->item(row,COL_BALVC)->text().isEmpty())
		{
			value1 = ui.tableWidget->item(row,COL_STDVD)->text().toFloat(&ok);
			value0 = ui.tableWidget->item(row,COL_BALVC)->text().toFloat(&ok);
			ui.tableWidget->item(row,COL_STDERR)->setText(QString::number(value0/value1));
		}
		break;
	case COL_STDERR:
		notEmpty = 0;
		value0 = 0.0;
		startRow = getStartRow(row);
		endRow   = startRow + CHK_CNTS - 1;
		for (int i=startRow; i<=endRow; i++)
		{
			if (!ui.tableWidget->item(i,COL_STDERR)->text().isEmpty())
			{
				notEmpty++;
				value0 += ui.tableWidget->item(i, COL_STDERR)->text().toFloat(&ok);
			}
		}

		if (notEmpty > 0)
		{
			avr = value0/notEmpty;
			ui.tableWidget->item(startRow, COL_STDERR_AVR)->setText(QString::number(avr));

			if (notEmpty == CHK_CNTS)
			{
				//重复性 = SQRT(SUM(SQUARE(误差i-算术平均误差),0...N-1)/(N-1))x100%
				for (int i=startRow; i<=endRow; i++)
				{
					value0 = ui.tableWidget->item(i, COL_STDERR)->text().toFloat(&ok);
					rep += (value0-avr)*(value0-avr);
				}
				ui.tableWidget->item(startRow, COL_STDREP)->setText(QString::number(100*qSqrt(rep/(CHK_CNTS-1))));
			}
		}
		break;
	default:
		break;
	}
}

int StdMtrCoeCorrect::getStartRow(int row)
{
	return (row/CHK_CNTS)*CHK_CNTS;
}

void StdMtrCoeCorrect::setRegulatorOpening(int regNO, int opening)
{
	if (regNO == m_portsetinfo.regSmallNo) //小调节阀
	{
		ui.spinBoxOpeningSmall->setValue(opening);
		on_btnRegulateSmall_clicked();
	}
	else if (regNO == m_portsetinfo.regMid1No) //中一调节阀
	{
		ui.spinBoxOpeningMid1->setValue(opening);
		on_btnRegulateMid1_clicked();
	}
	else if (regNO == m_portsetinfo.regMid2No) //中二调节阀
	{
		ui.spinBoxOpeningMid2->setValue(opening);
		on_btnRegulateMid2_clicked();
	}
	else if (regNO == m_portsetinfo.regBigNo) //大调节阀
	{
		ui.spinBoxOpeningBig->setValue(opening);
		on_btnRegulateBig_clicked();
	}
}

//电动调节阀
void StdMtrCoeCorrect::on_btnRegulateSmall_clicked() //调节阀1-DN3
{
	m_smallOpening = ui.ThermoSmall->value();
	askControlRegulate(m_portsetinfo.regSmallNo, ui.spinBoxOpeningSmall->value());
	m_regSmallTimer->start(REGULATE_FRESH_TIME);
}

void StdMtrCoeCorrect::on_btnRegulateMid1_clicked() //调节阀2-DN10
{
	m_mid1Opening = ui.ThermoMid1->value();
	askControlRegulate(m_portsetinfo.regMid1No, ui.spinBoxOpeningMid1->value());
	m_regMid1Timer->start(REGULATE_FRESH_TIME);
}

void StdMtrCoeCorrect::on_btnRegulateMid2_clicked() //调节阀3-DN25
{
	m_mid2Opening = ui.ThermoMid2->value();
	askControlRegulate(m_portsetinfo.regMid2No, ui.spinBoxOpeningMid2->value());
	m_regMid2Timer->start(REGULATE_FRESH_TIME);
}

void StdMtrCoeCorrect::on_btnRegulateBig_clicked() //调节阀4-DN50
{
	m_bigOpening = ui.ThermoBig->value();
	askControlRegulate(m_portsetinfo.regBigNo, ui.spinBoxOpeningBig->value());
	m_regBigTimer->start(REGULATE_FRESH_TIME);
}

void StdMtrCoeCorrect::askControlRegulate(int regNO, int opening)
{
	if (regNO>=1 && regNO<=3)
	{
		m_controlObj->askControlRegulate(regNO, opening);
	}
	else
	{
		m_controlObj2->askControlRegulate(regNO-3, opening);
	}
}

void StdMtrCoeCorrect::on_lineEditOpeningSmall_textChanged(const QString & text)
{
	ui.ThermoSmall->setValue(text.toFloat());
}

void StdMtrCoeCorrect::on_lineEditOpeningMid1_textChanged(const QString & text)
{
	ui.ThermoMid1->setValue(text.toFloat());
}

void StdMtrCoeCorrect::on_lineEditOpeningMid2_textChanged(const QString & text)
{
	ui.ThermoMid2->setValue(text.toFloat());
}

void StdMtrCoeCorrect::on_lineEditOpeningBig_textChanged(const QString & text)
{
	ui.ThermoBig->setValue(text.toFloat());
}

void StdMtrCoeCorrect::slotFreshSmallRegOpening()
{
	if (ui.ThermoSmall->value() < ui.spinBoxOpeningSmall->value())
	{
		ui.lineEditOpeningSmall->setText(QString("%1").arg(m_smallOpening++));
	}
	else
	{
		ui.lineEditOpeningSmall->setText(QString("%1").arg(m_smallOpening--));
	}

	if (ui.lineEditOpeningSmall->text().toInt() == ui.spinBoxOpeningSmall->value())
	{
		m_regSmallTimer->stop();
	}
}

void StdMtrCoeCorrect::slotFreshMid1RegOpening()
{
	if (ui.ThermoMid1->value() < ui.spinBoxOpeningMid1->value())
	{
		ui.lineEditOpeningMid1->setText(QString("%1").arg(m_mid1Opening++));
	}
	else
	{
		ui.lineEditOpeningMid1->setText(QString("%1").arg(m_mid1Opening--));
	}

	if (ui.lineEditOpeningMid1->text().toInt() == ui.spinBoxOpeningMid1->value())
	{
		m_regMid1Timer->stop();
	}
}

void StdMtrCoeCorrect::slotFreshMid2RegOpening()
{
	if (ui.ThermoMid2->value() < ui.spinBoxOpeningMid2->value())
	{
		ui.lineEditOpeningMid2->setText(QString("%1").arg(m_mid2Opening++));
	}
	else
	{
		ui.lineEditOpeningMid2->setText(QString("%1").arg(m_mid2Opening--));
	}

	if (ui.lineEditOpeningMid2->text().toInt() == ui.spinBoxOpeningMid2->value())
	{
		m_regMid2Timer->stop();
	}
}

void StdMtrCoeCorrect::slotFreshBigRegOpening()
{
	if (ui.ThermoBig->value() < ui.spinBoxOpeningBig->value())
	{
		ui.lineEditOpeningBig->setText(QString("%1").arg(m_bigOpening++));
	}
	else
	{
		ui.lineEditOpeningBig->setText(QString("%1").arg(m_bigOpening--));
	}

	if (ui.lineEditOpeningBig->text().toInt() == ui.spinBoxOpeningBig->value())
	{
		m_regBigTimer->stop();
	}
}

void StdMtrCoeCorrect::on_rBtn_DN3_toggled()
{
	if (ui.rBtn_DN3->isChecked())
		m_curStdMeter = FLOW_RATE_SMALL;
}

void StdMtrCoeCorrect::on_rBtn_DN10_toggled()
{
	if (ui.rBtn_DN10->isChecked())
		m_curStdMeter = FLOW_RATE_MID_1;
}

void StdMtrCoeCorrect::on_rBtn_DN25_toggled()
{
	if (ui.rBtn_DN25->isChecked())
		m_curStdMeter = FLOW_RATE_MID_2;
}

void StdMtrCoeCorrect::on_rBtn_DN50_toggled()
{
	if (ui.rBtn_DN50->isChecked())
		m_curStdMeter = FLOW_RATE_BIG;
}

void StdMtrCoeCorrect::on_btnSave_clicked()
{
	if (m_curStdMeter != -1)
		saveMeterConfig((flow_rate_wdg)m_curStdMeter);
}

void StdMtrCoeCorrect::saveMeterConfig(flow_rate_wdg wdg)
{
	switch(m_curStdMeter)
	{
	case FLOW_RATE_BIG:
		m_stdMeterConfig->beginWriteArray("BigFlowK");
		break;
	case FLOW_RATE_MID_2:
		m_stdMeterConfig->beginWriteArray("Mid2FlowK");
		break;
	case FLOW_RATE_MID_1:
		m_stdMeterConfig->beginWriteArray("Mid1FlowK");
		break;
	case FLOW_RATE_SMALL:
		m_stdMeterConfig->beginWriteArray("SmallFlowK");
		break;
	default:
		break;
	}

	for (int i=0; i<FLOW_POINTS; i++)
	{
		m_stdMeterConfig->setArrayIndex(i);
		m_stdMeterConfig->setValue("flowPoint", ui.tableWidget->item(i*CHK_CNTS, COL_FLOW_POINT)->text());
		m_stdMeterConfig->setValue("KCoe", ui.tableWidget->item(i*CHK_CNTS, COL_STDERR_AVR)->text());
	}
	m_stdMeterConfig->endArray();
}