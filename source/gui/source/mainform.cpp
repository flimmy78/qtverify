#include <QtGui/QMessageBox>
#include <QAxObject>
#include <QProcess>

#include "mainform.h"

MainForm::MainForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.btnExit->setFlat(true);

	m_algobj = new alg();
 	spobj = new SerialPortSet();
	dbmysqlobj = new DbMySql();
	dbsqliteobj = new DbSqlite();

	connect(ui.btnExit, SIGNAL(clicked()), this, SLOT(close()));
	
}

MainForm::~MainForm()
{

}

void MainForm::on_action_spset_triggered()
{
//  QMessageBox::warning(this, "title", "you clicked");	
	spobj->show();
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
	m_algobj->calc(2.0, 5.6);
}

void MainForm::on_action_queryExcel_triggered()
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
	spobj->sp_anyfunc();
}

void MainForm::on_btnPara_clicked()
{
	QProcess *myProcess = new QProcess(this);
	QStringList cmdlist;
	cmdlist<<"/v:"<<"192.168.1.132"<<"/console";
	myProcess->start("mstsc", cmdlist);
}
