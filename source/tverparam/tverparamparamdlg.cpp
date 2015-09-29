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
	//表规格
	getMeterStandard(m_meterStdNum, m_meterStdPtr);
	for (int i=0; i<m_meterStdNum; i++)
	{
		qDebug()<<"id:"<<m_meterStdPtr[i].id<<",name:"<<m_meterStdPtr[i].name;
		ui.cBox_stand->insertItem(i, m_meterStdPtr[i].name);
	}

	//制造单位
	getManufacture(m_manuFacNum, m_manuFacPtr);
	for (int m=0; m<m_manuFacNum; m++)
	{
		qDebug()<<"id:"<<m_manuFacPtr[m].id<<",desc:"<<QString::fromLocal8Bit(m_manuFacPtr[m].desc);
		ui.cBox_manu->insertItem(m, QString::fromLocal8Bit(m_manuFacPtr[m].desc)); //汉字编码
	}

	//送检单位
	int col_id = 0;
	QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this, g_defaultdb);  
	model->setTable("T_Verify_Dept");  
	model->setRelation(col_id, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));  
	//QComboBox与QListWidget很相拟,因为它有一个内部模型去保存它的数据条目,所以我们用自己建的模型代替那个自带的模型。
	//给出QSqlRelationalTableModel使用的关系模型，这个模型有两列,必须指出组合框应该显示哪一列   
	QSqlTableModel *relationModel = model->relationModel(col_id); // 部门ID   
	ui.cBox_inst->setModel(relationModel);  
	ui.cBox_inst->setModelColumn(relationModel->fieldIndex("F_Desc")); // 使用字段名得到正确的标题索引,以使组合框显示部门名  

	//核验员
	int col_id1 = 0;
	QSqlRelationalTableModel *model1 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model1->setTable("T_User_Def_Tab");  
	model1->setRelation(col_id1, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));  
	QSqlTableModel *relationModel1 = model1->relationModel(col_id1);   
	ui.cBox_chk->setModel(relationModel1);  
	ui.cBox_chk->setModelColumn(relationModel1->fieldIndex("F_Desc"));

	//检测员
	int col_id2 = 0;
	QSqlRelationalTableModel *model3 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model3->setTable("T_User_Def_Tab");  
	model3->setRelation(col_id2, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));  
	QSqlTableModel *relationModel2 = model3->relationModel(col_id2);   
	ui.cBox_verifier->setModel(relationModel2);  
	ui.cBox_verifier->setModelColumn(relationModel2->fieldIndex("F_Desc"));

	//型号
	int col_id3 = 0;
	QSqlRelationalTableModel *model2 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model2->setTable("T_Meter_Model");  
	model2->setRelation(col_id3, QSqlRelation("T_Meter_Model","F_ID","F_Desc"));  
	QSqlTableModel *relationModel3 = model2->relationModel(col_id3);   
	ui.cBox_model->setModel(relationModel3);  
	ui.cBox_model->setModelColumn(relationModel3->fieldIndex("F_Desc")); 

	cBoxData_inited = true;//下拉条已初始化完毕
}

void tverparamparamDlg::showEvent(QShowEvent * event)
{
	m_config = new QSettings(getFullIniFileName("tverparamconfig.ini"), QSettings::IniFormat);
	initCmbBox();
	readConfig();//读取上次设置参数
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