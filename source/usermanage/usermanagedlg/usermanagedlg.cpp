/***********************************************
**  文件名:     usermanagedlg.cpp
**  功能:       用户权限管理界面
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/9/30
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2015/09 第一版
**  内容包含:
**  说明:
**  更新记录:
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRelation>
#include <QtSql/QSqlRelationalDelegate>
#include <QtSql/QSqlRecord>

#include "usermanagedlg.h"
#include "commondefine.h"
#include "qtexdb.h"

UserManageDlg::UserManageDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	m_userModel = NULL;
	m_manudeptModel = NULL;
	m_verifydeptModel = NULL;
	m_modelModel = NULL;
	m_deviceModel = NULL;

	initUserList();
	initManuDept();
	initVerifyDept();
	initMeterModel();
	initDeviceInfo();
}

UserManageDlg::~UserManageDlg()
{
	qDebug()<<"!!! UserManageDlg destructor";

	if (m_userModel)
	{
		delete m_userModel;
		m_userModel = NULL;
	}

	if (m_manudeptModel)
	{
		delete m_manudeptModel;
		m_manudeptModel = NULL;
	}

	if (m_verifydeptModel)
	{
		delete m_verifydeptModel;
		m_verifydeptModel = NULL;
	}

	if (m_modelModel)
	{
		delete m_modelModel;
		m_modelModel = NULL;
	}

	if (m_deviceModel)
	{
		delete m_deviceModel;
		m_deviceModel = NULL;
	}

}

void UserManageDlg::on_btnExit_clicked()
{
	this->close();
}

/************************************************************************/
/* T_User_Def_Tab                                                       */
/************************************************************************/
void UserManageDlg::initUserList()
{
	m_userModel = new QSqlRelationalTableModel(this, g_defaultdb);  
	m_userModel->setTable("T_User_Def_Tab");  
	m_userModel->setRelation(4, QSqlRelation("T_Role_Def_Tab", "F_ID", "F_Desc"));
	//设置水平标题
	m_userModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
	m_userModel->setHeaderData(1, Qt::Horizontal, QObject::tr("UserName"));
	m_userModel->setHeaderData(2, Qt::Horizontal, QObject::tr("UserDesc"));
	m_userModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Password"));
	m_userModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Role"));
	m_userModel->setSort(0, Qt::AscendingOrder);
	m_userModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_userModel->select();  

	ui.userTableView->setModel(m_userModel);  
	ui.userTableView->resizeColumnsToContents(); //列宽度自适应
	ui.userTableView->setItemDelegate(new QSqlRelationalDelegate(ui.userTableView)); //外键字段只能在已有的数据中编辑
	ui.userTableView->setEditTriggers(QAbstractItemView::CurrentChanged);
	ui.userTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//	ui.userTableView->setContextMenuPolicy(Qt::CustomContextMenu);	
// 	ui.userTableView->hideColumn(0);
// 	ui.userTableView->hideColumn(1);
}

void UserManageDlg::on_btnSubmit_clicked()
{
	m_userModel->database().transaction();
	if (m_userModel->submitAll())
	{
		m_userModel->database().commit();
// 		QMessageBox::warning(this, tr("OK"), tr("Submit Successfully!"));
	}
	else
	{
		m_userModel->database().rollback();
		QMessageBox::warning(this, tr("Error"), tr("database error: %1 ").arg(m_userModel->lastError().text()));
	}
}

void UserManageDlg::on_btnRevert_clicked()
{
	m_userModel->revertAll();
}

void UserManageDlg::on_btnAdd_clicked()
{
	int rowNum = m_userModel->rowCount();
	m_userModel->insertRow(rowNum);
 	int id = m_userModel->data(m_userModel->index(rowNum-1, 0)).toInt(); //获取当前最大ID
	m_userModel->setData(m_userModel->index(rowNum, 0), id+1);//ID加1
// 	m_userModel->submitAll();
}

void UserManageDlg::on_btnDelete_clicked()
{
	int row = ui.userTableView->currentIndex().row();
	if (row < 0)
	{
		return;
	}
	m_userModel->removeRow(row);
	int ok = QMessageBox::warning(this, tr("Question"), tr("Delete current row really?"), QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		m_userModel->revertAll();
	}
	else
	{
		m_userModel->submitAll();
	}
}

void UserManageDlg::on_userTableView_clicked(const QModelIndex &index)
{
// 	qDebug()<<"index ="<<index;
// 	qDebug()<<index.model()->data(index).toString();
// 	qDebug()<<index.row()<<index.column();

	bool ok;
	qDebug()<<m_userModel->record(index.row()).value("F_Name").toString();
	qDebug()<<m_userModel->record(index.row()).value("F_Desc").toString();
	qDebug()<<m_userModel->record(index.row()).value("F_Password").toString();
	qDebug()<<m_userModel->record(index.row()).value("F_ID").toInt(&ok);
	qDebug()<<m_userModel->record(index.row()).value(4).toString();
	qDebug()<<m_userModel->record(index.row()).value(4).toInt();
}

/************************************************************************/
/* T_Manufacture_Dept                                                   */
/************************************************************************/
void UserManageDlg::initManuDept()
{
	m_manudeptModel = new QSqlTableModel(this, g_defaultdb);  
	m_manudeptModel->setTable("T_Manufacture_Dept");  
	//设置水平标题
	m_manudeptModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
	m_manudeptModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
	m_manudeptModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Desc"));
	m_manudeptModel->setSort(0, Qt::AscendingOrder);
	m_manudeptModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_manudeptModel->select();  

	ui.manudeptTableView->setModel(m_manudeptModel);  
	ui.manudeptTableView->resizeColumnsToContents(); //列宽度自适应
	ui.manudeptTableView->setEditTriggers(QAbstractItemView::CurrentChanged);
	ui.manudeptTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void UserManageDlg::on_btnSubmit_2_clicked()
{
	m_manudeptModel->database().transaction();
	if (m_manudeptModel->submitAll())
	{
		m_manudeptModel->database().commit();
	}
	else
	{
		m_manudeptModel->database().rollback();
		QMessageBox::warning(this, tr("Error"), tr("database error: %1 ").arg(m_manudeptModel->lastError().text()));
	}
}

void UserManageDlg::on_btnRevert_2_clicked()
{
	m_manudeptModel->revertAll();
}

void UserManageDlg::on_btnAdd_2_clicked()
{
	int rowNum = m_manudeptModel->rowCount();
	m_manudeptModel->insertRow(rowNum);
	int id = m_manudeptModel->data(m_manudeptModel->index(rowNum-1, 0)).toInt(); //获取当前最大ID
	m_manudeptModel->setData(m_manudeptModel->index(rowNum, 0), id+1);//ID加1
// 	m_manudeptModel->submitAll();
}

void UserManageDlg::on_btnDelete_2_clicked()
{
	int row = ui.manudeptTableView->currentIndex().row();
	if (row < 0)
	{
		return;
	}
	m_manudeptModel->removeRow(row);
	int ok = QMessageBox::warning(this, tr("Question"), tr("Delete current row really?"), QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		m_manudeptModel->revertAll();
	}
	else
	{
		m_manudeptModel->submitAll();
	}
}

/************************************************************************/
/* T_Verify_Dept                                                        */
/************************************************************************/
void UserManageDlg::initVerifyDept()
{
	m_verifydeptModel = new QSqlTableModel(this, g_defaultdb);  
	m_verifydeptModel->setTable("T_Verify_Dept");  
	//设置水平标题
	m_verifydeptModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
	m_verifydeptModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
	m_verifydeptModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Desc"));
	m_verifydeptModel->setSort(0, Qt::AscendingOrder);
	m_verifydeptModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_verifydeptModel->select();  

	ui.verifydeptTableView->setModel(m_verifydeptModel);  
	ui.verifydeptTableView->resizeColumnsToContents(); //列宽度自适应
	ui.verifydeptTableView->setEditTriggers(QAbstractItemView::CurrentChanged);
	ui.verifydeptTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void UserManageDlg::on_btnSubmit_3_clicked()
{
	m_verifydeptModel->database().transaction();
	if (m_verifydeptModel->submitAll())
	{
		m_verifydeptModel->database().commit();
	}
	else
	{
		m_verifydeptModel->database().rollback();
		QMessageBox::warning(this, tr("Error"), tr("database error: %1 ").arg(m_verifydeptModel->lastError().text()));
	}
}

void UserManageDlg::on_btnRevert_3_clicked()
{
	m_verifydeptModel->revertAll();
}

void UserManageDlg::on_btnAdd_3_clicked()
{
	int rowNum = m_verifydeptModel->rowCount();
	m_verifydeptModel->insertRow(rowNum);
	int id = m_verifydeptModel->data(m_verifydeptModel->index(rowNum-1, 0)).toInt(); //获取当前最大ID
	m_verifydeptModel->setData(m_verifydeptModel->index(rowNum, 0), id+1);//ID加1
// 	m_verifydeptModel->submitAll();
}

void UserManageDlg::on_btnDelete_3_clicked()
{
	int row = ui.verifydeptTableView->currentIndex().row();
	if (row < 0)
	{
		return;
	}
	m_verifydeptModel->removeRow(row);
	int ok = QMessageBox::warning(this, tr("Question"), tr("Delete current row really?"), QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		m_verifydeptModel->revertAll();
	}
	else
	{
		m_verifydeptModel->submitAll();
	}
}

/************************************************************************/
/* T_Meter_Model                                                        */
/************************************************************************/
void UserManageDlg::initMeterModel()
{
	m_modelModel = new QSqlTableModel(this, g_defaultdb);  
	m_modelModel->setTable("T_Meter_Model");  
	//设置水平标题
	m_modelModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
	m_modelModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
	m_modelModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Desc"));
	m_modelModel->setSort(0, Qt::AscendingOrder);
	m_modelModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_modelModel->select();  

	ui.modelTableView->setModel(m_modelModel);  
	ui.modelTableView->resizeColumnsToContents(); //列宽度自适应
	ui.modelTableView->setEditTriggers(QAbstractItemView::CurrentChanged);
	ui.modelTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void UserManageDlg::on_btnSubmit_4_clicked()
{
	m_modelModel->database().transaction();
	if (m_modelModel->submitAll())
	{
		m_modelModel->database().commit();
	}
	else
	{
		m_modelModel->database().rollback();
		QMessageBox::warning(this, tr("Error"), tr("database error: %1 ").arg(m_modelModel->lastError().text()));
	}
}

void UserManageDlg::on_btnRevert_4_clicked()
{
	m_modelModel->revertAll();
}

void UserManageDlg::on_btnAdd_4_clicked()
{
	int rowNum = m_modelModel->rowCount();
	m_modelModel->insertRow(rowNum);
	int id = m_modelModel->data(m_modelModel->index(rowNum-1, 0)).toInt(); //获取当前最大ID
	m_modelModel->setData(m_modelModel->index(rowNum, 0), id+1);//ID加1
	// 	m_modelModel->submitAll();
}

void UserManageDlg::on_btnDelete_4_clicked()
{
	int row = ui.modelTableView->currentIndex().row();
	if (row < 0)
	{
		return;
	}
	m_modelModel->removeRow(row);
	int ok = QMessageBox::warning(this, tr("Question"), tr("Delete current row really?"), QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		m_modelModel->revertAll();
	}
	else
	{
		m_modelModel->submitAll();
	}
}

/************************************************************************/
/* T_Verify_Device_Info                                                        */
/************************************************************************/
void UserManageDlg::initDeviceInfo()
{
	m_deviceModel = new QSqlTableModel(this, g_defaultdb);  
	m_deviceModel->setTable("T_Verify_Device_Info");  
	//设置水平标题
	m_deviceModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
	m_deviceModel->setHeaderData(1, Qt::Horizontal, QObject::tr("DeviceName"));
	m_deviceModel->setHeaderData(2, Qt::Horizontal, QObject::tr("DeviceNo"));
	m_deviceModel->setHeaderData(3, Qt::Horizontal, QObject::tr("DeviceModel"));
	m_deviceModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Manufact"));
	m_deviceModel->setHeaderData(5, Qt::Horizontal, QObject::tr("DeviceGrade"));
	m_deviceModel->setHeaderData(6, Qt::Horizontal, QObject::tr("MeasureRange"));
	m_deviceModel->setHeaderData(7, Qt::Horizontal, QObject::tr("CertNo"));
	m_deviceModel->setHeaderData(8, Qt::Horizontal, QObject::tr("VerifyRule"));
	m_deviceModel->setHeaderData(9, Qt::Horizontal, QObject::tr("DeviceValidDate"));
	m_deviceModel->setHeaderData(10, Qt::Horizontal, QObject::tr("CertValidDate"));
	m_deviceModel->setHeaderData(11, Qt::Horizontal, QObject::tr("RuleValidDate"));
	m_deviceModel->setSort(0, Qt::AscendingOrder);
	m_deviceModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_deviceModel->select();  

	ui.deviceTableView->setModel(m_deviceModel);  
	ui.deviceTableView->resizeColumnsToContents(); //列宽度自适应
	ui.deviceTableView->setEditTriggers(QAbstractItemView::CurrentChanged);
	ui.deviceTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	ui.deviceTableView->hideColumn(12);
	ui.deviceTableView->hideColumn(13);
	ui.deviceTableView->hideColumn(14);
	ui.deviceTableView->hideColumn(15);
}

void UserManageDlg::on_btnSubmit_5_clicked()
{
	m_deviceModel->database().transaction();
	if (m_deviceModel->submitAll())
	{
		m_deviceModel->database().commit();
	}
	else
	{
		m_deviceModel->database().rollback();
		QMessageBox::warning(this, tr("Error"), tr("database error: %1 ").arg(m_deviceModel->lastError().text()));
	}
}

void UserManageDlg::on_btnRevert_5_clicked()
{
	m_deviceModel->revertAll();
}

void UserManageDlg::on_btnAdd_5_clicked()
{
	int rowNum = m_deviceModel->rowCount();
	m_deviceModel->insertRow(rowNum);
	int id = m_deviceModel->data(m_deviceModel->index(rowNum-1, 0)).toInt(); //获取当前最大ID
	m_deviceModel->setData(m_deviceModel->index(rowNum, 0), id+1);//ID加1
// 	m_deviceModel->submitAll();
}

void UserManageDlg::on_btnDelete_5_clicked()
{
	int row = ui.deviceTableView->currentIndex().row();
	if (row < 0)
	{
		return;
	}
	m_deviceModel->removeRow(row);
	int ok = QMessageBox::warning(this, tr("Question"), tr("Delete current row really?"), QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		m_deviceModel->revertAll();
	}
	else
	{
		m_deviceModel->submitAll();
	}
}

