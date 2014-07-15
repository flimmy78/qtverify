/***********************************************
**  �ļ���:     qtexdb.cpp
**  ����:       ��װ�����ݿ������(SQLITE3)
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/25
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:   
***********************************************/

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtGui/QMessageBox>

#include "qtexdb.h"
#include "commondefine.h"

int testFunc(int a, int b)
{
	printf_s("%d + %d = %d\n", a, b, (a+b));
	return (a + b);
}

CBaseExdb::CBaseExdb()
{
}

CBaseExdb::~CBaseExdb()
{

}

int CBaseExdb::startdb()
{
	if (QSqlDatabase::contains("qt_sql_default_connection"))
	{
		db = QSqlDatabase::database("qt_sql_default_connection");
	}
	else
	{
		db = QSqlDatabase::addDatabase("QSQLITE");
	}

	char dbname[FILENAME_LENGTH];
	memset(dbname, 0, sizeof(char)*FILENAME_LENGTH);
	sprintf_s(dbname, "%s/database/mysqlite375.db", getenv("RUNHOME"));
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

//��ȡ���еı���
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

//��ȡ���еı�����
int CBaseExdb::getMeterType(int& num, MeterType_PTR &ptr)
{
	int i = 0;
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	bool a = query.driver()->hasFeature(QSqlDriver::QuerySize); //�Ƿ�֧��QuerySize����
	if(query.exec("select count(*) from t_meter_type")) // t_meter_type ��ļ�¼��
	{
		// ���β�ѯ�ɹ�
		query.first(); //��һ����¼
		num = query.value(0).toInt();
		ptr = new MeterType_STR[num];
		memset(ptr, 0, sizeof(MeterType_STR)*num);
	}

	if(query.exec("select id,desc from t_meter_type order by id"))
	{
		while(query.next())
		{
			ptr[i].id = query.value(0).toInt();
			strcpy(ptr[i].desc, query.value(1).toString().toLocal8Bit()); //���ֱ���
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


//��ȡ���е����쵥λ
int CBaseExdb::getManufacture(int& num, Manufacture_PTR &ptr)
{
	int i = 0;
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	if(query.exec("select count(*) from t_manufacture_tab")) // t_manufacture_tab ��ļ�¼��
	{
		// ���β�ѯ�ɹ�
		query.first(); //��һ����¼
		num = query.value(0).toInt();
		ptr = new Manufacture_STR[num];
		memset(ptr, 0, sizeof(Manufacture_STR)*num);
	}

	if(query.exec("select id,desc from t_manufacture_tab order by id"))
	{
		while(query.next())
		{
			ptr[i].id = query.value(0).toInt();
			strcpy(ptr[i].desc, query.value(1).toString().toLocal8Bit()); //���ֱ���
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
