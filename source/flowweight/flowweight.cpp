/***********************************************
**  �ļ���:     flowweight.cpp
**  ����:       �����춨(������)������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2015/2/9
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2015/02 ��һ��
**  ���ݰ���:
**  ˵��:		
**  ���¼�¼:   
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QTest>
#include <QtSql/QSqlTableModel>
#include <QtGui/QFileDialog>
#include <QtCore/QSignalMapper>
#include <math.h>

#include "flowweight.h"
#include "commondefine.h"
#include "algorithm.h"
#include "qtexdb.h"
#include "parasetdlg.h"
#include "readcomconfig.h"

FlowWeightDlg::FlowWeightDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"FlowWeightDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);
	ui.btnGoOn->hide();
 	ui.btnNext->hide();   //����"��һ��"��ť

	//��ͬ�ȼ����������Ӧ�ı�׼���,��λ%
	m_gradeErrA[1] = 1.00f;
	m_gradeErrA[2] = 2.00f;
	m_gradeErrA[3] = 3.00f;

	m_gradeErrB[1] = 0.01f;
	m_gradeErrB[2] = 0.02f;
	m_gradeErrB[3] = 0.05f;

	m_mapNormalFlow[0] = 1.5f; //DN15�������� 1.5
	m_mapNormalFlow[1] = 2.5f; //DN20�������� 2.5
	m_mapNormalFlow[2] = 3.5f; //DN25�������� 3.5

	if (!getPortSetIni(&m_portsetinfo)) //��ȡ��λ���˿ں�������Ϣ
	{
		QMessageBox::warning(this, tr("Warning"), tr("Warning:get port set info failed!"));
	}

	m_readComConfig = new ReadComConfig(); //���������ýӿڣ�������initBalanceComǰ���ã�
	m_readComConfig->getBalancePara(m_balMaxWht, m_balBottomWht); //��ȡ��ƽ��������ͻ�ˮ����

	m_balanceObj = NULL;
	initBalanceCom();		//��ʼ����ƽ����

	m_tempObj = NULL;
	m_tempTimer = NULL;
	initTemperatureCom();	//��ʼ���¶Ȳɼ�����

	m_controlObj = NULL;
	initControlCom();		//��ʼ�����ƴ���

	m_meterObj = NULL;      //������ͨѶ
	m_recPtr = NULL;        //���������

	//����������
	m_totalcount = 0;
	m_startWeight = 0.0;
	m_endWeight = 0.0;
	memset(m_deltaWeight, 0, sizeof(float)*FLOW_SAMPLE_NUM);
	m_flowRateTimer = new QTimer();
	connect(m_flowRateTimer, SIGNAL(timeout()), this, SLOT(slotFreshFlowRate()));
	m_flowRateTimer->start(TIMEOUT_FLOW_SAMPLE);

	//������ӿ�
	m_chkAlg = new CAlgorithm();

	//ӳ���ϵ����ʼ������״̬	
	initValveStatus();      

	m_exaustTimer = new QTimer(this); //������ʱ��
	connect(m_exaustTimer, SIGNAL(timeout()), this, SLOT(slotExaustFinished()));

	m_stopFlag = false; //ֹͣ����־���˳�����󣬲��ټ����ƽ������

	m_avgTFCount = 1; //����ƽ���¶��õ��ۼӼ�����
	m_nowOrder = 0;  //��ǰ���еļ춨���

	m_nowParams = new Verify_Params_STR;
	memset(m_nowParams, 0, sizeof(Verify_Params_STR));
	m_continueVerify = true; //�����춨
	m_resetZero = false;     //��ֵ����
	m_autopick = false;      //�Զ��ɼ�
	m_flowPointNum = 0;      //���������
	m_maxMeterNum = 0;       //ĳ�������֧�ֵļ�����
	m_oldMaxMeterNum = 0;
	m_validMeterNum = 0;     //ʵ�ʼ�����
	m_exaustSecond = 45;     //Ĭ������ʱ��45��
	m_pickcode = PROTOCOL_VER_DELU; //�ɼ����� Ĭ�ϵ�³
	m_flowSC = 1.0;			 //������ȫϵ����Ĭ��1.0
	m_meterStartValue = NULL;
	m_meterEndValue = NULL;
	m_meterTemper = NULL;
	m_meterDensity = NULL;
	m_meterStdValue = NULL;
	m_meterError = NULL;
	m_balStartV = 0;
	m_balEndV = 0;
	m_timeStamp = "";
	m_nowDate = "";
	m_validDate = "";

	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable("T_Meter_Standard");  
	model->select();  
	m_meterStdMapper = new QDataWidgetMapper(this);
	m_meterStdMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	m_meterStdMapper->setModel(model);
	m_meterStdMapper->addMapping(ui.lnEditStandard, 1); //ӳ���"T_Meter_Standard"�ĵڶ����ֶ�

	m_paraSetDlg = NULL;    //�������öԻ���
	m_paraSetReader = new ParaSetReader(); //���������ýӿ�
	if (!readNowParaConfig()) //��ȡ��ǰ�춨����
	{
		qWarning()<<"��ȡ���������ļ�ʧ��!";
	}

	if (!isComAndPortNormal())
	{
		qWarning()<<"���ڡ��˿����ô���!";
	}
}

FlowWeightDlg::~FlowWeightDlg()
{
}

void FlowWeightDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^FlowWeightDlg::closeEvent";

	m_stopFlag = true;

	openWaterOutValve(); //�˳�ʱ�򿪷�ˮ��
	closeWaterPump();    //�˳�ʱ�ر�ˮ��
	openValve(m_portsetinfo.bigNo); //�򿪴������㷧�ţ��ͷŹ�·ѹ��
	ui.labelHintPoint->clear();
	ui.labelHintProcess->setText(tr("release pipe pressure..."));
	QTest::qWait(2000);
	closeValve(m_portsetinfo.bigNo);


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

	if (m_tempObj)  // �¶Ȳɼ�
	{
		delete m_tempObj;
		m_tempObj = NULL;

		m_tempThread.exit(); //������־�л��о���"QThread: Destroyed while thread is still running"
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

	if (m_balanceObj)  //��ƽ�ɼ�
	{
		delete m_balanceObj;
		m_balanceObj = NULL;

		m_balanceThread.exit();
	}

	if (m_controlObj)  //���ſ���
	{
		delete m_controlObj;
		m_controlObj = NULL;

		m_valveThread.exit();
	}

	if (m_chkAlg)//������
	{
		delete m_chkAlg;
		m_chkAlg = NULL;
	}

	//������ͨѶ
	if (m_meterObj)
	{
		delete []m_meterObj;
		m_meterObj = NULL;

		for (int i=0; i<m_oldMaxMeterNum; i++)
		{
			m_meterThread[i].exit();
		}
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
}

//��ƽ�ɼ����� ��λ��ֱ�Ӳɼ�
void FlowWeightDlg::initBalanceCom()
{
	ComInfoStruct balanceStruct = m_readComConfig->ReadBalanceConfig();
	m_balanceObj = new BalanceComObject();
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

	//��ƽ��ֵ����λ��ֱ��ͨ����ƽ���ڲɼ�
	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const float &)), this, SLOT(slotFreshBalanceValue(const float &)));
}

/*
** �¶Ȳɼ����� ��λ��ֱ�Ӳɼ�
** ��������
*/
void FlowWeightDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadTempConfig();
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer();
	connect(m_tempTimer, SIGNAL(timeout()), m_tempObj, SLOT(writeTemperatureComBuffer()));
	
	m_tempTimer->start(TIMEOUT_PIPE_TEMPER); //���������¶�
}

//���ư�ͨѶ����
void FlowWeightDlg::initControlCom()
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

//������ͨѶ����
void FlowWeightDlg::initMeterCom()
{
	if (m_meterObj)
	{
		delete []m_meterObj;
		m_meterObj = NULL;

		for (int i=0; i<m_oldMaxMeterNum; i++)
		{
			m_meterThread[i].exit();
		}
	}
	if (m_maxMeterNum <= 0)
	{
		return;
	}

	m_oldMaxMeterNum = m_maxMeterNum;
	m_meterThread = new ComThread[m_maxMeterNum];

	m_meterObj = new MeterComObject[m_maxMeterNum];
	int i=0;
	for (i=0; i<m_maxMeterNum; i++)
	{
		m_meterObj[i].moveToThread(&m_meterThread[i]);
		m_meterObj[i].setProtocolVersion(m_pickcode); //���ñ�Э������
		m_meterThread[i].start();
		m_meterObj[i].openMeterCom(&m_readComConfig->ReadMeterConfigByNum(QString("%1").arg(i+1)));
		
		connect(&m_meterObj[i], SIGNAL(readMeterNoIsOK(const QString&, const QString&)), this, SLOT(slotSetMeterNumber(const QString&, const QString&)));
		connect(&m_meterObj[i], SIGNAL(readMeterFlowIsOK(const QString&, const float&)), this, SLOT(slotSetMeterFlow(const QString&, const float&)));
	}
}

/*
** �˿ں�-����ӳ���ϵ����ʼ������״̬��Ĭ�Ϸ��ų�ʼ״̬ȫ��Ϊ�ر�,ˮ�ó�ʼ״̬Ϊ�رգ�
** ��Ҫ�Ľ��ø������
*/
void FlowWeightDlg::initValveStatus()
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

	//��ʼ������ˮ��Ϊ�򿪣���������Ϊ�ر�״̬
	m_valveStatus[m_portsetinfo.bigNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.smallNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle1No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle2No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterOutNo] = VALVE_OPEN;
	m_valveStatus[m_portsetinfo.pumpNo] = VALVE_CLOSE; //ˮ��

	setValveBtnBackColor(m_valveBtn[m_portsetinfo.bigNo], m_valveStatus[m_portsetinfo.bigNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.smallNo], m_valveStatus[m_portsetinfo.smallNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle1No], m_valveStatus[m_portsetinfo.middle1No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle2No], m_valveStatus[m_portsetinfo.middle2No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterInNo], m_valveStatus[m_portsetinfo.waterInNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterOutNo], m_valveStatus[m_portsetinfo.waterOutNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.pumpNo], m_valveStatus[m_portsetinfo.pumpNo]);
}

/*
** �������ܣ�
	�ڽ���ˢ����ƽ��ֵ
	����ͻ����ֵ
	��ֹ��ƽ���
*/
void FlowWeightDlg::slotFreshBalanceValue(const float& balValue)
{
	QString wht = QString::number(balValue, 'f', 3);
	ui.lcdBigBalance->display(wht);
	if (balValue > m_balMaxWht) //��ֹ��ƽ���
	{
		closeValve(m_portsetinfo.waterInNo); //�رս�ˮ��
		closeAllFlowPointValves(); //�ر����������㷧��
		openWaterOutValve(); //�򿪷�ˮ��
		closeWaterPump(); //�ر�ˮ��
	}
}

//�ڽ���ˢ������¶Ⱥͳ����¶�ֵ
void FlowWeightDlg::slotFreshComTempValue(const QString& tempStr)
{
	ui.lcdInTemper->display(tempStr.left(DATA_WIDTH));   //����¶� PV
	ui.lcdOutTemper->display(tempStr.right(DATA_WIDTH)); //�����¶� SV
}

/*
** ��������
*/
void FlowWeightDlg::slotFreshFlowRate()
{
// 	qDebug()<<"FlowWeightDlg::slotFreshFlowRate thread:"<<QThread::currentThreadId();
	if (m_totalcount > 4294967290) //��ֹm_totalcount��� 32λ�޷���������Χ0~4294967295
	{
		m_totalcount = 0;
		m_startWeight = 0.0;
		m_endWeight = 0.0;
		memset(m_deltaWeight, 0, sizeof(float)*FLOW_SAMPLE_NUM);
	}
	if (m_totalcount == 0) //��¼��ƽ��ʼ����
	{
		m_startWeight = ui.lcdBigBalance->value();
		m_totalcount ++;
		return;
	}

	float flowValue = 0.0;
	float totalWeight = 0.0;
	m_endWeight = ui.lcdBigBalance->value();//ȡ��ǰ��ƽֵ, ��Ϊ��ǰ�������ֵ
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
	if (m_totalcount >= FLOW_SAMPLE_NUM)
	{
		ui.lcdFlowRate->display(QString::number(flowValue, 'f', 3)); //��ui.lcdFlowRate����ʾ����
	}
	m_totalcount ++;//�������ۼ�
	m_startWeight = m_endWeight;//����ǰֵ����, ��Ϊ�´�����ĳ�ֵ
}

//��⴮�ڡ��˿������Ƿ���ȷ
int FlowWeightDlg::isComAndPortNormal()
{
	return true;
}

//��ȡ��ǰ�춨����;��ʼ�����ؼ�����ʾ�ؼ���������ʼ��������ͨѶ����
int FlowWeightDlg::readNowParaConfig()
{
	if (NULL == m_paraSetReader)
	{
		return false;
	}

	m_state = STATE_INIT;

	m_nowParams = m_paraSetReader->getParams();
	m_continueVerify = m_nowParams->bo_converify; //�����춨
	m_resetZero = m_nowParams->bo_resetzero; //��ֵ����
	m_autopick = m_nowParams->bo_autopick;   //�Զ��ɼ�
	m_flowPointNum = m_nowParams->total_fp;  //��Ч������ĸ��� 
	m_exaustSecond = m_nowParams->ex_time;   //����ʱ��
	m_standard = m_nowParams->m_stand;       //����
	m_model = m_nowParams->m_model;   //���ͺ�
	m_maxMeterNum = m_nowParams->m_maxMeters;//��ͬ�����Ӧ�����������
	m_pickcode = m_nowParams->m_pickcode; //�ɼ�����
	m_flowSC = m_nowParams->sc_flow; //������ȫϵ��

	initTableWidget();
	showNowKeyParaConfig();
	initMeterCom();

	return true;
}

//��ʼ�����ؼ�
void FlowWeightDlg::initTableWidget()
{
	if (m_maxMeterNum <= 0)
	{
		return;
	}
	ui.tableWidget->setRowCount(m_maxMeterNum); //���ñ������

	QSignalMapper *m_signalMapper1 = new QSignalMapper();
	QSignalMapper *m_signalMapper2 = new QSignalMapper();
	QSignalMapper *m_signalMapper3 = new QSignalMapper();
	QSignalMapper *m_signalMapper4 = new QSignalMapper();

	QStringList vLabels;
	for (int i=0; i< m_maxMeterNum; i++)
	{
		vLabels<<QString(QObject::tr("meterPosNo%1").arg(i+1));

		ui.tableWidget->setItem(i, COLUMN_METER_NUMBER, new QTableWidgetItem(QString()));
		ui.tableWidget->setItem(i, COLUMN_METER_START, new QTableWidgetItem(QString()));
		ui.tableWidget->setItem(i, COLUMN_METER_END, new QTableWidgetItem(QString()));

		QPushButton *btnModNo = new QPushButton(tr("ModifyNO"));
		ui.tableWidget->setCellWidget(i, COLUMN_MODIFY_METERNO, btnModNo);
		m_signalMapper1->setMapping(btnModNo, i);
		connect(btnModNo, SIGNAL(clicked()), m_signalMapper1, SLOT(map()));

		QPushButton *btnAdjErr = new QPushButton(tr("AdjustErr"));
		ui.tableWidget->setCellWidget(i, COLUMN_ADJUST_ERROR, btnAdjErr);
		m_signalMapper2->setMapping(btnAdjErr, i);
		connect(btnAdjErr, SIGNAL(clicked()), m_signalMapper2, SLOT(map()));

		QPushButton *btnReadMeter = new QPushButton(tr("ReadMeter"));
		ui.tableWidget->setCellWidget(i, COLUMN_READ_METER, btnReadMeter);
		m_signalMapper3->setMapping(btnReadMeter, i);
		connect(btnReadMeter, SIGNAL(clicked()), m_signalMapper3, SLOT(map()));

		QPushButton *btnVerifySt = new QPushButton(tr("VerifySt"));
		ui.tableWidget->setCellWidget(i, COLUMN_VERIFY_STATUS, btnVerifySt);
		m_signalMapper4->setMapping(btnVerifySt, i);
		connect(btnVerifySt, SIGNAL(clicked()), m_signalMapper4, SLOT(map()));

	}
	connect(m_signalMapper1, SIGNAL(mapped(const int &)),this, SLOT(slotModifyMeterNO(const int &)));
	connect(m_signalMapper2, SIGNAL(mapped(const int &)),this, SLOT(slotAdjustError(const int &)));
	connect(m_signalMapper3, SIGNAL(mapped(const int &)),this, SLOT(slotReadMeter(const int &)));
	connect(m_signalMapper4, SIGNAL(mapped(const int &)),this, SLOT(slotVerifyStatus(const int &)));

	ui.tableWidget->setVerticalHeaderLabels(vLabels);

	for (int m=0; m<ui.tableWidget->rowCount(); m++)
	{
		for (int n=0; n<ui.tableWidget->columnCount(); n++)
		{
			ui.tableWidget->setItem(m, n, new QTableWidgetItem(QString("")));
		}
	}
// 	ui.tableWidget->resizeColumnsToContents();
}

//��ʾ��ǰ�ؼ�����������Ϣ
void FlowWeightDlg::showNowKeyParaConfig()
{
	if (NULL == m_nowParams)
	{
		return;
	}

	ui.cmbAutoPick->setCurrentIndex(m_nowParams->bo_autopick);
	ui.cmbContinue->setCurrentIndex(m_nowParams->bo_converify);
	ui.cmbResetZero->setCurrentIndex(m_nowParams->bo_resetzero);
	m_meterStdMapper->setCurrentIndex(m_nowParams->m_stand);
}

//������ݲɼ��Ƿ�������������ƽ���¶ȡ����������
int FlowWeightDlg::isDataCollectNormal()
{
	return true;
}

//�����з��ź�ˮ��
int FlowWeightDlg::openAllValveAndPump()
{
	//�򿪷���
	openWaterOutValve();
	openValve(m_portsetinfo.bigNo);
	openValve(m_portsetinfo.middle1No);
	openValve(m_portsetinfo.middle2No);
	openValve(m_portsetinfo.smallNo);
	openValve(m_portsetinfo.waterInNo);

	//��ˮ��
	openWaterPump();

	return true;
}

/*
** ������ʱ����Ӧ����
*/
void FlowWeightDlg::slotExaustFinished()
{
	m_exaustSecond --;
	ui.labelHintProcess->setText(tr("Exhaust countdown: %1 second").arg(m_exaustSecond));
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

	if (m_stopFlag)
	{
		return;
	}

	if (!prepareInitBalance())//׼����ƽ��ʼ����
	{
		return;
	}

	if (setAllMeterVerifyStatus()) //���ü춨״̬�ɹ�
	{
		startVerify();
	}
}

/*
** ���������󡢿�ʼ�춨ǰ��׼����ƽ,�ﵽҪ��ĳ�ʼ����
*/
int FlowWeightDlg::prepareInitBalance()
{
	ui.labelHintPoint->setText(tr("prepare balance init weight ...")); //׼����ƽ��ʼ����(��ˮ����)
	int ret = 0;
	//�ж���ƽ����,���С��Ҫ��Ļ�ˮ����(5kg)����رշ�ˮ�����򿪴�������
	if (ui.lcdBigBalance->value() < m_balBottomWht)
	{
		if (!closeWaterOutValve()) 
		{
			qWarning()<<"�رշ�ˮ��ʧ��";
		}
		if (!openValve(m_portsetinfo.bigNo))
		{
			qWarning()<<"�򿪴�������ʧ��";
		}
		//�жϲ��ȴ���ƽ���������ڻ�ˮ����(5kg)
		if (isBalanceValueBigger(m_balBottomWht, true))
		{
			if (!closeValve(m_portsetinfo.bigNo))
			{
				qWarning()<<"�رմ�������ʧ��";
			}
			ret = 1;
		}
	}
	else
	{
		closeWaterOutValve(); //�رշ�ˮ��
		ret = 1;
	}

	return ret;
}

/*
** ��ȡ�ȱ�
*/
int FlowWeightDlg::readAllMeter()
{
	on_btnAllReadMeter_clicked();
	return true;
}

//�����������������춨״̬
int FlowWeightDlg::setAllMeterVerifyStatus()
{
	on_btnAllVerifyStatus_clicked();
	return true;
}

//�ر����������㷧��
int FlowWeightDlg::closeAllFlowPointValves()
{
	closeValve(m_portsetinfo.bigNo);
	closeValve(m_portsetinfo.middle1No);
	closeValve(m_portsetinfo.middle2No);
	closeValve(m_portsetinfo.smallNo);

	return true;
}

//�رշ�ˮ����
int FlowWeightDlg::closeWaterOutValve()
{
	closeValve(m_portsetinfo.waterOutNo);
	return true;
}

//�򿪷�ˮ����
int FlowWeightDlg::openWaterOutValve()
{
	openValve(m_portsetinfo.waterOutNo);
	return true;
}

/*
** ��Ӧ������ƽ�����ı仯
** ���������
	targetV: Ŀ������
	flg: true-Ҫ�����Ŀ������(Ĭ��)��false-Ҫ��С��Ŀ������
*/
int FlowWeightDlg::isBalanceValueBigger(float targetV, bool flg)
{
	int ret = 0;
	if (flg) //Ҫ�����Ŀ������
	{
		while (!m_stopFlag && (ui.lcdBigBalance->value() < targetV))
		{
			qDebug()<<"��ƽ���� ="<<ui.lcdBigBalance->value()<<", С��Ҫ������� "<<targetV;
			QTest::qWait(1000);
		}
		ret = !m_stopFlag && (ui.lcdBigBalance->value() >= targetV);
	}
	else //Ҫ��С��Ŀ������
	{
		while (!m_stopFlag && (ui.lcdBigBalance->value() > targetV))
		{
			qDebug()<<"��ƽ���� ="<<ui.lcdBigBalance->value()<<", ����Ҫ������� "<<targetV;
			QTest::qWait(1000);
		}
		ret = !m_stopFlag && (ui.lcdBigBalance->value() <= targetV);
	}

	return ret;
}

/*
** ���ܣ��ж���ƽ�����Ƿ�ﵽҪ��ļ춨��������춨���̵�ƽ���¶Ⱥ�ƽ������(m3/h)
*/
int FlowWeightDlg::judgeBalanceAndCalcAvgTemperAndFlow(float targetV)
{
	QDateTime startTime = QDateTime::currentDateTime();
	int second = 0;
	float nowFlow = m_paraSetReader->getFpBySeq(m_nowOrder).fp_verify;
	while (!m_stopFlag && (ui.lcdBigBalance->value() < targetV))
	{
		qDebug()<<"��ƽ���� ="<<ui.lcdBigBalance->value()<<", С��Ҫ������� "<<targetV;
		m_avgTFCount++;
		m_pipeInTemper += ui.lcdInTemper->value();
		m_pipeOutTemper += ui.lcdOutTemper->value();
// 		if (m_avgTFCount > FLOW_SAMPLE_NUM*2) //ǰ20���˲ʱ���ٲ�׼�����������
// 		{
// 			m_realFlow += ui.lcdFlowRate->value();
// 		}
		second = 3.6*(targetV - ui.lcdBigBalance->value())/nowFlow;
		ui.labelHintPoint->setText(tr("NO. %1 flow point: %2 m3/h").arg(m_nowOrder).arg(nowFlow));
		ui.labelHintProcess->setText(tr("Verifying...\nPlease wait for about %1 second").arg(second));
		QTest::qWait(1000);
	}

	m_pipeInTemper = m_pipeInTemper/m_avgTFCount;   //���ƽ���¶�
	m_pipeOutTemper = m_pipeOutTemper/m_avgTFCount; //����ƽ���¶�
// 	if (m_avgTFCount > FLOW_SAMPLE_NUM*2)
// 	{
// 		m_realFlow = m_realFlow/(m_avgTFCount-FLOW_SAMPLE_NUM*2+1); //ƽ������
// 	}
	QDateTime endTime = QDateTime::currentDateTime();
	int tt = startTime.secsTo(endTime);
	m_realFlow = 3.6*(m_paraSetReader->getFpBySeq(m_nowOrder).fp_quantity + ui.lcdBigBalance->value() - targetV)/tt;
	ui.labelHintPoint->setText(tr("NO. %1 flow point: %2 m3/h").arg(m_nowOrder).arg(nowFlow));
	ui.labelHintProcess->setText(tr("Verify Finished!"));
	if (m_nowOrder == m_flowPointNum)
	{
		ui.labelHintProcess->setText(tr("All flow points has verified!"));
		ui.btnNext->hide();
	}
	int ret = !m_stopFlag && (ui.lcdBigBalance->value() >= targetV);
	return ret;
}

//��ձ�񣬵�һ�г���("���"��)
void FlowWeightDlg::clearTableContents()
{
	for (int i=0; i<m_maxMeterNum; i++)
	{
		for (int j=1; j<ui.tableWidget->columnCount(); j++) //�ӵڶ��п�ʼ
		{
			if (ui.tableWidget->item(i,j) == 0)
			{
				continue;
			}
			ui.tableWidget->item(i,j)->setText("");
		}
	}
// 	ui.tableWidget->clearContents(); //��ձ��
}

//���"��ʼ"��ť
void FlowWeightDlg::on_btnStart_clicked()
{
	if (!on_btnExhaust_clicked())
	{
		return;
	}

	ui.btnStart->setEnabled(false);
	ui.btnExhaust->setEnabled(false);
	ui.btnGoOn->hide();
	ui.btnNext->hide();

	m_stopFlag = false;
	m_state = STATE_INIT;
	for (int i=0; i<ui.tableWidget->rowCount(); i++)
	{
		ui.tableWidget->item(i,COLUMN_METER_NUMBER)->setText("");
	}
	clearTableContents();
	m_validMeterNum = 0;

	if (m_autopick) //�Զ�����
	{
		readAllMeter();
	}
	else //�ֶ�����
	{
		ui.labelHintPoint->setText(tr("Please input meter number!"));
	}

	return;
}

/*
** ���"����"��ť
*/
int FlowWeightDlg::on_btnExhaust_clicked()
{
	if (!isDataCollectNormal())
	{
		qWarning()<<"���ݲɼ���������";
		QMessageBox::warning(this, tr("Warning"), tr("data acquisition error, please check!"));
		return false;
	}

	if (!openAllValveAndPump())
	{
		qWarning()<<"�����з��ź�ˮ�� ʧ��!";
		QMessageBox::warning(this, tr("Warning"), tr("exhaust air failed!"));
		return false;
	}
	m_stopFlag = true;
	m_exaustSecond = m_nowParams->ex_time;
	m_exaustTimer->start(1000);//��ʼ��������ʱ
	ui.labelHintProcess->setText(tr("Exhaust countdown: %1 second").arg(m_exaustSecond));
	ui.labelHintPoint->clear();
	qDebug()<<"��������ʱ:"<<m_exaustSecond<<"��";

	return true;
}

//���"����"��ť
void FlowWeightDlg::on_btnGoOn_clicked()
{
	ui.btnGoOn->hide();
	startVerify();
}

//���"��һ��"��ť
void FlowWeightDlg::on_btnNext_clicked()
{
	if (m_nowOrder >= m_flowPointNum)
	{
		QMessageBox::warning(this, tr("Warning"), tr("All flow points has verified!"));
		return;
	}
	m_state = STATE_INIT;
	clearTableContents();

	m_nowOrder ++;
	if (m_nowOrder == m_flowPointNum)
	{
		ui.btnNext->hide();
	}
	prepareVerifyFlowPoint(m_nowOrder); // ��ʼ������һ��������ļ춨

}

//���"��ֹ���"��ť
void FlowWeightDlg::on_btnStop_clicked()
{
	int button = QMessageBox::question(this, tr("Question"), tr("Stop Really ?"), \
		QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape);
	if (button == QMessageBox::No)
	{
		return;
	}

	m_stopFlag = true; //���ټ����ƽ����
	stopVerify();
}

void FlowWeightDlg::on_btnExit_clicked()
{
	this->close();
}

//ֹͣ�춨
void FlowWeightDlg::stopVerify()
{
	m_exaustTimer->stop();//ֹͣ������ʱ��
	closeAllFlowPointValves();//�ر����������㷧��
	closeValve(m_portsetinfo.waterInNo);//�رս�ˮ��
	closeWaterPump();//�ر�ˮ��
	openWaterOutValve();//�򿪷�ˮ��
	ui.labelHintPoint->clear();
	ui.labelHintProcess->setText(tr("Verify has Stoped!"));
	ui.btnStart->setEnabled(true);
	ui.btnExhaust->setEnabled(true);
	ui.btnNext->hide();
}

//��ʼ�춨
void FlowWeightDlg::startVerify()
{
	m_nowOrder = 1;

	//�ж�ʵ�ʼ��ĸ���(���ݻ�ȡ���ı�Ÿ���)
	if (getValidMeterNum() != m_maxMeterNum)
	{
		ui.labelHintPoint->clear();
		QMessageBox *messageBox = new QMessageBox(QMessageBox::Question, tr("Question"), \
			tr("meter count maybe error ! read meter number again?\nclick \'Yes\' to read meter again;or click \'No\' to continue verify"), \
			QMessageBox::Yes|QMessageBox::No, this);
		messageBox->setDefaultButton(QMessageBox::Yes);
		QTimer timer;
		connect(&timer, SIGNAL(timeout()), messageBox, SLOT(close()));
		timer.start(5000);
		if (messageBox->exec()==QMessageBox::Yes)
		{
			ui.btnGoOn->show();
			return;
		}
	}

	if (m_recPtr != NULL)
	{
		delete []m_recPtr;
		m_recPtr = NULL;
	}
	m_recPtr = new Flow_Verify_Record_STR[m_validMeterNum];
	memset(m_recPtr, 0, sizeof(Flow_Verify_Record_STR)*m_validMeterNum);

	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //��¼ʱ���
	m_nowDate = QDateTime::currentDateTime().toString("yyyy-MM-dd"); //��ǰ����'2014-08-07'
	m_validDate = QDateTime::currentDateTime().addYears(VALID_YEAR).addDays(-1).toString("yyyy-MM-dd"); //��Ч��

	m_state = STATE_INIT; //��ʼ״̬

	m_meterStartValue = new float[m_validMeterNum]; //���ֵ 
	memset(m_meterStartValue, 0, sizeof(float)*m_validMeterNum);

	m_meterEndValue = new float[m_validMeterNum];   //����ֵ
	memset(m_meterEndValue, 0, sizeof(float)*m_validMeterNum);

	m_meterTemper = new float[m_validMeterNum];     //���¶�
	memset(m_meterTemper, 0, sizeof(float)*m_validMeterNum);

	m_meterDensity = new float[m_validMeterNum];    //���ܶ�
	memset(m_meterDensity, 0, sizeof(float)*m_validMeterNum);

	m_meterStdValue = new float[m_validMeterNum];   //�����ı�׼ֵ
	memset(m_meterStdValue, 0, sizeof(float)*m_validMeterNum);

	m_meterError = new float[m_validMeterNum];      //���������
	memset(m_meterError, 0, sizeof(float)*m_validMeterNum);
	
	if (m_continueVerify) //�����춨
	{
		if (!judgeBalanceCapacity()) //�ж���ƽ�����Ƿ��ܹ�����춨����
		{
			ui.labelHintPoint->setText(tr("prepare balance capacity ..."));
			openWaterOutValve();
			while (!judgeBalanceCapacity())
			{ 
				QTest::qWait(1000);
			}
			closeWaterOutValve(); //������춨��������رշ�ˮ��
			QTest::qWait(3000); //�ȴ�3����(�ȴ�ˮ���ȶ�)
		}
	}

	//////////////////////////////
	if (m_autopick) //�Զ��ɼ�
	{
		for (int j=0; j<m_flowPointNum; j++)
		{
			m_nowOrder = j+1;
			prepareVerifyFlowPoint(j+1);
		}
	}
	else //�ֶ��ɼ�
	{
		if (prepareVerifyFlowPoint(1)) //��һ��������춨
		{
			ui.btnNext->show();
			ui.btnNext->setFocus();
		}
	}
	//������
}

//��ȡ��Ч������,������ӳ���ϵ��������±�-��λ�ţ�
int FlowWeightDlg::getValidMeterNum()
{
	m_validMeterNum = 0; //������
	bool ok;
	for (int i=0; i<m_maxMeterNum; i++)
	{
		if (NULL == ui.tableWidget->item(i, COLUMN_METER_NUMBER)) //"���"��Ԫ��Ϊ��
		{
			continue;
		}
		ui.tableWidget->item(i, COLUMN_METER_NUMBER)->text().toInt(&ok, 10);
		if (!ok) //���ת��ʧ��(������)
		{
			continue;
		}

		m_meterPosMap[m_validMeterNum] = i+1; //��λ�Ŵ�1��ʼ
		m_validMeterNum++;
	}
	return m_validMeterNum;
}

/*
** �жϱ�λ���Ƿ���Ч(�ñ�λ�Ƿ���Ҫ���)
����:meterPos(��λ��)����1��ʼ
����:������±꣬��0��ʼ
*/
int FlowWeightDlg::isMeterPosValid(int meterPos)
{
	for (int i=0; i<m_validMeterNum; i++)
	{
		if (m_meterPosMap[i] == meterPos)
		{
			return i;
		}
	}
	return -1;
}

/*
** �ж���ƽ�����Ƿ�����춨����
** �����춨ʱ�������ܼ춨����
*/
bool FlowWeightDlg::judgeBalanceCapacity()
{
	bool ret = false;
	float totalQuantity = 0;
	int num = m_paraSetReader->getParams()->total_fp; //��Ч������ĸ���
	for (int i=0; i<num; i++)
	{
		totalQuantity += m_paraSetReader->getParams()->fp_info[i].fp_quantity;
	}
	ret = (ui.lcdBigBalance->value() + totalQuantity) < (m_balMaxWht - 2);
	return ret;
}

/*
** �ж���ƽ�����Ƿ�����춨����
** �������춨ʱ�����㵥�μ춨����
** ע�⣺order��1��ʼ
*/
int FlowWeightDlg::judgeBalanceCapacitySingle(int order)
{
	if (order < 1 || order > VERIFY_POINTS)
	{
		return false;
	}
	bool ret = false;
	float quantity = 0;
	quantity += m_paraSetReader->getParams()->fp_info[order-1].fp_quantity;
	ret = (ui.lcdBigBalance->value() + quantity) < (m_balMaxWht - 2);
	return ret;
}

/*
** ׼������������ļ춨�����б�Ҫ�ļ��
** ע�⣺order��1��ʼ
*/
int FlowWeightDlg::prepareVerifyFlowPoint(int order)
{
	if (order < 1 || m_stopFlag)
	{
		return false;
	}
	if (m_validMeterNum <= 0)
	{
		QMessageBox::warning(this, tr("Warning"), tr("please input meter number"));//�������ţ�
		return false;
	}

	if (!m_continueVerify) //�������춨��ÿ�μ춨��ʼ֮ǰ��Ҫ�ж���ƽ����
	{
		if (!judgeBalanceCapacitySingle(order)) //��ƽ���������㱾�μ춨����
		{
			ui.labelHintPoint->setText(tr("prepare balance capacity ..."));
			openWaterOutValve(); //�򿪷�ˮ������ƽ��ˮ
			while (!judgeBalanceCapacitySingle(order)) //�ȴ���ƽ��ˮ��ֱ�����㱾�μ춨����
			{ 
				QTest::qWait(1000);
			}
			closeWaterOutValve(); //������춨��������رշ�ˮ��
			QTest::qWait(3000);   //�ȴ�3���ӣ��ȴ�ˮ���ȶ�
		}
	}

	int i=0;
	if (m_resetZero) //��ֵ����
	{
		if (m_autopick || order==1 ) //�Զ��ɼ������ǵ�һ���춨��,��Ҫ�ȴ��ȱ��ֵ����
		{
			ui.labelHintPoint->setText(tr("Reset Zero"));
			while (i < RESET_ZERO_TIME && !m_stopFlag) //�ȴ�������ֵ����
			{
				ui.labelHintProcess->setText(tr("please wait %1 seconds for reset zero").arg(RESET_ZERO_TIME-i));
				i++;
				QTest::qWait(1000); 
			}
		}
		memset(m_meterStartValue, 0, sizeof(float)*m_validMeterNum);
		for (int i=0; i<m_validMeterNum; i++)
		{
			ui.tableWidget->item(m_meterPosMap[i]-1, COLUMN_METER_START)->setText(QString("%1").arg(m_meterStartValue[i]));
		}
	}
	else //��ֵ������
	{
		if (order >= 2) //�ڶ����춨��֮��
		{
			if (m_autopick)
			{
				QTest::qWait(2000); //��2�룬��������Ա����һ�εļ춨���
				clearTableContents();
			}
			makeStartValueByLastEndValue(); //��һ�ε���ֵ��Ϊ���εĳ�ֵ
		}
		else //��һ���춨��
		{
			if (!getMeterStartValue()) //��ȡ���ֵ
			{
				return false;
			}
		}
	}

	startVerifyFlowPoint(order);
	return true;
}

//���е���������ļ춨
int FlowWeightDlg::startVerifyFlowPoint(int order)
{
	if (m_stopFlag)
	{
		return false;
	}
	m_balStartV = ui.lcdBigBalance->value(); //��¼��ƽ��ֵ
	m_pipeInTemper = ui.lcdInTemper->value();
	m_pipeOutTemper = ui.lcdOutTemper->value();
	m_realFlow = ui.lcdFlowRate->value();
	m_avgTFCount = 1;

	int portNo = m_paraSetReader->getFpBySeq(order).fp_valve;  //order��Ӧ�ķ��Ŷ˿ں�
	float verifyQuantity = m_paraSetReader->getFpBySeq(order).fp_quantity; //��order�μ춨��Ӧ�ļ춨��
	float frequence = m_paraSetReader->getFpBySeq(order).fp_freq; //order��Ӧ��Ƶ��
	m_controlObj->askSetDriverFreq(frequence);
	if (openValve(portNo)) //�򿪷��ţ���ʼ������
	{
		if (judgeBalanceAndCalcAvgTemperAndFlow(m_balStartV + verifyQuantity)) //����춨��������˹��̵�ƽ���¶Ⱥ�ƽ������
		{
			closeValve(portNo); //�ر�order��Ӧ�ķ���
			QTest::qWait(3000); //�ȴ�3���ӣ�����ƽ��ֵ�ȶ�
			m_balEndV = ui.lcdBigBalance->value(); //��¼��ƽ��ֵ

			for (int m=0; m<m_validMeterNum; m++) //
			{
				m_meterTemper[m] = m_chkAlg->getMeterTempByPos(m_pipeInTemper, m_pipeOutTemper, m_meterPosMap[m]);//����ÿ���������¶�
				m_meterDensity[m] = m_chkAlg->getDensityByQuery(m_meterTemper[m]);//����ÿ���������ܶ�
				m_meterStdValue[m] = m_chkAlg->getStdVolByPos((m_balEndV-m_balStartV), m_pipeInTemper, m_pipeOutTemper, m_meterPosMap[m]); //����ÿ�������������׼ֵ

				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_FLOW_POINT, new QTableWidgetItem(QString::number(m_realFlow, 'f', 2)));//������
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_BAL_START, new QTableWidgetItem(QString::number(m_balStartV, 'f', 3)));//��ƽ��ֵ
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_BAL_END, new QTableWidgetItem(QString::number(m_balEndV, 'f', 3)));    //��ƽ��ֵ
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_TEMPER, new QTableWidgetItem(QString::number(m_meterTemper[m], 'f', 2)));  //�¶�
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_DENSITY, new QTableWidgetItem(QString::number(m_meterDensity[m], 'f', 3)));//�ܶ�
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_STD_VALUE, new QTableWidgetItem(QString::number(m_meterStdValue[m], 'f', 3)));//��׼ֵ
			}

			if (order==m_flowPointNum) //���һ��������
			{
				stopVerify(); //ֹͣ�춨
			}

			if (!getMeterEndValue()) //��ȡ����ֵ
			{
				return false;
			}

			if (m_autopick && !m_stopFlag) //�Զ��ɼ�
			{
				calcAllMeterError();
				saveAllVerifyRecords();
			}
		}
	}

	return true;
}

/*
** �������б��������
*/
int FlowWeightDlg::calcAllMeterError()
{
	for (int i=0; i<m_validMeterNum; i++)
	{
		calcMeterError(i);
	}
	return true; 
}

/*
** ����ĳ�����������
** ���������
**     idx:��������������
*/
int FlowWeightDlg::calcMeterError(int idx)
{
	m_meterError[idx] = 100*(m_meterEndValue[idx] - m_meterStartValue[idx] - m_meterStdValue[idx])/m_meterStdValue[idx];//����ĳ��������
	ui.tableWidget->setItem(m_meterPosMap[idx]-1, COLUMN_ERROR, new QTableWidgetItem(QString::number(m_meterError[idx], 'f', 4))); //���
	float stdError = m_flowSC*(m_gradeErrA[m_nowParams->m_grade] + m_gradeErrB[m_nowParams->m_grade]*m_mapNormalFlow[m_standard]/m_realFlow); //��׼���=���Ҫ�����*������ȫϵ��
	if (fabs(m_meterError[idx]) > stdError)
	{
		ui.tableWidget->item(m_meterPosMap[idx]-1, COLUMN_ERROR)->setForeground(QBrush(Qt::red));
	}
	QString meterNoPrefix = getNumPrefixOfManufac(m_nowParams->m_manufac);
	QString meterNoStr = meterNoPrefix + QString("%1").arg(ui.tableWidget->item(m_meterPosMap[idx]-1, 0)->text(), 8, '0');

	strncpy_s(m_recPtr[idx].timestamp, m_timeStamp.toAscii(), TIMESTAMP_LEN);
	m_recPtr[idx].flowPoint = m_realFlow;
	strcpy_s(m_recPtr[idx].meterNo, meterNoStr.toAscii());
	m_recPtr[idx].flowPointIdx = m_nowOrder; //
	m_recPtr[idx].methodFlag = WEIGHT_METHOD; //������
	m_recPtr[idx].meterValue0 = m_meterStartValue[idx];
	m_recPtr[idx].meterValue1 = m_meterEndValue[idx];
	m_recPtr[idx].balWeight0 = m_balStartV;
	m_recPtr[idx].balWeight1 = m_balEndV;
	m_recPtr[idx].pipeTemper = m_meterTemper[idx]; 
	m_recPtr[idx].density = m_meterDensity[idx];
	m_recPtr[idx].stdValue = m_meterStdValue[idx];
	m_recPtr[idx].dispError = m_meterError[idx];
	m_recPtr[idx].grade = m_nowParams->m_grade;
	m_recPtr[idx].stdError = stdError; //��ı�׼���
	m_recPtr[idx].result = (fabs(m_recPtr[idx].dispError) <= fabs(m_recPtr[idx].stdError)) ? 1 : 0;
	m_recPtr[idx].meterPosNo = m_meterPosMap[idx];
	m_recPtr[idx].standard = m_standard;
	m_recPtr[idx].model = m_model;
	m_recPtr[idx].pickcode = m_pickcode; //�ɼ�����
	m_recPtr[idx].manufactDept = m_nowParams->m_manufac;
	m_recPtr[idx].verifyDept = m_nowParams->m_vcomp;
	m_recPtr[idx].verifyPerson = m_nowParams->m_vperson;
	m_recPtr[idx].checkPerson = m_nowParams->m_cperson;
	strncpy_s(m_recPtr[idx].verifyDate, m_nowDate.toAscii(), DATE_LEN);
	strncpy_s(m_recPtr[idx].validDate, m_validDate.toAscii(), DATE_LEN);
	m_recPtr[idx].airPress = m_nowParams->m_airpress.toFloat();
	m_recPtr[idx].envTemper = m_nowParams->m_temper.toFloat();
	m_recPtr[idx].envHumidity = m_nowParams->m_humidity.toFloat();

	return true; 
}

//�򿪷���
int FlowWeightDlg::openValve(UINT8 portno)
{
	m_controlObj->askControlRelay(portno, VALVE_OPEN);
	if (m_portsetinfo.version==OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(portno, VALVE_OPEN);
	}
	return true;
}

//�رշ���
int FlowWeightDlg::closeValve(UINT8 portno)
{
	m_controlObj->askControlRelay(portno, VALVE_CLOSE);
	if (m_portsetinfo.version==OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(portno, VALVE_CLOSE);
	}
	return true;
}

//�������ţ��򿪻��߹ر�
int FlowWeightDlg::operateValve(UINT8 portno)
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
int FlowWeightDlg::openWaterPump()
{
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->askControlWaterPump(m_nowPortNo, VALVE_OPEN);
	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_nowPortNo, VALVE_OPEN);
	}
	return true;
}

//�ر�ˮ��
int FlowWeightDlg::closeWaterPump()
{
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->askControlWaterPump(m_nowPortNo, VALVE_CLOSE);
	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_nowPortNo, VALVE_CLOSE);
	}
	return true;
}

//����ˮ�� �򿪻��߹ر�
int FlowWeightDlg::operateWaterPump()
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
void FlowWeightDlg::slotSetValveBtnStatus(const UINT8 &portno, const bool &status)
{
	m_valveStatus[portno] = status;
	setValveBtnBackColor(m_valveBtn[portno], m_valveStatus[portno]);
}

//��Ӧ���ڷ����ڳɹ�
void FlowWeightDlg::slotSetRegulateOk()
{
// 	setRegBtnBackColor(m_regBtn[m_nowRegIdx], true);
}


//�Զ���ȡ��ųɹ� ��ʾ���
void FlowWeightDlg::slotSetMeterNumber(const QString& comName, const QString& meterNo)
{
	int meterPos = m_readComConfig->getMeterPosByComName(comName);
	if (meterPos < 1)
	{
		return;
	}
	ui.tableWidget->setItem(meterPos-1, COLUMN_METER_NUMBER, new QTableWidgetItem(meterNo.right(8))); //���
}

/*
** �Զ���ȡ�������ɹ� ��ʾ������
*/
void FlowWeightDlg::slotSetMeterFlow(const QString& comName, const float& flow)
{
	int meterPos = m_readComConfig->getMeterPosByComName(comName);
	if (meterPos < 1)
	{
		return;
	}
	int idx = isMeterPosValid(meterPos);
	if (m_state == STATE_START_VALUE) //��ֵ
	{
		ui.tableWidget->setItem(meterPos - 1, COLUMN_METER_START, new QTableWidgetItem(QString::number(flow)));
		if (idx>=0 && m_meterStartValue!=NULL)
		{
			m_meterStartValue[idx] = flow;
		}
	}
	else if (m_state == STATE_END_VALUE) //��ֵ
	{
		ui.tableWidget->setItem(meterPos - 1, COLUMN_METER_END, new QTableWidgetItem(QString::number(flow)));
		if (idx>=0 && m_meterEndValue!=NULL)
		{
			m_meterEndValue[idx] = flow;
		}
	}
}

//���÷��Ű�ť����ɫ
void FlowWeightDlg::setValveBtnBackColor(QToolButton *btn, bool status)
{
	if (NULL == btn)
	{
		return;
	}
	if (status) //���Ŵ� ��ɫ
	{
		btn->setStyleSheet("background-color:rgb(0,255,0);border:0px;border-radius:10px;");
// 		btn->setStyleSheet("border-image:url(:/weightmethod/images/btncheckon.png)");
	}
	else //���Źر� ��ɫ
	{
		btn->setStyleSheet("background-color:rgb(255,0,0);border:0px;border-radius:10px;");
// 		btn->setStyleSheet("border-image:url(:/weightmethod/images/btncheckoff.png)");
	}
}

//���õ��ڷ���ť����ɫ
void FlowWeightDlg::setRegBtnBackColor(QPushButton *btn, bool status)
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
void FlowWeightDlg::on_btnParaSet_clicked()
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
void FlowWeightDlg::on_btnWaterIn_clicked() //��ˮ��
{
	m_nowPortNo = m_portsetinfo.waterInNo;
	operateValve(m_nowPortNo);
}

void FlowWeightDlg::on_btnWaterOut_clicked() //��ˮ��
{
	m_nowPortNo = m_portsetinfo.waterOutNo;
	operateValve(m_nowPortNo);
}

void FlowWeightDlg::on_btnValveBig_clicked() //��������
{
	m_nowPortNo = m_portsetinfo.bigNo;
	operateValve(m_nowPortNo);
}

void FlowWeightDlg::on_btnValveMiddle1_clicked() //����һ��
{
	m_nowPortNo = m_portsetinfo.middle1No;
	operateValve(m_nowPortNo);
}

void FlowWeightDlg::on_btnValveMiddle2_clicked() //��������
{
	m_nowPortNo = m_portsetinfo.middle2No;
	operateValve(m_nowPortNo);
}

void FlowWeightDlg::on_btnValveSmall_clicked() //С������
{
	m_nowPortNo = m_portsetinfo.smallNo;
	operateValve(m_nowPortNo);
}

/*
** ����ˮ�ÿ���
*/
void FlowWeightDlg::on_btnWaterPump_clicked()
{
/*	if (ui.spinBoxFrequency->value() <= 0)
	{
		QMessageBox::warning(this, tr("Warning"), tr("please input frequency of transducer"));//�����ñ�Ƶ��Ƶ�ʣ�
		ui.spinBoxFrequency->setFocus();
	}
 	m_controlObj->askControlRegulate(m_portsetinfo.pumpNo, ui.spinBoxFrequency->value());
*/
	m_nowPortNo = m_portsetinfo.pumpNo;
	operateWaterPump();
}

/*
** ���ñ�Ƶ��Ƶ��
*/
void FlowWeightDlg::on_btnSetFreq_clicked()
{
	m_controlObj->askSetDriverFreq(ui.spinBoxFreq->value());
}

//��ȡ���ֵ
int FlowWeightDlg::getMeterStartValue()
{
	if (m_stopFlag)
	{
		return false;
	}

	m_state = STATE_START_VALUE;

	if (m_autopick) //�Զ��ɼ�
	{
		readAllMeter();
		QTest::qWait(2000); //�ȴ����ڷ�������
		return true;
	}
	else //�ֶ�����
	{
		QMessageBox::information(this, tr("Hint"), tr("please input init value of heat meter"));//�������������ֵ��
		ui.tableWidget->setCurrentCell(m_meterPosMap[0]-1, COLUMN_METER_START); //��λ����һ����Ҫ�����ֵ�ĵط�
		return false;
	}
}

//��һ�ε���ֵ��Ϊ���εĳ�ֵ
void FlowWeightDlg::makeStartValueByLastEndValue()
{
	float flow = m_paraSetReader->getFpBySeq(m_nowOrder).fp_verify;
	for (int i=0; i<m_validMeterNum; i++)
	{
		m_meterStartValue[i] = m_meterEndValue[i];
		ui.tableWidget->item(m_meterPosMap[i]-1, COLUMN_METER_START)->setText(QString("%1").arg(m_meterStartValue[i]));
 		ui.tableWidget->item(m_meterPosMap[i]-1, COLUMN_FLOW_POINT)->setText(QString("%1").arg(flow));
	}
}

//��ȡ����ֵ
int FlowWeightDlg::getMeterEndValue()
{
	if (m_stopFlag)
	{
		return false;
	}
		
	m_state = STATE_END_VALUE;

	if (m_autopick) //�Զ��ɼ�
	{
		readAllMeter();
		QTest::qWait(2000); //�ȴ����ڷ�������
		return true;
	}
	else //�ֶ�����
	{
		QMessageBox::information(this, tr("Hint"), tr("please input end value of heat meter"));//��������������ֵ��
		ui.tableWidget->setCurrentCell(m_meterPosMap[0]-1, COLUMN_METER_END); //��λ����һ����Ҫ������ֵ�ĵط�
		return false;
	}
}

/*
** ��Ӧ�����û���������ֵ������ֵ
   ���������
      row����������0��ʼ
	  column����������0��ʼ
*/
void FlowWeightDlg::on_tableWidget_cellChanged(int row, int column)
{
// 	if (m_autopick) //�Զ��ɼ�
// 	{
// 		return;
// 	}

	if (NULL==ui.tableWidget->item(row,  column) || NULL==m_meterStartValue || NULL==m_meterEndValue)
	{
		return;
	}

	int meterPos = row + 1; //��λ��
	int idx = -1;
	idx = isMeterPosValid(meterPos);
	if (idx < 0)
	{
		return;
	}
	bool ok;
	if (column==COLUMN_METER_START && m_state==STATE_START_VALUE) //���ֵ�� �� ���������ֵ
	{
		m_meterStartValue[idx] = ui.tableWidget->item(row, column)->text().toFloat(&ok);
		if (!ok)
		{
			QMessageBox::warning(this, tr("Warning"), tr("Error: please input digits"));//�����������������
			return;
		}

		if (meterPos == m_meterPosMap[m_validMeterNum-1]) //�������һ�����ֵ
		{
			startVerifyFlowPoint(m_nowOrder);
		}
		else //�������һ�����ֵ,�Զ���λ����һ��
		{
			ui.tableWidget->setCurrentCell(m_meterPosMap[idx+1]-1, column);
		}
	}

	if (column==COLUMN_METER_END && m_state==STATE_END_VALUE) //����ֵ�� �� ����������ֵ
	{
		m_meterEndValue[idx] = ui.tableWidget->item(row, column)->text().toFloat(&ok);
		if (!ok)
		{
			QMessageBox::warning(this, tr("Warning"), tr("Error: please input digits"));//�����������������
			return;
		}
		calcMeterError(idx);

		if (meterPos == m_meterPosMap[m_validMeterNum-1]) //�������һ������ֵ
		{
			saveAllVerifyRecords();
		}
		else //�������һ������ֵ,�Զ���λ����һ��
		{
			ui.tableWidget->setCurrentCell(m_meterPosMap[idx+1]-1, column);
		}
	}
}

/*
** �������б����ļ춨��¼
*/
int FlowWeightDlg::saveAllVerifyRecords()
{
 	insertFlowVerifyRec(m_recPtr, m_validMeterNum);
	return true;
}

//����������б��㲥��ַ����
void FlowWeightDlg::on_btnAllReadMeter_clicked()
{
	for (int j=0; j<m_maxMeterNum; j++)
	{
		m_meterObj[j].askReadMeter();
	}
}

//���ü춨״̬�����б�
void FlowWeightDlg::on_btnAllVerifyStatus_clicked()
{
	for (int i=0; i<m_maxMeterNum; i++)
	{
		m_meterObj[i].askSetVerifyStatus();
	}
}

//���������б�
void FlowWeightDlg::on_btnAllAdjError_clicked()
{

}

//�޸ı�ţ����б�
void FlowWeightDlg::on_btnAllModifyNO_clicked()
{
	for (int i=0; i<m_maxMeterNum; i++)
	{
		m_meterObj[i].askModifyMeterNO("11110000000000", ui.tableWidget->item(i, COLUMN_METER_NUMBER)->text());
	}
}

/*
** �޸ı��
** ���������
	row:�кţ���row����֪����ǰ�ȱ��Ӧ�Ĵ��ڡ���š����ȵ�
   ע�⣺���Ϊ14λ
*/
void FlowWeightDlg::slotModifyMeterNO(const int &row)
{
	qDebug()<<"slotModifyMeterNO row ="<<row;
	m_meterObj[row].askModifyMeterNO("11110000000000", ui.tableWidget->item(row, COLUMN_METER_NUMBER)->text());
}

/*
** �������
** ���������
	row:�кţ���row����֪����ǰ�ȱ��Ӧ�Ĵ��ڡ���š����ȵ�
*/
void FlowWeightDlg::slotAdjustError(const int &row)
{
	qDebug()<<"slotAdjustError row ="<<row;
// 	QString meterNO = ui.tableWidget->item(row, COLUMN_METER_NUMBER)->text();
// 	float bigErr = ui.lnEditBigNewError->text().toFloat();
// 	float mid2Err = ui.lnEditMid2NewError->text().toFloat();
// 	float mid1Err = ui.lnEditMid1NewError->text().toFloat();
// 	float smallErr = ui.lnEditSmallNewError->text().toFloat();
// 	m_meterObj->askModifyFlowCoe(meterNO, bigErr, mid2Err, mid1Err, smallErr);
}

/*
** ��ȡ���
** ���������
	row:�кţ���row����֪����ǰ�ȱ��Ӧ�Ĵ��ڡ���š����ȵ�
*/
void FlowWeightDlg::slotReadMeter(const int &row)
{
	qDebug()<<"slotReadMeter row ="<<row;
	m_meterObj[row].askReadMeter();
}

/*
** �춨״̬
** ���������
	row:�кţ���row����֪����ǰ�ȱ��Ӧ�Ĵ��ڡ���š����ȵ�
*/
void FlowWeightDlg::slotVerifyStatus(const int &row)
{
	qDebug()<<"slotVerifyStatus row ="<<row;
	m_meterObj[row].askSetVerifyStatus();
}
