#ifndef TOTALSTANDARD_H
#define TOTALSTANDARD_H

#ifdef TOTALSTANDARD_DLL
#  ifdef WIN32
#  define TOTALSTANDARD_EXPORT __declspec(dllexport)
#  else
#  define TOTALSTANDARD_EXPORT
#  endif
#else
#  ifdef WIN32
#  define TOTALSTANDARD_EXPORT __declspec(dllimport)
#  else
#  define TOTALSTANDARD_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>

#include "ui_totalstandard.h"
#include "comobject.h"

class CAlgorithm;
class ParaSetDlg;
class ParaSetReader;
class ReadComConfig;


class TOTALSTANDARD_EXPORT TotalStandardDlg : public QWidget
{
	Q_OBJECT

public:
	TotalStandardDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~TotalStandardDlg();

	QDataWidgetMapper *m_meterStdMapper;

	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;

	QTimer *m_exaustTimer; //排气定时器

	ComThread m_balanceThread; //天平采集线程
	BalanceComObject *m_balanceObj;

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

	//检定过程相关的控制参数 begin
	Verify_Params_PTR m_nowParams; //当前检定参数
	bool m_continueVerify;    //是否连续检定
	bool m_resetZero;         //是否初值回零
	bool m_autopick;          //是否自动采集
	int m_flowPointNum;       //流量点的个数
	int m_exaustSecond;		  //排气时间
	int m_standard;           //表规格
	int m_model;              //表型号
	int m_meterType;          //表类型
	int m_manufac;			  //制造厂商(德鲁航天, 天罡等)
	//检定过程相关的控制参数 end

	int m_tempCount;		  //计算平均温度用的累加计数器
	int m_maxMeterNum;        //表格的行数（被检表的最大个数）
	int m_validMeterNum;          //实际检表的个数
	QMap<int, int> m_meterPosMap; //被检表下标与表位号的映射关系
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

	Flow_Verify_Record_PTR m_recPtr; //有效的检定记录
	QString m_timeStamp; //时间戳 秒数
	QString m_nowDate;  
	QString m_validDate;

	float m_flowPoint;
	int m_nowOrder;				//当前检定次序

	bool m_inputStartValue; //手动采集时，等待输入初值状态
	bool m_inputEndValue;   //手动采集时，等待输入终值状态

	bool m_startValueFlag;  //自动采集时，区分是热表初值还是终值

	ReadComConfig *m_readComConfig; //读串口设置
	PortSet_Ini_STR m_portsetinfo;  //端口配置

	float m_balLastValue; //天平上一次读数，用来判断天平数值是否发生突变，防错用

	//计算流速用
	uint m_totalcount;  //计数器
	float m_startWeight;//天平初值
	float m_endWeight;  //天平终值
	float m_deltaWeight[FLOW_SAMPLE_NUM];
	QTimer *m_flowRateTimer;  //计时器:用于计算流速


	void initBalanceCom();     //天平串口
	void initTemperatureCom(); //温度采集串口
	void initControlCom();     //阀门控制串口
	void initMeterCom();       //热量表串口
	void initValveStatus();	   //初始化阀门状态

	int isComAndPortNormal();   //串口、端口设置是否正常
	int isWaterOutValveOpen();  //检查放水阀门是否打开
	int isDataCollectNormal();	//检查数据采集是否正常（天平、温度、电磁流量计等）
	int isMeterPosValid(int meterPos); //判断表位号是否有效(该表位是否需要检表)


public slots:
	void closeEvent(QCloseEvent * event);

	int readNowParaConfig();	 //获取当前检定参数
	void showNowKeyParaConfig(); //显示当前关键参数设置信息
	void initTableWidget();     //设置表格行数

	void on_btnExhaust_clicked(); //点击"排气"按钮
	void on_btnStart_clicked();   //点击"开始"按钮
	void on_btnNext_clicked();    //点击"下一步"按钮
	void on_btnStop_clicked();    //点击"终止检测"按钮
	void slotExaustFinished();    //排气时间结束
	int openAllValveAndPump();    //打开所有阀门和水泵
	int readMeter();          //读取热表
	int setMeterVerifyStatus();   //设置热量表进入检定状态
	int closeAllFlowPointValves();//关闭所有流量点阀门
	int closeWaterOutValve();     //关闭放水阀
	int openWaterOutValve();      //打开放水阀
	int openBigFlowValve();       //打开大流量点阀门
	int closeBigFlowValve();      //关闭大流量点阀门
	int judgeBalanceInitValue(float v);    //判断天平质量
	int judgeBalanceAndCalcAvgTemper(float targetV); //判断天平质量，并累加进出口温度，每秒累加一次，用于计算进出口平均温度
	void startVerify();           //开始检定
	int getValidMeterNum();       //获取有效的检表个数()
	bool judgeBalanceCapacity();   //判断天平容量是否能够满足检定用量 连续检定
	int judgeBalanceCapacitySingle(int order); //判断天平容量是否能够满足检定用量 不连续检定
	int prepareVerifyFlowPoint(int order);     //准备单个流量点的检定
	int startVerifyFlowPoint(int order);       //开始单个流量点的检定
	int openValve(UINT8 portno);    //打开控制阀
	int closeValve(UINT8 portno);   //关闭控制阀
	int operateValve(UINT8 portno); //操作控制阀：打开或者关闭
	int getMeterStartValue();     //获取表初值
	int getMeterEndValue();       //获取表终值
	void makeStartValueByLastEndValue(); //上一次的终值作为本次的初值
	int calcAllMeterError();//计算所有被检表的误差
	int calcMeterError(int idx); //计算某个表的误差

	void slotFreshBalanceValue(const float& balValue);  //刷新天平数值
	void slotFreshComTempValue(const QString& tempStr); //刷新温度值
	void slotFreshFlowRate(); //计算流速

	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //继电器返回成功对应的槽函数
	void slotSetRegulateOk();     //调节阀返回成功对应的槽函数

	void slotSetMeterNumber(const QString& comName, const QString& meterNumber);
	void slotSetMeterFlow(const QString& comName, const float& flow);
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

	void on_btnReadMeter_clicked(); //读表按钮
	void on_btnExit_clicked();//退出按钮
	
	void slotModifyMeterNo(const int &row); //修改表号
	void slotAdjustError(const int &row); //调整误差

private slots:

signals:

private:
	Ui::TotalStandardClass ui;

};

#endif //TOTALSTANDARD_H