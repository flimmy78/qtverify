#ifndef QTCOMDLG_GLOBAL_H
#define QTCOMDLG_GLOBAL_H


#ifdef QTCOMDLG_DLL
#  ifdef WIN32
#  define QTCOMDLG_EXPORT __declspec(dllexport)
#  else
#  define QTCOMDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define QTCOMDLG_EXPORT __declspec(dllimport)
#  else
#  define QTCOMDLG_EXPORT
#  endif
#endif

#endif //QTCOMDLG_GLOBAL_H