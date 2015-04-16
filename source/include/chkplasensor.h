#ifndef CHKPLASENSOR_H
#define CHKPLASENSOR_H

#include <QtGui/QWidget>
#include <QSettings>

#include "basedef.h"
#include "ui_chkplasensor.h"
#include "systemsetdlg_global.h"

class SYSTEMSETDLG_EXPORT chkplasensorDlg : public QWidget
{
	Q_OBJECT

public:
	chkplasensorDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~chkplasensorDlg();

public slots:
		void closeEvent(QCloseEvent *event);

		void on_btn_calc_clicked();
		void on_btn_save_clicked();
		void on_btn_default_clicked();
		void on_btn_exit_clicked();

private:
	Ui::ChkPlaSensorClass ui;

	QSettings* m_config;
	
private:
	void readConfig();
	void saveConfig();
	void calcConfig();
};
#endif//CHKPLASENSOR_H