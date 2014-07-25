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

#define  VALVE_NUM	6	//实际用到的阀门总数


#include <QtGui/QWidget>

#include "ui_weightmethod.h"
#include "parasetdlg.h"
#include "comobject.h"
#include "ReadComConfig.h"

class WEIGHTMETHOD_EXPORT WeightMethodDlg : public QWidget
{
	Q_OBJECT

public:
	WeightMethodDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~WeightMethodDlg();

	ParaSetReader *m_paraSetReader;

	QTimer *m_exaustTimer; //排气定时器
	int m_exaustSecond;	

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

	//检定过程相关的控制参数 begin
	bool m_continueVerify; //是否连续检定
	bool m_resetZero;      //是否初值回零
	QMap<int, int> m_meterNumMap;//被检表最大个数，与规格相关
	int m_meterNum;           //被检表最大个数
	int m_flowPointNum;       //流量点的个数
	float *m_meterStartValue; //被检表的初值
	float *m_meterEndValue;   //被检表的终值
	float m_balStartV;        //天平初值
	float m_balEndV;          //天平终值
	float m_pipeInTemper;     //入口温度
	float m_pipeOutTemper;    //出口温度
	//检定过程相关的控制参数 end

	ReadComConfig *m_readComConfig; //读串口设置
	void initBalanceCom();     //天平串口
	void initTemperatureCom(); //温度采集串口
	void initControlCom();     //阀门控制串口
	void initValveStatus();	   //初始化阀门状态

	int isComAndPortNormal(); //串口、端口设置是否正常
	int isWaterOutValveOpen(); //检查放水阀门是否打开
	int readParaConfig();		//读参数配置文件
	int isDataCollectNormal();	//检查数据采集是否正常（天平、温度、电磁流量计等）
	int isAllMeterInVerifyStatus(); //判断热量表都已进入检定状态

public slots:
	void closeEvent(QCloseEvent * event);
	void removeSubTab(int index);
	void on_btnExhaust_clicked();  //点击"排气按钮"
	void on_btnStart_clicked();    //点击"开始"按钮
	void on_btnNext_clicked();
	int openAllValuesAndPump();   //打开所有阀门和水泵
	void slotExaustFinished();    //排气时间结束
	int readMeterNumber();        //读取表号
	int setMeterVerifyStatus();   //设置热量表进入检定状态
	int closeAllFlowPointValves();//关闭所有流量点阀门
	int closeWaterOutValve();     //关闭放水阀
	int openWaterOutValve();      //打开放水阀
	int openBigFlowValve();       //打开大流量点阀门
	int closeBigFlowValve();      //关闭大流量点阀门
	int judgeBalanceInitValue(float v); //判断天平质量
	void startVerify();           //开始检定
	int judgeBalanceCapacity();   //判断天平容量是否能够满足检定用量 连续检定
	int judgeBalanceCapacitySingle(int order); //判断天平容量是否能够满足检定用量 不连续检定
	int startVerifyFlowPoint(int order); //单个流量点的检定
	int openValve(int portno);    //打开控制阀
	int closeValve(int portno);   //关闭控制阀

	void slotFreshBalanceValue(const QString& Str); //刷新天平数值
	void slotFreshComTempValue(const QString& tempStr); //刷新温度值
	void slotFreshFlow(); //计算流量

	void slotSetValveBtnStatus(); //继电器返回成功对应的槽函数
	void slotSetRegulateOk();     //调节阀返回成功对应的槽函数

	void setValveBtnBackColor(QToolButton *btn, bool status); //设置阀门按钮背景色
	void setRegBtnBackColor(QPushButton *btn, bool status);	  //设置调节阀按钮背景色


	void freshBigBalaceValue();   //刷新大天平数值 仅用于测试 模拟天平数值变化

private slots:

signals:


private:
	Ui::WeightMethodClass ui;

};


#endif //WEIGHTMETHOD_H