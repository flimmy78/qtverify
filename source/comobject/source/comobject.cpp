/***********************************************
**  �ļ���:     comthread.cpp
**  ����:       �̹߳����༰���ڹ�����
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/14
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:   2014-6-14�����¶ȴ��ڹ�����
                2014-6-17������ƽ���ڹ�����
***********************************************/

#include <QtCore/QDebug>
#include <QtTest/QTest>

#include "comobject.h"
#include "commondefine.h"

/************************************************
������ComThread
���ܣ��̹߳����ࣻ�������߳�
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
	exec(); //���뱾�̵߳���Ϣѭ��
}   


/************************************************
������ComObject
���ܣ����ڲ�������
*************************************************/
ComObject::ComObject(QObject* parent) : QObject(parent)
{
}

ComObject::~ComObject()
{
}


/************************************************
������TempComObject
���ܣ��¶ȴ�����- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
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

	QString portName = comStruct->portName;// "COM2";//��ȡ������
#ifdef Q_OS_LINUX
	m_tempCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_tempCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_tempCom, SIGNAL(readyRead()), this, SLOT(readTemperatureComBuffer()));

	m_tempCom->setBaudRate((BaudRateType)comStruct->baudRate);// BAUD9600); //���ò�����  
	m_tempCom->setDataBits((DataBitsType)comStruct->dataBit); //DATA_8);    //��������λ
	m_tempCom->setParity((ParityType)comStruct->parity);	  //PAR_EVEN);  //����У��λ
	m_tempCom->setStopBits((StopBitsType)comStruct->stopBit); //STOP_1);    //����ֹͣλ
	m_tempCom->setFlowControl(FLOW_OFF); //��������������  
	m_tempCom->setTimeout(TIME_OUT);     //������ʱ

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

//�����¶�
void TempComObject::writeTemperatureComBuffer()
{
// 	qDebug()<<"TempComObject::writeTemperatureComBuffer thread:"<<QThread::currentThreadId();
	m_tempProtocol->makeSendBuf();
	QByteArray buf = m_tempProtocol->getSendBuf();
	m_tempCom->write(buf);
}

//���¶ȴ��ڻ�����
void TempComObject::readTemperatureComBuffer()
{
	QByteArray tmp = m_tempCom->readAll();
// 	qDebug()<<"read TemperatureComBuffer thread:"<<QThread::currentThreadId();

	bool ret = false;
	ret = m_tempProtocol->readTemperComBuffer(tmp); //ͨѶЭ��ӿ�
	if (ret)
	{
		QString tempStr = m_tempProtocol->getTempStr();
		emit temperatureIsReady(tempStr);
	}
}


/*********************************************************
������ControlComObject
���ܣ����ƴ�����- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
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

	QString portName = comStruct->portName; //��ȡ������
#ifdef Q_OS_LINUX
	m_controlCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_controlCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_controlCom, SIGNAL(readyRead()), this, SLOT(readControlComBuffer()));

	m_controlCom->setBaudRate((BaudRateType)comStruct->baudRate); //���ò�����  
	m_controlCom->setDataBits((DataBitsType)comStruct->dataBit);  //��������λ
	m_controlCom->setParity((ParityType)comStruct->parity);       //����У��λ
	m_controlCom->setStopBits((StopBitsType)comStruct->stopBit);  //����ֹͣλ
	m_controlCom->setFlowControl(FLOW_OFF); //��������������  
	m_controlCom->setTimeout(TIME_OUT);     //������ʱ

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

//�̵�������
void ControlComObject::makeRelaySendBuf(UINT8 portno, bool status)
{
	qDebug()<<"makeRelaySendBuf thread:"<<QThread::currentThreadId();
	
	QByteArray buf;
	m_controlProtocol->makeRelaySendBuf(portno, status);
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//���ڷ�����
void ControlComObject::makeRegulateSendBuf(UINT8 portno, int degree)
{
	QByteArray buf;
	m_controlProtocol->makeRegulateSendBuf(portno, degree);
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//��ѯ�ӻ�״̬
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
	if (m_conTmp.at(num-1) != END_CODE) //һ֡�������
	{
		return;
	}
	
	UINT8 ret = 0x00;
	ret = m_controlProtocol->readControlComBuffer(m_conTmp);
	m_conTmp.clear(); //����

	UINT8 portno;
	UINT8 st;
	bool status;
	if (ret == FUNC_RELAY) //�̵���
	{
		portno = m_controlProtocol->getConFrame()->data[1];
		st = m_controlProtocol->getConFrame()->data[(portno-1)/8 + 2];
		status = st ? VALVE_OPEN : VALVE_CLOSE;
		emit controlRelayIsOk(portno, status);
		qDebug()<<"controlRelayIsOk"<<"\n";
	}
	else if (ret == FUNC_REGULATE) //���ڷ�
	{
		qDebug()<<"controlRegulateIsOk"<<"\n";
		emit controlRegulateIsOk();
	}
	else if (ret == FUNC_QUERY) //��ѯ
	{
		m_conFrame = m_controlProtocol->getConFrame();
	}
	else if (ret == FUNC_BALANCE) //��ƽ
	{
		m_balValue = m_controlProtocol->getBalanceValue();
		emit controlGetBalanceValueIsOk(m_balValue);
		QDateTime endtime = QDateTime::currentDateTime();
		UINT32 usedSec = begintime.msecsTo(endtime);
// 		qDebug()<<"��ȡ��ƽ���ݣ���ʱ"<<usedSec<<"����";
	}
}

/*********************************************************
������BalanceComObject
���ܣ���ƽ������- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
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

	QString portName = comStruct->portName;// "COM2";//��ȡ������
#ifdef Q_OS_LINUX
	m_balanceCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_balanceCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_balanceCom, SIGNAL(readyRead()), this, SLOT(readBalanceComBuffer()));

	m_balanceCom->setBaudRate((BaudRateType)comStruct->baudRate);// BAUD9600); //���ò�����  
	m_balanceCom->setDataBits((DataBitsType)comStruct->dataBit);//DATA_8);   //��������λ
	m_balanceCom->setParity((ParityType)comStruct->parity);//PAR_EVEN);   //����У��λ
	m_balanceCom->setStopBits((StopBitsType)comStruct->stopBit);//STOP_1);   //����ֹͣλ
	m_balanceCom->setFlowControl(FLOW_OFF); //��������������  
	m_balanceCom->setTimeout(TIME_OUT);     //������ʱ

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

//��ȡ��ƽ��������
void BalanceComObject::readBalanceComBuffer()
{
	m_balTmp.append(m_balanceCom->readAll());
	int num = m_balTmp.size();

	if (num>=BAL_DATA_LENGTH && m_balTmp.at(num-1)==ASCII_LF && m_balTmp.at(num-2)==ASCII_CR ) //��������ֽ��ǻس����ͻ��з�
	{
 		qDebug()<<"readBalanceComBuffer thread:"<<QThread::currentThreadId()<<", Read data is:"<<m_balTmp;

		bool ret = false;
		ret = m_balanceProtocol->readBalanceComBuffer(m_balTmp.right(BAL_DATA_LENGTH)); //ͨѶЭ��ӿ�
		m_balTmp.clear();
		if (ret)
		{
			QString balStr = m_balanceProtocol->getBalanceValue();
			emit balanceValueIsReady(balStr);
		}
	}
}


/*********************************************************
������MeterComObject
���ܣ�����������- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
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
	QString portName = comStruct->portName; //��ȡ������
	qDebug()<<"openMeterCom:"<<portName<<"thread:"<<QThread::currentThreadId();
#ifdef Q_OS_LINUX
	m_meterCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_meterCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_meterCom, SIGNAL(readyRead()), this, SLOT(readMeterComBuffer()));

	m_meterCom->setBaudRate((BaudRateType)comStruct->baudRate);  //���ò�����  
	m_meterCom->setDataBits((DataBitsType)comStruct->dataBit);   //��������λ
	m_meterCom->setParity((ParityType)comStruct->parity);        //����У��λ
	m_meterCom->setStopBits((StopBitsType)comStruct->stopBit);   //����ֹͣλ
	m_meterCom->setFlowControl(FLOW_OFF); //��������������  
	m_meterCom->setTimeout(TIME_OUT);     //������ʱ

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