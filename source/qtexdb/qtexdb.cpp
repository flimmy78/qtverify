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

/************************************************************************/
/* ��������ȡ��Ӧ��������춨����                       */
/************************************************************************/
int CBaseExdb::getMaxMeterByIdx(int idx)
{
	MeterStandard_PTR ptr;
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	bool a = query.driver()->hasFeature(QSqlDriver::Transactions);
	QString sql = "select F_Meter_Quantity from t_meter_standard where f_id = "+ QString::number(idx);
	if(query.exec(sql))
	{
		while(query.next())
		{
			return query.value(0).toInt();
		}
	}
	else  // �����ѯʧ�ܣ�������ķ����õ��������ݿⷵ�ص�ԭ��
	{
		QSqlError error = query.lastError();
		return -1;
	}
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
			ptr[i].v_flow = query.value(6).toFloat();
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

//�����ݿ����һ���춨���
int CBaseExdb::insertVerifyRec(Record_Quality_PTR ptr)
{
	if (!db.isOpen())
	{
		startdb();
	}
	
	QSqlQuery query(db); // �½�һ����ѯ��ʵ��
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