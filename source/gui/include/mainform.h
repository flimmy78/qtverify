#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>

#include "ui_mainform.h"
#include "dbmysql.h"
#include "dbsqlite.h"
#include "monsterinterface.h" //²å¼þ½Ó¿Ú
#include "alg.h"
#include "comsetdlg.h"
#include "SetComFrm.h"
#include "qualitydlg.h"
#include "mythread.h"

// #define  DELETE_ARRAY(a)      {if ( a ) delete []a, a = NULL;}


class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainForm();

	DbMySql *dbmysqlobj;
	DbSqlite *dbsqliteobj;
	MonsterInterface *m_monster;
	CAlg *m_alg;
	SetComFrm *m_setcom;
	ComSetDlg *m_spset;
	QualityDlg *m_qualitydlg;


public slots:
	void on_action_spset_triggered();
	void on_action_mysql_triggered();
	void on_action_sqlite_triggered();
	void on_actionComSet_triggered();
	void on_action_queryExcel_triggered();
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
