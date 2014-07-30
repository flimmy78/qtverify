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

class ALGORITHM_EXPORT CAlgorithm
{
public:
	CAlgorithm();
	~CAlgorithm();

	float calc(float a, float b);

	float getMeterTempByPos(float inlet, float oulet, enum metertype meterType, int num);//按表位号计算其温度
	float getDensityByTemp(float temp);//根据水的温度值查找密度值
private:

};

#endif // ALGORITHM_H
