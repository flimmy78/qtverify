/***********************************************
**  文件名:     weightmethod.cpp
**  功能:       质量法检定主界面
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/7/15
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/07 第一版
**  内容包含:
**  说明:		
**  更新记录:   
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QThread>

#include "weightmethod.h"
#include "commondefine.h"

WeightMethodDlg::WeightMethodDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"WeightMethodDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	ui.tabWidget->setTabsClosable(true);
	connect(ui.tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));

	ui.lcdNumberInTemper->display("27.8");
	QString inTemper = QString("%1").arg(ui.lcdNumberInTemper->value(), 4);
	float iii = inTemper.toFloat();

/*	for (int i=0; i<4; i++)
	{
		ui.tabWidget->removeTab(1);
	}*/
}

WeightMethodDlg::~WeightMethodDlg()
{
}

void WeightMethodDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^WeightMethodDlg::closeEvent";

}

//关闭标签页
void WeightMethodDlg::removeSubTab(int index) 
{ 
	ui.tabWidget->removeTab(index); 
} 