/***********************************************
**  文件名:     stdparaset.cpp
**  功能:       标准表参数设定
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/3/5
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2015/03 第一版
**  内容包含:
**  说明:
**  更新记录:
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QTextCodec>
#include <QThread>
#include <QtGui/QMessageBox>
#include <QtCore/QProcessEnvironment>

#include "algorithm.h"
#include "stdmtrparaset.h"

StdMtrParaSet::StdMtrParaSet(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"StdParaSet thread:"<<QThread::currentThreadId();
	ui.setupUi(this);
	m_stdParam = NULL;
	m_stdParam = new QSettings(getFullIniFileName("stdmtrparaset.ini"),QSettings::IniFormat);
	m_needCorrection = false;
}

void StdMtrParaSet::showEvent(QShowEvent *)
{
	initWdgVec();
	initBtnGroup();
	installStdMeter();
	installRoute();
}

StdMtrParaSet::~StdMtrParaSet()
{
	releaseSource();
}

void StdMtrParaSet::closeEvent(QCloseEvent *)
{
	releaseSource();
	emit signalClosed();
}

void StdMtrParaSet::releaseSource()
{
	if (m_stdParam)
	{
		delete m_stdParam;
		m_stdParam = NULL;
	}

	if (m_btnGroupCorrection)
	{
		delete m_btnGroupCorrection;
		m_btnGroupCorrection = NULL;
	}
}

void StdMtrParaSet::initBtnGroup()
{
	m_btnGroupCorrection = new QButtonGroup(ui.gBox_Correction); //计量单位
	m_btnGroupCorrection->addButton(ui.rBtnCorrection, true);
	m_btnGroupCorrection->addButton(ui.rBtnNotCorrection, false);
	connect(m_btnGroupCorrection, SIGNAL(buttonClicked(int)), this, SLOT(slotCorrectionclicked(int)));
}

void StdMtrParaSet::slotCorrectionclicked(int idx)
{
	m_needCorrection = idx;
}

void StdMtrParaSet::initWdgVec()
{	
	m_vecflowPointBig.append(ui.lineEdit_FLowPoint_0_0);
	m_vecflowPointBig.append(ui.lineEdit_FLowPoint_1_0);
	m_vecflowPointBig.append(ui.lineEdit_FLowPoint_2_0);
	m_vecflowPointBig.append(ui.lineEdit_FLowPoint_3_0);
	m_vecflowPointBig.append(ui.lineEdit_FLowPoint_4_0);
	m_vecflowPointBig.append(ui.lineEdit_FLowPoint_5_0);
	m_vecflowPointBig.append(ui.lineEdit_FLowPoint_6_0);
	m_vecflowPointBig.append(ui.lineEdit_FLowPoint_7_0);
	m_vecflowPointBig.append(ui.lineEdit_FLowPoint_8_0);
	m_vecflowPointBig.append(ui.lineEdit_FLowPoint_9_0);

	m_vecflowPointMid2.append(ui.lineEdit_FLowPoint_0_1);
	m_vecflowPointMid2.append(ui.lineEdit_FLowPoint_1_1);
	m_vecflowPointMid2.append(ui.lineEdit_FLowPoint_2_1);
	m_vecflowPointMid2.append(ui.lineEdit_FLowPoint_3_1);
	m_vecflowPointMid2.append(ui.lineEdit_FLowPoint_4_1);
	m_vecflowPointMid2.append(ui.lineEdit_FLowPoint_5_1);
	m_vecflowPointMid2.append(ui.lineEdit_FLowPoint_6_1);
	m_vecflowPointMid2.append(ui.lineEdit_FLowPoint_7_1);
	m_vecflowPointMid2.append(ui.lineEdit_FLowPoint_8_1);
	m_vecflowPointMid2.append(ui.lineEdit_FLowPoint_9_1);

	m_vecflowPointMid1.append(ui.lineEdit_FLowPoint_0_2);	   
	m_vecflowPointMid1.append(ui.lineEdit_FLowPoint_1_2);
	m_vecflowPointMid1.append(ui.lineEdit_FLowPoint_2_2);
	m_vecflowPointMid1.append(ui.lineEdit_FLowPoint_3_2);
	m_vecflowPointMid1.append(ui.lineEdit_FLowPoint_4_2);
	m_vecflowPointMid1.append(ui.lineEdit_FLowPoint_5_2);
	m_vecflowPointMid1.append(ui.lineEdit_FLowPoint_6_2);
	m_vecflowPointMid1.append(ui.lineEdit_FLowPoint_7_2);
	m_vecflowPointMid1.append(ui.lineEdit_FLowPoint_8_2);
	m_vecflowPointMid1.append(ui.lineEdit_FLowPoint_9_2);

	m_vecflowPointSmall.append(ui.lineEdit_FLowPoint_0_3);
	m_vecflowPointSmall.append(ui.lineEdit_FLowPoint_1_3);
	m_vecflowPointSmall.append(ui.lineEdit_FLowPoint_2_3);
	m_vecflowPointSmall.append(ui.lineEdit_FLowPoint_3_3);
	m_vecflowPointSmall.append(ui.lineEdit_FLowPoint_4_3);
	m_vecflowPointSmall.append(ui.lineEdit_FLowPoint_5_3);
	m_vecflowPointSmall.append(ui.lineEdit_FLowPoint_6_3);
	m_vecflowPointSmall.append(ui.lineEdit_FLowPoint_7_3);
	m_vecflowPointSmall.append(ui.lineEdit_FLowPoint_8_3);
	m_vecflowPointSmall.append(ui.lineEdit_FLowPoint_9_3);

	m_vecKCoeBig.append(ui.lineEdit_KCoe_0_0);
	m_vecKCoeBig.append(ui.lineEdit_KCoe_1_0);
	m_vecKCoeBig.append(ui.lineEdit_KCoe_2_0);
	m_vecKCoeBig.append(ui.lineEdit_KCoe_3_0);
	m_vecKCoeBig.append(ui.lineEdit_KCoe_4_0);
	m_vecKCoeBig.append(ui.lineEdit_KCoe_5_0);
	m_vecKCoeBig.append(ui.lineEdit_KCoe_6_0);
	m_vecKCoeBig.append(ui.lineEdit_KCoe_7_0);
	m_vecKCoeBig.append(ui.lineEdit_KCoe_8_0);
	m_vecKCoeBig.append(ui.lineEdit_KCoe_9_0);

	m_vecKCoeMid2.append(ui.lineEdit_KCoe_0_1);
	m_vecKCoeMid2.append(ui.lineEdit_KCoe_1_1);
	m_vecKCoeMid2.append(ui.lineEdit_KCoe_2_1);
	m_vecKCoeMid2.append(ui.lineEdit_KCoe_3_1);
	m_vecKCoeMid2.append(ui.lineEdit_KCoe_4_1);
	m_vecKCoeMid2.append(ui.lineEdit_KCoe_5_1);
	m_vecKCoeMid2.append(ui.lineEdit_KCoe_6_1);
	m_vecKCoeMid2.append(ui.lineEdit_KCoe_7_1);
	m_vecKCoeMid2.append(ui.lineEdit_KCoe_8_1);
	m_vecKCoeMid2.append(ui.lineEdit_KCoe_9_1);

	m_vecKCoeMid1.append(ui.lineEdit_KCoe_0_2);	
	m_vecKCoeMid1.append(ui.lineEdit_KCoe_1_2);
	m_vecKCoeMid1.append(ui.lineEdit_KCoe_2_2);
	m_vecKCoeMid1.append(ui.lineEdit_KCoe_3_2);
	m_vecKCoeMid1.append(ui.lineEdit_KCoe_4_2);
	m_vecKCoeMid1.append(ui.lineEdit_KCoe_5_2);
	m_vecKCoeMid1.append(ui.lineEdit_KCoe_6_2);
	m_vecKCoeMid1.append(ui.lineEdit_KCoe_7_2);
	m_vecKCoeMid1.append(ui.lineEdit_KCoe_8_2);
	m_vecKCoeMid1.append(ui.lineEdit_KCoe_9_2);

	m_vecKCoeSmall.append(ui.lineEdit_KCoe_0_3);
	m_vecKCoeSmall.append(ui.lineEdit_KCoe_1_3);
	m_vecKCoeSmall.append(ui.lineEdit_KCoe_2_3);
	m_vecKCoeSmall.append(ui.lineEdit_KCoe_3_3);
	m_vecKCoeSmall.append(ui.lineEdit_KCoe_4_3);
	m_vecKCoeSmall.append(ui.lineEdit_KCoe_5_3);
	m_vecKCoeSmall.append(ui.lineEdit_KCoe_6_3);
	m_vecKCoeSmall.append(ui.lineEdit_KCoe_7_3);
	m_vecKCoeSmall.append(ui.lineEdit_KCoe_8_3);
	m_vecKCoeSmall.append(ui.lineEdit_KCoe_9_3);

	m_mapPulseWdg[FLOW_RATE_BIG]   = ui.lineEdit_Pulse_0;
	m_mapPulseWdg[FLOW_RATE_MID_2] = ui.lineEdit_Pulse_1;
	m_mapPulseWdg[FLOW_RATE_MID_1] = ui.lineEdit_Pulse_2;
	m_mapPulseWdg[FLOW_RATE_SMALL] = ui.lineEdit_Pulse_3;

	m_mapUpperFlowWdg[FLOW_RATE_BIG]   = ui.lineEdit_UpperFlow_0;
	m_mapUpperFlowWdg[FLOW_RATE_MID_2] = ui.lineEdit_UpperFlow_1;
	m_mapUpperFlowWdg[FLOW_RATE_MID_1] = ui.lineEdit_UpperFlow_2;
	m_mapUpperFlowWdg[FLOW_RATE_SMALL] = ui.lineEdit_UpperFlow_3;

	m_mapAdjustWdg[FLOW_RATE_BIG]   = ui.lineEdit_adjust_0;
	m_mapAdjustWdg[FLOW_RATE_MID_2] = ui.lineEdit_adjust_1;
	m_mapAdjustWdg[FLOW_RATE_MID_1] = ui.lineEdit_adjust_2;
	m_mapAdjustWdg[FLOW_RATE_SMALL] = ui.lineEdit_adjust_3;

	m_mapInstRouteWdg[FLOW_RATE_BIG]    = ui.cBox_instroute_0;
	m_mapInstRouteWdg[FLOW_RATE_MID_2]  = ui.cBox_instroute_1;
	m_mapInstRouteWdg[FLOW_RATE_MID_1]  = ui.cBox_instroute_2;
	m_mapInstRouteWdg[FLOW_RATE_SMALL]  = ui.cBox_instroute_3;

	m_mapAccumRouteWdg[FLOW_RATE_BIG]    = ui.cBox_accumroute_0;
	m_mapAccumRouteWdg[FLOW_RATE_MID_2]  = ui.cBox_accumroute_1;
	m_mapAccumRouteWdg[FLOW_RATE_MID_1]  = ui.cBox_accumroute_2;
	m_mapAccumRouteWdg[FLOW_RATE_SMALL]  = ui.cBox_accumroute_3;

	m_mapBalanceRouteWdg[FLOW_RATE_BIG]    = ui.cBox_Bal_0;
	m_mapBalanceRouteWdg[FLOW_RATE_MID_2]  = ui.cBox_Bal_1;
	m_mapBalanceRouteWdg[FLOW_RATE_MID_1]  = ui.cBox_Bal_2;
	m_mapBalanceRouteWdg[FLOW_RATE_SMALL]  = ui.cBox_Bal_3;
}

void StdMtrParaSet::installStdMeter()
{
	installFlowKCoe();
	installPulse();
	installFlowRate();
}

void StdMtrParaSet::installRoute()
{
	m_stdParam->beginReadArray("Route");
	for (int i=0;i<DIAMETER_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_mapInstRouteWdg[(flow_rate_wdg)i]->setCurrentIndex(m_stdParam->value("InstRoute").toInt()+1);
		m_mapAccumRouteWdg[(flow_rate_wdg)i]->setCurrentIndex(m_stdParam->value("AccumRoute").toInt()+1);
		m_mapBalanceRouteWdg[(flow_rate_wdg)i]->setCurrentIndex(m_stdParam->value("Balance").toInt());
	}
	m_stdParam->endArray();

	m_stdParam->beginGroup("DevNo.");
	ui.lineEdit_instDevNo->setText(m_stdParam->value("InstDevNo").toString());
	ui.lineEdit_accumDevNo->setText(m_stdParam->value("AccumDevNo").toString());
	m_stdParam->endGroup();

	m_stdParam->beginGroup("NeedCorrection");
	m_needCorrection = m_stdParam->value("NeedCorrection").toBool();
	ui.rBtnCorrection->setChecked(m_needCorrection);
	ui.rBtnNotCorrection->setChecked(!m_needCorrection);
	m_stdParam->endGroup();
}

void StdMtrParaSet::installFlowRate()
{
	m_stdParam->beginReadArray("FlowRate");
	for (int i=0;i<DIAMETER_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_mapUpperFlowWdg[(flow_rate_wdg)i]->setText(m_stdParam->value("UpperFlow").toString());
		m_mapAdjustWdg[(flow_rate_wdg)i]->setText(m_stdParam->value("Adjust").toString());
	}
	m_stdParam->endArray();
}

void StdMtrParaSet::installPulse()
{
	m_stdParam->beginReadArray("Pulse");
	for (int i=0;i<DIAMETER_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_mapPulseWdg[(flow_rate_wdg)i]->setText(m_stdParam->value("Pulse").toString());
	}
	m_stdParam->endArray();
}

void StdMtrParaSet::installFlowKCoe()
{
	m_stdParam->beginReadArray("BigFlowK");
	for (int i=0;i<FLOW_K_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_vecflowPointBig.at(i)->setText(m_stdParam->value("flowPoint").toString());
		m_vecKCoeBig.at(i)->setText(m_stdParam->value("KCoe").toString());
	}
	m_stdParam->endArray();

	m_stdParam->beginReadArray("Mid2FlowK");
	for (int i=0;i<FLOW_K_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_vecflowPointMid2.at(i)->setText(m_stdParam->value("flowPoint").toString());
		m_vecKCoeMid2.at(i)->setText(m_stdParam->value("KCoe").toString());
	}
	m_stdParam->endArray();

	m_stdParam->beginReadArray("Mid1FlowK");
	for (int i=0;i<FLOW_K_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_vecflowPointMid1.at(i)->setText(m_stdParam->value("flowPoint").toString());
		m_vecKCoeMid1.at(i)->setText(m_stdParam->value("KCoe").toString());
	}
	m_stdParam->endArray();

	m_stdParam->beginReadArray("SmallFlowK");
	for (int i=0;i<FLOW_K_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_vecflowPointSmall.at(i)->setText(m_stdParam->value("flowPoint").toString());
		m_vecKCoeSmall.at(i)->setText(m_stdParam->value("KCoe").toString());
	}
	m_stdParam->endArray();
}

void StdMtrParaSet::writeStdMeter()
{
	writeFlowKCoe();
	writePulse();
	writeUpperFlow();
}

void StdMtrParaSet::writeFlowKCoe()
{
	m_stdParam->beginWriteArray("BigFlowK");
	for (int i=0;i<FLOW_K_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_stdParam->setValue("flowPoint",m_vecflowPointBig.at(i)->text());
		m_stdParam->setValue("KCoe",m_vecKCoeBig.at(i)->text());
	}
	m_stdParam->endArray();

	m_stdParam->beginWriteArray("Mid2FlowK");
	for (int i=0;i<FLOW_K_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_stdParam->setValue("flowPoint",m_vecflowPointMid2.at(i)->text());
		m_stdParam->setValue("KCoe",m_vecKCoeMid2.at(i)->text());
	}
	m_stdParam->endArray();

	m_stdParam->beginWriteArray("Mid1FlowK");
	for (int i=0;i<FLOW_K_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_stdParam->setValue("flowPoint",m_vecflowPointMid1.at(i)->text());
		m_stdParam->setValue("KCoe",m_vecKCoeMid1.at(i)->text());
	}
	m_stdParam->endArray();

	m_stdParam->beginWriteArray("SmallFlowK");
	for (int i=0;i<FLOW_K_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_stdParam->setValue("flowPoint",m_vecflowPointSmall.at(i)->text());
		m_stdParam->setValue("KCoe",m_vecKCoeSmall.at(i)->text());
	}
	m_stdParam->endArray();
}

void StdMtrParaSet::writePulse()
{
	m_stdParam->beginWriteArray("Pulse");
	for (int i=0;i<DIAMETER_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_stdParam->setValue("Pulse", m_mapPulseWdg[(flow_rate_wdg)i]->text());		
	}
	m_stdParam->endArray();
}

void StdMtrParaSet::writeUpperFlow()
{
	m_stdParam->beginWriteArray("FlowRate");
	for (int i=0;i<DIAMETER_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_stdParam->setValue(QString("UpperFlow"), m_mapUpperFlowWdg[(flow_rate_wdg)i]->text());
		m_stdParam->setValue(QString("Adjust"), m_mapAdjustWdg[(flow_rate_wdg)i]->text());
	}
	m_stdParam->endArray();
}

void StdMtrParaSet::writeRoute()
{
	m_stdParam->beginWriteArray("Route");
	for (int i=0;i<DIAMETER_NUM;i++)
	{
		m_stdParam->setArrayIndex(i);
		m_stdParam->setValue(QString("InstRoute"), m_mapInstRouteWdg[(flow_rate_wdg)i]->currentIndex()-1);
		m_stdParam->setValue(QString("AccumRoute"), m_mapAccumRouteWdg[(flow_rate_wdg)i]->currentIndex()-1);
		m_stdParam->setValue(QString("Balance"), m_mapBalanceRouteWdg[(flow_rate_wdg)i]->currentIndex());
	}
	m_stdParam->endArray();

	m_stdParam->beginGroup("DevNo.");
	m_stdParam->setValue("InstDevNo", ui.lineEdit_instDevNo->text());
	m_stdParam->setValue("AccumDevNo", ui.lineEdit_accumDevNo->text());
	m_stdParam->endGroup();

	m_stdParam->beginGroup("NeedCorrection");
	m_stdParam->setValue("NeedCorrection", m_needCorrection);
	m_stdParam->endGroup();
}

void StdMtrParaSet::on_btnSave_clicked()
{
	writeStdMeter();
	writeRoute();
}

void StdMtrParaSet::on_btnExit_clicked()
{
	this->close();
}