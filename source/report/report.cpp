#include "algorithm.h"
#include "report.h"


CReport::CReport(const QString& condition)
{
	m_rpt_config= NULL;
	m_query = NULL;
	m_book = NULL;
	m_sheet = NULL;
	m_format = NULL;
	m_font = NULL;
	m_query = new QSqlQuery(g_defaultdb);
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
	QString ininame = getFullIniFileName(ini);
	m_rpt_config = new QSettings(getFullIniFileName(ini), QSettings::IniFormat);

	m_temp_file = QProcessEnvironment::systemEnvironment().value("TEMP");
	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
	QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
#ifdef Q_OS_LINUX
	m_template_file   = adehome + "\/doc\/";
	m_temp_file		  = m_temp_file+"\/" + current_time + ".xls";
#elif defined (Q_OS_WIN)
	m_template_file   = adehome + "\\doc\\";
	m_temp_file		  = m_temp_file+"\\" + current_time + ".xls";
#endif
	m_template_file.append(m_rpt_config->value("template/name").toString());

	if (!QFile::exists(m_template_file))
	{
		qCritical() << "template file::"<< m_template_file <<"not exists !";
		throw QString("template file: ").append(m_template_file).append(" not exists !");
		return;
	}
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
	deleteLog();
}

void CReport::writeHead()
{
	QStringList coordinates;//coordinates of current_field, QStringList
	int x, y;//coordinates of current_field
	int idx;//current field's column index
	QString field_name;//current field's name
	QString field_value;//current field's value
	if (!m_query->first())
	{
		throw QString("no record");
	}
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
	if (!m_query->first())
	{
		throw QString("no record");
	}
	QSqlRecord rec = m_query->record();
	int offset = 0;
	do
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
		offset++;
	}while (m_query->next());
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

		if (need_merge[i].toLower() == "valid_en")
		{
			mergeBool(need_merge[i], cur_merge_info);
		}
		else if (need_merge[i].toLower() == "f_rowid")
		{
			mergeRowId(need_merge[i], cur_merge_info[1]);
		}
		else if (cur_merge_info[0].toLower() == "this")//"this", 只在本列查找相关合并信息即可
		{
			mergeSingleCol(need_merge[i]);
		}
		else if (cur_merge_info[0].toLower() == "father")
		{
			mergeColByFather(need_merge[i], cur_merge_info);
		}
	}
}

void CReport::mergeSingleCol(QString colName, int colNum)
{
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();//表体开始行号

	int start_row, end_row;//合并时的开始结束行号
	start_row = end_row = start_with;
	int current_row_num;//表体的当前行号
	QString current_value, pre_value;//当前值和先前值

	m_query->seek(0);
	QSqlRecord rec;
	rec = m_query->record();
	int idx = rec.indexOf(colName);
	current_value = pre_value = m_query->value(idx).toString().toLocal8Bit();
	current_row_num = start_with;
	do
	{
		current_value = m_query->value(idx).toString().toLocal8Bit();
		if (current_value != pre_value)
		{
			end_row = current_row_num-1;
			m_sheet->setMerge(start_row, end_row, colNum, colNum);
			start_row = current_row_num;
			pre_value = current_value;
		}
		current_row_num++;
	} while (m_query->next());
	m_sheet->setMerge(start_row, current_row_num-1, colNum, colNum);//合并最后一个值
}

void CReport::mergeSingleCol(QString colName)
{
	int colNum = m_rpt_config->value(QString("tablebody/%1").arg(colName)).toInt();//当前列的列号
	mergeSingleCol(colName, colNum);
}

void CReport::mergeRowId(QString colName, QString father)
{
	int colNum = m_rpt_config->value(QString("tablebody/%1").arg(colName)).toInt();//当前列的列号
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();//表体开始行号
	int start_row, end_row;//合并时的开始结束行号
	start_row = end_row = start_with;
	int current_row_num;//表体的当前行号
	QString current_value, pre_value;//当前值和先前值
	
	if (!m_query->first())
	{
		throw QString("mergeRowId no record");
	}
	qDebug() << "mergeRowId seek first"<< m_query->first();
	QSqlRecord rec;
	rec = m_query->record();
	int idx = rec.indexOf(father);//父字段在查询中所处的列号

	current_value = pre_value = m_query->value(idx).toString().toLocal8Bit();
	int seq = 1;//序号
	current_row_num = start_with;
	do
	{
		current_value = m_query->value(idx).toString().toLocal8Bit();
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
	m_sheet->setMerge(start_row, current_row_num-1, colNum, colNum);//合并最后一个值
}

void CReport::mergeBool(QString colName, QStringList fatherList)
{
	int colNum = m_rpt_config->value(QString("tablebody/%1").arg(colName)).toInt();//当前列的列号
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();//表体开始行号
	int start_row, end_row;//合并时的开始结束行号
	start_row = end_row = start_with;
	int current_row_num;//表体的当前行号
	QString current_value, pre_value;//当前值和先前值
	QStringList currentVList, previousVList;
	QList<int> fatherColNumList;//父字段的列编号列表

	bool valid_value;
	QString validStr = ("合格");
	QString invalidStr = ("不合格");
	//设置字体, 用到的资源会在m_book->release()时被销毁
	Font *valid_font = m_book->addFont();
	Font *invalid_font = m_book->addFont();
	Format* valid_format = m_book->addFormat();
	Format* invalid_format = m_book->addFormat();

	valid_format->setAlignH(ALIGNH_CENTER);
	valid_format->setAlignV(ALIGNV_CENTER);
	valid_format->setBorder(BORDERSTYLE_THIN);
	invalid_format->setAlignH(ALIGNH_CENTER);
	invalid_format->setAlignV(ALIGNV_CENTER);
	invalid_format->setBorder(BORDERSTYLE_THIN);

	valid_font->setSize(10);
	valid_font->setName("宋体");
	valid_font->setColor(COLOR_GREEN);
	invalid_font->setSize(10);
	invalid_font->setName("宋体");
	invalid_font->setColor(COLOR_RED);
	valid_format->setFont(valid_font);
	invalid_format->setFont(invalid_font);

	m_query->seek(0);
	QSqlRecord rec;
	rec = m_query->record();
	for (int i = 1; i < fatherList.length();i++)//fatherList的项从1开始, 0是关键字"father"
	{
		fatherColNumList.append(rec.indexOf(fatherList.at(i)));
	}
	

	int valid_col = fatherList.length();
	int valueLen = valid_col-1;
	for (int i = 0; i < valueLen;i++)
	{
		currentVList.append(m_query->value(fatherColNumList.at(i)).toString().toLocal8Bit());
		previousVList.append(m_query->value(fatherColNumList.at(i)).toString().toLocal8Bit());
	}
	int idx = rec.indexOf(colName);
	valid_value = (m_query->value(idx).toString().toLocal8Bit().toLower() == "yes");
	current_row_num = start_with;

	bool fatherChanged = false;
	do
	{
		for(int i=0; i < valueLen;i++)
		{
			currentVList[i] = m_query->value(fatherColNumList.at(i)).toString().toLocal8Bit();
			fatherChanged = ( fatherChanged || !(currentVList.at(i)==previousVList.at(i)));
		}
		if (fatherChanged)
		{
			end_row = current_row_num-1;
			m_sheet->writeStr(start_row, colNum, QString(valid_value?validStr:invalidStr).toStdString().data(), valid_value?valid_format:invalid_format);
			m_sheet->setMerge(start_row, end_row, colNum, colNum);
			start_row = current_row_num;
			for (int i=0; i < valueLen;i++)
			{
				previousVList[i]=currentVList.at(i);
			}
			valid_value = true;
			fatherChanged = false;
		}
		valid_value = (valid_value && (m_query->value(idx).toString().toLocal8Bit().toLower() == "yes"));
		current_row_num++;
	} while (m_query->next());
	m_sheet->writeStr(start_row, colNum, QString(valid_value?validStr:invalidStr).toStdString().data(), valid_value?valid_format:invalid_format);//设置最后一个bool值
	m_sheet->setMerge(start_row, current_row_num-1, colNum, colNum);//合并最后一个值
}

void CReport::mergeColByFather(QString colName, QStringList fatherList)
{
	int colNum = m_rpt_config->value(QString("tablebody/%1").arg(colName)).toInt();//当前列的列号
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();//表体开始行号
	int start_row, end_row;//合并时的开始结束行号
	start_row = end_row = start_with;
	int current_row_num;//表体的当前行号
	QString current_value, pre_value;//当前值和先前值
	QStringList currentVList, previousVList;
	QList<int> fatherColNumList;

	m_query->seek(0);
	QSqlRecord rec;
	rec = m_query->record();
	for (int i = 1; i < fatherList.length();i++)//fatherList的项从1开始, 0是关键字"father"
	{
		fatherColNumList.append(rec.indexOf(fatherList.at(i)));
	}

	int valid_col = fatherList.length();
	int valueLen = valid_col-1;
	for (int i = 0; i < valueLen;i++)
	{
		currentVList.append(m_query->value(fatherColNumList.at(i)).toString().toLocal8Bit());
		previousVList.append(m_query->value(fatherColNumList.at(i)).toString().toLocal8Bit());
	}
	current_row_num = start_with;

	bool fatherChanged = false;
	do
	{
		for(int i=0; i < valueLen;i++)
		{
			currentVList[i] = m_query->value(fatherColNumList.at(i)).toString().toLocal8Bit();

			fatherChanged = ( fatherChanged || !(currentVList.at(i)==previousVList.at(i)));
		}
		qDebug() << "currentVList: " << currentVList;
		if (fatherChanged)
		{
			end_row = current_row_num-1;
			m_sheet->setMerge(start_row, end_row, colNum, colNum);
			start_row = current_row_num;
			for (int i=0; i < valueLen;i++)
			{
				previousVList[i]=currentVList.at(i);
			}
			fatherChanged = false;
		}
		current_row_num++;
	} while (m_query->next());
	m_sheet->setMerge(start_row, current_row_num-1, colNum, colNum);//合并最后一个值
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
	 m_view	 = m_rpt_config->value("tableview/view").toString();
	 m_table = m_rpt_config->value("tableview/table").toString();
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
	m_query_Sql.append("from " + m_view);
	m_query_Sql.append(" where ");
	m_query_Sql.append(m_condition);
}

/*
* 为加快查询速度, 先从主表查找符合
* 查询条件的数据, 并生成临时表;
* 然后再以临时表为基础生成对应的视图
*/
void CReport::getDbData()
{
	qDebug() << "database file path: " << g_defaultdb.hostName();
	m_query->exec(DROP_TBL_STMT);//删除临时表

	qDebug() << "create temp table statment: " << CREATE_TEMP_TBL_STMT;
	qDebug() << "EXECUTED CREATE_TEMP_TBL_STMT: " << m_query->exec(CREATE_TEMP_TBL_STMT);//按查询条件, 创建临时表
	
	qDebug() << "EXECUTED DROP_TEMP_VIEW_STMT: " << m_query->exec(DROP_TEMP_VIEW_STMT);//删除临时视图
	m_queryStmtId = m_rpt_config->value("tableview/stmtId").toString();
	qDebug() << "EXECUTED QUERY_CREATE_VIEW_STMT: " << m_query->exec(QUERY_CREATE_VIEW_STMT);//查询创建临时视图的语句
	qDebug() << "QUERY VIEW statment: " << QUERY_CREATE_VIEW_STMT;
	m_query->seek(0);
	QString createViewSql = m_query->value(0).toString();
	qDebug() << "createViewSql: " << createViewSql;
	qDebug() << "EXECUTED createViewSql: " << m_query->exec(createViewSql);//以临时表为主表, 创建临时视图
	
	qDebug()  << "m_query_Sql: " << m_query_Sql;
	qDebug() << "EXECUTED m_query_Sql: " << m_query->exec(m_query_Sql);//查询临时视图

	qDebug() << "number of rows returned: " << m_query->numRowsAffected();
}

//删除版权信息
void CReport::deleteLog()
{
	QExcel j(m_temp_file);
	j.selectSheet("Sheet1");
	QString copyright = j.getCellValue(1,1).toString();
	if (copyright=="Created by LibXL trial version. Please buy the LibXL full version for removing this message.")
	{
		j.deleteRow(1,1);
	}
	j.save();
	j.close();
}

void CReport::saveTo(QString file_path)
{
	QFile::copy(m_temp_file, file_path);
	QFile::remove(m_temp_file);
}