#include <QtCore/QDebug>
#include "alg.h"

CAlg::CAlg()
{

}

CAlg::~CAlg()
{

}

float CAlg::calc(float a, float b)
{
	float sum = a + b;
	qDebug("%.2f + %.2f = %.2f \n", a, b, sum);
	return sum;
}
