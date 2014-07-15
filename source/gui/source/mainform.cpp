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

	dbmysqlobj = new DbMySql();
	dbsqliteobj = new DbSqlite();
	m_alg = new CAlgorithm();

	m_comdebugger = NULL;
	m_setcom = NULL;
	m_qualitydlg = NULL;
	m_portSet = NULL;
	m_masterslave = NULL;
	m_weightDlg = NULL;

	QLabel *permanent = new QLabel(this);
	permanent->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	permanent->setText(tr("<a href=\"http://www.sdm.com.cn\">山东德鲁计量科技有限公司</a>"));
	permanent->setTextFormat(Qt::RichText);
	permanent->setOpenExternalLinks(true);
	ui.statusBar->addPermanentWidget(permanent);
}

MainForm::~MainForm()
{
}

void MainForm::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^MainForm::closeEvent";

	if (dbmysqlobj)
	{
		delete dbmysqlobj;
		dbmysqlobj = NULL;
	}

	if (dbsqliteobj)
	{
		delete dbsqliteobj;
		dbsqliteobj = NULL;
	}

	if (m_alg)
	{
		delete m_alg;
		m_alg = NULL;
	}

	if (m_comdebugger)
	{
		delete m_comdebugger;
		m_comdebugger = NULL;
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

	if (m_qualitydlg)
	{
		delete m_qualitydlg;
		m_qualitydlg = NULL;
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

}

void MainForm::on_actionComDebuger_triggered()
{
	if (NULL == m_comdebugger)
	{
		m_comdebugger = new ComSetDlg();
	}
	m_comdebugger->show();
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
	dbmysqlobj->show();
}

void MainForm::on_actionSqlite_triggered()
{
	dbsqliteobj->show();
}

void MainForm::on_actionExit_triggered()
{
	this->close();
}

void MainForm::on_btnStart_clicked()
{
	m_alg->calc(2.0, 5.6);
}

void MainForm::on_actionQueryExcel_triggered()
{
	QAxObject *excel = NULL;
	QAxObject *workbooks = NULL;
	QAxObject *workbook = NULL;
	excel = new QAxObject("Excel.Application");
	if (!excel)
	{ 
		QMessageBox::critical(this, "错误信息", "EXCEL对象丢失");
		return;
	}
	excel->dynamicCall("SetVisible(bool)", false);
	workbooks = excel->querySubObject("WorkBooks");
	workbook = workbooks->querySubObject("Open(QString, QVariant)", QString(tr("d:\\test.xlsx")));
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

void MainForm::on_btnSave_clicked()
{
}

void MainForm::on_btnPara_clicked()
{
	QProcess *myProcess = new QProcess(this);
	QStringList cmdlist;
	cmdlist<<"/v:"<<"192.168.1.132"<<"/console";
	myProcess->start("mstsc", cmdlist);
}

void MainForm::on_btnAirOut_clicked()
{
	QProcess *myProcess = new QProcess(this);
	myProcess->start("calc.exe");
}

void MainForm::on_btnExit_clicked()
{
	this->close();
}

void MainForm::on_actionPlugin_triggered()
{
	QDir pluginsDir("F:/mysoft/trunk/plugindemo/GameSystem/plugins");
	foreach (QString fileName, pluginsDir.entryList(QDir::Files)) 
	{
		QFileInfo pluginFileInfo(fileName);
		if (pluginFileInfo.completeSuffix() == "dll" || pluginFileInfo.completeSuffix() == "so") 
		{
			QPluginLoader *pluginLoader	= new QPluginLoader(pluginsDir.absoluteFilePath(fileName), this);
			QObject *pluginObject = pluginLoader->instance();
			if (pluginObject) 
			{
				m_monster = qobject_cast <MonsterInterface *>(pluginObject);
				qDebug() << m_monster->name();
			}
		}
	}
}

//质量法-分量检定
void MainForm::on_actionQualityComp_triggered()
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
void MainForm::on_actionQualityTotal_triggered()
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
	if (NULL == m_qualitydlg)
	{
		m_qualitydlg = new QualityDlg();
	}
	else //目的是执行QualityDlg的构造函数
	{
		delete m_qualitydlg;
		m_qualitydlg = NULL;
		m_qualitydlg = new QualityDlg();
	}
	m_qualitydlg->show();
}