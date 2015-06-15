/***********************************************
**  �ļ���:     flowresult.cpp
**  ����:       ��ѯ�����춨���(SQLITE3)
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2015/3/2
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2015/03 ��һ��
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
#include <QtSql/QSqlRelationalDelegate>
#include <QtGui/QFileDialog>
#include <QtCore/QProcessEnvironment>
#include <QAxObject>

#include "flow_result.h"
#include "qexcel.h"
#include "qtexdb.h"
#include "report.h"

FlowResultDlg::FlowResultDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	m_count = 0;

	model = new QSqlRelationalTableModel(this);
/*
	QStringList drivers = QSqlDatabase::drivers();
	foreach(QString driver, drivers)
	{
		qDebug()<<driver;
	}
*/
	initUiData();

	ui.btnInsert->hide();
	ui.btnStop->hide();
	ui.spinBoxNums->hide();
}

FlowResultDlg::~FlowResultDlg()
{

}

void FlowResultDlg::initUiData()
{
	//���쵥λ
	int col_id1 = 0;
	QSqlRelationalTableModel *model1 = new QSqlRelationalTableModel(this);  
	model1->setTable("T_Manufacture_Dept");  
	model1->setRelation(col_id1, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel1 = model1->relationModel(col_id1);   
	ui.cmbManufactDept->setModel(relationModel1);  
	ui.cmbManufactDept->setModelColumn(relationModel1->fieldIndex("F_Desc")); 
	ui.cmbManufactDept->insertItem(ui.cmbManufactDept->count(), "");
	ui.cmbManufactDept->setCurrentIndex(ui.cmbManufactDept->count()-1);

	//�ͼ쵥λ
	int col_id2 = 0;
	QSqlRelationalTableModel *model2 = new QSqlRelationalTableModel(this);  
	model2->setTable("T_Verify_Dept");  
	model2->setRelation(col_id2, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel2 = model2->relationModel(col_id2);   
	ui.cmbVerifyDept->setModel(relationModel2);  
	ui.cmbVerifyDept->setModelColumn(relationModel2->fieldIndex("F_Desc")); 
	ui.cmbVerifyDept->insertItem(ui.cmbVerifyDept->count(), "");
	ui.cmbVerifyDept->setCurrentIndex(ui.cmbVerifyDept->count()-1);

	//�춨Ա
	int col_id3 = 0;
	QSqlRelationalTableModel *model3 = new QSqlRelationalTableModel(this);  
	model3->setTable("T_User_Def_Tab");  
	model3->setRelation(col_id3, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));  
	QSqlTableModel *relationModel3 = model3->relationModel(col_id3);   
	ui.cmbVerifyPerson->setModel(relationModel3);  
	ui.cmbVerifyPerson->setModelColumn(relationModel3->fieldIndex("F_Desc")); 
	ui.cmbVerifyPerson->insertItem(ui.cmbVerifyPerson->count(), "");
	ui.cmbVerifyPerson->setCurrentIndex(ui.cmbVerifyPerson->count()-1);

	//���ͺ�
	int col_id4 = 0;
	QSqlRelationalTableModel *model4 = new QSqlRelationalTableModel(this);  
	model4->setTable("T_Meter_Model");  
	model4->setRelation(col_id4, QSqlRelation("T_Meter_Model","F_ID","F_Name"));  
	QSqlTableModel *relationModel4 = model4->relationModel(col_id4);   
	ui.cmbModel->setModel(relationModel4);  
	ui.cmbModel->setModelColumn(relationModel4->fieldIndex("F_Name")); 
	ui.cmbModel->insertItem(ui.cmbModel->count(), "");
	ui.cmbModel->setCurrentIndex(ui.cmbModel->count()-1);

	//����
	int col_id5 = 0;
	QSqlRelationalTableModel *model5 = new QSqlRelationalTableModel(this);  
	model5->setTable("T_Meter_Standard");  
	model5->setRelation(col_id5, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));  
	QSqlTableModel *relationModel5 = model5->relationModel(col_id5);   
	ui.cmbStandard->setModel(relationModel5);  
	ui.cmbStandard->setModelColumn(relationModel5->fieldIndex("F_Name")); 
	ui.cmbStandard->insertItem(ui.cmbStandard->count(), "");
	ui.cmbStandard->setCurrentIndex(ui.cmbStandard->count()-1);

	//��ȼ�
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "1");
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "2");
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "3");
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "");
	ui.cmbGrade->setCurrentIndex(ui.cmbGrade->count()-1);

	//�Ƿ�ϸ�
	ui.cmbIsValid->setCurrentIndex(ui.cmbIsValid->count()-1);

	ui.startDateTime->setDateTime(QDateTime::currentDateTime().addDays(-7));//��ȥһ��
	ui.endDateTime->setDateTime(QDateTime::currentDateTime());
}

//��ѯ�춨���
void FlowResultDlg::on_btnQuery_clicked()
{
	getConditon();
	queryData();
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

void FlowResultDlg::getConditon()
{
	m_conStr.clear();
	m_conStr = QString("F_TimeStamp>=\'%1\' and F_TimeStamp<=\'%2\'").arg(ui.startDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))\
		.arg(ui.endDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz")); //��ֹʱ��

	int method = ui.cmbMethod->currentIndex();
	m_conStr.append(QString(" and F_MethodFlag = %1").arg(method));

	int idx, count;
	idx = ui.cmbManufactDept->currentIndex();
	count = ui.cmbManufactDept->count();

	int not_select = 0;
	not_select = ~not_select;
	if (idx != (count-1) && idx != not_select)//���쵥λ
	{
		m_conStr.append(QString(" and F_ManufactDept=%1").arg(ui.cmbManufactDept->currentIndex()));
	}
	idx = ui.cmbVerifyDept->currentIndex();
	count = ui.cmbVerifyDept->count();
	if (idx != (count-1) && idx != not_select)//�ͼ쵥λ
	{
		m_conStr.append(QString(" and F_VerifyDept=%1").arg(ui.cmbVerifyDept->currentIndex()));
	}
	idx = ui.cmbVerifyPerson->currentIndex();
	count = ui.cmbVerifyPerson->count();
	if (idx != (count-1) && idx != not_select)//�춨Ա
	{
		m_conStr.append(QString(" and F_VerifyPerson=%1").arg(ui.cmbVerifyPerson->currentIndex()));
	}
	
	idx = ui.cmbFlowPointIdx->currentIndex();
	if (idx > 0)//������
	{
		m_conStr.append(QString(" and F_FlowPointIdx=%1").arg(ui.cmbFlowPointIdx->currentIndex()));
	}

	idx = ui.cmbModel->currentIndex();
	count = ui.cmbModel->count();
	if (idx != (count-1) && idx != not_select)//���ͺ�
	{
		m_conStr.append(QString(" and F_Model=%1").arg(ui.cmbModel->currentIndex()));
	}

	idx = ui.cmbStandard->currentIndex();
	count = ui.cmbStandard->count();
	if (idx != (count-1) && idx != not_select)//����
	{
		m_conStr.append(QString(" and F_Standard=%1").arg(ui.cmbStandard->currentIndex()));
	}

	idx = ui.cmbGrade->currentIndex();
	count = ui.cmbGrade->count();
	if (idx != (count-1) && idx != not_select)//��ȼ�
	{
		m_conStr.append(QString(" and F_Grade=%1").arg(ui.cmbGrade->currentIndex()+1));
	}

	idx = ui.cmbIsValid->currentIndex();
	count = ui.cmbIsValid->count();
	if (idx != (count-1))//�Ƿ�ϸ�
	{
		m_conStr.append(QString(" and F_Result=%1").arg(ui.cmbIsValid->currentIndex()));
	}

	if (!ui.lnEditMeterNO->text().isEmpty())//���
	{
		m_conStr.append(QString(" and F_MeterNo like \"\%%1\%\"").arg(ui.lnEditMeterNO->text()));
	}
}

void FlowResultDlg::queryData()
{
	QSqlRelationalTableModel *model1 = new QSqlRelationalTableModel(this);
	model1->setEditStrategy(QSqlTableModel::OnFieldChange); //���Ա仯ʱд�����ݿ�
	model1->setTable("T_Flow_Verify_Record");
	model1->setFilter(m_conStr); //���ò�ѯ����
	
	//�������
	model1->setRelation(17, QSqlRelation("T_Yes_No_Tab","F_ID","F_Desc"));
	model1->setRelation(19, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model1->setRelation(20, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model1->setRelation(21, QSqlRelation("T_Meter_PickCode","F_ID","F_Desc"));
	model1->setRelation(22, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model1->setRelation(23, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model1->setRelation(25, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model1->setRelation(26, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));

	//����ˮƽ����
	model1->setHeaderData(1, Qt::Horizontal, QObject::tr("time"));//ʱ��
	model1->setHeaderData(2, Qt::Horizontal, QObject::tr("MeterNO."));//���
	model1->setHeaderData(3, Qt::Horizontal, QObject::tr("FlowPoint"));//������
	model1->setHeaderData(4, Qt::Horizontal, QObject::tr("Flow"));//����
	model1->setHeaderData(5, Qt::Horizontal, QObject::tr("Method"));//�춨���� 0:��������1:��׼��
	model1->setHeaderData(6, Qt::Horizontal, QObject::tr("MeterValue0"));//�ȱ��ֵ
	model1->setHeaderData(7, Qt::Horizontal, QObject::tr("MeterValue1"));//�ȱ���ֵ
	model1->setHeaderData(8, Qt::Horizontal, QObject::tr("BalValue0"));//��ƽ��ֵ
	model1->setHeaderData(9, Qt::Horizontal, QObject::tr("BalValue1"));//��ƽ��ֵ
	model1->setHeaderData(10, Qt::Horizontal, QObject::tr("F_StdMeterV0"));//��׼���ֵ
	model1->setHeaderData(11, Qt::Horizontal, QObject::tr("F_StdMeterV1"));//��׼����ֵ
	model1->setHeaderData(12, Qt::Horizontal, QObject::tr("PipeTemp"));//��·�¶�
	model1->setHeaderData(13, Qt::Horizontal, QObject::tr("Density"));//�ܶ�
	model1->setHeaderData(14, Qt::Horizontal, QObject::tr("StdValue"));//��׼ֵ
	model1->setHeaderData(15, Qt::Horizontal, QObject::tr("Error"));//���
	model1->setHeaderData(16, Qt::Horizontal, QObject::tr("StdError"));//�ϸ��׼
	model1->setHeaderData(17, Qt::Horizontal, QObject::tr("Result"));//�ϸ��־
	model1->setHeaderData(18, Qt::Horizontal, QObject::tr("MeterPosNO."));//��λ��
	model1->setHeaderData(19, Qt::Horizontal, QObject::tr("Model"));//�ͺ�
	model1->setHeaderData(20, Qt::Horizontal, QObject::tr("Standard"));//���
	model1->setHeaderData(21, Qt::Horizontal, QObject::tr("PickCode"));//�ɼ�����
	model1->setHeaderData(22, Qt::Horizontal, QObject::tr("ManufactDept"));//���쵥λ
	model1->setHeaderData(23, Qt::Horizontal, QObject::tr("VerifyDept"));//�ͼ쵥λ
	model1->setHeaderData(24, Qt::Horizontal, QObject::tr("Grade"));//�����ȼ�
	model1->setHeaderData(25, Qt::Horizontal, QObject::tr("VerifyPerson"));//�춨Ա
	model1->setHeaderData(26, Qt::Horizontal, QObject::tr("CheckPerson"));//����Ա
	model1->setHeaderData(27, Qt::Horizontal, QObject::tr("DeviceInfoId"));//�豸��ϢID
	model1->setHeaderData(28, Qt::Horizontal, QObject::tr("VerifyDate"));//�춨����
	model1->setHeaderData(29, Qt::Horizontal, QObject::tr("ValidDate"));//��Ч��
	model1->setHeaderData(30, Qt::Horizontal, QObject::tr("EnvTemp"));//�����¶�
	model1->setHeaderData(31, Qt::Horizontal, QObject::tr("EnvHumidity"));//����ʪ��
	model1->setHeaderData(32, Qt::Horizontal, QObject::tr("AirPressure"));//��ѹ
	model1->setHeaderData(33, Qt::Horizontal, QObject::tr("CertNO"));//�춨֤����
	model1->setHeaderData(34, Qt::Horizontal, QObject::tr("FlowCoe"));//����ϵ��
	//model1->setHeaderData(35, Qt::Horizontal, QObject::tr("Bak1"));//������1
	//model1->setHeaderData(36, Qt::Horizontal, QObject::tr("Bak2"));//������2
	//model1->setHeaderData(37, Qt::Horizontal, QObject::tr("Bak3"));//������3
	model1->select();
	ui.tableView->setModel(model1);
	ui.tableView->resizeColumnsToContents(); //�п������Ӧ
	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //����ֶ�ֻ�������е������б༭
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //ʹ�䲻�ɱ༭

	ui.tableView->hideColumn(0);
	ui.tableView->hideColumn(35);
	ui.tableView->hideColumn(36);
	ui.tableView->hideColumn(37);
}

void FlowResultDlg::on_btnInsert_clicked()
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

void FlowResultDlg::on_btnStop_clicked()
{
	m_count = 1;
	qDebug()<<"on_btnStop_clicked, m_count ="<<m_count;
}

void FlowResultDlg::on_btnExport_clicked()
{
	if (NULL==model)
	{
		QMessageBox::warning(this, tr("Warning"), tr("no data need to be exported!"));
		return;
	}

	QString defaultPath = QProcessEnvironment::systemEnvironment().value("ADEHOME") + "//report//" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
	QString file = QFileDialog::getSaveFileName(this, tr("Save File"), defaultPath, tr("Microsoft Excel (*.xls)"));//��ȡ����·��
	if (!file.isEmpty())
	{
		getConditon();
		startdb();
		CReport rpt(" where " + m_conStr);
		rpt.writeRpt();
		rpt.saveTo(file);
		closedb();
		QMessageBox::information(this, tr("OK"), tr("export excel file successful!"));
	}
}

void FlowResultDlg::on_btnExit_clicked()
{
	this->close();
}


