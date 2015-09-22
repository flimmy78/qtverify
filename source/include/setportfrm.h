#ifndef SETPORTFRM_H
#define SETPORTFRM_H

#include <QtGui/QWidget>
#include <QtXml/QtXml>

#include "comobject.h"
#include "readcomconfig.h"
#include "ui_setportfrm.h"
#include "systemsetdlg_global.h"

class SYSTEMSETDLG_EXPORT SetPortFrm : public QWidget
{
	Q_OBJECT

public slots:

public:
	SetPortFrm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SetPortFrm();

private:
	Ui::SetPortDlgClass gui;
	QSettings *PortSet;
	ReadComConfig *m_readComConfig;
	ControlComObject *m_controlObj;
	QMap<int, bool> m_valveStatus;//<·§ÃÅ¶Ë¿ÚºÅ£¬·§ÃÅ×´Ì¬>
	
	void initControlCom();
	void initValveStatus();//³õÊ¼»¯·§ÃÅ×´Ì¬
	void InstallIni();
	void WriteIni();

private slots:
	void on_btn_Exit_clicked();
	void on_btn_Save_clicked();

	void on_btnRoutine_1_clicked();
	void on_btnRoutine_2_clicked();
	void on_btnRoutine_3_clicked();
	void on_btnRoutine_4_clicked();
	void on_btnRoutine_5_clicked();
	void on_btnRoutine_6_clicked();
	void on_btnRoutine_7_clicked();
	void on_btnRoutine_8_clicked();
};

#endif // SETPORTFRM_H