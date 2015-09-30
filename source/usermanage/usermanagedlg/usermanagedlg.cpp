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
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtCore/QDebug>

#include "usermanagedlg.h"
#include "commondefine.h"

UserManageDlg::UserManageDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

}

UserManageDlg::~UserManageDlg()
{
	qDebug()<<"!!! UserManageDlg destructor";
}

void UserManageDlg::on_btnSave_clicked()
{
	QMessageBox::warning(this, tr("OK"), tr("Save Successfully!"));
}

void UserManageDlg::on_btnExit_clicked()
{
	this->close();
}