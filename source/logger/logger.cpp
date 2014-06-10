#include <QtCore/QDebug>
#include "logger.h"

CLogger::CLogger()
{

}

CLogger::~CLogger()
{

}

float CLogger::calc(float a, float b)
{
	float sum = a + b;
	qDebug("%.2f + %.2f = %.2f \n", a, b, sum);
	return sum;
}
