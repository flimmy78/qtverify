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

#include <QtGui/QWidget>

#include "ui_weightmethod.h"
#include "parasetdlg.h"

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
	float m_balValue;
	float m_tempValue;  //模拟温度值


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

	int isComAndPortNormal(); //串口、端口设置是否正常
	int isWaterOutValveOpen(); //检查放水阀门是否打开
	int readParaConfig();		//读参数配置文件
	int isDataCollectNormal();	//检查数据采集是否正常（天平、温度、电磁流量计等）
	int isAllMeterInVerifyStatus(); //判断热量表都已进入检定状态

public slots:
	void closeEvent(QCloseEvent * event);
	void removeSubTab(int index);
	int on_btnExhaust_clicked();  //点击"排气按钮"
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


	void freshBigBalaceValue();   //刷新大天平数值 仅用于测试 模拟天平数值变化

private slots:

signals:


private:
	Ui::WeightMethodClass ui;

};


#endif //WEIGHTMETHOD_H