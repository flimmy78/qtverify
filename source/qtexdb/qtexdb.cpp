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
			ptr[i].v_flow = query.value(6).toFloat();
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

//向数据库插入一条检定结果
int CBaseExdb::insertVerifyRec(Record_Quality_PTR ptr)
{
	if (!db.isOpen())
	{
		startdb();
	}
	
	QSqlQuery query(db); // 新建一个查询的实例
	QString sql = "insert into T_Verify_Record";
	sql.append("(");
	sql.append("F_TimeStamp,");
	sql.append("F_MeterNo,");
	sql.append("F_FlowPointIdx,");
	sql.append("F_FlowPoint,");
	sql.append("F_TotalFlag,");
	sql.append("F_MeterValue0,");
	sql.append("F_MeterValue1,");
	sql.append("F_MeterDeltaV,");
	sql.append("F_BalWeight0,");
	sql.append("F_BalWeight1,");
	sql.append("F_BalDeltaW,");
	sql.append("F_InSlotTemper,");
	sql.append("F_OutSlotTemper,");
	sql.append("F_PipeTemper,");
	sql.append("F_Density,");
	sql.append("F_StandValue,");
	sql.append("F_DispError,");
	sql.append("F_StdError,");
	sql.append("F_Result,");
	sql.append("F_MeterPosNo,");
	sql.append("F_Model,");
	sql.append("F_Standard ,");
	sql.append("F_MeterType,");
	sql.append("F_Manufacture,");
	sql.append("F_VerifyUnit,");
	sql.append("F_Grade,");
	sql.append("F_VerifyPerson,");
	sql.append("F_CheckPerson,");
	sql.append("F_VerifyDate,");
	sql.append("F_EnvTemper,");
	sql.append("F_EnvHumidity,");
	sql.append("F_AirPressure,");
	sql.append("F_ValidDate,");
	sql.append("F_RecordNumber");
	sql.append(")");
	sql.append("values");
	sql.append("(");//start
	sql.append(QString("%1, ").arg(ptr->timestamp, 0, 10));//F_TimeStamp
	sql.append(QString("%1, ").arg(ptr->meterNo,0, 10));//F_MeterNo
	sql.append(QString("%1, ").arg(ptr->flowPointIdx, 0, 10));//F_FlowPointIdx
	sql.append(QString("%1, ").arg(ptr->flowPoint, 6, 'g', 6));//F_FlowPoint
	sql.append(QString("%1, ").arg(ptr->totalFlag, 0, 10));//F_TotalFlag
	sql.append(QString("%1, ").arg(ptr->meterValue0, 6, 'g', 6));//F_MeterValue0
	sql.append(QString("%1, ").arg(ptr->meterValue1, 6, 'g', 6));//F_MeterValue1
	sql.append(QString("%1, ").arg(ptr->meterDeltaV, 6, 'g', 6));//F_MeterDeltaV
	sql.append(QString("%1, ").arg(ptr->balWeight0, 6, 'g', 6));//F_BalWeight0
	sql.append(QString("%1, ").arg(ptr->balWeight1, 6, 'g', 6));//F_BalWeight1
	sql.append(QString("%1, ").arg(ptr->balDeltaW, 6, 'g', 6));//F_BalDeltaW
	sql.append(QString("%1, ").arg(ptr->inSlotTemper, 6, 'g', 6));//F_InSlotTemper
	sql.append(QString("%1, ").arg(ptr->outSlotTemper, 6, 'g', 6));//F_OutSlotTemper
	sql.append(QString("%1, ").arg(ptr->pipeTemper, 6, 'g', 6));//F_PipeTemper
	sql.append(QString("%1, ").arg(ptr->density, 6, 'g', 6));//F_Density
	sql.append(QString("%1, ").arg(ptr->stdValue, 6, 'g', 6));//F_StandValue
	sql.append(QString("%1, ").arg(ptr->dispError, 6, 'g', 6));//F_DispError
	sql.append(QString("%1, ").arg(ptr->stdError, 6, 'g', 6));//F_StdError
	sql.append(QString("%1, ").arg(ptr->result, 0, 10));//F_Result
	sql.append(QString("%1, ").arg(ptr->meterPosNo, 0, 10));//F_MeterPosNo
	sql.append(QString("%1, ").arg(ptr->model, 0, 10));//F_Model
	sql.append(QString("%1, ").arg(ptr->standard, 0, 10));//F_Standard
	sql.append(QString("%1, ").arg(ptr->meterType, 0, 10));//F_MeterType
	sql.append(QString("%1, ").arg(ptr->manufacture, 0, 10));//F_Manufacture
	sql.append(QString("%1, ").arg(ptr->verifyUnit, 0, 10));//F_VerifyUnit
	sql.append(QString("%1, ").arg(ptr->grade, 0, 10));//F_Grade
	sql.append(QString("%1, ").arg(ptr->verifyPerson, 0, 10));//F_VerifyPerson
	sql.append(QString("%1, ").arg(ptr->checkPerson, 0, 10));//F_CheckPerson
	sql.append(QString("%1, ").arg(ptr->date, 0, 10));//F_VerifyDate
	sql.append(QString("%1, ").arg(ptr->envTemper, 6, 'g', 6));//F_EnvTemper
	sql.append(QString("%1, ").arg(ptr->envHumidity, 6, 'g', 6));//F_EnvHumidity
	sql.append(QString("%1, ").arg(ptr->airPress, 6, 'g', 6));//F_AirPressure
	sql.append(QString("%1, ").arg(ptr->validDate, 0, 10));//F_ValidDate
	sql.append(QString("%1").arg(ptr->recordNumber, 0, 10));//F_RecordNumber
	sql.append(")");//end
	if (query.exec(sql))
	{
		qDebug() << "insert succeed";
	}
	else
	{
		QSqlError error = query.lastError();
		qDebug() << error.text();
	}
	if (db.isOpen())
	{
		closedb();
	}
	return true;
}

/******************************************************
* 获取表的定义语句                                  *
* tbl_name: 表的名称                                 *
* 异常: 表名不存在                                    *
/******************************************************/
QString CBaseExdb::getTblDdl(QString tbl_name)
{
	QString sql = QString("SELECT sql FROM sqlite_master WHERE upper(tbl_name) = upper('%1') AND type = 'table'").arg(tbl_name);//查询语句
	QString ddl;//表的定义语句
	if (!db.isOpen())
	{
		startdb();
	}
	QStringList tbls = db.tables();
	//如果表名不存在, 抛出异常
	if (!tbls.contains(tbl_name, Qt::CaseInsensitive))
	{
		throw QString("no this table: %1").arg(tbl_name);
	}
	//开始查询
	QSqlQuery query(db);
	if (query.exec(sql))
	{
		query.first();
		ddl = query.value(0).toString();
	}
	else
	{
		throw query.lastError().text();
	}
	if (db.isOpen())
	{
		closedb();
	}
	return ddl;
}

/************************************************************************/
/* 去掉sql语句中的注释                                                    */
/* s: sql语句, 可以带注释, 也可以不带注释                      */
/************************************************************************/
QString CBaseExdb::removeComment(QString s)
{
	QString t;
	bool starts=false, ends=false;
	for(int i = 0; i < s.length() - 1; i++)
	{
		//注释以"--"开始, 以'\n'结束
		if ( (s[i] == '-') && (s[i + 1] == '-'))
		{
			//comment starts
			while ( s[i] != '\n')
			{
				i++;
			}
			//comment ends
		}
		else
		{
			t.append(s[i]);
		}
	}

	//由于循环时, 只扫描到倒数第2个字符
	//所以要检查最后一个字符是否需要追加至返回字串
	char last = s[s.length()-1].toAscii();
	if (last != ' ' && last != '\n')
	{
		t.append(last);
	}
	return t;
}

/************************************************************************/
/* 得到QMap<字段名, 字段类型>键值                             */
/* tbl_name: 表的名称                                                       */
/************************************************************************/
QMap<QString, QString> CBaseExdb::getColInfo(QString tbl_name)
{
	//获取建表的sql语句
	QString ddl = getTblDdl(tbl_name);
	/////////////////去掉括号,只保留字段定义///////////////////////
	int left_parenthesis_idx = ddl.indexOf('(');//第一个左括号索引
	int right_parenthesis_idx = ddl.lastIndexOf(')');//最后一个右括号索引
	QString mid = ddl.mid(left_parenthesis_idx + 1, right_parenthesis_idx - left_parenthesis_idx - 1);
	//mid = mid.left(mid.length()-1);
	////////////////////去掉注释, 并合并空白/////////////////////////
	QString remove_comment = removeComment(mid).simplified();
	/////////////////////用','号打断//////////////////////////////////////
	QStringList columns = remove_comment.split(',');

	QMap<QString, QString> colInfo;//QMap<字段名, 字段类型>键值
	for (int i = 0; i < columns.count(); i++)
	{
		QStringList col = columns[i].simplified().split(' ');//去掉字串开头与结尾的空白, 合并中间的空白
		colInfo[col[0]] = col[1];//存储键-值
	}
	return colInfo;
}