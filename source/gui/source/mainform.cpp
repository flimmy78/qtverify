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
#include "stdmtrparaset.h"
#include "stdmtrcoecorrect.h"
#include "tvercomp.h"

MainForm::MainForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	qDebug()<<"MainForm thread:"<<QThread::currentThreadId();

	ui.setupUi(this);
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");
	QString logofile = runhome.replace("\\", "/") + "\/uif\/pixmap\/adelogo.jpg";
	ui.label->setStyleSheet(QString::fromUtf8("border-image: url(%1);").arg(logofile));

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
	m_tvercompDlg = NULL;
	m_stdParaSet = NULL;
	m_stdCoeCorrect = NULL;

	QLabel *permanent = new QLabel(this);
	permanent->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	permanent->setText(tr("<a href=\"http://www.sdm.com.cn\">Yantai Aerospace Delu Energy-saving technology Co.,Ltd</a>"));
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

		if (m_tvercompDlg)
		{
			delete m_tvercompDlg;
			m_tvercompDlg = NULL;
		}	

		if (m_stdParaSet)
		{
			delete m_stdParaSet;
			m_stdParaSet = NULL;
		}

		if (m_stdCoeCorrect)
		{
			delete m_stdCoeCorrect;
			m_stdCoeCorrect = NULL;
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

//�ɼ�����Ʋ��Գ���
void MainForm::on_actionDataTest_triggered()
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

//���ô��ڵ��Թ���
void MainForm::on_actionComDebuger_triggered()
{
	QStringList cmdlist;
	cmdlist<<"-zh";
	m_comProcess->start("qcom", cmdlist);
}

//��׼������趨
void MainForm::on_actionStdMtrParaSet_triggered()
{
	if (NULL == m_stdParaSet)
	{
		m_stdParaSet = new StdMtrParaSet();
	}
	else //Ŀ����ִ��StdParaSet�Ĺ��캯��
	{
		delete m_stdParaSet;
		m_stdParaSet = NULL;
		m_stdParaSet = new StdMtrParaSet();
	}
	m_stdParaSet->show();
}

//��׼��ϵ������
void MainForm::on_actionStdMtrCoeCorrect_triggered()
{
	if (NULL == m_stdCoeCorrect)
	{
		m_stdCoeCorrect = new StdMtrCoeCorrect();
	}
	else //Ŀ����ִ��StdCoeCorrect�Ĺ��캯��
	{
		delete m_stdCoeCorrect;
		m_stdCoeCorrect = NULL;
		m_stdCoeCorrect = new StdMtrCoeCorrect();
	}
	m_stdCoeCorrect->show();
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

void MainForm::on_actionMySql_triggered()
{
	if (NULL == m_mySql)
	{
		m_mySql = new DbMySql();
	}
	m_mySql->show();
}


//�����춨(������)
void MainForm::on_actionFlowWeight_triggered()
{
	if (NULL == m_flowWeightDlg)
	{
		m_flowWeightDlg = new FlowWeightDlg();
	}
	else //Ŀ����ִ��FlowWeightDlg�Ĺ��캯��
	{
		delete m_flowWeightDlg;
		m_flowWeightDlg = NULL;
		m_flowWeightDlg = new FlowWeightDlg();
	}
	m_flowWeightDlg->show();
}

//�����춨(��׼��)
void MainForm::on_actionFlowStandard_triggered()
{
	if (NULL == m_flowStandardDlg)
	{
		m_flowStandardDlg = new FlowStandardDlg();
	}
	else //Ŀ����ִ��FlowStandardDlg�Ĺ��캯��
	{
		delete m_flowStandardDlg;
		m_flowStandardDlg = NULL;
		m_flowStandardDlg = new FlowStandardDlg();
	}
	m_flowStandardDlg->show();
}

//�¶ȼ춨(�ȽϷ�)
void MainForm::on_actionTemperCompare_triggered()
{
	if (NULL == m_tvercompDlg)
	{
		m_tvercompDlg = new tvercompDlg();
	}
	else //Ŀ����ִ��tvercompDlg�Ĺ��캯��
	{
		delete m_tvercompDlg;
		m_tvercompDlg = NULL;
		m_tvercompDlg = new tvercompDlg();
	}
	m_tvercompDlg->show();
}

//�¶ȼ춨(������)
void MainForm::on_actionTemperPara_triggered()
{
}

//�������춨
void MainForm::on_actionCalculator_triggered()
{
	if (NULL == m_calcDlg)
	{
		m_calcDlg = new CalcDlg();
	}
	else //Ŀ����ִ��CalcDlg�Ĺ��캯��
	{
		delete m_calcDlg;
		m_calcDlg = NULL;
		m_calcDlg = new CalcDlg();
	}
	m_calcDlg->show();
}

//�¶�/��������ϼ춨
void MainForm::on_actionCombine_triggered()
{
}

//�����춨����������
void MainForm::on_actionTotalWeight_triggered()
{
	if (NULL == m_totalWeightDlg)
	{
		m_totalWeightDlg = new TotalWeightDlg();
	}
	else //Ŀ����ִ��TotalWeightDlg�Ĺ��캯��
	{
		delete m_totalWeightDlg;
		m_totalWeightDlg = NULL;
		m_totalWeightDlg = new TotalWeightDlg();
	}
	m_totalWeightDlg->show();
}

//�����춨����׼����
void MainForm::on_actionTotalStandard_triggered()
{
	if (NULL == m_totalStandardDlg)
	{
		m_totalStandardDlg = new TotalStandardDlg();
	}
	else //Ŀ����ִ��TotalStandardDlg�Ĺ��캯��
	{
		delete m_totalStandardDlg;
		m_totalStandardDlg = NULL;
		m_totalStandardDlg = new TotalStandardDlg();
	}
	m_totalStandardDlg->show();
}

//��ѯ�����춨����������������ͱ�׼����
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

//��ѯ�����춨����������������ͱ�׼����
void MainForm::on_actionTotalResult_triggered()
{
}

//��ѯ�¶ȴ������춨���
void MainForm::on_actionTemperResult_triggered()
{
}

//��ѯ�������춨���
void MainForm::on_actionCalculatorResult_triggered()
{
}

//��ѯ�¶�/��������ϼ춨���
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

//�˳�
void MainForm::on_actionExit_triggered()
{
	this->close();
}

void MainForm::on_actionAbout_triggered()
{
	QMessageBox::aboutQt(this);
}

//��ʾ���
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