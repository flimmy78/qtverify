#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include <QtGui/QCloseEvent>
#include <QtCore/QProcess>

#include "ui_mainform.h"

class DbMySql;
class FlowResultDlg;
class SetComDlg;
class DataTestDlg;
class SetPortFrm;
class CMasterSlave;
class CAlgorithm;
class FlowWeightDlg;
class FlowStandardDlg;
class TotalWeightDlg;
class TotalStandardDlg;
class CalcDlg;
class CmbVerifyDlg;
class StdMtrParaSet;
class StdMtrCoeCorrect;
class tvercompDlg;
class tverparamDlg;
class stdplasensorDlg;
class chkplasensorDlg;
class PlaResultDlg;
class CalcResultDlg;
class CmbResultDlg;
class TotalResultDlg;

class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainForm();

	DbMySql *m_mySql;
	
	CAlgorithm *m_alg;
	SetComDlg *m_setcom; //串口参数设置
	DataTestDlg *m_datatestdlg; //采集与控制测试程序
	SetPortFrm *m_portSet; //端口模块设置
	CMasterSlave *m_masterslave; //主机-从机设置
	QProcess *m_comProcess; //调用外部串口调试工具
	FlowWeightDlg *m_flowWeightDlg;      //流量检定(质量法)
	FlowStandardDlg *m_flowStandardDlg;  //流量检定(标准表法)
	TotalWeightDlg *m_totalWeightDlg;    //总量检定(标准表法)
	TotalStandardDlg *m_totalStandardDlg;//总量检定(标准表法)

	CalcDlg *m_calcDlg; //计算器检定
	CmbVerifyDlg *m_cmbVerifyDlg; //组合检定
	tvercompDlg *m_tvercompDlg; //温度检定(比较法)
	tverparamDlg *m_tverparaDlg; //温度检定(参数法)

	StdMtrParaSet *m_stdParaSet; //标准表参数设定
	StdMtrCoeCorrect *m_stdCoeCorrect; //标准表系数标定
	stdplasensorDlg *m_stdPtParaDlg; //标准铂电阻参数设定
	chkplasensorDlg *m_chkPtParaDlg; //被检铂电阻参数设置

	///////////////////////////////////////////////
	////              检定结果              ////////
	///////////////////////////////////////////////
	FlowResultDlg *m_flowResultDlg;
	PlaResultDlg* m_PlaResultDlg;
	CalcResultDlg* m_CalcResultDlg;
	CmbResultDlg* m_CmbResultDlg;
	TotalResultDlg* m_TotalResultDlg;

	void closeEvent(QCloseEvent * event);

public slots:
	//SystemSet
	void on_actionComSet_triggered();
	void on_actionPortSet_triggered();
	void on_actionComDebuger_triggered();
	void on_actionDataTest_triggered();
	void on_actionStdMtrParaSet_triggered();
	void on_actionStdMtrCoeCorrect_triggered();
	void on_actionStdPtParaSet_triggered();
	void on_actionPtParaSet_triggered();
	
	void on_actionMasterSlaveSet_triggered();
	void on_actionMySql_triggered();

	//Component Verify
	void on_actionFlowWeight_triggered();
	void on_actionFlowStandard_triggered();
	void on_actionTemperCompare_triggered();
	void on_actionTemperPara_triggered();
	void on_actionCalculator_triggered();
	void on_actionCombine_triggered();

	//Total Verify
	void on_actionTotalWeight_triggered();
	void on_actionTotalStandard_triggered();

	//Data Query
	void on_actionFlowResult_triggered();
	void on_actionTotalResult_triggered();
	void on_actionTemperResult_triggered();
	void on_actionCalculatorResult_triggered();
	void on_actionCombineResult_triggered();
	void on_actionQueryExcel_triggered();

	//About
	void on_actionExit_triggered();
	void on_actionAbout_triggered();

	//Style
	void on_actionDefault_triggered();
	void on_actionClassic_triggered();
	void on_actionFashion_triggered();

	//Language
	void chaneLanguage(QString lang);
	void on_actionEnglish_triggered();
	void on_actionChinese_triggered();

	//
	void slotFlowWeightClosed();

private:
	Ui::qMainFormClass ui;
};

extern MainForm *g_mainform;

#endif // MAINFORM_H
