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
	INT16 check;	//У����
}Temp_Frame_Struct;

//�¶Ȳɼ�Э��
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


//��ƽЭ��
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

//��λ������Э�� begin
#define		START_CODE		0x69		//��ʼ��
#define		END_CODE		0x16		//������
#define		FUNC_RELAY		0x01		//������-�̵�������
#define		FUNC_REGULATE   0x02		//������-���ڷ�����
#define     FUNC_QUERY		0x03		//������-��ѯ


#define START_STATE		0x00
#define FUNC_STATE		0x01
#define DATA_STATE		0x02
#define CS_STATE        0x03
#define END_STATE       0x04

#define		DATA_LENGTH			55  //�������ֽڸ���(���55��)
#define		RELAY_DATA_LENGTH	5	//�̵������� �������ֽڸ���
#define		REGU_DATA_LENGTH	3   //���ڷ����� �������ֽڸ���
typedef struct  
{
	UINT8 startCode;	//��ʼ��
	UINT8 funcCode;		//������
	UINT8 data[DATA_LENGTH];  //������
	UINT8 check;	    //У����
	UINT8 endCode;      //������
}Con_Frame_Struct;

class PROTOCOL_EXPORT ControlProtocol : public CProtocol
{

public:
	ControlProtocol();
	~ControlProtocol();

	QByteArray m_sendBuf;
	Con_Frame_Struct *m_conFrame;

public slots:
	void makeRelaySendBuf(UINT8 portno, bool status);
	void makeRegulateSendBuf(UINT8 portno, int degree);
	void makeQuerySendBuf();
	QByteArray getSendBuf();
	UINT8 readControlComBuffer(QByteArray tmp);
	UINT8 CountCheck(Con_Frame_Struct *pFrame);
	void analyseFrame();

private:
};

#endif // PROTOCOL_H
