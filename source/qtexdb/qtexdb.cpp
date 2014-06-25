#include <QtCore/QDebug>
#include "qtexdb.h"

/*int GetLdfIniInfomation( LDF_INIINFO_PTR info )
{
	FILE *fp = NULL;
	char filename[255];
	char* ldfhome = getenv( "WPFHOME" );
#ifdef __unix
	sprintf( filename, "%s/ini/wpfini.ini", ldfhome );
#else
	sprintf( filename, "%s\\ini\\wpfini.ini", ldfhome );
#endif

	fp = fopen( filename, "r" );
	printf(">>>>>>>>>>>>>>> filename=%s fp=%d %s %d\n", filename, fp, __FILE__, __LINE__);
	if( fp!=NULL )
	{
		int i=0;
		char str[255];
		while( !feof(fp) )
		{
			strcpy(str, "");
			fgets(str,125,fp);
			str[strlen(str)-1]='\0';
			sscanf(str, "%s", str);
			if(str[0]== '#') continue;
			if(!strcmp(str, "}" )) continue;
			if(!strcmp(str, "{" ))
			{
				strcpy(str, "");
				fgets(str,125,fp);
				sscanf(str, "%s", str);
				if(i==0) info->nMaxPointNum = atoi(str);
				if(i==1) info->nDataBeginFlag = atoi(str);
				if(i==2) info->nStParaSrc = atoi(str);
				if(i==3) info->nStDataSrc = atoi(str);
				if(i==4) info->nPrintFlag = atoi(str);
				if(i==5) info->nWeatherFlag = atoi(str);
				if(i==6) info->nStlfItemFlag = atoi(str);
				if(i==7) info->nBlfLoacatedFlag = atoi(str);
				if(i==8) info->nMlfLoacatedFlag = atoi(str);
				if(i==9) info->nSstlfLoacatedFlag = atoi(str);
				i++;
			}
		}
		fclose(fp);
		if(info->nDataBeginFlag!=0) info->nDataBeginFlag=1;
		return True;
	}
	else{
		return False;
	}
}*/

int testFunc(int a, int b)
{
	printf_s("%d + %d = %d\n", a, b, (a+b));
	return (a + b);
}
CQtExdb::CQtExdb()
{

}

CQtExdb::~CQtExdb()
{

}

