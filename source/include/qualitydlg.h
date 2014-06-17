#ifndef QUALITYDLG_H
#define QUALITYDLG_H

#include <QtGui/QWidget>

#include "qualitydlg_global.h"
#include "ui_qualitydlg.h"
#include "parasetdlg.h"
#include "comthread.h"

#define TIMEOUT_TEMPER  500 //ÿ0.5��������һ���¶�ֵ

class QUALITYDLG_EXPORT QualityDlg : public QWidget
{
	Q_OBJECT

public:
	QualityDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QualityDlg();

	ParaSetDlg *m_paraset;

	ComThread m_tempThread;  //�¶Ȳɼ��߳�
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

	ComThread m_valveThread;  //���ſ����߳�
	ValveComObject *m_valveObj;

	ComThread m_balanceThread; //��ƽ�ɼ��߳�
	BalanceComObject *m_balanceObj;



public slots:
	void on_btnWaterIn_clicked();

	void on_btnParaSet_clicked();
	void on_btnExit_clicked();

	void setValveBtnBackColor(QPushButton *btn, bool isOpen);

	void slotFreshComTempValue(const QString& tempStr); //ˢ���¶�ֵ
	void slotFreshBalanceValue(const QString& Str);     //ˢ����ƽ��ֵ

	void initTemperatureCom(); //�¶Ȳɼ�����

	void initValveControlCom();//���ſ��ƴ��� 
	void slotSetValveBtnStatus(const int& isOpen );

	void initBalanceCom();     //��ƽ����
private:
	Ui::QualityDlgClass ui;

private slots:

};

#endif // QUALITYDLG_H
