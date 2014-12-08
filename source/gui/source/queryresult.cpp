/***********************************************
**  文件名:     queryresult.cpp
**  功能:       查询检定结果(SQLITE3)
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/8/8
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/08 第一版
**  内容包含:
**  说明:
**  更新记录:  
***********************************************/

#include <QtGui/QMessageBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QTextEdit>
#include <QtCore/QDebug>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlIndex>
#include <QtSql/QSqlRelationalDelegate>
#include <QtGui/QFileDialog>
#include <QAxObject>

#include "queryresult.h"
#include "qexcel.h"


QueryResult::QueryResult(QWidget *parent, Qt::WFlags flags)
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

QueryResult::~QueryResult()
{

}

//
void QueryResult::initUiData()
{
	//制造单位
	int col_id1 = 0;
	QSqlRelationalTableModel *model1 = new QSqlRelationalTableModel(this);  
	model1->setTable(tr("T_Manufacture_Dept"));  
	model1->setRelation(col_id1, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel1 = model1->relationModel(col_id1);   
	ui.cmbManufactDept->setModel(relationModel1);  
	ui.cmbManufactDept->setModelColumn(relationModel1->fieldIndex("F_Desc")); 
	ui.cmbManufactDept->insertItem(ui.cmbManufactDept->count(), "");
	ui.cmbManufactDept->setCurrentIndex(ui.cmbManufactDept->count()-1);

	//送检单位
	int col_id2 = 0;
	QSqlRelationalTableModel *model2 = new QSqlRelationalTableModel(this);  
	model2->setTable(tr("T_Verify_Dept"));  
	model2->setRelation(col_id2, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel2 = model2->relationModel(col_id2);   
	ui.cmbVerifyDept->setModel(relationModel2);  
	ui.cmbVerifyDept->setModelColumn(relationModel2->fieldIndex("F_Desc")); 
	ui.cmbVerifyDept->insertItem(ui.cmbVerifyDept->count(), "");
	ui.cmbVerifyDept->setCurrentIndex(ui.cmbVerifyDept->count()-1);

	//检定员
	int col_id3 = 0;
	QSqlRelationalTableModel *model3 = new QSqlRelationalTableModel(this);  
	model3->setTable(tr("T_User_Def_Tab"));  
	model3->setRelation(col_id3, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));  
	QSqlTableModel *relationModel3 = model3->relationModel(col_id3);   
	ui.cmbVerifyPerson->setModel(relationModel3);  
	ui.cmbVerifyPerson->setModelColumn(relationModel3->fieldIndex("F_Desc")); 
	ui.cmbVerifyPerson->insertItem(ui.cmbVerifyPerson->count(), "");
	ui.cmbVerifyPerson->setCurrentIndex(ui.cmbVerifyPerson->count()-1);

	ui.startDateTime->setDateTime(QDateTime::currentDateTime().addDays(-7));//过去一周
	ui.endDateTime->setDateTime(QDateTime::currentDateTime());
}

//查询检定结果
void QueryResult::on_btnQuery_clicked()
{
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //属性变化时写入数据库
	model->setTable("T_Verify_Record");
	
	QString conStr;
	conStr = QString("F_TimeStamp>=\'%1\' and F_TimeStamp<=\'%2\'").arg(ui.startDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))\
		.arg(ui.endDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz")); //起止时间
	if (ui.cmbManufactDept->currentIndex() != (ui.cmbManufactDept->count()-1))//制造单位
	{
		conStr.append(QString(" and F_ManufactDept=%1").arg(ui.cmbManufactDept->currentIndex()));
	}
	if (ui.cmbVerifyDept->currentIndex() != (ui.cmbVerifyDept->count()-1))//送检单位
	{
		conStr.append(QString(" and F_VerifyDept=%1").arg(ui.cmbVerifyDept->currentIndex()));
	}
	if (ui.cmbVerifyPerson->currentIndex() != (ui.cmbVerifyPerson->count()-1))//检定员
	{
		conStr.append(QString(" and F_VerifyPerson=%1").arg(ui.cmbVerifyPerson->currentIndex()));
	}
	model->setFilter(conStr); //设置查询条件
	
	//设置外键
	model->setRelation(19, QSqlRelation("T_Yes_No_Tab","F_ID","F_Desc"));
	model->setRelation(21, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	//将T_Verify_Record表的第22个属性设为T_Meter_Standard表的F_ID属性的外键，并将其显示为T_Meter_Standard表的F_Name属性的值
	model->setRelation(22, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setRelation(23, QSqlRelation("T_Meter_Type","F_ID","F_Desc"));
	model->setRelation(24, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setRelation(25, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setRelation(27, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setRelation(28, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));

	//设置水平标题
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("时间"));
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("表号"));
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("流量点"));
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("流量"));
	model->setHeaderData(5, Qt::Horizontal, QObject::tr("总量检定标志"));
	model->setHeaderData(6, Qt::Horizontal, QObject::tr("表初值"));
	model->setHeaderData(7, Qt::Horizontal, QObject::tr("表终值"));
	model->setHeaderData(8, Qt::Horizontal, QObject::tr("表示值"));
	model->setHeaderData(9, Qt::Horizontal, QObject::tr("天平初值"));
	model->setHeaderData(10, Qt::Horizontal, QObject::tr("天平终值"));
	model->setHeaderData(11, Qt::Horizontal, QObject::tr("天平示值"));
	model->setHeaderData(12, Qt::Horizontal, QObject::tr("入口温度"));
	model->setHeaderData(13, Qt::Horizontal, QObject::tr("出口温度"));
	model->setHeaderData(14, Qt::Horizontal, QObject::tr("管路温度"));
	model->setHeaderData(15, Qt::Horizontal, QObject::tr("密度"));
	model->setHeaderData(16, Qt::Horizontal, QObject::tr("标准值"));
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("误差"));
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("合格标准"));
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("合格标志"));
	model->setHeaderData(20, Qt::Horizontal, QObject::tr("表位号"));
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("型号"));
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("规格"));
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("表类型"));
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("制造单位"));
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("送检单位"));
	model->setHeaderData(26, Qt::Horizontal, QObject::tr("计量等级"));
	model->setHeaderData(27, Qt::Horizontal, QObject::tr("检定员"));
	model->setHeaderData(28, Qt::Horizontal, QObject::tr("核验员"));
	model->setHeaderData(29, Qt::Horizontal, QObject::tr("检定日期"));
	model->setHeaderData(30, Qt::Horizontal, QObject::tr("环境温度"));
	model->setHeaderData(31, Qt::Horizontal, QObject::tr("环境湿度"));
	model->setHeaderData(32, Qt::Horizontal, QObject::tr("气压"));
	model->setHeaderData(33, Qt::Horizontal, QObject::tr("有效期"));
	model->setHeaderData(34, Qt::Horizontal, QObject::tr("记录编号"));

	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //列宽度自适应
 	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //外键字段只能在已有的数据中编辑
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //使其不可编辑
/*
 	ui.tableView->hideColumn(0);
	QString tbname = model->tableName();
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
	db.transaction(); //开启事务处理
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
    db.commit(); //提交事务，此时才真正打开文件执行SQL语句
	endTime = QDateTime::currentDateTime();
	qDebug()<<"  end time is:"<<endTime.toString("yyMMddhhmmss");
	int usedSec = statTime.msecsTo(endTime);
	qDebug()<<"Insert"<<ui.spinBoxNums->value()<<"record。"<<"used time is:"<<usedSec<<"micro seconds\n";
}

void QueryResult::on_btnStop_clicked()
{
	m_count = 1;
	qDebug()<<"on_btnStop_clicked, m_count ="<<m_count;
}

void QueryResult::on_btnExport_clicked()
{
	if (NULL==model)
	{
		QMessageBox::warning(this, "warning", "no data need to be exported!");
		return;
	}

	QString defaultPath = QString("%1/dat").arg(getenv("RUNHOME"));
	QString file = QFileDialog::getSaveFileName(this,tr("Save File"),defaultPath,tr("Microsoft Excel (*.xlsx;*.xls)"));//获取保存路径
	if (!file.isEmpty())
	{
		QAxObject *excel = new QAxObject(this);
		excel->setControl("Excel.Application");//连接Excel控件
		excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
		excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭时会出现类似“文件已修改，是否保存”的提示

		QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
		workbooks->dynamicCall("Add");//新建一个工作簿
		QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
		//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
		workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(file));
		workbook->dynamicCall("Close()");//关闭工作簿
		excel->dynamicCall("Quit()");//关闭excel
		delete excel;
		excel=NULL;

		QString preStr = "";
		QExcel xlsFile(file);	
		xlsFile.selectSheet(1);//激活一张工作表
		for (int j=0; j<model->columnCount(); j++)
		{
			if (j==1 || j==2) //时间戳和表号列
			{
				preStr = "'";
			}
			else
			{
				preStr = "";
			}
			xlsFile.setCellString(1, j+1, model->headerData(j, Qt::Horizontal).toString()); //标题行
			for(int i=0;i<model->rowCount();i++)
			{
				xlsFile.setCellString(i+2, j+1, preStr+model->data(model->index(i,j)).toString());
			}
// 			xlsFile.setAutoFitColumn(j+1);
		}
		xlsFile.setAutoFitColumnAll();
		xlsFile.save();

		QMessageBox::information(this, "hint", "export excel successful!");
	}
}

void QueryResult::on_btnExit_clicked()
{
	this->close();
}


