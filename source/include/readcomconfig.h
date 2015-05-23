#ifndef READCOMCONFIG_H
#define READCOMCONFIG_H

#include <QtXml/QtXml>
#include <QSettings>
#include "basedef.h"
#include "systemsetdlg_global.h"

#define METER_STR	"Meter"
#define meter(a) "Meter_"#a

class SYSTEMSETDLG_EXPORT ReadComConfig
{
public:
	ReadComConfig();
	~ReadComConfig();
	QStringList ReadIndexByName(QString ConfigId);//读取配置文件中相应配置的索引值
	/************读取配置文件****************/
	ComInfoStruct ReadValveConfig();
	ComInfoStruct ReadBalanceConfig();
	ComInfoStruct ReadTempConfig();
	ComInfoStruct ReadStdTempConfig();
	ComInfoStruct ReadMeterConfigByNum(QString MeterNum);
	ComInfoStruct ReadMeterConfigByNum(int MeterNum);
	int getMeterPosByComName(QString comName);//根据串口名返回对应的表位号
	/***************************************************/
private:
	QSettings* m_com_settings;
	ComInfoStruct ReadConfigByName(QString ConfigId);
};

#endif // READCOMCONFIG_H