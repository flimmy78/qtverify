#include <QtGui/QMessageBox>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include "algorithm.h"
#include "cmbparam.h"

CmbParamDlg::CmbParamDlg(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
	: QWidget(parent, flags)
{

	ui.setupUi(this);
}

CmbParamDlg::~CmbParamDlg()
{

}

void CmbParamDlg::showEvent(QShowEvent * event)
{
	cBoxData_inited = false;
	m_param_config = new QSettings(getFullIniFileName("cmbparam.ini"), QSettings::IniFormat);

	initCmbBox();
	readConfig();
}

void CmbParamDlg::closeEvent(QCloseEvent * event)
{
	if (m_param_config)
	{
		delete m_param_config;
		m_param_config = NULL;
	}
}

void CmbParamDlg::on_btn_save_clicked()
{
	saveConfig();
}

void CmbParamDlg::initCmbBox()
{
	initStand();
	initModel();
	initCollCode();
	initManufac();
	initInst();
	initChker();
	cBoxData_inited = true;
}

void CmbParamDlg::initStand()
{
	QSqlTableModel *model = new QSqlTableModel(this);
	model->setTable("T_Meter_Standard");
	model->select();
	ui.cBox_stand->setModel(model);
	ui.cBox_stand->setModelColumn(model->fieldIndex("F_Name"));
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void CmbParamDlg::initModel()
{
	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable("T_Meter_Model");  
	model->select();
	ui.cBox_model->setModel(model);  
	ui.cBox_model->setModelColumn(model->fieldIndex("F_Desc")); 
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void CmbParamDlg::initCollCode()
{
	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable("T_Meter_PickCode");
	model->select();
	ui.cBox_collcode->setModel(model);  
	ui.cBox_collcode->setModelColumn(model->fieldIndex("F_Desc")); 
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void CmbParamDlg::initManufac()
{
	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable("T_Manufacture_Dept");  
	model->select();
	ui.cBox_manu->setModel(model);  
	ui.cBox_manu->setModelColumn(model->fieldIndex("F_Desc")); 
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void CmbParamDlg::initInst()
{
	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable("T_Verify_Dept");  
	model->select();
	ui.cBox_inst->setModel(model);  
	ui.cBox_inst->setModelColumn(model->fieldIndex("F_Desc")); 
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void CmbParamDlg::initChker()
{
	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable("T_User_Def_Tab");  
	model->select();  
	ui.cBox_chk->setModel(model);  
	ui.cBox_chk->setModelColumn(model->fieldIndex("F_Desc"));
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void CmbParamDlg::readConfig()
{
	if (cBoxData_inited)
	{
		m_param_config->beginGroup("common");
		ui.cBox_stand->setCurrentIndex(m_param_config->value("stand").toInt());
		ui.lineEdit_dnflow->setText(m_param_config->value("dnflow").toString());
		ui.cBox_collcode->setCurrentIndex(m_param_config->value("collcode").toInt());
		ui.cBox_model->setCurrentIndex(m_param_config->value("model").toInt());
		ui.cBox_manu->setCurrentIndex(m_param_config->value("manu").toInt());
		ui.cBox_grade->setCurrentIndex(m_param_config->value("grade").toInt());
		ui.cBox_inst->setCurrentIndex(m_param_config->value("inst").toInt());
		ui.cBox_chk->setCurrentIndex(m_param_config->value("chk").toInt());
		m_param_config->endGroup();

		
		m_param_config->beginGroup("diff");
		ui.lineEdit_quan->setText(m_param_config->value("quantity").toString());
		ui.lineEdit_temp_diff->setText(m_param_config->value("temp_deff").toString());
		m_param_config->endGroup();
		
	}
}

void CmbParamDlg::saveConfig()
{
	m_param_config->beginGroup("common");
	m_param_config->setValue("stand", ui.cBox_stand->currentIndex());
	m_param_config->setValue("dnflow", ui.lineEdit_dnflow->text());
	m_param_config->setValue("collcode", ui.cBox_collcode->currentIndex());
	m_param_config->setValue("model", ui.cBox_model->currentIndex());
	m_param_config->setValue("manu", ui.cBox_manu->currentIndex());
	m_param_config->setValue("grade", ui.cBox_grade->currentIndex());
	m_param_config->setValue("inst", ui.cBox_inst->currentIndex());
	m_param_config->setValue("chk", ui.cBox_chk->currentIndex());
	m_param_config->endGroup();

	m_param_config->beginGroup("diff");
	m_param_config->setValue("quantity", ui.lineEdit_quan->text());
	m_param_config->setValue("temp_deff", ui.lineEdit_temp_diff->text());
	m_param_config->endGroup();
	
	emit saveSuccessfully();
}

void CmbParamDlg::on_btn_exit_clicked()
{
	this->close();
}