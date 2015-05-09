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
#include <QtGui/QButtonGroup>

#include "ui_calcverify.h"
#include "comobject.h"

class CalcParaDlg;
class CAlgorithm;

#define COLUMN_IN_RESIST		1 //���ڵ���
#define COLUMN_OUT_RESIST		2 //���ڵ���
#define COLUMN_RECOM_V			3 //��������(L)
#define COLUMN_ANALOG_V			4 //ģ������(L)
#define COLUMN_IN_TEMPER		5 //�����¶�
#define COLUMN_OUT_TEMPER		6 //�����¶�
#define COLUMN_K_COE			7 //Kϵ�������ʲ�
#define COLUMN_THEORY_ENERGY	8 //��������
#define COLUMN_E0				9 //E0
#define COLUMN_E1				10 //E1
#define COLUMN_DISP_ENERGY		11 //����ʾֵ
#define COLUMN_DISP_ERROR		12 //ʾֵ���
#define COLUMN_STD_ERROR		13 //����Ҫ��


class CALCVERIFY_EXPORT CalcDlg : public QDialog
{
	Q_OBJECT

public:
	CalcDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CalcDlg();

	CalcParaDlg *m_calcParaDlg;
	CAlgorithm *m_algo;

	QString algoStr[2];
	QString unitStr[2];
	QString KStr[2][2];

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

	QButtonGroup *btnGroupInstallPos; //��װλ�� 0:���ڣ�1:����
	QButtonGroup *btnGroupEnergyUnit; //������λ 0:MJ;1:kwh
	QButtonGroup *btnGroupAlgorithm;  //�㷨 0:�ʲ��1:Kϵ����

	void initUi();
	float calcTemperByResist(int port, float resist); //���ݵ�������¶�
	float getKCoeByTemper(float inT, float outT); //���ݽ����¶Ⱥͳ����¶Ȼ�ȡKϵ��
	float getEnthalpyDiffByTemper(float inT, float outT); //���ݽ����¶Ⱥͳ����¶Ȼ�ȡ�ʲ�
	float calcRecomVolumeByKCoe(float stdErr, float inTemper, float outTemper, float kCoe); //�����Ƽ����(Kϵ����)
	float calcRecomVolumeByEnthalpy(float stdErr, float inTemper, float outTemper, float enthalpyDiff); //�����Ƽ����(�ʲ)
	float calcTheoryEnergyByKCoe(float kCoe, float analogV, float inTemper, float outTemper); //Kϵ����������������
	float calcTheoryEnergyByEnthalpy(float analogV, float inTemper, float outTemper);//�ʲ������������

	int saveVerifyRecords(); //ͳ����Ч�ļ춨�������

public slots:
	void closeEvent(QCloseEvent * event);

	void on_btnPara_clicked();
	void on_btnStart_clicked();
	void on_btnSave_clicked();
	void on_btnExit_clicked();

	void freshCalcPara();
	void on_tableWidget_cellChanged(int row, int column);
	void slot_btnGroupInstallPos_clicked(int id);
	void slot_btnGroupEnergyUnit_clicked(int id);
	void slot_btnGroupAlgorithm_clicked(int id);

private slots:

signals:

private:
	Ui::CalcDlgClass ui;

};

#endif //CALCVERIFY_H