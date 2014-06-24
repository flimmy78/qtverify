#include <QtGui/QApplication>
#include <QtCore/QTranslator>

#include "SetComFrm.h"
#include "ReadComConfig.h"
#include "comsetdlg.h"
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

	SetComFrm w;
	w.show();
	ReadComConfig r;
	ComInfoStruct cominfo=r.ReadValveConfig();

	try
	{
		qDebug() << cominfo.portName;
		qDebug() << cominfo.baudRate;
		qDebug() << cominfo.dataBit;
		qDebug() << cominfo.parity;
		qDebug() << cominfo.stopBit;
		qDebug() << "\/";
		QString aa = "sadfd";
		qDebug() << aa.toInt();
	}
	catch (QString e)
	{
		qDebug() << e;
	}

	return app.exec();
}