#ifndef CALCPARA_H
#define CALCPARA_H

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>

#include "ui_calcpara.h"

class QSettings;
class QSqlTableModel;

class CalcParaDlg : public QDialog
{
	Q_OBJECT

public:
	CalcParaDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CalcParaDlg();

	QSettings *settings;

	void mapVfDeptModel();   //�ͼ쵥λģ��
	void mapManuDeptModel(); //���쵥λģ��
	void mapUserModel();     //���Աģ��
	void mapMeterModelModel();//���ͺ�ģ��
	void mapMeterStandardModel();//����ģ��

	void initSettings();
	void readSettings();
	void writeSettings();

	QString getMeterNO();
	int getStandard();
	int getModel();
	int getGrade();
	int getManuFact();
	int getVerifyDept();
	int getVerifyPerson();
	float getMaxT();
	float getMinT();
	float getMaxDeltaT();
	float getMinDeltaT();
signals:
	void saveSuccessSignal();

public slots:
	void closeEvent(QCloseEvent * event);
	void on_btnOK_clicked();
	void on_btnExit_clicked();

private slots:

signals:

private:
	Ui::CalcParaClass ui;
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
};

#endif //CALCPARA_H