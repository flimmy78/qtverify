/***********************************************
**  文件名:     algorithm.cpp
**  功能:       检定算法及读取配置文件等
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/26
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/06 第一版
**  内容包含:
**  说明:		
**  更新记录:   
***********************************************/

#include <QtCore/QDebug>
#include <QtCore/QSettings>
 #include <QProcessEnvironment>

#include "algorithm.h"
#include "commondefine.h"

//获取控制板的端口号配置信息
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

//获取参数设置(质量法-分量检测)
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
	settings.setIniCodec("GB2312"); //解决ini文件读中文乱码
	strcpy(info->meterstandard, settings.value("paraset/standard").toString().toAscii());
	strcpy(info->metertype, settings.value("paraset/metertype").toString().toAscii());

	return true;
}

//获取主机-从机设置信息
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
类名：CAlgorithm
功能：检定算法类
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
* 按表位号计算其温度(距离均布法)                                      
* inlet: 进水口温度值                                                              
* oulet: 出水口温度值																						   
* num: 表位号(从1开始至最大检表数量), 以此计算此热表离进口的距离        
/********************************************************************************************/
float CAlgorithm::getMeterTempByPos(float inlet, float oulet, int num)
{
	//1, 根据meterType读取 {管路-表位号} 的配置参数, 取出管路总长度t_length
	//1.1* 获取配置文件
	QString IniPath;
#ifdef Q_OS_LINUX
	IniPath = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\/ini\/meterposition.ini";
#elif defined (Q_OS_WIN)
	IniPath = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\\ini\\meterposition.ini";
#endif
	QSettings *PortSet = new QSettings(IniPath, QSettings::IniFormat);
	//1.2* 读取管路总长度t_length
	float t_length = PortSet->value("total/length").toFloat();
	//2, 根据取得的配置参数和num计算被检热表离进水口的距离d_length;
	//2.1* 获取被检表的规格
	QString paraPath;
#ifdef Q_OS_LINUX
	paraPath = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\/ini\/qualityParaSet.ini";
#elif defined (Q_OS_WIN)
	paraPath = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\\ini\\qualityParaSet.ini";
#endif
	QSettings *ParaSet = new QSettings(paraPath, QSettings::IniFormat);//参数配置文件
	int meterType = ParaSet->value("head/standard").toInt();//被检表规格
	float d_length = PortSet->value(QString::number(meterType) + "/" + QString::number(num)).toFloat();
	//2.2* 释放内存
	delete ParaSet;
	ParaSet = NULL;
	delete PortSet;
	PortSet = NULL;
	//3, 根据 被检热表离进水口的距离和管路总长度计算温度系数 coeff = d_length / t_length
	float coeff = d_length / t_length;
	//4, 计算温度差值 delta = (oulet - inlet)
	float delta = oulet - inlet;
	//5, 根据温度差值和温度系数最终得出被检热表的温度值 t = (inlet + coeff * delta)
	return (inlet + coeff * delta);
}

/************************************************************************
* 根据水温-密度表(JGG 225-2010 热量表检定规程)
* 进行多项式拟合(MATLAB, 9次方)
* float temp: 温度值 ( 1 ≤ temp ≤ 150 , 单位千克/升, kg/L)
* f(x) = p1*x^9 + p2*x^8 + p3*x^7 + p4*x^6 + 
* p5*x^5 + p6*x^4 + p7*x^3 + p8*x^2 + p9*x + p10               
/************************************************************************/
double CAlgorithm::getDensityByFit(float temp)
{
	//p1~p10为多项式系数
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
	//exp2~exp9为参数的幂值
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
* 查表求对应水温的密度值(单位千克/升, kg/L)
* 设当前水温为temp
* temp的整数部分为 low, 
* low温度值查表可得density[low - 1](density的索引从0开始)
* (若temp的小数部分不为零, 那么认为在温度low-1至low之间
* 密度值是线性变化的)
/****************************************************************************/
double CAlgorithm::getDensityByQuery(float temp)
{
	int low = getInt(temp);

	return (density[low -1] +  getDecimal(temp) * (density[low] - density[low - 1])) / 1000.0;
}

/************************************************************************
* 计算浮点数的整数部分           
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
* 计算浮点数的小数部分           
/************************************************************************/
float CAlgorithm::getDecimal(float p)
{
	return (p - getInt(p));
}

/************************************************************************
* 按表位号获取对应表位的标准体积流量 (单位升, L)                       
* mass: 天平的质量差(单位千克, kg)
* inlet: 进水口温度
* outlet: 出水口温度
* num: 表位号(从1开始至最大检表数量)
************************************************************************/
double CAlgorithm::getStdVolByPos(float mass, float inlet, float outlet, int num)
{	
	float temp = getMeterTempByPos(inlet, outlet, num);//获取温度
#ifdef FIT
	float den = getDensityByFit(temp);//获取密度
#else
	float den = getDensityByQuery(temp);//获取密度
#endif

	return (mass / den);//返回标准体积
}