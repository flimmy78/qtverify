#ifndef WATER_RESULT_H
#define WATER_RESULT_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include "resultquery_globlal.h"
#include "ui_water_result.h"

class RESULTQUERYDLG_EXPORT WaterResultDlg : public QWidget
{
	Q_OBJECT

public:
	WaterResultDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~WaterResultDlg();

	uint m_count;

	void initUiData();

public slots:
	void closeEvent(QCloseEvent *);
signals:
	void signalClosed();

private:
	Ui::WaterResultClass ui;
	QSqlRelationalTableModel *model;
	QString m_conStr;//²éÑ¯Ìõ¼þ

private slots:
	void on_btnQuery_clicked();
	void on_btnStop_clicked();
	void on_btnExport_clicked();
	void on_btnExit_clicked();
	void on_btnImport_clicked();

private:
	void getCondition();
	void queryData();
};

#endif // WATER_RESULT_H
