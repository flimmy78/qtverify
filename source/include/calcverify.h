#ifndef CALCVERIFY_H
#define CALCVERIFY_H

#ifdef CALCVERIFY_DLL
#  ifdef WIN32
#  define CALCVERIFY_EXPORT __declspec(dllexport)
#  else
#  define CALCVERIFY_EXPORT
#  endif
#else
#  ifdef WIN32
#  define CALCVERIFY_EXPORT __declspec(dllimport)
#  else
#  define CALCVERIFY_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>

#include "ui_calcverify.h"
#include "comobject.h"

class CalcParaDlg;

#define COLUMN_IN_RESIST	1 //���ڵ���
#define COLUMN_OUT_RESIST	2 //���ڵ���
#define COLUMN_RECOM_V		3 //��������(L)
#define COLUMN_ANALOG_V		4 //ģ������(L)
#define COLUMN_IN_TEMPER	5 //�����¶�
#define COLUMN_OUT_TEMPER	6 //�����¶�
#define COLUMN_K_COE		7 //Kϵ��
#define COLUMN_THEORY_E		8 //��������
#define COLUMN_E0			9 //E0
#define COLUMN_E1			10 //E1
#define COLUMN_DISP_E		11 //����ʾֵ
#define COLUMN_DISP_ERROR	12 //ʾֵ���
#define COLUMN_STD_ERROR	13 //����Ҫ��

class CALCVERIFY_EXPORT CalcDlg : public QDialog
{
	Q_OBJECT

public:
	CalcDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CalcDlg();

	CalcParaDlg *m_calcParaDlg;

	QString m_meterNO;
	int m_standard;
	int m_model;
	int m_grade;
	int m_manufact;
	int m_verifydept;
	int m_verifyperson;
	float m_maxT;
	float m_minT;
	float m_maxDeltaT;
	float m_minDeltaT;
	float m_refT;
	float m_refDeltaT;
	QMap<int, int> mapIdx;

	Calc_Verify_Record_PTR m_recPtr; //��Ч�ļ춨��¼
	QString m_timeStamp; //��¼ʱ���

	void initUi();
	float calcTemperByResist(int port, float resist); //���ݵ�������¶�
	float getKCoeByTemper(float inT, float outT); //���ݽ����¶Ⱥͳ����¶Ȼ�ȡKϵ��
	float calcRecomVolume(float stdErr, float inTemper, float outTemper, float kCoe); //�����Ƽ����
	float calcTheoryEnergy(float kCoe, float analogV, float inTemper, float outTemper); //������������

	int saveVerifyRecords(); //ͳ����Ч�ļ춨�������

public slots:
	void closeEvent(QCloseEvent * event);

	void on_btnPara_clicked();
	void on_btnStart_clicked();
	void on_btnSave_clicked();
	void on_btnExit_clicked();

	void freshCalcPara();
	void on_tableWidget_cellChanged(int row, int column);
private slots:

signals:

private:
	Ui::CalcDlgClass ui;

};

#endif //CALCVERIFY_H