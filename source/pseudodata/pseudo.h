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

/*获取随机值*/
#define GET_RAND(number)		qsrand((QTime::currentTime()).msec());\
								int rand = qrand()%number;

#define MAP_FP(mapType)			mapType[flowPoint]//各个流量点的参数
#define SIGN					(rand%2?1:-1)//由随机数的奇偶性决定正负号
#define RATIONAL_RAND(number)	(rand/number)//适应不同用途的随机值范围
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
	Book*				m_book;//报表
	Sheet*				m_sheet;//表单
	Format*				m_format;//单元格格式
	Font*				m_font;//单元格字体
	
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
	void initWriteFp();//得到哪两个流量点要写入
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
	float getErr(float errLmt);//每行的误差根据误差限, 调整一个随机值

	float getStdEnergy(float hTemp, float lTemp, float mass);
	float getMeterEnergy(float stdEnergy, float err);

	void insertLogoRow(QString filename);
	void deleteLog(QString filename);
};

#endif//PSEUDO_H