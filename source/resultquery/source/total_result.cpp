#include <QtSql/QSqlRelationalDelegate>
#include <QtCore/QDebug>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

#include "total_result.h"
#include "report.h"

TotalResultDlg::TotalResultDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	model = new QSqlRelationalTableModel(this, g_defaultdb);
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
	//制造单位
	int col_id1 = 0;
	QSqlRelationalTableModel *model1 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model1->setTable("T_Manufacture_Dept");  
	model1->setRelation(col_id1, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel1 = model1->relationModel(col_id1);   
	ui.cmbManufactDept->setModel(relationModel1);  
	ui.cmbManufactDept->setModelColumn(relationModel1->fieldIndex("F_Desc")); 
	ui.cmbManufactDept->insertItem(ui.cmbManufactDept->count(), "");
	ui.cmbManufactDept->setCurrentIndex(ui.cmbManufactDept->count()-1);

	//送检单位
	int col_id2 = 0;
	QSqlRelationalTableModel *model2 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model2->setTable("T_Verify_Dept");  
	model2->setRelation(col_id2, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel2 = model2->relationModel(col_id2);   
	ui.cmbVerifyDept->setModel(relationModel2);  
	ui.cmbVerifyDept->setModelColumn(relationModel2->fieldIndex("F_Desc")); 
	ui.cmbVerifyDept->insertItem(ui.cmbVerifyDept->count(), "");
	ui.cmbVerifyDept->setCurrentIndex(ui.cmbVerifyDept->count()-1);

	//检定员
	int col_id3 = 0;
	QSqlRelationalTableModel *model3 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model3->setTable("T_User_Def_Tab");  
	model3->setRelation(col_id3, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));  
	QSqlTableModel *relationModel3 = model3->relationModel(col_id3);   
	ui.cmbVerifyPerson->setModel(relationModel3);  
	ui.cmbVerifyPerson->setModelColumn(relationModel3->fieldIndex("F_Desc")); 
	ui.cmbVerifyPerson->insertItem(ui.cmbVerifyPerson->count(), "");
	ui.cmbVerifyPerson->setCurrentIndex(ui.cmbVerifyPerson->count()-1);

	//表型号
	int col_id4 = 0;
	QSqlRelationalTableModel *model4 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model4->setTable("T_Meter_Model");  
	model4->setRelation(col_id4, QSqlRelation("T_Meter_Model","F_ID","F_Name"));  
	QSqlTableModel *relationModel4 = model4->relationModel(col_id4);   
	ui.cmbModel->setModel(relationModel4);  
	ui.cmbModel->setModelColumn(relationModel4->fieldIndex("F_Name")); 
	ui.cmbModel->insertItem(ui.cmbModel->count(), "");
	ui.cmbModel->setCurrentIndex(ui.cmbModel->count()-1);

	//表规格
	int col_id5 = 0;
	QSqlRelationalTableModel *model5 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model5->setTable("T_Meter_Standard");  
	model5->setRelation(col_id5, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));  
	QSqlTableModel *relationModel5 = model5->relationModel(col_id5);   
	ui.cmbStandard->setModel(relationModel5);  
	ui.cmbStandard->setModelColumn(relationModel5->fieldIndex("F_Name")); 
	ui.cmbStandard->insertItem(ui.cmbStandard->count(), "");
	ui.cmbStandard->setCurrentIndex(ui.cmbStandard->count()-1);

	//表等级
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "1");
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "2");
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "3");
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "");
	ui.cmbGrade->setCurrentIndex(ui.cmbGrade->count()-1);

	//是否合格
	ui.cmbIsValid->setCurrentIndex(ui.cmbIsValid->count()-1);

	//检定时间
	ui.startDateTime->setDateTime(QDateTime::currentDateTime().addSecs(-3600) );//过去一小时
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
		.arg(ui.endDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))); //起止时间

	int method = ui.cmbMethod->currentIndex();//质量法还是标准表法
	m_conStr.append(QString(" and F_MethodFlag = %1").arg(method));

	int idx, count;
	int not_select = 0;
	not_select = ~not_select;

	idx = ui.cmbManufactDept->currentIndex();
	count = ui.cmbManufactDept->count();
	if (idx != (count-1))//制造单位
	{
		m_conStr.append(QString(" and F_ManufactDept=%1").arg(ui.cmbManufactDept->currentIndex()));
	}

	idx = ui.cmbVerifyDept->currentIndex();
	count = ui.cmbVerifyDept->count();
	if (idx != (count-1))//送检单位
	{
		m_conStr.append(QString(" and F_VerifyDept=%1").arg(ui.cmbVerifyDept->currentIndex()));
	}

	idx = ui.cmbVerifyPerson->currentIndex();
	count = ui.cmbVerifyPerson->count();
	if (idx != (count-1))//检定员
	{
		m_conStr.append(QString(" and F_VerifyPerson=%1").arg(ui.cmbVerifyPerson->currentIndex()));
	}

	idx = ui.cmbFlowPointIdx->currentIndex();
	if (idx > 0)//流量点
	{
		m_conStr.append(QString(" and F_FlowPointIdx=%1").arg(ui.cmbFlowPointIdx->currentIndex()));
	}

	idx = ui.cmbModel->currentIndex();
	count = ui.cmbModel->count();
	if (idx != (count-1))//表型号
	{
		m_conStr.append(QString(" and F_Model=%1").arg(ui.cmbModel->currentIndex()));
	}

	idx = ui.cmbStandard->currentIndex();
	count = ui.cmbStandard->count();
	if (idx != (count-1))//表规格
	{
		m_conStr.append(QString(" and F_Standard=%1").arg(ui.cmbStandard->currentIndex()));
	}

	idx = ui.cmbGrade->currentIndex();
	count = ui.cmbGrade->count();
	if (idx != (count-1))//表等级
	{
		m_conStr.append(QString(" and F_Grade=%1").arg(ui.cmbGrade->currentIndex()+1));
	}

	idx = ui.cmbIsValid->currentIndex();
	count = ui.cmbIsValid->count();
	if (idx != (count-1))//是否合格
	{
		m_conStr.append(QString(" and F_Result=%1").arg(ui.cmbIsValid->currentIndex()));
	}

	if (!ui.lnEditMeterNO->text().isEmpty())//表号
	{
		m_conStr.append(QString(" and F_MeterNo like \"\%%1\%\"").arg(ui.lnEditMeterNO->text()));
	}
}

void TotalResultDlg::queryData()
{
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //属性变化时写入数据库
	model->setTable("T_Total_Verify_Record");
	model->setFilter(m_conStr); //设置查询条件

	//设置外键	
	model->setRelation(19, QSqlRelation("T_Yes_No_Tab","F_ID","F_Desc"));	
	model->setRelation(21, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model->setRelation(22, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setRelation(23, QSqlRelation("T_Meter_PickCode","F_ID","F_Desc"));
	model->setRelation(24, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setRelation(25, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setRelation(27, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setRelation(28, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	//model->setRelation(29, QSqlRelation("T_Verify_Device_Info","F_ID","F_DeviceNo"));

	//设置水平标题
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("Time"));//时间戳（'yyyy-MM-dd HH:mm:ss.zzz')
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("MeterNo."));//表号(14位数字: 6 + 8)
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("FlowPointIdx"));//流量点索引，例如1,2,3,4...
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("FlowPoint"));//流量点数值，单位m3/h
	//model->setHeaderData(5, Qt::Horizontal, QObject::tr("MethodFlag"));//方法标志：0(质量法)；1(标准表法)
	model->setHeaderData(6, Qt::Horizontal, QObject::tr("MeterValue0"));//热量表初值（热量），单位kwh
	model->setHeaderData(7, Qt::Horizontal, QObject::tr("MeterValue1"));//热量表终值（热量），单位kwh
	model->setHeaderData(8, Qt::Horizontal, QObject::tr("BalWeight0"));//天平初值（重量），单位kg（质量法使用）
	model->setHeaderData(9, Qt::Horizontal, QObject::tr("BalWeight1"));//天平终值（重量），单位kg（质量法使用）
	model->setHeaderData(10, Qt::Horizontal, QObject::tr("StdMeterV0"));//标准表初值（体积），单位L（标准表法使用）
	model->setHeaderData(11, Qt::Horizontal, QObject::tr("StdMeterV1"));//标准表终值（体积），单位L（标准表法使用）
	model->setHeaderData(12, Qt::Horizontal, QObject::tr("InSlotTemper"));//恒温槽入口温度，单位℃
	model->setHeaderData(13, Qt::Horizontal, QObject::tr("OutSlotTemper"));//恒温槽出口温度，单位℃
	model->setHeaderData(14, Qt::Horizontal, QObject::tr("PipeTemper"));//分配到每个表位的温度，单位℃
	model->setHeaderData(15, Qt::Horizontal, QObject::tr("Density"));//分配到每个表位的密度，单位kg/L
	model->setHeaderData(16, Qt::Horizontal, QObject::tr("StandValue"));//经过修正的标准值，单位kwh
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("DispError"));//示值误差，单位%
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("StdError"));//要求误差(合格标准),单位%
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("Result"));//检定结果（1：合格，0：不合格）----------
	model->setHeaderData(20, Qt::Horizontal, QObject::tr("MeterPosNo"));//表位号
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("Model"));//表型号
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("Standard"));//表规格(DN15/DN20/DN25) ----------
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("PickCode"));//表类型(采集代码) ----------
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("ManufactDept"));//制造单位 ----------
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("VerifyDept"));//送检单位 ----------
	model->setHeaderData(26, Qt::Horizontal, QObject::tr("Grade"));//计量等级（1,2,3）
	model->setHeaderData(27, Qt::Horizontal, QObject::tr("VerifyPerson"));//检定员 ----------
	model->setHeaderData(28, Qt::Horizontal, QObject::tr("CheckPerson"));//核验员 ----------
	model->setHeaderData(29, Qt::Horizontal, QObject::tr("DeviceInfoID"));//检定装置设备信息ID ----------
	model->setHeaderData(30, Qt::Horizontal, QObject::tr("VerifyDate"));//检定日期('2014-05-22')
	model->setHeaderData(31, Qt::Horizontal, QObject::tr("ValidDate"));//检表结果有效期(生产型不需要)('2014-08-07')
	model->setHeaderData(32, Qt::Horizontal, QObject::tr("EnvTemper"));//环境温度，单位℃
	model->setHeaderData(33, Qt::Horizontal, QObject::tr("EnvHumidity"));//环境湿度
	model->setHeaderData(34, Qt::Horizontal, QObject::tr("AirPressure"));//大气压力
	model->setHeaderData(35, Qt::Horizontal, QObject::tr("CertNO"));//检定证书编号(检表过程不写编号，留给用户以后填写)
	model->setHeaderData(36, Qt::Horizontal, QObject::tr("TotalCoe"));//总量系数

	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //列宽度自适应
	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //外键字段只能在已有的数据中编辑
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //使其不可编辑

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

void TotalResultDlg::on_btnExport_clicked()
{
	if (NULL==model)
	{
		QMessageBox::warning(this, tr("Warning"), tr("no data need to be exported!"));
		return;
	}

	QString defaultPath = QProcessEnvironment::systemEnvironment().value("ADEHOME") + "//report//total//" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
	QString file = QFileDialog::getSaveFileName(this, tr("Save File"), defaultPath, tr("Microsoft Excel (*.xls)"));//获取保存路径
	if (!file.isEmpty())
	{
		try
		{
			getCondition();
			CReport rpt(m_conStr);
			rpt.setIniName("rptconfig_total.ini");
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

void TotalResultDlg::on_btnExit_clicked()
{
	this->close();
}