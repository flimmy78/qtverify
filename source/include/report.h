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
	CReport(const QString& condition);// condition, ��" where "��ͷ�ĺϷ���sql��ѯ����
	~CReport();
public:
	void writeRpt();//д����
	void saveTo(QString);//���汨��ָ���ļ���
private:
	QSettings* m_rpt_config;//��������
	QString m_template_file;//ģ���ļ�·��
	QString m_rpt_file;//�����ļ�·��
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
	Format* m_format;//��Ԫ���ʽ
	Font* m_font;//��Ԫ������
private:
	void writeHead();//д��ͷ
	void writeBody();//д����
	void mergeCells(int start_row, int end_row, int start_col, int end_col);//��start_row��end_row�� ��ֵ��ȵĵ�Ԫ��ϲ�
	void writeBool(int start_with_row, int end_with_row, int start_with_col, int end_with_col);//��start_with_row��end_with_row�� ��boolֵ�ĵ�Ԫ��ϲ�
	void readTblName();//�������ͼ��
	void readConfigTHead();//ȡ�������ļ�������ͷ
	void readConfigTBody();//ȡ�������ļ���������
	void getRptSQL();//��֯��ѯSQL���
	void getDbData();//��ȡ�������ݼ�
	void deleteLog();//ɾ�����еİ�Ȩ��Ϣ��������ʱ���ɵ��ļ����Ƶ�Ŀ���ļ���	 
};
#endif