#ifndef QUALITYDLG_H
#define QUALITYDLG_H

#include <QtGui/QWidget>

#include "qualitydlg_global.h"
#include "ui_qualitydlg.h"

class QUALITYDLG_EXPORT QualityDlg : public QWidget
{
	Q_OBJECT

public:
	QualityDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QualityDlg();

public slots:
	void on_btnWaterIn_clicked();
// 	void on_btnWaterOut_clicked();
// 	void on_btnWaterValve1_clicked();
// 	void on_btnWaterValve2_clicked();
// 	void on_btnWaterValve3_clicked();
// 	void on_btnWaterValve4_clicked();

	void setValveBtnBackColor(QPushButton *btn, bool isOpen);

private:
	Ui::QualityDlgClass ui;

private slots:

};

#endif // QUALITYDLG_H
