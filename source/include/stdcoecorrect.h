#ifndef STDCOECORRECT_H
#define STDCOECORRECT_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QDateTime>

#include "ui_stdcoecorrect.h"
#include "systemsetdlg_global.h"
#include "basedef.h"

class SYSTEMSETDLG_EXPORT StdCoeCorrect : public QWidget
{
	Q_OBJECT

public:
	StdCoeCorrect(QWidget *parent = 0, Qt::WFlags flags = 0);
	~StdCoeCorrect();

signals:

public slots:
	void on_btnExit_clicked();


private:
	Ui::StdCoeCorrectClass ui;
private slots:

};

#endif // STDCOECORRECT_H
