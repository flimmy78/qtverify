/***********************************************
**  文件名:     flowweight.cpp
**  功能:       流量检定(质量法)主界面
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/2/9
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2015/02 第一版
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

#include "flowweight.h"
#include "commondefine.h"
#include "algorithm.h"
#include "qtexdb.h"
#include "parasetdlg.h"
#include "readcomconfig.h"

FlowWeightDlg::FlowWeightDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"FlowWeightDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);
 	ui.btnNext->hide();   //隐藏"下一步"按钮

	//不同等级的热量表对应的标准误差,单位%
	m_gradeErr[1] = 1.00f;
	m_gradeErr[2] = 2.00f;
	m_gradeErr[3] = 3.00f;

	if (!getPortSetIni(&m_portsetinfo)) //获取下位机端口号配置信息
	{
		QMessageBox::warning(this, tr("Warning"), tr("Warning:get port set info failed!"));
	}

	m_readComConfig = new ReadComConfig(); //读串口设置接口（必须在initBalanceCom前调用）

	m_balanceObj = NULL;
	initBalanceCom();		//初始化天平串口

	m_tempObj = NULL;
	m_tempTimer = NULL;
	initTemperatureCom();	//初始化温度采集串口

	m_controlObj = NULL;
	initControlCom();		//初始化控制串口

	m_meterObj = NULL;      //热量表通讯
	m_recPtr = NULL;        //流量检测结果

	//计算流速用
	m_totalcount = 0;
	m_startWeight = 0.0;
	m_endWeight = 0.0;
	memset(m_deltaWeight, 0, sizeof(float)*FLOW_SAMPLE_NUM);
	m_flowRateTimer = new QTimer();
	connect(m_flowRateTimer, SIGNAL(timeout()), this, SLOT(slotFreshFlowRate()));
	m_flowRateTimer->start(TIMEOUT_FLOW_SAMPLE);

	//计算类接口
	m_chkAlg = new CAlgorithm();

	//映射关系；初始化阀门状态	
	initValveStatus();      

	m_exaustTimer = new QTimer(this); //排气定时器
	connect(m_exaustTimer, SIGNAL(timeout()), this, SLOT(slotExaustFinished()));

	m_inputStartValue = false; 
	m_inputEndValue = false;
	m_stopFlag = false; //停止检测标志（退出界面后，不再检查天平容量）

	m_tempCount = 1; //计算平均温度用的累加计数器
	m_nowOrder = 0;  //当前进行的检定序号

	m_nowParams = new Verify_Params_STR;
	memset(m_nowParams, 0, sizeof(Verify_Params_STR));
	m_continueVerify = true; //连续检定
	m_resetZero = false;     //初值回零
	m_autopick = false;      //自动采集
	m_flowPointNum = 0;      //流量点个数
	m_maxMeterNum = 0;       //某规格表最多支持的检表个数
	m_oldMaxMeterNum = 0;
	m_validMeterNum = 0;     //实际检表个数
	m_exaustSecond = 45;     //默认排气时间45秒
	m_manufac = 0;           //制造厂商 默认德鲁
	m_meterStartValue = NULL;
	m_meterEndValue = NULL;
	m_meterTemper = NULL;
	m_meterDensity = NULL;
	m_meterStdValue = NULL;
	m_meterError = NULL;
	m_balStartV = 0;
	m_balEndV = 0;
	m_timeStamp = "";
	m_nowDate = "";
	m_validDate = "";
	m_flowPoint = 0;          //流量(m3/h)

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
}

FlowWeightDlg::~FlowWeightDlg()
{
}

void FlowWeightDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^FlowWeightDlg::closeEvent";

	m_stopFlag = true;

	openWaterOutValve(); //退出时打开放水阀
	closeWaterPump();    //退出时关闭水泵

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

	if (m_tempTimer) //计时器
	{
		if (m_tempTimer->isActive())
		{
			m_tempTimer->stop();
		}
		delete m_tempTimer;
		m_tempTimer = NULL;
	}

	if (m_balanceObj)  //天平采集
	{
		delete m_balanceObj;
		m_balanceObj = NULL;

		m_balanceThread.exit();
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

	m_exaustTimer->stop();
}

//天平采集串口 上位机直接采集
void FlowWeightDlg::initBalanceCom()
{
	ComInfoStruct balanceStruct = m_readComConfig->ReadBalanceConfig();
	m_balanceObj = new BalanceComObject();
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

	//天平数值由上位机直接通过天平串口采集
	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const float &)), this, SLOT(slotFreshBalanceValue(const float &)));
}

/*
** 温度采集串口 上位机直接采集
** 周期请求
*/
void FlowWeightDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadTempConfig();
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer();
	connect(m_tempTimer, SIGNAL(timeout()), m_tempObj, SLOT(writeTemperatureComBuffer()));
	
	m_tempTimer->start(TIMEOUT_TEMPER); //周期请求温度
}

//控制板通讯串口
void FlowWeightDlg::initControlCom()
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
void FlowWeightDlg::initMeterCom()
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
		m_meterObj[i].setProtocolVersion(m_manufac); //设置表协议类型
		m_meterThread[i].start();
		m_meterObj[i].openMeterCom(&m_readComConfig->ReadMeterConfigByNum(QString("%1").arg(i+1)));
		
		connect(&m_meterObj[i], SIGNAL(readMeterNoIsOK(const QString&, const QString&)), this, SLOT(slotSetMeterNumber(const QString&, const QString&)));
		connect(&m_meterObj[i], SIGNAL(readMeterFlowIsOK(const QString&, const float&)), this, SLOT(slotSetMeterFlow(const QString&, const float&)));
	}
}

/*
** 端口号-阀门映射关系；初始化阀门状态（默认阀门初始状态全部为关闭,水泵初始状态为关闭）
** 需要改进得更加灵活
*/
void FlowWeightDlg::initValveStatus()
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

/*
** 函数功能：
	在界面刷新天平数值
	过滤突变数值
	防止天平溢出
*/
void FlowWeightDlg::slotFreshBalanceValue(const float& balValue)
{
	QString wht = QString::number(balValue, 'f', 3);
	ui.lcdBigBalance->display(wht);
	if (balValue > BALANCE_CAPACITY) //防止天平溢出 暂设天平容量为100kg
	{
		closeValve(m_portsetinfo.waterInNo); //关闭进水阀
		closeAllFlowPointValves(); //关闭所有流量点阀门
		openWaterOutValve(); //打开放水阀
		closeWaterPump(); //关闭水泵
	}
}

//在界面刷新入口温度和出口温度值
void FlowWeightDlg::slotFreshComTempValue(const QString& tempStr)
{
	ui.lcdInTemper->display(tempStr.left(DATA_WIDTH));   //入口温度 PV
	ui.lcdOutTemper->display(tempStr.right(DATA_WIDTH)); //出口温度 SV
}

/*
** 计算流速
*/
void FlowWeightDlg::slotFreshFlowRate()
{
// 	qDebug()<<"FlowWeightDlg::slotFreshFlowRate thread:"<<QThread::currentThreadId();
	if (m_totalcount > 4294967290) //防止m_totalcount溢出 32位无符号整数范围0~4294967295
	{
		m_totalcount = 0;
		m_startWeight = 0.0;
		m_endWeight = 0.0;
		memset(m_deltaWeight, 0, sizeof(float)*FLOW_SAMPLE_NUM);
	}
	if (m_totalcount == 0) //记录天平初始重量
	{
		m_startWeight = ui.lcdBigBalance->value();
		m_totalcount ++;
		return;
	}

	float flowValue = 0.0;
	float totalWeight = 0.0;
	m_endWeight = ui.lcdBigBalance->value();//取当前天平值, 作为当前运算的终值
	float delta_weight = m_endWeight - m_startWeight;
	m_deltaWeight[m_totalcount%FLOW_SAMPLE_NUM] = delta_weight;
// 	qWarning()<<"m_totalcount ="<<m_totalcount;
	for (int i=0; i<FLOW_SAMPLE_NUM; i++)
	{
		totalWeight += m_deltaWeight[i];
// 		qWarning()<<"totalWeight ="<<totalWeight<<", m_deltaWeight["<<i<<"] ="<<m_deltaWeight[i];
	}
	flowValue = 3.6*(totalWeight)*1000/(FLOW_SAMPLE_NUM*TIMEOUT_FLOW_SAMPLE);//总累积水量/总时间  (吨/小时, t/h, m3/h)
//	flowValue = (totalWeight)*1000/(FLOW_SAMPLE_NUM*TIMEOUT_FLOW_SAMPLE);// kg/s
// 	qDebug()<<"flowValue ="<<flowValue;
	if (m_totalcount >= FLOW_SAMPLE_NUM)
	{
		ui.lcdFlowRate->display(QString::number(flowValue, 'f', 3)); //在ui.lcdFlowRate中显示流速
	}
	m_totalcount ++;//计数器累加
	m_startWeight = m_endWeight;//将当前值保存, 作为下次运算的初值
}

//检测串口、端口设置是否正确
int FlowWeightDlg::isComAndPortNormal()
{
	return true;
}

//获取当前检定参数
int FlowWeightDlg::readNowParaConfig()
{
	if (NULL == m_paraSetReader)
	{
		return false;
	}

	m_nowParams = m_paraSetReader->getParams();
	m_continueVerify = m_nowParams->bo_converify; //连续检定
	m_resetZero = m_nowParams->bo_resetzero; //初值回零
	m_autopick = m_nowParams->bo_autopick;   //自动采集
	m_flowPointNum = m_nowParams->total_fp;  //有效流量点的个数 
	m_exaustSecond = m_nowParams->ex_time;   //排气时间
	m_standard = m_nowParams->m_stand;       //表规格
	m_model = m_nowParams->m_model;   //表型号
	m_meterType = m_nowParams->m_type;//表类型
	m_maxMeterNum = m_nowParams->m_maxMeters;//不同表规格对应的最大检表数量
	m_manufac = m_nowParams->m_manufac; //制造厂商

	initTableWidget();
	showNowKeyParaConfig();
	initMeterCom();

	return true;
}

//初始化表格控件
void FlowWeightDlg::initTableWidget()
{
	if (m_maxMeterNum <= 0)
	{
		return;
	}
	ui.tableWidget->setRowCount(m_maxMeterNum); //设置表格行数

	QSignalMapper *m_signalMapper1 = new QSignalMapper();
	QSignalMapper *m_signalMapper2 = new QSignalMapper();
	QSignalMapper *m_signalMapper3 = new QSignalMapper();
	QSignalMapper *m_signalMapper4 = new QSignalMapper();

	QStringList vLabels;
	for (int i=0; i< m_maxMeterNum; i++)
	{
		vLabels<<QString(QObject::tr("meterPosNo%1").arg(i+1));

		ui.tableWidget->setItem(i, COLUMN_METER_NUMBER, new QTableWidgetItem(QString()));
		ui.tableWidget->setItem(i, COLUMN_METER_START, new QTableWidgetItem(QString()));
		ui.tableWidget->setItem(i, COLUMN_METER_END, new QTableWidgetItem(QString()));

		QPushButton *btnModNo = new QPushButton(tr("ModifyNO"));
		ui.tableWidget->setCellWidget(i, COLUMN_MODIFY_METERNO, btnModNo);
		m_signalMapper1->setMapping(btnModNo, i);
		connect(btnModNo, SIGNAL(clicked()), m_signalMapper1, SLOT(map()));

		QPushButton *btnAdjErr = new QPushButton(tr("AdjustErr"));
		ui.tableWidget->setCellWidget(i, COLUMN_ADJUST_ERROR, btnAdjErr);
		m_signalMapper2->setMapping(btnAdjErr, i);
		connect(btnAdjErr, SIGNAL(clicked()), m_signalMapper2, SLOT(map()));

		QPushButton *btnReadMeter = new QPushButton(tr("ReadMeter"));
		ui.tableWidget->setCellWidget(i, COLUMN_READ_METER, btnReadMeter);
		m_signalMapper3->setMapping(btnReadMeter, i);
		connect(btnReadMeter, SIGNAL(clicked()), m_signalMapper3, SLOT(map()));

		QPushButton *btnVerifySt = new QPushButton(tr("VerifySt"));
		ui.tableWidget->setCellWidget(i, COLUMN_VERIFY_STATUS, btnVerifySt);
		m_signalMapper4->setMapping(btnVerifySt, i);
		connect(btnVerifySt, SIGNAL(clicked()), m_signalMapper4, SLOT(map()));

	}
	connect(m_signalMapper1, SIGNAL(mapped(const int &)),this, SLOT(slotModifyMeterNO(const int &)));
	connect(m_signalMapper2, SIGNAL(mapped(const int &)),this, SLOT(slotAdjustError(const int &)));
	connect(m_signalMapper3, SIGNAL(mapped(const int &)),this, SLOT(slotReadMeter(const int &)));
	connect(m_signalMapper4, SIGNAL(mapped(const int &)),this, SLOT(slotVerifyStatus(const int &)));

	ui.tableWidget->setVerticalHeaderLabels(vLabels);
// 	ui.tableWidget->resizeColumnsToContents();
}

//显示当前关键参数设置信息
void FlowWeightDlg::showNowKeyParaConfig()
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
int FlowWeightDlg::isDataCollectNormal()
{
	return true;
}

//打开所有阀门和水泵
int FlowWeightDlg::openAllValveAndPump()
{
	//打开阀门
	openValve(m_portsetinfo.waterOutNo);
	openValve(m_portsetinfo.bigNo);
	openValve(m_portsetinfo.middle1No);
	openValve(m_portsetinfo.middle2No);
	openValve(m_portsetinfo.smallNo);
	openValve(m_portsetinfo.waterInNo);

	//打开水泵
	openWaterPump();

	return true;
}

/*
** 排气定时器响应函数
*/
void FlowWeightDlg::slotExaustFinished()
{
	m_exaustSecond --;
	ui.labelHintProcess->setText(tr("Exhaust countdown: %1 second").arg(m_exaustSecond));
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

	if (!prepareInitBalance())//准备天平初始重量
	{
		return;
	}

	if (setAllMeterVerifyStatus()) //设置检定状态成功
	{
		startVerify();
	}
}

/*
** 排气结束后、开始检定前，准备天平,达到要求的初始重量
*/
int FlowWeightDlg::prepareInitBalance()
{
	ui.labelHintPoint->setText(tr("prepare balance ...")); //准备天平
	int ret = 0;
	//判断天平重量,如果小于要求的初始重量(5kg)，则关闭放水阀，打开大流量阀
	if (ui.lcdBigBalance->value() < BALANCE_INIT_VALUE)
	{
		if (!closeWaterOutValve()) 
		{
			qWarning()<<"关闭放水阀失败";
		}
		if (!openValve(m_portsetinfo.bigNo))
		{
			qWarning()<<"打开大流量阀失败";
		}
		//判断并等待天平重量，大于初始重量(5kg)
		if (isBalanceValueBigger(BALANCE_INIT_VALUE, true))
		{
			if (!closeValve(m_portsetinfo.bigNo))
			{
				qWarning()<<"关闭大流量阀失败";
			}
			ret = 1;
		}
	}
	else
	{
		closeWaterOutValve(); //关闭放水阀
		ret = 1;
	}

	return ret;
}

/*
** 读取热表
*/
int FlowWeightDlg::readAllMeter()
{
	on_btnAllReadMeter_clicked();
	return true;
}

//设置所有热量表进入检定状态
int FlowWeightDlg::setAllMeterVerifyStatus()
{
	on_btnAllVerifyStatus_clicked();
	return true;
}

//关闭所有流量点阀门
int FlowWeightDlg::closeAllFlowPointValves()
{
	closeValve(m_portsetinfo.bigNo);
	closeValve(m_portsetinfo.middle1No);
	closeValve(m_portsetinfo.middle2No);
	closeValve(m_portsetinfo.smallNo);

	return true;
}

//关闭放水阀门
int FlowWeightDlg::closeWaterOutValve()
{
	closeValve(m_portsetinfo.waterOutNo);
	return true;
}

//打开放水阀门
int FlowWeightDlg::openWaterOutValve()
{
	openValve(m_portsetinfo.waterOutNo);
	return true;
}

/*
** 响应处理天平质量的变化
** 输入参数：
	targetV: 目标重量
	flg: true-要求大于目标重量(默认)；false-要求小于目标重量
*/
int FlowWeightDlg::isBalanceValueBigger(float targetV, bool flg)
{
	int ret = 0;
	if (flg) //要求大于目标重量
	{
		while (!m_stopFlag && (ui.lcdBigBalance->value() < targetV))
		{
			qDebug()<<"天平重量 ="<<ui.lcdBigBalance->value()<<", 小于要求的重量 "<<targetV;
			QTest::qWait(1000);
		}
		ret = !m_stopFlag && (ui.lcdBigBalance->value() >= targetV);
	}
	else //要求小于目标重量
	{
		while (!m_stopFlag && (ui.lcdBigBalance->value() > targetV))
		{
			qDebug()<<"天平重量 ="<<ui.lcdBigBalance->value()<<", 大于要求的重量 "<<targetV;
			QTest::qWait(1000);
		}
		ret = !m_stopFlag && (ui.lcdBigBalance->value() <= targetV);
	}

	return ret;
}

int FlowWeightDlg::judgeBalanceAndCalcAvgTemper(float targetV)
{
	int second = 0;
	float nowFlow = m_paraSetReader->getFpBySeq(m_nowOrder).fp_verify;
	while (!m_stopFlag && (ui.lcdBigBalance->value() < targetV))
	{
		qDebug()<<"天平重量 ="<<ui.lcdBigBalance->value()<<", 小于要求的重量 "<<targetV;
		m_pipeInTemper += ui.lcdInTemper->value();
		m_pipeOutTemper += ui.lcdOutTemper->value();
		m_tempCount++;

		second = 3.6*(targetV - ui.lcdBigBalance->value())/nowFlow;
		ui.labelHintPoint->setText(tr("NO. %1 flow point: %2 m3/h").arg(m_nowOrder).arg(nowFlow));
		ui.labelHintProcess->setText(tr("Verifying...\nPlease wait for about %1 second").arg(second));
		QTest::qWait(1000);
	}

	m_pipeInTemper = m_pipeInTemper/m_tempCount;   //入口平均温度
	m_pipeOutTemper = m_pipeOutTemper/m_tempCount; //出口平均温度
	ui.labelHintPoint->setText(tr("NO. %1 flow point: %2 m3/h").arg(m_nowOrder).arg(nowFlow));
	ui.labelHintProcess->setText(tr("Verify Finished!"));
	if (m_nowOrder == m_flowPointNum)
	{
		ui.labelHintProcess->setText(tr("All flow points has verified!"));
		ui.btnNext->hide();
	}
	int ret = !m_stopFlag && (ui.lcdBigBalance->value() >= targetV);
	return ret;
}

//清空表格，第一列除外("表号"列)
void FlowWeightDlg::clearTableContents()
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
void FlowWeightDlg::on_btnStart_clicked()
{
	if (!on_btnExhaust_clicked())
	{
		return;
	}

	m_stopFlag = false;
	clearTableContents();
	m_validMeterNum = 0;

	m_exaustSecond = m_nowParams->ex_time;
	m_exaustTimer->start(1000);//开始排气倒计时
	ui.labelHintProcess->setText(tr("Exhaust countdown: %1 second").arg(m_exaustSecond));
	ui.labelHintPoint->clear();
	qDebug()<<"排气倒计时:"<<m_exaustSecond<<"秒";

	if (m_autopick) //自动读表
	{
		readAllMeter();
	}
	else //手动读表
	{
		ui.labelHintPoint->setText(tr("Please input meter number!"));
	}

	return;
}

/*
** 点击"排气按钮"，开始检定
*/
int FlowWeightDlg::on_btnExhaust_clicked()
{
	if (!isDataCollectNormal())
	{
		qWarning()<<"数据采集错误，请检查";
		QMessageBox::warning(this, tr("Warning"), tr("data acquisition error, please check!"));
		return false;
	}

	if (!openAllValveAndPump())
	{
		qWarning()<<"打开所有阀门和水泵 失败!";
		QMessageBox::warning(this, tr("Warning"), tr("exhaust air failed!"));
		return false;
	}

	return true;
}

//点击"下一步"按钮
void FlowWeightDlg::on_btnNext_clicked()
{
	if (m_nowOrder >= m_flowPointNum)
	{
		QMessageBox::warning(this, tr("Warning"), tr("All flow points has verified!"));
		return;
	}

	clearTableContents();

	m_nowOrder ++;
	if (m_nowOrder == m_flowPointNum)
	{
		ui.btnNext->hide();
	}
	prepareVerifyFlowPoint(m_nowOrder); // 开始进行下一次流量点的检定

}

//点击"终止检测"按钮
void FlowWeightDlg::on_btnStop_clicked()
{
	int button = QMessageBox::question(this, tr("Question"), tr("Stop Really ?"), \
		QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape);
	if (button == QMessageBox::No)
	{
		return;
	}

	m_stopFlag = true; //不再检查天平质量
	m_inputStartValue = false;
	m_inputEndValue = false;
	
	m_exaustTimer->stop();//停止排气定时器

	closeValve(m_portsetinfo.waterInNo);//关闭进水阀
	closeAllFlowPointValves();//关闭所有流量点阀门
	//openWaterOutValve();//打开放水阀
	closeWaterPump();//关闭水泵

	ui.labelHintProcess->setText(tr("Verify has Stoped!"));
}

void FlowWeightDlg::on_btnExit_clicked()
{
	this->close();
}


//开始检定
void FlowWeightDlg::startVerify()
{
	m_nowOrder = 1;

	//判断实际检表的个数(根据获取到的表号个数)
	if (getValidMeterNum() <= 0)
	{
		QMessageBox::warning(this, tr("Warning"), tr("please input meter number, then click \"start\" button!"));//请输入表号！然后点击'开始'按钮
		ui.btnStart->show();
		return;
	}

	if (m_recPtr != NULL)
	{
		delete []m_recPtr;
		m_recPtr = NULL;
	}
	m_recPtr = new Flow_Verify_Record_STR[m_validMeterNum];
	memset(m_recPtr, 0, sizeof(Flow_Verify_Record_STR)*m_validMeterNum);

	m_flowPoint = m_paraSetReader->getFpBySeq(1).fp_verify;//第一个流量点
	for (int m=0; m<m_validMeterNum; m++) //
	{
		ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_FLOW_POINT, new QTableWidgetItem(QString::number(m_flowPoint, 'f', 2)));//流量点
	}

	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //记录时间戳
	m_nowDate = QDateTime::currentDateTime().toString("yyyy-MM-dd"); //当前日期'2014-08-07'
	m_validDate = QDateTime::currentDateTime().addYears(VALID_YEAR).addDays(-1).toString("yyyy-MM-dd"); //有效期

	m_startValueFlag = true; //默认是初值

	m_meterStartValue = new float[m_validMeterNum]; //表初值 
	memset(m_meterStartValue, 0, sizeof(float)*m_validMeterNum);

	m_meterEndValue = new float[m_validMeterNum];   //表终值
	memset(m_meterEndValue, 0, sizeof(float)*m_validMeterNum);

	m_meterTemper = new float[m_validMeterNum];     //表温度
	memset(m_meterTemper, 0, sizeof(float)*m_validMeterNum);

	m_meterDensity = new float[m_validMeterNum];    //表密度
	memset(m_meterDensity, 0, sizeof(float)*m_validMeterNum);

	m_meterStdValue = new float[m_validMeterNum];   //被检表的标准值
	memset(m_meterStdValue, 0, sizeof(float)*m_validMeterNum);

	m_meterError = new float[m_validMeterNum];      //被检表的误差
	memset(m_meterError, 0, sizeof(float)*m_validMeterNum);
	
	if (m_continueVerify) //连续检定
	{
		if (!judgeBalanceCapacity()) //判断天平容量是否能够满足检定用量
		{
			openWaterOutValve();
			while (!judgeBalanceCapacity())
			{ 
				QTest::qWait(1000);
			}
			closeWaterOutValve(); //若满足检定用量，则关闭放水阀
			QTest::qWait(3000); //等待3秒钟(等待水流稳定)
		}
	}

	//////////////////////////////
	if (m_autopick) //自动采集
	{
		for (int j=0; j<m_flowPointNum; j++)
		{
			m_nowOrder = j+1;
			prepareVerifyFlowPoint(j+1);
		}
	}
	else //手动采集
	{
		if (prepareVerifyFlowPoint(1)) //第一个流量点检定
		{
			ui.btnNext->show();
			ui.btnNext->setFocus();
		}
	}
	//检测结束
}

//获取有效检表个数,并生成映射关系（被检表下标-表位号）
int FlowWeightDlg::getValidMeterNum()
{
	bool ok;
	for (int i=0; i<m_maxMeterNum; i++)
	{
		if (NULL == ui.tableWidget->item(i, COLUMN_METER_NUMBER)) //"表号"单元格为空
		{
			continue;
		}
		ui.tableWidget->item(i, COLUMN_METER_NUMBER)->text().toInt(&ok, 10);
		if (!ok) //表号转换失败(非数字)
		{
			continue;
		}

		m_meterPosMap[m_validMeterNum] = i+1; //表位号从1开始
		m_validMeterNum++;
	}
	return m_validMeterNum;
}

/*
** 判断天平容量是否满足检定用量
** 连续检定时：满足总检定用量
*/
bool FlowWeightDlg::judgeBalanceCapacity()
{
	bool ret = false;
	float totalQuantity = 0;
	int num = m_paraSetReader->getParams()->total_fp; //有效流量点的个数
	for (int i=0; i<num; i++)
	{
		totalQuantity += m_paraSetReader->getParams()->fp_info[i].fp_quantity;
	}
	ret = (ui.lcdBigBalance->value() + totalQuantity) < (BALANCE_CAPACITY-3); //假设天平容量为100kg
	return ret;
}

/*
** 判断天平容量是否满足检定用量
** 不连续检定时：满足单次检定用量
*/
int FlowWeightDlg::judgeBalanceCapacitySingle(int order)
{
	return true;
}

/*
** 准备单个流量点的检定，进行必要的检查
** 注意：order从1开始
*/
int FlowWeightDlg::prepareVerifyFlowPoint(int order)
{
	if (order < 1 || m_stopFlag)
	{
		return false;
	}
	if (m_validMeterNum <= 0)
	{
		QMessageBox::warning(this, tr("Warning"), tr("please input meter number"));//请输入表号！
		return false;
	}

	if (!m_continueVerify) //非连续检定，每次检定开始之前都要判断天平容量
	{
		if (!judgeBalanceCapacitySingle(order)) //天平容量不满足本次检定用量
		{
			openWaterOutValve(); //打开放水阀，天平放水

			while (!judgeBalanceCapacitySingle(order)) //等待天平放水，直至满足本次检定用量
			{ 
				QTest::qWait(1000);
			}
			closeWaterOutValve(); //若满足检定用量，则关闭放水阀
			QTest::qWait(3000);   //等待3秒钟，等待水流稳定
		}
	}

	int i=0;
	if (m_resetZero) //初值回零
	{
		if (m_autopick || order==1 ) //自动采集或者是第一个检定点,需要等待热表初值回零
		{
			ui.labelHintPoint->setText(tr("Reset Zero"));
			while (i < RESET_ZERO_TIME && !m_stopFlag) //等待被检表初值回零
			{
				ui.labelHintProcess->setText(tr("please wait %1 seconds for reset zero").arg(RESET_ZERO_TIME-i));
				i++;
				QTest::qWait(1000); 
			}
		}
		memset(m_meterStartValue, 0, sizeof(float)*m_validMeterNum);
		for (int i=0; i<m_validMeterNum; i++)
		{
			ui.tableWidget->item(m_meterPosMap[i]-1, COLUMN_METER_START)->setText(QString("%1").arg(m_meterStartValue[i]));
		}
	}
	else //初值不回零
	{
		if (order >= 2) //第二个检定点之后
		{
			if (m_autopick)
			{
				QTest::qWait(2000); //等2秒，供操作人员看上一次的检定结果
				clearTableContents();
			}
			makeStartValueByLastEndValue(); //上一次的终值作为本次的初值
		}
		else //第一个检定点
		{
			if (!getMeterStartValue()) //获取表初值
			{
				return false;
			}
		}
	}

	startVerifyFlowPoint(order);
	return true;
}

//进行单个流量点的检定
int FlowWeightDlg::startVerifyFlowPoint(int order)
{
	if (m_stopFlag)
	{
		return false;
	}
	m_balStartV = ui.lcdBigBalance->value(); //记录天平初值
	m_pipeInTemper = ui.lcdInTemper->value();
	m_pipeOutTemper = ui.lcdOutTemper->value();
	m_tempCount = 1;

	m_flowPoint = m_paraSetReader->getFpBySeq(order).fp_verify;//order对应的流量点
	int portNo = m_paraSetReader->getFpBySeq(order).fp_valve;  //order对应的阀门端口号
	float verifyQuantity = m_paraSetReader->getFpBySeq(order).fp_quantity; //第order次检定对应的检定量
	float frequence = m_paraSetReader->getFpBySeq(order).fp_freq; //order对应的频率
	m_controlObj->askSetDriverFreq(frequence);
	if (openValve(portNo)) //打开阀门，开始跑流量
	{
		if (judgeBalanceAndCalcAvgTemper(m_balStartV + verifyQuantity)) //跑完检定量并计算此过程的平均温度
		{
			closeValve(portNo); //关闭order对应的阀门
			QTest::qWait(3000); //等待3秒钟，让天平数值稳定
			m_balEndV = ui.lcdBigBalance->value(); //记录天平终值

			for (int m=0; m<m_validMeterNum; m++) //
			{
				m_meterTemper[m] = m_chkAlg->getMeterTempByPos(m_pipeInTemper, m_pipeOutTemper, m_meterPosMap[m]);//计算每个被检表的温度
				m_meterDensity[m] = m_chkAlg->getDensityByQuery(m_meterTemper[m]);//计算每个被检表的密度
				m_meterStdValue[m] = m_chkAlg->getStdVolByPos((m_balEndV-m_balStartV), m_pipeInTemper, m_pipeOutTemper, m_meterPosMap[m]); //计算每个被检表的体积标准值

				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_FLOW_POINT, new QTableWidgetItem(QString::number(m_flowPoint, 'f', 2)));//流量点
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_BAL_START, new QTableWidgetItem(QString::number(m_balStartV, 'f', 3)));//天平初值
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_BAL_END, new QTableWidgetItem(QString::number(m_balEndV, 'f', 3)));    //天平终值
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_TEMPER, new QTableWidgetItem(QString::number(m_meterTemper[m], 'f', 2)));  //温度
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_DENSITY, new QTableWidgetItem(QString::number(m_meterDensity[m], 'f', 3)));//密度
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_STD_VALUE, new QTableWidgetItem(QString::number(m_meterStdValue[m], 'f', 3)));//标准值
			}

			if (!getMeterEndValue()) //获取表终值
			{
				return false;
			}

			if (m_autopick && !m_stopFlag) //自动采集
			{
				calcAllMeterError();
				saveAllVerifyRecords();
			}
		}
	}
	return true;
}

/*
** 计算所有被检表的误差
*/
int FlowWeightDlg::calcAllMeterError()
{
	for (int i=0; i<m_validMeterNum; i++)
	{
		calcMeterError(i);
	}
	return true; 
}

/*
** 计算某个被检表的误差
** 输入参数：
**     idx:被检表数组的索引
*/
int FlowWeightDlg::calcMeterError(int idx)
{
	m_meterError[idx] = 100*(m_meterEndValue[idx] - m_meterStartValue[idx] - m_meterStdValue[idx])/m_meterStdValue[idx];//计算某个表的误差
	ui.tableWidget->setItem(m_meterPosMap[idx]-1, COLUMN_ERROR, new QTableWidgetItem(QString::number(m_meterError[idx], 'f', 4))); //误差
	if (fabs(m_meterError[idx]) > m_gradeErr[2])
	{
		ui.tableWidget->item(m_meterPosMap[idx]-1, COLUMN_ERROR)->setForeground(QBrush(Qt::red));
	}
	QString meterNoPrefix = getNumPrefixOfManufac(m_nowParams->m_manufac);
	QString meterNoStr = meterNoPrefix + QString("%1").arg(ui.tableWidget->item(m_meterPosMap[idx]-1, 0)->text(), 8, '0');

	strncpy_s(m_recPtr[idx].timestamp, m_timeStamp.toAscii(), TIMESTAMP_LEN);
	m_recPtr[idx].flowPoint = m_flowPoint;
	strcpy_s(m_recPtr[idx].meterNo, meterNoStr.toAscii());
	m_recPtr[idx].flowPointIdx = m_nowOrder; //
	m_recPtr[idx].methodFlag = WEIGHT_METHOD; //质量法
	m_recPtr[idx].meterValue0 = m_meterStartValue[idx];
	m_recPtr[idx].meterValue1 = m_meterEndValue[idx];
	m_recPtr[idx].balWeight0 = m_balStartV;
	m_recPtr[idx].balWeight1 = m_balEndV;
	m_recPtr[idx].pipeTemper = m_meterTemper[idx]; 
	m_recPtr[idx].density = m_meterDensity[idx];
	m_recPtr[idx].stdValue = m_meterStdValue[idx];
	m_recPtr[idx].dispError = m_meterError[idx];
	m_recPtr[idx].grade = m_nowParams->m_grade;
	m_recPtr[idx].stdError = m_gradeErr[m_nowParams->m_grade]; //二级表 标准误差
	m_recPtr[idx].result = (fabs(m_recPtr[idx].dispError) <= fabs(m_recPtr[idx].stdError)) ? 1 : 0;
	m_recPtr[idx].meterPosNo = m_meterPosMap[idx];
	m_recPtr[idx].standard = m_standard;
	m_recPtr[idx].model = m_model;
	m_recPtr[idx].meterType = m_meterType; //表类型
	m_recPtr[idx].manufactDept = m_nowParams->m_manufac;
	m_recPtr[idx].verifyDept = m_nowParams->m_vcomp;
	m_recPtr[idx].verifyPerson = m_nowParams->m_vperson;
	strncpy_s(m_recPtr[idx].verifyDate, m_nowDate.toAscii(), DATE_LEN);
	strncpy_s(m_recPtr[idx].validDate, m_validDate.toAscii(), DATE_LEN);
	m_recPtr[idx].airPress = m_nowParams->m_airpress.toFloat();
	m_recPtr[idx].envTemper = m_nowParams->m_temper.toFloat();
	m_recPtr[idx].envHumidity = m_nowParams->m_humidity.toFloat();

	return true; 
}

//打开阀门
int FlowWeightDlg::openValve(UINT8 portno)
{
	m_controlObj->askControlRelay(portno, VALVE_OPEN);
	if (m_portsetinfo.version==OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(portno, VALVE_OPEN);
	}
	return true;
}

//关闭阀门
int FlowWeightDlg::closeValve(UINT8 portno)
{
	m_controlObj->askControlRelay(portno, VALVE_CLOSE);
	if (m_portsetinfo.version==OLD_CTRL_VERSION) //老控制板 无反馈
	{
		slotSetValveBtnStatus(portno, VALVE_CLOSE);
	}
	return true;
}

//操作阀门：打开或者关闭
int FlowWeightDlg::operateValve(UINT8 portno)
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
int FlowWeightDlg::openWaterPump()
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
int FlowWeightDlg::closeWaterPump()
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
int FlowWeightDlg::operateWaterPump()
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
void FlowWeightDlg::slotSetValveBtnStatus(const UINT8 &portno, const bool &status)
{
	m_valveStatus[portno] = status;
	setValveBtnBackColor(m_valveBtn[portno], m_valveStatus[portno]);
}

//响应调节阀调节成功
void FlowWeightDlg::slotSetRegulateOk()
{
// 	setRegBtnBackColor(m_regBtn[m_nowRegIdx], true);
}


//自动读取表号成功 显示表号
void FlowWeightDlg::slotSetMeterNumber(const QString& comName, const QString& meterNo)
{
	int meterPos = m_readComConfig->getMeterPosByComName(comName);
	if (meterPos < 1)
	{
		return;
	}
	ui.tableWidget->setItem(meterPos-1, COLUMN_METER_NUMBER, new QTableWidgetItem(meterNo.right(8))); //表号
}

/*
** 自动读取表流量成功 显示表流量
*/
void FlowWeightDlg::slotSetMeterFlow(const QString& comName, const float& flow)
{
	int meterPos = m_readComConfig->getMeterPosByComName(comName);
	if (meterPos < 1)
	{
		return;
	}
	int idx = isMeterPosValid(meterPos);
	if (m_startValueFlag) //初值
	{
		ui.tableWidget->setItem(meterPos - 1, COLUMN_METER_START, new QTableWidgetItem(QString::number(flow)));
		if (idx>=0 && m_meterStartValue!=NULL)
		{
			m_meterStartValue[idx] = flow;
		}
	}
	else //终值
	{
		ui.tableWidget->setItem(meterPos - 1, COLUMN_METER_END, new QTableWidgetItem(QString::number(flow)));
		if (idx>=0 && m_meterEndValue!=NULL)
		{
			m_meterEndValue[idx] = flow;
		}
	}
}

//设置阀门按钮背景色
void FlowWeightDlg::setValveBtnBackColor(QToolButton *btn, bool status)
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
void FlowWeightDlg::setRegBtnBackColor(QPushButton *btn, bool status)
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
void FlowWeightDlg::on_btnParaSet_clicked()
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
void FlowWeightDlg::on_btnWaterIn_clicked() //进水阀
{
	m_nowPortNo = m_portsetinfo.waterInNo;
	operateValve(m_nowPortNo);
}

void FlowWeightDlg::on_btnWaterOut_clicked() //出水阀
{
	m_nowPortNo = m_portsetinfo.waterOutNo;
	operateValve(m_nowPortNo);
}

void FlowWeightDlg::on_btnValveBig_clicked() //大流量阀
{
	m_nowPortNo = m_portsetinfo.bigNo;
	operateValve(m_nowPortNo);
}

void FlowWeightDlg::on_btnValveMiddle1_clicked() //中流一阀
{
	m_nowPortNo = m_portsetinfo.middle1No;
	operateValve(m_nowPortNo);
}

void FlowWeightDlg::on_btnValveMiddle2_clicked() //中流二阀
{
	m_nowPortNo = m_portsetinfo.middle2No;
	operateValve(m_nowPortNo);
}

void FlowWeightDlg::on_btnValveSmall_clicked() //小流量阀
{
	m_nowPortNo = m_portsetinfo.smallNo;
	operateValve(m_nowPortNo);
}

/*
** 控制水泵开关
*/
void FlowWeightDlg::on_btnWaterPump_clicked()
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
void FlowWeightDlg::on_btnSetFreq_clicked()
{
	m_controlObj->askSetDriverFreq(ui.spinBoxFreq->value());
}

//获取表初值
int FlowWeightDlg::getMeterStartValue()
{
	if (m_autopick) //自动采集
	{
		m_startValueFlag = true;
		readAllMeter();
		QTest::qWait(2000); //等待串口返回数据
		return true;
	}
	else //手动输入
	{
		m_inputStartValue = true; //允许输入初值
		QMessageBox::information(this, tr("Hint"), tr("please input init value of heat meter"));//请输入热量表初值！
		ui.tableWidget->setCurrentCell(m_meterPosMap[0]-1, COLUMN_METER_START); //定位到第一个需要输入初值的地方
		return false;
	}
}

//上一次的终值作为本次的初值
void FlowWeightDlg::makeStartValueByLastEndValue()
{
	float flow = m_paraSetReader->getFpBySeq(m_nowOrder).fp_verify;
	for (int i=0; i<m_validMeterNum; i++)
	{
		m_meterStartValue[i] = m_meterEndValue[i];
		ui.tableWidget->item(m_meterPosMap[i]-1, COLUMN_METER_START)->setText(QString("%1").arg(m_meterStartValue[i]));
 		ui.tableWidget->item(m_meterPosMap[i]-1, COLUMN_FLOW_POINT)->setText(QString("%1").arg(flow));
	}
}

//获取表终值
int FlowWeightDlg::getMeterEndValue()
{
	if (m_stopFlag)
	{
		return false;
	}

	if (m_autopick) //自动采集
	{
		m_startValueFlag = false;
		readAllMeter();
		QTest::qWait(2000); //等待串口返回数据
		return true;
	}
	else //手动输入
	{
		m_inputEndValue = true; //允许输入终值
		QMessageBox::information(this, tr("Hint"), tr("please input end value of heat meter"));//请输入热量表终值！
		ui.tableWidget->setCurrentCell(m_meterPosMap[0]-1, COLUMN_METER_END); //定位到第一个需要输入终值的地方
		return false;
	}
}

/*
** 响应处理用户输入完表初值、表终值
   输入参数：
      row：行数，从0开始
	  column：列数，从0开始
*/
void FlowWeightDlg::on_tableWidget_cellChanged(int row, int column)
{
	if (m_autopick) //自动采集
	{
		return;
	}

	if (NULL == ui.tableWidget->item(row,  column))
	{
		return;
	}

	int meterPos = row + 1; //表位号
	int idx = -1;
	idx = isMeterPosValid(meterPos);
	if (idx < 0)
	{
		return;
	}
	bool ok;
	if (column==COLUMN_METER_START && m_inputStartValue) //表初值列 且 允许输入初值
	{
		m_meterStartValue[idx] = ui.tableWidget->item(row, column)->text().toFloat(&ok);
		if (!ok)
		{
			QMessageBox::warning(this, tr("Warning"), tr("Error: please input digits"));//输入错误！请输入数字
			return;
		}

		if (meterPos == m_meterPosMap[m_validMeterNum-1]) //输入最后一个表初值
		{
			m_inputStartValue = false;
			startVerifyFlowPoint(m_nowOrder);
		}
		else //不是最后一个表初值,自动定位到下一个
		{
			ui.tableWidget->setCurrentCell(m_meterPosMap[idx+1]-1, column);
		}
	}

	if (column==COLUMN_METER_END && m_inputEndValue) //表终值列 且 允许输入终值
	{
		m_meterEndValue[idx] = ui.tableWidget->item(row, column)->text().toFloat(&ok);
		if (!ok)
		{
			QMessageBox::warning(this, tr("Warning"), tr("Error: please input digits"));//输入错误！请输入数字
			return;
		}
		calcMeterError(idx);

		if (meterPos == m_meterPosMap[m_validMeterNum-1]) //输入最后一个表终值
		{
			m_inputEndValue = false;
			saveAllVerifyRecords();

			if (m_autopick) //自动采集
			{
				ui.btnNext->hide();
			}
			else if ( !m_autopick && (m_nowOrder != m_flowPointNum) )//手动采集并且不是最后一个检定点 
			{
				ui.btnNext->show();
			}
		}
		else //不是最后一个表终值,自动定位到下一个
		{
			ui.tableWidget->setCurrentCell(m_meterPosMap[idx+1]-1, column);
		}
	}
}

/*
** 判断表位号是否有效(该表位是否需要检表)
   输入:meterPos(表位号)，从1开始
   返回:被检表下标，从0开始
*/
int FlowWeightDlg::isMeterPosValid(int meterPos)
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
** 保存所有被检表的检定记录
*/
int FlowWeightDlg::saveAllVerifyRecords()
{
 	insertFlowVerifyRec(m_recPtr, m_validMeterNum);
	return true;
}

//请求读表（所有表、广播地址读表）
void FlowWeightDlg::on_btnAllReadMeter_clicked()
{
	for (int j=0; j<m_maxMeterNum; j++)
	{
		m_meterObj[j].askReadMeter();
	}
}

//设置检定状态（所有表）
void FlowWeightDlg::on_btnAllVerifyStatus_clicked()
{
	for (int i=0; i<m_maxMeterNum; i++)
	{
		m_meterObj[i].askSetVerifyStatus();
	}
}

//调整误差（所有表）
void FlowWeightDlg::on_btnAllAdjError_clicked()
{

}

//修改表号（所有表）
void FlowWeightDlg::on_btnAllModifyNO_clicked()
{

}

/*
** 修改表号
** 输入参数：
	row:行号，由row可以知道当前热表对应的串口、表号、误差等等
*/
void FlowWeightDlg::slotModifyMeterNO(const int &row)
{
	qDebug()<<"slotModifyMeterNO row ="<<row;
	m_meterObj[row].askModifyMeterNO("12345678", ui.tableWidget->item(row, COLUMN_METER_NUMBER)->text());
}

/*
** 调整误差
** 输入参数：
	row:行号，由row可以知道当前热表对应的串口、表号、误差等等
*/
void FlowWeightDlg::slotAdjustError(const int &row)
{
	qDebug()<<"slotAdjustError row ="<<row;
// 	QString meterNO = ui.tableWidget->item(row, COLUMN_METER_NUMBER)->text();
// 	float bigErr = ui.lnEditBigNewError->text().toFloat();
// 	float mid2Err = ui.lnEditMid2NewError->text().toFloat();
// 	float mid1Err = ui.lnEditMid1NewError->text().toFloat();
// 	float smallErr = ui.lnEditSmallNewError->text().toFloat();
// 	m_meterObj->askModifyFlowCoe(meterNO, bigErr, mid2Err, mid1Err, smallErr);
}

/*
** 读取表号
** 输入参数：
	row:行号，由row可以知道当前热表对应的串口、表号、误差等等
*/
void FlowWeightDlg::slotReadMeter(const int &row)
{
	qDebug()<<"slotReadMeter row ="<<row;
	m_meterObj[row].askReadMeter();
}

/*
** 检定状态
** 输入参数：
	row:行号，由row可以知道当前热表对应的串口、表号、误差等等
*/
void FlowWeightDlg::slotVerifyStatus(const int &row)
{
	qDebug()<<"slotVerifyStatus row ="<<row;
	m_meterObj[row].askSetVerifyStatus();
}
