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

	void on_btnStart_clicked();   //���"��ʼ"��ť
	void on_btnGoOn_clicked();    //���"����"��ť
	void on_btnStop_clicked();    //���"��ֹ���"��ť
	void on_btnExit_clicked();    //���"�˳�"��ť
	void on_btnParaSet_clicked();	   //��������
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

private slots:
	void slotExaustFinished();    //����ʱ�����
	void slotAskPipeTemperature();//�����·�¶�
	void slotFreshComTempValue(const QString& tempStr); //ˢ���¶�ֵ
	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //�̵������سɹ���Ӧ�Ĳۺ���
	void slotSetRegulateOk();     //���ڷ����سɹ���Ӧ�Ĳۺ���

	/*******************�綯���ڷ�******************************/
	void openAllRegulator();  //�����е��ڷ����趨�Ŀ���
	void closeAllRegulator(); //�ر����е��ڷ�
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

	ComThread m_tempThread;  //�¶Ȳɼ��߳�
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;
	int m_avgTFCount;//���ڼ�����ڵ�ƽ���¶�

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

	bool m_stopFlag;//�رս�����˳�
	now_state m_state; //��ǰ����״̬����ʼ̬������ֵ̬������ֵ̬��

	CAlgorithm *m_chkAlg;//�춨�����õ��ļ��㷽��

	//�춨������صĿ��Ʋ��� begin
	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;
	Verify_Params_PTR m_nowParams;//��ǰ�춨����
	int m_flowPointNum;//������ĸ���
	int m_exaustSecond;//����ʱ��

	float m_meterStartValue;//�����ĳ�ֵ
	float m_meterEndValue;//��������ֵ
	float m_meterStdValue;//�����ı�׼ֵ
	float m_meterError;//���������(��ǰ�����㲻ͬ��λ�����)
	float m_stdStartVol;//��׼�������ֵ
	float m_stdEndVol;//��׼�������ֵ
	float m_StdStartMass;//���¶������ı�׼��������ֵ
	float m_StdEndMass;//���¶������ı�׼��������ֵ
	float m_pipeInTemper;//�����¶�
	float m_pipeOutTemper;//�����¶�
	QString m_timeStamp;//ʱ��� ����
	QString m_nowDate;  
	QString m_validDate;
	//�춨������صĿ��Ʋ��� end

	QMap<int, QLineEdit*> m_RegLineEdit; //���ڷ��˿ں�����ڷ�������ʾ�ؼ���ӳ���ϵ
	QMap<int, QSpinBox*> m_RegSpinBox; //���ڷ��˿ں�����ڷ�Ŀ�꿪�ȿؼ���ӳ���ϵ
	int m_lastPortNO; //��¼��һ��������ķ��Ŷ˿ںţ�һ����·�ܶ��������ʱʹ�ã�

	/*******************��׼������******************************/
	CStdMeterReader* m_stdMeterReader;
	QMap<flow_rate_wdg, QLCDNumber *> m_mapInstWdg;
	QMap<flow_rate_wdg, QLCDNumber *> m_mapAccumWdg;
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
	int readNowParaConfig();	 //��ȡ��ǰ�춨����
	int startExhaustCountDown();  //��ʼ��������ʱ
	int openAllValveAndPump();    //�����з��ź�ˮ��
	int closeAllValveAndPumpOpenOutValve(); //�ر����з��ź�ˮ�á��򿪷�ˮ��
	int closeAllFlowPointValves();//�ر����������㷧��
	int judgeTartgetVolAndCalcAvgTemperAndFlow(double initV, double verifyV); //�ж��Ƿ���ɼ춨���춨�������ۼӳ����¶ȣ�ÿ���ۼ�һ�Σ����ڼ��������ƽ���¶�
	void stopVerify();            //ֹͣ�춨
	void startVerify();           //��ʼ�춨
	int startVerifyFlowPoint(int order);//��ʼ����������ļ춨
	int openValve(UINT8 portno);    //�򿪿��Ʒ�
	int closeValve(UINT8 portno);   //�رտ��Ʒ�
	int operateValve(UINT8 portno); //�������Ʒ����򿪻��߹ر�
	int openWaterPump();			//��ˮ��
	int closeWaterPump();			//�ر�ˮ��
	int operateWaterPump();			//����ˮ�ã��򿪻��߹ر�
	int getMeterStartValue();       //��ȡ���ֵ
	int getMeterEndValue();         //��ȡ����ֵ
	int calcMeterError(int idx);  //����ĳ��������
	void clearTableContents();		//��ձ��
	int saveAllVerifyRecords(); //�������б����ļ춨��¼
	void setValveBtnBackColor(QToolButton *btn, bool status); //���÷��Ű�ť����ɫ
	void setRegBtnBackColor(QPushButton *btn, bool status);	  //���õ��ڷ���ť����ɫ
};

#endif //STDCOECORRECT_H