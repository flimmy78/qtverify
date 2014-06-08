#include <QtGui/QMessageBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QTextEdit>
#include <QDebug>

#include "dbsqlite.h"


DbSqlite::DbSqlite(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	dbsqliteui.setupUi(this);

	dbsqliteui.btnQuery->setEnabled(false);
	dbsqliteui.btnOK->setEnabled(false);
	dbsqliteui.btnInsert->setEnabled(false);

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
		dbsqliteui.btnQuery->setEnabled(true);
		dbsqliteui.btnOK->setEnabled(true);
		dbsqliteui.btnInsert->setEnabled(true);
	}
	else
	{
		QMessageBox::information(this, "DbShow", "connect sqlite database failed !", "Ok", "Cancel");	
		dbsqliteui.btnQuery->setEnabled(false);
		dbsqliteui.btnOK->setEnabled(false);
		dbsqliteui.btnInsert->setEnabled(false);
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
		dbsqliteui.display->append("==========================================="); 
		dbsqliteui.display->append(QString::fromLocal8Bit(" id | 姓名 | 生日 | 电话")); 
		dbsqliteui.display->append("--------------------------------------");
		while(query.next())// 定位结果到下一条记录
		{ 
			id = query.value(0).toString();
			lname = QString::fromLocal8Bit(query.value(1).toByteArray());
			fname = QString::fromLocal8Bit(query.value(2).toByteArray());
			dob = query.value(3).toDateTime();
			phone = QString::fromLocal8Bit(query.value(4).toByteArray());
			QString result = id + " " + fname + lname + " " + (dob.toString()) + " "+phone;
			dbsqliteui.display->append(result); 

			numRows ++;
		}
		dbsqliteui.display->append("============================================");
		dbsqliteui.display->append(QString("totally %1 rows").arg( numRows) );
	}
	else  // 如果查询失败，用下面的方法得到具体数据库返回的原因
	{
		QSqlError error = query.lastError();
		dbsqliteui.display->append("From sqlite database: " + error.databaseText());
	}
}

void DbSqlite::on_btnOK_clicked()
{
	QSqlTableModel *model = new QSqlTableModel(this, db);
	model->setTable("employee");
	model->select();
	dbsqliteui.tableView->setModel(model);
}

void DbSqlite::on_btnInsert_clicked()
{
	QDateTime statTime = QDateTime::currentDateTime();
	qDebug()<<"start time is:"<<statTime.toString("yyMMddhhmmss");
	QDateTime endTime;
	int sucNum=0, failNum=0;
	QSqlQuery query;
	m_count = dbsqliteui.spinBoxNums->value();
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
	qDebug()<<"Insert"<<dbsqliteui.spinBoxNums->value()<<"record； success"<<sucNum<<"； failed"<<failNum<<"。used time is:"<<usedSec<<"micro seconds\n";
}

void DbSqlite::on_btnStop_clicked()
{
	m_count = 1;
	qDebug()<<"on_btnStop_clicked, m_count ="<<m_count;
}

