/***********************************************
**  �ļ���:     cmbverify.cpp
**  ����:       ��ϼ춨������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2015/5/6
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2015/05 ��һ��
**  ���ݰ���:
**  ˵��:		
**  ���¼�¼:   
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QTest>
#include <QtSql/QSqlTableModel>
#include <QtGui/QFileDialog>
#include <QtCore/QSignalMapper>
#include <math.h>

#include "cmbverify.h"

CmbVerifyDlg::CmbVerifyDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
}

CmbVerifyDlg::~CmbVerifyDlg()
{
}

void CmbVerifyDlg::showEvent(QShowEvent *)
{
	m_CmbParamDlg = NULL;
	m_param_config = new QSettings(getFullIniFileName("cmbparam.ini"), QSettings::IniFormat);
	m_algo = new CAlgorithm;
}

void CmbVerifyDlg::closeEvent( QCloseEvent * event)
{
	if(NULL != m_CmbParamDlg)
	{
		delete m_CmbParamDlg;
		m_CmbParamDlg = NULL;
	}

	if (NULL != m_param_config)
	{
		delete m_param_config;
		m_param_config = NULL;
	}

	if (NULL != m_algo)
	{
		delete m_algo;
		m_algo = NULL;
	}
}

void CmbVerifyDlg::on_btnPara_clicked()
{
	if (NULL == m_CmbParamDlg)
	{
		m_CmbParamDlg = new CmbParamDlg();
	}
	else
	{
		delete m_CmbParamDlg;
		m_CmbParamDlg = new CmbParamDlg();
	}
	connect(m_CmbParamDlg, SIGNAL(saveSuccessfully()), this, SLOT(freshCmbParam()));
	m_CmbParamDlg->show();
}

void CmbVerifyDlg::freshCmbParam(void)
{

}

void CmbVerifyDlg::on_btnExit_clicked()
{
	this->close();
}
