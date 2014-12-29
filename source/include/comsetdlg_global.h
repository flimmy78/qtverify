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

typedef struct ComInfo_Struct
{
	QString portName; //串口名
	int     baudRate; //波特率
	int     dataBit;  //数据位
	int     parity;   //奇偶校验
	int     stopBit;  //停止位
}ComInfoStruct;

#endif //COMSETDLG_GLOBAL_H