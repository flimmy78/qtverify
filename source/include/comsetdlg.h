#ifndef COMSETDLG_H
#define COMSETDLG_H

#include <QtGui/QWidget>

#include "comsetdlg_global.h"
#include "ui_comsetdlg.h"
#include "qextserialport.h"


typedef struct ComInfo_Struct
{
	QString portName; //������
	int     baudRate; //������
	int     dataBit;  //����λ
	int     parity;   //��żУ��
	int     stopBit;  //ֹͣλ
}ComInfoStruct;


class COMSETDLG_EXPORT ComSetDlg : public QWidget
{
	Q_OBJECT

public:
	ComSetDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ComSetDlg();

	QextSerialPort *myCom;

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
