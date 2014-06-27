#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtGui/QMessageBox>

#include "qtexdb.h"


int testFunc(int a, int b)
{
	printf_s("%d + %d = %d\n", a, b, (a+b));
	return (a + b);
}

CBaseExdb::CBaseExdb()
{
	WriteSettings();
	ReadSettings();
}

CBaseExdb::~CBaseExdb()
{

}

void CBaseExdb::WriteSettings()
{
	char filename[255];
	char* runhome = getenv( "RUNHOME" );
#ifdef __unix
	sprintf( filename, "%s/ini/Option.ini", runhome );
#else
	sprintf( filename, "%s\\ini\\Option.ini", runhome );
#endif

	QSettings settings(filename, QSettings::IniFormat); // ��ǰĿ¼��INI�ļ�
	settings.beginGroup("DevOption");
	settings.setValue("mainFun", 25);
	settings.setValue("subFun", 40);
	settings.setValue("service", "sonics");
	settings.endGroup();
}

void CBaseExdb::ReadSettings()
{
	char filename[255];
	char* runhome = getenv( "RUNHOME" );
#ifdef __unix
	sprintf( filename, "%s/ini/Option.ini", runhome );
#else
	sprintf( filename, "%s\\ini\\Option.ini", runhome );
#endif

	QSettings settings(filename, QSettings::IniFormat); // ��ǰĿ¼��INI�ļ�

	int mainFun = settings.value("DevOption/mainFun").toInt();
	int subFun = settings.value("DevOption/subFun").toInt();
	QString service = settings.value("DevOption/service").toString();

	qDebug() << "mainFun" << mainFun;
	qDebug() << "subFun" << subFun;
	qDebug() << "service" << service;
}

int CBaseExdb::startdb()
{
	char dbname[100];
	sprintf_s(dbname, "%s/database/mysqlite375.db", getenv("RUNHOME"));
	db = QSqlDatabase::addDatabase("QSQLITE"); // ʹ��sqlite���ݿ����� 
	db.setDatabaseName(dbname);
	bool ok = db.open(); // �����������ݿ�

	if(ok) // �ɹ��������ݿ�
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CBaseExdb::closedb()
{
	db.close();
}

int CBaseExdb::getMeterStandard(int& num, MeterStandard_PTR &ptr)
{
	int i = 0;
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	bool a = query.driver()->hasFeature(QSqlDriver::Transactions);
	if(query.exec("select count(*) from t_meter_standard")) // t_meter_standard ��ļ�¼��
	{
		// ���β�ѯ�ɹ�
		query.first(); //��һ����¼
 		num = query.value(0).toInt();
		ptr = new MeterStandard_STR[num];
		memset(ptr, 0, sizeof(MeterStandard_STR)*num);
	}

	if(query.exec("select id,name from t_meter_standard order by id"))
	{
		while(query.next())
		{
			ptr[i].id = query.value(0).toInt();
			strcpy(ptr[i].name, query.value(1).toString().toAscii());
			i++;
		}
	}
	else  // �����ѯʧ�ܣ�������ķ����õ��������ݿⷵ�ص�ԭ��
	{
		QSqlError error = query.lastError();
		return false;
	}

	return true;
}


int CBaseExdb::getMeterType(int& num, MeterType_PTR &ptr)
{
	int i = 0;
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	bool a = query.driver()->hasFeature(QSqlDriver::QuerySize);
	if(query.exec("select count(*) from t_meter_type")) // t_meter_type ��ļ�¼��
	{
		// ���β�ѯ�ɹ�
		query.first(); //��һ����¼
		num = query.value(0).toInt();
		ptr = new MeterType_STR[num];
		memset(ptr, 0, sizeof(MeterType_STR)*num);
	}

	if(query.exec("select id,name from t_meter_type order by id"))
	{
		while(query.next())
		{
			ptr[i].id = query.value(0).toInt();
			strcpy(ptr[i].name, query.value(1).toString().toLocal8Bit()); //���ֱ���
			i++;
		}
	}
	else  // �����ѯʧ�ܣ�������ķ����õ��������ݿⷵ�ص�ԭ��
	{
		QSqlError error = query.lastError();
		return false;
	}

	return true;
}
