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
#include "qextserialport.h"


#define VALVE_OPEN		true	//阀门打开状态
#define VALVE_CLOSE		false   //阀门关闭状态

#define REG_SUCCESS	 true	//调节阀调节成功
#define REG_FAILED	 false  //调节阀调节失败

#define TIME_OUT	10		//延时，TIME_OUT是串口读写的延时

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


class COMOBJECT_EXPORT ComObject : public QObject 
{       
	Q_OBJECT  

public: 
	ComObject(QObject* parent=0);
	~ComObject();


signals:

public slots:

};    

/*
** 类名：TempComObject
** 功能：温度串口类- 打开串口；设置串口参数；关闭串口；
*/
class COMOBJECT_EXPORT TempComObject : public ComObject
{
	Q_OBJECT  

public: 
	TempComObject(QObject* parent=0);
	~TempComObject();

	QextSerialPort *m_tempCom;      //温度采集串口
	Temp_Frame_Struct *m_tempFrame; //温度采集通讯帧结构
	TempProtocol *m_tempProtocol;   //温度采集通讯协议类对象
	QByteArray m_buf; //串口缓冲区数据
signals:
	void temperatureIsReady(const QString& tempStr); //成功获取温度值

public slots:
	bool openTemperatureCom(ComInfoStruct *comStruct);
	void writeTemperatureComBuffer();
	void readTemperatureComBuffer();

};

/*
** 类名：ValveComObject
** 功能：阀门控制串口类- 打开串口；设置串口参数；关闭串口；
*/
class COMOBJECT_EXPORT ControlComObject : public ComObject
{
	Q_OBJECT  

public: 
	ControlComObject(QObject* parent=0);
	~ControlComObject();

	QextSerialPort *m_controlCom;
	CtrlProtocol *m_controlProtocol;   //下位机控制通讯协议类对象
	QByteArray m_conTmp;
	float m_balValue;
	int m_protocolVersion; //控制板通讯协议版本

	NewCtrl_Frame_Struct *m_conFrame;

signals:
	void controlRelayIsOk(const UINT8 &portno, const bool &status);
	void controlRegulateIsOk();
	void controlGetBalanceValueIsOk(const float& balValue);

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


/*
** 类名：BalanceComObject
** 功能：天平串口类- 打开串口；设置串口参数；关闭串口；
*/
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
	void balanceValueIsReady(const float& balValue); //成功获取天平数值

public slots:
	bool openBalanceCom(ComInfoStruct *comStruct);
	void readBalanceComBuffer();
};

/*
** 类名：MeterComObject
** 功能：热量表串口类- 打开串口；设置串口参数；关闭串口；
*/
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
	void readMeterFlowIsOK(const QString& portName, const float& flow);  //获取表流量成功
	void readMeterHeatIsOK(const QString& portName, const QString& heat);  //获取表热量成功
	void readMeterTemperIsOK(const QString& portName, const QString& tempIn, const QString& tempOut);  //获取表进出口温度成功
	void readMeterDateIsOK(const QString& portName, const QString& date);  //获取表日期成功
	void readMeterBigCoeIsOK(const QString& portName, const QString& bigCoe); //获取大流量系数成功
	void readMeterMid2CoeIsOK(const QString& portName, const QString& mid2Coe); //获取中流2流量系数成功
	void readMeterMid1CoeIsOK(const QString& portName, const QString& mid1Coe); //获取中流1流量系数成功
	void readMeterSmallCoeIsOK(const QString& portName, const QString& smallCoe); //获取小流量系数成功

public slots:
	bool openMeterCom(ComInfoStruct *comStruct);
	void closeMeterCom();
	void readMeterComBuffer(); //解析串口返回数据

	void askReadMeter();       //请求读表（广播地址读表）
	void askSetVerifyStatus(); //请求设置进入检定状态
	void askModifyMeterNO(QString oldMeterNo, QString newMeterNo);   //请求修改表号
	void askModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr);  //请求修改流量系数

	void setProtocolVersion(int version);
};

/*
** 类名：Sti1062aComObject
** 功能：Sti1062a温度串口类-打开串口;设置串口参数；关闭串口；
*/
class COMOBJECT_EXPORT Sti1062aComObject : public ComObject
{
	Q_OBJECT  

public: 
	Sti1062aComObject(QObject* parent=0);
	~Sti1062aComObject();

	QextSerialPort *m_tempCom;      //温度采集串口
	sti1062ATempProtocol *m_sti1062aProtocol;   //温度采集通讯协议类对象
signals:
	void temperatureIsReady(const QString &tempStr); //成功获取仪器返回值

	public slots:
		bool openTemperatureCom(ComInfoStruct *comStruct);
		void writeTemperatureComBuffer(sti1062Acommand);
		void readTemperatureComBuffer();
		void close();
};
#endif //COMOBJECT_H