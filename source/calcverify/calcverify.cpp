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
#include "qtexdb.h"

CalcDlg::CalcDlg(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	disconnect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
	initUi();
	connect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));

	m_calcParaDlg = NULL;
	m_meterNO = "";
	m_standard = 0;
	m_model = 0;
	m_grade = 0;
	m_manufact = 0;
	m_verifydept = 0;
	m_verifyperson = 0;
	m_maxT = 0.0;
	m_minT = 0.0;
	m_maxDeltaT = 0.0;
	m_minDeltaT = 0.0;
	m_refT = 0.0;
	m_refDeltaT = 0.0;
	m_recPtr = NULL;

	mapIdx[3] = 1;
	mapIdx[4] = 2;
	mapIdx[5] = 3;
	mapIdx[6] = 4;
	mapIdx[8] = 5;
	mapIdx[9] = 6;
	mapIdx[10] = 7;
	mapIdx[12] = 8;
	mapIdx[13] = 9;
	mapIdx[14] = 10;
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

	if (m_recPtr) //检定结果
	{
		delete []m_recPtr;
		m_recPtr = NULL;
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

void CalcDlg::on_btnStart_clicked()
{
}

void CalcDlg::on_btnSave_clicked()
{
	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //记录时间戳
	if (saveVerifyRecords())
	{
		QMessageBox::information(this, tr("Hint"), tr("save database successful !"));
	}
	else
	{
		QMessageBox::information(this, tr("Hint"), tr("save database failed !"));
	}
}

void CalcDlg::on_btnExit_clicked()
{
	this->close();
}

void CalcDlg::initUi()
{
	QColor color(232,232,232);
	for (int i=0; i<ui.tableWidget->rowCount(); i++)
	{
		for (int j=0; j<ui.tableWidget->columnCount(); j++)
		{
			ui.tableWidget->setItem(i, j, new QTableWidgetItem(QString("")));
		}
		ui.tableWidget->item(i, 0)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_RECOM_V)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_RECOM_V)->setBackgroundColor(color);
		ui.tableWidget->item(i, COLUMN_IN_TEMPER)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_IN_TEMPER)->setBackgroundColor(color);
		ui.tableWidget->item(i, COLUMN_OUT_TEMPER)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_OUT_TEMPER)->setBackgroundColor(color);
		ui.tableWidget->item(i, COLUMN_K_COE)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_K_COE)->setBackgroundColor(color);
		ui.tableWidget->item(i, COLUMN_THEORY_E)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_THEORY_E)->setBackgroundColor(color);
		ui.tableWidget->item(i, COLUMN_DISP_ERROR)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_DISP_ERROR)->setBackgroundColor(color);
		ui.tableWidget->item(i, COLUMN_STD_ERROR)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_STD_ERROR)->setBackgroundColor(color);
	}
	for (int m=0; m<ui.tableWidget->columnCount(); m++)
	{
		ui.tableWidget->item(0, m)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(1, m)->setFlags(Qt::NoItemFlags);
	}
	//初始化表格控件
// 	ui.tableWidget->horizontalHeader()->setVisible(false);
	ui.tableWidget->verticalHeader()->setVisible(false);

	ui.tableWidget->setSpan(0, 0, 2, 1);
	ui.tableWidget->item(0, 0)->setText(QString(tr("Delta T\n(K)")));
	ui.tableWidget->item(0, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(0, 0)->setTextColor(Qt::red);

	ui.tableWidget->setSpan(0, 1, 1, 4);
	ui.tableWidget->item(0, 1)->setText(QString(tr("analog input")));
	ui.tableWidget->item(0, 1)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(0, 1)->setTextColor(Qt::darkGreen);
	ui.tableWidget->setSpan(0, 5, 1, 4);
	ui.tableWidget->item(0, 5)->setText(QString(tr("standard value")));
	ui.tableWidget->item(0, 5)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(0, 5)->setTextColor(Qt::darkGreen);
	ui.tableWidget->setSpan(0, 9, 1, 5);
	ui.tableWidget->item(0, 9)->setText(QString(tr("disp value and error")));
	ui.tableWidget->item(0, 9)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(0, 9)->setTextColor(Qt::darkGreen);

	ui.tableWidget->item(1, 1)->setText(QString(tr("ResistIn(Ω)")));
	ui.tableWidget->item(1, 1)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, 2)->setText(QString(tr("ResistOut(Ω)")));
	ui.tableWidget->item(1, 2)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, 3)->setText(QString(tr("RecomValue(L)")));
	ui.tableWidget->item(1, 3)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, 4)->setText(QString(tr("Flow(L)")));
	ui.tableWidget->item(1, 4)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, 5)->setText(QString(tr("TemperIn(℃)")));
	ui.tableWidget->item(1, 5)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, 6)->setText(QString(tr("TemperOut(℃)")));
	ui.tableWidget->item(1, 6)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, 7)->setText(QString(tr("KCoe")));
	ui.tableWidget->item(1, 7)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, 8)->setText(QString(tr("StdEnergy(kwh)")));
	ui.tableWidget->item(1, 8)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, 9)->setText(QString(tr("E0(kwh)")));
	ui.tableWidget->item(1, 9)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, 10)->setText(QString(tr("E1(kwh)")));
	ui.tableWidget->item(1, 10)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, 11)->setText(QString(tr("DispEnergy(kwh)")));
	ui.tableWidget->item(1, 11)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, 12)->setText(QString(tr("DispError(%)")));
	ui.tableWidget->item(1, 12)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, 13)->setText(QString(tr("StdError(%)")));
	ui.tableWidget->item(1, 13)->setTextAlignment(Qt::AlignCenter);

	ui.tableWidget->setSpan(2, 0, 1, 14);
	ui.tableWidget->item(2, 0)->setText(QString(tr("TemperOut: θmin≤θd≤θmin+5")));
	ui.tableWidget->item(2, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(2, 0)->setTextColor(Qt::blue);
	ui.tableWidget->item(3, 0)->setText(QString(tr("Δθmin")));
	ui.tableWidget->item(3, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(3, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(4, 0)->setText(QString(tr("5")));
	ui.tableWidget->item(4, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(4, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(5, 0)->setText(QString(tr("20")));
	ui.tableWidget->item(5, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(5, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(6, 0)->setText(QString(tr("Δθref")));
	ui.tableWidget->item(6, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(6, 0)->setTextColor(Qt::red);

	ui.tableWidget->setSpan(7, 0, 1, 14);
	ui.tableWidget->item(7, 0)->setText(QString(tr("TemperOut: θd = θref±5")));
	ui.tableWidget->item(7, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(7, 0)->setTextColor(Qt::blue);
	ui.tableWidget->item(8, 0)->setText(QString(tr("Δθmin")));
	ui.tableWidget->item(8, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(8, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(9, 0)->setText(QString(tr("5")));
	ui.tableWidget->item(9, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(9, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(10, 0)->setText(QString(tr("20")));
	ui.tableWidget->item(10, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(10, 0)->setTextColor(Qt::red);

	ui.tableWidget->setSpan(11, 0, 1, 14);
	ui.tableWidget->item(11, 0)->setText(QString(tr("TemperIn:  θmax-5≤θe ≤ θmax")));
	ui.tableWidget->item(11, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(11, 0)->setTextColor(Qt::blue);
	ui.tableWidget->item(12, 0)->setText(QString(tr("20")));
	ui.tableWidget->item(12, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(12, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(13, 0)->setText(QString(tr("Δθref")));
	ui.tableWidget->item(13, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(13, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(14, 0)->setText(QString(tr("Δθmax-5")));
	ui.tableWidget->item(14, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(14, 0)->setTextColor(Qt::red);

// 	ui.tableWidget->resizeColumnsToContents();
}

void CalcDlg::freshCalcPara()
{
	m_meterNO = m_calcParaDlg->getMeterNO();
	m_standard = m_calcParaDlg->getStandard();
	m_model = m_calcParaDlg->getModel();
	m_grade = m_calcParaDlg->getGrade();
	m_manufact = m_calcParaDlg->getManuFact();
	m_verifydept = m_calcParaDlg->getVerifyDept();
	m_verifyperson = m_calcParaDlg->getVerifyPerson();

	m_maxT = m_calcParaDlg->getMaxT();
	m_minT = m_calcParaDlg->getMinT();
	m_maxDeltaT = m_calcParaDlg->getMaxDeltaT();
	m_minDeltaT = m_calcParaDlg->getMinDeltaT();
	m_refT = (m_minT + m_maxT)/2;
	m_refDeltaT = (20 + m_maxDeltaT)/2;

	ui.lnEditMinDeltaT->setText(QString("%1").arg(m_minDeltaT));

	ui.tableWidget->item(2, 0)->setText(QString(tr("TemperOut: %1 - %2 ℃")).arg(m_minT).arg(m_minT+5));
	ui.tableWidget->item(2, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(2, 0)->setTextColor(Qt::blue);
	ui.tableWidget->item(3, 0)->setText(QString(tr("%1")).arg(m_minDeltaT));
	ui.tableWidget->item(3, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(3, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(6, 0)->setText(QString(tr("%1")).arg(m_refDeltaT));
	ui.tableWidget->item(6, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(6, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(7, 0)->setText(QString(tr("TemperOut: %1 - %2 ℃")).arg(m_refT-5).arg(m_refT+5));
	ui.tableWidget->item(7, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(7, 0)->setTextColor(Qt::blue);
	ui.tableWidget->item(8, 0)->setText(QString(tr("%1")).arg(m_minDeltaT));
	ui.tableWidget->item(8, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(8, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(11, 0)->setText(QString(tr("TemperIn: %1 - %2 ℃")).arg(m_maxT-5).arg(m_maxT));
	ui.tableWidget->item(11, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(11, 0)->setTextColor(Qt::blue);
	ui.tableWidget->item(13, 0)->setText(QString(tr("%1")).arg(m_refDeltaT));
	ui.tableWidget->item(13, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(13, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(14, 0)->setText(QString(tr("%1")).arg(m_maxDeltaT-5));
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
		ui.tableWidget->item(row, COLUMN_IN_TEMPER)->setText(QString("%1").arg(inTemper));
		ui.tableWidget->setCurrentCell(row, COLUMN_OUT_RESIST);
		break;
	case COLUMN_OUT_RESIST: //出口电阻
		outR = ui.tableWidget->item(row, column)->text().toFloat(&ok);
		if (!ok)
		{
			return;
		}
		outTemper = calcTemperByResist(outR); //计算出口温度
		ui.tableWidget->item(row, COLUMN_OUT_TEMPER)->setText(QString("%1").arg(outTemper));
		KCoe = getKCoeByTemper(inTemper, outTemper); //获取K系数
		ui.tableWidget->item(row, COLUMN_K_COE)->setText(QString("%1").arg(KCoe));
		recomV = calcRecomVolume(); //计算建议体积
		ui.tableWidget->item(row, COLUMN_RECOM_V)->setText(QString("%1").arg(recomV));
		stdError = (0.5 + m_minDeltaT/(outTemper-inTemper)); //标准误差
		ui.tableWidget->item(row, COLUMN_STD_ERROR)->setText(QString("%1").arg(stdError));
		ui.tableWidget->setCurrentCell(row, COLUMN_ANALOG_V); 
		break;
	case COLUMN_ANALOG_V: //模拟流量
		theoryEnergy = calcTheoryEnergy(); //计算理论热量
		ui.tableWidget->item(row, COLUMN_THEORY_E)->setText(QString("%1").arg(theoryEnergy));
		ui.tableWidget->setCurrentCell(row, COLUMN_E0); 
		break;
	case COLUMN_E0: //E0
		ui.tableWidget->setCurrentCell(row, COLUMN_E1); 
		break;
	case COLUMN_E1: //E1
		theoryEnergy = calcTheoryEnergy(); //计算理论热量
		E0 = ui.tableWidget->item(row, COLUMN_E0)->text().toFloat(&ok);
		E1 = ui.tableWidget->item(row, COLUMN_E1)->text().toFloat(&ok);
		dispEnergy = E1 - E0; //热量示值
		ui.tableWidget->item(row, COLUMN_DISP_E)->setText(QString("%1").arg(dispEnergy));
		dispError = 100*(dispEnergy - theoryEnergy)/theoryEnergy; //计算示值误差
		ui.tableWidget->item(row, COLUMN_DISP_ERROR)->setText(QString("%1").arg(dispError));
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

int CalcDlg::saveVerifyRecords()
{
	int ret = 0;
	bool ok;
	float dispErr;
	int rowNum = ui.tableWidget->rowCount();
	int columnNum = ui.tableWidget->columnCount();
	for (int i=3; i<rowNum; i++)
	{
		if (ui.tableWidget->item(i, COLUMN_DISP_ERROR)->text().isEmpty())
		{
			continue;
		}
		dispErr = ui.tableWidget->item(i, COLUMN_DISP_ERROR)->text().toFloat(&ok);
		if (ok)
		{
			m_recPtr = new Calc_Verify_Record_STR;
			memset(m_recPtr, 0, sizeof(Calc_Verify_Record_STR));
			strncpy_s(m_recPtr->timestamp, m_timeStamp.toAscii(), TIMESTAMP_LEN);
			strcpy_s(m_recPtr->meterNo, m_meterNO.toAscii());
			m_recPtr->deltaTidx = mapIdx[i];
			m_recPtr->standard = m_standard;
			m_recPtr->model = m_model;
			m_recPtr->grade = m_grade;
			m_recPtr->manufactDept = m_manufact;
			m_recPtr->verifyDept = m_verifydept;
			m_recPtr->verifyPerson = m_verifyperson;
			m_recPtr->maxT = m_maxT;
			m_recPtr->minT = m_minT;
			m_recPtr->maxDeltaT = m_maxDeltaT;
			m_recPtr->minDeltaT = m_minDeltaT;
			m_recPtr->installPos = ui.radioButtonPosOut->isChecked();
			m_recPtr->energyUnit = ui.radioButtonKwh->isChecked();
			m_recPtr->algorithm = ui.radioButtonKCoe->isChecked();
			m_recPtr->inTemper = ui.tableWidget->item(i, COLUMN_IN_TEMPER)->text().toFloat();
			m_recPtr->outTemper = ui.tableWidget->item(i, COLUMN_OUT_TEMPER)->text().toFloat();
			m_recPtr->inR= ui.tableWidget->item(i, COLUMN_IN_RESIST)->text().toFloat();
			m_recPtr->outR = ui.tableWidget->item(i, COLUMN_OUT_RESIST)->text().toFloat();
			m_recPtr->recomVolume = ui.tableWidget->item(i, COLUMN_RECOM_V)->text().toFloat();
			m_recPtr->analogVolume = ui.tableWidget->item(i, COLUMN_ANALOG_V)->text().toFloat();
			m_recPtr->kCoe = ui.tableWidget->item(i, COLUMN_K_COE)->text().toFloat();
			m_recPtr->stdEnergy = ui.tableWidget->item(i, COLUMN_STD_VALUE)->text().toFloat();
			m_recPtr->meterE0 = ui.tableWidget->item(i, COLUMN_E0)->text().toFloat();
			m_recPtr->meterE1 = ui.tableWidget->item(i, COLUMN_E1)->text().toFloat();
			m_recPtr->dispError = ui.tableWidget->item(i, COLUMN_DISP_ERROR)->text().toFloat();
			m_recPtr->stdError = ui.tableWidget->item(i, COLUMN_STD_ERROR)->text().toFloat();
			m_recPtr->result = (m_recPtr->dispError < m_recPtr->stdError) ? 1 : 0;
			
			ret += insertCalcVerifyRec(m_recPtr, 1);
		}
	}

	return ret;
}