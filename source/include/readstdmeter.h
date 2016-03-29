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
	void slotClearAccum();//把力创模块的累计流量清零

signals:
	void signalReadInstReady(const flow_rate_wdg&, const float&);
	void signalReadAccumReady(const flow_rate_wdg&, const float&);
	void signalReadTolInstReady(const float&);
	void signalReadTolAccumReady(const float&);

private:
	/*-------------------------瞬时流量---------------------------------*/
	lcModRtuComObject *m_instantFlowCom;//瞬时流量串口对象
	ComThread m_instantFlowThread;//瞬时流量采集线程
	QTimer* m_instSTDMeterTimer;//瞬时流量计时器
	QByteArray m_instStdCurrent;//瞬时流量电流值, 需二次加工
	/*-------------------------瞬时流量end------------------------------*/

	/*-------------------------累积流量------------------------------------*/
	lcModRtuComObject *m_accumulateFlowCom;//累积流量串口对象
	ComThread m_accumFlowThread;//累积流量采集线程
	QTimer* m_accumSTDMeterTimer;//累积流量计时器
	QByteArray m_accumStdPulse;//16路累积流量脉冲值, 需二次加工
	/*-------------------------累积流量end-----------------------------------*/

	ReadComConfig *m_readComConfig;
	QSettings *m_stdParam;//读取标准表设置
	bool m_needAdjust;//是否需要修正标准表的累计流量
	QMap<flow_rate_wdg, int> m_accumCount;//记录当前脉冲值, 用于计算下一次采集时的脉冲增量, 以计算体积增量
	QMap<flow_rate_wdg, float> m_accumVol;//记录当前算出的体积值, 用于计算下一次采集时的体积增量
	QMap<flow_rate_wdg, QMap<float, float>> m_mapFlowK;//各流量点的流量-K系数表

	void initObj();
	void readFlowK();//读取各流量点的流量-K系数表
	void initInstStdCom();//瞬时流量串口初始化
	void initAccumStdCom();//累积流量串口初始化

	int getRouteByWdg(flow_rate_wdg, flow_type);//根据部件号读取标准表的通道号
	float getStdUpperFlow(flow_rate_wdg wdgIdx);//根据部件号读取相应标准表的上限流量值
	double getStdPulse(flow_rate_wdg wdgIdx);//根据部件号读取相应标准表的脉冲值

	float getInstFlowRate(flow_rate_wdg idx);
	float getAccumFLowVolume(flow_rate_wdg idx);

	float getKCoe(flow_rate_wdg idx);//计算当前流量点的K系数(线性插值)
	void getBound(flow_rate_wdg idx, float currentFlow, float& inf, float& sup);//根据当前流量, 查找其在表中的最小上限和最大下限
	float getInstStdMeterValue(float elecValue, float upperValue, flow_rate_wdg idx);//计算瞬时流量
private slots:
	void slotAskInstBytes();//请求瞬时流量
	void slotAskAccumBytes();//请求累积流量
	void slotGetInstStdMeterPulse(const QByteArray &);//瞬时流量槽函数
	void slotGetAccumStdMeterPulse(const QByteArray &);//累积流量槽函数
};
#endif//READSTDMETER_H