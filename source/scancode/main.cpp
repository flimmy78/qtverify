/***********************************************
**  �ļ���:     main.cpp
**  ����:       ɨ��д���-������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2015/9/8
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2015/09 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:
***********************************************/

#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QTextCodec>
#include <QtCore/QProcess>

#include "scancodedlg.h"
#include "qtexdb.h"

int main( int argc, char ** argv )
{
	QApplication app( argc, argv );
	QString lang = "zh";//Ĭ����ʾ����
	if (argc == 2)
	{
		lang = QString::fromAscii(argv[1]);
	}

	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("GB2312"));

	QTranslator translator(0);
	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
	if (!adehome.isEmpty()) 
	{
		QString filename = adehome + "\\uif\\i18n\\" + lang + "\\scancodedlg_" + lang + ".qm";
		bool loadok = translator.load(filename, "");
		if (!loadok)
		{
			qDebug()<<"load translator file \""<<filename<<"\" failed!";
		}
		app.installTranslator(&translator);
	}
	qDebug()<<"scancode main thread:"<<QThread::currentThreadId();
	startdb();
	
	ScanCodeDlg w;
	w.show();
	app.exec();

	closedb();
	return 0;
}