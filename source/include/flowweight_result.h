#ifndef FLOWWEIGHT_RESULT_H
#define FLOWWEIGHT_RESULT_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include "resultquery_globlal.h"
#include "ui_flowresult.h"

class RESULTQUERYDLG_EXPORT FlowWeightResultDlg : public QWidget
{
	Q_OBJECT

public:
	FlowWeightResultDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~FlowWeightResultDlg();

	uint m_count;

	void initUiData();

public slots:


private:
	Ui::FlowResultClass ui;
	QSqlRelationalTableModel *model;
	QString m_conStr;//²éÑ¯Ìõ¼þ
private slots:
	void on_btnQuery_clicked();
	void on_btnInsert_clicked();
	void on_btnStop_clicked();
	void on_btnExport_clicked();
	void on_btnExit_clicked();
private:
	void getConditon();
};

#endif // FLOWWEIGHT_RESULT_H
