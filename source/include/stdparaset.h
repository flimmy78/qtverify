#ifndef STDPARASET_H
#define STDPARASET_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QDateTime>

#include "ui_stdparaset.h"
#include "systemsetdlg_global.h"
#include "basedef.h"

class SYSTEMSETDLG_EXPORT StdParaSet : public QWidget
{
	Q_OBJECT

public:
	StdParaSet(QWidget *parent = 0, Qt::WFlags flags = 0);
	~StdParaSet();

signals:

public slots:

private:
	Ui::StdParaSetClass ui;
private slots:

};

#endif // STDPARASET_H
