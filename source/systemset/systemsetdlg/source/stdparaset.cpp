/***********************************************
**  文件名:     stdparaset.cpp
**  功能:       标准表参数设定
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/3/5
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2015/03 第一版
**  内容包含:
**  说明:
**  更新记录:
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QTextCodec>
#include <QThread>
#include <QtGui/QMessageBox>
#include <QtCore/QProcessEnvironment>

#include "stdparaset.h"

StdParaSet::StdParaSet(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"StdParaSet thread:"<<QThread::currentThreadId();
	ui.setupUi(this);
}

ParaSetDlg::~ParaSetDlg()
{
	qDebug()<<"!!! StdParaSet destructor";
}
