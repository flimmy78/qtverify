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


ALGORITHM_EXPORT int getPortSetIni(PORTSET_INI_PTR info); //��ȡ���ư�Ķ˿ں�������Ϣ
ALGORITHM_EXPORT int getParaSetIni(PARASET_INI_PTR info); //��ȡ��������(������-�������)
ALGORITHM_EXPORT int getMasterSlaveIni(MASTERSLAVE_INI_PTR info); //��ȡ����-�ӻ�������Ϣ

class ALGORITHM_EXPORT CAlgorithm
{
public:
	CAlgorithm();
	~CAlgorithm();

	float calc(float a, float b);

private:

};

#endif // ALGORITHM_H
