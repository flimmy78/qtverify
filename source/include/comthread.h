#ifndef	COMTHREAD_H
#define COMTHREAD_H

#include <QtCore/QThread>  
#include <QtCore/QObject> 
#include <intsafe.h>

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
	UINT8 warn;	    //����״̬
	INT16 para;     //����д����ֵ
	UINT16 check;	//У����
}Temp_Frame_Struct;


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

#define TIME_OUT	10		//��ʱ��TIME_OUT�Ǵ��ڶ�д����ʱ

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