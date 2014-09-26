#ifndef DBMYSQL_H
#define DBMYSQL_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>

#include "ui_dbmysql.h"

class DbMySql : public QWidget
{
	Q_OBJECT

public:
	DbMySql(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DbMySql();

	QSqlDatabase m_db;

	void closeEvent(QCloseEvent * event);

public slots:

private:
	Ui::DbMySqlClass ui;

private slots:
	void on_btnConnect_clicked();
	void on_btnQuery_clicked();

};

#endif // DBMYSQL_H
