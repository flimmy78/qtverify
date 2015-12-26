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
	/*-------------------------瞬时流量---------------------------------*/
	lcModRtuComObject *m_instantFlowCom;//瞬时流量串口对象
	ComThread m_instantFlowThread;//瞬时流量采集线程
	QTimer* m_instSTDMeterTimer;//瞬时流量计时器
	QByteArray m_instStdCurrent;//瞬时流量电流值, 需二次加工
	QLCDNumber* m_totalInstLcd;
	QMap<flow_rate_wdg, QLCDNumber *> *m_mapInstWdg;
	/*-------------------------瞬时流量end------------------------------*/

	/*-------------------------累积流量------------------------------------*/
	lcModRtuComObject *m_accumulateFlowCom;//累积流量串口对象
	ComThread m_accumFlowThread;//累积流量采集线程
	QTimer* m_accumSTDMeterTimer;//累积流量计时器
	QByteArray m_accumStdPulse;//16路累积流量脉冲值, 需二次加工
	QLCDNumber* m_totalAccumLcd;
	QMap<flow_rate_wdg, QLCDNumber *>* m_mapAccumWdg;
	/*-------------------------累积流量end-----------------------------------*/

	ReadComConfig *m_readComConfig;
	QSettings *m_stdParam;//读取标准表设置
	bool m_InstOnlyDispTotal;//是否只需显示总流速即可
	bool m_AccumOnlyDispTotal;//是否只需显示总流量即可

	void initObj();
	void initInstStdCom();//瞬时流量串口初始化
	void initAccumStdCom();//累积流量串口初始化

	int getRouteByWdg(flow_rate_wdg, flow_type);//根据部件号读取标准表的通道号
	float getStdUpperFlow(flow_rate_wdg wdgIdx);//根据部件号读取相应标准表的上限流量值
	double getStdPulse(flow_rate_wdg wdgIdx);//根据部件号读取相应标准表的脉冲值

	void freshInstStdMeter();//刷新瞬时读数
	void freshAccumStdMeter();//刷新累积读数

	float getInstFlowRate(flow_rate_wdg idx);
	float getAccumFLowVolume(flow_rate_wdg idx);
private slots:
	void slotAskInstBytes();//请求瞬时流量
	void slotAskAccumBytes();//请求累积流量
	void slotGetInstStdMeterPulse(const QByteArray &);//瞬时流量槽函数
	void slotGetAccumStdMeterPulse(const QByteArray &);//累积流量槽函数
};
#endif//READSTDMETER_H