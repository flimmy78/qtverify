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

/*	for (int i=0; i<4; i++)
	{
		ui.tabWidget->removeTab(1);
	}*/
	////////////////////////////////////////////////////////


	m_exaustTimer = new QTimer(this); //排气定时器
	connect(m_exaustTimer, SIGNAL(timeout()), this, SLOT(slotExaustFinished()));
	m_exaustSecond = 10; //排气时间默认45秒

	m_balTimer = new QTimer(this);
	connect(m_balTimer, SIGNAL(timeout()), this, SLOT(freshBigBalaceValue()));
	m_balTimer->start(200); //模拟天平每200毫秒更新一次
	m_balValue = 0.0;

	if (!isComAndPortNormal())
	{
		qWarning()<<"串口、端口设置错误!";
	}

	if (!isWaterOutValveOpen())
	{
		qWarning()<<"放水阀门未打开";
	}

	if (!readParaConfig())
	{
		qWarning()<<"读取参数配置文件失败!";
	}
}

WeightMethodDlg::~WeightMethodDlg()
{
}

void WeightMethodDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^WeightMethodDlg::closeEvent";

}

//关闭标签页
void WeightMethodDlg::removeSubTab(int index) 
{ 
	ui.tabWidget->removeTab(index); 
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
	return true;
}

/*
**	点击"排气按钮"，开始检定
*/
int WeightMethodDlg::on_btnExhaust_clicked()
{
	if (!isDataCollectNormal())
	{
		qWarning()<<"数据采集不正常，请检查";
		return false;
	}

	if (!openAllValuesAndPump())
	{
		qWarning()<<"打开所有阀门和水泵 失败!";
		return false;
	}

	m_exaustTimer->start(m_exaustSecond*1000);//开始排气倒计时

	readMeterNumber();

	setMeterVerifyStatus();

	return true;
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

void WeightMethodDlg::on_btnStart_clicked()
{
	startVerify();
}

//开始检定
void WeightMethodDlg::startVerify()
{
	
}


void WeightMethodDlg::freshBigBalaceValue()
{
	if (m_balValue > 10)
	{
		m_balValue = 0;
	}
	m_balValue += 0.01;
	ui.lnEditBigBalance->setText(QString("%1").arg(m_balValue));
}