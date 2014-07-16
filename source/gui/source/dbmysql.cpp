#include <QtGui/QMessageBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QTextEdit>

#include "dbmysql.h"


DbMySql::DbMySql(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	dbmysqlui.setupUi(this);

	dbmysqlui.btnQuery->setEnabled(false);
}

DbMySql::~DbMySql()
{

}

void DbMySql::on_btnConnect_clicked()
{
	db = QSqlDatabase::addDatabase("QMYSQL"); // ʹ��mysql���ݿ����� 
	db.setHostName("localhost");
	db.setDatabaseName("dbs1"); // ����֮ǰ���������ݿ�
	db.setUserName("xopens"); // ���Ǵ����� xopens �û���
	db.setPassword("ytdf000"); // xopens �û�������
	bool ok = db.open(); // �����������ݿ�
// 	db.exec("SET NAMES 'GB2312'");
	if(ok) // ������xopens�Ѿ��ɹ��������ݿ�
	{
		QMessageBox::information(this, "DbShow", "connect mysql database success !", "Ok", "Cancel");	
		dbmysqlui.btnQuery->setEnabled(true);
	}
	else
	{
		QMessageBox::information(this, "DbShow", "connect mysql database failed !", "Ok", "Cancel");	
		dbmysqlui.btnQuery->setEnabled(false);
	}
}

void DbMySql::on_btnQuery_clicked()
{
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	if(query.exec("select * from employee")) // �����г� employee ������м�¼
	{
		// ���β�ѯ�ɹ�
		int numRows = 0; // ѯ�����ݿ��������Ƿ���������ĳ������ 
		if(db.driver()->hasFeature(QSqlDriver::QuerySize))
		{
			numRows = query.size(); // ���֧�ֽ��Ӱ�����������ôֱ�Ӽ�¼����
		}
		else
		{
			query.last(); //����λ��������qt �ĵ�˵����������ǳ���
			numRows = query.at() + 1;
		}
		QString id, lname, fname, phone; QDateTime dob; 
		dbmysqlui.display->append("==========================================="); 
		dbmysqlui.display->append(QString::fromLocal8Bit(" id | ���� | ���� | �绰")); 
		dbmysqlui.display->append("--------------------------------------");
		while(query.next())// ��λ�������һ����¼
		{ 
			id = query.value(0).toString();
			lname = QString::fromLocal8Bit(query.value(1).toByteArray());
			fname = QString::fromLocal8Bit(query.value(2).toByteArray());
			dob = query.value(3).toDateTime();
			phone = QString::fromLocal8Bit(query.value(4).toByteArray());
			QString result = id + " " + fname + lname + " " + (dob.toString()) + " "+phone;
			dbmysqlui.display->append(result); 
		}
		dbmysqlui.display->append("============================================");
		dbmysqlui.display->append(QString("totally %1 rows").arg( numRows) );
	}
	else  // �����ѯʧ�ܣ�������ķ����õ��������ݿⷵ�ص�ԭ��
	{
		QSqlError error = query.lastError();
		dbmysqlui.display->append("From mysql database: " + error.databaseText());
	}
}