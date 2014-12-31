/***********************************************
**  �ļ���:     mainform.cpp
**  ����:       �춨̨��λ����������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/12
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:		ֻ�����DN15~DN25��С̨��
**  ���¼�¼:   
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

}

void MainForm::on_actionComDebuger_triggered()
{
	QProcess *myProcess = new QProcess(this);
	QStringList cmdlist;
	cmdlist<<"zh";
	myProcess->start("qcom", cmdlist);
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

void MainForm::on_actionQuery_triggered()
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

void MainForm::on_btnStart_clicked()
{
	m_alg->calc(2.0, 5.6);
}

void MainForm::on_actionQueryExcel_triggered()
{
	QAxObject *excel = NULL;
	excel = new QAxObject("Excel.Application");
	if (!excel)
	{ 
		QMessageBox::critical(this, "������Ϣ", "EXCEL����ʧ");
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
	int a = ui.comSetWidget->getLcdNumber();
	QString comname = ui.comSetWidget->ui.comboBox1->currentText();
	QMessageBox::information(this, "hint", QString("lcdnumber=%1, com=%2").arg(a).arg(comname));
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

//������-�����춨
void MainForm::on_actionWeightComp_triggered()
{
	if (NULL == m_weightDlg)
	{
		m_weightDlg = new WeightMethodDlg();
	}
	else //Ŀ����ִ��WeightMethodDlg�Ĺ��캯��
	{
		delete m_weightDlg;
		m_weightDlg = NULL;
		m_weightDlg = new WeightMethodDlg();
	}
	m_weightDlg->show();
}

//������-�����춨
void MainForm::on_actionWeightTotal_triggered()
{
}

//����-�ӻ�����
void MainForm::on_actionMasterSlaveSet_triggered()
{
	if (NULL == m_masterslave)
	{
		m_masterslave = new CMasterSlave();
	}
	m_masterslave->show();
}

//�ɼ�����Ʋ��Գ���
void MainForm::on_actionTest_triggered()
{
	if (NULL == m_datatestdlg)
	{
		m_datatestdlg = new DataTestDlg();
	}
	else //Ŀ����ִ��QualityDlg�Ĺ��캯��
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

