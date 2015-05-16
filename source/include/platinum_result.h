#ifndef PLATINUM_RESULT_H
#define PLATINUM_RESULT_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include "resultquery_globlal.h"
#include "ui_platinum_result.h"

class RESULTQUERYDLG_EXPORT PlaResultDlg : public QWidget
{
	Q_OBJECT

public:
	PlaResultDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~PlaResultDlg();

public slots:
	void showEvent(QShowEvent *);
	void closeEvent(QCloseEvent *);

	void on_btnQuery_clicked();
	void on_btnExit_clicked();
private:
	Ui::PlaResultDlgClass ui;
	QSqlRelationalTableModel *model;
	QString m_conStr;//²éÑ¯Ìõ¼þ


	void initCmb();
	void getCondition();
	void queryData();

};

#endif//PLATINUM_RESULT_H