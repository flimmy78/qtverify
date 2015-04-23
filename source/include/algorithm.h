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
#include "basedef.h"

ALGORITHM_EXPORT int getPortSetIni(PortSet_Ini_PTR info); //获取控制板的端口号配置信息
ALGORITHM_EXPORT int getParaSetIni(ParaSet_Ini_PTR info); //获取参数设置(质量法-分量检测)
ALGORITHM_EXPORT int getMasterSlaveIni(MasterSlave_Ini_PTR info); //获取主机-从机设置信息
ALGORITHM_EXPORT QString getIniFileName(QString ini);//获取配置文件int的完整路径
ALGORITHM_EXPORT float detA(float a00, float a01, float a10, float a11);//计算2阶行列式的值， aij表示第i行 第j列的元素
ALGORITHM_EXPORT plaParam_PTR getPlaParam(pla_T_R_PTR pla_p, int num=3);//计算铂电阻的电气系数
ALGORITHM_EXPORT float getPlaRt(float r0, float a, float b, float tmp);//计算铂电阻在温度tmp(tmp>0℃)时的电阻值
ALGORITHM_EXPORT float getPlaTr(float r0, float a, float b, float resis);//计算铂电阻在电阻值resis(resis>r0)时的温度值
const float density[150] = {
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
private:
	
	int getInt(float p);
	float getDecimal(float p);

};

#endif // ALGORITHM_H
