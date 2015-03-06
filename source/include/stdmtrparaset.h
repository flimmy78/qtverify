#ifndef STDPARASET_H
#define STDPARASET_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QDateTime>

#include "ui_stdmtrparaset.h"
#include "systemsetdlg_global.h"
#include "basedef.h"

class SYSTEMSETDLG_EXPORT StdMtrParaSet : public QWidget
{
	Q_OBJECT

public:
	StdMtrParaSet(QWidget *parent = 0, Qt::WFlags flags = 0);
	~StdMtrParaSet();

signals:

public slots:
	void on_btnExit_clicked();

private:
	Ui::StdMtrParaSetClass ui;
private slots:

};

#endif // STDPARASET_H
