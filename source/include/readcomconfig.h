#ifndef READCOMCONFIG_H
#define READCOMCONFIG_H

#include <QtXml/QtXml>
#include <QSettings>
#include "basedef.h"
#include "systemsetdlg_global.h"

#define METER_STR	"Meter"
#define meter(a) QString(METER_STR).append("_").append(QString::number(a))

class SYSTEMSETDLG_EXPORT ReadComConfig
{
public:
	ReadComConfig();
	~ReadComConfig();
	QStringList ReadIndexByName(QString ConfigId);//��ȡ�����ļ�����Ӧ���õ�����ֵ
	/************��ȡ�����ļ�****************/
	ComInfoStruct ReadValveConfig();
	ComInfoStruct ReadValveConfig2();
	ComInfoStruct ReadBalanceConfig();
	ComInfoStruct ReadBalanceConfig2();
	ComInfoStruct ReadTempConfig();
	ComInfoStruct ReadStdTempConfig();
	ComInfoStruct ReadInstStdConfig();
	ComInfoStruct ReadAccumStdConfig();
	ComInfoStruct ReadMeterConfigByNum(int MeterNum);
	ComInfoStruct ReadMeterConfigByNum(QString MeterNum);
	int getMeterPosByComName(QString comName);//���ݴ��������ض�Ӧ�ı�λ��
	void getBalancePara(float &maxWht, float &bottomWht);
	void getBalancePara2(float &maxWht, float &bottomWht);
	int getBalanceType();
	int getBalanceType2();
	int getDeviceInfoID();
	/***************************************************/
private:
	QSettings* m_com_settings;
	ComInfoStruct ReadConfigByName(QString ConfigId);
};

#endif // READCOMCONFIG_H