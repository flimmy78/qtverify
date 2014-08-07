#ifndef WEIGHTMETHOD_H
#define WEIGHTMETHOD_H

#ifdef WEIGHTMETHOD_DLL
#  ifdef WIN32
#  define WEIGHTMETHOD_EXPORT __declspec(dllexport)
#  else
#  define WEIGHTMETHOD_EXPORT
#  endif
#else
#  ifdef WIN32
#  define WEIGHTMETHOD_EXPORT __declspec(dllimport)
#  else
#  define WEIGHTMETHOD_EXPORT
#  endif
#endif

#define BALANCE_START_VALUE		2 //天平初值

#define TIMEOUT_TEMPER		500 //每0.5秒钟请求一次温度值

#define VALVE_OPEN		true	//阀门打开状态
#define VALVE_CLOSE		false   //阀门关闭状态

/*
**	阀门位置索引
*/
#define VALVE_IN_IDX	 0	//进水阀
#define VALVE_BIG_IDX	 1	//大流量阀
#define VALVE_MID1_IDX	 2	//中一流量
#define VALVE_MID2_IDX	 3	//中二流量
#define VALVE_SMALL_IDX	 4	//小流量
#define VALVE_OUT_IDX	 5	//放水阀
#define VALVE_NUM	     6	//实际用到的阀门总数

/*
** 表格列
*/
#define COLUMN_METER_NUMBER 0 //表号列
#define COLUMN_FLOW_POINT	1 //流量点
#define COLUMN_START_VALUE	2 //初值列
#define COLUMN_END_VALUE	3 //终值列
#define COLUMN_BAL_START	4 //天平初值
#define COLUMN_BAL_END		5 //天平终值
#define COLUMN_TEMPER		6 //温度列
#define COLUMN_DENSITY		7 //密度列
#define COLUMN_STD_VALUE	8 //标准值
#define COLUMN_ERROR		9 //示值误差列


#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>

#include "ui_weightmethod.h"
#include "parasetdlg.h"
#include "comobject.h"
#include "ReadComConfig.h"
#include "algorithm.h"

class WEIGHTMETHOD_EXPORT WeightMethodDlg : public QWidget
{
	Q_OBJECT

public:
	WeightMethodDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~WeightMethodDlg();

	QDataWidgetMapper *m_mapper;

	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;


	QTimer *m_exaustTimer; //排气定时器

	QTimer *m_balTimer; //模拟天平定时刷新用 仅用于测试
	float m_balValue;   //模拟天平值
	float m_tempValue;  //模拟温度值

	ComThread m_balanceThread; //天平采集线程
	BalanceComObject *m_balanceObj;

	ComThread m_tempThread;  //温度采集线程
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

	ComThread m_valveThread;   //阀门控制线程
	ControlComObject *m_controlObj;
	QMap<int, bool> m_valveStatus;
	QMap<int, QToolButton*> m_valveBtn;	
	int m_nowPortNo;	//当前控制阀门端口号
	int m_nowPortIdx;	//当前控制阀门端口索引

	CAlgorithm *m_chkAlg;//检定过程用到的计算方法

	bool m_stopFlag;      //关闭界面后退出

	//检定过程相关的控制参数 begin
	Quality_Params_PTR m_nowParams; //当前检定参数
	bool m_continueVerify;    //是否连续检定
	bool m_resetZero;         //是否初值回零
	bool m_autopick;          //是否自动采集
	int m_flowPointNum;       //流量点的个数
	int m_exaustSecond;		  //排气时间
	int m_totalFlag;          //1:总量检定；2:分量检定
	int m_standard;           //表规格
	int m_model;              //表型号
	int m_meterType;          //表类型

	int m_tempCount;		  //计算平均温度用的累加计数器
	int m_rowNum;             //表格的行数（被检表的最大个数）
	int m_meterNum;           //实际检表的个数
	QMap<int, int> m_meterPosMap; //被检表与表位号的映射关系
	QMap<int, float> m_gradeErr;  //不同等级热表对应的标准误差

	float *m_meterStartValue; //被检表的初值
	float *m_meterEndValue;   //被检表的终值
	float *m_meterTemper;	  //被检表的温度
	float *m_meterDensity;    //被检表的密度
	float *m_meterStdValue;   //被检表的标准值
	float *m_meterError;	  //被检表的误差
	float m_balStartV;        //天平初值
	float m_balEndV;          //天平终值
	double m_pipeInTemper;    //入口温度
	double m_pipeOutTemper;   //出口温度
	//检定过程相关的控制参数 end

	int m_recNum; //有效的检定记录个数
	Record_Quality_PTR m_recPtr; //有效的检定记录
	int m_timeStamp;
	float m_flowPoint;
	int m_nowOrder;				//当前检定次序

	bool waitInput; //等待输入状态

	ReadComConfig *m_readComConfig; //读串口设置
	PortSet_Ini_STR m_portsetinfo;  //端口配置

	void initBalanceCom();     //天平串口
	void initTemperatureCom(); //温度采集串口
	void initControlCom();     //阀门控制串口
	void initValveStatus();	   //初始化阀门状态

	int isComAndPortNormal();   //串口、端口设置是否正常
	int isWaterOutValveOpen();  //检查放水阀门是否打开
	int isDataCollectNormal();	//检查数据采集是否正常（天平、温度、电磁流量计等）
	int isAllMeterInVerifyStatus(); //判断热量表都已进入检定状态
	int isMeterPosValid(int row);   //判断表位号是否有效(该表位是否需要检表)


public slots:
	void closeEvent(QCloseEvent * event);
	void removeSubTab(int index);

	int readNowParaConfig();	 //获取当前检定参数
	void showNowKeyParaConfig(); //显示当前关键参数设置信息
	void setTableRowCount();     //设置表格行数

	void on_btnExhaust_clicked(); //点击"排气"按钮
	void on_btnStart_clicked();   //点击"开始"按钮
	void on_btnNext_clicked();    //点击"下一步"按钮
	void on_btnStop_clicked();    //点击"终止检测"按钮
	int openAllValuesAndPump();   //打开所有阀门和水泵
	void slotExaustFinished();    //排气时间结束
	int readMeterNumber();        //读取表号
	int setMeterVerifyStatus();   //设置热量表进入检定状态
	int closeAllFlowPointValves();//关闭所有流量点阀门
	int closeWaterOutValve();     //关闭放水阀
	int openWaterOutValve();      //打开放水阀
	int openBigFlowValve();       //打开大流量点阀门
	int closeBigFlowValve();      //关闭大流量点阀门
	int judgeBalanceInitValue(float v);    //判断天平质量
	int judgeBalanceAndCalcTemper(float targetV); //判断天平质量，并累加进出口温度，每秒累加一次，用于计算进出口平均温度
	void startVerify();           //开始检定
	int getValidMeterNum();       //获取有效的检表个数()
	int judgeBalanceCapacity();   //判断天平容量是否能够满足检定用量 连续检定
	int judgeBalanceCapacitySingle(int order); //判断天平容量是否能够满足检定用量 不连续检定
	int prepareVerifyFlowPoint(int order);     //准备单个流量点的检定
	int startVerifyFlowPoint(int order);       //开始单个流量点的检定
	int openValve(int portno);    //打开控制阀
	int closeValve(int portno);   //关闭控制阀
	int getMeterStartValue();     //获取表初值
	int getMeterEndValue();       //获取表终值
	int calcMeterErrorAndSaveDb();//计算表误差

	void slotFreshBalanceValue(const QString& Str);     //刷新天平数值
	void slotFreshComTempValue(const QString& tempStr); //刷新温度值
	void slotFreshFlow(); //计算流量

	void slotSetValveBtnStatus(); //继电器返回成功对应的槽函数
	void slotSetRegulateOk();     //调节阀返回成功对应的槽函数

	void setValveBtnBackColor(QToolButton *btn, bool status); //设置阀门按钮背景色
	void setRegBtnBackColor(QPushButton *btn, bool status);	  //设置调节阀按钮背景色

	void on_btnParaSet_clicked();	   //参数设置
	void on_btnWaterIn_clicked();      //进水阀
	void on_btnWaterOut_clicked();     //放水阀
	void on_btnValveBig_clicked();     //大流量阀
	void on_btnValveMiddle1_clicked(); //中流一
	void on_btnValveMiddle2_clicked(); //中流二
	void on_btnValveSmall_clicked();   //小流量阀

	void on_btnWaterPumpStart_clicked(); //启动水泵
	void on_btnWaterPumpStop_clicked();  //停止水泵

	void on_tableWidget_cellChanged(int row, int column);
	int saveVerifyRecord(); //保存检定记录
	void clearTableContents();

	void freshBigBalaceValue();   //刷新大天平数值 仅用于测试 模拟天平数值变化

private slots:

signals:

private:
	Ui::WeightMethodClass ui;

};


#endif //WEIGHTMETHOD_H