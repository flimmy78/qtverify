/***********************************************
**  文件名:     main.cpp
**  功能:       采集与控制测试-主程序
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/12
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/06 第一版
**  内容包含:
**  说明:
**  更新记录:
***********************************************/

#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QTextCodec>

#include "qtexdb.h"
#include "logger.h"
#include "datatestdlg.h"

int main( int argc, char ** argv )
{
	QApplication app( argc, argv );
	QString lang = "zh";//默认显示中文
	if (argc == 2)
	{
		lang = QString::fromAscii(argv[1]);
	}

	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("GB2312"));

	//注册MessageHandler
	qInstallMsgHandler(myMessageOutput);

	QTranslator translator(0);
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");
	if (!runhome.isEmpty()) 
	{
		QString filename = runhome + "\\uif\\i18n\\" + lang + "\\datatestdlg_" + lang + ".qm";
		bool loadok = translator.load(filename, "");
		if (!loadok)
		{
			qDebug()<<"load translator file \""<<filename<<"\" failed!";
		}
		app.installTranslator(&translator);
	}
	qDebug()<<"datatest main thread:"<<QThread::currentThreadId();
// 	qApp->setStyleSheet("QLineEdit { background-color: yellow }");
	startdb();

	DataTestDlg w;
	w.show();
	app.exec();

	closedb();
	return 0;
}