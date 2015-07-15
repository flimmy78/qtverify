#ifndef FLOWSTANDARD_H
#define FLOWSTANDARD_H

#ifdef FLOWSTANDARD_DLL
#  ifdef WIN32
#  define FLOWSTANDARD_EXPORT __declspec(dllexport)
#  else
#  define FLOWSTANDARD_EXPORT
#  endif
#else
#  ifdef WIN32
#  define FLOWSTANDARD_EXPORT __declspec(dllimport)
#  else
#  define FLOWSTANDARD_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QByteArray>
#include <QSettings>
#include <QtGui/QDataWidgetMapper>

#include "ui_flowstandard.h"
#include "comobject.h"

class CAlgorithm;
class ParaSetDlg;
class ParaSetReader;
class ReadComConfig;


/*
** 表格列
*/
#define COLUMN_METER_NUMBER			0 //表号列
#define COLUMN_FLOW_POINT			1 //流量点
#define COLUMN_METER_START			2 //表初值列
#define COLUMN_METER_END			3 //表终值列
#define COLUMN_BAL_START			4 //天平初值
#define COLUMN_BAL_END				5 //天平终值
#define COLUMN_TEMPER				6 //温度列
#define COLUMN_DENSITY				7 //密度列
#define COLUMN_STD_VALUE			8 //标准值
#define COLUMN_ERROR				9 //示值误差列
#define COLUMN_READ_METER			10 //读表数据列
#define COLUMN_VERIFY_STATUS		11 //设置检定状态列
#define COLUMN_ADJUST_ERROR			12 //调整误差列
#define COLUMN_MODIFY_METERNO		13 //修改表号列

#define TIMEOUT_STD_INST			500//请求标准表瞬时流量周期
#define TIMEOUT_STD_ACCUM			500//请求标准表累积流量周期
#define TIMEOUT_MODIFY_STD_ACCUM	2000//修改累积脉冲数周期

class FLOWSTANDARD_EXPORT FlowStandardDlg : public QWidget
{
	Q_OBJECT

public:
	FlowStandardDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~FlowStandardDlg();

	QDataWidgetMapper *m_meterStdMapper;

	QTimer *m_exaustTimer; //排气定时器


	ComThread m_tempThread;  //温度采集线程
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

	ComThread m_valveThread;   //阀门控制线程
	ControlComObject *m_controlObj;
	QMap<int, bool> m_valveStatus; //阀门号与阀门状态的映射关系
	QMap<int, QToolButton*> m_valveBtn;	//阀门号与阀门按钮的映射关系
	int m_nowPortNo;	//当前控制阀门端口号

	ComThread *m_meterThread;	//热量表通讯线程
	MeterComObject *m_meterObj;	

	CAlgorithm *m_chkAlg;//检定过程用到的计算方法

	bool m_stopFlag;     //关闭界面后退出
	bool m_conFlag;      //自动检表时，遇到读表数据失败的，等待重新读表的标识。1:等待  0:不等待

	//检定过程相关的控制参数 begin
	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;
	Verify_Params_PTR m_nowParams; //当前检定参数
	bool m_continueVerify;    //是否连续检定
	bool m_resetZero;         //是否初值回零
	bool m_autopick;          //是否自动采集
	int m_flowPointNum;       //流量点的个数
	int m_exaustSecond;		  //排气时间
	int m_standard;           //表规格
	int m_model;              //表型号
	int m_pickcode;			  //采集代码(热表通讯协议版本号)
	float m_flowSC;           //流量检定安全系数
	bool m_adjErr;            //是否调整误差
	bool m_writeNO;          //是否修改表号
	//检定过程相关的控制参数 end

	int m_avgTFCount;		  //计算平均温度和平均流量用的累加计数器
	int m_maxMeterNum;        //被检表的最大个数
	int m_oldMaxMeterNum;     //上次被检表的最大个数
	int m_validMeterNum;          //实际被检表的个数
	QMap<int, int> m_meterPosMap; //被检表下标与表位号的映射关系
	QMap<int, float> m_gradeErrA;  //不同等级热表对应的标准误差参数A
	QMap<int, float> m_gradeErrB;  //不同等级热表对应的标准误差参数B
	QMap<int, float> m_mapNormalFlow;  //不同规格热表对应的常用流量

	float *m_meterStartValue; //被检表的初值
	float *m_meterEndValue;   //被检表的终值
	float *m_meterTemper;	  //被检表的温度
	float *m_meterDensity;    //被检表的密度
	float *m_meterStdValue;   //被检表的标准值
	float *m_meterError;	  //被检表的误差(当前流量点不同表位的误差)
	float m_StdStartV;        //标准表初值
	float m_StdEndV;          //标准表终值
	float m_pipeInTemper;     //入口温度
	float m_pipeOutTemper;    //出口温度
	float m_realFlow;		  //流速(m3/h）
	float **m_meterErr;       //被检表的误差(不同表位、不同流量点的误差)
	int *m_meterResult;       //检表结果 1:合格；0:不合格
	MeterCoe_PTR *m_oldMeterCoe; //热量表原来的各流量点系数

	Flow_Verify_Record_PTR m_recPtr; //有效的检定记录
	QString m_timeStamp; //时间戳 秒数
	QString m_nowDate;  
	QString m_validDate;
	UINT32 m_newMeterNO;   //新表号
	QMap<int, UINT32> m_mapMeterPosAndNewNO; //检表结果合格的表位与新表号映射关系

	int m_nowOrder;				//当前检定次序

	now_state m_state; //当前运行状态（初始态、读初值态、读终值态）

	ReadComConfig *m_readComConfig; //读串口设置
	PortSet_Ini_STR m_portsetinfo;  //端口配置

	void initInstStdCom();//瞬时流量串口初始化
	void initAccumStdCom();//累积流量串口初始化

	void initTemperatureCom(); //温度采集串口
	void initControlCom();     //阀门控制串口
	void initMeterCom();       //热量表串口
	void initValveStatus();	   //初始化阀门状态

	int isComAndPortNormal();   //串口、端口设置是否正常
	int isDataCollectNormal();	//检查数据采集是否正常（天平、温度、电磁流量计等）
	int isMeterPosValid(int meterPos); //判断表位号是否有效(该表位是否需要检表)
	int getValidMeterNum();//获取有效的检表个数()


	public slots:
		void showEvent(QShowEvent * event);
		void closeEvent(QCloseEvent * event);

		int readNowParaConfig();	 //获取当前检定参数
		void showNowKeyParaConfig(); //显示当前关键参数设置信息
		void initTableWidget();     //设置表格行数

		int on_btnExhaust_clicked();  //点击"排气"按钮
		void on_btnStart_clicked();   //点击"开始"按钮
		void on_btnGoOn_clicked();    //点击"继续"按钮
		void on_btnNext_clicked();    //点击"下一步"按钮
		void on_btnStop_clicked();    //点击"终止检测"按钮
		void on_btnExit_clicked();    //退出按钮
		int startExhaustCountDown();  //开始排气倒计时
		void slotExaustFinished();    //排气时间结束
		int openAllValveAndPump();    //打开所有阀门和水泵
		int readAllMeter();           //读取所有被检表
		int setAllMeterVerifyStatus();   //设置热量表进入检定状态
		int closeAllFlowPointValves();//关闭所有流量点阀门
		int closeWaterOutValve();     //关闭放水阀
		int openWaterOutValve();      //打开放水阀
		int judgeTartgetVolAndCalcAvgTemperAndFlow(float targetV); //判断是否完成检定量检定量，并累加进出口温度，每秒累加一次，用于计算进出口平均温度
		void stopVerify();            //停止检定
		void startVerify();           //开始检定
		int prepareVerifyFlowPoint(int order);     //准备单个流量点的检定
		int startVerifyFlowPoint(int order);       //开始单个流量点的检定
		int openValve(UINT8 portno);    //打开控制阀
		int closeValve(UINT8 portno);   //关闭控制阀
		int operateValve(UINT8 portno); //操作控制阀：打开或者关闭
		int openWaterPump();			//打开水泵
		int closeWaterPump();			//关闭水泵
		int operateWaterPump();			//操作水泵：打开或者关闭
		int getMeterStartValue();     //获取表初值
		int getMeterEndValue();       //获取表终值
		void makeStartValueByLastEndValue(); //上一次的终值作为本次的初值
		int calcAllMeterError();//计算所有被检表的误差
		int calcMeterError(int idx); //计算某个表的误差

		void slotFreshComTempValue(const QString& tempStr); //刷新温度值

		void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //继电器返回成功对应的槽函数
		void slotSetRegulateOk();     //调节阀返回成功对应的槽函数

		void slotSetMeterNumber(const QString& comName, const QString& meterNumber);
		void slotSetMeterFlow(const QString& comName, const float& flow);
		void slotFreshBigCoe(const QString& comName, const QString& bigCoe); //刷新大流量系数
		void slotFreshMid2Coe(const QString& comName, const QString& mid2Coe); //刷新中流2流量系数
		void slotFreshMid1Coe(const QString& comName, const QString& mid1Coe); //刷新中流1流量系数
		void slotFreshSmallCoe(const QString& comName, const QString& smallCoe); //刷新小流量系数
		void setValveBtnBackColor(QToolButton *btn, bool status); //设置阀门按钮背景色
		void setRegBtnBackColor(QPushButton *btn, bool status);	  //设置调节阀按钮背景色

		void on_btnParaSet_clicked();	   //参数设置
		void on_btnWaterIn_clicked();      //进水阀
		void on_btnWaterOut_clicked();     //放水阀
		void on_btnValveBig_clicked();     //大流量阀
		void on_btnValveMiddle1_clicked(); //中流一
		void on_btnValveMiddle2_clicked(); //中流二
		void on_btnValveSmall_clicked();   //小流量阀

		void on_btnWaterPump_clicked(); //水泵
		void on_btnSetFreq_clicked();   //设置变频器频率

		void on_tableWidget_cellChanged(int row, int column);
		int saveAllVerifyRecords(); //保存所有被检表的检定记录
		void clearTableContents();

		void on_btnAllReadMeter_clicked();   //读表(所有表）
		void on_btnAllVerifyStatus_clicked();//设置检定状态(所有表）
		void on_btnAllAdjError_clicked(); //调整误差(所有表)
		void on_btnAllModifyNO_clicked(); //修改表号(所有表）
		void on_btnReCalc_clicked(); 

		void slotModifyMeterNO(const int &row); //修改表号
		void slotAdjustError(const int &row);   //调整误差
		void slotReadMeter(const int &row);     //读表(单个表)
		void slotVerifyStatus(const int &row);  //检定状态

		void saveStartMeterNO(); //保存起始表号

private slots:
	void slotAskInstPulse();//请求瞬时流量
	void slotAskAccumPulse();//请求累积流量
	void slotModifyAccumPulse();//修改累积流量, 以模拟标准表采集环境

	void slotGetInstStdMeterPulse(const QByteArray &);//瞬时流量槽函数
	void slotGetAccumStdMeterPulse(const QByteArray &);//累积流量槽函数
signals:
	void signalClosed();

private:
	Ui::FlowStandardClass ui;

	uchar m_accumDevAddress;//当前累积流量采集所使用的力创模块设备地址, 默认为0x01
	uchar m_instDevAddress;//当前瞬时流量采集所使用的力创模块设备地址, 默认为0x01
	lcModRtuComObject *m_instantFlowCom;//瞬时流量串口对象
	ComThread m_instantFlowThread;//瞬时流量采集线程
	QTimer* m_instSTDMeterTimer;//瞬时流量计时器
	QByteArray m_instStdPulse;//瞬时流量脉冲值, 需二次加工

	lcModRtuComObject *m_accumulateFlowCom;//累积流量串口对象
	ComThread m_accumFlowThread;//累积流量采集线程
	QTimer* m_accumSTDMeterTimer;//累积流量计时器
	QTimer* m_accumModifyStdMeterTimer;//修改累积流量脉冲数计时器
	int m_writeAccumCnt;//写累积流量的累加计数器
	QByteArray m_accumStdPulse;//16路累积流量脉冲值, 需二次加工

	QList<int> m_instRouteIsRead;//瞬时流量的通道号是否被采集过
	QList<int> m_accumRouteIsRead;//累积流量的通道号是否被采集过
	QSettings *m_stdParam;//读取标准表设置

	float getFlowValueByValve(flow_rate_wdg, flow_type);//根据流量点的部件号查找流量值
	int getRouteByWdg(flow_rate_wdg, flow_type);//根据部件号读取标准表的通道号
	float getStdUpperFlow(flow_rate_wdg wdgIdx);//根据部件号读取相应标准表的上限流量值
	float getStdPulse(flow_rate_wdg wdgIdx);//根据部件号读取相应标准表的脉冲值

	void inputMeterData();//手动检表时, 需要输入表的初值和终值
};

#endif //FLOWSTANDARD_H