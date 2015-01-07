/***********************************************
**  �ļ���:     protocol.cpp
**  ����:       ͨѶЭ����
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/16
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:   2014-6-16�����¶Ȳɼ�Э�飨�������AI702Ѳ���ǣ�
                2014-6-17������ƽЭ��(������˹)
				2014-6-23���ӿ��ư���Э��
				2014-9-10���ӵ�³������ͨѶЭ��(��λ����������ֱ��ͨѶ)
***********************************************/

#include <QtCore/QDebug>
#include <QtCore/QDateTime>

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
������TempProtocol
���ܣ�������� AI702Ѳ���� ͨѶЭ�飨�¶ȣ�
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

//�����¶�ֵ ��֡
void TempProtocol::makeSendBuf()
{
	m_sendBuf = "";
	m_sendBuf.append(ADDR_CODE_FIRST).append(ADDR_CODE_FIRST);//��ַ����
	m_sendBuf.append(READ_CODE); //��׼������
	UINT8 paracode = 0x00; //��������
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

//��֡ ��ȡ�¶�ֵ
bool TempProtocol::readTemperComBuffer(QByteArray tmp)
{
	memset(m_tempFrame, 0, sizeof(Temp_Frame_Struct));
	bool ret = false;
	int state = PV_STATE;

	UINT8 uch = 0; //�޷���8λ����
	INT8  ch = 0;  //�з���8λ����
	int number = tmp.size();
	int m=0;
	int pv_i=0, sv_i=0, para_i=0, check_i=0;
 	INT16 ck=0; //�������ļ�����
	for (m=0; m<number; m++)
	{
		switch(state)
		{
		case PV_STATE: //16λ�з���
			{
				if (pv_i == 0) //���ֽ�
				{
					uch = (UINT8)tmp.at(m);
					m_tempFrame->pv = uch;
					pv_i++;
					break;
				}
				if (pv_i == 1) //���ֽ�
				{
					ch = (INT8)tmp.at(m);
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
					uch = (UINT8)tmp.at(m);
					m_tempFrame->sv = uch;
					sv_i++;
					break;
				}
				if (sv_i == 1) //���ֽ�
				{
					ch = (INT8)tmp.at(m);
					state = MV_STATE;
					m_tempFrame->sv = ch*256 + m_tempFrame->sv;
					sv_i = 0;
				}
				break;
			}

		case MV_STATE: //8λ�з���
			{
				ch = (INT8)tmp.at(m);
				m_tempFrame->mv = ch;
				state = WARN_STATE;
				break;
			}    
		case WARN_STATE: //8λ�޷���
			{
				ch = (INT8)tmp.at(m);
				m_tempFrame->warn = ch;
				state = PARA_STATE;
				break;
			} 
		case PARA_STATE: //16λ�з���
			{
				if (para_i == 0) //���ֽ� �޷���
				{
					uch = (UINT8)tmp.at(m);
					m_tempFrame->para = uch;
					para_i++;
					break;
				}
				if (para_i == 1) //���ֽ� �з���
				{
					ch = (INT8)tmp.at(m);
					state = CHECK_STATE;
					m_tempFrame->para = ch*256 + m_tempFrame->para;
					para_i = 0;
				}
				break;
			} 
		case CHECK_STATE: //16λ
			{
				if (check_i == 0) //���ֽ�
				{
					uch = (UINT8)tmp.at(m);
					m_tempFrame->cs = uch;
					check_i++;
					break;
				}
				if (check_i == 1) //���ֽ�
				{
					ch = (INT8)tmp.at(m);
					m_tempFrame->cs = ch*256 + m_tempFrame->cs;
					check_i = 0;
					state = PV_STATE;
					ck = CountCheck(m_tempFrame);
					if (ck == m_tempFrame->cs) //У��ͨ��
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

//����"У����"
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
������BalanceProtocol
���ܣ���ƽЭ��
************************************************/
BalanceProtocol::BalanceProtocol()
{
	m_balValue = "";
}

BalanceProtocol::~BalanceProtocol()
{
}

//����������˹��ƽ��������
bool BalanceProtocol::readBalanceComBuffer(QByteArray tmp)
{
	m_balValue = "";
	bool ret = false;
	int num = tmp.size();
	if (num < 16) //һ֡ͨ����22�ֽڣ�
	{
		return ret;
	}
	int m=0;
	char ch;
	UINT8 ch1, ch2;
	ch1 = (UINT8)tmp.at(num-1);
	ch2 = (UINT8)tmp.at(num-2);
	if (ch1==ASCII_LF && ch2==ASCII_CR) //0x0A����; 0x0D�س�����ʾһ֡������
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
������ControlProtocol
���ܣ���λ������Э��
************************************************/
ControlProtocol::ControlProtocol()
{
	m_sendBuf = "";

	m_ctrlFrame = new Ctrl_Frame_Struct();
	memset(m_ctrlFrame, 0, sizeof(Ctrl_Frame_Struct));

	m_balValueStr = "";
}

ControlProtocol::~ControlProtocol()
{
	if (m_ctrlFrame)
	{
		delete m_ctrlFrame;
		m_ctrlFrame = NULL;
	}
}

/************************************************************************
	�¿��ư�Э�飺�̵������� ͬʱֻ����1·                                       
	status: true(���Ŵ�)��false(���Źر�)
************************************************************************/
void ControlProtocol::makeRelaySendBuf(UINT8 portno, bool status)
{
	m_sendBuf = "";
	m_sendBuf.append(CTRL_START_CODE).append(CTRL_FUNC_RELAY);
	UINT8 relay_num = 0x01; //���Ƶļ̵������� 1·
	m_sendBuf.append(relay_num);
	m_sendBuf.append(portno); //��protno·�̵���
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


//���Ƶ��ڷ� ͬʱֻ����һ·
void ControlProtocol::makeRegulateSendBuf(UINT8 portno, UINT16 degree)
{
	m_sendBuf = "";
	m_sendBuf.append(CTRL_START_CODE).append(CTRL_FUNC_REGULATE);
	float a = 2;
	UINT8 regulate_num = (UINT8)pow(a, (portno-1)); //���Ƶĵ��ڷ����� ֻ����1·
	m_sendBuf.append(regulate_num);
	QString degStr = QString("%1").arg(degree, 4, 16).replace(" ", "0");
	bool ok;
	UINT8 dataL = degStr.right(2).toUInt(&ok, 16);//���� ���ֽ� ��Ҫʵ��ͼ���õ�
	UINT8 dataH = degStr.left(2).toUInt(&ok, 16); //���� ���ֽ�
// 	UINT8 dataL = 0x66;
// 	UINT8 dataH = 0x01;
	m_sendBuf.append(dataL).append(dataH);
	UINT8 cs = CTRL_START_CODE + CTRL_FUNC_REGULATE + regulate_num + dataL + dataH;
	m_sendBuf.append(cs).append(CTRL_END_CODE);
}

//��ѯ�ӻ�״̬
void ControlProtocol::makeQuerySendBuf()
{
	m_sendBuf = "";
	m_sendBuf.append(CTRL_START_CODE).append(CTRL_FUNC_QUERY);
	UINT8 code0 = 0x00;
	m_sendBuf.append(code0).append(code0).append(code0).append(code0);
	UINT8 cs = CTRL_START_CODE + CTRL_FUNC_QUERY + code0 + code0 + code0 + code0;
	m_sendBuf.append(cs).append(CTRL_END_CODE);
}


QByteArray ControlProtocol::getSendBuf()
{
	return m_sendBuf;
}


//��֡
UINT8 ControlProtocol::readControlComBuffer(QByteArray tmp)
{
// 	qDebug()<<"readControlComBuffer ControlProtocol thread:"<<QThread::currentThreadId();
	UINT8 ret = 0x00;
	int state = CTRL_START_STATE;
	UINT8 ch = 0; //�޷���8λ����
	int number = tmp.size();

	int m=0;
	int num_i=0;
	UINT8 ck=0; //�������ļ�����
	for (m=0; m<number; m++)
	{
		ch = (UINT8)tmp.at(m);
// 		qDebug()<<"read data is:"<<ch;
		switch(state)
		{
		case CTRL_START_STATE: //8λ�޷���
			{
				if (ch == CTRL_START_CODE)
				{
					m_ctrlFrame->startCode = CTRL_START_CODE;
					state = CTRL_FUNC_STATE;
				}
				break;
			}
		case CTRL_FUNC_STATE: //8λ�޷���
			{   
				if (ch == CTRL_FUNC_RELAY) //������-�̵�������
				{
					m_ctrlFrame->funcCode = CTRL_FUNC_RELAY;
					state = CTRL_DATA_STATE;
					break;
				}
				if (ch == CTRL_FUNC_REGULATE) //������-���ڷ�����
				{
					m_ctrlFrame->funcCode = CTRL_FUNC_REGULATE;
					state = CTRL_DATA_STATE;
					break;
				}
				if (ch == CTRL_FUNC_QUERY) //������-��ѯ
				{
					m_ctrlFrame->funcCode = CTRL_FUNC_QUERY;
					state = CTRL_DATA_STATE;
					break;
				}
				if (ch == CTRL_FUNC_BALANCE) //������-��ƽ�ɼ�
				{
					m_ctrlFrame->funcCode = CTRL_FUNC_BALANCE;
					state = CTRL_DATA_STATE;
					break;
				}
				break;
			}

		case CTRL_DATA_STATE: //8λ�޷���
			{
				if (m_ctrlFrame->funcCode == CTRL_FUNC_RELAY) //�̵���
				{
					m_ctrlFrame->data[num_i++] = ch;
					if (num_i == RELAY_DATA_LENGTH)
					{
						state = CTRL_CS_STATE;
						num_i = 0;
					}
				}
				if (m_ctrlFrame->funcCode == CTRL_FUNC_REGULATE) //���ڷ�
				{
					m_ctrlFrame->data[num_i++] = ch;
					if (num_i == REGU_DATA_LENGTH)
					{
						state = CTRL_CS_STATE;
						num_i = 0;
					}
				}
				if (m_ctrlFrame->funcCode == CTRL_FUNC_QUERY)  //��ѯ
				{
					m_ctrlFrame->data[num_i++] = ch;
					if (num_i == DATA_LENGTH)
					{
						state = CTRL_CS_STATE;
						num_i = 0;
					}
				}
				if (m_ctrlFrame->funcCode == CTRL_FUNC_BALANCE)  //��ƽ
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
		case CTRL_CS_STATE: //8λ�޷���
			{
				m_ctrlFrame->cs = ch;
				state = CTRL_END_STATE;
				break;
			} 
		case CTRL_END_STATE: //8λ�޷���
			{
				m_ctrlFrame->endCode = CTRL_END_CODE;
				state = CTRL_START_STATE;
				ck = CountCheck(m_ctrlFrame);
				if (ck == m_ctrlFrame->cs) //У��ͨ��
				{
					analyseFrame();
// 					qDebug()<<"check is ok У��ͨ��";
					ret = m_ctrlFrame->funcCode; //�Թ����뷵�أ���������
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

UINT8 ControlProtocol::CountCheck(Ctrl_Frame_Struct *pFrame)
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

void ControlProtocol::analyseFrame()
{
	if (NULL==m_ctrlFrame)
	{
		return;
	}

	if (m_ctrlFrame->funcCode == CTRL_FUNC_BALANCE) //��ƽ�ɼ�
	{
		m_balValueStr = ""; //������
		char ch;
		UINT8 ch1, ch2;
		ch1 = m_ctrlFrame->data[BAL_DATA_LENGTH-1];
		ch2 = m_ctrlFrame->data[BAL_DATA_LENGTH-2];
		if (ch1==ASCII_LF && ch2==ASCII_CR) //0x0A����; 0x0D�س�����ʾһ֡������
		{
			for (int i=6; i<16; i++)
			{
				ch = m_ctrlFrame->data[i];
				m_balValueStr += ch;
			}
// 			m_balValueStr.replace(" ", "0");
		}
	}
}

Ctrl_Frame_Struct * ControlProtocol::getConFrame()
{
	return m_ctrlFrame;
}

QString ControlProtocol::getBalanceValue()
{
	return m_balValueStr;
}

/***********************************************
������MeterProtocol
���ܣ�������ͨѶЭ�����
************************************************/
MeterProtocol::MeterProtocol()
{
	m_sendBuf = "";
}

MeterProtocol::~MeterProtocol()
{
}

//��ȡ��֡���
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
	return m_date;;
}


/***********************************************
������DeluMeterProtocol
���ܣ�������ͨѶЭ��-��³������
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

//����"У����"
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

//��֡
UINT8 DeluMeterProtocol::readMeterComBuffer(QByteArray tmp)
{
	qDebug()<<"readMeterComBuffer MeterProtocol thread:"<<QThread::currentThreadId();

	UINT8 ret = 0x00;
	int state = METER_START_STATE;
	UINT8 ch = 0; //�޷���8λ����
	int number = tmp.size();

	int m=0;
	int addr_num=0, dataID_num=0, data_num=0;
	UINT8 ck=0; //�������ļ�����
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
				if (ch == METER_TYPE_ANSWER_CODE) //��Ӧ
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
		case METER_SN_STATE: //���к�
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
				if (ck == m_deluMeterFrame->cs) //У��ͨ��
				{
					analyseFrame();
					ret = 1; //
					qDebug()<<"check is ok У��ͨ��";
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

	//���
	m_fullMeterNo = "";
	for (int i=METER_ADDR_LEN-1; i>=0; i--)
	{
		m_fullMeterNo.append(QString("%1").arg(m_deluMeterFrame->addr[i], 2, 16)).replace(' ', '0');
	}

	//��ˮ�¶�
	m_inTemper = "";
	m_inTemper.append(QString("%1%2.%3").arg(m_deluMeterFrame->data[2], 2, 16)\
		.arg(m_deluMeterFrame->data[1], 2, 16).arg(m_deluMeterFrame->data[0], 2, 16));
	m_inTemper.replace(' ', '0');

	//����
	m_flow = "";
	m_flow.append(QString("%1.%2%3%4").arg(m_deluMeterFrame->data[9], 2, 16)\
		.arg(m_deluMeterFrame->data[8], 2, 16).arg(m_deluMeterFrame->data[7], 2, 16)\
		.arg(m_deluMeterFrame->data[6], 2, 16));
	m_flow.replace(' ', '0');

	//����
	m_heat = "";
	m_heat.append(QString("%1%2.%3%4").arg(m_deluMeterFrame->data[14], 2, 16)\
		.arg(m_deluMeterFrame->data[13], 2, 16).arg(m_deluMeterFrame->data[12], 2, 16)\
		.arg(m_deluMeterFrame->data[11], 2, 16));
	m_heat.replace(' ', '0');

	//��ˮ�¶�
	m_outTemper = "";
	m_outTemper.append(QString("%1%2.%3").arg(m_deluMeterFrame->data[48], 2, 16)\
		.arg(m_deluMeterFrame->data[47], 2, 16).arg(m_deluMeterFrame->data[46], 2, 16));
	m_outTemper.replace(' ', '0');

	//����
	m_date = "";
	m_date.append(QString("%1%2%3%4").arg(m_deluMeterFrame->data[52], 2, 16)\
		.arg(m_deluMeterFrame->data[51], 2, 16).arg(m_deluMeterFrame->data[50], 2, 16).\
		arg(m_deluMeterFrame->data[49], 2, 16));
	m_date.replace(' ', '0');

}

// ��֡���㲥��ַ����
void DeluMeterProtocol::makeFrameOfReadMeter()
{
	m_sendBuf = "";

	for (int i=0; i<WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//���Ѻ���
	}

	for (int j=0; j<PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //ǰ���ֽ�
	}

	m_sendBuf.append(METER_START_CODE);//��ʼ��
	m_sendBuf.append(METER_TYPE_ASK_CODE); //�Ǳ����� ����
	for (int m=0; m<METER_ADDR_LEN; m++)
	{
		m_sendBuf.append(METER_ADDR_CODE); //�㲥��ַ
	}
	m_sendBuf.append(METER_CTRL_CODE);//������
	m_sendBuf.append(0x03);//���ݳ���
	m_sendBuf.append(0x3F).append(0x90); //���ݱ�ʶ
	m_sendBuf.append(0x03);//���к�
	UINT8 cs = METER_START_CODE + METER_TYPE_ASK_CODE + METER_ADDR_CODE*METER_ADDR_LEN + METER_CTRL_CODE\
		+ 0x03 + 0x3F + 0x90 + 0x03;
	m_sendBuf.append(cs);//У����
	m_sendBuf.append(METER_END_CODE);//������
}

// ��֡�����ý���춨״̬
void DeluMeterProtocol::makeFrameOfSetVerifyStatus()
{
	m_sendBuf = "";

	for (int i=0; i<WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//���Ѻ���
	}

	for (int j=0; j<PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //ǰ���ֽ�
	}

	m_sendBuf.append(METER_START_CODE);//��ʼ��
	m_sendBuf.append(METER_TYPE_ASK_CODE); //�Ǳ����� ����
	for (int m=0; m<METER_ADDR_LEN; m++)
	{
		m_sendBuf.append(METER_ADDR_CODE); //�㲥��ַ
	}

	UINT8 code0 = 0x00;
	m_sendBuf.append(0x33).append(code0).append(0x61).append(0x16);
}

// ��֡���޸ı��
void DeluMeterProtocol::makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo)
{
	m_sendBuf = "";

	for (int i=0; i<WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//���Ѻ���
	}

	for (int j=0; j<PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //ǰ���ֽ�
	}

	m_sendBuf.append(METER_START_CODE);//��ʼ��
	m_sendBuf.append(METER_TYPE_ASK_CODE); //�Ǳ����� ����
	UINT8 cs = METER_START_CODE + METER_TYPE_ASK_CODE;
	UINT8 oldNo;
	bool ok;
	for (int m=METER_ADDR_LEN-1; m>=0; m--)
	{
		oldNo = oldMeterNo.mid(2*m, 2).toUInt(&ok, 16);
		m_sendBuf.append(oldNo); //�ɱ��
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
		m_sendBuf.append(newNo); //�±��
		cs += newNo;
	}

	UINT8 timeCode;
	QString currentTime = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");//"20150107125930"
	for (int p=6; p>=0; p--)
	{
		timeCode = currentTime.mid(2*p, 2).toUInt(&ok, 16);
		m_sendBuf.append(timeCode); //��ǰʱ��
		cs += timeCode;
	}

	m_sendBuf.append(cs).append(0x16);
}

// ��֡���޸���������
void DeluMeterProtocol::makeFrameOfModifyFlowPara()
{
}

/***********************************************
������TgMeterProtocol
���ܣ�������ͨѶЭ��-���������
************************************************/
TgMeterProtocol::TgMeterProtocol()
{
}

TgMeterProtocol::~TgMeterProtocol()
{
}

UINT8 TgMeterProtocol::CountCheck(DeluMeter_Frame_Struct *pFrame)
{
	return 0;
}

UINT8 TgMeterProtocol::readMeterComBuffer(QByteArray tmp)
{
	return 0;
}

void TgMeterProtocol::analyseFrame()
{

}

void TgMeterProtocol::makeFrameOfReadMeter()
{

}

void TgMeterProtocol::makeFrameOfSetVerifyStatus()
{

}

void TgMeterProtocol::makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo)
{

}

void TgMeterProtocol::makeFrameOfModifyFlowPara()
{

}