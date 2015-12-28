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

	void on_btnSave_clicked();
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
	void on_rBtn_DN3_toggled();
	void on_rBtn_DN10_toggled();
	void on_rBtn_DN25_toggled();
	void on_rBtn_DN50_toggled();

private slots:
	void slotAskPipeTemperature();//请求管路温度
	void slotFreshComTempValue(const QString& tempStr); //刷新温度值
	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //继电器返回成功对应的槽函数
	void slotSetRegulateOk();     //调节阀返回成功对应的槽函数

	/*******************电动调节阀******************************/
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
	int m_curStdMeter;//当前被选中的标准表

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
	int openAllValveAndPump();    //打开所有阀门和水泵
	int closeAllValveAndPumpOpenOutValve(); //关闭所有阀门和水泵、打开防水阀
	int closeAllFlowPointValves();//关闭所有流量点阀门
	int startVerifyFlowPoint(int order);//开始单个流量点的检定
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
};

#endif //STDCOECORRECT_H