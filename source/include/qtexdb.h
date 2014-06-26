#ifndef QTEXDB_H
#define QTEXDB_H


#ifdef QTEXDB_DLL
#  ifdef WIN32
#  define QTEXDB_EXPORT __declspec(dllexport)
#  else
#  define QTEXDB_EXPORT
#  endif
#else
#  ifdef WIN32
#  define QTEXDB_EXPORT __declspec(dllimport)
#  else
#  define QTEXDB_EXPORT
#  endif
#endif

QTEXDB_EXPORT int testFunc(int a, int b);

class QTEXDB_EXPORT CQtExdb
{
public:
	CQtExdb();
	~CQtExdb();


private:

public slots:
	void WriteSettings();
	void ReadSettings();

};

#endif // QTEXDB_H
