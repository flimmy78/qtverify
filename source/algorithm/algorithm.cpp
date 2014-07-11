#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include "algorithm.h"

int getPortSetIni(PORTSET_INI_PTR info)
{
	char filename[255];
	char* runhome = getenv( "RUNHOME" );
#ifdef __unix
	sprintf( filename, "%s/ini/portset.ini", runhome );
#else
	sprintf( filename, "%s\\ini\\portset.ini", runhome );
#endif

	QSettings settings(filename, QSettings::IniFormat);

	info->waterInNo = settings.value("Relay/waterInNo").toInt();
	info->bigNo = settings.value("Relay/bigNo").toInt();
	info->middle1No = settings.value("Relay/middle1No").toInt();
	info->middle2No = settings.value("Relay/middle2No").toInt();
	info->smallNo = settings.value("Relay/smallNo").toInt();
	info->waterOutNo = settings.value("Relay/waterOutNo").toInt();
	
	info->regflow1No = settings.value("Regulate/regflow1No").toInt();
	info->regflow2No = settings.value("Regulate/regflow2No").toInt();
	info->regflow3No = settings.value("Regulate/regflow3No").toInt();
	info->pumpNo = settings.value("Regulate/pumpNo").toInt();

	return true;
}

int getParaSetIni(PARASET_INI_PTR info)
{
	char filename[255];
	char* runhome = getenv( "RUNHOME" );
#ifdef __unix
	sprintf( filename, "%s/ini/qualityParaSet.ini", runhome );
#else
	sprintf( filename, "%s\\ini\\qualityParaSet.ini", runhome );
#endif

	QSettings settings(filename, QSettings::IniFormat);
	settings.setIniCodec("GB2312"); //解决ini文件读中文乱码
	strcpy(info->meterstandard, settings.value("paraset/standard").toString().toAscii());
	strcpy(info->metertype, settings.value("paraset/collectCode").toString().toAscii());

	return true;
}

int getMasterSlaveIni(MASTERSLAVE_INI_PTR info)
{
	char filename[255];
	char* runhome = getenv( "RUNHOME" );
#ifdef __unix
	sprintf( filename, "%s/ini/masterslaveset.ini", runhome );
#else
	sprintf( filename, "%s\\ini\\masterslaveset.ini", runhome );
#endif

	QSettings settings(filename, QSettings::IniFormat);

	info->netmode = settings.value("localhost/netmode").toInt();
	info->hostflag = settings.value("localhost/hostflag").toInt();
	strcpy(info->mastername, settings.value("master/hostname").toString().toAscii());
	strcpy(info->masterIP, settings.value("master/ip").toString().toAscii());
	strcpy(info->slave1name, settings.value("slave1/hostname").toString().toAscii());
	strcpy(info->slave1IP, settings.value("slave1/ip").toString().toAscii());
	strcpy(info->slave2name, settings.value("slave2/hostname").toString().toAscii());
	strcpy(info->slave2IP, settings.value("slave2/ip").toString().toAscii());
	strcpy(info->slave3name, settings.value("slave3/hostname").toString().toAscii());
	strcpy(info->slave3IP, settings.value("slave3/ip").toString().toAscii());
	strcpy(info->slave4name, settings.value("slave4/hostname").toString().toAscii());
	strcpy(info->slave4IP, settings.value("slave4/ip").toString().toAscii());

	return true;
}


/**********************************************************
***********************************************************/
CAlgorithm::CAlgorithm()
{

}

CAlgorithm::~CAlgorithm()
{

}

float CAlgorithm::calc(float a, float b)
{
	float sum = a + b;
	qDebug("%.2f + %.2f = %.2f \n", a, b, sum);
	return sum;
}
