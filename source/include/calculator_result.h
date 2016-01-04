#ifndef CALCULATOR_RESULT_H
#define CALCULATOR_RESULT_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include "resultquery_globlal.h"
#include "ui_calculator_result.h"

class RESULTQUERYDLG_EXPORT CalcResultDlg : public QWidget
{
	Q_OBJECT

public:
	CalcResultDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CalcResultDlg();

public slots:
	void showEvent(QShowEvent *);
	void closeEvent(QCloseEvent *);

	void on_btnQuery_clicked();
	void on_btnExit_clicked();
signals:
	void signalClosed();
private:
	Ui::CalcResultDlgClass ui;
	QSqlRelationalTableModel *model;
	QString m_conStr;//²éÑ¯Ìõ¼þ


	void initCmb();
	void getCondition();
	void queryData();

};

#endif//CALCULATOR_RESULT_H