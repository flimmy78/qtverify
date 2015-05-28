/***********************************************
**  文件名:     SetPortFrm.cpp
**  功能:       将用户对各个设备的串口设置保存到 $ADEHOME/ini/comconfig.xml文件中;
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
#include <QMessageBox>

#include "setportfrm.h"
#include "commondefine.h"
#include "algorithm.h"

SetPortFrm::SetPortFrm(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	gui.setupUi(this);

	QString filename = getFullIniFileName("portset.ini");
	PortSet = new QSettings(filename, QSettings::IniFormat);

	InstallIni();
}

SetPortFrm::~SetPortFrm()
{
	if (PortSet)
	{
		delete PortSet;
		PortSet = NULL;
	}
}

void SetPortFrm::on_btn_Exit_clicked()
{
	close();
}

void SetPortFrm::on_btn_Save_clicked()
{
	WriteIni();
	QMessageBox::information(this, tr("OK"), tr("Save Successful !"));
}
/*
** 读取上次的端口配置
*/
void SetPortFrm::InstallIni()
{
	gui.cBox_Inlet->setCurrentIndex(PortSet->value("Relay/waterInNo").toInt() - 1);
	gui.cBox_Outlet->setCurrentIndex(PortSet->value("Relay/waterOutNo").toInt() - 1);
	gui.cBox_Rate_1->setCurrentIndex(PortSet->value("Relay/bigNo").toInt() - 1);
	gui.cBox_Rate_2->setCurrentIndex(PortSet->value("Relay/middle2No").toInt() - 1);
	gui.cBox_Rate_3->setCurrentIndex(PortSet->value("Relay/middle1No").toInt() - 1);
	gui.cBox_Rate_4->setCurrentIndex(PortSet->value("Relay/smallNo").toInt() - 1);

	gui.cBox_Pump->setCurrentIndex(PortSet->value("Regulate/pumpNo").toInt() - 1);
	gui.cBox_Regulate_1->setCurrentIndex(PortSet->value("Regulate/regflow1No").toInt() - 1);
	gui.cBox_Regulate_2->setCurrentIndex(PortSet->value("Regulate/regflow2No").toInt() - 1);
	gui.cBox_Regulate_3->setCurrentIndex(PortSet->value("Regulate/regflow3No").toInt() - 1);
	gui.cBox_Regulate_4->setCurrentIndex(PortSet->value("Regulate/regflow4No").toInt() - 1);

	gui.cBox_Version->setCurrentIndex(PortSet->value("CtrlBoard/version").toInt());
}

/*
** 保存端口配置
*/
void SetPortFrm::WriteIni()
{
	PortSet->setValue("Relay/waterInNo",gui.cBox_Inlet->currentIndex() + 1);
	PortSet->setValue("Relay/waterOutNo",gui.cBox_Outlet->currentIndex() + 1);
	PortSet->setValue("Relay/bigNo",gui.cBox_Rate_1->currentIndex() + 1);
	PortSet->setValue("Relay/middle2No",gui.cBox_Rate_2->currentIndex() + 1);
	PortSet->setValue("Relay/middle1No",gui.cBox_Rate_3->currentIndex() + 1);
	PortSet->setValue("Relay/smallNo",gui.cBox_Rate_4->currentIndex() + 1);

	PortSet->setValue("Regulate/pumpNo",gui.cBox_Pump->currentIndex() + 1);
	PortSet->setValue("Regulate/regflow1No",gui.cBox_Regulate_1->currentIndex() + 1);
	PortSet->setValue("Regulate/regflow2No",gui.cBox_Regulate_2->currentIndex() + 1);
	PortSet->setValue("Regulate/regflow3No",gui.cBox_Regulate_3->currentIndex() + 1);
	PortSet->setValue("Regulate/regflow4No",gui.cBox_Regulate_4->currentIndex() + 1);
	
	PortSet->setValue("CtrlBoard/version",gui.cBox_Version->currentIndex());
}