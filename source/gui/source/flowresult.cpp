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

#include "flowresult.h"
#include "qexcel.h"


FlowResultDlg::FlowResultDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	m_count = 0;

	model = new QSqlRelationalTableModel(this);

	QStringList drivers = QSqlDatabase::drivers();
	foreach(QString driver, drivers)
	{
		qDebug()<<driver;
	}

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

	ui.startDateTime->setDateTime(QDateTime::currentDateTime().addDays(-7));//��ȥһ��
	ui.endDateTime->setDateTime(QDateTime::currentDateTime());
}

//��ѯ�춨���
void FlowResultDlg::on_btnQuery_clicked()
{
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //���Ա仯ʱд�����ݿ�
	model->setTable("T_Flow_Verify_Record");
	
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
	if (!ui.lnEditMeterNO->text().isEmpty())//���
	{
		conStr.append(QString(" and F_MeterNo like \"\%%1\%\"").arg(ui.lnEditMeterNO->text()));
	}

	model->setFilter(conStr); //���ò�ѯ����
	
	//�������
	model->setRelation(17, QSqlRelation("T_Yes_No_Tab","F_ID","F_Desc"));
	model->setRelation(19, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	//��T_Verify_Record��ĵ�20��������ΪT_Meter_Standard���F_ID���Ե��������������ʾΪT_Meter_Standard���F_Name���Ե�ֵ
	model->setRelation(20, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setRelation(21, QSqlRelation("T_Meter_Type","F_ID","F_Desc"));
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
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("MeterType"));//������
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

	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //�п������Ӧ
 	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //����ֶ�ֻ�������е������б༭
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //ʹ�䲻�ɱ༭

 	ui.tableView->hideColumn(0);
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

	QString defaultPath = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "//dat";
	QString file = QFileDialog::getSaveFileName(this, tr("Save File"), defaultPath, tr("Microsoft Excel (*.xlsx;*.xls)"));//��ȡ����·��
	if (!file.isEmpty())
	{
		QAxObject *excel = new QAxObject(this);
		excel->setControl("Excel.Application");//����Excel�ؼ�
		excel->dynamicCall("SetVisible (bool Visible)","false");//����ʾ����
		excel->setProperty("DisplayAlerts", false);//����ʾ�κξ�����Ϣ�����Ϊtrue��ô�ڹر�ʱ��������ơ��ļ����޸ģ��Ƿ񱣴桱����ʾ

		QAxObject *workbooks = excel->querySubObject("WorkBooks");//��ȡ����������
		workbooks->dynamicCall("Add");//�½�һ��������
		QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//��ȡ��ǰ������
		//������filepath��ע��һ��Ҫ��QDir::toNativeSeparators��·���е�"/"ת��Ϊ"\"����Ȼһ�����治�ˡ�
		workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(file));
		workbook->dynamicCall("Close()");//�رչ�����
		excel->dynamicCall("Quit()");//�ر�excel
		delete excel;
		excel=NULL;

		QString preStr = "";
		QExcel xlsFile(file);	
		xlsFile.selectSheet(1);//����һ�Ź�����
		for (int j=0; j<model->columnCount(); j++)
		{
			if (j==1 || j==2) //ʱ����ͱ����
			{
				preStr = "'";
			}
			else
			{
				preStr = "";
			}
			xlsFile.setCellString(1, j+1, model->headerData(j, Qt::Horizontal).toString()); //������
			for(int i=0;i<model->rowCount();i++)
			{
				xlsFile.setCellString(i+2, j+1, preStr+model->data(model->index(i,j)).toString());
			}
// 			xlsFile.setAutoFitColumn(j+1);
		}
		xlsFile.setAutoFitColumnAll();
		xlsFile.save();

		QMessageBox::information(this, tr("OK"), tr("export excel file successful!"));
	}
}

void FlowResultDlg::on_btnExit_clicked()
{
	this->close();
}


