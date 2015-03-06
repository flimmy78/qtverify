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
 	ui.btnNext->hide(); //����"��һ��"��ť
	ui.btnStart->hide();
	m_inputStartValue = false;
	m_inputEndValue = false;

	//��ͬ�ȼ����������Ӧ�ı�׼���,��λ%
	m_gradeErr[1] = 1.00f;
	m_gradeErr[2] = 2.00f;
	m_gradeErr[3] = 3.00f;

	if (!getPortSetIni(&m_portsetinfo)) //��ȡ��λ���˿ں�������Ϣ
	{
		QMessageBox::warning(this, tr("Warning"), tr("Warning:get port set info failed!"));//��ȡ��λ���˿ں�������Ϣʧ��!���������ã�
	}

	m_stopFlag = false; //�˳�����󣬲��ټ����ƽ����

	m_readComConfig = new ReadComConfig(); //���������ýӿ�

	m_balanceObj = NULL;
	initBalanceCom();		//��ʼ����ƽ����

	m_tempObj = NULL;
	m_tempTimer = NULL;
	initTemperatureCom();	//��ʼ���¶Ȳɼ�����

	m_controlObj = NULL;
	initControlCom();		//��ʼ�����ƴ���

	m_balLastValue = 0.0;   //�����ж���ƽֵ�Ƿ���ͻ��

	//����������
	m_totalcount = 0;
	m_startWeight = 0.0;
	m_endWeight = 0.0;
	memset(m_deltaWeight, 0, sizeof(float)*FLOW_SAMPLE_NUM);
	m_flowRateTimer = new QTimer();
	connect(m_flowRateTimer, SIGNAL(timeout()), this, SLOT(slotFreshFlowRate()));
	m_flowRateTimer->start(TIMEOUT_FLOW_SAMPLE);

	m_chkAlg = new CAlgorithm();//������ӿ�

	initValveStatus();      //ӳ���ϵ����ʼ������״̬

	m_exaustTimer = new QTimer(this); //������ʱ��
	connect(m_exaustTimer, SIGNAL(timeout()), this, SLOT(slotExaustFinished()));

	m_tempCount = 1; //����ƽ���¶��õ��ۼӼ�����
	m_nowOrder = 0;  //��ǰ���еļ춨���

	m_nowParams = new Verify_Params_STR;
	memset(m_nowParams, 0, sizeof(Verify_Params_STR));
	m_continueVerify = true; //�����춨
	m_resetZero = false;     //��ֵ����
	m_autopick = false;      //�Զ��ɼ�
	m_flowPointNum = 0;      //���������
	m_maxMeterNum = 0;       //ĳ�������֧�ֵļ�����
	m_validMeterNum = 0;     //ʵ�ʼ�����
	m_exaustSecond = 45;     //Ĭ������ʱ��45��
	m_manufac = 0;           //���쳧�� Ĭ�ϵ�³
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
	m_flowPoint = 0;          //����(m3/h)

	m_recPtr = NULL;

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

	m_meterThread = NULL;
	m_meterObj = NULL;
	initMeterCom(); //��ʼ��������ͨѶ����

	if (!isWaterOutValveOpen())
	{
		qDebug()<<"��ˮ����δ��";
		openWaterOutValve();
	}
}

FlowWeightDlg::~FlowWeightDlg()
{
}

void FlowWeightDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^FlowWeightDlg::closeEvent";

	m_stopFlag = true;

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

	if (m_tempTimer) //��ʱ��
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

		for (int i=0; i<m_maxMeterNum; i++)
		{
			m_meterThread[i].exit();
		}
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
	
	m_tempTimer->start(TIMEOUT_TEMPER); //���������¶�
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
	//��ƽ��ֵ�ӿ��ư��ȡ
// 	connect(m_controlObj, SIGNAL(controlGetBalanceValueIsOk(const float&)), this, SLOT(slotFreshBalanceValue(const float &)));
}

//������ͨѶ����
void FlowWeightDlg::initMeterCom()
{
	if (m_maxMeterNum <= 0)
	{
		return;
	}

	m_meterThread = new ComThread[m_maxMeterNum];

	m_meterObj = new MeterComObject[m_maxMeterNum];
	int i=0;
	for (i=0; i<m_maxMeterNum; i++)
	{
		m_meterObj[i].moveToThread(&m_meterThread[i]);
		m_meterObj[i].setProtocolVersion(m_manufac); //���ñ�Э������
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

	//��ʼ�� ȫ������״̬Ϊ�ر�
	m_valveStatus[m_portsetinfo.bigNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.smallNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle1No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle2No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterOutNo] = VALVE_CLOSE;
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
	if (fabs(m_balLastValue - balValue) > 1) //��ƽÿ�α仯�����ܴ���1kg
	{
		m_balLastValue = balValue;
		return;
	}
	QString wht = QString::number(balValue, 'f', 3);
	ui.lcdBigBalance->display(wht);
	m_balLastValue = balValue;
	if (balValue > BALANCE_CAPACITY) //��ֹ��ƽ��� ������ƽ����Ϊ100kg
	{
		m_controlObj->askControlRelay(m_portsetinfo.waterInNo, VALVE_CLOSE);// �رս�ˮ��
		m_controlObj->askControlRelay(m_portsetinfo.waterOutNo, VALVE_OPEN);// �򿪷�ˮ��	
		if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
		{
			slotSetValveBtnStatus(m_portsetinfo.waterOutNo, VALVE_OPEN);
			slotSetValveBtnStatus(m_portsetinfo.waterInNo, VALVE_CLOSE);
		}
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
// 	qDebug()<<"FlowWeightDlg::slotFreshFlow thread:"<<QThread::currentThreadId();
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
	ui.lcdFlowRate->display(QString::number(flowValue, 'f', 3)); //��ui.lcdFlowRate����ʾ����
	m_totalcount ++;//�������ۼ�
	m_startWeight = m_endWeight;//����ǰֵ����, ��Ϊ�´�����ĳ�ֵ
}

//��⴮�ڡ��˿������Ƿ���ȷ
int FlowWeightDlg::isComAndPortNormal()
{
	return true;
}

//����ˮ�����Ƿ�� ��:true���ر�:false
int FlowWeightDlg::isWaterOutValveOpen()
{
	return true;
}

//��ȡ��ǰ�춨����
int FlowWeightDlg::readNowParaConfig()
{
	if (NULL == m_paraSetReader)
	{
		return false;
	}

	m_nowParams = m_paraSetReader->getParams();
	m_continueVerify = m_nowParams->bo_converify; //�����춨
	m_resetZero = m_nowParams->bo_resetzero; //��ֵ����
	m_autopick = m_nowParams->bo_autopick;   //�Զ��ɼ�
	m_flowPointNum = m_nowParams->total_fp;  //��Ч������ĸ��� 
	m_exaustSecond = m_nowParams->ex_time;   //����ʱ��
	m_standard = m_nowParams->m_stand;       //����
	m_model = m_nowParams->m_model;   //���ͺ�
	m_meterType = m_nowParams->m_type;//������
	m_maxMeterNum = m_nowParams->m_maxMeters;//��ͬ�����Ӧ�����������
	m_manufac = m_nowParams->m_manufac; //���쳧��

	initTableWidget();
	showNowKeyParaConfig();

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

	QStringList vLabels;
	for (int i=0; i< m_maxMeterNum; i++)
	{
		vLabels<<QString(QObject::tr("meterPosNo%1").arg(i+1));

		ui.tableWidget->setItem(i, COLUMN_METER_NUMBER, new QTableWidgetItem(QString()));
		ui.tableWidget->setItem(i, COLUMN_METER_START, new QTableWidgetItem(QString()));
		ui.tableWidget->setItem(i, COLUMN_METER_END, new QTableWidgetItem(QString()));

		QPushButton *btnModNo = new QPushButton(tr("Modify NO."));
		ui.tableWidget->setCellWidget(i, COLUMN_MODIFY_METERNO, btnModNo);
		m_signalMapper1->setMapping(btnModNo, i);
		connect(btnModNo, SIGNAL(clicked()), m_signalMapper1, SLOT(map()));

		QPushButton *btnAdjErr = new QPushButton(tr("Adjust Err"));
		ui.tableWidget->setCellWidget(i, COLUMN_ADJUST_ERROR, btnAdjErr);
		m_signalMapper2->setMapping(btnAdjErr, i);
		connect(btnAdjErr, SIGNAL(clicked()), m_signalMapper2, SLOT(map()));
	}
	connect(m_signalMapper1, SIGNAL(mapped(const int &)),this, SLOT(slotModifyMeterNo(const int &)));
	connect(m_signalMapper2, SIGNAL(mapped(const int &)),this, SLOT(slotAdjustError(const int &)));

	ui.tableWidget->setVerticalHeaderLabels(vLabels);
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

/*
** ���"������ť"����ʼ�춨
*/
void FlowWeightDlg::on_btnExhaust_clicked()
{
	if (!isDataCollectNormal())
	{
		qWarning()<<"���ݲɼ�������������";
		return;
	}

	if (!openAllValveAndPump())
	{
		qWarning()<<"�����з��ź�ˮ�� ʧ��!";
		return;
	}
	m_stopFlag = false;
	clearTableContents();
	m_validMeterNum = 0;

	m_exaustSecond = m_nowParams->ex_time;
	m_exaustTimer->start(1000);//��ʼ��������ʱ
	ui.labelHintProcess->setText(tr("Exhaust countdown: %1 second").arg(m_exaustSecond));
	qDebug()<<"��������ʱ:"<<m_exaustSecond<<"��";

	if (m_autopick) //�Զ�����
	{
		readMeter();
	}
	else //�ֶ�����
	{
		ui.labelHintPoint->setText(tr("Please input meter number!"));
	}
	
	return;
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
	openValve(m_portsetinfo.waterOutNo);
	openValve(m_portsetinfo.bigNo);
	openValve(m_portsetinfo.middle1No);
	openValve(m_portsetinfo.middle2No);
	openValve(m_portsetinfo.smallNo);
	openValve(m_portsetinfo.waterInNo);

	//��ˮ��
	m_controlObj->askControlWaterPump(m_portsetinfo.pumpNo, VALVE_OPEN);
	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_portsetinfo.pumpNo, VALVE_OPEN);
	}

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

	ui.labelHintPoint->setText(tr("prepare balance ..."));

	//�ж���ƽ����,���С��Ҫ��ĳ�ʼ����(5kg)����رշ�ˮ�����򿪴�������
	if (ui.lcdBigBalance->value() < BALANCE_START_VALUE)
	{
		if (!closeWaterOutValve()) 
		{
			qWarning()<<"�رշ�ˮ��ʧ��";
		}

		if (!openBigFlowValve())
		{
			qWarning()<<"�򿪴�������ʧ��";
		}
	}

	//�жϲ��ȴ���ƽ���������ڳ�ʼ����(5kg)
	if (judgeBalanceInitValue(BALANCE_START_VALUE))
	{
		if (!closeBigFlowValve())
		{
			qWarning()<<"�رմ�������ʧ��";
		}
	}

	if (setMeterVerifyStatus()) //���ü춨״̬�ɹ�
	{
		startVerify();
	}
}

/*
** ��ȡ�ȱ�
*/
int FlowWeightDlg::readMeter()
{
	on_btnReadMeter_clicked();
	return true;
}

//�������������춨״̬
int FlowWeightDlg::setMeterVerifyStatus()
{
	for (int i=0; i<m_maxMeterNum; i++)
	{
		m_meterObj[i].askSetVerifyStatus();
	}

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

//�򿪴������㷧��
int FlowWeightDlg::openBigFlowValve()
{
	openValve(m_portsetinfo.bigNo);
	return true;
}

//�رմ������㷧��
int FlowWeightDlg::closeBigFlowValve()
{
	closeValve(m_portsetinfo.bigNo);
	return true;
}

//��Ӧ������ƽ�����ı仯
int FlowWeightDlg::judgeBalanceInitValue(float v)
{
	while (!m_stopFlag && (ui.lcdBigBalance->value() < v))
	{
		qDebug()<<"��ƽ���� ="<<ui.lcdBigBalance->value()<<", С��Ҫ������� "<<v;
		QTest::qWait(1000);
	}

	return true;
}

int FlowWeightDlg::judgeBalanceAndCalcAvgTemper(float targetV)
{
	int second;
	float nowFlow =m_paraSetReader->getFpBySeq(m_nowOrder).fp_verify;;
	while (!m_stopFlag && (ui.lcdBigBalance->value() < targetV))
	{
		qDebug()<<"��ƽ���� ="<<ui.lcdBigBalance->value()<<", С��Ҫ������� "<<targetV;
		m_pipeInTemper += ui.lcdInTemper->value();
		m_pipeOutTemper += ui.lcdOutTemper->value();
		m_tempCount++;

		second = 3.6*(targetV - ui.lcdBigBalance->value())/nowFlow;
		ui.labelHintPoint->setText(tr("NO. %1 flow point: %2 m3/h").arg(m_nowOrder).arg(nowFlow));
		ui.labelHintProcess->setText(tr("Verifying...\nPlease wait for about %1 second").arg(second));
		QTest::qWait(1000);
	}

	m_pipeInTemper = m_pipeInTemper/m_tempCount;   //���ƽ���¶�
	m_pipeOutTemper = m_pipeOutTemper/m_tempCount; //����ƽ���¶�
	ui.labelHintPoint->setText(tr("NO. %1 flow point: %2 m3/h").arg(m_nowOrder).arg(nowFlow));
	ui.labelHintProcess->setText(tr("Verify Finished!"));
	if (m_nowOrder == m_flowPointNum)
	{
		ui.labelHintProcess->setText(tr("All flow points has verified !"));
		ui.btnNext->hide();
	}
	return true;
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
	startVerify();
	ui.btnStart->hide();
}

//���"��һ��"��ť
void FlowWeightDlg::on_btnNext_clicked()
{
	if (m_nowOrder >= m_flowPointNum)
	{
		QMessageBox::warning(this, tr("Warning"), tr("all flow points has verified!"));
		return;
	}

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
	m_stopFlag = true; //���ټ����ƽ����
	m_inputStartValue = false;
	m_inputEndValue = false;
	
	m_exaustTimer->stop();//ֹͣ������ʱ��

	//�رս�ˮ�������������㷧��

	//�򿪷�ˮ��

	//ֹͣˮ��

	ui.labelHintProcess->setText(tr("Verify has Stoped!"));
}

//��ʼ�춨
void FlowWeightDlg::startVerify()
{
	m_nowOrder = 1;

	//�ж�ʵ�ʼ��ĸ���(���ݻ�ȡ���ı�Ÿ���)
	if (getValidMeterNum() <= 0)
	{
		QMessageBox::warning(this, tr("Warning"), tr("please input meter number, then click \"start\" button!"));//�������ţ�Ȼ����'��ʼ'��ť
		ui.btnStart->show();
		return;
	}

	if (m_recPtr != NULL)
	{
		delete []m_recPtr;
		m_recPtr = NULL;
	}
	m_recPtr = new Flow_Verify_Record_STR[m_validMeterNum];
	memset(m_recPtr, 0, sizeof(Flow_Verify_Record_STR)*m_validMeterNum);

	m_flowPoint = m_paraSetReader->getFpBySeq(1).fp_verify;//��һ��������
	for (int m=0; m<m_validMeterNum; m++) //
	{
		ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_FLOW_POINT, new QTableWidgetItem(QString::number(m_flowPoint, 'f', 2)));//������
	}

	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //��¼ʱ���
	m_nowDate = QDateTime::currentDateTime().toString("yyyy-MM-dd"); //��ǰ����'2014-08-07'
	m_validDate = QDateTime::currentDateTime().addYears(VALID_YEAR).addDays(-1).toString("yyyy-MM-dd"); //��Ч��

	m_startValueFlag = true; //Ĭ���ǳ�ֵ

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
	ret = (ui.lcdBigBalance->value() + totalQuantity) < BALANCE_CAPACITY; //������ƽ����Ϊ100kg
	return ret;
}

/*
** �ж���ƽ�����Ƿ�����춨����
** �������춨ʱ�����㵥�μ춨����
*/
int FlowWeightDlg::judgeBalanceCapacitySingle(int order)
{
	return true;
}

/*
** ׼������������ļ춨�����б�Ҫ�ļ��
** ע�⣺order��1��ʼ
*/
int FlowWeightDlg::prepareVerifyFlowPoint(int order)
{
	if (order < 1)
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
			while (i < RESET_ZERO_TIME) //�ȴ�������ֵ����
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
	m_balStartV = ui.lcdBigBalance->value(); //��¼��ƽ��ֵ
	m_pipeInTemper = ui.lcdInTemper->value();
	m_pipeOutTemper = ui.lcdOutTemper->value();
	m_tempCount = 1;

	m_flowPoint = m_paraSetReader->getFpBySeq(order).fp_verify;//order��Ӧ��������
	int portNo = m_paraSetReader->getFpBySeq(order).fp_valve;  //order��Ӧ�ķ��Ŷ˿ں�
	float verifyQuantity = m_paraSetReader->getFpBySeq(order).fp_quantity; //��order�μ춨��Ӧ�ļ춨��
	if (openValve(portNo)) //�򿪷��ţ���ʼ������
	{
		if (judgeBalanceAndCalcAvgTemper(m_balStartV + verifyQuantity)) //����춨��������˹��̵�ƽ���¶�
		{
			closeValve(portNo); //�ر�order��Ӧ�ķ���
			QTest::qWait(3000); //�ȴ�3���ӣ�����ƽ��ֵ�ȶ�
			m_balEndV = ui.lcdBigBalance->value(); //��¼��ƽ��ֵ

			for (int m=0; m<m_validMeterNum; m++) //
			{
				m_meterTemper[m] = m_chkAlg->getMeterTempByPos(m_pipeInTemper, m_pipeOutTemper, m_meterPosMap[m]);//����ÿ���������¶�
				m_meterDensity[m] = m_chkAlg->getDensityByQuery(m_meterTemper[m]);//����ÿ���������ܶ�
				m_meterStdValue[m] = m_chkAlg->getStdVolByPos((m_balEndV-m_balStartV), m_pipeInTemper, m_pipeOutTemper, m_meterPosMap[m]); //����ÿ�������������׼ֵ

				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_FLOW_POINT, new QTableWidgetItem(QString::number(m_flowPoint, 'f', 2)));//������
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_BAL_START, new QTableWidgetItem(QString::number(m_balStartV, 'f', 3)));//��ƽ��ֵ
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_BAL_END, new QTableWidgetItem(QString::number(m_balEndV, 'f', 3)));    //��ƽ��ֵ
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_TEMPER, new QTableWidgetItem(QString::number(m_meterTemper[m], 'f', 2)));  //�¶�
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_DENSITY, new QTableWidgetItem(QString::number(m_meterDensity[m], 'f', 3)));//�ܶ�
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_STD_VALUE, new QTableWidgetItem(QString::number(m_meterStdValue[m], 'f', 3)));//��׼ֵ
			}

			if (!getMeterEndValue()) //��ȡ����ֵ
			{
				return false;
			}

			if (m_autopick) //�Զ��ɼ�
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

	QString meterNoPrefix = getNumPrefixOfManufac(m_nowParams->m_manufac);
	QString meterNoStr = meterNoPrefix + QString("%1").arg(ui.tableWidget->item(m_meterPosMap[idx]-1, 0)->text(), 8, '0');

	strncpy_s(m_recPtr[idx].timestamp, m_timeStamp.toAscii(), TIMESTAMP_LEN);
	m_recPtr[idx].flowPoint = m_flowPoint;
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
	m_recPtr[idx].stdError = m_gradeErr[m_nowParams->m_grade]; //������ ��׼���
	m_recPtr[idx].result = (fabs(m_recPtr[idx].dispError) <= fabs(m_recPtr[idx].stdError)) ? 1 : 0;
	m_recPtr[idx].meterPosNo = m_meterPosMap[idx];
	m_recPtr[idx].standard = m_standard;
	m_recPtr[idx].model = m_model;
	m_recPtr[idx].meterType = m_meterType; //������
	m_recPtr[idx].manufactDept = m_nowParams->m_manufac;
	m_recPtr[idx].verifyDept = m_nowParams->m_vcomp;
	m_recPtr[idx].verifyPerson = m_nowParams->m_vperson;
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
	if (m_startValueFlag) //��ֵ
	{
		ui.tableWidget->setItem(meterPos - 1, COLUMN_METER_START, new QTableWidgetItem(QString::number(flow)));
		if (idx>=0 && m_meterStartValue!=NULL)
		{
			m_meterStartValue[idx] = flow;
		}
	}
	else //��ֵ
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
	m_controlObj->askControlWaterPump(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	if (m_portsetinfo.version == OLD_CTRL_VERSION) //�Ͽ��ư� �޷���
	{
		slotSetValveBtnStatus(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
	}
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
	if (m_autopick) //�Զ��ɼ�
	{
		m_startValueFlag = true;
		readMeter();
		QTest::qWait(2000); //�ȴ����ڷ�������
		return true;
	}
	else //�ֶ�����
	{
		m_inputStartValue = true; //���������ֵ
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
	if (m_autopick) //�Զ��ɼ�
	{
		m_startValueFlag = false;
		readMeter();
		QTest::qWait(2000); //�ȴ����ڷ�������
		return true;
	}
	else //�ֶ�����
	{
		m_inputEndValue = true; //����������ֵ
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
	if (m_autopick) //�Զ��ɼ�
	{
		return;
	}

	if (NULL == ui.tableWidget->item(row,  column))
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
	if (column==COLUMN_METER_START && m_inputStartValue) //���ֵ�� �� ���������ֵ
	{
		m_meterStartValue[idx] = ui.tableWidget->item(row, column)->text().toFloat(&ok);
		if (!ok)
		{
			QMessageBox::warning(this, tr("Warning"), tr("Error: please input digits"));//�����������������
			return;
		}

		if (meterPos == m_meterPosMap[m_validMeterNum-1]) //�������һ�����ֵ
		{
			m_inputStartValue = false;
			startVerifyFlowPoint(m_nowOrder);
		}
		else //�������һ�����ֵ,�Զ���λ����һ��
		{
			ui.tableWidget->setCurrentCell(m_meterPosMap[idx+1]-1, column);
		}
	}

	if (column==COLUMN_METER_END && m_inputEndValue) //����ֵ�� �� ����������ֵ
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
			m_inputEndValue = false;
			saveAllVerifyRecords();

			if (m_autopick) //�Զ��ɼ�
			{
				ui.btnNext->hide();
			}
			else if ( !m_autopick && (m_nowOrder != m_flowPointNum) )//�ֶ��ɼ����Ҳ������һ���춨�� 
			{
				ui.btnNext->show();
			}
		}
		else //�������һ������ֵ,�Զ���λ����һ��
		{
			ui.tableWidget->setCurrentCell(m_meterPosMap[idx+1]-1, column);
		}
	}
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
** �������б����ļ춨��¼
*/
int FlowWeightDlg::saveAllVerifyRecords()
{
 	insertFlowVerifyRec(m_recPtr, m_validMeterNum);
	return true;
}

//��������㲥��ַ����
void FlowWeightDlg::on_btnReadMeter_clicked()
{
	for (int j=0; j<m_maxMeterNum; j++)
	{
		m_meterObj[j].setProtocolVersion(m_manufac); //������������
		m_meterObj[j].askReadMeter();
	}
}

/*
** �޸ı��
** ���������
	row:�кţ���row����֪����ǰ�ȱ��Ӧ�Ĵ��ڡ���š����ȵ�
*/
void FlowWeightDlg::slotModifyMeterNo(const int &row)
{
	qDebug()<<"row ="<<row;
	m_meterObj[row].askModifyMeterNo("12345678", ui.tableWidget->item(row, COLUMN_METER_NUMBER)->text());
}

/*
** �������
** ���������
	row:�кţ���row����֪����ǰ�ȱ��Ӧ�Ĵ��ڡ���š����ȵ�
*/
void FlowWeightDlg::slotAdjustError(const int &row)
{
	qDebug()<<"adj row ="<<row;
}

void FlowWeightDlg::on_btnExit_clicked()
{
	this->close();
}

