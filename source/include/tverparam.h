#ifndef TVERPARAM_H
#define TVERPARAM_H

#ifdef TVERPARAM_DLL
#  ifdef WIN32
#  define TVERPARAM_EXPORT __declspec(dllexport)
#  else
#  define TVERPARAM_EXPORT
#  endif
#else
#  ifdef WIN32
#  define TVERPARAM_EXPORT __declspec(dllimport)
#  else
#  define TVERPARAM_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>
#include "ui_tverparam.h"
#include "tverparamparamdlg.h"
#include "protocol.h"

class TVERPARAM_EXPORT tverparamDlg : public QWidget
{
	Q_OBJECT

public:
	tverparamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~tverparamDlg();

public:
	float readStdTmp();//
	public slots:
		void closeEvent(QCloseEvent * event);


		void on_btn_param_clicked();
		void on_btn_excel_clicked();//保存至Excel
		void on_btn_save_clicked();//保存至数据库
		void on_btn_exit_clicked();
private:
	Ui::PlaParamDlgClass ui;
	tverparamparamDlg *m_PlaCompParamDlg;
private:
	void readConfig();
};

#endif//TVERPARAM_H