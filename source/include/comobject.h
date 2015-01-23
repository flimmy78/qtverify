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
#include <QtCore/QTimer>

#include "basedef.h"
#include "protocol.h"
#include "comsetdlg_global.h"


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
	bool openTemperatureCom(ComInfoStruct *comStruct);
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
	CtrlProtocol *m_controlProtocol;   //下位机控制通讯协议类对象
	QByteArray m_conTmp;
	QString m_balValue;
	int m_protocolVersion; //控制板通讯协议版本

	NewCtrl_Frame_Struct *m_conFrame;

signals:
	void controlRelayIsOk(const UINT8 &portno, const bool &status);
	void controlRegulateIsOk();
	void controlGetBalanceValueIsOk(const QString& balValue);

public slots:
	bool openControlCom(ComInfoStruct *comStruct);
	void askControlRelay(UINT8 portno, bool status);
	void askControlRegulate(UINT8 portno, int degree);
	void askControlQuery();
	void askControlWaterPump(UINT8 portno, bool status);
	void askSetDriverFreq(int freq);
	void readControlComBuffer();
	void readNewControlComBuffer();

	void setProtocolVersion(int version);

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
	QTimer *m_balTimer; //定时器 (轮询天平数据)

signals:
	void balanceValueIsReady(const QString& tempStr); //成功获取天平数值

public slots:
	bool openBalanceCom(ComInfoStruct *comStruct);
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
	MeterProtocol *m_meterProtocol;
	QByteArray m_meterTmp;
	QString m_portName;
	int m_protocolVersion; //热表协议类型

signals:
	void readMeterNoIsOK(const QString& portName, const QString& meterNo); //获取表号成功
	void readMeterFlowIsOK(const QString& portName, const QString& flow);  //获取表流量成功
	void readMeterHeatIsOK(const QString& portName, const QString& heat);  //获取表热量成功
	void readMeterTemperIsOK(const QString& portName, const QString& tempIn, const QString& tempOut);  //获取表进出口温度成功
	void readMeterDateIsOK(const QString& portName, const QString& date);  //获取表日期成功

public slots:
	bool openMeterCom(ComInfoStruct *comStruct);
	void closeMeterCom();
	void readMeterComBuffer(); //解析串口返回数据

	void askReadMeter();       //请求读表（广播地址读表）
	void askSetVerifyStatus(); //请求设置进入检定状态
	void askModifyMeterNo(QString oldMeterNo, QString newMeterNo);   //请求修改表号
	void askModifyFlowPara();  //请求修改流量参数

	void setProtocolVersion(int version);
};


#endif //COMOBJECT_H