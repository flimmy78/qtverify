#include <QtGui/QMessageBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QTextEdit>
#include <QtCore/QDebug>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlIndex>
#include <QtSql/QSqlRelationalTableModel>
#include <QtSql/QSqlRelationalDelegate>

#include "dbsqlite.h"


DbSqlite::DbSqlite(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	ui.btnQuery->setEnabled(false);
	ui.btnOK->setEnabled(false);
	ui.btnInsert->setEnabled(false);

	m_count = 0;
}

DbSqlite::~DbSqlite()
{

}

void DbSqlite::on_btnConnect_clicked()
{
	char dbname[100];
	sprintf_s(dbname, "%s/database/mysqlite375.db", getenv("RUNHOME"));
	db = QSqlDatabase::addDatabase("QSQLITE"); // 使用sqlite数据库驱动 
	db.setDatabaseName(dbname);
	bool ok = db.open(); // 尝试连接数据库

	if(ok) // 成功连上数据库
	{
		QMessageBox::information(this, "DbShow", "connect sqlite database success !", "Ok", "Cancel");	
		ui.btnQuery->setEnabled(true);
		ui.btnOK->setEnabled(true);
		ui.btnInsert->setEnabled(true);
	}
	else
	{
		QMessageBox::information(this, "DbShow", "connect sqlite database failed !", "Ok", "Cancel");	
		ui.btnQuery->setEnabled(false);
		ui.btnOK->setEnabled(false);
		ui.btnInsert->setEnabled(false);
	}
}

void DbSqlite::on_btnQuery_clicked()
{
	QSqlQuery query; // 新建一个查询的实例
	if(query.exec("select * from employee")) // 尝试列出 employee 表的所有记录
	{
		// 本次查询成功
		int numRows = 0;
		QString id, lname, fname, phone; QDateTime dob; 
		ui.display->append("==========================================="); 
		ui.display->append(QString::fromLocal8Bit(" id | 姓名 | 生日 | 电话")); 
		ui.display->append("--------------------------------------");
		while(query.next())// 定位结果到下一条记录
		{ 
			id = query.value(0).toString();
			lname = QString::fromLocal8Bit(query.value(1).toByteArray());
			fname = QString::fromLocal8Bit(query.value(2).toByteArray());
			dob = query.value(3).toDateTime();
			phone = QString::fromLocal8Bit(query.value(4).toByteArray());
			QString result = id + " " + fname + lname + " " + (dob.toString()) + " "+phone;
			ui.display->append(result); 

			numRows ++;
		}
		ui.display->append("============================================");
		ui.display->append(QString("totally %1 rows").arg( numRows) );
	}
	else  // 如果查询失败，用下面的方法得到具体数据库返回的原因
	{
		QSqlError error = query.lastError();
		ui.display->append("From sqlite database: " + error.databaseText());
	}
}

void DbSqlite::on_btnOK_clicked()
{
	QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this, db);
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //属性变化时写入数据库
	model->setTable("t_verify_record");
	//将t_verify_record表的第18个属性设为t_meter_standard表的id属性的外键，并将其显示为t_meter_standard表的name属性的值
	model->setRelation(17, QSqlRelation("t_meter_standard","id","name"));
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("规格"));
	model->setRelation(18, QSqlRelation("t_meter_type","id","desc"));
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("表类型"));
	model->setRelation(19, QSqlRelation("t_manufacture_tab","id","desc"));
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("生产厂家"));
	model->select();
	ui.tableView->setModel(model);
//	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //使其不可编辑

	QString tbname = model->tableName();
	QString fdname1 = model->record(0).fieldName(0);
	QString pkname = model->primaryKey().name();
	int cnt = model->primaryKey().count();
	QString pkname1 = model->primaryKey().fieldName(0);
	int rowcount = model->rowCount();
	int pmId = model->primaryKey().value(0).toUInt();
	int colCount = model->columnCount();

 	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView));
}

void DbSqlite::on_btnInsert_clicked()
{
	QDateTime statTime = QDateTime::currentDateTime();
	qDebug()<<"start time is:"<<statTime.toString("yyMMddhhmmss");
	QDateTime endTime;
	int sucNum=0, failNum=0;
	QSqlQuery query;
	m_count = ui.spinBoxNums->value();
	while (m_count--)
	{
		if(query.exec(" INSERT INTO employee VALUES ('001', 'Jordan', 'Michael', '2000-05-18', '5188')")) 
		{
// 			qDebug()<<"insert"<<++sucNum<<"record success!";
			sucNum++;
		}
		else
		{
// 			qDebug()<<"insert"<<++failNum<<"failed!";
			failNum++;
		}
	}
	endTime = QDateTime::currentDateTime();
	qDebug()<<"  end time is:"<<endTime.toString("yyMMddhhmmss");
	int usedSec = statTime.msecsTo(endTime);
	qDebug()<<"Insert"<<ui.spinBoxNums->value()<<"record； success"<<sucNum<<"； failed"<<failNum<<"。used time is:"<<usedSec<<"micro seconds\n";
}

void DbSqlite::on_btnStop_clicked()
{
	m_count = 1;
	qDebug()<<"on_btnStop_clicked, m_count ="<<m_count;
}

