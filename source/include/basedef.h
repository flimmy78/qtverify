#ifndef BASEDEF_H
#define BASEDEF_H

#include <intsafe.h>

/*
** 变量长度宏定义                                                       
*/
#define FILENAME_LENGTH		100		//文件名(全路径)长度
#define ASCNAME_LEN			24		//数据库表中代码域的长度
#define DESC_LEN			60		//数据库表中描述域的长度
#define TIMESTAMP_LEN	    24      //数据库中timestamp类型对应的字符串长度'2014-08-08 08:30:30.666'
#define DATE_LEN            12      //数据库中date类型对应的字符串长度'2014-08-08'
#define METERNO_LEN			16      //"表号"的字符串长度
#define NUMPREFIX_LEN		6		//"表号"的前缀长度。6位前缀

#define METER_QUANTITY		20	   //本检定台可以检表的最大数量

#ifndef VERIFY_POINTS
#define VERIFY_POINTS		4  //检定流量点的数量, 一般为4个(大, 中一, 中二, 小), 但客户也可能需要更多
#endif

#ifndef SEP
#define SEP "#SEP#"//分隔符
#endif

#define TIMEOUT_TEMPER		1000  //每1秒钟请求一次温度值

#define FLOW_SAMPLE_NUM		10    //计算流速 采样点个数
#define TIMEOUT_FLOW_SAMPLE	1000  //计算流速 每1秒采样一次天平数值

#define TIMEOUT_BALANCE		200	  //每200毫秒读一次天平数据

#define RESET_ZERO_TIME		20    //等待热表初值回零的时间，单位：秒
/*
** 被检表类型枚举            
*/
enum metertype
{
	DN15=0,
	DN20,
	DN25
};

/*
** FUNCTION -- 获取下位机端口设置信息(portset.ini文件)
*/
class PortSet_Ini_STR{
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
	int     version;
};
typedef PortSet_Ini_STR* PortSet_Ini_PTR;

/*
** FUNCTION -- 获取质量法参数设置信息(qualityParaSet.ini文件)
*/
class ParaSet_Ini_STR{
public:
    char     meterstandard[8];               //表规格
    char     metertype[24];					 //表类型
};
typedef ParaSet_Ini_STR* ParaSet_Ini_PTR;

/*
** FUNCTION -- 获取主机-从机设置信息(masterslaveset.ini文件)
*/
class MasterSlave_Ini_STR{
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
typedef MasterSlave_Ini_STR* MasterSlave_Ini_PTR;

/*
** FUNCTION -- 热量表规格(DN15,DN20,DN25等) 
*/
class MeterStandard_STR{
public:
    int       id;                   //主键
    char   name[ASCNAME_LEN];		//规格
	UINT16 quantity;//被检表的最大数量
};
typedef MeterStandard_STR* MeterStandard_PTR;

/*
** FUNCTION -- 热量表类型(机械表、超声波表等)
*/
class MeterType_STR{
public:
    int    id;                   //
	char   name[ASCNAME_LEN];	 //
	char   desc[DESC_LEN];	     //
};
typedef MeterType_STR* MeterType_PTR;

/*
** FUNCTION -- 制造单位()
*/
class Manufacture_STR{
public:
    int     id;                   //
	char    name[ASCNAME_LEN];
    char    desc[DESC_LEN];				//
	char    numprefix[NUMPREFIX_LEN]; //该厂家的表号前缀
};
typedef Manufacture_STR* Manufacture_PTR;

/*
** FUNCTION -- 各规格热表的默认检定参数()
*/
class DftDbInfo_STR
{
public:
	int id;//主键
	int stand_id;//外键,表规格的id
	float n_flow;//常用流量点
	float upper_flow;//检定流量点
	float v_flow;//检定量
	float v_quan;//水泵频率
	float pump_freq;//水泵频率
	int vale_num;//阀门编号
	int seq;//检测序列号
};
typedef DftDbInfo_STR* DftDbInfo_PTR;

/*
** FUNCTION -- 检定结果记录表（质量法）
*/
class Record_Quality_STR{
public:
    int     id;                   
	char	timestamp[TIMESTAMP_LEN];
	char    meterNo[METERNO_LEN];
	INT16   flowPointIdx;
	float   flowPoint;         //流量(m3/h)
	INT16   totalFlag;         //总量检定标志(1:总量检定  0:分量检定)
	float	meterValue0;
	float	meterValue1;
	float	meterDeltaV;
	float	balWeight0;
	float   balWeight1;
	float   balDeltaW;
	float	inSlotTemper;	//恒温槽入口温度
	float	outSlotTemper;	//恒温槽出口温度
	float	pipeTemper;		//管路温度
	float	density;		//密度(kg/L)
	float	stdValue;		//经过修正的标准值
	float	dispError;		//示值误差
	float	stdError;		//要求误差(合格标准)
	INT16   result;			//检定结果(1:合格  0:不合格)
	INT16	meterPosNo;		//表位号
	int	model;			    //表型号
	int	standard;		    //表规格
	int	meterType;		    //表类型
	int	manufactDept;	    //制造单位
	int	verifyDept;		    //送检单位
	INT16	grade;	        //计量等级
	int	verifyPerson;	    //检定员
	int	checkPerson;	    //核验员
	char	date[DATE_LEN];	//检定日期（'2014-07-25'）
	float	envTemper;		//环境温度
	float	envHumidity;	//环境湿度
	float	airPress;		//大气压力
	char	validDate[DATE_LEN];	//检定结果有效期('2015-07-25')
	INT32	recordNumber;	//检定记录证书编号
};
typedef Record_Quality_STR* Record_Quality_PTR;

/*
** 检定流量点信息; fp为flow point的头字母
** i 是界面上预先定义的控件顺序
*/
struct Flow_Point_Info_STR
{
	qint64 fp_timestamp;//第i流量点的时间戳
	float fp_upperlmt;//第i流量点的上限流量值(2.7m³/h)
	float fp_verify;//第i流量点的检定流量值(2.5m³/h)
	float fp_quantity;//第i流量点的检定水量(50L)
	float fp_freq;//第i流量点的水泵频率(35Hz)
	int fp_valve;//第i流量点的控制阀(大)
	int fp_seq;//第i流量点的检定次序(3)
};
typedef struct Flow_Point_Info_STR Flow_Point_Info;

/*
** 质量检定法用到的相关参数值
*/
class Quality_Params_STR
{
public:
	qint64 file_timestamp;//配置文件的时间戳
	//被检热量表的基本信息; m为meter的头字母
	qint64 m_timestamp;//基本信息时间戳
	int m_stand;//被检表规格(DN15,DN20,DN25等) 
	int m_maxMeters;//被检表的最大数量
	int m_type;//被检表类型(机械表、超声波表等)
	int m_manufac;//制造厂商(德鲁航天, 天罡等)
	int m_grade;//被检表等级(一级,二级,三级等)
	int m_model;//被检表型号(DELU-14.17W, SHARKY-475等)
	int m_vcomp;//检定机构(山东省计量院)
	int m_vperson;//检定员(张三)
	int m_pickcode;//采集代码
	int m_nflowpnt;//被检表的常用流量

	Flow_Point_Info fp_info[VERIFY_POINTS];//第i流量点信息
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
typedef Quality_Params_STR* Quality_Params_PTR;

typedef struct ComInfo_Struct
{
	QString portName; //串口名
	int     baudRate; //波特率
	int     dataBit;  //数据位
	int     parity;   //奇偶校验
	int     stopBit;  //停止位
}ComInfoStruct;

#endif	//BASEDEF_H