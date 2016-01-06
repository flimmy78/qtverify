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
#include <QtCore/QDateTime>

#include "comobject.h"
#include "commondefine.h"

/*
** ������ComThread
** ���ܣ��̹߳����ࣻ�������߳�
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
		qDebug()<<"### OpenTemperatureCom:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
		return true;
	}
	else
	{
		qDebug()<<"### OpenTemperatureCom:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return false;
	}
}

//�����¶�
void TempComObject::writeTemperatureComBuffer()
{
// 	qDebug()<<"TempComObject::writeTemperatureComBuffer thread:"<<QThread::currentThreadId();
	if (NULL==m_tempProtocol || !m_tempCom->isOpen())
	{
		return;
	}
	m_tempProtocol->makeSendBuf();
	QByteArray buf = m_tempProtocol->getSendBuf();
// 	int size = buf.size();
// 	for (int i=0; i<size; i++)
// 	{
// 		printf("������¶ȣ�0x%.2x\n", (UINT8)buf.at(i));
// 	}
// 	printf("\n\n");
	m_tempCom->flush();
	m_tempCom->write(buf);
}

//���¶ȴ��ڻ�����
void TempComObject::readTemperatureComBuffer()
{
// 	qDebug()<<"TempComObject::readTemperatureComBuffer thread:"<<QThread::currentThreadId();
	if (NULL==m_tempCom || !m_tempCom->isOpen())
	{
		return;
	}
	QByteArray tmp = m_tempCom->readAll();
	m_tempCom->flush();
	if (tmp.isEmpty())
	{
		return;
	}
	m_buf += tmp;
	int num = m_buf.size();
// 	qDebug()<<m_tempCom->portName()<<": receive"<<num<<"bytes !";
// 	for (int i=0; i<num; i++)
// 	{
// 		printf("�����¶ȣ�0x%.2x\n", (UINT8)m_buf.at(i));
// 	}
// 	printf("\n\n");
	if (num < 10)
	{
		return;
	}
	bool ret = false;
	ret = m_tempProtocol->readTemperComBuffer(m_buf); //ͨѶЭ��ӿ�
	if (ret)
	{
		QString tempStr = m_tempProtocol->getTempStr();
		emit temperatureIsReady(tempStr);
	}
	m_buf.clear();
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

//����Э��汾��
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
//	qDebug()<<"*** openControlCom thread:"<<QThread::currentThreadId();
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
**	���ܣ����Ƽ̵����Ͽ����պϣ������������������ϣ�
**	���������
		portno:�̵������
		status: false(�رշ���)��true(�򿪷���)
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

//���ڷ�����
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

//��ѯ�ӻ�״̬
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

//����ˮ��
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

//���ñ�Ƶ��Ƶ��
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

//��ȡ���ư巵������
void ControlComObject::readControlComBuffer()
{
// 	qDebug()<<"readControlComBuffer ControlComObject thread:"<<QThread::currentThreadId();
	
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
		qDebug()<<"$$$ OpenBalanceCom:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
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
		qDebug()<<"$$$ OpenBalanceCom:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return false;
	}
}

//��ȡ��ƽ��������
void BalanceComObject::readBalanceComBuffer()
{
// 	qDebug()<<"BalanceComObject::readBalanceComBuffer thread:"<<QThread::currentThreadId();
	if (NULL==m_balanceCom)
	{
		return;
	}
	QByteArray balBuffer = m_balanceCom->readAll();
	m_balanceCom->flush();
	if (balBuffer.isEmpty())
	{
		return;
	}
// 	qDebug()<<"balBuffer.size() ="<<balBuffer.size();
// 	qDebug()<<"read data is:"<<balBuffer;
// 	for (int i=0;i<balBuffer.size();i++)
// 	{
// 		printf("0x%02X ", (uchar)balBuffer.at(i));
// 	}
// 	printf("\n");
	bool ret = false;
	ret = m_balanceProtocol->readBalanceComBuffer(balBuffer);//ͨѶЭ��ӿ�
	if (ret)
	{
		float balValue = m_balanceProtocol->getBalanceValue();
		emit balanceValueIsReady(balValue);
	}
}

/*
** ������ƽ����
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
	case BALANCE_TYPE_Satorius:	//������˹
		m_balanceProtocol = new BalSatoriusProtocol();
		break;
	case BALANCE_TYPE_SatoriusH: //������˹H
		m_balanceProtocol = new BalSatoriusHProtocol();
		break;
	case BALANCE_TYPE_Bizerba: //�̲�
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
** ������MeterComObject
** ���ܣ�����������- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
*/
MeterComObject::MeterComObject(QObject* parent) : ComObject(parent)
{
	m_meterCom = NULL;
	m_meterProtocol = NULL;                                                                                                                    
	m_meterTmp="";
	m_portName = "";

	setProtocolVersion(PROTOCOL_VER_DELU); //Ĭ���ǵ�³������
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
	case PROTOCOL_VER_COMMON:	//ͨ��Э��
	case PROTOCOL_VER_DELU:	    //��³��������
	case PROTOCOL_VER_TIANGANG: //���������
	case PROTOCOL_VER_RUINA:    //���ɳ�������
		m_meterProtocol = new DeluMeterProtocol();
		break;
	case PROTOCOL_VER_LICHSONIC: //������������
		m_meterProtocol = new LiChMeterProtocol();
		break;
	case PROTOCOL_VER_HUIZH: //���г�������
		m_meterProtocol = new HuiZhongMeterProtocol();
		break;
	case PROTOCOL_VER_ADE:   //�����³��������
		m_meterProtocol = new AdeMeterProtocol();
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
// 	qDebug()<<"!!! openMeterCom:"<<m_portName<<"thread:"<<QThread::currentThreadId();
	m_portName = comStruct->portName; //��ȡ������
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
		qDebug()<<"!!! openMeterCom:"<<m_portName<<"Success!"<<" thread id:"<<QThread::currentThreadId();
		return true;
	}
	else
	{
		qDebug()<<"!!! openMeterCom:"<<m_portName<<"Failed!"<<" thread id:"<<QThread::currentThreadId();
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
	if (NULL==m_meterCom)
	{
		return;
	}
	//������ͷ���ϣ�����������ԭ�ⲻ�����ؽ��նˣ����������������
	QByteArray tmp = m_meterCom->readAll();
	if (tmp.isEmpty())
	{
		return;
	}
	bool flg = true;
	for (int i=0; i<tmp.size(); i++)
	{
		flg *= ((UINT8)tmp.at(i) == ADE_WAKEUP_CODE);
	}
	if (flg) //ȫ���ǻ�����
	{
		return;
	}
	//������ͷ���Ͻ���
	m_meterTmp.append(tmp);
	sleep(500);
	m_meterTmp.append(m_meterCom->readAll());
/***********************************************************
	int idx = m_meterTmp.indexOf(METER_START_CODE); //��ʼ��
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
	if (num < framelen || m_meterTmp.at(num-1) !=  METER_END_CODE) //һ֡�������
	{
		return;
	}
**************************************************************/
// 	qDebug()<<m_meterCom->portName()<<"readMeterComBuffer MeterComObject thread:"<<QThread::currentThreadId();
	qDebug()<<"MeterComObject::readMeterComBuffer"<<m_meterCom->portName()<<"read"<<m_meterTmp.size()<<"bytes!";
// 	QDateTime begintime = QDateTime::currentDateTime();
// 	qDebug()<<"begintime:"<<begintime.toString("yyyy-MM-dd HH:mm:ss.zzz");
	UINT8 ret = 0x00;
	if (NULL==m_meterProtocol)
	{
		return;
	}
	ret = m_meterProtocol->readMeterComBuffer(m_meterTmp);
	m_meterTmp.clear(); //����

	QString meterNo;
	QString flow, heat;
	QString tempIn, tempOut, date;
	QString bigCoe,mid2Coe,mid1Coe,smallCoe;
	if (ret == 1) //��֡�ɹ�
	{
		//���
		meterNo = m_meterProtocol->getFullMeterNo();
		emit readMeterNoIsOK(m_portName, meterNo);

		//����������
		flow = m_meterProtocol->getFlow();
		emit readMeterFlowIsOK(m_portName, flow);

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

// 		QDateTime endtime = QDateTime::currentDateTime();
// 		qDebug()<<"endtime:  "<<endtime.toString("yyyy-MM-dd HH:mm:ss.zzz");
// 		UINT32 usedSec = begintime.msecsTo(endtime);
//		qDebug()<<"�������������ݣ���ʱ"<<usedSec<<"����";
		qDebug()<<"�������������ݣ��ɹ�";
	}
}

/*
** ��������
*/
void MeterComObject::askReadMeterNO()
{
	qDebug()<<m_meterCom->portName()<<"111 MeterComObject askReadMeterNo thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfReadMeterNO();
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** �����������ϵ��
*/
void MeterComObject::askReadMeterFlowCoe()
{
	qDebug()<<m_meterCom->portName()<<"111 MeterComObject askReadMeterFlowCoe thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfReadMeterFlowCoe();
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** ��������㲥��ַ����
** ������� vType: �춨����
				0�������춨
				1�������춨
*/
void MeterComObject::askReadMeterData(int vType)
{
	qDebug()<<m_meterCom->portName()<<"111 MeterComObject askReadMeterData thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfReadMeterData();
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** �������ý���춨״̬
** ������� vType: �춨����
				0�������춨
				1�������춨
*/
void MeterComObject::askSetVerifyStatus(int vType)
{
	qDebug()<<m_meterCom->portName()<<"111 MeterComObject askSetVerifyStatus thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfSetVerifyStatus(vType);
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** �����˳��춨״̬
** ������� vType: �춨����
				0�������춨
				1�������춨
*/
void MeterComObject::askExitVerifyStatus(int vType)
{
	qDebug()<<m_meterCom->portName()<<"111 MeterComObject askExitVerifyStatus thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfExitVerifyStatus(vType);
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** �����޸ı��(14λ���)
*/
void MeterComObject::askModifyMeterNO(QString oldMeterNo, QString newMeterNo)
{
	qDebug()<<m_meterCom->portName()<<"111 MeterComObject askModifyMeterNO thread:"<<QThread::currentThreadId();
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
	qDebug()<<m_meterCom->portName()<<"111 MeterComObject askModifyFlowCoe thread:"<<QThread::currentThreadId();
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
** �����޸���������
*/
void MeterComObject::askModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr, MeterCoe_PTR oldCoe)
{
	qDebug()<<m_meterCom->portName()<<"222 MeterComObject askModifyFlowCoe thread:"<<QThread::currentThreadId();
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
** ���ÿھ�-�����³������
*/
void MeterComObject::askSetStandard(UINT8 std)
{
	qDebug()<<m_meterCom->portName()<<"222 MeterComObject askSetStandard thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfSetStandard(std);
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** ����ϵͳʱ��-�����³������
*/
void MeterComObject::askSetSystemTime()
{
	qDebug()<<m_meterCom->portName()<<"222 MeterComObject askSetSystemTime thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfSetSystemTime();
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** ����һ����ַ-�����³������
*/
void MeterComObject::askSetAddress1(QString curAddr1, QString newAddr2)
{
	qDebug()<<m_meterCom->portName()<<"222 MeterComObject askSetAddress1 thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfSetAddress1(curAddr1, newAddr2);
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}

/*
** ���ö�����ַ-�����³������
*/
void MeterComObject::askSetAddress2(QString curAddr1, QString newAddr2)
{
	qDebug()<<m_meterCom->portName()<<"222 MeterComObject askSetAddress2 thread:"<<QThread::currentThreadId();
	if (NULL==m_meterProtocol)
	{
		return;
	}
	m_meterProtocol->makeFrameOfSetAddress2(curAddr1, newAddr2);
	QByteArray buf = m_meterProtocol->getSendFrame();
	m_meterCom->write(buf);
}


/*
** ������StdTempComObject
** ���ܣ���׼�¶ȼƴ�����-�򿪴���;���ô��ڲ������رմ��ڣ�
*/
StdTempComObject::StdTempComObject(QObject* parent) : ComObject(parent)
{
	m_tempCom = NULL;
	m_stdTempProtocol = NULL;
}

StdTempComObject::~StdTempComObject()
{
	if (m_tempCom != NULL)
	{
		if (m_tempCom->isOpen())
		{
			m_tempCom->close();
			qDebug()<<"m_tempCom closed";
		}
		delete m_tempCom;
		m_tempCom = NULL;
	}

	if (m_stdTempProtocol != NULL)
	{
		delete m_stdTempProtocol;
		m_stdTempProtocol = NULL;
	}
}

void StdTempComObject::setStdTempVersion(int version, int valueType)
{
	if (m_stdTempProtocol)
	{
		delete m_stdTempProtocol;
		m_stdTempProtocol = NULL;
	}

	switch (version)
	{
	case TEMPERATURE_TYPE_METROLOGY:
		m_stdTempProtocol = new instituteTempProtocol();
		break;
	case TEMPERATURE_TYPE_WEILI:
		m_stdTempProtocol = new sti1062ATempProtocol();
		break;
	case TEMPERATURE_TYPE_HUAYI:
		m_stdTempProtocol = new huayiTempProtocol();
		if (valueType == STD_RESIST)
		{
			m_tempCom->write("R"); //�л�����������״̬
		}
		else //if (valueType == STD_TEMPER)
		{
			m_tempCom->write("T"); //�л��������¶�״̬
		}
		break;
	default:
		m_stdTempProtocol = new huayiTempProtocol();
		break;
	}
}

bool StdTempComObject::openTemperatureCom(ComInfoStruct *comStruct)
{
// 	qDebug()<<"&&& StdTempComObject::openTemperatureCom thread:"<<QThread::currentThreadId();
	QString portName = comStruct->portName;// "COM2", ��ȡ������
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
		qDebug()<<"&&& StdTempComObject::openTemperatureCom:"<<portName<<"Success!"<<" thread id;"<<QThread::currentThreadId();
		return true;
	}
	else
	{
		qDebug()<<"&&& StdTempComObject::openTemperatureCom:"<<portName<<"Failed!"<<" thread id;"<<QThread::currentThreadId();
		return false;
	}
}

//�����¶�
void StdTempComObject::writeStdTempComBuffer(stdTempCommand command)
{
	qDebug()<<"StdTempComObject::writeStdTempComBuffer"<<QThread::currentThreadId();
	int version = m_stdTempProtocol->getProtocolVersion();
	switch (version)
	{
	case TEMPERATURE_TYPE_METROLOGY:
		break;
	case TEMPERATURE_TYPE_WEILI:
		m_stdTempProtocol->makeSendBuf(command);
		m_tempCom->write(m_stdTempProtocol->getSendBuf());
		break;
	case TEMPERATURE_TYPE_HUAYI:
		switch (command)
		{
		case stdTempR1:
			m_tempCom->write("A");
			break;
		case stdTempR2:
			m_tempCom->write("B");
			break;
		default:
			break;
		}
		QTimer::singleShot(2000, this, SLOT(writeComByteM()));
// 		wait(2000);
// 		m_tempCom->write("M");
		break;
	default:
		break;
	}
}

//ֻ��Ի��ױ�׼�¶ȼ�
void StdTempComObject::writeComByteM()
{
	qDebug()<<"StdTempComObject::writeComByteM"<<QThread::currentThreadId();
	m_tempCom->write("M");
}

//����׼�¶ȴ��ڻ�����
void StdTempComObject::readTemperatureComBuffer()
{
	qDebug()<<"StdTempComObject::readTemperatureComBuffer"<<QThread::currentThreadId();
	QByteArray tmp = m_tempCom->readAll();

	bool ret = false;
	ret = m_stdTempProtocol->readTemperComBuffer(tmp); //ͨѶЭ��ӿ�
	if (ret)
	{
		m_tempCom->flush();
		QString tempStr = m_stdTempProtocol->getReadStr();
		emit temperatureIsReady(tempStr);
	}
}

void StdTempComObject::close()
{
	m_tempCom->close();
}
/*
** StdTempComObject END
*/

/*
** ������lcModRtuComObject
** ���ܣ�����ModRtuͨѶ������, ���ڶ�ȡ�����ӵ��
** ������������
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
		m_lcModCom->close();
		qDebug()<<m_lcModCom->portName()<<" m_lcModCom closed";
		delete m_lcModCom;
		m_lcModCom = NULL;
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

	QString portName = comStruct->portName;// "COM2", ��ȡ������
#ifdef Q_OS_LINUX
	m_lcModCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_lcModCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_lcModCom, SIGNAL(readyRead()), this, SLOT(readLcModComBuffer()));

	m_lcModCom->setBaudRate((BaudRateType)comStruct->baudRate);// BAUD9600); //���ò�����  
	m_lcModCom->setDataBits((DataBitsType)comStruct->dataBit); //DATA_8);    //��������λ
	m_lcModCom->setParity((ParityType)comStruct->parity);	  //PAR_EVEN);  //����У��λ
	m_lcModCom->setStopBits((StopBitsType)comStruct->stopBit); //STOP_1);    //����ֹͣλ
	m_lcModCom->setFlowControl(FLOW_OFF); //��������������  
	m_lcModCom->setTimeout(TIME_OUT);     //������ʱ

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

//address: ����ģ����豸��ַ
void lcModRtuComObject::ask9150A16RoutesCmd(uchar address)
{
	lcModSendCmd command;
	command.address = address;
	command.func = read_multi_reg;
	command.start = EDA_9150A_START_REG;
	command.regCount = (EDA_9150A_ROUTE_CNT*EDA9150A_ROUTE_BYTES)/LC_EDA_REG_BYTES;//�ܹ��ļĴ�������
	writeLcModComBuffer(command);
}

void lcModRtuComObject::ask9150ARouteI(int i, uchar address)
{
	lcModSendCmd command;
	command.address = address;
	command.func = read_multi_reg;
	command.start = EDA_9150A_START_REG + 2*i;//һ���Ĵ���2���ֽ�
	command.regCount = (EDA9150A_ROUTE_BYTES/LC_EDA_REG_BYTES);//һ��ͨ����Ӧ�����Ĵ���
	writeLcModComBuffer(command);
}

void lcModRtuComObject::ask9150ARouteL(UINT16 len, uchar address)
{
	lcModSendCmd command;
	command.address = address;
	command.func = read_multi_reg;
	command.start = EDA_9150A_START_REG;//һ���Ĵ���2���ֽ�
	command.regCount = (EDA9150A_ROUTE_BYTES/LC_EDA_REG_BYTES)*len;//һ��ͨ����Ӧ�����Ĵ���
	writeLcModComBuffer(command);
}

void lcModRtuComObject::ask901712RoutesCmd(uchar address)
{
	lcModSendCmd command;
	command.address = address;
	command.func = read_multi_reg;
	command.start = EDA_9017_START_REG;
	command.regCount = (EDA_9017_ROUTE_CNT*EDA9017_ROUTE_BYTES)/LC_EDA_REG_BYTES;//�ܹ��ļĴ�������
	writeLcModComBuffer(command);
}

void lcModRtuComObject::readLcModComBuffer()
{
	QByteArray tmp = m_lcModCom->readAll();
	if (tmp.length() == 0)
	{
		return;
	}
	bool ret = m_lcModProtocol->readMeterComBuffer(tmp); //ͨѶЭ��ӿ�
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

/************************************************************************/
/* �������9510Aģ���ͨ��ֵ
 * uchar address, ����ģ��ĵ�ַ��
 * bool backward, �Ƿ������ǰ8·ͨ����ֵ
/************************************************************************/
void lcModRtuComObject::clearLcModAccum(uchar address, bool backward)
{
	//���ǰ8·ͨ����ֵ
	lcMod9150AWriteCmd cmd;
	cmd.address = address;
	cmd.func = write_multi_switch;
	cmd.start = EDA_9150A_START_REG+backward*0x0010;
	cmd.regCount = (EDA_9150A_ROUTE_CNT/2)*LC_EDA_REG_BYTES;//8·ͨ����Ӧ�ļĴ�������
	cmd.ByteCount = cmd.regCount*LC_EDA_REG_BYTES;
	cmd.pData = new uint[cmd.regCount/LC_EDA_REG_BYTES];
	memset(cmd.pData, 0, sizeof(uint)*cmd.regCount/LC_EDA_REG_BYTES);
	m_lcModProtocol->makeWriteBuf(cmd);
	m_lcModCom->write(m_lcModProtocol->getWriteBuf());
}
/*
** lcModRtuComObject END
*/