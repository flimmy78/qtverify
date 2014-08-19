#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>

#include "ui_queryresult.h"


class QueryResult : public QWidget
{
	Q_OBJECT

public:
	QueryResult(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QueryResult();

	uint m_count;

public slots:


private:
	Ui::QueryResultClass ui;

private slots:
	void on_btnQuery_clicked();
	void on_btnInsert_clicked();
	void on_btnStop_clicked();
};

#endif // QUERYRESULT_H
