#include <QDebug>
#include <QProcessEnvironment>
#include "report.h"


CReport::CReport(const QString& condition)
{
	      temp_path = QProcessEnvironment::systemEnvironment().value("TEMP");
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");
#ifdef Q_OS_LINUX
	rpt_config_file = runhome + "\/ini\/rptconfig_common.ini";
	template_file   = runhome + "\/doc\/rpt-template.xls";
#elif defined (Q_OS_WIN)
	rpt_config_file = runhome + "\\ini\\rptconfig_common.ini";
	template_file   = runhome + "\\doc\\rpt-template.xls";
#endif
	rpt_config = new QSettings(rpt_config_file, QSettings::IniFormat);
}

CReport::~CReport()
{
	if (rpt_config)
	{
		delete rpt_config;
		rpt_config = NULL;
	}
	
	qDebug()<<"destructing report";
}

void CReport::writeRpt()
{
	QStringList headList = readConfigTHead();
	QStringList bodyList = readConfigTBody();

}
void CReport::writeHead()
{

}

void CReport::writeBody()
{

}

QStringList CReport::readConfigTHead()
{
	 rpt_config->beginGroup("tablehead");
	 QStringList headList = rpt_config->allKeys();
	 rpt_config->endGroup();
	 return headList;
}

QStringList CReport::readConfigTBody()
{
	rpt_config->beginGroup("tablebody");
	QStringList bodyList = rpt_config->allKeys();
	rpt_config->endGroup();
	return bodyList;
}

QString CReport::getRptSQL()
{
   return "";
}
