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

	QSqlDatabase db;

public slots:


private:
	Ui::DbMySqlClass dbmysqlui;

private slots:
	void slotConnectMySqlDataBase();
	void slotQueryData();

};

#endif // DBMYSQL_H
