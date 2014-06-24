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

#define TIME_OUT	10		//��ʱ��TIME_OUT�Ǵ��ڶ�д����ʱ

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
������TempComObject
���ܣ��¶ȴ�����- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
****************************************/
class COMOBJECT_EXPORT TempComObject : public ComObject
{
	Q_OBJECT  

public: 
	TempComObject(QObject* parent=0);
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
������ValveComObject
���ܣ����ſ��ƴ�����- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
****************************************/
class COMOBJECT_EXPORT ControlComObject : public ComObject
{
	Q_OBJECT  

public: 
	ControlComObject(QObject* parent=0);
	~ControlComObject();

	QextSerialPort *m_controlCom;
	ControlProtocol *m_controlProtocol;   //��λ������ͨѶЭ�������
	Con_Frame_Struct *m_conFrame;

signals:
	void controlRelayIsOk();
	void controlRegulateIsOk();

public slots:
	void openControlCom(ComInfoStruct *comStruct);
	void makeRelaySendBuf(UINT8 portno, bool status);
	void makeRegulateSendBuf(UINT8 portno, int degree);
	void makeQuerySendBuf();
	void readControlComBuffer();
	void analyseFrame();
};


/***************************************
������BalanceComObject
���ܣ���ƽ������- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
****************************************/
class COMOBJECT_EXPORT BalanceComObject : public ComObject
{
	Q_OBJECT  

public: 
	BalanceComObject(QObject* parent=0);
	~BalanceComObject();

	QextSerialPort *m_balanceCom;
	BalanceProtocol *m_balanceProtocol;   //��ƽͨѶЭ�������
	bool m_sendContinue; //ֻΪ������

signals:
	void balanceValueIsReady(const QString& tempStr); //�ɹ���ȡ��ƽ��ֵ

public slots:
	void openBalanceCom(ComInfoStruct *comStruct);
	void readBalanceComBuffer();
	void writeBalanceComBuffer();
	void setSendContinue(bool a);
};


#endif //COMOBJECT_H