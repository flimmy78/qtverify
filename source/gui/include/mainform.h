#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>

#include "ui_mainform.h"
#include "dbmysql.h"
#include "dbsqlite.h"
#include "monsterinterface.h" //插件接口
#include "alg.h"
#include "comsetdlg.h"
#include "SetComFrm.h"
#include "qualitydlg.h"
#include "mythread.h"
#include "SetPortFrm.h"

class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainForm();

	DbMySql *dbmysqlobj;
	DbSqlite *dbsqliteobj;
	MonsterInterface *m_monster;
	CAlgorithm *m_alg;
	SetComFrm *m_setcom; //串口参数设置
	ComSetDlg *m_comdebugger;
	QualityDlg *m_qualitydlg;
	SetPortFrm *m_portSet; //端口模块设置

	void closeEvent(QCloseEvent * event);

public slots:
	void on_actionComDebuger_triggered();
	void on_actionMySql_triggered();
	void on_actionSqlite_triggered();
	void on_actionComSet_triggered();
	void on_actionPortSet_triggered();
	void on_actionQueryExcel_triggered();
	void on_actionPlugin_triggered();
	void on_actionQualityComp_triggered();
	void on_actionQualityTotal_triggered();

	void on_btnStart_clicked();
	void on_btnSave_clicked();
	void on_btnPara_clicked();
	void on_btnAirOut_clicked();

private:
	Ui::qMainFormClass ui;
};

extern MainForm *g_mainform;

#endif // MAINFORM_H
