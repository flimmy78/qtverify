#ifndef WEIGHTMETHOD_H
#define WEIGHTMETHOD_H

#ifdef WEIGHTMETHOD_DLL
#  ifdef WIN32
#  define WEIGHTMETHOD_EXPORT __declspec(dllexport)
#  else
#  define WEIGHTMETHOD_EXPORT
#  endif
#else
#  ifdef WIN32
#  define WEIGHTMETHOD_EXPORT __declspec(dllimport)
#  else
#  define WEIGHTMETHOD_EXPORT
#  endif
#endif

#define BALANCE_START_VALUE		2 //��ƽ��ֵ

#define TIMEOUT_TEMPER		500 //ÿ0.5��������һ���¶�ֵ

#define VALVE_OPEN		true	//���Ŵ�״̬
#define VALVE_CLOSE		false   //���Źر�״̬

/*
**	����λ������
*/
#define VALVE_IN_IDX	 0	//��ˮ��
#define VALVE_BIG_IDX	 1	//��������
#define VALVE_MID1_IDX	 2	//��һ����
#define VALVE_MID2_IDX	 3	//�ж�����
#define VALVE_SMALL_IDX	 4	//С����
#define VALVE_OUT_IDX	 5	//��ˮ��
#define VALVE_NUM	     6	//ʵ���õ��ķ�������


#include <QtGui/QWidget>

#include "ui_weightmethod.h"
#include "parasetdlg.h"
#include "comobject.h"
#include "ReadComConfig.h"
#include "algorithm.h"

class WEIGHTMETHOD_EXPORT WeightMethodDlg : public QWidget
{
	Q_OBJECT

public:
	WeightMethodDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~WeightMethodDlg();

	CBaseExdb m_db;

	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;


	QTimer *m_exaustTimer; //������ʱ��
	int m_exaustSecond;	

	QTimer *m_balTimer; //ģ����ƽ��ʱˢ���� �����ڲ���
	float m_balValue;   //ģ����ƽֵ
	float m_tempValue;  //ģ���¶�ֵ

	ComThread m_balanceThread; //��ƽ�ɼ��߳�
	BalanceComObject *m_balanceObj;

	ComThread m_tempThread;  //�¶Ȳɼ��߳�
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

	ComThread m_valveThread;   //���ſ����߳�
	ControlComObject *m_controlObj;
	QMap<int, bool> m_valveStatus;
	QMap<int, QToolButton*> m_valveBtn;	
	int m_nowPortNo;	//��ǰ���Ʒ��Ŷ˿ں�
	int m_nowPortIdx;	//��ǰ���Ʒ��Ŷ˿�����
	CAlgorithm *m_chkAlg;//�춨�����õ��ļ��㷽��


	//�춨������صĿ��Ʋ��� begin
	bool m_continueVerify; //�Ƿ������춨
	bool m_resetZero;      //�Ƿ��ֵ����
	bool m_autopick;       //�Ƿ��Զ��ɼ�
	int m_rowNum;             //������������������������
	int m_meterNum;           //ʵ�ʼ��ĸ���
	QMap<int, int> m_meterPosNo; //��λ��
	int m_flowPointNum;       //������ĸ���
	float *m_meterStartValue; //�����ĳ�ֵ
	float *m_meterEndValue;   //��������ֵ
	float *m_meterTemper;	  //�������¶�
	float *m_meterDensity;    //�������ܶ�
	float *m_meterStdValue;   //�����ı�׼ֵ
	float *m_meterError;	  //���������
	float m_balStartV;        //��ƽ��ֵ
	float m_balEndV;          //��ƽ��ֵ
	double m_pipeInTemper;     //����¶�
	double m_pipeOutTemper;    //�����¶�
	int m_tempCount;		   //
	//�춨������صĿ��Ʋ��� end

	int m_nowOrder;					//��ǰ�춨����
	ReadComConfig *m_readComConfig; //����������
	PortSet_Ini_STR m_portsetinfo;  //�˿�����

	void initBalanceCom();     //��ƽ����
	void initTemperatureCom(); //�¶Ȳɼ�����
	void initControlCom();     //���ſ��ƴ���
	void initValveStatus();	   //��ʼ������״̬

	int isComAndPortNormal();   //���ڡ��˿������Ƿ�����
	int isWaterOutValveOpen();  //����ˮ�����Ƿ��
	int readParaConfig();		//�����������ļ�
	int isDataCollectNormal();	//������ݲɼ��Ƿ���������ƽ���¶ȡ���������Ƶȣ�
	int isAllMeterInVerifyStatus(); //�ж��������ѽ���춨״̬
	int isMeterPosValid(int row); //�жϱ�λ���Ƿ���Ч(�ñ�λ�Ƿ���Ҫ���)
public slots:
	void closeEvent(QCloseEvent * event);
	void removeSubTab(int index);
	void on_btnExhaust_clicked();  //���"������ť"
	void on_btnStart_clicked();    //���"��ʼ"��ť
	void on_btnNext_clicked();
	int openAllValuesAndPump();   //�����з��ź�ˮ��
	void slotExaustFinished();    //����ʱ�����
	int readMeterNumber();        //��ȡ���
	int setMeterVerifyStatus();   //�������������춨״̬
	int closeAllFlowPointValves();//�ر����������㷧��
	int closeWaterOutValve();     //�رշ�ˮ��
	int openWaterOutValve();      //�򿪷�ˮ��
	int openBigFlowValve();       //�򿪴������㷧��
	int closeBigFlowValve();      //�رմ������㷧��
	int judgeBalanceInitValue(float v); //�ж���ƽ����
	int judgeBalanceAndSumTemper(float v); //�ж���ƽ���������ۼӽ������¶ȣ�ÿ���ۼ�һ�Σ����ڼ��������ƽ���¶�
	void startVerify();           //��ʼ�춨
	int judgeBalanceCapacity();   //�ж���ƽ�����Ƿ��ܹ�����춨���� �����춨
	int judgeBalanceCapacitySingle(int order); //�ж���ƽ�����Ƿ��ܹ�����춨���� �������춨
	int prepareVerifyFlowPoint(int order);     //׼������������ļ춨
	int startVerifyFlowPoint(int order);       //��ʼ����������ļ춨
	int openValve(int portno);    //�򿪿��Ʒ�
	int closeValve(int portno);   //�رտ��Ʒ�
	int getMeterStartValue();     //��ȡ���ֵ
	int getMeterEndValue();       //��ȡ����ֵ
	int calcMeterError();         //��������

	void slotFreshBalanceValue(const QString& Str);     //ˢ����ƽ��ֵ
	void slotFreshComTempValue(const QString& tempStr); //ˢ���¶�ֵ
	void slotFreshFlow(); //��������

	void slotSetValveBtnStatus(); //�̵������سɹ���Ӧ�Ĳۺ���
	void slotSetRegulateOk();     //���ڷ����سɹ���Ӧ�Ĳۺ���

	void setValveBtnBackColor(QToolButton *btn, bool status); //���÷��Ű�ť����ɫ
	void setRegBtnBackColor(QPushButton *btn, bool status);	  //���õ��ڷ���ť����ɫ

	void on_btnParaSet_clicked();	   //��������
	void on_btnWaterIn_clicked();      //��ˮ��
	void on_btnWaterOut_clicked();     //��ˮ��
	void on_btnValveBig_clicked();     //��������
	void on_btnValveMiddle1_clicked(); //����һ
	void on_btnValveMiddle2_clicked(); //������
	void on_btnValveSmall_clicked();   //С������

	void on_btnWaterPumpStart_clicked(); //����ˮ��
	void on_btnWaterPumpStop_clicked();  //ֹͣˮ��

	void on_tableWidget_cellChanged(int row, int column);

	void freshBigBalaceValue();   //ˢ�´���ƽ��ֵ �����ڲ��� ģ����ƽ��ֵ�仯

private slots:

signals:


private:
	Ui::WeightMethodClass ui;

};


#endif //WEIGHTMETHOD_H