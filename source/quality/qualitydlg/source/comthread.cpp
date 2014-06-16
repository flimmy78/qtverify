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

	m_tempFrame = new Temp_Frame_Struct();
	memset(m_tempFrame, 0, sizeof(Temp_Frame_Struct));
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
}

//�����¶�
void TempComObject::writeTemperatureComBuffer()
{
	qDebug()<<"write TemperatureComBuffer thread:"<<QThread::currentThreadId();
	QByteArray buf;
	buf.append(ADDR_CODE_FIRST).append(ADDR_CODE_FIRST);//��ַ����
	buf.append(READ_CODE); //��׼������
	UINT8 paracode = 0x00; //��������
	buf.append(paracode); 
	UINT8 datacode = 0x00;
	buf.append(datacode).append(datacode);
 	UINT16 checkcode = paracode*256 + READ_CODE + ADDR_FIRST;
	QString checkstr;
	checkstr = QString("%1").arg(checkcode, 4, 16).replace(" ", "0");
	bool ok;
	UINT8 lownum = checkstr.right(2).toUInt(&ok, 16);
	UINT8 hightnum = checkstr.left(2).toUInt(&ok, 16);
	buf.append(lownum).append(hightnum);
	m_tempCom->write(buf);
// 	m_tempCom->write("Write Temp com");
}

void TempComObject::readTemperatureComBuffer()
{
	int state = PV_STATE;
	qDebug()<<"read TemperatureComBuffer thread:"<<QThread::currentThreadId();

	QByteArray temp = m_tempCom->readAll();
	UINT8 uch = 0; //�޷���8λ����
	INT8  ch = 0;  //�з���8λ���� 
	int number = temp.size();
	int m=0;
	int pv_i=0, sv_i=0, para_i=0, check_i=0;
	UINT16 checknum=0; //�������ļ�����
	for (m=0; m<number; m++)
	{
// 		ch = (UINT8)temp.at(m);
// 		qDebug()<<ch;
// 
		switch(state)
		{
		case PV_STATE: //16λ�з���
			{
				if (pv_i == 0) //���ֽ�
				{
					uch = (UINT8)temp.at(m);
					m_tempFrame->pv = uch;
					pv_i++;
					break;
				}
				if (pv_i == 1) //���ֽ�
				{
					ch = (INT8)temp.at(m);
					state = SV_STATE;
					m_tempFrame->pv = ch*256 + m_tempFrame->pv;
					pv_i = 0;
				}
				break;
			}
		case SV_STATE: //16λ�з���
			{   
				if (sv_i == 0) //���ֽ�
				{
					uch = (UINT8)temp.at(m);
					m_tempFrame->sv = uch;
					sv_i++;
					break;
				}
				if (sv_i == 1) //���ֽ�
				{
					ch = (INT8)temp.at(m);
					state = MV_STATE;
					m_tempFrame->sv = ch*256 + m_tempFrame->sv;
					sv_i = 0;
				}
				break;
			}

		case MV_STATE: //8λ�з���
			{
				ch = (INT8)temp.at(m);
				m_tempFrame->mv = ch;
				state = WARN_STATE;
				break;
			}    
		case WARN_STATE: //8λ�޷���
			{
				uch = (UINT8)temp.at(m);
				m_tempFrame->warn = uch;
				state = PARA_STATE;
				break;
			} 
		case PARA_STATE: //16λ�з���
			{
				if (para_i == 0) //���ֽ� �޷���
				{
					uch = (UINT8)temp.at(m);
					m_tempFrame->para = uch;
					para_i++;
					break;
				}
				if (para_i == 1) //���ֽ� �з���
				{
					ch = (INT8)temp.at(m);
					state = CHECK_STATE;
					m_tempFrame->para = ch*256 + m_tempFrame->para;
					para_i = 0;
				}
				break;
			} 
		case CHECK_STATE: //16λ�޷���
			{
				ch = (UINT8)temp.at(m);
				if (check_i == 0) //���ֽ�
				{
					m_tempFrame->check = ch;
					check_i++;
					break;
				}
				if (check_i == 1) //���ֽ�
				{
					m_tempFrame->check = ch*256 + m_tempFrame->check;
					check_i = 0;
					state = PV_STATE;
					checknum = CountCheck(m_tempFrame);
					if (checknum == m_tempFrame->check)
					{
						analyseFrame();
					}
				}
				break;
			}
		default :
			{
				state = PV_STATE;
				break;
			}
		} //END OF switch(state)        
	} //END OF for (m=0; m<number; m++)

}


//����"У����"
UINT16 TempComObject::CountCheck(Temp_Frame_Struct *pFrame)
{
	if (NULL == pFrame)
	{
		return 0;
	}

	UINT16 cs = 0;
	cs = pFrame->pv + pFrame->sv + (pFrame->warn*256 + pFrame->mv) + pFrame->para + ADDR_FIRST;

	return cs; 
}



void TempComObject::analyseFrame()
{
	qDebug()<<"TempComObject::analyseFrame thread:"<<QThread::currentThreadId();

	float PV = ((float)m_tempFrame->pv)/10;
	float SV = ((float)m_tempFrame->sv)/10;
	QString pvStr, svStr;
	pvStr.setNum(PV, 'f', 1);
	svStr.setNum(SV, 'f', 1);
	QString Str = pvStr + svStr;
	emit temperatureIsReady(Str);
}

/************************************************
������ValveComObject
���ܣ����ſ��ƴ�����- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
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

	QString portName = comStruct->portName;// "COM2";//��ȡ������
#ifdef Q_OS_LINUX
	m_tempCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_valveCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_valveCom, SIGNAL(readyRead()), this, SLOT(readValveControlComBuffer()));

	m_valveCom->setBaudRate((BaudRateType)comStruct->baudRate);// BAUD9600); //���ò�����  
	m_valveCom->setDataBits((DataBitsType)comStruct->dataBit);//DATA_8);   //��������λ
	m_valveCom->setParity((ParityType)comStruct->parity);//PAR_EVEN);   //����У��λ
	m_valveCom->setStopBits((StopBitsType)comStruct->stopBit);//STOP_1);   //����ֹͣλ
	m_valveCom->setFlowControl(FLOW_OFF); //��������������  
	m_valveCom->setTimeout(TIME_OUT);     //������ʱ

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
	int isOpen = 1;
	emit valveComIsAnalysed(isOpen);
}
