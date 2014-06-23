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

//协议基类
class  CProtocol
{
public:
	CProtocol();
	~CProtocol();

	float calc(float a, float b);

private:

};


//温度采集协议 begin
#define DATA_WIDTH			4  //温度值字符串长度 4 
#define DATA_PRECISION		1  //温度值精度，一位小数

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
	INT16 pv;		//测量值PV，
	INT16 sv;		//给定值SV
	INT8  mv;       //输出值MV
	INT8 warn;	    //报警状态
	INT16 para;     //所读写参数值
	INT16 check;	//校验码
}Temp_Frame_Struct;

//温度采集协议
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
//温度采集协议 end


//天平协议
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

//下位机控制协议 begin
#define		START_CODE		0x69		//起始码
#define		END_CODE		0x16		//结束码
#define		FUNC_RELAY		0x01		//功能码-继电器控制
#define		FUNC_REGULATE   0x02		//功能码-调节阀控制
#define     FUNC_QUERY		0x03		//功能码-查询


#define START_STATE		0x00
#define FUNC_STATE		0x01
#define DATA_STATE		0x02
#define CS_STATE        0x03
#define END_STATE       0x04

#define		DATA_LENGTH			55  //数据区字节个数(最多55个)
#define		RELAY_DATA_LENGTH	5	//继电器控制 数据区字节个数
#define		REGU_DATA_LENGTH	3   //调节阀控制 数据区字节个数
typedef struct  
{
	UINT8 startCode;	//起始码
	UINT8 funcCode;		//功能码
	UINT8 data[DATA_LENGTH];  //数据区
	UINT8 check;	    //校验码
	UINT8 endCode;      //结束码
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
