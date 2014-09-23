/***********************************************
**  文件名:     ReadComConfig.cpp
**  功能:       读取 $RUNHOME/ini/comconfig.xml文件的串口配置
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/16
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

#include "ReadComConfig.h"
#include "comsetdlg.h"
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
/*读取阀门设置*/
ComInfoStruct ReadComConfig::ReadValveConfig()
{
	return ReadConfigByName("valve");
}
/*读取天平设置*/
ComInfoStruct ReadComConfig::ReadBalanceConfig()
{
	return ReadConfigByName("balance");
}
/*读取温度采集设置*/
ComInfoStruct ReadComConfig::ReadTempConfig()
{
	return ReadConfigByName("temp");
}
/*读取标准温度计设置*/
ComInfoStruct ReadComConfig::ReadStdTempConfig()
{
	return ReadConfigByName("stdtemp");
}
/*读取被检表设置*/
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

/*按xml中的id读取设置*/
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
	//判断是否读取被检表配置
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
	//判断是否读取被检表配置
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
	//QString sep="#SEP#";
	com_info.append(configs["com"].split(SEP)[1]);
	com_info.append(configs["baud"].split(SEP)[1]);
	com_info.append(configs["bits"].split(SEP)[1]);
	com_info.append(configs["chkbit"].split(SEP)[1]);
	com_info.append(configs["endbit"].split(SEP)[1]);
	return com_info;
}

/*打开文件测试*/
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
/*  根据端口号返回对应的表位号                                             */
/*  参数: QString comNum, 端口名称                                       */
/*  返回值:int MeterNum, 如果在配置文件中成功查找到表位号, 则返回此表位号		*/
/*         失败, 返回 -1
/************************************************************************/
int ReadComConfig::readMeterNumByComNum(QString comNum)
{
		ComInfoStruct meterConfigSTR;
		for (int i=1; i <= METER_QUANTITY; i++)
		{
			meterConfigSTR = ReadMeterConfigByNum(i);
			if (meterConfigSTR.portName == comNum)			
				return i;			
		}
		return -1;
}