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

#include <QtGui/QWidget>

#include "ui_weightmethod.h"
#include "parasetdlg.h"
#include "comobject.h"
#include "ReadComConfig.h"

class WEIGHTMETHOD_EXPORT WeightMethodDlg : public QWidget
{
	Q_OBJECT

public:
	WeightMethodDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~WeightMethodDlg();

	ParaSetReader *m_paraSetReader;

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

	//�춨������صĿ��Ʋ��� begin
	bool m_continueVerify; //�Ƿ������춨
	bool m_resetZero;      //�Ƿ��ֵ����
	QMap<int, int> m_meterNumMap;//��������������������
	int m_meterNum;           //�����������
	int m_flowPointNum;       //������ĸ���
	float *m_meterStartValue; //�����ĳ�ֵ
	float *m_meterEndValue;   //��������ֵ
	float m_balStartV;        //��ƽ��ֵ
	float m_balEndV;          //��ƽ��ֵ
	float m_pipeInTemper;     //����¶�
	float m_pipeOutTemper;    //�����¶�
	//�춨������صĿ��Ʋ��� end

	ReadComConfig *m_readComConfig; //����������
	void initBalanceCom();     //��ƽ����
	void initTemperatureCom(); //�¶Ȳɼ�����

	int isComAndPortNormal(); //���ڡ��˿������Ƿ�����
	int isWaterOutValveOpen(); //����ˮ�����Ƿ��
	int readParaConfig();		//�����������ļ�
	int isDataCollectNormal();	//������ݲɼ��Ƿ���������ƽ���¶ȡ���������Ƶȣ�
	int isAllMeterInVerifyStatus(); //�ж��������ѽ���춨״̬

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
	void startVerify();           //��ʼ�춨
	int judgeBalanceCapacity();   //�ж���ƽ�����Ƿ��ܹ�����춨���� �����춨
	int judgeBalanceCapacitySingle(int order); //�ж���ƽ�����Ƿ��ܹ�����춨���� �������춨
	int startVerifyFlowPoint(int order); //����������ļ춨
	int openValve(int portno);    //�򿪿��Ʒ�
	int closeValve(int portno);   //�رտ��Ʒ�

	void slotFreshBalanceValue(const QString& Str); //ˢ����ƽ��ֵ
	void slotFreshComTempValue(const QString& tempStr); //ˢ���¶�ֵ
	void slotFreshFlow(); //��������

	void freshBigBalaceValue();   //ˢ�´���ƽ��ֵ �����ڲ��� ģ����ƽ��ֵ�仯

private slots:

signals:


private:
	Ui::WeightMethodClass ui;

};


#endif //WEIGHTMETHOD_H