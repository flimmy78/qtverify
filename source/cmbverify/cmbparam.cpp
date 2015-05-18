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
	m_lineEdit_quan_vec.append(ui.lineEdit_quan_1);
	m_lineEdit_quan_vec.append(ui.lineEdit_quan_2);
	m_lineEdit_quan_vec.append(ui.lineEdit_quan_3);

	m_lineEdit_temp_vec.append(ui.lineEdit_temp_1);
	m_lineEdit_temp_vec.append(ui.lineEdit_temp_2);
	m_lineEdit_temp_vec.append(ui.lineEdit_temp_3);

	m_cbox_order_vec.append(ui.cbox_seq_1);
	m_cbox_order_vec.append(ui.cbox_seq_2);
	m_cbox_order_vec.append(ui.cbox_seq_3);

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
	model->setTable("T_Meter_Type");
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

		
		for (int i=0;i < VERIFY_POINTS;i++)
		{
			m_param_config->beginGroup("diff_" + QString::number(i));
			if (m_param_config->value("in_use").toInt())
			{
				m_lineEdit_quan_vec[i]->setText(m_param_config->value("quantity").toString());
				m_lineEdit_temp_vec[i]->setText(m_param_config->value("temp_deff").toString());
				m_cbox_order_vec[i]->setCurrentIndex(m_param_config->value("order").toInt());
			}
			m_param_config->endGroup();
		}
	}
}

void CmbParamDlg::saveConfig()
{
	if (!chkSeq())
	{
		QMessageBox::warning(this, tr("Warning"), tr("verify sequence is invalid!"));
		return;
	}

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

	for (int i=0;i < VERIFY_POINTS; i++)
	{
		if (m_cbox_order_vec[i]->currentIndex())
		{
			m_param_config->beginGroup("diff_" + QString::number(i));
			m_param_config->setValue("in_use", 1);
			m_param_config->setValue("quantity", m_lineEdit_quan_vec[i]->text());
			m_param_config->setValue("temp_deff", m_lineEdit_temp_vec[i]->text());
			m_param_config->setValue("order", m_cbox_order_vec[i]->currentIndex());
			m_param_config->endGroup();
		}
		else
		{
			m_param_config->beginGroup("diff_" + QString::number(i));
			m_param_config->setValue("in_use", NOT_USE);
			m_param_config->setValue("quantity", 0.0);
			m_param_config->setValue("temp_deff", 0.0);
			m_param_config->setValue("order", 0);
			m_param_config->endGroup();
		}
	}

	emit saveSuccessfully();
}

bool CmbParamDlg::chkSeq()
{
	int max_seq = 0;//最大的次序号
	int total_seqs = 0;//非零的检定次序号的个数
	QVector<int> repeat_seq;//已发现的元素序列

	for (int i=0; i < VERIFY_POINTS; i++)
	{
		int current_seq = m_cbox_order_vec[i]->currentIndex();

		if (current_seq > 0)//本函数中的自然数序列不包含零元素
		{
			//挑出最大的!*非零元素*!次序号
			if (max_seq < current_seq)
			{
				max_seq = current_seq;
			}

			total_seqs ++;//计算!*非零元素*!的个数
			//如果存在*重复*的!*非零元素*!, 则返回false;否则将当前元素加入已发现的元素序列
			if (repeat_seq.contains(current_seq))
			{
				return false;
			}
			else
			{
				repeat_seq.append(current_seq);
			}
		}
	}
	//如果最大的次序号为0, 则认为用户漏选了检定次序
	if (max_seq == 0)
	{
		return false;
	}

	return (max_seq == total_seqs);
}

void CmbParamDlg::on_btn_exit_clicked()
{
	this->close();
}