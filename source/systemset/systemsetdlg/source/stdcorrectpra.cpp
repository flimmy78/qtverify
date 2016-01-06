#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QtGui/QFileDialog>
#include <QCloseEvent>

#include "algorithm.h"
#include "stdcorrectpra.h"

StdMtrCorrectPra::StdMtrCorrectPra(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"StdMtrCorrectPra thread:"<<QThread::currentThreadId();

	ui = NULL;
	ui = new Ui::StdCorrectPraClass;
	ui->setupUi(this);

	m_stdCorrectConfig = NULL;
	m_stdCorrectConfig = new QSettings(getFullIniFileName("stdCorrectpra.ini"), QSettings::IniFormat);
	m_rx.setPattern("\\d+(\\.\\d+)?");
	initTables();
	installParas();
}

StdMtrCorrectPra::~StdMtrCorrectPra()
{
	releaseSource();
}

void StdMtrCorrectPra::showEvent(QShowEvent * event)
{
	qDebug()<<"StdMtrCorrectPra::showEvent";
}

void StdMtrCorrectPra::initTables()
{
	QStringList header;
	header<<tr("Flow Point\n(m3/h)")<<tr("Check Quantity\n(kg)");
	INIT_TABLE(tableWidget_0)
	INIT_TABLE(tableWidget_1)
	INIT_TABLE(tableWidget_2)
	INIT_TABLE(tableWidget_3)
}

void StdMtrCorrectPra::closeEvent(QCloseEvent * event)
{
	releaseSource();
	emit signalClosed();
}

void StdMtrCorrectPra::releaseSource()
{
	RELEASE_PTR(ui)
	RELEASE_PTR(m_stdCorrectConfig)
}

void StdMtrCorrectPra::resizeEvent(QResizeEvent * event)
{
	qDebug()<<"StdMtrCoeCorrect::resizeEvent...";
	int th = ui->tableWidget_0->size().height();
	int tw = ui->tableWidget_0->size().width();
	int hh = ui->tableWidget_0->horizontalHeader()->size().height();
	int vw = ui->tableWidget_0->verticalHeader()->size().width();
	int vSize = (int)((th-hh-2)/ui->tableWidget_0->rowCount());
	int hSize = (int)((tw-vw-2)/ui->tableWidget_0->columnCount());

	ui->tableWidget_0->verticalHeader()->setDefaultSectionSize(vSize);
	ui->tableWidget_0->horizontalHeader()->setDefaultSectionSize(hSize);
	ui->tableWidget_1->verticalHeader()->setDefaultSectionSize(vSize);
	ui->tableWidget_1->horizontalHeader()->setDefaultSectionSize(hSize);
	ui->tableWidget_2->verticalHeader()->setDefaultSectionSize(vSize);
	ui->tableWidget_2->horizontalHeader()->setDefaultSectionSize(hSize);
	ui->tableWidget_3->verticalHeader()->setDefaultSectionSize(vSize);
	ui->tableWidget_3->horizontalHeader()->setDefaultSectionSize(hSize);
}

void StdMtrCorrectPra::on_btnSave_clicked()
{
	writeParas();
}

void StdMtrCorrectPra::on_btnExit_clicked()
{
	this->close();
}

void StdMtrCorrectPra::on_tableWidget_0_cellChanged(int row, int column)
{
	 if (!m_rx.exactMatch(ui->tableWidget_0->item(row, column)->text()))
		 ui->tableWidget_0->item(row, column)->setText("");
}

void StdMtrCorrectPra::on_tableWidget_1_cellChanged(int row, int column)
{
	if (!m_rx.exactMatch(ui->tableWidget_1->item(row, column)->text()))
		ui->tableWidget_0->item(row, column)->setText("");
}

void StdMtrCorrectPra::on_tableWidget_2_cellChanged(int row, int column)
{
	if (!m_rx.exactMatch(ui->tableWidget_2->item(row, column)->text()))
		ui->tableWidget_0->item(row, column)->setText("");
}

void StdMtrCorrectPra::on_tableWidget_3_cellChanged(int row, int column)
{
	if (!m_rx.exactMatch(ui->tableWidget_3->item(row, column)->text()))
		ui->tableWidget_0->item(row, column)->setText("");
}

void StdMtrCorrectPra::installParas()
{
	m_stdCorrectConfig->beginReadArray("bigflow");
	for (int i=0;i<ui->tableWidget_0->rowCount();i++)
	{
		m_stdCorrectConfig->setArrayIndex(i);
		ui->tableWidget_0->item(i, COL_FP)->setText(m_stdCorrectConfig->value("flowPoint").toString());
		ui->tableWidget_0->item(i, COL_QUAN)->setText(m_stdCorrectConfig->value("quantity").toString());
	}
	m_stdCorrectConfig->endArray();

	m_stdCorrectConfig->beginReadArray("mid2flow");
	for (int i=0;i<ui->tableWidget_1->rowCount();i++)
	{
		m_stdCorrectConfig->setArrayIndex(i);
		ui->tableWidget_1->item(i, COL_FP)->setText(m_stdCorrectConfig->value("flowPoint").toString());
		ui->tableWidget_1->item(i, COL_QUAN)->setText(m_stdCorrectConfig->value("quantity").toString());
	}
	m_stdCorrectConfig->endArray();

	m_stdCorrectConfig->beginReadArray("mid1flow");
	for (int i=0;i<ui->tableWidget_2->rowCount();i++)
	{
		m_stdCorrectConfig->setArrayIndex(i);
		ui->tableWidget_2->item(i, COL_FP)->setText(m_stdCorrectConfig->value("flowPoint").toString());
		ui->tableWidget_2->item(i, COL_QUAN)->setText(m_stdCorrectConfig->value("quantity").toString());
	}
	m_stdCorrectConfig->endArray();

	m_stdCorrectConfig->beginReadArray("smallflow");
	for (int i=0;i<ui->tableWidget_3->rowCount();i++)
	{
		m_stdCorrectConfig->setArrayIndex(i);
		ui->tableWidget_3->item(i, COL_FP)->setText(m_stdCorrectConfig->value("flowPoint").toString());
		ui->tableWidget_3->item(i, COL_QUAN)->setText(m_stdCorrectConfig->value("quantity").toString());
	}
	m_stdCorrectConfig->endArray();

	m_stdCorrectConfig->beginGroup("times");
	ui->comboBox->setCurrentIndex(m_stdCorrectConfig->value("time").toInt());
	m_stdCorrectConfig->endGroup();
}

void StdMtrCorrectPra::writeParas()
{
	m_stdCorrectConfig->beginWriteArray("bigflow");
	for (int i=0;i<ui->tableWidget_0->rowCount();i++)
	{
		m_stdCorrectConfig->setArrayIndex(i);
		m_stdCorrectConfig->setValue("flowPoint", ui->tableWidget_0->item(i, COL_FP)->text());
		m_stdCorrectConfig->setValue("quantity", ui->tableWidget_0->item(i, COL_QUAN)->text());
	}
	m_stdCorrectConfig->endArray();

	m_stdCorrectConfig->beginWriteArray("mid2flow");
	for (int i=0;i<ui->tableWidget_0->rowCount();i++)
	{
		m_stdCorrectConfig->setArrayIndex(i);
		m_stdCorrectConfig->setValue("flowPoint", ui->tableWidget_1->item(i, COL_FP)->text());
		m_stdCorrectConfig->setValue("quantity", ui->tableWidget_1->item(i, COL_QUAN)->text());
	}
	m_stdCorrectConfig->endArray();

	m_stdCorrectConfig->beginWriteArray("mid1flow");
	for (int i=0;i<ui->tableWidget_0->rowCount();i++)
	{
		m_stdCorrectConfig->setArrayIndex(i);
		m_stdCorrectConfig->setValue("flowPoint", ui->tableWidget_2->item(i, COL_FP)->text());
		m_stdCorrectConfig->setValue("quantity", ui->tableWidget_2->item(i, COL_QUAN)->text());
	}
	m_stdCorrectConfig->endArray();

	m_stdCorrectConfig->beginWriteArray("smallflow");
	for (int i=0;i<ui->tableWidget_0->rowCount();i++)
	{
		m_stdCorrectConfig->setArrayIndex(i);
		m_stdCorrectConfig->setValue("flowPoint", ui->tableWidget_3->item(i, COL_FP)->text());
		m_stdCorrectConfig->setValue("quantity", ui->tableWidget_3->item(i, COL_QUAN)->text());
	}
	m_stdCorrectConfig->endArray();

	m_stdCorrectConfig->beginGroup("times");
	m_stdCorrectConfig->setValue("time", ui->comboBox->currentIndex());
	m_stdCorrectConfig->endGroup();
}