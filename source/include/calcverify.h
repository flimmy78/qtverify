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

#define COLUMN_IN_RESIST	1 //进口电阻
#define COLUMN_OUT_RESIST	2 //出口电阻
#define COLUMN_RECOM_V		3 //建议流量(L)
#define COLUMN_ANALOG_V		4 //模拟流量(L)
#define COLUMN_IN_TEMPER	5 //进口温度
#define COLUMN_OUT_TEMPER	6 //出口温度
#define COLUMN_K_COE		7 //K系数
#define COLUMN_THEORY_E		8 //理论热量
#define COLUMN_E0			9 //E0
#define COLUMN_E1			10 //E1
#define COLUMN_DISP_E		11 //热量示值
#define COLUMN_DISP_ERROR	12 //示值误差
#define COLUMN_STD_ERROR	13 //技术要求

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

	Calc_Verify_Record_PTR m_recPtr; //有效的检定记录
	QString m_timeStamp; //记录时间戳

	void initUi();
	float calcTemperByResist(float resist); //根据电阻计算温度
	float getKCoeByTemper(float inT, float outT); //根据进口温度和出口温度获取K系数
	float calcRecomVolume(); //计算推荐体积
	float calcTheoryEnergy(); //计算理论热量

	int saveVerifyRecords(); //统计有效的检定结果数量

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