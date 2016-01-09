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
class StdMtrCorrectPraDlg;

#define RELEASE_PTR(ptr)		if (ptr != NULL)\
								{\
									delete ptr;\
									ptr = NULL;\
								}

#define EXIT_THREAD(th)		if (th.isRunning())\
							{\
								th.exit();\
							}

#define FLOW_POINTS	(8)//每个标准表需要标定的最多流量点个数
#define CHK_CNTS	(3)//每个流量点需要重复检测的次数
#define COL_CNTS   (12)//表格的列数

#define COL_FLOW_POINT	0//流量点列
#define COL_BALV0		1//天平初值列
#define COL_BALV1		2//天平终值列
#define COL_BALVD		3//天平示值列
#define COL_DEN			4//密度列
#define COL_BALVC		5//标准值列
#define COL_STDV0		6//标准表初值列
#define COL_STDV1		7//标准表终值列
#define COL_STDVD		8//标准表示值列
#define COL_STDERR		9//标准表误差列
#define COL_STDERR_AVR	10//标准表平均误差列
#define COL_STDREP		11//可重复列

#define EX_DEGREE		80//用于排气时的调节阀开度
#define REG_DEGREE_ZERO	0//用于排气时的调节阀开度
#define EX_GREQ			25//用于排气时的水泵频率

#define FLAG_SUCCESS 0
#define FLAG_FAIL    1

typedef struct{
	float flowpoint;//当前检定的流量点 m3/h
	int	  degree;//调节阀开度
	int	  freq;//水泵频率
	float quantity;//检定量
}StdCorrectPara_STR;
typedef StdCorrectPara_STR* StdCorrectPara_PTR;

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

	void on_btnPra_clicked();//参数设置按钮
	void on_btnClearTbl_clicked();//清空表格按钮
	void on_btnSave_clicked();//保存标定误差按钮
	void on_btnExit_clicked();    //点击"退出"按钮
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
	void on_btnRegulateSmall_clicked();//调节小调节阀
	void on_btnRegulateMid1_clicked();//调节中一调节阀
	void on_btnRegulateMid2_clicked();//调节中二调节阀
	void on_btnRegulateBig_clicked();//调节大调节阀
	void on_btnStart_clicked();//点击开始
	void on_btnGoOn_clicked();//点击继续

	void on_lineEditOpeningSmall_textChanged(const QString & text);//响应小调节阀开度变化
	void on_lineEditOpeningMid1_textChanged(const QString & text);//响应中一调节阀开度变化
	void on_lineEditOpeningMid2_textChanged(const QString & text);//响应中二调节阀开度变化
	void on_lineEditOpeningBig_textChanged(const QString & text);//响应大调节阀开度变化
	void on_tableWidget_cellChanged(int row, int column);//响应表格内容变化
	void on_rBtn_DN3_toggled();//选取DN3标准表
	void on_rBtn_DN10_toggled();//选取DN10标准表
	void on_rBtn_DN25_toggled();//选取DN25标准表
	void on_rBtn_DN50_toggled();//选取DN50标准表

	void slotFreshBigBalanceValue(const float& balValue);  //刷新大天平数值
	void slotFreshSmallBalanceValue(const float& balValue);//刷新小天平数值
	void slotOnStdMtrCorrectPraClosed();//响应参数设置窗口关闭
	void slotExaustFinished();//响应排气完成
	/*******************标准流量计******************************/
	void slotFreshInstFlow(const flow_rate_wdg&, const float&);//刷新瞬时流量
	void slotFreshAccumFlow(const flow_rate_wdg&, const float&);//刷新累积流量
	void slotFreshTolInst(const float&);//刷新瞬时流量和
	void slotFreshTolAccum(const float&);//刷新累积流量和
	/******************标准流量计end****************************/
private slots:
	void slotAskPipeTemperature();//请求管路温度
	void slotFreshComTempValue(const QString& tempStr); //刷新温度值
	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //继电器返回成功对应的槽函数
	void slotSetRegulateOk();     //调节阀返回成功对应的槽函数
	void slotReadCorrectParas();   //读取参数设定
	/*******************电动调节阀******************************/
	void openAllRegulator();  //打开所有调节阀至设定的开度
	void closeAllRegulator(); //关闭所有调节阀
	void setRegulatorOpening(int regNO, int opening); //设置单个调节阀开度，并在界面显示
	void askControlRegulate(int retNO, int opening); //发送控制调节阀开度命令
	void slotFreshSmallRegOpening();//刷新小调节阀开度值
	void slotFreshMid1RegOpening();//刷新中一调节阀开度值
	void slotFreshMid2RegOpening();//刷新中二调节阀开度值
	void slotFreshBigRegOpening();//刷新大调节阀开度值
	/******************电动调节阀end***************************/

signals:
	void signalClosed();

private:
	Ui::StdMtrCoeCorrectClass ui;
	StdMtrCorrectPraDlg* m_StdMtrCorrectPraDlg;//参数设定窗口
	bool m_stopFlag;//当前是否为停止检定状态
	int m_exhaustSecond;//排气时间
	Balance_Capacity m_curBalance;//当前标准表所在管路所使用的天平
	int m_curStdMeter;//当前被选中的标准表
	QMap<flow_rate_wdg, QList<StdCorrectPara_PTR>> m_mapFlowPoint;//管路-<流量点, 检定量, 调节阀开度, 水泵频率>配置表
	int m_chkTimes;//每个流量点的检定次数

	QTimer *m_exhaustTimer; //排气定时器


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

	float m_tempPipeOut;
	int m_avgTFCount;//用于计算出口的平均温度
	ComThread m_tempThread;  //温度采集线程
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

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

	CAlgorithm *m_chkAlg;//检定过程用到的计算方法
	QSettings* m_stdMeterConfig;//标准表的配置文件
	QSettings* m_stdCorrectParas;//标定过程中的参数

	QMap<int, QLineEdit*> m_RegLineEdit; //调节阀端口号与调节阀开度显示控件的映射关系
	QMap<int, QSpinBox*> m_RegSpinBox; //调节阀端口号与调节阀目标开度控件的映射关系
	int m_lastPortNO; //记录上一个流量点的阀门端口号(一条管路跑多个流量点时使用)

	/*******************标准流量计******************************/
	CStdMeterReader* m_stdMeterReader;//标准流量计读取模块
	QMap<flow_rate_wdg, QLCDNumber *> m_mapInstWdg;//管路-显示部件对应表, 瞬时流量
	QMap<flow_rate_wdg, QLCDNumber *> m_mapAccumWdg;//管路-显示部件对应表, 累积流量
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

	void clearMapFlowPoint();
	void releaseSource();	   //释放资源
	int openAllValveAndPump();    //打开所有阀门和水泵
	int closeAllValveAndPumpOpenOutValve(); //关闭所有阀门和水泵、打开防水阀
	int closeAllFlowPointValves();//关闭所有流量点阀门
	int openValve(UINT8 portno);    //打开控制阀
	int closeValve(UINT8 portno);   //关闭控制阀
	int operateValve(UINT8 portno); //操作控制阀：打开或者关闭
	int openWaterPump();			//打开水泵
	int closeWaterPump();			//关闭水泵
	int operateWaterPump();			//操作水泵：打开或者关闭

	void clearTableContents();		//清空表格
	void setValveBtnBackColor(QToolButton *btn, bool status); //设置阀门按钮背景色
	void setRegBtnBackColor(QPushButton *btn, bool status);	  //设置调节阀按钮背景色
	int getStartRow(int row);//获取当前行对应流量点的起始行
	void saveMeterConfig(flow_rate_wdg wdg);//保存标定误差

	void startVerify();//开始总检定
	int  startVerifyFlowPoint(StdCorrectPara_PTR flowpoint);//开始单个流量点的检定
	void startVerifySeq(int i);//开始流量点的第i次检定
	void stopVerify();//停止检定

	bool judgeBalanceCapacity(int &bigOK, int &smallOK);//判断天平容量是否能够满足检定用量 连续检定
	int judgeBalanceCapacitySingle(int order, int &bigBalance);//判断天平容量是否能够满足检定用量 不连续检定
	int prepareVerifyFlowPoint(int order);//准备单个流量点的检定
	int judgeBalanceAndCalcAvgTemperAndFlow(float targetV, bool bigFlag); //判断大天平质量，并累加进出口温度，每秒累加一次，用于计算进出口平均温度
	int startExhaustCountDown();  //开始排气倒计时
};

#endif //STDCOECORRECT_H