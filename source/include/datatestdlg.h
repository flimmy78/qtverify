#ifndef DATATESTDLG_H
#define DATATESTDLG_H

#include <QtGui/QWidget>

#include "datatestdlg_global.h"
#include "ui_datatestdlg.h"
#include "parasetdlg.h"
#include "comobject.h"
#include "readcomconfig.h"
#include "algorithm.h"


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
	QTimer *m_tempTimer;  //计时器:用于请求管路温度

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

	ComThread m_meterThread;  //热量表线程
	MeterComObject *m_meterObj;

	//计算流速用
	uint m_totalcount;  //计数器
	float m_startWeight;//天平初值
	float m_endWeight;  //天平终值
	float m_deltaWeight[FLOW_SAMPLE_NUM];
	QTimer *m_flowRateTimer;  //计时器:用于计算流速
	

	PortSet_Ini_STR m_portsetinfo; //端口配置
	ParaSet_Ini_STR m_parasetinfo; //参数设置(质量法-分量检测)

	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent *event);
	void initTemperatureCom(); //温度采集串口
	void initBalanceCom();     //天平串口
	void initControlCom();     //阀门控制串口
	void initComOfHeatMeter();  //热量表1串口

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

	void on_btnSetFreq_clicked(); //设置频率
	void on_btnRegulate1_clicked();
	void on_btnQueryStatus_clicked();

	void on_btnParaSet_clicked();
	void on_btnStart_clicked();
	void on_btnExit_clicked();

	void slotFreshComTempValue(const QString& tempStr); //刷新温度值
	void slotFreshBalanceValue(const float& balValue);     //刷新天平数值
	
	void slotFreshMeterNo(const QString& comName, const QString& meterNo);//刷新表号
	void slotFreshMeterFlow(const QString& comName, const QString& flow); //刷新表流量
	void slotFreshMeterHeat(const QString& comName, const QString& heat); //刷新表热量
	void slotFreshMeterDate(const QString& comName, const QString& date); //刷新表日期
	void slotFreshMeterTemper(const QString& comName, const QString& tempIn, const QString& tempOut); //刷新表进出水温度

	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //继电器返回成功对应的槽函数
	void slotSetRegulateOk();

	void setValveBtnBackColor(QPushButton *btn, bool status); //设置阀门按钮背景色
	void setRegBtnBackColor(QPushButton *btn, bool status);	//设置调节阀按钮背景色

	void slotFreshFlowRate();//计算流速

	void on_btnSetVerifyStatus_clicked();//设置检定状态
	void on_btnReadMeterData_clicked(); //读表数据
	void on_btnModifyMeterNo_clicked(); //修改表号
	void on_btnModifyFlowPara_clicked(); //修改流量参数

	void on_btnOpenCom_clicked(); //打开串口
	void on_btnCloseCom_clicked();//关闭串口

private:
	Ui::DataTestDlgClass ui;

private slots:

};

#endif // DATATESTDLG_H
