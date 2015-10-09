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
	initUserList();
}

UserManageDlg::~UserManageDlg()
{
	qDebug()<<"!!! UserManageDlg destructor";
}

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

void UserManageDlg::on_btnExit_clicked()
{
	this->close();
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