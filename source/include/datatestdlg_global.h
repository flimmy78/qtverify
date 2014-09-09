#ifndef DATATESTDLG_GLOBAL_H
#define DATATESTDLG_GLOBAL_H


#ifdef DATATESTDLG_DLL
#  ifdef WIN32
#  define DATATESTDLG_EXPORT __declspec(dllexport)
#  else
#  define DATATESTDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define DATATESTDLG_EXPORT __declspec(dllimport)
#  else
#  define DATATESTDLG_EXPORT
#  endif
#endif

#endif //DATATESTDLG_GLOBAL_H