#ifndef PSEUDO_H
#define PSEUDO_H

#ifdef PSEUDO_DLL
#  ifdef WIN32
#  define PSEUDO_EXPORT __declspec(dllexport)
#  else
#  define PSEUDO_EXPORT
#  endif
#else
#  ifdef WIN32
#  define PSEUDO_EXPORT __declspec(dllimport)
#  else
#  define PSEUDO_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QSettings>
#include "libxl/libxl.h"
#include "ui_pseudo.h"

#define FLOW_POINTS 3;

/*��ȡ���ֵ*/
#define GET_RAND(number)		qsrand((QTime::currentTime()).msec());\
								int rand = qrand()%number;

#define MAP_FP(mapType)			mapType[flowPoint]//����������Ĳ���
#define SIGN					(rand%2?1:-1)//�����������ż�Ծ���������
#define RATIONAL_RAND(number)	(rand/number)//��Ӧ��ͬ��;�����ֵ��Χ
#define FLOAT_TO_CHAR(value)	QString::number(value).toStdString().data()

using namespace libxl;

class ReportConfigStr
{
public:
	int meterCount;
	int dataStartRow;
	float normalFlowRate;
	float minDiffTemp;

	float HTemp_BRate;
	float LTemp_BRate;
	float PTemp_BRate;
	float Quantity_BRate;
	float FlowPoint_BRate;

	float HTemp_MRate;
	float LTemp_MRate;
	float PTemp_MRate;
	float Quantity_MRate;
	float FlowPoint_MRate;

	float HTemp_SRate;
	float LTemp_SRate;
	float PTemp_SRate;
	float Quantity_SRate;
	float FlowPoint_SRate;

	int col_Seq;
	int col_RecNo;
	int col_MeterNo;
	int col_FLowPoint;
	int col_InTemp;
	int col_OutTemp;
	int col_DiffTemp;
	int col_MeterE0;
	int col_MeterE1;
	int col_MeterE;
	int col_BalMass;
	int col_PipeTemp;
	int col_Density;
	int col_StandE;
	int col_Err;
	int col_ErrLmt;
	int col_Result;
};
typedef ReportConfigStr* ReportConfigPtr;

enum flowPointEnum
{
	BIG_RATE_ROW_OFFSET = 0,
	MID_RATE_ROW_OFFSET,
	SML_RATE_ROW_OFFSET
};

class PSEUDO_EXPORT CPseudoDlg : public QWidget
{
		Q_OBJECT
public:
	CPseudoDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CPseudoDlg();
public slots:
	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent *event);

	void on_btn_Exit_clicked();
	void on_btn_SaveConfig_clicked();
	void on_btn_FileList_clicked();
	void on_btn_Export_clicked();

private:
	Ui::PseudoDlgClass *ui;

	QStringList			m_excelFiles;
	QSettings		   *m_config;
	ReportConfigPtr		m_prameterPtr;
	int					m_writeFlowPoints;
	QList<flowPointEnum>m_fpList;
	Book*				m_book;//����
	Sheet*				m_sheet;//��
	Format*				m_format;//��Ԫ���ʽ
	Font*				m_font;//��Ԫ������
	
	QMap<flowPointEnum, float>	m_mapHTemp;
	QMap<flowPointEnum, float>	m_mapLTemp;
	QMap<flowPointEnum, float>	m_mapPTemp;
	QMap<flowPointEnum, float>	m_mapVerifyMass;
	QMap<flowPointEnum, float>	m_mapFlowPoint;

	void installConfig();
	void freshConfig();
	void mapFlowPoints();
	void LoadExcel(QString filename);
	void saveExcel(QString filename);
	void saveConfig();
	void disableInputs();
	void initWriteFp();//�õ�������������Ҫд��
	bool chkFlowPoints();
	void exportReports();
	void exportReport(QString filename);
	void insertRows();
	void writeSingleRow(flowPointEnum flowPoint, int rowNum);
	void mergeCells(int meterNo);
	int getStartRowNum(int meterNo);
	int getEndRowNum(int meterNo);

	float getHighTemp(flowPointEnum flowPoint);
	float getLowTemp(flowPointEnum flowPoint);
	float getPipeTemp(flowPointEnum flowPoint);
	float getPipeDensity(float temp);
	float getBalanceMass(flowPointEnum flowPoint);
	float getFlowPoint(flowPointEnum flowPoint);
	float getErrLmt(float delta_t, float flow_rate);
	float getErr(float errLmt);//ÿ�е������������, ����һ�����ֵ

	float getStdEnergy(float hTemp, float lTemp, float mass);
	float getMeterEnergy(float stdEnergy, float err);

	void insertLogoRow(QString filename);
	void deleteLog(QString filename);
};

#endif//PSEUDO_H