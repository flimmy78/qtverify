#ifndef RESULTQUERY_GLOBAL_H
#define RESULTQUERY_GLOBAL_H

#ifdef RESULTQUERYDLG_DLL
#  ifdef WIN32
#  define RESULTQUERYDLG_EXPORT __declspec(dllexport)
#  else
#  define RESULTQUERYDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define RESULTQUERYDLG_EXPORT __declspec(dllimport)
#  else
#  define RESULTQUERYDLG_EXPORT
#  endif
#endif

#endif //RESULTQUERY_GLOBAL_H