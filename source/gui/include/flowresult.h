#ifndef FLOWRESULT_H
#define FLOWRESULT_H

#include <QtGui/QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>

#include "ui_flowresult.h"

class FlowResultDlg : public QWidget
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
private slots:
	void on_btnQuery_clicked();
	void on_btnInsert_clicked();
	void on_btnStop_clicked();
	void on_btnExport_clicked();
	void on_btnExit_clicked();
};

#endif // FLOWRESULT_H
