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
#include "algorithm.h"
#include "commondefine.h"

ReadComConfig::ReadComConfig()
{
	m_com_settings = new QSettings(getFullIniFileName("comconfig.ini"), QSettings::IniFormat);
}

ReadComConfig::~ReadComConfig()
{
	if (NULL != m_com_settings)
	{
		delete m_com_settings;
		m_com_settings = NULL;
	}
}

//��ȡ��������
ComInfoStruct ReadComConfig::ReadValveConfig()
{
	return ReadConfigByName("Valve");
}

//��ȡ��ƽ����
ComInfoStruct ReadComConfig::ReadBalanceConfig()
{
	return ReadConfigByName("Balance");
}

//��ȡ�¶Ȳɼ�����
ComInfoStruct ReadComConfig::ReadTempConfig()
{
	return ReadConfigByName("TempSenor");
}

//��ȡ��׼�¶ȼ�����
ComInfoStruct ReadComConfig::ReadStdTempConfig()
{
	return ReadConfigByName("StdTmpSensor");
}

//��ȡ���������
ComInfoStruct ReadComConfig::ReadMeterConfigByNum(QString MeterNum)
{
	QRegExp rx("[0-9]{1,2}");
	if (!rx.exactMatch(MeterNum))
	{
		throw QString("Please input an integer!");
	}
	return ReadConfigByName("Meter_" + MeterNum);
}

ComInfoStruct ReadComConfig::ReadMeterConfigByNum(int MeterNum)
{
	return ReadMeterConfigByNum(QString::number(MeterNum));
}

//��xml�е�id��ȡ����
ComInfoStruct ReadComConfig::ReadConfigByName(QString ConfigId)
{
	ComInfoStruct com_info;

	int meterNum;
	//�ж��Ƿ��ȡ���������
	if (ConfigId.contains("Meter"))
	{
		m_com_settings->beginReadArray("Meters");
		meterNum = ConfigId.split('_')[1].toInt();
		m_com_settings->setArrayIndex(meterNum-1);
	}
	else
		m_com_settings->beginGroup(ConfigId);

	com_info.portName = m_com_settings->value("com_name").toString().split(SEP)[0];
	com_info.baudRate = m_com_settings->value("baud").toString().split(SEP)[0].toInt();
	com_info.dataBit  = m_com_settings->value("bits").toString().split(SEP)[0].toInt();
	com_info.parity   = m_com_settings->value("chkbit").toString().split(SEP)[0].toInt();
	com_info.stopBit  = m_com_settings->value("endbit").toString().split(SEP)[0].toInt();

	if (ConfigId.contains("Meter"))
		m_com_settings->endArray();
	else
		m_com_settings->endGroup();

	return com_info;
}

QStringList ReadComConfig::ReadIndexByName(QString ConfigId)
{
	QStringList com_info;
	int meterNum;
	//�ж��Ƿ��ȡ���������
	if (ConfigId.contains("Meter"))
	{
		m_com_settings->beginReadArray("Meters");
		meterNum = ConfigId.split('_')[1].toInt();
		m_com_settings->setArrayIndex(meterNum-1);
	}
	else
		m_com_settings->beginGroup(ConfigId);

	com_info.append(m_com_settings->value("com_name").toString().split(SEP)[1]);
	com_info.append(m_com_settings->value("baud").toString().split(SEP)[1]);
	com_info.append(m_com_settings->value("bits").toString().split(SEP)[1]);
	com_info.append(m_com_settings->value("chkbit").toString().split(SEP)[1]);
	com_info.append(m_com_settings->value("endbit").toString().split(SEP)[1]);

	if (ConfigId.contains("meter"))
		m_com_settings->endArray();
	else
		m_com_settings->endGroup();

	return com_info;
}

/*
**  ���ݶ˿ںŷ��ض�Ӧ�ı�λ��
**  ����: QString comName, �˿�����,����"COM1"
**  ����ֵ:����������ļ��гɹ����ҵ���λ��, �򷵻ظñ�λ��;������Ҵ˱�λ��ʧ��,�򷵻�-1
*/
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