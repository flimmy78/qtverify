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
	m_alg = new CAlg();
	m_comset = new ComSetDlg();
	m_qualitydlg = new QualityDlg();

	connect(ui.btnExit, SIGNAL(clicked()), this, SLOT(close()));

}

MainForm::~MainForm()
{
	if (m_alg)
	{
		delete m_alg;
		m_alg = NULL;
	}

	if (m_comset)
	{
		delete m_comset;
		m_comset = NULL;
	}

	if (m_qualitydlg)
	{
		delete m_qualitydlg;
		m_qualitydlg = NULL;
	}
}

void MainForm::on_action_spset_triggered()
{
//  QMessageBox::warning(this, "title", "you clicked");	
	m_comset->show();
}

void MainForm::on_action_mysql_triggered()
{
	dbmysqlobj->show();
}

void MainForm::on_action_sqlite_triggered()
{
	dbsqliteobj->show();
}

void MainForm::on_btnStart_clicked()
{
	m_alg->calc(2.0, 5.6);
}

void MainForm::on_action_queryExcel_triggered()
{
	QAxObject *excel = NULL;
	QAxObject *workbooks = NULL;
	QAxObject *workbook = NULL;
	excel = new QAxObject("Excel.Application");
	if (!excel)
	{ 
		QMessageBox::critical(this, "������Ϣ", "EXCEL����ʧ");
		return;
	}
	excel->dynamicCall("SetVisible(bool)", false);
	workbooks = excel->querySubObject("WorkBooks");
	workbook = workbooks->querySubObject("Open(QString, QVariant)", QString(tr("d:\\test.xlsx")));
	QAxObject * worksheet = workbook->querySubObject("WorkSheets(int)", 1);//�򿪵�һ��sheet
	QAxObject * usedrange = worksheet->querySubObject("UsedRange");//��ȡ��sheet��ʹ�÷�Χ����
	QAxObject * rows = usedrange->querySubObject("Rows");
	QAxObject * columns = usedrange->querySubObject("Columns");
	int intRowStart = usedrange->property("Row").toInt();
	int intColStart = usedrange->property("Column").toInt();
	int intCols = columns->property("Count").toInt();
	int intRows = rows->property("Count").toInt();

	for (int i = intRowStart; i < intRowStart + intRows; i++) //�� 
	{
		for (int j = intColStart; j < intColStart + intCols; j++) //�� 
		{
			QAxObject * range = worksheet->querySubObject("Cells(int,int)", i, j ); //��ȡ��Ԫ��  
			qDebug("row %d, col %d, value is %d\n", i, j, range->property("Value").toInt()); //************������!!!!!! 
		} 
	}
}

void MainForm::on_btnSave_clicked()
{
	m_comset->sp_anyfunc();
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
	myProcess->start("comset.exe");
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

void MainForm::on_actionQualityComp_triggered()
{
	m_qualitydlg->showMaximized();
}

void MainForm::on_actionQualityTotal_triggered()
{
	int count = m_comset->myCom->bytesAvailable();
	QByteArray temp = m_comset->myCom->readAll();
	if (!temp.isEmpty())
	{
		int number = temp.size();
		for (int i=0; i<number; i++)
		{
			printf_s("i=%d, data=%02c\n", i, (UINT8)temp.at(i));
		}
	}
}

