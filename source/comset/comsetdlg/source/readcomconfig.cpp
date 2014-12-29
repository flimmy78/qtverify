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

#include "readcomconfig.h"
#include "commondefine.h"

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

ComInfoStruct ReadComConfig::ReadMeterConfigByNum(int MeterNum)
{
	return ReadMeterConfigByNum(QString::number(MeterNum));
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
	//QString sep="#SEP#";
	com_info.portName = configs["com"].split(SEP)[0];
	com_info.baudRate = configs["baud"].split(SEP)[0].toInt();
	com_info.dataBit = configs["bits"].split(SEP)[0].toInt();
	com_info.parity = configs["chkbit"].split(SEP)[0].toInt();
	com_info.stopBit = configs["endbit"].split(SEP)[0].toInt();
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
	//QString sep="#SEP#";
	com_info.append(configs["com"].split(SEP)[1]);
	com_info.append(configs["baud"].split(SEP)[1]);
	com_info.append(configs["bits"].split(SEP)[1]);
	com_info.append(configs["chkbit"].split(SEP)[1]);
	com_info.append(configs["endbit"].split(SEP)[1]);
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

/********************************************************************** */
/*  ���ݶ˿ںŷ��ض�Ӧ�ı�λ��                                          */
/*  ����: QString comName, �˿�����,����"COM1"                          */
/*  ����ֵ:int MeterNum, ����������ļ��гɹ����ҵ���λ��, �򷵻ش˱�λ�� */
/*         ʧ��, ���� -1
/************************************************************************/
int ReadComConfig::getMeterPosByComName(QString comName)
{
		ComInfoStruct meterConfigSTR;
		for (int i=1; i <= METER_QUANTITY; i++)
		{
			meterConfigSTR = ReadMeterConfigByNum(i);
			if (meterConfigSTR.portName == comName)			
				return i;			
		}
		return -1;
}