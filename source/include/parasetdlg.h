#ifndef PARASETDLG_H
#define PARASETDLG_H

#include <QtGui/QWidget>

#include "ui_parasetdlg.h"
#include "qtexdb.h"


class ParaSetDlg : public QWidget
{
	Q_OBJECT

public:
	ParaSetDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ParaSetDlg();

	int m_meterStdNum;	//热量表规格
	MeterStandard_PTR m_meterStdPtr;

	int m_meterTypeNum;	//热量表类型
	MeterType_PTR m_meterTypePtr;

	CBaseExdb m_basedb;

	void initUiData(); //从数据库读取记录，填充combox等

	

	void closeEvent(QCloseEvent * event);

public slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();

private:
	Ui::ParaSetDlgClass ui;

private slots:

};

#endif // PARASETDLG_H
