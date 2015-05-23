#ifndef READCOMCONFIG_H
#define READCOMCONFIG_H

#include <QtXml/QtXml>
#include <QSettings>
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
	QSettings* m_com_settings;
	ComInfoStruct ReadConfigByName(QString ConfigId);
};

#endif // READCOMCONFIG_H