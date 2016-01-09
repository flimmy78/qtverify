#ifndef STDCOECORRECT_H
#define STDCOECORRECT_H

#include <QtGui/QWidget>
#include <QByteArray>
#include <QSettings>
#include <QtGui/QDataWidgetMapper>

#include "ui_stdmtrcoecorrect.h"
#include "systemsetdlg_global.h"
#include "basedef.h"
#include "comobject.h"

class CAlgorithm;
class ParaSetDlg;
class ParaSetReader;
class ReadComConfig;
class CStdMeterReader;
class StdMtrCorrectPraDlg;

#define RELEASE_PTR(ptr)		if (ptr != NULL)\
								{\
									delete ptr;\
									ptr = NULL;\
								}

#define EXIT_THREAD(th)		if (th.isRunning())\
							{\
								th.exit();\
							}

#define FLOW_POINTS	(8)//ÿ����׼����Ҫ�궨��������������
#define CHK_CNTS	(3)//ÿ����������Ҫ�ظ����Ĵ���
#define COL_CNTS   (12)//��������

#define COL_FLOW_POINT	0//��������
#define COL_BALV0		1//��ƽ��ֵ��
#define COL_BALV1		2//��ƽ��ֵ��
#define COL_BALVD		3//��ƽʾֵ��
#define COL_DEN			4//�ܶ���
#define COL_BALVC		5//��׼ֵ��
#define COL_STDV0		6//��׼���ֵ��
#define COL_STDV1		7//��׼����ֵ��
#define COL_STDVD		8//��׼��ʾֵ��
#define COL_STDERR		9//��׼�������
#define COL_STDERR_AVR	10//��׼��ƽ�������
#define COL_STDREP		11//���ظ���

#define EX_DEGREE		80//��������ʱ�ĵ��ڷ�����
#define REG_DEGREE_ZERO	0//��������ʱ�ĵ��ڷ�����
#define EX_GREQ			25//��������ʱ��ˮ��Ƶ��

typedef struct{
	float flowpoint;//��ǰ�춨�������� m3/h
	int	  degree;//���ڷ�����
	int	  freq;//ˮ��Ƶ��
	float quantity;//�춨��
}StdCorrectPara_STR;
typedef StdCorrectPara_STR* StdCorrectPara_PTR;

class SYSTEMSETDLG_EXPORT StdMtrCoeCorrect : public QWidget
{
	Q_OBJECT

public:
	StdMtrCoeCorrect(QWidget *parent = 0, Qt::WFlags flags = 0);
	~StdMtrCoeCorrect();

public slots:
	void showEvent(QShowEvent * event);
	void closeEvent(QCloseEvent * event);
	void resizeEvent(QResizeEvent * event);

	void on_btnPra_clicked();//�������ð�ť
	void on_btnClearTbl_clicked();//��ձ��ť
	void on_btnSave_clicked();//����궨��ť
	void on_btnExit_clicked();    //���"�˳�"��ť
	void on_btnWaterIn_clicked();      //��ˮ��
	void on_btnBigWaterIn_clicked();   //����ƽ��ˮ��
	void on_btnBigWaterOut_clicked();  //����ƽ��ˮ��
	void on_btnSmallWaterIn_clicked(); //С��ƽ��ˮ��
	void on_btnSmallWaterOut_clicked();//С��ƽ��ˮ��
	void on_btnValveBig_clicked();     //��������
	void on_btnValveMiddle1_clicked(); //����һ
	void on_btnValveMiddle2_clicked(); //������
	void on_btnValveSmall_clicked();   //С������
	void on_btnWaterPump_clicked(); //ˮ��
	void on_btnSetFreq_clicked();   //���ñ�Ƶ��Ƶ��
	void on_btnRegulateSmall_clicked();//����С���ڷ�
	void on_btnRegulateMid1_clicked();//������һ���ڷ�
	void on_btnRegulateMid2_clicked();//�����ж����ڷ�
	void on_btnRegulateBig_clicked();//���ڴ���ڷ�
	void on_btnStart_clicked();//�����ʼ
	void on_btnGoOn_clicked();//�������

	void on_lineEditOpeningSmall_textChanged(const QString & text);//��ӦС���ڷ����ȱ仯
	void on_lineEditOpeningMid1_textChanged(const QString & text);//��Ӧ��һ���ڷ����ȱ仯
	void on_lineEditOpeningMid2_textChanged(const QString & text);//��Ӧ�ж����ڷ����ȱ仯
	void on_lineEditOpeningBig_textChanged(const QString & text);//��Ӧ����ڷ����ȱ仯
	void on_tableWidget_cellChanged(int row, int column);//��Ӧ������ݱ仯
	void on_rBtn_DN3_toggled();//ѡȡDN3��׼��
	void on_rBtn_DN10_toggled();//ѡȡDN10��׼��
	void on_rBtn_DN25_toggled();//ѡȡDN25��׼��
	void on_rBtn_DN50_toggled();//ѡȡDN50��׼��

	void slotFreshBigBalanceValue(const float& balValue);  //ˢ�´���ƽ��ֵ
	void slotFreshSmallBalanceValue(const float& balValue);//ˢ��С��ƽ��ֵ
	void slotOnStdMtrCorrectPraClosed();//��Ӧ�������ô��ڹر�
	void slotExaustFinished();//��Ӧ�������
	/*******************��׼������******************************/
	void slotFreshInstFlow(const flow_rate_wdg&, const float&);//ˢ��˲ʱ����
	void slotFreshAccumFlow(const flow_rate_wdg&, const float&);//ˢ���ۻ�����
	void slotFreshTolInst(const float&);//ˢ��˲ʱ������
	void slotFreshTolAccum(const float&);//ˢ���ۻ�������
	/******************��׼������end****************************/
private slots:
	void slotAskPipeTemperature();//�����·�¶�
	void slotFreshComTempValue(const QString& tempStr); //ˢ���¶�ֵ
	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //�̵������سɹ���Ӧ�Ĳۺ���
	void slotSetRegulateOk();     //���ڷ����سɹ���Ӧ�Ĳۺ���
	void slotReadCorrectParas();   //��ȡ�����趨
	/*******************�綯���ڷ�******************************/
	void openAllRegulator();  //�����е��ڷ����趨�Ŀ���
	void closeAllRegulator(); //�ر����е��ڷ�
	void setRegulatorOpening(int regNO, int opening); //���õ������ڷ����ȣ����ڽ�����ʾ
	void askControlRegulate(int retNO, int opening); //���Ϳ��Ƶ��ڷ���������
	void slotFreshSmallRegOpening();//ˢ��С���ڷ�����ֵ
	void slotFreshMid1RegOpening();//ˢ����һ���ڷ�����ֵ
	void slotFreshMid2RegOpening();//ˢ���ж����ڷ�����ֵ
	void slotFreshBigRegOpening();//ˢ�´���ڷ�����ֵ
	/******************�綯���ڷ�end***************************/

signals:
	void signalClosed();

private:
	Ui::StdMtrCoeCorrectClass ui;
	StdMtrCorrectPraDlg* m_StdMtrCorrectPraDlg;//�����趨����
	bool m_stopFlag;//��ǰ�Ƿ�Ϊֹͣ�춨״̬
	int m_exhaustSecond;//����ʱ��
	Balance_Capacity m_curBalance;//��ǰ��׼�����ڹ�·��ʹ�õ���ƽ
	int m_curStdMeter;//��ǰ��ѡ�еı�׼��
	int m_chkTimes;//ÿ��������ļ춨����
	bool m_reachTargetRate;//�û��Ƿ����趨������
	int m_flowSeq;//��ǰ��׼��ĵڼ���������
	int m_chkTime;//��ǰ������ĵڼ��μ춨
	StdCorrectPara_PTR m_curFlowPoint;//��ǰ�춨������Ĳ���

	QMap<flow_rate_wdg, QList<StdCorrectPara_PTR>> m_mapFlowPoint;//��·-<������, �춨��, ���ڷ�����, ˮ��Ƶ��>���ñ�

	QTimer *m_exhaustTimer; //������ʱ��

	ComThread m_balanceThread; //��ƽ�ɼ��߳�
	BalanceComObject *m_balanceObj;

	ComThread m_balanceThread2; //��ƽ�ɼ��߳�2
	BalanceComObject *m_balanceObj2;
	//����ƽ��������ͻ�ˮ����
	float m_balMaxWhtBig;
	float m_balBottomWhtBig;

	//С��ƽ��������ͻ�ˮ����
	float m_balMaxWhtSmall;
	float m_balBottomWhtSmall;

	float m_tempPipeOut;
	int m_avgTFCount;//���ڼ�����ڵ�ƽ���¶�
	ComThread m_tempThread;  //�¶Ȳɼ��߳�
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

	ComThread m_valveThread;//���ſ����߳�
	ControlComObject *m_controlObj;

	ComThread m_valveThread2;//���ſ����߳�2
	ControlComObject *m_controlObj2;

	QMap<int, bool> m_valveStatus; //���ź��뷧��״̬��ӳ���ϵ
	QMap<int, QToolButton*> m_valveBtn;	//���ź��뷧�Ű�ť��ӳ���ϵ
	int m_nowPortNo;//��ǰ���Ʒ��Ŷ˿ں�

	ReadComConfig *m_readComConfig; //����������
	PortSet_Ini_STR m_portsetinfo;  //�˿�����

	QTimer *m_regSmallTimer; //��ʱ��, ���ڶ�̬��ʾС���ڷ��Ŀ���
	int m_smallOpening;
	QTimer *m_regMid1Timer; //��ʱ��, ���ڶ�̬��ʾ��һ���ڷ��Ŀ���
	int m_mid1Opening;
	QTimer *m_regMid2Timer; //��ʱ��, ���ڶ�̬��ʾ�ж����ڷ��Ŀ���
	int m_mid2Opening;
	QTimer *m_regBigTimer;  //��ʱ��, ���ڶ�̬��ʾ����ڷ��Ŀ���
	int m_bigOpening;

	CAlgorithm *m_chkAlg;//�춨�����õ��ļ��㷽��
	QSettings* m_stdMeterConfig;//��׼��������ļ�
	QSettings* m_stdCorrectParas;//�궨�����еĲ���

	QMap<int, QLineEdit*> m_RegLineEdit; //���ڷ��˿ں�����ڷ�������ʾ�ؼ���ӳ���ϵ
	QMap<int, QSpinBox*> m_RegSpinBox; //���ڷ��˿ں�����ڷ�Ŀ�꿪�ȿؼ���ӳ���ϵ
	int m_lastPortNO; //��¼��һ��������ķ��Ŷ˿ں�(һ����·�ܶ��������ʱʹ��)

	/*******************��׼������******************************/
	CStdMeterReader* m_stdMeterReader;//��׼�����ƶ�ȡģ��
	QMap<flow_rate_wdg, QLCDNumber *> m_mapInstWdg;//��·-��ʾ������Ӧ��, ˲ʱ����
	QMap<flow_rate_wdg, QLCDNumber *> m_mapAccumWdg;//��·-��ʾ������Ӧ��, �ۻ�����
	/******************��׼������end***************************/

	void initBalanceCom();     //��ƽ����
	void initBalanceCom2();    //��ƽ����2
	int prepareBigBalanceInitWeight(); //��ʼ�춨ǰ��׼������ƽ��ʼ����
	int prepareSmallBalanceInitWeight(); //��ʼ�춨ǰ��׼��С��ƽ��ʼ����
	int isBalanceValueBigger(float targetV, bool flg=true);//�ж���ƽ����, flg: true-Ҫ�����Ŀ������(Ĭ��)��false-Ҫ��С��Ŀ������
	int isBigBalanceValueBigger(float targetV, bool flg=true);   //�жϴ���ƽ����,flg: true-Ҫ�����Ŀ������(Ĭ��)��false-Ҫ��С��Ŀ������
	int isSmallBalanceValueBigger(float targetV, bool flg=true); //�ж�С��ƽ����,flg: true-Ҫ�����Ŀ������(Ĭ��)��false-Ҫ��С��Ŀ������

	void initTemperatureCom(); //�¶Ȳɼ�����
	void initControlCom();     //���ſ��ƴ���
	void initControlCom2();    //���ſ��ƴ���2
	void initValveStatus();	   //��ʼ������״̬
	void initRegulateStatus(); //��ʼ���綯���ڷ�״̬
	void initTableWdg();	   //��ʼ�������

	void clearMapFlowPoint();
	void releaseSource();	   //�ͷ���Դ
	int openAllValveAndPump();    //�����з��ź�ˮ��
	int closeAllValveAndPumpOpenOutValve(); //�ر����з��ź�ˮ�á��򿪷�ˮ��
	int closeAllFlowPointValves();//�ر����������㷧��
	int openValve(UINT8 portno);    //�򿪿��Ʒ�
	int closeValve(UINT8 portno);   //�رտ��Ʒ�
	int operateValve(UINT8 portno); //�������Ʒ����򿪻��߹ر�
	int openWaterPump();			//��ˮ��
	int closeWaterPump();			//�ر�ˮ��
	int operateWaterPump();			//����ˮ�ã��򿪻��߹ر�

	void clearTableContents();		//��ձ��
	void setValveBtnBackColor(QToolButton *btn, bool status); //���÷��Ű�ť����ɫ
	void setRegBtnBackColor(QPushButton *btn, bool status);	  //���õ��ڷ���ť����ɫ
	int getStartRow(int row);//��ȡ��ǰ�ж�Ӧ���������ʼ��
	void saveMeterConfig(flow_rate_wdg wdg);//����궨���

	void startVerify();//��ʼ�ܼ춨
	int  startVerifyFlowPoint();//��ʼ����������ļ춨
	int  startVerifyTime();//��ʼ������ĵ�i�μ춨
	void stopVerify();//ֹͣ�춨

	int judgeBalanceAndCalcAvgTemperAndFlow(float targetV, bool bigFlag); //�жϴ���ƽ���������ۼӽ������¶ȣ�ÿ���ۼ�һ�Σ����ڼ��������ƽ���¶�
	int startExhaustCountDown();  //��ʼ��������ʱ
};

#endif //STDCOECORRECT_H