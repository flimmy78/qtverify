#ifndef DATATESTDLG_H
#define DATATESTDLG_H

#include <QtGui/QWidget>

#include "datatestdlg_global.h"
#include "ui_datatestdlg.h"
#include "parasetdlg.h"
#include "comobject.h"
#include "ReadComConfig.h"
#include "algorithm.h"

#define TIMEOUT_TEMPER		500 //ÿ0.5��������һ���¶�ֵ
#define CALC_FLOW_COUNT		2   //��������Ƶ�ʣ�ʵ�ʼ���Ƶ�� = CALC_FLOW_COUNT * TIMEOUT_TEMPER��


/*
**	������DataTestDlg
**	���ܣ����ݲɼ������
*/
class DATATESTDLG_EXPORT DataTestDlg : public QWidget
{
	Q_OBJECT

public:
	DataTestDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DataTestDlg();

	ParaSetDlg *m_paraset;

	ReadComConfig *m_readComConfig; //����������

	ComThread m_tempThread;  //�¶Ȳɼ��߳�
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;
	QTimer *m_flowTimer;//������ʱ��
	QTimer *m_setBalTimer;//�趨��ƽ������ʱ��

	ComThread m_valveThread;   //���ſ����߳�
	ControlComObject *m_controlObj;

	QMap<int, bool> m_valveStatus;//<���Ŷ˿ںţ�����״̬>
	QMap<int, QPushButton*> m_valveBtn;	//<���Ŷ˿ںţ����Ű�ť>
	int m_nowPortNo;	//��ǰ���Ʒ��Ŷ˿ں�

	QMap<int, bool> m_regStatus; //<���ڷ��˿ںţ����ڷ�״̬>
	QMap<int, QPushButton*> m_regBtn;//<���ڷ��˿ںţ����ڷ���ť>	
	int m_nowRegNo;  //��ǰ���ڷ��˿ں�

	ComThread m_balanceThread; //��ƽ�ɼ��߳�
	BalanceComObject *m_balanceObj;

	ComThread m_meterThread;  //�������߳�
	MeterComObject *m_meterObj;

	uint m_flowcount;  //��������ʱ ������ , 0~4294967295, ��10΢�����һ��, �ɼ���497��
	uint m_totalcount;//�ۻ���������
	float m_flow1;//��ƽ��ֵ
	float m_flow2;//��ƽ��ֵ
	float start_quan;//�ۻ�����ƽ��ֵ
	float end_quan;//�ۻ�����ƽ��ֵ
	float total_quantity;//�ۻ�����(�Ӷ�����ʼ, ����������һ�����ۻ���)
	float bal_quan;//��ƽ����ģ����
	

	PortSet_Ini_STR m_portsetinfo; //�˿�����
	ParaSet_Ini_STR m_parasetinfo; //��������(������-�������)

	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent *event);
	void initTemperatureCom(); //�¶Ȳɼ�����
	void initBalanceCom();     //��ƽ����
	void initControlCom();     //���ſ��ƴ���
	void initComOfHeatMeter();  //������1����

	void initValveStatus();	   //��ʼ������״̬
	void initRegulateStatus(); //��ʼ�����ڷ�״̬

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
	
	void slotFreshMeterNo(const QString& comName, const QString& meterNo);//ˢ�±��
	void slotFreshMeterFlow(const QString& comName, const QString& flow); //ˢ�±�����
	void slotFreshMeterHeat(const QString& comName, const QString& heat); //ˢ�±�����
	void slotFreshMeterDate(const QString& comName, const QString& date); //ˢ�±�����
	void slotFreshMeterTemper(const QString& comName, const QString& tempIn, const QString& tempOut); //ˢ�±����ˮ�¶�

	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //�̵������سɹ���Ӧ�Ĳۺ���
	void slotSetRegulateOk();

	void setValveBtnBackColor(QPushButton *btn, bool status); //���÷��Ű�ť����ɫ
	void setRegBtnBackColor(QPushButton *btn, bool status);	//���õ��ڷ���ť����ɫ

	void slotFreshFlow(); //��������
	void slotFreshFlow_total();//��������(�ۼƷ�)
	void setBalQuantity();//ģ����ƽ����

	void on_btnSetVerifyStatus_clicked();//���ü춨״̬
	void on_btnReadMeterData_clicked(); //��������
	void on_btnModifyMeterNo_clicked(); //�޸ı��
	void on_btnModifyFlowPara_clicked(); //�޸���������

	void on_btnOpenCom_clicked(); //�򿪴���
	void on_btnCloseCom_clicked();//�رմ���

private:
	Ui::DataTestDlgClass ui;

private slots:

};

#endif // DATATESTDLG_H
