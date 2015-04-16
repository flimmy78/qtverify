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
#include <QProcessEnvironment>

#include "algorithm.h"
#include "commondefine.h"

//��ȡ���ư�Ķ˿ں�������Ϣ
int getPortSetIni(PortSet_Ini_PTR info)
{
	QString filename;
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");
	if (runhome.isEmpty())
	{
		qWarning()<<"Get $(RUNHOME) Failed!";
		return false;
	}
#ifdef __unix
	filename = runhome + "\/ini\/portset.ini";
#else
	filename = runhome + "\\ini\\portset.ini";
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

	info->version = settings.value("CtrlBoard/version").toInt();
	return true;
}

//��ȡ��������(������-�������)
int getParaSetIni(ParaSet_Ini_PTR info)
{
	QString filename;
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");
	if (runhome.isEmpty())
	{
		qWarning()<<"Get $(RUNHOME) Failed!";
		return false;
	}
#ifdef __unix
	filename = runhome + "\/ini\/verifyparaset.ini";
#else
	filename = runhome + "\\ini\\verifyparaset.ini";
#endif

	QSettings settings(filename, QSettings::IniFormat);
	settings.setIniCodec("GB2312"); //���ini�ļ�����������
	strcpy_s(info->meterstandard, settings.value("head/standard").toString().toAscii());
	strcpy_s(info->metertype, settings.value("head/metertype").toString().toAscii());

	return true;
}

//��ȡ����-�ӻ�������Ϣ
int getMasterSlaveIni(MasterSlave_Ini_PTR info)
{
	QString filename;
	QString runhome;
	if (runhome.isEmpty())
	{
		qWarning()<<"Get $(RUNHOME) Failed!";
		return false;
	}
#ifdef __unix
	filename = runhome + "\/ini\/masterslaveset.ini";
#else
	filename = runhome + "\\ini\\masterslaveset.ini";
#endif

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

QString getIniFileName(QString ini)
{
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");
	if (runhome.isEmpty())
	{
		qWarning()<<"Get $(RUNHOME) Failed! Please set up this system variable.";
		return "";
	}
	QString filename;
#ifdef __unix
	filename = runhome + "\/ini\/" + ini;
#else
	filename = runhome + "\\ini\\" + ini;
#endif
	return filename;
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
* oulet: ��ˮ���¶�ֵ																						   
* num: ��λ��(��1��ʼ�����������), �Դ˼�����ȱ�����ڵľ���        
/********************************************************************************************/
float CAlgorithm::getMeterTempByPos(float inlet, float oulet, int num)
{
	//1, ����meterType��ȡ {��·-��λ��} �����ò���, ȡ����·�ܳ���t_length
	//1.1* ��ȡ�����ļ�
	QString IniPath;
#ifdef Q_OS_LINUX
	IniPath = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\/ini\/meterposition.ini";
#elif defined (Q_OS_WIN)
	IniPath = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\\ini\\meterposition.ini";
#endif
	QSettings *PortSet = new QSettings(IniPath, QSettings::IniFormat);
	//1.2* ��ȡ��·�ܳ���t_length
	float t_length = PortSet->value("total/length").toFloat();
	//2, ����ȡ�õ����ò�����num���㱻���ȱ����ˮ�ڵľ���d_length;
	//2.1* ��ȡ�����Ĺ��
	QString paraPath;
#ifdef Q_OS_LINUX
	paraPath = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\/ini\/verifyparaset.ini";
#elif defined (Q_OS_WIN)
	paraPath = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\\ini\\verifyparaset.ini";
#endif
	QSettings *ParaSet = new QSettings(paraPath, QSettings::IniFormat);//���������ļ�
	int meterType = ParaSet->value("head/standard").toInt();//�������
	float d_length = PortSet->value(QString::number(meterType) + "/" + QString::number(num)).toFloat();
	//2.2* �ͷ��ڴ�
	delete ParaSet;
	ParaSet = NULL;
	delete PortSet;
	PortSet = NULL;
	//3, ���� �����ȱ����ˮ�ڵľ���͹�·�ܳ��ȼ����¶�ϵ�� coeff = d_length / t_length
	float coeff = d_length / t_length;
	//4, �����¶Ȳ�ֵ delta = (oulet - inlet)
	float delta = oulet - inlet;
	//5, �����¶Ȳ�ֵ���¶�ϵ�����յó������ȱ���¶�ֵ t = (inlet + coeff * delta)
	return (inlet + coeff * delta);
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
	int low = getInt(temp);

	return (density[low -1] +  getDecimal(temp) * (density[low] - density[low - 1])) / 1000.0;
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

	return (mass / den);//���ر�׼���
}