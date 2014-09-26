#ifndef DATATESTDLG_H
#define DATATESTDLG_H

#include <QtGui/QWidget>

#include "datatestdlg_global.h"
#include "ui_datatestdlg.h"
#include "parasetdlg.h"
#include "comobject.h"
#include "ReadComConfig.h"
#include "algorithm.h"

#define TIMEOUT_TEMPER		500 //每0.5秒钟请求一次温度值
#define CALC_FLOW_COUNT		2   //计算流量频率（实际计算频率 = CALC_FLOW_COUNT * TIMEOUT_TEMPER）


/*
**	类名：DataTestDlg
**	功能：数据采集与测试
*/
class DATATESTDLG_EXPORT DataTestDlg : public QWidget
{
	Q_OBJECT

public:
	DataTestDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DataTestDlg();

	ParaSetDlg *m_paraset;

	ReadComConfig *m_readComConfig; //读串口设置

	ComThread m_tempThread;  //温度采集线程
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;
	QTimer *m_flowTimer;//流量计时器
	QTimer *m_setBalTimer;//设定天平读数计时器

	ComThread m_valveThread;   //阀门控制线程
	ControlComObject *m_controlObj;

	QMap<int, bool> m_valveStatus;//<阀门端口号，阀门状态>
	QMap<int, QPushButton*> m_valveBtn;	//<阀门端口号，阀门按钮>
	int m_nowPortNo;	//当前控制阀门端口号

	QMap<int, bool> m_regStatus; //<调节阀端口号，调节阀状态>
	QMap<int, QPushButton*> m_regBtn;//<调节阀端口号，调节阀按钮>	
	int m_nowRegNo;  //当前调节阀端口号

	ComThread m_balanceThread; //天平采集线程
	BalanceComObject *m_balanceObj;

	ComThread m_meterThread1;  //热量表1线程
	MeterComObject *m_meterObj1;

	uint m_flowcount;  //计算流量时 计数用 , 0~4294967295, 按10微秒计数一次, 可计数497年
	uint m_totalcount;//累积法计数器
	float m_flow1;//天平初值
	float m_flow2;//天平终值
	float start_quan;//累积法天平初值
	float end_quan;//累积法天平终值
	float total_quantity;//累积质量(从读数开始, 到读数结束一共的累积量)
	float bal_quan;//天平读数模拟量
	

	PortSet_Ini_STR m_portsetinfo; //端口配置
	ParaSet_Ini_STR m_parasetinfo; //参数设置(质量法-分量检测)

	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent *event);
	void initTemperatureCom(); //温度采集串口
	void initBalanceCom();     //天平串口
	void initControlCom();     //阀门控制串口
	void initComOfHeatMeter1();  //热量表1串口

	void initValveStatus();	   //初始化阀门状态
	void initRegulateStatus(); //初始化调节阀状态

public slots:
	void on_btnWaterIn_clicked(); //进水阀
	void on_btnWaterOut_clicked();//放水阀
	void on_btnValveBig_clicked(); //大流量阀
	void on_btnValveMiddle1_clicked(); //中流一
	void on_btnValveMiddle2_clicked(); //中流二
	void on_btnValveSmall_clicked(); //小流量阀
	void on_btnWaterPump_clicked(); //水泵

	void on_btnRegulate1_clicked();
	void on_btnQueryStatus_clicked();

	void on_btnParaSet_clicked();
	void on_btnStart_clicked();
	void on_btnExit_clicked();

	void slotFreshComTempValue(const QString& tempStr); //刷新温度值
	void slotFreshBalanceValue(const QString& Str);     //刷新天平数值
	
	void slotFreshMeterNo(const QString& comName, const QString& meterNo);      //刷新表号
	void slotFreshMeterData(const QString& comName, const QString& flow, const QString& heat); //刷新表数据(流量、热量)

	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //继电器返回成功对应的槽函数
	void slotSetRegulateOk();

	void setValveBtnBackColor(QPushButton *btn, bool status); //设置阀门按钮背景色
	void setRegBtnBackColor(QPushButton *btn, bool status);	//设置调节阀按钮背景色

	void slotFreshFlow(); //计算流量
	void slotFreshFlow_total();//计算流量(累计法)
	void setBalQuantity();//模拟天平读数
	void on_btnReadMeterNo_clicked(); //读取表号
	void on_btnReadMeterData_clicked(); //读表数据
	void on_btnSetVerifyStatus_clicked(); //设置检定状态

private:
	Ui::DataTestDlgClass ui;

private slots:

};

#endif // DATATESTDLG_H
