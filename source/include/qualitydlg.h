#ifndef QUALITYDLG_H
#define QUALITYDLG_H

#include <QtGui/QWidget>

#include "qualitydlg_global.h"
#include "ui_qualitydlg.h"
#include "parasetdlg.h"
#include "comthread.h"


class QUALITYDLG_EXPORT QualityDlg : public QWidget
{
	Q_OBJECT

public:
	QualityDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QualityDlg();

	ParaSetDlg *m_paraset;

	ComThread m_tempThread;
 	TempComObject *m_tempObj;


public slots:
	void on_btnWaterIn_clicked();

	void on_btnParaSet_clicked();
	void on_btnExit_clicked();

	void setValveBtnBackColor(QPushButton *btn, bool isOpen);

	void slotFreshComTempValue(const QString& tempStr);

private:
	Ui::QualityDlgClass ui;

private slots:

};

#endif // QUALITYDLG_H
