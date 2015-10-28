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
#include <QtSql/QSqlField>
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

	model = new QSqlRelationalTableModel(this, g_defaultdb);
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
	QSqlRelationalTableModel *model1 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model1->setTable("T_Manufacture_Dept");  
	model1->setRelation(col_id1, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel1 = model1->relationModel(col_id1);   
	ui.cmbManufactDept->setModel(relationModel1);  
	ui.cmbManufactDept->setModelColumn(relationModel1->fieldIndex("F_Desc")); 
	ui.cmbManufactDept->insertItem(ui.cmbManufactDept->count(), "");
	ui.cmbManufactDept->setCurrentIndex(ui.cmbManufactDept->count()-1);

	//�ͼ쵥λ
	int col_id2 = 0;
	QSqlRelationalTableModel *model2 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model2->setTable("T_Verify_Dept");  
	model2->setRelation(col_id2, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel2 = model2->relationModel(col_id2);   
	ui.cmbVerifyDept->setModel(relationModel2);  
	ui.cmbVerifyDept->setModelColumn(relationModel2->fieldIndex("F_Desc")); 
	ui.cmbVerifyDept->insertItem(ui.cmbVerifyDept->count(), "");
	ui.cmbVerifyDept->setCurrentIndex(ui.cmbVerifyDept->count()-1);

	//�춨Ա
	int col_id3 = 0;
	QSqlRelationalTableModel *model3 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model3->setTable("T_User_Def_Tab");  
	model3->setRelation(col_id3, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));  
	QSqlTableModel *relationModel3 = model3->relationModel(col_id3);   
	ui.cmbVerifyPerson->setModel(relationModel3);  
	ui.cmbVerifyPerson->setModelColumn(relationModel3->fieldIndex("F_Desc")); 
	ui.cmbVerifyPerson->insertItem(ui.cmbVerifyPerson->count(), "");
	ui.cmbVerifyPerson->setCurrentIndex(ui.cmbVerifyPerson->count()-1);

	//���ͺ�
	int col_id4 = 0;
	QSqlRelationalTableModel *model4 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model4->setTable("T_Meter_Model");  
	model4->setRelation(col_id4, QSqlRelation("T_Meter_Model","F_ID","F_Name"));  
	QSqlTableModel *relationModel4 = model4->relationModel(col_id4);   
	ui.cmbModel->setModel(relationModel4);  
	ui.cmbModel->setModelColumn(relationModel4->fieldIndex("F_Name")); 
	ui.cmbModel->insertItem(ui.cmbModel->count(), "");
	ui.cmbModel->setCurrentIndex(ui.cmbModel->count()-1);

	//����
	int col_id5 = 0;
	QSqlRelationalTableModel *model5 = new QSqlRelationalTableModel(this, g_defaultdb);  
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

	ui.startDateTime->setDateTime(QDateTime::currentDateTime().addSecs(-3600) );//��ȥһСʱ
	ui.endDateTime->setDateTime(QDateTime::currentDateTime());
}

//��ѯ�춨���
void FlowResultDlg::on_btnQuery_clicked()
{
	getCondition();
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

void FlowResultDlg::getCondition()
{
	m_conStr.clear();
	m_conStr = QString("F_TimeStamp>=\'%1\' and F_TimeStamp<=\'%2\'").arg(ui.startDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))\
		.arg(ui.endDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz")); //��ֹʱ��

	int method = ui.cmbMethod->currentIndex();//���������Ǳ�׼��
	m_conStr.append(QString(" and F_MethodFlag = %1").arg(method));

	int idx, count;
	idx = ui.cmbManufactDept->currentIndex();
	count = ui.cmbManufactDept->count();

	int not_select = 0;
	not_select = ~not_select;
	if (idx != (count-1))//���쵥λ
	{
		m_conStr.append(QString(" and F_ManufactDept=%1").arg(ui.cmbManufactDept->currentIndex()));
	}
	idx = ui.cmbVerifyDept->currentIndex();
	count = ui.cmbVerifyDept->count();
	if (idx != (count-1))//�ͼ쵥λ
	{
		m_conStr.append(QString(" and F_VerifyDept=%1").arg(ui.cmbVerifyDept->currentIndex()));
	}
	idx = ui.cmbVerifyPerson->currentIndex();
	count = ui.cmbVerifyPerson->count();
	if (idx != (count-1))//�춨Ա
	{
		m_conStr.append(QString(" and F_VerifyPerson=%1").arg(ui.cmbVerifyPerson->currentIndex()));
	}
	
	idx = ui.cmbFlowPointIdx->currentIndex();
	if (idx > 0)//������
	{
		m_conStr.append(QString(" and F_FlowPointIdx=%1").arg(ui.cmbFlowPointIdx->currentIndex()));
	}

	idx = ui.cmbMeterPos->currentIndex();
	if (idx > 0)//��λ��
	{
		m_conStr.append(QString(" and F_MeterPosNo=%1").arg(ui.cmbMeterPos->currentIndex()));
	}

	idx = ui.cmbModel->currentIndex();
	count = ui.cmbModel->count();
	if (idx != (count-1))//���ͺ�
	{
		m_conStr.append(QString(" and F_Model=%1").arg(ui.cmbModel->currentIndex()));
	}

	idx = ui.cmbStandard->currentIndex();
	count = ui.cmbStandard->count();
	if (idx != (count-1))//����
	{
		m_conStr.append(QString(" and F_Standard=%1").arg(ui.cmbStandard->currentIndex()));
	}

	idx = ui.cmbGrade->currentIndex();
	count = ui.cmbGrade->count();
	if (idx != (count-1))//��ȼ�
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
	//model->setEditStrategy(QSqlTableModel::OnFieldChange); //���Ա仯ʱд�����ݿ�
	model->setTable("T_Flow_Verify_Record");
	model->setFilter(m_conStr); //���ò�ѯ����
	
	//�������
	model->setRelation(17, QSqlRelation("T_Yes_No_Tab","F_ID","F_Desc"));
	model->setRelation(19, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model->setRelation(20, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setRelation(21, QSqlRelation("T_Meter_PickCode","F_ID","F_Desc"));
	model->setRelation(22, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setRelation(23, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setRelation(25, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setRelation(26, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));

	//����ˮƽ����
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("time"));//ʱ��
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("MeterNO."));//���
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("FlowPoint"));//������
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("Flow"));//����
	model->setHeaderData(5, Qt::Horizontal, QObject::tr("Method"));//�춨���� 0:��������1:��׼��
	model->setHeaderData(6, Qt::Horizontal, QObject::tr("MeterValue0"));//�ȱ��ֵ
	model->setHeaderData(7, Qt::Horizontal, QObject::tr("MeterValue1"));//�ȱ���ֵ
	model->setHeaderData(8, Qt::Horizontal, QObject::tr("BalValue0"));//��ƽ��ֵ
	model->setHeaderData(9, Qt::Horizontal, QObject::tr("BalValue1"));//��ƽ��ֵ
	model->setHeaderData(10, Qt::Horizontal, QObject::tr("F_StdMeterV0"));//��׼���ֵ
	model->setHeaderData(11, Qt::Horizontal, QObject::tr("F_StdMeterV1"));//��׼����ֵ
	model->setHeaderData(12, Qt::Horizontal, QObject::tr("PipeTemp"));//��·�¶�
	model->setHeaderData(13, Qt::Horizontal, QObject::tr("Density"));//�ܶ�
	model->setHeaderData(14, Qt::Horizontal, QObject::tr("StdValue"));//��׼ֵ
	model->setHeaderData(15, Qt::Horizontal, QObject::tr("Error"));//���
	model->setHeaderData(16, Qt::Horizontal, QObject::tr("StdError"));//�ϸ��׼
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("Result"));//�ϸ��־
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("MeterPosNO."));//��λ��
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("Model"));//�ͺ�
	model->setHeaderData(20, Qt::Horizontal, QObject::tr("Standard"));//���
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("PickCode"));//�ɼ�����
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("ManufactDept"));//���쵥λ
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("VerifyDept"));//�ͼ쵥λ
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("Grade"));//�����ȼ�
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("VerifyPerson"));//�춨Ա
	model->setHeaderData(26, Qt::Horizontal, QObject::tr("CheckPerson"));//����Ա
	model->setHeaderData(27, Qt::Horizontal, QObject::tr("DeviceInfoId"));//�豸��ϢID
	model->setHeaderData(28, Qt::Horizontal, QObject::tr("VerifyDate"));//�춨����
	model->setHeaderData(29, Qt::Horizontal, QObject::tr("ValidDate"));//��Ч��
	model->setHeaderData(30, Qt::Horizontal, QObject::tr("EnvTemp"));//�����¶�
	model->setHeaderData(31, Qt::Horizontal, QObject::tr("EnvHumidity"));//����ʪ��
	model->setHeaderData(32, Qt::Horizontal, QObject::tr("AirPressure"));//��ѹ
	model->setHeaderData(33, Qt::Horizontal, QObject::tr("CertNO"));//�춨֤����
	model->setHeaderData(34, Qt::Horizontal, QObject::tr("FlowCoe"));//����ϵ��
	
	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //�п������Ӧ
	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //����ֶ�ֻ�������е������б༭
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //ʹ�䲻�ɱ༭

	ui.tableView->hideColumn(0);

	int method = ui.cmbMethod->currentIndex();
	if (method)
	{
		ui.tableView->showColumn(10);
		ui.tableView->showColumn(11);
	}
	else
	{
		ui.tableView->hideColumn(10);
		ui.tableView->hideColumn(11);
	}
	ui.tableView->hideColumn(35);
	ui.tableView->hideColumn(36);
	ui.tableView->hideColumn(37);
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
	QString defaultPath = QProcessEnvironment::systemEnvironment().value("ADEHOME") + "//report//flow//"+(ui.cmbMethod->currentIndex() ? "std//":"mass//") + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
	QString file = QFileDialog::getSaveFileName(this, tr("Save File"), defaultPath, tr("Microsoft Excel (*.xls)"));//��ȡ����·��
	if (!file.isEmpty())
	{
		try
		{
			getCondition();
			CReport rpt(m_conStr);
			QString iniFileName = ui.cmbMethod->currentIndex() ? "rptconfig_flow_std.ini":"rptconfig_flow_mass.ini";
			rpt.setIniName(iniFileName);
			rpt.writeRpt();
			rpt.saveTo(file);
			QMessageBox::information(this, tr("OK"), tr("export excel file successful!"));
		}
		catch (QString e)
		{
			QMessageBox::warning(this, tr("Error"), e);
		}
	}
}

void FlowResultDlg::on_btnExit_clicked()
{
	this->close();
}

void FlowResultDlg::on_btnImport_clicked()
{
	//�ӱ���SQLite���ݿ��ѯ����
	QSqlQuery query1(g_defaultdb);
	QString sql1 = "select * from T_Flow_Verify_Record where " + m_conStr;
	bool ok1 = query1.exec(sql1);
	if (!ok1) //��ѯʧ��
	{
		QSqlError error = query1.lastError();
		QString err = error.databaseText();
		return; //����
	}
	int rowNum = 0; //��ѯ���ļ�¼����
	if (g_defaultdb.driver()->hasFeature(QSqlDriver::QuerySize))
	{
		rowNum = query1.size();
	}
	else
	{
		query1.last();
		rowNum = query1.at() + 1;
	}
	QSqlRecord rec = query1.record();
	int colNum = rec.count(); //������

	//Զ��MySQL���ݿ�
	QSqlQuery query2(g_mysqldb);
	QString sql2 = "insert into T_Flow_Verify_Record values(";
	int i = 0, j = 0;
	for (i = 0; i < colNum; i++)
	{
		sql2.append("?, ");
	}
	sql2.replace(sql2.size()-2, 1, ")");
	query2.prepare(sql2);

	QVariantList vals2;
	for (int m=0; m<rowNum; m++)
	{
		vals2<<QVariant(QVariant::Int);
	}
	query2.addBindValue(vals2); //F_ID

	for (j = 1; j < colNum; j++) //�ӵڶ���"F_TimeStamp"��ʼ���б���
	{
		QVariantList vals;
		if (query1.first())
		{
			do 
			{
/*				switch (rec.field(j).type())
				{
				case QVariant::String:
					vals<<query1.value(j).toString();
					break;
				case QVariant::Int:
					vals<<query1.value(j).toInt();
					break;
				default:
					vals<<query1.value(j);
					break;
				}*/
				vals<<query1.value(j);
			} while (query1.next());
			query2.addBindValue(vals);
		}
	}
	if (query2.execBatch())
	{

		qDebug()<<"Import from SQLite to MySQL success :"<<rowNum<<"records!";
		QMessageBox::information(this, tr("Import Success"), QString("Import from SQLite to MySQL : %1 records!").arg(rowNum));
	}
	else
	{
		qDebug()<<query2.lastError();
		QMessageBox::information(this, tr("Import Failed"), query2.lastError().databaseText());
	}
}

