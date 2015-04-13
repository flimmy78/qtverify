#ifndef TVERCOMP_H
#define TVERCOMP_H

#ifdef TVERCOMP_DLL
#  ifdef WIN32
#  define TVERCOMP_EXPORT __declspec(dllexport)
#  else
#  define TVERCOMP_EXPORT
#  endif
#else
#  ifdef WIN32
#  define TVERCOMP_EXPORT __declspec(dllimport)
#  else
#  define TVERCOMP_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>
#include "ui_tvercomp.h"
#include "tvercompparamdlg.h"
#include "protocol.h"

class TVERCOMP_EXPORT tvercompDlg : public QWidget
{
	Q_OBJECT

public:
	tvercompDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~tvercompDlg();

public:
	float readStdTmp();//
	public slots:
		void closeEvent(QCloseEvent * event);

		/******�ɼ���׼�¶ȼ���ֵ*********/
		void on_btn_read_1_clicked();
		void on_btn_read_2_clicked();
		void on_btn_read_3_clicked();

		/******��ձ�׼�¶ȼ���ֵ*********/
		void on_btn_clear_1_clicked();
		void on_btn_clear_2_clicked();
		void on_btn_clear_3_clicked();

		/******���첬������ֵ*********/
		void on_tbl_std_1_cellChanged(int, int);
		void on_tbl_std_2_cellChanged(int, int);
		void on_tbl_std_3_cellChanged(int, int);

		/******���첬�������*********/
		void on_tbl_chkerror_1_cellChanged(int, int);
		void on_tbl_chkerror_2_cellChanged(int, int);
		void on_tbl_chkerror_3_cellChanged(int, int);

		void on_btn_param_clicked();
		void on_btn_excel_clicked();//������Excel
		void on_btn_save_clicked();//���������ݿ�
		void on_btn_exit_clicked();
private:
	Ui::PlaCompDlgClass ui;
	tvercompparamDlg *m_PlaCompParamDlg;
private:
	void readConfig();
};

#endif//TCHKCOMP_H