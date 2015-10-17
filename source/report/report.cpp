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
	qDebug() << "m_template_file Name :" << m_template_file;

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
	m_font->setName("����");
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
	m_query->exec(DROP_TEMP_VIEW_STMT);//��ɾ����ʱ��ͼ
	m_query->exec(DROP_TBL_STMT);//��ɾ����ʱ��
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
		else if (cur_merge_info[0].toLower() == "this")//"this", ֻ�ڱ��в�����غϲ���Ϣ����
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
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();//���忪ʼ�к�

	int start_row, end_row;//�ϲ�ʱ�Ŀ�ʼ�����к�
	start_row = end_row = start_with;
	int current_row_num;//����ĵ�ǰ�к�
	QString current_value, pre_value;//��ǰֵ����ǰֵ

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
	m_sheet->setMerge(start_row, current_row_num-1, colNum, colNum);//�ϲ����һ��ֵ
}

void CReport::mergeSingleCol(QString colName)
{
	int colNum = m_rpt_config->value(QString("tablebody/%1").arg(colName)).toInt();//��ǰ�е��к�
	mergeSingleCol(colName, colNum);
}

void CReport::mergeRowId(QString colName, QString father)
{
	int colNum = m_rpt_config->value(QString("tablebody/%1").arg(colName)).toInt();//��ǰ�е��к�
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();//���忪ʼ�к�
	int start_row, end_row;//�ϲ�ʱ�Ŀ�ʼ�����к�
	start_row = end_row = start_with;
	int current_row_num;//����ĵ�ǰ�к�
	QString current_value, pre_value;//��ǰֵ����ǰֵ
	
	if (!m_query->first())
	{
		throw QString("mergeRowId no record");
	}
	qDebug() << "mergeRowId seek first"<< m_query->first();
	QSqlRecord rec;
	rec = m_query->record();
	int idx = rec.indexOf(father);//���ֶ��ڲ�ѯ���������к�

	current_value = pre_value = m_query->value(idx).toString().toLocal8Bit();
	int seq = 1;//���
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
			seq++;//���е�ֵ�仯, �����1
		}
		current_row_num++;
	} while (m_query->next());
	m_sheet->writeStr(start_row, colNum, QString::number(seq).toStdString().data(), m_format);//�������һ�����
	m_sheet->setMerge(start_row, current_row_num-1, colNum, colNum);//�ϲ����һ��ֵ
}

void CReport::mergeBool(QString colName, QStringList fatherList)
{
	int colNum = m_rpt_config->value(QString("tablebody/%1").arg(colName)).toInt();//��ǰ�е��к�
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();//���忪ʼ�к�
	int start_row, end_row;//�ϲ�ʱ�Ŀ�ʼ�����к�
	start_row = end_row = start_with;
	int current_row_num;//����ĵ�ǰ�к�
	QString current_value, pre_value;//��ǰֵ����ǰֵ
	QStringList currentVList, previousVList;
	QList<int> fatherColNumList;//���ֶε��б���б�

	bool valid_value;
	QString validStr = ("�ϸ�");
	QString invalidStr = ("���ϸ�");
	//��������, �õ�����Դ����m_book->release()ʱ������
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
	valid_font->setName("����");
	valid_font->setColor(COLOR_GREEN);
	invalid_font->setSize(10);
	invalid_font->setName("����");
	invalid_font->setColor(COLOR_RED);
	valid_format->setFont(valid_font);
	invalid_format->setFont(invalid_font);

	m_query->seek(0);
	QSqlRecord rec;
	rec = m_query->record();
	for (int i = 1; i < fatherList.length();i++)//fatherList�����1��ʼ, 0�ǹؼ���"father"
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
	m_sheet->writeStr(start_row, colNum, QString(valid_value?validStr:invalidStr).toStdString().data(), valid_value?valid_format:invalid_format);//�������һ��boolֵ
	m_sheet->setMerge(start_row, current_row_num-1, colNum, colNum);//�ϲ����һ��ֵ
}

void CReport::mergeColByFather(QString colName, QStringList fatherList)
{
	int colNum = m_rpt_config->value(QString("tablebody/%1").arg(colName)).toInt();//��ǰ�е��к�
	int start_with = m_rpt_config->value("otherbodyInfo/startwith").toInt();//���忪ʼ�к�
	int start_row, end_row;//�ϲ�ʱ�Ŀ�ʼ�����к�
	start_row = end_row = start_with;
	int current_row_num;//����ĵ�ǰ�к�
	QString current_value, pre_value;//��ǰֵ����ǰֵ
	QStringList currentVList, previousVList;
	QList<int> fatherColNumList;
	bool valid_value;

	m_query->seek(0);
	QSqlRecord rec;
	rec = m_query->record();
	for (int i = 1; i < fatherList.length();i++)//fatherList�����1��ʼ, 0�ǹؼ���"father"
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
	m_sheet->setMerge(start_row, current_row_num-1, colNum, colNum);//�ϲ����һ��ֵ
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
* Ϊ�ӿ��ѯ�ٶ�, �ȴ�������ҷ���
* ��ѯ����������, ��������ʱ��;
* Ȼ��������ʱ��Ϊ�������ɶ�Ӧ����ͼ
*/
void CReport::getDbData()
{
	m_query->exec(DROP_TBL_STMT);//ɾ����ʱ��
	m_query->exec(CREATE_TEMP_TBL_STMT);//����ѯ����, ������ʱ��
	m_query->exec(DROP_TEMP_VIEW_STMT);//ɾ����ʱ��ͼ
	m_queryStmtId = m_rpt_config->value("tableview/stmtId").toString();
	m_query->exec(QUERY_CREATE_VIEW_STMT);//��ѯ������ʱ��ͼ�����
	m_query->seek(0);
	QString createViewSql = m_query->value(0).toString();
	//qDebug() << createViewSql;
	m_query->exec(createViewSql);//����ʱ��Ϊ����, ������ʱ��ͼ
	m_query->exec(m_query_Sql);//��ѯ��ʱ��ͼ
}

//ɾ����Ȩ��Ϣ
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