#ifndef READCOMCONFIG_H
#define READCOMCONFIG_H

#include <QtXml/QtXml>

#include "comsetdlg_global.h"

class COMSETDLG_EXPORT ReadComConfig
{
public:
	ReadComConfig();
	~ReadComConfig();
	/************∂¡»°≈‰÷√Œƒº˛****************/
	QMap<QString, QString> ReadValeConfig();
	QMap<QString, QString> ReadBalanceConfig();
	QMap<QString, QString> ReadTempConfig();
	QMap<QString, QString> ReadStdTempConfig();
	QMap<QString, QString> ReadMeterConfigByNum(QString MeterNum);
	/***************************************************/
private:
	QString ConfigFileName;
	QDomDocument m_doc;
	QMap<QString, QString> ReadConfigByName(QString ConfigId);
	bool OpenConfigFile();
};

#endif // READCOMCONFIG_H