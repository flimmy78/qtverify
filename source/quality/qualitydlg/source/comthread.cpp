/***********************************************
**  文件名:     comthread.cpp
**  功能:       线程管理类及串口管理类
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/14
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/06 第一版
**  内容包含:
**  说明:
**  更新记录:   2014-6-14增加温度串口管理类
                2014-6-17增加天平串口管理类
***********************************************/

#include <QtCore/QDebug>
#include <QtTest/QTest>

#include "comthread.h"

/************************************************
类名：ComThread
功能：线程管理类；开辟新线程
*************************************************/
ComThread::ComThread(QObject* parent) : QThread(parent)
{
}   

ComThread::~ComThread()
{
}

void ComThread::slot_main()
{           
	qDebug()<<"ComThread slot_main thread:" <<currentThreadId();       
} 

void ComThread::run()
{           
	qDebug()<<"ComThread run thread:"<<currentThreadId();
	exec(); //进入本线程的消息循环
}   


/************************************************
类名：ComObject
功能：串口操作基类
*************************************************/
ComObject::ComObject() : QObject()
{
}

ComObject::~ComObject()
{
}


/************************************************
类名：TempComObject
功能：温度串口类- 打开串口；设置串口参数；关闭串口；
*************************************************/
TempComObject::TempComObject() : ComObject()
{
	m_tempCom = NULL;

	m_tempFrame = new Temp_Frame_Struct();
	memset(m_tempFrame, 0, sizeof(Temp_Frame_Struct));

	m_tempProtocol = new TempProtocol();
}

TempComObject::~TempComObject()
{
	if(m_tempCom != NULL)
	{
		if(m_tempCom->isOpen())
		{
			m_tempCom->close();
		}
		delete m_tempCom;
	}

	if (m_tempFrame != NULL)
	{
		delete m_tempFrame;
		m_tempFrame = NULL;
	}

	if (m_tempProtocol != NULL)
	{
		delete m_tempProtocol;
		m_tempProtocol = NULL;
	}

}

void TempComObject::openTemperatureCom(ComInfoStruct *comStruct)
{
	qDebug()<<"openTemperatureCom thread:"<<QThread::currentThreadId();

	QString portName = comStruct->portName;// "COM2";//获取串口名
#ifdef Q_OS_LINUX
	m_tempCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_tempCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_tempCom, SIGNAL(readyRead()), this, SLOT(readTemperatureComBuffer()));

	m_tempCom->setBaudRate((BaudRateType)comStruct->baudRate);// BAUD9600); //设置波特率  
	m_tempCom->setDataBits((DataBitsType)comStruct->dataBit); //DATA_8);    //设置数据位
	m_tempCom->setParity((ParityType)comStruct->parity);	  //PAR_EVEN);  //设置校验位
	m_tempCom->setStopBits((StopBitsType)comStruct->stopBit); //STOP_1);    //设置停止位
	m_tempCom->setFlowControl(FLOW_OFF); //设置数据流控制  
	m_tempCom->setTimeout(TIME_OUT);     //设置延时

	if(m_tempCom->open(QIODevice::ReadWrite))
	{
		qDebug()<<"Open SerialPort:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
	}
	else
	{
		qDebug()<<"Open SerialPort:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return;
	}
}

//请求温度
void TempComObject::writeTemperatureComBuffer()
{
 	qDebug()<<"TempComObject::writeTemperatureComBuffer thread:"<<QThread::currentThreadId();
	m_tempProtocol->makeSendBuf();
	QByteArray buf = m_tempProtocol->getSendBuf();
	m_tempCom->write(buf);
}

//读串口缓冲区
void TempComObject::readTemperatureComBuffer()
{
	QByteArray tmp = m_tempCom->readAll();
 	qDebug()<<"read TemperatureComBuffer thread:"<<QThread::currentThreadId()<<",data is:"<<tmp;

	bool ret = false;
	ret = m_tempProtocol->readTemperComBuffer(tmp); //通讯协议接口
	if (ret)
	{
		QString tempStr = m_tempProtocol->getTempStr();
		emit temperatureIsReady(tempStr);
	}
}



/*********************************************************
类名：ValveComObject
功能：阀门控制串口类- 打开串口；设置串口参数；关闭串口；
**********************************************************/
ValveComObject::ValveComObject() : ComObject()
{
	m_valveCom = NULL;
}

ValveComObject::~ValveComObject()
{
	if(m_valveCom != NULL)
	{
		if(m_valveCom->isOpen())
		{
			m_valveCom->close();
		}
		delete m_valveCom;
	}
}

void ValveComObject::openValveControlCom(ComInfoStruct *comStruct)
{
	qDebug()<<"openValveControlCom thread:"<<QThread::currentThreadId();

	QString portName = comStruct->portName;// "COM2";//获取串口名
#ifdef Q_OS_LINUX
	m_valveCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_valveCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_valveCom, SIGNAL(readyRead()), this, SLOT(readValveControlComBuffer()));

	m_valveCom->setBaudRate((BaudRateType)comStruct->baudRate);// BAUD9600); //设置波特率  
	m_valveCom->setDataBits((DataBitsType)comStruct->dataBit);//DATA_8);   //设置数据位
	m_valveCom->setParity((ParityType)comStruct->parity);//PAR_EVEN);   //设置校验位
	m_valveCom->setStopBits((StopBitsType)comStruct->stopBit);//STOP_1);   //设置停止位
	m_valveCom->setFlowControl(FLOW_OFF); //设置数据流控制  
	m_valveCom->setTimeout(TIME_OUT);     //设置延时

	if(m_valveCom->open(QIODevice::ReadWrite))
	{
		qDebug()<<"Open SerialPort:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
	}
	else
	{
		qDebug()<<"Open SerialPort:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return;
	}
}

void ValveComObject::writeValveControlComBuffer(bool status)
{
	qDebug()<<"writeValveControlComBuffer thread:"<<QThread::currentThreadId();
	
	QByteArray buf;
	if (status) //打开阀门
	{
		buf.append(0x01);
	}
	else //关闭阀门
	{
		buf.append(0x02);
	}
	m_valveCom->write(buf);
}

void ValveComObject::readValveControlComBuffer()
{
	QByteArray tmp = m_valveCom->readAll();
	int num = tmp.size();
	UINT8 ch = (UINT8)tmp.at(0);
	qDebug()<<"readValveControlComBuffer thread:"<<QThread::currentThreadId()<<", Read data is:"<<ch;
	if (ch==0x01) //打开阀门成功
	{
		emit valveComIsAnalysed(true);
	}
	else if (ch==0x02) //关闭阀门成功
	{
		emit valveComIsAnalysed(false);
	}
// 	analyseFrame();
}

void ValveComObject::analyseFrame()
{
	qDebug()<<"ValveComObject::analyseFrame thread:"<<QThread::currentThreadId();
	int isOpen = 1;
	emit valveComIsAnalysed(isOpen);
}


/*********************************************************
类名：BalanceComObject
功能：天平串口类- 打开串口；设置串口参数；关闭串口；
**********************************************************/
BalanceComObject::BalanceComObject() : ComObject()
{
	m_balanceCom = NULL;

	m_balanceProtocol = new BalanceProtocol;

	m_sendContinue = true;
}

BalanceComObject::~BalanceComObject()
{
	if(m_balanceCom != NULL)
	{
		if(m_balanceCom->isOpen())
		{
			m_balanceCom->close();
		}
		delete m_balanceCom;
	}

	if (m_balanceProtocol)
	{
		delete m_balanceProtocol;
		m_balanceProtocol = NULL;
	}
}

void BalanceComObject::openBalanceCom(ComInfoStruct *comStruct)
{
	qDebug()<<"openBalanceCom thread:"<<QThread::currentThreadId();

	QString portName = comStruct->portName;// "COM2";//获取串口名
#ifdef Q_OS_LINUX
	m_balanceCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_balanceCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_balanceCom, SIGNAL(readyRead()), this, SLOT(readBalanceComBuffer()));

	m_balanceCom->setBaudRate((BaudRateType)comStruct->baudRate);// BAUD9600); //设置波特率  
	m_balanceCom->setDataBits((DataBitsType)comStruct->dataBit);//DATA_8);   //设置数据位
	m_balanceCom->setParity((ParityType)comStruct->parity);//PAR_EVEN);   //设置校验位
	m_balanceCom->setStopBits((StopBitsType)comStruct->stopBit);//STOP_1);   //设置停止位
	m_balanceCom->setFlowControl(FLOW_OFF); //设置数据流控制  
	m_balanceCom->setTimeout(TIME_OUT);     //设置延时

	if(m_balanceCom->open(QIODevice::ReadWrite)) 
	{
		qDebug()<<"Open SerialPort:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
	}
	else
	{
		qDebug()<<"Open SerialPort:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return;
	}

	QByteArray buf;
	buf.append(0x4E).append(0x20).append(0x20).append(0x20).append(0x20).append(0x20);
	buf.append(0x2D).append(0x31).append(0x32).append(0x33).append(0x34).append(0x2E).append(0x35).append(0x36).append(0x37).append(0x38);
	buf.append(0x20).append(0x6B).append(0x67).append(0x20).append(0x0D).append(0x0A);
	m_balanceCom->write(buf);

}

void BalanceComObject::writeBalanceComBuffer()
{
	UINT8 wg = 0x31;
	while(m_sendContinue)
	{
		QByteArray buf;
		buf.append(0x4E).append(0x20).append(0x20).append(0x20).append(0x20).append(0x20);
		buf.append(0x2D).append(wg++).append(0x38).append(0x37).append(0x36).append(0x2E).append(0x35).append(0x34).append(0x33).append(0x32);
		buf.append(0x20).append(0x6B).append(0x67).append(0x20).append(0x0D).append(0x0A);
		m_balanceCom->write(buf);
		QTest::qWait(1000);
	}
}

void BalanceComObject::readBalanceComBuffer()
{
	QByteArray tmp = m_balanceCom->readAll();
	qDebug()<<"readBalanceComBuffer thread:"<<QThread::currentThreadId()<<", Read data is:"<<tmp;

	bool ret = false;
	ret = m_balanceProtocol->readBalanceComBuffer(tmp); //通讯协议接口
	if (ret)
	{
		QString balStr = m_balanceProtocol->getBalanceValue();
		emit balanceValueIsReady(balStr);
	}
}

void BalanceComObject::setSendContinue(bool a)
{
	m_sendContinue = a;
}