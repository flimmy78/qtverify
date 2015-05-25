#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QSettings>
#include <QtCore/QPoint>

#include "setportfrm.h"
#include "setcomfrm.h"

int main( int argc, char ** argv )
{
	QApplication app( argc, argv );
	QString lang = "zh";//Ĭ����ʾ����
	if (argc == 2)
	{
		lang = QString::fromAscii(argv[1]);
	}
	QTranslator translator(0);
	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
	if (!adehome.isEmpty()) 
	{
		QString filename;
		filename = adehome + "\\uif\\i18n\\" + lang + "\\comsetdlg_" + lang + ".qm";
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