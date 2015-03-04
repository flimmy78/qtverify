#ifndef SYSTEMSETDLG_GLOBAL_H
#define SYSTEMSETDLG_GLOBAL_H


#ifdef SYSTEMSETDLG_DLL
#  ifdef WIN32
#  define SYSTEMSETDLG_EXPORT __declspec(dllexport)
#  else
#  define SYSTEMSETDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define SYSTEMSETDLG_EXPORT __declspec(dllimport)
#  else
#  define SYSTEMSETDLG_EXPORT
#  endif
#endif

#endif //SYSTEMSETDLG_GLOBAL_H