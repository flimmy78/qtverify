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

	void mapVfDeptModel();   //送检单位模型
	void mapManuDeptModel(); //制造单位模型
	void mapUserModel();     //检测员模型
	void mapMeterModelModel();//表型号模型
	void mapMeterStandardModel();//表规格模型

	void initSettings();
	void readSettings();
	void writeSettings();

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
	float m_maxT;
	float m_minT;
	float m_maxDeltaT;
	float m_minDeltaT;
};

#endif //CALCPARA_H