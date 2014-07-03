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

	QSettings settings(filename, QSettings::IniFormat); // 当前目录的INI文件
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

	QSettings settings(filename, QSettings::IniFormat); // 当前目录的INI文件

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
	db = QSqlDatabase::addDatabase("QSQLITE"); // 使用sqlite数据库驱动 
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

	if(query.exec("select id,name from t_meter_standard order by id"))
	{
		while(query.next())
		{
			ptr[i].id = query.value(0).toInt();
			strcpy(ptr[i].name, query.value(1).toString().toAscii());
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

	if(query.exec("select id,desc from t_meter_type order by id"))
	{
		while(query.next())
		{
			ptr[i].id = query.value(0).toInt();
			strcpy(ptr[i].desc, query.value(1).toString().toLocal8Bit()); //汉字编码
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
	if(query.exec("select count(*) from t_manufacture_tab")) // t_manufacture_tab 表的记录数
	{
		// 本次查询成功
		query.first(); //第一条记录
		num = query.value(0).toInt();
		ptr = new Manufacture_STR[num];
		memset(ptr, 0, sizeof(Manufacture_STR)*num);
	}

	if(query.exec("select id,desc from t_manufacture_tab order by id"))
	{
		while(query.next())
		{
			ptr[i].id = query.value(0).toInt();
			strcpy(ptr[i].desc, query.value(1).toString().toLocal8Bit()); //汉字编码
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
