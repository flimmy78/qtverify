#ifndef	COMTHREAD_H
#define COMTHREAD_H

#include <QtCore/QThread>  
#include <QtCore/QObject> 
#include <intsafe.h>


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
	UINT8 warn;	    //报警状态
	INT16 para;     //所读写参数值
	UINT16 check;	//校验码
}Temp_Frame_Struct;
//温度采集协议 end

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

****************************************/
class TempComObject : public ComObject
{
	Q_OBJECT  

public: 
	TempComObject();
	~TempComObject();

	QextSerialPort *m_tempCom;
	Temp_Frame_Struct *m_tempFrame;

signals:
	void temperatureIsReady(const QString& tempStr);

public slots:
	void openTemperatureCom(ComInfoStruct *comStruct);
	void writeTemperatureComBuffer();
	void readTemperatureComBuffer();
	UINT16 CountCheck(Temp_Frame_Struct *pFrame);
	void analyseFrame();

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