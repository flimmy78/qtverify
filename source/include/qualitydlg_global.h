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
	QString portName; //������
	int     baudRate; //������
	int     dataBit;  //����λ
	int     parity;   //��żУ��
	int     stopBit;  //ֹͣλ
}ComInfoStruct;

#endif //QUALITYDLG_GLOBAL_H