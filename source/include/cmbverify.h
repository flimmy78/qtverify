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



class CMBVERIFY_EXPORT CmbVerifyDlg : public QWidget
{
	Q_OBJECT

public:
	CmbVerifyDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CmbVerifyDlg();


public slots:
	void closeEvent(QCloseEvent * event);

	void on_btnPara_clicked();
	void on_btnExit_clicked();

private slots:

signals:

private:
	Ui::CmbVerifyClass ui;

};

#endif //CMBVERIFY_H