/***********************************************
**  �ļ���:     parasetdlg.cpp
**  ����:       ������-�����춨-�������ý���
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/12
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QThread>
#include <QtCore/QSettings>

#include "parasetdlg.h"
#include "commondefine.h"

ParaSetDlg::ParaSetDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"ParaSetDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	m_basedb.startdb();

	m_meterStdNum = 0;
	m_meterStdPtr = NULL;

	m_meterTypeNum = 0;
	m_meterTypePtr = NULL;

	m_manuFacNum = 0;
	m_manuFacPtr = NULL;

	initUiData();

//	this->setStyleSheet("QLineEdit { background-color: yellow }");

// 	ui.lnEdit_Flow1->setStyleSheet("color: red;"
// 		"background-color: yellow;"
// 		"selection-color: greed;"
// 		"selection-background-color: blue;");

	ui.lnEdit_Flow1->setStyleSheet("border: 2px solid gray;"
		"border-radius: 10px;"
		"padding: 0 8px;"
		"background: yellow;"
		"selection-background-color:darkgray;");
}

ParaSetDlg::~ParaSetDlg()
{
	qDebug()<<"!!! ParaSetDlg destructor";
}

void ParaSetDlg::closeEvent(QCloseEvent * event)
{
	qDebug()<<"&&& ParaSetDlg closeEvent";

	if (m_meterStdPtr)
	{
		delete []m_meterStdPtr;
		m_meterStdPtr = NULL;
	}

	if (m_meterTypePtr)
	{
		delete []m_meterTypePtr;
		m_meterTypePtr = NULL;
	}

	if (m_manuFacPtr)
	{
		delete []m_manuFacPtr;
		m_manuFacPtr = NULL;
	}

	m_basedb.closedb();
}

void ParaSetDlg::on_btnSave_clicked()
{
	testFunc(10, 20);
	char filename[255];
	char* runhome = getenv( "RUNHOME" );
#ifdef __unix
	sprintf( filename, "%s/ini/qualityParaSet.ini", runhome );
#else
	sprintf( filename, "%s\\ini\\qualityParaSet.ini", runhome );
#endif

	QSettings settings(filename, QSettings::IniFormat);
	settings.setIniCodec("GB2312"); //�����ini�ļ���д��������
	settings.beginGroup("paraset");
	settings.setValue("standard", ui.cmbStandard->currentText());
	settings.setValue("metertype", ui.cmbCollectCode->currentText());
	settings.setValue("manufacture", ui.cmbManufacture->currentText());
	settings.setValue("grade", (ui.cmbGrade->currentIndex()+1));
	settings.endGroup();
}

void ParaSetDlg::on_btnExit_clicked()
{
	this->close();
}

void ParaSetDlg::initUiData()
{
	//����
	m_basedb.getMeterStandard(m_meterStdNum, m_meterStdPtr);
	for (int i=0; i<m_meterStdNum; i++)
	{
		qDebug()<<"id:"<<m_meterStdPtr[i].id<<",name:"<<m_meterStdPtr[i].name;
		ui.cmbStandard->insertItem(i, m_meterStdPtr[i].name);
	}

	//������
	m_basedb.getMeterType(m_meterTypeNum, m_meterTypePtr);
	for (int j=0; j<m_meterTypeNum; j++)
	{
		qDebug()<<"id:"<<m_meterTypePtr[j].id<<",desc:"<<QString::fromLocal8Bit(m_meterTypePtr[j].desc);
		ui.cmbCollectCode->insertItem(j, QString::fromLocal8Bit(m_meterTypePtr[j].desc)); //���ֱ���
	}	

	//���쵥λ
	m_basedb.getManufacture(m_manuFacNum, m_manuFacPtr);
	for (int m=0; m<m_manuFacNum; m++)
	{
		qDebug()<<"id:"<<m_manuFacPtr[m].id<<",desc:"<<QString::fromLocal8Bit(m_manuFacPtr[m].desc);
		ui.cmbManufacture->insertItem(m, QString::fromLocal8Bit(m_manuFacPtr[m].desc)); //���ֱ���
	}	


}