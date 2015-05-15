#include <QtSql/QSqlRelationalDelegate>
#include <QtCore/QDebug>
#include "platinum_result.h"

PlaResultDlg::PlaResultDlg(QWidget *parent, Qt::WFlags flags)
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

PlaResultDlg::~PlaResultDlg()
{

}

void PlaResultDlg::showEvent(QShowEvent *)
{
	initCmb();
	m_conStr = "select * from T_Platinum_Verify_Record";
}

void PlaResultDlg::closeEvent(QCloseEvent *)
{

}

void PlaResultDlg::initCmb()
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

void PlaResultDlg::on_btnQuery_clicked()
{
	getCondition();
	queryData();
}

void PlaResultDlg::getCondition()
{
	m_conStr.clear();
	int method = ui.cmbMethod->currentIndex();
	m_conStr.append(QString("F_CompOrParam = %1 ").arg(QString::number(method)));
	m_conStr.append( QString(" and F_TimeStamp>=\'%1\' and F_TimeStamp<=\'%2\'").arg(ui.startDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))\
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

void PlaResultDlg::queryData()
{
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //属性变化时写入数据库
	model->setTable("T_Platinum_Verify_Record");
	model->setFilter(m_conStr); //设置查询条件

	//设置外键
	model->setRelation(4, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setRelation(5, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model->setRelation(6, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setRelation(7, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setRelation(8, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setRelation(9, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));

	//设置水平标题
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("PlaManufactDept"));//铂电阻生产商
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("Standard"));//表规格
	model->setHeaderData(5, Qt::Horizontal, QObject::tr("Model"));//表型号
	model->setHeaderData(6, Qt::Horizontal, QObject::tr("ManufactDept"));//表厂商
	model->setHeaderData(7, Qt::Horizontal, QObject::tr("VerifyDept"));//送检机构
	model->setHeaderData(8, Qt::Horizontal, QObject::tr("CheckPerson"));//检验员
	model->setHeaderData(9, Qt::Horizontal, QObject::tr("VerifyPerson"));//复检员
	model->setHeaderData(10, Qt::Horizontal, QObject::tr("MinTmpDiff"));//最小温差
	model->setHeaderData(11, Qt::Horizontal, QObject::tr("TmpDiff"));//检测温差值
	model->setHeaderData(12, Qt::Horizontal, QObject::tr("StdModel"));//标准温度计型号
	model->setHeaderData(13, Qt::Horizontal, QObject::tr("StdInRresis"));//标准温度计进口电阻值
	model->setHeaderData(14, Qt::Horizontal, QObject::tr("StdOutRresis"));//标准温度计出口电阻值
	model->setHeaderData(15, Qt::Horizontal, QObject::tr("StdInTmp"));//标准温度计进口温度值
	model->setHeaderData(16, Qt::Horizontal, QObject::tr("StdOutTmp"));//标准温度计出口温度值
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("PlaSerial"));//表号
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("PlaInRresis"));//被检铂电阻进口电阻值
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("PlaOutRresis"));//被检铂电阻出口电阻值
	model->setHeaderData(20, Qt::Horizontal, QObject::tr("PlaInTmp"));//被检铂电阻进口温度值
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("PlaOutTmp"));//被检铂电阻出口温度值
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("PlaTmpDiffErr"));//被检铂电阻进出口温度差的误差值
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("PlaParamR0"));//被检铂电阻0℃电阻值
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("PlaCoeA"));//被检铂电阻系数A
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("PlaCoeB"));//被检铂电阻系数B
	model->setHeaderData(26, Qt::Horizontal, QObject::tr("PlaCoeC"));//被检铂电阻系数C
	model->setHeaderData(27, Qt::Horizontal, QObject::tr("InErr"));//被检铂电阻进口误差(℃)
	model->setHeaderData(28, Qt::Horizontal, QObject::tr("OutErr"));//被检铂电阻出口误差(℃)
	model->setHeaderData(29, Qt::Horizontal, QObject::tr("DeltaErrLimit"));//被检铂电阻进出口温差的误差限(%)
	model->setHeaderData(30, Qt::Horizontal, QObject::tr("InErrLimit"));//被检铂电阻进口误差限(℃)
	model->setHeaderData(31, Qt::Horizontal, QObject::tr("OutErrLimit"));//被检铂电阻出口误差限(℃)
	model->setHeaderData(32, Qt::Horizontal, QObject::tr("verify_seq"));//第几次检定
	model->setHeaderData(33, Qt::Horizontal, QObject::tr("TmpIndex"));//温差点索引


	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //列宽度自适应
	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //外键字段只能在已有的数据中编辑
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //使其不可编辑

	ui.tableView->hideColumn(0);
	ui.tableView->hideColumn(1);
	ui.tableView->hideColumn(2);
}

void PlaResultDlg::on_btnExit_clicked()
{
	this->close();
}