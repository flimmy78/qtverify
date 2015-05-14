#ifndef PLAPARAM_RESULT_H
#define PLAPARAM_RESULT_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include "resultquery_globlal.h"
#include "ui_plaparam_result.h"

class RESULTQUERYDLG_EXPORT PLaParamResultDlg : public QWidget
{
	Q_OBJECT

public:
	PLaParamResultDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~PLaParamResultDlg();

public slots:
		void showEvent(QShowEvent *);
		void closeEvent(QCloseEvent *);

		void on_btnQuery_clicked();
		void on_btnExit_clicked();
private:
	Ui::PlaParamResultClass ui;
	QSqlRelationalTableModel *model;
	QString m_conStr;//²éÑ¯Ìõ¼þ


	void initCmb();
	void getCondition();
	void queryData();

};
#endif//PLAPARAM_RESULT_H