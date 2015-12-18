#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QTextCodec>
#include "pseudo.h"

int main( int argc, char ** argv )
{
	QApplication app( argc, argv );
	CPseudoDlg p;
	p.show();
	return app.exec();
}