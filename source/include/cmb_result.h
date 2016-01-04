#ifndef CMB_RESULT_H
#define CMB_RESULT_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include "resultquery_globlal.h"
#include "ui_cmb_result.h"

class RESULTQUERYDLG_EXPORT CmbResultDlg : public QWidget
{
	Q_OBJECT

public:
	CmbResultDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CmbResultDlg();

public slots:
	void showEvent(QShowEvent *);
	void closeEvent(QCloseEvent *);

	void on_btnQuery_clicked();
	void on_btnExit_clicked();
	void on_btnExport_clicked();
signals:
	void signalClosed();
private:
	Ui::CmbResultClass ui;
	QSqlRelationalTableModel *model;
	QString m_conStr;//²éÑ¯Ìõ¼þ


	void initCmb();
	void getCondition();
	void queryData();
};

#endif // CMB_RESULT_H
