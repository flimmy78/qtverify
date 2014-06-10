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


class LOGGER_EXPORT CLogger
{
public:
	CLogger();
	~CLogger();

	float calc(float a, float b);

private:

};

#endif // LOGGER_H
