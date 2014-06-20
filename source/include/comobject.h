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
#include "qualitydlg_global.h"

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

signals:
	void controlComIsAnalysed(const bool& status);

public slots:
	void openControlCom(ComInfoStruct *comStruct);
	void writeControlComBuffer(int portno, bool status);
	void readControlComBuffer();
	void analyseFrame();
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
	bool m_sendContinue; //只为测试用

signals:
	void balanceValueIsReady(const QString& tempStr); //成功获取天平数值

public slots:
	void openBalanceCom(ComInfoStruct *comStruct);
	void readBalanceComBuffer();
	void writeBalanceComBuffer();
	void setSendContinue(bool a);
};


#endif //COMOBJECT_H