#ifndef BASEDEF_H
#define BASEDEF_H

#include "commondefine.h"

#ifndef VERIFY_POINTS
	#define VERIFY_POINTS 8//检定流量点的数量, 一般为4个(大, 中一, 中二, 小), 但客户也可能需要更多
#endif

#ifndef SEP
#define SEP "#SEP#"//分隔符
#endif

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
    char   name[ASCNAME_LEN];		//
};
typedef MeterStandard_STR* MeterStandard_PTR;

/*
**      FUNCTION -- 热量表类型(机械表、超声波表等)
*/
class MeterType_STR{
public:
    int       id;                   //
	char   name[ASCNAME_LEN];				//
	char   desc[DESC_LEN];				//
};
typedef MeterType_STR* MeterType_PTR;

/*
**      FUNCTION -- 制造单位()
*/
class Manufacture_STR{
public:
    int     id;                   //
	char    name[ASCNAME_LEN];
    char    desc[DESC_LEN];				//
};
typedef Manufacture_STR* Manufacture_PTR;

/*
* 检定流量点信息; fp为flow point的头字母
* i 是界面上预先定义的控件顺序
*/

struct flow_point_info_str
{
	qint64 fp_timestamp;//第i流量点的时间戳
	float fp_upperlmt;//第i流量点的上限流量值(2.7m³/h)
	float fp_verify;//第i流量点的检定流量值(2.5m³/h)
	float fp_quantity;//第i流量点的检定水量(50L)
	float fp_freq;//第i流量点的水泵频率(35Hz)
	int fp_valve;//第i流量点的控制阀(大)
	int fp_seq;//第i流量点的检定次序(3)
};
typedef struct flow_point_info_str flow_point_info;

/*
**      质量检定法用到的相关参数值
*/
class Quality_Params
{
public:
	qint64 file_timestamp;//配置文件的时间戳
	//被检热量表的基本信息; m为meter的头字母
	qint64 m_timestamp;//基本信息时间戳
	char m_stand[50];//被检表规格(DN15,DN20,DN25等) 
	char m_type[50];//被检表类型(机械表、超声波表等)
	char m_manufac[100];//制造厂商(德鲁航天, 天罡等)
	int m_grade;//被检表等级(一级,二级,三级等)
	char m_model[50];//被检表规格(DELU-14.17W, SHARKY-475等)
	char m_vcomp[50];//检定机构(山东省计量院)
	char m_vperson[50];//检定员(张三)
	char m_pickcode[50];//采集代码
	float m_nflowpnt;//被检表的常用流量

	flow_point_info fp_info[VERIFY_POINTS];//第i流量点信息
	int total_fp;//有效流量点的数目

	//检定时的控制参数, 全部为布尔型参数, 故前缀以bo_开头
	qint64 bo_timestamp;//布尔值时间戳
	bool bo_autopick;//是否自动采集
	bool bo_total;//是否总量检定
	bool bo_adjerror;//是否调整误差
	bool bo_writenum;//是否写表号
	bool bo_converify;//是否连续检定
	bool bo_resetzero;//是否初值回零
	//其他参数
	qint64 oth_timestamp;//其他参数时间戳
	float sc_flow;//流量安全系数,sc为safe coefficient头字母
	float sc_thermal;//热量安全系数
	int ex_time;//排气时间
};
typedef Quality_Params* QParams_PTR;

#endif	//BASEDEF_H