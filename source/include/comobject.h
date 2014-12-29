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
#include "comsetdlg_global.h"


#define VALVE_OPEN		true	//���Ŵ�״̬
#define VALVE_CLOSE		false   //���Źر�״̬

#define REG_SUCCESS	 true	//���ڷ����ڳɹ�
#define REG_FAILED	 false  //���ڷ�����ʧ��


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
	Ctrl_Frame_Struct *m_conFrame;
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
	QByteArray m_balTmp;

signals:
	void balanceValueIsReady(const QString& tempStr); //�ɹ���ȡ��ƽ��ֵ

public slots:
	void openBalanceCom(ComInfoStruct *comStruct);
	void readBalanceComBuffer();
};

/***************************************
������MeterComObject
���ܣ�����������- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
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
	int m_manufact; //�ȱ���������

signals:
	void readMeterNoIsOK(const QString& portName, const QString& meterNo);
	void readMeterDataIsOK(const QString& portName, const QString& flow, const QString& heat);

public slots:
	void openMeterCom(ComInfoStruct *comStruct);
	void readMeterComBuffer(); //�������ڷ�������

	void askReadMeter();       //��������㲥��ַ����
	void askSetVerifyStatus(); //�������ý���춨״̬
	void askModifyMeterNo(QString oldMeterNo, QString newMeterNo);   //�����޸ı��
	void askModifyFlowPara();  //�����޸���������

	void setManufact(int manufact);
};


#endif //COMOBJECT_H