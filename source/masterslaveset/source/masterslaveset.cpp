#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QProcessEnvironment>

#include "masterslaveset.h"
#include "commondefine.h"
#include "algorithm.h"

CMasterSlave::CMasterSlave(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	if ( getMasterSlaveIni(&m_masterslaveIni) )
	{
		initSettingsInfo();
	}

	QString filename = getFullIniFileName("masterslaveset.ini");
	m_settings = new QSettings(filename, QSettings::IniFormat);
}

CMasterSlave::~CMasterSlave()
{
	if (m_settings)
	{
		delete m_settings;
		m_settings = NULL;
	}
}

void CMasterSlave::initSettingsInfo()
{
	if (m_masterslaveIni.netmode) //网络模式
	{
		ui.checkBoxNetMode->setCheckState(Qt::Checked);
		ui.btnGrpHostFlag->setEnabled(true);
		ui.grpBoxMaster->setEnabled(true);
		ui.grpBoxSlave->setEnabled(true);
	}
	else //本地模式
	{
		ui.checkBoxNetMode->setCheckState(Qt::Unchecked);
		ui.btnGrpHostFlag->setEnabled(false);
		ui.grpBoxMaster->setEnabled(false);
		ui.grpBoxSlave->setEnabled(false);
	}
// 	ui.checkBoxNetMode->setCheckState((m_masterslaveIni.netmode ? Qt::Checked : Qt::Unchecked));
	ui.btnGrpHostFlag->setButton(m_masterslaveIni.hostflag);
	
	ui.lnEditIpSlave1->setText(m_masterslaveIni.slave1IP);
	ui.lnEditHostnameSlave1->setText(QString::fromLocal8Bit(m_masterslaveIni.slave1name));//汉字编码
	ui.lnEditIpSlave2->setText(m_masterslaveIni.slave2IP);
	ui.lnEditHostnameSlave2->setText(QString::fromLocal8Bit(m_masterslaveIni.slave2name));
	ui.lnEditIpSlave3->setText(m_masterslaveIni.slave3IP);
	ui.lnEditHostnameSlave3->setText(QString::fromLocal8Bit(m_masterslaveIni.slave3name));
	ui.lnEditIpSlave4->setText(m_masterslaveIni.slave4IP);
	ui.lnEditHostnameSlave4->setText(QString::fromLocal8Bit(m_masterslaveIni.slave4name));
	ui.lnEditIpMaster->setText(m_masterslaveIni.masterIP);
	ui.lnEditHostnameMaster->setText(QString::fromLocal8Bit(m_masterslaveIni.mastername));
}

void CMasterSlave::on_btnSave_clicked()
{
	m_settings->setIniCodec("GB2312"); //解决向ini文件中写汉字乱码

	m_settings->setValue("localhost/netmode",(ui.checkBoxNetMode->isChecked()?1:0));
	m_settings->setValue("localhost/hostflag",ui.btnGrpHostFlag->selectedId());

	m_settings->setValue("master/hostname",ui.lnEditHostnameMaster->text());
	m_settings->setValue("master/ip",ui.lnEditIpMaster->text());
	m_settings->setValue("slave1/hostname",ui.lnEditHostnameSlave1->text());
	m_settings->setValue("slave1/ip",ui.lnEditIpSlave1->text());
	m_settings->setValue("slave2/hostname",ui.lnEditHostnameSlave2->text());
	m_settings->setValue("slave2/ip",ui.lnEditIpSlave2->text());
	m_settings->setValue("slave3/hostname",ui.lnEditHostnameSlave3->text());
	m_settings->setValue("slave3/ip",ui.lnEditIpSlave3->text());
	m_settings->setValue("slave4/hostname",ui.lnEditHostnameSlave4->text());
	m_settings->setValue("slave4/ip",ui.lnEditIpSlave4->text());

	QMessageBox::information(this, tr("Hint"), tr("Save Settings Successfully"), QMessageBox::Ok);
}

void CMasterSlave::on_btnExit_clicked()
{
	this->close();
}

void CMasterSlave::on_checkBoxNetMode_stateChanged(int state)
{
	if (state==Qt::Checked)
	{
		ui.btnGrpHostFlag->setEnabled(true);
		ui.grpBoxMaster->setEnabled(true);
		ui.grpBoxSlave->setEnabled(true);
	}
	else
	{
		ui.btnGrpHostFlag->setEnabled(false);
		ui.grpBoxMaster->setEnabled(false);
		ui.grpBoxSlave->setEnabled(false);
	}
}

void CMasterSlave::on_btnGrpHostFlag_clicked(int id)
{
	if (id==1) //设为主机
	{
		ui.grpBoxSlave->setEnabled(true);
		ui.grpBoxMaster->setEnabled(false);
	}
	else if (id==0) //设为从机
	{
		ui.grpBoxSlave->setEnabled(false);
		ui.grpBoxMaster->setEnabled(true);
	}
}