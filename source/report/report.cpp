#include "report.h"


CReport::CReport(const QString& condition)
{
	    m_temp_file = QProcessEnvironment::systemEnvironment().value("TEMP");
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");
	QString current_time = QDateTime::currentDateTime().toString("yyyy-mm-dd hh-MM-ss");
#ifdef Q_OS_LINUX
	m_rpt_config_file = runhome + "\/ini\/rptconfig_common.ini";
	m_template_file   = runhome + "\/doc\/rpt-template.xls";
	m_temp_file		  = m_temp_file+"\/temp.xls";
	m_rpt_file        = runhome + "\/report\/report.xls" + current_time + ".xls";
#elif defined (Q_OS_WIN)
	m_rpt_config_file = runhome + "\\ini\\rptconfig_common.ini";
	m_template_file   = runhome + "\\doc\\rpt-template.xls";
	m_temp_file		  = m_temp_file+"\\temp.xls";
	m_rpt_file        = runhome + "\\report\\report" + current_time + ".xls";
#endif
	m_rpt_config = new QSettings(m_rpt_config_file, QSettings::IniFormat);

	m_query = new QSqlQuery();

	QFile::copy(m_template_file,m_temp_file);
	m_book = xlCreateBook();
	m_book->load(m_temp_file.toStdString().data());
	m_sheet = m_book->getSheet(0);
	m_condition = condition;
}

CReport::~CReport()
{
	if (m_rpt_config)
	{
		delete m_rpt_config;
		m_rpt_config = NULL;
	}
	if (m_query)
	{
		delete m_query;
		m_query = NULL;
	}
	if (m_book)
	{
		delete m_book;
		m_book = NULL;
	}
	if (m_sheet)
	{
		delete m_sheet;
		m_sheet = NULL;
	}
	qDebug()<<"destructing report";
}

void CReport::writeRpt()
{
	readConfigTHead();
	readConfigTBody();
	readTblName();
	getRptSQL();
	getDbData();
	writeHead();
	writeBody();
	deleteLog();
}

void CReport::writeHead()
{
	/************************************************************************/
	/* loop while (not arrive the end of headlist)							*/
	/*	1. get coordinates of current_field									*/
	/*	2. get current_field's db_value										*/
	/*	3. write current_field onto its position of target report file		*/
	/* end loop																*/
	/************************************************************************/
	m_query->first();
	QStringList coordinates;//coordinates of current_field, QStringList
	int x, y;//coordinates of current_field
	int idx;//current field's column index
	QString field_name;//current field's name
	QString field_value;//current field's value
	 
	for (int i=0; i < m_headList.count(); i++)
	{
		field_name = m_headList[i];
		coordinates = (QStringList)m_rpt_config->value("tablehead/" + field_name).toStringList();
		x = coordinates[0].toInt();
		y = coordinates[1].toInt();

		idx = m_query->record().indexOf(field_name);
		field_value = m_query->value(idx).toString().toLocal8Bit();

		m_sheet->writeStr(x,y,field_value.toStdString().data());
	}
}

void CReport::writeBody()
{

}

void CReport::readConfigTHead()
{
	 m_rpt_config->beginGroup("tablehead");
	 m_headList = m_rpt_config->allKeys();
	 m_rpt_config->endGroup();
}

void CReport::readConfigTBody()
{
	m_rpt_config->beginGroup("tablebody");
	QStringList m_bodyList = m_rpt_config->allKeys();
	m_rpt_config->endGroup();
}

void CReport::readTblName()
{
	 m_table_name = m_rpt_config->value("tableview/name").toString();
}

void CReport::getRptSQL()
{
	QStringList fields = m_headList + m_bodyList;
	m_query_Sql = "select ";
	for (int i=0; i< fields.count()-1; i++)
	{
		m_query_Sql.append(fields[i]);
		m_query_Sql.append(",");
	}
	m_query_Sql.append(fields[fields.count()-1] + " ");
	m_query_Sql.append("from " + m_table_name);
	m_query_Sql.append(" ");
	m_query_Sql.append(m_condition);
}

void CReport::getDbData()
{
	m_query->exec(m_query_Sql);
}

void CReport::deleteLog()
{
	//删除版权信息
	QExcel j(m_temp_file);
	j.selectSheet("Sheet1");
	QString copyright = j.getCellValue(1,1).toString();
	if (copyright=="Created by LibXL trial version. Please buy the LibXL full version for removing this message.")
	{
		j.deleteRow(1,1);
	}
	j.save();
	j.close();
	//保存报表到指定文件夹
	m_book->save(m_temp_file.toStdString().data());
	m_book->release();
	QFile::copy(m_temp_file, m_rpt_file);
}