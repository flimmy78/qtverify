#include <QtCore/QDebug>
#include <QString>
#include <QTextCodec>
#include <QTextStream>
#include <iostream>
#include <QFile>
#include <QProcessEnvironment>

#include "logger.h"

CLogger::CLogger()
{
	QString path = QProcessEnvironment::systemEnvironment().value("RUNHOME");
#ifdef Q_OS_LINUX
	logfile = path + "\/log\/log.txt";
#elif defined (Q_OS_WIN)
	logfile = path + "\\log\\log.txt";
#endif
}

CLogger::~CLogger()
{

}

bool CLogger::WriteLn(const char * log_line)
{
	QFile log(logfile);

	if(!log.open(QIODevice::WriteOnly | QIODevice::Append))
	{
		throw "Can not Open file :" + logfile;
	}

	QTextStream out(&log);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
	QTextCodec *codec=QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForCStrings(codec);
	out.setCodec(codec);
	out<<QObject::tr(log_line)<<endl;
	out.flush();
	log.close();
	return true;
}