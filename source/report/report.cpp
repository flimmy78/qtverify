#include "algorithm.h"
#include "report.h"


CReport::CReport(const QString& condition)
{
	    m_temp_file = QProcessEnvironment::systemEnvironment().value("TEMP");
	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
	QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
#ifdef Q_OS_LINUX
	m_template_file   = adehome + "\/doc\/rpt-template.xls";
	m_temp_file		  = m_temp_file+"\/" + current_time + ".xls";
	m_rpt_file        = adehome + "\/report\/report-" + current_time + ".xls";
#elif defined (Q_OS_WIN)
	m_template_file   = adehome + "\\doc\\rpt-template.xls";
	m_temp_file		  = m_temp_file+"\\" + current_time + ".xls";
	m_rpt_file        = adehome + "\\report\\report-" + current_time + ".xls";
#endif

	m_rpt_config= NULL;

	m_query = new QSqlQuery();

	QFile::copy(m_template_file,m_temp_file);
	m_book = xlCreateBook();
	m_book->load(m_temp_file.toStdString().data());
	m_sheet = m_book->getSheet(0);
	m_format = m_book->addFormat();
	m_font = m_book->addFont();

	//set cell format
	m_format->setBorder(BORDERSTYLE_THIN);
	m_font->setSize(10);
	m_font->setColor(COLOR_BLACK);
	m_font->setName("宋体");
	m_format->setFont(m_font);
	m_format->setAlignH(ALIGNH_CENTER);
	m_format->setAlignV(ALIGNV_CENTER);

	m_condition = condition;
}

CReport::~CReport()
{
	qDebug()<<"destructing report";

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
		m_book->release();//release all resources including sheet, format and font
		m_book = NULL;
	}
	if (m_sheet)
	{
		m_sheet = NULL;
	}
	if (m_format)
	{
		m_format = NULL;
	}
	if (m_font)
	{
		m_font = NULL;
	}
}

void CReport::setIniName(QString ini)
{
	if (m_rpt_config)
	{
		delete m_rpt_config;
	}
	m_rpt_config = new QSettings(getFullIniFileName(ini), QSettings::IniFormat);
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
	mergeBody();
	m_book->save(m_temp_file.toStdString().data());
	//deleteLog();
}

void CReport::writeHead()
{
	QStringList coordinates;//coordinates of current_field, QStringList
	int x, y;//coordinates of current_field
	int idx;//current field's column index
	QString field_name;//current field's name
	QString field_value;//current field's value

	m_query->first();
	QSqlRecord rec = m_query->record();
	for (int i=0; i < m_headList.count(); i++)
	{
		field_name = m_headList[i];
		coordinates = m_rpt_config->value("tablehead/" + field_name).toStringList();
		x = coordinates[0].toInt();
		y = coordinates[1].toInt();

		idx = rec.indexOf(field_name);
		field_value = m_query->value(idx).toString().toLocal8Bit();

		m_sheet->writeStr(x,y,field_value.toStdString().data());
	}
}

void CReport::writeBody()
{
	//read fundamental info
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();

	//declare some variables
	int rowidx, colidx;//coordinates of current_field
	int idx;//current field's column index in query record
	QString field_name;//current field's name
	QString field_value;//current field's value
	
	//write cells value
	m_query->seek(0);
	QSqlRecord rec = m_query->record();
	int offset = 0;
	while (true)
	{
		rowidx = start_with + offset;
		rec = m_query->record();
		for (int i=0; i < m_bodyList.count(); i++)
		{
			field_name = m_bodyList[i];
			colidx = m_rpt_config->value("tablebody/" + field_name).toInt();

			idx = rec.indexOf(field_name);
			field_value = m_query->value(idx).toString().toLocal8Bit();

			m_sheet->writeStr(rowidx,colidx,field_value.toStdString().data(), m_format);
		}
		if (!m_query->next())
		{
			break;
		}
		offset++;
	}
}

void CReport::mergeBody()
{
	//cols need merged
	QStringList need_merge = m_rpt_config->value("mergeInfo/needMerge").toStringList();

	for (int i=0; i < need_merge.count(); i++)
	{
		int start_col, end_col;
		start_col = end_col = m_rpt_config->value("tablebody/" + need_merge[i]).toInt();

		QStringList cur_merge_info = m_rpt_config->value("mergeInfo/" + need_merge[i]).toStringList();

		if (need_merge[i].toLower() == "valid")
		{
			mergeBool(need_merge[i], cur_merge_info[1]);
		}
		else if (need_merge[i].toLower() == "rowid")
		{
			mergeRowId(need_merge[i], cur_merge_info[1]);
		}
		else if (cur_merge_info[0].toLower() == "this")//"this", 只在本列查找相关合并信息即可
		{
			mergeSingleCol(need_merge[i]);
		}
	}
}

void CReport::mergeSingleCol(QString colName, int colNum)
{
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();//表体开始行号

	int start_row, end_row;//合并时的开始结束行号
	start_row = end_row = start_with;
	int current_row_num;//表体的当前行号
	int end_with_row = start_with + m_totalRecords-1;//表体的结束行号
	QString current_value, pre_value;//当前值和先前值
	QString sql = QString("select %1 from %2").arg(colName).arg(TEMP_QUERY_VIEW_NAME);

	m_query->exec(sql);
	m_query->seek(0);

	current_value = pre_value = m_query->value(0).toString().toLocal8Bit();
	current_row_num = start_with;
	do 
	{
		current_value = m_query->value(0).toString().toLocal8Bit();
		if (current_value != pre_value)
		{
			end_row = current_row_num-1;
			m_sheet->setMerge(start_row, end_row, colNum, colNum);
			start_row = current_row_num;
			pre_value = current_value;
		}
		current_row_num++;
	} while (m_query->next());
	m_sheet->setMerge(start_row, end_with_row, colNum, colNum);//合并最后一个值
}

void CReport::mergeSingleCol(QString colName)
{
	int colNum = m_rpt_config->value(QString("tablebody/%1").arg(colName)).toInt();//当前列的列号
	mergeSingleCol(colName, colNum);
}

void CReport::mergeBool(QString colName, QString father)
{
	int colNum = m_rpt_config->value(QString("tablebody/%1").arg(colName)).toInt();//当前列的列号
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();//表体开始行号
	int start_row, end_row;//合并时的开始结束行号
	start_row = end_row = start_with;
	int current_row_num;//表体的当前行号
	int end_with_row = start_with + m_totalRecords-1;//表体的结束行号
	QString current_value, pre_value;//当前值和先前值
	bool invalid_value;
	QString sql = QString("select %1, %2 from %3").arg(father).arg(colName).arg(TEMP_QUERY_VIEW_NAME);

	//设置字体, 用到的资源会在m_book->release()时被销毁
	Font *bool_font = m_book->addFont();
	Format* bool_format = m_book->addFormat();
	bool_format->setAlignH(ALIGNH_CENTER);
	bool_format->setAlignV(ALIGNV_CENTER);
	bool_format->setBorder(BORDERSTYLE_THIN);
	bool_font->setSize(10);
	bool_font->setName("宋体");
	bool_format->setFont(bool_font);

	m_query->exec(sql);
	m_query->seek(0);

	current_value = pre_value = m_query->value(0).toString().toLocal8Bit();
	invalid_value = (m_query->value(1).toString().toLocal8Bit().toLower() == "valid");
	current_row_num = start_with;
	do 
	{
		current_value = m_query->value(0).toString().toLocal8Bit();
		invalid_value = (invalid_value && (m_query->value(1).toString().toLocal8Bit().toLower() == "valid"));
		if (current_value != pre_value)
		{
			end_row = current_row_num-1;
			invalid_value ? bool_font->setColor(COLOR_GREEN):bool_font->setColor(COLOR_RED);		
			m_sheet->writeStr(start_row, colNum, QString(invalid_value?"合格":"不合格").toStdString().data(), bool_format);
			m_sheet->setMerge(start_row, end_row, colNum, colNum);
			start_row = current_row_num;
			pre_value = current_value;
			invalid_value = true;
		}
		current_row_num++;
	} while (m_query->next());
	m_sheet->writeStr(start_row, colNum, QString(invalid_value?"合格":"不合格").toStdString().data(), bool_format);//设置最后一个bool值
	m_sheet->setMerge(start_row, end_with_row, colNum, colNum);//合并最后一个值
}

void CReport::mergeRowId(QString colName, QString father)
{
	int colNum = m_rpt_config->value(QString("tablebody/%1").arg(colName)).toInt();//当前列的列号
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();//表体开始行号
	int start_row, end_row;//合并时的开始结束行号
	start_row = end_row = start_with;
	int current_row_num;//表体的当前行号
	int end_with_row = start_with + m_totalRecords-1;//表体的结束行号
	QString current_value, pre_value;//当前值和先前值
	int seq;//序号
	QString sql = QString("select %1, %2 from %3").arg(father).arg(colName).arg(TEMP_QUERY_VIEW_NAME);

	m_query->exec(sql);
	m_query->seek(0);

	current_value = pre_value = m_query->value(0).toString().toLocal8Bit();
	seq = 1;
	current_row_num = start_with;
	do 
	{
		current_value = m_query->value(0).toString().toLocal8Bit();
		if (current_value != pre_value)
		{
			end_row = current_row_num-1;
			m_sheet->writeStr(start_row, colNum, QString::number(seq).toStdString().data(), m_format);
			m_sheet->setMerge(start_row, end_row, colNum, colNum);
			start_row = current_row_num;
			pre_value = current_value;
			seq++;//父列的值变化, 序号增1
		}
		current_row_num++;
	} while (m_query->next());
	m_sheet->writeStr(start_row, colNum, QString::number(seq).toStdString().data(), m_format);//设置最后一个序号
	m_sheet->setMerge(start_row, end_with_row, colNum, colNum);//合并最后一个值
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
	m_bodyList = m_rpt_config->allKeys();
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
	for (int i=0; i < fields.count()-1; i++)
	{
		m_query_Sql.append(fields[i]);
		m_query_Sql.append(", ");
	}
	m_query_Sql.append(fields[fields.count()-1] + " ");
	m_query_Sql.append("from " + m_table_name);
	m_query_Sql.append(" ");
	m_query_Sql.append(m_condition);
}

void CReport::getDbData()
{
	m_query->exec(DROP_VIEW_STMT);
	QString createViewSql = QString("CREATE view %1 as %2 ;").arg(TEMP_QUERY_VIEW_NAME).arg(m_query_Sql);
	m_query->exec(createViewSql);

	m_query->exec(QString("select count(*) from %1").arg(TEMP_QUERY_VIEW_NAME));
	m_query->seek(0);
	m_totalRecords = m_query->value(0).toInt();
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
	//保存临时报表到指定文件夹
	//QFile::copy(m_temp_file, m_rpt_file);
}

void CReport::saveTo(QString file_path)
{
	QFile::copy(m_temp_file, file_path);
	QFile::remove(m_temp_file);
}