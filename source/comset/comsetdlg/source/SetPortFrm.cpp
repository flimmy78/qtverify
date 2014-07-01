/***********************************************
**  文件名:     SetComFrm.cpp
**  功能:       将用户对各个设备的串口设置保存到 $RUNHOME/ini/comconfig.xml文件中;
					并在窗口加载时，将配置文件中的相应配置装载到窗口中
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/15
**  专业组:     德鲁计量软件组
**  程序设计者: 宋宝善
**  程序员:     宋宝善
**  版本历史:   2014/06 第一版
**  内容包含:
**  说明:
**  更新记录:
***********************************************/

#include <QSettings>

#include "SetPortFrm.h"

SetPortFrm::SetPortFrm(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	gui.setupUi(this);

	QString path = QProcessEnvironment::systemEnvironment().value("RUNHOME");
#ifdef Q_OS_LINUX
		IniPath = path + "\/ini\/port.ini";
#elif defined (Q_OS_WIN)
		IniPath = path + "\\ini\\port.ini";
#endif
	PortSet = new QSettings(IniPath, QSettings::IniFormat);

	InstallIni();
}

SetPortFrm::~SetPortFrm()
{
	if (PortSet)
	{
		delete PortSet;
	}
}

void SetPortFrm::on_btn_Exit_clicked()
{
	close();
}

void SetPortFrm::on_btn_Save_clicked()
{
	WriteIni();
}

void SetPortFrm::InstallIni()
{
	gui.cBox_Inlet->setCurrentIndex(PortSet->value("Relay/WaterIn").toInt() - 1);
	gui.cBox_Outlet->setCurrentIndex(PortSet->value("Relay/WaterOut").toInt() - 1);
	gui.cBox_Rate_1->setCurrentIndex(PortSet->value("Relay/big").toInt() - 1);
	gui.cBox_Rate_2->setCurrentIndex(PortSet->value("Relay/middle2").toInt() - 1);
	gui.cBox_Rate_3->setCurrentIndex(PortSet->value("Relay/middle1").toInt() - 1);
	gui.cBox_Rate_4->setCurrentIndex(PortSet->value("Relay/small").toInt() - 1);
}

void SetPortFrm::WriteIni()
{
	PortSet->setValue("Relay/WaterIn",gui.cBox_Inlet->currentIndex() + 1);
	PortSet->setValue("Relay/WaterOut",gui.cBox_Outlet->currentIndex() + 1);
	PortSet->setValue("Relay/big",gui.cBox_Rate_1->currentIndex() + 1);
	PortSet->setValue("Relay/middle2",gui.cBox_Rate_2->currentIndex() + 1);
	PortSet->setValue("Relay/middle1",gui.cBox_Rate_3->currentIndex() + 1);
	PortSet->setValue("Relay/small",gui.cBox_Rate_4->currentIndex() + 1);
}