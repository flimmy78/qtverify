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

extern "C" {  // only need to export C interface if	used by C++ source code
QTEXDB_EXPORT int testFunc(int a, int b);

QTEXDB_EXPORT int startdb(); //�������ݿ�ǰ�����ȵ���startdb()
QTEXDB_EXPORT void closedb();//�����˳�ǰ������closedb()���ر����ݿ�

QTEXDB_EXPORT	int getMeterStandard(int& num, MeterStandard_PTR &ptr);
QTEXDB_EXPORT	int getMaxMeterByIdx(int idx);
QTEXDB_EXPORT	int getMeterType(int& num, MeterType_PTR &ptr);
QTEXDB_EXPORT	int getManufacture(int& num, Manufacture_PTR &ptr);
QTEXDB_EXPORT	int getDftDBinfo(int &num, DftDbInfo_PTR &ptr, int stand_id);
QTEXDB_EXPORT	int insertVerifyRec(Record_Quality_PTR ptr, int num);

}
QTEXDB_EXPORT	QString getTblDdl(QString tbl_name);
QTEXDB_EXPORT	QString removeComment(QString s);
QTEXDB_EXPORT	QMap<QString, QString> getColInfo(QString ddl);




#endif // QTEXDB_H
