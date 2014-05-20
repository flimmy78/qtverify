#include <QtGui/QMessageBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QTextEdit>

#include "dbshow.h"


DbShow::DbShow(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	dbshowui.setupUi(this);

	connect(dbshowui.conMySqlBtn, SIGNAL(clicked()), this, SLOT(slotConnectMySqlDataBase()));
	connect(dbshowui.QueryBtn, SIGNAL(clicked()), this, SLOT(slotQueryData()));
	dbshowui.QueryBtn->setEnabled(false);

}

DbShow::~DbShow()
{

}

void DbShow::slotConnectMySqlDataBase()
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
		dbshowui.QueryBtn->setEnabled(true);
	}
	else
	{
		QMessageBox::information(this, "DbShow", "connect mysql database failed !", "Ok", "Cancel");	
		dbshowui.QueryBtn->setEnabled(false);
	}
}

void DbShow::slotQueryData()
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
		dbshowui.display->append("==========================================="); 
		dbshowui.display->append(QString::fromLocal8Bit(" id | ���� | ���� | �绰")); 
		dbshowui.display->append("--------------------------------------");
		while(query.next())// ��λ�������һ����¼
		{ 
			id = query.value(0).toString();
			lname = QString::fromLocal8Bit(query.value(1).toByteArray());
			fname = QString::fromLocal8Bit(query.value(2).toByteArray());
			dob = query.value(3).toDateTime();
			phone = QString::fromLocal8Bit(query.value(4).toByteArray());
			QString result = id + " " + fname + lname + " " + (dob.toString()) + " "+phone;
			dbshowui.display->append(result); 
		}
		dbshowui.display->append("============================================");
		dbshowui.display->append(QString("totally %1 rows").arg( numRows) );
	}
	else  // �����ѯʧ�ܣ�������ķ����õ��������ݿⷵ�ص�ԭ��
	{
		QSqlError error = query.lastError();
		dbshowui.display->append("From mysql database: " + error.databaseText());
	}
}