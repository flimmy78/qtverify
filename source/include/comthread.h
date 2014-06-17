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
������TempComObject
���ܣ��¶ȴ�����- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
****************************************/
class TempComObject : public ComObject
{
	Q_OBJECT  

public: 
	TempComObject();
	~TempComObject();

	QextSerialPort *m_tempCom;      //�¶Ȳɼ�����
	Temp_Frame_Struct *m_tempFrame; //�¶Ȳɼ�ͨѶ֡�ṹ
	TempProtocol *m_tempProtocol;   //�¶Ȳɼ�ͨѶЭ�������

signals:
	void temperatureIsReady(const QString& tempStr); //�ɹ���ȡ�¶�ֵ

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