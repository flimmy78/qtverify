#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include <QtGui/QCloseEvent>
#include <QtCore/QProcess>

#include "ui_mainform.h"

class DbMySql;
class QueryResult;
class SetComFrm;
class DataTestDlg;
class SetPortFrm;
class CMasterSlave;
class CAlgorithm;
class FlowWeightDlg;
class FlowStandardDlg;
class TotalWeightDlg;
class TotalStandardDlg;

class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainForm();

	DbMySql *m_mySql;
	QueryResult *m_query;
	CAlgorithm *m_alg;
	SetComFrm *m_setcom; //���ڲ�������
	DataTestDlg *m_datatestdlg; //�ɼ�����Ʋ��Գ���
	SetPortFrm *m_portSet; //�˿�ģ������
	CMasterSlave *m_masterslave; //����-�ӻ�����
	QProcess *m_comProcess; //�����ⲿ���ڵ��Թ���
	FlowWeightDlg *m_flowWeightDlg;      //�����춨(������)
	FlowStandardDlg *m_flowStandardDlg;  //�����춨(��׼��)
	TotalWeightDlg *m_totalWeightDlg;    //�����춨(��׼��)
	TotalStandardDlg *m_totalStandardDlg;//�����춨(��׼��)

	void closeEvent(QCloseEvent * event);

public slots:
	//SystemSet
	void on_actionComSet_triggered();
	void on_actionPortSet_triggered();
	void on_actionComDebuger_triggered();
	void on_actionDataTest_triggered();
	void on_actionMasterSlaveSet_triggered();
	void on_actionMySql_triggered();

	//Component Verify
	void on_actionFlowWeight_triggered();
	void on_actionFlowStandard_triggered();
	void on_actionTemperCompare_triggered();
	void on_actionTemperPara_triggered();
	void on_actionCalculator_triggered();
	void on_actionCombine_triggered();

	//Total Verify
	void on_actionTotalWeight_triggered();
	void on_actionTotalStandard_triggered();

	//Data Query
	void on_actionFlowResult_triggered();
	void on_actionTotalResult_triggered();
	void on_actionTemperResult_triggered();
	void on_actionCalculatorResult_triggered();
	void on_actionCombineResult_triggered();
	void on_actionQueryExcel_triggered();

	//About
	void on_actionExit_triggered();
	void on_actionAbout_triggered();

	//Style
	void on_actionDefault_triggered();
	void on_actionClassic_triggered();
	void on_actionFashion_triggered();

	//Language
	void chaneLanguage(QString lang);
	void on_actionEnglish_triggered();
	void on_actionChinese_triggered();

private:
	Ui::qMainFormClass ui;
};

extern MainForm *g_mainform;

#endif // MAINFORM_H
