/***********************************************
**  �ļ���:     SetPortFrm.cpp
**  ����:       ���û��Ը����豸�Ĵ������ñ��浽 $ADEHOME/ini/comconfig.xml�ļ���;
					���ڴ��ڼ���ʱ���������ļ��е���Ӧ����װ�ص�������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/15
**  רҵ��:     ��³���������
**  ���������: �α���
**  ����Ա:     �α���
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:
***********************************************/

#include <QSettings>
#include <QMessageBox>

#include "setportfrm.h"
#include "commondefine.h"

SetPortFrm::SetPortFrm(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	gui.setupUi(this);

	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
#ifdef Q_OS_LINUX
		IniPath = adehome + "\/ini\/portset.ini";
#elif defined (Q_OS_WIN)
		IniPath = adehome + "\\ini\\portset.ini";
#endif
	PortSet = new QSettings(IniPath, QSettings::IniFormat);

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
** ��ȡ�ϴεĶ˿�����
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
** ����˿�����
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