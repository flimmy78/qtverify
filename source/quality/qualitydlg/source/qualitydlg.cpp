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
	initTemperatureCom(); //初始化温度采集串口

	m_controlObj = NULL;
// 	initControlCom();//打开控制串口
	m_valveWaterInStatus = false;//进水阀门状态 false：关闭状态; true:打开状态 
	setBtnBackColor(ui.btnWaterIn, m_valveWaterInStatus);
	m_Valve1Status = false; //大流量点阀门状态
	setBtnBackColor(ui.btnWaterValve1, m_Valve1Status);

	m_balanceObj = NULL;
// 	initBalanceCom();
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
}

void QualityDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadTempConfig();
// 	tempStruct.portName = "COM2";
// 	tempStruct.baudRate = 9600;
// 	tempStruct.dataBit = 8;
// 	tempStruct.parity = 0;
// 	tempStruct.stopBit = 0;
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer(this);
	connect(m_tempTimer, SIGNAL(timeout()), m_tempObj, SLOT(writeTemperatureComBuffer()));
	m_tempTimer->start(TIMEOUT_TEMPER); //周期请求温度
}

void QualityDlg::initControlCom()
{
	ComInfoStruct valveStruct = m_readComConfig->ReadValeConfig();
	m_controlObj = new ControlComObject();
	m_controlObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_controlObj->openControlCom(&valveStruct);

	connect(m_controlObj, SIGNAL(controlComIsAnalysed(const bool &)), this, SLOT(slotSetValveBtnStatus(const bool &)));
}

void QualityDlg::initBalanceCom()
{
	ComInfoStruct balanceStruct = m_readComConfig->ReadBalanceConfig();
	m_balanceObj = new BalanceComObject();
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

 	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const QString &)), this, SLOT(slotFreshBalanceValue(const QString &)));
}

void QualityDlg::on_btnWaterIn_clicked()
{
	int portno = 1; //假设端口号为1
	m_controlObj->writeControlComBuffer(portno, !m_valveWaterInStatus);
	m_valveWaterInStatus = !m_valveWaterInStatus; //只测试用
	setBtnBackColor(ui.btnWaterIn, m_valveWaterInStatus); //只测试用
}

void QualityDlg::on_btnWaterOut_clicked()
{
	m_balanceObj->writeBalanceComBuffer(); //临时调试用(模拟天平连续发送数据) 写天平串口缓冲区
}

void QualityDlg::on_btnWaterValve1_clicked()
{
	int portno = 2; //假设端口号为1
	m_controlObj->writeControlComBuffer(portno, !m_Valve1Status);
	m_Valve1Status = !m_Valve1Status; //只测试用
	setBtnBackColor(ui.btnWaterValve1, m_Valve1Status); //只测试用
}

void QualityDlg::setBtnBackColor(QPushButton *btn, bool status)
{
	if (status) //打开
	{
		btn->setStyleSheet("background:red;border:0px;");  
		btn->setIcon(QIcon("open.png"));
	}
	else
	{
		btn->setStyleSheet("background:green;border:0px;");  
		btn->setIcon(QIcon("close.png"));
	}
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

void QualityDlg::slotSetValveBtnStatus(const bool& status )
{
	m_valveWaterInStatus = status;
	setBtnBackColor(ui.btnWaterIn, m_valveWaterInStatus);
}




