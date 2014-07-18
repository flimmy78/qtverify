#ifndef PARASETDLG_H
#define PARASETDLG_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QDateTime>

#include "ui_parasetdlg.h"
#include "qtexdb.h"
#include "parasetdlg_global.h"
#include "basedef.h"
class PARASETDLG_EXPORT ParaSetReader;
class PARASETDLG_EXPORT ParaSetDlg : public QWidget
{
	Q_OBJECT

public:
	ParaSetDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ParaSetDlg();

	int m_meterStdNum;	//热量表规格
	MeterStandard_PTR m_meterStdPtr;

	int m_meterTypeNum;	//热量表类型
	MeterType_PTR m_meterTypePtr;

	int m_manuFacNum;	//制造单位
	Manufacture_PTR m_manuFacPtr;

	CBaseExdb m_basedb;

	void initUiData(); //从数据库读取记录，填充combox等
	void closeEvent(QCloseEvent * event);

public slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();

private:
	Ui::ParaSetDlgClass ui;
	char filename[255];
	
	QSettings *settings;//配置文件
	QParams_PTR params;//本次的配置参数
	ParaSetReader *lastParams;//上次的配置参数
	qint64 timestamp;//时间戳

	QVector<QLineEdit*> lineEdit_uppers;
	QVector<QLineEdit*> lineEdit_flows;
	QVector<QLineEdit*> lineEdit_quantites;
	QVector<QLineEdit*> lineEdit_valves;
	QVector<QComboBox*> cBox_seqs;

	void flowPointVector();

	void installLastParams();//装载上次的参数配置
	void 	installHead();
	void installFlowPoint();
	void installBool();
	void installOther();

	void SaveHead();//保存基本信息
	void SaveFlowPoint(int i);//保存流量点信息
	void SaveBool();//保存布尔值
	void SaveOther();//保存其他信息
private slots:

};

class PARASETDLG_EXPORT ParaSetReader
{
	public:
		QSettings *settings;
		QParams_PTR params;

		ParaSetReader();
		~ParaSetReader();

		
		flow_point_info getFpBySeq(int);

		int* readParamIndexes();
private:
	void readParamValues();
	void readHead();
	void readFlowPoints();

	void readBool();
	void readOther();
};
#endif // PARASETDLG_H
