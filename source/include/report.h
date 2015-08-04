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

#define TEMP_QUERY_VIEW_NAME	QString("V_Temp_Query_Result")//��ʱ��ѯ�����ͼ
#define DROP_TBL_STMT			QString("drop view if exists ").append(TEMP_QUERY_VIEW_NAME).append(";")
#define CREATE_TEMP_TBL_STMT	QString("\nCREATE view %1 as ").arg(TEMP_QUERY_VIEW_NAME).append(m_query_Sql).append(";")
#define QUERY_TEMP_TBL_STMT		QString("select * from %1").arg(TEMP_QUERY_VIEW_NAME)

using namespace libxl;

class REPORT_EXPORT CReport
{
public:
	CReport(const QString& condition);// condition, ��" where "��ͷ�ĺϷ���sql��ѯ����
	~CReport();
public:
	void writeRpt();//д����
	void setIniName(QString);//���ñ��������ļ���
	void saveTo(QString);//���汨��ָ���ļ���
private:
	QString		m_rptIniName;//����������ļ���
	QSettings*	m_rpt_config;//��������
	QString		m_template_file;//ģ���ļ�·��
	QString		m_rpt_file;//�����ļ�·��
	QString		m_temp_file;//��ʱ�ļ�·��
	QString		m_query_Sql;//��ѯ���ݵ�sql���
	QString		m_query_condition;//sql���Ĳ�ѯ����

	QStringList m_headList;//��ͷ�ֶ��б�
	QStringList m_bodyList;//�����ֶ��б�
	QString		m_table_name;//�����Ӧ�ı�������ͼ��
	QString		m_condition;//�����ѯ����
	QSqlQuery*	m_query;//��ѯ
	Book*		m_book;//����
	Sheet*		m_sheet;//��
	Format*		m_format;//��Ԫ���ʽ
	Font*		m_font;//��Ԫ������
private:
	void writeHead();//д��ͷ
	void writeBody();//д����
	void mergeBody();//д��ϲ�
	void mergeSingleCol(QString);//�ϲ����е�����ֵ
	void mergeSingleCol(QString, int);//�ϲ����е�����ֵ
	void mergeBool(QString, QStringList);//�ϲ��ϸ��벻�ϸ�
	void mergeRowId(QString, QString);//�ϲ����
	void readTblName();//�������ͼ��
	void readConfigTHead();//ȡ�������ļ�������ͷ
	void readConfigTBody();//ȡ�������ļ���������
	void getRptSQL();//��֯��ѯSQL���
	void getDbData();//��ȡ�������ݼ�
	void deleteLog();//ɾ�����еİ�Ȩ��Ϣ��������ʱ���ɵ��ļ����Ƶ�Ŀ���ļ���	 
};
#endif