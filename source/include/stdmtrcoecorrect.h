#ifndef STDCOECORRECT_H
#define STDCOECORRECT_H

#include <QtGui/QWidget>
#include <QByteArray>
#include <QSettings>
#include <QtGui/QDataWidgetMapper>

#include "ui_stdmtrcoecorrect.h"
#include "systemsetdlg_global.h"
#include "basedef.h"
#include "comobject.h"

class CAlgorithm;
class ParaSetDlg;
class ParaSetReader;
class ReadComConfig;
class CStdMeterReader;

#define RELEASE_PTR(ptr)		if (ptr != NULL)\
								{\
									delete ptr;\
									ptr = NULL;\
								}

#define RELEASE_TIMER(timerptr)		if (timerptr != NULL)\
									{\
										if (timerptr->isActive())\
										{\
											timerptr->stop();\
										}\
										delete timerptr;\
										timerptr = NULL;\
									}

#define EXIT_THREAD(th)		if (th.isRunning())\
							{\
								th.exit();\
							}

class SYSTEMSETDLG_EXPORT StdMtrCoeCorrect : public QWidget
{
	Q_OBJECT

public:
	StdMtrCoeCorrect(QWidget *parent = 0, Qt::WFlags flags = 0);
	~StdMtrCoeCorrect();

public slots:
	void showEvent(QShowEvent * event);
	void closeEvent(QCloseEvent * event);
	void resizeEvent(QResizeEvent * event);

	void on_btnStart_clicked();   //点击"开始"按钮
	void on_btnGoOn_clicked();    //点击"继续"按钮
	void on_btnStop_clicked();    //点击"终止检测"按钮
	void on_btnExit_clicked();    //点击"退出"按钮
	void on_btnParaSet_clicked();	   //参数设置
	void on_btnWaterIn_clicked();      //进水阀
	void on_btnBigWaterIn_clicked();   //大天平进水阀
	void on_btnBigWaterOut_clicked();  //大天平放水阀
	void on_btnSmallWaterIn_clicked(); //小天平进水阀
	void on_btnSmallWaterOut_clicked();//小天平放水阀
	void on_btnValveBig_clicked();     //大流量阀
	void on_btnValveMiddle1_clicked(); //中流一
	void on_btnValveMiddle2_clicked(); //中流二
	void on_btnValveSmall_clicked();   //小流量阀
	void on_btnWaterPump_clicked(); //水泵
	void on_btnSetFreq_clicked();   //设置变频器频率
	void on_tableWidget_cellChanged(int row, int column);
	void on_btnRegulateSmall_clicked();
	void on_btnRegulateMid1_clicked();
	void on_btnRegulateMid2_clicked();
	void on_btnRegulateBig_clicked();
	void on_lineEditOpeningSmall_textChanged(const QString & text);
	void on_lineEditOpeningMid1_textChanged(const QString & text);
	void on_lineEditOpeningMid2_textChanged(const QString & text);
	void on_lineEditOpeningBig_textChanged(const QString & text);
	void on_btnStdMeterV0_clicked();//读取标准表初值
	void on_btnStdMeterV1_clicked();//读取标准表终值

private slots:
	void slotExaustFinished();    //排气时间结束
	void slotAskPipeTemperature();//请求管路温度
	void slotFreshComTempValue(const QString& tempStr); //刷新温度值
	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //继电器返回成功对应的槽函数
	void slotSetRegulateOk();     //调节阀返回成功对应的槽函数

	/*******************电动调节阀******************************/
	void openAllRegulator();  //打开所有调节阀至设定的开度
	void closeAllRegulator(); //关闭所有调节阀
	void setRegulatorOpening(int regNO, int opening); //设置单个调节阀开度，并在界面显示
	void askControlRegulate(int retNO, int opening); //发送控制调节阀开度命令
	void slotFreshSmallRegOpening();
	void slotFreshMid1RegOpening();
	void slotFreshMid2RegOpening();
	void slotFreshBigRegOpening();
	/******************电动调节阀end***************************/

signals:
	void signalClosed();

private:
	Ui::StdMtrCoeCorrectClass ui;

	QTimer *m_exaustTimer; //排气定时器

	ComThread m_balanceThread; //天平采集线程
	BalanceComObject *m_balanceObj;

	ComThread m_balanceThread2; //天平采集线程2
	BalanceComObject *m_balanceObj2;
	//大天平最大容量和回水底量
	float m_balMaxWht;
	float m_balBottomWht;

	//小天平最大容量和回水底量
	float m_balMaxWht2;
	float m_balBottomWht2;

	ComThread m_tempThread;  //温度采集线程
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;
	int m_avgTFCount;//用于计算出口的平均温度

	ComThread m_valveThread;//阀门控制线程
	ControlComObject *m_controlObj;

	ComThread m_valveThread2;//阀门控制线程2
	ControlComObject *m_controlObj2;

	QMap<int, bool> m_valveStatus; //阀门号与阀门状态的映射关系
	QMap<int, QToolButton*> m_valveBtn;	//阀门号与阀门按钮的映射关系
	int m_nowPortNo;//当前控制阀门端口号

	ReadComConfig *m_readComConfig; //读串口设置
	PortSet_Ini_STR m_portsetinfo;  //端口配置

	QTimer *m_regSmallTimer; //计时器, 用于动态显示小调节阀的开度
	int m_smallOpening; 
	QTimer *m_regMid1Timer; //计时器, 用于动态显示中一调节阀的开度
	int m_mid1Opening; 
	QTimer *m_regMid2Timer; //计时器, 用于动态显示中二调节阀的开度
	int m_mid2Opening; 
	QTimer *m_regBigTimer;  //计时器, 用于动态显示大调节阀的开度
	int m_bigOpening; 

	bool m_stopFlag;//关闭界面后退出
	now_state m_state; //当前运行状态（初始态、读初值态、读终值态）

	CAlgorithm *m_chkAlg;//检定过程用到的计算方法

	//检定过程相关的控制参数 begin
	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;
	Verify_Params_PTR m_nowParams;//当前检定参数
	int m_flowPointNum;//流量点的个数
	int m_exaustSecond;//排气时间

	float m_meterStartValue;//被检表的初值
	float m_meterEndValue;//被检表的终值
	float m_meterStdValue;//被检表的标准值
	float m_meterError;//被检表的误差(当前流量点不同表位的误差)
	float m_stdStartVol;//标准表体积初值
	float m_stdEndVol;//标准表体积终值
	float m_StdStartMass;//经温度修正的标准表质量初值
	float m_StdEndMass;//经温度修正的标准表质量终值
	float m_pipeInTemper;//进口温度
	float m_pipeOutTemper;//出口温度
	QString m_timeStamp;//时间戳 秒数
	QString m_nowDate;  
	QString m_validDate;
	//检定过程相关的控制参数 end

	QMap<int, QLineEdit*> m_RegLineEdit; //调节阀端口号与调节阀开度显示控件的映射关系
	QMap<int, QSpinBox*> m_RegSpinBox; //调节阀端口号与调节阀目标开度控件的映射关系
	int m_lastPortNO; //记录上一个流量点的阀门端口号（一条管路跑多个流量点时使用）

	/*******************标准流量计******************************/
	CStdMeterReader* m_stdMeterReader;
	QMap<flow_rate_wdg, QLCDNumber *> m_mapInstWdg;
	QMap<flow_rate_wdg, QLCDNumber *> m_mapAccumWdg;
	/******************标准流量计end***************************/

	void initBalanceCom();     //天平串口
	void initBalanceCom2();    //天平串口2
	int prepareBigBalanceInitWeight(); //开始检定前，准备大天平初始重量
	int prepareSmallBalanceInitWeight(); //开始检定前，准备小天平初始重量
	int isBigBalanceValueBigger(float targetV, bool flg=true);   //判断大天平质量,flg: true-要求大于目标重量(默认)；false-要求小于目标重量
	int isSmallBalanceValueBigger(float targetV, bool flg=true); //判断小天平质量,flg: true-要求大于目标重量(默认)；false-要求小于目标重量

	void initTemperatureCom(); //温度采集串口
	void initControlCom();     //阀门控制串口
	void initControlCom2();    //阀门控制串口2
	void initValveStatus();	   //初始化阀门状态
	void initRegulateStatus(); //初始化电动调节阀状态
	void initTableWdg();	   //初始化表格画面
	int readNowParaConfig();	 //获取当前检定参数
	int startExhaustCountDown();  //开始排气倒计时
	int openAllValveAndPump();    //打开所有阀门和水泵
	int closeAllValveAndPumpOpenOutValve(); //关闭所有阀门和水泵、打开防水阀
	int closeAllFlowPointValves();//关闭所有流量点阀门
	int judgeTartgetVolAndCalcAvgTemperAndFlow(double initV, double verifyV); //判断是否完成检定量检定量，并累加出口温度，每秒累加一次，用于计算进出口平均温度
	void stopVerify();            //停止检定
	void startVerify();           //开始检定
	int startVerifyFlowPoint(int order);//开始单个流量点的检定
	int openValve(UINT8 portno);    //打开控制阀
	int closeValve(UINT8 portno);   //关闭控制阀
	int operateValve(UINT8 portno); //操作控制阀：打开或者关闭
	int openWaterPump();			//打开水泵
	int closeWaterPump();			//关闭水泵
	int operateWaterPump();			//操作水泵：打开或者关闭
	int getMeterStartValue();       //获取表初值
	int getMeterEndValue();         //获取表终值
	int calcMeterError(int idx);  //计算某个表的误差
	void clearTableContents();		//清空表格
	int saveAllVerifyRecords(); //保存所有被检表的检定记录
	void setValveBtnBackColor(QToolButton *btn, bool status); //设置阀门按钮背景色
	void setRegBtnBackColor(QPushButton *btn, bool status);	  //设置调节阀按钮背景色
};

#endif //STDCOECORRECT_H