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

class LOGGER_EXPORT CLogger
{
public:
	CLogger();
	~CLogger();

	bool WriteLn(const char *);
private:
	QString logfile;
};


void myMessageOutput(QtMsgType type, const char *msg)
{
	static QMutex mutex;
	mutex.lock();

	QString text;
	switch (type) {
	case QtDebugMsg:
		text = QString("Debug:");
		break;
	case QtWarningMsg:
		text = QString("Warning:");
		break;
	case QtCriticalMsg:
		text = QString("Critical:");
		break;
	case QtFatalMsg:
		text = QString("Fatal:");
// 		abort();
	}

	QString context_info = QString("File:(%1) Line:(%2)").arg(__FILE__).arg(__LINE__);
	QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
	QString current_date = QString("(%1)").arg(current_date_time);
	QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

	char filename[60];
	memset(filename, 0, sizeof(char)*60);
	sprintf_s(filename, "%s/log/log.txt", getenv("RUNHOME"));
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


#endif // LOGGER_H
