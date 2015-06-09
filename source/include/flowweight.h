#ifndef FLOWWEIGHT_H
#define FLOWWEIGHT_H

#ifdef FLOWWEIGHT_DLL
#  ifdef WIN32
#  define FLOWWEIGHT_EXPORT __declspec(dllexport)
#  else
#  define FLOWWEIGHT_EXPORT
#  endif
#else
#  ifdef WIN32
#  define FLOWWEIGHT_EXPORT __declspec(dllimport)
#  else
#  define FLOWWEIGHT_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>

#include "ui_flowweight.h"
#include "comobject.h"

class CAlgorithm;
class ParaSetDlg;
class ParaSetReader;
class ReadComConfig;

/*
** �����
*/
#define COLUMN_METER_NUMBER       0 //�����
#define COLUMN_FLOW_POINT	      1 //������
#define COLUMN_METER_START	      2 //���ֵ��
#define COLUMN_METER_END	      3 //����ֵ��
#define COLUMN_BAL_START	      4 //��ƽ��ֵ
#define COLUMN_BAL_END		      5 //��ƽ��ֵ
#define COLUMN_TEMPER		      6 //�¶���
#define COLUMN_DENSITY		      7 //�ܶ���
#define COLUMN_STD_VALUE	      8 //��׼ֵ
#define COLUMN_ERROR		      9 //ʾֵ�����
#define COLUMN_READ_METER		  10 //����������
#define COLUMN_VERIFY_STATUS	  11 //���ü춨״̬��
#define COLUMN_ADJUST_ERROR		  12 //���������
#define COLUMN_MODIFY_METERNO	  13 //�޸ı����


class FLOWWEIGHT_EXPORT FlowWeightDlg : public QWidget
{
	Q_OBJECT

public:
	FlowWeightDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~FlowWeightDlg();

	QDataWidgetMapper *m_meterStdMapper;

	QTimer *m_exaustTimer; //������ʱ��

	ComThread m_balanceThread; //��ƽ�ɼ��߳�
	BalanceComObject *m_balanceObj;

	ComThread m_tempThread;  //�¶Ȳɼ��߳�
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

	ComThread m_valveThread;   //���ſ����߳�
	ControlComObject *m_controlObj;
	QMap<int, bool> m_valveStatus; //���ź��뷧��״̬��ӳ���ϵ
	QMap<int, QToolButton*> m_valveBtn;	//���ź��뷧�Ű�ť��ӳ���ϵ
	int m_nowPortNo;	//��ǰ���Ʒ��Ŷ˿ں�

	ComThread *m_meterThread;	//������ͨѶ�߳�
	MeterComObject *m_meterObj;	

	CAlgorithm *m_chkAlg;//�춨�����õ��ļ��㷽��

	bool m_stopFlag;     //�رս�����˳�

	//�춨������صĿ��Ʋ��� begin
	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;
	Verify_Params_PTR m_nowParams; //��ǰ�춨����
	bool m_continueVerify;    //�Ƿ������춨
	bool m_resetZero;         //�Ƿ��ֵ����
	bool m_autopick;          //�Ƿ��Զ��ɼ�
	int m_flowPointNum;       //������ĸ���
	int m_exaustSecond;		  //����ʱ��
	int m_standard;           //����
	int m_model;              //���ͺ�
	int m_pickcode;			  //�ɼ�����(�ȱ�ͨѶЭ��汾��)
	float m_flowSC;           //�����춨��ȫϵ��
	bool m_adjErr;            //�Ƿ�������
	//�춨������صĿ��Ʋ��� end

	int m_avgTFCount;		  //����ƽ���¶Ⱥ�ƽ�������õ��ۼӼ�����
	int m_maxMeterNum;        //������������������������
	int m_oldMaxMeterNum;     //�ϴα�����������
	int m_validMeterNum;          //ʵ�ʼ��ĸ���
	QMap<int, int> m_meterPosMap; //������±����λ�ŵ�ӳ���ϵ
	QMap<int, float> m_gradeErrA;  //��ͬ�ȼ��ȱ��Ӧ�ı�׼������A
	QMap<int, float> m_gradeErrB;  //��ͬ�ȼ��ȱ��Ӧ�ı�׼������B
	QMap<int, float> m_mapNormalFlow;  //��ͬ����ȱ��Ӧ�ĳ�������

	float *m_meterStartValue; //�����ĳ�ֵ
	float *m_meterEndValue;   //��������ֵ
	float *m_meterTemper;	  //�������¶�
	float *m_meterDensity;    //�������ܶ�
	float *m_meterStdValue;   //�����ı�׼ֵ
	float *m_meterError;	  //���������(��ǰ�����㲻ͬ��λ�����)
	float m_balStartV;        //��ƽ��ֵ
	float m_balEndV;          //��ƽ��ֵ
	float m_pipeInTemper;     //����¶�
	float m_pipeOutTemper;    //�����¶�
	float m_realFlow;		  //����(m3/h��
	float **m_meterErr;       //���������(��ͬ��λ����ͬ����������)

	Flow_Verify_Record_PTR m_recPtr; //��Ч�ļ춨��¼
	QString m_timeStamp; //ʱ��� ����
	QString m_nowDate;  
	QString m_validDate;

	int m_nowOrder;				//��ǰ�춨����

	now_state m_state; //��ǰ����״̬����ʼ̬������ֵ̬������ֵ̬��

	ReadComConfig *m_readComConfig; //����������
	PortSet_Ini_STR m_portsetinfo;  //�˿�����

	//����������
	uint m_totalcount;  //������
	float m_startWeight;//��ƽ��ֵ
	float m_endWeight;  //��ƽ��ֵ
	float m_deltaWeight[FLOW_SAMPLE_NUM];
	QTimer *m_flowRateTimer;  //��ʱ��:���ڼ�������

	//��ƽ��������ͻ�ˮ����
	float m_balMaxWht;
	float m_balBottomWht;

	void initBalanceCom();     //��ƽ����
	void initTemperatureCom(); //�¶Ȳɼ�����
	void initControlCom();     //���ſ��ƴ���
	void initMeterCom();       //��������
	void initValveStatus();	   //��ʼ������״̬

	int isComAndPortNormal();   //���ڡ��˿������Ƿ�����
	int isDataCollectNormal();	//������ݲɼ��Ƿ���������ƽ���¶ȡ���������Ƶȣ�
	int isMeterPosValid(int meterPos); //�жϱ�λ���Ƿ���Ч(�ñ�λ�Ƿ���Ҫ���)
	int getValidMeterNum();       //��ȡ��Ч�ļ�����()


public slots:
	void closeEvent(QCloseEvent * event);

	int readNowParaConfig();	 //��ȡ��ǰ�춨����
	void showNowKeyParaConfig(); //��ʾ��ǰ�ؼ�����������Ϣ
	void initTableWidget();     //���ñ������

	int on_btnExhaust_clicked();  //���"����"��ť
	void on_btnStart_clicked();   //���"��ʼ"��ť
	void on_btnGoOn_clicked();    //���"����"��ť
	void on_btnNext_clicked();    //���"��һ��"��ť
	void on_btnStop_clicked();    //���"��ֹ���"��ť
	void on_btnExit_clicked();    //�˳���ť
	void slotExaustFinished();    //����ʱ�����
	int prepareInitBalance();     //��ʼ�춨ǰ��׼����ƽ��ʼ����
	int openAllValveAndPump();    //�����з��ź�ˮ��
	int readAllMeter();           //��ȡ���б����
	int setAllMeterVerifyStatus();   //�������������춨״̬
	int closeAllFlowPointValves();//�ر����������㷧��
	int closeWaterOutValve();     //�رշ�ˮ��
	int openWaterOutValve();      //�򿪷�ˮ��
	int isBalanceValueBigger(float targetV, bool flg=true);    //�ж���ƽ����,flg: true-Ҫ�����Ŀ������(Ĭ��)��false-Ҫ��С��Ŀ������
	int judgeBalanceAndCalcAvgTemperAndFlow(float targetV); //�ж���ƽ���������ۼӽ������¶ȣ�ÿ���ۼ�һ�Σ����ڼ��������ƽ���¶�
	void stopVerify();            //ֹͣ�춨
	void startVerify();           //��ʼ�춨
	bool judgeBalanceCapacity();   //�ж���ƽ�����Ƿ��ܹ�����춨���� �����춨
	int judgeBalanceCapacitySingle(int order); //�ж���ƽ�����Ƿ��ܹ�����춨���� �������춨
	int prepareVerifyFlowPoint(int order);     //׼������������ļ춨
	int startVerifyFlowPoint(int order);       //��ʼ����������ļ춨
	int openValve(UINT8 portno);    //�򿪿��Ʒ�
	int closeValve(UINT8 portno);   //�رտ��Ʒ�
	int operateValve(UINT8 portno); //�������Ʒ����򿪻��߹ر�
	int openWaterPump();			//��ˮ��
	int closeWaterPump();			//�ر�ˮ��
	int operateWaterPump();			//����ˮ�ã��򿪻��߹ر�
	int getMeterStartValue();     //��ȡ���ֵ
	int getMeterEndValue();       //��ȡ����ֵ
	void makeStartValueByLastEndValue(); //��һ�ε���ֵ��Ϊ���εĳ�ֵ
	int calcAllMeterError();//�������б��������
	int calcMeterError(int idx); //����ĳ��������

	void slotFreshBalanceValue(const float& balValue);  //ˢ����ƽ��ֵ
	void slotFreshComTempValue(const QString& tempStr); //ˢ���¶�ֵ
	void slotFreshFlowRate(); //��������

	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //�̵������سɹ���Ӧ�Ĳۺ���
	void slotSetRegulateOk();     //���ڷ����سɹ���Ӧ�Ĳۺ���

	void slotSetMeterNumber(const QString& comName, const QString& meterNumber);
	void slotSetMeterFlow(const QString& comName, const float& flow);
	void setValveBtnBackColor(QToolButton *btn, bool status); //���÷��Ű�ť����ɫ
	void setRegBtnBackColor(QPushButton *btn, bool status);	  //���õ��ڷ���ť����ɫ

	void on_btnParaSet_clicked();	   //��������
	void on_btnWaterIn_clicked();      //��ˮ��
	void on_btnWaterOut_clicked();     //��ˮ��
	void on_btnValveBig_clicked();     //��������
	void on_btnValveMiddle1_clicked(); //����һ
	void on_btnValveMiddle2_clicked(); //������
	void on_btnValveSmall_clicked();   //С������

	void on_btnWaterPump_clicked(); //ˮ��
	void on_btnSetFreq_clicked();   //���ñ�Ƶ��Ƶ��

	void on_tableWidget_cellChanged(int row, int column);
	int saveAllVerifyRecords(); //�������б����ļ춨��¼
	void clearTableContents();

	void on_btnAllReadMeter_clicked();   //����(���б�
	void on_btnAllVerifyStatus_clicked();//���ü춨״̬(���б�
	void on_btnAllAdjError_clicked(); //�������(���б�)
	void on_btnAllModifyNO_clicked(); //�޸ı��(���б�

	void slotModifyMeterNO(const int &row); //�޸ı��
	void slotAdjustError(const int &row);   //�������
	void slotReadMeter(const int &row);     //����(������)
	void slotVerifyStatus(const int &row);  //�춨״̬

private slots:

signals:

private:
	Ui::FlowWeightClass ui;

};

#endif //FLOWWEIGHT_H