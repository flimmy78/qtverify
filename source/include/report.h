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
	void writeRpt();//д����

private:
	QSettings* rpt_config;
	QString template_file;//ģ���ļ�·��
	QString rpt_file;//�����ļ�·��
	QString rpt_config_file;//����������ļ�·��
	QString temp_path;//ϵͳ��ʱ�ļ�·��
	Record_Quality_PTR verify_rec_ptr;//ȡ�������ݼ�¼

	void writeHead();//д��ͷ
	void writeBody();//д����
	QStringList readConfigTHead();//ȡ�������ļ�������ͷ
	QStringList readConfigTBody();//ȡ�������ļ���������
	QString getRptSQL();//��֯��ѯSQL���
	Record_Quality_PTR rec_ptr;//��ѯ����� 
};
#endif