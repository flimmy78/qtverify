#ifndef ALGORITHM_H
#define ALGORITHM_H

#ifdef ALGORITHM_DLL
#  ifdef WIN32
#  define ALGORITHM_EXPORT __declspec(dllexport)
#  else
#  define ALGORITHM_EXPORT
#  endif
#else
#  ifdef WIN32
#  define ALGORITHM_EXPORT __declspec(dllimport)
#  else
#  define ALGORITHM_EXPORT
#  endif
#endif

#include <QString>
#include <QByteArray>
#include "basedef.h"

ALGORITHM_EXPORT int getPortSetIni(PortSet_Ini_PTR info); //获取控制板的端口号配置信息
ALGORITHM_EXPORT int getMasterSlaveIni(MasterSlave_Ini_PTR info); //获取主机-从机设置信息
ALGORITHM_EXPORT QString getFullIniFileName(QString filename);//获取配置文件filename的完整路径
ALGORITHM_EXPORT QStringList getPickCodeStringList();//获取所有采集代码对应的中文名称
ALGORITHM_EXPORT float detA(float a00, float a01, float a10, float a11);//计算2阶行列式的值， aij表示第i行 第j列的元素
ALGORITHM_EXPORT plaParam_PTR getPlaParam(pla_T_R_PTR pla_p, int num=3);//计算铂电阻的电气系数
ALGORITHM_EXPORT float getPlaRt(float r0, float a, float b, float tmp);//计算铂电阻在温度tmp(tmp>0℃)时的电阻值
ALGORITHM_EXPORT float getPlaTr(float r0, float a, float b, float resis);//计算铂电阻在电阻值resis(resis>r0)时的温度值
ALGORITHM_EXPORT float getDeltaTmpErr(float std_delta_t, float min_delta_t);//根据jjg225-2001计算温差误差限限(%), 以浮点数返回
ALGORITHM_EXPORT float getSingleTmpErr(float std_delta_t);//根据jjg225-2001计算单支铂电阻温度误差限(%), 以浮点数返回
ALGORITHM_EXPORT float getMeterGradeErrLmt(int grade, float delta_t_min, float delta_t, float dn_flow_rate, float flow_rate);//根据表的等级, 计算表的示值误差限(%), 以浮点数返回
ALGORITHM_EXPORT float calcFloatValueOfCoe(QString coe);//根据热量表通讯返回的两字节数据，计算出对应的浮点型数值
ALGORITHM_EXPORT float calcErrorValueOfCoe(QString coe);//根据热量表通讯返回的两字节数据，计算出对应的误差值
ALGORITHM_EXPORT UINT16 calcModRtuCRC(uchar *, int);//计算modbus-RTU协议的CRC校验值
ALGORITHM_EXPORT QByteArray getCRCArray(UINT16);//将CRC计算结果转换为QByteArray
ALGORITHM_EXPORT int get9150ARouteI(int i, QByteArray valueArray);//获取力创模块中通道i的脉冲值
ALGORITHM_EXPORT int get9017RouteI(int i, QByteArray valueArray);//获取力创模块中通道i的脉冲值
const float density[150] = { //压力<=0.6MPa
	1000.2f,
	1000.2f,
	1000.2f,
	1000.2f,
	1000.2f,
	1000.2f,
	1000.1f,
	1000.1f,
	1000.0f,
	999.94f,
	999.84f,
	999.74f,
	999.61f,
	999.48f,
	999.34f,
	999.18f,
	999.01f,
	998.83f,
	998.64f,
	998.44f,
	998.22f,
	998.00f,
	997.77f,
	997.52f,
	997.27f,
	997.01f,
	996.74f,
	996.46f,
	996.17f,
	995.87f,
	995.56f,
	995.25f,
	994.93f,
	994.59f,
	994.25f,
	993.91f,
	993.55f,
	993.19f,
	992.81f,
	992.44f,
	992.05f,
	991.65f,
	991.25f,
	990.85f,
	990.43f,
	990.01f,
	989.58f,
	989.14f,
	988.70f,
	988.25f,
	987.80f,
	987.33f,
	986.87f,
	986.39f,
	985.91f,
	985.42f,
	984.93f,
	984.43f,
	983.93f,
	983.41f,
	982.90f,
	982.37f,
	981.84f,
	981.31f,
	980.77f,
	980.22f,
	979.67f,
	979.12f,
	978.55f,
	977.98f,
	977.41f,
	976.83f,
	976.25f,
	975.66f,
	975.06f,
	974.46f,
	973.86f,
	973.25f,
	972.63f,
	972.01f,
	971.39f,
	970.76f,
	970.12f,
	969.48f,
	968.84f,
	968.19f,
	967.53f,
	966.87f,
	966.21f,
	965.54f,
	964.86f,
	964.18f,
	963.50f,
	962.81f,
	962.12f,
	961.42f,
	960.72f,
	960.01f,
	959.30f,
	958.58f,
	957.86f,
	957.14f,
	956.41f,
	955.67f,
	954.93f,
	954.19f,
	953.44f,
	952.69f,
	951.93f,
	951.17f,
	950.40f,
	949.63f,
	948.86f,
	948.08f,
	947.29f,
	946.51f,
	945.71f,
	944.92f,
	944.11f,
	943.31f,
	942.50f,
	941.68f,
	940.86f,
	940.04f,
	939.21f,
	938.38f,
	937.54f,
	936.70f,
	935.86f,
	935.01f,
	934.15f,
	933.29f,
	932.43f,
	931.56f,
	930.69f,
	929.81f,
	928.93f,
	928.05f,
	927.16f,
	926.26f,
	925.37f,
	924.46f,
	923.56f,
	922.64f,
	921.73f,
	920.81f,
	919.88f,
	918.95f,
	918.02f,
	917.08f
};//水温-密度表, (下标的索引值 + 1) 即为(整数温度值), 密度单位(千克/立方米, kg/m3)

const float enthalpy[150] = { //压力<=0.6MPa
	4.7841f,
	8.9963f,
	13.206f,
	17.412f,
	21.616f,
	25.818f,
	30.018f,
	34.215f,
	38.411f,
	42.605f,
	46.798f,
	50.989f,
	55.178f,
	59.367f,
	63.554f,
	67.74f,
	71.926f,
	76.11f,
	80.294f,
	84.476f,
	88.659f,
	92.84f,
	97.021f,
	101.2f,
	105.38f,
	109.56f,
	113.74f,
	117.92f,
	122.1f,
	126.28f,
	130.46f,
	134.63f,
	138.81f,
	142.99f,
	147.17f,
	151.35f,
	155.52f,
	159.7f,
	163.88f,
	168.06f,
	172.24f,
	176.41f,
	180.59f,
	184.77f,
	188.95f,
	193.13f,
	197.31f,
	201.49f,
	205.67f,
	209.85f,
	214.03f,
	218.21f,
	222.39f,
	226.57f,
	230.75f,
	234.94f,
	239.12f,
	243.3f,
	247.48f,
	251.67f,
	255.85f,
	260.04f,
	264.22f,
	268.41f,
	272.59f,
	276.78f,
	280.97f,
	285.15f,
	289.34f,
	293.53f,
	297.72f,
	301.91f,
	306.1f,
	310.29f,
	314.48f,
	318.68f,
	322.87f,
	327.06f,
	331.26f,
	335.45f,
	339.65f,
	343.85f,
	348.04f,
	352.24f,
	356.44f,
	360.64f,
	364.84f,
	369.04f,
	373.25f,
	377.45f,
	381.65f,
	385.86f,
	390.07f,
	394.27f,
	398.48f,
	402.69f,
	406.9f,
	411.11f,
	415.33f,
	419.54f,
	423.76f,
	427.97f,
	432.19f,
	436.41f,
	440.63f,
	444.85f,
	449.07f,
	453.3f,
	457.52f,
	461.75f,
	465.98f,
	470.2f,
	474.44f,
	478.67f,
	482.9f,
	487.14f,
	491.37f,
	495.61f,
	499.85f,
	504.09f,
	508.34f,
	512.58f,
	516.83f,
	521.08f,
	525.33f,
	529.58f,
	533.83f,
	538.09f,
	542.35f,
	546.61f,
	550.87f,
	555.13f,
	559.4f,
	563.67f,
	567.93f,
	572.21f,
	576.48f,
	580.76f,
	585.04f,
	589.32f,
	593.6f,
	597.88f,
	602.17f,
	606.46f,
	610.76f,
	615.05f,
	619.35f,
	623.65f,
	627.95f,
	632.26f
};//水温-焓值表, (下标的索引值 + 1) 即为(整数温度值), 焓值单位(kJ/kg)

//参考欧标EN1434《热能表》计算K系数用参数
const double n[34] =
{
	0.14632971213167,
	-0.84548187169114,
	-0.37563603672040e1,
	0.33855169168385e1,
	-0.95791963387872,
	0.15772038513228,
	-0.16616417199501e-1,
	0.81214629983568e-3,
	0.28319080123804e-3,
	-0.60706301565874e-3,
	-0.18990068218419e-1,
	-0.32529748770505e-1,
	-0.21841717175414e-1,
	-0.52838357969930e-4,
	-0.47184321073267e-3,
	-0.30001780793026e-3,
	0.47661393906987e-4,	
	-0.44141845330846e-5,
	-0.72694996297594e-15,
	-0.31679644845054e-4,
	-0.28270797985312e-5,
	-0.85205128120103e-9,
	-0.22425281908000e-5,
	-0.65171222895601e-6,
	-0.14341729937924e-12,
	-0.40516996860117e-6,
	-0.12734301741641e-8,
	-0.17424871230634e-9,
	-0.68762131295531e-18,
	0.14478307828521e-19,
	0.26335781662795e-22,
	-0.11947622640071e-22,
	0.18228094581404e-23,
	-0.93537087292458e-25
};

const int I[34] = 
{
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 2, 2,
	2, 2, 2, 3, 3, 3, 4, 4,
	4, 5, 8, 8, 21, 23, 29, 30,
	31, 32
};

const int J[34] = 
{
	-2, -1,  0, 1, 2, 3, 4, 5,
	-9, -7, -1, 0, 1, 3, -3,0,
	 1,  3, 17, -4, 0, 6,-5, -2,
	 10, -8, -11,-6,-29,-31,-38,-39,
	-40,-41
};


class ALGORITHM_EXPORT CAlgorithm
{
public:
	CAlgorithm();
	~CAlgorithm();
	
	float calc(float a, float b);
	
	float getMeterTempByPos(float inlet, float oulet, int num);//按表位号计算其温度
	double getDensityByFit(float temp);//根据水的温度值计算密度值(拟合法)
	double getDensityByQuery(float temp);//根据水的温度值查找密度值(查表法)
	double getStdVolByPos(float mass, float inlet, float outlet, int num);//获取对应表位的标准体积流量
	double getEnthalpyByQuery(float temp);//根据水的温度值查找焓值(查表法)
	double calcKCoeOfWater(float inTemper, float outTemper,  int installPos, float pressure=0.6); //根据进水温度、出水温度、安装位置计算K系数
	double getGamaPai(float pai, float tao);//用于水的热量K系数计算的γ
	double getGamaTao(float pai, float tao);//用于水的比焓值计算的γ
	double calcEnthalpyOfWater(float temp, float pressure);//计算水的比焓值, 温度范围0℃~350℃
	double calcEnergyByEnthalpy(float inTemper, float outTemper, float vol,  int installPos, int unit, float pressure=NORMAL_PRESSURE);//焓差法计算热值（组合检定）
	double calcStdEnergyByEnthalpy(float inTemper, float outTemper, float mass, int unit, float pressure=NORMAL_PRESSURE); //焓差法计算热值(质量法总量检定)
private:
	int getInt(float p);
	float getDecimal(float p);

};

#endif // ALGORITHM_H
