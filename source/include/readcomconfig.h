#ifndef READCOMCONFIG_H
#define READCOMCONFIG_H

#include <QtXml/QtXml>

#include "basedef.h"
#include "systemsetdlg_global.h"

class SYSTEMSETDLG_EXPORT ReadComConfig
{
public:
	ReadComConfig();
	~ReadComConfig();
	QStringList ReadIndexByName(QString ConfigId);//��ȡ�����ļ�����Ӧ���õ�����ֵ
	/************��ȡ�����ļ�****************/
	ComInfoStruct ReadValveConfig();
	ComInfoStruct ReadBalanceConfig();
	ComInfoStruct ReadTempConfig();
	ComInfoStruct ReadStdTempConfig();
	ComInfoStruct ReadMeterConfigByNum(QString MeterNum);
	ComInfoStruct ReadMeterConfigByNum(int MeterNum);
	int getMeterPosByComName(QString comName);//���ݴ��������ض�Ӧ�ı�λ��
	/***************************************************/
private:
	QString ConfigFileName;
	QDomDocument m_doc;
	ComInfoStruct ReadConfigByName(QString ConfigId);
	bool OpenConfigFile();
};

#endif // READCOMCONFIG_H