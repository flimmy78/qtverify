#ifndef DBSQLITE_H
#define DBSQLITE_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>

#include "ui_dbsqlite.h"

class DbSqlite : public QWidget
{
	Q_OBJECT

public:
	DbSqlite(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DbSqlite();

	QSqlDatabase db;
	uint m_count;

public slots:


private:
	Ui::DbSqliteClass dbsqliteui;

	private slots:
		void on_btnConnect_clicked();
		void on_btnQuery_clicked();
		void on_btnOK_clicked();
		void on_btnInsert_clicked();
		void on_btnStop_clicked();
};

#endif // DBSQLITE_H
