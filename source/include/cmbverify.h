#ifndef CMBVERIFY_H
#define CMBVERIFY_H

#ifdef CMBVERIFY_DLL
#  ifdef WIN32
#  define CMBVERIFY_EXPORT __declspec(dllexport)
#  else
#  define CMBVERIFY_EXPORT
#  endif
#else
#  ifdef WIN32
#  define CMBVERIFY_EXPORT __declspec(dllimport)
#  else
#  define CMBVERIFY_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>

#include "ui_cmbverify.h"
#include "protocol.h"
#include "comobject.h"
#include "readcomconfig.h"
#include "algorithm.h"
#include "cmbparam.h"

#define READ_STI1062A_TIMEOUT	200//定时器间隔

#define COL_NUM			12//列数量
#define COL_BTN_NUM		3//读取表数据的按钮数量
#define COL_SN			0//热表序列号
#define COL_E0			1//初始热值
#define COL_V0			2//初始体积流量
#define COL_V1			3//最终体积流量
#define COL_E1			4//最终热值
#define COL_IN_T		5//进口温度值
#define COL_OUT_T		6//出口温度值
#define COL_DELTA_E		7//模拟热值
#define COL_DELTA_V		8//模拟体积
#define COL_STD_E		9//标准热值
#define COL_ERR			10//示值误差
#define COL_READ_DATA	11//读表数据


#define MAX_METER_NUM	20//最大检表数

class CMBVERIFY_EXPORT CmbVerifyDlg : public QWidget
{
	Q_OBJECT

public:
	CmbVerifyDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CmbVerifyDlg();


public slots:
	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent *);

	void on_btn_collection_clicked();//采集标准温度计数据
	void on_btn_stop_clicked();//停止采集标准温度计

	void on_tableWidget_cellChanged(int row, int col);
	void on_btnPara_clicked();
	void on_btnStart_clicked();
	void on_btnSave_clicked();
	void on_btnExit_clicked();
	void on_lineEdit_min_theta_textEdited(const QString & text);
	void on_lineEdit_std_in_t_textChanged(const QString & text);
	void on_lineEdit_std_out_t_textChanged(const QString & text);
private slots:
	void freshCmbParam(void);
	void startVefifySlot(void);
	void on_btnGroup_unit_clicked(int);
	void on_btnGroup_pos_clicked(int);

	void sendCommands();
	void clearTempComObjs();
	void setStdTempUi(const QString &tempStr);//标准温度计各数据读取结果

	void slotReadData(const int &);//读取表数据

	void slotSetMeterNumber(const QString& comName, const QString& meterNumber);//获取表号
	void slotSetMeterFlow(const QString& comName, const float& flow);//获取体积流量
	void slotSetMeterHeat(const QString& portName, const QString& heat);//获取热值
	void slotSetMeterTemp(const QString& portName, const QString& tempIn, const QString& tempOut);//获取进出口温度
signals:
	void vefifyCanStart(void);//可以开始检测
	void tempDiffAchived(void);//恒温槽达到设定的温差
private:
	Ui::CmbVerifyClass ui;
	CmbParamDlg* m_CmbParamDlg;//参数设置窗体
	CAlgorithm* m_algo;//计算热值
	QButtonGroup *m_btnGroup_unit; //安装位置 0:进口；1:出口
	QButtonGroup *m_btnGroup_pos; //能量单位 0:MJ;1:kwh

	/*----------计算中用到的关键参数-----------*/
	int m_current_pos;//安装位置
	bool m_pos_selected;//安装位置已选择
	int m_current_unit;//热量单位
	bool m_unit_selected;//计量单位已选则

	float m_std_temperate_in;//标准温度计进口温度
	float m_std_temperate_out;//标准温度计出口温度

	float m_min_tempdiff;//最小温差
	bool m_min_tempdiff_set;//最小温差已设置

	bool m_delta_temp_achieved;//当前恒温槽达到检定温差

	float m_stdErrLmtByGrade;//根据表的等级得出的示值误差限
	/*----------计算中用到的关键参数end--------*/
	Cmb_Verify_Record_PTR m_recPtr; //有效的检定记录
	QString m_timeStamp; //记录时间戳

	QSettings* m_param_config;//操作参数配置文件


	void initUi();//初始化Ui设置
	void initTbl();
	void chkIfCanStartVerify();//检测是否可以开始检测
	void stdTempChanged();//标准温度计读数变化
	float getEnthalpyDiffByTemper(float inT, float outT); //根据进口温度和出口温度获取焓差
	float getEnergyByEnthalpy(float analogV, float inTemper, float outTemper);//焓差法计算理论热量
	float getStdEnergy(float analogV);//根据标准温度计计算热量
	float getKCoeByTemper(float inTemper, float outTemper);//计算K系数
	/*----------读取标准温度计-----------*/
	QTimer* m_sendTimer;//定时发送命令
	ComThread m_tempThread; //标准温度计采集线程
	sti1062Acommand m_StdCommand;//读取标准温度计的命令
	ReadComConfig* m_readComConfig;//串口设置
	Sti1062aComObject* m_tempObj;//标准温度计串口对象
	/*----------读取标准温度计end--------*/

	/*-------------读取表数据----------*/
	MeterComObject *m_meterObj;
	ComThread *m_meterThread;	//热量表通讯线程
	void initMeterCom();       //热量表串口
	bool m_vol0_is_read[MAX_METER_NUM];//流量初值已被读取
	bool m_eng0_is_read[MAX_METER_NUM];//热量初值已被读取

	/*--------------------------------*/

	//void addNewTblRow(QSignalMapper *);//添加一个表位
	int saveVerifyRecords(); //统计有效的检定结果数量
};

#endif //CMBVERIFY_H