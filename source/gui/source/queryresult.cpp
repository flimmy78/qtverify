/***********************************************
**  文件名:     queryresult.cpp
**  功能:       查询检定结果(SQLITE3)
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/8/8
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/08 第一版
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
#include <QtSql/QSqlRelationalTableModel>
#include <QtSql/QSqlRelationalDelegate>
#include <QtGui/QFileDialog>

#include "queryresult.h"


QueryResult::QueryResult(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	m_count = 0;
// 	ui.btnInsert->setEnabled(false);
// 	ui.btnStop->setEnabled(false);

	QStringList drivers = QSqlDatabase::drivers();
	foreach(QString driver, drivers)
	{
		qDebug()<<driver;
	}
}

QueryResult::~QueryResult()
{

}

void QueryResult::on_btnQuery_clicked()
{
	QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //属性变化时写入数据库
	model->setTable("T_Verify_Record");
	
	model->setRelation(19, QSqlRelation("T_Yes_No_Tab","F_ID","F_Desc"));
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("合格标志"));
	model->setRelation(21, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("型号"));
	//将T_Verify_Record表的第22个属性设为T_Meter_Standard表的id属性的外键，并将其显示为t_meter_standard表的name属性的值
	model->setRelation(22, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("规格"));
	model->setRelation(23, QSqlRelation("T_Meter_Type","F_ID","F_Desc"));
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("表类型"));
	model->setRelation(24, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("制造单位"));
	model->setRelation(25, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("送检单位"));
	model->setRelation(27, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setHeaderData(27, Qt::Horizontal, QObject::tr("检定员"));
	model->setRelation(28, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setHeaderData(28, Qt::Horizontal, QObject::tr("核验员"));


	model->setHeaderData(1, Qt::Horizontal, QObject::tr("时间"));
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("表号"));
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("流量点"));
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("流量"));
	model->setHeaderData(5, Qt::Horizontal, QObject::tr("总量检定标志"));
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("误差"));
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("合格标准"));

	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //列宽度自适应
 	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //外键字段只能在已有的数据中编辑
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //使其不可编辑

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

void QueryResult::on_btnInsert_clicked()
{
	QDateTime statTime = QDateTime::currentDateTime();
	qDebug()<<"start time is:"<<statTime.toString("yyMMddhhmmss");
	QDateTime endTime;
	m_count = ui.spinBoxNums->value();
//  QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
// 	db.transaction(); //开启事务处理
	QSqlQuery q;
	q.prepare("insert into T_Meter_Standard(F_ID,F_Name) values(?, ?)");
	QVariantList ints;
	QVariantList names;
	while (m_count)
	{
		ints << m_count;
		names << QString("DN-%1").arg(m_count);
		m_count--;
	}	
	q.addBindValue(ints);
	q.addBindValue(names);
	if (!q.execBatch())
	{
		qDebug() << q.lastError();
		return;
	}
//  db.commit(); //提交事务，此时才真正打开文件执行SQL语句
	endTime = QDateTime::currentDateTime();
	qDebug()<<"  end time is:"<<endTime.toString("yyMMddhhmmss");
	int usedSec = statTime.msecsTo(endTime);
	qDebug()<<"Insert"<<ui.spinBoxNums->value()<<"record。"<<"used time is:"<<usedSec<<"micro seconds\n";
}

void QueryResult::on_btnStop_clicked()
{
	m_count = 1;
	qDebug()<<"on_btnStop_clicked, m_count ="<<m_count;
}