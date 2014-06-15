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
���ܣ����ڲ�������
*************************************************/
ComObject::ComObject() : QObject()
{
}

ComObject::~ComObject()
{
}


/************************************************
������TempComObject
���ܣ��¶ȴ�����- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
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

	QString portName = comStruct->portName;// "COM2";//��ȡ������
#ifdef Q_OS_LINUX
	m_tempCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_tempCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_tempCom, SIGNAL(readyRead()), this, SLOT(readTemperatureComBuffer()));

	m_tempCom->setBaudRate((BaudRateType)comStruct->baudRate);// BAUD9600); //���ò�����  
	m_tempCom->setDataBits((DataBitsType)comStruct->dataBit);//DATA_8);   //��������λ
	m_tempCom->setParity((ParityType)comStruct->parity);//PAR_EVEN);   //����У��λ
	m_tempCom->setStopBits((StopBitsType)comStruct->stopBit);//STOP_1);   //����ֹͣλ
	m_tempCom->setFlowControl(FLOW_OFF); //��������������  
	m_tempCom->setTimeout(TIME_OUT);     //������ʱ

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

	m_tempCom->write("0xA8yangshen");
}

void TempComObject::readTemperatureComBuffer()
{
	QByteArray temp = m_tempCom->readAll();
	qDebug()<<"readTemperatureComBuffer thread:"<<QThread::currentThreadId()<<", Read data is:"<<temp;
	analyseFrame();
}

void TempComObject::analyseFrame()
{
	qDebug()<<"analyseFrame thread:"<<QThread::currentThreadId();

	float tempValue = 66.68;
	QString tempStr;
	tempStr.setNum(tempValue, 'f', 2);
	emit tempComIsAnalysed(tempStr);
}
