#include <QtSql/QSqlRelationalDelegate>
#include <QtCore/QDebug>
#include "total_result.h"

TotalResultDlg::TotalResultDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	model = new QSqlRelationalTableModel(this);
}

TotalResultDlg::~TotalResultDlg()
{

}

void TotalResultDlg::showEvent(QShowEvent *)
{
	initCmb();
}

void TotalResultDlg::closeEvent(QCloseEvent *)
{

}

void TotalResultDlg::initCmb()
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

	//�춨ʱ��
	ui.startDateTime->setDateTime(QDateTime::currentDateTime().addDays(-7));//��ȥһ��
	ui.endDateTime->setDateTime(QDateTime::currentDateTime());
}

void TotalResultDlg::on_btnQuery_clicked()
{
	getCondition();
	queryData();
}

void TotalResultDlg::getCondition()
{
	m_conStr.clear();

	m_conStr.append( QString(" F_TimeStamp>=\'%1\' and F_TimeStamp<=\'%2\'").arg(ui.startDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))\
		.arg(ui.endDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))); //��ֹʱ��

	int method = ui.cmbMethod->currentIndex();//���������Ǳ�׼��
	m_conStr.append(QString(" and F_MethodFlag = %1").arg(method));

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

	idx = ui.cmbFlowPointIdx->currentIndex();
	if (idx > 0)//������
	{
		m_conStr.append(QString(" and F_FlowPointIdx=%1").arg(ui.cmbFlowPointIdx->currentIndex()));
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

void TotalResultDlg::queryData()
{
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //���Ա仯ʱд�����ݿ�
	model->setTable("T_Total_Verify_Record");
	model->setFilter(m_conStr); //���ò�ѯ����

	//�������	
	model->setRelation(19, QSqlRelation("T_Yes_No_Tab","F_ID","F_Desc"));	
	model->setRelation(21, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model->setRelation(22, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setRelation(23, QSqlRelation("T_Meter_PickCode","F_ID","F_Desc"));
	model->setRelation(24, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setRelation(25, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setRelation(27, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setRelation(28, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	//model->setRelation(29, QSqlRelation("T_Verify_Device_Info","F_ID","F_DeviceNo"));

	//����ˮƽ����
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("Time"));//ʱ�����'yyyy-MM-dd HH:mm:ss.zzz')
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("MeterNo."));//���(14λ����: 6 + 8)
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("FlowPointIdx"));//����������������1,2,3,4...
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("FlowPoint"));//��������ֵ����λm3/h
	//model->setHeaderData(5, Qt::Horizontal, QObject::tr("MethodFlag"));//������־��0(������)��1(��׼��)
	model->setHeaderData(6, Qt::Horizontal, QObject::tr("MeterValue0"));//�������ֵ������������λkwh
	model->setHeaderData(7, Qt::Horizontal, QObject::tr("MeterValue1"));//��������ֵ������������λkwh
	model->setHeaderData(8, Qt::Horizontal, QObject::tr("BalWeight0"));//��ƽ��ֵ������������λkg��������ʹ�ã�
	model->setHeaderData(9, Qt::Horizontal, QObject::tr("BalWeight1"));//��ƽ��ֵ������������λkg��������ʹ�ã�
	model->setHeaderData(10, Qt::Horizontal, QObject::tr("StdMeterV0"));//��׼���ֵ�����������λL����׼��ʹ�ã�
	model->setHeaderData(11, Qt::Horizontal, QObject::tr("StdMeterV1"));//��׼����ֵ�����������λL����׼��ʹ�ã�
	model->setHeaderData(12, Qt::Horizontal, QObject::tr("InSlotTemper"));//���²�����¶ȣ���λ��
	model->setHeaderData(13, Qt::Horizontal, QObject::tr("OutSlotTemper"));//���²۳����¶ȣ���λ��
	model->setHeaderData(14, Qt::Horizontal, QObject::tr("PipeTemper"));//���䵽ÿ����λ���¶ȣ���λ��
	model->setHeaderData(15, Qt::Horizontal, QObject::tr("Density"));//���䵽ÿ����λ���ܶȣ���λkg/L
	model->setHeaderData(16, Qt::Horizontal, QObject::tr("StandValue"));//���������ı�׼ֵ����λkwh
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("DispError"));//ʾֵ����λ%
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("StdError"));//Ҫ�����(�ϸ��׼),��λ%
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("Result"));//�춨�����1���ϸ�0�����ϸ�----------
	model->setHeaderData(20, Qt::Horizontal, QObject::tr("MeterPosNo"));//��λ��
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("Model"));//���ͺ�
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("Standard"));//����(DN15/DN20/DN25) ----------
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("PickCode"));//������(�ɼ�����) ----------
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("ManufactDept"));//���쵥λ ----------
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("VerifyDept"));//�ͼ쵥λ ----------
	model->setHeaderData(26, Qt::Horizontal, QObject::tr("Grade"));//�����ȼ���1,2,3��
	model->setHeaderData(27, Qt::Horizontal, QObject::tr("VerifyPerson"));//�춨Ա ----------
	model->setHeaderData(28, Qt::Horizontal, QObject::tr("CheckPerson"));//����Ա ----------
	model->setHeaderData(29, Qt::Horizontal, QObject::tr("DeviceInfoID"));//�춨װ���豸��ϢID ----------
	model->setHeaderData(30, Qt::Horizontal, QObject::tr("VerifyDate"));//�춨����('2014-05-22')
	model->setHeaderData(31, Qt::Horizontal, QObject::tr("ValidDate"));//�������Ч��(�����Ͳ���Ҫ)('2014-08-07')
	model->setHeaderData(32, Qt::Horizontal, QObject::tr("EnvTemper"));//�����¶ȣ���λ��
	model->setHeaderData(33, Qt::Horizontal, QObject::tr("EnvHumidity"));//����ʪ��
	model->setHeaderData(34, Qt::Horizontal, QObject::tr("AirPressure"));//����ѹ��
	model->setHeaderData(35, Qt::Horizontal, QObject::tr("CertNO"));//�춨֤����(�����̲�д��ţ������û��Ժ���д)
	model->setHeaderData(36, Qt::Horizontal, QObject::tr("TotalCoe"));//����ϵ��

	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //�п������Ӧ
	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //����ֶ�ֻ�������е������б༭
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //ʹ�䲻�ɱ༭

	ui.tableView->hideColumn(0);
	ui.tableView->hideColumn(5);

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
	ui.tableView->hideColumn(37);
	ui.tableView->hideColumn(38);
	ui.tableView->hideColumn(39);
}

void TotalResultDlg::on_btnExit_clicked()
{
	this->close();
}