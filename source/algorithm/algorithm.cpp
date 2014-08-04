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
	char filename[FILENAME_LENGTH];
	memset(filename, 0, sizeof(char)*FILENAME_LENGTH);
	char* runhome = getenv( "RUNHOME" );
	if (NULL == runhome)
	{
		qWarning()<<"Get $(RUNHOME) Failed!";
		return false;
	}
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

//��ȡ��������(������-�������)
int getParaSetIni(ParaSet_Ini_PTR info)
{
	char filename[FILENAME_LENGTH];
	memset(filename, 0, sizeof(char)*FILENAME_LENGTH);
	char* runhome = getenv( "RUNHOME" );
	if (NULL == runhome)
	{
		qWarning()<<"Get $(RUNHOME) Failed!";
		return false;
	}
#ifdef __unix
	sprintf( filename, "%s/ini/qualityParaSet.ini", runhome );
#else
	sprintf( filename, "%s\\ini\\qualityParaSet.ini", runhome );
#endif

	QSettings settings(filename, QSettings::IniFormat);
	settings.setIniCodec("GB2312"); //���ini�ļ�����������
	strcpy(info->meterstandard, settings.value("paraset/standard").toString().toAscii());
	strcpy(info->metertype, settings.value("paraset/metertype").toString().toAscii());

	return true;
}

//��ȡ����-�ӻ�������Ϣ
int getMasterSlaveIni(MasterSlave_Ini_PTR info)
{
	char filename[FILENAME_LENGTH];
	memset(filename, 0, sizeof(char)*FILENAME_LENGTH);
	char* runhome = getenv( "RUNHOME" );
	if (NULL == runhome)
	{
		qWarning()<<"Get $(RUNHOME) Failed!";
		return false;
	}
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

/****************************************************************************
* ����λ�ż������¶�(���������)                                      *
* inlet: ��ˮ���¶�ֵ                                                              *
* oulet: ��ˮ���¶�ֵ                                                             *
* num: �����ı�λ��, �Դ˼�����ȱ�����ڵľ���        *
/****************************************************************************/
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
	paraPath = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\/ini\/qualityParaSet.ini";
#elif defined (Q_OS_WIN)
	paraPath = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\\ini\\qualityParaSet.ini";
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
* float temp: �¶�ֵ ( 1 �� temp �� 150 )
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

	return  p1*exp9 + p2*exp8 + p3*exp7 + p4*exp6 + p5*exp5 + p6 * exp4 + p7*exp3 +  + p8*exp2 +  + p9*temp + p10;
}

/*****************************************************************************
* ������Ӧˮ�µ��ܶ�ֵ
* �赱ǰˮ��Ϊtemp
* temp����������Ϊ low, 
* low�¶�ֵ���ɵ�density[low - 1](density��������0��ʼ)
* (��temp��С�����ֲ�Ϊ��, ��ô��Ϊ���¶�low��low+1֮��
* �ܶ�ֵ�ı仯�����Ե�)
/****************************************************************************/
double CAlgorithm::getDensityByQuery(float temp)
{
	int low = getInt(temp);

	return density[low -1] +  getDecimal(temp) * (density[low] - density[low]);
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
* ����λ�Ż�ȡ��Ӧ��λ�ı�׼�������                        
* mass: ��ƽ��������
* inlet: ��ˮ���¶�
* outlet: ��ˮ���¶�
* num: ��λ��
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