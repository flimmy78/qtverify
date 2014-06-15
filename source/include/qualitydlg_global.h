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

typedef struct ComInfo_Struct
{
	QString portName; //串口名
	int     baudRate; //波特率
	int     dataBit;  //数据位
	int     parity;   //奇偶校验
	int     stopBit;  //停止位
}ComInfoStruct;

#endif //QUALITYDLG_GLOBAL_H