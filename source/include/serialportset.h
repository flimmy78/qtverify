#ifndef SERIALPORTSET_H
#define SERIALPORTSET_H

#include <QtGui/QWidget>

#include "qtcomdlg_global.h"
#include "ui_serialportset.h"
#include "win_qextserialport.h"

class QTCOMDLG_EXPORT SerialPortSet : public QWidget
{
	Q_OBJECT

public:
	SerialPortSet(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SerialPortSet();

	void sp_anyfunc();

public slots:
	

private:
	Ui::SerialPortSetClass spsetui;
	Win_QextSerialPort *myCom;

private slots:
	void slotReadMyCom();
	void on_btnOpenCom_clicked();
	void on_btnCloseCom_clicked();
	void on_btnSendMsg_clicked();
	void on_btnClearMsg_clicked();
};

#endif // SERIALPORTSET_H
