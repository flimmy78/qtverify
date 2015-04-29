/***********************************************
**  文件名:     calcverify.cpp
**  功能:       计算器检定主界面
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/4/27
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2015/04 第一版
**  内容包含:
**  说明:		
**  更新记录:   
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QTest>
#include <QtSql/QSqlTableModel>
#include <QtGui/QFileDialog>
#include <QtCore/QSignalMapper>
#include <math.h>

#include "calcverify.h"
#include "calcpara.h"

CalcDlg::CalcDlg(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	initUi();

	m_calcParaDlg = NULL;
	m_maxT = 0.0;
	m_minT = 0.0;
	m_maxDeltaT = 0.0;
	m_minDeltaT = 0.0;
	m_refT = 0.0;
	m_refDeltaT = 0.0;
}

CalcDlg::~CalcDlg()
{
}

void CalcDlg::closeEvent( QCloseEvent * event)
{
	if (m_calcParaDlg) //计算器参数设置对话框
	{
		delete m_calcParaDlg;
		m_calcParaDlg = NULL;
	}

}

void CalcDlg::on_btnPara_clicked()
{
	if (NULL == m_calcParaDlg)
	{
		m_calcParaDlg = new CalcParaDlg();
	}
	else
	{
		delete m_calcParaDlg;
		m_calcParaDlg = new CalcParaDlg();
	}
	connect(m_calcParaDlg, SIGNAL(saveSuccessSignal()), this, SLOT(freshCalcPara()));
	m_calcParaDlg->show();
}

void CalcDlg::on_btnSave_clicked()
{

}

void CalcDlg::on_btnExit_clicked()
{
	this->close();
}

void CalcDlg::initUi()
{
	//初始化表格控件
// 	ui.tableWidget->horizontalHeader()->setVisible(false);
	ui.tableWidget->verticalHeader()->setVisible(false);

	ui.tableWidget->setSpan(0, 0, 2, 1);
	ui.tableWidget->setItem(0, 0, new QTableWidgetItem(QString(tr("Delta T\n(K)"))));
	ui.tableWidget->item(0, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(0, 0)->setTextColor(Qt::red);

	ui.tableWidget->setSpan(0, 1, 1, 4);
	ui.tableWidget->setItem(0, 1, new QTableWidgetItem(QString(tr("analog input"))));
	ui.tableWidget->item(0, 1)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(0, 1)->setTextColor(Qt::darkGreen);
	ui.tableWidget->setSpan(0, 5, 1, 4);
	ui.tableWidget->setItem(0, 5, new QTableWidgetItem(QString(tr("standard value"))));
	ui.tableWidget->item(0, 5)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(0, 5)->setTextColor(Qt::darkGreen);
	ui.tableWidget->setSpan(0, 9, 1, 5);
	ui.tableWidget->setItem(0, 9, new QTableWidgetItem(QString(tr("disp value and error"))));
	ui.tableWidget->item(0, 9)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(0, 9)->setTextColor(Qt::darkGreen);

	ui.tableWidget->setItem(1, 1, new QTableWidgetItem(QString(tr("ResistIn(Ω)"))));
	ui.tableWidget->item(1, 1)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->setItem(1, 2, new QTableWidgetItem(QString(tr("ResistOut(Ω)"))));
	ui.tableWidget->item(1, 2)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->setItem(1, 3, new QTableWidgetItem(QString(tr("RecomValue(L)"))));
	ui.tableWidget->item(1, 3)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->setItem(1, 4, new QTableWidgetItem(QString(tr("Flow(L)"))));
	ui.tableWidget->item(1, 4)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->setItem(1, 5, new QTableWidgetItem(QString(tr("TemperIn(℃)"))));
	ui.tableWidget->item(1, 5)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->setItem(1, 6, new QTableWidgetItem(QString(tr("TemperOut(℃)"))));
	ui.tableWidget->item(1, 6)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->setItem(1, 7, new QTableWidgetItem(QString(tr("KCoe"))));
	ui.tableWidget->item(1, 7)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->setItem(1, 8, new QTableWidgetItem(QString(tr("StdEnergy(kwh)"))));
	ui.tableWidget->item(1, 8)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->setItem(1, 9, new QTableWidgetItem(QString(tr("E0(kwh)"))));
	ui.tableWidget->item(1, 9)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->setItem(1, 10, new QTableWidgetItem(QString(tr("E1(kwh)"))));
	ui.tableWidget->item(1, 10)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->setItem(1, 11, new QTableWidgetItem(QString(tr("DispEnergy(kwh)"))));
	ui.tableWidget->item(1, 11)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->setItem(1, 12, new QTableWidgetItem(QString(tr("DispError(%)"))));
	ui.tableWidget->item(1, 12)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->setItem(1, 13, new QTableWidgetItem(QString(tr("StdError(%)"))));
	ui.tableWidget->item(1, 13)->setTextAlignment(Qt::AlignCenter);

	ui.tableWidget->setSpan(2, 0, 1, 14);
	ui.tableWidget->setItem(2, 0, new QTableWidgetItem(QString(tr("TemperOut: θmin≤θd≤θmin+5"))));
	ui.tableWidget->item(2, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(2, 0)->setTextColor(Qt::blue);
	ui.tableWidget->setItem(3, 0, new QTableWidgetItem(QString(tr("Δθmin"))));
	ui.tableWidget->item(3, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(3, 0)->setTextColor(Qt::red);
	ui.tableWidget->setItem(4, 0, new QTableWidgetItem(QString(tr("5"))));
	ui.tableWidget->item(4, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(4, 0)->setTextColor(Qt::red);
	ui.tableWidget->setItem(5, 0, new QTableWidgetItem(QString(tr("20"))));
	ui.tableWidget->item(5, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(5, 0)->setTextColor(Qt::red);
	ui.tableWidget->setItem(6, 0, new QTableWidgetItem(QString(tr("Δθref"))));
	ui.tableWidget->item(6, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(6, 0)->setTextColor(Qt::red);

	ui.tableWidget->setSpan(7, 0, 1, 14);
	ui.tableWidget->setItem(7, 0, new QTableWidgetItem(QString(tr("TemperOut: θd = θref±5"))));
	ui.tableWidget->item(7, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(7, 0)->setTextColor(Qt::blue);
	ui.tableWidget->setItem(8, 0, new QTableWidgetItem(QString(tr("Δθmin"))));
	ui.tableWidget->item(8, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(8, 0)->setTextColor(Qt::red);
	ui.tableWidget->setItem(9, 0, new QTableWidgetItem(QString(tr("5"))));
	ui.tableWidget->item(9, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(9, 0)->setTextColor(Qt::red);
	ui.tableWidget->setItem(10, 0, new QTableWidgetItem(QString(tr("20"))));
	ui.tableWidget->item(10, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(10, 0)->setTextColor(Qt::red);

	ui.tableWidget->setSpan(11, 0, 1, 14);
	ui.tableWidget->setItem(11, 0, new QTableWidgetItem(QString(tr("TemperIn:  θmax-5≤θe ≤ θmax"))));
	ui.tableWidget->item(11, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(11, 0)->setTextColor(Qt::blue);
	ui.tableWidget->setItem(12, 0, new QTableWidgetItem(QString(tr("20"))));
	ui.tableWidget->item(12, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(12, 0)->setTextColor(Qt::red);
	ui.tableWidget->setItem(13, 0, new QTableWidgetItem(QString(tr("Δθref"))));
	ui.tableWidget->item(13, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(13, 0)->setTextColor(Qt::red);
	ui.tableWidget->setItem(14, 0, new QTableWidgetItem(QString(tr("Δθmax-5"))));
	ui.tableWidget->item(14, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(14, 0)->setTextColor(Qt::red);

// 	ui.tableWidget->resizeColumnsToContents();
}

void CalcDlg::freshCalcPara()
{
	m_maxT = m_calcParaDlg->getMaxT();
	m_minT = m_calcParaDlg->getMinT();
	m_maxDeltaT = m_calcParaDlg->getMaxDeltaT();
	m_minDeltaT = m_calcParaDlg->getMinDeltaT();
	m_refT = (m_minT + m_maxT)/2;
	m_refDeltaT = (20 + m_maxDeltaT)/2;

	ui.lnEditMinDeltaT->setText(QString("%1").arg(m_minDeltaT));

	ui.tableWidget->setItem(2, 0, new QTableWidgetItem(QString(tr("TemperOut: %1 - %2 ℃")).arg(m_minT).arg(m_minT+5)));
	ui.tableWidget->item(2, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(2, 0)->setTextColor(Qt::blue);
	ui.tableWidget->setItem(3, 0, new QTableWidgetItem(QString(tr("%1")).arg(m_minDeltaT)));
	ui.tableWidget->item(3, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(3, 0)->setTextColor(Qt::red);
	ui.tableWidget->setItem(6, 0, new QTableWidgetItem(QString(tr("%1")).arg(m_refDeltaT)));
	ui.tableWidget->item(6, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(6, 0)->setTextColor(Qt::red);
	ui.tableWidget->setItem(7, 0, new QTableWidgetItem(QString(tr("TemperOut: %1 - %2 ℃")).arg(m_refT-5).arg(m_refT+5)));
	ui.tableWidget->item(7, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(7, 0)->setTextColor(Qt::blue);
	ui.tableWidget->setItem(8, 0, new QTableWidgetItem(QString(tr("%1")).arg(m_minDeltaT)));
	ui.tableWidget->item(8, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(8, 0)->setTextColor(Qt::red);
	ui.tableWidget->setItem(11, 0, new QTableWidgetItem(QString(tr("TemperIn: %1 - %2 ℃")).arg(m_maxT-5).arg(m_maxT)));
	ui.tableWidget->item(11, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(11, 0)->setTextColor(Qt::blue);
	ui.tableWidget->setItem(13, 0, new QTableWidgetItem(QString(tr("%1")).arg(m_refDeltaT)));
	ui.tableWidget->item(13, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(13, 0)->setTextColor(Qt::red);
	ui.tableWidget->setItem(14, 0, new QTableWidgetItem(QString(tr("%1")).arg(m_maxDeltaT-5)));
	ui.tableWidget->item(14, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(14, 0)->setTextColor(Qt::red);

}

void CalcDlg::on_tableWidget_cellChanged(int row, int column)
{
	if (NULL == ui.tableWidget->item(row,  column))
	{
		return;
	}
	qDebug()<<"row ="<<row<<", column ="<<column;
	bool ok;
	float inR = 0.0;
	float outR = 0.0;
	float Volume = 0.0;
	float inTemper = 0.0;
	float outTemper = 0.0;
	float KCoe = 0.0;
	float recomV = 0.0;
	float theoryEnergy = 0.0;
	float E0 = 0.0;
	float E1 = 0.0;
	float dispEnergy = 0.0;
	float dispError = 0.0;
	float stdError = 0.0;

	switch (column)
	{
	case COLUMN_IN_RESIST: //进口电阻
		inR = ui.tableWidget->item(row, column)->text().toFloat(&ok);
		if (!ok)
		{
			return;
		}
		inTemper = calcTemperByResist(inR); //计算进口温度
		ui.tableWidget->setItem(row, COLUMN_IN_TEMPER, new QTableWidgetItem(QString("%1").arg(inTemper)));
		ui.tableWidget->setCurrentCell(row, COLUMN_OUT_RESIST);
		break;
	case COLUMN_OUT_RESIST: //出口电阻
		outR = ui.tableWidget->item(row, column)->text().toFloat(&ok);
		if (!ok)
		{
			return;
		}
		outTemper = calcTemperByResist(outR); //计算出口温度
		ui.tableWidget->setItem(row, COLUMN_OUT_TEMPER, new QTableWidgetItem(QString("%1").arg(outTemper)));
		KCoe = getKCoeByTemper(inTemper, outTemper); //获取K系数
		ui.tableWidget->setItem(row, COLUMN_K_COE, new QTableWidgetItem(QString("%1").arg(KCoe)));
		recomV = calcRecomVolume(); //计算建议体积
		ui.tableWidget->setItem(row, COLUMN_RECOM_V, new QTableWidgetItem(QString("%1").arg(recomV)));
		stdError = (0.5 + m_minDeltaT/(outTemper-inTemper)); //标准误差
		ui.tableWidget->setItem(row, COLUMN_STD_ERROR, new QTableWidgetItem(QString("%1").arg(stdError)));
		ui.tableWidget->setCurrentCell(row, COLUMN_ANALOG_V); 
		break;
	case COLUMN_ANALOG_V: //模拟流量
		theoryEnergy = calcTheoryEnergy(); //计算理论热量
		ui.tableWidget->setItem(row, COLUMN_THEORY_E, new QTableWidgetItem(QString("%1").arg(theoryEnergy)));
		ui.tableWidget->setCurrentCell(row, COLUMN_E0); 
		break;
	case COLUMN_E0: //E0
		ui.tableWidget->setCurrentCell(row, COLUMN_E1); 
		break;
	case COLUMN_E1: //E1
		E0 = ui.tableWidget->item(row, COLUMN_E0)->text().toFloat(&ok);
		E1 = ui.tableWidget->item(row, COLUMN_E1)->text().toFloat(&ok);
		dispEnergy = E1 - E0; //热量示值
		ui.tableWidget->setItem(row, COLUMN_DISP_E, new QTableWidgetItem(QString("%1").arg(dispEnergy)));
		theoryEnergy = calcTheoryEnergy(); //计算理论热量
		dispError = 100*(dispEnergy - theoryEnergy)/theoryEnergy; //计算示值误差
		ui.tableWidget->setItem(row, COLUMN_DISP_ERROR, new QTableWidgetItem(QString("%1").arg(dispError)));
		break;
	default:
		qDebug()<<"no need input";
		break;
	}
}

float CalcDlg::calcTemperByResist(float resist)
{
	return resist*2;
}

float CalcDlg::getKCoeByTemper(float inT, float outT)
{
	return 1.22;
}

float CalcDlg::calcRecomVolume()
{
	return 100.123;
}

float CalcDlg::calcTheoryEnergy()
{
	return 5.678;
}