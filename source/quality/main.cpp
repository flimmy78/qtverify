#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QThread>
#include <QtCore/QDebug>

#include "qualitydlg.h"

QualityDlg *g_qualitydlg;

int main( int argc, char ** argv )
{
	QApplication app( argc, argv );

	QTranslator translator(0);
	char *path = getenv("RUNHOME");
	if (NULL != path) 
	{
		char filename[100];
		memset( filename, 0, sizeof(char)*100 );
		sprintf( filename, "%s/uif/i18n/qualitydlg_zh.qm", path );
		bool loadok = translator.load(filename, "");
		if (!loadok)
		{
			printf(" load translator file: %s failed! \n", filename);
		}
		app.installTranslator(&translator);
	}
	qDebug()<<"quality main thread:"<<QThread::currentThreadId();

	g_qualitydlg = new QualityDlg();
	g_qualitydlg->showMaximized();

	return app.exec();
}