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
#include "algorithm.h"

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

	float m_balValue;
	float m_lastValue;
	unsigned int m_count;

public slots:
	bool readBalanceComBuffer(QByteArray tmp);
	float getBalanceValue();

private:
};
//��ƽЭ�� end

//��λ������Э�� begin
#define		CTRL_START_CODE		0x69		//��ʼ��
#define		CTRL_END_CODE		0x16		//������
#define		CTRL_FUNC_RELAY		0x01		//������-�̵�������
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
}NewCtrl_Frame_Struct;

#define NEW_CTRL_VERSION  0  //�¿��ư�Э��汾�� �з���
#define OLD_CTRL_VERSION  1  //�Ͽ��ư�Э��汾�� �޷���
#define LICH_CTRL_VERSION 2  //�������ư�Э��汾�� �з���

/*
** ����Э�����
*/
class PROTOCOL_EXPORT CtrlProtocol : public CProtocol
{
public:
	CtrlProtocol();
	~CtrlProtocol();

	QByteArray m_sendBuf;

public slots:
	//pure virtual
	virtual void makeFrameOfCtrlRelay(UINT8 portno, bool status) = 0;
	virtual void makeFrameOfCtrlRegulate(UINT8 portno, UINT16 degree) = 0;
	virtual void makeFrameOfCtrlQuery() = 0;
	virtual void makeFrameOfCtrlWaterPump(UINT8 portno, bool status) = 0;
	virtual void makeFrameOfSetDriverFreq(int freq) = 0;
	virtual UINT8 readCtrlComBuffer(QByteArray tmp) = 0;
	virtual void analyseFrame() = 0;

	//virtual
	virtual QByteArray getSendBuf();

private:
};

//�¿��ư�Э���� ��ӦЭ������ 
class PROTOCOL_EXPORT NewCtrlProtocol : public CtrlProtocol
{
	NewCtrl_Frame_Struct *m_ctrlFrame;
	float m_balValue;

public:
	NewCtrlProtocol();
	~NewCtrlProtocol();

public slots:
	//pure virtual
	virtual void makeFrameOfCtrlRelay(UINT8 portno, bool status);
	virtual void makeFrameOfCtrlRegulate(UINT8 portno, UINT16 degree);
	virtual void makeFrameOfCtrlQuery();
	virtual void makeFrameOfCtrlWaterPump(UINT8 portno, bool status);
	virtual void makeFrameOfSetDriverFreq(int freq);
	virtual UINT8 readCtrlComBuffer(QByteArray tmp);
	virtual void analyseFrame();

	//virtual
	virtual UINT8 CountCheck(NewCtrl_Frame_Struct *pFrame);
	virtual NewCtrl_Frame_Struct* getConFrame();
	virtual float getBalanceValue();
};


//�Ͽ��ư�Э���� ��ӦЭ������
class PROTOCOL_EXPORT OldCtrlProtocol : public CtrlProtocol
{
public:
	OldCtrlProtocol();
	~OldCtrlProtocol();

	QMap <int, UINT8> portCloseMap; //�պϼ̵���
	QMap <int, UINT8> portOpenMap;  //�Ͽ��̵���

	public slots:
	//pure virtual
	virtual void makeFrameOfCtrlRelay(UINT8 portno, bool status);
	virtual void makeFrameOfCtrlRegulate(UINT8 portno, UINT16 degree);
	virtual void makeFrameOfCtrlQuery();
	virtual void makeFrameOfCtrlWaterPump(UINT8 portno, bool status);
	virtual void makeFrameOfSetDriverFreq(int freq);
	virtual UINT8 readCtrlComBuffer(QByteArray tmp);
	virtual void analyseFrame();

	//virtual
	virtual void makeFrameOfCtrlPressPump(bool status); //��ѹ�� ��ʱ����
};

//��λ������Э�� end

//������ͨѶЭ�� begin
#define     METER_WAKEUP_CODE_NUM		200     //���������
#define     METER_PREFIX_CODE_NUM		4       //ǰ���ֽڸ���

#define		METER_WAKEUP_CODE	        0xFF	//������
#define		METER_PREFIX_CODE	        0xFE	//ǰ���ֽ�
#define		METER_START_CODE	        0x68	//��ʼ��
#define		METER_TYPE_ASK_CODE		    0x20	//�Ǳ����� ������ ����
#define		METER_TYPE_ANSWER_CODE	    0x25	//�Ǳ����� ������ ��Ӧ
#define     METER_ADDR_CODE		        0xAA	//�㲥��ַ
#define     METER_CTRL_CODE		        0x01	//������
#define     METER_END_CODE		        0x16	//������

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

#define     METER_ADDR_LEN		7
#define     METER_DATAID_LEN	2
#define     METER_DATA_LEN		55

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
}DeluMeter_Frame_Struct;

//������ͨѶЭ�����
class PROTOCOL_EXPORT MeterProtocol : public CProtocol
{
public:
	MeterProtocol();
	~MeterProtocol();

	QByteArray m_sendBuf;
	QString m_fullMeterNo;  //������� 7���ֽ�
	QString m_inTemper; //��ˮ�¶�
	QString m_outTemper;//��ˮ�¶�
	QString m_flow; //���� 
	QString m_heat; //����
	QString m_date; //��ǰ����
	QString m_bigCoe; //������������ϵ��
	QString m_mid2Coe; //����������ϵ��
	QString m_mid1Coe; //����һ����ϵ��
	QString m_smallCoe; //С����������ϵ��

public slots:
	virtual UINT8 readMeterComBuffer(QByteArray tmp){return 0;};
	virtual void analyseFrame(){};

	virtual void makeFrameOfReadMeter(){};        //�����㲥��ַ����
	virtual void makeFrameOfSetVerifyStatus(){};	//���ý���춨״̬
	virtual void makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo){};	//�޸ı��
	virtual void makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr){};	//�޸���������

	virtual QByteArray getSendFrame();
	virtual QString getFullMeterNo();
	virtual QString getFlow();
	virtual QString getInTemper();
	virtual QString getOutTemper();
	virtual QString getHeat();
	virtual QString getDate();
	virtual QString getBigCoe();
	virtual QString getMid2Coe();
	virtual QString getMid1Coe();
	virtual QString getSmallCoe();

private:

};

//��³������ͨѶЭ����
class PROTOCOL_EXPORT DeluMeterProtocol : public MeterProtocol
{
public:
	DeluMeterProtocol();
	~DeluMeterProtocol();

public slots:
	virtual UINT8 CountCheck(DeluMeter_Frame_Struct *pFrame);
	virtual UINT8 readMeterComBuffer(QByteArray tmp);
	virtual void analyseFrame();

	virtual void makeFrameOfReadMeter();        //�����㲥��ַ����
	virtual void makeFrameOfSetVerifyStatus();	//���ý���춨״̬
	virtual void makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo);	//�޸ı��(14λ���)
	virtual void makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr);	//�޸���������

private:
	DeluMeter_Frame_Struct *m_deluMeterFrame;

};

//���������ͨѶЭ����
class PROTOCOL_EXPORT TgMeterProtocol : public MeterProtocol
{
public:
	TgMeterProtocol();
	~TgMeterProtocol();

public slots:
	virtual UINT8 CountCheck(DeluMeter_Frame_Struct *pFrame);
	virtual UINT8 readMeterComBuffer(QByteArray tmp);
	virtual void analyseFrame();

	virtual void makeFrameOfReadMeter();        //�����㲥��ַ����
	virtual void makeFrameOfSetVerifyStatus();	//���ý���춨״̬
	virtual void makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo);	//�޸ı��
	virtual void makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr);	//�޸���������

private:
	DeluMeter_Frame_Struct *m_deluMeterFrame;

};
//������ͨѶЭ�� end

//��׼�¶ȼ�-STI-1062A����Э����
#define CHNT12	QString("FETC?").toLatin1().append(ASCII_CR).append(ASCII_LF)//��ȡͨ��1��2���¶�ֵ
#define CHNR12	QString("FETC?R").toLatin1().append(ASCII_CR).append(ASCII_LF)//��ȡͨ��1��2�ĵ���ֵ
#define CHNT1	QString("FETC? (@1)").toLatin1().append(ASCII_CR).append(ASCII_LF)//��ȡͨ��1���¶�ֵ
#define CHNR1	QString("FETC?R (@1)").toLatin1().append(ASCII_CR).append(ASCII_LF)//��ȡͨ��1�ĵ���ֵ
#define CHNT2	QString("FETC? (@2)").toLatin1().append(ASCII_CR).append(ASCII_LF)//��ȡͨ��2���¶�ֵ
#define CHNR2	QString("FETC?R (@2)").toLatin1().append(ASCII_CR).append(ASCII_LF)//��ȡͨ��2�ĵ���ֵ

#define DATA_STATE	0x00
#define END_STATE	0x01
enum sti1062Acommand
{
	sti1062aT12=0, //����ͨ��1��2��·�¶ȡ�����ֵ���ݻس�+���з�����ͨ��1��2
	sti1062aR12,
	sti1062aT1,
	sti1062aT2,
	sti1062aR1,
	sti1062aR2
};

class PROTOCOL_EXPORT sti1062ATempProtocol : public CProtocol
{
	QByteArray m_sendBuf;//��������
	QByteArray m_readBuf;//���յ�������
	QString m_valueStr;//��������ֵ
	int m_state;
public:
	sti1062ATempProtocol();
	~sti1062ATempProtocol();

public slots:
	bool readTemperComBuffer(QByteArray tmp);
	void makeSendBuf(sti1062Acommand);
	QByteArray getSendBuf();
	QString getReadStr();
private:

};//sti1062ATempProtocol END

//����EDA9150A/9017��Ʒ, ModbusRTUͨѶЭ��
//��Ҫ���ڶ�ȡ�����ӵ�������Ƶ�������
#define EDA_9150A_START_REG	0x0010//EDA9150Aģ���һͨ������ʼ�Ĵ����ĵ�ַ
#define EDA_9150A_ROUTE_CNT	0x0010//EDA9150Aģ��ͨ����16·
#define EDA_9017_START_REG	0x0003//EDA9017ģ���һ·�Ĵ����ĵ�ַ, ��12·
#define EDA_9017_ROUTE_CNT	0x000C//EDA9017ģ��ͨ����12·
#define MOD_ADDRESS_LEN		0x01//��Ӧ�ĵ�ַλ���ֽ���
#define MOD_FUNC_LEN		0x01//��Ӧ�Ĺ�����λ���ֽ���
#define MOD_DATALEN_LEN		0x01//��Ӧ�����ݳ�����Ϣλ���ֽ���

enum lcModbusRTUFunc//����ModbusRTU, ������
{
	read_multi_switch_out = 0x01,//�� 1 ·���·���������״̬
	read_multi_switch_in = 0x02,//�� 1 ·���·����������״̬ DI
	read_multi_reg = 0x03//����·�Ĵ���
};

enum lcModAnswerState
{
	init_state = 0x00,
	address_state = 0x01,
	func_state = 0x02,
	length_state = 0x03,
	data_state = 0x04,
	crc_state = 0x05
};

struct lcModSendCmd
{
	uchar address;
	lcModbusRTUFunc func; 
	UINT16 start;
	UINT16 regCount;
};

class PROTOCOL_EXPORT lcModbusRTUProtocol : public CProtocol
{	
public:
	lcModbusRTUProtocol();
	~lcModbusRTUProtocol();
public slots:
	bool readMeterComBuffer(QByteArray tmp);//��ȡ��׼��������
	void makeSendBuf(uchar address, lcModbusRTUFunc func, UINT16 start, UINT16 regCount);
	void makeSendBuf(lcModSendCmd);
	QByteArray getSendBuf();
	QByteArray getReadVale();//��ȡȫ����ȡ����ֵ
	QByteArray getData(int i);//��ȡ��i���Ĵ�����ֵ, ��λ��0, ��λ��1
	int getIntData(int i);//��ȡ��i��ͨ����ֵ, ����DI0����0ͨ��; DI6����6ͨ��
private:
	void initParams();//��ʼ������

	QByteArray m_sendBuf;//��������
	QByteArray m_readBuf;//���յ�������(����crcУ��ֵ�����������)
	UINT16 m_readDataLength;//���յ��ĸ����Ĵ������ݳ���
	
	QByteArray m_valueArray;//�����ĸ����Ĵ�����ֵ
	QByteArray m_crcValue;//������crcֵ

	UINT16 m_calcDataLength;//���ݷ�������, Ԥ�Ƶķ������ݳ���
	
	lcModAnswerState m_state;
};//lcModbusRTUProtocol END

#endif // PROTOCOL_H
