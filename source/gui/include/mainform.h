#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>

#include "ui_mainform.h"
#include "dbmysql.h"
#include "queryresult.h"
#include "setcomfrm.h"
#include "datatestdlg.h"
#include "setportfrm.h"
#include "masterslaveset.h"
#include "weightmethod.h"

class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainForm();

	DbMySql *m_mySql;
	QueryResult *m_query;
	CAlgorithm *m_alg;
	SetComFrm *m_setcom; //串口参数设置
	DataTestDlg *m_datatestdlg; //采集与控制测试程序
	SetPortFrm *m_portSet; //端口模块设置
	CMasterSlave *m_masterslave; //主机-从机设置
	WeightMethodDlg *m_weightDlg; //质量法检定界面
	QProcess *m_comProcess; //调用外部串口调试工具

	void closeEvent(QCloseEvent * event);

public slots:
	void on_actionComDebuger_triggered();
	void on_actionMySql_triggered();
	void on_actionQuery_triggered();
	void on_actionComSet_triggered();
	void on_actionPortSet_triggered();
	void on_actionQueryExcel_triggered();
	void on_actionWeightComp_triggered();
	void on_actionWeightTotal_triggered();
	void on_actionExit_triggered();
	void on_actionAbout_triggered();
	void on_actionMasterSlaveSet_triggered();
	void on_actionTest_triggered();
	void on_actionDefault_triggered();
	void on_actionClassic_triggered();
	void on_actionFashion_triggered();
	void on_actionEnglish_triggered();
	void on_actionChinese_triggered();

private:
	Ui::qMainFormClass ui;
};

extern MainForm *g_mainform;

#endif // MAINFORM_H
