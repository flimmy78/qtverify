#ifndef QUALITYDLG_GLOBAL_H
#define QUALITYDLG_GLOBAL_H


#ifdef QUALITYDLG_DLL
#  ifdef WIN32
#  define QUALITYDLG_EXPORT __declspec(dllexport)
#  else
#  define QUALITYDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define QUALITYDLG_EXPORT __declspec(dllimport)
#  else
#  define QUALITYDLG_EXPORT
#  endif
#endif

#endif //QUALITYDLG_GLOBAL_H