/***********************************************
**  �ļ���:     usermanagedlg.cpp
**  ����:       �û�Ȩ�޹������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2015/9/30
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2015/09 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:
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
	//����ˮƽ����
	m_userModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
	m_userModel->setHeaderData(1, Qt::Horizontal, QObject::tr("UserName"));
	m_userModel->setHeaderData(2, Qt::Horizontal, QObject::tr("UserDesc"));
	m_userModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Password"));
	m_userModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Role"));
	m_userModel->setSort(0, Qt::AscendingOrder);
	m_userModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_userModel->select();  

	ui.userTableView->setModel(m_userModel);  
	ui.userTableView->resizeColumnsToContents(); //�п������Ӧ
	ui.userTableView->setItemDelegate(new QSqlRelationalDelegate(ui.userTableView)); //����ֶ�ֻ�������е������б༭
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
 	int id = m_userModel->data(m_userModel->index(rowNum-1, 0)).toInt(); //��ȡ��ǰ���ID
	m_userModel->setData(m_userModel->index(rowNum, 0), id+1);//ID��1
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