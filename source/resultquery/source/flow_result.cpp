/***********************************************
**  文件名:     flowresult.cpp
**  功能:       查询流量检定结果(SQLITE3)
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/3/2
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2015/03 第一版
**  内容包含:
**  说明:
**  更新记录:  
***********************************************/

#include <QtGui/QMessageBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QTextEdit>
#include <QtCore/QDebug>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlIndex>
#include <QtSql/QSqlRelationalDelegate>
#include <QtGui/QFileDialog>
#include <QtCore/QProcessEnvironment>
#include <QAxObject>

#include "flow_result.h"
#include "qexcel.h"
#include "qtexdb.h"
#include "report.h"

FlowResultDlg::FlowResultDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	m_count = 0;

	model = new QSqlRelationalTableModel(this);
/*
	QStringList drivers = QSqlDatabase::drivers();
	foreach(QString driver, drivers)
	{
		qDebug()<<driver;
	}
*/
	initUiData();

	ui.btnInsert->hide();
	ui.btnStop->hide();
	ui.spinBoxNums->hide();
}

FlowResultDlg::~FlowResultDlg()
{

}

void FlowResultDlg::initUiData()
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

	//表型号
	int col_id4 = 0;
	QSqlRelationalTableModel *model4 = new QSqlRelationalTableModel(this);  
	model4->setTable("T_Meter_Model");  
	model4->setRelation(col_id4, QSqlRelation("T_Meter_Model","F_ID","F_Name"));  
	QSqlTableModel *relationModel4 = model4->relationModel(col_id4);   
	ui.cmbModel->setModel(relationModel4);  
	ui.cmbModel->setModelColumn(relationModel4->fieldIndex("F_Name")); 
	ui.cmbModel->insertItem(ui.cmbModel->count(), "");
	ui.cmbModel->setCurrentIndex(ui.cmbModel->count()-1);

	//表规格
	int col_id5 = 0;
	QSqlRelationalTableModel *model5 = new QSqlRelationalTableModel(this);  
	model5->setTable("T_Meter_Standard");  
	model5->setRelation(col_id5, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));  
	QSqlTableModel *relationModel5 = model5->relationModel(col_id5);   
	ui.cmbStandard->setModel(relationModel5);  
	ui.cmbStandard->setModelColumn(relationModel5->fieldIndex("F_Name")); 
	ui.cmbStandard->insertItem(ui.cmbStandard->count(), "");
	ui.cmbStandard->setCurrentIndex(ui.cmbStandard->count()-1);

	//表等级
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "1");
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "2");
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "3");
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "");
	ui.cmbGrade->setCurrentIndex(ui.cmbGrade->count()-1);

	//是否合格
	ui.cmbIsValid->setCurrentIndex(ui.cmbIsValid->count()-1);

	ui.startDateTime->setDateTime(QDateTime::currentDateTime().addSecs(-3600) );//过去一小时
	ui.endDateTime->setDateTime(QDateTime::currentDateTime());
}

//查询检定结果
void FlowResultDlg::on_btnQuery_clicked()
{
	getCondition();
	queryData();
/*	QString tbname = model->tableName();
	QString fdname1 = model->record(0).fieldName(0);
	QString pkname = model->primaryKey().name();
	int cnt = model->primaryKey().count();
	QString pkname1 = model->primaryKey().fieldName(0);
	int rowcount = model->rowCount();
	int pmId = model->primaryKey().value(0).toUInt();
	int colCount = model->columnCount();
*/
}

void FlowResultDlg::getCondition()
{
	m_conStr.clear();
	m_conStr = QString("F_TimeStamp>=\'%1\' and F_TimeStamp<=\'%2\'").arg(ui.startDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))\
		.arg(ui.endDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz")); //起止时间

	int method = ui.cmbMethod->currentIndex();//质量法还是标准表法
	m_conStr.append(QString(" and F_MethodFlag = %1").arg(method));

	int idx, count;
	idx = ui.cmbManufactDept->currentIndex();
	count = ui.cmbManufactDept->count();

	int not_select = 0;
	not_select = ~not_select;
	if (idx != (count-1))//制造单位
	{
		m_conStr.append(QString(" and F_ManufactDept=%1").arg(ui.cmbManufactDept->currentIndex()));
	}
	idx = ui.cmbVerifyDept->currentIndex();
	count = ui.cmbVerifyDept->count();
	if (idx != (count-1))//送检单位
	{
		m_conStr.append(QString(" and F_VerifyDept=%1").arg(ui.cmbVerifyDept->currentIndex()));
	}
	idx = ui.cmbVerifyPerson->currentIndex();
	count = ui.cmbVerifyPerson->count();
	if (idx != (count-1))//检定员
	{
		m_conStr.append(QString(" and F_VerifyPerson=%1").arg(ui.cmbVerifyPerson->currentIndex()));
	}
	
	idx = ui.cmbFlowPointIdx->currentIndex();
	if (idx > 0)//流量点
	{
		m_conStr.append(QString(" and F_FlowPointIdx=%1").arg(ui.cmbFlowPointIdx->currentIndex()));
	}

	idx = ui.cmbMeterPos->currentIndex();
	if (idx > 0)//表位号
	{
		m_conStr.append(QString(" and F_MeterPosNo=%1").arg(ui.cmbMeterPos->currentIndex()));
	}

	idx = ui.cmbModel->currentIndex();
	count = ui.cmbModel->count();
	if (idx != (count-1))//表型号
	{
		m_conStr.append(QString(" and F_Model=%1").arg(ui.cmbModel->currentIndex()));
	}

	idx = ui.cmbStandard->currentIndex();
	count = ui.cmbStandard->count();
	if (idx != (count-1))//表规格
	{
		m_conStr.append(QString(" and F_Standard=%1").arg(ui.cmbStandard->currentIndex()));
	}

	idx = ui.cmbGrade->currentIndex();
	count = ui.cmbGrade->count();
	if (idx != (count-1))//表等级
	{
		m_conStr.append(QString(" and F_Grade=%1").arg(ui.cmbGrade->currentIndex()+1));
	}

	idx = ui.cmbIsValid->currentIndex();
	count = ui.cmbIsValid->count();
	if (idx != (count-1))//是否合格
	{
		m_conStr.append(QString(" and F_Result=%1").arg(ui.cmbIsValid->currentIndex()));
	}

	if (!ui.lnEditMeterNO->text().isEmpty())//表号
	{
		m_conStr.append(QString(" and F_MeterNo like \"\%%1\%\"").arg(ui.lnEditMeterNO->text()));
	}
}

void FlowResultDlg::queryData()
{
	//model->setEditStrategy(QSqlTableModel::OnFieldChange); //属性变化时写入数据库
	model->setTable("T_Flow_Verify_Record");
	model->setFilter(m_conStr); //设置查询条件
	
	//设置外键
	model->setRelation(17, QSqlRelation("T_Yes_No_Tab","F_ID","F_Desc"));
	model->setRelation(19, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model->setRelation(20, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setRelation(21, QSqlRelation("T_Meter_PickCode","F_ID","F_Desc"));
	model->setRelation(22, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setRelation(23, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setRelation(25, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setRelation(26, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));

	//设置水平标题
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("time"));//时间
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("MeterNO."));//表号
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("FlowPoint"));//流量点
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("Flow"));//流量
	model->setHeaderData(5, Qt::Horizontal, QObject::tr("Method"));//检定方法 0:质量法；1:标准表法
	model->setHeaderData(6, Qt::Horizontal, QObject::tr("MeterValue0"));//热表初值
	model->setHeaderData(7, Qt::Horizontal, QObject::tr("MeterValue1"));//热表终值
	model->setHeaderData(8, Qt::Horizontal, QObject::tr("BalValue0"));//天平初值
	model->setHeaderData(9, Qt::Horizontal, QObject::tr("BalValue1"));//天平终值
	model->setHeaderData(10, Qt::Horizontal, QObject::tr("F_StdMeterV0"));//标准表初值
	model->setHeaderData(11, Qt::Horizontal, QObject::tr("F_StdMeterV1"));//标准表终值
	model->setHeaderData(12, Qt::Horizontal, QObject::tr("PipeTemp"));//管路温度
	model->setHeaderData(13, Qt::Horizontal, QObject::tr("Density"));//密度
	model->setHeaderData(14, Qt::Horizontal, QObject::tr("StdValue"));//标准值
	model->setHeaderData(15, Qt::Horizontal, QObject::tr("Error"));//误差
	model->setHeaderData(16, Qt::Horizontal, QObject::tr("StdError"));//合格标准
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("Result"));//合格标志
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("MeterPosNO."));//表位号
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("Model"));//型号
	model->setHeaderData(20, Qt::Horizontal, QObject::tr("Standard"));//规格
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("PickCode"));//采集代码
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("ManufactDept"));//制造单位
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("VerifyDept"));//送检单位
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("Grade"));//计量等级
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("VerifyPerson"));//检定员
	model->setHeaderData(26, Qt::Horizontal, QObject::tr("CheckPerson"));//核验员
	model->setHeaderData(27, Qt::Horizontal, QObject::tr("DeviceInfoId"));//设备信息ID
	model->setHeaderData(28, Qt::Horizontal, QObject::tr("VerifyDate"));//检定日期
	model->setHeaderData(29, Qt::Horizontal, QObject::tr("ValidDate"));//有效期
	model->setHeaderData(30, Qt::Horizontal, QObject::tr("EnvTemp"));//环境温度
	model->setHeaderData(31, Qt::Horizontal, QObject::tr("EnvHumidity"));//环境湿度
	model->setHeaderData(32, Qt::Horizontal, QObject::tr("AirPressure"));//气压
	model->setHeaderData(33, Qt::Horizontal, QObject::tr("CertNO"));//检定证书编号
	model->setHeaderData(34, Qt::Horizontal, QObject::tr("FlowCoe"));//流量系数
	
	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //列宽度自适应
	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //外键字段只能在已有的数据中编辑
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //使其不可编辑

	ui.tableView->hideColumn(0);

	int method = ui.cmbMethod->currentIndex();
	if (method)
	{
		ui.tableView->showColumn(10);
		ui.tableView->showColumn(11);
	}
	else
	{
		ui.tableView->hideColumn(10);
		ui.tableView->hideColumn(11);
	}
	ui.tableView->hideColumn(35);
	ui.tableView->hideColumn(36);
	ui.tableView->hideColumn(37);
}

void FlowResultDlg::on_btnStop_clicked()
{
	m_count = 1;
	qDebug()<<"on_btnStop_clicked, m_count ="<<m_count;
}

void FlowResultDlg::on_btnExport_clicked()
{
	if (NULL==model)
	{
		QMessageBox::warning(this, tr("Warning"), tr("no data need to be exported!"));
		return;
	}

	QString defaultPath = QProcessEnvironment::systemEnvironment().value("ADEHOME") + "//report//" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
	QString file = QFileDialog::getSaveFileName(this, tr("Save File"), defaultPath, tr("Microsoft Excel (*.xls)"));//获取保存路径
	if (!file.isEmpty())
	{
		getCondition();
		CReport rpt(m_conStr);
		rpt.setIniName("rptconfig_flow.ini");
		rpt.writeRpt();
		rpt.saveTo(file);
		QMessageBox::information(this, tr("OK"), tr("export excel file successful!"));
	}
}

void FlowResultDlg::on_btnExit_clicked()
{
	this->close();
}