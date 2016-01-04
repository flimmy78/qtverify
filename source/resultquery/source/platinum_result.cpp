#include <QtSql/QSqlRelationalDelegate>
#include <QtCore/QDebug>

#include "platinum_result.h"
#include "qtexdb.h"

PlaResultDlg::PlaResultDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	model = new QSqlRelationalTableModel(this, g_defaultdb);
}

PlaResultDlg::~PlaResultDlg()
{

}

void PlaResultDlg::showEvent(QShowEvent *)
{
	initCmb();
}

void PlaResultDlg::closeEvent(QCloseEvent *)
{
	emit signalClosed();
}

void PlaResultDlg::initCmb()
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

	ui.startDateTime->setDateTime(QDateTime::currentDateTime().addDays(-7));//��ȥһ��
	ui.endDateTime->setDateTime(QDateTime::currentDateTime());
}

void PlaResultDlg::on_btnQuery_clicked()
{
	getCondition();
	queryData();
}

void PlaResultDlg::getCondition()
{
	m_conStr.clear();
	int method = ui.cmbMethod->currentIndex();
	m_conStr.append(QString("F_CompOrParam = %1 ").arg(QString::number(method)));
	m_conStr.append( QString(" and F_TimeStamp>=\'%1\' and F_TimeStamp<=\'%2\'").arg(ui.startDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))\
		.arg(ui.endDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))); //��ֹʱ��
	int idx, count;
	int not_select = 0;
	not_select = ~not_select;

	idx = ui.cmbManufactDept->currentIndex();
	count = ui.cmbManufactDept->count();
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
	if (!ui.lnEditMeterNO->text().isEmpty())//���
	{
		m_conStr.append(QString(" and F_MeterNo like \"\%%1\%\"").arg(ui.lnEditMeterNO->text()));
	}
}

void PlaResultDlg::queryData()
{
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //���Ա仯ʱд�����ݿ�
	model->setTable("T_Platinum_Verify_Record");
	model->setFilter(m_conStr); //���ò�ѯ����

	//�������
	model->setRelation(4, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setRelation(5, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model->setRelation(6, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setRelation(7, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setRelation(8, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setRelation(9, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));

	//����ˮƽ����
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("PlaManufactDept"));//������������
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("Standard"));//����
	model->setHeaderData(5, Qt::Horizontal, QObject::tr("Model"));//���ͺ�
	model->setHeaderData(6, Qt::Horizontal, QObject::tr("ManufactDept"));//����
	model->setHeaderData(7, Qt::Horizontal, QObject::tr("VerifyDept"));//�ͼ����
	model->setHeaderData(8, Qt::Horizontal, QObject::tr("CheckPerson"));//����Ա
	model->setHeaderData(9, Qt::Horizontal, QObject::tr("VerifyPerson"));//����Ա
	model->setHeaderData(10, Qt::Horizontal, QObject::tr("MinTmpDiff"));//��С�²�
	model->setHeaderData(11, Qt::Horizontal, QObject::tr("TmpDiff"));//����²�ֵ
	model->setHeaderData(12, Qt::Horizontal, QObject::tr("StdModel"));//��׼�¶ȼ��ͺ�
	model->setHeaderData(13, Qt::Horizontal, QObject::tr("StdInRresis"));//��׼�¶ȼƽ��ڵ���ֵ
	model->setHeaderData(14, Qt::Horizontal, QObject::tr("StdOutRresis"));//��׼�¶ȼƳ��ڵ���ֵ
	model->setHeaderData(15, Qt::Horizontal, QObject::tr("StdInTmp"));//��׼�¶ȼƽ����¶�ֵ
	model->setHeaderData(16, Qt::Horizontal, QObject::tr("StdOutTmp"));//��׼�¶ȼƳ����¶�ֵ
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("PlaSerial"));//���
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("PlaInRresis"));//���첬������ڵ���ֵ
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("PlaOutRresis"));//���첬������ڵ���ֵ
	model->setHeaderData(20, Qt::Horizontal, QObject::tr("PlaInTmp"));//���첬��������¶�ֵ
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("PlaOutTmp"));//���첬��������¶�ֵ
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("PlaTmpDiffErr"));//���첬����������¶Ȳ�����ֵ
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("PlaParamR0"));//���첬����0�����ֵ
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("PlaCoeA"));//���첬����ϵ��A
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("PlaCoeB"));//���첬����ϵ��B
	model->setHeaderData(26, Qt::Horizontal, QObject::tr("PlaCoeC"));//���첬����ϵ��C
	model->setHeaderData(27, Qt::Horizontal, QObject::tr("InErr"));//���첬����������(��)
	model->setHeaderData(28, Qt::Horizontal, QObject::tr("OutErr"));//���첬����������(��)
	model->setHeaderData(29, Qt::Horizontal, QObject::tr("DeltaErrLimit"));//���첬����������²�������(%)
	model->setHeaderData(30, Qt::Horizontal, QObject::tr("InErrLimit"));//���첬������������(��)
	model->setHeaderData(31, Qt::Horizontal, QObject::tr("OutErrLimit"));//���첬������������(��)
	model->setHeaderData(32, Qt::Horizontal, QObject::tr("verify_seq"));//�ڼ��μ춨
	model->setHeaderData(33, Qt::Horizontal, QObject::tr("TmpIndex"));//�²������


	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //�п������Ӧ
	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //����ֶ�ֻ�������е������б༭
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //ʹ�䲻�ɱ༭

	ui.tableView->hideColumn(0);
	ui.tableView->hideColumn(1);
	ui.tableView->hideColumn(2);
}

void PlaResultDlg::on_btnExit_clicked()
{
	this->close();
}