/***********************************************
**  �ļ���:     stdparaset.cpp
**  ����:       ��׼������趨
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2015/3/5
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2015/03 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:
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
