/***********************************************
**  �ļ���:     flowstandard50.cpp
**  ����:       �����춨(��׼����������-DN50��˫��ƽ��˫���ư�
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2015/11/27
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2015/11 ��һ��
**  ���ݰ���:
**  ˵��:		
**  ���¼�¼:   

***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QtSql/QSqlTableModel>
#include <QtGui/QFileDialog>
#include <QtCore/QSignalMapper>
#include <QCloseEvent>
#include <math.h>

#include "stdmtrcoecorrect.h"
#include "commondefine.h"
#include "algorithm.h"
#include "qtexdb.h"
#include "parasetdlg.h"
#include "readcomconfig.h"
#include "report.h"
#include "readstdmeter.h"

StdMtrCoeCorrect::StdMtrCoeCorrect(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"StdMtrCoeCorrect thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	ui.btnExhaust->hide();
	ui.btnGoOn->hide();

	if (!getPortSetIni(&m_portsetinfo)) //��ȡ��λ���˿ں�������Ϣ
	{
		QMessageBox::warning(this, tr("Warning"), tr("Warning:get port set info failed!"));
	}

	m_readComConfig = NULL;
	m_readComConfig = new ReadComConfig(); //���������ýӿڣ�������initBalanceComǰ���ã�

	m_balanceObj = NULL;
	initBalanceCom();		//��ʼ����ƽ����

	m_balanceObj2 = NULL;
	initBalanceCom2();		//��ʼ����ƽ����2

	m_tempObj = NULL;
	m_tempTimer = NULL;
	initTemperatureCom();	//��ʼ���¶Ȳɼ�����

	m_controlObj = NULL;
	initControlCom();		//��ʼ�����ƴ���

	m_controlObj2 = NULL;
	initControlCom2();		//��ʼ�����ƴ���2

	//������ӿ�
	m_chkAlg = NULL;
	m_chkAlg = new CAlgorithm();

	//ӳ���ϵ����ʼ������״̬	
	initValveStatus();      
	initRegulateStatus();

	m_exaustTimer = NULL;
	m_exaustTimer = new QTimer(this); //������ʱ��
	connect(m_exaustTimer, SIGNAL(timeout()), this, SLOT(slotExaustFinished()));

	m_stopFlag = true; //ֹͣ����־���˳�����󣬲��ټ����ƽ������

	m_avgTFCount = 1; //����ƽ���¶��õ��ۼӼ�����

	m_nowParams = NULL;
	m_exaustSecond = 45;     //Ĭ������ʱ��45��
	m_meterStartValue = 0.0;
	m_meterEndValue = 0.0;
	m_meterStdValue = 0.0;
	m_meterError = 0.0;
	m_stdStartVol = 0.0;
	m_stdEndVol = 0.0;
	m_StdStartMass = 0.0;
	m_StdEndMass = 0.0;
	m_timeStamp = "";
	m_nowDate = "";
	m_validDate = "";

	QSqlTableModel *model = new QSqlTableModel(this, g_defaultdb);  
	model->setTable("T_Meter_Standard");  
	model->select();  

	m_paraSetDlg = NULL;    //�������öԻ���
	m_paraSetReader = new ParaSetReader(); //���������ýӿ�
	if (!readNowParaConfig()) //��ȡ��ǰ�춨����
	{
		qWarning()<<"��ȡ���������ļ�ʧ��!";
	}

	ui.lcdInTemper->display(50);
	ui.lcdOutTemper->display(50);

	/***************��׼������***********************/
	m_mapInstWdg[FLOW_RATE_BIG]   = ui.lcdInstStdMeter_50;
	m_mapInstWdg[FLOW_RATE_MID_2] = ui.lcdInstStdMeter_25;
	m_mapInstWdg[FLOW_RATE_MID_1] = ui.lcdInstStdMeter_10;
	m_mapInstWdg[FLOW_RATE_SMALL] = ui.lcdInstStdMeter_3;

	m_mapAccumWdg[FLOW_RATE_BIG]   = ui.lcdAccumStdMeter_50;
	m_mapAccumWdg[FLOW_RATE_MID_2] = ui.lcdAccumStdMeter_25;
	m_mapAccumWdg[FLOW_RATE_MID_1] = ui.lcdAccumStdMeter_10;
	m_mapAccumWdg[FLOW_RATE_SMALL] = ui.lcdAccumStdMeter_3;
	m_stdMeterReader = NULL;
	m_stdMeterReader = new CStdMeterReader;
	m_stdMeterReader->mapInstWdg(&m_mapInstWdg, ui.lcdFlowRate);
	m_stdMeterReader->mapAccumWdg(&m_mapAccumWdg, ui.lcdVolume);
	m_stdMeterReader->startReadMeter();
	/***************��׼������end********************/
}

StdMtrCoeCorrect::~StdMtrCoeCorrect()
{
}

void StdMtrCoeCorrect::showEvent(QShowEvent * event)
{
	qDebug()<<"StdMtrCoeCorrect::showEvent";

	ui.tableWidget->setRowCount(18);
	ui.tableWidget->verticalHeader()->setVisible(false);
	for (int i=0; i<ui.tableWidget->rowCount(); i+=3)
	{
		ui.tableWidget->setSpan(i,0,3,1);
		ui.tableWidget->setSpan(i,8,3,1);
		ui.tableWidget->setSpan(i,9,3,1);
	}
}

void StdMtrCoeCorrect::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^StdMtrCoeCorrect::closeEvent";
	int button = QMessageBox::question(this, tr("Question"), tr("Exit Really ?"), \
		QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape);
	if (button == QMessageBox::No)
	{
		return event->ignore();
	}
	else
	{
		event->accept();
	}

	if (!m_stopFlag)
	{
		stopVerify();
	}
	openValve(m_portsetinfo.bigWaterOutNo);
	ui.labelHintPoint->clear();
	ui.labelHintProcess->setText(tr("release pipe pressure..."));
	openValve(m_portsetinfo.bigNo); //�򿪴������㷧�ţ��ͷŹ�·ѹ��
 	wait(RELEASE_PRESS_TIME); //�ȴ�2�룬�ͷŹ�·ѹ��
	closeValve(m_portsetinfo.bigNo);
	ui.labelHintProcess->clear();
	ui.btnStart->setEnabled(true);

	if (m_paraSetReader) //���춨����
	{
		delete m_paraSetReader;
		m_paraSetReader = NULL;
	}

	if (m_paraSetDlg)    //�������öԻ���
	{
		delete m_paraSetDlg;
		m_paraSetDlg = NULL;
	}

	if (m_readComConfig) //����������
	{
		delete m_readComConfig;
		m_readComConfig = NULL;
	}

	if (m_tempThread.isRunning())  // �¶Ȳɼ�
	{
		m_tempThread.exit(); //������־�л��о���"QThread: Destroyed while thread is still running"
		if (m_tempObj)
		{
			delete m_tempObj;
			m_tempObj = NULL; 
		}	 		 		
	}	   

	if (m_tempTimer) //�ɼ��¶ȼ�ʱ��
	{
		if (m_tempTimer->isActive())
		{
			m_tempTimer->stop();
		}
		delete m_tempTimer;
		m_tempTimer = NULL;
	}


	if (m_controlObj)  //���ſ���
	{
		delete m_controlObj;
		m_controlObj = NULL;

		m_valveThread.exit();
	}

	if (m_controlObj2)  //���ſ���2
	{
		delete m_controlObj2;
		m_controlObj2 = NULL;

		m_valveThread2.exit();
	}

	if (m_chkAlg)//������
	{
		delete m_chkAlg;
		m_chkAlg = NULL;
	}

	if (m_exaustTimer) //������ʱ��
	{
		if (m_exaustTimer->isActive())
		{
			m_exaustTimer->stop();
		}
		delete m_exaustTimer;
		m_exaustTimer = NULL;
	}

	//��ʱ�������ڶ�̬��ʾ���ڷ�����
	if (m_regSmallTimer)
	{
		if (m_regSmallTimer->isActive())
		{
			m_regSmallTimer->stop();
		}
		delete m_regSmallTimer;
		m_regSmallTimer = NULL;
	}

	if (m_regMid1Timer)
	{
		if (m_regMid1Timer->isActive())
		{
			m_regMid1Timer->stop();
		}
		delete m_regMid1Timer;
		m_regMid1Timer = NULL;
	}

	if (m_regMid2Timer)
	{
		if (m_regMid2Timer->isActive())
		{
			m_regMid2Timer->stop();
		}
		delete m_regMid2Timer;
		m_regMid2Timer = NULL;
	}

	if (m_regBigTimer)
	{
		if (m_regBigTimer->isActive())
		{
			m_regBigTimer->stop();
		}
		delete m_regBigTimer;
		m_regBigTimer = NULL;
	}

	if (m_stdMeterReader)
	{
		delete m_stdMeterReader;
		m_stdMeterReader = NULL;
	}

	emit signalClosed();
}

void StdMtrCoeCorrect::resizeEvent(QResizeEvent * event)
{
	qDebug()<<"StdMtrCoeCorrect::resizeEvent...";

	int th = ui.tableWidget->size().height();
	int tw = ui.tableWidget->size().width();
	int hh = ui.tableWidget->horizontalHeader()->size().height();
	int vw = ui.tableWidget->verticalHeader()->size().width();
	int vSize = (int)((th-hh-10)/ui.tableWidget->rowCount());
	int hSize = (int)((tw-vw-10)/ui.tableWidget->columnCount());
	ui.tableWidget->verticalHeader()->setDefaultSectionSize(vSize);
	ui.tableWidget->horizontalHeader()->setDefaultSectionSize(hSize);
}

//��ƽ�ɼ����� ��λ��ֱ�Ӳɼ�
void StdMtrCoeCorrect::initBalanceCom()
{
	ComInfoStruct balanceStruct = m_readComConfig->ReadBalanceConfig();
	m_balanceObj = new BalanceComObject();
	int type = m_readComConfig->getBalanceType();
	m_balanceObj->setBalanceType(type);
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

	//��ƽ��ֵ����λ��ֱ��ͨ����ƽ���ڲɼ�
	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const float &)), this, SLOT(slotFreshBigBalanceValue(const float &)));
}

//��ƽ�ɼ�����2 ��λ��ֱ�Ӳɼ�
void StdMtrCoeCorrect::initBalanceCom2()
{
	ComInfoStruct balanceStruct2 = m_readComConfig->ReadBalanceConfig2();
	m_balanceObj2 = new BalanceComObject();
	int type = m_readComConfig->getBalanceType2();
	m_balanceObj2->setBalanceType(type);
	m_balanceObj2->moveToThread(&m_balanceThread2);
	m_balanceThread2.start();
	m_balanceObj2->openBalanceCom(&balanceStruct2);

	//��ƽ��ֵ����λ��ֱ��ͨ����ƽ���ڲɼ�
	connect(m_balanceObj2, SIGNAL(balanceValueIsReady(const float &)), this, SLOT(slotFreshSmallBalanceValue(const float &)));
}

/*
** �¶Ȳɼ����� ��λ��ֱ�Ӳɼ�
** ��������
*/
void StdMtrCoeCorrect::initTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadTempConfig();
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer();
	connect(m_tempTimer, SIGNAL(timeout()), this, SLOT(slotAskPipeTemperature()));

	m_tempTimer->start(TIMEOUT_PIPE_TEMPER); //���������¶�
}

void StdMtrCoeCorrect::slotAskPipeTemperature()
{
	m_tempObj->writeTemperatureComBuffer();
}

//���ư�ͨѶ����
void StdMtrCoeCorrect::initControlCom()
{
	ComInfoStruct valveStruct = m_readComConfig->ReadValveConfig();
	m_controlObj = new ControlComObject();
	m_controlObj->setProtocolVersion(m_portsetinfo.version);
	m_controlObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_controlObj->openControlCom(&valveStruct);

	connect(m_controlObj, SIGNAL(controlRelayIsOk(const UINT8 &, const bool &)), this, SLOT(slotSetValveBtnStatus(const UINT8 &, const bool &)));
	connect(m_controlObj, SIGNAL(controlRegulateIsOk()), this, SLOT(slotSetRegulateOk()));
}

//���ư�ͨѶ����2
void StdMtrCoeCorrect::initControlCom2()
{
	ComInfoStruct valveStruct2 = m_readComConfig->ReadValveConfig2();
	m_controlObj2 = new ControlComObject();
	m_controlObj2->setProtocolVersion(m_portsetinfo.version);
	m_controlObj2->moveToThread(&m_valveThread2);
	m_valveThread2.start();
	m_controlObj2->openControlCom(&valveStruct2);

	connect(m_controlObj2, SIGNAL(controlRelayIsOk(const UINT8 &, const bool &)), this, SLOT(slotSetValveBtnStatus(const UINT8 &, const bool &)));
	connect(m_controlObj2, SIGNAL(controlRegulateIsOk()), this, SLOT(slotSetRegulateOk()));
}

/*
** �˿ں�-����ӳ���ϵ����ʼ������״̬��Ĭ�Ϸ��ų�ʼ״̬ȫ��Ϊ�ر�,ˮ�ó�ʼ״̬Ϊ�رգ�
** ��Ҫ�Ľ��ø������
*/
void StdMtrCoeCorrect::initValveStatus()
{
	m_nowPortNo = 0;

	//�˿ں�-���Ű�ť ӳ���ϵ
	m_valveBtn[m_portsetinfo.bigNo] = ui.btnValveBig;
	m_valveBtn[m_portsetinfo.smallNo] = ui.btnValveSmall;
	m_valveBtn[m_portsetinfo.middle1No] = ui.btnValveMiddle1;
	m_valveBtn[m_portsetinfo.middle2No] = ui.btnValveMiddle2;
	m_valveBtn[m_portsetinfo.waterInNo] = ui.btnWaterIn;
	m_valveBtn[m_portsetinfo.bigWaterInNo] = ui.btnBigWaterIn;
	m_valveBtn[m_portsetinfo.bigWaterOutNo] = ui.btnBigWaterOut;
	m_valveBtn[m_portsetinfo.smallWaterInNo] = ui.btnSmallWaterIn;
	m_valveBtn[m_portsetinfo.smallWaterOutNo] = ui.btnSmallWaterOut;
	m_valveBtn[m_portsetinfo.pumpNo] = ui.btnWaterPump; //ˮ��

	//��ʼ������ˮ��Ϊ�򿪣���������Ϊ�ر�״̬
	m_valveStatus[m_portsetinfo.bigNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.smallNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle1No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle2No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.bigWaterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.bigWaterOutNo] = VALVE_OPEN;
	m_valveStatus[m_portsetinfo.smallWaterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.smallWaterOutNo] = VALVE_OPEN;
	m_valveStatus[m_portsetinfo.pumpNo] = VALVE_CLOSE; //ˮ��

	setValveBtnBackColor(m_valveBtn[m_portsetinfo.bigNo], m_valveStatus[m_portsetinfo.bigNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.smallNo], m_valveStatus[m_portsetinfo.smallNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle1No], m_valveStatus[m_portsetinfo.middle1No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle2No], m_valveStatus[m_portsetinfo.middle2No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterInNo], m_valveStatus[m_portsetinfo.waterInNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.bigWaterInNo], m_valveStatus[m_portsetinfo.bigWaterInNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.bigWaterOutNo], m_valveStatus[m_portsetinfo.bigWaterOutNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.smallWaterInNo], m_valveStatus[m_portsetinfo.smallWaterInNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.smallWaterOutNo], m_valveStatus[m_portsetinfo.smallWaterOutNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.pumpNo], m_valveStatus[m_portsetinfo.pumpNo]);
}

void StdMtrCoeCorrect::initRegulateStatus()
{
	//�˿ں�-���Ű�ť ӳ���ϵ
	m_RegLineEdit[m_portsetinfo.regSmallNo] = ui.lineEditOpeningSmall;
	m_RegLineEdit[m_portsetinfo.regMid1No] = ui.lineEditOpeningMid1;
	m_RegLineEdit[m_portsetinfo.regMid2No] = ui.lineEditOpeningMid2;
	m_RegLineEdit[m_portsetinfo.regBigNo] = ui.lineEditOpeningBig;

	m_RegSpinBox[m_portsetinfo.regSmallNo] = ui.spinBoxOpeningSmall;
	m_RegSpinBox[m_portsetinfo.regMid1No] = ui.spinBoxOpeningMid1;
	m_RegSpinBox[m_portsetinfo.regMid2No] = ui.spinBoxOpeningMid2;
	m_RegSpinBox[m_portsetinfo.regBigNo] = ui.spinBoxOpeningBig;

	//��ʱ������̬��ʾ���ڷ�����
	m_smallOpening = 0;
	m_regSmallTimer = new QTimer();
	connect(m_regSmallTimer, SIGNAL(timeout()), this, SLOT(slotFreshSmallRegOpening()));

	m_mid1Opening = 0;
	m_regMid1Timer = new QTimer();
	connect(m_regMid1Timer, SIGNAL(timeout()), this, SLOT(slotFreshMid1RegOpening()));

	m_mid2Opening = 0;
	m_regMid2Timer = new QTimer();
	connect(m_regMid2Timer, SIGNAL(timeout()), this, SLOT(slotFreshMid2RegOpening()));

	m_bigOpening = 0;
	m_regBigTimer = new QTimer();
	connect(m_regBigTimer, SIGNAL(timeout()), this, SLOT(slotFreshBigRegOpening()));
}

//�ڽ���ˢ������¶Ⱥͳ����¶�ֵ
void StdMtrCoeCorrect::slotFreshComTempValue(const QString& tempStr)
{
	ui.lcdInTemper->display(tempStr.left(TEMPER_DATA_WIDTH));   //����¶� PV
	ui.lcdOutTemper->display(tempStr.right(TEMPER_DATA_WIDTH)); //�����¶� SV
}

//��ȡ��ǰ�춨����;��ʼ�����ؼ�����ʾ�ؼ���������ʼ��������ͨѶ����
int StdMtrCoeCorrect::readNowParaConfig()
{
	if (NULL == m_paraSetReader)
	{
		return false;
	}

	if (!m_stopFlag)
	{
		return false;
	}

	m_state = STATE_INIT;

	m_nowParams = m_paraSetReader->getParams();
	m_flowPointNum = m_nowParams->total_fp;  //��Ч������ĸ��� 
	m_exaustSecond = m_nowParams->ex_time;   //����ʱ��
	return true;
}

/*
** ��ʼ��������ʱ
*/
int StdMtrCoeCorrect::startExhaustCountDown()
{
	//��4·�綯���ڷ�
	openAllRegulator();
	ui.labelHintProcess->setText(tr("regulator is opening, please wait..."));
	ui.labelHintPoint->clear();
 	wait(5000); //�ȴ��綯���ڷ�������һ�����ȣ���������

	m_controlObj->askSetDriverFreq(m_nowParams->fp_info[0].fp_freq);
	if (!openAllValveAndPump())
	{
		qWarning()<<"�����з��ź�ˮ�� ʧ��!";
		QMessageBox::warning(this, tr("Warning"), tr("exhaust air failed!"));
		return false;
	}
	m_stopFlag = false;
	m_exaustSecond = m_nowParams->ex_time;
	m_exaustTimer->start(CYCLE_TIME);//��ʼ��������ʱ
	ui.labelHintProcess->setText(tr("Exhaust countdown: <font color=DarkGreen size=6><b>%1</b></font> second").arg(m_exaustSecond));
	ui.labelHintPoint->clear();
	qDebug()<<"��������ʱ:"<<m_exaustSecond<<"��";

	return true;
}

/*
** ������ʱ����Ӧ����
*/
void StdMtrCoeCorrect::slotExaustFinished()
{
	if (m_stopFlag)
	{
		return;
	}

	m_exaustSecond --;
	ui.labelHintProcess->setText(tr("Exhaust countdown: <font color=DarkGreen size=6><b>%1</b></font> second").arg(m_exaustSecond));
	qDebug()<<"��������ʱ:"<<m_exaustSecond<<"��";
	if (m_exaustSecond > 1)
	{
		return;
	}

	m_exaustTimer->stop(); //ֹͣ������ʱ
	ui.labelHintProcess->setText(tr("Exhaust countdown finished!"));
	ui.labelHintProcess->clear();
	if (!closeAllFlowPointValves()) //�ر����������㷧�� ʧ��
	{
		if (!closeAllFlowPointValves()) //�ٳ��Թر�һ��
		{
			qWarning()<<"�ر����������㷧��ʧ�ܣ��춨����";
			return;
		}
	}

	startVerify();
}

/*
** �����з��ź�ˮ�ã��رմ�С��ƽ��ˮ������Ϊ��׼������Ҫʹ����ƽ��
*/
int StdMtrCoeCorrect::openAllValveAndPump()
{
	openValve(m_portsetinfo.bigWaterOutNo); //����ƽ��ˮ��
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.smallWaterOutNo);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.bigWaterInNo);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.smallWaterInNo);
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.waterInNo);
	openWaterPump();//��ˮ��
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.smallNo);
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.middle1No);
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.middle2No);
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.bigNo);

	return true;
}

//�ر����з��ź�ˮ��
int StdMtrCoeCorrect::closeAllValveAndPumpOpenOutValve()
{
	openValve(m_portsetinfo.bigWaterOutNo); //�򿪴���ƽ��ˮ��
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.bigWaterInNo);  //�رմ���ƽ��ˮ��
	wait(CYCLE_TIME);
	openValve(m_portsetinfo.smallWaterOutNo);//��С��ƽ��ˮ��
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.smallWaterInNo);//�ر�С��ƽ��ˮ��
	wait(CYCLE_TIME);
	closeWaterPump();    //�˳�ʱ�ر�ˮ��
	closeAllFlowPointValves();//�ر����������㷧��
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.waterInNo);//�رս�ˮ��

	return true;
}

//�ر����������㷧��
int StdMtrCoeCorrect::closeAllFlowPointValves()
{
	closeValve(m_portsetinfo.bigNo);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.middle2No);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.middle1No);
	wait(CYCLE_TIME);
	closeValve(m_portsetinfo.smallNo);

	return true;
}

/*
** ���ܣ��ж���ƽ�����Ƿ�ﵽҪ��ļ춨��������춨���̵�ƽ���¶Ⱥ�ƽ������(m3/h)
** ��������ܴ󣬳���float�ķ�Χ������Ҫ��double
*/
int StdMtrCoeCorrect::judgeTartgetVolAndCalcAvgTemperAndFlow(double initV, double verifyV)
{
	double targetV       = initV + verifyV;
	ui.tableWidget->setEnabled(false);
	QDateTime startTime = QDateTime::currentDateTime();
	int second          = 0;
	double nowFlow;
	/************************************************************************/
	/* 
	double nowFlow       = m_paraSetReader->getFpBySeq(m_nowOrder).fp_verify;
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	/************************************************************************/
	double nowVol        = initV;
	while (!m_stopFlag && (nowVol < targetV))
	{
		qDebug()<<"��ǰ��ˮ�� ="<<nowVol<<", С��Ŀ����� "<<targetV;
		qDebug()<<"m_stopFlag: "<<m_stopFlag;
		m_avgTFCount++;
		m_pipeInTemper += ui.lcdInTemper->value();
		m_pipeOutTemper += ui.lcdOutTemper->value();
		second = 3.6*(targetV - nowVol)/nowFlow;

		ui.labelHintProcess->setText(tr("Verifying...Please wait for about <font color=DarkGreen size=6><b>%1</b></font> second").arg(second));
		wait(CYCLE_TIME);		
		nowVol = ui.lcdVolume->value();//��¼��׼�����(L)
	}

	m_pipeInTemper = m_pipeInTemper/m_avgTFCount;   //���ƽ���¶�
	m_pipeOutTemper = m_pipeOutTemper/m_avgTFCount; //����ƽ���¶�

	QDateTime endTime = QDateTime::currentDateTime();
	int tt = startTime.secsTo(endTime);
	if (NULL==m_paraSetReader || m_stopFlag)
	{
		return false;
	}
	/************************************************************************/
	/* 
	 * 
	 * 
	 * 	ui.labelHintPoint->setText(tr("NO. <font color=DarkGreen size=6><b>%1</b></font> flow point: <font color=DarkGreen size=6><b>%2</b></font> m3/h")\
	 .arg(m_nowOrder).arg(nowFlow));
	 ui.labelHintProcess->setText(tr("NO. <font color=DarkGreen size=6><b>%1</b></font> flow point: Verify Finished!").arg(m_nowOrder));

	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	/************************************************************************/

	int ret = !m_stopFlag && (ui.lcdVolume->value() >= targetV);
	return ret;
}

//��ձ�񣬵�һ�г���("������"��)
void StdMtrCoeCorrect::clearTableContents()
{
	for (int i=0; i<18; i++)
	{
		for (int j=1; j<ui.tableWidget->columnCount(); j++) //�ӵڶ��п�ʼ
		{
			if (ui.tableWidget->item(i,j) == NULL)
				continue;

			ui.tableWidget->item(i,j)->setText("");
		}
	}
}

//���"��ʼ"��ť
void StdMtrCoeCorrect::on_btnStart_clicked()
{
	
}

//���"����"��ť
void StdMtrCoeCorrect::on_btnGoOn_clicked()
{
	ui.btnGoOn->hide();
	startVerify();
}

//���"��ֹ���"��ť
void StdMtrCoeCorrect::on_btnStop_clicked()
{
	int button = QMessageBox::question(this, tr("Question"), tr("Stop Really ?"), \
		QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape);

	if (button == QMessageBox::No)
		return;

	stopVerify();
}

void StdMtrCoeCorrect::on_btnExit_clicked()
{
	stopVerify();
	this->close();
}

//ֹͣ�춨
void StdMtrCoeCorrect::stopVerify()
{
	ui.labelHintPoint->clear();
	if (!m_stopFlag)
	{
		ui.labelHintProcess->setText(tr("stopping verify...please wait a minute"));
		m_stopFlag = true;
		m_exaustTimer->stop();//ֹͣ������ʱ��
		closeAllValveAndPumpOpenOutValve();
	}
	closeAllRegulator();

	ui.labelHintProcess->setText(tr("Verify has Stoped!"));
	m_state = STATE_INIT; //���ó�ʼ״̬

	ui.tableWidget->setEnabled(true);
	ui.btnStart->setEnabled(true);
}

//��ʼ�춨
void StdMtrCoeCorrect::startVerify()
{
	m_state = STATE_INIT; //��ʼ״̬
	m_meterStartValue = 0.0;//���ֵ
	m_meterEndValue = 0.0;//����ֵ
	m_meterStdValue = 0.0;//�����ı�׼ֵ
	m_meterError = 0.0;//���������
}

/************************************************************************/
/* ���е���������ļ춨                                                               
/* ֮����ʹ��������, �������ùܵ��еĶ������������غ�ԭ��, 
/* �����ڹܵ��еĶ�������״̬��Һ��,������ܵ�������, ��������������Һ���������.
/* �����ڽ��б�׼��춨ʱ, ���뽫��׼����������Ϊ��Ӧ�¶��µ�����.
/************************************************************************/
int StdMtrCoeCorrect::startVerifyFlowPoint(int order)
{
	
	return true;
}

/*
** ����ĳ�����������
** ���������
**     idx:��������������
*/
int StdMtrCoeCorrect::calcMeterError(int idx)
{

	return 1; 
}

//�򿪷���
int StdMtrCoeCorrect::openValve(UINT8 portno)
{	
	if (NULL == m_controlObj)
	{
		return false;
	}
	if (portno <= 8)
	{
		m_controlObj->askControlRelay(portno, VALVE_OPEN);
	}
	else
	{
		m_controlObj2->askControlRelay(portno-8, VALVE_OPEN);
	}
	if (m_portsetinfo.version==OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(portno, VALVE_OPEN);
	}
	return true;
}

//�رշ���
int StdMtrCoeCorrect::closeValve(UINT8 portno)
{
	if (NULL == m_controlObj)
	{
		return false;
	}
	if (portno <= 8)
	{
		m_controlObj->askControlRelay(portno, VALVE_CLOSE);
	}
	else
	{
		m_controlObj2->askControlRelay(portno-8, VALVE_CLOSE);
	}
	if (m_portsetinfo.version==OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(portno, VALVE_CLOSE);
	}
	return true;
}

//�������ţ��򿪻��߹ر�
int StdMtrCoeCorrect::operateValve(UINT8 portno)
{
	if (m_valveStatus[portno]==VALVE_OPEN) //����ԭ���Ǵ�״̬
	{
		closeValve(portno);
	}
	else //����ԭ���ǹر�״̬
	{
		openValve(portno);
	}
	return true;
}

//��ˮ��
int StdMtrCoeCorrect::openWaterPump()
{
	if (NULL == m_controlObj)
	{
		return false;
	}
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->askControlWaterPump(m_nowPortNo, VALVE_OPEN);
	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_nowPortNo, VALVE_OPEN);
	}
	return true;
}

//�ر�ˮ��
int StdMtrCoeCorrect::closeWaterPump()
{
	if (NULL == m_controlObj)
	{
		return false;
	}
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->askControlWaterPump(m_nowPortNo, VALVE_CLOSE);
	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_nowPortNo, VALVE_CLOSE);
	}
	return true;
}

//����ˮ�� �򿪻��߹ر�
int StdMtrCoeCorrect::operateWaterPump()
{
	if (m_valveStatus[m_portsetinfo.pumpNo]==VALVE_OPEN) //ˮ��ԭ���Ǵ�״̬
	{
		closeWaterPump();
	}
	else //ˮ��ԭ���ǹر�״̬
	{
		openWaterPump();
	}
	return true;
}

//��Ӧ����״̬���óɹ�
void StdMtrCoeCorrect::slotSetValveBtnStatus(const UINT8 &portno, const bool &status)
{
	m_valveStatus[portno] = status;
	setValveBtnBackColor(m_valveBtn[portno], m_valveStatus[portno]);
}

//��Ӧ���ڷ����ڳɹ�
void StdMtrCoeCorrect::slotSetRegulateOk()
{
}

//���÷��Ű�ť����ɫ
void StdMtrCoeCorrect::setValveBtnBackColor(QToolButton *btn, bool status)
{
	if (NULL == btn)
	{
		return;
	}
	if (status) //���Ŵ� ��ɫ
	{
		btn->setStyleSheet("background-color:rgb(0,255,0);border:0px;border-radius:10px;");
	}
	else //���Źر� ��ɫ
	{
		btn->setStyleSheet("background-color:rgb(255,0,0);border:0px;border-radius:10px;");
	}
}

//���õ��ڷ���ť����ɫ
void StdMtrCoeCorrect::setRegBtnBackColor(QPushButton *btn, bool status)
{
	if (NULL == btn)
	{
		return;
	}
	if (status) //���ڳɹ�
	{
		btn->setStyleSheet("background:blue;border:0px;");
	}
	else //����ʧ��
	{
		btn->setStyleSheet("");
	}
}

//��������
void StdMtrCoeCorrect::on_btnParaSet_clicked()
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
	connect(m_paraSetDlg, SIGNAL(saveSuccessSignal()), this, SLOT(readNowParaConfig()));
	m_paraSetDlg->show();
}

/*
** ���Ƽ̵�������
*/
void StdMtrCoeCorrect::on_btnWaterIn_clicked() //��ˮ��
{
	m_nowPortNo = m_portsetinfo.waterInNo;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnBigWaterIn_clicked() //����ƽ��ˮ��
{
	m_nowPortNo = m_portsetinfo.bigWaterInNo;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnBigWaterOut_clicked() //����ƽ��ˮ��
{
	m_nowPortNo = m_portsetinfo.bigWaterOutNo;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnSmallWaterIn_clicked() //С��ƽ��ˮ��
{
	m_nowPortNo = m_portsetinfo.smallWaterInNo;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnSmallWaterOut_clicked() //С��ƽ��ˮ��
{
	m_nowPortNo = m_portsetinfo.smallWaterOutNo;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnValveBig_clicked() //��������
{
	m_nowPortNo = m_portsetinfo.bigNo;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnValveMiddle1_clicked() //����һ��
{
	m_nowPortNo = m_portsetinfo.middle1No;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnValveMiddle2_clicked() //��������
{
	m_nowPortNo = m_portsetinfo.middle2No;
	operateValve(m_nowPortNo);
}

void StdMtrCoeCorrect::on_btnValveSmall_clicked() //С������
{
	m_nowPortNo = m_portsetinfo.smallNo;
	operateValve(m_nowPortNo);
}

/*
** ����ˮ�ÿ���
*/
void StdMtrCoeCorrect::on_btnWaterPump_clicked()
{
	m_nowPortNo = m_portsetinfo.pumpNo;
	operateWaterPump();
}

/*
** ���ñ�Ƶ��Ƶ��
*/
void StdMtrCoeCorrect::on_btnSetFreq_clicked()
{
	if (NULL == m_controlObj)
	{
		return;
	}
	m_controlObj->askSetDriverFreq(ui.spinBoxFreq->value());
}

//��ȡ���ֵ
int StdMtrCoeCorrect::getMeterStartValue()
{
	
	return true;
}

//��ȡ����ֵ
int StdMtrCoeCorrect::getMeterEndValue()
{
	if (m_stopFlag)
	{
		return false;
	}

	return true;
}

/*
** ��Ӧ�����û���������ֵ������ֵ
   ���������
      row����������0��ʼ
	  column����������0��ʼ
*/
void StdMtrCoeCorrect::on_tableWidget_cellChanged(int row, int column)
{
	
}

/*
** �������б����ļ춨��¼
*/
int StdMtrCoeCorrect::saveAllVerifyRecords()
{

	return 1;
}
/*
** ��4·�綯���ڷ����趨�Ŀ���
** ע�⣺ѡ�еĹ�·�������ڷ����ȵ������趨���ȣ�
         δѡ�еĹ�·���������ڷ����ȵ�����50%����������
*/
void StdMtrCoeCorrect::openAllRegulator()
{
	int regNO = 0;
	float opening = 0;
	int valve_idx = 0;
	QString last_valve_idx;
	for (int i=1; i<=m_flowPointNum; i++) //ѡ�еĹ�·�������ڷ����ȵ������趨����
	{
		regNO = m_paraSetReader->getFpBySeq(i).fp_regno;
		opening = m_paraSetReader->getFpBySeq(i).fp_opening;
		valve_idx = m_paraSetReader->getFpBySeq(i).fp_valve_idx;
		if (last_valve_idx.contains(QString("%1").arg(valve_idx))) //ͬһ��·�ܶ��������
		{
			continue;
		}
		switch (valve_idx)
		{
		case 0: //��������
			ui.spinBoxOpeningBig->setValue(opening);
			on_btnRegulateBig_clicked();
			break;
		case 1: //�ж�������
			ui.spinBoxOpeningMid2->setValue(opening);
			on_btnRegulateMid2_clicked();
			break;
		case 2: //��һ������
			ui.spinBoxOpeningMid1->setValue(opening);
			on_btnRegulateMid1_clicked();
			break;
		case 3: //С������
			ui.spinBoxOpeningSmall->setValue(opening);
			on_btnRegulateSmall_clicked();
			break;
		default:
			break;
		}
		last_valve_idx += QString("%1").arg(valve_idx);
	}

	//δѡ�еĹ�·�������ڷ����ȵ�����50%����������
	if (ui.spinBoxOpeningSmall->value()==0)
	{
		ui.spinBoxOpeningSmall->setValue(50);
		on_btnRegulateSmall_clicked();
	}
	if (ui.spinBoxOpeningMid1->value()==0)
	{
		ui.spinBoxOpeningMid1->setValue(50);
		on_btnRegulateMid1_clicked();
	}
	if (ui.spinBoxOpeningMid2->value()==0)
	{
		ui.spinBoxOpeningMid2->setValue(50);
		on_btnRegulateMid2_clicked();
	}
	if (ui.spinBoxOpeningBig->value()==0)
	{
		ui.spinBoxOpeningBig->setValue(50);
		on_btnRegulateBig_clicked();
	}
}

/*
** �ر�4·�綯���ڷ�
*/
void StdMtrCoeCorrect::closeAllRegulator()
{
	if (ui.spinBoxOpeningSmall->value()!=0)
	{
		ui.spinBoxOpeningSmall->setValue(0);
		on_btnRegulateSmall_clicked();
	}
	if (ui.spinBoxOpeningMid1->value()!=0)
	{
		ui.spinBoxOpeningMid1->setValue(0);
		on_btnRegulateMid1_clicked();
	}
	if (ui.spinBoxOpeningMid2->value()!=0)
	{
		ui.spinBoxOpeningMid2->setValue(0);
		on_btnRegulateMid2_clicked();
	}
	if (ui.spinBoxOpeningBig->value()!=0)
	{
		ui.spinBoxOpeningBig->setValue(0);
		on_btnRegulateBig_clicked();
	}
}

void StdMtrCoeCorrect::setRegulatorOpening(int regNO, int opening)
{
	if (regNO == m_portsetinfo.regSmallNo) //С���ڷ�
	{
		ui.spinBoxOpeningSmall->setValue(opening);
		on_btnRegulateSmall_clicked();
	}
	else if (regNO == m_portsetinfo.regMid1No) //��һ���ڷ�
	{
		ui.spinBoxOpeningMid1->setValue(opening);
		on_btnRegulateMid1_clicked();
	}
	else if (regNO == m_portsetinfo.regMid2No) //�ж����ڷ�
	{
		ui.spinBoxOpeningMid2->setValue(opening);
		on_btnRegulateMid2_clicked();
	}
	else if (regNO == m_portsetinfo.regBigNo) //����ڷ�
	{
		ui.spinBoxOpeningBig->setValue(opening);
		on_btnRegulateBig_clicked();
	}
}

//�綯���ڷ�
void StdMtrCoeCorrect::on_btnRegulateSmall_clicked() //���ڷ�1-DN3
{
	m_smallOpening = ui.ThermoSmall->value();
	askControlRegulate(m_portsetinfo.regSmallNo, ui.spinBoxOpeningSmall->value());
	m_regSmallTimer->start(REGULATE_FRESH_TIME);
}

void StdMtrCoeCorrect::on_btnRegulateMid1_clicked() //���ڷ�2-DN10
{
	m_mid1Opening = ui.ThermoMid1->value();
	askControlRegulate(m_portsetinfo.regMid1No, ui.spinBoxOpeningMid1->value());
	m_regMid1Timer->start(REGULATE_FRESH_TIME);
}

void StdMtrCoeCorrect::on_btnRegulateMid2_clicked() //���ڷ�3-DN25
{
	m_mid2Opening = ui.ThermoMid2->value();
	askControlRegulate(m_portsetinfo.regMid2No, ui.spinBoxOpeningMid2->value());
	m_regMid2Timer->start(REGULATE_FRESH_TIME);
}

void StdMtrCoeCorrect::on_btnRegulateBig_clicked() //���ڷ�4-DN50
{
	m_bigOpening = ui.ThermoBig->value();
	askControlRegulate(m_portsetinfo.regBigNo, ui.spinBoxOpeningBig->value());
	m_regBigTimer->start(REGULATE_FRESH_TIME);
}

void StdMtrCoeCorrect::askControlRegulate(int regNO, int opening)
{
	if (regNO>=1 && regNO<=3)
	{
		m_controlObj->askControlRegulate(regNO, opening);
	}
	else
	{
		m_controlObj2->askControlRegulate(regNO-3, opening);
	}
}

void StdMtrCoeCorrect::on_lineEditOpeningSmall_textChanged(const QString & text)
{
	ui.ThermoSmall->setValue(text.toFloat());
}

void StdMtrCoeCorrect::on_lineEditOpeningMid1_textChanged(const QString & text)
{
	ui.ThermoMid1->setValue(text.toFloat());
}

void StdMtrCoeCorrect::on_lineEditOpeningMid2_textChanged(const QString & text)
{
	ui.ThermoMid2->setValue(text.toFloat());
}

void StdMtrCoeCorrect::on_lineEditOpeningBig_textChanged(const QString & text)
{
	ui.ThermoBig->setValue(text.toFloat());
}

void StdMtrCoeCorrect::slotFreshSmallRegOpening()
{
	if (ui.ThermoSmall->value() < ui.spinBoxOpeningSmall->value())
	{
		ui.lineEditOpeningSmall->setText(QString("%1").arg(m_smallOpening++));
	}
	else
	{
		ui.lineEditOpeningSmall->setText(QString("%1").arg(m_smallOpening--));
	}

	if (ui.lineEditOpeningSmall->text().toInt() == ui.spinBoxOpeningSmall->value())
	{
		m_regSmallTimer->stop();
	}
}

void StdMtrCoeCorrect::slotFreshMid1RegOpening()
{
	if (ui.ThermoMid1->value() < ui.spinBoxOpeningMid1->value())
	{
		ui.lineEditOpeningMid1->setText(QString("%1").arg(m_mid1Opening++));
	}
	else
	{
		ui.lineEditOpeningMid1->setText(QString("%1").arg(m_mid1Opening--));
	}

	if (ui.lineEditOpeningMid1->text().toInt() == ui.spinBoxOpeningMid1->value())
	{
		m_regMid1Timer->stop();
	}
}

void StdMtrCoeCorrect::slotFreshMid2RegOpening()
{
	if (ui.ThermoMid2->value() < ui.spinBoxOpeningMid2->value())
	{
		ui.lineEditOpeningMid2->setText(QString("%1").arg(m_mid2Opening++));
	}
	else
	{
		ui.lineEditOpeningMid2->setText(QString("%1").arg(m_mid2Opening--));
	}

	if (ui.lineEditOpeningMid2->text().toInt() == ui.spinBoxOpeningMid2->value())
	{
		m_regMid2Timer->stop();
	}
}

void StdMtrCoeCorrect::slotFreshBigRegOpening()
{
	if (ui.ThermoBig->value() < ui.spinBoxOpeningBig->value())
	{
		ui.lineEditOpeningBig->setText(QString("%1").arg(m_bigOpening++));
	}
	else
	{
		ui.lineEditOpeningBig->setText(QString("%1").arg(m_bigOpening--));
	}

	if (ui.lineEditOpeningBig->text().toInt() == ui.spinBoxOpeningBig->value())
	{
		m_regBigTimer->stop();
	}
}
