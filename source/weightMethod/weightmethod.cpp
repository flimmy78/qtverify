/***********************************************
**  文件名:     weightmethod.cpp
**  功能:       质量法检定主界面
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/7/15
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/07 第一版
**  内容包含:
**  说明:		
**  更新记录:   
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QTest>

#include "weightmethod.h"
#include "commondefine.h"

WeightMethodDlg::WeightMethodDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"WeightMethodDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	ui.tabWidget->setTabsClosable(true);
	connect(ui.tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));

	/////////////////////////////////////////////////////////
	ui.lcdNumberInTemper->display("27.8");
	QString inTemper = QString("%1").arg(ui.lcdNumberInTemper->value(), 4);
	float iii = inTemper.toFloat();

	m_balTimer = new QTimer(this);
	connect(m_balTimer, SIGNAL(timeout()), this, SLOT(freshBigBalaceValue()));
	m_balTimer->start(200); //模拟天平每200毫秒更新一次
	m_balValue = 0.0;
	m_tempValue = 20.0;

	m_readComConfig = NULL;
	m_readComConfig = new ReadComConfig();

	m_balanceObj = NULL;
	initBalanceCom();		//初始化天平串口

	m_tempObj = NULL;
	m_tempTimer = NULL;
	initTemperatureCom();	//初始化温度采集串口


/*	for (int i=0; i<4; i++)
	{
		ui.tabWidget->removeTab(1);
	}*/
	////////////////////////////////////////////////////////

	m_meterNumMap[0] = 16; //DN15规格，最多检定16块
	m_meterNumMap[1] = 16; //DN20规格，最多检定16块
    m_meterNumMap[2] = 12; //DN25规格，最多检定12块

	m_paraSetReader = new ParaSetReader();

	m_exaustTimer = new QTimer(this); //排气定时器
	connect(m_exaustTimer, SIGNAL(timeout()), this, SLOT(slotExaustFinished()));



	m_continueVerify = true;
	m_resetZero = false;
	m_flowPointNum = 0;
	m_exaustSecond = 45;
	m_meterStartValue = NULL;
	m_meterEndValue = NULL;
	m_balStartV = 0;
	m_balEndV = 0;
	if (!readParaConfig())
	{
		qWarning()<<"读取参数配置文件失败!";
	}

	if (!isComAndPortNormal())
	{
		qWarning()<<"串口、端口设置错误!";
	}

	if (!isWaterOutValveOpen())
	{
		qDebug()<<"放水阀门未打开";
		openWaterOutValve();
	}
}

WeightMethodDlg::~WeightMethodDlg()
{
}

void WeightMethodDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^WeightMethodDlg::closeEvent";

	if (NULL == m_paraSetReader) //读检定参数
	{
		delete []m_paraSetReader;
		m_paraSetReader = NULL;
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

}

//关闭标签页
void WeightMethodDlg::removeSubTab(int index) 
{ 
	ui.tabWidget->removeTab(index); 
} 

//天平采集串口 上位机直接采集
void WeightMethodDlg::initBalanceCom()
{
	ComInfoStruct balanceStruct = m_readComConfig->ReadBalanceConfig();
	m_balanceObj = new BalanceComObject();
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

	//天平数值由上位机直接通过天平串口采集
	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const QString &)), this, SLOT(slotFreshBalanceValue(const QString &)));
}


/***************************************
	温度采集串口 上位机直接采集
	周期请求
****************************************/
void WeightMethodDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadTempConfig();
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer();
	connect(m_tempTimer, SIGNAL(timeout()), m_tempObj, SLOT(writeTemperatureComBuffer()));
// 	connect(m_tempTimer, SIGNAL(timeout()), this, SLOT(slotFreshFlow()));
	
	m_tempTimer->start(TIMEOUT_TEMPER); //周期请求温度
}

//在界面刷新天平数值
void WeightMethodDlg::slotFreshBalanceValue(const QString& Str)
{
	ui.lnEditBigBalance->setText(Str);
}

//在界面刷新入口温度和出口温度值
void WeightMethodDlg::slotFreshComTempValue(const QString& tempStr)
{
	ui.lcdNumberInTemper->display(tempStr.left(DATA_WIDTH).toFloat());   //入口温度 PV
	ui.lcdNumberOutTemper->display(tempStr.right(DATA_WIDTH).toFloat()); //出口温度 SV
}

/************************************************************************/
/* 计算瞬时流量(待改进、需要实验验证)                                   */
/************************************************************************/
void WeightMethodDlg::slotFreshFlow()
{
 	qDebug()<<"slotFreshFlow thread:"<<QThread::currentThreadId(); //

}

//检测串口、端口设置是否正确
int WeightMethodDlg::isComAndPortNormal()
{
	return true;
}

//检查放水阀门是否打开 打开:true，关闭:false
int WeightMethodDlg::isWaterOutValveOpen()
{
	return true;
}

//读参数配置文件
int WeightMethodDlg::readParaConfig()
{
	m_continueVerify = m_paraSetReader->params->bo_converify; //连续检定
	m_resetZero = m_paraSetReader->params->bo_resetzero; //初值回零
	m_flowPointNum = m_paraSetReader->params->total_fp;  //有效流量点的个数 
	m_exaustSecond = m_paraSetReader->params->ex_time;   //排气时间


	int standard = m_paraSetReader->params->m_stand; //表规格
	m_meterNum = m_meterNumMap[standard]; //不同表规格对应的最大检表数量
	m_meterStartValue = new float[m_meterNum]; 
	memset(m_meterStartValue, 0, sizeof(float)*m_meterNum);
	m_meterStartValue[0] = 111.111;
	m_meterEndValue = new float[m_meterNum];
	memset(m_meterEndValue, 0, sizeof(float)*m_meterNum);
	ui.tableWidget->setRowCount(m_meterNum);

	return true;
}

/*
**	点击"排气按钮"，开始检定
*/
void WeightMethodDlg::on_btnExhaust_clicked()
{
	if (!isDataCollectNormal())
	{
		qWarning()<<"数据采集不正常，请检查";
		return;
	}

	if (!openAllValuesAndPump())
	{
		qWarning()<<"打开所有阀门和水泵 失败!";
		return;
	}

	m_exaustTimer->start(m_exaustSecond*1000);//开始排气倒计时

	readMeterNumber();

	setMeterVerifyStatus();

	return;
}

//检查数据采集是否正常，包括天平、温度、电磁流量计
int WeightMethodDlg::isDataCollectNormal()
{
	return true;
}

//打开所有阀门和水泵
int WeightMethodDlg::openAllValuesAndPump()
{
	return true;
}

/*
** 排气时间结束的响应函数
*/
void WeightMethodDlg::slotExaustFinished()
{
	m_exaustTimer->stop(); //停止排气计时

	if (!closeAllFlowPointValves()) //关闭所有流量点阀门 失败
	{
		if (!closeAllFlowPointValves()) //再尝试关闭一次
		{
			qWarning()<<"检定结束";
			return;
		}
	}

	//判断并等待天平重量,大于要求的初始重量(2kg)
	if (judgeBalanceInitValue(BALANCE_START_VALUE))
	{
		if (!closeWaterOutValve()) 
		{
			qWarning()<<"关闭放水阀失败";
		}

		if (!openBigFlowValve())
		{
			qWarning()<<"打开大流量阀失败";
		}
	}

	//判断并等待天平重量，大于初始重量(2kg)+3kg
	if (judgeBalanceInitValue(BALANCE_START_VALUE + 3))
	{
		if (!closeBigFlowValve())
		{
			qWarning()<<"关闭大流量阀失败";
		}
	}

	if (isAllMeterInVerifyStatus()) //热量表已进入检定状态
	{
		startVerify();
	}

}

//读取表号
int WeightMethodDlg::readMeterNumber()
{

	return true;
}

//设置热量表进入检定状态
int WeightMethodDlg::setMeterVerifyStatus()
{
	return true;
}

//关闭所有流量点阀门
int WeightMethodDlg::closeAllFlowPointValves()
{
	return true;
}

//关闭放水阀门
int WeightMethodDlg::closeWaterOutValve()
{
	return true;
}

//打开放水阀门
int WeightMethodDlg::openWaterOutValve()
{
	return true;
}

//打开大流量点阀门
int WeightMethodDlg::openBigFlowValve()
{
	return true;
}

//关闭大流量点阀门
int WeightMethodDlg::closeBigFlowValve()
{
	return true;
}

//响应处理天平质量的变化
int WeightMethodDlg::judgeBalanceInitValue(float v)
{
	while (ui.lnEditBigBalance->text().toFloat() < v)
	{
		qDebug()<<"天平重量 ="<<ui.lnEditBigBalance->text().toFloat()<<", 小于要求的重量 "<<v;
		QTest::qWait(1000);
	}

	return true;
}

//判断热量表都已进入检定状态
int WeightMethodDlg::isAllMeterInVerifyStatus()
{
	return true;
}

//点击"开始"按钮
void WeightMethodDlg::on_btnStart_clicked()
{
	startVerify();
}

//点击"下一步"按钮
void WeightMethodDlg::on_btnNext_clicked()
{
	startVerifyFlowPoint(2); // 开始进行下一次流量点的检定
}


//开始检定
void WeightMethodDlg::startVerify()
{
	if (m_continueVerify) //连续检定
	{
		if (!judgeBalanceCapacity()) //判断天平容量是否能够满足检定用量
		{
			openWaterOutValve();
		}
		while (!judgeBalanceCapacity())
		{ 
			QTest::qWait(1000);
		}
		closeWaterOutValve(); //若满足检定用量，则关闭放水阀
		QTest::qWait(3000); //等待3秒钟(等待水流稳定)
	}


	////////////////////////////////连续检定
	if (m_continueVerify)
	{
		for (int j=0; j<m_flowPointNum; j++)
		{
			startVerifyFlowPoint(j+1);
		}
	}

	////////////////////////////////不连续检定
	if (!m_continueVerify)
	{
		if (startVerifyFlowPoint(1)) //第一个流量点检定
		{
			ui.btnNext->show();
			ui.btnNext->setDefault(true);
		}
	}
	//检测结束
}

//刷新天平数值 仅测试用
void WeightMethodDlg::freshBigBalaceValue()
{
	if (m_balValue > 10)
	{
		m_balValue = 0;
	}
	m_balValue += 0.01;
	ui.lnEditBigBalance->setText(QString("%1").arg(m_balValue));

	if (m_tempValue > 90)
	{
		m_tempValue = 20;
	}
	m_tempValue += 0.2;
	ui.lcdNumberInTemper->display(m_tempValue);
	ui.lcdNumberOutTemper->display(m_tempValue+0.12);

}

/*
** 判断天平容量是否满足检定用量
** 连续检定时：满足总检定用量
*/
int WeightMethodDlg::judgeBalanceCapacity()
{
	return true;
}

/*
** 判断天平容量是否满足检定用量
** 不连续检定时：满足单次检定用量
*/
int WeightMethodDlg::judgeBalanceCapacitySingle(int order)
{
	return true;
}

//单个流量点的检定,order从1开始
int WeightMethodDlg::startVerifyFlowPoint(int order)
{
	if (!m_continueVerify) //非连续检定，每次检定开始之前都要判断天平容量
	{
		if (!judgeBalanceCapacitySingle(order)) //判断天平容量是否能够满足单次检定用量
		{
			openWaterOutValve();
		}
		while (!judgeBalanceCapacitySingle(order))
		{ 
			QTest::qWait(1000);
		}
		closeWaterOutValve(); //若满足检定用量，则关闭放水阀
		QTest::qWait(3000); //等待3秒钟，等待水流稳定
	}

	if (m_resetZero) //初值回零
	{
		QTest::qWait(18000); //等待18秒，等待被检表初值回零
		memset(m_meterStartValue, 0, sizeof(float)*m_meterNum);
	}
	else //初值不回零
	{
		for (int i=0; i<m_meterNum; i++)
		{
			m_meterStartValue[i] = 0.66;  //读取被检表初值
		}		
	}

	m_balStartV = ui.lnEditBigBalance->text().toFloat(); //记录天平初值
	m_pipeInTemper = ui.lcdNumberInTemper->value();
	m_pipeOutTemper = ui.lcdNumberOutTemper->value();

	int portNo = m_paraSetReader->getFpBySeq(order).fp_valve;  //order对应的阀门端口号
	float verifyQuantity = m_paraSetReader->getFpBySeq(order).fp_quantity; //第order次检定对应的检定量
	if (openValve(portNo))
	{
		if (judgeBalanceInitValue(m_balStartV + verifyQuantity))
		{
			closeValve(portNo); //关闭order对应的阀门
			m_balEndV = ui.lnEditBigBalance->text().toFloat(); //记录天平终值
			memset(m_meterEndValue, 50.5, sizeof(float)*m_meterNum); //记录表终值

			//计算每个被检表的温度
			//计算每个被检表的密度
			//计算每个被检表的标准值
			//计算每个表的误差，在界面显示
			//保存至数据库
		}
	}

	return true;
}

//打开阀门
int WeightMethodDlg::openValve(int portno)
{
	return true;
}

//关闭阀门
int WeightMethodDlg::closeValve(int portno)
{
	return true;
}
