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
	initTemperatureCom();	//��ʼ���¶Ȳɼ�����

	m_controlObj = NULL;
// 	initControlCom();		//��ʼ�����ƴ���
	m_valveWaterInStatus = false;//��ˮ����״̬ false���ر�״̬; true:��״̬ 
	setBtnBackColor(ui.btnWaterIn, m_valveWaterInStatus);
	m_Valve1Status = false; //�������㷧��״̬
	setBtnBackColor(ui.btnWaterValve1, m_Valve1Status);

	m_balanceObj = NULL;
// 	initBalanceCom();		//��ʼ����ƽ����

	m_meterObj1 = NULL;
// 	initHeatMeterCom1();	//��ʼ��������1����

	m_flowcount = 0;
	m_flow1 = 0.0;
	m_flow2 = 0.0;
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

//���Ƽ̵�������
void QualityDlg::on_btnWaterIn_clicked()
{
	UINT8 portno = 6; //����˿ں�Ϊ6
	m_controlObj->makeRelaySendBuf(portno, !m_valveWaterInStatus);
}

void QualityDlg::on_btnWaterOut_clicked()
{
	m_balanceObj->writeBalanceComBuffer(); //��ʱ������(ģ����ƽ������������) д��ƽ���ڻ�����
}

void QualityDlg::on_btnWaterValve1_clicked()
{
	UINT8 portno = 2; //����˿ں�Ϊ1
	m_controlObj->makeRelaySendBuf(portno, !m_Valve1Status);
	m_Valve1Status = !m_Valve1Status; //ֻ������
	setBtnBackColor(ui.btnWaterValve1, m_Valve1Status); //ֻ������
}

//���ڷ�����
void QualityDlg::on_btnRegulate1_clicked()
{
	ui.btnRegulate1->setStyleSheet("background:light;border:0px;");  
	UINT8 portno = 4; //�����ǵ�4·���ڷ�
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
	m_valveWaterInStatus = !m_valveWaterInStatus;
	setBtnBackColor(ui.btnWaterIn, m_valveWaterInStatus);
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
		btn->setStyleSheet("background:red;border:0px;");  
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
	m_meterObj1->writeMeterCom1Buffer(); //������
}

