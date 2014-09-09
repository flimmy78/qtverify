#ifndef	COMOBJECT_H
#define COMOBJECT_H

#ifdef COMOBJECT_DLL
#  ifdef WIN32
#  define COMOBJECT_EXPORT __declspec(dllexport)
#  else
#  define COMOBJECT_EXPORT
#  endif
#else
#  ifdef WIN32
#  define COMOBJECT_EXPORT __declspec(dllimport)
#  else
#  define COMOBJECT_EXPORT
#  endif
#endif


#include <QtCore/QThread>  
#include <QtCore/QObject> 

#include "protocol.h"
#include "comsetdlg.h"


#define VALVE_OPEN		true	//阀门打开状态
#define VALVE_CLOSE		false   //阀门关闭状态

#define REG_SUCCESS	 true	//调节阀调节成功
#define REG_FAILED	 false  //调节阀调节失败


class COMOBJECT_EXPORT ComThread : public QThread 
{      
	Q_OBJECT 

public:       
	ComThread(QObject* parent=0);
	~ComThread();

public slots:     
	void slot_main();   

protected:     
	virtual void run();     
};  


#include "qextserialport.h"
#include "datatestdlg_global.h"

#define TIME_OUT	10		//延时，TIME_OUT是串口读写的延时

class COMOBJECT_EXPORT ComObject : public QObject 
{       
	Q_OBJECT  

public: 
	ComObject(QObject* parent=0);
	~ComObject();


signals:

public slots:

};    

/***************************************
类名：TempComObject
功能：温度串口类- 打开串口；设置串口参数；关闭串口；
****************************************/
class COMOBJECT_EXPORT TempComObject : public ComObject
{
	Q_OBJECT  

public: 
	TempComObject(QObject* parent=0);
	~TempComObject();

	QextSerialPort *m_tempCom;      //温度采集串口
	Temp_Frame_Struct *m_tempFrame; //温度采集通讯帧结构
	TempProtocol *m_tempProtocol;   //温度采集通讯协议类对象

signals:
	void temperatureIsReady(const QString& tempStr); //成功获取温度值

public slots:
	void openTemperatureCom(ComInfoStruct *comStruct);
	void writeTemperatureComBuffer();
	void readTemperatureComBuffer();

};

/***************************************
类名：ValveComObject
功能：阀门控制串口类- 打开串口；设置串口参数；关闭串口；
****************************************/
class COMOBJECT_EXPORT ControlComObject : public ComObject
{
	Q_OBJECT  

public: 
	ControlComObject(QObject* parent=0);
	~ControlComObject();

	QextSerialPort *m_controlCom;
	ControlProtocol *m_controlProtocol;   //下位机控制通讯协议类对象
	Con_Frame_Struct *m_conFrame;
	QByteArray m_conTmp;
	QString m_balValue;

signals:
	void controlRelayIsOk(const UINT8 &portno, const bool &status);
	void controlRegulateIsOk();
	void controlGetBalanceValueIsOk(const QString& balValue);

public slots:
	void openControlCom(ComInfoStruct *comStruct);
	void makeRelaySendBuf(UINT8 portno, bool status);
	void makeRegulateSendBuf(UINT8 portno, int degree);
	void makeQuerySendBuf();
	void readControlComBuffer();
};


/***************************************
类名：BalanceComObject
功能：天平串口类- 打开串口；设置串口参数；关闭串口；
****************************************/
class COMOBJECT_EXPORT BalanceComObject : public ComObject
{
	Q_OBJECT  

public: 
	BalanceComObject(QObject* parent=0);
	~BalanceComObject();

	QextSerialPort *m_balanceCom;
	BalanceProtocol *m_balanceProtocol;   //天平通讯协议类对象
	QByteArray m_balTmp;

signals:
	void balanceValueIsReady(const QString& tempStr); //成功获取天平数值

public slots:
	void openBalanceCom(ComInfoStruct *comStruct);
	void readBalanceComBuffer();
};

/***************************************
类名：MeterComObject
功能：热量表串口类- 打开串口；设置串口参数；关闭串口；
****************************************/
class COMOBJECT_EXPORT MeterComObject : public ComObject
{
	Q_OBJECT  

public: 
	MeterComObject(QObject* parent=0);
	~MeterComObject();

	QextSerialPort *m_meterCom;

signals:
	void readMeterNoIsOK(const QString& meterNo);

public slots:
	void openMeterCom(ComInfoStruct *comStruct);
	void readMeterComBuffer();
	void writeMeterComBuffer();

};


#endif //COMOBJECT_H