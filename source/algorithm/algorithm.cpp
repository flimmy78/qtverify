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
#include <QtCore/QFile>
#include <QProcessEnvironment>
#include <qmath.h>

#include "algorithm.h"
#include "commondefine.h"

//获取控制板的端口号配置信息
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

//获取主机-从机设置信息
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

//获取所有采集代码对应的中文名称
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
			str = stream.readLine().simplified(); //去除首尾空格
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
/* 一般只需三组温度-阻值即可计算出此铂电阻的温度系数和0℃温度                 */
/************************************************************************/
plaParam_PTR getPlaParam(pla_T_R_PTR pla_p, int num)
{
	plaParam_PTR p_param;
	p_param = new plaParam_STR;
	float coe[2][3];//方程系数, coe[i,j]前两列对应于线性方程组的第i个方程第j个未知数的系数, 第三列是常数项
	coe[0][0] = detA(pla_p[0].resis, pla_p[0].tmp, pla_p[1].resis, pla_p[1].tmp);
	coe[0][1] = detA(pla_p[0].resis, pla_p[0].tmp*pla_p[0].tmp, pla_p[1].resis, pla_p[1].tmp*pla_p[1].tmp);
	coe[0][2] = pla_p[1].resis - pla_p[0].resis;
	coe[1][0] = detA(pla_p[0].resis, pla_p[0].tmp, pla_p[2].resis, pla_p[2].tmp);
	coe[1][1] = detA(pla_p[0].resis, pla_p[0].tmp*pla_p[0].tmp, pla_p[2].resis, pla_p[2].tmp*pla_p[2].tmp);
	coe[1][2] = pla_p[2].resis - pla_p[0].resis;

	float M;//克莱姆法则系数方阵的行列式的值
	float A;//第一未知数a的值
	float B;//第二未知数b的值
	M = detA(coe[0][0], coe[0][1], coe[1][0], coe[1][1]);
	A = detA(coe[0][2], coe[0][1], coe[1][2], coe[1][1]);
	B = detA(coe[0][0], coe[0][2], coe[1][0], coe[1][2]);
	p_param->a = A/M;
	p_param->b = B/M;
	p_param->r0 = pla_p[0].resis/(1 + p_param->a*pla_p[0].tmp + p_param->b*pla_p[0].tmp*pla_p[0].tmp);
	p_param->c;//参数c一般不做计算，只有0℃以下才用到
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

float getDeltaTmpErr(float std_delta_t, float min_delta_t)
{
	return qAbs(0.5 + 3*min_delta_t/std_delta_t);
}

float getSingleTmpErr(float std_delta_t)
{
	return (0.3 + 0.005*qAbs(std_delta_t));
}

/************************************************************************/
/*根据JJG-2001 Page4, 表1
/*grade, 表的等级, 1级, 2级等
/*delta_t_min, 表的最小温差
/*deta_t, 实际检测时的温差
/*dn_flow_rate, 表的常用(额定)流量, 计量单位与flow_rate相同
/*flow_rate, 实际检测时表的流量
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

float calcFloatValueOfCoe(QString coe)
{
	bool ok;
	float dec = coe.right(3).toInt(&ok, 16)/4096.0;
	float coeV = coe.left(1).toFloat() + dec; 
	float fValue = 100/coeV - 100;

	return fValue;
}

/* 计算ModBus-RTU传输协议的CRC校验值
 * ref: http://www.ccontrolsys.com/w/How_to_Compute_the_Modbus_RTU_Message_CRC
 * 生成多项式为0xA001
 * data, 指向消息头的指针;
 * len, 消息体的长度
 */
UINT16 calcModRtuCRC(uchar *buf, int len)
{
	UINT16 crc = 0xFFFF;

	for (int pos = 0; pos < len; pos++) {
		crc ^= (UINT16)buf[pos];          // XOR byte into least sig. byte of crc

		for (int i = 8; i > 0; i--) {    // Loop over each bit
			if ((crc & 0x0001) != 0) {      // If the LSB is set
				crc >>= 1;                    // Shift right and XOR 0xA001
				crc ^= POLY;
			}
			else                            // Else LSB is not set
				crc >>= 1;                    // Just shift right
		}
	}
	return ((crc<<8) | (crc>>8));//交换计算结果的高低位
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
* outlet: 出水口温度值																						   
* num: 表位号(从1开始至最大检表数量), 以此计算此热表离进口的距离        
/********************************************************************************************/
float CAlgorithm::getMeterTempByPos(float inlet, float outlet, int num)
{
	//1, 根据meterType读取 {管路-表位号} 的配置参数, 取出管路总长度t_length
	//1.1* 获取配置文件
	QSettings *PortSet = new QSettings(getFullIniFileName("meterposition.ini"), QSettings::IniFormat);
	//1.2* 读取管路总长度t_length
	float t_length = PortSet->value("total/length").toFloat();
	//2, 根据取得的配置参数和num计算被检热表离进水口的距离d_length;
	//2.1* 获取被检表的规格
	QSettings *ParaSet = new QSettings(getFullIniFileName("verifyparaset.ini"), QSettings::IniFormat);//参数配置文件
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
	float delta = outlet - inlet;
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

/*
** 查表求对应水温的焓值(单位 kJ/kg)
*/
double CAlgorithm::getEnthalpyByQuery(float temp)
{
	int low = getInt(temp);
	float ret = enthalpy[low -1] +  getDecimal(temp) * (enthalpy[low] - enthalpy[low - 1]);
	return ret;
}

/*
** 根据欧标EN1434《热能表》计算水的K系数
** 默认K系数单位MJ/m3℃
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

	if (installPos==INSTALLPOS_IN) //安装位置 入口
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
	else if (installPos==INSTALLPOS_OUT)	//安装位置 出口
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
** 根据欧标EN1434《热能表》Part-1 计算水的比焓值
** 单位KJ/kg
** temp 温度, ℃
** pressure 压强, MPa
*/
double CAlgorithm::calcEnthalpyOfWater(float temp, float pressure)
{
	float T = temp + 273.15;//开尔文温度标
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
** 根据欧标EN1434《热能表》Part-1 计算水的比焓值
** 单位(kWh/MJ)
** inTemper 进口温度, ℃
** outTemper 出口温度, ℃
** volum 体积, L
** installPos 安装位置, 进口/出口
** unit 使用的热值单位, kWh/MJ
** pressure 压强, MPa
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

/*
** 根据焓差计算标准热量（JJG-2001)
** 单位(kWh或MJ)
** inTemper 进口标准温度, ℃
** outTemper 出口标准温度, ℃
** mass 质量, kg
** unit 使用的热值单位, 0:MJ ; 1:kWh
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

