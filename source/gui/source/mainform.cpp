#include <QtGui/QMessageBox>
#include <QAxObject>

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

//  connect(ui.btnExit, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.btnSave, SIGNAL(clicked()), this, SLOT(on_btnSave_clicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(on_btnStart_Clicked()));
	connect(ui.action_spset, SIGNAL(triggered()), this, SLOT(slotSerialPortSet()));
	connect(ui.action_mysql, SIGNAL(triggered()), this, SLOT(slotDBShow_MySql()));
	connect(ui.action_sqlite, SIGNAL(triggered()), this, SLOT(slotDBShow_Sqlite()));
	connect(ui.action_queryExcel, SIGNAL(triggered()), this, SLOT(slotQueryExcel()));
	
}

MainForm::~MainForm()
{

}

void MainForm::slotSerialPortSet()
{
//  QMessageBox::warning(this, "title", "you clicked");	
	spobj->show();
}

void MainForm::slotDBShow_MySql()
{
	dbmysqlobj->show();
}

void MainForm::slotDBShow_Sqlite()
{
	dbsqliteobj->show();
}

void MainForm::on_btnStart_Clicked()
{
	m_algobj->calc(2.0, 5.6);
}

void MainForm::slotQueryExcel()
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
	spobj->anyfunc();
}
