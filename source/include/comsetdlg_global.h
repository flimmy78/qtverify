#ifndef COMSETDLG_GLOBAL_H
#define COMSETDLG_GLOBAL_H


#ifdef COMSETDLG_DLL
#  ifdef WIN32
#  define COMSETDLG_EXPORT __declspec(dllexport)
#  else
#  define COMSETDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define COMSETDLG_EXPORT __declspec(dllimport)
#  else
#  define COMSETDLG_EXPORT
#  endif
#endif

#endif //COMSETDLG_GLOBAL_H