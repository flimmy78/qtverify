/***********************************************
**  �ļ���:     qtexdb.cpp
**  ����:       ��װ�����ݿ��������(SQLITE3)
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/25
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:  
	2014-8-7�޸�:
		�ɵ������Ϊ�����������������ݿ�ǰ����startdb()��Ȼ��ֱ�ӵ��õ����������ɣ������˳�ʱ������closedb()��
***********************************************/

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtGui/QMessageBox>
#include <QtCore/QProcess>

#include "qtexdb.h"
#include "commondefine.h"

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
		g_db = QSqlDatabase::addDatabase("QSQLITE");
	}

	QString dbname = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\\database\\" + g_dbname;
	g_db.setDatabaseName(dbname);
	if (!g_db.open())// �����������ݿ�
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

//��ȡ���еı���
int getMeterStandard(int& num, MeterStandard_PTR &ptr)
{
	int i = 0;
	QSqlQuery query; // �½�һ����ѯ��ʵ��
// 	bool a = query.driver()->hasFeature(QSqlDriver::Transactions);
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
			strcpy_s(ptr[i].name, query.value(1).toString().toAscii());
			ptr[i].quantity = query.value(2).toInt();
			i++;
		}
	}
	else  // �����ѯʧ�ܣ�������ķ����õ��������ݿⷵ�ص�ԭ��
	{
		QSqlError error = query.lastError();
		qWarning()<<error.text();
		return false;
	}

	return true;
}

/*
** ��������ȡ��Ӧ��������춨����
*/
int getMaxMeterByIdx(int idx)
{
	QSqlQuery query; // �½�һ����ѯ��ʵ��
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
		qWarning()<<error.text();
	}
	return -1;
}

//��ȡ���еı�����
int getMeterType(int& num, MeterType_PTR &ptr)
{
	int i = 0;
	QSqlQuery query; // �½�һ����ѯ��ʵ��
// 	bool a = query.driver()->hasFeature(QSqlDriver::QuerySize); //�Ƿ�֧��QuerySize����
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
			strcpy_s(ptr[i].name, query.value(1).toString().toAscii());
			strcpy_s(ptr[i].desc, query.value(2).toString().toLocal8Bit()); //���ֱ���
			qDebug()<<ptr[i].desc<<"::"<<query.value(1).toString().toLocal8Bit();
			i++;
		}
	}
	else  // �����ѯʧ�ܣ�������ķ����õ��������ݿⷵ�ص�ԭ��
	{
		QSqlError error = query.lastError();
		qWarning()<<error.text();
		return false;
	}

	return true;
}


//��ȡ���е����쵥λ
int getManufacture(int& num, Manufacture_PTR &ptr)
{
	int i = 0;
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	if(query.exec("select count(*) from t_manufacture_dept")) // t_manufacture_dept ��ļ�¼��
	{
		// ���β�ѯ�ɹ�
		query.first(); //��һ����¼
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
			strncpy_s(ptr[i].desc, query.value(2).toString().toLocal8Bit(), DESC_LEN); //���ֱ���
			strncpy(ptr[i].numprefix, query.value(3).toString().toLocal8Bit(), NUMPREFIX_LEN);
			i++;
		}
	}
	else  // �����ѯʧ�ܣ�������ķ����õ��������ݿⷵ�ص�ԭ��
	{
		QSqlError error = query.lastError();
		qWarning()<<error.text();
		return false;
	}

	return true;
}

/*
**  ��ȡ������ȱ��Ĭ�ϼ춨����
**  num: ��ѯ����ļ�¼��
**  ptr: �����ݱ�t_meter_default_params��Ӧ�Ľṹ
**  stand_id: ���������ֵ, �������������ϵ�comboBox
*/
int getDftDBinfo(int &num, DftDbInfo_PTR &ptr, int stand_id)
{
	int i = 0;
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	QString sql = "select count(*) from t_meter_default_params where F_StandardID = " + QString::number(stand_id);
	if(query.exec(sql)) // t_meter_standard ��ļ�¼��
	{
		// ���β�ѯ�ɹ�
		query.first(); //��һ����¼
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
		qWarning()<<error.text();
		return false;
	}

	return true;
}

/*
** �����ݿ����һ���춨����������߸�����ǰ�����ݿ�startdb()
*/
int insertVerifyRec(Record_Quality_PTR ptr, int num)
{
	for (int i=0; i<num; i++)
	{
		QSqlQuery query(g_db); // �½�һ����ѯ��ʵ��
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
		sql.append("F_ManufactDept,");
		sql.append("F_VerifyDept,");
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
		sql.append(QString("\'%1\', ").arg(ptr[i].timestamp, 0, 10));//F_TimeStamp
		sql.append(QString("%1, ").arg(ptr[i].meterNo,0, 10));//F_MeterNo
		sql.append(QString("%1, ").arg(ptr[i].flowPointIdx, 0, 10));//F_FlowPointIdx
		sql.append(QString("%1, ").arg(ptr[i].flowPoint, 6, 'g', 6));//F_FlowPoint
		sql.append(QString("%1, ").arg(ptr[i].totalFlag, 0, 10));//F_TotalFlag
		sql.append(QString("%1, ").arg(ptr[i].meterValue0, 6, 'g', 6));//F_MeterValue0
		sql.append(QString("%1, ").arg(ptr[i].meterValue1, 6, 'g', 6));//F_MeterValue1
		sql.append(QString("%1, ").arg(ptr[i].meterDeltaV, 6, 'g', 6));//F_MeterDeltaV
		sql.append(QString("%1, ").arg(ptr[i].balWeight0, 6, 'g', 6));//F_BalWeight0
		sql.append(QString("%1, ").arg(ptr[i].balWeight1, 6, 'g', 6));//F_BalWeight1
		sql.append(QString("%1, ").arg(ptr[i].balDeltaW, 6, 'g', 6));//F_BalDeltaW
		sql.append(QString("%1, ").arg(ptr[i].inSlotTemper, 6, 'g', 6));//F_InSlotTemper
		sql.append(QString("%1, ").arg(ptr[i].outSlotTemper, 6, 'g', 6));//F_OutSlotTemper
		sql.append(QString("%1, ").arg(ptr[i].pipeTemper, 6, 'g', 6));//F_PipeTemper
		sql.append(QString("%1, ").arg(ptr[i].density, 6, 'g', 6));//F_Density
		sql.append(QString("%1, ").arg(ptr[i].stdValue, 6, 'g', 6));//F_StandValue
		sql.append(QString("%1, ").arg(ptr[i].dispError, 6, 'g', 6));//F_DispError
		sql.append(QString("%1, ").arg(ptr[i].stdError, 6, 'g', 6));//F_StdError
		sql.append(QString("%1, ").arg(ptr[i].result, 0, 10));//F_Result
		sql.append(QString("%1, ").arg(ptr[i].meterPosNo, 0, 10));//F_MeterPosNo
		sql.append(QString("%1, ").arg(ptr[i].model, 0, 10));//F_Model
		sql.append(QString("%1, ").arg(ptr[i].standard, 0, 10));//F_Standard
		sql.append(QString("%1, ").arg(ptr[i].meterType, 0, 10));//F_MeterType
		sql.append(QString("%1, ").arg(ptr[i].manufactDept, 0, 10));//F_ManufactDept
		sql.append(QString("%1, ").arg(ptr[i].verifyDept, 0, 10));//F_VerifyDept
		sql.append(QString("%1, ").arg(ptr[i].grade, 0, 10));//F_Grade
		sql.append(QString("%1, ").arg(ptr[i].verifyPerson, 0, 10));//F_VerifyPerson
		sql.append(QString("%1, ").arg(ptr[i].checkPerson, 0, 10));//F_CheckPerson
		sql.append(QString("\'%1\', ").arg(ptr[i].date));//F_VerifyDate
		sql.append(QString("%1, ").arg(ptr[i].envTemper, 6, 'g', 6));//F_EnvTemper
		sql.append(QString("%1, ").arg(ptr[i].envHumidity, 6, 'g', 6));//F_EnvHumidity
		sql.append(QString("%1, ").arg(ptr[i].airPress, 6, 'g', 6));//F_AirPressure
		sql.append(QString("\'%1\', ").arg(ptr[i].validDate, 0, 10));//F_ValidDate
		sql.append(QString("%1").arg(ptr[i].recordNumber, 0, 10));//F_RecordNumber
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
** �����ݿ����һ�������춨����������߸�����ǰ�����ݿ�startdb()
*/
int insertFlowVerifyRec(Flow_Verify_Record_PTR ptr, int num)
{
	for (int i=0; i<num; i++)
	{
		QSqlQuery query(g_db); // �½�һ����ѯ��ʵ��
		QString sql = "insert into T_Flow_Verify_Record";
		sql.append("(");
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
		sql.append("F_MeterType,");
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
		sql.append("F_Bak1,");
		sql.append("F_Bak2,");
		sql.append("F_Bak3,");
		sql.append("F_Bak4");
		sql.append(")");
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
		sql.append(QString("%1, ").arg(ptr[i].meterType, 0, 10));//F_MeterType
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
		sql.append(QString("%1").arg(ptr[i].certNo, 0, 10));//F_CertNO
		sql.append(QString("%1").arg(ptr[i].bak1, 0, 10));//F_Bak1
		sql.append(QString("%1").arg(ptr[i].bak2, 0, 10));//F_Bak2
		sql.append(QString("%1").arg(ptr[i].bak3, 0, 10));//F_Bak3
		sql.append(QString("%1").arg(ptr[i].bak4, 0, 10));//F_Bak4
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
	QSqlQuery query; // �½�һ����ѯ��ʵ��
	if(query.exec(sqlstr))
	{
		query.next();
		str = query.value(1).toString();
		return str;
	}
	else  // �����ѯʧ�ܣ�������ķ����õ��������ݿⷵ�ص�ԭ��
	{
		QSqlError error = query.lastError();
		qWarning()<<error.text();
		return "";
	}
}

/*
** ��ȡ��Ķ������
** tbl_name: �������
** �쳣: ����������
*/
QString getTblDdl(QString tbl_name)
{
	QString sql = QString("SELECT sql FROM sqlite_master WHERE upper(tbl_name) = upper('%1') AND type = 'table'").arg(tbl_name);//��ѯ���
	QString ddl;//��Ķ������

	QStringList tbls = g_db.tables();
	//�������������, �׳��쳣
	if (!tbls.contains(tbl_name, Qt::CaseInsensitive))
	{
		throw QString("no this table: %1").arg(tbl_name);
	}
	//��ʼ��ѯ
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
** ȥ��sql����е�ע��
** s: sql���, ���Դ�ע��, Ҳ���Բ���ע��
*/
QString removeComment(QString s)
{
	QString t;
	for(int i = 0; i < s.length() - 1; i++)
	{
		//ע����"--"��ʼ, ��'\n'����
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

	//����ѭ��ʱ, ֻɨ�赽������2���ַ�
	//����Ҫ������һ���ַ��Ƿ���Ҫ׷���������ִ�
	char last = s[s.length()-1].toAscii();
	if (last != ' ' && last != '\n')
	{
		t.append(last);
	}
	return t;
}

/*
** �õ�QMap<�ֶ���, �ֶ�����>��ֵ
** tbl_name: �������
*/
QMap<QString, QString> getColInfo(QString tbl_name)
{
	//��ȡ�����sql���
	QString ddl = getTblDdl(tbl_name);
	/////////////////ȥ������,ֻ�����ֶζ���///////////////////////
	int left_parenthesis_idx = ddl.indexOf('(');//��һ������������
	int right_parenthesis_idx = ddl.lastIndexOf(')');//���һ������������
	QString mid = ddl.mid(left_parenthesis_idx + 1, right_parenthesis_idx - left_parenthesis_idx - 1);
	//mid = mid.left(mid.length()-1);
	////////////////////ȥ��ע��, ���ϲ��հ�/////////////////////////
	QString remove_comment = removeComment(mid).simplified();
	/////////////////////��','�Ŵ��//////////////////////////////////////
	QStringList columns = remove_comment.split(',');

	QMap<QString, QString> colInfo;//QMap<�ֶ���, �ֶ�����>��ֵ
	for (int i = 0; i < columns.count(); i++)
	{
		QStringList col = columns[i].simplified().split(' ');//ȥ���ִ���ͷ���β�Ŀհ�, �ϲ��м�Ŀհ�
		colInfo[col[0]] = col[1];//�洢��-ֵ
	}
	return colInfo;
}