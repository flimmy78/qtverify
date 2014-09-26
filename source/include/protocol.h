#ifndef PROTOCOL_H
#define PROTOCOL_H

#ifdef PROTOCOL_DLL
#  ifdef WIN32
#  define PROTOCOL_EXPORT __declspec(dllexport)
#  else
#  define PROTOCOL_EXPORT
#  endif
#else
#  ifdef WIN32
#  define PROTOCOL_EXPORT __declspec(dllimport)
#  else
#  define PROTOCOL_EXPORT
#  endif
#endif

#include <intsafe.h>
#include <QtCore/QThread>
#include <QtCore/QMap>

//Э�����
class  CProtocol
{
public:
	CProtocol();
	~CProtocol();

	float calc(float a, float b);

private:

};


//�¶Ȳɼ�Э�� begin
#define DATA_WIDTH			4  //�¶�ֵ�ַ������� 4 
#define DATA_PRECISION		1  //�¶�ֵ���ȣ�һλС��

#define ADDR_FIX			0x80
#define ADDR_FIRST			0x01
#define ADDR_CODE_FIRST		(ADDR_FIX + ADDR_FIRST)
#define READ_CODE			0x52


#define PV_STATE		0x00
#define SV_STATE		0x01
#define MV_STATE		0x02
#define WARN_STATE      0x03
#define PARA_STATE      0x04
#define CHECK_STATE     0x05


typedef struct  
{
	INT16 pv;		//����ֵPV��
	INT16 sv;		//����ֵSV
	INT8  mv;       //���ֵMV
	INT8 warn;	    //����״̬
	INT16 para;     //����д����ֵ
	INT16 cs;	//У����
}Temp_Frame_Struct;

class PROTOCOL_EXPORT TempProtocol : public CProtocol
{

	QString m_tempStr;
	QByteArray m_sendBuf;

public:
	TempProtocol();
	~TempProtocol();

	Temp_Frame_Struct *m_tempFrame;

public slots:
	bool readTemperComBuffer(QByteArray tmp);
	INT16 CountCheck(Temp_Frame_Struct *pFrame);
	void analyseFrame();
	void makeSendBuf();

	QString getTempStr();
	QByteArray getSendBuf();

private:

};
//�¶Ȳɼ�Э�� end


//��ƽЭ�� begin
#define    ASCII_CR				0x0D	//�س���
#define    ASCII_LF				0x0A	//���м�

class PROTOCOL_EXPORT BalanceProtocol : public CProtocol
{

public:
	BalanceProtocol();
	~BalanceProtocol();

	QString m_balValue;

public slots:
	bool readBalanceComBuffer(QByteArray tmp);
	QString getBalanceValue();

private:
};
//��ƽЭ�� end

//��λ������Э�� begin
#define		CTRL_START_CODE		0x69		//��ʼ��
#define		CTRL_FUNC_RELAY		0x01		//������-�̵�������
#define		CTRL_END_CODE		0x16		//������
#define		CTRL_FUNC_REGULATE  0x02		//������-���ڷ�����
#define     CTRL_FUNC_QUERY		0x03		//������-��ѯ
#define     CTRL_FUNC_BALANCE	0x04		//������-��ȡ��ƽ����

#define		CTRL_START_STATE	0x00
#define		CTRL_FUNC_STATE		0x01
#define		CTRL_DATA_STATE		0x02
#define		CTRL_CS_STATE       0x03
#define		CTRL_END_STATE      0x04

#define		DATA_LENGTH			55  //�������ֽڸ���(���55��)
#define		RELAY_DATA_LENGTH	5	//�̵������� �������ֽڸ���
#define		REGU_DATA_LENGTH	3   //���ڷ����� �������ֽڸ���
#define     BAL_DATA_LENGTH		22	//��ƽ	�������ֽڸ���

typedef struct  
{
	UINT8 startCode;	//��ʼ��
	UINT8 funcCode;		//������
	UINT8 data[DATA_LENGTH];  //������
	UINT8 cs;	    //У����
	UINT8 endCode;      //������
}Ctrl_Frame_Struct;

class PROTOCOL_EXPORT ControlProtocol : public CProtocol
{

	QByteArray m_sendBuf;
	Ctrl_Frame_Struct *m_ctrlFrame;
	QString m_balValueStr;

public:
	ControlProtocol();
	~ControlProtocol();


public slots:
	void makeRelaySendBuf(UINT8 portno, bool status);
	void makeRegulateSendBuf(UINT8 portno, UINT16 degree);
	void makeQuerySendBuf();
	QByteArray getSendBuf();
	UINT8 readControlComBuffer(QByteArray tmp);
	UINT8 CountCheck(Ctrl_Frame_Struct *pFrame);
	void analyseFrame();
	Ctrl_Frame_Struct* getConFrame();
	QString getBalanceValue();

private:
};
//��λ������Э�� end

//������ͨѶЭ�� begin
#define     WAKEUP_CODE_NUM		200     //���������
#define     PREFIX_CODE_NUM		4       //ǰ���ֽڸ���

#define		METER_WAKEUP_CODE	0xFF	//������
#define		METER_PREFIX_CODE	0xFE	//ǰ���ֽ�
#define		METER_START_CODE	0x68	//��ʼ��
#define		METER_TYPE_ASK_CODE		0x20	//�Ǳ����� ������ ����
#define		METER_TYPE_ANSWER_CODE	0x25	//�Ǳ����� ������ ��Ӧ
#define     METER_ADDR_CODE		0xAA	//�㲥��ַ
#define     METER_CTRL_CODE		0x01	//������
#define     METER_END_CODE		0x16	//������

#define		METER_START_STATE		0x00
#define		METER_TYPE_STATE		0x01
#define		METER_ADDR_STATE		0x02
#define		METER_CTRL_STATE		0x03
#define		METER_DATALEN_STATE		0x04
#define		METER_DATAID_STATE		0x05
#define		METER_SN_STATE			0x06
#define		METER_DATA_STATE		0x07
#define		METER_CS_STATE			0x08
#define		METER_END_STATE			0x09

#define METER_ADDR_LEN		7
#define METER_DATAID_LEN	2
#define METER_DATA_LEN		55

typedef struct  
{
	UINT8 startCode;	//��ʼ��
	UINT8 typeCode;		//�Ǳ�����
	UINT8 addr[METER_ADDR_LEN];		//��ַ
	UINT8 ctrlCode;		//������
	UINT8 dataLen;		//���ݳ���
	UINT8 dataID[METER_DATAID_LEN];	//���ݱ�ʶ
	UINT8 sn;			//���к�
	UINT8 data[METER_DATA_LEN];		//������
	UINT8 cs;	    //У����
	UINT8 endCode;      //������
}Meter_Frame_Struct;

class PROTOCOL_EXPORT MeterProtocol : public CProtocol
{

	QByteArray m_sendBuf;
	Meter_Frame_Struct *m_meterFrame;

public:
	MeterProtocol();
	~MeterProtocol();

public slots:
	UINT8 readMeterComBuffer(QByteArray tmp);
 	UINT8 CountCheck(Meter_Frame_Struct *pFrame);
 	void analyseFrame();

	void makeFrameOfReadMeter();        //�����㲥��ַ����
	void makeFrameOfSetVerifyStatus();	//���ý���춨״̬
	void makeFrameOfModifyMeterNo();	//�޸ı��
	void makeFrameOfModifyFlowPara();	//�޸���������

	QByteArray getSendFrame();
	QString getFullMeterNo();
	QString getFlow();
	QString getInTemper();
	QString getOutTemper();
	QString getHeat();


private:
	QString m_fullMeterNo;  //������� 7���ֽ�
	QString m_inTemper; //��ˮ�¶�
	QString m_outTemper;//��ˮ�¶�
	QString m_flow; //���� 
	QString m_heat; //����
	QString m_date; //��ǰ����

};
//������ͨѶЭ�� end

#endif // PROTOCOL_H
