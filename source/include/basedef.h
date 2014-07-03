#ifndef BASEDEF_H
#define BASEDEF_H

/*
**      FUNCTION -- ��ȡ��λ���˿�������Ϣ(portset.ini�ļ�)
*/
class PORTSET_INI_STR{
public:
    int     waterInNo;                   //
    int     bigNo;					 //
    int     middle1No;                     //
    int     middle2No;                     //
    int     smallNo;                     //
    int     waterOutNo;                  //
	int		regflow1No;
	int		regflow2No;
	int		regflow3No;
	int     pumpNo;
};
typedef PORTSET_INI_STR* PORTSET_INI_PTR;

/*
**      FUNCTION -- ��ȡ����������������Ϣ(qualityParaSet.ini�ļ�)
*/
class PARASET_INI_STR{
public:
    char     meterstandard[8];               //����
    char     metertype[24];					 //������
};
typedef PARASET_INI_STR* PARASET_INI_PTR;

/*
**      FUNCTION -- �������� 
*/
class MeterStandard_STR{
public:
    int       id;                   //
    char   name[8];					 //
};
typedef MeterStandard_STR* MeterStandard_PTR;

/*
**      FUNCTION -- ����������(��е�����������)
*/
class MeterType_STR{
public:
    int       id;                   //
    char   desc[24];				//
};
typedef MeterType_STR* MeterType_PTR;

#endif	//BASEDEF_H