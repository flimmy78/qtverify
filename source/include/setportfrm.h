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

signals:
	void signalClosed();
public:
	SetPortFrm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SetPortFrm();

	void closeEvent(QCloseEvent * event);

private:
	Ui::SetPortDlgClass gui;
	QSettings *PortSet;
	ReadComConfig m_readComConfig;
	ControlComObject *m_controlObj;
	ControlComObject *m_controlObj2; //2#¿ØÖÆ°å
	QMap<int, bool> m_valveStatus;//<·§ÃÅ¶Ë¿ÚºÅ£¬·§ÃÅ×´Ì¬>
	
	void initControlCom();
	void initControlCom2();
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
	void on_btnRoutine_9_clicked();
	void on_btnRoutine_10_clicked();
	void on_btnRoutine_11_clicked();
	void on_btnRoutine_12_clicked();
	void on_btnRoutine_13_clicked();
	void on_btnRoutine_14_clicked();
	void on_btnRoutine_15_clicked();
	void on_btnRoutine_16_clicked();
};

#endif // SETPORTFRM_H