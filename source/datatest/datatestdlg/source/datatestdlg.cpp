/***********************************************
**  �ļ���:     datatestdlg.cpp
**  ����:       �ɼ�����Ʋ��Գ���
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/12
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:		ֻ���ڲ��Բɼ�����ƣ�����Ϊ�������춨��������(2014-07-15��ע)
**  ���¼�¼:   
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>

#include "datatestdlg.h"
#include "commondefine.h"
#include "parasetdlg.h"
#include "readcomconfig.h"
#include "algorithm.h"

DataTestDlg::DataTestDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	m_stdParam = new QSettings(getFullIniFileName("stdmtrparaset.ini"), QSettings::IniFormat);
}

DataTestDlg::~DataTestDlg()
{
}

void DataTestDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^DataTestDlg::closeEvent";
	
	if (m_paraSetReader) //���춨����
	{
		delete m_paraSetReader;
		m_paraSetReader = NULL;
	}

	if (m_paraSetDlg) //�������öԻ���
	{
		delete m_paraSetDlg;
		m_paraSetDlg = NULL;
	}

	if (m_readComConfig)  //����������
	{
		delete m_readComConfig;
		m_readComConfig = NULL;
	}

	if (m_tempThread.isRunning())
	{
		m_tempThread.exit();
		if (m_tempObj)  // �¶Ȳɼ�
		{
			delete m_tempObj;
			m_tempObj = NULL;
		}
	}
	
	if (m_controlObj)  //���ſ���
	{
		delete m_controlObj;
		m_controlObj = NULL;

		m_valveThread.exit();
	}

	if (m_balanceObj)  //��ƽ�ɼ�
	{
		delete m_balanceObj;
		m_balanceObj = NULL;

		m_balanceThread.exit();
	}
	
	if (m_meterObj)  //��������ͨѶ
	{
		delete m_meterObj;
		m_meterObj = NULL;

		m_meterThread.exit();
	}

	if (m_tempTimer) //���¶ȼ�ʱ��
	{
		if (m_tempTimer->isActive())
		{
			m_tempTimer->stop();
		}
		delete m_tempTimer;
		m_tempTimer = NULL;
	}

	if (m_stdTempTimer) //����׼�¶ȼ�ʱ��
	{
		if (m_stdTempTimer->isActive())
		{
			m_stdTempTimer->stop();
		}
		delete m_stdTempTimer;
		m_stdTempTimer = NULL;
	}

	if (m_stdTempObj)  // ��׼�¶Ȳɼ�
	{
		delete m_stdTempObj;
		m_stdTempObj = NULL;

		m_stdTempThread.exit();
	}

	if (m_flowRateTimer) //����������ʱ��
	{
		if (m_flowRateTimer->isActive())
		{
			m_flowRateTimer->stop();
		}
		delete m_flowRateTimer;
		m_flowRateTimer = NULL;
	}

	if (m_oldCoe)
	{
		delete m_oldCoe;
		m_oldCoe = NULL;
	}
/*****************************************************/
	if (m_instSTDMeterTimer)
	{
		if (m_instSTDMeterTimer->isActive())
		{
			m_instSTDMeterTimer->stop();
		}

		delete m_instSTDMeterTimer;
		m_instSTDMeterTimer = NULL;
	}

	if (m_instantFlowCom)
	{
		m_instantFlowThread.exit();
		delete m_instantFlowCom;
		m_instantFlowCom = NULL;
	}

	if (m_accumSTDMeterTimer)
	{
		if (m_accumSTDMeterTimer->isActive())
		{
			m_accumSTDMeterTimer->stop();
		}
		delete m_accumSTDMeterTimer;
		m_accumSTDMeterTimer = NULL;
	}

	if (m_accumulateFlowCom)
	{
		m_accumFlowThread.exit();
		delete m_accumulateFlowCom;
		m_accumulateFlowCom = NULL;
	}
/*****************************************************/
	if (m_setRegularTimer) //�Զ�����������ʱ��
	{
		if (m_setRegularTimer->isActive())
		{
			m_setRegularTimer->stop();
		}
		delete m_setRegularTimer;
		m_setRegularTimer = NULL;
	}
/*****************************************************/
}

void DataTestDlg::showEvent(QShowEvent *event)
{
	qDebug()<<"DataTestDlg showEvent thread:"<<QThread::currentThreadId();
	//��ȡ��λ���˿�������Ϣ
	if (!getPortSetIni(&m_portsetinfo))
	{
		QMessageBox::warning(this, tr("Warning"), tr("get port set info failed!"));//��ȡ��λ���˿�������Ϣʧ��!���������ã�
	}

	initValveStatus();      //��ʼ������״̬
	initRegulateStatus();   //��ʼ�����ڷ�״̬

	m_paraSetDlg = NULL;
	m_paraSetReader = new ParaSetReader(); //���������ýӿ�

	m_readComConfig = NULL;
	m_readComConfig = new ReadComConfig();
	m_readComConfig->getBalancePara(m_balMaxWht, m_balBottomWht); //��ȡ��ƽ��������ͻ�ˮ����

	m_tempObj = NULL;
	m_tempTimer = NULL;
	initTemperatureCom();	 //��ʼ����·�¶Ȳɼ�����

	m_stdTempObj = NULL;
	m_stdTempTimer = NULL;
	initStdTemperatureCom(); //��ʼ����׼�¶Ȳɼ�����

	m_controlObj = NULL;
	m_setRegularTimer = NULL;
	m_openRegulateTimes = 0;
	initControlCom();		//��ʼ�����ƴ���

	m_balanceObj = NULL;
	initBalanceCom();		//��ʼ����ƽ����

	m_meterObj = NULL;
	initComOfHeatMeter();	//��ʼ����������

	//����������
	m_totalcount = 0;
	m_startWeight = 0.0;
	m_endWeight = 0.0;
	memset(m_deltaWeight, 0, sizeof(float)*FLOW_SAMPLE_NUM);
	m_flowRateTimer = new QTimer();
	connect(m_flowRateTimer, SIGNAL(timeout()), this, SLOT(slotFreshFlowRate()));
	m_flowRateTimer->start(TIMEOUT_FLOW_SAMPLE);

	m_oldCoe = new MeterCoe_STR;
	memset(m_oldCoe, 0, sizeof(MeterCoe_STR));

	/********************************************/
	m_instantFlowCom = NULL;
	m_instSTDMeterTimer = NULL;
	initInstStdCom();//��ʼ��˲ʱ��������

	m_accumulateFlowCom = NULL;
	m_accumSTDMeterTimer = NULL;
	initAccumStdCom();//��ʼ���ۻ���������
	/*********************************************/
}

//˲ʱ�����ɼ�����, ��λ��ֱ�Ӳɼ�
void DataTestDlg::initInstStdCom()
{
	ComInfoStruct InstStdCom = m_readComConfig->ReadInstStdConfig();
	m_instantFlowCom = new lcModRtuComObject();
	m_instantFlowCom->moveToThread(&m_instantFlowThread);
	m_instantFlowThread.start();
	m_instantFlowCom->openLcModCom(&InstStdCom);

	connect(m_instantFlowCom, SIGNAL(lcModValueIsReady(const QByteArray &)), this, SLOT(slotGetInstStdMeterPulse(const QByteArray &)));

	if (m_instSTDMeterTimer == NULL)
		m_instSTDMeterTimer = new QTimer();

	connect(m_instSTDMeterTimer, SIGNAL(timeout()), this, SLOT(slotAskInstPulse()));
	m_instSTDMeterTimer->start(TIMEOUT_STD_INST);
}
//�ۼ������ɼ�����, ��λ��ֱ�Ӳɼ�
void DataTestDlg::initAccumStdCom()
{
	ComInfoStruct AccumStdCom = m_readComConfig->ReadAccumStdConfig();
	m_accumulateFlowCom = new lcModRtuComObject();
	m_accumulateFlowCom->moveToThread(&m_accumFlowThread);
	m_accumFlowThread.start();
	m_accumulateFlowCom->openLcModCom(&AccumStdCom);

	connect(m_accumulateFlowCom, SIGNAL(lcModValueIsReady(const QByteArray &)), this, SLOT(slotGetAccumStdMeterPulse(const QByteArray &)));

	if (m_accumSTDMeterTimer == NULL)
		m_accumSTDMeterTimer = new QTimer();

	connect(m_accumSTDMeterTimer, SIGNAL(timeout()), this, SLOT(slotAskAccumPulse()));
	m_accumSTDMeterTimer->start(TIMEOUT_STD_ACCUM);
}

void DataTestDlg::slotAskInstPulse()
{
	bool ok;
	uchar address = (uchar)m_stdParam->value("DevNo./InstDevNo").toString().toInt(&ok, 16);
	m_instantFlowCom->ask901712RoutesCmd(address);
}

void DataTestDlg::slotAskAccumPulse()
{
	bool ok;
	uchar address = (uchar)m_stdParam->value("DevNo./AccumDevNo").toString().toInt(&ok, 16);
	m_accumulateFlowCom->ask9150A16RoutesCmd(address);
}

/*
** ����һ�����̣߳����¶Ȳɼ�����
*/
void DataTestDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadTempConfig();
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer();
	//connect(m_tempTimer, SIGNAL(timeout()), m_tempObj, SLOT(writeTemperatureComBuffer()));
	connect(m_tempTimer, SIGNAL(timeout()), this, SLOT(slotAskPipeTemperature()));
// 	connect(m_tempTimer, SIGNAL(timeout()), this, SLOT(slotFreshFlow()));
	
	m_tempTimer->start(TIMEOUT_PIPE_TEMPER); //���������¶�
}

void DataTestDlg::slotAskPipeTemperature()
{
	m_tempObj->writeTemperatureComBuffer();
}

/*
** ����һ�����̣߳��򿪱�׼�¶Ȳɼ�����
*/
void DataTestDlg::initStdTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadStdTempConfig();
	m_stdTempObj = new StdTempComObject();
	QSettings stdconfig(getFullIniFileName("stdplasensor.ini"), QSettings::IniFormat);
	m_stdTempObj->moveToThread(&m_stdTempThread);
	m_stdTempThread.start();
	m_stdTempObj->openTemperatureCom(&tempStruct); //�ȴ򿪴��ڣ�Ȼ�������ñ�׼�¶ȼƵ�Э��汾
	m_stdTempObj->setStdTempVersion(stdconfig.value("in_use/model").toInt());
	connect(m_stdTempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshStdTempValue(const QString &)));

	m_stdTempCommand = stdTempR1;
	m_stdTempTimer = new QTimer();
	connect(m_stdTempTimer, SIGNAL(timeout()), this, SLOT(slotAskStdTemperature()));
	
 	m_stdTempTimer->start(TIMEOUT_STD_TEMPER);
}

void DataTestDlg::slotAskStdTemperature()
{
	m_stdTempObj->writeStdTempComBuffer(m_stdTempCommand);
}

//��ƽ�ɼ����� ��λ��ֱ�Ӳɼ�
void DataTestDlg::initBalanceCom()
{
	ComInfoStruct balanceStruct = m_readComConfig->ReadBalanceConfig();
	m_balanceObj = new BalanceComObject();
	m_balanceObj->setBalanceType(m_readComConfig->getBalanceType());
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

	//��ƽ��ֵ����λ��ֱ��ͨ����ƽ���ڲɼ�
	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const float &)), this, SLOT(slotFreshBalanceValue(const float &)));
}

/*
** ����һ�����̣߳��򿪿��ư�ͨѶ����
*/
void DataTestDlg::initControlCom()
{
	ComInfoStruct valveStruct = m_readComConfig->ReadValveConfig();
	m_controlObj = new ControlComObject();
	m_controlObj->setProtocolVersion(m_portsetinfo.version); //����Э��汾
	m_controlObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_controlObj->openControlCom(&valveStruct);

	connect(m_controlObj, SIGNAL(controlRelayIsOk(const UINT8 &, const bool &)), this, SLOT(slotSetValveBtnStatus(const UINT8 &, const bool &)));
	connect(m_controlObj, SIGNAL(controlRegulateIsOk()), this, SLOT(slotSetRegulateOk()));
	 
	/*****************************************************************************************************/
	m_maxRateGetted = false;
	ui.lnEditTargetRate->setReadOnly(false);
	m_setRegularTimer = new QTimer;
	connect(m_setRegularTimer, SIGNAL(timeout()), this, SLOT(slotSetRegulate()));
	/*****************************************************************************************************/
	//��ƽ��ֵ�ӿ��ư��ȡ
// 	connect(m_controlObj, SIGNAL(controlGetBalanceValueIsOk(const float&)), this, SLOT(slotFreshBalanceValue(const float &)));
}

void DataTestDlg::on_lnEditMaxRate_returnPressed()
{
	QString str = ui.lnEditMaxRate->text();
	QRegExp rx("\\d+.\\d*");//ƥ��������С��
	if (rx.exactMatch(str))
	{
		m_maxRate = str.toFloat();
		m_maxRateGetted = true;
		qCritical()<<"max flow rate setted: " << m_maxRate;
		if (m_setRegularTimer->isActive())
			m_setRegularTimer->stop();
	}
}

void DataTestDlg::on_lnEditTargetRate_returnPressed()
{						   
	if (!m_maxRateGetted)
	{
		QMessageBox::warning(this, tr("MaxRate"), tr("please set maxRate first!"));
		return;
	}
	if (!m_nowRegNo)
	{
		m_nowRegNo = m_portsetinfo.regflow1No;
	}
	m_pre_error = 0.0;
	m_integral = 0.0;
	QString str = ui.lnEditTargetRate->text();
	QRegExp rx("\\d+.\\d*");//ƥ��������С��
	if (rx.exactMatch(str))
	{
		float target = str.toFloat();
		if (target > m_maxRate)
		{
			QMessageBox::warning(this, tr("Too Large"), tr("setted rate is greater than maxRate, exit!"));
			qCritical() <<"setted rate is greater than maxRate, exit!";
			return;
		}

		if (m_setRegularTimer->isActive())
			m_setRegularTimer->stop();

		qCritical() <<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ starting m_setRegularTimer $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
		m_controlObj->askControlRegulate(m_nowRegNo, 99);
		m_controlObj->askControlWaterPump(m_portsetinfo.pumpNo, true);//�趨Ŀ������, ��ˮ��
		m_setRegularTimer->start(WAIT_REG_TIME);
	}
}

void DataTestDlg::slotSetRegulate()
{
	this->setRegulate(ui.lcdStdMeterFlowRate->value(), ui.lnEditTargetRate->text().toFloat());
}

void DataTestDlg::setRegulate(float currentRate, float targetRate)
{
	qCritical() << "current Rate : " << currentRate;
	qCritical() << "target Rate : " << targetRate;
	qCritical() << "current regular number: " << m_nowRegNo;
	qCritical() << "current waitting time: "  << WAIT_REG_TIME;
	//���currentRate��0, ��ô�����綯����m_degree
	//�������5��, currentRate����0, ��ô��ʾ�û����ֶ���
	if (currentRate <=0.0f)
	{
		qCritical() << "current m_openRegulateTimes: " <<m_openRegulateTimes;
		if (m_openRegulateTimes >= 5)
		{
			QMessageBox::warning(this, tr("Open Valve"), tr("please open Manual Ball Valve"));
			stopSetRegularTimer();
			return;
		}
		m_controlObj->askControlRegulate(m_nowRegNo, m_degree);
		m_openRegulateTimes++;
		return;
	}
	
	float deltaV = qAbs(targetRate - currentRate);
	m_degree = degreeGet(currentRate, targetRate);
	qCritical() << "current degree: " << m_degree;
	m_controlObj->askControlRegulate(m_nowRegNo, m_degree);
	qCritical() << "%%%%%%% regular setted %%%%%%%";
	if (deltaV <= PRECISION)
	{
		//stopSetRegularTimer();
		//m_controlObj->askControlWaterPump(m_portsetinfo.pumpNo, false);//����Ŀ������, �ر�ˮ��
		qCritical() << "\n######################################gain target rate.######################################\n";
		
	}
}

int DataTestDlg::degreeGet(float currentRate, float targetRate)
{
	m_curr_error = targetRate - currentRate;
	m_integral += m_curr_error*WAIT_SECOND;
	float derivative = (m_curr_error - m_pre_error)/WAIT_SECOND;
	float output = Kp*m_curr_error + Ki*m_integral + Kd*derivative;
	qCritical() << "Kp:--" <<Kp<<" Ki:--"<<Ki<<" Kd:--"<<Kd<<" maxRate:--"<<m_maxRate;
	qCritical() << "P:--" <<Kp*m_curr_error<<" I:--"<<Ki*m_integral<<" D:--"<<Kd*derivative;
	qCritical() <<"m_pre_error:--"<<m_pre_error<< "m_curr_error:--" <<m_curr_error<<" m_integral:--"<<m_integral<<" derivative:--"<<derivative;
	qCritical() << "oooooutput: " << output;
	m_pre_error = m_curr_error;
	int outdegree =  (int)(output>0 ? output: 0);
	if (outdegree > 99)
	{
		outdegree = 99;
	}

	return outdegree;
}

void DataTestDlg::stopSetRegularTimer()
{
	if (m_setRegularTimer->isActive())
	{
		m_setRegularTimer->stop();
		qDebug() << "m_setRegularTimer stoped";
	}
}

//��������ͨѶ
void DataTestDlg::initComOfHeatMeter()
{
	m_meterObj = new MeterComObject();
	int version = m_paraSetReader->getParams()->m_pickcode;
	m_meterObj->setProtocolVersion(version);//����Э��汾��
	m_meterObj->moveToThread(&m_meterThread);
	m_meterThread.start();

	connect(m_meterObj, SIGNAL(readMeterNoIsOK(const QString&, const QString&)), this, SLOT(slotFreshMeterNo(const QString&, const QString&)));
	connect(m_meterObj, SIGNAL(readMeterFlowIsOK(const QString&, const QString&)), this, SLOT(slotFreshMeterFlow(const QString&, const QString&)));
	connect(m_meterObj, SIGNAL(readMeterHeatIsOK(const QString&, const QString&)), this, SLOT(slotFreshMeterHeat(const QString&, const QString&)));
	connect(m_meterObj, SIGNAL(readMeterDateIsOK(const QString&, const QString&)), this, SLOT(slotFreshMeterDate(const QString&, const QString&)));
	connect(m_meterObj, SIGNAL(readMeterTemperIsOK(const QString&, const QString&, const QString&)), \
		this, SLOT(slotFreshMeterTemper(const QString&, const QString&, const QString&)));
	connect(m_meterObj, SIGNAL(readMeterBigCoeIsOK(const QString&, const QString&)), \
		this, SLOT(slotFreshBigCoe(const QString&, const QString&)));
	connect(m_meterObj, SIGNAL(readMeterMid2CoeIsOK(const QString&, const QString&)), \
		this, SLOT(slotFreshMid2Coe(const QString&, const QString&)));
	connect(m_meterObj, SIGNAL(readMeterMid1CoeIsOK(const QString&, const QString&)), \
		this, SLOT(slotFreshMid1Coe(const QString&, const QString&)));
	connect(m_meterObj, SIGNAL(readMeterSmallCoeIsOK(const QString&, const QString&)), \
		this, SLOT(slotFreshSmallCoe(const QString&, const QString&)));

	QStringList cfgList = m_readComConfig->ReadIndexByName(meter(1));
	ui.portNameComboBox->setCurrentIndex(cfgList.at(0).toInt());
	ui.baudRateComboBox->setCurrentIndex(cfgList.at(1).toInt());
	ui.dataBitsComboBox->setCurrentIndex(cfgList.at(2).toInt());
	ui.parityComboBox->setCurrentIndex(cfgList.at(3).toInt());
	ui.stopBitsComboBox->setCurrentIndex(cfgList.at(4).toInt());

	ui.btnOpenCom->setEnabled(true);
	ui.btnCloseCom->setEnabled(false);
	setMeterComboxEnabled(true);
	setMeterOperBtnEnabled(false);
	clearMeterDispInfo();
}

//��ʼ������״̬
void DataTestDlg::initValveStatus()
{
	m_nowPortNo = 0;

	//�˿ں�-���Ű�ť ӳ���ϵ
	m_valveBtn[m_portsetinfo.bigNo] = ui.btnValveBig;
	m_valveBtn[m_portsetinfo.smallNo] = ui.btnValveSmall;
	m_valveBtn[m_portsetinfo.middle1No] = ui.btnValveMiddle1;
	m_valveBtn[m_portsetinfo.middle2No] = ui.btnValveMiddle2;
	m_valveBtn[m_portsetinfo.waterInNo] = ui.btnWaterIn;
	m_valveBtn[m_portsetinfo.waterOutNo] = ui.btnWaterOut;
	m_valveBtn[m_portsetinfo.pumpNo] = ui.btnWaterPump; //ˮ��

	//�˿ں�-����״̬ ȫ������״̬Ϊ�ر�
	m_valveStatus[m_portsetinfo.bigNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.smallNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle1No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle2No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterOutNo] = VALVE_CLOSE;
	//�˿ں�-ˮ��״̬ ��ʼΪ�ر�
	m_valveStatus[m_portsetinfo.pumpNo] = VALVE_CLOSE;

	setValveBtnBackColor(m_valveBtn[m_portsetinfo.bigNo], m_valveStatus[m_portsetinfo.bigNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.smallNo], m_valveStatus[m_portsetinfo.smallNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle1No], m_valveStatus[m_portsetinfo.middle1No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle2No], m_valveStatus[m_portsetinfo.middle2No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterInNo], m_valveStatus[m_portsetinfo.waterInNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterOutNo], m_valveStatus[m_portsetinfo.waterOutNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.pumpNo], m_valveStatus[m_portsetinfo.pumpNo]); //ˮ��
}

//��ʼ�����ڷ�״̬
void DataTestDlg::initRegulateStatus()
{
	m_nowRegNo = 0;

	//�˿ں�-���ڷ���ť ӳ���ϵ
	m_regBtn[m_portsetinfo.regflow1No] = ui.btnRegulate1;

	//���ڷ���ʼ״̬
	m_regStatus[m_portsetinfo.regflow1No] = REG_SUCCESS;

	setRegBtnBackColor(m_regBtn[m_portsetinfo.regflow1No], m_regStatus[m_portsetinfo.regflow1No]);
}

//��������ͨѶ����
void DataTestDlg::on_btnOpenCom_clicked()
{
	ComInfoStruct comStruct;
	comStruct.portName = ui.portNameComboBox->currentText();
	comStruct.baudRate = ui.baudRateComboBox->currentText().toInt();
	comStruct.dataBit = ui.dataBitsComboBox->currentText().toInt();
	comStruct.parity = ui.parityComboBox->currentIndex();
	comStruct.stopBit = ui.stopBitsComboBox->currentIndex();
	if (!m_meterObj->openMeterCom(&comStruct))
	{
		return; //���ȱ�ͨѶ����ʧ��
	}

	ui.btnOpenCom->setEnabled(false);
	ui.btnCloseCom->setEnabled(true);
	setMeterOperBtnEnabled(true);
	setMeterComboxEnabled(false);
}

//�ر�������ͨѶ����
void DataTestDlg::on_btnCloseCom_clicked()
{
	m_meterObj->closeMeterCom();

	ui.btnOpenCom->setEnabled(true);
	ui.btnCloseCom->setEnabled(false);
	setMeterOperBtnEnabled(false);
	setMeterComboxEnabled(true);
}

/*
** ���Ƽ̵�������
*/
void DataTestDlg::on_btnWaterIn_clicked() //��ˮ��
{
	m_nowPortNo = m_portsetinfo.waterInNo;
	m_controlObj->askControlRelay(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
}

void DataTestDlg::on_btnWaterOut_clicked() //��ˮ��
{
	m_nowPortNo = m_portsetinfo.waterOutNo;
	m_controlObj->askControlRelay(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
}

void DataTestDlg::on_btnValveBig_clicked() //��������
{
	m_nowPortNo = m_portsetinfo.bigNo;
	m_controlObj->askControlRelay(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
	m_maxRateGetted = false;
}

void DataTestDlg::on_btnValveMiddle1_clicked() //����һ��
{
	m_nowPortNo = m_portsetinfo.middle1No;
	m_controlObj->askControlRelay(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
	m_maxRateGetted = false;
}

void DataTestDlg::on_btnValveMiddle2_clicked() //��������
{
	m_nowPortNo = m_portsetinfo.middle2No;
	m_controlObj->askControlRelay(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
	m_maxRateGetted = false;
}

void DataTestDlg::on_btnValveSmall_clicked() //С������
{
	m_nowPortNo = m_portsetinfo.smallNo;
	m_controlObj->askControlRelay(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
	m_maxRateGetted = false;
}

/*
** ����ˮ�ÿ���
*/
void DataTestDlg::on_btnWaterPump_clicked() //ˮ��
{
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->askControlWaterPump(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
}

//����Ƶ��
void DataTestDlg::on_btnSetFreq_clicked()
{
	m_controlObj->askSetDriverFreq(ui.spinBoxFreq->value());
}

//���ڷ�
void DataTestDlg::on_btnRegulate1_clicked() //���ڷ�1
{
	m_nowRegNo = m_portsetinfo.regflow1No;
	setRegBtnBackColor(m_regBtn[m_nowRegNo], false); //��ʼ�����ڷ�����ɫ
	m_controlObj->askControlRegulate(m_nowRegNo, ui.spinBoxValveOpening->value());
}

void DataTestDlg::on_btnRegulate2_clicked() //���ڷ�2
{
	m_nowRegNo = m_portsetinfo.regflow2No;
	setRegBtnBackColor(m_regBtn[m_nowRegNo], false); //��ʼ�����ڷ�����ɫ
	m_controlObj->askControlRegulate(m_nowRegNo, ui.spinBoxValveOpening2->value());
}

//��������
void DataTestDlg::on_btnParaSet_clicked()
{
	if (NULL == m_paraSetDlg)
	{
		m_paraSetDlg = new ParaSetDlg();
	}
	else
	{
		delete m_paraSetDlg;
		m_paraSetDlg = new ParaSetDlg();
	}
	m_paraSetDlg->show();
}

void DataTestDlg::on_btnExit_clicked()
{
	this->close();
}

//�ɼ���׼�¶�
void DataTestDlg::on_btnStdTempCollect_clicked()
{
	m_stdTempTimer->start(TIMEOUT_STD_TEMPER);
}

//ֹͣ�ɼ���׼�¶�
void DataTestDlg::on_btnStdTempStop_clicked()
{
	m_stdTempTimer->stop();
}

void DataTestDlg::on_lnEditInStdResist_textChanged(const QString & text)
{
	float resis = text.toFloat();
	float temp = calcTemperByResis(resis);
	ui.lnEditInStdTemp->setText(QString::number(temp));
}

void DataTestDlg::on_lnEditOutStdResist_textChanged(const QString & text)
{
	float resis = text.toFloat();
	float temp = calcTemperByResis(resis);
	ui.lnEditOutStdTemp->setText(QString::number(temp));
}

//ˢ���¶�
void DataTestDlg::slotFreshComTempValue(const QString& tempStr)
{
	ui.lnEditTempIn->setText(tempStr.left(TEMPER_DATA_WIDTH));   //����¶� PV
	ui.lnEditTempOut->setText(tempStr.right(TEMPER_DATA_WIDTH)); //�����¶� SV
}

//ˢ�±�׼�¶�
void DataTestDlg::slotFreshStdTempValue(const QString& stdTempStr)
{
// 	qDebug()<<"stdTempStr ="<<stdTempStr<<"; m_stdTempCommand ="<<m_stdTempCommand;
	switch (m_stdTempCommand)
	{
	case stdTempR1: 
		ui.lnEditInStdResist->setText(stdTempStr);
		m_stdTempCommand = stdTempR2;
		break;
	case stdTempR2: 
		ui.lnEditOutStdResist->setText(stdTempStr);
		m_stdTempCommand = stdTempR1;
		break;
	default:
		break;
	}
}

//ˢ����ƽ��ֵ
void DataTestDlg::slotFreshBalanceValue(const float& balValue)
{
	ui.lnEditBigBalance->setText(QString::number(balValue, 'f', 3));
	
	if (balValue > m_balMaxWht) //��ֹ��ƽ���
	{
		m_controlObj->askControlRelay(m_portsetinfo.waterOutNo, VALVE_OPEN);// �򿪷�ˮ��	
		m_controlObj->askControlRelay(m_portsetinfo.waterInNo, VALVE_CLOSE);// �رս�ˮ��
		if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
		{
			slotSetValveBtnStatus(m_portsetinfo.waterOutNo, VALVE_OPEN);
			slotSetValveBtnStatus(m_portsetinfo.waterInNo, VALVE_CLOSE);
		}
	}
}

//��Ӧ����״̬���óɹ�
void DataTestDlg::slotSetValveBtnStatus(const UINT8 &portno, const bool &status)
{
	m_valveStatus[portno] = status;
	setValveBtnBackColor(m_valveBtn[portno], m_valveStatus[portno]);
}

//��Ӧ���ڷ����ڳɹ�
void DataTestDlg::slotSetRegulateOk()
{
	setRegBtnBackColor(m_regBtn[m_nowRegNo], REG_SUCCESS);
}

//���÷��Ű�ť����ɫ
void DataTestDlg::setValveBtnBackColor(QPushButton *btn, bool status)
{
	if (NULL == btn)
	{
		return;
	}
	if (status) //���Ŵ� ��ɫ
	{
		btn->setStyleSheet("background-color:rgb(0,255,0);"); 
	}
	else //���Źر� ��ɫ
	{
		btn->setStyleSheet("background-color:rgb(255,0,0);border:0px;border-image: url(:/datatestdlg/images/close.png);"); 
	}
}

//���õ��ڷ���ť����ɫ
void DataTestDlg::setRegBtnBackColor(QPushButton *btn, bool status)
{
	if (NULL == btn)
	{
		return;
	}
	if (status) //���ڳɹ�
	{
// 		btn->setStyleSheet("background:rgb(0,255,0);border-image: url(:/datatestdlg/images/success.png);");
	}
	else //����ʧ��
	{
// 		btn->setStyleSheet("background:rgb(255,0,0);border-image: url(:/datatestdlg/images/failed.png);");
	}
}


/*
** ��������(ÿ1�����һ����ƽ�仯ֵ������ǰ10���ƽ������)
*/
void DataTestDlg::slotFreshFlowRate()
{
	if (m_totalcount > 4294967290) //��ֹm_totalcount��� 32λ�޷���������Χ0~4294967295
	{
		m_totalcount = 0;
		m_startWeight = 0.0;
		m_endWeight = 0.0;
		memset(m_deltaWeight, 0, sizeof(float)*FLOW_SAMPLE_NUM);
	}
	if (m_totalcount == 0) //��¼��ƽ��ʼ����
	{
		m_startWeight = ui.lnEditBigBalance->text().replace(" ", 0).toFloat();
		m_totalcount ++;
		return;
	}

	float flowValue = 0.0;
	float totalWeight = 0.0;
	m_endWeight = ui.lnEditBigBalance->text().replace(" ", 0).toFloat();//ȡ��ǰ��ƽֵ, ��Ϊ��ǰ�������ֵ
	float delta_weight = m_endWeight - m_startWeight;
	m_deltaWeight[m_totalcount%FLOW_SAMPLE_NUM] = delta_weight;
// 	qWarning()<<"m_totalcount ="<<m_totalcount;
	for (int i=0; i<FLOW_SAMPLE_NUM; i++)
	{
		totalWeight += m_deltaWeight[i];
// 		qWarning()<<"totalWeight ="<<totalWeight<<", m_deltaWeight["<<i<<"] ="<<m_deltaWeight[i];
	}
	flowValue = 3.6*(totalWeight)*1000/(FLOW_SAMPLE_NUM*TIMEOUT_FLOW_SAMPLE);//���ۻ�ˮ��/��ʱ��  (��/Сʱ, t/h, m3/h)
//	flowValue = (totalWeight)*1000/(FLOW_SAMPLE_NUM*TIMEOUT_FLOW_SAMPLE);// kg/s
// 	qDebug()<<"flowValue ="<<flowValue;
	ui.lnEditFlowRate->setText(QString::number(flowValue, 'f', 3)); //��ui.lnEditFlowRate����ʾ����
	m_totalcount ++;//�������ۼ�
	m_startWeight = m_endWeight;//����ǰֵ����, ��Ϊ�´�����ĳ�ֵ
}

void DataTestDlg::clearMeterDispInfo()
{
	ui.lnEditMeterNo->clear();
	ui.lnEditMeterTempIn->clear();
	ui.lnEditMeterTempOut->clear();
	ui.lnEditMeterTotalFlow->clear();
	ui.lnEditMeterHeat->clear();
	ui.dateEditMeter->setDate(QDate(2000,1,1));
	ui.lnEditBigOldError->clear();
	ui.lnEditBigOldCoe->clear();
	ui.lnEditBigOrgCoe->clear();
	ui.lnEditMid2OldError->clear();
	ui.lnEditMid2OldCoe->clear();
	ui.lnEditMid2OrgCoe->clear();
	ui.lnEditMid1OldError->clear();
	ui.lnEditMid1OldCoe->clear();
	ui.lnEditMid1OrgCoe->clear();
	ui.lnEditSmallOldError->clear();
	ui.lnEditSmallOldCoe->clear();
	ui.lnEditSmallOrgCoe->clear();
}

//���ü춨״̬
void DataTestDlg::on_btnSetVerifyStatus_clicked()
{
	qDebug()<<"���ý���춨״̬...";
	m_meterObj->askSetVerifyStatus(); //���ý���춨״̬
}

//��������
void DataTestDlg::on_btnReadMeterData_clicked()
{
	clearMeterDispInfo();
	qDebug()<<"���� ��ʼ...";
 	m_meterObj->askReadMeterData(); //�������
}

//�޸ı��
void DataTestDlg::on_btnModifyMeterNo_clicked()
{
	QString oldMeterNo = ui.lnEditMeterNo->text();
	QString newMeterNo = ui.lnEditNewMeterNo->text();
	if (oldMeterNo.isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("MeterNO. is empty! please read meter first!"));
		return;
	}
	if (newMeterNo.isEmpty() || newMeterNo.size()!=2*CJ188_ADDR_LEN)
	{
		QMessageBox::warning(this, tr("Warning"), tr("new NO. is error!\nplease input 14 bits meter number!"));
		ui.lnEditNewMeterNo->setFocus();
		return;
	}

	m_meterObj->askModifyMeterNO(oldMeterNo, newMeterNo); //�����޸ı��
}

//�޸�����ϵ��
void DataTestDlg::on_btnModifyFlowCoe_clicked()
{
	QString meterNO = ui.lnEditMeterNo->text();
	if (meterNO.isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("MeterNO. is empty! please read meter first!"));
		return;
	}
	bool ok;
	float bigErr = ui.lnEditBigNewError->text().toFloat(&ok);
	if (!ok || ui.lnEditBigNewError->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("err is error! please input err first!"));
		return;
	}
	float mid2Err = ui.lnEditMid2NewError->text().toFloat();
	if (!ok || ui.lnEditMid2NewError->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("err is error! please input err first!"));
		return;
	}
	float mid1Err = ui.lnEditMid1NewError->text().toFloat();
	if (!ok || ui.lnEditMid1NewError->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("err is error! please input err first!"));
		return;
	}
	float smallErr = ui.lnEditSmallNewError->text().toFloat();
	if (!ok || ui.lnEditSmallNewError->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("err is error! please input err first!"));
		return;
	}
	m_meterObj->askModifyFlowCoe(meterNO, bigErr, mid2Err, mid1Err, smallErr);
}

//�����޸�����ϵ��
void DataTestDlg::on_btn2ModifyFlowCoe_clicked()
{
	QString meterNO = ui.lnEditMeterNo->text();
	if (meterNO.isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("MeterNO. is empty! please read meter first!"));
		return;
	}
	bool ok;
	float bigErr = ui.lnEditBigNewError->text().toFloat(&ok);
	if (!ok || ui.lnEditBigNewError->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("err is error! please input err first!"));
		return;
	}
	float mid2Err = ui.lnEditMid2NewError->text().toFloat(&ok);
	if (!ok || ui.lnEditMid2NewError->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("err is error! please input err first!"));
		return;
	}
	float mid1Err = ui.lnEditMid1NewError->text().toFloat(&ok);
	if (!ok || ui.lnEditMid1NewError->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("err is error! please input err first!"));
		return;
	}
	float smallErr = ui.lnEditSmallNewError->text().toFloat(&ok);
	if (!ok || ui.lnEditSmallNewError->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("err is error! please input err first!"));
		return;
	}

	m_oldCoe->bigCoe = ui.lnEditBigOldCoe->text().toFloat(&ok);
	if (!ok || ui.lnEditBigOldCoe->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("oldCoe is empty! please read meter first!"));
		return;
	}
	m_oldCoe->mid2Coe = ui.lnEditMid2OldCoe->text().toFloat(&ok);
	if (!ok || ui.lnEditMid2OldCoe->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("oldCoe is empty! please read meter first!"));
		return;
	}
	m_oldCoe->mid1Coe = ui.lnEditMid1OldCoe->text().toFloat(&ok);
	if (!ok || ui.lnEditMid1OldCoe->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("oldCoe is empty! please read meter first!"));
		return;
	}
	m_oldCoe->smallCoe = ui.lnEditSmallOldCoe->text().toFloat(&ok);
	if (!ok || ui.lnEditSmallOldCoe->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("oldCoe is empty! please read meter first!"));
		return;
	}
	m_meterObj->askModifyFlowCoe(meterNO, bigErr, mid2Err, mid1Err, smallErr, m_oldCoe);
}

//��Ӧ��ȡ��ųɹ�
void DataTestDlg::slotFreshMeterNo(const QString& comName, const QString& meterNo)
{
	ui.lnEditMeterNo->setText(meterNo);
	qDebug()<<"��ȡ��� �ɹ�...";
}

//��Ӧ��ȡ�������ɹ�
void DataTestDlg::slotFreshMeterFlow(const QString& comName, const QString& flow)
{
	ui.lnEditMeterTotalFlow->setText(flow);
	qDebug()<<"��ȡ������ �ɹ�...";
}

//��Ӧ��ȡ�������ɹ�
void DataTestDlg::slotFreshMeterHeat(const QString& comName, const QString& heat)
{
	ui.lnEditMeterHeat->setText(heat);
	qDebug()<<"��ȡ������ �ɹ�...";
}

//��Ӧ��ȡ�����ڳɹ�
void DataTestDlg::slotFreshMeterDate(const QString& comName, const QString& date)
{
	ui.dateEditMeter->setDate(QDate::fromString(date, "yyyyMMdd"));
	qDebug()<<"��ȡ������ �ɹ�...";
}

//��Ӧ��ȡ�����ˮ�¶ȳɹ�
void DataTestDlg::slotFreshMeterTemper(const QString& comName, const QString& tempIn, const QString& tempOut)
{
	ui.lnEditMeterTempIn->setText(tempIn);
	ui.lnEditMeterTempOut->setText(tempOut);
	qDebug()<<"��ȡ�����ˮ�¶� �ɹ�...";
}

void DataTestDlg::slotFreshBigCoe(const QString& comName, const QString& bigCoe)
{
	ui.lnEditBigOrgCoe->setText(bigCoe);
	float bigCoeV = calcFloatValueOfCoe(bigCoe);
	ui.lnEditBigOldCoe->setText(QString::number(bigCoeV, 'f', ERR_PRECISION));
	float bigErr = calcErrorValueOfCoe(bigCoe);
	ui.lnEditBigOldError->setText(QString::number(bigErr, 'f', ERR_PRECISION));
	qDebug()<<"��ȡ������ϵ�� �ɹ�...";
}

void DataTestDlg::slotFreshMid2Coe(const QString& comName, const QString& mid2Coe)
{
	ui.lnEditMid2OrgCoe->setText(mid2Coe);
	float mid2CoeV = calcFloatValueOfCoe(mid2Coe);
	ui.lnEditMid2OldCoe->setText(QString::number(mid2CoeV, 'f', ERR_PRECISION));
	float mid2Err = calcErrorValueOfCoe(mid2Coe);
	ui.lnEditMid2OldError->setText(QString::number(mid2Err, 'f', ERR_PRECISION));
	qDebug()<<"��ȡ����2����ϵ�� �ɹ�...";
}

void DataTestDlg::slotFreshMid1Coe(const QString& comName, const QString& mid1Coe)
{
	ui.lnEditMid1OrgCoe->setText(mid1Coe);
	float mid1CoeV = calcFloatValueOfCoe(mid1Coe);
	ui.lnEditMid1OldCoe->setText(QString::number(mid1CoeV, 'f', ERR_PRECISION));
	float mid1Err = calcErrorValueOfCoe(mid1Coe);
	ui.lnEditMid1OldError->setText(QString::number(mid1Err, 'f', ERR_PRECISION));
	qDebug()<<"��ȡ����1����ϵ�� �ɹ�...";
}

void DataTestDlg::slotFreshSmallCoe(const QString& comName, const QString& smallCoe)
{
	ui.lnEditSmallOrgCoe->setText(smallCoe);
	float smallCoeV = calcFloatValueOfCoe(smallCoe);
	ui.lnEditSmallOldCoe->setText(QString::number(smallCoeV, 'f', ERR_PRECISION));
	float smallErr = calcErrorValueOfCoe(smallCoe);
	ui.lnEditSmallOldError->setText(QString::number(smallErr, 'f', ERR_PRECISION));
	qDebug()<<"��ȡС����ϵ�� �ɹ�...";
}

void DataTestDlg::setMeterComboxEnabled(bool flag)
{
	ui.portNameComboBox->setEnabled(flag);
	ui.baudRateComboBox->setEnabled(flag);
	ui.dataBitsComboBox->setEnabled(flag);
	ui.parityComboBox->setEnabled(flag);
	ui.stopBitsComboBox->setEnabled(flag);
}

void DataTestDlg::setMeterOperBtnEnabled(bool flag)
{
	ui.btnSetVerifyStatus->setEnabled(flag);
	ui.btnReadMeterData->setEnabled(flag);
	ui.btnModifyMeterNo->setEnabled(flag);
	ui.btnModifyFlowCoe->setEnabled(flag);
	ui.btn2ModifyFlowCoe->setEnabled(flag);
}


void DataTestDlg::slotGetInstStdMeterPulse(const QByteArray & valueArray)
{
	m_instStdPulse = valueArray;
	freshInstStdMeter();
	float instValue = 0.0;//˲ʱ����	
	instValue = ui.lcdInstStdMeter_3->value()+ui.lcdInstStdMeter_10->value()+ui.lcdInstStdMeter_25->value();
	ui.lcdStdMeterFlowRate->display(instValue);
}

int DataTestDlg::getRouteByWdg(flow_rate_wdg wdgIdx, flow_type fType)
{
	int route = -1;
	m_stdParam->beginReadArray("Route");
	m_stdParam->setArrayIndex(wdgIdx);
	switch(fType)
	{
	case INST_FLOW_VALUE:
		route = m_stdParam->value("InstRoute").toInt();
		break;
	case ACCUM_FLOW_VALUE:
		route = m_stdParam->value("AccumRoute").toInt();
		break;
	default:
		break;
	}	
	m_stdParam->endArray();
	return route;
}

float DataTestDlg::getStdUpperFlow(flow_rate_wdg wdgIdx)
{
	float upperFlow = 0.0f;

	m_stdParam->beginReadArray("Route");
	m_stdParam->setArrayIndex(wdgIdx);
	int diamWdg = m_stdParam->value("Diameter").toInt();//��ȡ�ܾ��Ĳ�����
	m_stdParam->endArray();

	m_stdParam->beginReadArray("FlowRate");
	m_stdParam->setArrayIndex(diamWdg);
	upperFlow = m_stdParam->value("UpperFlow").toFloat();
	m_stdParam->endArray();
	return upperFlow;
}

double DataTestDlg::getStdPulse(flow_rate_wdg wdgIdx)
{
	double pulse = 0.0f;
	m_stdParam->beginReadArray("Route");
	m_stdParam->setArrayIndex(wdgIdx);
	int diamWdg = m_stdParam->value("Diameter").toInt();//��ȡ�ܾ��Ĳ�����
	m_stdParam->endArray();

	m_stdParam->beginReadArray("Pulse");
	m_stdParam->setArrayIndex(diamWdg);
	pulse = m_stdParam->value("Pulse").toDouble();
	m_stdParam->endArray();
	return pulse;
}

void DataTestDlg::slotGetAccumStdMeterPulse(const QByteArray & valueArray)
{
	m_accumStdPulse = valueArray;
	freshAccumStdMeter();
	float accumValue = 0.0;//�ۻ�����	
	accumValue = ui.lcdAccumStdMeter_3->value()+ui.lcdAccumStdMeter_10->value()+ui.lcdAccumStdMeter_25->value();
	ui.lcdAccumStdMeter->display(accumValue);	
}

void DataTestDlg::freshInstStdMeter()
{
	ui.lcdInstStdMeter_25->display(getInstFlowRate(FLOW_RATE_BIG));
	ui.lcdInstStdMeter_10->display(getInstFlowRate(FLOW_RATE_MID_1));
	ui.lcdInstStdMeter_3->display(getInstFlowRate(FLOW_RATE_SMALL));
}

void DataTestDlg::freshAccumStdMeter()
{
	ui.lcdAccumStdMeter_25->display(getAccumFLowVolume(FLOW_RATE_BIG));
	ui.lcdAccumStdMeter_10->display(getAccumFLowVolume(FLOW_RATE_MID_1));
	ui.lcdAccumStdMeter_3->display(getAccumFLowVolume(FLOW_RATE_SMALL));
}

float DataTestDlg::getInstFlowRate(flow_rate_wdg idx)
{
	int route = getRouteByWdg(idx, INST_FLOW_VALUE);
	int count = get9017RouteI(route, m_instStdPulse);
	float upperFlow = getStdUpperFlow(idx);
	//qDebug() <<"valve:--"<<idx<<" count:--"<<count<<" upperFlow:--"<<upperFlow;
	return getInstStdValue(count, upperFlow);
}

float DataTestDlg::getAccumFLowVolume(flow_rate_wdg idx)
{
	int route = getRouteByWdg(idx, ACCUM_FLOW_VALUE);
	int count = get9150ARouteI(route, m_accumStdPulse);
	double pulse = getStdPulse(idx);
	//qDebug() <<"valve:--"<<idx<<" count:--"<<count<<" pulse:--"<<pulse;
	return count*pulse;
}