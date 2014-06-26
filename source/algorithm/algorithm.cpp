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

	info->waterInNo = settings.value("Relay/waterIn").toInt();
	info->flow1No = settings.value("Relay/flow1").toInt();
	info->flow2No = settings.value("Relay/flow2").toInt();
	info->flow3No = settings.value("Relay/flow3").toInt();
	info->flow4No = settings.value("Relay/flow4").toInt();
	info->waterOutNo = settings.value("Relay/waterOut").toInt();

	info->regflow1No = settings.value("Regulate/regFlow1").toInt();
	info->regflow2No = settings.value("Regulate/regFlow2").toInt();
	info->regflow3No = settings.value("Regulate/regFlow3").toInt();
	info->regflow4No = settings.value("Regulate/regFlow4").toInt();

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
