#ifndef QUALITYDLG_H
#define QUALITYDLG_H

#include <QtGui/QWidget>

#include "qualitydlg_global.h"
#include "ui_qualitydlg.h"
#include "parasetdlg.h"
#include "comthread.h"
#include "ReadComConfig.h"

#define TIMEOUT_TEMPER  500 //每0.5秒钟请求一次温度值

class QUALITYDLG_EXPORT QualityDlg : public QWidget
{
	Q_OBJECT

public:
	QualityDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QualityDlg();

	ParaSetDlg *m_paraset;

	ReadComConfig *m_readComConfig;//读串口设置

	ComThread m_tempThread;  //温度采集线程
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

	ComThread m_valveThread;  //阀门控制线程
	ValveComObject *m_valveObj;
	bool m_valveWaterInStatus;

	ComThread m_balanceThread; //天平采集线程
	BalanceComObject *m_balanceObj;

	void closeEvent(QCloseEvent * event);

public slots:
	void on_btnWaterIn_clicked();
	void on_btnWaterOut_clicked();

	void on_btnParaSet_clicked();
	void on_btnSave_clicked();
	void on_btnExit_clicked();

	void setBtnBackColor(QPushButton *btn, bool status);

	void slotFreshComTempValue(const QString& tempStr); //刷新温度值
	void slotFreshBalanceValue(const QString& Str);     //刷新天平数值

	void initTemperatureCom(); //温度采集串口

	void initValveControlCom();//阀门控制串口 
	void slotSetValveBtnStatus(const bool& status );

	void initBalanceCom();     //天平串口
private:
	Ui::QualityDlgClass ui;

private slots:

};

#endif // QUALITYDLG_H
