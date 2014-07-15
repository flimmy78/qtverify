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

	if (!db.startdb())
	{
		qWarning()<<"�������ݿ�ʧ�ܣ�";
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
		QMessageBox::information(this, tr("����������"), tr("�����������ٵ�¼"));
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
			QMessageBox::warning(this, tr("�������"), tr("��������ȷ������ٵ�¼"));
			ui.passwordEdit->clear();
			ui.passwordEdit->setFocus();
		}
	}
}

void LoginDialog::on_quitButton_clicked()
{
	QDialog::reject();//���ضԻ��򣬷��;ܾ��ź�
}