/***********************************************
**  文件名:     qtexdb.cpp
**  功能:       封装的数据库操作函数(SQLITE3)
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/25
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/06 第一版
**  内容包含:
**  说明:
**  更新记录:  
	2014-8-7修改:
		由导出类改为导出函数，操作数据库前，先startdb()，然后直接调用导出函数即可，程序退出时，调用closedb()。
***********************************************/

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtGui/QMessageBox>
#include <QtCore/QProcess>

#include "qtexdb.h"
#include "commondefine.h"
#include "algorithm.h"

int testFunc(int a, int b)
{
	qDebug()<<a<<"+"<<b<<"="<<(a+b);
	return (a + b);
}

void hello()  
{  
	qDebug()<<"hello world!";  
}  


QSqlDatabase g_db;

int startdb()
{
	if (QSqlDatabase::contains("qt_sql_default_connection"))
	{
		g_db = QSqlDatabase::database("qt_sql_default_connection");
	}
	else
	{
		QString dbname;
		DatabasePara_STR dbpara;
		getDatabaseParaIni(&dbpara);
		switch (dbpara.type)
		{
		case T_MYSQL:
			g_db = QSqlDatabase::addDatabase("QMYSQL"); // 使用mysql数据库驱动 
			g_db.setHostName(dbpara.hostname);   //数据库服务器主机名或IP地址
			g_db.setDatabaseName(dbpara.dbname); // 我们之前建立的数据库
			g_db.setUserName(dbpara.username);   // 我们创建的 xopens 用户名
			g_db.setPassword(dbpara.password);   // xopens 用户的密码
			break;
		case T_SQLITE:
			g_db = QSqlDatabase::addDatabase("QSQLITE");
			dbname = QProcessEnvironment::systemEnvironment().value("ADEHOME") + "\\database\\" + QString::fromAscii(dbpara.dbname) + ".db";
			g_db.setDatabaseName(dbname);
			break;
		default:
			g_db = QSqlDatabase::addDatabase("QSQLITE");
			dbname = QProcessEnvironment::systemEnvironment().value("ADEHOME") + "\\database\\" + QString::fromAscii(dbpara.dbname) + ".db";
			g_db.setDatabaseName(dbname);
			break;
		}
	}

	if (!g_db.open())// 尝试连接数据库
	{
		QMessageBox::critical(0, QObject::tr("Database Error"), g_db.lastError().text());
		return false;
	}
	return true;
}

void closedb()
{
	g_db.close();
}

//获取所有的表规格
int getMeterStandard(int& num, MeterStandard_PTR &ptr)
{
	int i = 0;
	QSqlQuery query; // 新建一个查询的实例
// 	bool a = query.driver()->hasFeature(QSqlDriver::Transactions);
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
			strcpy_s(ptr[i].name, query.value(1).toString().toAscii());
			ptr[i].quantity = query.value(2).toInt();
			i++;
		}
	}
	else  // 如果查询失败，用下面的方法得到具体数据库返回的原因
	{
		QSqlError error = query.lastError();
		qWarning()<<error.text();
		return false;
	}

	return true;
}

/*
** 按主键获取对应表规格的最大检定数量
*/
int getMaxMeterByIdx(int idx)
{
	QSqlQuery query; // 新建一个查询的实例
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
		qWarning()<<error.text();
	}
	return -1;
}


//获取所有的制造单位
int getManufacture(int& num, Manufacture_PTR &ptr)
{
	int i = 0;
	QSqlQuery query; // 新建一个查询的实例
	if(query.exec("select count(*) from t_manufacture_dept")) // t_manufacture_dept 表的记录数
	{
		// 本次查询成功
		query.first(); //第一条记录
		num = query.value(0).toInt();
		ptr = new Manufacture_STR[num];
		memset(ptr, 0, sizeof(Manufacture_STR)*num);
	}

	if(query.exec("select f_id,f_name,f_desc,f_numprefix from t_manufacture_dept order by f_id"))
	{
		while(query.next())
		{
			ptr[i].id = query.value(0).toInt();
			strncpy_s(ptr[i].name, query.value(1).toString().toAscii(), ASCNAME_LEN);
			strncpy_s(ptr[i].desc, query.value(2).toString().toLocal8Bit(), DESC_LEN); //汉字编码
			strncpy(ptr[i].numprefix, query.value(3).toString().toLocal8Bit(), NUMPREFIX_LEN);
			i++;
		}
	}
	else  // 如果查询失败，用下面的方法得到具体数据库返回的原因
	{
		QSqlError error = query.lastError();
		qWarning()<<error.text();
		return false;
	}

	return true;
}

/*
**  获取各规格热表的默认检定参数
**  num: 查询结果的记录数
**  ptr: 与数据表t_meter_default_params对应的结构
**  stand_id: 表规格的主键值, 用于索引界面上的comboBox
*/
int getDftDBinfo(int &num, DftDbInfo_PTR &ptr, int stand_id)
{
	int i = 0;
	QSqlQuery query; // 新建一个查询的实例
	QString sql = "select count(*) from t_meter_default_params where F_StandardID = " + QString::number(stand_id);
	if(query.exec(sql)) // t_meter_standard 表的记录数
	{
		// 本次查询成功
		query.first(); //第一条记录
		num = query.value(0).toInt();
		ptr = new DftDbInfo_STR[num];
		memset(ptr, 0, sizeof(DftDbInfo_STR)*num);
	}
	sql = "select F_ID, F_StandardID, F_NormalFlow, F_UpperFlow, F_VerifyFlow, F_FlowQuantity, F_PumpFrequencey, F_Valve_i, \
		  F_Seq_i from T_Meter_Default_Params where F_StandardID = " + QString::number(stand_id) + " order by F_ID";
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
		qWarning()<<error.text();
		return false;
	}

	return true;
}


/*
** 向数据库插入流量检定结果。调用者负责提前打开数据库startdb()
*/
int insertFlowVerifyRec(Flow_Verify_Record_PTR ptr, int num)
{
	for (int i=0; i<num; i++)
	{
		QSqlQuery query(g_db); // 新建一个查询的实例
		QString sql = "insert into T_Flow_Verify_Record";
		sql.append(" (");
		sql.append("F_TimeStamp,");
		sql.append("F_MeterNo,");
		sql.append("F_FlowPointIdx,");
		sql.append("F_FlowPoint,");
		sql.append("F_MethodFlag,");
		sql.append("F_MeterValue0,");
		sql.append("F_MeterValue1,");
		sql.append("F_BalWeight0,");
		sql.append("F_BalWeight1,");
		sql.append("F_StdMeterV0,");
		sql.append("F_StdMeterV1,");
		sql.append("F_PipeTemper,");
		sql.append("F_Density,");
		sql.append("F_StandValue,");
		sql.append("F_DispError,");
		sql.append("F_StdError,");
		sql.append("F_Result,");
		sql.append("F_MeterPosNo,");
		sql.append("F_Model,");
		sql.append("F_Standard ,");
		sql.append("F_PickCode,");
		sql.append("F_ManufactDept,");
		sql.append("F_VerifyDept,");
		sql.append("F_Grade,");
		sql.append("F_VerifyPerson,");
		sql.append("F_CheckPerson,");
		sql.append("F_DeviceInfoID,");
		sql.append("F_VerifyDate,");
		sql.append("F_ValidDate,");
		sql.append("F_EnvTemper,");
		sql.append("F_EnvHumidity,");
		sql.append("F_AirPressure,");
		sql.append("F_CertNO,");
		sql.append("F_FlowCoe,");
		sql.append("F_Bak2,");
		sql.append("F_Bak3,");
		sql.append("F_Bak4");
		sql.append(") ");
		sql.append("values");
		sql.append("(");//start
		sql.append(QString("\'%1\', ").arg(ptr[i].timestamp, 0, 10));//F_TimeStamp
		sql.append(QString("%1, ").arg(ptr[i].meterNo,0, 10));//F_MeterNo
		sql.append(QString("%1, ").arg(ptr[i].flowPointIdx, 0, 10));//F_FlowPointIdx
		sql.append(QString("%1, ").arg(ptr[i].flowPoint, 6, 'g', 6));//F_FlowPoint
		sql.append(QString("%1, ").arg(ptr[i].methodFlag, 0, 10));//F_TotalFlag
		sql.append(QString("%1, ").arg(ptr[i].meterValue0, 6, 'g', 6));//F_MeterValue0
		sql.append(QString("%1, ").arg(ptr[i].meterValue1, 6, 'g', 6));//F_MeterValue1
		sql.append(QString("%1, ").arg(ptr[i].balWeight0, 6, 'g', 6));//F_BalWeight0
		sql.append(QString("%1, ").arg(ptr[i].balWeight1, 6, 'g', 6));//F_BalWeight1
		sql.append(QString("%1, ").arg(ptr[i].stdMeterV0, 6, 'g', 6));//F_BalDeltaW
		sql.append(QString("%1, ").arg(ptr[i].stdMeterV1, 6, 'g', 6));//F_InSlotTemper
		sql.append(QString("%1, ").arg(ptr[i].pipeTemper, 6, 'g', 6));//F_PipeTemper
		sql.append(QString("%1, ").arg(ptr[i].density, 6, 'g', 6));//F_Density
		sql.append(QString("%1, ").arg(ptr[i].stdValue, 6, 'g', 6));//F_StandValue
		sql.append(QString("%1, ").arg(ptr[i].dispError, 6, 'g', 6));//F_DispError
		sql.append(QString("%1, ").arg(ptr[i].stdError, 6, 'g', 6));//F_StdError
		sql.append(QString("%1, ").arg(ptr[i].result, 0, 10));//F_Result
		sql.append(QString("%1, ").arg(ptr[i].meterPosNo, 0, 10));//F_MeterPosNo
		sql.append(QString("%1, ").arg(ptr[i].model, 0, 10));//F_Model
		sql.append(QString("%1, ").arg(ptr[i].standard, 0, 10));//F_Standard
		sql.append(QString("%1, ").arg(ptr[i].pickcode, 0, 10));//F_PickCode
		sql.append(QString("%1, ").arg(ptr[i].manufactDept, 0, 10));//F_ManufactDept
		sql.append(QString("%1, ").arg(ptr[i].verifyDept, 0, 10));//F_VerifyDept
		sql.append(QString("%1, ").arg(ptr[i].grade, 0, 10));//F_Grade
		sql.append(QString("%1, ").arg(ptr[i].verifyPerson, 0, 10));//F_VerifyPerson
		sql.append(QString("%1, ").arg(ptr[i].checkPerson, 0, 10));//F_CheckPerson
		sql.append(QString("%1, ").arg(ptr[i].deviceInfoId, 0, 10));//F_DeviceInfoID
		sql.append(QString("\'%1\', ").arg(ptr[i].verifyDate));//F_VerifyDate
		sql.append(QString("\'%1\', ").arg(ptr[i].validDate));//F_ValidDate
		sql.append(QString("%1, ").arg(ptr[i].envTemper, 6, 'g', 6));//F_EnvTemper
		sql.append(QString("%1, ").arg(ptr[i].envHumidity, 6, 'g', 6));//F_EnvHumidity
		sql.append(QString("%1, ").arg(ptr[i].airPress, 6, 'g', 6));//F_AirPressure
		sql.append(QString("\'%1\', ").arg(ptr[i].certNo, 0, 10));//F_CertNO
		sql.append(QString("%1, ").arg(ptr[i].flowcoe, 6, 'g', 6));//F_FlowCoe
		sql.append(QString("\'%1\', ").arg(ptr[i].bak2, 0, 10));//F_Bak2
		sql.append(QString("\'%1\', ").arg(ptr[i].bak3, 0, 10));//F_Bak3
		sql.append(QString("\'%1\'").arg(ptr[i].bak4, 0, 10));//F_Bak4
		sql.append(")");//end
		if (query.exec(sql))
		{
			qDebug()<<"insert succeed";
		}
		else
		{
 			QSqlError error = query.lastError();
			qWarning()<<error.text();
		}
	}
	
	return true;
}

/*
** 修改数据库中流量检定结果的表号。调用者负责提前打开数据库startdb()
*/
int modifyFlowVerifyRec_MeterNO(QString newMeterNO, QString timeStamp, int meterPos)
{
	QSqlQuery query(g_db); // 新建一个查询的实例
	QString sql = "update T_Flow_Verify_Record set F_MeterNo=";
	sql.append(newMeterNO);
	sql.append(" where F_TimeStamp=\"");
	sql.append(timeStamp.toAscii());
	sql.append("\" and F_MeterPosNo=");
	sql.append(QString("%1").arg(meterPos, 0, 10));
	if (query.exec(sql))
	{
		qDebug()<<"update succeed"<<timeStamp<<meterPos<<newMeterNO;
	}
	else
	{
		QSqlError error = query.lastError();
		qWarning()<<error.text();
	}

	return true;
}

/*
** 向数据库插入总量检定结果。调用者负责提前打开数据库startdb()
*/
int insertTotalVerifyRec(Total_Verify_Record_PTR ptr, int num)
{
	for (int i=0; i<num; i++)
	{
		QSqlQuery query(g_db); // 新建一个查询的实例
		QString sql = "insert into T_Total_Verify_Record";
		sql.append(" (");
		sql.append("F_TimeStamp,");
		sql.append("F_MeterNo,");
		sql.append("F_FlowPointIdx,");
		sql.append("F_FlowPoint,");
		sql.append("F_MethodFlag,");
		sql.append("F_MeterValue0,");
		sql.append("F_MeterValue1,");
		sql.append("F_BalWeight0,");
		sql.append("F_BalWeight1,");
		sql.append("F_StdMeterV0,");
		sql.append("F_StdMeterV1,");
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
		sql.append("F_PickCode,");
		sql.append("F_ManufactDept,");
		sql.append("F_VerifyDept,");
		sql.append("F_Grade,");
		sql.append("F_VerifyPerson,");
		sql.append("F_CheckPerson,");
		sql.append("F_DeviceInfoID,");
		sql.append("F_VerifyDate,");
		sql.append("F_ValidDate,");
		sql.append("F_EnvTemper,");
		sql.append("F_EnvHumidity,");
		sql.append("F_AirPressure,");
		sql.append("F_CertNO,");
		sql.append("F_TotalCoe,");
		sql.append("F_Bak2,");
		sql.append("F_Bak3,");
		sql.append("F_Bak4");
		sql.append(") ");
		sql.append("values");
		sql.append("(");//start
		sql.append(QString("\'%1\', ").arg(ptr[i].timestamp, 0, 10));//F_TimeStamp
		sql.append(QString("%1, ").arg(ptr[i].meterNo,0, 10));//F_MeterNo
		sql.append(QString("%1, ").arg(ptr[i].flowPointIdx, 0, 10));//F_FlowPointIdx
		sql.append(QString("%1, ").arg(ptr[i].flowPoint, 6, 'g', 6));//F_FlowPoint
		sql.append(QString("%1, ").arg(ptr[i].methodFlag, 0, 10));//F_TotalFlag
		sql.append(QString("%1, ").arg(ptr[i].meterValue0, 6, 'g', 6));//F_MeterValue0
		sql.append(QString("%1, ").arg(ptr[i].meterValue1, 6, 'g', 6));//F_MeterValue1
		sql.append(QString("%1, ").arg(ptr[i].balWeight0, 6, 'g', 6));//F_BalWeight0
		sql.append(QString("%1, ").arg(ptr[i].balWeight1, 6, 'g', 6));//F_BalWeight1
		sql.append(QString("%1, ").arg(ptr[i].stdMeterV0, 6, 'g', 6));//F_StdMeterV0
		sql.append(QString("%1, ").arg(ptr[i].stdMeterV1, 6, 'g', 6));//F_StdMeterV1
		sql.append(QString("%1, ").arg(ptr[i].inSlotTemper, 6, 'g', 6));//F_PipeTemper
		sql.append(QString("%1, ").arg(ptr[i].outSlotTemper, 6, 'g', 6));//F_PipeTemper
		sql.append(QString("%1, ").arg(ptr[i].pipeTemper, 6, 'g', 6));//F_PipeTemper
		sql.append(QString("%1, ").arg(ptr[i].density, 6, 'g', 6));//F_Density
		sql.append(QString("%1, ").arg(ptr[i].stdValue, 6, 'g', 6));//F_StandValue
		sql.append(QString("%1, ").arg(ptr[i].dispError, 6, 'g', 6));//F_DispError
		sql.append(QString("%1, ").arg(ptr[i].stdError, 6, 'g', 6));//F_StdError
		sql.append(QString("%1, ").arg(ptr[i].result, 0, 10));//F_Result
		sql.append(QString("%1, ").arg(ptr[i].meterPosNo, 0, 10));//F_MeterPosNo
		sql.append(QString("%1, ").arg(ptr[i].model, 0, 10));//F_Model
		sql.append(QString("%1, ").arg(ptr[i].standard, 0, 10));//F_Standard
		sql.append(QString("%1, ").arg(ptr[i].pickcode, 0, 10));//F_PickCode
		sql.append(QString("%1, ").arg(ptr[i].manufactDept, 0, 10));//F_ManufactDept
		sql.append(QString("%1, ").arg(ptr[i].verifyDept, 0, 10));//F_VerifyDept
		sql.append(QString("%1, ").arg(ptr[i].grade, 0, 10));//F_Grade
		sql.append(QString("%1, ").arg(ptr[i].verifyPerson, 0, 10));//F_VerifyPerson
		sql.append(QString("%1, ").arg(ptr[i].checkPerson, 0, 10));//F_CheckPerson
		sql.append(QString("%1, ").arg(ptr[i].deviceInfoId, 0, 10));//F_DeviceInfoID
		sql.append(QString("\'%1\', ").arg(ptr[i].verifyDate));//F_VerifyDate
		sql.append(QString("\'%1\', ").arg(ptr[i].validDate));//F_ValidDate
		sql.append(QString("%1, ").arg(ptr[i].envTemper, 6, 'g', 6));//F_EnvTemper
		sql.append(QString("%1, ").arg(ptr[i].envHumidity, 6, 'g', 6));//F_EnvHumidity
		sql.append(QString("%1, ").arg(ptr[i].airPress, 6, 'g', 6));//F_AirPressure
		sql.append(QString("\'%1\', ").arg(ptr[i].certNo, 0, 10));//F_CertNO
		sql.append(QString("%1, ").arg(ptr[i].totalcoe, 6, 'g', 6));//F_TotalCoe
		sql.append(QString("\'%1\', ").arg(ptr[i].bak2, 0, 10));//F_Bak2
		sql.append(QString("\'%1\', ").arg(ptr[i].bak3, 0, 10));//F_Bak3
		sql.append(QString("\'%1\'").arg(ptr[i].bak4, 0, 10));//F_Bak4
		sql.append(")");//end
		if (query.exec(sql))
		{
			qDebug()<<"insert succeed";
		}
		else
		{
 			QSqlError error = query.lastError();
			qWarning()<<error.text();
		}
	}
	
	return true;
}

QString getNumPrefixOfManufac(int idx)
{
	if (idx < 0)
	{
		return "";
	}

	QString str, sqlstr;
	sqlstr = QString("select f_id,f_numprefix from t_manufacture_dept where f_id=%1").arg(idx);
	QSqlQuery query; // 新建一个查询的实例
	if(query.exec(sqlstr))
	{
		query.next();
		str = query.value(1).toString();
		return str;
	}
	else  // 如果查询失败，用下面的方法得到具体数据库返回的原因
	{
		QSqlError error = query.lastError();
		qWarning()<<error.text();
		return "";
	}
}

/*
** 获取表的定义语句
** tbl_name: 表的名称
** 异常: 表名不存在
*/
QString getTblDdl(QString tbl_name)
{
	QString sql = QString("SELECT sql FROM sqlite_master WHERE upper(tbl_name) = upper('%1') AND type = 'table'").arg(tbl_name);//查询语句
	QString ddl;//表的定义语句

	QStringList tbls = g_db.tables();
	//如果表名不存在, 抛出异常
	if (!tbls.contains(tbl_name, Qt::CaseInsensitive))
	{
		throw QString("no this table: %1").arg(tbl_name);
	}
	//开始查询
	QSqlQuery query(g_db);
	if (query.exec(sql))
	{
		query.first();
		ddl = query.value(0).toString();
	}
	else
	{
		throw query.lastError().text();
	}

	return ddl;
}

/*
** 去掉sql语句中的注释
** s: sql语句, 可以带注释, 也可以不带注释
*/
QString removeComment(QString s)
{
	QString t;
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

/*
** 得到QMap<字段名, 字段类型>键值
** tbl_name: 表的名称
*/
QMap<QString, QString> getColInfo(QString tbl_name)
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

//获取数据库配置信息
int getDatabaseParaIni(DatabasePara_PTR info)
{
	QString filename;
	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
	if (adehome.isEmpty())
	{
		qWarning()<<"Get $(ADEHOME) Failed!";
		return false;
	}
#ifdef __unix
	filename = adehome + "\/ini\/databasepara.ini";
#else
	filename = adehome + "\\ini\\databasepara.ini";
#endif

	QSettings settings(filename, QSettings::IniFormat);

	info->type = settings.value("type").toInt();
	strcpy_s(info->hostname, settings.value("hostname").toString().toAscii());
	strcpy_s(info->dbname, settings.value("dbname").toString().toAscii());
	strcpy_s(info->username, settings.value("username").toString().toAscii());
	strcpy_s(info->password, settings.value("password").toString().toAscii());

	return true;
}

int insertPlatinumVerifyRec(T_Platinum_Verify_Record_PTR ptr, int num)
{
	int ret = 0;
	for (int i=0; i<num; i++)
	{
		QSqlQuery query(g_db); // 新建一个查询的实例
		QString sql = "insert into T_Platinum_Verify_Record";
		sql.append(" (");
		sql.append("F_TimeStamp, ");
		sql.append("F_CompOrParam, ");
		sql.append("F_PlaManufactDept, ");
		sql.append("F_Standard, ");
		sql.append("F_Model, ");
		sql.append("F_ManufactDept, ");
		sql.append("F_VerifyDept, ");
		sql.append("F_VerifyPerson, ");
		sql.append("F_CheckPerson, ");
		sql.append("F_MinTmpDiff, ");
		sql.append("F_TmpDiff, ");
		sql.append("F_StdInRresis, ");
		sql.append("F_StdOutRresis, ");
		sql.append("F_StdInTmp, ");
		sql.append("F_StdOutTmp, ");
		sql.append("F_PlaSerial, ");
		sql.append("F_PlaInRresis, ");
		sql.append("F_PlaOutRresis, ");
		sql.append("F_PlaInTmp, ");
		sql.append("F_PlaOutTmp, ");
		sql.append("F_PlaTmpDiffErr, ");
		sql.append("F_PlaParamR0, ");
		sql.append("F_PlaCoeA, ");
		sql.append("F_PlaCoeB, ");
		sql.append("F_PlaCoeC, ");
		sql.append("F_InErr, ");
		sql.append("F_OutErr, ");
		sql.append("F_MaxErrPoint, ");
		sql.append("F_InErrLimit, ");
		sql.append("F_OutErrLimit, ");
		sql.append("F_DeltaErrLimit, ");
		sql.append("F_verify_seq, ");
		sql.append("F_TmpIndex, ");
		sql.append("F_StdModel");
		sql.append(") ");
		sql.append("values");
		sql.append("(");//start
		sql.append(QString("\'%1\', ").arg(ptr[i].timestamp, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_CompOrParam,0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_PlaManufactDept, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_Standard, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_Model, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_ManufactDept, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_VerifyDept, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_VerifyPerson, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_CheckPerson, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_MinTmpDiff, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_TmpDiff, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_StdInRresis, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_StdOutRresis, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_StdInTmp, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_StdOutTmp, 6, 'g', 6));
		sql.append(QString("\'%1\', ").arg(ptr[i].F_PlaSerial,0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_PlaInRresis, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_PlaOutRresis, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_PlaInTmp, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_PlaOutTmp, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_PlaTmpDiffErr, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_PlaParamR0, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_PlaCoeA, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_PlaCoeB, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_PlaCoeC, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_InErr, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_OutErr, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_MaxErrPoint, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_InErrLimit, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_OutErrLimit, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_DeltaErrLimit, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_verify_seq,0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_TmpIndex,0, 10));
		sql.append(QString("\'%1\'").arg(ptr[i].F_StdModel, 0, 10));
		sql.append(")");//end
		if (query.exec(sql))
		{
			qDebug()<<"insert succeed";
		}
		else
		{
			QSqlError error = query.lastError();
			qWarning()<<error.text();
		}
	}

	return true;
}

/*
** 向数据库插入计算器检定结果。调用者负责提前打开数据库startdb()
*/
int insertCalcVerifyRec(Calc_Verify_Record_PTR ptr, int num)
{
	int ret = 1;
	for (int i=0; i<num; i++)
	{
		QSqlQuery query(g_db); // 新建一个查询的实例
		QString sql = "insert into T_Calc_Verify_Record";
		sql.append(" (");
		sql.append("F_TimeStamp,");
		sql.append("F_MeterNo,");
		sql.append("F_DeltaTIdx,");
		sql.append("F_Standard,");
		sql.append("F_Model,");
		sql.append("F_Grade,");
		sql.append("F_ManufactDept,");
		sql.append("F_VerifyDept,");
		sql.append("F_VerifyPerson,");
		sql.append("F_MaxT,");
		sql.append("F_MinT,");
		sql.append("F_MaxDeltaT,");
		sql.append("F_MinDeltaT,");
		sql.append("F_Algorithm,");
		sql.append("F_InstallPos,");
		sql.append("F_EnergyUnit,");
		sql.append("F_StdTempIn,");
		sql.append("F_StdTempOut,");
		sql.append("F_StdResistIn,");
		sql.append("F_StdResistOut,");
		sql.append("F_RecomVolume,");
		sql.append("F_AnalogVolume,");
		sql.append("F_Kcoe,");
		sql.append("F_StdEnergy,");
		sql.append("F_MeterE0,");
		sql.append("F_MeterE1,");
		sql.append("F_DispError,");
		sql.append("F_StdError,");
		sql.append("F_Result,");
		sql.append("F_Bak2,");
		sql.append("F_Bak3,");
		sql.append("F_Bak4");
		sql.append(") ");
		sql.append("values");
		sql.append("(");//start
		sql.append(QString("\'%1\', ").arg(ptr[i].timestamp, 0, 10));//F_TimeStamp
		sql.append(QString("%1, ").arg(ptr[i].meterNo,0, 10));//F_MeterNo
		sql.append(QString("%1, ").arg(ptr[i].deltaTidx, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].standard, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].model, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].grade, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].manufactDept, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].verifyDept, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].verifyPerson, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].maxT, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].minT, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].maxDeltaT, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].minDeltaT, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].algorithm, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].installPos, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].energyUnit, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].inTemper, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].outTemper, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].inR, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].outR, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].recomVolume, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].analogVolume, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].kCoe, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].theoryEnergy, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].meterE0,  6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].meterE1, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].dispError, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].stdError, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].result, 0, 10));
		sql.append(QString("\'%1\', ").arg(ptr[i].bak2, 0, 10));//F_Bak2
		sql.append(QString("\'%1\', ").arg(ptr[i].bak3, 0, 10));//F_Bak3
		sql.append(QString("\'%1\'").arg(ptr[i].bak4, 0, 10));//F_Bak4
		sql.append(")");//end
		if (query.exec(sql))
		{
			qDebug()<<"insert succeed";
		}
		else
		{
 			QSqlError error = query.lastError();
			qWarning()<<error.text();
			ret = 0;
		}
	}
	
	return ret;
}

/*
** 向数据库插入组合检定结果。调用者负责提前打开数据库startdb()
*/
int insertCmbVerifyRec(Cmb_Verify_Record_PTR ptr, int num)
{
	int ret = 1;
	for (int i=0; i<num; i++)
	{
		QSqlQuery query(g_db); // 新建一个查询的实例
		QString sql = "insert into T_Combined_Verify_Record";
		sql.append(" (");
		sql.append("F_TimeStamp,");
		sql.append("F_MeterNo,");
		//sql.append("F_DeltaTIdx,");
		sql.append("F_Standard,");
		sql.append("F_Model,");
		sql.append("F_Grade,");
		sql.append("F_ManufactDept,");
		sql.append("F_VerifyDept,");
		sql.append("F_VerifyPerson,");
		sql.append("F_DeltaTemp,");
		sql.append("F_VerifyVolume,");
		sql.append("F_DeltaTempMin,");
		sql.append("F_InstallPos,");
		sql.append("F_HeatUnit,");
		sql.append("F_StdTempIn,");
		sql.append("F_StdTempOut,");
		sql.append("F_StdResistIn,");
		sql.append("F_StdResistOut,");
		sql.append("F_Kcoe,");
		sql.append("F_StdValue,");
		sql.append("F_MeterV0,");
		sql.append("F_MeterV1,");
		sql.append("F_MeterE0,");
		sql.append("F_MeterE1,");
		sql.append("F_DispError,");
		sql.append("F_StdError,");
		sql.append("F_Result,");
		sql.append("F_Bak2,");
		sql.append("F_Bak3,");
		sql.append("F_Bak4");
		sql.append(") ");
		sql.append("values");
		sql.append("(");//start
		sql.append(QString("\'%1\', ").arg(ptr[i].F_TimeStamp, 0, 10));//F_TimeStamp
		sql.append(QString("\'%1\', ").arg(ptr[i].F_MeterNo,0, 10));//F_MeterNo
		sql.append(QString("%1, ").arg(ptr[i].F_Standard, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_Model, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_Grade, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_ManufactDept, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_VerifyDept, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_VerifyPerson, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_DeltaTemp, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_VerifyVolume, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_DeltaTempMin, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_InstallPos, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_HeatUnit, 0, 10));
		sql.append(QString("%1, ").arg(ptr[i].F_StdTempIn, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_StdTempOut, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_StdResistIn, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_StdResistOut, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_Kcoe, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_StdValue, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_MeterV0, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_MeterV1, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_MeterE0, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_MeterE1, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_DispError, 6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_StdError,  6, 'g', 6));
		sql.append(QString("%1, ").arg(ptr[i].F_Result, 0, 10));
		sql.append(QString("\'%1\', ").arg(ptr[i].F_Bak2, 0, 10));//F_Bak2
		sql.append(QString("\'%1\', ").arg(ptr[i].F_Bak3, 0, 10));//F_Bak3
		sql.append(QString("\'%1\'").arg(ptr[i].F_Bak4, 0, 10));//F_Bak4
		sql.append(")");//end
		if (query.exec(sql))
		{
			qDebug()<<"insert succeed";
		}
		else
		{
			QSqlError error = query.lastError();
			qWarning()<<error.text();
			ret = 0;
		}
	}

	return ret;
}
