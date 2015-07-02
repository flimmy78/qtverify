#include <QSqlTableModel>
#include <QDebug>
#include <QSqlRelationalTableModel>
#include "tverparamparamdlg.h"
#include "algorithm.h"

tverparamparamDlg::tverparamparamDlg(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
}

tverparamparamDlg::~tverparamparamDlg()
{

}

void tverparamparamDlg::on_btn_save_clicked()
{
	saveConfig();
}

void tverparamparamDlg::on_btn_exit_clicked()
{
	this->close();
}

void tverparamparamDlg::initCmbBox()
{
	
	startdb();
	//����
	getMeterStandard(m_meterStdNum, m_meterStdPtr);
	for (int i=0; i<m_meterStdNum; i++)
	{
		qDebug()<<"id:"<<m_meterStdPtr[i].id<<",name:"<<m_meterStdPtr[i].name;
		ui.cBox_stand->insertItem(i, m_meterStdPtr[i].name);
	}

	//���쵥λ
	getManufacture(m_manuFacNum, m_manuFacPtr);
	for (int m=0; m<m_manuFacNum; m++)
	{
		qDebug()<<"id:"<<m_manuFacPtr[m].id<<",desc:"<<QString::fromLocal8Bit(m_manuFacPtr[m].desc);
		ui.cBox_manu->insertItem(m, QString::fromLocal8Bit(m_manuFacPtr[m].desc)); //���ֱ���
	}

	//�ͼ쵥λ
	int col_id = 0;
	QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);  
	model->setTable("T_Verify_Dept");  
	model->setRelation(col_id, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));  
	//QComboBox��QListWidget������,��Ϊ����һ���ڲ�ģ��ȥ��������������Ŀ,�����������Լ�����ģ�ʹ����Ǹ��Դ���ģ�͡�
	//����QSqlRelationalTableModelʹ�õĹ�ϵģ�ͣ����ģ��������,����ָ����Ͽ�Ӧ����ʾ��һ��   
	QSqlTableModel *relationModel = model->relationModel(col_id); // ����ID   
	ui.cBox_inst->setModel(relationModel);  
	ui.cBox_inst->setModelColumn(relationModel->fieldIndex("F_Desc")); // ʹ���ֶ����õ���ȷ�ı�������,��ʹ��Ͽ���ʾ������  

	//����Ա
	int col_id1 = 0;
	QSqlRelationalTableModel *model1 = new QSqlRelationalTableModel(this);  
	model1->setTable("T_User_Def_Tab");  
	model1->setRelation(col_id1, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));  
	QSqlTableModel *relationModel1 = model1->relationModel(col_id1);   
	ui.cBox_chk->setModel(relationModel1);  
	ui.cBox_chk->setModelColumn(relationModel1->fieldIndex("F_Desc"));

	//���Ա
	int col_id2 = 0;
	QSqlRelationalTableModel *model3 = new QSqlRelationalTableModel(this);  
	model3->setTable("T_User_Def_Tab");  
	model3->setRelation(col_id2, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));  
	QSqlTableModel *relationModel2 = model3->relationModel(col_id2);   
	ui.cBox_verifier->setModel(relationModel2);  
	ui.cBox_verifier->setModelColumn(relationModel2->fieldIndex("F_Desc"));

	//�ͺ�
	int col_id3 = 0;
	QSqlRelationalTableModel *model2 = new QSqlRelationalTableModel(this);  
	model2->setTable("T_Meter_Model");  
	model2->setRelation(col_id3, QSqlRelation("T_Meter_Model","F_ID","F_Desc"));  
	QSqlTableModel *relationModel3 = model2->relationModel(col_id3);   
	ui.cBox_model->setModel(relationModel3);  
	ui.cBox_model->setModelColumn(relationModel3->fieldIndex("F_Desc")); 
	closedb();
	cBoxData_inited = true;//�������ѳ�ʼ�����
}

void tverparamparamDlg::showEvent(QShowEvent * event)
{
	m_config = new QSettings(getFullIniFileName("tverparamconfig.ini"), QSettings::IniFormat);
	initCmbBox();
	readConfig();//��ȡ�ϴ����ò���
}

void tverparamparamDlg::closeEvent(QCloseEvent * event)
{
	if (m_config)
	{
		delete m_config;
		m_config = NULL;
	}
}

void tverparamparamDlg::readConfig()
{
	if(cBoxData_inited)
	{
		//read last configuration
		ui.cBox_stand->setCurrentIndex(m_config->value("chkinfo/stand").toInt());
		ui.cBox_model->setCurrentIndex(m_config->value("chkinfo/model").toInt());
		ui.cBox_manu->setCurrentIndex(m_config->value("chkinfo/manufac").toInt());
		ui.cBox_inst->setCurrentIndex(m_config->value("chkinfo/inst").toInt());
		ui.cBox_chk->setCurrentIndex(m_config->value("chkinfo/chker").toInt());
		ui.cBox_verifier->setCurrentIndex(m_config->value("chkinfo/verifyer").toInt());
		ui.cBox_chanel->setCurrentIndex(m_config->value("chkinfo/chanel").toInt());
	}
}

void tverparamparamDlg::saveConfig()
{
	//save configuration to config file'
	m_config->beginGroup("chkinfo");
	m_config->setValue("stand", ui.cBox_stand->currentIndex());
	m_config->setValue("model", ui.cBox_model->currentIndex());
	m_config->setValue("manufac", ui.cBox_manu->currentIndex());
	m_config->setValue("inst", ui.cBox_inst->currentIndex());
	m_config->setValue("chker", ui.cBox_chk->currentIndex());
	m_config->setValue("verifyer", ui.cBox_verifier->currentIndex());
	m_config->setValue("chanel", ui.cBox_chanel->currentIndex());
	m_config->endGroup();
}