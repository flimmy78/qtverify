/***********************************************
**  �ļ���:     qualitydlg.cpp
**  ����:       ������-�����춨-������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/12
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>

#include "qualitydlg.h"

QualityDlg::QualityDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"QualityDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	m_paraset = NULL;
	m_paraset = new ParaSetDlg();

	m_readComConfig = NULL;
	m_readComConfig = new ReadComConfig();

	m_tempObj = NULL;
	m_tempTimer = NULL;
// 	initTemperatureCom();	//��ʼ���¶Ȳɼ�����

	m_controlObj = NULL;
	initControlCom();		//��ʼ�����ƴ���

	initValveStatus();      //��ʼ������״̬

	m_balanceObj = NULL;
// 	initBalanceCom();		//��ʼ����ƽ����

	m_meterObj1 = NULL;
// 	initHeatMeterCom1();	//��ʼ��������1����

	m_flowcount = 0;
	m_flow1 = 0.0;
	m_flow2 = 0.0;

	getPortSetIni(&m_portsetinfo); //��ȡ��λ���˿�������Ϣ
	getParaSetIni(&m_parasetinfo); //��ȡ����������Ϣ
}

QualityDlg::~QualityDlg()
{
}

void QualityDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^QualityDlg::closeEvent";

	if (m_paraset)  //��������
	{
		delete m_paraset;
		m_paraset = NULL;
	}

	if (m_readComConfig)  //����������
	{
		delete m_readComConfig;
		m_readComConfig = NULL;
	}

	if (m_tempObj)  // �¶Ȳɼ�
	{
		delete m_tempObj;
		m_tempObj = NULL;
	}

	if (m_controlObj)  //���ſ���
	{
		delete m_controlObj;
		m_controlObj = NULL;
	}

	if (m_balanceObj)  //��ƽ�ɼ�
	{
		delete m_balanceObj;
		m_balanceObj = NULL;
	}
	
	if (m_meterObj1)  //������1����ͨѶ
	{
		delete m_meterObj1;
		m_meterObj1 = NULL;
	}
}

/***************************************
	�¶Ȳɼ�
	��������
****************************************/
void QualityDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadTempConfig();
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer(this);
	connect(m_tempTimer, SIGNAL(timeout()), m_tempObj, SLOT(writeTemperatureComBuffer()));
	connect(m_tempTimer, SIGNAL(timeout()), this, SLOT(slotFreshFlow()));
	
	m_tempTimer->start(TIMEOUT_TEMPER); //���������¶�
}

//���ư�ͨѶ����
void QualityDlg::initControlCom()
{
	ComInfoStruct valveStruct = m_readComConfig->ReadValveConfig();
	m_controlObj = new ControlComObject();
	m_controlObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_controlObj->openControlCom(&valveStruct);

	connect(m_controlObj, SIGNAL(controlRelayIsOk()), this, SLOT(slotSetValveBtnStatus()));
	connect(m_controlObj, SIGNAL(controlRegulateIsOk()), this, SLOT(slotSetRegulateOk()));
}

//��ʼ������״̬
void QualityDlg::initValveStatus()
{
	m_nowPortNo = 0;
	m_nowPortIdx = 0;

	for(int i=0; i<VALVE_NUM; i++)
	{
		m_valveStatus[i] = VALVE_CLOSE;
	}
	m_valveBtn[VALVE_IN_IDX] = ui.btnWaterIn;
	m_valveBtn[VALVE_BIG_IDX] = ui.btnValveBig;
	m_valveBtn[VALVE_MID1_IDX] = ui.btnValveMiddle1;
	m_valveBtn[VALVE_MID2_IDX] = ui.btnValveMiddle2;
	m_valveBtn[VALVE_SMALL_IDX] = ui.btnValveSmall;
	m_valveBtn[VALVE_OUT_IDX] = ui.btnWaterOut;
	m_valveBtn[VALVE_PUMP_IDX] = ui.btnWaterPump;

	for(int i=0; i<VALVE_NUM; i++)
	{
		setBtnBackColor(m_valveBtn[i], m_valveStatus[i]);
	}

	
/*	m_waterInStatus = VALVE_CLOSE;//��ˮ����״̬ 
	setBtnBackColor(ui.btnWaterIn, m_waterInStatus);

	m_waterOutStatus = VALVE_CLOSE;//��ˮ����״̬  
	setBtnBackColor(ui.btnWaterOut, m_waterOutStatus);

	m_valveBigStatus = VALVE_CLOSE; //�������㷧��״̬
	setBtnBackColor(ui.btnValveBig, m_valveBigStatus);

	m_valveMiddle1Status = VALVE_CLOSE;//����һ����״̬  
	setBtnBackColor(ui.btnValveMiddle1, m_valveMiddle1Status);

	m_valveMiddle2Status = VALVE_CLOSE; //����������״̬
	setBtnBackColor(ui.btnValveMiddle2, m_valveMiddle1Status);

	m_valveSmallStatus = VALVE_CLOSE; //С�����㷧��״̬
	setBtnBackColor(ui.btnValveSmall, m_valveSmallStatus);

	m_valvePumpStatus = VALVE_CLOSE; //ˮ��״̬
	setBtnBackColor(ui.btnWaterPump, m_valvePumpStatus);*/
}

//��ƽ�ɼ�����
void QualityDlg::initBalanceCom()
{
	ComInfoStruct balanceStruct = m_readComConfig->ReadBalanceConfig();
	m_balanceObj = new BalanceComObject();
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

 	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const QString &)), this, SLOT(slotFreshBalanceValue(const QString &)));
}

//������1����ͨѶ
void QualityDlg::initHeatMeterCom1()
{
	ComInfoStruct comStruct = m_readComConfig->ReadMeterConfigByNum("1");
	m_meterObj1 = new MeterComObject();
	m_meterObj1->moveToThread(&m_meterThread1);
	m_meterThread1.start();
	m_meterObj1->openMeterCom1(&comStruct);

// 	connect(m_meterObj1, SIGNAL(balanceValueIsReady(const QString &)), this, SLOT(slotFreshBalanceValue(const QString &)));
}

/*
**	���Ƽ̵�������
*/
void QualityDlg::on_btnWaterIn_clicked() //��ˮ��
{
	m_nowPortIdx = VALVE_IN_IDX;
	m_nowPortNo = m_portsetinfo.waterInNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);
}

void QualityDlg::on_btnWaterOut_clicked() //��ˮ��
{
	m_nowPortIdx = VALVE_OUT_IDX;
	m_nowPortNo = m_portsetinfo.waterOutNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);

// 	m_balanceObj->writeBalanceComBuffer(); //��ʱ������(ģ����ƽ������������) д��ƽ���ڻ�����
}

void QualityDlg::on_btnValveBig_clicked() //��������
{
	m_nowPortIdx = VALVE_BIG_IDX;
	m_nowPortNo = m_portsetinfo.bigNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);
}

void QualityDlg::on_btnValveMiddle1_clicked() //����һ��
{
	m_nowPortIdx = VALVE_MID1_IDX;
	m_nowPortNo = m_portsetinfo.middle1No;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);

}

void QualityDlg::on_btnValveMiddle2_clicked() //��������
{
	m_nowPortIdx = VALVE_MID2_IDX;
	m_nowPortNo = m_portsetinfo.middle2No;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);

}

void QualityDlg::on_btnValveSmall_clicked() //С������
{
	m_nowPortIdx = VALVE_SMALL_IDX;
	m_nowPortNo = m_portsetinfo.smallNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);
}

void QualityDlg::on_btnWaterPump_clicked() //ˮ��
{
	m_nowPortIdx = VALVE_PUMP_IDX;
	m_nowPortNo = m_portsetinfo.pumpNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortIdx]);
}


/*
**	���ڷ�����
*/
void QualityDlg::on_btnRegulate1_clicked() //���ڷ�1
{
// 	ui.btnRegulate1->setStyleSheet("background:light;border:0px;");  
	UINT8 portno = m_portsetinfo.regflow1No;
	m_controlObj->makeRegulateSendBuf(portno, ui.spinBox1->value());
}

//��ѯ�ӻ�״̬
void QualityDlg::on_btnQueryStatus_clicked()
{
	m_controlObj->makeQuerySendBuf();
}

void QualityDlg::on_btnParaSet_clicked()
{
	m_paraset->show();
}

void QualityDlg::on_btnStart_clicked()
{
	m_balanceObj->setSendContinue(false); //��ʱ������(ģ����ƽ������������) ֹͣ��������
}

void QualityDlg::on_btnExit_clicked()
{
	this->close();
}

void QualityDlg::slotFreshComTempValue(const QString& tempStr)
{
	ui.lnEditTempIn->setText(tempStr.right(DATA_WIDTH)); //����¶� PV
	ui.lnEditTempOut->setText(tempStr.left(DATA_WIDTH)); //�����¶� SV
}

void QualityDlg::slotFreshBalanceValue(const QString& Str)
{
	ui.lnEditBigBalance->setText(Str);
	double v = ui.lnEditBigBalance->text().toDouble();
	ui.lnEditSmallBalance->setText(QString("%1").arg(v, 9, 'f', 4));
}

void QualityDlg::slotSetValveBtnStatus()
{
	m_valveStatus[m_nowPortIdx] = !m_valveStatus[m_nowPortIdx];
	setBtnBackColor(m_valveBtn[m_nowPortIdx], m_valveStatus[m_nowPortIdx]);
}

void QualityDlg::slotSetRegulateOk()
{
	setBtnBackColor(ui.btnRegulate1, true);
}

void QualityDlg::setBtnBackColor(QPushButton *btn, bool status)
{
	if (status) //���Ŵ� ��ɫ
	{
		btn->setStyleSheet("background:green;border:0px;");  
		btn->setIcon(QIcon("open.png"));
	}
	else //���Źر� ��ɫ
	{
		btn->setStyleSheet("background:lightgray;border:0px;");  
		btn->setIcon(QIcon("close.png"));
	}
}

//����˲ʱ����
void QualityDlg::slotFreshFlow()
{
	float flowValue = 0.0;
	if (m_flowcount == 0)
	{
		m_flow1 = ui.lnEditBigBalance->text().toFloat();
	}
	m_flowcount ++;
	if (m_flowcount == 20) //20*TIMEOUT_TEMPER
	{
		m_flow2 = ui.lnEditBigBalance->text().toFloat();
		m_flowcount = 0;
		flowValue = 3.6*(m_flow2 - m_flow1)/(20*TIMEOUT_TEMPER);
		ui.lnEditFlow->setText(QString("%1").arg(flowValue));
	}
}

//��ȡ���
void QualityDlg::on_btnReadMeterNo_clicked()
{
// 	m_meterObj1->writeMeterCom1Buffer(); //������
}


