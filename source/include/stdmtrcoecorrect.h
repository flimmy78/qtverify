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

#define RELEASE_PTR(ptr)		if (ptr != NULL)\
								{\
									delete ptr;\
									ptr = NULL;\
								}

#define RELEASE_TIMER(timerptr)		if (timerptr != NULL)\
									{\
										if (timerptr->isActive())\
										{\
											timerptr->stop();\
										}\
										delete timerptr;\
										timerptr = NULL;\
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

	void on_btnSave_clicked();
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
	void on_tableWidget_cellChanged(int row, int column);
	void on_btnRegulateSmall_clicked();
	void on_btnRegulateMid1_clicked();
	void on_btnRegulateMid2_clicked();
	void on_btnRegulateBig_clicked();
	void on_lineEditOpeningSmall_textChanged(const QString & text);
	void on_lineEditOpeningMid1_textChanged(const QString & text);
	void on_lineEditOpeningMid2_textChanged(const QString & text);
	void on_lineEditOpeningBig_textChanged(const QString & text);
	void on_btnStdMeterV0_clicked();//��ȡ��׼���ֵ
	void on_btnStdMeterV1_clicked();//��ȡ��׼����ֵ
	void on_rBtn_DN3_toggled();
	void on_rBtn_DN10_toggled();
	void on_rBtn_DN25_toggled();
	void on_rBtn_DN50_toggled();

	/*******************��׼������******************************/
	void slotFreshInstFlow(const flow_rate_wdg&, const float&);
	void slotFreshAccumFlow(const flow_rate_wdg&, const float&);
	void slotFreshTolInst(const float&);
	void slotFreshTolAccum(const float&);
	/******************��׼������end****************************/
private slots:
	void slotAskPipeTemperature();//�����·�¶�
	void slotFreshComTempValue(const QString& tempStr); //ˢ���¶�ֵ
	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //�̵������سɹ���Ӧ�Ĳۺ���
	void slotSetRegulateOk();     //���ڷ����سɹ���Ӧ�Ĳۺ���

	/*******************�綯���ڷ�******************************/
	void setRegulatorOpening(int regNO, int opening); //���õ������ڷ����ȣ����ڽ�����ʾ
	void askControlRegulate(int retNO, int opening); //���Ϳ��Ƶ��ڷ���������
	void slotFreshSmallRegOpening();
	void slotFreshMid1RegOpening();
	void slotFreshMid2RegOpening();
	void slotFreshBigRegOpening();
	/******************�綯���ڷ�end***************************/

signals:
	void signalClosed();

private:
	Ui::StdMtrCoeCorrectClass ui;
	int m_curStdMeter;//��ǰ��ѡ�еı�׼��

	QTimer *m_exaustTimer; //������ʱ��

	ComThread m_balanceThread; //��ƽ�ɼ��߳�
	BalanceComObject *m_balanceObj;

	ComThread m_balanceThread2; //��ƽ�ɼ��߳�2
	BalanceComObject *m_balanceObj2;
	//����ƽ��������ͻ�ˮ����
	float m_balMaxWht;
	float m_balBottomWht;

	//С��ƽ��������ͻ�ˮ����
	float m_balMaxWht2;
	float m_balBottomWht2;

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

	QMap<int, QLineEdit*> m_RegLineEdit; //���ڷ��˿ں�����ڷ�������ʾ�ؼ���ӳ���ϵ
	QMap<int, QSpinBox*> m_RegSpinBox; //���ڷ��˿ں�����ڷ�Ŀ�꿪�ȿؼ���ӳ���ϵ
	int m_lastPortNO; //��¼��һ��������ķ��Ŷ˿ںţ�һ����·�ܶ��������ʱʹ�ã�

	/*******************��׼������******************************/
	CStdMeterReader* m_stdMeterReader;
	/******************��׼������end***************************/

	void initBalanceCom();     //��ƽ����
	void initBalanceCom2();    //��ƽ����2
	int prepareBigBalanceInitWeight(); //��ʼ�춨ǰ��׼������ƽ��ʼ����
	int prepareSmallBalanceInitWeight(); //��ʼ�춨ǰ��׼��С��ƽ��ʼ����
	int isBigBalanceValueBigger(float targetV, bool flg=true);   //�жϴ���ƽ����,flg: true-Ҫ�����Ŀ������(Ĭ��)��false-Ҫ��С��Ŀ������
	int isSmallBalanceValueBigger(float targetV, bool flg=true); //�ж�С��ƽ����,flg: true-Ҫ�����Ŀ������(Ĭ��)��false-Ҫ��С��Ŀ������

	void initTemperatureCom(); //�¶Ȳɼ�����
	void initControlCom();     //���ſ��ƴ���
	void initControlCom2();    //���ſ��ƴ���2
	void initValveStatus();	   //��ʼ������״̬
	void initRegulateStatus(); //��ʼ���綯���ڷ�״̬
	void initTableWdg();	   //��ʼ�������
	int openAllValveAndPump();    //�����з��ź�ˮ��
	int closeAllValveAndPumpOpenOutValve(); //�ر����з��ź�ˮ�á��򿪷�ˮ��
	int closeAllFlowPointValves();//�ر����������㷧��
	int startVerifyFlowPoint(int order);//��ʼ����������ļ춨
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
	void saveMeterConfig(flow_rate_wdg wdg);
};

#endif //STDCOECORRECT_H