#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QFile>
#include <QtXml/QtXml>
#include <iostream>

#include "ReadComConfig.h"

ReadComConfig::ReadComConfig()
{
	ConfigFileName="comconfig.xml";
}

ReadComConfig::~ReadComConfig()
{

}

QMap<QString, QString> ReadComConfig::ReadValeConfig()
{
	return ReadConfigByName("valve");
}

QMap<QString, QString> ReadComConfig::ReadBalanceConfig()
{
	return ReadConfigByName("balance");
}

QMap<QString, QString> ReadComConfig::ReadTempConfig()
{
	return ReadConfigByName("temp");
}

QMap<QString, QString> ReadComConfig::ReadStdTempConfig()
{
	return ReadConfigByName("stdtemp");
}

QMap<QString, QString> ReadComConfig::ReadMeterConfigByNum(QString MeterNum)
{
	QString pattern("[0-9]{1,2}");
	QRegExp rx(pattern);
	if (!rx.exactMatch(MeterNum))
	{
		throw QString("Please input an integer!");
	}
	return ReadConfigByName("meter" + MeterNum);
}

QMap<QString, QString> ReadComConfig::ReadConfigByName(QString ConfigId)
{
	QMap<QString, QString> configs;

	if (!OpenConfigFile())
		return configs;

	QDomElement root = m_doc.documentElement();
	if(root.tagName()!= "configs")
		return configs;

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
					configs[node.nodeName()] = node.firstChild().nodeValue();
				}
			}      
		}
		n = n.nextSibling();
	}

	return configs;
}

bool ReadComConfig::OpenConfigFile()
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