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
**  ���¼�¼:
***********************************************/

#include <QtCore/QDebug>
#include "comthread.h"


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
���ܣ����ڲ�������- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
*************************************************/
ComObject::ComObject() : QObject()
{
	m_tempCom = NULL;
}

ComObject::~ComObject()
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

void ComObject::myslot()
{    
	qDebug()<<"myslot thread:" <<QThread::currentThreadId();
	openTemperatureCom();
}   

void ComObject::openTemperatureCom()
{
	qDebug()<<"openTemperatureCom thread:"<<QThread::currentThreadId();

	QString portName = "COM2";//��ȡ������
#ifdef Q_OS_LINUX
	m_tempCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_tempCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_tempCom, SIGNAL(readyRead()), this, SLOT(readTemperatureComBuffer()));

	m_tempCom->setBaudRate(BAUD9600); //���ò�����  
	m_tempCom->setDataBits(DATA_8);   //��������λ
	m_tempCom->setParity(PAR_EVEN);   //����У��λ
	m_tempCom->setStopBits(STOP_1);   //����ֹͣλ
	m_tempCom->setFlowControl(FLOW_OFF); //��������������  
	m_tempCom->setTimeout(TIME_OUT);     //������ʱ

	if(m_tempCom->open(QIODevice::ReadWrite))
	{
// 		QMessageBox::information(this, tr("Open Success"), tr("Open SerialPort ") + portName + tr(" Success!"), QMessageBox::Ok);
		qDebug()<<"Open SerialPort:"<<portName<<"Success!";
	}
	else
	{
// 		QMessageBox::critical(this, tr("Open Failed"), tr("Can't Open SerialPort ") + portName + tr("\nDevice isn't exist or is occupied!"), QMessageBox::Ok);
		qDebug()<<"Open SerialPort:"<<portName<<"Failed!";
		return;
	}

	m_tempCom->write("0xA8yangshen");
}

void ComObject::readTemperatureComBuffer()
{
	QByteArray temp = m_tempCom->readAll();
	qDebug()<<"readTemperatureComBuffer thread:"<<QThread::currentThreadId()<<", Read data is:"<<temp;
	float tempValue = 66.68;
	QString tempStr;
	tempStr.setNum(tempValue, 'f', 2);
	emit tempValueIsReady(tempStr);
}

