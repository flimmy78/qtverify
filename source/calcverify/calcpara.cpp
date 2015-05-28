/***********************************************
**  文件名:     calcparam.cpp
**  功能:       计算器检定参数设置
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/4/28
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
#include <QtSql/QSqlRelationalTableModel>
#include <QtGui/QFileDialog>
#include <QtCore/QSignalMapper>
#include <QtCore/QProcess>
#include <QtCore/QSettings>
#include <math.h>

#include "calcpara.h"
#include "algorithm.h"

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

//映射送检单位
void CalcParaDlg::mapVfDeptModel()
{
	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable("T_Verify_Dept");  
	model->select();
	ui.cmbVerifyDept->setModel(model);  
	ui.cmbVerifyDept->setModelColumn(model->fieldIndex("F_Desc")); // 使用字段名得到正确的标题索引,以使组合框显示部门名  
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

//映射制造单位
void CalcParaDlg::mapManuDeptModel()
{
	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable("T_Manufacture_Dept");  
	model->select();
	ui.cmbManufact->setModel(model);  
	ui.cmbManufact->setModelColumn(model->fieldIndex("F_Desc")); // 使用字段名得到正确的标题索引,以使组合框显示部门名  
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

//映射送检员
void CalcParaDlg::mapUserModel()
{
	QSqlTableModel *m_userModel = new QSqlTableModel(this);  
	m_userModel->setTable("T_User_Def_Tab");  
	m_userModel->select();  
	ui.cmbVerifyPerson->setModel(m_userModel);  
	ui.cmbVerifyPerson->setModelColumn(m_userModel->fieldIndex("F_Desc"));
	m_userModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

//映射表型号
void CalcParaDlg::mapMeterModelModel()
{
	QSqlTableModel *m_modelModel = new QSqlTableModel(this);  
	m_modelModel->setTable("T_Meter_Model");  
	m_modelModel->select();
	ui.cmbModel->setModel(m_modelModel);  
	ui.cmbModel->setModelColumn(m_modelModel->fieldIndex("F_Desc")); 
	m_modelModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

//映射表规格
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
	QString filename = getFullIniFileName("calcpara.ini");//配置文件的文件名
	settings = new QSettings(filename, QSettings::IniFormat);
	settings->setIniCodec("GB2312");//解决向ini文件中写汉字乱码
}

void CalcParaDlg::readSettings()
{
	//检定参数
	ui.lnEditMeterNO->setText(settings->value("verifypara/meterno").toString());
	ui.cmbStandard->setCurrentIndex(settings->value("verifypara/standard").toInt());
	ui.cmbModel->setCurrentIndex(settings->value("verifypara/model").toInt());
	ui.cmbGrade->setCurrentIndex(settings->value("verifypara/grade").toInt());
	ui.cmbManufact->setCurrentIndex(settings->value("verifypara/manufact").toInt());
	ui.cmbVerifyDept->setCurrentIndex(settings->value("verifypara/verifydept").toInt());
	ui.cmbVerifyPerson->setCurrentIndex(settings->value("verifypara/verifyer").toInt());
	//热量表参数
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
