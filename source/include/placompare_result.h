#ifndef PLACOMPARE_RESULT_H
#define PLACOMPARE_RESULT_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include "resultquery_globlal.h"
#include "ui_placompare_result.h"

class RESULTQUERYDLG_EXPORT PLaCompareResultDlg : public QWidget
{
	Q_OBJECT

public:
	PLaCompareResultDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~PLaCompareResultDlg();

public slots:
	void showEvent(QShowEvent *);
	void closeEvent(QCloseEvent *);

	void on_btnQuery_clicked();
	void on_btnExit_clicked();
private:
	Ui::PlaCompResultClass ui;
	QSqlRelationalTableModel *model;
	QString m_conStr;//²éÑ¯Ìõ¼þ


	void initCmb();
	void getCondition();
	void queryData();

};

#endif//PLACOMPARE_RESULT_H