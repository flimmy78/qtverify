#include <QtSql/QSqlRelationalDelegate>
#include <QtCore/QDebug>
#include "calculator_result.h"

CalcResultDlg::CalcResultDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	model = new QSqlRelationalTableModel(this);
}

CalcResultDlg::~CalcResultDlg()
{

}

void CalcResultDlg::showEvent(QShowEvent *)
{
	initCmb();
}

void CalcResultDlg::closeEvent(QCloseEvent *)
{

}

void CalcResultDlg::initCmb()
{
	//制造单位
	int col_id1 = 0;
	QSqlRelationalTableModel *model1 = new QSqlRelationalTableModel(this);  
	model1->setTable("T_Manufacture_Dept");  
	model1->setRelation(col_id1, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel1 = model1->relationModel(col_id1);   
	ui.cmbManufactDept->setModel(relationModel1);  
	ui.cmbManufactDept->setModelColumn(relationModel1->fieldIndex("F_Desc")); 
	ui.cmbManufactDept->insertItem(ui.cmbManufactDept->count(), "");
	ui.cmbManufactDept->setCurrentIndex(ui.cmbManufactDept->count()-1);

	//送检单位
	int col_id2 = 0;
	QSqlRelationalTableModel *model2 = new QSqlRelationalTableModel(this);  
	model2->setTable("T_Verify_Dept");  
	model2->setRelation(col_id2, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel2 = model2->relationModel(col_id2);   
	ui.cmbVerifyDept->setModel(relationModel2);  
	ui.cmbVerifyDept->setModelColumn(relationModel2->fieldIndex("F_Desc")); 
	ui.cmbVerifyDept->insertItem(ui.cmbVerifyDept->count(), "");
	ui.cmbVerifyDept->setCurrentIndex(ui.cmbVerifyDept->count()-1);

	//检定员
	int col_id3 = 0;
	QSqlRelationalTableModel *model3 = new QSqlRelationalTableModel(this);  
	model3->setTable("T_User_Def_Tab");  
	model3->setRelation(col_id3, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));  
	QSqlTableModel *relationModel3 = model3->relationModel(col_id3);   
	ui.cmbVerifyPerson->setModel(relationModel3);  
	ui.cmbVerifyPerson->setModelColumn(relationModel3->fieldIndex("F_Desc")); 
	ui.cmbVerifyPerson->insertItem(ui.cmbVerifyPerson->count(), "");
	ui.cmbVerifyPerson->setCurrentIndex(ui.cmbVerifyPerson->count()-1);

	ui.startDateTime->setDateTime(QDateTime::currentDateTime().addDays(-7));//过去一周
	ui.endDateTime->setDateTime(QDateTime::currentDateTime());
}

void CalcResultDlg::on_btnQuery_clicked()
{
	getCondition();
	queryData();
}

void CalcResultDlg::getCondition()
{
	m_conStr.clear();
	m_conStr.append( QString("F_TimeStamp>=\'%1\' and F_TimeStamp<=\'%2\'").arg(ui.startDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))\
		.arg(ui.endDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))); //起止时间
	int idx, count;
	idx = ui.cmbManufactDept->currentIndex();
	count = ui.cmbManufactDept->count();

	int not_select = 0;
	not_select = ~not_select;
	if (idx != (count-1) && idx != not_select)//制造单位
	{
		m_conStr.append(QString(" and F_ManufactDept=%1").arg(ui.cmbManufactDept->currentIndex()));
	}

	idx = ui.cmbVerifyDept->currentIndex();//送检单位
	count = ui.cmbVerifyDept->count();
	if (idx != (count-1) && idx != not_select)
	{
		m_conStr.append(QString(" and F_VerifyDept=%1").arg(ui.cmbVerifyDept->currentIndex()));
	}

	idx = ui.cmbVerifyPerson->currentIndex();//检定员
	count = ui.cmbVerifyPerson->count();
	if (idx != (count-1) && idx != not_select)
	{
		m_conStr.append(QString(" and F_VerifyPerson=%1").arg(ui.cmbVerifyPerson->currentIndex()));
	}

	idx = ui.cmbAlgorithm->currentIndex();//算法
	count = ui.cmbAlgorithm->count();
	if (idx != (count-1) && idx != not_select)
	{
		m_conStr.append(QString(" and F_Algorithm=%1").arg(ui.cmbAlgorithm->currentIndex()));
	}

	idx = ui.cmbInstallPos->currentIndex();//安装位置
	count = ui.cmbInstallPos->count();
	if (idx != (count-1) && idx != not_select)
	{
		m_conStr.append(QString(" and F_InstallPos=%1").arg(ui.cmbInstallPos->currentIndex()));
	}

	if (!ui.lnEditMeterNO->text().isEmpty())//表号
	{
		m_conStr.append(QString(" and F_MeterNo like \"\%%1\%\"").arg(ui.lnEditMeterNO->text()));
	}
}

void CalcResultDlg::queryData()
{
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //属性变化时写入数据库
	model->setTable("T_Calc_Verify_Record");
	model->setFilter(m_conStr); //设置查询条件

	//设置外键
	model->setRelation(4, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setRelation(5, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model->setRelation(7, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setRelation(8, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setRelation(9, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));

	//设置水平标题
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("timestamp"));
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("MeterNo"));
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("deltaTIdx")); //温差点索引
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("Standard"));
	model->setHeaderData(5, Qt::Horizontal, QObject::tr("Model"));
	model->setHeaderData(6, Qt::Horizontal, QObject::tr("Grade"));
	model->setHeaderData(7, Qt::Horizontal, QObject::tr("ManufactDept"));
	model->setHeaderData(8, Qt::Horizontal, QObject::tr("VerifyDept"));
	model->setHeaderData(9, Qt::Horizontal, QObject::tr("VerifyPerson"));
	model->setHeaderData(10, Qt::Horizontal, QObject::tr("TempMax"));
	model->setHeaderData(11, Qt::Horizontal, QObject::tr("TempMin"));
	model->setHeaderData(12, Qt::Horizontal, QObject::tr("DeltaTempMax"));
	model->setHeaderData(13, Qt::Horizontal, QObject::tr("DeltaTempMin"));
	model->setHeaderData(14, Qt::Horizontal, QObject::tr("algorithm"));
	model->setHeaderData(15, Qt::Horizontal, QObject::tr("InstallPos"));
	model->setHeaderData(16, Qt::Horizontal, QObject::tr("HeatUnit"));
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("StdTempIn"));
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("StdTempOut"));
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("StdResistIn"));
	model->setHeaderData(20, Qt::Horizontal, QObject::tr("StdResistOut"));
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("RecomVolume"));
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("SimulateVolume"));
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("Kcoe"));
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("StdEnergy"));
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("MeterE0"));
	model->setHeaderData(26, Qt::Horizontal, QObject::tr("MeterE1"));
	model->setHeaderData(27, Qt::Horizontal, QObject::tr("DispError"));
	model->setHeaderData(28, Qt::Horizontal, QObject::tr("StdError"));
	model->setHeaderData(29, Qt::Horizontal, QObject::tr("Result"));

	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //列宽度自适应
	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //外键字段只能在已有的数据中编辑
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //使其不可编辑

	ui.tableView->hideColumn(0);
	ui.tableView->hideColumn(30);
	ui.tableView->hideColumn(31);
	ui.tableView->hideColumn(32);
}

void CalcResultDlg::on_btnExit_clicked()
{
	this->close();
}