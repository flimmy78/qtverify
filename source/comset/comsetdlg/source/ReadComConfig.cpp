/***********************************************
**  �ļ���:     ReadComConfig.cpp
**  ����:       ��ȡ $RUNHOME/ini/comconfig.xml�ļ��Ĵ�������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/16
**  רҵ��:     ��³���������
**  ���������: �α���
**  ����Ա:     �α���
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:
***********************************************/
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QFile>
#include <QtXml/QtXml>
#include <iostream>

#include "ReadComConfig.h"
#include "comsetdlg.h"

ReadComConfig::ReadComConfig()
{
	QString path = QProcessEnvironment::systemEnvironment().value("RUNHOME");
#ifdef Q_OS_LINUX
	ConfigFileName = path + "\/ini\/comconfig.xml";
#elif defined (Q_OS_WIN)
	ConfigFileName = path + "\\ini\\comconfig.xml";
#endif
}

ReadComConfig::~ReadComConfig()
{

}
/*��ȡ��������*/
ComInfoStruct ReadComConfig::ReadValveConfig()
{
	return ReadConfigByName("valve");
}
/*��ȡ��ƽ����*/
ComInfoStruct ReadComConfig::ReadBalanceConfig()
{
	return ReadConfigByName("balance");
}
/*��ȡ�¶Ȳɼ�����*/
ComInfoStruct ReadComConfig::ReadTempConfig()
{
	return ReadConfigByName("temp");
}
/*��ȡ��׼�¶ȼ�����*/
ComInfoStruct ReadComConfig::ReadStdTempConfig()
{
	return ReadConfigByName("stdtemp");
}
/*��ȡ���������*/
ComInfoStruct ReadComConfig::ReadMeterConfigByNum(QString MeterNum)
{
	QRegExp rx("[0-9]{1,2}");
	if (!rx.exactMatch(MeterNum))
	{
		throw QString("Please input an integer!");
	}
	return ReadConfigByName("meter" + MeterNum);
}
/*��xml�е�id��ȡ����*/
ComInfoStruct ReadComConfig::ReadConfigByName(QString ConfigId)
{
	QMap<QString, QString> configs;
	ComInfoStruct com_info;
	try
	{
		OpenConfigFile();
	}
	catch(QString e)
	{
		throw e;
	}

	QDomElement root = m_doc.documentElement();
	if(root.tagName()!= "configs")
		throw "file format is invalid";

	QDomNode n;
	//�ж��Ƿ��ȡ���������
	if (ConfigId.contains("meter"))
		n = root.lastChild().firstChild();
	else
		n = root.firstChild();

	while ( !n.isNull() )
	{
		QDomElement e = n.toElement();
		if( !e.isNull())
		{
			if( e.tagName() == "config" && e.attribute("id") == ConfigId)//����id��
			{
				QDomNodeList list = e.childNodes(); //���Ԫ��e�������ӽڵ���б�(com�š������ʡ�У��λ��)
				for(int i=0; i<list.count(); i++) //�������б�
				{
					QDomNode node = list.at(i);
					configs[node.nodeName()] = node.firstChild().nodeValue();
				}
			}      
		}
		n = n.nextSibling();
	}
	QString sep="#SEP#";
	com_info.portName = configs["com"].split(sep)[0];
	com_info.baudRate = configs["baud"].split(sep)[0].toInt();
	com_info.dataBit = configs["bits"].split(sep)[0].toInt();
	com_info.parity = configs["chkbit"].split(sep)[0].toInt();
	com_info.stopBit = configs["endbit"].split(sep)[0].toInt();
	return com_info;
}



QStringList ReadComConfig::ReadIndexByName(QString ConfigId)
{
	QMap<QString, QString> configs;
	QStringList com_info;
	try
	{
		OpenConfigFile();
	}
	catch(QString e)
	{
		throw e;
	}

	QDomElement root = m_doc.documentElement();
	if(root.tagName()!= "configs")
		throw "file format is invalid";

	QDomNode n;
	//�ж��Ƿ��ȡ���������
	if (ConfigId.contains("meter"))
		n = root.lastChild().firstChild();
	else
		n = root.firstChild();

	while ( !n.isNull() )
	{
		QDomElement e = n.toElement();
		if( !e.isNull())
		{
			if( e.tagName() == "config" && e.attribute("id") == ConfigId)//����id��
			{
				QDomNodeList list = e.childNodes(); //���Ԫ��e�������ӽڵ���б�(com�š������ʡ�У��λ��)
				for(int i=0; i<list.count(); i++) //�������б�
				{
					QDomNode node = list.at(i);
					configs[node.nodeName()] = node.firstChild().nodeValue();
				}
			}      
		}
		n = n.nextSibling();
	}
	QString sep="#SEP#";
	com_info.append(configs["com"].split(sep)[1]);
	com_info.append(configs["baud"].split(sep)[1]);
	com_info.append(configs["bits"].split(sep)[1]);
	com_info.append(configs["chkbit"].split(sep)[1]);
	com_info.append(configs["endbit"].split(sep)[1]);
	return com_info;
}

/*���ļ�����*/
bool ReadComConfig::OpenConfigFile()
{
	QFile file( ConfigFileName );
	if( !file.open( QFile::ReadOnly | QFile::Text  ) )
	{
		throw QString("Can not open file: " + ConfigFileName);
		return false;
	}
	if( !m_doc.setContent( &file ) )
	{
		throw QString("Can not setContent file: " + ConfigFileName);
		file.close();
		return false;
	}
	file.close();
	return true;
}