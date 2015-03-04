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
#include "dbmysql.h"
#include "flowresult.h"
#include "setcomfrm.h"
#include "datatestdlg.h"
#include "setportfrm.h"
#include "masterslaveset.h"
#include "algorithm.h"
#include "flowweight.h"
#include "flowstandard.h"
#include "totalweight.h"
#include "totalstandard.h"
#include "calcverify.h"

MainForm::MainForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	qDebug()<<"MainForm thread:"<<QThread::currentThreadId();

	ui.setupUi(this);

	m_mySql = NULL;
	m_flowResultDlg = NULL;
	m_alg = new CAlgorithm();

	m_setcom = NULL;
	m_datatestdlg = NULL;
	m_portSet = NULL;
	m_masterslave = NULL;
	m_comProcess = new QProcess(this);
	m_flowWeightDlg = NULL;
	m_flowStandardDlg = NULL;
	m_totalWeightDlg = NULL;
	m_totalStandardDlg = NULL;
	m_calcDlg = NULL;

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

		if (m_flowResultDlg)
		{
			delete m_flowResultDlg;
			m_flowResultDlg = NULL;
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

		if (m_comProcess)
		{
			m_comProcess->kill();
		}

		if (m_flowWeightDlg)
		{
			delete m_flowWeightDlg;
			m_flowWeightDlg = NULL;
		}

		if (m_flowStandardDlg)
		{
			delete m_flowStandardDlg;
			m_flowStandardDlg = NULL;
		}

		if (m_totalWeightDlg)
		{
			delete m_totalWeightDlg;
			m_totalWeightDlg = NULL;
		}

		if (m_totalStandardDlg)
		{
			delete m_totalStandardDlg;
			m_totalStandardDlg = NULL;
		}

		if (m_calcDlg)
		{
			delete m_calcDlg;
			m_calcDlg = NULL;
		}
	}
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

//采集与控制测试程序
void MainForm::on_actionDataTest_triggered()
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

//调用串口调试工具
void MainForm::on_actionComDebuger_triggered()
{
	QStringList cmdlist;
	cmdlist<<"-zh";
	m_comProcess->start("qcom", cmdlist);
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

void MainForm::on_actionMySql_triggered()
{
	if (NULL == m_mySql)
	{
		m_mySql = new DbMySql();
	}
	m_mySql->show();
}


//流量检定(质量法)
void MainForm::on_actionFlowWeight_triggered()
{
	if (NULL == m_flowWeightDlg)
	{
		m_flowWeightDlg = new FlowWeightDlg();
	}
	else //目的是执行FlowWeightDlg的构造函数
	{
		delete m_flowWeightDlg;
		m_flowWeightDlg = NULL;
		m_flowWeightDlg = new FlowWeightDlg();
	}
	m_flowWeightDlg->show();
}

//流量检定(标准表法)
void MainForm::on_actionFlowStandard_triggered()
{
	if (NULL == m_flowStandardDlg)
	{
		m_flowStandardDlg = new FlowStandardDlg();
	}
	else //目的是执行FlowStandardDlg的构造函数
	{
		delete m_flowStandardDlg;
		m_flowStandardDlg = NULL;
		m_flowStandardDlg = new FlowStandardDlg();
	}
	m_flowStandardDlg->show();
}

//温度检定(比较法)
void MainForm::on_actionTemperCompare_triggered()
{
}

//温度检定(参数法)
void MainForm::on_actionTemperPara_triggered()
{
}

//计算器检定
void MainForm::on_actionCalculator_triggered()
{
	if (NULL == m_calcDlg)
	{
		m_calcDlg = new CalcDlg();
	}
	else //目的是执行CalcDlg的构造函数
	{
		delete m_calcDlg;
		m_calcDlg = NULL;
		m_calcDlg = new CalcDlg();
	}
	m_calcDlg->show();
}

//温度/计算器组合检定
void MainForm::on_actionCombine_triggered()
{
}

//总量检定（质量法）
void MainForm::on_actionTotalWeight_triggered()
{
	if (NULL == m_totalWeightDlg)
	{
		m_totalWeightDlg = new TotalWeightDlg();
	}
	else //目的是执行TotalWeightDlg的构造函数
	{
		delete m_totalWeightDlg;
		m_totalWeightDlg = NULL;
		m_totalWeightDlg = new TotalWeightDlg();
	}
	m_totalWeightDlg->show();
}

//总量检定（标准表法）
void MainForm::on_actionTotalStandard_triggered()
{
	if (NULL == m_totalStandardDlg)
	{
		m_totalStandardDlg = new TotalStandardDlg();
	}
	else //目的是执行TotalStandardDlg的构造函数
	{
		delete m_totalStandardDlg;
		m_totalStandardDlg = NULL;
		m_totalStandardDlg = new TotalStandardDlg();
	}
	m_totalStandardDlg->show();
}

//查询流量检定结果（包括质量法和标准表法）
void MainForm::on_actionFlowResult_triggered()
{
	if (NULL == m_flowResultDlg)
	{
		m_flowResultDlg = new FlowResultDlg();
	}
	else
	{
		delete m_flowResultDlg;
		m_flowResultDlg = new FlowResultDlg();
	}
	m_flowResultDlg->show();
}

//查询总量检定结果（包括质量法和标准表法）
void MainForm::on_actionTotalResult_triggered()
{
}

//查询温度传感器检定结果
void MainForm::on_actionTemperResult_triggered()
{
}

//查询计算器检定结果
void MainForm::on_actionCalculatorResult_triggered()
{
}

//查询温度/计算器组合检定结果
void MainForm::on_actionCombineResult_triggered()
{
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

//退出
void MainForm::on_actionExit_triggered()
{
	this->close();
}

void MainForm::on_actionAbout_triggered()
{
	QMessageBox::aboutQt(this);
}

//显示风格
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
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");
	QString file_name = runhome + "\\ini\\tr_qtverify.ini";
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
		line = line + "_" + lang + ".qm";
		i18nName.append(line);//.append(QString("_%1.qm").arg(lang));
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