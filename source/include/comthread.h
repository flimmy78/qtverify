#ifndef	COMTHREAD_H
#define COMTHREAD_H

#include <QtCore/QThread>  
#include <QtCore/QObject> 

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

#define TIME_OUT	10		//延时，TIME_OUT是串口读写的延时

class ComObject : public QObject 
{       
	Q_OBJECT  

public: 
	ComObject();
	~ComObject();

	QextSerialPort *m_tempCom;

signals:
	void tempValueIsReady(const QString& tempStr);

public slots:
	void myslot();
	void openTemperatureCom();
	void readTemperatureComBuffer();
};    
/*
class TempComObject : public ComObject
{
	Q_OBJECT  

public: 
	TempComObject();
	~TempComObject();

	QextSerialPort *m_tempCom;

signals:
	void tempValueIsReady(const QString& tempStr);

public slots:
	void myslot();
	void openTemperatureCom();
	void readTemperatureComBuffer();
};*/

#endif //COMTHREAD_H