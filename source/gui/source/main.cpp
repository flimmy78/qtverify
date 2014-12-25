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

	QSplashScreen *splash = new QSplashScreen;
	QString startPic = QProcessEnvironment::systemEnvironment().value("RUNHOME") + "/uif/pixmap/facility.png";;
	splash->setPixmap(QPixmap(startPic));
	splash->show();

	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("GB2312"));

	//ע��MessageHandler
	qInstallMsgHandler(myMessageOutput);

	//��ӡ��־���ļ���
// 	qDebug()<<"This is a debug message";
// 	qWarning()<<"This is a warning message";
// 	qCritical()<<"This is a critical message";
// 	qFatal("file< %s >, line< %d >, This is a fatal message", __FILE__, __LINE__);
// 	qFatal("This is a fatal message");
	
	Qt::Alignment align = Qt::AlignCenter | Qt::AlignBottom;
	splash->showMessage(QObject::tr("load translator files ..."), align, Qt::blue);
	QTest::qSleep(500);

	char filename[100];
	sprintf_s( filename, "%s/uif/i18n/qtverify_zh.qm", getenv("RUNHOME"));
	QTranslator *translator;
	translator = new QTranslator();
	bool loadok = translator->load( filename );
	if (!loadok)
	{
		 printf_s(" load translator file \"%s\" failed! \n", filename);
	}
	app.installTranslator( translator );
	qDebug()<<"qtverify main thread:"<<QThread::currentThreadId();

	splash->showMessage(QObject::tr("connect database ..."), align, Qt::blue);
	QTest::qSleep(500);
	startdb(); //�������ݿ�

	splash->showMessage(QObject::tr("setting up the mainwindow ..."), align, Qt::blue);
	QTest::qSleep(500);
	g_mainform = new MainForm;

// 	LoginDialog login;
// 	if (login.exec() == QDialog::Accepted)
// 	{
		g_mainform->show();//showMaximized();
		splash->finish(g_mainform);
		delete splash;
		app.exec();
//	}

	closedb();
	return 0;
}
