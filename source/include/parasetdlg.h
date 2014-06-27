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

	int m_meterStdNum;	//��������
	MeterStandard_PTR m_meterStdPtr;

	int m_meterTypeNum;	//����������
	MeterType_PTR m_meterTypePtr;

	CBaseExdb m_basedb;

	void initUiData(); //�����ݿ��ȡ��¼�����combox��

	

	void closeEvent(QCloseEvent * event);

public slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();

private:
	Ui::ParaSetDlgClass ui;

private slots:

};

#endif // PARASETDLG_H
