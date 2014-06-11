#ifndef SERIALPORTSET_H
#define SERIALPORTSET_H

#include <QtGui/QWidget>

#include "comsetdlg_global.h"
#include "ui_serialportset.h"
#include "win_qextserialport.h"

class COMSETDLG_EXPORT SerialPortSet : public QWidget
{
	Q_OBJECT

public:
	SerialPortSet(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SerialPortSet();

	Win_QextSerialPort *myCom;

	void sp_anyfunc();

public slots:
	

private:
	Ui::SerialPortSetClass spsetui;

private slots:
	void slotReadMyCom();
	void on_btnOpenCom_clicked();
	void on_btnCloseCom_clicked();
	void on_btnSendMsg_clicked();
	void on_btnClearMsg_clicked();
};

#endif // SERIALPORTSET_H
