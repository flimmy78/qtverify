#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>

#include "ui_mainform.h"
#include "serialportset.h"
#include "dbmysql.h"
#include "dbsqlite.h"
#include "alg.h"

class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainForm();

	alg *m_algobj;
	SerialPortSet *spobj;
	DbMySql *dbmysqlobj;
	DbSqlite *dbsqliteobj;

public slots:
	void on_action_spset_triggered();
	void on_action_mysql_triggered();
	void on_action_sqlite_triggered();
	void on_action_queryExcel_triggered();
	void on_btnStart_clicked();
	void on_btnSave_clicked();

private:
	Ui::qMainFormClass ui;
};

#endif // MAINFORM_H
