#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QSettings>
#include <QtCore/QPoint>

#include "SetPortFrm.h"
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
	//try
	//{
		//ReadComConfig r;
		//ComInfoStruct cominfo=r.ReadValeConfig();

		//qDebug() << cominfo.portName;
		//qDebug() << cominfo.baudRate;
		//qDebug() << cominfo.dataBit;
		//qDebug() << cominfo.parity;
		//qDebug() << cominfo.stopBit;
		//qDebug() << "\/";
		//QString aa = "sadfd";
		//qDebug() << aa.toInt();
	//}
	//catch (QString e)
	//{
	//	qDebug() << e;
	//}
	SetPortFrm w;
	w.show();
	//QSettings *ConfigIni = new QSettings("./QtPad.ini", QSettings::IniFormat);

	//QString pth = ConfigIni->fileName();
	//ConfigIni->setValue("pnt/point", "fuck");
	//ConfigIni->setValue("com/com1/com2", QPoint(100, 40));
	//delete ConfigIni;
	 
	return app.exec();
}