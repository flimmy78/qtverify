#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QThread>
#include "qualitydlg.h"

QualityDlg::QualityDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"QualityDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	m_paraset = new ParaSetDlg();

}

QualityDlg::~QualityDlg()
{
	if (m_paraset)
	{
		delete m_paraset;
		m_paraset = NULL;
	}
}

void QualityDlg::on_btnWaterIn_clicked()
{
	setValveBtnBackColor(ui.btnWaterIn, true);
}

void QualityDlg::setValveBtnBackColor(QPushButton *btn, bool isOpen)
{
	if (isOpen)
	{
		btn->setStyleSheet("background:green;border:0px;");  
	}
	else
	{
		btn->setStyleSheet("background:red;border:0px;");  
	}
}

void QualityDlg::on_btnParaSet_clicked()
{
	m_paraset->show();
}

void QualityDlg::on_btnExit_clicked()
{
	this->close();
}

void QualityDlg::readWaterTemperature()
{
	qDebug()<<"readWaterTemperature:";
}

