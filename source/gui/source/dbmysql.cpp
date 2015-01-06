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


	//Qt��ʽ����DLL begin
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
	//Qt��ʽ����DLL end
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
	m_db = QSqlDatabase::addDatabase("QMYSQL"); // ʹ��mysql���ݿ����� 
	m_db.setHostName("localhost");
	m_db.setDatabaseName("dbs1"); // ����֮ǰ���������ݿ�
	m_db.setUserName("xopens"); // ���Ǵ����� xopens �û���
	m_db.setPassword("ytdf000"); // xopens �û�������
	bool ok = m_db.open(); // �����������ݿ�
// 	m_db.exec("SET NAMES 'GB2312'");
	if(ok) // ������xopens�Ѿ��ɹ��������ݿ�
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
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	if(query.exec("select * from employee")) // �����г� employee ������м�¼
	{
		// ���β�ѯ�ɹ�
		int numRows = 0; // ѯ�����ݿ��������Ƿ���������ĳ������ 
		if(m_db.driver()->hasFeature(QSqlDriver::QuerySize))
		{
			numRows = query.size(); // ���֧�ֽ��Ӱ�����������ôֱ�Ӽ�¼����
		}
		else
		{
			query.last(); //����λ��������qt �ĵ�˵����������ǳ���
			numRows = query.at() + 1;
		}
		QString id, lname, fname, phone; QDateTime dob; 
		ui.display->append("==========================================="); 
		ui.display->append(QString::fromLocal8Bit(" id | name | birthday | telephone")); 
		ui.display->append("--------------------------------------");
		while(query.next())// ��λ�������һ����¼
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
	else  // �����ѯʧ�ܣ�������ķ����õ��������ݿⷵ�ص�ԭ��
	{
		QSqlError error = query.lastError();
		ui.display->append("From mysql database: " + error.databaseText());
	}
}