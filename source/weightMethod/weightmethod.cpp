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
#include <QtSql/QSqlTableModel>
#include <QtGui/QFileDialog>


#include "weightmethod.h"
#include "commondefine.h"
#include "algorithm.h"
#include "math.h"

WeightMethodDlg::WeightMethodDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"WeightMethodDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);
 	ui.btnNext->hide(); //隐藏"下一步"按钮
	ui.btnStart->hide();
	m_inputStartValue = false;
	m_inputEndValue = false;

	//不同等级的热量表对应的标准误差
	m_gradeErr[1] = 0.01;
	m_gradeErr[2] = 0.02;
	m_gradeErr[3] = 0.03;
/*	
	ui.tabWidget->setTabsClosable(true);
	connect(ui.tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));
	for (int i=0; i<4; i++)
	{
		ui.tabWidget->removeTab(1);
	}
*/

/*********************************************************/
	m_balTimer = new QTimer(this);
	connect(m_balTimer, SIGNAL(timeout()), this, SLOT(freshBigBalaceValue()));
	m_balTimer->start(200); //模拟天平每200毫秒更新一次
	m_balValue = 0.0;
	m_tempValue = 20.0;
/*********************************************************/
	m_stopFlag = false; //退出界面后，不再检查天平容量

	m_readComConfig = new ReadComConfig(); //读串口设置接口

	m_balanceObj = NULL;
	initBalanceCom();		//初始化天平串口

	m_tempObj = NULL;
	m_tempTimer = NULL;
	initTemperatureCom();	//初始化温度采集串口

	m_controlObj = NULL;
	initControlCom();		//初始化控制串口


	m_chkAlg = new CAlgorithm();//计算类接口

	if (!getPortSetIni(&m_portsetinfo)) //获取下位机端口号配置信息
	{
		QMessageBox::warning(this, tr("Warning"), tr("获取下位机端口号配置信息失败!请重新设置！"));
	}

	initValveStatus();      //映射关系；初始化阀门状态

	m_exaustTimer = new QTimer(this); //排气定时器
	connect(m_exaustTimer, SIGNAL(timeout()), this, SLOT(slotExaustFinished()));

	m_tempCount = 1; //计算平均温度用的累加计数器
	m_nowOrder = 0;  //当前进行的检定序号

	m_nowParams = new Quality_Params_STR;
	memset(m_nowParams, 0, sizeof(Quality_Params_STR));
	m_continueVerify = true; //连续检定
	m_resetZero = false;     //初值回零
	m_autopick = false;      //自动采集
	m_flowPointNum = 0;      //流量点个数
	m_rowNum = 0;            //某规格表最多支持的检表个数
	m_meterNum = 0;          //实际检表个数
	m_exaustSecond = 45;     //默认排气时间45秒
	m_totalFlag = 0;         //默认分量检定
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

	m_recPtr = NULL;

	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable(tr("T_Meter_Standard"));  
	model->select();  
	m_mapper = new QDataWidgetMapper(this);
	m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	m_mapper->setModel(model);
	m_mapper->addMapping(ui.lnEditStandard, 1); //映射表"T_Meter_Standard"的第二个字段

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

	if (!isWaterOutValveOpen())
	{
		qDebug()<<"放水阀门未打开";
		openWaterOutValve();
	}

	ui.lnEditSmallBalance->setInputMask("00000000");
}

WeightMethodDlg::~WeightMethodDlg()
{
}

void WeightMethodDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^WeightMethodDlg::closeEvent";

	m_stopFlag = true;

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


/*
** 温度采集串口 上位机直接采集
** 周期请求
*/
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
// 	connect(m_tempTimer, SIGNAL(timeout()), this, SLOT(slotFreshFlow())); //计算流量
	
	m_tempTimer->start(TIMEOUT_TEMPER); //周期请求温度
}

//控制板通讯串口
void WeightMethodDlg::initControlCom()
{
	ComInfoStruct valveStruct = m_readComConfig->ReadValveConfig();
	m_controlObj = new ControlComObject();
	m_controlObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_controlObj->openControlCom(&valveStruct);

	connect(m_controlObj, SIGNAL(controlRelayIsOk(const UINT8 &, const bool &)), this, SLOT(slotSetValveBtnStatus(const UINT8 &, const bool &)));
	connect(m_controlObj, SIGNAL(controlRegulateIsOk()), this, SLOT(slotSetRegulateOk()));

	//天平数值从控制板获取
// 	connect(m_controlObj, SIGNAL(controlGetBalanceValueIsOk(const QString&)), this, SLOT(slotFreshBalanceValue(const QString &)));
}

/*
** 端口号-阀门映射关系；初始化阀门状态
** 需要改进得更加灵活
*/
void WeightMethodDlg::initValveStatus()
{
	m_nowPortNo = 0;

	//端口号-阀门按钮 映射关系
	m_valveBtn[m_portsetinfo.bigNo] = ui.btnValveBig;
	m_valveBtn[m_portsetinfo.smallNo] = ui.btnValveSmall;
	m_valveBtn[m_portsetinfo.middle1No] = ui.btnValveMiddle1;
	m_valveBtn[m_portsetinfo.middle2No] = ui.btnValveMiddle2;
	m_valveBtn[m_portsetinfo.waterInNo] = ui.btnWaterIn;
	m_valveBtn[m_portsetinfo.waterOutNo] = ui.btnWaterOut;

	//初始化 全部阀门状态为关闭
	m_valveStatus[m_portsetinfo.bigNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.smallNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle1No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle2No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterOutNo] = VALVE_CLOSE;

	setValveBtnBackColor(m_valveBtn[m_portsetinfo.bigNo], m_valveStatus[m_portsetinfo.bigNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.smallNo], m_valveStatus[m_portsetinfo.smallNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle1No], m_valveStatus[m_portsetinfo.middle1No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle2No], m_valveStatus[m_portsetinfo.middle2No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterInNo], m_valveStatus[m_portsetinfo.waterInNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterOutNo], m_valveStatus[m_portsetinfo.waterOutNo]);
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

/*
** 计算瞬时流量(待改进、需要实验验证)
*/
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

//获取当前检定参数
int WeightMethodDlg::readNowParaConfig()
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
	m_totalFlag = m_nowParams->bo_total;	 //总量检定标志(1:总量检定  0:分量检定)
	m_standard = m_nowParams->m_stand;       //表规格
	m_model = m_nowParams->m_model;   //表型号
	m_meterType = m_nowParams->m_type;//表类型
	m_rowNum = m_nowParams->m_maxMeters;     //不同表规格对应的最大检表数量

	setTableRowCount();
	showNowKeyParaConfig();

	return true;
}

//设置表格行数
void WeightMethodDlg::setTableRowCount()
{
	if (m_rowNum <= 0)
	{
		return;
	}

	ui.tableWidget->setRowCount(m_rowNum); //设置表格行数
	QStringList vLabels;
	for (int i=1; i<= m_rowNum; i++)
	{
		vLabels<<QString("表位号%1").arg(i);
// 		QSpinBox *box = new QSpinBox(this);
// 		box->setMinimum(0);
// 		box->setMaximum(99999999);
// 		ui.tableWidget->setCellWidget(i-1,0, box);
	}
	ui.tableWidget->setVerticalHeaderLabels(vLabels);
}

//显示当前关键参数设置信息
void WeightMethodDlg::showNowKeyParaConfig()
{
	if (NULL == m_nowParams)
	{
		return;
	}

	ui.cmbAutoPick->setCurrentIndex(m_nowParams->bo_autopick);
	ui.cmbContinue->setCurrentIndex(m_nowParams->bo_converify);

	m_mapper->setCurrentIndex(m_nowParams->m_stand);
}

/*
** 点击"排气按钮"，开始检定
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
	m_stopFlag = false;
	clearTableContents();
	m_meterNum = 0;

	m_exaustSecond = m_nowParams->ex_time;
	m_exaustTimer->start(1000);//开始排气倒计时

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
** 定时器响应函数
*/
void WeightMethodDlg::slotExaustFinished()
{
	m_exaustSecond --;
	ui.labelHintInfo->setText(QString("排气倒计时：%1 秒").arg(m_exaustSecond));
	qDebug()<<"排气倒计时:"<<m_exaustSecond<<"秒";

	if (m_exaustSecond > 1)
	{
		return;
	}
	m_exaustTimer->stop(); //停止排气计时
	ui.labelHintInfo->setText(QString("排气倒计时 结束！"));
	if (!closeAllFlowPointValves()) //关闭所有流量点阀门 失败
	{
		if (!closeAllFlowPointValves()) //再尝试关闭一次
		{
			qWarning()<<"关闭所有流量点阀门失败，检定结束";
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

/*
** 读取表号 自动读取或手动填写
*/
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
	while (!m_stopFlag && (ui.lnEditBigBalance->text().toFloat() < v))
	{
		qDebug()<<"天平重量 ="<<ui.lnEditBigBalance->text().toFloat()<<", 小于要求的重量 "<<v;
		QTest::qWait(1000);
	}

	return true;
}

int WeightMethodDlg::judgeBalanceAndCalcTemper(float targetV)
{
	int second;
	float nowFlow =m_paraSetReader->getFpBySeq(m_nowOrder).fp_verify;;
	while (!m_stopFlag && (ui.lnEditBigBalance->text().toFloat() < targetV))
	{
		qDebug()<<"天平重量 ="<<ui.lnEditBigBalance->text().toFloat()<<", 小于要求的重量 "<<targetV;
		m_pipeInTemper += ui.lcdNumberInTemper->value();
		m_pipeOutTemper += ui.lcdNumberOutTemper->value();
		m_tempCount++;

		second = 3.6*(targetV - ui.lnEditBigBalance->text().toFloat())/nowFlow;
		ui.labelHintInfo->setText(QString("第%1流量点: %2 m3/h\n剩余时间 %3 秒").arg(m_nowOrder).arg(nowFlow).arg(second));
		QTest::qWait(1000);
	}

	m_pipeInTemper = m_pipeInTemper/m_tempCount;   //入口平均温度
	m_pipeOutTemper = m_pipeOutTemper/m_tempCount; //出口平均温度
	ui.labelHintInfo->setText(QString("第%1流量点: %2 m3/h\n检定完毕!").arg(m_nowOrder).arg(nowFlow));
	if (m_nowOrder == m_flowPointNum)
	{
		ui.labelHintInfo->setText("所有流量点已经检定完毕!");
		ui.btnNext->hide();
	}
	return true;
}

//判断热量表都已进入检定状态
int WeightMethodDlg::isAllMeterInVerifyStatus()
{
	return true;
}

void WeightMethodDlg::clearTableContents()
{
	for (int i=0; i<m_rowNum; i++)
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
// 	ui.tableWidget->clearContents();
}

//点击"开始"按钮
void WeightMethodDlg::on_btnStart_clicked()
{
	startVerify();
}

//点击"下一步"按钮
void WeightMethodDlg::on_btnNext_clicked()
{
	if (m_nowOrder >= m_flowPointNum)
	{
		QMessageBox::warning(this, "warning", "所有流量点已经检定完毕!");
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
void WeightMethodDlg::on_btnStop_clicked()
{
	m_stopFlag = true; //不再检查天平质量
	m_inputStartValue = false;
	m_inputEndValue = false;
	
	m_exaustTimer->stop();//停止排气定时器

	//关闭进水阀、所有流量点阀门

	//打开放水阀

	//停止水泵

	ui.labelHintInfo->setText("已终止检测");
}

//开始检定
void WeightMethodDlg::startVerify()
{
	m_nowOrder = 1;

	//判断实际检表的个数(根据获取到的表号个数)
	if (getValidMeterNum() <= 0)
	{
		QMessageBox::warning(this, tr("Warning"), tr("请输入表号！"));
		return;
	}

	if (m_recPtr != NULL)
	{
		delete []m_recPtr;
		m_recPtr = NULL;
	}
	m_recPtr = new Record_Quality_STR[m_meterNum];
	memset(m_recPtr, 0, sizeof(Record_Quality_STR)*m_meterNum);

	m_flowPoint = m_paraSetReader->getFpBySeq(1).fp_verify;//第一个流量点
	for (int m=0; m<m_meterNum; m++) //
	{
		ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_FLOW_POINT, new QTableWidgetItem(QString::number(m_flowPoint, 'f', 2)));//流量点
	}

	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //记录时间戳
	m_nowDate = QDateTime::currentDateTime().toString("yyyy-MM-dd"); //当前日期'2014-08-07'
	m_validDate = QDateTime::currentDateTime().addYears(VALID_YEAR).addDays(-1).toString("yyyy-MM-dd"); //有效期

	m_meterStartValue = new float[m_meterNum]; //表初值 
	memset(m_meterStartValue, 0, sizeof(float)*m_meterNum);

	m_meterEndValue = new float[m_meterNum];   //表终值
	memset(m_meterEndValue, 0, sizeof(float)*m_meterNum);

	m_meterTemper = new float[m_meterNum];     //表温度
	memset(m_meterTemper, 0, sizeof(float)*m_meterNum);

	m_meterDensity = new float[m_meterNum];    //表密度
	memset(m_meterDensity, 0, sizeof(float)*m_meterNum);

	m_meterStdValue = new float[m_meterNum];   //被检表的标准值
	memset(m_meterStdValue, 0, sizeof(float)*m_meterNum);

	m_meterError = new float[m_meterNum];      //被检表的误差
	memset(m_meterError, 0, sizeof(float)*m_meterNum);
	
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

int WeightMethodDlg::getValidMeterNum()
{
	bool ok;
	for (int i=0; i<m_rowNum; i++)
	{
		if (NULL == ui.tableWidget->item(i, 0)) //"表号"单元格为空
		{
			continue;
		}
		ui.tableWidget->item(i, 0)->text().toInt(&ok, 10);
		if (!ok) //表号转换失败(非数字)
		{
			continue;
		}

		m_meterPosMap[m_meterNum] = i+1; //表位号从1开始
		m_meterNum++;
	}
	return m_meterNum;
}

//刷新天平、温度数值 仅测试用
void WeightMethodDlg::freshBigBalaceValue()
{
// 	if (m_balValue > 100)
// 	{
// 		m_balValue = 0;
// 	}
	m_balValue += 0.2;
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

/*
** 准备单个流量点的检定，进行必要的检查
** 注意：order从1开始
*/
int WeightMethodDlg::prepareVerifyFlowPoint(int order)
{
	if (order < 1)
	{
		return false;
	}
	if (m_meterNum <= 0)
	{
		QMessageBox::warning(this, tr("Warning"), tr("请输入表号！"));
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

	if (m_resetZero) //初值回零
	{
		QTest::qWait(18000); //等待18秒，等待被检表初值回零
		memset(m_meterStartValue, 0, sizeof(float)*m_meterNum);
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
int WeightMethodDlg::startVerifyFlowPoint(int order)
{
	m_balStartV = ui.lnEditBigBalance->text().toFloat(); //记录天平初值
	m_pipeInTemper = ui.lcdNumberInTemper->value();
	m_pipeOutTemper = ui.lcdNumberOutTemper->value();

	m_flowPoint = m_paraSetReader->getFpBySeq(order).fp_verify;//order对应的流量点
	int portNo = m_paraSetReader->getFpBySeq(order).fp_valve;  //order对应的阀门端口号
	float verifyQuantity = m_paraSetReader->getFpBySeq(order).fp_quantity; //第order次检定对应的检定量
	if (openValve(portNo)) //打开阀门，开始跑流量
	{
		if (judgeBalanceAndCalcTemper(m_balStartV + verifyQuantity)) //跑完检定量并计算次过程的平均温度
		{
			closeValve(portNo); //关闭order对应的阀门
			m_balEndV = ui.lnEditBigBalance->text().toFloat(); //记录天平终值

			for (int m=0; m<m_meterNum; m++) //
			{
				m_meterTemper[m] = m_chkAlg->getMeterTempByPos(m_pipeInTemper, m_pipeOutTemper, m_meterPosMap[m]);//计算每个被检表的温度
				m_meterDensity[m] = m_chkAlg->getDensityByQuery(m_meterTemper[m]);//计算每个被检表的密度
				m_meterStdValue[m] = m_chkAlg->getStdVolByPos((m_balEndV-m_balStartV), m_pipeInTemper, m_pipeOutTemper, m_meterPosMap[m]); //计算每个被检表的体积标准值

				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_FLOW_POINT, new QTableWidgetItem(QString::number(m_flowPoint, 'f', 2)));//流量点
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_BAL_START, new QTableWidgetItem(QString::number(m_balStartV, 'f', 2)));//天平初值
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_BAL_END, new QTableWidgetItem(QString::number(m_balEndV, 'f', 2)));    //天平终值
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_TEMPER, new QTableWidgetItem(QString::number(m_meterTemper[m], 'f', 2)));  //温度
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_DENSITY, new QTableWidgetItem(QString::number(m_meterDensity[m], 'f', 2)));//密度
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_STD_VALUE, new QTableWidgetItem(QString::number(m_meterStdValue[m], 'f', 2)));//标准值
			}

			if (!getMeterEndValue()) //获取表终值
			{
				return false;
			}

			if (m_autopick) //自动采集
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
int WeightMethodDlg::calcAllMeterError()
{
	for (int m=0; m<m_meterNum; m++)
	{
		m_meterError[m] = (m_meterEndValue[m] - m_meterStartValue[m] - m_meterStdValue[m])/m_meterStdValue[m];//计算每个表的误差
		ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_ERROR, new QTableWidgetItem(QString::number(m_meterError[m], 'f', 6))); //误差
	}

	QString meterNoPrefix = getNumPrefixOfManufac(m_nowParams->m_manufac);
	QString meterNoStr;

	for (int i=0; i<m_meterNum; i++)
	{
		strncpy(m_recPtr[i].timestamp, m_timeStamp.toAscii(), TIMESTAMP_LEN);
		m_recPtr[i].flowPoint = m_flowPoint;
		meterNoStr = meterNoPrefix + QString("%1").arg(ui.tableWidget->item(m_meterPosMap[i]-1, 0)->text(), 8, '0');
		strcpy(m_recPtr[i].meterNo, meterNoStr.toAscii());
		m_recPtr[i].flowPointIdx = m_nowOrder;
		m_recPtr[i].totalFlag = m_totalFlag;
		m_recPtr[i].meterValue0 = m_meterStartValue[i];
		m_recPtr[i].meterValue1 = m_meterEndValue[i];
		m_recPtr[i].meterDeltaV = m_recPtr[i].meterValue1 - m_recPtr[i].meterValue0;
		m_recPtr[i].balWeight0 = m_balStartV;
		m_recPtr[i].balWeight1 = m_balEndV;
		m_recPtr[i].balDeltaW = m_recPtr[i].balWeight1 - m_recPtr[i].balWeight0;
		m_recPtr[i].inSlotTemper = m_pipeInTemper;
		m_recPtr[i].outSlotTemper = m_pipeOutTemper;
		m_recPtr[i].pipeTemper = m_meterTemper[i]; 
		m_recPtr[i].density = m_meterDensity[i];
		m_recPtr[i].stdValue = m_meterStdValue[i];
		m_recPtr[i].dispError = m_meterError[i];
		m_recPtr[i].grade = m_nowParams->m_grade;
		m_recPtr[i].stdError = m_gradeErr[m_nowParams->m_grade]; //二级表 标准误差
		m_recPtr[i].result = (fabs(m_recPtr[i].dispError) <= fabs(m_recPtr[i].stdError)) ? 1 : 0;
		m_recPtr[i].meterPosNo = m_meterPosMap[i];
		m_recPtr[i].standard = m_standard;
		m_recPtr[i].model = m_model;
		m_recPtr[i].meterType = m_meterType; //表类型
		m_recPtr[i].manufactDept = m_nowParams->m_manufac;
		m_recPtr[i].verifyDept = m_nowParams->m_vcomp;
		m_recPtr[i].verifyPerson = m_nowParams->m_vperson;
		strncpy(m_recPtr[i].date, m_nowDate.toAscii(), DATE_LEN);
		strncpy(m_recPtr[i].validDate, m_validDate.toAscii(), DATE_LEN);
	}

	return true; 
}

/*
** 计算某个被检表的误差
** 输入参数：
**     idx:被检表数组的索引
*/
int WeightMethodDlg::calcMeterError(int idx)
{
	m_meterError[idx] = (m_meterEndValue[idx] - m_meterStartValue[idx] - m_meterStdValue[idx])/m_meterStdValue[idx];//计算某个表的误差
	ui.tableWidget->setItem(m_meterPosMap[idx]-1, COLUMN_ERROR, new QTableWidgetItem(QString::number(m_meterError[idx], 'f', 6))); //误差

	QString meterNoPrefix = getNumPrefixOfManufac(m_nowParams->m_manufac);
	QString meterNoStr;

	strncpy(m_recPtr[idx].timestamp, m_timeStamp.toAscii(), TIMESTAMP_LEN);
	m_recPtr[idx].flowPoint = m_flowPoint;
	meterNoStr = meterNoPrefix + QString("%1").arg(ui.tableWidget->item(m_meterPosMap[idx]-1, 0)->text(), 8, '0');
	strcpy(m_recPtr[idx].meterNo, meterNoStr.toAscii());
	m_recPtr[idx].flowPointIdx = m_nowOrder; //
	m_recPtr[idx].totalFlag = m_totalFlag;
	m_recPtr[idx].meterValue0 = m_meterStartValue[idx];
	m_recPtr[idx].meterValue1 = m_meterEndValue[idx];
	m_recPtr[idx].meterDeltaV = m_recPtr[idx].meterValue1 - m_recPtr[idx].meterValue0;
	m_recPtr[idx].balWeight0 = m_balStartV;
	m_recPtr[idx].balWeight1 = m_balEndV;
	m_recPtr[idx].balDeltaW = m_recPtr[idx].balWeight1 - m_recPtr[idx].balWeight0;
	m_recPtr[idx].inSlotTemper = m_pipeInTemper;
	m_recPtr[idx].outSlotTemper = m_pipeOutTemper;
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
	strncpy(m_recPtr[idx].date, m_nowDate.toAscii(), DATE_LEN);
	strncpy(m_recPtr[idx].validDate, m_validDate.toAscii(), DATE_LEN);

	return true; 

}

//打开阀门
int WeightMethodDlg::openValve(UINT8 portno)
{
	m_controlObj->makeRelaySendBuf(portno, VALVE_OPEN);
	return true;
}

//关闭阀门
int WeightMethodDlg::closeValve(UINT8 portno)
{
	m_controlObj->makeRelaySendBuf(portno, VALVE_CLOSE);
	return true;
}

//响应阀门状态设置成功
void WeightMethodDlg::slotSetValveBtnStatus(const UINT8 &portno, const bool &status)
{
	m_valveStatus[portno] = status;
	setValveBtnBackColor(m_valveBtn[portno], m_valveStatus[portno]);
}

//响应调节阀调节成功
void WeightMethodDlg::slotSetRegulateOk()
{
// 	setRegBtnBackColor(m_regBtn[m_nowRegIdx], true);
}


//设置阀门按钮背景色
void WeightMethodDlg::setValveBtnBackColor(QToolButton *btn, bool status)
{
	if (NULL == btn)
	{
		return;
	}
	if (status) //阀门打开 绿色
	{
		btn->setStyleSheet("background:rgb(199,237,204);border:0px;");  
// 		btn->setIcon(QIcon("open.png"));
	}
	else //阀门关闭 红色
	{
		btn->setStyleSheet( "background-color:rgb(255,200,200);border:0px;border-radius:10px;");
// 		btn->setIcon(QIcon("close.png"));
	}
}

//设置调节阀按钮背景色
void WeightMethodDlg::setRegBtnBackColor(QPushButton *btn, bool status)
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
void WeightMethodDlg::on_btnParaSet_clicked()
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
void WeightMethodDlg::on_btnWaterIn_clicked() //进水阀
{
	m_nowPortNo = m_portsetinfo.waterInNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void WeightMethodDlg::on_btnWaterOut_clicked() //出水阀
{
	m_nowPortNo = m_portsetinfo.waterOutNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void WeightMethodDlg::on_btnValveBig_clicked() //大流量阀
{
	m_nowPortNo = m_portsetinfo.bigNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void WeightMethodDlg::on_btnValveMiddle1_clicked() //中流一阀
{
	m_nowPortNo = m_portsetinfo.middle1No;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

}

void WeightMethodDlg::on_btnValveMiddle2_clicked() //中流二阀
{
	m_nowPortNo = m_portsetinfo.middle2No;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void WeightMethodDlg::on_btnValveSmall_clicked() //小流量阀
{
	m_nowPortNo = m_portsetinfo.smallNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}


/*
** 启动水泵
*/
void WeightMethodDlg::on_btnWaterPumpStart_clicked()
{
	if (ui.spinBoxFrequency->value() <= 0)
	{
		QMessageBox::warning(this, tr("Warning"), tr("请设置变频器频率！"));
		ui.spinBoxFrequency->setFocus();
	}
	m_controlObj->makeRegulateSendBuf(m_portsetinfo.pumpNo, ui.spinBoxFrequency->value());
}

/*
** 停止水泵
*/
void WeightMethodDlg::on_btnWaterPumpStop_clicked()
{
	m_controlObj->makeRegulateSendBuf(m_portsetinfo.pumpNo, 0);
}

//获取表初值
int WeightMethodDlg::getMeterStartValue()
{
	if (m_autopick) //自动采集
	{
		for (int i=0; i<m_meterNum; i++)
		{
			m_meterStartValue[i] = 0.66;  //读取被检表初值
			ui.tableWidget->setItem(m_meterPosMap[i]-1, COLUMN_METER_START, new QTableWidgetItem(QString::number(m_meterStartValue[i])));//表初值
		}
		return true;
	}
	else //手动输入
	{
		QMessageBox::information(this, tr("Hint"), tr("请输入热量表初值！"));
		ui.tableWidget->setCurrentCell(m_meterPosMap[0]-1, COLUMN_METER_START); //定位到第一个需要输入初值的地方
		m_inputStartValue = true; //允许输入初值
		return false;
	}
}

//上一次的终值作为本次的初值
void WeightMethodDlg::makeStartValueByLastEndValue()
{
	float flow = m_paraSetReader->getFpBySeq(m_nowOrder).fp_verify;
	for (int i=0; i<m_meterNum; i++)
	{
		m_meterStartValue[i] = m_meterEndValue[i];
		ui.tableWidget->item(m_meterPosMap[i]-1, COLUMN_METER_START)->setText(QString("%1").arg(m_meterStartValue[i]));
 		ui.tableWidget->item(m_meterPosMap[i]-1, COLUMN_FLOW_POINT)->setText(QString("%1").arg(flow));
	}
}

//获取表终值
int WeightMethodDlg::getMeterEndValue()
{
	if (m_autopick) //自动采集
	{
		for (int i=0; i<m_meterNum; i++)
		{
			m_meterEndValue[i] = 10.88;  //读取被检表终值
			ui.tableWidget->setItem(m_meterPosMap[i]-1, COLUMN_METER_END, new QTableWidgetItem(QString::number(m_meterEndValue[i])));//表终值
		}
		return true;
	}
	else //手动输入
	{
		QMessageBox::information(this, tr("Hint"), tr("请输入热量表终值！"));
		ui.tableWidget->setCurrentCell(m_meterPosMap[0]-1, COLUMN_METER_END); //定位到第一个需要输入终值的地方
		m_inputEndValue = true; //允许输入终值
		return false;
	}
}

//响应处理用户输入完表初值、表终值
void WeightMethodDlg::on_tableWidget_cellChanged(int row, int column)
{
	if (m_autopick) //自动采集
	{
		return;
	}

	if (NULL == ui.tableWidget->item(row,  column))
	{
		return;
	}

	int idx = -1;
	bool ok;
	if (column==COLUMN_METER_START && m_inputStartValue) //表初值列 且 允许输入初值
	{
		idx = isMeterPosValid(row);
		if (idx < 0)
		{
			return;
		}
		else
		{
			m_meterStartValue[idx] = ui.tableWidget->item(row, column)->text().toFloat(&ok);
			if (!ok)
			{
				QMessageBox::warning(this, tr("Warning"), tr("输入错误！请输入数字"));
				return;
			}
		}

		if (row == (m_meterPosMap[m_meterNum-1]-1)) //输入最后一个表初值
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
		idx = isMeterPosValid(row);
		if (idx < 0)
		{
			return;
		}
		else
		{
			m_meterEndValue[idx] = ui.tableWidget->item(row, column)->text().toFloat(&ok);
			if (!ok)
			{
				QMessageBox::warning(this, tr("Warning"), tr("输入错误！请输入数字"));
				return;
			}
			calcMeterError(idx);
			insertVerifyRec(&m_recPtr[idx], 1);

			if (row == (m_meterPosMap[m_meterNum-1]-1)) //输入最后一个表终值
			{
				m_inputEndValue = false;
// 				calcAllMeterError();
// 				saveAllVerifyRecords();

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

}

/*
** 判断表位号是否有效(该表位是否需要检表)
** 返回被检表数组的索引
*/
int WeightMethodDlg::isMeterPosValid(int row)
{
	for (int i=0; i<m_meterNum; i++)
	{
		if ((m_meterPosMap[i]-1) == row)
		{
			return i;
		}
	}
	return -1;
}

/*
** 保存所有被检表的检定记录
*/
int WeightMethodDlg::saveAllVerifyRecords()
{
 	insertVerifyRec(m_recPtr, m_meterNum);
	return true;
}

/*
void WeightMethodDlg::on_btnOpen_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("excelfile(*.xls*)"));
	m_excel.Open(fileName, 1, false); //打开指定的xls文件的指定sheet，且指定是否可见

	int num = 0;
	for (int i=1; i<=10; i++)
	{
		for (int j=1; j<=10; j++)
		{
			m_excel.SetCellData(i,j,++num); //修改指定单元数据
		}
	}

	QVariant data = m_excel.GetCellData(1,1); //访问指定单元格数据
	m_excel.GetCellData(2,2);
	m_excel.GetCellData(3,3);
	m_excel.Save(); //保存
	m_excel.Close();
}

void WeightMethodDlg::on_btnImport_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("excelfile(*.xls*)"));
	m_excel.Open(fileName, 1, false);
	m_excel.ReadDataToTable(ui.excelTable); //导入到widget中
	m_excel.Close();
}
*/
void WeightMethodDlg::on_btnExport_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("excelfile(*.xls*)"));
	m_excel.Open(fileName, 1, false);
	m_excel.SaveDataFrTable(ui.tableWidget); //导出报表
	m_excel.Close();
}


