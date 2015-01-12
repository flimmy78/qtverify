#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include <QtCore/QDebug>
#include <QtGui/QSplashScreen>
#include <QtTest/QTest>

#include "mainform.h"
#include "logger.h"
#include "logindialog.h"

MainForm *g_mainform;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QFile qss(":/qtverify/qss/default.qss");
	qss.open(QFile::ReadOnly);
	app.setStyleSheet(qss.readAll());
	qss.close();

	QSplashScreen *splash = new QSplashScreen;
// 	QString startPic = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "\\uif\\pixmap\\facility.png";;
	splash->setPixmap(QPixmap(":/qtverify/images/facility.png"));
	splash->show();

	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("GB2312"));

	//注册MessageHandler
	qInstallMsgHandler(myMessageOutput);

	//打印日志到文件中
// 	qDebug()<<"This is a debug message";
// 	qWarning()<<"This is a warning message";
// 	qCritical()<<"This is a critical message";
// 	qFatal("file< %s >, line< %d >, This is a fatal message", __FILE__, __LINE__);
// 	qFatal("This is a fatal message");
	
	Qt::Alignment align = Qt::AlignCenter | Qt::AlignBottom;
	splash->showMessage(QObject::tr("load translator files ..."), align, Qt::blue);
	QTest::qSleep(200);

	QString lang = "zh"; //默认显示中文
	if (argc == 2)
	{
		lang = QString::fromLocal8Bit(argv[1]);
	}
	char file_name[100];
	sprintf_s( file_name, "%s\\ini\\tr_qtverify.ini", getenv("RUNHOME"));
	QFile file(file_name );
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) ) 
	{
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
			i18nName.append(line).append(QString("_%1.qm").arg(lang));
			translator = new QTranslator( 0 );
			if (!translator->load( i18nName ))
			{
				qDebug()<<"load translator file"<<line<<"failed!";
			}
			app.installTranslator( translator );
		}
		file.close();
	}
	else
	{
		qDebug("no i18n ini file.\n");
	}

	qDebug()<<"qtverify main thread:"<<QThread::currentThreadId();

	splash->showMessage(QObject::tr("connect database ..."), align, Qt::blue);
	QTest::qSleep(200);
	startdb(); //连接数据库

	splash->showMessage(QObject::tr("setting up the mainwindow ..."), align, Qt::blue);
	QTest::qSleep(200);
	g_mainform = new MainForm;

// 	LoginDialog login;
// 	if (login.exec() == QDialog::Accepted)
// 	{
		g_mainform->showMaximized();
		splash->finish(g_mainform);
		delete splash;
		app.exec();
// 	}

	closedb();
	return 0;
}
