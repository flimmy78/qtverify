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

ALGORITHM_EXPORT int getPortSetIni(PORTSET_INI_PTR info); //端口配置
ALGORITHM_EXPORT int getParaSetIni(PARASET_INI_PTR info); //参数设置(质量法-分量检测)
ALGORITHM_EXPORT int getMasterSlaveIni(MASTERSLAVE_INI_PTR info); //主机-从机设置信息

class ALGORITHM_EXPORT CAlgorithm
{
public:
	CAlgorithm();
	~CAlgorithm();

	float calc(float a, float b);

private:

};

#endif // ALGORITHM_H
