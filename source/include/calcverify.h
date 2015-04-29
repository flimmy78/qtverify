#ifndef CALCVERIFY_H
#define CALCVERIFY_H

#ifdef CALCVERIFY_DLL
#  ifdef WIN32
#  define CALCVERIFY_EXPORT __declspec(dllexport)
#  else
#  define CALCVERIFY_EXPORT
#  endif
#else
#  ifdef WIN32
#  define CALCVERIFY_EXPORT __declspec(dllimport)
#  else
#  define CALCVERIFY_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>

#include "ui_calcverify.h"
#include "comobject.h"

class CalcParaDlg;

class CALCVERIFY_EXPORT CalcDlg : public QDialog
{
	Q_OBJECT

public:
	CalcDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CalcDlg();

	CalcParaDlg *m_calcParaDlg;
	float m_maxT;
	float m_minT;
	float m_maxDeltaT;
	float m_minDeltaT;
	float m_refT;
	float m_refDeltaT;

	void initUi();

public slots:
	void closeEvent(QCloseEvent * event);

	void on_btnPara_clicked();
	void on_btnExit_clicked();

	void freshCalcPara();
	void on_tableWidget_cellChanged(int row, int column);
private slots:

signals:

private:
	Ui::CalcDlgClass ui;

};

#endif //CALCVERIFY_H