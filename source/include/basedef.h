#ifndef BASEDEF_H
#define BASEDEF_H

/*
**      FUNCTION -- 获取下位机端口设置信息(portset.ini文件)
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
**      FUNCTION -- 获取质量法参数设置信息(qualityParaSet.ini文件)
*/
class PARASET_INI_STR{
public:
    char     meterstandard[8];               //表规格
    char     metertype[24];					 //表类型
};
typedef PARASET_INI_STR* PARASET_INI_PTR;

/*
**      FUNCTION -- 获取主机-从机设置信息(masterslaveset.ini文件)
*/
class MASTERSLAVE_INI_STR{
public:
    int     netmode;				//0:本地模式；1:网络模式
    int     hostflag;				//0:从机；1:主机
	char	mastername[20];			//主机 机器名
	char	masterIP[20];			//主机 IP地址
	char	slave1name[20];			//从机1 机器名
	char	slave1IP[20];			//从机1	IP地址
	char	slave2name[20];			//从机2 机器名
	char	slave2IP[20];			//从机2	IP地址
	char	slave3name[20];			//从机3 机器名
	char	slave3IP[20];			//从机3	IP地址
	char	slave4name[20];			//从机4 机器名
	char	slave4IP[20];			//从机4	IP地址
};
typedef MASTERSLAVE_INI_STR* MASTERSLAVE_INI_PTR;

/*
**      FUNCTION -- 热量表规格(DN15,DN20,DN25等) 
*/
class MeterStandard_STR{
public:
    int       id;                   //
    char   name[8];					 //
};
typedef MeterStandard_STR* MeterStandard_PTR;

/*
**      FUNCTION -- 热量表类型(机械表、超声波表等)
*/
class MeterType_STR{
public:
    int       id;                   //
    char   desc[24];				//
};
typedef MeterType_STR* MeterType_PTR;

/*
**      FUNCTION -- 制造单位()
*/
class Manufacture_STR{
public:
    int       id;                   //
    char   desc[60];				//
};
typedef Manufacture_STR* Manufacture_PTR;

#endif	//BASEDEF_H