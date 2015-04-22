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

/*
** ������ComThread
** ���ܣ��̹߳����ࣻ�������߳�
*/
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


/*
** ������ComObject
** ���ܣ����ڲ�������
*/
ComObject::ComObject(QObject* parent) : QObject(parent)
{
}

ComObject::~ComObject()
{
}


/*
** ������TempComObject
** ���ܣ��¶ȴ�����- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
*/
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

bool TempComObject::openTemperatureCom(ComInfoStruct *comStruct)
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
		return true;
	}
	else
	{
		qDebug()<<"Open Temperature Com:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return false;
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


/*
** ������ControlComObject
** ���ܣ����ƴ�����- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
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

	setProtocolVersion(NEW_CTRL_VERSION); //Ĭ���¿��ư�Э��
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
	case NEW_CTRL_VERSION: //�¿��ư�Э��
		m_controlProtocol = new NewCtrlProtocol();
		break;
	case OLD_CTRL_VERSION: //�Ͽ��ư�Э��
		m_controlProtocol = new OldCtrlProtocol();
		break;
	default: 
		m_controlProtocol =  new NewCtrlProtocol();
		break;
	}

}

bool ControlComObject::openControlCom(ComInfoStruct *comStruct)
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
		return true;
	}
	else
	{
		qDebug()<<"Open Control Com:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return false;
	}
}

/*
**	���ܣ����Ƽ̵����Ͽ����պϣ������������������ϣ�
**	���������
		portno:�̵������
		status: false(�رշ���)��true(�򿪷���)
*/
void ControlComObject::askControlRelay(UINT8 portno, bool status)
{
	qDebug()<<"askControlRelay thread:"<<QThread::currentThreadId();
	
	QByteArray buf;
	m_controlProtocol->makeFrameOfCtrlRelay(portno, status);
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//���ڷ�����
void ControlComObject::askControlRegulate(UINT8 portno, int degree)
{
	QByteArray buf;
	m_controlProtocol->makeFrameOfCtrlRegulate(portno, degree);
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//��ѯ�ӻ�״̬
void ControlComObject::askControlQuery()
{
	QByteArray buf;
	m_controlProtocol->makeFrameOfCtrlQuery();
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//����ˮ��
void ControlComObject::askControlWaterPump(UINT8 portno, bool status)
{
	QByteArray buf;
	m_controlProtocol->makeFrameOfCtrlWaterPump(portno, status);
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//���ñ�Ƶ��Ƶ��
void ControlComObject::askSetDriverFreq(int freq)
{
	QByteArray buf;
	m_controlProtocol->makeFrameOfSetDriverFreq(freq);
	buf = m_controlProtocol->getSendBuf();
	m_controlCom->write(buf);
}

//��ȡ���ư巵������
void ControlComObject::readControlComBuffer()
{
	qDebug()<<"readControlComBuffer ControlComObject thread:"<<QThread::currentThreadId();
	
	switch (m_protocolVersion)
	{
	case NEW_CTRL_VERSION: //�¿��ư�Э��
		readNewControlComBuffer();
		break;
	case OLD_CTRL_VERSION: //�Ͽ��ư�Э��
		
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
	if (m_conTmp.at(num-1) != CTRL_END_CODE) //һ֡�������
	{
		return;
	}
	QDateTime begintime = QDateTime::currentDateTime();

	UINT8 ret = 0x00;
	NewCtrlProtocol * protocolObj = (NewCtrlProtocol *)m_controlProtocol;
	ret = protocolObj->readCtrlComBuffer(m_conTmp);
	m_conTmp.clear(); //����

	UINT8 portno;
	UINT8 st;
	bool status;
	if (ret == CTRL_FUNC_RELAY) //�̵���
	{
		portno = protocolObj->getConFrame()->data[1];
		st = protocolObj->getConFrame()->data[(portno-1)/8 + 2];
		status = st ? VALVE_OPEN : VALVE_CLOSE;
		emit controlRelayIsOk(portno, status);
		qDebug()<<"controlRelayIsOk"<<"\n";
	}
	else if (ret == CTRL_FUNC_REGULATE) //���ڷ�
	{
		qDebug()<<"controlRegulateIsOk"<<"\n";
		emit controlRegulateIsOk();
	}
	else if (ret == CTRL_FUNC_QUERY) //��ѯ
	{
		m_conFrame = protocolObj->getConFrame();
	}
	else if (ret == CTRL_FUNC_BALANCE) //��ƽ
	{
		m_balValue = protocolObj->getBalanceValue();
		emit controlGetBalanceValueIsOk(m_balValue);
		QDateTime endtime = QDateTime::currentDateTime();
// 		UINT32 usedSec = begintime.msecsTo(endtime);
// 		qDebug()<<"��ȡ��ƽ���ݣ���ʱ"<<usedSec<<"����";
	}
	
}

/*
** ������BalanceComObject
** ���ܣ���ƽ������- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
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
	qDebug()<<"openBalanceCom thread:"<<QThread::currentThreadId();

	QString portName = comStruct->portName;// "COM2";//��ȡ������
#ifdef Q_OS_LINUX
	m_balanceCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
// 	m_balanceCom = new QextSerialPort(portName, QextSerialPort::EventDriven); //�¼�������ʽ
	m_balanceCom = new QextSerialPort(portName, QextSerialPort::Polling); //��ѯ��ʽ
#endif
// 	connect(m_balanceCom, SIGNAL(readyRead()), this, SLOT(readBalanceComBuffer()));
	connect(m_balTimer, SIGNAL(timeout()), this, SLOT(readBalanceComBuffer()));

	m_balanceCom->setBaudRate((BaudRateType)comStruct->baudRate);// BAUD9600); //���ò�����  
	m_balanceCom->setDataBits((DataBitsType)comStruct->dataBit);//DATA_8);   //��������λ
	m_balanceCom->setParity((ParityType)comStruct->parity);//PAR_EVEN);   //����У��λ
	m_balanceCom->setStopBits((StopBitsType)comStruct->stopBit);//STOP_1);   //����ֹͣλ
	m_balanceCom->setFlowControl(FLOW_OFF); //��������������  
	m_balanceCom->setTimeout(TIME_OUT);     //������ʱ

	if(m_balanceCom->open(QIODevice::ReadWrite)) 
	{
		qDebug()<<"Open Balance Com:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
/*
		QByteArray buf;
		buf.append(0x4E).append(0x20).append(0x20).append(0x20).append(0x20).append(0x20);
		buf.append(0x2D).append(0x31).append(0x32).append(0x33).append(0x34).append(0x2E).append(0x35).append(0x36).append(0x37).append(0x38);
		buf.append(0x20).append(0x6B).append(0x67).append(0x20).append(0x0D).append(0x0A);
		m_balanceCom->write(buf);
*/
		m_balTimer->start(TIMEOUT_BALANCE); //ÿ200�����ѯһ����ƽ����
		return true;
	}
	else
	{
		qDebug()<<"Open Balance Com:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return false;
	}
}

//��ȡ��ƽ��������
void BalanceComObject::readBalanceComBuffer()
{
	QByteArray balBuffer = m_balanceCom->readAll();
// 	qDebug()<<"balBuffer.size() ="<<balBuffer.size();
//  qDebug()<<"readBalanceComBuffer thread:"<<QThread::currentThreadId()<<", Read data is:"<<balBuffer;

	bool ret = false;
	ret = m_balanceProtocol->readBalanceComBuffer(balBuffer);//ͨѶЭ��ӿ�
	if (ret)
	{
		float balValue = m_balanceProtocol->getBalanceValue();
		emit balanceValueIsReady(balValue);
	}
}


/*
** ������MeterComObject
** ���ܣ�����������- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
*/
MeterComObject::MeterComObject(QObject* parent) : ComObject(parent)
{
	m_meterCom = NULL;
	m_meterProtocol = NULL;                                                                                                                    
	m_meterTmp="";
	m_portName = "";

	setProtocolVersion(0); //Ĭ���ǵ�³������
}

MeterComObject::~MeterComObject()
{
	if(m_meterCom != NULL)
	{
		if(m_meterCom->isOpen())
		{
			m_meterCom->close();
			qDebug()<<"m_meterCom closed";
		}
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
	case 0:	//��³������
		m_meterProtocol = new DeluMeterProtocol();
		break;
	case 1: //���������
		m_meterProtocol = new TgMeterProtocol();
		break;
	default: 
		m_meterProtocol =  new DeluMeterProtocol();
		break;
	}
}

/*
** �򿪴��ڣ���ʼ�����ڲ�����
*/
bool MeterComObject::openMeterCom(ComInfoStruct *comStruct)
{
	m_portName = comStruct->portName; //��ȡ������
// 	qDebug()<<"openMeterCom:"<<m_portName<<"thread:"<<QThread::currentThreadId();
#ifdef Q_OS_LINUX
	m_meterCom = new QextSerialPort("/dev/" + m_portName);
#elif defined (Q_OS_WIN)
	m_meterCom = new QextSerialPort(m_portName, QextSerialPort::EventDriven);
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
		qDebug()<<"Open openMeter Com:"<<m_portName<<"Success!"<<" thread id:"<<QThread::currentThreadId();
		return true;
	}
	else
	{
		qDebug()<<"Open Meter Com:"<<m_portName<<"Failed!"<<" thread id:"<<QThread::currentThreadId();
		return false;
	}
}

//�رմ���
void MeterComObject::closeMeterCom()
{
	m_meterCom->close();
}

/*
** �������ڷ�������
*/
void MeterComObject::readMeterComBuffer()
{
// 	qDebug()<<"readMeterComBuffer MeterComObject thread:"<<QThread::currentThreadId();
// 	qDebug()<<"Read"<<m_meterCom->bytesAvailable()<<"bytes!";
	m_meterTmp.append(m_meterCom->readAll());
	int num = m_meterTmp.size();
	if (num < 71) //����ǰ������һ֡����71���ֽ�
	{
//		qDebug()<<"���ڷ����ֽڸ��� ="<<num;
		return;
	}
	if (m_meterTmp.at(num-1) !=  METER_END_CODE) //һ֡�������
	{
		return;
	}

	UINT8 ret = 0x00;
	ret = m_meterProtocol->readMeterComBuffer(m_meterTmp);
	m_meterTmp.clear(); //����
	QDateTime begintime = QDateTime::currentDateTime();
	qDebug()<<"begintime:"<<begintime.toString("yyyy-MM-dd HH:mm:ss.zzz");

	bool ok;
	QString meterNo;
	float flow;
	QString heat;
	QString tempIn, tempOut, date;
	QString bigCoe,mid2Coe,mid1Coe,smallCoe;
	if (ret == 1) //��֡�ɹ�
	{
		//���
		meterNo = m_meterProtocol->getFullMeterNo();
		emit readMeterNoIsOK(m_portName, meterNo);
		QDateTime endtime = QDateTime::currentDateTime();
		qDebug()<<"endtime:  "<<endtime.toString("yyyy-MM-dd HH:mm:ss.zzz");
		UINT32 usedSec = begintime.msecsTo(endtime);

		//����������
		flow = m_meterProtocol->getFlow().toFloat(&ok);
		if (ok)
		{
			flow *= 1000; //��λת�� m3->L
			emit readMeterFlowIsOK(m_portName, flow);
		}

		//����
		heat = m_meterProtocol->getHeat();
		emit readMeterHeatIsOK(m_portName, heat);

		//����ˮ�¶�
		tempIn = m_meterProtocol->getInTemper();
		tempOut = m_meterProtocol->getOutTemper();
		emit readMeterTemperIsOK(m_portName, tempIn, tempOut);

		//�ȱ�����
		date = m_meterProtocol->getDate();
		emit readMeterDateIsOK(m_portName, date);

		//������ϵ��
		bigCoe = m_meterProtocol->getBigCoe();
		emit readMeterBigCoeIsOK(m_portName, bigCoe);

		//����2����ϵ��
		mid2Coe = m_meterProtocol->getMid2Coe();
		emit readMeterMid2CoeIsOK(m_portName, mid2Coe);

		//����1����ϵ��
		mid1Coe = m_meterProtocol->getMid1Coe();
		emit readMeterMid1CoeIsOK(m_portName, mid1Coe);

		//С����ϵ��
		smallCoe = m_meterProtocol->getSmallCoe();
		emit readMeterSmallCoeIsOK(m_portName, smallCoe);

		qDebug()<<"�������������ݣ���ʱ"<<usedSec<<"����";
	}
}

/*
** ��������㲥��ַ����
*/
void MeterComObject::askReadMeter()
{
	m_meterProtocol->makeFrameOfReadMeter();
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** �������ý���춨״̬
*/
void MeterComObject::askSetVerifyStatus()
{
	m_meterProtocol->makeFrameOfSetVerifyStatus();
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** �����޸ı��
*/
void MeterComObject::askModifyMeterNO(QString oldMeterNo, QString newMeterNo)
{
	m_meterProtocol->makeFrameOfModifyMeterNo(oldMeterNo, newMeterNo);
	QByteArray buf = m_meterProtocol->getSendFrame();
/*
	int num = buf.size();
	qDebug()<<"buf size ="<<num;
	for (int i=0; i<buf.size(); i++)
	{
		qDebug()<<"�����޸ı�ţ�"<<(UINT8)buf.at(i);
	}
*/	
	m_meterCom->write(buf);
}

/*
** �����޸���������
*/
void MeterComObject::askModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr)
{
	m_meterProtocol->makeFrameOfModifyFlowCoe(meterNO, bigErr, mid2Err, mid1Err, smallErr);
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

