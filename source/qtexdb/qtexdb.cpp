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

	if(query.exec("select f_id,f_name, F_Meter_Quantity from t_meter_standard order by f_id"))
	{
		while(query.next())
		{
			ptr[i].id = query.value(0).toInt();
			strcpy(ptr[i].name, query.value(1).toString().toAscii());
			ptr[i].quantity = query.value(2).toInt();
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

	if(query.exec("select f_id,f_name,f_desc from t_meter_type order by f_id"))
	{
		while(query.next())
		{
			ptr[i].id = query.value(0).toInt();
			strcpy(ptr[i].name, query.value(1).toString().toAscii());
			strcpy(ptr[i].desc, query.value(2).toString().toLocal8Bit()); //���ֱ���
			qDebug()<<ptr[i].desc<<"::"<<query.value(1).toString().toLocal8Bit();
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
	if(query.exec("select count(*) from t_manufacture_unit")) // t_manufacture_unit ��ļ�¼��
	{
		// ���β�ѯ�ɹ�
		query.first(); //��һ����¼
		num = query.value(0).toInt();
		ptr = new Manufacture_STR[num];
		memset(ptr, 0, sizeof(Manufacture_STR)*num);
	}

	QString testStr;
	if(query.exec("select f_id,f_name,f_desc from t_manufacture_unit order by f_id"))
	{
		while(query.next())
		{
			ptr[i].id = query.value(0).toInt();
			strcpy(ptr[i].name, query.value(1).toString().toAscii());
			testStr = query.value(2).toString();
			strcpy(ptr[i].desc, query.value(2).toString().toLocal8Bit()); //���ֱ���
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

/*
 *  ��ȡ������ȱ��Ĭ�ϼ춨����
 *  num: ��ѯ����ļ�¼��
 *  ptr: �����ݱ�t_meter_default_params��Ӧ�Ľṹ
 *  stand_id: ���������ֵ, �������������ϵ�comboBox
 */
int CBaseExdb::getDftDBinfo(int &num, DftDbInfo_PTR &ptr, int stand_id)
{
	int i = 0;
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	bool a = query.driver()->hasFeature(QSqlDriver::Transactions);
	QString sql = "select count(*) from t_meter_default_params where f_standard_id = " + QString::number(stand_id);
	if(query.exec(sql)) // t_meter_standard ��ļ�¼��
	{
		// ���β�ѯ�ɹ�
		query.first(); //��һ����¼
		num = query.value(0).toInt();
		ptr = new DftDbInfo_STR[num];
		memset(ptr, 0, sizeof(DftDbInfo_STR)*num);
	}
	sql = "select f_id, f_standard_id, f_nflowpoint, f_upperflow, f_verifyflow, f_flowquantity, f_pumpfrequencey, f_valve_i, f_seq_i, F_Flow_idx from t_meter_default_params where f_standard_id = " + QString::number(stand_id) + " order by F_Flow_idx";
	if(query.exec(sql))
	{
		while(query.next())
		{
			ptr[i].id = query.value(0).toInt();
			ptr[i].stand_id = query.value(1).toInt();
			ptr[i].n_flow = query.value(2).toFloat();
			ptr[i].upper_flow = query.value(3).toFloat();
			ptr[i].v_flow = query.value(4).toFloat();
			ptr[i].v_quan = query.value(5).toFloat();
			ptr[i].pump_freq = query.value(6).toFloat();
			ptr[i].vale_num = query.value(7).toInt();
			ptr[i].seq = query.value(8).toInt();
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

int CBaseExdb::insertVerfiyRecords(int num, Record_Quality_PTR ptr)
{

	return true;
}