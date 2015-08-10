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

#define TEMP_QUERY_TBL_NAME		QString("T_Temp_Query_Result")//查询结果临时表
#define DROP_TBL_STMT			QString("drop table if exists ").append(TEMP_QUERY_TBL_NAME).append(";")
#define CREATE_TEMP_TBL_STMT	QString("CREATE table %1 as select * from %2 where ").arg(TEMP_QUERY_TBL_NAME).arg(m_table).append(m_condition).append(";")
#define QUERY_CREATE_VIEW_STMT	QString("select F_STMT from T_Create_Query_View_Stmt where F_id=%1").arg(m_queryStmtId)
#define DROP_TEMP_VIEW_STMT		QString("drop view if exists %1 ;").arg(m_view)

using namespace libxl;

class REPORT_EXPORT CReport
{
public:
	CReport(const QString& condition);// condition, 以" where "开头的合法的sql查询条件
	~CReport();
public:
	void writeRpt();//写报表
	void setIniName(QString);//设置报表配置文件名
	void saveTo(QString);//保存报表到指定文件夹
private:
	QString		m_rptIniName;//报表的配置文件名
	QSettings*	m_rpt_config;//报表配置
	QString		m_template_file;//模板文件路径
	QString		m_temp_file;//临时文件路径
	QString		m_query_Sql;//查询数据的sql语句
	QString		m_query_condition;//sql语句的查询条件

	QStringList m_headList;//表头字段列表
	QStringList m_bodyList;//表体字段列表
	QString		m_queryStmtId;//创建临时视图时, 语句对应的F_ID
	QString		m_table;//报表对应的主表名
	QString		m_view;//报表对应的视图名

	QString		m_condition;//报表查询条件
	QSqlQuery*	m_query;//查询
	Book*		m_book;//报表
	Sheet*		m_sheet;//表单
	Format*		m_format;//单元格格式
	Font*		m_font;//单元格字体
private:
	void writeHead();//写表头
	void writeBody();//写表体
	void mergeBody();//写入合并
	void mergeSingleCol(QString);//合并列中的相似值
	void mergeSingleCol(QString, int);//合并列中的相似值
	void mergeBool(QString, QStringList);//合并合格与不合格
	void mergeRowId(QString, QString);//合并序号
	void readTblName();//读表或视图名
	void readConfigTHead();//取出配置文件的配置头
	void readConfigTBody();//取出配置文件的配置体
	void getRptSQL();//组织查询SQL语句
	void getDbData();//获取报表数据集
	void deleteLog();//删除首行的版权信息，并将临时生成的文件复制到目标文件夹	 
};
#endif