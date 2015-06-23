#include <QtGui/QMessageBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QTextEdit>
#include <QDebug>
#include <QProcess>
#include <QFile>

#include "register.h"
#include "md5encode.h"


RegisterDlg::RegisterDlg(QString code, QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	ui.lineEditCode->setText(code);
}

RegisterDlg::~RegisterDlg()
{
}

void RegisterDlg::closeEvent( QCloseEvent * event)
{
}

void RegisterDlg::on_btnRegister_clicked()
{
	QString license = ui.lineEditLicense->text();
	QString diskCode = qGetVolumeInfo();
	QString encode = QString::fromStdString(md5(diskCode.toStdString()));
	if (license == encode)
	{
		QString filename = QProcessEnvironment::systemEnvironment().value("ADEHOME") + "\\bin\\license";
		QFile file(filename);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			return;
		}
		QTextStream out(&file);
		out << license;
		file.close();
		QMessageBox::information(this, tr("OK"), tr("Register successfully!"));
	}
	else
	{
		QMessageBox::warning(this, tr("Warn"), tr("Register failed!"));
	}
}

void RegisterDlg::on_btnExit_clicked()
{
	this->close();
}
