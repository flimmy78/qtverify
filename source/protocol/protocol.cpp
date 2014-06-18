/***********************************************
**  文件名:     protocol.cpp
**  功能:       通讯协议类
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/16
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/06 第一版
**  内容包含:
**  说明:
**  更新记录:   2014-6-16增加温度采集协议（厦门宇电AI702巡检仪）
                2014-6-17增加天平协议(赛多利斯)
***********************************************/

#include <QtCore/QDebug>
#include "protocol.h"

CProtocol::CProtocol()
{

}

CProtocol::~CProtocol()
{

}

float CProtocol::calc(float a, float b)
{
	float sum = a + b;
	qDebug("%.2f + %.2f = %.2f \n", a, b, sum);
	return sum;
}

/***********************************************
类名：TempProtocol
功能：厦门宇电 AI702巡检仪 通讯协议（温度）
************************************************/
TempProtocol::TempProtocol()
{
	m_tempFrame = new Temp_Frame_Struct();
	memset(m_tempFrame, 0, sizeof(Temp_Frame_Struct));

	m_tempStr = "";
	m_sendBuf = "";
}

TempProtocol::~TempProtocol()
{
	if (m_tempFrame != NULL)
	{
		delete m_tempFrame;
		m_tempFrame = NULL;
	}
}

//请求温度值 组帧
void TempProtocol::makeSendBuf()
{
	m_sendBuf = "";
	m_sendBuf.append(ADDR_CODE_FIRST).append(ADDR_CODE_FIRST);//地址代号
	m_sendBuf.append(READ_CODE); //标准读代码
	UINT8 paracode = 0x00; //参数代号
	m_sendBuf.append(paracode); 
	UINT8 datacode = 0x00;
	m_sendBuf.append(datacode).append(datacode);
	UINT16 checkcode = paracode*256 + READ_CODE + ADDR_FIRST;
	QString checkstr;
	checkstr = QString("%1").arg(checkcode, 4, 16).replace(" ", "0");
	bool ok;
	UINT8 lownum = checkstr.right(2).toUInt(&ok, 16);
	UINT8 hightnum = checkstr.left(2).toUInt(&ok, 16);
	m_sendBuf.append(lownum).append(hightnum);
}

//解帧 获取温度值
bool TempProtocol::readTemperComBuffer(QByteArray tmp)
{
	memset(m_tempFrame, 0, sizeof(Temp_Frame_Struct));
	bool ret = false;
	int state = PV_STATE;

	UINT8 uch = 0; //无符号8位数字
	INT8  ch = 0;  //有符号8位数字 
	int number = tmp.size();
	int m=0;
	int pv_i=0, sv_i=0, para_i=0, check_i=0;
 	INT16 ck=0; //程序计算的检验码
	for (m=0; m<number; m++)
	{
		switch(state)
		{
		case PV_STATE: //16位有符号
			{
				if (pv_i == 0) //低字节
				{
					uch = (UINT8)tmp.at(m);
					m_tempFrame->pv = uch;
					pv_i++;
					break;
				}
				if (pv_i == 1) //高字节
				{
					ch = (INT8)tmp.at(m);
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
					uch = (UINT8)tmp.at(m);
					m_tempFrame->sv = uch;
					sv_i++;
					break;
				}
				if (sv_i == 1) //高字节
				{
					ch = (INT8)tmp.at(m);
					state = MV_STATE;
					m_tempFrame->sv = ch*256 + m_tempFrame->sv;
					sv_i = 0;
				}
				break;
			}

		case MV_STATE: //8位有符号
			{
				ch = (INT8)tmp.at(m);
				m_tempFrame->mv = ch;
				state = WARN_STATE;
				break;
			}    
		case WARN_STATE: //8位无符号
			{
				ch = (INT8)tmp.at(m);
				m_tempFrame->warn = ch;
				state = PARA_STATE;
				break;
			} 
		case PARA_STATE: //16位有符号
			{
				if (para_i == 0) //低字节 无符号
				{
					uch = (UINT8)tmp.at(m);
					m_tempFrame->para = uch;
					para_i++;
					break;
				}
				if (para_i == 1) //高字节 有符号
				{
					ch = (INT8)tmp.at(m);
					state = CHECK_STATE;
					m_tempFrame->para = ch*256 + m_tempFrame->para;
					para_i = 0;
				}
				break;
			} 
		case CHECK_STATE: //16位
			{
				if (check_i == 0) //低字节
				{
					uch = (UINT8)tmp.at(m);
					m_tempFrame->check = uch;
					check_i++;
					break;
				}
				if (check_i == 1) //高字节
				{
					ch = (INT8)tmp.at(m);
					m_tempFrame->check = ch*256 + m_tempFrame->check;
					check_i = 0;
					state = PV_STATE;
					ck = CountCheck(m_tempFrame);
					if (ck == m_tempFrame->check) //校验通过
					{
						analyseFrame();
						ret = true;
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

	return ret;
}

//计算"校验码"
INT16 TempProtocol::CountCheck(Temp_Frame_Struct *pFrame)
{
	if (NULL == pFrame)
	{
		return 0;
	}

	INT16 cs = 0;
	cs = pFrame->pv + pFrame->sv + (pFrame->warn*256 + pFrame->mv) + pFrame->para + ADDR_FIRST;

	return cs; 
}


void TempProtocol::analyseFrame()
{
	float PV = ((float)m_tempFrame->pv)/10;
	float SV = ((float)m_tempFrame->sv)/10;
	QString pvStr = QString("%1").arg(PV, DATA_WIDTH, 'f', DATA_PRECISION);
	QString svStr = QString("%1").arg(SV, DATA_WIDTH, 'f', DATA_PRECISION);
	m_tempStr = pvStr + svStr;
	qDebug()<<"TempProtocol::analyseFrame thread:"<<QThread::currentThreadId();
}

QString TempProtocol::getTempStr()
{
	qDebug()<<"TempProtocol::getTempStr thread:"<<QThread::currentThreadId();
	return m_tempStr;
}

QByteArray TempProtocol::getSendBuf()
{
	return m_sendBuf;
}


/***********************************************
类名：BalanceProtocol
功能：天平协议
************************************************/
BalanceProtocol::BalanceProtocol()
{
	m_balValue = "";
}

BalanceProtocol::~BalanceProtocol()
{
}

//解析赛多利斯天平串口数据
bool BalanceProtocol::readBalanceComBuffer(QByteArray tmp)
{
	m_balValue = "";
	bool ret = false;
	int num = tmp.size();
	if (num < 16) //一帧通常是22字节；
	{
		return ret;
	}
	int m=0;
	char ch;
	UINT8 ch1, ch2;
	ch1 = (UINT8)tmp.at(num-1);
	ch2 = (UINT8)tmp.at(num-2);
	if (ch1==0x0A && ch2==0x0D)
	{
		for (m=num-16; m<num-6; m++)
		{
			ch = tmp.at(m);
			m_balValue += ch;
		}
		ret = true;
	}

	return ret;
}

QString BalanceProtocol::getBalanceValue()
{
	return m_balValue;
}


/***********************************************
类名：ControlProtocol
功能：下位机控制协议
************************************************/
ControlProtocol::ControlProtocol()
{
	m_sendBuf = "";

	m_OpenPortNo[1] = 0xE1; //打开阀门(闭合继电器)
	m_OpenPortNo[2] = 0xE3;
	m_OpenPortNo[3] = 0xE5;
	m_OpenPortNo[4] = 0xE7;
	m_OpenPortNo[5] = 0xE9;
	m_OpenPortNo[6] = 0xEB;
	m_OpenPortNo[7] = 0xED;
	m_OpenPortNo[8] = 0xEF;

	m_closePortNo[1] = 0xE0; //关闭阀门(断开继电器)
	m_closePortNo[2] = 0xE2;
	m_closePortNo[3] = 0xE4;
	m_closePortNo[4] = 0xE6;
	m_closePortNo[5] = 0xE8;
	m_closePortNo[6] = 0xEA;
	m_closePortNo[7] = 0xEC;
	m_closePortNo[8] = 0xEE;
}

ControlProtocol::~ControlProtocol()
{
}

void ControlProtocol::makeRelaySendBuf(int portno, bool status)
{
	m_sendBuf = "";
	m_sendBuf.append(0xFF);
	if (status) //打开阀门(闭合继电器)
	{
		m_sendBuf.append(m_OpenPortNo[portno]);
	}
	else //关闭阀门(断开继电器)
	{
		m_sendBuf.append(m_closePortNo[portno]);
	}
	UINT8 code0 = 0x00;
	m_sendBuf.append(code0).append(code0).append(0xFE);
}

QByteArray ControlProtocol::getSendBuf()
{
	return m_sendBuf;
}