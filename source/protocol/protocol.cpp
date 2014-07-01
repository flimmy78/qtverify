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
				2014-6-23增加控制板新协议
***********************************************/

#include <QtCore/QDebug>
#include <math.h>
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
// 	qDebug()<<"TempProtocol::analyseFrame thread:"<<QThread::currentThreadId();
}

QString TempProtocol::getTempStr()
{
// 	qDebug()<<"TempProtocol::getTempStr thread:"<<QThread::currentThreadId();
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
	if (ch1==ASCII_LF && ch2==ASCII_CR) //0x0A换行; 0x0D回车（表示一帧结束）
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

	m_conFrame = new Con_Frame_Struct();
	memset(m_conFrame, 0, sizeof(Con_Frame_Struct));

	m_balValueStr = "";
}

ControlProtocol::~ControlProtocol()
{
}

/************************************************************************
	新控制板协议：继电器控制 同时只控制1路                                       
	status: true(开关闭合)；false(开关打开)
************************************************************************/
void ControlProtocol::makeRelaySendBuf(UINT8 portno, bool status)
{
	m_sendBuf = "";
	m_sendBuf.append(START_CODE).append(FUNC_RELAY);
	UINT8 relay_num = 0x01; //控制的继电器数量 1路
	m_sendBuf.append(relay_num);
	m_sendBuf.append(portno); //第protno路继电器
	float a = 2;
	UINT8 code0 = 0x00;
	UINT8 data;
	UINT8 st = status ? 0xFF : 0x00;
	
	if (portno>=1 && portno<=8)
	{
		data = (UINT8)pow(a, (portno-1)) & st;
		m_sendBuf.append(data).append(code0).append(code0);
	}
	else if (portno>=9 && portno<=16)
	{
		data = (UINT8)pow(a, (portno-9)) & st;;
		m_sendBuf.append(code0).append(data).append(code0);
	}
	else if (portno>=17 && portno<=24)
	{
		data = (UINT8)pow(a, (portno-17)) & st;;
		m_sendBuf.append(code0).append(code0).append(data);
	}
	UINT8 cs = START_CODE + FUNC_RELAY + relay_num + portno + code0 + code0 + data;
	m_sendBuf.append(cs).append(END_CODE);
}


//控制调节阀 同时只控制一路
void ControlProtocol::makeRegulateSendBuf(UINT8 portno, UINT16 degree)
{
	m_sendBuf = "";
	m_sendBuf.append(START_CODE).append(FUNC_REGULATE);
	float a = 2;
	UINT8 regulate_num = (UINT8)pow(a, (portno-1)); //控制的调节阀数量 只控制1路
	m_sendBuf.append(regulate_num);
	QString degStr = QString("%1").arg(degree, 4, 16).replace(" ", "0");
	bool ok;
	UINT8 dataL = degStr.right(2).toUInt(&ok, 16);//开度 低字节 需要实验和计算得到
	UINT8 dataH = degStr.left(2).toUInt(&ok, 16); //开度 高字节
// 	UINT8 dataL = 0x66;
// 	UINT8 dataH = 0x01;
	m_sendBuf.append(dataL).append(dataH);
	UINT8 cs = START_CODE + FUNC_REGULATE + regulate_num + dataL + dataH;
	m_sendBuf.append(cs).append(END_CODE);
}

//查询从机状态
void ControlProtocol::makeQuerySendBuf()
{
	m_sendBuf = "";
	m_sendBuf.append(START_CODE).append(FUNC_QUERY);
	UINT8 code0 = 0x00;
	m_sendBuf.append(code0).append(code0).append(code0).append(code0);
	UINT8 cs = START_CODE + FUNC_QUERY + code0 + code0 + code0 + code0;
	m_sendBuf.append(cs).append(END_CODE);
}


QByteArray ControlProtocol::getSendBuf()
{
	return m_sendBuf;
}


//解帧
UINT8 ControlProtocol::readControlComBuffer(QByteArray tmp)
{
// 	qDebug()<<"readControlComBuffer ControlProtocol thread:"<<QThread::currentThreadId();
	UINT8 ret = 0x00;
	int state = START_STATE;
	UINT8 ch = 0; //无符号8位数字
	int number = tmp.size();

	int m=0;
	int num_i=0;
	UINT8 ck=0; //程序计算的检验码
	for (m=0; m<number; m++)
	{
		ch = (UINT8)tmp.at(m);
// 		qDebug()<<"read data is:"<<ch;
		switch(state)
		{
		case START_STATE: //8位无符号
			{
				if (ch == START_CODE)
				{
					m_conFrame->startCode = START_CODE;
					state = FUNC_STATE;
				}
				break;
			}
		case FUNC_STATE: //8位无符号
			{   
				if (ch == FUNC_RELAY) //功能码-继电器控制
				{
					m_conFrame->funcCode = FUNC_RELAY;
					state = DATA_STATE;
					break;
				}
				if (ch == FUNC_REGULATE) //功能码-调节阀控制
				{
					m_conFrame->funcCode = FUNC_REGULATE;
					state = DATA_STATE;
					break;
				}
				if (ch == FUNC_QUERY) //功能码-查询
				{
					m_conFrame->funcCode = FUNC_QUERY;
					state = DATA_STATE;
					break;
				}
				if (ch == FUNC_BALANCE) //功能码-天平采集
				{
					m_conFrame->funcCode = FUNC_BALANCE;
					state = DATA_STATE;
					break;
				}
				break;
			}

		case DATA_STATE: //8位无符号
			{
				if (m_conFrame->funcCode == FUNC_RELAY) //继电器
				{
					m_conFrame->data[num_i++] = ch;
					if (num_i == RELAY_DATA_LENGTH)
					{
						state = CS_STATE;
						num_i = 0;
					}
				}
				if (m_conFrame->funcCode == FUNC_REGULATE) //调节阀
				{
					m_conFrame->data[num_i++] = ch;
					if (num_i == REGU_DATA_LENGTH)
					{
						state = CS_STATE;
						num_i = 0;
					}
				}
				if (m_conFrame->funcCode == FUNC_QUERY)  //查询
				{
					m_conFrame->data[num_i++] = ch;
					if (num_i == DATA_LENGTH)
					{
						state = CS_STATE;
						num_i = 0;
					}
				}
				if (m_conFrame->funcCode == FUNC_BALANCE)  //天平
				{
					m_conFrame->data[num_i++] = ch;
					if (num_i == BAL_DATA_LENGTH)
					{
						state = CS_STATE;
						num_i = 0;
					}
				}

				break;
			}    
		case CS_STATE: //8位无符号
			{
				m_conFrame->check = ch;
				state = END_STATE;
				break;
			} 
		case END_STATE: //8位无符号
			{
				m_conFrame->endCode = END_CODE;
				state = START_STATE;
				ck = CountCheck(m_conFrame);
				if (ck == m_conFrame->check) //校验通过
				{
					analyseFrame();
// 					qDebug()<<"check is ok 校验通过";
					ret = m_conFrame->funcCode; //以功能码返回，便于区分
				}
				break;
			} 
		default :
			{
				state = START_STATE;
				break;
			}
		} //END OF switch(state)        
	} //END OF for (m=0; m<number; m++)
	
	return ret;
}

UINT8 ControlProtocol::CountCheck(Con_Frame_Struct *pFrame)
{
	if (NULL == pFrame)
	{
		return 0;
	}

	UINT8 cs = pFrame->startCode + pFrame->funcCode;
	int i = 0;
	if (pFrame->funcCode == FUNC_RELAY)
	{
		for (i=0; i<RELAY_DATA_LENGTH; i++)
		{
			cs += pFrame->data[i];
		}
	}
	if (pFrame->funcCode == FUNC_REGULATE)
	{
		for (i=0; i<REGU_DATA_LENGTH; i++)
		{
			cs += pFrame->data[i];
		}
	}
	if (pFrame->funcCode == FUNC_QUERY)
	{
		for (i=0; i<DATA_LENGTH; i++)
		{
			cs += pFrame->data[i];
		}
	}
	if (pFrame->funcCode == FUNC_BALANCE)
	{
		for (i=0; i<BAL_DATA_LENGTH; i++)
		{
			cs += pFrame->data[i];
		}
	}

	return cs;
}

void ControlProtocol::analyseFrame()
{
	if (NULL==m_conFrame)
	{
		return;
	}

	if (m_conFrame->funcCode == FUNC_BALANCE) //天平采集
	{
		m_balValueStr = ""; //先清零
		char ch;
		UINT8 ch1, ch2;
		ch1 = m_conFrame->data[BAL_DATA_LENGTH-1];
		ch2 = m_conFrame->data[BAL_DATA_LENGTH-2];
		if (ch1==ASCII_LF && ch2==ASCII_CR) //0x0A换行; 0x0D回车（表示一帧结束）
		{
			for (int i=6; i<16; i++)
			{
				ch = m_conFrame->data[i];
				m_balValueStr += ch;
			}
// 			m_balValueStr.replace(" ", "0");
		}
	}
}

Con_Frame_Struct * ControlProtocol::getConFrame()
{
	return m_conFrame;
}

QString ControlProtocol::getBalanceValue()
{
	return m_balValueStr;
}