/***********************************************
**  文件名:     mainform.cpp
**  功能:       检定台上位机主界面框架
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/12
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/06 第一版
**  内容包含:
**  说明:		只针对于DN15~DN25的小台子
**  更新记录:   
***********************************************/

#include <QtGui/QMessageBox>
#include <QAxObject>
#include <QProcess>
#include <QtCore>

#include "mainform.h"

MainForm::MainForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	qDebug()<<"MainForm thread:"<<QThread::currentThreadId();

	ui.setupUi(this);

	m_mySql = NULL;
	m_query = NULL;
	m_alg = new CAlgorithm();

	m_setcom = NULL;
	m_datatestdlg = NULL;
	m_portSet = NULL;
	m_masterslave = NULL;
	m_weightDlg = NULL;
	m_comProcess = new QProcess(this);

	QLabel *permanent = new QLabel(this);
	permanent->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	permanent->setText(tr("<a href=\"http://www.sdm.com.cn\">Shandong Delu Measurement Co.,Ltd.</a>"));
	permanent->setTextFormat(Qt::RichText);
	permanent->setOpenExternalLinks(true);
	ui.statusBar->addPermanentWidget(permanent);
}

MainForm::~MainForm()
{
}

void MainForm::closeEvent( QCloseEvent * event)
{
	int button = QMessageBox::question(this, tr("Question"), tr("Quit Really ?"), \
		QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape);
	if (button == QMessageBox::No)
	{
		event->ignore();
	}
	else if (button == QMessageBox::Yes)
	{
		event->accept();
		qDebug()<<"^^^^^MainForm::closeEvent";

		if (m_mySql)
		{
			delete m_mySql;
			m_mySql = NULL;
		}

		if (m_query)
		{
			delete m_query;
			m_query = NULL;
		}

		if (m_alg)
		{
			delete m_alg;
			m_alg = NULL;
		}

		if (m_setcom)
		{
			delete m_setcom;
			m_setcom = NULL;
		}

		if (m_portSet)
		{
			delete m_portSet;
			m_portSet = NULL;
		}

		if (m_datatestdlg)
		{
			delete m_datatestdlg;
			m_datatestdlg = NULL;
		}

		if (m_masterslave)
		{
			delete m_masterslave;
			m_masterslave = NULL;
		}

		if (m_weightDlg)
		{
			delete m_weightDlg;
			m_weightDlg = NULL;
		}

		if (m_comProcess)
		{
			m_comProcess->kill();
		}
	}
}

void MainForm::on_actionComDebuger_triggered()
{
	QStringList cmdlist;
	cmdlist<<"-zh";
	m_comProcess->start("qcom", cmdlist);
}

void MainForm::on_actionComSet_triggered()
{
	if (NULL == m_setcom)
	{
		m_setcom = new SetComFrm();
	}
	m_setcom->show();
}

void MainForm::on_actionPortSet_triggered()
{
	if (NULL == m_portSet)
	{
		m_portSet = new SetPortFrm();
	}
	m_portSet->show();
}

void MainForm::on_actionMySql_triggered()
{
	if (NULL == m_mySql)
	{
		m_mySql = new DbMySql();
	}
	m_mySql->show();
}

void MainForm::on_actionFlowResult_triggered()
{
	if (NULL == m_query)
	{
		m_query = new QueryResult();
	}
	else
	{
		delete m_query;
		m_query = new QueryResult();
	}
	m_query->show();
}

void MainForm::on_actionExit_triggered()
{
	this->close();
}

void MainForm::on_actionAbout_triggered()
{
	QMessageBox::aboutQt(this);
}

void MainForm::on_actionQueryExcel_triggered()
{
	QAxObject *excel = NULL;
	excel = new QAxObject("Excel.Application");
	if (!excel)
	{ 
		QMessageBox::critical(this, tr("Error"), tr("Excel object lose!"));
		return;
	}
	QAxObject *workbooks = NULL;
	QAxObject *workbook = NULL;
	excel->dynamicCall("SetVisible(bool)", false);
	workbooks = excel->querySubObject("WorkBooks");
	QString xlsFile = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\\dat\\test.xlsx";
	workbook = workbooks->querySubObject("Open(QString, QVariant)", xlsFile);
	if (NULL==workbook)
	{
		return;
	}
	QAxObject * worksheet = workbook->querySubObject("WorkSheets(int)", 1);//打开第一个sheet
	QAxObject * usedrange = worksheet->querySubObject("UsedRange");//获取该sheet的使用范围对象
	QAxObject * rows = usedrange->querySubObject("Rows");
	QAxObject * columns = usedrange->querySubObject("Columns");
	int intRowStart = usedrange->property("Row").toInt();
	int intColStart = usedrange->property("Column").toInt();
	int intCols = columns->property("Count").toInt();
	int intRows = rows->property("Count").toInt();

	for (int i = intRowStart; i < intRowStart + intRows; i++) //行 
	{
		for (int j = intColStart; j < intColStart + intCols; j++) //列 
		{
			QAxObject * range = worksheet->querySubObject("Cells(int,int)", i, j ); //获取单元格  
			qDebug("row %d, col %d, value is %d\n", i, j, range->property("Value").toInt()); //************出问题!!!!!! 
		} 
	}
}

//质量法-分量检定
void MainForm::on_actionWeightComp_triggered()
{
	if (NULL == m_weightDlg)
	{
		m_weightDlg = new WeightMethodDlg();
	}
	else //目的是执行WeightMethodDlg的构造函数
	{
		delete m_weightDlg;
		m_weightDlg = NULL;
		m_weightDlg = new WeightMethodDlg();
	}
	m_weightDlg->show();
}

//质量法-总量检定
void MainForm::on_actionWeightTotal_triggered()
{
}

//主机-从机设置
void MainForm::on_actionMasterSlaveSet_triggered()
{
	if (NULL == m_masterslave)
	{
		m_masterslave = new CMasterSlave();
	}
	m_masterslave->show();
}

//采集与控制测试程序
void MainForm::on_actionTest_triggered()
{
	if (NULL == m_datatestdlg)
	{
		m_datatestdlg = new DataTestDlg();
	}
	else //目的是执行QualityDlg的构造函数
	{
		delete m_datatestdlg;
		m_datatestdlg = NULL;
		m_datatestdlg = new DataTestDlg();
	}
	m_datatestdlg->show();
}

void MainForm::on_actionDefault_triggered()
{
	QFile qss(":/qtverify/qss/default.qss");
	qss.open(QFile::ReadOnly);
	this->setStyleSheet(qss.readAll());
	qss.close();
}

void MainForm::on_actionClassic_triggered()
{
	QFile qss(":/qtverify/qss/classic.qss");
	qss.open(QFile::ReadOnly);
	this->setStyleSheet(qss.readAll());
	qss.close();
}

void MainForm::on_actionFashion_triggered()
{
	QFile qss(":/qtverify/qss/fashion.qss");
	qss.open(QFile::ReadOnly);
	this->setStyleSheet(qss.readAll());
	qss.close();
}

void MainForm::chaneLanguage(QString lang)
{
	char file_name[100];
	sprintf_s( file_name, "%s\\ini\\tr_qtverify.ini", getenv("RUNHOME"));
	QFile file(file_name );
	if( !file.open(QIODevice::ReadOnly | QIODevice::Text) ) 
	{
		qDebug("no i18n ini file.\n");
		return;
	}
	QTranslator *translator = NULL;
	QTextStream text(&file);
	QString line ;
	while ( !text.atEnd() ) 
	{
		line = text.readLine().simplified();
		if( line.length() == 0 ) 
			continue;
		if( line.at(0) == '#' ) 
			continue;

		QString i18nName = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\\uif\\i18n\\" + lang + "\\";
		i18nName.append(line).append(QString("_%1.qm").arg(lang));
		translator = new QTranslator( 0 );
		if (!translator->load( i18nName ))
		{
			qDebug()<<"load translator file"<<line<<"failed!";
			continue;
		}
		qApp->installTranslator( translator );
		ui.retranslateUi(this);
	}
	file.close();
	delete []translator;
}

void MainForm::on_actionEnglish_triggered()
{
	chaneLanguage("en");
}

void MainForm::on_actionChinese_triggered()
{
	chaneLanguage("zh");
}