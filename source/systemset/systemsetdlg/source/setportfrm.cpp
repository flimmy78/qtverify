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
#include "algorithm.h"

SetPortFrm::SetPortFrm(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	gui.setupUi(this);

	QString filename = getFullIniFileName("portset.ini");
	PortSet = new QSettings(filename, QSettings::IniFormat);
	InstallIni();

	m_readComConfig = NULL;
	m_controlObj = NULL;
	initControlCom();
	initValveStatus();
}

SetPortFrm::~SetPortFrm()
{
	if (PortSet)
	{
		delete PortSet;
		PortSet = NULL;
	}

	if (m_readComConfig)
	{
		delete m_readComConfig;
		m_readComConfig = NULL;
	}

	if (m_controlObj)
	{
		delete m_controlObj;
		m_controlObj = NULL;
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

void SetPortFrm::initControlCom()
{
	m_readComConfig = new ReadComConfig();
	ComInfoStruct valveStruct = m_readComConfig->ReadValveConfig();
	m_controlObj = new ControlComObject();
	m_controlObj->setProtocolVersion(gui.cBox_Version->currentIndex()); //����Э��汾
	m_controlObj->openControlCom(&valveStruct);
}

void SetPortFrm::on_btnRoutine_1_clicked()
{
	m_valveStatus[0] = !m_valveStatus[0];
	m_controlObj->askControlRelay(1, m_valveStatus[0]);
}

void SetPortFrm::on_btnRoutine_2_clicked()
{
	m_valveStatus[1] = !m_valveStatus[1];
	m_controlObj->askControlRelay(2, m_valveStatus[1]);
}

void SetPortFrm::on_btnRoutine_3_clicked()
{
	m_valveStatus[2] = !m_valveStatus[2];
	m_controlObj->askControlRelay(3, m_valveStatus[2]);
}

void SetPortFrm::on_btnRoutine_4_clicked()
{
	m_valveStatus[3] = !m_valveStatus[3];
	m_controlObj->askControlRelay(4, m_valveStatus[3]);
}

void SetPortFrm::on_btnRoutine_5_clicked()
{
	m_valveStatus[4] = !m_valveStatus[4];
	m_controlObj->askControlRelay(5, m_valveStatus[4]);
}

void SetPortFrm::on_btnRoutine_6_clicked()
{
	m_valveStatus[5] = !m_valveStatus[5];
	m_controlObj->askControlRelay(6, m_valveStatus[5]);
}

void SetPortFrm::on_btnRoutine_7_clicked()
{
	m_valveStatus[6] = !m_valveStatus[6];
	m_controlObj->askControlRelay(7, m_valveStatus[6]);
}

void SetPortFrm::on_btnRoutine_8_clicked()
{
	m_valveStatus[7] = !m_valveStatus[7];
	m_controlObj->askControlRelay(8, m_valveStatus[7]);
}

void SetPortFrm::initValveStatus()
{
	//�˿ں�-����״̬ ȫ������״̬Ϊ�ر�
	m_valveStatus[0] = VALVE_CLOSE;
	m_valveStatus[1] = VALVE_CLOSE;
	m_valveStatus[2] = VALVE_CLOSE;
	m_valveStatus[3] = VALVE_CLOSE;
	m_valveStatus[4] = VALVE_CLOSE;
	m_valveStatus[5] = VALVE_CLOSE;
	m_valveStatus[6] = VALVE_CLOSE;
	m_valveStatus[7] = VALVE_CLOSE;
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