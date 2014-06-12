#include "mainform.h"
#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include <QDebug>

MainForm *g_mainform;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("GB2312"));

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
	qDebug()<<"main thread:"<<QThread::currentThreadId();

	g_mainform = new MainForm;
	g_mainform->showMaximized();

	return app.exec();
}
