#ifndef DBSHOW_H
#define DBSHOW_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>

#include "ui_dbshow.h"

class DbShow : public QWidget
{
	Q_OBJECT

public:
	DbShow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DbShow();

	QSqlDatabase db;

public slots:


private:
	Ui::DBShowClass dbshowui;

private slots:
	void slotConnectMySqlDataBase();
	void slotQueryData();

};

#endif // DBSHOW_H
