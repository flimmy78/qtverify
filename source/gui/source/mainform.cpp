#include <QtGui/QMessageBox>
#include <QAxObject>

#include "mainform.h"

qtVerify::qtVerify(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.pushButton_Exit->setFlat(true);

	m_algobj = new alg();
 	spobj = new SerialPortSet();
	dbshowobj = new DbShow();

//  connect(ui.pushButton_Exit, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.pushButton_Save, SIGNAL(clicked()), this, SLOT(on_pushButton_Save_clicked()));
	connect(ui.pushButton_Start, SIGNAL(clicked()), this, SLOT(slotCalc()));
	connect(ui.action_spset, SIGNAL(triggered()), this, SLOT(slotSerialPortSet()));
	connect(ui.action_database, SIGNAL(triggered()), this, SLOT(slotDBShow()));
	connect(ui.action_dataquery, SIGNAL(triggered()), this, SLOT(slotDataQuery()));
	
}

qtVerify::~qtVerify()
{

}

void qtVerify::slotSerialPortSet()
{
//  QMessageBox::warning(this, "title", "you clicked");	
	spobj->show();
}

void qtVerify::slotDBShow()
{
	dbshowobj->show();
}

void qtVerify::slotCalc()
{
	m_algobj->calc(2.0, 5.6);
}

void qtVerify::slotDataQuery()
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

void qtVerify::on_pushButton_Save_clicked()
{
	spobj->anyfunc();
}
