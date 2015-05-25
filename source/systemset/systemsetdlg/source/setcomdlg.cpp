/***********************************************
**  文件名:     SetComFrm.cpp
**  功能:       将用户对各个设备的串口设置保存到 $ADEHOME/ini/comconfig.xml文件中;
					并在窗口加载时，将配置文件中的相应配置装载到窗口中
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/15
**  专业组:     德鲁计量软件组
**  程序设计者: 宋宝善
**  程序员:     宋宝善
**  版本历史:   2014/06 第一版
**  内容包含:
**  说明:
**  更新记录:
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QFile>
#include <QtXml/QtXml>
#include <iostream>

#include "basedef.h"
#include "algorithm.h"
#include "setcomDlg.h"
#include "commondefine.h"
#include "readcomconfig.h"

SetComDlg::SetComDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	gui.setupUi(this);
}

SetComDlg::~SetComDlg()
{
	
}

void SetComDlg::showEvent(QShowEvent *)
{
	m_config = new ReadComConfig();
	InstallConfigs();
	m_com_settings = new QSettings(getFullIniFileName("comconfig.ini"), QSettings::IniFormat);
}

void SetComDlg::closeEvent(QCloseEvent *)
{
	if (m_config)
	{
		delete m_config;
		m_config=NULL;
	}

	if (m_com_settings)
	{
		delete m_com_settings;
		m_com_settings = NULL;
	}
}

void SetComDlg::on_btnExit_clicked()
{
	this->close();
}

void SetComDlg::on_btnSave_clicked()
{
	WriteValveConfig();
	WriteBalanceConfig();
	WriteTempConfig();
	WriteStdTempConfig();
	WriteMetersConfig();
	QMessageBox::information(this, tr("OK"), tr("Save Settings Successfully !"));
}

void SetComDlg::InstallConfigs()
{
	InstallValeConfig();
	InstallBalanceConfig();
	InstallTempConfig();
	InstallStdtmpConfig();
	InstallMetersConfig();
}

void SetComDlg::InstallValeConfig()
{
	QStringList valve_index = m_config->ReadIndexByName("Valve");
	gui.comboValveSerialNum->setCurrentIndex(valve_index[0].toInt());
	gui.comboValveBaudRate->setCurrentIndex(valve_index[1].toInt());
	gui.comboValveBits->setCurrentIndex(valve_index[2].toInt());
	gui.comboValveChkBit->setCurrentIndex(valve_index[3].toInt());
	gui.comboValveEndBit->setCurrentIndex(valve_index[4].toInt());
}

void SetComDlg::InstallBalanceConfig()
{
	QStringList valve_index = m_config->ReadIndexByName("Balance");
	gui.comboBalSerialNum->setCurrentIndex(valve_index[0].toInt());
	gui.comboBalBaudRate->setCurrentIndex(valve_index[1].toInt());
	gui.comboBalBits->setCurrentIndex(valve_index[2].toInt());
	gui.comboBalChkBit->setCurrentIndex(valve_index[3].toInt());
	gui.comboBalEndBit->setCurrentIndex(valve_index[4].toInt());
}

void SetComDlg::InstallTempConfig()
{
	QStringList valve_index = m_config->ReadIndexByName("TempSenor");
	gui.comboTempSerialNum->setCurrentIndex(valve_index[0].toInt());
	gui.comboTempBaudRate->setCurrentIndex(valve_index[1].toInt());
	gui.comboTempBits->setCurrentIndex(valve_index[2].toInt());
	gui.comboTempChkBit->setCurrentIndex(valve_index[3].toInt());
	gui.comboTempEndBit->setCurrentIndex(valve_index[4].toInt());
}

void SetComDlg::InstallStdtmpConfig()
{
	QStringList valve_index = m_config->ReadIndexByName("StdTmpSensor");
	gui.comboStdTmpSerialNum->setCurrentIndex(valve_index[0].toInt());
	gui.comboStdTmpBaudRate->setCurrentIndex(valve_index[1].toInt());
	gui.comboStdTmpBits->setCurrentIndex(valve_index[2].toInt());
	gui.comboStdTmpChkBit->setCurrentIndex(valve_index[3].toInt());
	gui.comboStdTmpEndBit->setCurrentIndex(valve_index[4].toInt());
}

void SetComDlg::InstallMetersConfig()
{
	const QObjectList list=gui.gBoxMeters->children();
	foreach(QObject *obj, list)
	{
		QString class_name = QString::fromAscii( obj->metaObject()->className() );
		if (class_name == "QGroupBox")
		{
			InstallMeterConfigByNum((QGroupBox*)obj);
		}
	}
}

void SetComDlg::InstallMeterConfigByNum(QGroupBox *gBox)
{
	const QObjectList list=gBox->children();
	QStringList configs = m_config->ReadIndexByName(gBox->objectName());
	foreach(QObject* obj, list)
	{
		QString class_name = QString::fromAscii( obj->metaObject()->className() );
		if(class_name=="QComboBox")
		{
			QComboBox *CBox=(QComboBox*)obj;
			QString object_name = CBox->objectName();

			if (object_name.contains("SerialNum",Qt::CaseSensitive))
			{
				CBox->setCurrentIndex(configs[0].toInt());
			}
			else if (object_name.contains("BaudRate",Qt::CaseSensitive))
			{
				CBox->setCurrentIndex(configs[1].toInt());
			}
			else if (object_name.contains("Bits",Qt::CaseSensitive))
			{
				CBox->setCurrentIndex(configs[2].toInt());
			}
			else if (object_name.contains("ChkBit",Qt::CaseSensitive))
			{
				CBox->setCurrentIndex(configs[3].toInt());
			}
			else if (object_name.contains("EndBit",Qt::CaseSensitive))
			{
				CBox->setCurrentIndex(configs[4].toInt());
			}
		}
	}
}

//写入阀门设置
void SetComDlg::WriteValveConfig()
{
	m_com_settings->beginGroup(gui.gBoxValve->objectName().split("gBox")[1]);
	WriteConfigById(gui.gBoxValve);
	m_com_settings->endGroup();
}

//写入天平设置
void  SetComDlg::WriteBalanceConfig()
{
	m_com_settings->beginGroup(gui.gBoxBalance->objectName().split("gBox")[1]);
	WriteConfigById(gui.gBoxBalance);
	m_com_settings->endGroup();
}

//写入温度采集设置
void  SetComDlg::WriteTempConfig()
{
	m_com_settings->beginGroup(gui.gBoxTempSenor->objectName().split("gBox")[1]);
	WriteConfigById(gui.gBoxTempSenor);
	m_com_settings->endGroup();
}

//写入标准温度计设置
void  SetComDlg::WriteStdTempConfig()
{
	m_com_settings->beginGroup(gui.gBoxStdTmpSensor->objectName().split("gBox")[1]);
	WriteConfigById(gui.gBoxStdTmpSensor);
	m_com_settings->endGroup();
}

//写入被检表设置
void SetComDlg::WriteMetersConfig()
{
	m_com_settings->beginWriteArray("Meters");
	for (int MeterNum=0; MeterNum< METER_QUANTITY; MeterNum++)
	{
		m_com_settings->setArrayIndex(MeterNum);
		WriteMeterConfigByNum(MeterNum+1);
	}
	m_com_settings->endArray();
}

void SetComDlg::WriteMeterConfigByNum(int MeterNum)
{
	const QString sep=SEP;//分隔符，用于分隔界面值和索引值
	const QObjectList list=gui.gBoxMeters->children();
	foreach(QObject* obj, list)
	{
		QString class_name = QString::fromAscii( obj->metaObject()->className() );
		if(class_name=="QGroupBox")
		{
			QGroupBox *gBox=(QGroupBox*)obj;
			QString object_name = gBox->objectName();

			QStringList words = object_name.split("_");//获取控件名的后缀
			if (words[1].toInt() == MeterNum)
			{
				WriteConfigById(gBox);
			}
		}
	}
}

void SetComDlg::WriteConfigById(QGroupBox *gBox)
{
	QString obj_name = gBox->objectName();
	QString com_name ;
	QString baud_rate ;
	QString data_bits ;
	QString chk_bit ;
	QString stop_bit ;
	const QString sep=SEP;//分隔符，用于分隔界面值和索引值
	const QObjectList list=gBox->children();
	foreach(QObject* obj, list)
	{
		QString class_name = QString::fromAscii( obj->metaObject()->className() );
		if(class_name=="QComboBox")
		{
			QComboBox *CBox=(QComboBox*)obj;
			QString object_name = CBox->objectName();

			if (bool occur = object_name .contains("SerialNum",Qt::CaseSensitive))
			{
				com_name = CBox->currentText() + sep + QString::number(CBox->currentIndex(), 10);
			}
			else if (occur = object_name .contains("BaudRate",Qt::CaseSensitive))
			{
				baud_rate = CBox->currentText()+ sep + QString::number(CBox->currentIndex(), 10);
			}
			else if (occur = object_name .contains("Bits",Qt::CaseSensitive))
			{
				data_bits = CBox->currentText()+ sep + QString::number(CBox->currentIndex(), 10);
			}
			else if (occur = object_name .contains("ChkBit",Qt::CaseSensitive))
			{
				chk_bit = QString::number(CBox->currentIndex(), 10)+ sep + QString::number(CBox->currentIndex(), 10);
			}
			else if (occur = object_name .contains("EndBit",Qt::CaseSensitive))
			{
				stop_bit = QString::number(CBox->currentIndex(), 10)+ sep + QString::number(CBox->currentIndex(), 10);
			}
		}
	}
	
	m_com_settings->setValue("com_name",com_name);
	m_com_settings->setValue("baud", baud_rate);
	m_com_settings->setValue("bits", data_bits);
	m_com_settings->setValue("chkbit", chk_bit);
	m_com_settings->setValue("endbit", stop_bit);
}