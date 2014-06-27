#ifndef QUALITYDLG_H
#define QUALITYDLG_H

#include <QtGui/QWidget>

#include "qualitydlg_global.h"
#include "ui_qualitydlg.h"
#include "parasetdlg.h"
#include "comobject.h"
#include "ReadComConfig.h"
#include "algorithm.h"

#define TIMEOUT_TEMPER  500 //ÿ0.5��������һ���¶�ֵ

#define VALVE_OPEN		true	//���Ŵ�״̬
#define VALVE_CLOSE		false   //���Źر�״̬

#define VALVE_IN_IDX	 0	//��ˮ��
#define VALVE_BIG_IDX	 1	//��������
#define VALVE_MID1_IDX	 2	//��һ����
#define VALVE_MID2_IDX	 3	//�ж�����
#define VALVE_SMALL_IDX	 4	//С����
#define VALVE_OUT_IDX	 5	//��ˮ��
#define VALVE_PUMP_IDX	 6	//ˮ��

#define  VALVE_NUM	7	//ʵ���õ��ķ�������



class QUALITYDLG_EXPORT QualityDlg : public QWidget
{
	Q_OBJECT

public:
	QualityDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QualityDlg();

	ParaSetDlg *m_paraset;

	ReadComConfig *m_readComConfig; //����������

	ComThread m_tempThread;  //�¶Ȳɼ��߳�
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

	ComThread m_valveThread;   //���ſ����߳�
	ControlComObject *m_controlObj;

	QMap<int, bool> m_valveStatus;
	QMap<int, QPushButton*> m_valveBtn;	
// 	bool m_waterInStatus;	//��ˮ����״̬
// 	bool m_waterOutStatus;  //��ˮ����״̬
// 	bool m_valveBigStatus;		//����������״̬
// 	bool m_valveMiddle1Status;  //����һ����״̬
// 	bool m_valveMiddle2Status;  //����������״̬
// 	bool m_valveSmallStatus;    //С�����㷧��״̬
// 	bool m_valvePumpStatus;		//ˮ��״̬
	int m_nowPortNo;	//��ǰ���Ʒ��Ŷ˿ں�
	int m_nowPortIdx;	//��ǰ���Ʒ��Ŷ˿�����

	ComThread m_balanceThread; //��ƽ�ɼ��߳�
	BalanceComObject *m_balanceObj;

	ComThread m_meterThread1;  //������1�߳�
	MeterComObject *m_meterObj1;

	int m_flowcount;  //��������ʱ ������
	float m_flow1;
	float m_flow2;

	PORTSET_INI_STR m_portsetinfo; //�˿�����
	PARASET_INI_STR m_parasetinfo; //��������(������-�������)

	void closeEvent(QCloseEvent * event);
	void initTemperatureCom(); //�¶Ȳɼ�����
	void initBalanceCom();     //��ƽ����
	void initControlCom();     //���ſ��ƴ���
	void initHeatMeterCom1();  //��������

	void initValveStatus();	   //��ʼ������״̬

public slots:
	void on_btnWaterIn_clicked(); //��ˮ��
	void on_btnWaterOut_clicked();//��ˮ��
	void on_btnValveBig_clicked(); //��������
	void on_btnValveMiddle1_clicked(); //����һ
	void on_btnValveMiddle2_clicked(); //������
	void on_btnValveSmall_clicked(); //С������
	void on_btnWaterPump_clicked(); //ˮ��

	void on_btnRegulate1_clicked();
	void on_btnQueryStatus_clicked();

	void on_btnParaSet_clicked();
	void on_btnStart_clicked();
	void on_btnExit_clicked();

	void slotFreshComTempValue(const QString& tempStr); //ˢ���¶�ֵ
	void slotFreshBalanceValue(const QString& Str);     //ˢ����ƽ��ֵ

	void slotSetValveBtnStatus(); //�̵������سɹ���Ӧ�Ĳۺ���
	void slotSetRegulateOk();

	void setBtnBackColor(QPushButton *btn, bool status);

	void slotFreshFlow();

	void on_btnReadMeterNo_clicked();

private:
	Ui::QualityDlgClass ui;

private slots:

};

#endif // QUALITYDLG_H
