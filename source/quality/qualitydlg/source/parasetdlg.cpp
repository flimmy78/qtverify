#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QThread>
#include "parasetdlg.h"

ParaSetDlg::ParaSetDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"ParaSetDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);
}

ParaSetDlg::~ParaSetDlg()
{

}
