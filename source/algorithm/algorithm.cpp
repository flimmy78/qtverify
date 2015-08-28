/***********************************************
**  �ļ���:     algorithm.cpp
**  ����:       �춨�㷨����ȡ�����ļ���
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/26
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:		
**  ���¼�¼:   
***********************************************/

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtCore/QFile>
#include <QProcessEnvironment>
#include <QCoreApplication>
#include <QTime>
#include <qmath.h>

#include "algorithm.h"
#include "commondefine.h"
#include "qtexdb.h"

void wait(unsigned int msec)
{
	QTime n = QTime::currentTime();
	QTime now;
	do
	{
		now = QTime::currentTime();
	} while(n.msecsTo(now) <= msec); 
}
void sleep(unsigned int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while( QTime::currentTime() < dieTime )
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//��ȡ���ư�Ķ˿ں�������Ϣ
int getPortSetIni(PortSet_Ini_PTR info)
{
	QString filename = getFullIniFileName("portset.ini");
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

	info->version = settings.value("CtrlBoard/version").toInt();
	return true;
}

//��ȡ����-�ӻ�������Ϣ
int getMasterSlaveIni(MasterSlave_Ini_PTR info)
{
	QString filename = getFullIniFileName("masterslaveset.ini");
	QSettings settings(filename, QSettings::IniFormat);

	info->netmode = settings.value("localhost/netmode").toInt();
	info->hostflag = settings.value("localhost/hostflag").toInt();
	strcpy_s(info->mastername, settings.value("master/hostname").toString().toAscii());
	strcpy_s(info->masterIP, settings.value("master/ip").toString().toAscii());
	strcpy_s(info->slave1name, settings.value("slave1/hostname").toString().toAscii());
	strcpy_s(info->slave1IP, settings.value("slave1/ip").toString().toAscii());
	strcpy_s(info->slave2name, settings.value("slave2/hostname").toString().toAscii());
	strcpy_s(info->slave2IP, settings.value("slave2/ip").toString().toAscii());
	strcpy_s(info->slave3name, settings.value("slave3/hostname").toString().toAscii());
	strcpy_s(info->slave3IP, settings.value("slave3/ip").toString().toAscii());
	strcpy_s(info->slave4name, settings.value("slave4/hostname").toString().toAscii());
	strcpy_s(info->slave4IP, settings.value("slave4/ip").toString().toAscii());

	return true;
}

QString getFullIniFileName(QString filename)
{
	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
	if (adehome.isEmpty())
	{
		qWarning()<<"Get $(ADEHOME) Failed! Please set up this system variable.";
		return "";
	}
	QString fullname;
#ifdef __unix
	fullname = adehome + "\/ini\/" + filename;
#else
	fullname = adehome + "\\ini\\" + filename;
#endif
	return fullname;
}

//��ȡ���вɼ������Ӧ����������
QStringList getPickCodeStringList()
{
	QString filename = getFullIniFileName("pickcode.ini");
	QString str;
	QStringList strlist;
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream stream(&file);
		while (!stream.atEnd())
		{
			str = stream.readLine().simplified(); //ȥ����β�ո�
			if (str.isEmpty() || str.startsWith("#"))
			{
				continue;
			}
			strlist += str.section("=", 1);
		}
	}
	return strlist;
}

float detA(float a00, float a01, float a10, float a11)
{
	return a00*a11 - a01*a10;
}

/************************************************************************/
/* һ��ֻ�������¶�-��ֵ���ɼ�����˲�������¶�ϵ����0���¶�                 */
/************************************************************************/
plaParam_PTR getPlaParam(pla_T_R_PTR pla_p, int num)
{
	plaParam_PTR p_param;
	p_param = new plaParam_STR;
	float coe[2][3];//����ϵ��, coe[i,j]ǰ���ж�Ӧ�����Է�����ĵ�i�����̵�j��δ֪����ϵ��, �������ǳ�����
	coe[0][0] = detA(pla_p[0].resis, pla_p[0].tmp, pla_p[1].resis, pla_p[1].tmp);
	coe[0][1] = detA(pla_p[0].resis, pla_p[0].tmp*pla_p[0].tmp, pla_p[1].resis, pla_p[1].tmp*pla_p[1].tmp);
	coe[0][2] = pla_p[1].resis - pla_p[0].resis;
	coe[1][0] = detA(pla_p[0].resis, pla_p[0].tmp, pla_p[2].resis, pla_p[2].tmp);
	coe[1][1] = detA(pla_p[0].resis, pla_p[0].tmp*pla_p[0].tmp, pla_p[2].resis, pla_p[2].tmp*pla_p[2].tmp);
	coe[1][2] = pla_p[2].resis - pla_p[0].resis;

	float M;//����ķ����ϵ�����������ʽ��ֵ
	float A;//��һδ֪��a��ֵ
	float B;//�ڶ�δ֪��b��ֵ
	M = detA(coe[0][0], coe[0][1], coe[1][0], coe[1][1]);
	A = detA(coe[0][2], coe[0][1], coe[1][2], coe[1][1]);
	B = detA(coe[0][0], coe[0][2], coe[1][0], coe[1][2]);
	p_param->a = A/M;
	p_param->b = B/M;
	p_param->r0 = pla_p[0].resis/(1 + p_param->a*pla_p[0].tmp + p_param->b*pla_p[0].tmp*pla_p[0].tmp);
	p_param->c;//����cһ�㲻�����㣬ֻ��0�����²��õ�
	return p_param;
}

float getPlaRt(float r0, float a, float b, float tmp)
{
	return r0*(1+a*tmp+b*tmp*tmp);
}

float getPlaTr(float r0, float a, float b, float resis)
{
	if (b==0.0 && a != 0.0)
	{
		return (resis/r0 - 1)/a;
	}
	else if (b==0.0 && a == 0.0)
	{
		return -1;
	}

	float ret = (qSqrt(a*a + 4*b*(resis/r0 - 1)) - a)/(2*b);
	return ret;
}

float calcTemperByResis(float resis)
{
	QString filename = getFullIniFileName("stdplasensor.ini");
	QSettings settings(filename, QSettings::IniFormat);
	QString pt = settings.value("in_use/pt").toString();
	float rtp = settings.value(pt+"/in_rtp").toFloat();
	float a = settings.value(pt+"/in_a").toFloat();
	float b = settings.value(pt+"/in_b").toFloat();
	float temp = getPlaTr(rtp, a, b, resis);
	return temp;
}

float getDeltaTmpErr(float std_delta_t, float min_delta_t)
{
	return qAbs(0.5 + 3*min_delta_t/std_delta_t);
}

float getSingleTmpErr(float std_delta_t)
{
	return (0.3 + 0.005*qAbs(std_delta_t));
}

/************************************************************************/
/*����JJG-2001 Page4, ��1
/*grade, ��ĵȼ�, 1��, 2����
/*delta_t_min, �����С�²�
/*deta_t, ʵ�ʼ��ʱ���²�
/*dn_flow_rate, ��ĳ���(�)����, ������λ��flow_rate��ͬ
/*flow_rate, ʵ�ʼ��ʱ�������
/************************************************************************/
float getMeterGradeErrLmt(int grade, float delta_t_min, float delta_t, float dn_flow_rate, float flow_rate)
{
	float ret;
	float coe_a, coe_b, coe_c;
	switch(grade)
	{
		case GRADE_ONE:
			coe_a = 2.0f;
			coe_b = 4.0f;
			coe_c = 0.01f;
			break;
		case GRADE_TWO:
			coe_a = 3.0f;
			coe_b = 4.0f;
			coe_c = 0.02f;
			break;
		case GRADE_THREE:
			coe_a = 4.0f;
			coe_b = 4.0f;
			coe_c = 0.05f;
			break;
		default:
			break;
	}
	ret = qAbs(coe_a + coe_b*(delta_t_min/delta_t) + coe_c*(dn_flow_rate/flow_rate));
	return ret;
}

//����������ͨѶ���ص����ֽ����ݣ��������Ӧ�ĸ�������ֵ
float calcFloatValueOfCoe(QString coe)
{
	bool ok;
	float dec = coe.right(3).toInt(&ok, 16)/4096.0;
	float coeV = coe.left(1).toFloat() + dec; 

	return coeV;
}

//����������ͨѶ���ص����ֽ����ݣ��������Ӧ�����ֵ
float calcErrorValueOfCoe(QString coe)
{
	float coeV = calcFloatValueOfCoe(coe); 
	float errV = 100/coeV - 100;

	return errV;
}

/* ����ModBus-RTU����Э���CRCУ��ֵ
 * ref: http://www.ccontrolsys.com/w/How_to_Compute_the_Modbus_RTU_Message_CRC
 * ���ɶ���ʽΪ x^16+x^15+x^2+x^0, ��ϵ���ִ�Ϊ (1 1000 0000 0000 0101),
 * ����16���ݵ�ϵ����Ϊ (1000 0000 0000 0101, ��0x8005),
 * �ٷ���õ� (1010 0000 0000 0001, ��0xA001)
 * buf, ָ����Ϣͷ��ָ��;
 * len, ��Ϣ��ĳ���
 */
UINT16 calcModRtuCRC(uchar *buf, int len)
{
	UINT16 crc = 0xFFFF;

	for (int pos = 0; pos < len; pos++) {
		crc ^= (UINT16)buf[pos];          // XOR byte into least sig. byte of crc

		for (int i = 8; i > 0; i--) {    // Loop over each bit
			if ((crc & 0x0001) != 0) {      // If the LSB is set, that is the LSB is 1
				crc >>= 1;                  // Shift right, ignore LSB(LSB is the MSB before reverse)
				crc ^= POLY;				// and XOR 0xA001
			}
			else                            // Else LSB is not set, that is the LSB is 0
				crc >>= 1;                  // Just shift right, a XOR 0 = a, so not need to do XOR
		}
	}
	return crc;
}

/* ��CRC������ת��ΪQByteArray
 * ����ֵQByteArray sendbuf;
 * sendbuf.at(0) �ǵ�λ;  sendbuf.at(1) �Ǹ�λ
 * crc, ����õ���У��ֵ, ��λ��ǰ, ��λ�ں�
 */
QByteArray getCRCArray(UINT16 crc)
{
	QByteArray sendbuf;
	sendbuf.append((char)crc);//��λ
	sendbuf.append((char)(crc>>WORDLEN));//��λ
	return sendbuf;
}

int get9150ARouteI(int i, QByteArray valueArray)
{
	if(valueArray.length() < EDA9150A_ROUTE_BYTES)
		return -1;

	if ( (EDA9150A_ROUTE_BYTES*i) > valueArray.length())//i���ܳ�������ȡ��ͨ������
	{
		return -1;
	}

	QByteArray data;
	for (int k=0;k<EDA9150A_ROUTE_BYTES;k++)
		data.append(valueArray.at(EDA9150A_ROUTE_BYTES*i+k));

	int value = 0;	
	for (int k=0;k<EDA9150A_ROUTE_BYTES;k++)
	{
		value |= ( ((uchar)data.at(k)) << ((EDA9150A_ROUTE_BYTES-1-k)*WORDLEN) );
	}
	return value;
}

int get9017RouteI(int i, QByteArray valueArray)
{
	if(valueArray.length() < EDA9017_ROUTE_BYTES)
		return -1;

	if ( (EDA9017_ROUTE_BYTES*i) > valueArray.length())//i���ܳ�������ȡ��ͨ������
	{
		return -1;
	}

	QByteArray data;
	for (int k=0;k<EDA9017_ROUTE_BYTES;k++)
		data.append(valueArray.at(EDA9017_ROUTE_BYTES*i+k));

	int value = 0;	
	for (int k=0;k<EDA9017_ROUTE_BYTES;k++)
	{
		value |= ( ((uchar)data.at(k)) << ((EDA9017_ROUTE_BYTES-1-k)*WORDLEN) );
	}
	return value;
}

float getInstStdValue(float elecValue, float upperValue)
{
	if (ELEC_ZERO<=elecValue && elecValue <= ELEC_UPPER)
	{
		float deltaStd = ELEC_UPPER - ELEC_ZERO;
		float deltaCur = elecValue - ELEC_ZERO;
		return (deltaCur/deltaStd)*upperValue;
	}

	return 0.0f;	
}
/**********************************************************
������CAlgorithm
���ܣ��춨�㷨��
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

/*********************************************************************************************
* ����λ�ż������¶�(���������)                                      
* inlet: ��ˮ���¶�ֵ                                                              
* outlet: ��ˮ���¶�ֵ																						   
* num: ��λ��(��1��ʼ�����������), �Դ˼�����ȱ�����ڵľ���        
/********************************************************************************************/
float CAlgorithm::getMeterTempByPos(float inlet, float outlet, int num)
{
	//��ȡ�����Ĺ��
	QSettings *ParaSet = new QSettings(getFullIniFileName("verifyparaset.ini"), QSettings::IniFormat);//���������ļ�
	int standard = ParaSet->value("head/standard").toInt();//�������
    int totalCount = getMaxMeterByIdx(standard); //�ù���ȱ��Ӧ�����������
	float delta = (inlet - outlet)/(totalCount + 2); //˫��·��ƣ��������ǰ�����䴦�����ں����һ��������
	float temper = inlet - (num + (int)(2*(num-1)/totalCount))*delta;
	return temper;
}

/************************************************************************
* ����ˮ��-�ܶȱ�(JGG 225-2010 ������춨���)
* ���ж���ʽ���(MATLAB, 9�η�)
* float temp: �¶�ֵ ( 1 �� temp �� 150 , ��λǧ��/��, kg/L)
* f(x) = p1*x^9 + p2*x^8 + p3*x^7 + p4*x^6 + 
* p5*x^5 + p6*x^4 + p7*x^3 + p8*x^2 + p9*x + p10               
/************************************************************************/
double CAlgorithm::getDensityByFit(float temp)
{
	//p1~p10Ϊ����ʽϵ��
	double const p1 =  -3.562e-18;
	double const p2 =   2.303e-15;
	double const p3 =  -5.989e-13;
	double const p4 =   7.617e-11;
	double const p5 =  -3.716e-09;
	double const p6 =  -2.719e-07;
	double const p7 =   6.455e-05;
	double const p8 =   -0.008346;
	double const p9 =     0.05982;
	double const p10 =  1000.12;
	//exp2~exp9Ϊ��������ֵ
	double exp2 = temp * temp;
	double exp3 = exp2 * temp;
	double exp4 = exp3 * temp;
	double exp5 = exp4 * temp;
	double exp6 = exp5 * temp;
	double exp7 = exp6 * temp;
	double exp8 = exp7 * temp;
	double exp9 = exp8 * temp;

	return  (p1*exp9 + p2*exp8 + p3*exp7 + p4*exp6 + p5*exp5 + p6 * exp4 + p7*exp3 +  + p8*exp2 +  + p9*temp + p10) / 1000.0;
}

/*****************************************************************************
* ������Ӧˮ�µ��ܶ�ֵ(��λǧ��/��, kg/L)
* �赱ǰˮ��Ϊtemp
* temp����������Ϊ low, 
* low�¶�ֵ���ɵ�density[low - 1](density��������0��ʼ)
* (��temp��С�����ֲ�Ϊ��, ��ô��Ϊ���¶�low-1��low֮��
* �ܶ�ֵ�����Ա仯��)
/****************************************************************************/
double CAlgorithm::getDensityByQuery(float temp)
{
	if (temp<1 || temp>149)
	{
		return -1;
	}
	int low = getInt(temp);

	return (density[low -1] +  getDecimal(temp) * (density[low] - density[low - 1])) / 1000.0;
}

/*
** ������Ӧˮ�µ���ֵ(��λ kJ/kg)
*/
double CAlgorithm::getEnthalpyByQuery(float temp)
{
	int low = getInt(temp);
	float ret = enthalpy[low -1] +  getDecimal(temp) * (enthalpy[low] - enthalpy[low - 1]);
	return ret;
}

/*
** ����ŷ��EN1434�����ܱ�����ˮ��Kϵ��
** Ĭ��Kϵ����λMJ/m3��
*/
double CAlgorithm::calcKCoeOfWater(float inTemper, float outTemper, int installPos, float pressure)
{
	float kCoe = 0.0;
	float vIn = 0.0, vOut = 0.0;
	float tao = 0.0;
	float hIn = getEnthalpyByQuery(inTemper);
	float hOut = getEnthalpyByQuery(outTemper);
 	float pai = pressure/16.53;
	float kIn = inTemper + 273.13;
	float kOut = outTemper + 273.13;
	float R = 461.526;
	float lanmuda = 0.0;
	int i = 0;
	float tmp;

	if (installPos==INSTALLPOS_IN) //��װλ�� ���
	{
		tao = 1386/kIn;
		for (i=0; i<34; i++)
		{
			tmp = -n[i]*I[i]*pow(7.1-pai, I[i]-1)*pow(tao-1.222, J[i]);
			lanmuda += tmp;
		}
		vIn = pai*lanmuda*R*kIn/pressure/1000;
		kCoe = (hIn - hOut)/(inTemper - outTemper)/vIn;
	}
	else if (installPos==INSTALLPOS_OUT)	//��װλ�� ����
	{
		tao = 1386/kOut;
		for (i=0; i<34; i++)
		{
			tmp = -n[i]*I[i]*pow(7.1-pai, I[i]-1)*pow(tao-1.222, J[i]);
			lanmuda += tmp;
		}
		vOut = pai*lanmuda*R*kOut/pressure/1000;
		kCoe = (hIn - hOut)/(inTemper - outTemper)/vOut;
	}

	return kCoe;
}

/*
** ����ŷ��EN1434�����ܱ�Part-1 ����ˮ�ı���ֵ
** ��λKJ/kg
** temp �¶�, ��
** pressure ѹǿ, MPa
*/
double CAlgorithm::calcEnthalpyOfWater(float temp, float pressure)
{
	float T = temp + 273.15;//�������¶ȱ�
	float tao = 1386/T;
	float pai = pressure/16.53;
	float gamaTao = getGamaTao(pai, tao);

	float H = tao*gamaTao*ENTHALPY_R*T;

	return H/1000.0;
}

double CAlgorithm::getGamaPai(float pai, float tao)
{
	float gama = 0.0;
	for (int i=0; i<34; i++)
		gama += (-1)*n[i]*I[i]*pow(7.1-pai, I[i]-1)*pow(tao-1.222, J[i]);

	return gama;
}

double CAlgorithm::getGamaTao(float pai, float tao)
{
	float gama = 0.0;
	for (int i=0; i<34; i++)
		gama += n[i]*pow(7.1-pai, I[i])*J[i]*pow(tao - 1.222, J[i] - 1);

	return gama;
}

/*
** ����ŷ��EN1434�����ܱ�Part-1 ����ˮ�ı���ֵ
** ��λ(kWh/MJ)
** inTemper �����¶�, ��
** outTemper �����¶�, ��
** volum ���, L
** installPos ��װλ��, ����/����
** unit ʹ�õ���ֵ��λ, kWh/MJ
** pressure ѹǿ, MPa
*/
double CAlgorithm::calcEnergyByEnthalpy(float inTemper, float outTemper, float volum,  int installPos, int unit, float pressure)
{
	float inEnthalpy, outEnthalpy;
	float density;
	float mass;
	float energy;

	inEnthalpy = calcEnthalpyOfWater(inTemper, pressure);//KJ/kg
	outEnthalpy = calcEnthalpyOfWater(outTemper, pressure);//KJ/kg
	if (installPos == INSTALLPOS_IN)
	{
		density = getDensityByQuery(inTemper);//kg/L
	}
	else if (installPos == INSTALLPOS_OUT)
	{
		density = getDensityByQuery(outTemper);//kg/L
	}
	
	mass = density*volum;//kg
	energy = mass*(inEnthalpy-outEnthalpy);//KJ
	if (unit == UNIT_KWH)
	{
		energy /= 3600.0;
	}
	else if (unit == UNIT_MJ)
	{
		energy /= 1000.0;
	}
	return energy;
}

/************************************************************************
* ���㸡��������������           
/************************************************************************/
int CAlgorithm::getInt(float p)
{
	if (p > 0)
	{
		return int(p);
	}
	else if (p == 0)
	{
		return 0;
	}
	else
	{
		return (int(p) - 1);
	}
}
/************************************************************************
* ���㸡������С������           
/************************************************************************/
float CAlgorithm::getDecimal(float p)
{
	return (p - getInt(p));
}

/************************************************************************
* ����λ�Ż�ȡ��Ӧ��λ�ı�׼������� (��λ��, L)                       
* mass: ��ƽ��������(��λǧ��, kg)
* inlet: ��ˮ���¶�
* outlet: ��ˮ���¶�
* num: ��λ��(��1��ʼ�����������)
************************************************************************/
double CAlgorithm::getStdVolByPos(float mass, float inlet, float outlet, int num)
{	
	float temp = getMeterTempByPos(inlet, outlet, num);//��ȡ�¶�
#ifdef FIT
	float den = getDensityByFit(temp);//��ȡ�ܶ�
#else
	float den = getDensityByQuery(temp);//��ȡ�ܶ�
#endif

	return (mass*0.997 / den);//���ر�׼���(���Ǹ�ǧ��֮���ĸ�������)
}

/*
** �����ʲ�����׼������JJG-2001)
** ��λ(kWh��MJ)
** inTemper ���ڱ�׼�¶�, ��
** outTemper ���ڱ�׼�¶�, ��
** mass ����, kg
** unit ʹ�õ���ֵ��λ, 0:MJ ; 1:kWh
*/
double CAlgorithm::calcStdEnergyByEnthalpy(float inTemper, float outTemper, float mass, int unit, float pressure)
{
	float inEnthalpy, outEnthalpy, energy;

// 	inEnthalpy = calcEnthalpyOfWater(inTemper, pressure);//KJ/kg
// 	outEnthalpy = calcEnthalpyOfWater(outTemper, pressure);//KJ/kg
	inEnthalpy = getEnthalpyByQuery(inTemper);//KJ/kg
	outEnthalpy = getEnthalpyByQuery(outTemper);//KJ/kg
	energy = mass*(inEnthalpy-outEnthalpy);//KJ
	if (unit == UNIT_KWH)
	{
		energy /= 3600.0;
	}
	else if (unit == UNIT_MJ)
	{
		energy /= 1000.0;
	}
	return energy;
}

