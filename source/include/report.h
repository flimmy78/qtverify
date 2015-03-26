#ifndef REPORT_H
#define REPORT_H

#ifdef REPORT_DLL
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
	
#include <QDebug>
#include <QProcessEnvironment>
#include <QFile>
#include <QDateTime>
#include <QStringList>
#include <QSettings>
#include <QSqlRecord>

#include "libxl/libxl.h"
#include "basedef.h"
#include "qtexdb.h"
#include "qexcel.h"

using namespace libxl;

class REPORT_EXPORT CReport
{
public:
	CReport(const QString& condition);// condition, 以" where "开头的合法的sql查询条件
	~CReport();
public:
	void writeRpt();//写报表
	void saveTo(QString);//保存报表到指定文件夹
private:
	QSettings* m_rpt_config;//报表配置
	QString m_template_file;//模板文件路径
	QString m_rpt_file;//报告文件路径
	QString m_rpt_config_file;//报告的配置文件路径
	QString m_temp_file;//临时文件路径
	QString m_query_Sql;//查询数据的sql语句
	QString m_query_condition;//sql语句的查询条件

	QStringList m_headList;//表头字段列表
	QStringList m_bodyList;//表体字段列表
	QString		m_table_name;//报表对应的表名或视图名
	QString		m_condition;//报表查询条件
	QSqlQuery*	m_query;//查询
	Book* m_book;//报表
	Sheet* m_sheet;//表单
	Format* m_format;//单元格格式
	Font* m_font;//单元格字体
private:
	void writeHead();//写表头
	void writeBody();//写表体
	void mergeCells(int start_row, int end_row, int start_col, int end_col);//从start_row到end_row， 将值相等的单元格合并
	void writeBool(int start_with_row, int end_with_row, int start_with_col, int end_with_col);//从start_with_row到end_with_row， 将bool值的单元格合并
	void readTblName();//读表或视图名
	void readConfigTHead();//取出配置文件的配置头
	void readConfigTBody();//取出配置文件的配置体
	void getRptSQL();//组织查询SQL语句
	void getDbData();//获取报表数据集
	void deleteLog();//删除首行的版权信息，并将临时生成的文件复制到目标文件夹	 
};
#endif