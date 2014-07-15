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

LoginDialog::LoginDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.passwordEdit->setFocus();
	ui.passwordEdit->setEchoMode(QLineEdit::Password);
	ui.loginButton->setDefault(true);

	if (!db.startdb())
	{
		qWarning()<<"连接数据库失败！";
	}
	

	initUserComboBox();
}

LoginDialog::~LoginDialog()
{
	qDebug()<<"!!! CLoginDialog destructor";
	db.closedb();
}

void LoginDialog::initUserComboBox()
{
	int idx=0;
	QSqlQuery query;
	if (query.exec("select desc from t_user_def_tab order by id"))
	{
		while(query.next())
		{
			ui.userComboBox->insertItem(idx++, query.value(0).toString());
		}
	}
}

void LoginDialog::on_loginButton_clicked()
{
	if(ui.passwordEdit->text().isEmpty())
	{
		QMessageBox::information(this, tr("请输入密码"), tr("请输入密码再登录"));
		ui.passwordEdit->setFocus();
	}
	else
	{
		QSqlQuery query;
		query.exec(QString("select password from t_user_def_tab where id=%1").arg(ui.userComboBox->currentIndex()));
		query.next();
		if (query.value(0).toString() == ui.passwordEdit->text())
		{
			QDialog::accept();
		}
		else
		{
			QMessageBox::warning(this, tr("密码错误"), tr("请输入正确密码后再登录"));
			ui.passwordEdit->clear();
			ui.passwordEdit->setFocus();
		}
	}
}

void LoginDialog::on_quitButton_clicked()
{
	QDialog::reject();//隐藏对话框，发送拒绝信号
}