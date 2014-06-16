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
}

//请求温度
void TempComObject::writeTemperatureComBuffer()
{
// 	qDebug()<<"write TemperatureComBuffer thread:"<<QThread::currentThreadId();
	QByteArray buf;
	buf.append(ADDR_CODE_FIRST).append(ADDR_CODE_FIRST);//地址代号
	buf.append(READ_CODE); //标准读代码
	UINT8 paracode = 0x00; //参数代号
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
}

//读串口缓冲区
void TempComObject::readTemperatureComBuffer()
{
	int state = PV_STATE;
// 	qDebug()<<"read TemperatureComBuffer thread:"<<QThread::currentThreadId();

	QByteArray temp = m_tempCom->readAll();
	UINT8 uch = 0; //无符号8位数字
	INT8  ch = 0;  //有符号8位数字 
	int number = temp.size();
	int m=0;
	int pv_i=0, sv_i=0, para_i=0, check_i=0;
	UINT16 checknum=0; //程序计算的检验码
	for (m=0; m<number; m++)
	{
		switch(state)
		{
		case PV_STATE: //16位有符号
			{
				if (pv_i == 0) //低字节
				{
					uch = (UINT8)temp.at(m);
					m_tempFrame->pv = uch;
					pv_i++;
					break;
				}
				if (pv_i == 1) //高字节
				{
					ch = (INT8)temp.at(m);
					state = SV_STATE;
					m_tempFrame->pv = ch*256 + m_tempFrame->pv;
					pv_i = 0;
				}
				break;
			}
		case SV_STATE: //16位有符号
			{   
				if (sv_i == 0) //低字节
				{
					uch = (UINT8)temp.at(m);
					m_tempFrame->sv = uch;
					sv_i++;
					break;
				}
				if (sv_i == 1) //高字节
				{
					ch = (INT8)temp.at(m);
					state = MV_STATE;
					m_tempFrame->sv = ch*256 + m_tempFrame->sv;
					sv_i = 0;
				}
				break;
			}

		case MV_STATE: //8位有符号
			{
				ch = (INT8)temp.at(m);
				m_tempFrame->mv = ch;
				state = WARN_STATE;
				break;
			}    
		case WARN_STATE: //8位无符号
			{
				uch = (UINT8)temp.at(m);
				m_tempFrame->warn = uch;
				state = PARA_STATE;
				break;
			} 
		case PARA_STATE: //16位有符号
			{
				if (para_i == 0) //低字节 无符号
				{
					uch = (UINT8)temp.at(m);
					m_tempFrame->para = uch;
					para_i++;
					break;
				}
				if (para_i == 1) //高字节 有符号
				{
					ch = (INT8)temp.at(m);
					state = CHECK_STATE;
					m_tempFrame->para = ch*256 + m_tempFrame->para;
					para_i = 0;
				}
				break;
			} 
		case CHECK_STATE: //16位无符号
			{
				ch = (UINT8)temp.at(m);
				if (check_i == 0) //低字节
				{
					m_tempFrame->check = ch;
					check_i++;
					break;
				}
				if (check_i == 1) //高字节
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


//计算"校验码"
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
// 	qDebug()<<"TempComObject::analyseFrame thread:"<<QThread::currentThreadId();
	float PV = ((float)m_tempFrame->pv)/10;
	float SV = ((float)m_tempFrame->sv)/10;
	QString pvStr = QString("%1").arg(PV, DATA_WIDTH, 'f', DATA_PRECISION);
	QString svStr = QString("%1").arg(SV, DATA_WIDTH, 'f', DATA_PRECISION);
	QString Str = pvStr + svStr;
	emit temperatureIsReady(Str);
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
