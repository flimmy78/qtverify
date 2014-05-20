#ifndef QTVERIFY_H
#define QTVERIFY_H

#include <QtGui/QMainWindow>

#include "ui_qtverify.h"
#include "serialportset.h"
#include "dbshow.h"
#include "alg.h"

class qtVerify : public QMainWindow
{
	Q_OBJECT

public:
	qtVerify(QWidget *parent = 0, Qt::WFlags flags = 0);
	~qtVerify();

	alg *m_algobj;
	SerialPortSet *spobj;
	DbShow *dbshowobj;

public slots:
	void slotSerialPortSet();
	void slotDBShow();
	void slotCalc();
	void slotDataQuery();
	void on_pushButton_Save_clicked();

private:
	Ui::qtVerifyClass ui;
};

#endif // QTVERIFY_H
