#include "report.h"


CReport::CReport(const QString& condition)
{
	    m_temp_file = QProcessEnvironment::systemEnvironment().value("TEMP");
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");
	QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
#ifdef Q_OS_LINUX
	m_rpt_config_file = runhome + "\/ini\/rptconfig_common.ini";
	m_template_file   = runhome + "\/doc\/rpt-template.xls";
	m_temp_file		  = m_temp_file+"\/" + current_time + ".xls";
	m_rpt_file        = runhome + "\/report\/report-" + current_time + ".xls";
#elif defined (Q_OS_WIN)
	m_rpt_config_file = runhome + "\\ini\\rptconfig_common.ini";
	m_template_file   = runhome + "\\doc\\rpt-template.xls";
	m_temp_file		  = m_temp_file+"\\" + current_time + ".xls";
	m_rpt_file        = runhome + "\\report\\report-" + current_time + ".xls";
#endif
	m_rpt_config = new QSettings(m_rpt_config_file, QSettings::IniFormat);

	m_query = new QSqlQuery();

	QFile::copy(m_template_file,m_temp_file);
	m_book = xlCreateBook();
	m_book->load(m_temp_file.toStdString().data());
	m_sheet = m_book->getSheet(0);
	m_format = m_book->addFormat();
	m_font = m_book->addFont();
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
	m_query->first();
	QStringList coordinates;//coordinates of current_field, QStringList
	int x, y;//coordinates of current_field
	int idx;//current field's column index
	QString field_name;//current field's name
	QString field_value;//current field's value
	 
	for (int i=0; i < m_headList.count(); i++)
	{
		field_name = m_headList[i];
		coordinates = m_rpt_config->value("tablehead/" + field_name).toStringList();
		x = coordinates[0].toInt();
		y = coordinates[1].toInt();

		idx = m_query->record().indexOf(field_name);
		field_value = m_query->value(idx).toString().toLocal8Bit();

		m_sheet->writeStr(x,y,field_value.toStdString().data());
	}
}

void CReport::writeBody()
{
	//read fundamental info
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();
	QStringList need_merge = m_rpt_config->value("mergeInfo/needMerge").toStringList();

	//set cell format
	m_format->setBorder(BORDERSTYLE_THIN);
	m_font->setSize(10);
	m_font->setName("宋体");
	m_format->setFont(m_font);
	m_format->setAlignH(ALIGNH_CENTER);
	m_format->setAlignV(ALIGNV_CENTER);

	//declare some variables
	int rowidx, colidx;//coordinates of current_field
	int idx;//current field's column index in query record
	QString field_name;//current field's name
	QString field_value;//current field's value
	
	//write cells value
	m_query->seek(0);
	int offset = 0;
	while (true)
	{
		rowidx = start_with + offset;
		for (int i=0; i < m_bodyList.count(); i++)
		{
			field_name = m_bodyList[i];
			colidx = m_rpt_config->value("tablebody/" + field_name).toInt();

			idx = m_query->record().indexOf(field_name);
			field_value = m_query->value(idx).toString().toLocal8Bit();

			m_sheet->writeStr(rowidx,colidx,field_value.toStdString().data(), m_format);
		}
		if (!m_query->next())
		{
			break;
		}
		offset++;
	}

	//merge cells; need_merge[i]: current column's name
	int total_row = start_with + offset;
	for (int i=0; i < need_merge.count(); i++)
	{
		int start_col, end_col;
		start_col = end_col = m_rpt_config->value("tablebody/" + need_merge[i]).toInt();

		QStringList cur_merge_info = m_rpt_config->value("mergeInfo/" + need_merge[i]).toStringList();
		if (cur_merge_info[0].toLower() == "this")
		{
			mergeCells(start_with, total_row, start_col, end_col);
		}
		else if (cur_merge_info[0].toLower() == "ref")
		{
			int range_idx;

			QString ref_col_name = cur_merge_info[1];
			int ref_start_row, ref_end_row, ref_start_col, ref_end_col;
			ref_start_col = ref_end_col = m_rpt_config->value("tablebody/" + ref_col_name).toInt();			
			for (range_idx = start_with; range_idx <= total_row; range_idx = ref_end_row + 1)
			{
				m_sheet->getMerge(range_idx, ref_start_col, &ref_start_row, &ref_end_row, &ref_start_col, &ref_end_col);
				mergeCells(ref_start_row, ref_end_row, start_col, end_col);
			}			
		}
		else if (cur_merge_info[0].toLower() == "equal")
		{
			if (need_merge[i].toLower() == "valid")
			{
				int range_idx;

				QString ref_col_name = cur_merge_info[1];
				int ref_start_row, ref_end_row, ref_start_col, ref_end_col;
				ref_start_col = ref_end_col = m_rpt_config->value("tablebody/" + ref_col_name).toInt();			
				for (range_idx = start_with; range_idx <= total_row; range_idx = ref_end_row + 1)
				{
					m_sheet->getMerge(range_idx, ref_start_col, &ref_start_row, &ref_end_row, &ref_start_col, &ref_end_col);
					writeBool(ref_start_row, ref_end_row, start_col, end_col);
				}	
			}
		}
	}
}

void CReport::mergeCells(int start_with_row, int end_with_row, int start_with_col, int end_with_col)
{
	int start_row, end_row, start_col, end_col;
	int current_row;
	start_row = end_row = start_with_row;
	start_col = end_col = start_with_col;
	QString current_value, pre_value;//current cell value and previous cell value
	current_value = pre_value = m_sheet->readStr(start_row, start_col);//init value
	for (current_row = start_with_row; current_row <= end_with_row; current_row++)
	{
		current_value = m_sheet->readStr(current_row, start_col);
		
		if (current_value != pre_value)
		{
			end_row = current_row -1;
			m_sheet->setMerge(start_row, end_row, start_col, end_col);
			start_row = current_row;
			pre_value = current_value;
		}

		if (current_row == end_with_row)
		{
			end_row = current_row;
			m_sheet->setMerge(start_row, end_row, start_col, end_col);
		}
	}
}

void CReport::writeBool(int start_with_row, int end_with_row, int start_with_col, int end_with_col)
{
	QString value;
	bool found_invalid;
	//Font* invalid_font = m_book->addFont();
	for (int rowidx=start_with_row; rowidx<=end_with_row;rowidx++)
	{
		value = m_sheet->readStr(rowidx, start_with_col);
		if (value == "不合格")
		{
			//invalid_font->setColor(COLOR_RED);
			break;
		}
	}
	//Format* invalid_format = m_book->addFormat();
	//invalid_font->setSize(10);
	//invalid_font->setName("宋体");
	//invalid_format->setFont(invalid_font);
	m_sheet->writeStr(start_with_row, start_with_col, value.toStdString().data());
	m_sheet->setMerge(start_with_row, end_with_row, start_with_col, end_with_col);
	//if (invalid_format)
	//{
	//	delete invalid_format;
	//	invalid_format = NULL;
	//}
	//if (invalid_font)
	//{
	//	delete invalid_font;
	//	invalid_font = NULL;
	//}
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
	m_query->exec(m_query_Sql);
}

void CReport::deleteLog()
{
	//保存临时报表
	m_book->save(m_temp_file.toStdString().data());
	//m_book->release();
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
	QFile::copy(m_temp_file, m_rpt_file);
	QFile::remove(m_temp_file);
}

void CReport::saveTo(QString file_path)
{
	QFile::copy(m_rpt_file, file_path);
}