#ifndef SETPORTFRM_H
#define SETPORTFRM_H

#include <QtGui/QWidget>
#include <QtXml/QtXml>

#include "ui_SetPortFrm.h"
#include "comsetdlg_global.h"

class COMSETDLG_EXPORT SetPortFrm : public QWidget
{
	Q_OBJECT

public slots:

public:
	SetPortFrm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SetPortFrm();

private:
	Ui::SetPortFrm gui;
	QString IniPath;
	QSettings *PortSet;
	void InstallIni();
	void WriteIni();

private slots:
	void on_btn_Exit_clicked();
	void on_btn_Save_clicked();
};

#endif // SETPORTFRM_H