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

void CmbVerifyDlg::closeEvent( QCloseEvent * event)
{
}

void CmbVerifyDlg::on_btnPara_clicked()
{
// 	if (NULL == m_calcParaDlg)
// 	{
// 		m_calcParaDlg = new CalcParaDlg();
// 	}
// 	else
// 	{
// 		delete m_calcParaDlg;
// 		m_calcParaDlg = new CalcParaDlg();
// 	}
// 	connect(m_calcParaDlg, SIGNAL(saveSuccessSignal()), this, SLOT(freshCalcPara()));
// 	m_calcParaDlg->show();
}

void CmbVerifyDlg::on_btnExit_clicked()
{
	this->close();
}
