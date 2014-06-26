#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include "qtexdb.h"


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

void CQtExdb::WriteSettings()
{
	QSettings settings("Option.ini", QSettings::IniFormat); // 当前目录的INI文件
	settings.beginGroup("DevOption");
	settings.setValue("mainFun", 25);
	settings.setValue("subFun", 40);
	settings.setValue("service", 1);
	settings.endGroup();
}

void CQtExdb::ReadSettings()
{
	QSettings settings("Option.ini", QSettings::IniFormat);

	int mainFun = settings.value("DevOption/mainFun").toInt();
	int subFun = settings.value("DevOption/subFun").toInt();
	QString service = settings.value("DevOption/service").toString();

	qDebug() << "service" << service;
	qDebug() << "mainFun" << mainFun;
	qDebug() << "subFun" << subFun;
}
