/***********************************************
**  �ļ���:     main.cpp
**  ����:       ��������-������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/12
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:
***********************************************/

#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QTextCodec>

#include "qtexdb.h"
#include "logger.h"
#include "adjustratedlg.h"

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

	//ע��MessageHandler
	qInstallMsgHandler(myMessageOutput);

	QTranslator translator(0);
	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
	if (!adehome.isEmpty()) 
	{
		QString filename = adehome + "\\uif\\i18n\\" + lang + "\\adjustratedlg_" + lang + ".qm";
		bool loadok = translator.load(filename, "");
		if (!loadok)
		{
			qDebug()<<"load translator file \""<<filename<<"\" failed!";
		}
		app.installTranslator(&translator);
	}
	qDebug()<<"adjustratedlg main thread:"<<QThread::currentThreadId();
	startdb();
	AdjustRateDlg w;
	w.show();
	app.exec();
	closedb();
	return 0;
}