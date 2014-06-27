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
	info->pumpNo = settings.value("Relay/pumpNo").toInt();

	info->regflow1No = settings.value("Regulate/regflow1No").toInt();
	info->regflow2No = settings.value("Regulate/regflow2No").toInt();
	info->regflow3No = settings.value("Regulate/regflow3No").toInt();
	info->regflow4No = settings.value("Regulate/regflow4No").toInt();

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
	settings.setIniCodec("GBK");
	strcpy(info->meterstandard, settings.value("paraset/standard").toString().toLocal8Bit());
	strcpy(info->metertype, settings.value("paraset/metertype").toString().toLocal8Bit());

	return true;
}

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
