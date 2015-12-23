#include "readstdmeter.h"

CStdMeterReader::CStdMeterReader()
{
	m_instantFlowCom		= NULL;
	m_instSTDMeterTimer		= NULL;
	m_totalInstLcd			= NULL;
	m_mapInstWdg			= NULL;

	m_accumulateFlowCom		= NULL;
	m_accumSTDMeterTimer	= NULL;
	m_totalAccumLcd			= NULL;
	m_mapAccumWdg			= NULL;

	m_stdParam				= NULL;
	m_readComConfig			= NULL;

	initObj();
}

CStdMeterReader::~CStdMeterReader()
{
	m_totalInstLcd			= NULL;
	m_mapInstWdg			= NULL;
	m_totalAccumLcd			= NULL;
	m_mapAccumWdg			= NULL;

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
	m_readComConfig = new ReadComConfig;
}

void CStdMeterReader::initInstStdCom()
{
	ComInfoStruct InstStdCom = m_readComConfig->ReadInstStdConfig();
	m_instantFlowCom = new lcModRtuComObject();
	m_instantFlowCom->moveToThread(&m_instantFlowThread);
	m_instantFlowThread.start();
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

void CStdMeterReader::mapInstWdg(QMap<flow_rate_wdg, QLCDNumber *> *mapWdg, QLCDNumber *totalInstWdg, bool onlyDispTotal)
{
	m_mapInstWdg = mapWdg;
	m_totalInstLcd = totalInstWdg;
	m_InstOnlyDispTotal = onlyDispTotal;
	initInstStdCom();
}

void CStdMeterReader::mapAccumWdg(QMap<flow_rate_wdg, QLCDNumber *> *mapWdg, QLCDNumber *totalAccumWdg, bool onlyDispTotal)
{
	m_mapAccumWdg = mapWdg;
	m_totalAccumLcd = totalAccumWdg;
	m_AccumOnlyDispTotal = onlyDispTotal;
	initAccumStdCom();
}

void CStdMeterReader::startReadMeter()
{
	startReadInstMeter();
	startReadAccumMeter();
}

void CStdMeterReader::startReadInstMeter()
{
	if (m_instSTDMeterTimer)
	{
		m_instSTDMeterTimer->start(TIMEOUT_STD_INST);
	}
}

void CStdMeterReader::startReadAccumMeter()
{
	if (m_accumSTDMeterTimer)
	{
		m_accumSTDMeterTimer->start(TIMEOUT_STD_ACCUM);
	}
}

void CStdMeterReader::stopReadMeter()
{
	stopReadInstMeter();
	stopReadAccumMeter();
}

void CStdMeterReader::stopReadInstMeter()
{
	if (m_instSTDMeterTimer)
	{
		m_instSTDMeterTimer->stop();
	}
}

void CStdMeterReader::stopReadAccumMeter()
{
	if (m_accumSTDMeterTimer)
	{
		m_accumSTDMeterTimer->stop();
	}
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
	float instValue = 0.0;//瞬时流量	

	if (!m_InstOnlyDispTotal)
		freshInstStdMeter();

	for (int i=FLOW_RATE_BIG; i<=FLOW_RATE_SMALL; i++)
		instValue += getInstFlowRate((flow_rate_wdg)i);

	m_totalInstLcd->display(instValue);
}

void CStdMeterReader::slotGetAccumStdMeterPulse(const QByteArray & valueArray)
{
	m_accumStdPulse = valueArray;
	float accumValue = 0.0;//累积流量

	if (!m_AccumOnlyDispTotal)
		freshAccumStdMeter();
		
	for (int i=FLOW_RATE_BIG; i<=FLOW_RATE_SMALL; i++)
		accumValue += getAccumFLowVolume((flow_rate_wdg)i);

	m_totalAccumLcd->display(accumValue);	
}

void CStdMeterReader::freshInstStdMeter()
{
	for (int i=FLOW_RATE_BIG; i<=FLOW_RATE_SMALL; i++)
	{
		if (m_mapInstWdg->keys().contains((flow_rate_wdg)i))
		{
			m_mapInstWdg->value((flow_rate_wdg)i)->display(getInstFlowRate((flow_rate_wdg)i));
		}
	}
}

void CStdMeterReader::freshAccumStdMeter()
{
	for (int i=FLOW_RATE_BIG; i<=FLOW_RATE_SMALL; i++)
	{
		if (m_mapAccumWdg->keys().contains((flow_rate_wdg)i))
		{
			m_mapAccumWdg->value((flow_rate_wdg)i)->display(getAccumFLowVolume((flow_rate_wdg)i));
		}
	}
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
	return getInstStdValue(count, upperFlow);
}

float CStdMeterReader::getAccumFLowVolume(flow_rate_wdg idx)
{
	int route = getRouteByWdg(idx, ACCUM_FLOW_VALUE);
	int count = get9150ARouteI(route, m_accumStdPulse);
	double pulse = getStdPulse(idx);
	//qDebug() <<"wdg_idx:--"<<idx<<" AccumValue:--"<<count<<" pulse:--"<<pulse;
	return count*pulse;
}