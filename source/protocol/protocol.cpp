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
				2014-9-10增加德鲁热量表通讯协议(上位机与热量表直接通讯)
***********************************************/

#include <QtCore/QDebug>
#include <QtCore/QDateTime>
#include <QStringList>

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
// 	qDebug()<<"TempProtocol::makeSendBuf thread:"<<QThread::currentThreadId();
	m_sendBuf = "";
// 	printf("111111 file %s, line %d\n", __FILE__, __LINE__);
	m_sendBuf.append(ADDR_CODE_FIRST).append(ADDR_CODE_FIRST);//地址代号
// 	printf("222222 file %s, line %d\n", __FILE__, __LINE__);
	m_sendBuf.append(READ_CODE); //标准读代码
// 	printf("333333 file %s, line %d\n", __FILE__, __LINE__);
	UINT8 paracode = 0x00; //参数代号
	m_sendBuf.append(paracode); 
// 	printf("444444 file %s, line %d\n", __FILE__, __LINE__);
	UINT8 datacode = 0x00;
	m_sendBuf.append(datacode).append(datacode);
// 	printf("555555 file %s, line %d\n", __FILE__, __LINE__);
	UINT16 checkcode = paracode*256 + READ_CODE + ADDR_FIRST;
	QString checkstr;
	checkstr = QString("%1").arg(checkcode, 4, 16).replace(" ", "0");
	bool ok;
	UINT8 lownum = checkstr.right(2).toUInt(&ok, 16);
	UINT8 hightnum = checkstr.left(2).toUInt(&ok, 16);
// 	printf("666666 file %s, line %d\n", __FILE__, __LINE__);
	m_sendBuf.append(lownum).append(hightnum);
// 	printf("777777 file %s, line %d\n", __FILE__, __LINE__);
}

//解帧 获取温度值
bool TempProtocol::readTemperComBuffer(QByteArray tmp)
{
// 	qDebug()<<"TempProtocol::readTemperComBuffer thread:"<<QThread::currentThreadId();
	int number = tmp.size();
	Q_ASSERT(number > 0);
	memset(m_tempFrame, 0, sizeof(Temp_Frame_Struct));
	bool ret = false;
	int state = PV_STATE;

	UINT8 uch = 0; //无符号8位数字
	INT8  ch = 0;  //有符号8位数字
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
					m_tempFrame->cs = uch;
					check_i++;
					break;
				}
				if (check_i == 1) //高字节
				{
					ch = (INT8)tmp.at(m);
					m_tempFrame->cs = ch*256 + m_tempFrame->cs;
					check_i = 0;
					state = PV_STATE;
					ck = CountCheck(m_tempFrame);
					if (ck == m_tempFrame->cs) //校验通过
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
	if (NULL == m_tempFrame)
	{
		return;
	}
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
	int a = m_sendBuf.size();
	return m_sendBuf;
}


/***********************************************
类名：BalanceProtocol
功能：天平协议
************************************************/
BalanceProtocol::BalanceProtocol()
{
	m_balValue = 0.0;
	m_lastValue = 0.0;
	m_count = 0;
}

BalanceProtocol::~BalanceProtocol()
{
}

//解析赛多利斯天平串口数据
bool BalanceProtocol::readBalanceComBuffer(QByteArray tmp)
{
// 	qDebug()<<"BalanceProtocol::readBalanceComBuffer thread:"<<QThread::currentThreadId();
	bool ret = false;
	int number = tmp.size();
	if (number < BAL_DATA_LENGTH) //一帧通常是22字节；
	{
		return ret;
	}

	if (m_count>=10000)
	{
		m_count = 1;
	}
	QByteArray whtArray;
	m_balValue = 0.0;

	int m=0;
	char ch;
	UINT8 ch1, ch2;
	bool ok;
	for (int i=number; i>0; i--)
	{
		ch1 = (UINT8)tmp.at(i-1);
		if (ch1==ASCII_LF && i>=16) //0x0A换行（表示一帧结束）
		{
			for (m=i-16; m<i-6; m++)
			{
				ch = tmp.at(m);
				whtArray.append(ch);
			}
			m_balValue = whtArray.replace(" ", 0).toFloat(&ok);
			if (ok)  //数字转换成功
			{
				m_count++;
				if (m_count<=1)
				{
					m_lastValue = m_balValue;
					ret = true;
					break;
				}
				if (fabs(m_balValue-m_lastValue) <= 100.0) //过滤突变数据
				{
					m_lastValue = m_balValue;
					ret = true;
					break;
				}
			}
		}
	}
	return ret;
}

float BalanceProtocol::getBalanceValue()
{
	return m_balValue;
}


/***********************************************
类名：ControlProtocol
功能：下位机控制协议基类
************************************************/
CtrlProtocol::CtrlProtocol()
{
	m_sendBuf = "";
}

CtrlProtocol::~CtrlProtocol()
{
}

QByteArray CtrlProtocol::getSendBuf()
{
	return m_sendBuf;
}

/***********************************************
类名：NewCtrlProtocol
功能：下位机控制协议-新控制板
************************************************/
NewCtrlProtocol::NewCtrlProtocol()
{
	m_ctrlFrame = new NewCtrl_Frame_Struct();
	memset(m_ctrlFrame, 0, sizeof(NewCtrl_Frame_Struct));

	m_balValue = 0.0;
};

NewCtrlProtocol::~NewCtrlProtocol()
{
	if (m_ctrlFrame)
	{
		delete m_ctrlFrame;
		m_ctrlFrame = NULL;
	}
};

/************************************************************************
	新控制板协议：继电器控制 同时只控制1路                                       
	status: true(阀门打开)；false(阀门关闭)
************************************************************************/
void NewCtrlProtocol::makeFrameOfCtrlRelay(UINT8 portno, bool status)
{
	qDebug()<<"NewCtrlProtocol::makeFrameOfCtrlRelay thread:"<<QThread::currentThreadId();
	Q_ASSERT(portno >= 0);
	m_sendBuf = "";
	m_sendBuf.append(CTRL_START_CODE).append(CTRL_FUNC_RELAY);
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
		data = (UINT8)pow(a, (portno-17)) & st;
		m_sendBuf.append(code0).append(code0).append(data);
	}
	UINT8 cs = CTRL_START_CODE + CTRL_FUNC_RELAY + relay_num + portno + code0 + code0 + data;
	m_sendBuf.append(cs).append(CTRL_END_CODE);
}

//控制调节阀 同时只控制一路
void NewCtrlProtocol::makeFrameOfCtrlRegulate(UINT8 portno, UINT16 degree)
{
	Q_ASSERT(portno >= 0);
	m_sendBuf = "";
	m_sendBuf.append(CTRL_START_CODE).append(CTRL_FUNC_REGULATE);
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
	UINT8 cs = CTRL_START_CODE + CTRL_FUNC_REGULATE + regulate_num + dataL + dataH;
	m_sendBuf.append(cs).append(CTRL_END_CODE);
}

//查询从机状态
void NewCtrlProtocol::makeFrameOfCtrlQuery()
{
	m_sendBuf = "";
	m_sendBuf.append(CTRL_START_CODE).append(CTRL_FUNC_QUERY);
	UINT8 code0 = 0x00;
	m_sendBuf.append(code0).append(code0).append(code0).append(code0);
	UINT8 cs = CTRL_START_CODE + CTRL_FUNC_QUERY + code0 + code0 + code0 + code0;
	m_sendBuf.append(cs).append(CTRL_END_CODE);
}

//控制水泵
void NewCtrlProtocol::makeFrameOfCtrlWaterPump(UINT8 portno, bool status)
{

}

//设置变频器频率
void NewCtrlProtocol::makeFrameOfSetDriverFreq(int freq)
{

}

//解帧
UINT8 NewCtrlProtocol::readCtrlComBuffer(QByteArray tmp)
{
// 	qDebug()<<"readControlComBuffer ControlProtocol thread:"<<QThread::currentThreadId();
	UINT8 ret = 0x00;
	int state = CTRL_START_STATE;
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
		case CTRL_START_STATE: //8位无符号
			{
				if (ch == CTRL_START_CODE)
				{
					m_ctrlFrame->startCode = CTRL_START_CODE;
					state = CTRL_FUNC_STATE;
				}
				break;
			}
		case CTRL_FUNC_STATE: //8位无符号
			{   
				if (ch == CTRL_FUNC_RELAY) //功能码-继电器控制
				{
					m_ctrlFrame->funcCode = CTRL_FUNC_RELAY;
					state = CTRL_DATA_STATE;
					break;
				}
				if (ch == CTRL_FUNC_REGULATE) //功能码-调节阀控制
				{
					m_ctrlFrame->funcCode = CTRL_FUNC_REGULATE;
					state = CTRL_DATA_STATE;
					break;
				}
				if (ch == CTRL_FUNC_QUERY) //功能码-查询
				{
					m_ctrlFrame->funcCode = CTRL_FUNC_QUERY;
					state = CTRL_DATA_STATE;
					break;
				}
				if (ch == CTRL_FUNC_BALANCE) //功能码-天平采集
				{
					m_ctrlFrame->funcCode = CTRL_FUNC_BALANCE;
					state = CTRL_DATA_STATE;
					break;
				}
				break;
			}

		case CTRL_DATA_STATE: //8位无符号
			{
				if (m_ctrlFrame->funcCode == CTRL_FUNC_RELAY) //继电器
				{
					m_ctrlFrame->data[num_i++] = ch;
					if (num_i == RELAY_DATA_LENGTH)
					{
						state = CTRL_CS_STATE;
						num_i = 0;
					}
				}
				if (m_ctrlFrame->funcCode == CTRL_FUNC_REGULATE) //调节阀
				{
					m_ctrlFrame->data[num_i++] = ch;
					if (num_i == REGU_DATA_LENGTH)
					{
						state = CTRL_CS_STATE;
						num_i = 0;
					}
				}
				if (m_ctrlFrame->funcCode == CTRL_FUNC_QUERY)  //查询
				{
					m_ctrlFrame->data[num_i++] = ch;
					if (num_i == DATA_LENGTH)
					{
						state = CTRL_CS_STATE;
						num_i = 0;
					}
				}
				if (m_ctrlFrame->funcCode == CTRL_FUNC_BALANCE)  //天平
				{
					m_ctrlFrame->data[num_i++] = ch;
					if (num_i == BAL_DATA_LENGTH)
					{
						state = CTRL_CS_STATE;
						num_i = 0;
					}
				}

				break;
			}    
		case CTRL_CS_STATE: //8位无符号
			{
				m_ctrlFrame->cs = ch;
				state = CTRL_END_STATE;
				break;
			} 
		case CTRL_END_STATE: //8位无符号
			{
				m_ctrlFrame->endCode = CTRL_END_CODE;
				state = CTRL_START_STATE;
				ck = CountCheck(m_ctrlFrame);
				if (ck == m_ctrlFrame->cs) //校验通过
				{
					analyseFrame();
// 					qDebug()<<"check is ok 校验通过";
					ret = m_ctrlFrame->funcCode; //以功能码返回，便于区分
				}
				break;
			} 
		default :
			{
				state = CTRL_START_STATE;
				break;
			}
		} //END OF switch(state)        
	} //END OF for (m=0; m<number; m++)

	return ret;
}

UINT8 NewCtrlProtocol::CountCheck(NewCtrl_Frame_Struct *pFrame)
{
	if (NULL == pFrame)
	{
		return 0;
	}

	UINT8 cs = pFrame->startCode + pFrame->funcCode;
	int i = 0;
	if (pFrame->funcCode == CTRL_FUNC_RELAY)
	{
		for (i=0; i<RELAY_DATA_LENGTH; i++)
		{
			cs += pFrame->data[i];
		}
	}
	if (pFrame->funcCode == CTRL_FUNC_REGULATE)
	{
		for (i=0; i<REGU_DATA_LENGTH; i++)
		{
			cs += pFrame->data[i];
		}
	}
	if (pFrame->funcCode == CTRL_FUNC_QUERY)
	{
		for (i=0; i<DATA_LENGTH; i++)
		{
			cs += pFrame->data[i];
		}
	}
	if (pFrame->funcCode == CTRL_FUNC_BALANCE)
	{
		for (i=0; i<BAL_DATA_LENGTH; i++)
		{
			cs += pFrame->data[i];
		}
	}

	return cs;
}

void NewCtrlProtocol::analyseFrame()
{
	if (NULL==m_ctrlFrame)
	{
		return;
	}

	if (m_ctrlFrame->funcCode == CTRL_FUNC_BALANCE) //天平采集
	{
		QByteArray whtArray;
		m_balValue = 0.0; //先清零
		char ch;
		UINT8 ch1, ch2;
		ch1 = m_ctrlFrame->data[BAL_DATA_LENGTH-1];
		ch2 = m_ctrlFrame->data[BAL_DATA_LENGTH-2];
		if (ch1==ASCII_LF && ch2==ASCII_CR) //0x0A换行; 0x0D回车（表示一帧结束）
		{
			for (int i=6; i<16; i++)
			{
				ch = m_ctrlFrame->data[i];
				whtArray.append(ch);
			}
 			m_balValue = whtArray.replace(" ", "0").toFloat();
		}
	}
}

NewCtrl_Frame_Struct * NewCtrlProtocol::getConFrame()
{
	return m_ctrlFrame;
}

float NewCtrlProtocol::getBalanceValue()
{
	return m_balValue;
}

/***********************************************
类名：OldCtrlProtocol
功能：下位机控制协议-老控制板
************************************************/
OldCtrlProtocol::OldCtrlProtocol()
{
	portCloseMap.insert(1, 0xE1);
	portCloseMap.insert(2, 0xE3);
	portCloseMap.insert(3, 0xE5);
	portCloseMap.insert(4, 0xE7);
	portCloseMap.insert(5, 0xE9);
	portCloseMap.insert(6, 0xEB);
	portCloseMap.insert(7, 0xED);
	portCloseMap.insert(8, 0xEF);

	portOpenMap.insert(1, 0xE0);
	portOpenMap.insert(2, 0xE2);
	portOpenMap.insert(3, 0xE4);
	portOpenMap.insert(4, 0xE6);
	portOpenMap.insert(5, 0xE8);
	portOpenMap.insert(6, 0xEA);
	portOpenMap.insert(7, 0xEC);
	portOpenMap.insert(8, 0xEE);
}

OldCtrlProtocol::~OldCtrlProtocol()
{

}

/************************************************************************
	老控制板协议：继电器控制 同时只控制1路                                       
	status: true(阀门打开,闭合继电器)；false(阀门关闭，断开继电器)
************************************************************************/
void OldCtrlProtocol::makeFrameOfCtrlRelay(UINT8 portno, bool status)
{
	qDebug()<<"OldCtrlProtocol::makeFrameOfCtrlRelay thread:"<<QThread::currentThreadId();
	UINT8 zeroCode = 0x00;
	m_sendBuf = "";
	if (status) //true(阀门打开,闭合继电器)
	{
		m_sendBuf.append(0xFF).append(portCloseMap[portno]).append(zeroCode)\
			.append(zeroCode).append(0xFE);
	}
	else //false(阀门关闭，断开继电器)
	{
		m_sendBuf.append(0xFF).append(portOpenMap[portno]).append(zeroCode)\
			.append(zeroCode).append(0xFE);
	}
}

//控制调节阀 同时只控制一路
void OldCtrlProtocol::makeFrameOfCtrlRegulate(UINT8 portno, UINT16 degree)
{

}

//查询从机状态
void OldCtrlProtocol::makeFrameOfCtrlQuery()
{
}

//控制水泵开关
void OldCtrlProtocol::makeFrameOfCtrlWaterPump(UINT8 portno, bool status)
{
	UINT8 zeroCode = 0x00;
	m_sendBuf = "";
	if (status) //true 开水泵
	{
		m_sendBuf.append(0xFF).append(0xF9).append(zeroCode).append(zeroCode).append(0xFE);
	}
	else //false 关水泵
	{
		m_sendBuf.append(0xFF).append(0xFA).append(zeroCode).append(zeroCode).append(0xFE);
	}
}

//设置变频器频率
void OldCtrlProtocol::makeFrameOfSetDriverFreq(int freq)
{
	int data = int(freq*4095/50);//0~50Hz对应0~4095
	UINT8 dataH = data/256;
	UINT8 dataL = data%256;
	m_sendBuf = "";
	m_sendBuf.append(0xFF).append(0xF8).append(dataH).append(dataL).append(0xFE);
}


//解帧
UINT8 OldCtrlProtocol::readCtrlComBuffer(QByteArray tmp)
{
	return 0;
}

void OldCtrlProtocol::analyseFrame()
{
}

//控制打压泵开关
void OldCtrlProtocol::makeFrameOfCtrlPressPump(bool status)
{
	UINT8 zeroCode = 0x00;
	m_sendBuf = "";
	if (status) //开打压泵
	{
		m_sendBuf.append(0xFF).append(0xFB).append(zeroCode).append(zeroCode).append(0xFE);
	}
	else //false 关打压泵
	{
		m_sendBuf.append(0xFF).append(0xFC).append(zeroCode).append(zeroCode).append(0xFE);
	}
}


/***********************************************
类名：MeterProtocol
功能：热量表通讯协议基类
************************************************/
MeterProtocol::MeterProtocol()
{
	m_sendBuf = "";
}

MeterProtocol::~MeterProtocol()
{
}

//获取组帧结果
QByteArray MeterProtocol::getSendFrame()
{
	return m_sendBuf;
}


QString MeterProtocol::getFullMeterNo()
{
	return m_fullMeterNo;
}

QString MeterProtocol::getFlow()
{
	return m_flow;
}

QString MeterProtocol::getInTemper()
{
	return m_inTemper;
}

QString MeterProtocol::getOutTemper()
{
	return m_outTemper;
}

QString MeterProtocol::getHeat()
{
	return m_heat;
}

QString MeterProtocol::getDate()
{
	return m_date;
}

QString MeterProtocol::getBigCoe()
{
	return m_bigCoe;
}

QString MeterProtocol::getMid2Coe()
{
	return m_mid2Coe;
}

QString MeterProtocol::getMid1Coe()
{
	return m_mid1Coe;
}

QString MeterProtocol::getSmallCoe()
{
	return m_smallCoe;
}


/***********************************************
类名：DeluMeterProtocol
功能：热量表通讯协议-德鲁热量表
************************************************/
DeluMeterProtocol::DeluMeterProtocol()
{
	m_deluMeterFrame = new DeluMeter_Frame_Struct();
	memset(m_deluMeterFrame, 0, sizeof(DeluMeter_Frame_Struct));
}

DeluMeterProtocol::~DeluMeterProtocol()
{
	if (m_deluMeterFrame)
	{
		delete m_deluMeterFrame;
		m_deluMeterFrame = NULL;
	}
}

//计算"校验码"
UINT8 DeluMeterProtocol::CountCheck(DeluMeter_Frame_Struct *pFrame)
{
	if (NULL == pFrame)
	{
		return 0;
	}

	UINT8 cs = 0;
	cs = pFrame->startCode + pFrame->typeCode;
	for (int i=0; i<METER_ADDR_LEN; i++)
	{
		cs += pFrame->addr[i];
	}
	cs += pFrame->ctrlCode;
	cs += pFrame->dataLen;
	for (int j=0; j<METER_DATAID_LEN; j++)
	{
		cs += pFrame->dataID[j];
	}
	cs += pFrame->sn;
	for (int m=0; m<METER_DATA_LEN; m++)
	{
		cs += pFrame->data[m];
	}

	return cs; 
}

//解帧
UINT8 DeluMeterProtocol::readMeterComBuffer(QByteArray tmp)
{
	qDebug()<<"DeluMeterProtocol::readMeterComBuffer thread:"<<QThread::currentThreadId();

	UINT8 ret = 0x00;
	int state = METER_START_STATE;
	UINT8 ch = 0; //无符号8位数字
	int number = tmp.size();

	int m=0;
	int addr_num=0, dataID_num=0, data_num=0;
	UINT8 ck=0; //程序计算的检验码
	for (m=0; m<number; m++)
	{
		ch = (UINT8)tmp.at(m);
		// 		qDebug()<<"read data is:"<<ch;
		if (ch == METER_PREFIX_CODE)
		{
			continue;
		}
		switch(state)
		{
		case METER_START_STATE: //
			{
				if (ch == METER_START_CODE)
				{
					m_deluMeterFrame->startCode = METER_START_CODE;
					state = METER_TYPE_STATE;
				}
				break;
			}
		case METER_TYPE_STATE: //
			{   
				if (ch == METER_TYPE_ANSWER_CODE) //响应
				{
					m_deluMeterFrame->typeCode = ch;
					state = METER_ADDR_STATE;
				}
				break;
			}

		case METER_ADDR_STATE: //
			{
				m_deluMeterFrame->addr[addr_num++] = ch;
				if (addr_num == METER_ADDR_LEN)
				{
					state = METER_CTRL_STATE;
					addr_num = 0;
				}
				break;
			}    
		case METER_CTRL_STATE: //
			{
				m_deluMeterFrame->ctrlCode = ch;
				state = METER_DATALEN_STATE;
				break;
			} 
		case METER_DATALEN_STATE: //
			{
				m_deluMeterFrame->dataLen = ch;
				state = METER_DATAID_STATE;
				break;
			} 
		case METER_DATAID_STATE: //
			{
				m_deluMeterFrame->dataID[dataID_num++] = ch;
				if (dataID_num == METER_DATAID_LEN)
				{
					state = METER_SN_STATE;
					dataID_num = 0;
				}
				break;
			} 
		case METER_SN_STATE: //序列号
			{
				m_deluMeterFrame->sn = ch;
				state = METER_DATA_STATE;
				break;
			} 
		case METER_DATA_STATE: //
			{
				m_deluMeterFrame->data[data_num++] = ch;
				if (data_num == METER_DATA_LEN)
				{
					state = METER_CS_STATE;
					data_num = 0;
				}
				break;
			} 
		case METER_CS_STATE: //
			{
				m_deluMeterFrame->cs = ch;
				state = METER_END_STATE;
				break;
			} 
		case METER_END_STATE: //
			{
				m_deluMeterFrame->endCode = ch;
				state = METER_START_STATE;
				ck = CountCheck(m_deluMeterFrame);
				if (ck == m_deluMeterFrame->cs) //校验通过
				{
					analyseFrame();
					ret = 1; //
					qDebug()<<"check is ok 校验通过";
				}
				break;
			} 
		default :
			{
				state = METER_START_STATE;
				break;
			}
		} //END OF switch(state)        
	} //END OF for (m=0; m<number; m++)

	return ret;
}

void DeluMeterProtocol::analyseFrame()
{
	if (NULL == m_deluMeterFrame)
	{
		return;
	}

	//表号
	m_fullMeterNo = "";
	for (int i=METER_ADDR_LEN-1; i>=0; i--)
	{
		m_fullMeterNo.append(QString("%1").arg(m_deluMeterFrame->addr[i], 2, 16)).replace(' ', '0');
	}

	//供水温度
	m_inTemper = "";
	m_inTemper.append(QString("%1%2.%3").arg(m_deluMeterFrame->data[2], 2, 16)\
		.arg(m_deluMeterFrame->data[1], 2, 16).arg(m_deluMeterFrame->data[0], 2, 16));
	m_inTemper.replace(' ', '0');

	//流量
	m_flow = "";
	m_flow.append(QString("%1.%2%3%4").arg(m_deluMeterFrame->data[9], 2, 16)\
		.arg(m_deluMeterFrame->data[8], 2, 16).arg(m_deluMeterFrame->data[7], 2, 16)\
		.arg(m_deluMeterFrame->data[6], 2, 16));
	m_flow.replace(' ', '0');

	//热量
	m_heat = "";
	m_heat.append(QString("%1%2.%3%4").arg(m_deluMeterFrame->data[14], 2, 16)\
		.arg(m_deluMeterFrame->data[13], 2, 16).arg(m_deluMeterFrame->data[12], 2, 16)\
		.arg(m_deluMeterFrame->data[11], 2, 16));
	m_heat.replace(' ', '0');

	//大流量点流量系数
	m_bigCoe = "";
	m_bigCoe.append(QString("%1%2").arg(m_deluMeterFrame->data[33], 2, 16)\
		.arg(m_deluMeterFrame->data[32], 2, 16));
	m_bigCoe.replace(' ', '0');

	//中流二流量系数
	m_mid2Coe = "";
	m_mid2Coe.append(QString("%1%2").arg(m_deluMeterFrame->data[35], 2, 16)\
		.arg(m_deluMeterFrame->data[34], 2, 16));
	m_mid2Coe.replace(' ', '0');

	//中流一流量系数
	m_mid1Coe = "";
	m_mid1Coe.append(QString("%1%2").arg(m_deluMeterFrame->data[37], 2, 16)\
		.arg(m_deluMeterFrame->data[36], 2, 16));
	m_mid1Coe.replace(' ', '0');

	//小流量点流量系数
	m_smallCoe = "";
	m_smallCoe.append(QString("%1%2").arg(m_deluMeterFrame->data[39], 2, 16)\
		.arg(m_deluMeterFrame->data[38], 2, 16));
	m_smallCoe.replace(' ', '0');

	//回水温度
	m_outTemper = "";
	m_outTemper.append(QString("%1%2.%3").arg(m_deluMeterFrame->data[48], 2, 16)\
		.arg(m_deluMeterFrame->data[47], 2, 16).arg(m_deluMeterFrame->data[46], 2, 16));
	m_outTemper.replace(' ', '0');

	//日期
	m_date = "";
	m_date.append(QString("%1%2%3%4").arg(m_deluMeterFrame->data[52], 2, 16)\
		.arg(m_deluMeterFrame->data[51], 2, 16).arg(m_deluMeterFrame->data[50], 2, 16).\
		arg(m_deluMeterFrame->data[49], 2, 16));
	m_date.replace(' ', '0');

}

// 组帧：广播地址读表
void DeluMeterProtocol::makeFrameOfReadMeter()
{
	qDebug()<<"DeluMeterProtocol::makeFrameOfReadMeter thread:"<<QThread::currentThreadId();

	m_sendBuf = "";

	for (int i=0; i<METER_WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//唤醒红外
	}

	for (int j=0; j<METER_PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //前导字节
	}

	m_sendBuf.append(METER_START_CODE);//起始符
	m_sendBuf.append(METER_TYPE_ASK_CODE); //仪表类型 请求
	for (int m=0; m<METER_ADDR_LEN; m++)
	{
		m_sendBuf.append(METER_ADDR_CODE); //广播地址
	}
	m_sendBuf.append(METER_CTRL_CODE);//控制码
	m_sendBuf.append(0x03);//数据长度
	m_sendBuf.append(0x3F).append(0x90); //数据标识
	m_sendBuf.append(0x03);//序列号
	UINT8 cs = METER_START_CODE + METER_TYPE_ASK_CODE + METER_ADDR_CODE*METER_ADDR_LEN + METER_CTRL_CODE\
		+ 0x03 + 0x3F + 0x90 + 0x03;
	m_sendBuf.append(cs);//校验码
	m_sendBuf.append(METER_END_CODE);//结束符
}

// 组帧：设置进入检定状态
void DeluMeterProtocol::makeFrameOfSetVerifyStatus()
{
	qDebug()<<"DeluMeterProtocol::makeFrameOfSetVerifyStatus thread:"<<QThread::currentThreadId();

	m_sendBuf = "";

	for (int i=0; i<METER_WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//唤醒红外
	}

	for (int j=0; j<METER_PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //前导字节
	}

	m_sendBuf.append(METER_START_CODE);//起始符
	m_sendBuf.append(METER_TYPE_ASK_CODE); //仪表类型 请求
	for (int m=0; m<METER_ADDR_LEN; m++)
	{
		m_sendBuf.append(METER_ADDR_CODE); //广播地址
	}

	UINT8 code0 = 0x00;
	m_sendBuf.append(0x33).append(code0).append(0x61).append(0x16);
}

// 组帧：修改表号(14位表号)
void DeluMeterProtocol::makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo)
{
	m_sendBuf = "";

	for (int i=0; i<METER_WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//唤醒红外
	}

	for (int j=0; j<METER_PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //前导字节
	}

	m_sendBuf.append(METER_START_CODE);//起始符
	m_sendBuf.append(METER_TYPE_ASK_CODE); //仪表类型 请求
	UINT8 cs = METER_START_CODE + METER_TYPE_ASK_CODE;
	UINT8 oldNo;
	bool ok;
	for (int m=METER_ADDR_LEN-1; m>=0; m--)
	{
		oldNo = oldMeterNo.mid(2*m, 2).toUInt(&ok, 16);
		m_sendBuf.append(oldNo); //旧表号
		cs += oldNo;
	}

	UINT8 code1 = 0x39;
	UINT8 code2 = 0x11;
	UINT8 code3 = 0x18;
	UINT8 code4 = 0xA0;
	UINT8 code5 = 0xAA;

	m_sendBuf.append(code1).append(code2).append(code3).append(code4).append(code5);
	cs += code1 + code2 + code3 + code4 + code5;

	UINT8 newNo;
	for (int n=METER_ADDR_LEN-1; n>=0; n--)
	{
		newNo = newMeterNo.mid(2*n, 2).toUInt(&ok, 16);
		m_sendBuf.append(newNo); //新表号
		cs += newNo;
	}

	UINT8 timeCode;
	QString currentTime = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");//"20150107125930"
	for (int p=6; p>=0; p--)
	{
		timeCode = currentTime.mid(2*p, 2).toUInt(&ok, 16);
		m_sendBuf.append(timeCode); //当前时间
		cs += timeCode;
	}

	m_sendBuf.append(cs).append(0x16);
}

/*
** 组帧：修改流量系数
** 输入参数：
	meterNO:表号，14位
	bigErr:大流量点误差，单位%
	mid2Err:中流二误差，单位%
	mid1Err:中流一误差，单位%
	smallErr:小流量点误差，单位%
*/
void DeluMeterProtocol::makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr)
{
	m_sendBuf = "";

	for (int i=0; i<METER_WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//唤醒红外
	}

	for (int j=0; j<METER_PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //前导字节
	}

	m_sendBuf.append(METER_START_CODE);//起始符
	m_sendBuf.append(METER_TYPE_ASK_CODE); //仪表类型 请求
	UINT8 cs = METER_START_CODE + METER_TYPE_ASK_CODE;
	UINT8 oldNo;
	bool ok;
	for (int m=METER_ADDR_LEN-1; m>=0; m--)
	{
		oldNo = meterNO.mid(2*m, 2).toUInt(&ok, 16);
		m_sendBuf.append(oldNo); //表号
		cs += oldNo;
	}

	UINT8 code1 = 0x36;
	UINT8 code2 = 0x0C;
	UINT8 code3 = 0xA0;
	UINT8 code4 = 0x19;
	UINT8 code5 = 0x06;
	UINT8 code6 = 0x00;
	m_sendBuf.append(code1).append(code2).append(code3).append(code4).append(code5).append(code6);
	cs += code1 + code2 + code3 + code4 + code5 + code6;

	QString bigCoe = QString::number(1/(1+bigErr/100), 'f', 3); //保留3位小数，四舍五入
	QString mid2Coe = QString::number(1/(1+mid2Err/100), 'f', 3);
	QString mid1Coe = QString::number(1/(1+mid1Err/100), 'f', 3);
	QString smallCoe = QString::number(1/(1+smallErr/100), 'f', 3);

	int bigDec = bigCoe.section(".", 1).toUInt()*4096.0/1000.0; //只取整数部分，不再进行四舍五入
	int mid2Dec = mid2Coe.section(".", 1).toUInt()*4096.0/1000.0;
	int mid1Dec = mid1Coe.section(".", 1).toUInt()*4096.0/1000.0;
	int smallDec = smallCoe.section(".", 1).toUInt()*4096.0/1000.0;

	QString big = QString::number(bigDec, 16).rightJustified(3, '0');
	QString mid2 = QString::number(mid2Dec, 16).rightJustified(3, '0');
	QString mid1 = QString::number(mid1Dec, 16).rightJustified(3, '0');
	QString small = QString::number(smallDec, 16).rightJustified(3, '0');
	UINT8 A7 = big.right(2).toUInt(&ok, 16);
	UINT8 A6 = (bigCoe.left(1) + big.left(1)).toUInt(&ok, 16);
	UINT8 A5 = mid2.right(2).toUInt(&ok, 16);
	UINT8 A4 = (mid2Coe.left(1) + mid2.left(1)).toUInt(&ok, 16);
	UINT8 A3 = mid1.right(2).toUInt(&ok, 16);
	UINT8 A2 = (mid1Coe.left(1) + mid1.left(1)).toUInt(&ok, 16);
	UINT8 A1 = small.right(2).toUInt(&ok, 16);
	UINT8 A0 = (smallCoe.left(1) + small.left(1)).toUInt(&ok, 16);

	m_sendBuf.append(A7).append(A6).append(A5).append(A4).append(A3).append(A2).append(A1).append(A0);
	cs += A7 + A6 + A5 + A4 + A3 + A2 + A1 + A0;

	m_sendBuf.append(cs).append(0x16);
}

/*
** 组帧：修改流量系数
** 输入参数：
	meterNO:表号，14位
	bigErr:大流量点误差，单位%
	mid2Err:中流二误差，单位%
	mid1Err:中流一误差，单位%
	smallErr:小流量点误差，单位%
	oldCoe:热量表各流量点的原系数，无单位
*/
void DeluMeterProtocol::makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr, MeterCoe_PTR oldCoe)
{
	m_sendBuf = "";

	for (int i=0; i<METER_WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//唤醒红外
	}

	for (int j=0; j<METER_PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //前导字节
	}

	m_sendBuf.append(METER_START_CODE);//起始符
	m_sendBuf.append(METER_TYPE_ASK_CODE); //仪表类型 请求
	UINT8 cs = METER_START_CODE + METER_TYPE_ASK_CODE;
	UINT8 oldNo;
	bool ok;
	for (int m=METER_ADDR_LEN-1; m>=0; m--)
	{
		oldNo = meterNO.mid(2*m, 2).toUInt(&ok, 16);
		m_sendBuf.append(oldNo); //表号
		cs += oldNo;
	}

	UINT8 code1 = 0x36;
	UINT8 code2 = 0x0C;
	UINT8 code3 = 0xA0;
	UINT8 code4 = 0x19;
	UINT8 code5 = 0x06;
	UINT8 code6 = 0x00;
	m_sendBuf.append(code1).append(code2).append(code3).append(code4).append(code5).append(code6);
	cs += code1 + code2 + code3 + code4 + code5 + code6;

	QString bigCoe = QString::number(oldCoe->bigCoe/(1+bigErr/100), 'f', 3); //保留3位小数，四舍五入
	QString mid2Coe = QString::number(oldCoe->mid2Coe/(1+mid2Err/100), 'f', 3);
	QString mid1Coe = QString::number(oldCoe->mid1Coe/(1+mid1Err/100), 'f', 3);
	QString smallCoe = QString::number(oldCoe->smallCoe/(1+smallErr/100), 'f', 3);

	int bigDec = bigCoe.section(".", 1).toUInt()*4096.0/1000.0; //只取整数部分，不再进行四舍五入
	int mid2Dec = mid2Coe.section(".", 1).toUInt()*4096.0/1000.0;
	int mid1Dec = mid1Coe.section(".", 1).toUInt()*4096.0/1000.0;
	int smallDec = smallCoe.section(".", 1).toUInt()*4096.0/1000.0;

	QString big = QString::number(bigDec, 16).rightJustified(3, '0');
	QString mid2 = QString::number(mid2Dec, 16).rightJustified(3, '0');
	QString mid1 = QString::number(mid1Dec, 16).rightJustified(3, '0');
	QString small = QString::number(smallDec, 16).rightJustified(3, '0');
	UINT8 A7 = big.right(2).toUInt(&ok, 16);
	UINT8 A6 = (bigCoe.left(1) + big.left(1)).toUInt(&ok, 16);
	UINT8 A5 = mid2.right(2).toUInt(&ok, 16);
	UINT8 A4 = (mid2Coe.left(1) + mid2.left(1)).toUInt(&ok, 16);
	UINT8 A3 = mid1.right(2).toUInt(&ok, 16);
	UINT8 A2 = (mid1Coe.left(1) + mid1.left(1)).toUInt(&ok, 16);
	UINT8 A1 = small.right(2).toUInt(&ok, 16);
	UINT8 A0 = (smallCoe.left(1) + small.left(1)).toUInt(&ok, 16);

	m_sendBuf.append(A7).append(A6).append(A5).append(A4).append(A3).append(A2).append(A1).append(A0);
	cs += A7 + A6 + A5 + A4 + A3 + A2 + A1 + A0;

	m_sendBuf.append(cs).append(0x16);
}

/***********************************************
类名：TgMeterProtocol
功能：热量表通讯协议-天罡热量表
************************************************/
LiChMeterProtocol::LiChMeterProtocol()
{
}

LiChMeterProtocol::~LiChMeterProtocol()
{
}

UINT8 LiChMeterProtocol::CountCheck(DeluMeter_Frame_Struct *pFrame)
{
	return 0;
}

UINT8 LiChMeterProtocol::readMeterComBuffer(QByteArray tmp)
{
	return 0;
}

void LiChMeterProtocol::analyseFrame()
{

}

void LiChMeterProtocol::makeFrameOfReadMeter()
{

}

void LiChMeterProtocol::makeFrameOfSetVerifyStatus()
{

}

void LiChMeterProtocol::makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo)
{

}

void LiChMeterProtocol::makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr)
{

}

void LiChMeterProtocol::makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr, MeterCoe_PTR oldCoe)
{

}

/***********************************************
类名：sti1062ATempProtocol
功能：标准温度计-STI-1062A串口协议
************************************************/
sti1062ATempProtocol::sti1062ATempProtocol()
{
	m_state = DATA_STATE;
}

sti1062ATempProtocol::~sti1062ATempProtocol()
{

}

void sti1062ATempProtocol::makeSendBuf(sti1062Acommand command)
{
	switch(command)
	{
		case sti1062aT12:
			m_sendBuf = CHNT12;
			break;
		case sti1062aR12:
			m_sendBuf = CHNR12;
			break;
		case sti1062aT1:
			m_sendBuf = CHNT1;
			break;
		case sti1062aT2:
			m_sendBuf = CHNT2;
			break;
		case sti1062aR1:
			m_sendBuf = CHNR1;
			break;
		case sti1062aR2:
			m_sendBuf = CHNR2;
			break;
		default:
			m_sendBuf = CHNT12;
			break;
	}
}

QByteArray sti1062ATempProtocol::getSendBuf()
{
	return m_sendBuf;
}

bool sti1062ATempProtocol::readTemperComBuffer(QByteArray tmp)
{
	int number = tmp.size();
	//Q_ASSERT(number > 0);
	
	bool ret = false;
	char b = '\0';
	for (int i=0; i < number; i++)
	{
		b = tmp[i];
		switch(m_state)
		{
			case DATA_STATE:
				switch(b)
				{
					case ASCII_CR:
							m_state = END_STATE;
						break;
					default:
						ret = false;
						m_readBuf.append(b);
						break;
				}
				break;
			case END_STATE:
				switch(b)
				{
					case ASCII_LF:
						m_readBuf.append(b);
						ret = true;
						break;
					default:
						m_state = DATA_STATE;
						ret = false;
						m_readBuf.append(b);
						break;
				}
				break;
			default:
				break;
		}
	}

	if (ret)
	{
		m_valueStr = m_readBuf;
		m_readBuf.clear();
	}
	return ret;
}

QString sti1062ATempProtocol::getReadStr()
{
	return m_valueStr;
}
/***********************************************
类名：sti1062ATempProtocol END
************************************************/

/***********************************************
类名：lcModbusRTUFunc
功能：力创EDA9150A/9017产品, ModbusRTU通讯协议类
************************************************/
lcModbusRTUProtocol::lcModbusRTUProtocol()
{
	initParams();
}

lcModbusRTUProtocol::~lcModbusRTUProtocol()
{

}

void lcModbusRTUProtocol::initParams()
{
	m_calcDataLength = 0x0000;
	m_readDataLength = 0;
	m_crcValue.clear();
	m_readBuf.clear();
	m_state = init_state;
}

/*
** 读取力创模块9150A和9017的命令
** address, 力创模块的设备地址, 通常为0x01
** func, 功能码
** start, 欲读取的模块内部只读寄存器的开始地址
** regCount, 读取的集群器个数
*/
void lcModbusRTUProtocol::makeSendBuf(uchar address, lcModbusRTUFunc func, UINT16 start, UINT16 regCount)
{
	m_sendBuf.clear();
	m_sendBuf.append(address);
	m_sendBuf.append((uchar)(func));
	m_sendBuf.append((uchar)(start>>WORDLEN));
	m_sendBuf.append((uchar)(start));
	m_sendBuf.append((uchar)(regCount>>WORDLEN));
	m_sendBuf.append((uchar)(regCount));
	m_sendBuf.append(getCRCArray(calcModRtuCRC((uchar *)m_sendBuf.data(), m_sendBuf.length())));

	//printf("\nsendbuf:\n");
	//for (int i=0;i<m_sendBuf.length();i++)
	//{
	//	printf("%02X ", (uchar)m_sendBuf.at(i));
	//}
	//printf("\nsendbuf end:\n");
}

void lcModbusRTUProtocol::makeSendBuf(lcModSendCmd command)
{
	makeSendBuf(command.address, command.func, command.start, command.regCount);	
}

//不能一次性修改16路的数值, 模块不返回数据, 只能分两次, 每次8路
void lcModbusRTUProtocol::makeWriteBuf(lcMod9150AWriteCmd cmd)
{
	m_writeBuf.clear();
	m_writeBuf.append(cmd.address);
	m_writeBuf.append((uchar)(cmd.func));
	m_writeBuf.append((uchar)(cmd.start>>WORDLEN));
	m_writeBuf.append((uchar)(cmd.start));
	m_writeBuf.append((uchar)(cmd.regCount>>WORDLEN));
	m_writeBuf.append((uchar)(cmd.regCount));
	m_writeBuf.append((uchar)(cmd.ByteCount));
	for(int i=0;i<EDA_9150A_ROUTE_CNT/2;i++)
	{
		int diValue = cmd.pData[i];//通道号; 从DI[0]~DI[7], DI[8]~DI[15]
		for (int j=EDA9150A_ROUTE_BYTES-1;j>=0;j--)
		{			
			uchar b= (uchar)(diValue>>(j*WORDLEN));
			m_writeBuf.append(b);
		}
	}
	m_writeBuf.append(getCRCArray(calcModRtuCRC((uchar *)m_writeBuf.data(), m_writeBuf.length())));
}

QByteArray lcModbusRTUProtocol::getWriteBuf()
{
	return m_writeBuf;
}

//读取标准表脉冲数; 只能检测读取命令(0x03)的返回值, 不能检测其他命令的返回值
bool lcModbusRTUProtocol::readMeterComBuffer(QByteArray tmp)
{
	int number = tmp.size();
	//Q_ASSERT(number > 0);
	UINT16 dataLenInfo;//用于检验返回的数据长度信息是否正确
	UINT16 crc;//返回的crc校验值
	UINT16 calc_crc;//用于检验返回的crc校验值

	bool ret = false;
	char b = '\0';
	QString s;
	for (int i=0; i < number; i++)
	{
		b = tmp[i];
		switch(m_state)
		{
		case init_state:
			m_valueArray.clear();
			if(b == m_sendBuf.at(0))//发送的设备地址
			{
				m_readBuf.append(b);//加入设备地址
				m_state = address_state;
			}
			else//回应的地址位出错, 终止解析
			{
				qCritical() << "!!!!!!!address error!!!!!!!";
				qCritical() << "!!!!!!!m_sendBuf buf is :!!!!!!!";
				for (int idx=0;idx<m_sendBuf.length();idx++)
				{
					qCritical() << s.sprintf("%02X", (uchar)m_sendBuf.at(idx));
				}
				qCritical() << "!!!!!!!m_sendBuf buf end :!!!!!!!";

				qCritical() << "!!!!!!!tmp buf is :!!!!!!!";
				for (int idx=0;idx<tmp.length();idx++)
				{
					qCritical() << s.sprintf("%02X", (uchar)tmp.at(idx));
				}
				qCritical() << "!!!!!!!tmp buf end :!!!!!!!";

				qCritical() << "!!!!!!!address is :!!!!!!!";
				qCritical() << s.sprintf("%02X", (uchar)b);
				qCritical() << "!!!!!!!address end :!!!!!!!";

				qCritical() << "!!!!!!!m_readBuf buf is :!!!!!!!";
				for (int idx=0;idx<m_readBuf.length();idx++)
				{
					qCritical() << s.sprintf("%02X", (uchar)m_readBuf.at(idx));
				}
				qCritical() << "!!!!!!!m_readBuf buf end :!!!!!!!";
				initParams();
				return false;
			}
			break;
		case address_state:
			//printf("\naddress is: 0x%02X", m_sendBuf.at(3));
			if(b == m_sendBuf.at(1))//发送的功能码
			{
				m_readBuf.append(b);//加入功能码
				m_state = func_state;
			}
			else//回应的功能码出错, 终止解析
			{
				qCritical() << "!!!!!!!func error!!!!!!!";
				qCritical() << "!!!!!!!m_sendBuf buf is :!!!!!!!";
				for (int idx=0;idx<m_sendBuf.length();idx++)
				{
					qCritical() << s.sprintf("%02X", m_sendBuf.at(idx));
				}
				qCritical() << "!!!!!!!m_sendBuf buf end :!!!!!!!";

				qCritical() << "!!!!!!!tmp buf is :!!!!!!!";
				for (int idx=0;idx<tmp.length();idx++)
				{
					qCritical() << s.sprintf("%02X", tmp.at(idx));
				}
				qCritical() << "!!!!!!!tmp buf end :!!!!!!!";

				qCritical() << "!!!!!!!func is :!!!!!!!";
				qCritical() << s.sprintf("%02X", (uchar)b);
				qCritical() << "!!!!!!!func end :!!!!!!!";

				qCritical() << "!!!!!!!m_readBuf buf is :!!!!!!!";
				for (int idx=0;idx<m_readBuf.length();idx++)
				{
					qCritical() << s.sprintf("%02X", m_readBuf.at(idx));
				}
				qCritical() << "!!!!!!!m_readBuf buf end :!!!!!!!";
				initParams();
				return false;
			}
			break;
		case func_state:
			if (m_readBuf.length() == (MOD_ADDRESS_LEN+MOD_FUNC_LEN))
			{
				m_readBuf.append(b);//加入数据长度信息域的高位
				m_state = length_state;

				//检验数据长度信息是否正确
				m_calcDataLength = (m_sendBuf.at(5))<<1;//预计回应的数据区字节数

				if (b != m_calcDataLength)//数据长度信息错误, 终止解析
				{
					qCritical() << "dataLength error!!!!!!!";
					qCritical() << "!!!!!!!dataLength check error!!!!!!!";
					qCritical() << "!!!!!!!send buf is :!!!!!!!";
					for (int idx=0;idx<m_sendBuf.length();idx++)
					{
						qCritical() << s.sprintf("%02X", m_sendBuf.at(idx));
					}
					qCritical() << "!!!!!!!send buf end :!!!!!!!";

					qCritical() << "!!!!!!!tmp buf is :!!!!!!!";
					for (int idx=0;idx<tmp.length();idx++)
					{
						qCritical() << s.sprintf("%02X", tmp.at(idx));
					}
					qCritical() << "!!!!!!!tmp buf end :!!!!!!!";
					initParams();
					return false;
				}
			}
			break;
		case length_state:
			if (m_readBuf.length() == (MOD_ADDRESS_LEN+MOD_FUNC_LEN+MOD_DATALEN_LEN))//读取数据长度信息域完毕
			{
				//开始读取数据域
				m_readBuf.append(b);
				m_valueArray.append(b);
				m_readDataLength++;
				m_state = data_state;
			}			
			break;
		case data_state:
			if(m_readDataLength==m_calcDataLength)
			{
				m_crcValue.clear();
				m_crcValue.append(b);//读取crc校验值的低位
				m_state = crc_state;
			}
			else
			{
				m_readBuf.append(b);
				m_valueArray.append(b);
				m_readDataLength++;
			}
			break;
		case crc_state:
			m_crcValue.append(b);//crc校验值的高位
			crc  = ( (((uchar)m_crcValue.at(1))<<WORDLEN) | (uchar)m_crcValue.at(0) );
			calc_crc = calcModRtuCRC((uchar *)m_readBuf.data(), m_readBuf.length());
			if (crc == calc_crc)//crc校验通过
			{
				ret = true;
			}
			else//crc校验错误
			{
				qCritical() << "!!!!!!!crc check error!!!!!!!";
				qCritical() << "!!!!!!!m_sendBuf buf is :!!!!!!!";
				for (int idx=0;idx<m_sendBuf.length();idx++)
				{
					qCritical() << s.sprintf("%02X", m_sendBuf.at(idx));
				}
				qCritical() << "!!!!!!!m_sendBuf buf end :!!!!!!!";

				qCritical() << "!!!!!!!tmp buf is :!!!!!!!";
				for (int idx=0;idx<tmp.length();idx++)
				{
					qCritical() << s.sprintf("%02X", tmp.at(idx));
				}
				qCritical() << "!!!!!!!tmp buf end :!!!!!!!";

				qCritical() << "!!!!!!!m_readBuf buf is :!!!!!!!";
				for (int idx=0;idx<m_readBuf.length();idx++)
				{
					qCritical() << s.sprintf("%02X", m_readBuf.at(idx));
				}
				qCritical() << "!!!!!!!m_readBuf buf end :!!!!!!!";

				qCritical() << "!!!!!!!m_crcValue buf is :!!!!!!!";
				for (int idx=0;idx<m_crcValue.length();idx++)
				{
					qCritical() << s.sprintf("%02X", m_crcValue.at(idx));
				}
				qCritical() << "!!!!!!!m_crcValue buf end :!!!!!!!";
				
				initParams();
				return false;
			}
			break;
		default:
			break;
		}
	}

	if (ret)//初始化所有参数, 以便下一次接收
	{
		initParams();//m_valueArray留作后用, 不能清空
	}
	return ret;
}

QByteArray lcModbusRTUProtocol::getSendBuf()
{
	return m_sendBuf;
}

QByteArray lcModbusRTUProtocol::getReadVale()
{
	return m_valueArray;
}

/*
** i, 是以m_sendbuf.start为开始地址的通道偏移量; i的索引从0开始
** 返回值中高位在前, 低位在后
*/
QByteArray lcModbusRTUProtocol::getData(int i)
{
	if ( (EDA9150A_ROUTE_BYTES*i) > m_valueArray.length())//i不能超过被读取的通道数量
	{
		return QByteArray();
	}

	QByteArray data;
	for (int k=0;k<EDA9150A_ROUTE_BYTES;k++)
		data.append(m_valueArray.at(EDA9150A_ROUTE_BYTES*i+k));
	
	return data;
}

/*
** i, 通道号; 从0开始, 最大不超过15
** 每个通道占用4个字节, 两个寄存器
*/
int lcModbusRTUProtocol::getIntData(int i)
{
	QByteArray data = getData(i);
	if (data.isNull())//如果取数据失败, 返回-1
	{
		return -1;
	}

	int value = 0;	
	for (int k=0;k<EDA9150A_ROUTE_BYTES;k++)
	{
		value |= ( ((uchar)data.at(k)) << ((EDA9150A_ROUTE_BYTES-1-k)*WORDLEN) );
	}
	return value;
}
/***********************************************
类名：lcModbusRTUFunc END
************************************************/