#ifndef READCOMCONFIG_H
#define READCOMCONFIG_H

#include <QtXml/QtXml>

#include "comsetdlg_global.h"
#include "comsetdlg.h"

class COMSETDLG_EXPORT ReadComConfig
{
public:
	ReadComConfig();
	~ReadComConfig();
	
	/************∂¡»°≈‰÷√Œƒº˛****************/
	ComInfoStruct ReadValeConfig();
	ComInfoStruct ReadBalanceConfig();
	ComInfoStruct ReadTempConfig();
	ComInfoStruct ReadStdTempConfig();
	ComInfoStruct ReadMeterConfigByNum(QString MeterNum);
	/***************************************************/
private:
	QString ConfigFileName;
	QDomDocument m_doc;
	ComInfoStruct ReadConfigByName(QString ConfigId);
	bool OpenConfigFile();
};

#endif // READCOMCONFIG_H