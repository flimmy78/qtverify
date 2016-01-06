#ifndef STDCORRECTPRA_H
#define STDCORRECTPRA_H

#include <QtGui/QWidget>
#include <QByteArray>
#include <QSettings>
#include <QtGui/QDataWidgetMapper>

#include "ui_stdcorrectpra.h"
#include "systemsetdlg_global.h"
#include "stdmtrcoecorrect.h"

#define COL_FP		0
#define COL_QUAN	1

#define RELEASE_PTR(ptr)		if (ptr != NULL)\
								{\
									delete ptr;\
									ptr = NULL;\
								}

#define INIT_TABLE(tablewdg)	ui->tablewdg->setRowCount(FLOW_POINTS);\
								ui->tablewdg->setColumnCount(2);\
								ui->tablewdg->verticalHeader()->setVisible(false);\
								ui->tablewdg->setHorizontalHeaderLabels(header);\
								for (int i=0; i<ui->tablewdg->rowCount(); i++)\
								{\
									ui->tablewdg->setItem(i, COL_FP, new QTableWidgetItem(QString("")));\
									ui->tablewdg->setItem(i, COL_QUAN, new QTableWidgetItem(QString("")));\
								}\
								ui->tablewdg->resize(200, 400);


class SYSTEMSETDLG_EXPORT StdMtrCorrectPra : public QWidget
{
	Q_OBJECT

public:
	StdMtrCorrectPra(QWidget *parent = 0, Qt::WFlags flags = 0);
	~StdMtrCorrectPra();

public slots:
	void showEvent(QShowEvent * event);
	void closeEvent(QCloseEvent * event);
	void resizeEvent(QResizeEvent * event);

	void on_btnSave_clicked();
	void on_btnExit_clicked();
	void on_tableWidget_0_cellChanged(int row, int column);
	void on_tableWidget_1_cellChanged(int row, int column);
	void on_tableWidget_2_cellChanged(int row, int column);
	void on_tableWidget_3_cellChanged(int row, int column);
signals:
	void signalClosed();

private slots:

private:
	Ui::StdCorrectPraClass* ui;
	QRegExp m_rx;
	QSettings* m_stdCorrectConfig;

	void initTables();
	void installParas();
	void writeParas();
	void releaseSource();
};
#endif //STDCORRECTPRA_H