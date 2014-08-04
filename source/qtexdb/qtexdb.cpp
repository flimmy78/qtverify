/***********************************************
**  文件名:     qtexdb.cpp
**  功能:       封装的数据库管理类(SQLITE3)
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/25
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/06 第一版
**  内容包含:
**  说明:
**  更新记录:   
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
	bool ok = db.open(); // 尝试连接数据库

	if(ok) // 成功连上数据库
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

//获取所有的表规格
int CBaseExdb::getMeterStandard(int& num, MeterStandard_PTR &ptr)
{
	int i = 0;
	QSqlQuery query; // 新建一个查询的实例
	bool a = query.driver()->hasFeature(QSqlDriver::Transactions);
	if(query.exec("select count(*) from t_meter_standard")) // t_meter_standard 表的记录数
	{
		// 本次查询成功
		query.first(); //第一条记录
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
	else  // 如果查询失败，用下面的方法得到具体数据库返回的原因
	{
		QSqlError error = query.lastError();
		return false;
	}

	return true;
}

/************************************************************************/
/* 按主键获取对应表规格的最大检定数量                       */
/************************************************************************/
int CBaseExdb::getMaxMeterByIdx(int idx)
{
	MeterStandard_PTR ptr;
	QSqlQuery query; // 新建一个查询的实例
	bool a = query.driver()->hasFeature(QSqlDriver::Transactions);
	QString sql = "select F_Meter_Quantity from t_meter_standard where f_id = "+ QString::number(idx);
	if(query.exec(sql))
	{
		while(query.next())
		{
			return query.value(0).toInt();
		}
	}
	else  // 如果查询失败，用下面的方法得到具体数据库返回的原因
	{
		QSqlError error = query.lastError();
		return -1;
	}
}

//获取所有的表类型
int CBaseExdb::getMeterType(int& num, MeterType_PTR &ptr)
{
	int i = 0;
	QSqlQuery query; // 新建一个查询的实例
	bool a = query.driver()->hasFeature(QSqlDriver::QuerySize); //是否支持QuerySize特性
	if(query.exec("select count(*) from t_meter_type")) // t_meter_type 表的记录数
	{
		// 本次查询成功
		query.first(); //第一条记录
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
			strcpy(ptr[i].desc, query.value(2).toString().toLocal8Bit()); //汉字编码
			qDebug()<<ptr[i].desc<<"::"<<query.value(1).toString().toLocal8Bit();
			i++;
		}
	}
	else  // 如果查询失败，用下面的方法得到具体数据库返回的原因
	{
		QSqlError error = query.lastError();
		return false;
	}

	return true;
}


//获取所有的制造单位
int CBaseExdb::getManufacture(int& num, Manufacture_PTR &ptr)
{
	int i = 0;
	QSqlQuery query; // 新建一个查询的实例
	if(query.exec("select count(*) from t_manufacture_unit")) // t_manufacture_unit 表的记录数
	{
		// 本次查询成功
		query.first(); //第一条记录
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
			strcpy(ptr[i].desc, query.value(2).toString().toLocal8Bit()); //汉字编码
			i++;
		}
	}
	else  // 如果查询失败，用下面的方法得到具体数据库返回的原因
	{
		QSqlError error = query.lastError();
		return false;
	}

	return true;
}

/*
 *  获取各规格热表的默认检定参数
 *  num: 查询结果的记录数
 *  ptr: 与数据表t_meter_default_params对应的结构
 *  stand_id: 表规格的主键值, 用于索引界面上的comboBox
 */
int CBaseExdb::getDftDBinfo(int &num, DftDbInfo_PTR &ptr, int stand_id)
{
	int i = 0;
	QSqlQuery query; // 新建一个查询的实例
	bool a = query.driver()->hasFeature(QSqlDriver::Transactions);
	QString sql = "select count(*) from t_meter_default_params where f_standard_id = " + QString::number(stand_id);
	if(query.exec(sql)) // t_meter_standard 表的记录数
	{
		// 本次查询成功
		query.first(); //第一条记录
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
	else  // 如果查询失败，用下面的方法得到具体数据库返回的原因
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