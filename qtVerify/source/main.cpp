#include "qtverify.h"
#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("GB2312"));

	char filename[100];
	sprintf_s( filename, "%s/uif/i18n/qtVerify_zh.qm", getenv("RUNHOME"));
	QTranslator *translator;
	translator = new QTranslator();
	bool loadok = translator->load( filename );
	if (!loadok)
	{
		 printf(" load translator file \"%s\" failed! \n", filename);
	}
	app.installTranslator( translator );

	qtVerify w;
	w.show();
	
	return app.exec();
}
