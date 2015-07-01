#ifndef STDPLASENSOR_H
#define STDPLASENSOR_H

#include <QtGui/QWidget>
#include <QSettings>

#include "ui_stdplasensor.h"
#include "systemsetdlg_global.h"

class SYSTEMSETDLG_EXPORT stdplasensorDlg : public QWidget
{
	Q_OBJECT
public:
	stdplasensorDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~stdplasensorDlg();

	public slots:
		void closeEvent(QCloseEvent * event);
		void showEvent(QShowEvent *);

		void on_btn_pt25_save_clicked();
		void on_btn_pt100_calc_clicked();
		void on_btn_pt100_save_clicked();
		void on_btn_pt100_exit_clicked();
		void on_btn_model_save_clicked();
		void on_gBox_pt25_clicked();
		void on_gBox_pt100_clicked();
signals:

private:
	Ui::StdPlaSensorDlgClass ui;
	QSettings* m_config;//��׼�¶ȼƲ���
	bool m_tbls_inited;//���б���ʼ�����

	void initTbls();//��ʼ�����
	void initPt100tbl(QTableWidget *tbl);

	void readpt25config();
	void readpt100config();
	void readmodelconfig();
	void readInUse();

	void calcPt100In();
	void calcPt100Out();

	bool tblFilled(QTableWidget*);//����Ƿ��������
};
#endif//STDPLASENSOR_H