#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <windows.h>
#include "comsetdlg.h"
#include "SetComFrm.h"

int main( int argc, char ** argv )
{
	QApplication app( argc, argv );

	/*QTranslator translator(0);
	char *path = getenv("RUNHOME");
	if (NULL != path) 
	{
	char filename[100];
	memset( filename, 0, sizeof(char)*100 );
	sprintf( filename, "%s/uif/i18n/comsetdlg_zh.qm", path );
	bool loadok = translator.load(filename, "");
	if (!loadok)
	{
	printf(" load translator file: %s failed! \n", filename);
	}
	app.installTranslator(&translator);
	}*/

	//ComSetDlg wg;
	SetComFrm w;
	w.show();

	return app.exec();
}