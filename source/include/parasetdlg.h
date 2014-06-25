#ifndef PARASETDLG_H
#define PARASETDLG_H

#include <QtGui/QWidget>

#include "ui_parasetdlg.h"

class ParaSetDlg : public QWidget
{
	Q_OBJECT

public:
	ParaSetDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ParaSetDlg();

	void closeEvent(QCloseEvent * event);

public slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();

private:
	Ui::ParaSetDlgClass ui;

private slots:

};

#endif // PARASETDLG_H
