#ifndef READSTDMETER_H
#define READSTDMETER_H

#ifdef READSTDMETER_DLL
#  ifdef WIN32
#  define READSTDMETER_EXPORT __declspec(dllexport)
#  else
#  define READSTDMETER_EXPORT
#  endif
#else
#  ifdef WIN32
#  define READSTDMETER_EXPORT __declspec(dllimport)
#  else
#  define READSTDMETER_EXPORT
#  endif
#endif

#include <QtCore/QThread>  
#include <QtCore/QObject> 
#include <QtCore/QTimer>
#include <QSettings>
#include <QMap>
#include <QLCDNumber>

#include "algorithm.h"
#include "comobject.h"
#include "readcomconfig.h"

#define RELEASE_PTR(ptr)		if (ptr != NULL)\
								{\
									delete ptr;\
									ptr = NULL;\
								}

#define RELEASE_TIMER(timerptr)		if (timerptr != NULL)\
									{\
										if (timerptr->isActive())\
										{\
											timerptr->stop();\
										}\
										delete timerptr;\
										timerptr = NULL;\
									}

#define EXIT_THREAD(th)		if (th.isRunning())\
							{\
								th.exit();\
							}

class READSTDMETER_EXPORT CStdMeterReader : public QObject
{
	Q_OBJECT

public:
	CStdMeterReader(QObject* parent=0);
	~CStdMeterReader();

	void mapInstWdg(QMap<flow_rate_wdg, QLCDNumber *>*, QLCDNumber*, bool onlyDispTotal=false);
	void mapAccumWdg(QMap<flow_rate_wdg, QLCDNumber *>*, QLCDNumber*, bool onlyDispTotal=false);
	void startReadMeter();
	void startReadInstMeter();
	void startReadAccumMeter();
	void stopReadMeter();
	void stopReadInstMeter();
	void stopReadAccumMeter();
private:
	/*-------------------------˲ʱ����---------------------------------*/
	lcModRtuComObject *m_instantFlowCom;//˲ʱ�������ڶ���
	ComThread m_instantFlowThread;//˲ʱ�����ɼ��߳�
	QTimer* m_instSTDMeterTimer;//˲ʱ������ʱ��
	QByteArray m_instStdCurrent;//˲ʱ��������ֵ, ����μӹ�
	QLCDNumber* m_totalInstLcd;
	QMap<flow_rate_wdg, QLCDNumber *> *m_mapInstWdg;
	/*-------------------------˲ʱ����end------------------------------*/

	/*-------------------------�ۻ�����------------------------------------*/
	lcModRtuComObject *m_accumulateFlowCom;//�ۻ��������ڶ���
	ComThread m_accumFlowThread;//�ۻ������ɼ��߳�
	QTimer* m_accumSTDMeterTimer;//�ۻ�������ʱ��
	QByteArray m_accumStdPulse;//16·�ۻ���������ֵ, ����μӹ�
	QLCDNumber* m_totalAccumLcd;
	QMap<flow_rate_wdg, QLCDNumber *>* m_mapAccumWdg;
	/*-------------------------�ۻ�����end-----------------------------------*/

	ReadComConfig *m_readComConfig;
	QSettings *m_stdParam;//��ȡ��׼������
	bool m_InstOnlyDispTotal;//�Ƿ�ֻ����ʾ�����ټ���
	bool m_AccumOnlyDispTotal;//�Ƿ�ֻ����ʾ����������

	void initObj();
	void initInstStdCom();//˲ʱ�������ڳ�ʼ��
	void initAccumStdCom();//�ۻ��������ڳ�ʼ��

	int getRouteByWdg(flow_rate_wdg, flow_type);//���ݲ����Ŷ�ȡ��׼���ͨ����
	float getStdUpperFlow(flow_rate_wdg wdgIdx);//���ݲ����Ŷ�ȡ��Ӧ��׼�����������ֵ
	double getStdPulse(flow_rate_wdg wdgIdx);//���ݲ����Ŷ�ȡ��Ӧ��׼�������ֵ

	void freshInstStdMeter();//ˢ��˲ʱ����
	void freshAccumStdMeter();//ˢ���ۻ�����

	float getInstFlowRate(flow_rate_wdg idx);
	float getAccumFLowVolume(flow_rate_wdg idx);
private slots:
	void slotAskInstBytes();//����˲ʱ����
	void slotAskAccumBytes();//�����ۻ�����
	void slotGetInstStdMeterPulse(const QByteArray &);//˲ʱ�����ۺ���
	void slotGetAccumStdMeterPulse(const QByteArray &);//�ۻ������ۺ���
};
#endif//READSTDMETER_H