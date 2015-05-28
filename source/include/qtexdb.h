#ifndef QTEXDB_H
#define QTEXDB_H


#ifdef QTEXDB_DLL
#  ifdef WIN32
#  define QTEXDB_EXPORT __declspec(dllexport)
#  else
#  define QTEXDB_EXPORT
#  endif
#else
#  ifdef WIN32
#  define QTEXDB_EXPORT __declspec(dllimport)
#  else
#  define QTEXDB_EXPORT
#  endif
#endif


#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>

#include "basedef.h"

#define DB_TYPE  T_SQLITE

enum dbtype
{
	T_SQLITE = 0, 
	T_MYSQL
};

extern "C" {  // only need to export C interface if	used by C++ source code

QTEXDB_EXPORT int testFunc(int a, int b);
QTEXDB_EXPORT void hello();

QTEXDB_EXPORT int startdb(); //操作数据库前必须先调用startdb()
QTEXDB_EXPORT void closedb();//程序退出前，调用closedb()，关闭数据库

QTEXDB_EXPORT	int getMeterStandard(int& num, MeterStandard_PTR &ptr);
QTEXDB_EXPORT	int getMaxMeterByIdx(int idx);
QTEXDB_EXPORT	int getManufacture(int& num, Manufacture_PTR &ptr);

QTEXDB_EXPORT	int getDftDBinfo(int &num, DftDbInfo_PTR &ptr, int stand_id);
QTEXDB_EXPORT	int insertFlowVerifyRec(Flow_Verify_Record_PTR ptr, int num);
QTEXDB_EXPORT	int insertPlatinumVerifyRec(T_Platinum_Verify_Record_PTR ptr, int num);
QTEXDB_EXPORT	int insertCalcVerifyRec(Calc_Verify_Record_PTR ptr, int num);
QTEXDB_EXPORT	int insertCmbVerifyRec(Cmb_Verify_Record_PTR ptr, int num);
} //end of extern "C"

QTEXDB_EXPORT   QString getNumPrefixOfManufac(int idx); //获取某制造厂家的表号前缀
QTEXDB_EXPORT	QString getTblDdl(QString tbl_name);
QTEXDB_EXPORT	QString removeComment(QString s);
QTEXDB_EXPORT	QMap<QString, QString> getColInfo(QString ddl);
QTEXDB_EXPORT   int getDatabaseParaIni(DatabasePara_PTR info); //获取数据库配置信息




#endif // QTEXDB_H
