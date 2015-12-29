#ifndef BASEDEF_H
#define BASEDEF_H

#include <intsafe.h>

/*
** 插入数据库记录成功或失败
*/
#define OPERATE_DB_OK		1	//操作数据库成功
#define OPERATE_DB_FAIL		0	//操作默认数据库失败
#define OPERATE_MYSQL_FAIL	-1	//同时操作SQLite和MySQL时，操作MySQL失败

/*
** 热表检定相关宏定义
*/
#define VALID_YEAR				2 //检表有效期 2年
#define COE_PRECISION			3 //各流量点流量系数(误差)显示到小数点后3位
#define ERR_PRECISION			3 //误差精度保留小数点后3位

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
#define EN_NAME_LEN			24      //英文名字长度
#define ZH_NAME_LEN			50      //中文名字长度

#define METER_QUANTITY		24	    //本检定台可以检表的最大数量

#ifndef VERIFY_POINTS
#define VERIFY_POINTS		4       //检定流量点的数量, 一般为4个(大, 中一, 中二, 小), 但客户也可能需要更多
#endif

#ifndef SEP
#define SEP "#SEP#"//分隔符
#endif

#define TIMEOUT_PIPE_TEMPER    1000    //请求管路温度周期(毫秒)
#define TIMEOUT_STD_TEMPER	   5000    //请求标准温度周期

#define FLOW_SAMPLE_NUM		    10     //计算流速 采样点个数
#define TIMEOUT_FLOW_SAMPLE	    1000   //计算流速 每1秒采样一次天平数值

#define TIMEOUT_BALANCE		200	  //每200毫秒读一次天平数据

#define RESET_ZERO_TIME		24    //等待热表初值回零的时间，单位：秒

#define BALANCE_STABLE_TIME    3000   //等待天平数值稳定时间(水流稳定)，单位：毫秒
#define WAIT_COM_TIME          4000   //热量表串口通讯,等待串口数据的时间，单位：毫秒
#define WATCH_DATA_TIME        3000   //留给操作人员查看界面数据的时间，单位：毫秒
#define RELEASE_PRESS_TIME     2000   //释放管路压力的时间，单位：毫秒
#define CYCLE_TIME             1000   //周期循环时间，单位：毫秒

/* 力创模块发送的电流值不是4000微安,
** 而是1006, 4007, 4008, 4009, 4010等不规则的值, 取折中4008
** 上限流量的电流信号也有这个毛病
*/
#define ELEC_ZERO			   4008   //标准表瞬时流量为0时的电流, mA;
#define ELEC_UPPER			   20008  //标准表瞬时流量为最大时的电流, mA

#define MAX_ERROR              30     //修表时的最大允许误差，单位%。超过此误差代表异常，不允许修表

#define TIMEOUT_STD_INST			500 //请求标准表瞬时流量周期
#define TIMEOUT_STD_ACCUM			200 //请求标准表累积流量周期
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
** 当前运行状态枚举类型
*/
enum now_state
{
	STATE_INIT=1,       //初始状态
	STATE_START_VALUE,  //等待输入初值状态
	STATE_END_VALUE,    //等待输入终值状态
	STATE_READ_COE      //读取流量点系数状态
};

/*
** 控件索引号所对应的流量点枚举类型
*/
enum flow_rate_wdg
{
	FLOW_RATE_BIG=0,    //大流量
	FLOW_RATE_MID_2,	//中二流量
	FLOW_RATE_MID_1,    //中一流量
	FLOW_RATE_SMALL     //小流量
};

#define FLOW_K_NUM 10//标准表标定时的流量-K系数点的个数
#define DIAMETER_NUM 4//一共设置了几个管径的标准表

/*
** 流量的类型
*/
enum flow_type
{
	INST_FLOW_VALUE = 0,
	ACCUM_FLOW_VALUE
};

/*
** 检定方法类型枚举
*/
enum Verify_Method
{
	WEIGHT_METHOD = 0, //质量法
	STANDARD_METHOD    //标准表法
};

/*
** 天平容量枚举，用于区分天平进水管相应的修正系数
*/
enum Balance_Capacity
{
	BALANCE_CAP150 = 0, //150kg天平
	BALANCE_CAP600      //600kg天平
};

/*
** 进入检定状态的类型 0:流量检定；1:热量检定
*/
enum Verify_Type
{
	VTYPE_FLOW = 0, //进入流量检定状态
	VTYPE_HEAT      //进入热量检定状态
};

/*
** 表格列
*/
enum table_columns
{
	COLUMN_METER_NUMBER=0,  //表号列
	COLUMN_FLOW_POINT,	    //流量点
	COLUMN_METER_START,     //表初值列
	COLUMN_METER_END,	    //表终值列
	COLUMN_BAL_START,	    //天平初值
	COLUMN_BAL_END,		    //天平终值
	COLUMN_TEMPER,		    //温度列
	COLUMN_DENSITY,		    //密度列
	COLUMN_STD_VALUE,	    //标准值
	COLUMN_DISP_ERROR,		//示值误差列
	COLUMN_STD_ERROR,		//标准误差列(误差要求)
	COLUMN_READ_NO,		    //读表号列
	COLUMN_READ_DATA,		//读表数据列
	COLUMN_VERIFY_STATUS,	//设置检定状态列
	COLUMN_TOTAL_COUNT,     //总量检定的表格列数
	COLUMN_ADJUST_ERROR=COLUMN_TOTAL_COUNT,	//调整误差列
	COLUMN_MODIFY_METERNO,	//修改表号列
	COLUMN__FLOW_COUNT      //流量检定的表格列数         
};

#define ALGO_ENTHALPY		0 //焓差法
#define ALGO_KCOE			1 //K系数法

#define UNIT_MJ		0 //能量单位 MJ
#define UNIT_KWH	1 //能量单位 kWh

#define INSTALLPOS_IN	0 //安装位置 入口
#define INSTALLPOS_OUT	1 //安装位置 出口 

#define NORMAL_PRESSURE 0.6 //常用供热压力, 单位MPa
#define HIGH_PRESSURE   1.6 //高压供热压力, 单位MPa

#define ENTHALPY_R	461.526 //水的比焓常数, 个人理解为单位质量的水, 其温度变化1K, 所交换的热值(见IAPWS-IF97-Re 水和水蒸气特性v.pdf P5 及http://en.wikipedia.org/wiki/Gas_constant)

#define GRADE_ONE	    0  //1级表
#define GRADE_TWO	    1  //2级表
#define GRADE_THREE 	2  //3级表

#define IMITATION_FLOW_RATE 2.88 //模拟流量时的流速, m3/h

//热量表通讯协议版本号(采集代码)。必须与T_Meter_PickCode的F_ID对应
#define PROTOCOL_VER_COMMON	    0   //通用
#define PROTOCOL_VER_DELU	    1   //德鲁超声波表
#define PROTOCOL_VER_TIANGANG   2   //天罡超声波表
#define PROTOCOL_VER_LICHSONIC 	3   //力创超声波表
#define PROTOCOL_VER_LICHMACH  	4   //力创机械表
#define PROTOCOL_VER_HUIZH  	5   //汇中超声波表
#define PROTOCOL_VER_MAITUO  	6   //迈拓超声波表
#define PROTOCOL_VER_RUINA  	7   //瑞纳超声波表
#define PROTOCOL_VER_GUADA  	8   //光大
#define PROTOCOL_VER_HDLMT  	9   //荷德鲁美特
#define PROTOCOL_VER_ADE	  	10  //航天德鲁

//天平类型
#define BALANCE_TYPE_Satorius   0   //赛多利斯
#define BALANCE_TYPE_SatoriusH  1   //赛多利斯H
#define BALANCE_TYPE_Bizerba    2   //Bizerba(碧彩)
#define BALANCE_TYPE_Mettler    3   //Mettler Toledo

//温度计类型
#define TEMPERATURE_TYPE_METROLOGY  0//计量院
#define TEMPERATURE_TYPE_WEILI		1//唯立
#define TEMPERATURE_TYPE_HUAYI		2//华仪

#define POLY	0xA001//CRC16校验中的生成多项式
#define BYTE_LENGTH 8	  //一个字节的比特数
#define LC_EDA_REG_BYTES		2//力创EDA9150A和EDA9017模块中, 每个寄存器的字节数
#define EDA9150A_ROUTE_BYTES	4//力创EDA9150A模块中, 每个通道对应的字节数
#define EDA9017_ROUTE_BYTES		2//力创EDA9017模块中, 每个通道对应的字节数

#define REGULATE_OPEN_TIME	160  //电动调节阀打开（开度从0至100）所需要的时间，单位：秒
#define REGULATE_CLOSE_TIME	50   //电动调节阀关闭（开度从100至0）所需要的时间，单位：秒
#define REGULATE_FRESH_TIME (REGULATE_OPEN_TIME*10) //电动调节阀开度界面刷新周期，单位：毫秒

/*
** FUNCTION -- 获取下位机端口设置信息(portset.ini文件)
*/
class PortSet_Ini_STR{
public:
    int     waterInNo;  //
    int     bigNo;      //
    int     middle1No;  //
    int     middle2No;  //
    int     smallNo;    //
    int     waterOutNo; //
	int		bigWaterInNo;	//大天平进水阀
	int		smallWaterInNo;	//小天平进水阀
	int		bigWaterOutNo;	//大天平放水阀
	int		smallWaterOutNo;//小天平放水阀
	int		regSmallNo;
	int		regMid1No;
	int		regMid2No;
	int		regBigNo;
	int		regflow5No;
	int		regflow6No;
	int     pumpNo;
	int     version;
};
typedef PortSet_Ini_STR* PortSet_Ini_PTR;

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
    int    id;                   //主键
    char   name[ASCNAME_LEN];	 //规格
	UINT16 quantity;//被检表的最大数量
};
typedef MeterStandard_STR* MeterStandard_PTR;

/*
** FUNCTION -- 制造单位()
*/
class Manufacture_STR{
public:
    int     id;                       //
	char    name[ASCNAME_LEN];
    char    desc[DESC_LEN];			  //
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
	float upper_flow;//上限流量
	float v_flow;//检定流量
	float v_quan;//检定量
	float pump_freq;//水泵频率
	int vale_num;//阀门编号
	int seq;//检测序列号
	int opening; //电动调节阀开度
};
typedef DftDbInfo_STR* DftDbInfo_PTR;

/************************************************************************/
/* 铂电阻 阻值-温度 计算参数                                              */
/************************************************************************/
struct plaParam_STR
{
	float r0;
	float a;
	float b;
	float c;
};
typedef plaParam_STR* plaParam_PTR;
/************************************************************************/
/* 铂电阻的阻值-温度值                                                    */
/************************************************************************/
struct pla_T_R_STR
{
	float tmp;//温度
	float resis;//阻值
};
typedef pla_T_R_STR* pla_T_R_PTR;
/*
** 检定流量点信息; fp为flow point的头字母
** i 是界面上预先定义的控件顺序
*/
struct Flow_Point_Info_STR
{
	float fp_upperlmt;//第i流量点的上限流量值(2.7m³/h)
	float fp_verify;//第i流量点的检定流量值(2.5m³/h)
	float fp_quantity;//第i流量点的检定水量(50L)
	float fp_freq;//第i流量点的水泵频率(35Hz)
	int fp_valve_idx;//第i流量点的控制阀(大)对应的combbox索引
	int fp_valve;//第i流量点的控制阀(大)对应的端口号
	int fp_seq;//第i流量点的检定次序(3)
	int fp_opening; //第i流量点的开度
	int fp_regno; //第i流量点的调节阀对应的端口号
	//int fp_instStdRoute;//第i流量点的瞬时采集设备的通道号
	//int fp_accumStdRoute;//第i流量点的累积采集设备的通道号
};
typedef struct Flow_Point_Info_STR Flow_Point_Info;

/*
** 检定用到的相关参数
** 包括质量法流量检定、标准表法流量检定、质量法总量检定、标准表法总量检定，共用该结构
*/
class Verify_Params_STR
{
public:
	//被检热量表的基本信息; m为meter的头字母
	int m_stand;//被检表规格(DN15,DN20,DN25等) 
	int m_maxMeters;//被检表的最大数量
	int m_manufac;//制造厂商(德鲁航天, 天罡等)
	int m_grade;//被检表等级(一级,二级,三级等)
	int m_model;//被检表型号(DELU-14.17W, SHARKY-475等)
	int m_vcomp;//检定机构(山东省计量院)
	int m_vperson;//检定员(张三)
	int m_cperson;//核检员(张三)
	int m_pickcode;//采集代码
	int m_nflowpnt;//被检表的常用流量
	//QString m_version;//当前版本号
	QString m_temper;//当前温度  单位摄氏度
	QString m_humidity;//当前湿度 单位百分比
	QString m_airpress;//当前大气压力	单位Pa
	//QString m_instStdDevNo;//瞬时流量采集设备的地址
	//QString m_accumStdDevNo;//累积流量采集设备的地址
	Flow_Point_Info fp_info[VERIFY_POINTS];//第i流量点信息
	int total_fp;//有效流量点的数目

	//检定时的控制参数, 全部为布尔型参数, 故前缀以bo_开头
	bool bo_autopick;//是否自动采集
	bool bo_adjerror;//是否调整误差
	bool bo_writenum;//是否写表号
	bool bo_converify;//是否连续检定
	bool bo_resetzero;//是否初值回零
	bool bo_repeatverify;//是否重复检测
	//其他参数
	float sc_flow;//流量安全系数,sc为safe coefficient头字母
	float sc_thermal;//热量安全系数
	int ex_time;//排气时间
	UINT32 meterNo;//起始表号
	float Q3BiQ1;
	float Q3;
	float Q2BiQ1;
};
typedef Verify_Params_STR* Verify_Params_PTR;

typedef struct ComInfo_Struct
{
	QString portName; //串口名
	int     baudRate; //波特率
	int     dataBit;  //数据位
	int     parity;   //奇偶校验
	int     stopBit;  //停止位
}ComInfoStruct;

/*
** FUNCTION -- 流量检定结果记录表（包括质量法和标准表法）
*/
class Flow_Verify_Record_STR{
public:
    int     id;                   
	char	timestamp[TIMESTAMP_LEN];
	char    meterNo[METERNO_LEN];
	INT16   flowPointIdx;
	float   flowPoint;      //流量(m3/h)
	INT16   methodFlag;     //检定方法标志(0:质量法 1:标准表法)
	float	meterValue0;	//热量表初值(体积)，单位L
	float	meterValue1;	//热量表终值(体积)，单位L
	float	balWeight0;		//天平初值(重量)，单位kg，质量法使用
	float   balWeight1;		//天平终值(重量)，单位kg，质量法使用
	float	stdMeterV0;		//标准表初值(体积)，单位L，标准表法使用
	float   stdMeterV1;		//标准表终值(体积)，单位L，标准表法使用
	float	pipeTemper;		//分配到每个表位的温度
	float	density;		//密度(kg/L)
	float	stdValue;		//经过修正的标准值
	float	dispError;		//示值误差
	float	stdError;		//要求误差(合格标准)
	INT16   result;			//检定结果(1:合格  0:不合格)
	INT16	meterPosNo;		//表位号
	int	    model;			//表型号
	int  	standard;		//表规格
	int	    pickcode;		//采集代码
	int	    manufactDept;	//制造单位
	int	    verifyDept;		//送检单位
	INT16	grade;	        //计量等级
	int	    verifyPerson;	//检定员
	int	    checkPerson;	//核验员
	int	    deviceInfoId;	//检定装置设备信息ID
	char	verifyDate[DATE_LEN];	//检定日期（'2014-07-25'）
	char	validDate[DATE_LEN];	//检表结果有效期（'2014-07-25'）
	float	envTemper;		//环境温度
	float	envHumidity;	//环境湿度
	float	airPress;		//大气压力
	char	certNo[16];		//检定证书编号
	float	flowcoe;		//流量系数
	char	bak2[24];		//备用域2
	char	bak3[24];		//备用域3
	char	bak4[24];		//备用域4
};
typedef Flow_Verify_Record_STR* Flow_Verify_Record_PTR;

/*
** FUNCTION -- 总量检定结果记录表（包括质量法和标准表法）
*/
class Total_Verify_Record_STR{
public:
    int     id;                   
	char	timestamp[TIMESTAMP_LEN];
	char    meterNo[METERNO_LEN];
	INT16   flowPointIdx;
	float   flowPoint;      //流量(m3/h)
	INT16   methodFlag;     //检定方法标志(0:质量法 1:标准表法)
	float	meterValue0;	//热量表初值(热量)，单位kwh
	float	meterValue1;	//热量表终值(体积)，单位kwh
	float	balWeight0;		//天平初值(重量)，单位kg，质量法使用
	float   balWeight1;		//天平终值(重量)，单位kg，质量法使用
	float	stdMeterV0;		//标准表初值(热量)，单位kwh，标准表法使用
	float   stdMeterV1;		//标准表终值(热量)，单位kwh，标准表法使用
	float	inSlotTemper;	//入口标准温度
	float	outSlotTemper;	//出口标准温度
	float	pipeTemper;		//分配到每个表位的温度
	float	density;		//密度(kg/L)
	float	stdValue;		//经过修正的标准值
	float	dispError;		//示值误差
	float	stdError;		//要求误差(合格标准)
	INT16   result;			//检定结果(1:合格  0:不合格)
	INT16	meterPosNo;		//表位号
	int	    model;			//表型号
	int  	standard;		//表规格
	int	    pickcode;		//采集代码
	int	    manufactDept;	//制造单位
	int	    verifyDept;		//送检单位
	INT16	grade;	        //计量等级
	int	    verifyPerson;	//检定员
	int	    checkPerson;	//核验员
	int	    deviceInfoId;	//检定装置设备信息ID
	char	verifyDate[DATE_LEN];	//检定日期（'2014-07-25'）
	char	validDate[DATE_LEN];	//检表结果有效期（'2014-07-25'）
	float	envTemper;		//环境温度
	float	envHumidity;	//环境湿度
	float	airPress;		//大气压力
	char	certNo[16];		//检定证书编号
	float	totalcoe;		//总量系数
	char	bak2[24];		//备用域2
	char	bak3[24];		//备用域3
	char	bak4[24];		//备用域4
};
typedef Total_Verify_Record_STR* Total_Verify_Record_PTR;

/*
** FUNCTION -- 水表检定结果记录表（包括质量法和标准表法）
*/
class Water_Verify_Record_STR{
public:
    int     id;                   
	char	timestamp[TIMESTAMP_LEN];
	char    meterNo[METERNO_LEN];
	INT16   flowPointIdx;
	float   flowPoint;      //流量(m3/h)
	INT16   methodFlag;     //检定方法标志(0:质量法 1:标准表法)
	float	meterValue0;	//热量表初值(体积)，单位L
	float	meterValue1;	//热量表终值(体积)，单位L
	float	balWeight0;		//天平初值(重量)，单位kg，质量法使用
	float   balWeight1;		//天平终值(重量)，单位kg，质量法使用
	float	stdMeterV0;		//标准表初值(体积)，单位L，标准表法使用
	float   stdMeterV1;		//标准表终值(体积)，单位L，标准表法使用
	float	pipeTemper;		//分配到每个表位的温度
	float	density;		//密度(kg/L)
	float	stdValue;		//经过修正的标准值
	float	dispError;		//示值误差
	float	stdError;		//要求误差(合格标准)
	INT16   result;			//检定结果(1:合格  0:不合格)
	INT16	meterPosNo;		//表位号
	int	    model;			//表型号
	int  	standard;		//表规格
	int	    pickcode;		//采集代码
	int	    manufactDept;	//制造单位
	int	    verifyDept;		//送检单位
	INT16	grade;	        //计量等级
	int	    verifyPerson;	//检定员
	int	    checkPerson;	//核验员
	int	    deviceInfoId;	//检定装置设备信息ID
	char	verifyDate[DATE_LEN];	//检定日期（'2014-07-25'）
	char	validDate[DATE_LEN];	//检表结果有效期（'2014-07-25'）
	float	envTemper;		//环境温度
	float	envHumidity;	//环境湿度
	float	airPress;		//大气压力
	char	certNo[16];		//检定证书编号
	float	flowcoe;		//流量系数
	float   waterPress;		//水压
	float	Q3BiQ1;
	float	Q3;
	float	Q2BiQ1;
	char	bak1[24];		//备用域1
	char	bak2[24];		//备用域2
	char	bak3[24];		//备用域3
};
typedef Water_Verify_Record_STR* Water_Verify_Record_PTR;

/*
** FUNCTION -- V_Flow_Verify_Record, 对应视图V_Flow_Verify_Record的结构
*/
class V_Flow_Verify_Record_STR : public Flow_Verify_Record_STR
{
public:
	char m_model_en[EN_NAME_LEN];				//表型号英文
	char m_Model_zh[ZH_NAME_LEN];				//表型号中文                   
	char m_standard[ASCNAME_LEN];				//表规格DN15,DN20等                  
	char m_type_en[EN_NAME_LEN];				//表种类机械表，超声波表的英文名
	char m_type_zh[ZH_NAME_LEN];				//表种类机械表，超声波表的中文名             
	char m_manufacturer_en[EN_NAME_LEN];		//制造厂商，英文名
	char m_manufacturer_zh[ZH_NAME_LEN];		//制造厂商，中文名         
	char m_vfy_dept_en[EN_NAME_LEN];			//检验单位，英文名
	char m_vfy_dept_zh[ZH_NAME_LEN];			//检验单位，中文名                 
	char m_vfy_person[ZH_NAME_LEN];				//检验员的中文名  
	char m_chk_person[ZH_NAME_LEN];				//核检员的中文名  
	char m_device_name[ZH_NAME_LEN];			//检定装置名称，中文
	char m_device_no[EN_NAME_LEN];				//检定装置序列号
	char m_device_model[EN_NAME_LEN];			//检定装置型号编码
	char m_dev_manufacturer[ZH_NAME_LEN];		//检定装置生产商，中文
	char m_device_grade[EN_NAME_LEN];			//检定装置准确度等级
	char m_measure_range[EN_NAME_LEN];			//检定装置的测量范围
	char m_cert_no[EN_NAME_LEN];				//检定装置的证书编号
	char m_verify_rule[EN_NAME_LEN];			//检定规程编号("JJG225-2001")
	char m_device_valid_date[DATE_LEN];			//标准装置有效期('2014-08-07')
	char m_cert_valid_date[DATE_LEN];			//证书有效期('2014-08-07')
	char m_rule_valid_date[DATE_LEN]; 			//计量标准考核证书有效期('2014-08-07')
};
typedef V_Flow_Verify_Record_STR* V_Flow_Verify_Record_PTR;

/*
** FUNCTION -- 获取数据库配置信息(databasepara.ini文件)
*/
class DatabasePara_STR{
public:
    int     type;                 //数据库类型
    char    hostname[24];    	  //主机名/ip地址
	char    dbname[24];           //数据库名,如dbs1
	char    username[24];         //用户名
	char    password[24];         //密码
};
typedef DatabasePara_STR* DatabasePara_PTR;

/*
** FUNCTION -- 铂电阻检定结果记录, 对应T_Platinium_Verify_Record
*/
class T_Platinium_Verify_Record_STR
{
public:
		int F_ID;							//id
		char timestamp[TIMESTAMP_LEN];		//时间戳（'yyyy-MM-dd HH:mm:ss.zzz')
		int F_CompOrParam;					//比较法或参数法, 0-比较法, 1-参数法
		int F_PlaManufactDept;				//被检铂电阻制造单位，外键(T_Manufacture_Dept.F_ID)
		int F_Standard;						//表规格(DN15/DN20/DN25)，外键(T_Meter_Standard.F_ID)
		int F_Model;						//表型号，外键(T_Meter_Model.F_ID)
		int F_ManufactDept;					//热量表制造单位，外键(T_Manufacture_Dept.F_ID)
		int F_VerifyDept;					//送检单位，外键(T_Verify_Dept.F_ID)
		int F_CheckPerson;					//检定员，外键(T_User_Def_Tab.F_ID)
		int F_VerifyPerson;					//核验员，外键(T_User_Def_Tab.F_ID)
		float F_MinTmpDiff;					//最小温差, 参数
		float F_TmpDiff;					//检测温差
		float F_StdInRresis;				//标准温度计进口电阻值
		float F_StdOutRresis;				//标准温度计出口电阻值
		float F_StdInTmp;					//标准温度计进口电温度
		float F_StdOutTmp;					//标准温度计出口电温度
		char F_PlaSerial[ZH_NAME_LEN];		//被检铂电阻序列号
		float F_PlaInRresis;				//被检铂电阻进口电阻值
		float F_PlaOutRresis;				//被检铂电阻出口电阻值
		float F_PlaInTmp;					//被检铂电阻进口温度值
		float F_PlaOutTmp;					//被检铂电阻出口温度值
		float F_PlaTmpDiffErr;				//被检铂电阻进出口温差的误差
		float F_PlaParamR0;					//被检铂电阻0℃电阻值
		float F_PlaCoeA;					//被检铂电阻系数A
		float F_PlaCoeB;					//被检铂电阻系数B
		float F_PlaCoeC;					//被检铂电阻系数C
		float F_InErr;						//被检铂电阻进口误差(℃)
		float F_OutErr;						//被检铂电阻进口误差(℃)
		float F_InErrLimit;					//被检铂电阻进口误差限(℃)
		float F_OutErrLimit;				//被检铂电阻进口误差限(℃)
		float F_DeltaErrLimit;				//被检铂电阻进出口温差的误差限(%)
		float F_MaxErrPoint;				//最大误差点
		char  F_StdModel[ZH_NAME_LEN];		//标准铂电阻型号(唯力，华仪等)
		int F_verify_seq;					//第几次检定
		int	F_TmpIndex;						//温差点/温差点索引
};
typedef T_Platinium_Verify_Record_STR* T_Platinum_Verify_Record_PTR;


/*
** FUNCTION -- 计算器检定结果记录, 对应T_Calc_Verify_Record
*/
class Calc_Verify_Record_STR{
public:
    int     id;                   
	char	timestamp[TIMESTAMP_LEN];
	char    meterNo[METERNO_LEN];
	INT16   deltaTidx;      //温差点索引
	int  	standard;		//表规格
	int	    model;			//表型号
	INT16	grade;	        //计量等级
	int	    manufactDept;	//制造单位
	int	    verifyDept;		//送检单位
	int	    verifyPerson;	//检定员
	float   maxT;			//最高温度
	float   minT;
	float   maxDeltaT;
	float   minDeltaT;
	int     algorithm;      //算法(0:焓差法；1:K系数法)
	int     installPos;     //安装位置(0:进口； 1:出口)
	int     energyUnit;     //热量单位(0:MJ；1:kwh)
	float   inTemper;
	float   outTemper;
	float   inR;
	float   outR;
	float   recomVolume;
	float   analogVolume;
	float   kCoe;
	float   theoryEnergy;
	float   meterE0;
	float   meterE1;
	float   dispError;
	float   stdError;
	int     result;         //检定结果(1:合格  0:不合格)
	char	bak2[24];		//备用域2
	char	bak3[24];		//备用域3
	char	bak4[24];		//备用域4
};
typedef Calc_Verify_Record_STR* Calc_Verify_Record_PTR;

class Cmb_Verify_Record_STR{
public:
	int F_ID;
	char F_TimeStamp[TIMESTAMP_LEN];//时间戳（'yyyy-MM-dd HH:mm:ss.zzz')
	char F_MeterNo[METERNO_LEN];//表号(14位数字: 6 + 8)
	int F_Standard;//表规格(DN15/DN20/DN25)，外键(T_Meter_Standard.F_ID)
	int F_Model;//表型号，外键(T_Meter_Model.F_ID)
	int F_PickCode;//采集代码,外键
	int F_Grade;//计量等级（1,2,3）
	int F_ManufactDept;//制造单位，外键(T_Manufacture_Dept.F_ID)
	int F_VerifyDept;//送检单位，外键(T_Verify_Dept.F_ID)
	int F_VerifyPerson;//检定员，外键(T_User_Def_Tab.F_ID)
	float F_DeltaTemp;//温差(K)
	float F_VerifyVolume;//检定量(L)
	float F_DeltaTempMin;//最小温差(K)
	int F_InstallPos;//安装位置(0:进口；1:出口)
	int F_HeatUnit;//热量单位(1:kWh; 0:MJ)
	float F_StdTempIn;//入口温度-标准温度计(℃)
	float F_StdTempOut;//出口温度-标准温度计(℃)
	float F_StdResistIn;//入口电阻-标准温度计(Ω)
	float F_StdResistOut;//出口电阻-标准温度计(Ω)
	float F_Kcoe;//K系数
	float F_StdValue;//理论值(热量，kwh)
	float F_MeterV0;//热量表初值(体积)，单位L
	float F_MeterV1;//热量表终值(体积)，单位L
	float F_MeterE0;//热量表初值(热量)，单位kWh
	float F_MeterE1;//热量表终值(热量)，单位kWh
	float F_DispError;//示值误差，单位%
	float F_StdError;//要求误差(合格标准),单位%
	int F_Result;//检定结果(1：合格，0：不合格)
	char F_Bak2[ASCNAME_LEN];//备用域2
	char F_Bak3[ASCNAME_LEN];//备用域3
	char F_Bak4[ASCNAME_LEN];//备用域4
};
typedef Cmb_Verify_Record_STR* Cmb_Verify_Record_PTR;

class PIDDataStr
{
public:
	PIDDataStr()
	{
		pid_timestamp.clear();
		pid_maxRate = 0;
		pid_targetRate = 0;
		pid_currentRate = 0;
		pid_currentError = 0;
		pid_regularNo = 0;
		pid_waitTime = 0;
		pid_currentDegree = 0;
		pid_gainTargetRate = false;
		pid_nowErrorPercent = 0;
		pid_Kp = 0;
		pid_Ki = 0;
		pid_Kd = 0;
		pid_P = 0;
		pid_I = 0;
		pid_D = 0;
		pid_adjust_valve = false;//当前正在调节电动阀门
		pid_adjust_pump  = false;//当前正在调节水泵频率
		pid_pump_Kp = 0;
		pid_pump_Ki = 0;
		pid_pump_Kd = 0;
		pid_pump_P = 0;
		pid_pump_I = 0;
		pid_pump_D = 0;
		pid_pump_waitTime = 0;
		pid_pumpFreq = 0;	
	};

	QString pid_timestamp;
	float   pid_maxRate;
	float   pid_targetRate;
	float   pid_currentRate;
	float   pid_currentError;
	int		pid_regularNo;
	int		pid_waitTime;
	int     pid_currentDegree;
	bool    pid_gainTargetRate;
	float   pid_nowErrorPercent;
	float   pid_Kp;
	float   pid_Ki;
	float	pid_Kd;
	float   pid_P;
	float   pid_I;
	float	pid_D;

	bool pid_adjust_valve;//当前正在调节电动阀门
	bool pid_adjust_pump ;//当前正在调节水泵频率
	float   pid_pump_Kp;
	float   pid_pump_Ki;
	float	pid_pump_Kd;
	float   pid_pump_P;
	float   pid_pump_I;
	float	pid_pump_D;
	int		pid_pump_waitTime;

	int		pid_pumpFreq;
};
typedef PIDDataStr* PIDDataPtr;
#endif	//BASEDEF_H