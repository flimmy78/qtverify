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

	m_tempStr.clear();
	m_sendBuf.clear();
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
// 	qDebug()<<"TempProtocol::makeSendBuf thread:"<<QThread::currentThreadId();
	m_sendBuf.clear();
// 	printf("111111 file %s, line %d\n", __FILE__, __LINE__);
	m_sendBuf.append(ADDR_CODE_FIRST).append(ADDR_CODE_FIRST);//��ַ����
// 	printf("222222 file %s, line %d\n", __FILE__, __LINE__);
	m_sendBuf.append(READ_CODE); //��׼������
// 	printf("333333 file %s, line %d\n", __FILE__, __LINE__);
	UINT8 paracode = 0x00; //��������
	m_sendBuf.append(paracode); 
// 	printf("444444 file %s, line %d\n", __FILE__, __LINE__);
	UINT8 datacode = 0x00;
	m_sendBuf.append(datacode).append(datacode);
// 	printf("555555 file %s, line %d\n", __FILE__, __LINE__);
	UINT16 checkcode = paracode*256 + READ_CODE + ADDR_FIRST;
	UINT8 highnum = (UINT8)(checkcode>>8);//(UINT8)(checkcode/256)
	UINT8 lownum = (UINT8)checkcode;
// 	printf("666666 file %s, line %d\n", __FILE__, __LINE__);
	m_sendBuf.append(lownum).append(highnum);
// 	printf("777777 file %s, line %d\n", __FILE__, __LINE__);
}

//��֡ ��ȡ�¶�ֵ
bool TempProtocol::readTemperComBuffer(QByteArray tmp)
{
// 	qDebug()<<"TempProtocol::readTemperComBuffer thread:"<<QThread::currentThreadId();
	int number = tmp.size();
	Q_ASSERT(number > 0);
	memset(m_tempFrame, 0, sizeof(Temp_Frame_Struct));
	bool ret = false;
	int state = PV_STATE;

	UINT8 uch = 0; //�޷���8λ����
	INT8  ch = 0;  //�з���8λ����
	int m=0;
	int pv_i=0, sv_i=0, para_i=0, check_i=0;
 	INT16 ck=0; //�������ļ�����
	for (m=0; m<number; m++)
	{
		switch(state)
		{
		case PV_STATE: //16λ�з���
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
		case SV_STATE: //16λ�з���
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
		case MV_STATE: //8λ�з���
			ch = (INT8)tmp.at(m);
			m_tempFrame->mv = ch;
			state = WARN_STATE;
			break;
		case WARN_STATE: //8λ�޷���
			ch = (INT8)tmp.at(m);
			m_tempFrame->warn = ch;
			state = PARA_STATE;
			break;
		case PARA_STATE: //16λ�з���
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
		case CHECK_STATE: //16λ
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
		default :
			state = PV_STATE;
			break;
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
	if (NULL == m_tempFrame)
	{
		return;
	}
	float PV = ((float)m_tempFrame->pv)/10;
	float SV = ((float)m_tempFrame->sv)/10;
	QString pvStr = QString("%1").arg(PV, TEMPER_DATA_WIDTH, 'f', TEMPER_DATA_PRECISION);
	QString svStr = QString("%1").arg(SV, TEMPER_DATA_WIDTH, 'f', TEMPER_DATA_PRECISION);
	m_tempStr = pvStr + svStr;
// 	qDebug()<<"TempProtocol::analyseFrame thread:"<<QThread::currentThreadId();
	qDebug()<<"TempProtocol::analyseFrame, PV ="<<pvStr<<", SV ="<<svStr;
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
������BalanceProtocol
���ܣ���ƽЭ�����
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

float BalanceProtocol::getBalanceValue()
{
	return m_balValue;
}

/***********************************************
������BalSatoriusProtocol
���ܣ�Satorius(������˹)��ƽЭ��
************************************************/
BalSatoriusProtocol::BalSatoriusProtocol()
{
}

BalSatoriusProtocol::~BalSatoriusProtocol()
{
}

//����������˹��ƽ��������
bool BalSatoriusProtocol::readBalanceComBuffer(QByteArray tmp)
{
// 	qDebug()<<"BalSatoriusProtocol::readBalanceComBuffer thread:"<<QThread::currentThreadId();
	bool ret = false;
	int number = tmp.size();
	if (number < BAL_DATA_LENGTH) //һ֡ͨ����22�ֽڣ�
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
		if (ch1==ASCII_LF && i>=16) //0x0A���У���ʾһ֡������
		{
			for (m=i-16; m<i-6; m++)
			{
				ch = tmp.at(m);
				whtArray.append(ch);
			}
			m_balValue = whtArray.replace(" ", 0).toFloat(&ok);
			if (ok)  //����ת���ɹ�
			{
				m_count++;
				if (m_count<=1)
				{
					m_lastValue = m_balValue;
					ret = true;
					break;
				}
				if (fabs(m_balValue-m_lastValue) <= 100.0) //����ͻ������
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

/***********************************************
������BalSatoriusHProtocol
���ܣ�SatoriusH(������˹H)��ƽЭ��
************************************************/
BalSatoriusHProtocol::BalSatoriusHProtocol()
{
}

BalSatoriusHProtocol::~BalSatoriusHProtocol()
{
}

//����������˹H��ƽ��������
bool BalSatoriusHProtocol::readBalanceComBuffer(QByteArray tmp)
{
	return true;
}

/***********************************************
������BalMettlerProtocol
���ܣ�Metteler Toledo��ƽЭ��
************************************************/
BalMettlerProtocol::BalMettlerProtocol()
{
}

BalMettlerProtocol::~BalMettlerProtocol()
{
}

//����Metteler Toledo��ƽ��������
bool BalMettlerProtocol::readBalanceComBuffer(QByteArray tmp)
{
	return true;
}

/***********************************************
������BalBizerbaProtocol
���ܣ�Bizerba(�̲�)��ƽЭ��
************************************************/
BalBizerbaProtocol::BalBizerbaProtocol()
{
}

BalBizerbaProtocol::~BalBizerbaProtocol()
{
}

//�����̲���ƽ��������
bool BalBizerbaProtocol::readBalanceComBuffer(QByteArray tmp)
{
// 	qDebug()<<"BalBizerbaProtocol::readBalanceComBuffer thread:"<<QThread::currentThreadId();
	bool ret = false;
	int number = tmp.size();
	if (number < BAL_DATA_LENGTH) //һ֡ͨ����22�ֽڣ�
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
		if (ch1==ASCII_LF && i>=15) //0x0A���У�֡β0x0D 0x0A��
		{
			for (m=i-13; m<i-4; m++)//һ֡����15�ֽ�, ͷ�����ֽ���'S', 'T', ����ĸ��ֽ���'k','g',0x0D 0x0A
			{
				ch = tmp.at(m);
				whtArray.append(ch);
			}
			m_balValue = whtArray.replace(" ", 0).toFloat(&ok);
			if (ok)  //����ת���ɹ�
			{
				m_count++;
				if (m_count<=1)
				{
					m_lastValue = m_balValue;
					ret = true;
					break;
				}
				if (fabs(m_balValue-m_lastValue) <= 100.0) //����ͻ������
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

/***********************************************
������ControlProtocol
���ܣ���λ������Э�����
************************************************/
CtrlProtocol::CtrlProtocol()
{
	m_sendBuf.clear();
}

CtrlProtocol::~CtrlProtocol()
{
}

QByteArray CtrlProtocol::getSendBuf()
{
	return m_sendBuf;
}

/***********************************************
������NewCtrlProtocol
���ܣ���λ������Э��-�¿��ư�
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
	�¿��ư�Э�飺�̵������� ͬʱֻ����1·                                       
	status: true(���Ŵ�)��false(���Źر�)
************************************************************************/
void NewCtrlProtocol::makeFrameOfCtrlRelay(UINT8 portno, bool status)
{
	qDebug()<<"NewCtrlProtocol::makeFrameOfCtrlRelay thread:"<<QThread::currentThreadId();
	Q_ASSERT(portno >= 0);
	m_sendBuf.clear();
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
void NewCtrlProtocol::makeFrameOfCtrlRegulate(UINT8 portno, UINT16 degree)
{
	Q_ASSERT(portno >= 0);
	m_sendBuf.clear();
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
void NewCtrlProtocol::makeFrameOfCtrlQuery()
{
	m_sendBuf.clear();
	m_sendBuf.append(CTRL_START_CODE).append(CTRL_FUNC_QUERY);
	UINT8 code0 = 0x00;
	m_sendBuf.append(code0).append(code0).append(code0).append(code0);
	UINT8 cs = CTRL_START_CODE + CTRL_FUNC_QUERY + code0 + code0 + code0 + code0;
	m_sendBuf.append(cs).append(CTRL_END_CODE);
}

//����ˮ��
void NewCtrlProtocol::makeFrameOfCtrlWaterPump(UINT8 portno, bool status)
{

}

//���ñ�Ƶ��Ƶ��
void NewCtrlProtocol::makeFrameOfSetDriverFreq(int freq)
{

}

//��֡
UINT8 NewCtrlProtocol::readCtrlComBuffer(QByteArray tmp)
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
			if (ch == CTRL_START_CODE)
			{
				m_ctrlFrame->startCode = CTRL_START_CODE;
				state = CTRL_FUNC_STATE;
			}
			break;
		case CTRL_FUNC_STATE: //8λ�޷���
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
		case CTRL_DATA_STATE: //8λ�޷���
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
		case CTRL_CS_STATE: //8λ�޷���
			m_ctrlFrame->cs = ch;
			state = CTRL_END_STATE;
			break;
		case CTRL_END_STATE: //8λ�޷���
			m_ctrlFrame->endCode = CTRL_END_CODE;
			state = CTRL_START_STATE;
			ck = CountCheck(m_ctrlFrame);
			if (ck == m_ctrlFrame->cs) //У��ͨ��
			{
				analyseFrame();
// 				qDebug()<<"check is ok У��ͨ��";
				ret = m_ctrlFrame->funcCode; //�Թ����뷵�أ���������
			}
			break;
		default :
			state = CTRL_START_STATE;
			break;
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

	if (m_ctrlFrame->funcCode == CTRL_FUNC_BALANCE) //��ƽ�ɼ�
	{
		QByteArray whtArray;
		m_balValue = 0.0; //������
		char ch;
		UINT8 ch1, ch2;
		ch1 = m_ctrlFrame->data[BAL_DATA_LENGTH-1];
		ch2 = m_ctrlFrame->data[BAL_DATA_LENGTH-2];
		if (ch1==ASCII_LF && ch2==ASCII_CR) //0x0A����; 0x0D�س�����ʾһ֡������
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
������OldCtrlProtocol
���ܣ���λ������Э��-�Ͽ��ư�
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

	regPortMap.insert(1, 0xF2);
	regPortMap.insert(2, 0xF3);
	regPortMap.insert(3, 0xF4);
}

OldCtrlProtocol::~OldCtrlProtocol()
{

}

/************************************************************************
	�Ͽ��ư�Э�飺�̵������� ͬʱֻ����1·                                       
	status: true(���Ŵ�,�պϼ̵���)��false(���Źرգ��Ͽ��̵���)
************************************************************************/
void OldCtrlProtocol::makeFrameOfCtrlRelay(UINT8 portno, bool status)
{
// 	qDebug()<<"OldCtrlProtocol::makeFrameOfCtrlRelay thread:"<<QThread::currentThreadId();
	qDebug()<<"OldCtrlProtocol::makeFrameOfCtrlRelay portno ="<<portno<<", status ="<<status;
	UINT8 zeroCode = 0x00;
	m_sendBuf.clear();
	if (status) //true(���Ŵ�,�պϼ̵���)
	{
		m_sendBuf.append(0xFF).append(portCloseMap[portno]).append(zeroCode)\
			.append(zeroCode).append(0xFE);
	}
	else //false(���Źرգ��Ͽ��̵���)
	{
		m_sendBuf.append(0xFF).append(portOpenMap[portno]).append(zeroCode)\
			.append(zeroCode).append(0xFE);
	}
}

//���Ƶ��ڷ� ͬʱֻ����һ·
void OldCtrlProtocol::makeFrameOfCtrlRegulate(UINT8 portno, UINT16 degree)
{
// 	qDebug()<<"OldCtrlProtocol::makeFrameOfCtrlRegulate thread:"<<QThread::currentThreadId();
	qDebug()<<"OldCtrlProtocol::makeFrameOfCtrlRegulate portno ="<<portno<<", degree ="<<degree;
	int data = int(degree*4095/100);//0~100%��Ӧ0~4095
	UINT8 dataH = data/256;
	UINT8 dataL = data%256;
	UINT8 port = regPortMap[portno];
	m_sendBuf.clear();
	m_sendBuf.append(0xFF).append(port).append(dataH).append(dataL).append(0xFE);
}

//��ѯ�ӻ�״̬
void OldCtrlProtocol::makeFrameOfCtrlQuery()
{
}

//����ˮ�ÿ���
void OldCtrlProtocol::makeFrameOfCtrlWaterPump(UINT8 portno, bool status)
{
// 	qDebug()<<"OldCtrlProtocol::makeFrameOfCtrlWaterPump thread:"<<QThread::currentThreadId();
	qDebug()<<"OldCtrlProtocol::makeFrameOfCtrlWaterPump portno ="<<portno<<", status ="<<status;
	UINT8 zeroCode = 0x00;
	m_sendBuf.clear();
	if (status) //true ��ˮ��
	{
		m_sendBuf.append(0xFF).append(0xF9).append(zeroCode).append(zeroCode).append(0xFE);
	}
	else //false ��ˮ��
	{
		m_sendBuf.append(0xFF).append(0xFA).append(zeroCode).append(zeroCode).append(0xFE);
	}
}

//���ñ�Ƶ��Ƶ��
void OldCtrlProtocol::makeFrameOfSetDriverFreq(int freq)
{
// 	qDebug()<<"OldCtrlProtocol::makeFrameOfSetDriverFreq thread:"<<QThread::currentThreadId();
	qDebug()<<"OldCtrlProtocol::makeFrameOfSetDriverFreq freq ="<<freq;
	int data = int(freq*4095/50);//0~50Hz��Ӧ0~4095
	UINT8 dataH = data/256;
	UINT8 dataL = data%256;
	m_sendBuf.clear();
	m_sendBuf.append(0xFF).append(0xF8).append(dataH).append(dataL).append(0xFE);
}


//��֡
UINT8 OldCtrlProtocol::readCtrlComBuffer(QByteArray tmp)
{
	return 0;
}

void OldCtrlProtocol::analyseFrame()
{
}

//���ƴ�ѹ�ÿ���
void OldCtrlProtocol::makeFrameOfCtrlPressPump(bool status)
{
	UINT8 zeroCode = 0x00;
	m_sendBuf.clear();
	if (status) //����ѹ��
	{
		m_sendBuf.append(0xFF).append(0xFB).append(zeroCode).append(zeroCode).append(0xFE);
	}
	else //false �ش�ѹ��
	{
		m_sendBuf.append(0xFF).append(0xFC).append(zeroCode).append(zeroCode).append(0xFE);
	}
}


/***********************************************
������MeterProtocol
���ܣ�������ͨѶЭ�����
************************************************/
MeterProtocol::MeterProtocol()
{
	m_sendBuf.clear();
	
	m_CJ188DataFrame = new CJ188_Frame_Struct();
	memset(m_CJ188DataFrame, 0, sizeof(CJ188_Frame_Struct));
}

MeterProtocol::~MeterProtocol()
{
	if (m_CJ188DataFrame)
	{
		delete m_CJ188DataFrame;
		m_CJ188DataFrame = NULL;
	}
}

//��֡
UINT8 MeterProtocol::readMeterComBuffer(QByteArray tmp)
{
	qDebug()<<"MeterProtocol::readMeterComBuffer thread:"<<QThread::currentThreadId();

	UINT8 ret = 0x00;
	int state = STATE_METER_START;
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
		case STATE_METER_START: //
			if (ch == METER_START_CODE)
			{
				m_CJ188DataFrame->startCode = METER_START_CODE;
				state = STATE_METER_TYPE;
			}
			break;
		case STATE_METER_TYPE: //
			m_CJ188DataFrame->typeCode = ch;
			state = STATE_METER_ADDR;
			break;
		case STATE_METER_ADDR: //
			m_CJ188DataFrame->addr[addr_num++] = ch;
			if (addr_num == CJ188_ADDR_LEN)
			{
				state = STATE_METER_CTRL;
				addr_num = 0;
			}
			break;
		case STATE_METER_CTRL: //
			m_CJ188DataFrame->ctrlCode = ch;
			state = STATE_METER_DATALEN;
			break;
		case STATE_METER_DATALEN: //
			m_CJ188DataFrame->dataLen = ch;
			state = STATE_METER_DATAID;
			break;
		case STATE_METER_DATAID: //
			m_CJ188DataFrame->dataID[dataID_num++] = ch;
			if (dataID_num == CJ188_DATAID_LEN)
			{
				state = STATE_METER_SN;
				dataID_num = 0;
			}
			break;
		case STATE_METER_SN: //���к�
			m_CJ188DataFrame->sn = ch;
			if (m_CJ188DataFrame->dataLen <= 3)
			{
				state = STATE_METER_CS;
			}
			else
			{
				state = STATE_METER_DATA;
			}
			break;
		case STATE_METER_DATA: //
			m_CJ188DataFrame->data[data_num++] = ch;
			if (data_num == m_CJ188DataFrame->dataLen-3)
			{
				state = STATE_METER_CS;
				data_num = 0;
			}
			break;
		case STATE_METER_CS: //
			m_CJ188DataFrame->cs = ch;
			state = STATE_METER_END;
			break;
		case STATE_METER_END: //
			m_CJ188DataFrame->endCode = ch;
			state = STATE_METER_START;
			ck = CountCheck(m_CJ188DataFrame);
			if (ck == m_CJ188DataFrame->cs) //У��ͨ��
			{
				analyseFrame();
				ret = 1; //
				qDebug()<<"check is ok У��ͨ��";
			}
			break;
		default :
			state = STATE_METER_START;
			break;
		} //END OF switch(state)        
	} //END OF for (m=0; m<number; m++)

	return ret;
}

//����"У����"
UINT8 MeterProtocol::CountCheck(CJ188_Frame_Struct *pFrame)
{
	if (NULL == pFrame)
	{
		return 0;
	}

	UINT8 cs = 0;
	cs = pFrame->startCode + pFrame->typeCode;
	for (int i=0; i<CJ188_ADDR_LEN; i++)
	{
		cs += pFrame->addr[i];
	}
	cs += pFrame->ctrlCode;
	cs += pFrame->dataLen;
	for (int j=0; j<CJ188_DATAID_LEN; j++)
	{
		cs += pFrame->dataID[j];
	}
	cs += pFrame->sn;
	for (int m=0; m<CJ188_DATA_MAX_LEN; m++)
	{
		cs += pFrame->data[m];
	}

	return cs; 
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

QString MeterProtocol::getCoe()
{
	return m_Coe;
}


/***********************************************
������DeluMeterProtocol
���ܣ�������ͨѶЭ��-��³������
************************************************/
DeluMeterProtocol::DeluMeterProtocol()
{
}

DeluMeterProtocol::~DeluMeterProtocol()
{
}

void DeluMeterProtocol::analyseFrame()
{
	qDebug()<<"DeluMeterProtocol::analyseFrame thread:"<<QThread::currentThreadId();
	if (NULL == m_CJ188DataFrame)
	{
		return;
	}

	float flow = 0.0;
	//���
	m_fullMeterNo.clear();
	for (int i=CJ188_ADDR_LEN-1; i>=0; i--)
	{
		m_fullMeterNo.append(QString("%1").arg(m_CJ188DataFrame->addr[i], 2, 16)).replace(' ', '0');
	}

	//��ˮ�¶�
	m_inTemper.clear();
	m_inTemper.append(QString("%1%2.%3").arg(m_CJ188DataFrame->data[2], 2, 16)\
		.arg(m_CJ188DataFrame->data[1], 2, 16).arg(m_CJ188DataFrame->data[0], 2, 16));
	m_inTemper.replace(' ', '0');

	//����
	m_flow.clear();
	m_flow.append(QString("%1.%2%3%4").arg(m_CJ188DataFrame->data[9], 2, 16)\
		.arg(m_CJ188DataFrame->data[8], 2, 16).arg(m_CJ188DataFrame->data[7], 2, 16)\
		.arg(m_CJ188DataFrame->data[6], 2, 16));
	m_flow.replace(' ', '0');
	flow = m_flow.toFloat()*1000; //m3 -> L
	m_flow = QString::number(flow);

	//����
	m_heat.clear();
	m_heat.append(QString("%1%2.%3%4").arg(m_CJ188DataFrame->data[14], 2, 16)\
		.arg(m_CJ188DataFrame->data[13], 2, 16).arg(m_CJ188DataFrame->data[12], 2, 16)\
		.arg(m_CJ188DataFrame->data[11], 2, 16));
	m_heat.replace(' ', '0');

	//������������ϵ��
	m_bigCoe.clear();
	m_bigCoe.append(QString("%1%2").arg(m_CJ188DataFrame->data[33], 2, 16)\
		.arg(m_CJ188DataFrame->data[32], 2, 16));
	m_bigCoe.replace(' ', '0');

	//����������ϵ��
	m_mid2Coe.clear();
	m_mid2Coe.append(QString("%1%2").arg(m_CJ188DataFrame->data[35], 2, 16)\
		.arg(m_CJ188DataFrame->data[34], 2, 16));
	m_mid2Coe.replace(' ', '0');

	//����һ����ϵ��
	m_mid1Coe.clear();
	m_mid1Coe.append(QString("%1%2").arg(m_CJ188DataFrame->data[37], 2, 16)\
		.arg(m_CJ188DataFrame->data[36], 2, 16));
	m_mid1Coe.replace(' ', '0');

	//С����������ϵ��
	m_smallCoe.clear();
	m_smallCoe.append(QString("%1%2").arg(m_CJ188DataFrame->data[39], 2, 16)\
		.arg(m_CJ188DataFrame->data[38], 2, 16));
	m_smallCoe.replace(' ', '0');

	//��ˮ�¶�
	m_outTemper.clear();
	m_outTemper.append(QString("%1%2.%3").arg(m_CJ188DataFrame->data[48], 2, 16)\
		.arg(m_CJ188DataFrame->data[47], 2, 16).arg(m_CJ188DataFrame->data[46], 2, 16));
	m_outTemper.replace(' ', '0');

	//����
	m_date.clear();
	m_date.append(QString("%1%2%3%4").arg(m_CJ188DataFrame->data[52], 2, 16)\
		.arg(m_CJ188DataFrame->data[51], 2, 16).arg(m_CJ188DataFrame->data[50], 2, 16).\
		arg(m_CJ188DataFrame->data[49], 2, 16));
	m_date.replace(' ', '0');

}

// ��֡���㲥��ַ�����
void DeluMeterProtocol::makeFrameOfReadMeterNO()
{
	makeFrameOfReadMeterData(); //���������һ��
}

// ��֡���㲥��ַ��������ϵ��
void DeluMeterProtocol::makeFrameOfReadMeterFlowCoe()
{
	makeFrameOfReadMeterData(); //���������һ��
}

// ��֡���㲥��ַ��������
void DeluMeterProtocol::makeFrameOfReadMeterData(int vType)
{
	qDebug()<<"DeluMeterProtocol::makeFrameOfReadMeter thread:"<<QThread::currentThreadId();

	m_sendBuf.clear();

	for (int i=0; i<METER_WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//���Ѻ���
	}

	for (int j=0; j<METER_PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //ǰ���ֽ�
	}

	m_sendBuf.append(METER_START_CODE);//��ʼ��
	m_sendBuf.append(METER_TYPE_ASK_CODE); //�Ǳ����� ����
	for (int m=0; m<CJ188_ADDR_LEN; m++)
	{
		m_sendBuf.append(METER_ADDR_CODE); //�㲥��ַ
	}
	m_sendBuf.append(METER_CTRL_CODE);//������
	m_sendBuf.append(0x03);//���ݳ���
	m_sendBuf.append(0x3F).append(0x90); //���ݱ�ʶ
	m_sendBuf.append(0x03);//���к�
	UINT8 cs = METER_START_CODE + METER_TYPE_ASK_CODE + METER_ADDR_CODE*CJ188_ADDR_LEN + METER_CTRL_CODE\
		+ 0x03 + 0x3F + 0x90 + 0x03;
	m_sendBuf.append(cs);//У����
	m_sendBuf.append(METER_END_CODE);//������
}

// ��֡�����ý���춨״̬
void DeluMeterProtocol::makeFrameOfSetVerifyStatus(int vType)
{
	qDebug()<<"DeluMeterProtocol::makeFrameOfSetVerifyStatus thread:"<<QThread::currentThreadId();

	m_sendBuf.clear();

	for (int i=0; i<METER_WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//���Ѻ���
	}

	for (int j=0; j<METER_PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //ǰ���ֽ�
	}

	m_sendBuf.append(METER_START_CODE);//��ʼ��
	m_sendBuf.append(METER_TYPE_ASK_CODE); //�Ǳ����� ����
	for (int m=0; m<CJ188_ADDR_LEN; m++)
	{
		m_sendBuf.append(METER_ADDR_CODE); //�㲥��ַ
	}

	UINT8 code0 = 0x00;
	m_sendBuf.append(0x33).append(code0).append(0x61).append(0x16);
}

// ��֡���޸ı��(14λ���)
void DeluMeterProtocol::makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo)
{
// 	qDebug()<<"DeluMeterProtocol::makeFrameOfReadMeter thread:"<<QThread::currentThreadId();
	qDebug()<<"DeluMeterProtocol::makeFrameOfModifyMeterNo oldMeterNo ="<<oldMeterNo<<", newMeterNo ="<<newMeterNo;

	m_sendBuf.clear();

	for (int i=0; i<METER_WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//���Ѻ���
	}

	for (int j=0; j<METER_PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //ǰ���ֽ�
	}

	m_sendBuf.append(METER_START_CODE);//��ʼ��
	m_sendBuf.append(METER_TYPE_ASK_CODE); //�Ǳ����� ����
	UINT8 cs = METER_START_CODE + METER_TYPE_ASK_CODE;
	UINT8 oldNo;
	bool ok;
	for (int m=CJ188_ADDR_LEN-1; m>=0; m--)
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
	for (int n=CJ188_ADDR_LEN-1; n>=0; n--)
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

/*
** ��֡���޸�����ϵ��
** ���������
	meterNO:��ţ�14λ
	bigErr:������������λ%
	mid2Err:����������λ%
	mid1Err:����һ����λ%
	smallErr:С����������λ%
*/
void DeluMeterProtocol::makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr)
{
// 	qDebug()<<"DeluMeterProtocol::makeFrameOfModifyFlowCoe thread:"<<QThread::currentThreadId();
	qDebug()<<"DeluMeterProtocol::makeFrameOfModifyFlowCoe meterNO ="<<meterNO;
	qDebug()<<"bigErr ="<<bigErr<<", mid2Err ="<<mid2Err<<", mid1Err ="<<mid1Err<<", smallErr ="<<smallErr;

	m_sendBuf.clear();

	for (int i=0; i<METER_WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//���Ѻ���
	}

	for (int j=0; j<METER_PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //ǰ���ֽ�
	}

	m_sendBuf.append(METER_START_CODE);//��ʼ��
	m_sendBuf.append(METER_TYPE_ASK_CODE); //�Ǳ����� ����
	UINT8 cs = METER_START_CODE + METER_TYPE_ASK_CODE;
	UINT8 oldNo;
	bool ok;
	for (int m=CJ188_ADDR_LEN-1; m>=0; m--)
	{
		oldNo = meterNO.mid(2*m, 2).toUInt(&ok, 16);
		m_sendBuf.append(oldNo); //���
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

	QString bigCoe = QString::number(1/(1+bigErr/100), 'f', 3); //����3λС������������
	QString mid2Coe = QString::number(1/(1+mid2Err/100), 'f', 3);
	QString mid1Coe = QString::number(1/(1+mid1Err/100), 'f', 3);
	QString smallCoe = QString::number(1/(1+smallErr/100), 'f', 3);

	int bigDec = bigCoe.section(".", 1).toUInt()*4096.0/1000.0; //ֻȡ�������֣����ٽ�����������
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
** ��֡���޸�����ϵ��
** ���������
	meterNO:��ţ�14λ
	bigErr:������������λ%
	mid2Err:����������λ%
	mid1Err:����һ����λ%
	smallErr:С����������λ%
	oldCoe:��������������ԭϵ�����޵�λ
*/
void DeluMeterProtocol::makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr, MeterCoe_PTR oldCoe)
{
// 	qDebug()<<"DeluMeterProtocol::makeFrameOfModifyFlowCoe thread:"<<QThread::currentThreadId();
	qDebug()<<"DeluMeterProtocol::makeFrameOfModifyFlowCoe meterNO ="<<meterNO;
	qDebug()<<"bigErr ="<<bigErr<<", mid2Err ="<<mid2Err<<", mid1Err ="<<mid1Err<<", smallErr ="<<smallErr;
	qDebug()<<"oldCoe1 ="<<oldCoe->bigCoe<<", oldCoe2 ="<<oldCoe->mid2Coe<<", oldCoe3 ="<<oldCoe->mid1Coe<<", oldCoe4 ="<<oldCoe->smallCoe;

	m_sendBuf.clear();

	for (int i=0; i<METER_WAKEUP_CODE_NUM; i++)
	{
		m_sendBuf.append(METER_WAKEUP_CODE);//���Ѻ���
	}

	for (int j=0; j<METER_PREFIX_CODE_NUM; j++)
	{
		m_sendBuf.append(METER_PREFIX_CODE); //ǰ���ֽ�
	}

	m_sendBuf.append(METER_START_CODE);//��ʼ��
	m_sendBuf.append(METER_TYPE_ASK_CODE); //�Ǳ����� ����
	UINT8 cs = METER_START_CODE + METER_TYPE_ASK_CODE;
	UINT8 oldNo;
	bool ok;
	for (int m=CJ188_ADDR_LEN-1; m>=0; m--)
	{
		oldNo = meterNO.mid(2*m, 2).toUInt(&ok, 16);
		m_sendBuf.append(oldNo); //���
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

	QString bigCoe = QString::number(oldCoe->bigCoe/(1+bigErr/100), 'f', 3); //����3λС������������
	QString mid2Coe = QString::number(oldCoe->mid2Coe/(1+mid2Err/100), 'f', 3);
	QString mid1Coe = QString::number(oldCoe->mid1Coe/(1+mid1Err/100), 'f', 3);
	QString smallCoe = QString::number(oldCoe->smallCoe/(1+smallErr/100), 'f', 3);

	int bigDec = bigCoe.section(".", 1).toUInt()*4096.0/1000.0; //ֻȡ�������֣����ٽ�����������
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
������LiChMeterProtocol
���ܣ�������ͨѶЭ��-����������
************************************************/
LiChMeterProtocol::LiChMeterProtocol()
{
}

LiChMeterProtocol::~LiChMeterProtocol()
{
}

void LiChMeterProtocol::analyseFrame()
{

}

void LiChMeterProtocol::makeFrameOfReadMeterNO()
{

}

void LiChMeterProtocol::makeFrameOfReadMeterFlowCoe()
{

}

void LiChMeterProtocol::makeFrameOfReadMeterData(int vType)
{

}

void LiChMeterProtocol::makeFrameOfSetVerifyStatus(int vType)
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
������HuiZhongMeterProtocol
���ܣ�������ͨѶЭ��-��ɽ����������
************************************************/
HuiZhongMeterProtocol::HuiZhongMeterProtocol()
{
}

HuiZhongMeterProtocol::~HuiZhongMeterProtocol()
{
}

void HuiZhongMeterProtocol::analyseFrame()
{
	qDebug()<<"HuiZhongMeterProtocol::analyseFrame thread:"<<QThread::currentThreadId();
	if (NULL == m_CJ188DataFrame)
	{
		return;
	}

	UINT8 ctrlCode = m_CJ188DataFrame->ctrlCode;
	UINT8 DI0 = m_CJ188DataFrame->dataID[0];
	UINT8 DI1 = m_CJ188DataFrame->dataID[1];

	float *flow = new float[4];
	float *heat = new float[4];
	float *coe = new float[4];

	switch (ctrlCode)
	{
	case 0x83: //�����
		m_fullMeterNo.clear();
		for (int i=0; i<CJ188_ADDR_LEN; i++)
		{
			m_fullMeterNo.append(QString("%1").arg(m_CJ188DataFrame->addr[i], 2, 16)).replace(' ', '0');
		}
		break;
	case 0xBA: //���߾���������������������ϵ��
		if (DI0==0x2A && DI1==0x49) //���߾�������������
		{
			//����
			memcpy(flow, &m_CJ188DataFrame->data[4], 4);
			m_flow = QString::number(*flow, 'f', 4);

			//����
			memcpy(heat, &m_CJ188DataFrame->data[0], 4);
			m_heat = QString::number(*heat, 'f', 4);
		}
		else if (DI0==0x2A && DI1==0x43) //������ϵ��
		{
 			memcpy(coe, &m_CJ188DataFrame->data[0], 4);	//��������ϵ�������Ƿ���ȷ ������
			m_Coe = QString::number(*coe);
		}
		break;
	case 0x81: //��������(��������)
		break;
	case 0xBB: //�춨״̬������˳���д����ϵ��
		if (DI0==0xB2 || DI1==0x6C) //�����춨
		{
		}
		else if (DI0==0xB2 || DI1==0x6D) //�����춨
		{
		}
		else if (DI0==0xB2 || DI1==0x63) //д����ϵ��
		{
		}
		break;
	default:
		break;
	} //end of 	switch (ctrlCode)
}

void HuiZhongMeterProtocol::makeFrameOfReadMeterNO()
{
	qDebug()<<"HuiZhongMeterProtocol::makeFrameOfReadMeterNO thread:"<<QThread::currentThreadId();

	m_sendBuf.clear();
	m_sendBuf.append(METER_START_CODE);//��ʼ��
	m_sendBuf.append(METER_TYPE_ASK_CODE); //�Ǳ����� ����
	for (int m=0; m<CJ188_ADDR_LEN; m++)
	{
		m_sendBuf.append(METER_ADDR_CODE); //�㲥��ַ
	}
	m_sendBuf.append(0x03).append(0x03).append(0x81).append(0x0A).append(0x05);
	m_sendBuf.append(0xC4).append(0x16);
}

void HuiZhongMeterProtocol::makeFrameOfReadMeterFlowCoe()
{
	qDebug()<<"HuiZhongMeterProtocol::makeFrameOfReadMeterFlowCoe thread:"<<QThread::currentThreadId();

	m_sendBuf.clear();
	m_sendBuf.append(METER_START_CODE);//��ʼ��
	m_sendBuf.append(METER_TYPE_ASK_CODE); //�Ǳ����� ����
	for (int m=0; m<CJ188_ADDR_LEN; m++)
	{
		m_sendBuf.append(METER_ADDR_CODE); //�㲥��ַ
	}
	m_sendBuf.append(0x3A).append(0x03).append(0x2A).append(0x43).append(0x01);
	m_sendBuf.append(0xD9).append(0x16);
}

void HuiZhongMeterProtocol::makeFrameOfReadMeterData(int vType)
{
	qDebug()<<"HuiZhongMeterProtocol::makeFrameOfReadMeterData thread:"<<QThread::currentThreadId();

	m_sendBuf.clear();
	m_sendBuf.append(METER_START_CODE);//��ʼ��
	m_sendBuf.append(METER_TYPE_ASK_CODE); //�Ǳ����� ����
	for (int m=0; m<CJ188_ADDR_LEN; m++)
	{
		m_sendBuf.append(METER_ADDR_CODE); //�㲥��ַ
	}
	m_sendBuf.append(0x3A).append(0x03).append(0x2A).append(0x49).append(0x06);
	m_sendBuf.append(0xE4).append(0x16);
}

void HuiZhongMeterProtocol::makeFrameOfSetVerifyStatus(int vType)
{
	qDebug()<<"HuiZhongMeterProtocol::makeFrameOfSetVerifyStatus thread:"<<QThread::currentThreadId();

	m_sendBuf.clear();
	m_sendBuf.append(METER_START_CODE);//��ʼ��
	m_sendBuf.append(METER_TYPE_ASK_CODE); //�Ǳ����� ����
	for (int m=0; m<CJ188_ADDR_LEN; m++)
	{
		m_sendBuf.append(METER_ADDR_CODE); //�㲥��ַ
	}
	m_sendBuf.append(0x3B).append(0x04).append(0xB2);
	if (vType==VTYPE_FLOW) //���������춨
	{
		m_sendBuf.append(0x6D).append(0x01).append(0x01).append(0x8E).append(0x16);
	}
	else if (vType==VTYPE_HEAT) //���������춨
	{
		m_sendBuf.append(0x6C).append(0x01).append(0x01).append(0x8D).append(0x16);
	}
}

void HuiZhongMeterProtocol::makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo)
{

}

void HuiZhongMeterProtocol::makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr)
{

}

void HuiZhongMeterProtocol::makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr, MeterCoe_PTR oldCoe)
{

}

/***********************************************
���ࣺStdTempProtocol
���ܣ���׼�¶ȼ�Э�鸸��
************************************************/
StdTempProtocol::StdTempProtocol()
{
}

StdTempProtocol::~StdTempProtocol()
{
}

bool StdTempProtocol::readTemperComBuffer(QByteArray tmp)
{
	return true;
}

void StdTempProtocol::makeSendBuf(stdTempCommand)
{

}

QByteArray StdTempProtocol::getSendBuf()
{
	return m_sendBuf;
}

QString	StdTempProtocol::getReadStr()
{
	return m_valueStr;
}

/***********************************************
������sti1062ATempProtocol
���ܣ���׼�¶ȼ�-STI-1062A����Э��
************************************************/
sti1062ATempProtocol::sti1062ATempProtocol()
{
	m_state = DATA_STATE;
}

sti1062ATempProtocol::~sti1062ATempProtocol()
{

}

void sti1062ATempProtocol::makeSendBuf(stdTempCommand command)
{
	switch(command)
	{
	case stdTempT12:
		m_sendBuf = CHNT12;
		break;
	case stdTempR12:
		m_sendBuf = CHNR12;
		break;
	case stdTempT1:
		m_sendBuf = CHNT1;
		break;
	case stdTempT2:
		m_sendBuf = CHNT2;
		break;
	case stdTempR1:
		m_sendBuf = CHNR1;
		break;
	case stdTempR2:
		m_sendBuf = CHNR2;
		break;
	default:
		m_sendBuf = CHNT12;
		break;
	}
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

/***********************************************
������sti1062ATempProtocol END
************************************************/

/***********************************************
������instituteTempProtocol
���ܣ���׼�¶ȼ�-����Ժ����Э��
************************************************/
instituteTempProtocol::instituteTempProtocol()
{
}

instituteTempProtocol::~instituteTempProtocol()
{

}

void instituteTempProtocol::makeSendBuf(stdTempCommand command)
{
	
}

bool instituteTempProtocol::readTemperComBuffer(QByteArray tmp)
{
	int number = tmp.size();
	//Q_ASSERT(number > 0);

	bool ret = false;
	char b = '\0';
	
	return ret;
}

/***********************************************
������instituteTempProtocol END
************************************************/

/***********************************************
������huayiTempProtocol
���ܣ���׼�¶ȼ�-����Э��
************************************************/
huayiTempProtocol::huayiTempProtocol()
{
}

huayiTempProtocol::~huayiTempProtocol()
{

}

void huayiTempProtocol::makeSendBuf(stdTempCommand command)
{
	
}

bool huayiTempProtocol::readTemperComBuffer(QByteArray tmp)
{
	int number = tmp.size();
	//Q_ASSERT(number > 0);
	if (number != 11)
	{
		return false;
	}

	m_valueStr = tmp.mid(2);
	return true;
}

/***********************************************
������huayiTempProtocol END
************************************************/

/***********************************************
������lcModbusRTUFunc
���ܣ�����EDA9150A/9017��Ʒ, ModbusRTUͨѶЭ����
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
** ��ȡ����ģ��9150A��9017������
** address, ����ģ����豸��ַ, ͨ��Ϊ0x01
** func, ������
** start, ����ȡ��ģ���ڲ�ֻ���Ĵ����Ŀ�ʼ��ַ
** regCount, ��ȡ�ļ�Ⱥ������
*/
void lcModbusRTUProtocol::makeSendBuf(uchar address, lcModbusRTUFunc func, UINT16 start, UINT16 regCount)
{
	m_sendBuf.clear();
	m_sendBuf.append(address);
	m_sendBuf.append((uchar)(func));
	m_sendBuf.append((uchar)(start>>BYTE_LENGTH));
	m_sendBuf.append((uchar)(start));
	m_sendBuf.append((uchar)(regCount>>BYTE_LENGTH));
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

//����һ�����޸�16·����ֵ, ģ�鲻��������, ֻ�ܷ�����, ÿ��8·
void lcModbusRTUProtocol::makeWriteBuf(lcMod9150AWriteCmd cmd)
{
	m_writeBuf.clear();
	m_writeBuf.append(cmd.address);
	m_writeBuf.append((uchar)(cmd.func));
	m_writeBuf.append((uchar)(cmd.start>>BYTE_LENGTH));
	m_writeBuf.append((uchar)(cmd.start));
	m_writeBuf.append((uchar)(cmd.regCount>>BYTE_LENGTH));
	m_writeBuf.append((uchar)(cmd.regCount));
	m_writeBuf.append((uchar)(cmd.ByteCount));
	for(int i=0;i<EDA_9150A_ROUTE_CNT/2;i++)
	{
		int diValue = cmd.pData[i];//ͨ����; ��DI[0]~DI[7], DI[8]~DI[15]
		for (int j=EDA9150A_ROUTE_BYTES-1;j>=0;j--)
		{			
			uchar b= (uchar)(diValue>>(j*BYTE_LENGTH));
			m_writeBuf.append(b);
		}
	}
	m_writeBuf.append(getCRCArray(calcModRtuCRC((uchar *)m_writeBuf.data(), m_writeBuf.length())));
}

QByteArray lcModbusRTUProtocol::getWriteBuf()
{
	return m_writeBuf;
}

//��ȡ��׼��������; ֻ�ܼ���ȡ����(0x03)�ķ���ֵ, ���ܼ����������ķ���ֵ
bool lcModbusRTUProtocol::readMeterComBuffer(QByteArray tmp)
{
	int number = tmp.size();
	//Q_ASSERT(number > 0);
	UINT16 dataLenInfo;//���ڼ��鷵�ص����ݳ�����Ϣ�Ƿ���ȷ
	UINT16 crc;//���ص�crcУ��ֵ
	UINT16 calc_crc;//���ڼ��鷵�ص�crcУ��ֵ

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
			if(b == m_sendBuf.at(0))//���͵��豸��ַ
			{
				m_readBuf.append(b);//�����豸��ַ
				m_state = address_state;
			}
			else//��Ӧ�ĵ�ַλ����, ��ֹ����
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
			if(b == m_sendBuf.at(1))//���͵Ĺ�����
			{
				m_readBuf.append(b);//���빦����
				m_state = func_state;
			}
			else//��Ӧ�Ĺ��������, ��ֹ����
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
				m_readBuf.append(b);//�������ݳ�����Ϣ��ĸ�λ
				m_state = length_state;

				//�������ݳ�����Ϣ�Ƿ���ȷ
				m_calcDataLength = (m_sendBuf.at(5))<<1;//Ԥ�ƻ�Ӧ���������ֽ���

				if (b != m_calcDataLength)//���ݳ�����Ϣ����, ��ֹ����
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
			if (m_readBuf.length() == (MOD_ADDRESS_LEN+MOD_FUNC_LEN+MOD_DATALEN_LEN))//��ȡ���ݳ�����Ϣ�����
			{
				//��ʼ��ȡ������
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
				m_crcValue.append(b);//��ȡcrcУ��ֵ�ĵ�λ
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
			m_crcValue.append(b);//crcУ��ֵ�ĸ�λ
			crc  = ( (((uchar)m_crcValue.at(1))<<BYTE_LENGTH) | (uchar)m_crcValue.at(0) );
			calc_crc = calcModRtuCRC((uchar *)m_readBuf.data(), m_readBuf.length());
			if (crc == calc_crc)//crcУ��ͨ��
			{
				ret = true;
			}
			else//crcУ�����
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

	if (ret)//��ʼ�����в���, �Ա���һ�ν���
	{
		initParams();//m_valueArray��������, �������
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
** i, ����m_sendbuf.startΪ��ʼ��ַ��ͨ��ƫ����; i��������0��ʼ
** ����ֵ�и�λ��ǰ, ��λ�ں�
*/
QByteArray lcModbusRTUProtocol::getData(int i)
{
	if ( (EDA9150A_ROUTE_BYTES*i) > m_valueArray.length())//i���ܳ�������ȡ��ͨ������
	{
		return QByteArray();
	}

	QByteArray data;
	for (int k=0;k<EDA9150A_ROUTE_BYTES;k++)
		data.append(m_valueArray.at(EDA9150A_ROUTE_BYTES*i+k));
	
	return data;
}

/*
** i, ͨ����; ��0��ʼ, ��󲻳���15
** ÿ��ͨ��ռ��4���ֽ�, �����Ĵ���
*/
int lcModbusRTUProtocol::getIntData(int i)
{
	QByteArray data = getData(i);
	if (data.isNull())//���ȡ����ʧ��, ����-1
	{
		return -1;
	}

	int value = 0;	
	for (int k=0;k<EDA9150A_ROUTE_BYTES;k++)
	{
		value |= ( ((uchar)data.at(k)) << ((EDA9150A_ROUTE_BYTES-1-k)*BYTE_LENGTH) );
	}
	return value;
}
/***********************************************
������lcModbusRTUFunc END
************************************************/