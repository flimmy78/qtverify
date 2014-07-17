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
	db = QSqlDatabase::addDatabase("QSQLITE"); // ʹ��sqlite���ݿ����� 
	db.setDatabaseName(dbname);
	bool ok = db.open(); // �����������ݿ�

	if(ok) // �ɹ��������ݿ�
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
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	if(query.exec("select * from employee")) // �����г� employee ������м�¼
	{
		// ���β�ѯ�ɹ�
		int numRows = 0;
		QString id, lname, fname, phone; QDateTime dob; 
		ui.display->append("==========================================="); 
		ui.display->append(QString::fromLocal8Bit(" id | ���� | ���� | �绰")); 
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

			numRows ++;
		}
		ui.display->append("============================================");
		ui.display->append(QString("totally %1 rows").arg( numRows) );
	}
	else  // �����ѯʧ�ܣ�������ķ����õ��������ݿⷵ�ص�ԭ��
	{
		QSqlError error = query.lastError();
		ui.display->append("From sqlite database: " + error.databaseText());
	}
}

void DbSqlite::on_btnOK_clicked()
{
	QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this, db);
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //���Ա仯ʱд�����ݿ�
	model->setTable("t_verify_record");
	//��t_verify_record��ĵ�18��������Ϊt_meter_standard���id���Ե��������������ʾΪt_meter_standard���name���Ե�ֵ
	model->setRelation(17, QSqlRelation("t_meter_standard","id","name"));
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("���"));
	model->setRelation(18, QSqlRelation("t_meter_type","id","desc"));
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("������"));
	model->setRelation(19, QSqlRelation("t_manufacture_tab","id","desc"));
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("��������"));
	model->select();
	ui.tableView->setModel(model);
//	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //ʹ�䲻�ɱ༭

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
	qDebug()<<"Insert"<<ui.spinBoxNums->value()<<"record�� success"<<sucNum<<"�� failed"<<failNum<<"��used time is:"<<usedSec<<"micro seconds\n";
}

void DbSqlite::on_btnStop_clicked()
{
	m_count = 1;
	qDebug()<<"on_btnStop_clicked, m_count ="<<m_count;
}

