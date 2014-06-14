#ifndef SETCOMFRM_H
#define SETCOMFRM_H

#include <QtGui/QWidget>

#include "ui_SetComFrm.h"
#include "comsetdlg_global.h"

class COMSETDLG_EXPORT SetComFrm : public QWidget
{
	Q_OBJECT

public slots:

public:
	SetComFrm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SetComFrm();

private:
	Ui::SetComFrm gui;

	/*∂¡»°≈‰÷√*/
	char* ReadConfigByName();
	char* ReadValeConfig();
	char* ReadBalanceConfig();
	char* ReadTempConfig();
	char* ReadStdTempConfig();
	char* ReadMeterConfigByNum();
	/*–¥»Î≈‰÷√*/
	int WriteConfigByName();
	int WriteValeConfig();
	int WriteBalanceConfig();
	int WriteTempConfig();
	int WriteStdTempConfig();
	int WriteMeterConfigByNum();

private slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();
};

#endif // SETCOMFRM_H