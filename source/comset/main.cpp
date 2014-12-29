#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QSettings>
#include <QtCore/QPoint>

#include "setportfrm.h"
#include "setcomfrm.h"
#include "readcomconfig.h"

int main( int argc, char ** argv )
{
	QApplication app( argc, argv );

	QTranslator translator(0);
	char *path = getenv("RUNHOME");
	if (NULL != path) 
	{
		char filename[100];
		memset( filename, 0, sizeof(char)*100 );
		sprintf_s( filename, "%s\\uif\\i18n\\comsetdlg_zh.qm", path );
		bool loadok = translator.load(filename, "");
		if (!loadok)
		{
			printf_s(" load translator file \"%s\" failed! \n", filename);
		}
		app.installTranslator(&translator);
	}
	SetComFrm w;
	w.show();
	 
	return app.exec();
}