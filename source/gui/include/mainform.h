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
	void slotSerialPortSet();
	void slotDBShow_MySql();
	void slotDBShow_Sqlite();
	void slotQueryExcel();
	void on_btnStart_Clicked();
	void on_btnSave_clicked();

private:
	Ui::qMainFormClass ui;
};

#endif // MAINFORM_H
