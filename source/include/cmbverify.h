#ifndef CMBVERIFY_H
#define CMBVERIFY_H

#ifdef CMBVERIFY_DLL
#  ifdef WIN32
#  define CMBVERIFY_EXPORT __declspec(dllexport)
#  else
#  define CMBVERIFY_EXPORT
#  endif
#else
#  ifdef WIN32
#  define CMBVERIFY_EXPORT __declspec(dllimport)
#  else
#  define CMBVERIFY_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>

#include "ui_cmbverify.h"
#include "comobject.h"
#include "algorithm.h"
#include "cmbparam.h"



class CMBVERIFY_EXPORT CmbVerifyDlg : public QWidget
{
	Q_OBJECT

public:
	CmbVerifyDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CmbVerifyDlg();


public slots:
	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent *);

	void on_btnPara_clicked();
	void on_btnExit_clicked();

private slots:
	void freshCmbParam(void);
signals:

private:
	Ui::CmbVerifyClass ui;
	CmbParamDlg* m_CmbParamDlg;
	CAlgorithm* m_algo;

	QSettings* m_param_config;
};

#endif //CMBVERIFY_H