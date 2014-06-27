#ifndef QUALITYDLG_H
#define QUALITYDLG_H

#include <QtGui/QWidget>

#include "qualitydlg_global.h"
#include "ui_qualitydlg.h"
#include "parasetdlg.h"
#include "comobject.h"
#include "ReadComConfig.h"
#include "algorithm.h"

#define TIMEOUT_TEMPER  500 //每0.5秒钟请求一次温度值

#define VALVE_OPEN		true	//阀门打开状态
#define VALVE_CLOSE		false   //阀门关闭状态

#define VALVE_IN_IDX	 0	//进水阀
#define VALVE_BIG_IDX	 1	//大流量阀
#define VALVE_MID1_IDX	 2	//中一流量
#define VALVE_MID2_IDX	 3	//中二流量
#define VALVE_SMALL_IDX	 4	//小流量
#define VALVE_OUT_IDX	 5	//放水阀
#define VALVE_PUMP_IDX	 6	//水泵

#define  VALVE_NUM	7	//实际用到的阀门总数



class QUALITYDLG_EXPORT QualityDlg : public QWidget
{
	Q_OBJECT

public:
	QualityDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QualityDlg();

	ParaSetDlg *m_paraset;

	ReadComConfig *m_readComConfig; //读串口设置

	ComThread m_tempThread;  //温度采集线程
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

	ComThread m_valveThread;   //阀门控制线程
	ControlComObject *m_controlObj;

	QMap<int, bool> m_valveStatus;
	QMap<int, QPushButton*> m_valveBtn;	
// 	bool m_waterInStatus;	//进水阀门状态
// 	bool m_waterOutStatus;  //放水阀门状态
// 	bool m_valveBigStatus;		//大流量阀门状态
// 	bool m_valveMiddle1Status;  //中流一阀门状态
// 	bool m_valveMiddle2Status;  //中流二阀门状态
// 	bool m_valveSmallStatus;    //小流量点阀门状态
// 	bool m_valvePumpStatus;		//水泵状态
	int m_nowPortNo;	//当前控制阀门端口号
	int m_nowPortIdx;	//当前控制阀门端口索引

	ComThread m_balanceThread; //天平采集线程
	BalanceComObject *m_balanceObj;

	ComThread m_meterThread1;  //热量表1线程
	MeterComObject *m_meterObj1;

	int m_flowcount;  //计算流量时 计数用
	float m_flow1;
	float m_flow2;

	PORTSET_INI_STR m_portsetinfo; //端口配置
	PARASET_INI_STR m_parasetinfo; //参数设置(质量法-分量检测)

	void closeEvent(QCloseEvent * event);
	void initTemperatureCom(); //温度采集串口
	void initBalanceCom();     //天平串口
	void initControlCom();     //阀门控制串口
	void initHeatMeterCom1();  //热量表串口

	void initValveStatus();	   //初始化阀门状态

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

	void slotSetValveBtnStatus(); //继电器返回成功对应的槽函数
	void slotSetRegulateOk();

	void setBtnBackColor(QPushButton *btn, bool status);

	void slotFreshFlow();

	void on_btnReadMeterNo_clicked();

private:
	Ui::QualityDlgClass ui;

private slots:

};

#endif // QUALITYDLG_H
