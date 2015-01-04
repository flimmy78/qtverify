/***********************************************
**  �ļ���:     main.cpp
**  ����:       �ɼ�����Ʋ���-������
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

#include "datatestdlg.h"
#include "logger.h"

int main( int argc, char ** argv )
{
	QApplication app( argc, argv );

	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("GB2312"));

	//ע��MessageHandler
	qInstallMsgHandler(myMessageOutput);

	QTranslator translator(0);
	char *path = getenv("RUNHOME");
	if (NULL != path) 
	{
		char filename[100];
		memset( filename, 0, sizeof(char)*100 );
		sprintf( filename, "%s\\uif\\i18n\\zh\\datatestdlg_zh.qm", path );
		bool loadok = translator.load(filename, "");
		if (!loadok)
		{
			qDebug()<<"load translator file \""<<filename<<"\" failed!";
		}
		app.installTranslator(&translator);
	}
	qDebug()<<"datatest main thread:"<<QThread::currentThreadId();
// 	qApp->setStyleSheet("QLineEdit { background-color: yellow }");
	startdb();

	DataTestDlg w;
	w.show();
	app.exec();

	closedb();
	return 0;
}