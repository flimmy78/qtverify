#include <QtGui/QMessageBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QTextEdit>
#include <QDebug>
#include <QLibrary>

#include "dbmysql.h"


DbMySql::DbMySql(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	ui.btnQuery->setEnabled(false);


	//Qt显式加载DLL begin
	typedef void(*FUN1)();  
	typedef int(*FUN2)(int, int);  

	QLibrary lib("qtexdb.dll");  
	if (lib.load()) 
	{  
		qDebug() << "load dll ok!";  

		FUN1 hello = (FUN1)lib.resolve("hello");  
		FUN2 add = (FUN2)lib.resolve("testFunc");  
		if (hello) {  
			qDebug() << "load hello ok!";  
			hello();  
		}  
		if (add) {  
			qDebug() << "load add ok!";  
			qDebug() << add(3, 5);  
		}  
	} 
	else 
	{  
		qDebug() << "load error!";  
	} 
	//Qt显式加载DLL end
}

DbMySql::~DbMySql()
{
}

void DbMySql::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^DbMySql::closeEvent";
	if (m_db.isOpen())
	{
		m_db.close();
	}
}

void DbMySql::on_btnConnect_clicked()
{
	m_db = QSqlDatabase::addDatabase("QMYSQL"); // 使用mysql数据库驱动 
	m_db.setHostName("localhost");
	m_db.setDatabaseName("dbs1"); // 我们之前建立的数据库
	m_db.setUserName("xopens"); // 我们创建的 xopens 用户名
	m_db.setPassword("ytdf000"); // xopens 用户的密码
	bool ok = m_db.open(); // 尝试连接数据库
// 	m_db.exec("SET NAMES 'GB2312'");
	if(ok) // 这里用xopens已经成功连上数据库
	{
		QMessageBox::information(this, tr("OK"), tr("connect MySQL database success !"));	
		ui.btnQuery->setEnabled(true);
	}
	else
	{
		QMessageBox::warning(this, "Warning", "connect MySQL database failed !");	
		ui.btnQuery->setEnabled(false);
	}
}

void DbMySql::on_btnQuery_clicked()
{
	QSqlQuery query; // 新建一个查询的实例
	if(query.exec("select * from employee")) // 尝试列出 employee 表的所有记录
	{
		// 本次查询成功
		int numRows = 0; // 询问数据库驱动，是否驱动含有某种特性 
		if(m_db.driver()->hasFeature(QSqlDriver::QuerySize))
		{
			numRows = query.size(); // 如果支持结果影响的行数，那么直接记录下来
		}
		else
		{
			query.last(); //否则定位到结果最后，qt 文档说，这个方法非常慢
			numRows = query.at() + 1;
		}
		QString id, lname, fname, phone; QDateTime dob; 
		ui.display->append("==========================================="); 
		ui.display->append(QString::fromLocal8Bit(" id | name | birthday | telephone")); 
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
		}
		ui.display->append("============================================");
		ui.display->append(QString("totally %1 rows").arg( numRows) );
	}
	else  // 如果查询失败，用下面的方法得到具体数据库返回的原因
	{
		QSqlError error = query.lastError();
		ui.display->append("From mysql database: " + error.databaseText());
	}
}