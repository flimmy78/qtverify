#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QFile>
#include <QtXml/QtXml>
#include <iostream>

#include "SetComFrm.h"

SetComFrm::SetComFrm(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	gui.setupUi(this);
	ConfigFileName = "comconfig.xml";
}

SetComFrm::~SetComFrm()
{

}

#pragma region 按钮事件
void SetComFrm::on_btnExit_clicked()
{
	close();
}

void SetComFrm::on_btnSave_clicked()
{
	WriteValveConfig(ReadValeSet());
	WriteBalanceConfig(ReadBalanceSet());
	WriteTempConfig(ReadTempSet());
	WriteStdTempConfig(ReadStdTempSet());
	WriteMetersConfig();
	QMessageBox::about(NULL, "Success", "Successfully Save Settings !");
}
#pragma endregion

#pragma region 读取界面选择
QVector<QString> SetComFrm::ReadValeSet()//读取界面上阀门控制的配置
{
	QVector<QString> Configs = ReadGBoxSet(gui.gBoxValve);
	return Configs;
}

QVector<QString> SetComFrm::ReadBalanceSet()//读取界面上天平的配置
{
	QVector<QString> Configs = ReadGBoxSet(gui.gBoxBalance);
	return Configs;
}

QVector<QString> SetComFrm::ReadTempSet()//读取界面上温度采集的配置
{
	QVector<QString> Configs = ReadGBoxSet(gui.gBoxTempSenor);
	return Configs;
}

QVector<QString> SetComFrm::ReadStdTempSet()//读取界面上标准温度的配置
{
	QVector<QString> Configs = ReadGBoxSet(gui.gBoxStdTmpSensor);
	return Configs;
}

QVector<QString> SetComFrm::ReadMeterSetByNum(QString MeterNum)//按照表号读取界面上被检表的配置
{
	QVector<QString> meter_configs;
	const QObjectList list=gui.gBoxMeters->children();
	foreach(QObject *obj, list)
	{
		QString class_name = QString::fromAscii( obj->metaObject()->className() );
		if (class_name == "QGroupBox")
		{
			QGroupBox *meter_gbox = (QGroupBox*)obj;
			QString box_name = meter_gbox->objectName();

			QStringList words = box_name.split("_");//获取控件名的后缀
			if (words[1] == MeterNum)
			{
				meter_configs = ReadGBoxSet(meter_gbox);
				break;
			}
		}
	}

	return meter_configs;
}

//由于每个GroupBox的结构都相同，所以设计一个通用函数，读取当前GBox的设置值
//这个函数只适用于控件按规则: (控件名类名+设备名+设置项), 命名的情况
QVector<QString>  SetComFrm::ReadGBoxSet(QGroupBox *gBox)
{
	QString com_num ;
	QString baud_rate ;
	QString bits ;
	QString chk_bit ;
	QString end_bit ;

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
				com_num = CBox->currentText();
			}
			else if (occur = object_name .contains("BaudRate",Qt::CaseSensitive))
			{
				baud_rate = CBox->currentText();
			}
			else if (occur = object_name .contains("Bits",Qt::CaseSensitive))
			{
				bits = CBox->currentText();
			}
			else if (occur = object_name .contains("ChkBit",Qt::CaseSensitive))
			{
				chk_bit = CBox->currentText();
			}
			else if (occur = object_name .contains("EndBit",Qt::CaseSensitive))
			{
				end_bit = CBox->currentText();
			}
		}
	}
	QVector<QString> strArray;
	strArray.append(com_num);
	strArray.append(baud_rate);
	strArray.append(bits);
	strArray.append(chk_bit);
	strArray.append(end_bit);
	return strArray;
}
#pragma endregion

#pragma region 写入配置

bool  SetComFrm::WriteValveConfig(QVector<QString> ValveConfigs)
{
	return WriteConfigById("valve", ValveConfigs);
}

bool  SetComFrm::WriteBalanceConfig(QVector<QString> BalanceConfigs)
{
	return WriteConfigById("balance", BalanceConfigs);
}

bool  SetComFrm::WriteTempConfig(QVector<QString> TempConfigs)
{
	return WriteConfigById("temp", TempConfigs);
}

bool  SetComFrm::WriteStdTempConfig(QVector<QString> StdTempConfigs)
{
	return WriteConfigById("stdtemp", StdTempConfigs);
}

bool SetComFrm::WriteMetersConfig()
{
	QVector<QString> Configs;//相应表号的界面配置
	QString meter_num;//表号
	for (int i=1; i< 13; i++)
	{
		meter_num = QString::number(i, 10); 
		Configs = ReadMeterSetByNum(meter_num);
		if (!WriteMeterConfigByNum(meter_num, Configs))
		{
			QMessageBox::about(NULL, "False", "False  Save Settings of Meter: " + meter_num +"# !");
			return false;
		}
	}
	return true;
}

bool SetComFrm::WriteMeterConfigByNum(QString MeterNum, QVector<QString> MeterConfigs)
{
	QString ConfigId = "meter" + MeterNum;

	return WriteConfigById(ConfigId, MeterConfigs);
}

bool  SetComFrm::WriteConfigById(QString ConfigId, QVector<QString> Configs)
{
	if (!OpenConfigFile())
		return false;
	
	//修改保存xml
	QDomElement root = m_doc.documentElement();
	if(root.tagName()!= "configs")
		return false;

	QDomNode n;
	if (ConfigId.contains("meter"))
		 n = root.lastChild().firstChild();
	else
		n = root.firstChild();
	
	while ( !n.isNull() )
	{
		QDomElement e = n.toElement();
		if( !e.isNull())
		{
			if( e.tagName() == "config" && e.attribute("id") == ConfigId)//查找id号
			{
				QDomNodeList list = e.childNodes(); //获得元素e的所有子节点的列表(com号、波特率、校验位等)
				for(int i=0; i<list.count(); i++) //遍历该列表
				{
					QDomNode node = list.at(i);
					node.firstChild().setNodeValue(Configs[i]);
				}
			}      
		}
		n = n.nextSibling();
	}
	
	return WriteConfigFile();
}

bool SetComFrm::OpenConfigFile()
{
	QFile file( ConfigFileName );
	if( !file.open( QFile::ReadOnly | QFile::Text  ) )
	{
		QMessageBox::critical(NULL, "warning", "Can not open file: " + ConfigFileName, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return false;
	}
	if( !m_doc.setContent( &file ) )
	{
		QMessageBox::critical(NULL, "warning", "Can not setContent file: " + ConfigFileName, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		file.close();
		return false;
	}
	file.close();
	return true;
}

bool SetComFrm::WriteConfigFile()
{
	QFile filexml(ConfigFileName);

	if( !filexml.open( QFile::WriteOnly | QFile::Truncate) )
	{
		QMessageBox::critical(NULL, "warning", "Can not write to file: " + ConfigFileName, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return false;
	}
	QTextStream ts(&filexml);
	ts.reset();
	ts.setCodec("utf-8");
	m_doc.save(ts, 4, QDomNode::EncodingFromTextStream);
	filexml.close();
	return true;
}
#pragma endregion