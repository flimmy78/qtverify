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
#include <QtCore/QDateTime>

#include "comobject.h"
#include "commondefine.h"

/*
** 类名：ComThread
** 功能：线程管理类；开辟新线程
*/
ComThread::ComThread(QObject* parent) : QThread(parent)
{
	qDebug()<<"ComThread constructor thread:"<<currentThreadId();
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


/*
** 类名：ComObject
** 功能：串口操作基类
*/
ComObject::ComObject(QObject* parent) : QObject(parent)
{
}

ComObject::~ComObject()
{
}


/*
** 类名：TempComObject
** 功能：温度串口类- 打开串口；设置串口参数；关闭串口；
*/
TempComObject::TempComObject(QObject* parent) : ComObject(parent)
{
	m_tempCom = NULL;

	m_tempFrame = new Temp_Frame_Struct();
	memset(m_tempFrame, 0, sizeof(Temp_Frame_Struct));

	m_tempProtocol = new TempProtocol();

	m_buf.clear();
}

TempComObject::~TempComObject()
{
	if(m_tempCom != NULL)
	{
// 		if(m_tempCom->isOpen())
// 		{
			m_tempCom->close();
			qDebug()<<"m_tempCom :"<<m_tempCom->portName()<<" closed";
// 		}
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

bool TempComObject::openTemperatureCom(ComInfoStruct *comStruct)
{
// 	qDebug()<<"### openTemperatureCom thread:"<<QThread::currentThreadId();
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
		qDebug()<<"### OpenTemperatureCom:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
		return true;
	}
	else
	{
		qDebug()<<"### OpenTemperatureCom:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return false;
	}
}

//请求温度
void TempComObject::writeTemperatureComBuffer()
{
// 	qDebug()<<"TempComObject::writeTemperatureComBuffer thread:"<<QThread::currentThreadId();
	if (NULL==m_tempProtocol)
	{
		return;
	}
	m_tempProtocol->makeSendBuf();
	QByteArray buf = m_tempProtocol->getSendBuf();
// 	int size = buf.size();
// 	for (int i=0; i<size; i++)
// 	{
// 		printf("0x%.2x\n", (UINT8)buf.at(i));
// 	}
// 	printf("\n");
	m_tempCom->flush();
	m_tempCom->write(buf);
}

//读温度串口缓冲区
void TempComObject::readTemperatureComBuffer()
{
// 	qDebug()<<"TempComObject::readTemperatureComBuffer thread:"<<QThread::currentThreadId();
	if (NULL==m_tempCom)
	{
		return;
	}
	m_buf += m_tempCom->readAll();
	int num = m_buf.size();
	if (num < 10)
	{
		return;
	}
	bool ret = false;
	ret = m_tempProtocol->readTemperComBuffer(m_buf); //通讯协议接口
	if (ret)
	{
		QString tempStr = m_tempProtocol->getTempStr();
		emit temperatureIsReady(tempStr);
	}
	m_buf.clear();
	m_tempCom->flush();
}

/*
** 类名：ControlComObject
** 功能：控制串口类- 打开串口；设置串口参数；关闭串口；
*/
ControlComObject::ControlComObject(QObject* parent) : ComObject(parent)
{
	m_controlCom = NULL;

	m_controlProtocol = NULL;

	m_conFrame = NULL;
	m_conFrame = new NewCtrl_Frame_Struct();
	memset(m_conFrame, 0, sizeof(NewCtrl_Frame_Struct));

	m_conTmp = "";
	m_balValue = 0.0;

	setProtocolVersion(NEW_CTRL_VERSION); //默认新控制板协议
}

ControlComObject::~ControlComObject()
{
	if (m_controlCom != NULL)
	{
// 		if (m_controlCom->isOpen())
// 		{
			m_controlCom->close();
			qDebug()<<"m_controlCom :"<<m_controlCom->portName()<<" closed";
// 		}
		delete m_controlCom;
	}

	if (m_controlProtocol != NULL)
	{
		delete m_controlProtocol;
		m_controlProtocol = NULL;
	}

	if (m_conFrame)
	{
		delete m_conFrame;
		m_conFrame = NULL;
	}
}

//设置协议版本号
void ControlComObject::setProtocolVersion(int version)
{
	m_protocolVersion = version;
	if (m_controlProtocol != NULL)
	{
		delete m_controlProtocol;
		m_controlProtocol = NULL;
	}
	switch (m_protocolVersion)
	{
	case NEW_CTRL_VERSION: //新控制板协议
		m_controlProtocol = new NewCtrlProtocol();
		break;
	case OLD_CTRL_VERSION: //老控制板协议
		m_controlProtocol = new OldCtrlProtocol();
		break;
	default: 
		m_controlProtocol =  new NewCtrlProtocol();
		break;
	}

}

bool ControlComObject::openControlCom(ComInfoStruct *comStruct)
{
//	qDebug()<<"*** openControlCom thread:"<<QThread::currentThreadId();
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
		qDebug()<<"*** OpenControlCom:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
		return true;
	}
	else
	{
		qDebug()<<"*** OpenControlCom:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return false;
	}
}

/*
**	功能：控制继电器断开、闭合（即控制气动阀开、合）
**	输入参数：
		portno:继电器编号
		status: false(关闭阀门)；true(打开阀门)
*/
void ControlComObject::askControlRelay(UINT8 portno, bool status)
{
	qDebug()<<"ControlComObject::askControlRelay thread:"<<QThread::currentThreadId();
	if (NULL==m_controlProtocol)
	{
		return;
	}
	
	QByteArray buf;
	m_controlProtocol->makeFrameOfCtrlRelay(portno, status);
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//调节阀开度
void ControlComObject::askControlRegulate(UINT8 portno, int degree)
{
	if (NULL==m_controlProtocol)
	{
		return;
	}
	qDebug()<<"ControlComObject::askControlRegulate portno ="<<portno<<", degree ="<<degree;
	QByteArray buf;
	m_controlProtocol->makeFrameOfCtrlRegulate(portno, degree);
	buf = m_controlProtocol->getSendBuf();
	int size = buf.size();
	for (int i=0; i<size; i++)
	{
		printf("0x%.2X\n",(UINT8)buf.at(i));
	}
	m_controlCom->write(buf);
}

//查询从机状态
void ControlComObject::askControlQuery()
{
	if (NULL==m_controlProtocol)
	{
		return;
	}
	QByteArray buf;
	m_controlProtocol->makeFrameOfCtrlQuery();
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//控制水泵
void ControlComObject::askControlWaterPump(UINT8 portno, bool status)
{
	if (NULL==m_controlProtocol)
	{
		return;
	}
	QByteArray buf;
	m_controlProtocol->makeFrameOfCtrlWaterPump(portno, status);
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//设置变频器频率
void ControlComObject::askSetDriverFreq(int freq)
{
	if (NULL==m_controlProtocol)
	{
		return;
	}
	QByteArray buf;
	m_controlProtocol->makeFrameOfSetDriverFreq(freq);
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//读取控制板返回数据
void ControlComObject::readControlComBuffer()
{
	qDebug()<<"readControlComBuffer ControlComObject thread:"<<QThread::currentThreadId();
	
	switch (m_protocolVersion)
	{
	case NEW_CTRL_VERSION: //新控制板协议
		readNewControlComBuffer();
		break;
	case OLD_CTRL_VERSION: //老控制板协议
		
		break;
	default: 
		
		break;
	}
}

void ControlComObject::readNewControlComBuffer()
{
	qDebug()<<"readNewControlComBuffer ControlComObject thread:"<<QThread::currentThreadId();
	m_conTmp.append(m_controlCom->readAll());
	int num = m_conTmp.size();
	if (num <= 0)
	{
		return;
	}
	if (m_conTmp.at(num-1) != CTRL_END_CODE) //一帧接收完毕
	{
		return;
	}
	QDateTime begintime = QDateTime::currentDateTime();

	UINT8 ret = 0x00;
	NewCtrlProtocol * protocolObj = (NewCtrlProtocol *)m_controlProtocol;
	ret = protocolObj->readCtrlComBuffer(m_conTmp);
	m_conTmp.clear(); //清零

	UINT8 portno;
	UINT8 st;
	bool status;
	if (ret == CTRL_FUNC_RELAY) //继电器
	{
		portno = protocolObj->getConFrame()->data[1];
		st = protocolObj->getConFrame()->data[(portno-1)/8 + 2];
		status = st ? VALVE_OPEN : VALVE_CLOSE;
		emit controlRelayIsOk(portno, status);
		qDebug()<<"controlRelayIsOk"<<"\n";
	}
	else if (ret == CTRL_FUNC_REGULATE) //调节阀
	{
		qDebug()<<"controlRegulateIsOk"<<"\n";
		emit controlRegulateIsOk();
	}
	else if (ret == CTRL_FUNC_QUERY) //查询
	{
		m_conFrame = protocolObj->getConFrame();
	}
	else if (ret == CTRL_FUNC_BALANCE) //天平
	{
		m_balValue = protocolObj->getBalanceValue();
		emit controlGetBalanceValueIsOk(m_balValue);
		QDateTime endtime = QDateTime::currentDateTime();
// 		UINT32 usedSec = begintime.msecsTo(endtime);
// 		qDebug()<<"读取天平数据，用时"<<usedSec<<"毫秒";
	}
}

/*
** 类名：BalanceComObject
** 功能：天平串口类- 打开串口；设置串口参数；关闭串口；
*/
BalanceComObject::BalanceComObject(QObject* parent) : ComObject(parent)
{
	m_balanceCom = NULL;

	m_balanceProtocol = new BalanceProtocol;

	m_balTimer = new QTimer();
}

BalanceComObject::~BalanceComObject()
{
	if(m_balanceCom != NULL)
	{
// 		if(m_balanceCom->isOpen())
// 		{
			m_balanceCom->close();
			qDebug()<<"m_balanceCom :"<<m_balanceCom->portName()<<" closed";
// 		}
		delete m_balanceCom;
	}

	if (m_balanceProtocol)
	{
		delete m_balanceProtocol;
		m_balanceProtocol = NULL;
	}

	if (m_balTimer) 
	{
		if (m_balTimer->isActive())
		{
			m_balTimer->stop();
		}
		delete m_balTimer;
		m_balTimer = NULL;
	}
}

bool BalanceComObject::openBalanceCom(ComInfoStruct *comStruct)
{
// 	qDebug()<<"$$$ openBalanceCom thread:"<<QThread::currentThreadId();
	QString portName = comStruct->portName;// "COM2";//获取串口名
#ifdef Q_OS_LINUX
	m_balanceCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
// 	m_balanceCom = new QextSerialPort(portName, QextSerialPort::EventDriven); //事件驱动方式
	m_balanceCom = new QextSerialPort(portName, QextSerialPort::Polling); //查询方式
#endif
// 	connect(m_balanceCom, SIGNAL(readyRead()), this, SLOT(readBalanceComBuffer()));
	connect(m_balTimer, SIGNAL(timeout()), this, SLOT(readBalanceComBuffer()));

	m_balanceCom->setBaudRate((BaudRateType)comStruct->baudRate);// BAUD9600); //设置波特率  
	m_balanceCom->setDataBits((DataBitsType)comStruct->dataBit);//DATA_8);   //设置数据位
	m_balanceCom->setParity((ParityType)comStruct->parity);//PAR_EVEN);   //设置校验位
	m_balanceCom->setStopBits((StopBitsType)comStruct->stopBit);//STOP_1);   //设置停止位
	m_balanceCom->setFlowControl(FLOW_OFF); //设置数据流控制  
	m_balanceCom->setTimeout(TIME_OUT);     //设置延时

	if(m_balanceCom->open(QIODevice::ReadWrite)) 
	{
		qDebug()<<"$$$ OpenBalanceCom:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
/*
		QByteArray buf;
		buf.append(0x4E).append(0x20).append(0x20).append(0x20).append(0x20).append(0x20);
		buf.append(0x2D).append(0x31).append(0x32).append(0x33).append(0x34).append(0x2E).append(0x35).append(0x36).append(0x37).append(0x38);
		buf.append(0x20).append(0x6B).append(0x67).append(0x20).append(0x0D).append(0x0A);
		m_balanceCom->write(buf);
*/
		m_balTimer->start(TIMEOUT_BALANCE); //每200毫秒查询一次天平数据
		return true;
	}
	else
	{
		qDebug()<<"$$$ OpenBalanceCom:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return false;
	}
}

//读取天平串口数据
void BalanceComObject::readBalanceComBuffer()
{
// 	qDebug()<<"BalanceComObject::readBalanceComBuffer thread:"<<QThread::currentThreadId();
	if (NULL==m_balanceCom)
	{
		return;
	}
	QByteArray balBuffer = m_balanceCom->readAll();
// 	qDebug()<<"balBuffer.size() ="<<balBuffer.size();
// 	qDebug()<<"read data is:"<<balBuffer;
// 	for (int i=0;i<balBuffer.size();i++)
// 	{
// 		printf("0x%02X ", (uchar)balBuffer.at(i));
// 	}
// 	printf("\n");
	bool ret = false;
	ret = m_balanceProtocol->readBalanceComBuffer(balBuffer);//通讯协议接口
	if (ret)
	{
		float balValue = m_balanceProtocol->getBalanceValue();
		emit balanceValueIsReady(balValue);
	}
}

/*
** 设置天平类型
*/
void BalanceComObject::setBalanceType(int balType)
{
	if (m_balanceProtocol != NULL)
	{
		delete m_balanceProtocol;
		m_balanceProtocol = NULL;
	}
	switch (balType)
	{
	case BALANCE_TYPE_Satorius:	//赛多利斯
		m_balanceProtocol = new BalSatoriusProtocol();
		break;
	case BALANCE_TYPE_SatoriusH: //赛多利斯H
		m_balanceProtocol = new BalSatoriusHProtocol();
		break;
	case BALANCE_TYPE_Bizerba: //碧彩
		m_balanceProtocol = new BalBizerbaProtocol();
		break;
	case BALANCE_TYPE_Mettler: //Mettler Toledo
		m_balanceProtocol = new BalMettlerProtocol();
		break;
	default: 
		m_balanceProtocol =  new BalSatoriusProtocol();
		break;
	}
}


/*
** 类名：MeterComObject
** 功能：热量表串口类- 打开串口；设置串口参数；关闭串口；
*/
MeterComObject::MeterComObject(QObject* parent) : ComObject(parent)
{
	m_meterCom = NULL;
	m_meterProtocol = NULL;                                                                                                                    
	m_meterTmp="";
	m_portName = "";

	setProtocolVersion(PROTOCOL_VER_DELU); //默认是德鲁热量表
}

MeterComObject::~MeterComObject()
{
	if (m_meterCom != NULL)
	{
// 		if (m_meterCom->isOpen())
// 		{
			m_meterCom->close();
			qDebug()<<"m_meterCom :"<<m_meterCom->portName()<<" closed";
// 		}
		delete m_meterCom;
	}

	if (m_meterProtocol != NULL)
	{
		delete m_meterProtocol;
		m_meterProtocol = NULL;
	}
}

void MeterComObject::setProtocolVersion(int version)
{
	m_protocolVersion = version;
	if (m_meterProtocol != NULL)
	{
		delete m_meterProtocol;
		m_meterProtocol = NULL;
	}
	switch (m_protocolVersion)
	{
	case PROTOCOL_VER_COMMON:	//通用协议
	case PROTOCOL_VER_DELU:	    //德鲁超声波表
	case PROTOCOL_VER_TIANGANG: //天罡超声波表
	case PROTOCOL_VER_RUINA:    //瑞纳超声波表
		m_meterProtocol = new DeluMeterProtocol();
		break;
	case PROTOCOL_VER_LICHSONIC: //力创超声波表
		m_meterProtocol = new LiChMeterProtocol();
		break;
	case PROTOCOL_VER_HUIZH: //汇中超声波表
		m_meterProtocol = new HuiZhongMeterProtocol();
		break;
	default: 
		m_meterProtocol =  new DeluMeterProtocol();
		break;
	}
}

/*
** 打开串口，初始化串口参数等
*/
bool MeterComObject::openMeterCom(ComInfoStruct *comStruct)
{
// 	qDebug()<<"!!! openMeterCom:"<<m_portName<<"thread:"<<QThread::currentThreadId();
	m_portName = comStruct->portName; //获取串口名
#ifdef Q_OS_LINUX
	m_meterCom = new QextSerialPort("/dev/" + m_portName);
#elif defined (Q_OS_WIN)
	m_meterCom = new QextSerialPort(m_portName, QextSerialPort::EventDriven);
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
		qDebug()<<"!!! openMeterCom:"<<m_portName<<"Success!"<<" thread id:"<<QThread::currentThreadId();
		return true;
	}
	else
	{
		qDebug()<<"!!! openMeterCom:"<<m_portName<<"Failed!"<<" thread id:"<<QThread::currentThreadId();
		return false;
	}
}

//关闭串口
void MeterComObject::closeMeterCom()
{
	m_meterCom->close();
}

/*
** 解析串口返回数据
*/
void MeterComObject::readMeterComBuffer()
{
	if (NULL==m_meterCom)
	{
		return;
	}
	m_meterTmp.append(m_meterCom->readAll());
	int idx = m_meterTmp.indexOf(METER_START_CODE); //起始符
	if (idx < 0)
	{
		return;
	}
	int num = m_meterTmp.size();
	if (num <= idx + 10)
	{
		return;
	}
	UINT8 datalen = (UINT8)m_meterTmp.at(10+idx);
	int framelen = idx + 13 + datalen;
	if (num < framelen || m_meterTmp.at(num-1) !=  METER_END_CODE) //一帧接收完毕
	{
		return;
	}

	qDebug()<<m_meterCom->portName()<<"readMeterComBuffer MeterComObject thread:"<<QThread::currentThreadId();
	qDebug()<<m_meterCom->portName()<<"read"<<m_meterTmp.size()<<"bytes!";
	QDateTime begintime = QDateTime::currentDateTime();
	qDebug()<<"begintime:"<<begintime.toString("yyyy-MM-dd HH:mm:ss.zzz");
	UINT8 ret = 0x00;
	if (NULL==m_meterProtocol)
	{
		return;
	}
	ret = m_meterProtocol->readMeterComBuffer(m_meterTmp);
	m_meterTmp.clear(); //清零

	QString meterNo;
	QString flow, heat;
	QString tempIn, tempOut, date;
	QString bigCoe,mid2Coe,mid1Coe,smallCoe;
	if (ret == 1) //解帧成功
	{
		//表号
		meterNo = m_meterProtocol->getFullMeterNo();
		emit readMeterNoIsOK(m_portName, meterNo);

		//流量、热量
		flow = m_meterProtocol->getFlow();
		emit readMeterFlowIsOK(m_portName, flow);

		//热量
		heat = m_meterProtocol->getHeat();
		emit readMeterHeatIsOK(m_portName, heat);

		//进出水温度
		tempIn = m_meterProtocol->getInTemper();
		tempOut = m_meterProtocol->getOutTemper();
		emit readMeterTemperIsOK(m_portName, tempIn, tempOut);

		//热表日期
		date = m_meterProtocol->getDate();
		emit readMeterDateIsOK(m_portName, date);

		//大流量系数
		bigCoe = m_meterProtocol->getBigCoe();
		emit readMeterBigCoeIsOK(m_portName, bigCoe);

		//中流2流量系数
		mid2Coe = m_meterProtocol->getMid2Coe();
		emit readMeterMid2CoeIsOK(m_portName, mid2Coe);

		//中流1流量系数
		mid1Coe = m_meterProtocol->getMid1Coe();
		emit readMeterMid1CoeIsOK(m_portName, mid1Coe);

		//小流量系数
		smallCoe = m_meterProtocol->getSmallCoe();
		emit readMeterSmallCoeIsOK(m_portName, smallCoe);

		QDateTime endtime = QDateTime::currentDateTime();
		qDebug()<<"endtime:  "<<endtime.toString("yyyy-MM-dd HH:mm:ss.zzz");
		UINT32 usedSec = begintime.msecsTo(endtime);
		qDebug()<<"解析热量表数据，用时"<<usedSec<<"毫秒";
	}
}

/*
** 请求读表号
*/
void MeterComObject::askReadMeterNO()
{
	qDebug()<<"111 MeterComObject askReadMeterNo thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfReadMeterNO();
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** 请求读表流量系数
*/
void MeterComObject::askReadMeterFlowCoe()
{
	qDebug()<<"111 MeterComObject askReadMeterFlowCoe thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfReadMeterFlowCoe();
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** 请求读表（广播地址读表）
** 输入参数 vType: 检定类型
				0：流量检定
				1：热量检定
*/
void MeterComObject::askReadMeterData(int vType)
{
	qDebug()<<"111 MeterComObject askReadMeterData thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfReadMeterData();
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** 请求设置进入检定状态
** 输入参数 vType: 检定类型
				0：流量检定
				1：热量检定
*/
void MeterComObject::askSetVerifyStatus(int vType)
{
	qDebug()<<"111 MeterComObject askSetVerifyStatus thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfSetVerifyStatus(vType);
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** 请求修改表号(14位表号)
*/
void MeterComObject::askModifyMeterNO(QString oldMeterNo, QString newMeterNo)
{
	qDebug()<<"111 MeterComObject askModifyMeterNO thread:"<<QThread::currentThreadId();
	qDebug()<<"oldMeterNo:"<<oldMeterNo<<", newMeterNo:"<<newMeterNo;
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfModifyMeterNo(oldMeterNo, newMeterNo);
	QByteArray buf = m_meterProtocol->getSendFrame();
/*
	int num = buf.size();
	qDebug()<<"buf size ="<<num;
	for (int i=0; i<buf.size(); i++)
	{
		qDebug()<<"请求修改表号："<<(UINT8)buf.at(i);
	}
*/	
	m_meterCom->write(buf);
}

/*
** 请求修改流量参数
*/
void MeterComObject::askModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr)
{
	qDebug()<<"111 MeterComObject askModifyFlowCoe thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	qDebug()<<"askModifyFlowCoe"<<meterNO<<bigErr<<mid2Err<<mid1Err<<smallErr;
	m_meterProtocol->makeFrameOfModifyFlowCoe(meterNO, bigErr, mid2Err, mid1Err, smallErr);
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** 请求修改流量参数
*/
void MeterComObject::askModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr, MeterCoe_PTR oldCoe)
{
	qDebug()<<"222 MeterComObject askModifyFlowCoe thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	qDebug()<<"askModifyFlowCoe newErr:"<<meterNO<<bigErr<<mid2Err<<mid1Err<<smallErr;
	qDebug()<<"askModifyFlowCoe oldCoe:"<<meterNO<<oldCoe->bigCoe<<oldCoe->mid2Coe<<oldCoe->mid1Coe<<oldCoe->smallCoe;
	m_meterProtocol->makeFrameOfModifyFlowCoe(meterNO, bigErr, mid2Err, mid1Err, smallErr, oldCoe);
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** 类名：StdTempComObject
** 功能：Sti1062a温度串口类-打开串口;设置串口参数；关闭串口；
*/
StdTempComObject::StdTempComObject(QObject* parent) : ComObject(parent)
{
	m_tempCom = NULL;
	m_stdTempProtocol = NULL;
}

StdTempComObject::~StdTempComObject()
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

	if (m_stdTempProtocol != NULL)
	{
		delete m_stdTempProtocol;
		m_stdTempProtocol = NULL;
	}
}

void StdTempComObject::setStdTempVersion(int version)
{
	if (m_stdTempProtocol)
	{
		delete m_stdTempProtocol;
		m_stdTempProtocol = NULL;
	}

	switch (version)
	{
	case TEMPERATURE_TYPE_METROLOGY:
		break;
	case TEMPERATURE_TYPE_WEILI:
		m_stdTempProtocol = new sti1062ATempProtocol();
		break;
	case TEMPERATURE_TYPE_HUAYI:
		break;
	default:
		m_stdTempProtocol = new sti1062ATempProtocol();
		break;
	}
}

bool StdTempComObject::openTemperatureCom(ComInfoStruct *comStruct)
{
// 	qDebug()<<"&&& open Sti1062aTemperatureCom thread:"<<QThread::currentThreadId();
	QString portName = comStruct->portName;// "COM2", 获取串口名
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
		qDebug()<<"&&& Open Sti1062aTemperatureCom:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
		return true;
	}
	else
	{
		qDebug()<<"&&& Open Sti1062aTemperatureCom:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return false;
	}
}

//请求温度
void StdTempComObject::writeStdTempComBuffer(stdTempCommand command)
{
	m_stdTempProtocol->makeSendBuf(command);
	m_tempCom->write(m_stdTempProtocol->getSendBuf());
}

//读温度串口缓冲区
void StdTempComObject::readTemperatureComBuffer()
{
	QByteArray tmp = m_tempCom->readAll();

	bool ret = false;
	ret = m_stdTempProtocol->readTemperComBuffer(tmp); //通讯协议接口
	if (ret)
	{
		m_tempCom->flush();
		QString tempStr = m_stdTempProtocol->getReadStr();
		emit temperatureIsReady(tempStr);
	}
	//if (m_sti1062aProtocol->readTemperComBuffer(m_tempCom->readAll()))
	//{
	//	m_tempCom->flush();
	//	emit temperatureIsReady(m_sti1062aProtocol->getReadStr());
	//}
}

void StdTempComObject::close()
{
	m_tempCom->close();
}
/*
** StdTempComObject END
*/

/*
** 类名：lcModRtuComObject
** 功能：力创ModRtu通讯串口类, 用于读取西门子电磁
** 流量计脉冲数
*/
lcModRtuComObject::lcModRtuComObject(QObject* parent) : ComObject(parent)
{
	m_lcModCom = NULL;
	m_lcModProtocol = new lcModbusRTUProtocol();

	//m_int=0;
}

lcModRtuComObject::~lcModRtuComObject()
{
	if (m_lcModCom != NULL)
	{
		if(m_lcModCom->isOpen())
		{
			m_lcModCom->close();
			qDebug()<<m_lcModCom->portName()<<" m_lcModCom closed";
		}
		delete m_lcModCom;
	}

	if (m_lcModProtocol != NULL)
	{
		delete m_lcModProtocol;
		m_lcModProtocol = NULL;
	}
}

bool lcModRtuComObject::openLcModCom(ComInfoStruct *comStruct)
{
	qDebug()<<"open lcModRtu thread:"<<QThread::currentThreadId();

	QString portName = comStruct->portName;// "COM2", 获取串口名
#ifdef Q_OS_LINUX
	m_lcModCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_lcModCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_lcModCom, SIGNAL(readyRead()), this, SLOT(readLcModComBuffer()));

	m_lcModCom->setBaudRate((BaudRateType)comStruct->baudRate);// BAUD9600); //设置波特率  
	m_lcModCom->setDataBits((DataBitsType)comStruct->dataBit); //DATA_8);    //设置数据位
	m_lcModCom->setParity((ParityType)comStruct->parity);	  //PAR_EVEN);  //设置校验位
	m_lcModCom->setStopBits((StopBitsType)comStruct->stopBit); //STOP_1);    //设置停止位
	m_lcModCom->setFlowControl(FLOW_OFF); //设置数据流控制  
	m_lcModCom->setTimeout(TIME_OUT);     //设置延时

	if(m_lcModCom->open(QIODevice::ReadWrite))
	{
		qDebug()<<"Open lcModRtu Com:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
		return true;
	}
	else
	{
		qDebug()<<"Open lcModRtu Com:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return false;
	}
}

void lcModRtuComObject::writeLcModComBuffer(lcModSendCmd command)
{
	m_lcModProtocol->makeSendBuf(command.address, command.func, command.start, command.regCount);
	m_lcModCom->write(m_lcModProtocol->getSendBuf());
}

void lcModRtuComObject::modify9150ACombuf(lcMod9150AWriteCmd cmd)
{
	m_lcModProtocol->makeWriteBuf(cmd);
	m_lcModCom->write(m_lcModProtocol->getWriteBuf());
}

//address: 力创模块的设备地址
void lcModRtuComObject::ask9150A16RoutesCmd(uchar address)
{
	lcModSendCmd command;
	command.address = address;
	command.func = read_multi_reg;
	command.start = EDA_9150A_START_REG;
	command.regCount = (EDA_9150A_ROUTE_CNT*EDA9150A_ROUTE_BYTES)/LC_EDA_REG_BYTES;//总共的寄存器数量
	writeLcModComBuffer(command);
}

void lcModRtuComObject::ask9150ARouteI(int i, uchar address)
{
	lcModSendCmd command;
	command.address = address;
	command.func = read_multi_reg;
	command.start = EDA_9150A_START_REG + 2*i;//一个寄存器2个字节
	command.regCount = (EDA9150A_ROUTE_BYTES/LC_EDA_REG_BYTES);//一个通道对应两个寄存器
	writeLcModComBuffer(command);
}

void lcModRtuComObject::ask9150ARouteL(UINT16 len, uchar address)
{
	lcModSendCmd command;
	command.address = address;
	command.func = read_multi_reg;
	command.start = EDA_9150A_START_REG;//一个寄存器2个字节
	command.regCount = (EDA9150A_ROUTE_BYTES/LC_EDA_REG_BYTES)*len;//一个通道对应两个寄存器
	writeLcModComBuffer(command);
}

void lcModRtuComObject::ask901712RoutesCmd(uchar address)
{
	lcModSendCmd command;
	command.address = address;
	command.func = read_multi_reg;
	command.start = EDA_9017_START_REG;
	command.regCount = (EDA_9017_ROUTE_CNT*EDA9017_ROUTE_BYTES)/LC_EDA_REG_BYTES;//总共的寄存器数量
	writeLcModComBuffer(command);
}

void lcModRtuComObject::readLcModComBuffer()
{
	QByteArray tmp = m_lcModCom->readAll();
	bool ret = m_lcModProtocol->readMeterComBuffer(tmp); //通讯协议接口
	if (ret)
	{
		m_lcModCom->flush();
		QByteArray valueArray = m_lcModProtocol->getReadVale();
		emit lcModValueIsReady(valueArray);
	}
}

void lcModRtuComObject::close()
{
	m_lcModCom->close();
}
/*
** lcModRtuComObject END
*/