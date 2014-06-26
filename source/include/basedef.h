#ifndef BASEDEF_H
#define BASEDEF_H

/*
**      FUNCTION -- 获取下位机端口设置信息
*/
class PORTSET_INI_STR{
public:
    int     waterInNo;                   //
    int     flow1No;					 //
    int     flow2No;                     //
    int     flow3No;                     //
    int     flow4No;                     //
    int     waterOutNo;                  //
	int		regflow1No;
	int		regflow2No;
	int		regflow3No;
	int		regflow4No;
};
typedef PORTSET_INI_STR* PORTSET_INI_PTR;

#endif	//BASEDEF_H