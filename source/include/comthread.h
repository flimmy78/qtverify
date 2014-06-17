#ifndef	COMTHREAD_H
#define COMTHREAD_H

#include <QtCore/QThread>  
#include <QtCore/QObject> 

#include "protocol.h"

class ComThread : public QThread 
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

class ComObject : public QObject 
{       
	Q_OBJECT  

public: 
	ComObject();
	~ComObject();


signals:

public slots:

};    

/***************************************
类名：TempComObject
功能：温度串口类- 打开串口；设置串口参数；关闭串口；
****************************************/
class TempComObject : public ComObject
{
	Q_OBJECT  

public: 
	TempComObject();
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

****************************************/
class ValveComObject : public ComObject
{
	Q_OBJECT  

public: 
	ValveComObject();
	~ValveComObject();

	QextSerialPort *m_valveCom;

signals:
	void valveComIsAnalysed(const int& isOpen);

public slots:
	void openValveControlCom(ComInfoStruct *comStruct);
	void writeValveControlComBuffer();
	void readValveControlComBuffer();
	void analyseFrame();
};

#endif //COMTHREAD_H