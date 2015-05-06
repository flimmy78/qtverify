/***********************************************
**  �ļ���:     calcverify.cpp
**  ����:       �������춨������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2015/4/27
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2015/04 ��һ��
**  ���ݰ���:
**  ˵��:		
**  ���¼�¼:   
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QTest>
#include <QtSql/QSqlTableModel>
#include <QtGui/QFileDialog>
#include <QtCore/QSignalMapper>
#include <QtCore/QSettings>
#include <math.h>

#include "calcverify.h"
#include "calcpara.h"
#include "qtexdb.h"
#include "algorithm.h"

CalcDlg::CalcDlg(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	algoStr[0] = QObject::tr("EnthalpyDiff");
	algoStr[1] = QObject::tr("KCoe");
	unitStr[0] = QObject::tr("MJ");
	unitStr[1] = QObject::tr("kWh");
	KStr[0][0] = algoStr[0] + "\n(kJ/kg)";
	KStr[0][1] = algoStr[0] + "\n(kJ/kg)";
	KStr[1][0] = algoStr[1] + "\n(" + unitStr[0] + "/m3��)";
	KStr[1][1] = algoStr[1] + "\n(" + unitStr[1] + "/m3��)";

	this->setWindowFlags(Qt::Widget);
	ui.setupUi(this);
	disconnect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
	initUi();
	connect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));

	m_calcParaDlg = NULL;
	m_algo = new CAlgorithm();
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
	if (m_calcParaDlg) //�������������öԻ���
	{
		delete m_calcParaDlg;
		m_calcParaDlg = NULL;
	}

	if (m_recPtr) //�춨���
	{
		delete []m_recPtr;
		m_recPtr = NULL;
	}

	if (m_algo) //�㷨�ӿ�
	{
		delete m_algo;
		m_algo = NULL;
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
	ui.tableWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
// 	ui.tableWidget->setEnabled(true);
	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //��¼ʱ���

	ui.btnSave->setEnabled(true);
	ui.hintLabel->setText(tr("verifying: please input verify data!"));
}

void CalcDlg::on_btnSave_clicked()
{
// 	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //��¼ʱ���
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
	//QButtonGroup 
	btnGroupInstallPos = new QButtonGroup(ui.groupBoxInstallPos); //��װλ��
	btnGroupInstallPos->addButton(ui.radioButtonPosIn, 0);
	btnGroupInstallPos->addButton(ui.radioButtonPosOut, 1);
	connect(btnGroupInstallPos, SIGNAL(buttonClicked(int)), this, SLOT(slot_btnGroupInstallPos_clicked(int)));

	btnGroupEnergyUnit = new QButtonGroup(ui.groupBoxEnergyUnit); //������λ
	btnGroupEnergyUnit->addButton(ui.radioButtonMJ, 0);
	btnGroupEnergyUnit->addButton(ui.radioButtonKwh, 1);
	connect(btnGroupEnergyUnit, SIGNAL(buttonClicked(int)), this, SLOT(slot_btnGroupEnergyUnit_clicked(int)));

	btnGroupAlgorithm = new QButtonGroup(ui.groupBoxAlgorithm); //�㷨
	btnGroupAlgorithm->addButton(ui.radioButtonEnthalpy, 0);
	btnGroupAlgorithm->addButton(ui.radioButtonKCoe, 1);
	connect(btnGroupAlgorithm, SIGNAL(buttonClicked(int)), this, SLOT(slot_btnGroupAlgorithm_clicked(int)));

	int algo = btnGroupAlgorithm->checkedId();
	int unit = btnGroupEnergyUnit->checkedId();

	//���ñ��Ϊֻ��
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
		ui.tableWidget->item(i, COLUMN_THEORY_ENERGY)->setFlags(Qt::NoItemFlags);
		ui.tableWidget->item(i, COLUMN_THEORY_ENERGY)->setBackgroundColor(color);
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

	//��ʼ�����ؼ�
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

	ui.tableWidget->item(1, COLUMN_IN_RESIST)->setText(QString(tr("ResistIn(��)")));
	ui.tableWidget->item(1, COLUMN_IN_RESIST)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, COLUMN_OUT_RESIST)->setText(QString(tr("ResistOut(��)")));
	ui.tableWidget->item(1, COLUMN_OUT_RESIST)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, COLUMN_RECOM_V)->setText(QString(tr("RecomValue(L)")));
	ui.tableWidget->item(1, COLUMN_RECOM_V)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, COLUMN_ANALOG_V)->setText(QString(tr("Flow(L)")));
	ui.tableWidget->item(1, COLUMN_ANALOG_V)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, COLUMN_IN_TEMPER)->setText(QString(tr("TemperIn(��)")));
	ui.tableWidget->item(1, COLUMN_IN_TEMPER)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, COLUMN_OUT_TEMPER)->setText(QString(tr("TemperOut(��)")));
	ui.tableWidget->item(1, COLUMN_OUT_TEMPER)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, COLUMN_K_COE)->setText(KStr[algo][unit]);//QString(tr("KCoe(kWh/m3��)")));
	ui.tableWidget->item(1, COLUMN_K_COE)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, COLUMN_THEORY_ENERGY)->setText(tr("StdEnergy(\n") + unitStr[unit] + ")");//QString(tr("StdEnergy(kWh)")));
	ui.tableWidget->item(1, COLUMN_THEORY_ENERGY)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, COLUMN_E0)->setText(tr("E0(\n") + unitStr[unit] + ")");
	ui.tableWidget->item(1, COLUMN_E0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, COLUMN_E1)->setText(tr("E1(\n") + unitStr[unit] + ")");
	ui.tableWidget->item(1, COLUMN_E1)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, COLUMN_DISP_ENERGY)->setText(tr("DispEnergy(\n") + unitStr[unit] + ")");
	ui.tableWidget->item(1, COLUMN_DISP_ENERGY)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, COLUMN_DISP_ERROR)->setText(QString(tr("DispError(%)")));
	ui.tableWidget->item(1, COLUMN_DISP_ERROR)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(1, COLUMN_STD_ERROR)->setText(QString(tr("StdError(%)")));
	ui.tableWidget->item(1, COLUMN_STD_ERROR)->setTextAlignment(Qt::AlignCenter);

	ui.tableWidget->setSpan(2, 0, 1, 14);
	ui.tableWidget->item(2, 0)->setText(QString(tr("TemperOut: ��min�ܦ�d�ܦ�min+5")));
	ui.tableWidget->item(2, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(2, 0)->setTextColor(Qt::blue);
	ui.tableWidget->item(3, 0)->setText(QString(tr("����min")));
	ui.tableWidget->item(3, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(3, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(4, 0)->setText(QString(tr("5")));
	ui.tableWidget->item(4, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(4, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(5, 0)->setText(QString(tr("20")));
	ui.tableWidget->item(5, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(5, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(6, 0)->setText(QString(tr("����ref")));
	ui.tableWidget->item(6, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(6, 0)->setTextColor(Qt::red);

	ui.tableWidget->setSpan(7, 0, 1, 14);
	ui.tableWidget->item(7, 0)->setText(QString(tr("TemperOut: ��d = ��ref��5")));
	ui.tableWidget->item(7, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(7, 0)->setTextColor(Qt::blue);
	ui.tableWidget->item(8, 0)->setText(QString(tr("����min")));
	ui.tableWidget->item(8, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(8, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(9, 0)->setText(QString(tr("5")));
	ui.tableWidget->item(9, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(9, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(10, 0)->setText(QString(tr("20")));
	ui.tableWidget->item(10, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(10, 0)->setTextColor(Qt::red);

	ui.tableWidget->setSpan(11, 0, 1, 14);
	ui.tableWidget->item(11, 0)->setText(QString(tr("TemperIn:  ��max-5�ܦ�e �� ��max")));
	ui.tableWidget->item(11, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(11, 0)->setTextColor(Qt::blue);
	ui.tableWidget->item(12, 0)->setText(QString(tr("20")));
	ui.tableWidget->item(12, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(12, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(13, 0)->setText(QString(tr("����ref")));
	ui.tableWidget->item(13, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(13, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(14, 0)->setText(QString(tr("����max-5")));
	ui.tableWidget->item(14, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(14, 0)->setTextColor(Qt::red);

// 	ui.tableWidget->resizeColumnsToContents();

	//���ñ�񲻿ɱ༭
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
// 	ui.tableWidget->setEnabled(false);

	ui.btnStart->setEnabled(false);
	ui.btnSave->setEnabled(false);
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

	ui.tableWidget->item(2, 0)->setText(QString(tr("TemperOut: %1 - %2 ��")).arg(m_minT).arg(m_minT+5));
	ui.tableWidget->item(2, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(2, 0)->setTextColor(Qt::blue);
	ui.tableWidget->item(3, 0)->setText(QString(tr("%1")).arg(m_minDeltaT));
	ui.tableWidget->item(3, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(3, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(6, 0)->setText(QString(tr("%1")).arg(m_refDeltaT));
	ui.tableWidget->item(6, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(6, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(7, 0)->setText(QString(tr("TemperOut: %1 - %2 ��")).arg(m_refT-5).arg(m_refT+5));
	ui.tableWidget->item(7, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(7, 0)->setTextColor(Qt::blue);
	ui.tableWidget->item(8, 0)->setText(QString(tr("%1")).arg(m_minDeltaT));
	ui.tableWidget->item(8, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(8, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(11, 0)->setText(QString(tr("TemperIn: %1 - %2 ��")).arg(m_maxT-5).arg(m_maxT));
	ui.tableWidget->item(11, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	ui.tableWidget->item(11, 0)->setTextColor(Qt::blue);
	ui.tableWidget->item(13, 0)->setText(QString(tr("%1")).arg(m_refDeltaT));
	ui.tableWidget->item(13, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(13, 0)->setTextColor(Qt::red);
	ui.tableWidget->item(14, 0)->setText(QString(tr("%1")).arg(m_maxDeltaT-5));
	ui.tableWidget->item(14, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tableWidget->item(14, 0)->setTextColor(Qt::red);

	ui.hintLabel->setText(tr("please click \"start\" button to start verify!"));
	ui.btnStart->setEnabled(true);
}

void CalcDlg::on_tableWidget_cellChanged(int row, int column)
{
	if (NULL==ui.tableWidget->item(row,  column) || row<=2)
	{
		return;
	}
	qDebug()<<"row ="<<row<<", column ="<<column;
	bool ok;
	float inR = ui.tableWidget->item(row, COLUMN_IN_RESIST)->text().toFloat(&ok);
	float outR = ui.tableWidget->item(row, COLUMN_OUT_RESIST)->text().toFloat(&ok);
	float analogV = ui.tableWidget->item(row, COLUMN_ANALOG_V)->text().toFloat(&ok);
	float inTemper = ui.tableWidget->item(row, COLUMN_IN_TEMPER)->text().toFloat(&ok);
	float outTemper = ui.tableWidget->item(row, COLUMN_OUT_TEMPER)->text().toFloat(&ok);
	float KCoe = ui.tableWidget->item(row, COLUMN_K_COE)->text().toFloat(&ok); //����Kϵ�����ʲ�
	float recomV = ui.tableWidget->item(row, COLUMN_RECOM_V)->text().toFloat(&ok);
	float theoryEnergy = ui.tableWidget->item(row, COLUMN_THEORY_ENERGY)->text().toFloat(&ok);
	float E0 = ui.tableWidget->item(row, COLUMN_E0)->text().toFloat(&ok);
	float E1 = ui.tableWidget->item(row, COLUMN_E1)->text().toFloat(&ok);
	float dispEnergy = ui.tableWidget->item(row, COLUMN_DISP_ENERGY)->text().toFloat(&ok);
	float dispError = ui.tableWidget->item(row, COLUMN_DISP_ERROR)->text().toFloat(&ok);
	float stdError = ui.tableWidget->item(row, COLUMN_STD_ERROR)->text().toFloat(&ok);

	switch (column)
	{
	case COLUMN_IN_RESIST: //���ڵ���
		inTemper = calcTemperByResist(1, inR); //��������¶�
		ui.tableWidget->item(row, COLUMN_IN_TEMPER)->setText(QString("%1").arg(inTemper));
		ui.tableWidget->setCurrentCell(row, COLUMN_OUT_RESIST);
		break;
	case COLUMN_OUT_RESIST: //���ڵ���
		outTemper = calcTemperByResist(0, outR); //��������¶�
		ui.tableWidget->item(row, COLUMN_OUT_TEMPER)->setText(QString("%1").arg(outTemper));
		if (ui.radioButtonKCoe->isChecked()) //Kϵ����
		{
			KCoe = getKCoeByTemper(inTemper, outTemper); //��ȡKϵ��
		}
		else if (ui.radioButtonEnthalpy->isChecked()) //�ʲ
		{
			KCoe = getEnthalpyDiffByTemper(inTemper, outTemper);
		}
		ui.tableWidget->item(row, COLUMN_K_COE)->setText(QString("%1").arg(KCoe));
// 		stdError = (0.5 + m_minDeltaT/(inTemper-outTemper)); //��׼���
		stdError = 0.5 + m_minDeltaT/ui.tableWidget->item(row,0)->text().toFloat(); //��׼���
		ui.tableWidget->item(row, COLUMN_STD_ERROR)->setText(QString("%1").arg(stdError));
		recomV = calcRecomVolume(stdError, inTemper, outTemper, KCoe); //���㽨�����
		ui.tableWidget->item(row, COLUMN_RECOM_V)->setText(QString("%1").arg(recomV));
		ui.tableWidget->setCurrentCell(row, COLUMN_ANALOG_V); 
		break;
	case COLUMN_ANALOG_V: //ģ������
		if (ui.radioButtonKCoe->isChecked()) //Kϵ����
		{
			theoryEnergy = calcTheoryEnergyByKCoe(KCoe, analogV/1000, inTemper, outTemper); //������������
		}
		else if (ui.radioButtonEnthalpy->isChecked()) //�ʲ
		{
			theoryEnergy = calcTheoryEnergyByEnthalpy(analogV/1000, inTemper, outTemper); //������������
		}

		if (ui.radioButtonMJ->isChecked()) //��λMJ
		{
			theoryEnergy *= 3.6;
		}
		ui.tableWidget->item(row, COLUMN_THEORY_ENERGY)->setText(QString("%1").arg(theoryEnergy));
		ui.tableWidget->setCurrentCell(row, COLUMN_E0); 
		break;
	case COLUMN_E0: //E0
		ui.tableWidget->setCurrentCell(row, COLUMN_E1); 
		break;
	case COLUMN_E1: //E1
		dispEnergy = E1 - E0; //����ʾֵ
		ui.tableWidget->item(row, COLUMN_DISP_ENERGY)->setText(QString("%1").arg(dispEnergy));
		dispError = 100*(dispEnergy - theoryEnergy)/theoryEnergy; //����ʾֵ���
		ui.tableWidget->item(row, COLUMN_DISP_ERROR)->setText(QString("%1").arg(dispError));
		if (dispError > stdError)
		{
			ui.tableWidget->item(row, COLUMN_DISP_ERROR)->setTextColor(QColor(Qt::red));
		}
		break;
	default:
		qDebug()<<"no need input";
		break;
	}
}

/*
**
**	port: 1:��ڣ�0:����
*/
float CalcDlg::calcTemperByResist(int port, float resist)
{
	QString filename = getFullIniFileName("stdplasensor.ini");//�����ļ����ļ���
	QSettings *settings = new QSettings(filename, QSettings::IniFormat);
	settings->setIniCodec("GB2312");//�����ini�ļ���д��������
	
	float in_r0 = settings->value("pt100/in_rtp").toFloat();
	float in_a = settings->value("pt100/in_a").toFloat();
	float in_b = settings->value("pt100/in_b").toFloat();
	float inTemper = getPlaTr(in_r0, in_a, in_b, resist);

	float out_r0 = settings->value("pt100/out_rtp").toFloat();
	float out_a = settings->value("pt100/out_a").toFloat();
	float out_b = settings->value("pt100/out_b").toFloat();
	float outTemper = getPlaTr(out_r0, out_a, out_b, resist);

	float retT = 0.0;
	if (port) //���
	{
		retT = inTemper;
	}
	else
	{
		retT = outTemper;
	}
	return retT;
}

/*
** ��Ҫ���ǰ�װλ�ú�������λ
*/
float CalcDlg::getKCoeByTemper(float inT, float outT)
{
	return 1.143;
}

//���ݽ������¶Ȼ�ȡ�ʲ��λkJ/kg
float CalcDlg::getEnthalpyDiffByTemper(float inTemper, float outTemper)
{
	float ret = m_algo->getEnthalpyByQuery(inTemper) - m_algo->getEnthalpyByQuery(outTemper);
	return ret;
}

float CalcDlg::calcRecomVolume(float stdErr, float inTemper, float outTemper, float kCoe)
{
	float recomV = 0.0;
//	Text44(txt_idx) = Int(3000 / (Val(Text21(txt_idx).Text) * (Text11(txt_idx).Text - Text12(txt_idx).Text) * Text14(txt_idx).Text) / 10) * 10
	recomV = int(3000 / (stdErr * (inTemper - outTemper) * kCoe) / 10) * 10;

	return recomV;
}

/*
** ���ܣ�Kϵ������������
** ���������kCoe:Kϵ������λkwh/m3.��
			 analogV:�������λm3
		     inTemper:����¶ȣ���λ��
			 outTemper:�����¶ȣ���λ��
   ����ֵ:��������λkwh
*/
float CalcDlg::calcTheoryEnergyByKCoe(float kCoe, float analogV, float inTemper, float outTemper)
{
	float energy = 0.0;
	energy = kCoe*analogV*(inTemper - outTemper);
	return energy;
}

/*
** ���ܣ��ʲ��������
** ���������analogV:�������λm3
		     inTemper:����¶ȣ���λ��
			 outTemper:�����¶ȣ���λ��
   ����ֵ:��������λkwh
*/
float CalcDlg::calcTheoryEnergyByEnthalpy(float analogV, float inTemper, float outTemper)
{
	float energy = 0.0;
	float density = 0.0;
// 	float inDensity = 1000*m_algo->getDensityByQuery(inTemper);//�ܶȣ���λkg/m3
// 	float outDensity = 1000*m_algo->getDensityByQuery(outTemper);
	float inEnthalpy = m_algo->getEnthalpyByQuery(inTemper); //��ֵ����λkJ/kg
	float outEnthalpy = m_algo->getEnthalpyByQuery(outTemper);
	float diffEnthalpy = inEnthalpy - outEnthalpy; //�ʲ�
	if (ui.radioButtonPosIn->isChecked()) //��װλ�ã�����
	{
		density = 1000*m_algo->getDensityByQuery(inTemper);
	}
	else //��װλ�ã�����
	{
		density = 1000*m_algo->getDensityByQuery(outTemper);
	}
// 	float inEnergy = analogV*inDensity*inEnthalpy; //��λkJ
// 	float outEnergy = analogV*outDensity*outEnthalpy;
	energy = analogV*density*diffEnthalpy/3600;//��λת����kJ->kwh
	return energy;
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
			m_recPtr->theoryEnergy = ui.tableWidget->item(i, COLUMN_THEORY_ENERGY)->text().toFloat();
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

void CalcDlg::slot_btnGroupInstallPos_clicked(int id)
{
	qDebug()<<"id ="<<id;

}

void CalcDlg::slot_btnGroupEnergyUnit_clicked(int id)
{
	qDebug()<<"id ="<<id;
	int unit = btnGroupEnergyUnit->checkedId();
	int algo = btnGroupAlgorithm->checkedId();

	ui.tableWidget->item(1, COLUMN_K_COE)->setText(KStr[algo][unit]);
	ui.tableWidget->item(1, COLUMN_THEORY_ENERGY)->setText(tr("StdEnergy(\n") + unitStr[unit] + ")");
	ui.tableWidget->item(1, COLUMN_E0)->setText(tr("E0(\n") + unitStr[unit] + ")");
	ui.tableWidget->item(1, COLUMN_E1)->setText(tr("E1(\n") + unitStr[unit] + ")");
	ui.tableWidget->item(1, COLUMN_DISP_ENERGY)->setText(tr("DispEnergy(\n") + unitStr[unit] + ")");
}

void CalcDlg::slot_btnGroupAlgorithm_clicked(int id)
{
	qDebug()<<"id ="<<id;
	int unit = btnGroupEnergyUnit->checkedId();
	int algo = btnGroupAlgorithm->checkedId();

	ui.tableWidget->item(1, COLUMN_K_COE)->setText(KStr[algo][unit]);
}
