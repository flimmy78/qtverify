/***********************************************
**  �ļ���:     logindialog.cpp
**  ����:       ��¼�Ի���
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/7/14
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/07 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:
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

	initUserComboBox();
}

LoginDialog::~LoginDialog()
{
	qDebug()<<"!!! CLoginDialog destructor";
}

void LoginDialog::initUserComboBox()
{
	int idx=0;
	QSqlQuery query;
	if (query.exec("select F_Desc from T_User_Def_Tab order by F_ID"))
	{
		while(query.next())
		{
			ui.userComboBox->insertItem(idx++, query.value(0).toString());
		}
	}
}

void LoginDialog::on_loginButton_clicked()
{
	if (ui.passwordEdit->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("please input password!"));
		ui.passwordEdit->setFocus();
	}
	else
	{
		QSqlQuery query;
		query.exec(QString("select F_Password from T_User_Def_Tab where F_ID=%1").arg(ui.userComboBox->currentIndex()));
		query.next();
		if (query.value(0).toString() == ui.passwordEdit->text())
		{
			QDialog::accept();
		}
		else
		{
			QMessageBox::warning(this, tr("Warning"), tr("password error!"));
			ui.passwordEdit->clear();
			ui.passwordEdit->setFocus();
		}
	}
}

void LoginDialog::on_quitButton_clicked()
{
	QDialog::reject();//���ضԻ��򣬷��;ܾ��ź�
}