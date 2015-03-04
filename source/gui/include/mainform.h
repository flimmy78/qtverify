#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include <QtGui/QCloseEvent>
#include <QtCore/QProcess>

#include "ui_mainform.h"

class DbMySql;
class FlowResultDlg;
class SetComFrm;
class DataTestDlg;
class SetPortFrm;
class CMasterSlave;
class CAlgorithm;
class FlowWeightDlg;
class FlowStandardDlg;
class TotalWeightDlg;
class TotalStandardDlg;
class CalcDlg;

class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainForm();

	DbMySql *m_mySql;
	FlowResultDlg *m_flowResultDlg;
	CAlgorithm *m_alg;
	SetComFrm *m_setcom; //串口参数设置
	DataTestDlg *m_datatestdlg; //采集与控制测试程序
	SetPortFrm *m_portSet; //端口模块设置
	CMasterSlave *m_masterslave; //主机-从机设置
	QProcess *m_comProcess; //调用外部串口调试工具
	FlowWeightDlg *m_flowWeightDlg;      //流量检定(质量法)
	FlowStandardDlg *m_flowStandardDlg;  //流量检定(标准表法)
	TotalWeightDlg *m_totalWeightDlg;    //总量检定(标准表法)
	TotalStandardDlg *m_totalStandardDlg;//总量检定(标准表法)

	CalcDlg *m_calcDlg; //计算器检定

	void closeEvent(QCloseEvent * event);

public slots:
	//SystemSet
	void on_actionComSet_triggered();
	void on_actionPortSet_triggered();
	void on_actionComDebuger_triggered();
	void on_actionDataTest_triggered();
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

private:
	Ui::qMainFormClass ui;
};

extern MainForm *g_mainform;

#endif // MAINFORM_H
