#ifndef FLOW_RESULT_H
#define FLOW_RESULT_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include "resultquery_globlal.h"
#include "ui_flowresult.h"

class RESULTQUERYDLG_EXPORT FlowResultDlg : public QWidget
{
	Q_OBJECT

public:
	FlowResultDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~FlowResultDlg();

	uint m_count;

	void initUiData();

public slots:


private:
	Ui::FlowResultClass ui;
	QSqlRelationalTableModel *model;
	QString m_conStr;//²éÑ¯Ìõ¼þ
private slots:
	void on_btnQuery_clicked();
	void on_btnStop_clicked();
	void on_btnExport_clicked();
	void on_btnExit_clicked();
private:
	void getConditon();
	void queryData();
};

#endif // FLOW_RESULT_H
