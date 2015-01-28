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

#include "basedef.h"

ALGORITHM_EXPORT int getPortSetIni(PortSet_Ini_PTR info); //获取控制板的端口号配置信息
ALGORITHM_EXPORT int getParaSetIni(ParaSet_Ini_PTR info); //获取参数设置(质量法-分量检测)
ALGORITHM_EXPORT int getMasterSlaveIni(MasterSlave_Ini_PTR info); //获取主机-从机设置信息

const float density[150] = {
	1000.2,
	1000.2,
	1000.2,
	1000.2,
	1000.2,
	1000.2,
	1000.1,
	1000.1,
	1000,
	999.94,
	999.84,
	999.74,
	999.61,
	999.48,
	999.34,
	999.18,
	999.01,
	998.83,
	998.64,
	998.44,
	998.22,
	998,
	997.77,
	997.52,
	997.27,
	997.01,
	996.74,
	996.46,
	996.17,
	995.87,
	995.56,
	995.25,
	994.93,
	994.59,
	994.25,
	993.91,
	993.55,
	993.19,
	992.81,
	992.44,
	992.05,
	991.65,
	991.25,
	990.85,
	990.43,
	990.01,
	989.58,
	989.14,
	988.7,
	988.25,
	987.8,
	987.33,
	986.87,
	986.39,
	985.91,
	985.42,
	984.93,
	984.43,
	983.93,
	983.41,
	982.9,
	982.37,
	981.84,
	981.31,
	980.77,
	980.22,
	979.67,
	979.12,
	978.55,
	977.98,
	977.41,
	976.83,
	976.25,
	975.66,
	975.06,
	974.46,
	973.86,
	973.25,
	972.63,
	972.01,
	971.39,
	970.76,
	970.12,
	969.48,
	968.84,
	968.19,
	967.53,
	966.87,
	966.21,
	965.54,
	964.86,
	964.18,
	963.5,
	962.81,
	962.12,
	961.42,
	960.72,
	960.01,
	959.3,
	958.58,
	957.86,
	957.14,
	956.41,
	955.67,
	954.93,
	954.19,
	953.44,
	952.69,
	951.93,
	951.17,
	950.4,
	949.63,
	948.86,
	948.08,
	947.29,
	946.51,
	945.71,
	944.92,
	944.11,
	943.31,
	942.5,
	941.68,
	940.86,
	940.04,
	939.21,
	938.38,
	937.54,
	936.7 ,
	935.86,
	935.01,
	934.15,
	933.29,
	932.43,
	931.56,
	930.69,
	929.81,
	928.93,
	928.05,
	927.16,
	926.26,
	925.37,
	924.46,
	923.56,
	922.64,
	921.73,
	920.81,
	919.88,
	918.95,
	918.02,
	917.08
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
