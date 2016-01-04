#ifndef TOTAL_RESULT_H
#define TOTAL_RESULT_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include "resultquery_globlal.h"
#include "ui_total_result.h"

class RESULTQUERYDLG_EXPORT TotalResultDlg : public QWidget
{
	Q_OBJECT

public:
	TotalResultDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~TotalResultDlg();

public slots:
	void showEvent(QShowEvent *);
	void closeEvent(QCloseEvent *);

	void on_btnQuery_clicked();
	void on_btnExit_clicked();
	void on_btnExport_clicked();
signals:
	void signalClosed();
private:
	Ui::TotalResultClass ui;
	QSqlRelationalTableModel *model;
	QString m_conStr;//²éÑ¯Ìõ¼þ


	void initCmb();
	void getCondition();
	void queryData();
};

#endif // TOTAL_RESULT_H
