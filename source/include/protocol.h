#ifndef PROTOCOL_H
#define PROTOCOL_H

#ifdef PROTOCOL_DLL
#  ifdef WIN32
#  define PROTOCOL_EXPORT __declspec(dllexport)
#  else
#  define PROTOCOL_EXPORT
#  endif
#else
#  ifdef WIN32
#  define PROTOCOL_EXPORT __declspec(dllimport)
#  else
#  define PROTOCOL_EXPORT
#  endif
#endif

#include <intsafe.h>
#include <QtCore/QThread>
#include <QtCore/QMap>
#include "algorithm.h"

//协议基类
class  CProtocol
{
public:
	CProtocol();
	~CProtocol();

	float calc(float a, float b);

private:

};


//温度采集协议 begin
#define DATA_WIDTH			4  //温度值字符串长度 4 
#define DATA_PRECISION		1  //温度值精度，一位小数

#define ADDR_FIX			0x80
#define ADDR_FIRST			0x01
#define ADDR_CODE_FIRST		(ADDR_FIX + ADDR_FIRST)
#define READ_CODE			0x52


#define PV_STATE		0x00
#define SV_STATE		0x01
#define MV_STATE		0x02
#define WARN_STATE      0x03
#define PARA_STATE      0x04
#define CHECK_STATE     0x05


typedef struct  
{
	INT16 pv;		//测量值PV，
	INT16 sv;		//给定值SV
	INT8  mv;       //输出值MV
	INT8 warn;	    //报警状态
	INT16 para;     //所读写参数值
	INT16 cs;	//校验码
}Temp_Frame_Struct;

class PROTOCOL_EXPORT TempProtocol : public CProtocol
{

	QString m_tempStr;
	QByteArray m_sendBuf;

public:
	TempProtocol();
	~TempProtocol();

	Temp_Frame_Struct *m_tempFrame;

public slots:
	bool readTemperComBuffer(QByteArray tmp);
	INT16 CountCheck(Temp_Frame_Struct *pFrame);
	void analyseFrame();
	void makeSendBuf();

	QString getTempStr();
	QByteArray getSendBuf();

private:

};
//温度采集协议 end


//天平协议 begin
#define    ASCII_CR				0x0D	//回车键
#define    ASCII_LF				0x0A	//换行键

class PROTOCOL_EXPORT BalanceProtocol : public CProtocol
{

public:
	BalanceProtocol();
	~BalanceProtocol();

	float m_balValue;
	float m_lastValue;
	unsigned int m_count;

public slots:
	bool readBalanceComBuffer(QByteArray tmp);
	float getBalanceValue();

private:
};
//天平协议 end

//下位机控制协议 begin
#define		CTRL_START_CODE		0x69		//起始码
#define		CTRL_END_CODE		0x16		//结束码
#define		CTRL_FUNC_RELAY		0x01		//功能码-继电器控制
#define		CTRL_FUNC_REGULATE  0x02		//功能码-调节阀控制
#define     CTRL_FUNC_QUERY		0x03		//功能码-查询
#define     CTRL_FUNC_BALANCE	0x04		//功能码-获取天平重量

#define		CTRL_START_STATE	0x00
#define		CTRL_FUNC_STATE		0x01
#define		CTRL_DATA_STATE		0x02
#define		CTRL_CS_STATE       0x03
#define		CTRL_END_STATE      0x04

#define		DATA_LENGTH			55  //数据区字节个数(最多55个)
#define		RELAY_DATA_LENGTH	5	//继电器控制 数据区字节个数
#define		REGU_DATA_LENGTH	3   //调节阀控制 数据区字节个数
#define     BAL_DATA_LENGTH		22	//天平	数据区字节个数

typedef struct  
{
	UINT8 startCode;	//起始码
	UINT8 funcCode;		//功能码
	UINT8 data[DATA_LENGTH];  //数据区
	UINT8 cs;	    //校验码
	UINT8 endCode;      //结束码
}NewCtrl_Frame_Struct;

#define NEW_CTRL_VERSION  0  //新控制板协议版本号 有反馈
#define OLD_CTRL_VERSION  1  //老控制板协议版本号 无反馈
#define LICH_CTRL_VERSION 2  //力创控制板协议版本号 有反馈

/*
** 控制协议基类
*/
class PROTOCOL_EXPORT CtrlProtocol : public CProtocol
{
public:
	CtrlProtocol();
	~CtrlProtocol();

	QByteArray m_sendBuf;

public slots:
	//pure virtual
	virtual void makeFrameOfCtrlRelay(UINT8 portno, bool status) = 0;
	virtual void makeFrameOfCtrlRegulate(UINT8 portno, UINT16 degree) = 0;
	virtual void makeFrameOfCtrlQuery() = 0;
	virtual void makeFrameOfCtrlWaterPump(UINT8 portno, bool status) = 0;
	virtual void makeFrameOfSetDriverFreq(int freq) = 0;
	virtual UINT8 readCtrlComBuffer(QByteArray tmp) = 0;
	virtual void analyseFrame() = 0;

	//virtual
	virtual QByteArray getSendBuf();

private:
};

//新控制板协议类 对应协议类型 
class PROTOCOL_EXPORT NewCtrlProtocol : public CtrlProtocol
{
	NewCtrl_Frame_Struct *m_ctrlFrame;
	float m_balValue;

public:
	NewCtrlProtocol();
	~NewCtrlProtocol();

public slots:
	//pure virtual
	virtual void makeFrameOfCtrlRelay(UINT8 portno, bool status);
	virtual void makeFrameOfCtrlRegulate(UINT8 portno, UINT16 degree);
	virtual void makeFrameOfCtrlQuery();
	virtual void makeFrameOfCtrlWaterPump(UINT8 portno, bool status);
	virtual void makeFrameOfSetDriverFreq(int freq);
	virtual UINT8 readCtrlComBuffer(QByteArray tmp);
	virtual void analyseFrame();

	//virtual
	virtual UINT8 CountCheck(NewCtrl_Frame_Struct *pFrame);
	virtual NewCtrl_Frame_Struct* getConFrame();
	virtual float getBalanceValue();
};


//老控制板协议类 对应协议类型
class PROTOCOL_EXPORT OldCtrlProtocol : public CtrlProtocol
{
public:
	OldCtrlProtocol();
	~OldCtrlProtocol();

	QMap <int, UINT8> portCloseMap; //闭合继电器
	QMap <int, UINT8> portOpenMap;  //断开继电器
	QMap <UINT8, UINT8> regPortMap; //调节阀端口号

	public slots:
	//pure virtual
	virtual void makeFrameOfCtrlRelay(UINT8 portno, bool status);
	virtual void makeFrameOfCtrlRegulate(UINT8 portno, UINT16 degree);
	virtual void makeFrameOfCtrlQuery();
	virtual void makeFrameOfCtrlWaterPump(UINT8 portno, bool status);
	virtual void makeFrameOfSetDriverFreq(int freq);
	virtual UINT8 readCtrlComBuffer(QByteArray tmp);
	virtual void analyseFrame();

	//virtual
	virtual void makeFrameOfCtrlPressPump(bool status); //打压泵 暂时不用
};

//下位机控制协议 end

//热量表通讯协议 begin
#define     METER_WAKEUP_CODE_NUM		200     //唤醒码个数
#define     METER_PREFIX_CODE_NUM		4       //前导字节个数

#define		METER_WAKEUP_CODE	        0xFF	//唤醒码
#define		METER_PREFIX_CODE	        0xFE	//前导字节
#define		METER_START_CODE	        0x68	//起始符
#define		METER_TYPE_ASK_CODE		    0x20	//仪表类型 超声表 请求
#define		METER_TYPE_ANSWER_CODE	    0x25	//仪表类型 超声表 响应
#define     METER_ADDR_CODE		        0xAA	//广播地址
#define     METER_CTRL_CODE		        0x01	//控制码
#define     METER_END_CODE		        0x16	//结束符

#define		STATE_METER_START		0x00
#define		STATE_METER_TYPE		0x01
#define		STATE_METER_ADDR		0x02
#define		STATE_METER_CTRL		0x03
#define		STATE_METER_DATALEN		0x04
#define		STATE_METER_DATAID		0x05
#define		STATE_METER_SN			0x06
#define		STATE_METER_DATA		0x07
#define		STATE_METER_CS			0x08
#define		STATE_METER_END			0x09

#define     CJ188_ADDR_LEN			7
#define     CJ188_DATAID_LEN		2
#define     CJ188_DATA_MAX_LEN		97

typedef struct  
{
	UINT8 startCode;	//起始符
	UINT8 typeCode;		//仪表类型
	UINT8 addr[CJ188_ADDR_LEN];		//地址
	UINT8 ctrlCode;		//控制码
	UINT8 dataLen;		//数据长度
	UINT8 dataID[CJ188_DATAID_LEN];	//数据标识
	UINT8 sn;			//序列号
	UINT8 data[CJ188_DATA_MAX_LEN];	//数据域
	UINT8 cs;	        //校验码
	UINT8 endCode;      //结束符
}CJ188_Frame_Struct;

//四个流量点的系数结构
struct MeterCoe_STR
{
	float bigCoe; //无单位
	float mid2Coe;
	float mid1Coe;
	float smallCoe;
};
typedef MeterCoe_STR* MeterCoe_PTR;

//热量表通讯协议基类
class PROTOCOL_EXPORT MeterProtocol : public CProtocol
{
public:
	MeterProtocol();
	~MeterProtocol();

	QByteArray m_sendBuf;
	CJ188_Frame_Struct *m_CJ188DataFrame;
	QString m_fullMeterNo; //完整表号 7个字节
	QString m_inTemper; //进水温度
	QString m_outTemper;//回水温度
	QString m_flow; //流量 
	QString m_heat; //热量
	QString m_date; //当前日期
	QString m_bigCoe;  //大流量点流量系数
	QString m_mid2Coe; //中流二流量系数
	QString m_mid1Coe; //中流一流量系数
	QString m_smallCoe;//小流量点流量系数
	QString m_Coe; //总系数

public slots:
	virtual UINT8 readMeterComBuffer(QByteArray tmp);
	virtual UINT8 CountCheck(CJ188_Frame_Struct *pFrame);
	virtual void analyseFrame(){};

	virtual void makeFrameOfReadMeterNO(){};        //读表号（广播地址读表）
	virtual void makeFrameOfReadMeterFlowCoe(){};   //读表流量系数（广播地址读表）
	virtual void makeFrameOfReadMeterData(int vType=VTYPE_FLOW){};   //读表数据（广播地址读表）
	virtual void makeFrameOfSetVerifyStatus(int vType=VTYPE_FLOW){}; //设置进入检定状态
	virtual void makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo){};	//修改表号
	virtual void makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr){};	//修改流量参数
	virtual void makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr, MeterCoe_PTR oldCoe){};	//修改流量参数

	virtual QByteArray getSendFrame();
	virtual QString getFullMeterNo();
	virtual QString getFlow();
	virtual QString getInTemper();
	virtual QString getOutTemper();
	virtual QString getHeat();
	virtual QString getDate();
	virtual QString getBigCoe();
	virtual QString getMid2Coe();
	virtual QString getMid1Coe();
	virtual QString getSmallCoe();
	virtual QString getCoe();

private:

};

//德鲁热量表通讯协议类
class PROTOCOL_EXPORT DeluMeterProtocol : public MeterProtocol
{
public:
	DeluMeterProtocol();
	~DeluMeterProtocol();

public slots:
	virtual void analyseFrame();

	virtual void makeFrameOfReadMeterNO();        //读表号（广播地址读表）
	virtual void makeFrameOfReadMeterFlowCoe();   //读表流量系数（广播地址读表）
	virtual void makeFrameOfReadMeterData(int vType=VTYPE_FLOW);    //读表数据（广播地址读表）
	virtual void makeFrameOfSetVerifyStatus(int vType=VTYPE_FLOW);	//设置进入检定状态
	virtual void makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo);	//修改表号(14位表号)
	virtual void makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr);	//修改流量参数
	virtual void makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr, MeterCoe_PTR oldCoe);	//修改流量参数

private:

};

//力创热量表通讯协议类
class PROTOCOL_EXPORT LiChMeterProtocol : public MeterProtocol
{
public:
	LiChMeterProtocol();
	~LiChMeterProtocol();

public slots:
	virtual void analyseFrame();

	virtual void makeFrameOfReadMeterNO();        //读表号（广播地址读表）
	virtual void makeFrameOfReadMeterFlowCoe();   //读表流量系数（广播地址读表）
	virtual void makeFrameOfReadMeterData(int vType=VTYPE_FLOW);    //读表数据（广播地址读表）
	virtual void makeFrameOfSetVerifyStatus(int vType=VTYPE_FLOW);	//设置进入检定状态
	virtual void makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo);	//修改表号
	virtual void makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr);	//修改流量参数
	virtual void makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr, MeterCoe_PTR oldCoe);	//修改流量参数

private:

};

//汇中热量表通讯协议类
class PROTOCOL_EXPORT HuiZhongMeterProtocol : public MeterProtocol
{
public:
	HuiZhongMeterProtocol();
	~HuiZhongMeterProtocol();

public slots:
	virtual void analyseFrame();

	virtual void makeFrameOfReadMeterNO();        //读表号（广播地址读表）
	virtual void makeFrameOfReadMeterFlowCoe();   //读表流量系数（广播地址读表）
	virtual void makeFrameOfReadMeterData(int vType=VTYPE_FLOW);    //读表数据（广播地址读表）
	virtual void makeFrameOfSetVerifyStatus(int vType=VTYPE_FLOW);	//设置进入检定状态
	virtual void makeFrameOfModifyMeterNo(QString oldMeterNo, QString newMeterNo);	//修改表号
	virtual void makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr);	//修改流量参数
	virtual void makeFrameOfModifyFlowCoe(QString meterNO, float bigErr, float mid2Err, float mid1Err, float smallErr, MeterCoe_PTR oldCoe); //修改流量参数

private:

};


//热量表通讯协议 end

//标准温度计-STI-1062A串口协议类
#define CHNT12	QString("FETC?").toLatin1().append(ASCII_CR).append(ASCII_LF)//读取通道1，2的温度值
#define CHNR12	QString("FETC?R").toLatin1().append(ASCII_CR).append(ASCII_LF)//读取通道1，2的电阻值
#define CHNT1	QString("FETC? (@1)").toLatin1().append(ASCII_CR).append(ASCII_LF)//读取通道1的温度值
#define CHNR1	QString("FETC?R (@1)").toLatin1().append(ASCII_CR).append(ASCII_LF)//读取通道1的电阻值
#define CHNT2	QString("FETC? (@2)").toLatin1().append(ASCII_CR).append(ASCII_LF)//读取通道2的温度值
#define CHNR2	QString("FETC?R (@2)").toLatin1().append(ASCII_CR).append(ASCII_LF)//读取通道2的电阻值

#define DATA_STATE	0x00
#define END_STATE	0x01
enum sti1062Acommand
{
	sti1062aT12=0, //请求通道1、2两路温度。返回值根据回车+换行符区分通道1、2
	sti1062aR12,
	sti1062aT1,
	sti1062aT2,
	sti1062aR1,
	sti1062aR2
};

class PROTOCOL_EXPORT sti1062ATempProtocol : public CProtocol
{
	QByteArray m_sendBuf;//发送命令
	QByteArray m_readBuf;//接收到的数据
	QString m_valueStr;//读到的数值
	int m_state;
public:
	sti1062ATempProtocol();
	~sti1062ATempProtocol();

public slots:
	bool readTemperComBuffer(QByteArray tmp);
	void makeSendBuf(sti1062Acommand);
	QByteArray getSendBuf();
	QString getReadStr();
private:

};//sti1062ATempProtocol END

//力创EDA9150A/9017产品, ModbusRTU通讯协议
//主要用于读取西门子电磁流量计的脉冲数
#define EDA_9150A_START_REG	0x0010//EDA9150A模块第一通道的起始寄存器的地址
#define EDA_9150A_ROUTE_CNT	0x0010//EDA9150A模块通道共16路
#define EDA_9017_START_REG	0x0003//EDA9017模块第一路寄存器的地址, 共12路
#define EDA_9017_ROUTE_CNT	0x000C//EDA9017模块通道共12路
#define MOD_ADDRESS_LEN		0x01//回应的地址位的字节数
#define MOD_FUNC_LEN		0x01//回应的功能码位的字节数
#define MOD_DATALEN_LEN		0x01//回应的数据长度信息位的字节数

enum lcModbusRTUFunc//力创ModbusRTU, 功能码
{
	read_multi_switch_out = 0x01,//读 1 路或多路开关量输入状态 DI
	read_multi_switch_in = 0x02,//读 1 路或多路开关量输入状态 DI
	read_multi_reg = 0x03,//读多路寄存器
	write_multi_switch = 0x10//写多路寄存器的数值; 
};

enum lcModAnswerState
{
	init_state = 0x00,
	address_state = 0x01,
	func_state = 0x02,
	length_state = 0x03,
	data_state = 0x04,
	crc_state = 0x05
};

struct lcModSendCmd
{
	uchar address;
	lcModbusRTUFunc func; 
	UINT16 start;
	UINT16 regCount;
};

struct lcMod9150AWriteCmd : public lcModSendCmd
{
	uchar ByteCount;
	int *pData;
	uchar crc_low;
	uchar crc_high;
};

class PROTOCOL_EXPORT lcModbusRTUProtocol : public CProtocol
{	
public:
	lcModbusRTUProtocol();
	~lcModbusRTUProtocol();
public slots:
	bool readMeterComBuffer(QByteArray tmp);//读取标准表脉冲数
	void makeSendBuf(uchar address, lcModbusRTUFunc func, UINT16 start, UINT16 regCount);
	void makeSendBuf(lcModSendCmd);

	void makeWriteBuf(lcMod9150AWriteCmd);//组帧, 改写脉冲数命令. 应答暂时没做
	QByteArray getWriteBuf();

	QByteArray getSendBuf();
	QByteArray getReadVale();//读取全部获取的数值
	QByteArray getData(int i);//读取第i个寄存器的值, 高位在0, 低位在1
	int getIntData(int i);//读取第i个通道的值, 比如DI0就是0通道; DI6就是6通道
private:
	void initParams();//初始化参数
	QByteArray m_writeBuf;//改写力创模块脉冲寄存器数据的命令帧
	QByteArray m_sendBuf;//发送命令
	QByteArray m_readBuf;//接收到的数据(除了crc校验值外的所有数据)
	UINT16 m_readDataLength;//接收到的各个寄存器数据长度
	
	QByteArray m_valueArray;//读到的各个寄存器数值
	QByteArray m_crcValue;//读到的crc值

	UINT16 m_calcDataLength;//根据发送命令, 预计的返回数据长度
	
	lcModAnswerState m_state;
};//lcModbusRTUProtocol END

#endif // PROTOCOL_H
