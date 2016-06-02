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

QTEXDB_EXPORT QSqlDatabase g_defaultdb;
QTEXDB_EXPORT QSqlDatabase g_mysqldb;

enum dbtype
{
	T_SQLITE = 0, 
	T_MYSQL,
	T_BOTH       //ͬʱ����SQLite��MySQL
};

extern "C" {  // only need to export C interface if	used by C++ source code

QTEXDB_EXPORT int testFunc(int a, int b);
QTEXDB_EXPORT void hello();

QTEXDB_EXPORT int startdb(); //�������ݿ�ǰ�����ȵ���startdb()
QTEXDB_EXPORT void closedb();//�����˳�ǰ������closedb()���ر����ݿ�

QTEXDB_EXPORT	int getMeterStandard(int& num, MeterStandard_PTR &ptr);
QTEXDB_EXPORT	int getMaxMeterByIdx(int idx);
QTEXDB_EXPORT	int getManufacture(int& num, Manufacture_PTR &ptr);

QTEXDB_EXPORT	int getDftDBinfo(int &num, DftDbInfo_PTR &ptr, int stand_id);
QTEXDB_EXPORT	int updateDftDBinfo(DftDbInfo_PTR ptr, int stand_id); //
QTEXDB_EXPORT	int insertFlowVerifyRec(Flow_Verify_Record_PTR ptr, int num);
QTEXDB_EXPORT	int modifyFlowVerifyRec_MeterNO(QString newMeterNO, QString timeStamp, int meterPos, int deviceID=0);
QTEXDB_EXPORT	int insertWaterVerifyRec(Water_Verify_Record_PTR ptr, int num);
QTEXDB_EXPORT	int insertTotalVerifyRec(Total_Verify_Record_PTR ptr, int num);
QTEXDB_EXPORT	int insertPlatinumVerifyRec(T_Platinum_Verify_Record_PTR ptr, int num);
QTEXDB_EXPORT	int insertCalcVerifyRec(Calc_Verify_Record_PTR ptr, int num);
QTEXDB_EXPORT	int insertCmbVerifyRec(Cmb_Verify_Record_PTR ptr, int num);
} //end of extern "C"

QTEXDB_EXPORT   QString getNumPrefixOfManufac(int idx); //��ȡĳ���쳧�ҵı��ǰ׺
QTEXDB_EXPORT	QString getTblDdl(QString tbl_name);
QTEXDB_EXPORT	QString removeComment(QString s);
QTEXDB_EXPORT	QMap<QString, QString> getColInfo(QString ddl);
QTEXDB_EXPORT   int getDatabaseParaIni(DatabasePara_PTR info); //��ȡ���ݿ�������Ϣ
QTEXDB_EXPORT	int insertPidRec(PIDDataPtr pidStr);//����pid�趨ʱ���������



#endif // QTEXDB_H
