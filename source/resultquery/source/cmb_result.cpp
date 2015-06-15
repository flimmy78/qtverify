#include <QtSql/QSqlRelationalDelegate>
#include <QtCore/QDebug>
#include "cmb_result.h"

CmbResultDlg::CmbResultDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	model = new QSqlRelationalTableModel(this);

	QStringList drivers = QSqlDatabase::drivers();
	foreach(QString driver, drivers)
	{
		qDebug()<<driver;
	}
}

CmbResultDlg::~CmbResultDlg()
{

}

void CmbResultDlg::showEvent(QShowEvent *)
{
	initCmb();
}

void CmbResultDlg::closeEvent(QCloseEvent *)
{

}

void CmbResultDlg::initCmb()
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

void CmbResultDlg::on_btnQuery_clicked()
{
	getCondition();
	queryData();
}

void CmbResultDlg::getCondition()
{
	m_conStr.clear();

	m_conStr.append( QString(" F_TimeStamp>=\'%1\' and F_TimeStamp<=\'%2\'").arg(ui.startDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))\
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
	idx = ui.cmbVerifyDept->currentIndex();
	count = ui.cmbVerifyDept->count();
	if (idx != (count-1) && idx != not_select)//送检单位
	{
		m_conStr.append(QString(" and F_VerifyDept=%1").arg(ui.cmbVerifyDept->currentIndex()));
	}
	idx = ui.cmbVerifyPerson->currentIndex();
	count = ui.cmbVerifyPerson->count();
	if (idx != (count-1) && idx != not_select)//检定员
	{
		m_conStr.append(QString(" and F_VerifyPerson=%1").arg(ui.cmbVerifyPerson->currentIndex()));
	}
	if (!ui.lnEditMeterNO->text().isEmpty())//表号
	{
		m_conStr.append(QString(" and F_MeterNo like \"\%%1\%\"").arg(ui.lnEditMeterNO->text()));
	}
}

void CmbResultDlg::queryData()
{
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //属性变化时写入数据库
	model->setTable("T_Combined_Verify_Record");
	model->setFilter(m_conStr); //设置查询条件

	////设置外键
	model->setRelation(3, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setRelation(4, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model->setRelation(6, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setRelation(7, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setRelation(8, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setRelation(26, QSqlRelation("T_Yes_No_Tab","F_ID","F_Desc"));

	////设置水平标题
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("TimeStamp"));//时间戳（'yyyy-MM-dd HH:mm:ss.zzz')
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("MeterNo"));//表号(14位数字: 6 + 8)
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("Standard"));//表规格(DN15/DN20/DN25)，外键(T_Meter_Standard.F_ID)
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("Model"));//表型号，外键(T_Meter_Model.F_ID)
	model->setHeaderData(5, Qt::Horizontal, QObject::tr("Grade"));//计量等级（1,2,3）
	model->setHeaderData(6, Qt::Horizontal, QObject::tr("ManufactDept"));//制造单位，外键(T_Manufacture_Dept.F_ID)
	model->setHeaderData(7, Qt::Horizontal, QObject::tr("VerifyDept"));//送检单位，外键(T_Verify_Dept.F_ID)
	model->setHeaderData(8, Qt::Horizontal, QObject::tr("VerifyPerson"));//检定员，外键(T_User_Def_Tab.F_ID)
	model->setHeaderData(9, Qt::Horizontal, QObject::tr("DeltaTemp "));//温差(K)
	model->setHeaderData(10, Qt::Horizontal, QObject::tr("VerifyVolume "));//检定量(L)
	model->setHeaderData(11, Qt::Horizontal, QObject::tr("DeltaTempMin "));//最小温差(K)
	model->setHeaderData(12, Qt::Horizontal, QObject::tr("InstallPos"));//安装位置(0:进口；1:出口)
	model->setHeaderData(13, Qt::Horizontal, QObject::tr("HeatUnit"));//热量单位(1:kWh; 0:MJ)
	model->setHeaderData(14, Qt::Horizontal, QObject::tr("StdTempIn"));//入口温度-标准温度计(℃)
	model->setHeaderData(15, Qt::Horizontal, QObject::tr("StdTempOut"));//出口温度-标准温度计(℃)
	model->setHeaderData(16, Qt::Horizontal, QObject::tr("StdResistIn"));//入口电阻-标准温度计(Ω)
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("StdResistOut"));//出口电阻-标准温度计(Ω)
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("Kcoe"));//K系数
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("StdValue"));//理论值(热量，kwh)
	model->setHeaderData(20, Qt::Horizontal, QObject::tr("MeterV0"));//热量表初值(体积)，单位L
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("MeterV1"));//热量表终值(体积)，单位L
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("MeterE0"));//热量表初值(热量)，单位kWh
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("MeterE1"));//热量表终值(热量)，单位kWh
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("DispError"));//示值误差，单位%
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("StdError"));//要求误差(合格标准),单位%
	model->setHeaderData(26, Qt::Horizontal, QObject::tr("Result"));//检定结果(1：合格，0：不合格)

	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //列宽度自适应
	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //外键字段只能在已有的数据中编辑
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //使其不可编辑

	ui.tableView->hideColumn(0);
	ui.tableView->hideColumn(1);
	ui.tableView->hideColumn(27);
	ui.tableView->hideColumn(28);
	ui.tableView->hideColumn(29);
}

void CmbResultDlg::on_btnExit_clicked()
{
	this->close();
}