/***********************************************
**  �ļ���:     queryresult.cpp
**  ����:       ��ѯ�춨���(SQLITE3)
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/8/8
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/08 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:  
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

	QStringList drivers = QSqlDatabase::drivers();
	foreach(QString driver, drivers)
	{
		qDebug()<<driver;
	}

	initUiData();
}

QueryResult::~QueryResult()
{

}

//
void QueryResult::initUiData()
{
	//���쵥λ
	int col_id1 = 0;
	QSqlRelationalTableModel *model1 = new QSqlRelationalTableModel(this);  
	model1->setTable(tr("T_Manufacture_Dept"));  
	model1->setRelation(col_id1, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel1 = model1->relationModel(col_id1);   
	ui.cmbManufactDept->setModel(relationModel1);  
	ui.cmbManufactDept->setModelColumn(relationModel1->fieldIndex("F_Desc")); 
	ui.cmbManufactDept->insertItem(ui.cmbManufactDept->count(), "");
	ui.cmbManufactDept->setCurrentIndex(ui.cmbManufactDept->count()-1);

	//�ͼ쵥λ
	int col_id2 = 0;
	QSqlRelationalTableModel *model2 = new QSqlRelationalTableModel(this);  
	model2->setTable(tr("T_Verify_Dept"));  
	model2->setRelation(col_id2, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel2 = model2->relationModel(col_id2);   
	ui.cmbVerifyDept->setModel(relationModel2);  
	ui.cmbVerifyDept->setModelColumn(relationModel2->fieldIndex("F_Desc")); 
	ui.cmbVerifyDept->insertItem(ui.cmbVerifyDept->count(), "");
	ui.cmbVerifyDept->setCurrentIndex(ui.cmbVerifyDept->count()-1);

	//�춨Ա
	int col_id3 = 0;
	QSqlRelationalTableModel *model3 = new QSqlRelationalTableModel(this);  
	model3->setTable(tr("T_User_Def_Tab"));  
	model3->setRelation(col_id3, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));  
	QSqlTableModel *relationModel3 = model3->relationModel(col_id3);   
	ui.cmbVerifyPerson->setModel(relationModel3);  
	ui.cmbVerifyPerson->setModelColumn(relationModel3->fieldIndex("F_Desc")); 
	ui.cmbVerifyPerson->insertItem(ui.cmbVerifyPerson->count(), "");
	ui.cmbVerifyPerson->setCurrentIndex(ui.cmbVerifyPerson->count()-1);

	ui.startDateTime->setDateTime(QDateTime::currentDateTime().addDays(-7));//��ȥһ��
	ui.endDateTime->setDateTime(QDateTime::currentDateTime());
}

//��ѯ�춨���
void QueryResult::on_btnQuery_clicked()
{
	QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //���Ա仯ʱд�����ݿ�
	model->setTable("T_Verify_Record");

	QString conStr;
	conStr = QString("F_TimeStamp>=\'%1\' and F_TimeStamp<=\'%2\'").arg(ui.startDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))\
		.arg(ui.endDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz")); //��ֹʱ��
	if (ui.cmbManufactDept->currentIndex() != (ui.cmbManufactDept->count()-1))//���쵥λ
	{
		conStr.append(QString(" and F_ManufactDept=%1").arg(ui.cmbManufactDept->currentIndex()));
	}
	if (ui.cmbVerifyDept->currentIndex() != (ui.cmbVerifyDept->count()-1))//�ͼ쵥λ
	{
		conStr.append(QString(" and F_VerifyDept=%1").arg(ui.cmbVerifyDept->currentIndex()));
	}
	if (ui.cmbVerifyPerson->currentIndex() != (ui.cmbVerifyPerson->count()-1))//�춨Ա
	{
		conStr.append(QString(" and F_VerifyPerson=%1").arg(ui.cmbVerifyPerson->currentIndex()));
	}
	model->setFilter(conStr);
	
	model->setRelation(19, QSqlRelation("T_Yes_No_Tab","F_ID","F_Desc"));
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("�ϸ��־"));
	model->setRelation(21, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("�ͺ�"));
	//��T_Verify_Record��ĵ�22��������ΪT_Meter_Standard���id���Ե��������������ʾΪt_meter_standard���name���Ե�ֵ
	model->setRelation(22, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("���"));
	model->setRelation(23, QSqlRelation("T_Meter_Type","F_ID","F_Desc"));
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("������"));
	model->setRelation(24, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("���쵥λ"));
	model->setRelation(25, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("�ͼ쵥λ"));
	model->setRelation(27, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setHeaderData(27, Qt::Horizontal, QObject::tr("�춨Ա"));
	model->setRelation(28, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setHeaderData(28, Qt::Horizontal, QObject::tr("����Ա"));

	model->setHeaderData(1, Qt::Horizontal, QObject::tr("ʱ��"));
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("���"));
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("������"));
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("����"));
	model->setHeaderData(5, Qt::Horizontal, QObject::tr("�����춨��־"));
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("���"));
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("�ϸ��׼"));

	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //�п������Ӧ
 	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //����ֶ�ֻ�������е������б༭
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //ʹ�䲻�ɱ༭
// 	ui.tableView->hideColumn(0);

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
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
	db.transaction(); //����������
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
    db.commit(); //�ύ���񣬴�ʱ���������ļ�ִ��SQL���
	endTime = QDateTime::currentDateTime();
	qDebug()<<"  end time is:"<<endTime.toString("yyMMddhhmmss");
	int usedSec = statTime.msecsTo(endTime);
	qDebug()<<"Insert"<<ui.spinBoxNums->value()<<"record��"<<"used time is:"<<usedSec<<"micro seconds\n";
}

void QueryResult::on_btnStop_clicked()
{
	m_count = 1;
	qDebug()<<"on_btnStop_clicked, m_count ="<<m_count;
}