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
	CReport(const QString& condition);
	~CReport();
public:
	void writeRpt();//д����

private:
	QSettings* m_rpt_config;//��������
	QString m_template_file;//ģ���ļ�·��
	QString m_rpt_file;//�����ļ�·��
	QString m_rpt_config_file;//����������ļ�·��
	QString m_temp_file;//��ʱ�ļ�·��
	QString m_query_Sql;//��ѯ���ݵ�sql���
	QString m_query_condition;//sql���Ĳ�ѯ����

	QStringList m_headList;//��ͷ�ֶ��б�
	QStringList m_bodyList;//�����ֶ��б�
	QString		m_table_name;//�����Ӧ�ı�������ͼ��
	QString		m_condition;//�����ѯ����
	QSqlQuery*	m_query;//��ѯ
	Book* m_book;//����
	Sheet* m_sheet;//��
	
	void writeHead();//д��ͷ
	void writeBody();//д����
	void readTblName();//�������ͼ��
	void readConfigTHead();//ȡ�������ļ�������ͷ
	void readConfigTBody();//ȡ�������ļ���������
	void getRptSQL();//��֯��ѯSQL���
	void getDbData();//��ȡ�������ݼ�
	void deleteLog();//ɾ�����еİ�Ȩ��Ϣ��������ʱ���ɵ��ļ����Ƶ�Ŀ���ļ���	 
};
#endif