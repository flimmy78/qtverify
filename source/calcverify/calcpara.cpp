/***********************************************
**  �ļ���:     calcparam.cpp
**  ����:       �������춨��������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2015/4/28
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
#include <QtSql/QSqlRelationalTableModel>
#include <QtGui/QFileDialog>
#include <QtCore/QSignalMapper>
#include <QtCore/QProcess>
#include <QtCore/QSettings>
#include <math.h>

#include "calcpara.h"

CalcParaDlg::CalcParaDlg(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	mapVfDeptModel();
	mapManuDeptModel();
	mapUserModel();
	mapMeterModelModel();
	mapMeterStandardModel();

	settings = NULL;
	initSettings();
	readSettings();

	m_maxT = 0.0;
	m_minT = 0.0;
	m_maxDeltaT = 0.0;
	m_minDeltaT = 0.0;
}

CalcParaDlg::~CalcParaDlg()
{
}

void CalcParaDlg::closeEvent( QCloseEvent * event)
{
	if (settings)
	{
		delete []settings;
		settings = NULL;
	}

}

//ӳ���ͼ쵥λ
void CalcParaDlg::mapVfDeptModel()
{
	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable("T_Verify_Dept");  
	model->select();
	ui.cmbVerifyDept->setModel(model);  
	ui.cmbVerifyDept->setModelColumn(model->fieldIndex("F_Desc")); // ʹ���ֶ����õ���ȷ�ı�������,��ʹ��Ͽ���ʾ������  
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

//ӳ�����쵥λ
void CalcParaDlg::mapManuDeptModel()
{
	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable("T_Manufacture_Dept");  
	model->select();
	ui.cmbManufact->setModel(model);  
	ui.cmbManufact->setModelColumn(model->fieldIndex("F_Desc")); // ʹ���ֶ����õ���ȷ�ı�������,��ʹ��Ͽ���ʾ������  
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

//ӳ���ͼ�Ա
void CalcParaDlg::mapUserModel()
{
	QSqlTableModel *m_userModel = new QSqlTableModel(this);  
	m_userModel->setTable("T_User_Def_Tab");  
	m_userModel->select();  
	ui.cmbVerifyPerson->setModel(m_userModel);  
	ui.cmbVerifyPerson->setModelColumn(m_userModel->fieldIndex("F_Desc"));
	m_userModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

//ӳ����ͺ�
void CalcParaDlg::mapMeterModelModel()
{
	QSqlTableModel *m_modelModel = new QSqlTableModel(this);  
	m_modelModel->setTable("T_Meter_Model");  
	m_modelModel->select();
	ui.cmbModel->setModel(m_modelModel);  
	ui.cmbModel->setModelColumn(m_modelModel->fieldIndex("F_Desc")); 
	m_modelModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

//ӳ�����
void CalcParaDlg::mapMeterStandardModel()
{
	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable("T_Meter_Standard");  
	model->select();
	ui.cmbStandard->setModel(model);  
	ui.cmbStandard->setModelColumn(model->fieldIndex("F_Name")); 
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void CalcParaDlg::initSettings()
{
	QString filename;//�����ļ����ļ���
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");
#ifdef __unix
	filename = runhome + "\/ini\/calcpara.ini";
#else
	filename = runhome + "\\ini\\calcpara.ini";
#endif
	settings = new QSettings(filename, QSettings::IniFormat);
	settings->setIniCodec("GB2312");//�����ini�ļ���д��������
}

void CalcParaDlg::readSettings()
{
	//�춨����
	ui.lnEditMeterNO->setText(settings->value("verifypara/meterno").toString());
	ui.cmbStandard->setCurrentIndex(settings->value("verifypara/standard").toInt());
	ui.cmbModel->setCurrentIndex(settings->value("verifypara/model").toInt());
	ui.cmbGrade->setCurrentIndex(settings->value("verifypara/grade").toInt());
	ui.cmbManufact->setCurrentIndex(settings->value("verifypara/manufact").toInt());
	ui.cmbVerifyDept->setCurrentIndex(settings->value("verifypara/verifydept").toInt());
	ui.cmbVerifyPerson->setCurrentIndex(settings->value("verifypara/verifyer").toInt());
	//���������
	ui.lnEditMaxT->setText(settings->value("heatpara/maxT").toString());
	ui.lnEditMinT->setText(settings->value("heatpara/minT").toString());
	ui.lnEditMaxDeltaT->setText(settings->value("heatpara/maxDeltaT").toString());
	ui.lnEditMinDeltaT->setText(settings->value("heatpara/minDeltaT").toString());
}

void CalcParaDlg::writeSettings()
{
	settings->setValue("verifypara/meterno", ui.lnEditMeterNO->text());
	settings->setValue("verifypara/standard", ui.cmbStandard->currentIndex());
	settings->setValue("verifypara/model", ui.cmbModel->currentIndex());
	settings->setValue("verifypara/grade", ui.cmbGrade->currentIndex());
	settings->setValue("verifypara/manufact", ui.cmbManufact->currentIndex());
	settings->setValue("verifypara/verifydept", ui.cmbVerifyDept->currentIndex());
	settings->setValue("verifypara/verifyer", ui.cmbVerifyPerson->currentIndex());

	settings->setValue("heatpara/maxT", ui.lnEditMaxT->text());
	settings->setValue("heatpara/minT", ui.lnEditMinT->text());
	settings->setValue("heatpara/maxDeltaT", ui.lnEditMaxDeltaT->text());
	settings->setValue("heatpara/minDeltaT", ui.lnEditMinDeltaT->text());
}

QString CalcParaDlg::getMeterNO()
{
	return m_meterNO;
}

int CalcParaDlg::getStandard()
{
	return m_standard;
}

int CalcParaDlg::getModel()
{
	return m_model;
}

int CalcParaDlg::getGrade()
{
	return m_grade;
}

int CalcParaDlg::getManuFact()
{
	return m_manufact;
}

int CalcParaDlg::getVerifyDept()
{
	return m_verifydept;
}

int CalcParaDlg::getVerifyPerson()
{
	return m_verifyperson;
}

float CalcParaDlg::getMaxT()
{
	return m_maxT;
}

float CalcParaDlg::getMinT()
{
	return m_minT;
}

float CalcParaDlg::getMaxDeltaT()
{
	return m_maxDeltaT;
}

float CalcParaDlg::getMinDeltaT()
{
	return m_minDeltaT;
}

void CalcParaDlg::on_btnOK_clicked()
{
	writeSettings();

	m_meterNO = ui.lnEditMeterNO->text();
	m_standard = ui.cmbStandard->currentIndex();
	m_model = ui.cmbModel->currentIndex();
	m_grade = ui.cmbGrade->currentIndex();
	m_manufact = ui.cmbManufact->currentIndex();
	m_verifydept = ui.cmbVerifyDept->currentIndex();
	m_verifyperson = ui.cmbVerifyPerson->currentIndex();
	m_maxT = ui.lnEditMaxT->text().toFloat();
	m_minT = ui.lnEditMinT->text().toFloat();
	m_maxDeltaT = ui.lnEditMaxDeltaT->text().toFloat();
	m_minDeltaT = ui.lnEditMinDeltaT->text().toFloat();

	emit saveSuccessSignal();
}

void CalcParaDlg::on_btnExit_clicked()
{
	this->close();
}
