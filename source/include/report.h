#ifndef REPORT_H
#define REPORT_H

#ifdef QEXCEL_DLL
#  ifdef WIN32
#  define REPORT_EXPORT __declspec(dllexport)
#  else
#  define REPORT_EXPORT
#  endif
#else
#  ifdef WIN32
#  define REPORT_EXPORT __declspec(dllimport)
#  else
#  define REPORT_EXPORT
#  endif
#endif

#include <QStringList>
#include <QSettings>
#include "libxl/libxl.h"
#include "basedef.h"

class REPORT_EXPORT CReport
{
public:
	CReport(const QString& condition);
	~CReport();
public:
	void writeRpt();//写报表

private:
	QSettings* rpt_config;
	QString template_file;//模板文件路径
	QString rpt_file;//报告文件路径
	QString rpt_config_file;//报告的配置文件路径
	QString temp_path;//系统临时文件路径
	Record_Quality_PTR verify_rec_ptr;//取出的数据记录

	void writeHead();//写表头
	void writeBody();//写表体
	QStringList readConfigTHead();//取出配置文件的配置头
	QStringList readConfigTBody();//取出配置文件的配置体
	QString getRptSQL();//组织查询SQL语句
	Record_Quality_PTR rec_ptr;//查询结果表 
};
#endif