#ifndef QUALITYDLG_H
#define QUALITYDLG_H

#include <QtGui/QWidget>

#include "qualitydlg_global.h"
#include "ui_qualitydlg.h"
#include "parasetdlg.h"
#include "comthread.h"

#include "qextserialport.h"

#define TIME_OUT	10		//延时，TIME_OUT是串口读写的延时


class TempComObject : public QObject 
{       
	Q_OBJECT  

public: 
	TempComObject();
	~TempComObject();

	QextSerialPort *m_tempCom;

signals:
	void tempValueIsReady(const QString& tempStr);

public slots:
	void myslot();
	void openTemperatureCom();
	void readTemperatureComBuffer();
};    

class QUALITYDLG_EXPORT QualityDlg : public QWidget
{
	Q_OBJECT

public:
	QualityDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QualityDlg();

	ParaSetDlg *m_paraset;

	ComThread m_tempThread;
 	TempComObject *m_tempObj;


public slots:
	void on_btnWaterIn_clicked();
// 	void on_btnWaterOut_clicked();
// 	void on_btnWaterValve1_clicked();
// 	void on_btnWaterValve2_clicked();
// 	void on_btnWaterValve3_clicked();
// 	void on_btnWaterValve4_clicked();

	void on_btnParaSet_clicked();
	void on_btnExit_clicked();

	void setValveBtnBackColor(QPushButton *btn, bool isOpen);

	void freshComTempValue(const QString& tempStr);

private:
	Ui::QualityDlgClass ui;

private slots:

};

#endif // QUALITYDLG_H
