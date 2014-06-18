#ifndef QUALITYDLG_H
#define QUALITYDLG_H

#include <QtGui/QWidget>

#include "qualitydlg_global.h"
#include "ui_qualitydlg.h"
#include "parasetdlg.h"
#include "comthread.h"
#include "ReadComConfig.h"

#define TIMEOUT_TEMPER  500 //ÿ0.5��������һ���¶�ֵ

class QUALITYDLG_EXPORT QualityDlg : public QWidget
{
	Q_OBJECT

public:
	QualityDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QualityDlg();

	ParaSetDlg *m_paraset;

	ReadComConfig *m_readComConfig;//����������

	ComThread m_tempThread;  //�¶Ȳɼ��߳�
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

	ComThread m_valveThread;  //���ſ����߳�
	ControlComObject *m_controlObj;
	bool m_valveWaterInStatus; //��ˮ����״̬
	bool m_Valve1Status;  //�������㷧��״̬

	ComThread m_balanceThread; //��ƽ�ɼ��߳�
	BalanceComObject *m_balanceObj;

	void closeEvent(QCloseEvent * event);

public slots:
	void on_btnWaterIn_clicked();
	void on_btnWaterOut_clicked();
	void on_btnWaterValve1_clicked();

	void on_btnParaSet_clicked();
	void on_btnSave_clicked();
	void on_btnExit_clicked();

	void setBtnBackColor(QPushButton *btn, bool status);

	void slotFreshComTempValue(const QString& tempStr); //ˢ���¶�ֵ
	void slotFreshBalanceValue(const QString& Str);     //ˢ����ƽ��ֵ

	void initTemperatureCom(); //�¶Ȳɼ�����

	void initControlCom();//���ſ��ƴ��� 
	void slotSetValveBtnStatus(const bool& status );

	void initBalanceCom();     //��ƽ����
private:
	Ui::QualityDlgClass ui;

private slots:

};

#endif // QUALITYDLG_H
