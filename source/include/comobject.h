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


#define VALVE_OPEN		true	//���Ŵ�״̬
#define VALVE_CLOSE		false   //���Źر�״̬

#define REG_SUCCESS	 true	//���ڷ����ڳɹ�
#define REG_FAILED	 false  //���ڷ�����ʧ��

#define TIME_OUT	10		//��ʱ��TIME_OUT�Ǵ��ڶ�д����ʱ

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
** ������TempComObject
** ���ܣ��¶ȴ�����- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
*/
class COMOBJECT_EXPORT TempComObject : public ComObject
{
	Q_OBJECT  

public: 
	TempComObject(QObject* parent=0);
	~TempComObject();

	QextSerialPort *m_tempCom;      //�¶Ȳɼ�����
	Temp_Frame_Struct *m_tempFrame; //�¶Ȳɼ�ͨѶ֡�ṹ
	TempProtocol *m_tempProtocol;   //�¶Ȳɼ�ͨѶЭ�������
	QByteArray m_buf; //���ڻ���������
signals:
	void temperatureIsReady(const QString& tempStr); //�ɹ���ȡ�¶�ֵ

public slots:
	bool openTemperatureCom(ComInfoStruct *comStruct);
	void writeTemperatureComBuffer();
	void readTemperatureComBuffer();

};

/*
** ������ValveComObject
** ���ܣ����ſ��ƴ�����- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
*/
class COMOBJECT_EXPORT ControlComObject : public ComObject
{
	Q_OBJECT  

public: 
	ControlComObject(QObject* parent=0);
	~ControlComObject();

	QextSerialPort *m_controlCom;
	CtrlProtocol *m_controlProtocol;   //��λ������ͨѶЭ�������
	QByteArray m_conTmp;
	float m_balValue;
	int m_protocolVersion; //���ư�ͨѶЭ��汾

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
	void askSetDriverFreq(double freq);
	void askSetDriverFreq(float freq);
	void readControlComBuffer();
	void readNewControlComBuffer();

	void setProtocolVersion(int version);

};


/*
** ������BalanceComObject
** ���ܣ���ƽ������- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
*/
class COMOBJECT_EXPORT BalanceComObject : public ComObject
{
	Q_OBJECT  

public: 
	BalanceComObject(QObject* parent=0);
	~BalanceComObject();

	QextSerialPort *m_balanceCom;
	BalanceProtocol *m_balanceProtocol;   //��ƽͨѶЭ�������
	QTimer *m_balTimer; //��ʱ�� (��ѯ��ƽ����)

signals:
	void balanceValueIsReady(const float& balValue); //�ɹ���ȡ��ƽ��ֵ

public slots:
	bool openBalanceCom(ComInfoStruct *comStruct);
	void readBalanceComBuffer();

	void setBalanceType(int balType=BALANCE_TYPE_Satorius);
};

/*
** ������MeterComObject
** ���ܣ�����������- �򿪴��ڣ����ô��ڲ������رմ��ڣ�
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
	int m_protocolVersion; //�ȱ�Э������

signals:
	void readMeterNoIsOK(const QString& portName, const QString& meterNo); //��ȡ��ųɹ�
	void readMeterFlowIsOK(const QString& portName, const QString& flow);  //��ȡ�������ɹ�
	void readMeterHeatIsOK(const QString& portName, const QString& heat);  //��ȡ�������ɹ�
	void readMeterTemperIsOK(const QString& portName, const QString& tempIn, const QString& tempOut);  //��ȡ��������¶ȳɹ�
	void readMeterDateIsOK(const QString& portName, const QString& date);  //��ȡ�����ڳɹ�
	void readMeterBigCoeIsOK(const QString& portName, const QString& bigCoe); //��ȡ������ϵ���ɹ�
	void readMeterMid2CoeIsOK(const QString& portName, const QString& mid2Coe); //��ȡ����2����ϵ���ɹ�
	void readMeterMid1CoeIsOK(const QString& portName, const QString& mid1Coe); //��ȡ����1����ϵ���ɹ�
	void readMeterSmallCoeIsOK(const QString& portName, const QString& smallCoe); //��ȡС����ϵ���ɹ�
	void signalMeterCommunicateIsOK(const QString& portName); //��ͨѶ�ɹ�

public slots:
	bool openMeterCom(ComInfoStruct *comStruct);
	void closeMeterCom();
	void readMeterComBuffer(); //�������ڷ�������

	void askReadMeterNO();      //��������
	void askReadMeterFlowCoe(); //�����������ϵ��
	void askReadMeterData(int vType=VTYPE_FLOW);   //����������ݣ��㲥��ַ�������ݣ�
	void askSetVerifyStatus(int vType=VTYPE_FLOW); //�������ý���춨״̬
	void askExitVerifyStatus(int vType=VTYPE_FLOW);//�����˳�����춨״̬
	void askModifyMeterNO(QString oldMeterNo, QString newMeterNo);   //�����޸ı��(14λ���)
	void askModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr);  //�����޸�����ϵ��
	void askModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr, MeterCoe_PTR oldCoe);
	void askSetStandard(UINT8 std); //���ÿھ��������³������
	void askSetSystemTime(); //����ϵͳʱ�䣨�����³������
	void askSetAddress1(QString curAddr1, QString newAddr1); //����һ����ַ�������³������
	void askSetAddress2(QString curAddr1, QString newAddr2); //���ö�����ַ�������³������
	void askStartModifyCoe(); //�·�����������ʼ��������³������
	void askModifyMeterData(float flow, float heat, float cold); //�޸ı�����-��ʷ���ݣ������³������

	void setProtocolVersion(int version);
};

/*
** ������StdTempComObject
** ���ܣ�Sti1062a�¶ȴ�����-�򿪴���;���ô��ڲ������رմ��ڣ�
*/
class COMOBJECT_EXPORT StdTempComObject : public ComObject
{
	Q_OBJECT  

public: 
	StdTempComObject(QObject* parent=0);
	~StdTempComObject();

	QextSerialPort *m_tempCom;      //�¶Ȳɼ�����
	StdTempProtocol *m_stdTempProtocol;   //�¶Ȳɼ�ͨѶЭ�������
signals:
	void temperatureIsReady(const QString &tempStr); //�ɹ���ȡ��������ֵ

public slots:
	bool openTemperatureCom(ComInfoStruct *comStruct);
	void writeStdTempComBuffer(stdTempCommand);
	void readTemperatureComBuffer();
	void close();

	void setStdTempVersion(int version = TEMPERATURE_TYPE_HUAYI, int valueType = STD_TEMPER);
	void writeComByteM();
};

/*
** ������lcModRtuComObject
** ���ܣ�����ModRtuͨѶ������, ���ڶ�ȡ�����ӵ��
** ������������
*/

class COMOBJECT_EXPORT lcModRtuComObject : public ComObject
{
	Q_OBJECT  

public: 
	lcModRtuComObject(QObject* parent=0);
	~lcModRtuComObject();
	
signals:
	void lcModValueIsReady(const QByteArray &valueArray); //�ɹ���ȡ��������ֵ

public slots:
	bool openLcModCom(ComInfoStruct *comStruct);
	void writeLcModComBuffer(lcModSendCmd);
	void modify9150ACombuf(lcMod9150AWriteCmd);
	void ask9150A16RoutesCmd(uchar address);//ͬʱ����9510Aģ��16·ͨ������ֵ
	void ask901712RoutesCmd(uchar address);//ͬʱ����9017ģ��12·ͨ������ֵ
	void ask9150ARouteI(int i, uchar address);//�����i��ͨ������ֵ
	void ask9150ARouteL(UINT16 len, uchar address);
	void readLcModComBuffer();
	void close();
	void clearLcModAccum(uchar address, bool backward=false);//���9510Aģ��ͨ������ֵ
private:
	QextSerialPort *m_lcModCom;      //��������Ʋɼ�����
	lcModbusRTUProtocol *m_lcModProtocol;   //��������Ʋɼ�ͨѶЭ�������
};

#endif //COMOBJECT_H