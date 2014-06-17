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

	m_paraset = new ParaSetDlg();

	m_tempObj = NULL;
	m_tempTimer = NULL;
// 	initTemperatureCom(); //初始化温度采集串口

	m_valveObj = NULL;
// 	initValveControlCom();//打开阀门控制串口

	m_balanceObj = NULL;
	initBalanceCom();
}

QualityDlg::~QualityDlg()
{
	if (m_paraset)
	{
		delete m_paraset;
		m_paraset = NULL;
	}
	if (m_tempObj)
	{
		delete m_tempObj;
		m_tempObj = NULL;
	}
	if (m_tempTimer)
	{
		delete m_tempTimer;
		m_tempTimer = NULL;
	}
	if (m_valveObj)
	{
		delete m_valveObj;
		m_valveObj = NULL;
	}
	if (m_balanceObj)
	{
		delete m_balanceObj;
		m_balanceObj = NULL;
	}
}

void QualityDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct;
	tempStruct.portName = "COM2";
	tempStruct.baudRate = 9600;
	tempStruct.dataBit = 8;
	tempStruct.parity = 0;
	tempStruct.stopBit = 0;
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer();
	connect(m_tempTimer, SIGNAL(timeout()), m_tempObj, SLOT(writeTemperatureComBuffer()));
	m_tempTimer->start(TIMEOUT_TEMPER);
}

void QualityDlg::initValveControlCom()
{
	ComInfoStruct valveStruct;
	valveStruct.portName = "COM2";
	valveStruct.baudRate = 9600;
	valveStruct.dataBit = 8;
	valveStruct.parity = 0;
	valveStruct.stopBit = 0;
	m_valveObj = new ValveComObject();
	m_valveObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_valveObj->openValveControlCom(&valveStruct);

	connect(m_valveObj, SIGNAL(valveComIsAnalysed(const int &)), this, SLOT(slotSetValveBtnStatus(const int &)));
}

void QualityDlg::initBalanceCom()
{
	ComInfoStruct balanceStruct;
	balanceStruct.portName = "COM2";
	balanceStruct.baudRate = 9600;
	balanceStruct.dataBit = 8;
	balanceStruct.parity = 0;
	balanceStruct.stopBit = 0;
	m_balanceObj = new BalanceComObject();
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

 	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const QString &)), this, SLOT(slotFreshBalanceValue(const QString &)));
}

void QualityDlg::on_btnWaterIn_clicked()
{
	m_valveObj->writeValveControlComBuffer();
	setValveBtnBackColor(ui.btnWaterIn, true);
}

void QualityDlg::setValveBtnBackColor(QPushButton *btn, bool isOpen)
{
	if (isOpen)
	{
		btn->setStyleSheet("background:green;border:0px;");  
	}
	else
	{
		btn->setStyleSheet("background:red;border:0px;");  
	}
}

void QualityDlg::on_btnParaSet_clicked()
{
	m_paraset->show();
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
}

void QualityDlg::slotSetValveBtnStatus(const int& isOpen )
{
	setValveBtnBackColor(ui.btnWaterIn, isOpen);
}




