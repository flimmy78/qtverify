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
					m_tempFrame->check = uch;
					check_i++;
					break;
				}
				if (check_i == 1) //���ֽ�
				{
					ch = (INT8)tmp.at(m);
					m_tempFrame->check = ch*256 + m_tempFrame->check;
					check_i = 0;
					state = PV_STATE;
					ck = CountCheck(m_tempFrame);
					if (ck == m_tempFrame->check) //У��ͨ��
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

	m_conFrame = new Con_Frame_Struct();
	memset(m_conFrame, 0, sizeof(Con_Frame_Struct));
}

ControlProtocol::~ControlProtocol()
{
}

/************************************************************************
	�¿��ư�Э�飺�̵������� ͬʱֻ����1·                                       
	status: true(���رպ�)��false(���ش�)
************************************************************************/
void ControlProtocol::makeRelaySendBuf(UINT8 portno, bool status)
{
	m_sendBuf = "";
	m_sendBuf.append(START_CODE).append(FUNC_RELAY);
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
		data = (UINT8)pow(a, (portno-17)) & st;;
		m_sendBuf.append(code0).append(code0).append(data);
	}
	UINT8 cs = START_CODE + FUNC_RELAY + relay_num + portno + code0 + code0 + data;
	m_sendBuf.append(cs).append(END_CODE);
}


//���Ƶ��ڷ� ͬʱֻ����һ·
void ControlProtocol::makeRegulateSendBuf(UINT8 portno, int degree)
{
	m_sendBuf = "";
	m_sendBuf.append(START_CODE).append(FUNC_REGULATE);
	float a = 2;
	UINT8 regulate_num = (UINT8)pow(a, (portno-1)); //���Ƶĵ��ڷ����� ֻ����1·
	m_sendBuf.append(regulate_num);
	UINT8 dataL = 0x66; //���� ���ֽ� ��Ҫʵ��ͼ���õ�
	UINT8 dataH = 0x88; //���� ���ֽ�
	m_sendBuf.append(dataL).append(dataH);
	UINT8 cs = START_CODE + FUNC_REGULATE + regulate_num + dataL + dataH;
	m_sendBuf.append(cs).append(END_CODE);
}

//��ѯ�ӻ�״̬
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


//��֡
UINT8 ControlProtocol::readControlComBuffer(QByteArray tmp)
{
	qDebug()<<"readControlComBuffer ControlProtocol thread:"<<QThread::currentThreadId();
	UINT8 ret = 0x00;
	int state = START_STATE;
	UINT8 ch = 0; //�޷���8λ����
	int number = tmp.size();

	int m=0;
	int num_i=0;
	UINT8 ck=0; //�������ļ�����
	for (m=0; m<number; m++)
	{
		ch = (UINT8)tmp.at(m);
		qDebug()<<"read data is:"<<ch;
		switch(state)
		{
		case START_STATE: //8λ�޷���
			{
				if (ch == START_CODE)
				{
					m_conFrame->startCode = START_CODE;
					state = FUNC_STATE;
				}
				break;
			}
		case FUNC_STATE: //8λ�޷���
			{   
				if (ch == FUNC_RELAY) //������-�̵�������
				{
					m_conFrame->funcCode = FUNC_RELAY;
					state = DATA_STATE;
					break;
				}
				if (ch == FUNC_REGULATE) //������-���ڷ�����
				{
					m_conFrame->funcCode = FUNC_REGULATE;
					state = DATA_STATE;
					break;
				}
				if (ch = FUNC_QUERY) //������-��ѯ
				{
					m_conFrame->funcCode = FUNC_QUERY;
					state = DATA_STATE;
					break;
				}
				break;
			}

		case DATA_STATE: //8λ�޷���
			{
				if (m_conFrame->funcCode == FUNC_RELAY)
				{
					m_conFrame->data[num_i++] = ch;
					if (num_i == RELAY_DATA_LENGTH)
					{
						state = CS_STATE;
						num_i = 0;
					}
				}
				if (m_conFrame->funcCode == FUNC_REGULATE)
				{
					m_conFrame->data[num_i++] = ch;
					if (num_i == REGU_DATA_LENGTH)
					{
						state = CS_STATE;
						num_i = 0;
					}
				}
				if (m_conFrame->funcCode == FUNC_QUERY)
				{
					m_conFrame->data[num_i++] = ch;
					if (num_i == DATA_LENGTH)
					{
						state = CS_STATE;
						num_i = 0;
					}
				}

				break;
			}    
		case CS_STATE: //8λ�޷���
			{
				m_conFrame->check = ch;
				state = END_STATE;
				break;
			} 
		case END_STATE: //8λ�޷���
			{
				m_conFrame->endCode = END_CODE;
				state = START_STATE;
				ck = CountCheck(m_conFrame);
				if (ck == m_conFrame->check) //У��ͨ��
				{
					analyseFrame();
					qDebug()<<"check is ok У��ͨ��";
					ret = m_conFrame->funcCode; //�Թ����뷵�أ���������
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

	return cs;
}

void ControlProtocol::analyseFrame()
{

}

Con_Frame_Struct * ControlProtocol::getConFrame()
{
	return m_conFrame;
}