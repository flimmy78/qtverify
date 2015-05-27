#ifndef DATATESTDLG_H
#define DATATESTDLG_H

#ifdef DATATESTDLG_DLL
#  ifdef WIN32
#  define DATATESTDLG_EXPORT __declspec(dllexport)
#  else
#  define DATATESTDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define DATATESTDLG_EXPORT __declspec(dllimport)
#  else
#  define DATATESTDLG_EXPORT
#  endif
#endif

#include <QtGui/QWidget>

#include "ui_datatestdlg.h"
#include "comobject.h"

class ParaSetReader;
class ParaSetDlg;
class ReadComConfig;

/*
** ������DataTestDlg
** ���ܣ����ݲɼ������
*/
class DATATESTDLG_EXPORT DataTestDlg : public QWidget
{
	Q_OBJECT

public:
	DataTestDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DataTestDlg();

	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;

	ReadComConfig *m_readComConfig; //����������

	ComThread m_tempThread;  //�¶Ȳɼ��߳�
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;  //��ʱ��:���������·�¶�

	ComThread m_stdTempThread;  //��׼�¶Ȳɼ��߳�
	Sti1062aComObject *m_stdTempObj;
	QTimer *m_stdTempTimer;  //��ʱ��:���������׼�¶�
	sti1062Acommand m_stdTempCommand;

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

	//����������
	uint m_totalcount;  //������
	float m_startWeight;//��ƽ��ֵ
	float m_endWeight;  //��ƽ��ֵ
	float m_deltaWeight[FLOW_SAMPLE_NUM];
	QTimer *m_flowRateTimer;  //��ʱ��:���ڼ�������
	

	PortSet_Ini_STR m_portsetinfo; //�˿�����
	ParaSet_Ini_STR m_parasetinfo; //��������(������-�������)

	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent *event);
	void initTemperatureCom(); //�¶Ȳɼ�����
	void initStdTemperatureCom(); //��׼�¶Ȳɼ�����
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

	void on_btnSetFreq_clicked(); //����Ƶ��
	void on_btnRegulate1_clicked();

	void on_btnParaSet_clicked();
	void on_btnExit_clicked();

	void slotFreshComTempValue(const QString& tempStr); //ˢ���¶�ֵ
	void slotFreshStdTempValue(const QString& stdTempStr); //ˢ�±�׼�¶�ֵ
	void slotFreshBalanceValue(const float& balValue);     //ˢ����ƽ��ֵ
	
	void slotFreshMeterNo(const QString& comName, const QString& meterNo);//ˢ�±��
	void slotFreshMeterFlow(const QString& comName, const float& flow); //ˢ�±�����
	void slotFreshMeterHeat(const QString& comName, const QString& heat); //ˢ�±�����
	void slotFreshMeterDate(const QString& comName, const QString& date); //ˢ�±�����
	void slotFreshMeterTemper(const QString& comName, const QString& tempIn, const QString& tempOut); //ˢ�±����ˮ�¶�
	void slotFreshBigCoe(const QString& comName, const QString& bigCoe); //ˢ�´�����ϵ��
	void slotFreshMid2Coe(const QString& comName, const QString& mid2Coe); //ˢ������2����ϵ��
	void slotFreshMid1Coe(const QString& comName, const QString& mid1Coe); //ˢ������1����ϵ��
	void slotFreshSmallCoe(const QString& comName, const QString& smallCoe); //ˢ��С����ϵ��


	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //�̵������سɹ���Ӧ�Ĳۺ���
	void slotSetRegulateOk();

	void setValveBtnBackColor(QPushButton *btn, bool status); //���÷��Ű�ť����ɫ
	void setRegBtnBackColor(QPushButton *btn, bool status);	//���õ��ڷ���ť����ɫ

	void slotFreshFlowRate();//��������

	void on_btnSetVerifyStatus_clicked();//���ü춨״̬
	void on_btnReadMeterData_clicked(); //��������
	void on_btnModifyMeterNo_clicked(); //�޸ı��
	void on_btnModifyFlowCoe_clicked(); //�޸�����ϵ��

	void on_btnOpenCom_clicked(); //�򿪴���
	void on_btnCloseCom_clicked();//�رմ���

	void on_btnStdTempCollect_clicked(); //�ɼ���׼�¶�
	void on_btnStdTempStop_clicked(); //ֹͣ�ɼ���׼�¶�

	void slotAskStdTemperature();

private:
	Ui::DataTestDlgClass ui;

private slots:

};

#endif // DATATESTDLG_H
