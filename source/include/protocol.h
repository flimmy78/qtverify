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
class PROTOCOL_EXPORT ControlProtocol : public CProtocol
{

public:
	ControlProtocol();
	~ControlProtocol();

	QByteArray m_sendBuf;
	QMap<int, UINT8> m_closePortNo;
	QMap<int, UINT8> m_OpenPortNo;

public slots:
	void makeRelaySendBuf(int portno, bool status);
	QByteArray getSendBuf();

private:
};

#endif // PROTOCOL_H
