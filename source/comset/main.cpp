#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QSettings>
#include <QtCore/QPoint>

#include "setportfrm.h"
#include "setcomfrm.h"

int main( int argc, char ** argv )
{
	QApplication app( argc, argv );
	QString lang = "zh";//默认显示中文
	if (argc == 2)
	{
		lang = QString::fromAscii(argv[1]);
	}
	QTranslator translator(0);
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");
	if (!runhome.isEmpty()) 
	{
		QString filename;
		filename = runhome + "\\uif\\i18n\\" + lang + "\\comsetdlg_" + lang + ".qm";
		bool loadok = translator.load(filename, "");
		if (!loadok)
		{
			qDebug()<<"load translator file \""<<filename<<"\" failed!\n";
		}
		app.installTranslator(&translator);
	}
	SetComFrm w;
	w.show();
	 
	return app.exec();
}