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

#include "comobject.h"
#include "commondefine.h"

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
ComObject::ComObject(QObject* parent) : QObject(parent)
{
}

ComObject::~ComObject()
{
}


/************************************************
类名：TempComObject
功能：温度串口类- 打开串口；设置串口参数；关闭串口；
*************************************************/
TempComObject::TempComObject(QObject* parent) : ComObject(parent)
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
			qDebug()<<"m_tempCom closed";
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
		qDebug()<<"Open Temperature Com:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
	}
	else
	{
		qDebug()<<"Open Temperature Com:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return;
	}
}

//请求温度
void TempComObject::writeTemperatureComBuffer()
{
// 	qDebug()<<"TempComObject::writeTemperatureComBuffer thread:"<<QThread::currentThreadId();
	m_tempProtocol->makeSendBuf();
	QByteArray buf = m_tempProtocol->getSendBuf();
	m_tempCom->write(buf);
}

//读温度串口缓冲区
void TempComObject::readTemperatureComBuffer()
{
	QByteArray tmp = m_tempCom->readAll();
// 	qDebug()<<"read TemperatureComBuffer thread:"<<QThread::currentThreadId();

	bool ret = false;
	ret = m_tempProtocol->readTemperComBuffer(tmp); //通讯协议接口
	if (ret)
	{
		QString tempStr = m_tempProtocol->getTempStr();
		emit temperatureIsReady(tempStr);
	}
}


/*********************************************************
类名：ControlComObject
功能：控制串口类- 打开串口；设置串口参数；关闭串口；
**********************************************************/
ControlComObject::ControlComObject(QObject* parent) : ComObject(parent)
{
	m_controlCom = NULL;

	m_controlProtocol = NULL;
	m_controlProtocol = new ControlProtocol();

	m_conFrame = NULL;
	m_conFrame = new Con_Frame_Struct();
	memset(m_conFrame, 0, sizeof(Con_Frame_Struct));

	m_conTmp = "";
	m_balValue = "";
}

ControlComObject::~ControlComObject()
{
	if(m_controlCom != NULL)
	{
		if(m_controlCom->isOpen())
		{
			m_controlCom->close();
			qDebug()<<"m_controlCom closed";
		}
		delete m_controlCom;
	}

	if (m_controlProtocol != NULL)
	{
		delete m_controlProtocol;
		m_controlProtocol = NULL;
	}
}

void ControlComObject::openControlCom(ComInfoStruct *comStruct)
{
	qDebug()<<"openControlCom thread:"<<QThread::currentThreadId();

	QString portName = comStruct->portName; //获取串口名
#ifdef Q_OS_LINUX
	m_controlCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_controlCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_controlCom, SIGNAL(readyRead()), this, SLOT(readControlComBuffer()));

	m_controlCom->setBaudRate((BaudRateType)comStruct->baudRate); //设置波特率  
	m_controlCom->setDataBits((DataBitsType)comStruct->dataBit);  //设置数据位
	m_controlCom->setParity((ParityType)comStruct->parity);       //设置校验位
	m_controlCom->setStopBits((StopBitsType)comStruct->stopBit);  //设置停止位
	m_controlCom->setFlowControl(FLOW_OFF); //设置数据流控制  
	m_controlCom->setTimeout(TIME_OUT);     //设置延时

	if(m_controlCom->open(QIODevice::ReadWrite))
	{
		qDebug()<<"Open Control Com:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
	}
	else
	{
		qDebug()<<"Open Control Com:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return;
	}
}

//继电器控制
void ControlComObject::makeRelaySendBuf(UINT8 portno, bool status)
{
	qDebug()<<"makeRelaySendBuf thread:"<<QThread::currentThreadId();
	
	QByteArray buf;
	m_controlProtocol->makeRelaySendBuf(portno, status);
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//调节阀开度
void ControlComObject::makeRegulateSendBuf(UINT8 portno, int degree)
{
	QByteArray buf;
	m_controlProtocol->makeRegulateSendBuf(portno, degree);
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//查询从机状态
void ControlComObject::makeQuerySendBuf()
{
	QByteArray buf;
	m_controlProtocol->makeQuerySendBuf();
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

void ControlComObject::readControlComBuffer()
{
// 	qDebug()<<"readControlComBuffer ControlComObject thread:"<<QThread::currentThreadId();
	QDateTime begintime = QDateTime::currentDateTime();
	m_conTmp.append(m_controlCom->readAll());
	int num = m_conTmp.size();
	if (m_conTmp.at(num-1) != END_CODE) //一帧接收完毕
	{
		return;
	}
	
	UINT8 ret = 0x00;
	ret = m_controlProtocol->readControlComBuffer(m_conTmp);
	m_conTmp.clear(); //清零

	UINT8 portno;
	UINT8 st;
	bool status;
	if (ret == FUNC_RELAY) //继电器
	{
		portno = m_controlProtocol->getConFrame()->data[1];
		st = m_controlProtocol->getConFrame()->data[(portno-1)/8 + 2];
		status = st ? VALVE_OPEN : VALVE_CLOSE;
		emit controlRelayIsOk(portno, status);
		qDebug()<<"controlRelayIsOk"<<"\n";
	}
	else if (ret == FUNC_REGULATE) //调节阀
	{
		qDebug()<<"controlRegulateIsOk"<<"\n";
		emit controlRegulateIsOk();
	}
	else if (ret == FUNC_QUERY) //查询
	{
		m_conFrame = m_controlProtocol->getConFrame();
	}
	else if (ret == FUNC_BALANCE) //天平
	{
		m_balValue = m_controlProtocol->getBalanceValue();
		emit controlGetBalanceValueIsOk(m_balValue);
		QDateTime endtime = QDateTime::currentDateTime();
		UINT32 usedSec = begintime.msecsTo(endtime);
// 		qDebug()<<"读取天平数据，用时"<<usedSec<<"毫秒";
	}
}

/*********************************************************
类名：BalanceComObject
功能：天平串口类- 打开串口；设置串口参数；关闭串口；
**********************************************************/
BalanceComObject::BalanceComObject(QObject* parent) : ComObject(parent)
{
	m_balanceCom = NULL;

	m_balanceProtocol = new BalanceProtocol;

	m_balTmp = "";
}

BalanceComObject::~BalanceComObject()
{
	if(m_balanceCom != NULL)
	{
		if(m_balanceCom->isOpen())
		{
			m_balanceCom->close();
			qDebug()<<"m_balanceCom closed";
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
		qDebug()<<"Open Balance Com:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
	}
	else
	{
		qDebug()<<"Open Balance Com:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return;
	}

	QByteArray buf;
	buf.append(0x4E).append(0x20).append(0x20).append(0x20).append(0x20).append(0x20);
	buf.append(0x2D).append(0x31).append(0x32).append(0x33).append(0x34).append(0x2E).append(0x35).append(0x36).append(0x37).append(0x38);
	buf.append(0x20).append(0x6B).append(0x67).append(0x20).append(0x0D).append(0x0A);
	m_balanceCom->write(buf);

}

//读取天平串口数据
void BalanceComObject::readBalanceComBuffer()
{
	m_balTmp.append(m_balanceCom->readAll());
	int num = m_balTmp.size();

	if (num>=BAL_DATA_LENGTH && m_balTmp.at(num-1)==ASCII_LF && m_balTmp.at(num-2)==ASCII_CR ) //最后两个字节是回车符和换行符
	{
 		qDebug()<<"readBalanceComBuffer thread:"<<QThread::currentThreadId()<<", Read data is:"<<m_balTmp;

		bool ret = false;
		ret = m_balanceProtocol->readBalanceComBuffer(m_balTmp.right(BAL_DATA_LENGTH)); //通讯协议接口
		m_balTmp.clear();
		if (ret)
		{
			QString balStr = m_balanceProtocol->getBalanceValue();
			emit balanceValueIsReady(balStr);
		}
	}
}


/*********************************************************
类名：MeterComObject
功能：热量表串口类- 打开串口；设置串口参数；关闭串口；
**********************************************************/
MeterComObject::MeterComObject(QObject* parent) : ComObject(parent)
{

}

MeterComObject::~MeterComObject()
{
	if(m_meterCom != NULL)
	{
		if(m_meterCom->isOpen())
		{
			m_meterCom->close();
			qDebug()<<"m_meterCom1 closed";
		}
		delete m_meterCom;
	}
}

void MeterComObject::openMeterCom(ComInfoStruct *comStruct)
{
	QString portName = comStruct->portName; //获取串口名
	qDebug()<<"openMeterCom:"<<portName<<"thread:"<<QThread::currentThreadId();
#ifdef Q_OS_LINUX
	m_meterCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_meterCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_meterCom, SIGNAL(readyRead()), this, SLOT(readMeterComBuffer()));

	m_meterCom->setBaudRate((BaudRateType)comStruct->baudRate);  //设置波特率  
	m_meterCom->setDataBits((DataBitsType)comStruct->dataBit);   //设置数据位
	m_meterCom->setParity((ParityType)comStruct->parity);        //设置校验位
	m_meterCom->setStopBits((StopBitsType)comStruct->stopBit);   //设置停止位
	m_meterCom->setFlowControl(FLOW_OFF); //设置数据流控制  
	m_meterCom->setTimeout(TIME_OUT);     //设置延时

	if(m_meterCom->open(QIODevice::ReadWrite)) 
	{
		qDebug()<<"Open openMeter Com:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
	}
	else
	{
		qDebug()<<"Open Meter Com:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return;
	}
}

void MeterComObject::readMeterComBuffer()
{

}

void MeterComObject::writeMeterComBuffer()
{

}