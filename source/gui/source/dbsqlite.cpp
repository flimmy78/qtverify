#include <QtGui/QMessageBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QTextEdit>

#include "dbsqlite.h"


DbSqlite::DbSqlite(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	dbsqliteui.setupUi(this);

// 	connect(dbsqliteui.btnConnect, SIGNAL(clicked()), this, SLOT(on_btnConnect_clicked()));
// 	connect(dbsqliteui.btnQuery, SIGNAL(clicked()), this, SLOT(on_btnQuery_clicked()));
// 	connect(dbsqliteui.btnOK, SIGNAL(clicked()), this, SLOT(on_btnOK_clicked()));

	dbsqliteui.btnQuery->setEnabled(false);
	dbsqliteui.btnOK->setEnabled(false);
}

DbSqlite::~DbSqlite()
{

}

void DbSqlite::on_btnConnect_clicked()
{
	char dbname[100];
	sprintf_s(dbname, "%s/database/mysqlite375.db", getenv("RUNHOME"));
	db = QSqlDatabase::addDatabase("QSQLITE"); // ʹ��sqlite���ݿ����� 
	db.setDatabaseName(dbname);
	bool ok = db.open(); // �����������ݿ�

	if(ok) // �ɹ��������ݿ�
	{
		QMessageBox::information(this, "DbShow", "connect sqlite database success !", "Ok", "Cancel");	
		dbsqliteui.btnQuery->setEnabled(true);
		dbsqliteui.btnOK->setEnabled(true);
	}
	else
	{
		QMessageBox::information(this, "DbShow", "connect sqlite database failed !", "Ok", "Cancel");	
		dbsqliteui.btnQuery->setEnabled(false);
		dbsqliteui.btnOK->setEnabled(false);
	}
}

void DbSqlite::on_btnQuery_clicked()
{
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	if(query.exec("select * from employee")) // �����г� employee ������м�¼
	{
		// ���β�ѯ�ɹ�
		int numRows = 0;
		QString id, lname, fname, phone; QDateTime dob; 
		dbsqliteui.display->append("==========================================="); 
		dbsqliteui.display->append(QString::fromLocal8Bit(" id | ���� | ���� | �绰")); 
		dbsqliteui.display->append("--------------------------------------");
		while(query.next())// ��λ�������һ����¼
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
	else  // �����ѯʧ�ܣ�������ķ����õ��������ݿⷵ�ص�ԭ��
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