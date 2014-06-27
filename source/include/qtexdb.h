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

QTEXDB_EXPORT int testFunc(int a, int b);

class QTEXDB_EXPORT CBaseExdb
{
public:
	CBaseExdb();
	~CBaseExdb();

	QSqlDatabase db;

	int startdb();
	void closedb();

	int getMeterStandard(int& num, MeterStandard_PTR &ptr);
	int getMeterType(int& num, MeterType_PTR &ptr);

private:

public slots:
	void WriteSettings();
	void ReadSettings();

};

#endif // QTEXDB_H
