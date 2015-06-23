#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include <QtCore/QDebug>
#include <QtGui/QSplashScreen>
#include <QtTest/QTest>
#include <QtCore/QThread>
#include <QtGui/QDesktopWidget>

#include "mainform.h"
#include "logger.h"
#include "logindialog.h"
#include "qtexdb.h"
#include "algorithm.h"
#include "md5encode.h"
#include "register.h"

MainForm *g_mainform;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	//判断是否授权用户
	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
	QFile license(adehome + "\\bin\\license");
	license.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&license);
	QString code = in.readLine();
	license.close();
	if (!isLicenseOK(code))
	{
		RegisterDlg *reg = new RegisterDlg(qGetVolumeInfo());
		reg->show();
		qDebug()<<"please register first";
		return app.exec();
	}

	//加载样式表
	QFile qss(":/qtverify/qss/default.qss");
	qss.open(QFile::ReadOnly);
	app.setStyleSheet(qss.readAll());
	qss.close();

	QSplashScreen *splash = new QSplashScreen;
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

	//加载翻译文件
	QString lang = "zh"; //默认显示中文
	if (argc == 2) 
	{
		lang = QString::fromLocal8Bit(argv[1]);
	}
	QString file_name = getFullIniFileName("tr_qtverify.ini");
	QFile file(file_name );
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) ) 
	{
		QTranslator *translator = NULL;
		QTextStream text(&file);
		QString line ;
		while ( !text.atEnd() ) 
		{
			line = text.readLine().simplified();
			if ( line.isEmpty() || line.startsWith("#") ) 
			{
				continue;
			}
			QString i18nName = adehome + "\\uif\\i18n\\" + lang + "\\";
			line = line + "_" + lang + ".qm";
			i18nName.append(line);//.append(QString("_%1.qm").arg(lang));
			translator = new QTranslator( 0 );
			if (!translator->load( i18nName ))
			{
				qDebug()<<"load translator file"<<line<<"failed!";
			}
			app.installTranslator( translator );
		}
		file.close();

		splash->showMessage(QObject::tr("load translator files ..."), align, Qt::blue);
		QTest::qSleep(200);
	}
	else
	{
		splash->showMessage(QObject::tr("no translator files ..."), align, Qt::blue);
		QTest::qSleep(200);
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
		g_mainform->resize(1280, 800);  
		g_mainform->move((app.desktop()->width()-g_mainform->width())/2, (app.desktop()->height()-g_mainform->height())/2);  
		g_mainform->show();
		splash->finish(g_mainform);
		delete splash;
		app.exec();
// 	}

	closedb();
	return 0;
}
