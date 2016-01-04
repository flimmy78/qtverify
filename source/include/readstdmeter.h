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

	void startReadMeter();
	void startReadInstMeter();
	void startReadAccumMeter();
	void stopReadMeter();
	void stopReadInstMeter();
	void stopReadAccumMeter();
	void setAdjust(bool needAdjust=true);
public slots:
	void slotClearAccum();//������ģ����ۼ���������

signals:
	void signalReadInstReady(const flow_rate_wdg&, const float&);
	void signalReadAccumReady(const flow_rate_wdg&, const float&);
	void signalReadTolInstReady(const float&);
	void signalReadTolAccumReady(const float&);

private:
	/*-------------------------˲ʱ����---------------------------------*/
	lcModRtuComObject *m_instantFlowCom;//˲ʱ�������ڶ���
	ComThread m_instantFlowThread;//˲ʱ�����ɼ��߳�
	QTimer* m_instSTDMeterTimer;//˲ʱ������ʱ��
	QByteArray m_instStdCurrent;//˲ʱ��������ֵ, ����μӹ�
	/*-------------------------˲ʱ����end------------------------------*/

	/*-------------------------�ۻ�����------------------------------------*/
	lcModRtuComObject *m_accumulateFlowCom;//�ۻ��������ڶ���
	ComThread m_accumFlowThread;//�ۻ������ɼ��߳�
	QTimer* m_accumSTDMeterTimer;//�ۻ�������ʱ��
	QByteArray m_accumStdPulse;//16·�ۻ���������ֵ, ����μӹ�
	/*-------------------------�ۻ�����end-----------------------------------*/

	ReadComConfig *m_readComConfig;
	QSettings *m_stdParam;//��ȡ��׼������
	bool m_needAdjust;//�Ƿ���Ҫ������׼����ۼ�����
	QMap<flow_rate_wdg, int> m_accumCount;//��¼��ǰ����ֵ, ���ڼ�����һ�βɼ�ʱ����������, �Լ����������
	QMap<flow_rate_wdg, float> m_accumVol;//��¼��ǰ��������ֵ, ���ڼ�����һ�βɼ�ʱ���������
	QMap<flow_rate_wdg, QMap<float, float>> m_mapFlowK;//�������������-Kϵ����

	void initObj();
	void readFlowK();//��ȡ�������������-Kϵ����
	void initInstStdCom();//˲ʱ�������ڳ�ʼ��
	void initAccumStdCom();//�ۻ��������ڳ�ʼ��

	int getRouteByWdg(flow_rate_wdg, flow_type);//���ݲ����Ŷ�ȡ��׼���ͨ����
	float getStdUpperFlow(flow_rate_wdg wdgIdx);//���ݲ����Ŷ�ȡ��Ӧ��׼�����������ֵ
	double getStdPulse(flow_rate_wdg wdgIdx);//���ݲ����Ŷ�ȡ��Ӧ��׼�������ֵ

	float getInstFlowRate(flow_rate_wdg idx);
	float getAccumFLowVolume(flow_rate_wdg idx);

	float getKCoe(flow_rate_wdg idx);//���㵱ǰ�������Kϵ��(���в�ֵ)
	void getBound(flow_rate_wdg idx, float currentFlow, float& inf, float& sup);//���ݵ�ǰ����, �������ڱ��е���С���޺��������

private slots:
	void slotAskInstBytes();//����˲ʱ����
	void slotAskAccumBytes();//�����ۻ�����
	void slotGetInstStdMeterPulse(const QByteArray &);//˲ʱ�����ۺ���
	void slotGetAccumStdMeterPulse(const QByteArray &);//�ۻ������ۺ���
};
#endif//READSTDMETER_H