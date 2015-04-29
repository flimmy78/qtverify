/***********************************************
**  文件名:     cmbverify.cpp
**  功能:       组合检定主界面
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/5/6
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2015/05 第一版
**  内容包含:
**  说明:		
**  更新记录:   
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
