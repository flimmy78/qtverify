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
**  更新记录:
***********************************************/

#include <QtCore/QDebug>
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
	m_tempCom->setDataBits((DataBitsType)comStruct->dataBit);//DATA_8);   //设置数据位
	m_tempCom->setParity((ParityType)comStruct->parity);//PAR_EVEN);   //设置校验位
	m_tempCom->setStopBits((StopBitsType)comStruct->stopBit);//STOP_1);   //设置停止位
	m_tempCom->setFlowControl(FLOW_OFF); //设置数据流控制  
	m_tempCom->setTimeout(TIME_OUT);     //设置延时

	if(m_tempCom->open(QIODevice::ReadWrite))
	{
// 		QMessageBox::information(this, tr("Open Success"), tr("Open SerialPort ") + portName + tr(" Success!"), QMessageBox::Ok);
		qDebug()<<"Open SerialPort:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
	}
	else
	{
// 		QMessageBox::critical(this, tr("Open Failed"), tr("Can't Open SerialPort ") + portName + tr("\nDevice isn't exist or is occupied!"), QMessageBox::Ok);
		qDebug()<<"Open SerialPort:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return;
	}

	m_tempCom->write("Temp com");
}

void TempComObject::readTemperatureComBuffer()
{
	QByteArray temp = m_tempCom->readAll();
	qDebug()<<"readTemperatureComBuffer thread:"<<QThread::currentThreadId()<<", Read data is:"<<temp;
	analyseFrame();
}

void TempComObject::analyseFrame()
{
	qDebug()<<"TempComObject::analyseFrame thread:"<<QThread::currentThreadId();

	float tempValue = 66.68;
	QString tempStr;
	tempStr.setNum(tempValue, 'f', 2);
	emit tempComIsAnalysed(tempStr);
}

/************************************************
类名：ValveComObject
功能：阀门控制串口类- 打开串口；设置串口参数；关闭串口；
*************************************************/
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
	m_tempCom = new QextSerialPort("/dev/" + portName);
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
// 		QMessageBox::information(this, tr("Open Success"), tr("Open SerialPort ") + portName + tr(" Success!"), QMessageBox::Ok);
		qDebug()<<"Open SerialPort:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
	}
	else
	{
// 		QMessageBox::critical(this, tr("Open Failed"), tr("Can't Open SerialPort ") + portName + tr("\nDevice isn't exist or is occupied!"), QMessageBox::Ok);
		qDebug()<<"Open SerialPort:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return;
	}

	m_valveCom->write("test valve");
}

void ValveComObject::writeValveControlComBuffer()
{
	qDebug()<<"writeValveControlComBuffer thread:"<<QThread::currentThreadId();
	m_valveCom->write("write Valve Com");
}

void ValveComObject::readValveControlComBuffer()
{
	QByteArray temp = m_valveCom->readAll();
	qDebug()<<"readValveControlComBuffer thread:"<<QThread::currentThreadId()<<", Read data is:"<<temp;
	analyseFrame();
}
void ValveComObject::analyseFrame()
{
	qDebug()<<"ValveComObject::analyseFrame thread:"<<QThread::currentThreadId();
	int isOpen = 0;
	emit valveComIsAnalysed(isOpen);
}
