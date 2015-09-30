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