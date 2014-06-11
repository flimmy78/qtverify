#include <QtGui/QApplication>
#include <QtCore/QTranslator>

#include "serialportset.h"


int main( int argc, char ** argv )
{
	QApplication app( argc, argv );

	QTranslator translator(0);
	char *path = getenv("RUNHOME");
	if (NULL != path) 
	{
		char filename[64];
		memset( filename, 0, sizeof(char)*64 );
		sprintf( filename, "%s/uif/i18n/qtcomdlg_zh.qm", path );
		bool loadok = translator.load(filename, "");
		if (!loadok)
		{
			printf(" load translator file: %s failed! \n", filename);
		}
		app.installTranslator(&translator);
	}

	SerialPortSet w;
	w.show();

	return app.exec();
}