#ifndef STDCOECORRECT_H
#define STDCOECORRECT_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QDateTime>

#include "ui_stdmtrcoecorrect.h"
#include "systemsetdlg_global.h"
#include "basedef.h"

class SYSTEMSETDLG_EXPORT StdMtrCoeCorrect : public QWidget
{
	Q_OBJECT

public:
	StdMtrCoeCorrect(QWidget *parent = 0, Qt::WFlags flags = 0);
	~StdMtrCoeCorrect();

signals:

public slots:
	void on_btnExit_clicked();
	void resizeEvent(QResizeEvent * event);

private:
	Ui::StdMtrCoeCorrectClass ui;
private slots:

};

#endif // STDCOECORRECT_H
