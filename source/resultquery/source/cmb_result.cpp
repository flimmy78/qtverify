#include <QtSql/QSqlRelationalDelegate>
#include <QtCore/QDebug>
#include "cmb_result.h"

CmbResultDlg::CmbResultDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	model = new QSqlRelationalTableModel(this);
}

CmbResultDlg::~CmbResultDlg()
{

}

void CmbResultDlg::showEvent(QShowEvent *)
{
	initCmb();
}

void CmbResultDlg::closeEvent(QCloseEvent *)
{

}

void CmbResultDlg::initCmb()
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

	ui.startDateTime->setDateTime(QDateTime::currentDateTime().addSecs(-3600));//��ȥһСʱ
	ui.endDateTime->setDateTime(QDateTime::currentDateTime());
}

void CmbResultDlg::on_btnQuery_clicked()
{
	getCondition();
	queryData();
}

void CmbResultDlg::getCondition()
{
	m_conStr.clear();

	m_conStr.append( QString(" F_TimeStamp>=\'%1\' and F_TimeStamp<=\'%2\'").arg(ui.startDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))\
		.arg(ui.endDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))); //��ֹʱ��
	int idx, count;

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

	idx = ui.cmbInstallPos->currentIndex();
	count = ui.cmbInstallPos->count();
	if (idx != (count-1))//��װλ��
	{
		m_conStr.append(QString(" and F_InstallPos=%1").arg(ui.cmbInstallPos->currentIndex()));
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

void CmbResultDlg::queryData()
{
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //���Ա仯ʱд�����ݿ�
	model->setTable("T_Combined_Verify_Record");
	model->setFilter(m_conStr); //���ò�ѯ����

	////�������
	model->setRelation(3, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setRelation(4, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model->setRelation(6, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setRelation(7, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setRelation(8, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setRelation(26, QSqlRelation("T_Yes_No_Tab","F_ID","F_Desc"));

	////����ˮƽ����
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("TimeStamp"));//ʱ�����'yyyy-MM-dd HH:mm:ss.zzz')
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("MeterNo"));//���(14λ����: 6 + 8)
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("Standard"));//����(DN15/DN20/DN25)�����(T_Meter_Standard.F_ID)
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("Model"));//���ͺţ����(T_Meter_Model.F_ID)
	model->setHeaderData(5, Qt::Horizontal, QObject::tr("Grade"));//�����ȼ���1,2,3��
	model->setHeaderData(6, Qt::Horizontal, QObject::tr("ManufactDept"));//���쵥λ�����(T_Manufacture_Dept.F_ID)
	model->setHeaderData(7, Qt::Horizontal, QObject::tr("VerifyDept"));//�ͼ쵥λ�����(T_Verify_Dept.F_ID)
	model->setHeaderData(8, Qt::Horizontal, QObject::tr("VerifyPerson"));//�춨Ա�����(T_User_Def_Tab.F_ID)
	model->setHeaderData(9, Qt::Horizontal, QObject::tr("DeltaTemp "));//�²�(K)
	model->setHeaderData(10, Qt::Horizontal, QObject::tr("VerifyVolume "));//�춨��(L)
	model->setHeaderData(11, Qt::Horizontal, QObject::tr("DeltaTempMin "));//��С�²�(K)
	model->setHeaderData(12, Qt::Horizontal, QObject::tr("InstallPos"));//��װλ��(0:���ڣ�1:����)
	model->setHeaderData(13, Qt::Horizontal, QObject::tr("HeatUnit"));//������λ(1:kWh; 0:MJ)
	model->setHeaderData(14, Qt::Horizontal, QObject::tr("StdTempIn"));//����¶�-��׼�¶ȼ�(��)
	model->setHeaderData(15, Qt::Horizontal, QObject::tr("StdTempOut"));//�����¶�-��׼�¶ȼ�(��)
	model->setHeaderData(16, Qt::Horizontal, QObject::tr("StdResistIn"));//��ڵ���-��׼�¶ȼ�(��)
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("StdResistOut"));//���ڵ���-��׼�¶ȼ�(��)
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("Kcoe"));//Kϵ��
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("StdValue"));//����ֵ(������kwh)
	model->setHeaderData(20, Qt::Horizontal, QObject::tr("MeterV0"));//�������ֵ(���)����λL
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("MeterV1"));//��������ֵ(���)����λL
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("MeterE0"));//�������ֵ(����)����λkWh
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("MeterE1"));//��������ֵ(����)����λkWh
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("DispError"));//ʾֵ����λ%
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("StdError"));//Ҫ�����(�ϸ��׼),��λ%
	model->setHeaderData(26, Qt::Horizontal, QObject::tr("Result"));//�춨���(1���ϸ�0�����ϸ�)

	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //�п������Ӧ
	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //����ֶ�ֻ�������е������б༭
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //ʹ�䲻�ɱ༭

	ui.tableView->hideColumn(0);
	ui.tableView->hideColumn(27);
	ui.tableView->hideColumn(28);
	ui.tableView->hideColumn(29);
}

void CmbResultDlg::on_btnExit_clicked()
{
	this->close();
}