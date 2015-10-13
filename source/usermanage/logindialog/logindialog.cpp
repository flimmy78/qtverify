/***********************************************
**  文件名:     logindialog.cpp
**  功能:       登录对话框
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/7/14
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/07 第一版
**  内容包含:
**  说明:
**  更新记录:
***********************************************/

#include <QtGui/QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtCore/QDebug>

#include "logindialog.h"
#include "commondefine.h"
#include "qtexdb.h"

LoginDialog::LoginDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_curUserID = -1;
	m_curRoleID = -1;

	ui.passwordEdit->setFocus();
	ui.passwordEdit->setEchoMode(QLineEdit::Password);
	ui.loginButton->setDefault(true);

	initUserComboBox();
}

LoginDialog::~LoginDialog()
{
	qDebug()<<"!!! CLoginDialog destructor";
}

void LoginDialog::initUserComboBox()
{
	int idx=0;
	QSqlQuery query(g_defaultdb);
	if (query.exec("select F_Desc from T_User_Def_Tab order by F_ID"))
	{
		while(query.next())
		{
			ui.userComboBox->insertItem(idx++, query.value(0).toString());
		}
	}
}

int LoginDialog::getCurUserID()
{
	return m_curUserID;
}

int LoginDialog::getCurRoleID()
{
	return m_curRoleID;
}

void LoginDialog::on_loginButton_clicked()
{
// 	if (ui.passwordEdit->text().isEmpty())
// 	{
// 		QMessageBox::warning(this, tr("Warning"), tr("please input password!"));
// 		ui.passwordEdit->setFocus();
// 	}
// 	else
// 	{
		QSqlQuery query(g_defaultdb);
		query.exec(QString("select F_Password,F_RoleID from T_User_Def_Tab where F_ID=%1").arg(ui.userComboBox->currentIndex()));
		query.next();
		if (query.value(0).toString() == ui.passwordEdit->text())
		{
			m_curUserID = ui.userComboBox->currentIndex();
			m_curRoleID = query.value(1).toInt();
			QDialog::accept();
		}
		else
		{
			QMessageBox::warning(this, tr("Warning"), tr("password error!"));
			ui.passwordEdit->clear();
			ui.passwordEdit->setFocus();
		}
// 	}
}

void LoginDialog::on_quitButton_clicked()
{
	QDialog::reject();//隐藏对话框，发送拒绝信号
}