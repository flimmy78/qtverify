#ifndef COMSETDLG_H
#define COMSETDLG_H

#include <QtGui/QWidget>

#include "comsetdlg_global.h"
#include "ui_comsetdlg.h"
#include "win_qextserialport.h"

class COMSETDLG_EXPORT ComSetDlg : public QWidget
{
	Q_OBJECT

public:
	ComSetDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ComSetDlg();

	Win_QextSerialPort *myCom;

	void sp_anyfunc();

public slots:
	

private:
	Ui::ComSetDlgClass ui;

private slots:
	void slotReadMyCom();
	void on_btnOpenCom_clicked();
	void on_btnCloseCom_clicked();
	void on_btnSendMsg_clicked();
	void on_btnClearMsg_clicked();
};

#endif // COMSETDLG_H
