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
