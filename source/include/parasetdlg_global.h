#ifndef PARASETDLG_GLOBAL_H
#define PARASETDLG_GLOBAL_H


#ifdef DATATESTDLG_DLL
#  ifdef WIN32
#  define PARASETDLG_EXPORT __declspec(dllexport)
#  else
#  define PARASETDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define PARASETDLG_EXPORT __declspec(dllimport)
#  else
#  define PARASETDLG_EXPORT
#  endif
#endif

#endif //PARASETDLG_GLOBAL_H