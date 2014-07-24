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

#include <QtGui/QWidget>

#include "ui_weightmethod.h"

class WEIGHTMETHOD_EXPORT WeightMethodDlg : public QWidget
{
	Q_OBJECT

public:
	WeightMethodDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~WeightMethodDlg();

	QTimer *m_exaustTimer; //������ʱ��
	int m_exaustSecond;	

	QTimer *m_balTimer; //ģ����ƽ��ʱˢ���� �����ڲ���
	float m_balValue;

	int isComAndPortNormal(); //���ڡ��˿������Ƿ�����
	int isWaterOutValveOpen(); //����ˮ�����Ƿ��
	int readParaConfig();		//�����������ļ�
	int isDataCollectNormal();	//������ݲɼ��Ƿ���������ƽ���¶ȡ���������Ƶȣ�
	int isAllMeterInVerifyStatus(); //�ж��������ѽ���춨״̬

public slots:
	void closeEvent(QCloseEvent * event);
	void removeSubTab(int index);
	int on_btnExhaust_clicked();  //���"������ť"
	void on_btnStart_clicked();    //���"��ʼ"��ť
	int openAllValuesAndPump();   //�����з��ź�ˮ��
	void slotExaustFinished();    //����ʱ�����
	int readMeterNumber();        //��ȡ���
	int setMeterVerifyStatus();   //�������������춨״̬
	int closeAllFlowPointValves();//�ر����������㷧��
	int closeWaterOutValve();     //�رշ�ˮ��
	int openBigFlowValve();       //�򿪴������㷧��
	int closeBigFlowValve();      //�رմ������㷧��
	int judgeBalanceInitValue(float v); //�ж���ƽ����
	void startVerify();           //��ʼ�춨

	void freshBigBalaceValue();   //ˢ�´���ƽ��ֵ �����ڲ��� ģ����ƽ��ֵ�仯

private slots:

signals:


private:
	Ui::WeightMethodClass ui;

};


#endif //WEIGHTMETHOD_H