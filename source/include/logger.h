#ifndef LOGGER_H
#define LOGGER_H

#ifdef LOGGER_DLL
#  ifdef WIN32
#  define LOGGER_EXPORT __declspec(dllexport)
#  else
#  define LOGGER_EXPORT
#  endif
#else
#  ifdef WIN32
#  define LOGGER_EXPORT __declspec(dllimport)
#  else
#  define LOGGER_EXPORT
#  endif
#endif

#include <QString>
#include <QtCore/QtMsgHandler>
#include <QtCore/QDebug>
#include <QtCore/QMutex>
#include <QtGui/QDateTimeEdit>
#include <QtCore/QFile>

#include "commondefine.h"

void myMessageOutput(QtMsgType type, const char *msg)
{
	static QMutex mutex;
	mutex.lock();

 	QString text;
	switch (type) {
	case QtDebugMsg:
		fprintf(stderr, "Debug: %s\n", msg);
		text = QString("Debug: %1").arg(msg);
		mutex.unlock();
		return; // qDebug()信息不写入日志文件,只在后台打印
	case QtWarningMsg:
		fprintf(stderr, "%s\n", msg);
		text = QString("%1").arg(msg);
		break;
	case QtCriticalMsg:
		fprintf(stderr, "%s\n", msg);
		text = QString("%1").arg(msg);
		break;
	case QtFatalMsg:
		fprintf(stderr, "Fatal: %s\n", msg);
		text = QString("Fatal: %1").arg(msg);
// 		abort();
		break;
	default:
		fprintf(stderr, "Unknown Msg Type: %s\n", msg);
		text = QString("Unknown Msg Type: %1").arg(msg);
		break;
	}

 	QString current_date_time = QDateTime::currentDateTime().toString("hh:mm:ss ddd");
	QString message = QString("%1 %2").arg(current_date_time).arg(text);
	QString current_day = QDateTime::currentDateTime().toString("yyyy-MM-dd");

	char filename[100];
	memset(filename, 0, sizeof(char)*100);
	sprintf_s(filename, "%s/log/log_%s.txt", getenv("RUNHOME"), current_day.toStdString().c_str());
	QFile file(QString("%1").arg(filename));
	if (file.open(QIODevice::WriteOnly | QIODevice::Append))
	{
		QTextStream text_stream(&file);
		text_stream<<message<<"\r\n";
		file.flush();
		file.close();
	}

	mutex.unlock();
}



class LOGGER_EXPORT CLogger
{
public:
	CLogger();
	~CLogger();

	bool WriteLn(const char *);
private:
	QString logfile;
};

#endif // LOGGER_H
