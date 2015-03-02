#ifndef TOTALWEIGHT_H
#define TOTALWEIGHT_H

#ifdef TOTALWEIGHT_DLL
#  ifdef WIN32
#  define TOTALWEIGHT_EXPORT __declspec(dllexport)
#  else
#  define TOTALWEIGHT_EXPORT
#  endif
#else
#  ifdef WIN32
#  define TOTALWEIGHT_EXPORT __declspec(dllimport)
#  else
#  define TOTALWEIGHT_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>

#include "ui_totalweight.h"
#include "comobject.h"

class CAlgorithm;
class ParaSetDlg;
class ParaSetReader;
class ReadComConfig;


class TOTALWEIGHT_EXPORT TotalWeightDlg : public QWidget
{
	Q_OBJECT

public:
	TotalWeightDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~TotalWeightDlg();

	QDataWidgetMapper *m_meterStdMapper;

	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;

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
	Verify_Params_PTR m_nowParams; //��ǰ�춨����
	bool m_continueVerify;    //�Ƿ������춨
	bool m_resetZero;         //�Ƿ��ֵ����
	bool m_autopick;          //�Ƿ��Զ��ɼ�
	int m_flowPointNum;       //������ĸ���
	int m_exaustSecond;		  //����ʱ��
	int m_standard;           //����
	int m_model;              //���ͺ�
	int m_meterType;          //������
	int m_manufac;			  //���쳧��(��³����, ���)
	//�춨������صĿ��Ʋ��� end

	int m_tempCount;		  //����ƽ���¶��õ��ۼӼ�����
	int m_maxMeterNum;        //������������������������
	int m_validMeterNum;          //ʵ�ʼ��ĸ���
	QMap<int, int> m_meterPosMap; //������±����λ�ŵ�ӳ���ϵ
	QMap<int, float> m_gradeErr;  //��ͬ�ȼ��ȱ��Ӧ�ı�׼���

	float *m_meterStartValue; //�����ĳ�ֵ
	float *m_meterEndValue;   //��������ֵ
	float *m_meterTemper;	  //�������¶�
	float *m_meterDensity;    //�������ܶ�
	float *m_meterStdValue;   //�����ı�׼ֵ
	float *m_meterError;	  //���������
	float m_balStartV;        //��ƽ��ֵ
	float m_balEndV;          //��ƽ��ֵ
	double m_pipeInTemper;    //����¶�
	double m_pipeOutTemper;   //�����¶�

	Flow_Verify_Record_PTR m_recPtr; //��Ч�ļ춨��¼
	QString m_timeStamp; //ʱ��� ����
	QString m_nowDate;  
	QString m_validDate;

	float m_flowPoint;
	int m_nowOrder;				//��ǰ�춨����

	bool m_inputStartValue; //�ֶ��ɼ�ʱ���ȴ������ֵ״̬
	bool m_inputEndValue;   //�ֶ��ɼ�ʱ���ȴ�������ֵ״̬

	bool m_startValueFlag;  //�Զ��ɼ�ʱ���������ȱ��ֵ������ֵ

	ReadComConfig *m_readComConfig; //����������
	PortSet_Ini_STR m_portsetinfo;  //�˿�����

	float m_balLastValue; //��ƽ��һ�ζ����������ж���ƽ��ֵ�Ƿ���ͻ�䣬������

	//����������
	uint m_totalcount;  //������
	float m_startWeight;//��ƽ��ֵ
	float m_endWeight;  //��ƽ��ֵ
	float m_deltaWeight[FLOW_SAMPLE_NUM];
	QTimer *m_flowRateTimer;  //��ʱ��:���ڼ�������


	void initBalanceCom();     //��ƽ����
	void initTemperatureCom(); //�¶Ȳɼ�����
	void initControlCom();     //���ſ��ƴ���
	void initMeterCom();       //��������
	void initValveStatus();	   //��ʼ������״̬

	int isComAndPortNormal();   //���ڡ��˿������Ƿ�����
	int isWaterOutValveOpen();  //����ˮ�����Ƿ��
	int isDataCollectNormal();	//������ݲɼ��Ƿ���������ƽ���¶ȡ���������Ƶȣ�
	int isMeterPosValid(int meterPos); //�жϱ�λ���Ƿ���Ч(�ñ�λ�Ƿ���Ҫ���)


public slots:
	void closeEvent(QCloseEvent * event);

	int readNowParaConfig();	 //��ȡ��ǰ�춨����
	void showNowKeyParaConfig(); //��ʾ��ǰ�ؼ�����������Ϣ
	void initTableWidget();     //���ñ������

	void on_btnExhaust_clicked(); //���"����"��ť
	void on_btnStart_clicked();   //���"��ʼ"��ť
	void on_btnNext_clicked();    //���"��һ��"��ť
	void on_btnStop_clicked();    //���"��ֹ���"��ť
	void slotExaustFinished();    //����ʱ�����
	int openAllValveAndPump();    //�����з��ź�ˮ��
	int readMeter();          //��ȡ�ȱ�
	int setMeterVerifyStatus();   //�������������춨״̬
	int closeAllFlowPointValves();//�ر����������㷧��
	int closeWaterOutValve();     //�رշ�ˮ��
	int openWaterOutValve();      //�򿪷�ˮ��
	int openBigFlowValve();       //�򿪴������㷧��
	int closeBigFlowValve();      //�رմ������㷧��
	int judgeBalanceInitValue(float v);    //�ж���ƽ����
	int judgeBalanceAndCalcAvgTemper(float targetV); //�ж���ƽ���������ۼӽ������¶ȣ�ÿ���ۼ�һ�Σ����ڼ��������ƽ���¶�
	void startVerify();           //��ʼ�춨
	int getValidMeterNum();       //��ȡ��Ч�ļ�����()
	bool judgeBalanceCapacity();   //�ж���ƽ�����Ƿ��ܹ�����춨���� �����춨
	int judgeBalanceCapacitySingle(int order); //�ж���ƽ�����Ƿ��ܹ�����춨���� �������춨
	int prepareVerifyFlowPoint(int order);     //׼������������ļ춨
	int startVerifyFlowPoint(int order);       //��ʼ����������ļ춨
	int openValve(UINT8 portno);    //�򿪿��Ʒ�
	int closeValve(UINT8 portno);   //�رտ��Ʒ�
	int operateValve(UINT8 portno); //�������Ʒ����򿪻��߹ر�
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

	void on_btnReadMeter_clicked(); //����ť
	void on_btnExit_clicked();//�˳���ť
	
	void slotModifyMeterNo(const int &row); //�޸ı��
	void slotAdjustError(const int &row); //�������

private slots:

signals:

private:
	Ui::TotalWeightClass ui;

};

#endif //TOTALWEIGHT_H