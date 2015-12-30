#include <QThread>
#include "readstdmeter.h"

CStdMeterReader::CStdMeterReader(QObject* parent) : QObject(parent)
{
	m_instantFlowCom		= NULL;
	m_instSTDMeterTimer		= NULL;
	m_accumulateFlowCom		= NULL;
	m_accumSTDMeterTimer	= NULL;

	m_stdParam				= NULL;
	m_readComConfig			= NULL;

	initObj();
}

CStdMeterReader::~CStdMeterReader()
{
	RELEASE_TIMER(m_instSTDMeterTimer)
	EXIT_THREAD(m_instantFlowThread)
	RELEASE_PTR(m_instantFlowCom)

	RELEASE_TIMER(m_accumSTDMeterTimer)
	EXIT_THREAD(m_accumFlowThread)
	RELEASE_PTR(m_accumulateFlowCom)

	RELEASE_PTR(m_stdParam)
	RELEASE_PTR(m_readComConfig)
}

void CStdMeterReader::initObj()
{
	m_stdParam = new QSettings(getFullIniFileName("stdmtrparaset.ini"), QSettings::IniFormat);
	m_readComConfig = new ReadComConfig();

	m_accumCount[FLOW_RATE_BIG]   = 0;
	m_accumCount[FLOW_RATE_MID_2] = 0;
	m_accumCount[FLOW_RATE_MID_1] = 0;
	m_accumCount[FLOW_RATE_SMALL] = 0;

	m_accumVol[FLOW_RATE_BIG]   = 0.0;
	m_accumVol[FLOW_RATE_MID_2] = 0.0;
	m_accumVol[FLOW_RATE_MID_1] = 0.0;
	m_accumVol[FLOW_RATE_SMALL] = 0.0;
	readFlowK();
	initInstStdCom();
	initAccumStdCom();
}

void CStdMeterReader::readFlowK()
{
	QString flow;
	QString kcoe;
	m_stdParam->beginReadArray("BigFlowK");
	for (int i=0;i<FLOW_K_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		flow = m_stdParam->value("flowPoint").toString();
		kcoe = m_stdParam->value("KCoe").toString();
		//��������kϵ���ִ����ȶ�����0, �Ž�����ӵ�����-Kϵ����
		if (flow.length()*kcoe.length() > 0)
			m_mapFlowK[FLOW_RATE_BIG][flow.toFloat()] = kcoe.toFloat();
	}
	m_stdParam->endArray();

	m_stdParam->beginReadArray("Mid2FlowK");
	for (int i=0;i<FLOW_K_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		flow = m_stdParam->value("flowPoint").toString();
		kcoe = m_stdParam->value("KCoe").toString();
		if (flow.length()*kcoe.length() > 0)
			m_mapFlowK[FLOW_RATE_MID_2][flow.toFloat()] = kcoe.toFloat();
	}
	m_stdParam->endArray();

	m_stdParam->beginReadArray("Mid1FlowK");
	for (int i=0;i<FLOW_K_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		flow = m_stdParam->value("flowPoint").toString();
		kcoe = m_stdParam->value("KCoe").toString();
		if (flow.length()*kcoe.length() > 0)
			m_mapFlowK[FLOW_RATE_MID_1][flow.toFloat()] = kcoe.toFloat();
	}
	m_stdParam->endArray();

	m_stdParam->beginReadArray("SmallFlowK");
	for (int i=0;i<FLOW_K_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		flow = m_stdParam->value("flowPoint").toString();
		kcoe = m_stdParam->value("KCoe").toString();
		if (flow.length()*kcoe.length() > 0)
			m_mapFlowK[FLOW_RATE_SMALL][flow.toFloat()] = kcoe.toFloat();
	}
	m_stdParam->endArray();

	for (int i=FLOW_RATE_BIG; i<=FLOW_RATE_SMALL;i++)
	{
		qDebug() << m_mapFlowK[(flow_rate_wdg)i];
	}
}

void CStdMeterReader::initInstStdCom()
{
	ComInfoStruct InstStdCom = m_readComConfig->ReadInstStdConfig();
	m_instantFlowCom = new lcModRtuComObject();
	m_instantFlowCom->moveToThread(&m_instantFlowThread);

	m_instantFlowThread.start();
	qDebug() << "CStdMeterReader::initInstStdCom() running";
	m_instantFlowCom->openLcModCom(&InstStdCom);
	connect(m_instantFlowCom, SIGNAL(lcModValueIsReady(const QByteArray &)), this, SLOT(slotGetInstStdMeterPulse(const QByteArray &)));

	m_instSTDMeterTimer = new QTimer();
	connect(m_instSTDMeterTimer, SIGNAL(timeout()), this, SLOT(slotAskInstBytes()));
}

void CStdMeterReader::initAccumStdCom()
{
	ComInfoStruct AccumStdCom = m_readComConfig->ReadAccumStdConfig();
	m_accumulateFlowCom = new lcModRtuComObject();
	m_accumulateFlowCom->moveToThread(&m_accumFlowThread);
	m_accumFlowThread.start();
	m_accumulateFlowCom->openLcModCom(&AccumStdCom);
	connect(m_accumulateFlowCom, SIGNAL(lcModValueIsReady(const QByteArray &)), this, SLOT(slotGetAccumStdMeterPulse(const QByteArray &)));

	m_accumSTDMeterTimer = new QTimer();
	connect(m_accumSTDMeterTimer, SIGNAL(timeout()), this, SLOT(slotAskAccumBytes()));
}

void CStdMeterReader::startReadMeter()
{
	startReadInstMeter();
	startReadAccumMeter();
}

void CStdMeterReader::startReadInstMeter()
{
	if (m_instSTDMeterTimer)
		m_instSTDMeterTimer->start(TIMEOUT_STD_INST);
}

void CStdMeterReader::startReadAccumMeter()
{
	if (m_accumSTDMeterTimer)
		m_accumSTDMeterTimer->start(TIMEOUT_STD_ACCUM);
}

void CStdMeterReader::stopReadMeter()
{
	stopReadInstMeter();
	stopReadAccumMeter();
}

void CStdMeterReader::stopReadInstMeter()
{
	if (m_instSTDMeterTimer)
		m_instSTDMeterTimer->stop();
}

void CStdMeterReader::stopReadAccumMeter()
{
	if (m_accumSTDMeterTimer)
		m_accumSTDMeterTimer->stop();
}

void CStdMeterReader::slotAskInstBytes()
{
	bool ok;
	uchar address = (uchar)m_stdParam->value("DevNo./InstDevNo").toString().toInt(&ok, 16);
	m_instantFlowCom->ask901712RoutesCmd(address);
}

void CStdMeterReader::slotAskAccumBytes()
{
	bool ok;
	uchar address = (uchar)m_stdParam->value("DevNo./AccumDevNo").toString().toInt(&ok, 16);
	m_accumulateFlowCom->ask9150A16RoutesCmd(address);
}

void CStdMeterReader::slotGetInstStdMeterPulse(const QByteArray & valueArray)
{
	m_instStdCurrent = valueArray;
	float instValue = 0.0;//˲ʱ����	
	for (int i=FLOW_RATE_BIG; i<=FLOW_RATE_SMALL; i++)
		instValue += getInstFlowRate((flow_rate_wdg)i);
	emit signalReadTolInstReady(instValue);
}

void CStdMeterReader::slotGetAccumStdMeterPulse(const QByteArray & valueArray)
{
	m_accumStdPulse = valueArray;
	float accumValue = 0.0;//�ۻ�����
	for (int i=FLOW_RATE_BIG; i<=FLOW_RATE_SMALL; i++)
		accumValue += getAccumFLowVolume((flow_rate_wdg)i);
	emit signalReadTolAccumReady(accumValue);
}

int CStdMeterReader::getRouteByWdg(flow_rate_wdg wdgIdx, flow_type fType)
{
	int route = -1;
	m_stdParam->beginReadArray("Route");
	m_stdParam->setArrayIndex(wdgIdx);
	switch(fType)
	{
	case INST_FLOW_VALUE:
		route = m_stdParam->value("InstRoute").toInt();
		break;
	case ACCUM_FLOW_VALUE:
		route = m_stdParam->value("AccumRoute").toInt();
		break;
	default:
		break;
	}
	m_stdParam->endArray();
	return route;
}

float CStdMeterReader::getStdUpperFlow(flow_rate_wdg wdgIdx)
{
	float upperFlow = 0.0f;
	m_stdParam->beginReadArray("FlowRate");
	m_stdParam->setArrayIndex(wdgIdx);
	upperFlow = m_stdParam->value("UpperFlow").toFloat();
	m_stdParam->endArray();
	return upperFlow;
}

double CStdMeterReader::getStdPulse(flow_rate_wdg wdgIdx)
{
	double pulse = 0.0f;
	m_stdParam->beginReadArray("Pulse");
	m_stdParam->setArrayIndex(wdgIdx);
	pulse = m_stdParam->value("Pulse").toDouble();
	m_stdParam->endArray();
	return pulse;
}

float CStdMeterReader::getInstFlowRate(flow_rate_wdg idx)
{
	int route = getRouteByWdg(idx, INST_FLOW_VALUE);
	int count = get9017RouteI(route, m_instStdCurrent);
	float upperFlow = getStdUpperFlow(idx);
	//qDebug() <<"wdg_idx:--"<<idx<<" InstCurrent:--"<<count<<" upperFlow:--"<<upperFlow;
	float inst = getInstStdValue(count, upperFlow);
	emit signalReadInstReady(idx, inst);
	return inst;
}

/************************************************************************/
/* ÿһ�βɼ�����Ҫ����ɼ�����е���������, 
 * ���������������Ե�ǰ����(���ڲɼ�����ܶ�, �ѵ�ǰ���ٵ����ɼ�����ڵ�ƽ������)
 * �õ��������, �ټ�����ǰ�����, ��Ϊ����������ֵ
/************************************************************************/
float CStdMeterReader::getAccumFLowVolume(flow_rate_wdg idx)
{
	int route = getRouteByWdg(idx, ACCUM_FLOW_VALUE);
	int count = get9150ARouteI(route, m_accumStdPulse);
	int deltaCount = count - m_accumCount[idx];
	m_accumCount[idx] = count;
	double pulse = getStdPulse(idx);
	//qDebug() <<"wdg_idx:--"<<idx<<" AccumValue:--"<<count<<" pulse:--"<<pulse;
	float KCoe = getKCoe(idx);
	float deltaVol = deltaCount*pulse*KCoe;
	m_accumVol[idx] += deltaVol;
	emit signalReadAccumReady(idx, m_accumVol[idx]);
	return m_accumVol[idx];
}

void CStdMeterReader::slotClearLcMod()
{

}

float CStdMeterReader::getKCoe(flow_rate_wdg idx)
{
	float currentFlow = getInstFlowRate(idx);
	QList<float> keyList = m_mapFlowK[idx].keys();
	if (keyList.count() == 0)
	{
		return 1;//����-K��Ϊ��ʱ, ������
	}
	if (currentFlow < keyList.at(0))
	{//QMap��ȡ��ֵ��ʱ, �Զ��Լ���������, ���Կ���ֱ��ʹ������Сֵ
		return 1;//��ǰ����������-K�����С����Сʱ, ������
	}
	int length = keyList.length();
	if (currentFlow > keyList.at(length-1))
	{
		return 1;//��ǰ����������-K������������ʱ, ������
	}
	float inf;
	float sup;
	getBound(idx, currentFlow, inf, sup);
	float infK = m_mapFlowK[idx][inf];
	float supK = m_mapFlowK[idx][sup];
	float KCoe =  infK + (supK - infK)*(currentFlow-infK)/(sup-inf);
	return KCoe;
}

void CStdMeterReader::getBound(flow_rate_wdg idx, float currentFlow, float& inf, float& sup)
{
	QList<float> keyList = m_mapFlowK[idx].keys();
	//˳����Ҽ��б�, ���ص�һ�γ��ֵı�currentFlow��ļ�����ǰ����
	for (int i=0; i<keyList.count(); i++)
	{
		if (currentFlow<keyList.at(i+1))
		{
			inf = keyList.at(i);
			sup = keyList.at(i+1);
		}
	}
}