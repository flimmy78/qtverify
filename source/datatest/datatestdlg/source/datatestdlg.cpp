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

DataTestDlg::DataTestDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"QualityDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	m_paraset = NULL;

	m_readComConfig = NULL;
	m_readComConfig = new ReadComConfig();

	m_tempObj = NULL;
	m_tempTimer = NULL;
	initTemperatureCom();	//��ʼ���¶Ȳɼ�����

	m_controlObj = NULL;
	initControlCom();		//��ʼ�����ƴ���

	m_balanceObj = NULL;
	initBalanceCom();		//��ʼ����ƽ����

	bal_quan = 0.0;
	m_setBalTimer = new QTimer();
	connect(m_setBalTimer, SIGNAL(timeout()), this, SLOT(setBalQuantity()));
	m_setBalTimer->start(TIMEOUT_TEMPER/10);

	m_flowcount = 0;		//����������
	m_totalcount = 0;
	m_flow1 = 0.0;
	m_flow2 = 0.0;
	start_quan = 0.0;
	end_quan = 0.0;
	total_quantity = 0.0;
	m_flowTimer = new QTimer();
	connect(m_flowTimer, SIGNAL(timeout()), this,  SLOT(slotFreshFlow()));
	connect(m_flowTimer, SIGNAL(timeout()), this,  SLOT(slotFreshFlow_total()));
	m_flowTimer->start(TIMEOUT_TEMPER);

	m_meterObj1 = NULL;
 	initComOfHeatMeter1();	//��ʼ��������1����


	//��ȡ��λ���˿�������Ϣ
	if (!getPortSetIni(&m_portsetinfo))
	{
		QMessageBox::warning(this, tr("Warning"), tr("��ȡ��λ���˿�������Ϣʧ��!���������ã�"));
	}

	initValveStatus();      //��ʼ������״̬
	initRegulateStatus();   //��ʼ�����ڷ�״̬

	//��ȡ����������Ϣ
	if (!getParaSetIni(&m_parasetinfo))
	{
		QMessageBox::warning(this, tr("Warning"), tr("��ȡ����������������Ϣʧ��!���������ã�"));
	}
	qDebug()<<"metertype:"<<m_parasetinfo.metertype;
}

DataTestDlg::~DataTestDlg()
{
}

void DataTestDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^QualityDlg::closeEvent";

	if (m_paraset)
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

		m_tempThread.exit(); //������־�л��о���"QThread: Destroyed while thread is still running"
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
	
	if (m_meterObj1)  //������1����ͨѶ
	{
		delete m_meterObj1;
		m_meterObj1 = NULL;

		m_meterThread1.exit();
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

	if (m_flowTimer)
	{
		if (m_flowTimer->isActive())
		{
			m_flowTimer->stop();
		}
		delete m_flowTimer;
		m_flowTimer = NULL;
	}

	if (m_setBalTimer)
	{
		if (m_setBalTimer->isActive())
		{
			m_setBalTimer->stop();
		}
		delete m_setBalTimer;
		m_setBalTimer = NULL;
	}


}

void DataTestDlg::showEvent(QShowEvent *event)
{
	m_flowcount = 0;
	m_totalcount = 0;
	total_quantity = 0;
	//if (!m_setBalTimer)
	//{
	//	bal_quan = 0.0;
	//	m_setBalTimer = new QTimer();
	//	connect(m_setBalTimer, SIGNAL(timeout()), this, SLOT(setBalQuan()));
	//	m_setBalTimer->start(TIMEOUT_TEMPER/10);
	//}

	//if (!m_flowTimer)
	//{
	//	m_flowcount = 0;		//����������
	//	m_flow1 = 0.0;
	//	m_flow2 = 0.0;
	//	total_quantity = 0.0;
	//	m_flowTimer = new QTimer();
	//	connect(m_flowTimer, SIGNAL(timeout()), this,  SLOT(slotFreshFlow()));
	//	m_flowTimer->start(TIMEOUT_TEMPER/10);
	//}
}

//ģ����ƽ����
void DataTestDlg::setBalQuantity()
{
//	qDebug()<< " current thread id: "<< QThread::currentThreadId();
	QTime time;
	time= QTime::currentTime();
	qsrand(time.msec()+time.second()*1000);
	float random=qrand()%10;//��������� 0~10
	float delta = 0.1;
	QString txt = QString::number(ui.lnEditBigBalance->text().toFloat() + delta);
	ui.lnEditBigBalance->setText(txt);
}

/***************************************
	�¶Ȳɼ�
	��������
****************************************/
void DataTestDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadTempConfig();
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer();
	connect(m_tempTimer, SIGNAL(timeout()), m_tempObj, SLOT(writeTemperatureComBuffer()));
	//connect(m_tempTimer, SIGNAL(timeout()), this, SLOT(slotFreshFlow()));
	
	m_tempTimer->start(TIMEOUT_TEMPER); //���������¶�
}

//���ư�ͨѶ����
void DataTestDlg::initControlCom()
{
	ComInfoStruct valveStruct = m_readComConfig->ReadValveConfig();
	m_controlObj = new ControlComObject();
	m_controlObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_controlObj->openControlCom(&valveStruct);

	connect(m_controlObj, SIGNAL(controlRelayIsOk(const UINT8 &, const bool &)), this, SLOT(slotSetValveBtnStatus(const UINT8 &, const bool &)));
	connect(m_controlObj, SIGNAL(controlRegulateIsOk()), this, SLOT(slotSetRegulateOk()));

	//��ƽ��ֵ�ӿ��ư��ȡ
	connect(m_controlObj, SIGNAL(controlGetBalanceValueIsOk(const QString&)), this, SLOT(slotFreshBalanceValue(const QString &)));
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

	//�˿ں�-����״̬ ȫ������״̬Ϊ�ر�
	m_valveStatus[m_portsetinfo.bigNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.smallNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle1No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.middle2No] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterInNo] = VALVE_CLOSE;
	m_valveStatus[m_portsetinfo.waterOutNo] = VALVE_CLOSE;

	setValveBtnBackColor(m_valveBtn[m_portsetinfo.bigNo], m_valveStatus[m_portsetinfo.bigNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.smallNo], m_valveStatus[m_portsetinfo.smallNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle1No], m_valveStatus[m_portsetinfo.middle1No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.middle2No], m_valveStatus[m_portsetinfo.middle2No]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterInNo], m_valveStatus[m_portsetinfo.waterInNo]);
	setValveBtnBackColor(m_valveBtn[m_portsetinfo.waterOutNo], m_valveStatus[m_portsetinfo.waterOutNo]);
}

//��ʼ�����ڷ�״̬
void DataTestDlg::initRegulateStatus()
{
	m_nowRegNo = 0;

	//�˿ں�-���Ű�ť ӳ���ϵ
	m_regBtn[m_portsetinfo.pumpNo] = ui.btnWaterPump;
	m_regBtn[m_portsetinfo.regflow1No] = ui.btnRegulate1;

	m_regStatus[m_portsetinfo.pumpNo] = REG_SUCCESS;
	m_regStatus[m_portsetinfo.regflow1No] = REG_SUCCESS;

	setRegBtnBackColor(m_regBtn[m_portsetinfo.pumpNo], m_regStatus[m_portsetinfo.pumpNo]);
	setRegBtnBackColor(m_regBtn[m_portsetinfo.regflow1No], m_regStatus[m_portsetinfo.regflow1No]);
}

//��ƽ�ɼ����� ��λ��ֱ�Ӳɼ�
void DataTestDlg::initBalanceCom()
{
	ComInfoStruct balanceStruct = m_readComConfig->ReadBalanceConfig();
	m_balanceObj = new BalanceComObject();
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

	//��ƽ��ֵ����λ��ֱ��ͨ����ƽ���ڲɼ�
 	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const QString &)), this, SLOT(slotFreshBalanceValue(const QString &)));
}

//������1����ͨѶ
void DataTestDlg::initComOfHeatMeter1()
{
	ComInfoStruct comStruct1 = m_readComConfig->ReadMeterConfigByNum("3");
	m_meterObj1 = new MeterComObject();
	m_meterObj1->moveToThread(&m_meterThread1);
	m_meterThread1.start();
	m_meterObj1->openMeterCom(&comStruct1);

	connect(m_meterObj1, SIGNAL(readMeterNoIsOK(const QString&, const QString&)), this, SLOT(slotFreshMeterNo(const QString&, const QString&)));
	connect(m_meterObj1, SIGNAL(readMeterDataIsOK(const QString&, const QString&, const QString&)), this, \
		SLOT(slotFreshMeterData(const QString&, const QString&, const QString&)));
}

/*
**	���Ƽ̵�������
*/
void DataTestDlg::on_btnWaterIn_clicked() //��ˮ��
{
	m_nowPortNo = m_portsetinfo.waterInNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void DataTestDlg::on_btnWaterOut_clicked() //��ˮ��
{
	m_nowPortNo = m_portsetinfo.waterOutNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void DataTestDlg::on_btnValveBig_clicked() //��������
{
	m_nowPortNo = m_portsetinfo.bigNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void DataTestDlg::on_btnValveMiddle1_clicked() //����һ��
{
	m_nowPortNo = m_portsetinfo.middle1No;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void DataTestDlg::on_btnValveMiddle2_clicked() //��������
{
	m_nowPortNo = m_portsetinfo.middle2No;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void DataTestDlg::on_btnValveSmall_clicked() //С������
{
	m_nowPortNo = m_portsetinfo.smallNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

/*
**	���ڷ����ȡ�ˮ��(��Ƶ��Ƶ��)
*/
void DataTestDlg::on_btnWaterPump_clicked() //ˮ��
{
	m_nowRegNo = m_portsetinfo.pumpNo;
	setRegBtnBackColor(m_regBtn[m_nowRegNo], false); //��ʼ�����ڷ�����ɫ
	m_controlObj->makeRegulateSendBuf(m_nowRegNo, ui.spinBoxFreq->value());
}

void DataTestDlg::on_btnRegulate1_clicked() //���ڷ�1
{
	m_nowRegNo = m_portsetinfo.regflow1No;
	setRegBtnBackColor(m_regBtn[m_nowRegNo], false); //��ʼ�����ڷ�����ɫ
	m_controlObj->makeRegulateSendBuf(m_nowRegNo, ui.spinBoxFreq->value());
}

//��ѯ�ӻ�(���ư�)״̬
void DataTestDlg::on_btnQueryStatus_clicked()
{
	m_controlObj->makeQuerySendBuf();
}

//��������
void DataTestDlg::on_btnParaSet_clicked()
{
	if (NULL == m_paraset)
	{
		m_paraset = new ParaSetDlg();
	}
	else
	{
		delete m_paraset;
		m_paraset = new ParaSetDlg();
	}
	m_paraset->show();
}

void DataTestDlg::on_btnStart_clicked()
{
}

void DataTestDlg::on_btnExit_clicked()
{
	this->close();
}

//ˢ���¶�
void DataTestDlg::slotFreshComTempValue(const QString& tempStr)
{
	ui.lnEditTempIn->setText(tempStr.left(DATA_WIDTH));   //����¶� PV
	ui.lnEditTempOut->setText(tempStr.right(DATA_WIDTH)); //�����¶� SV
}

//ˢ����ƽ��ֵ
void DataTestDlg::slotFreshBalanceValue(const QString& Str)
{
	ui.lnEditBigBalance->setText(Str);
	if (Str.toFloat() > 100); //��ֹ��ƽ��� ������ƽ����Ϊ100kg
	{
		// �򿪷�ˮ��
		// �رս�ˮ��
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
		btn->setStyleSheet("background:green;border:0px;"); 
		btn->setIcon(QIcon("open.png"));
	}
	else //���Źر� ��ɫ
	{
		btn->setStyleSheet("background-color:rgb(255,0,0);border:0px;"
// 			"border-style: outset;"
// 			"border-width: 2px;"
			"border-radius: 10px;"
// 			"border-color: beige;"
// 			"font: bold 14px;"
// 			"min-width: 10em;"
// 			"padding: 6px;" 
		);
		btn->setIcon(QIcon("close.png"));
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
		btn->setStyleSheet("background:rgb(199,237,204);border:0px;");  
	}
	else //����ʧ��
	{
 		btn->setStyleSheet("background:rgb(255,200,200);border:0px;");  
	}
}

/************************************************************************/
/* ����˲ʱ����(���Ľ�����Ҫʵ����֤)                        */
/************************************************************************/
//void QualityDlg::slotFreshFlow()
//{
// 	qDebug()<<"slotFreshFlow thread:"<<QThread::currentThreadId(); //���߳�
//	float flowValue = 0.0;
//	int length = ui.lnEditBigBalance->text().length();
//	if (m_flowcount == 0)
//	{
//		QString a1 = ui.lnEditBigBalance->text();
//		m_flow1 = ui.lnEditBigBalance->text().right(length-1).toFloat();
//		qDebug()<<"start weight: "<<m_flow1;
//	}
//	m_flowcount ++;
//	if (m_flowcount == CALC_FLOW_COUNT) //ʵ�ʼ���Ƶ�� = CALC_FLOW_COUNT*TIMEOUT_TEMPER
//	{
//		QString a2 = ui.lnEditBigBalance->text();
//		m_flow2 = ui.lnEditBigBalance->text().right(length-1).toFloat();
//		qDebug()<<"end weight: "<<m_flow2;
//		m_flowcount = 0;
//		flowValue = 3.6*(m_flow2 - m_flow1)*1000/(CALC_FLOW_COUNT*TIMEOUT_TEMPER);
//		float difFlow = m_flow2 - m_flow1;
//		qDebug()<<"delta weight: "<<difFlow;
//		qDebug()<<"flow: "<<flowValue<<"\n";
//		ui.lnEditFlow->setText(QString("%1").arg(flowValue, 6, 'g', 4));
//	}
//}


/************************************************************************/
/* ����˲ʱ����(˲ʱ��)                                                */
/************************************************************************/
void DataTestDlg::slotFreshFlow()
{
// 	qDebug()<<"slotFreshFlow thread:"<<QThread::currentThreadId(); //���߳�
	float flowValue = 0.0;
	/**************************************************************************/
	/* ����ԭ��������߼�, ��ô�Ͷ�ʧ��һ����t���������� */
	/**************************************************************************/
	m_flowcount++;
	//if ( m_flowcount == 1)
	//{
	//	QString a1 = ui.lnEditBigBalance->text();
	//	m_flow1 = ui.lnEditBigBalance->text().toFloat();
	//}

	if (m_flowcount == CALC_FLOW_COUNT)//ʵ�ʼ���Ƶ�� = CALC_FLOW_COUNT*TIMEOUT_TEMPER
	{
		m_flow2 = ui.lnEditBigBalance->text().toFloat();
		float difFlow = m_flow2 - m_flow1;
		flowValue = 3.6*(difFlow)*1000/(CALC_FLOW_COUNT*TIMEOUT_TEMPER);
		//flowValue = (m_flow2 - m_flow1)*1000/(CALC_FLOW_COUNT*TIMEOUT_TEMPER);// kg/s
		
		m_flowcount = 0;
		ui.lnEditFlow->setText(QString::number(flowValue, 'f', 2));
		m_flow1 = m_flow2;
	}
	
}

/************************************************************************/
/* ����˲ʱ����(�ۻ�ˮ����, �ο��ϳ�����㷨)                           */
/************************************************************************/
void DataTestDlg::slotFreshFlow_total()
{
	if (m_totalcount > 4294967290) //��ֹm_totalcount��� 32λ�޷���������Χ0~4294967295
	{
		m_totalcount = 0;
		total_quantity = 0;
	}

	float flowValue = 0.0;
	m_totalcount ++;//�������ۼ�
	end_quan = ui.lnEditBigBalance->text().toFloat();//ȡ��ǰ��ƽֵ, ��Ϊ��ǰ�������ֵ
	float delta_weight = end_quan - start_quan;

	total_quantity += delta_weight;
	flowValue = 3.6*(total_quantity)*1000/(m_totalcount*TIMEOUT_TEMPER);//���ۻ�ˮ��/��ʱ��  (��/Сʱ, t/h)
	//flowValue = (total_quantity)*1000/(m_totalcount*TIMEOUT_TEMPER);// kg/s
	ui.lnEditSmallBalance->setText(QString::number(flowValue, 'f', 2)); //��ʱ��ui.lnEditSmallBalance����ʾ����
	start_quan = end_quan;//����ǰֵ����, ��Ϊ�´�����ĳ�ֵ
}

//��ȡ���
void DataTestDlg::on_btnReadMeterNo_clicked()
{
}

//��������
void DataTestDlg::on_btnReadMeterData_clicked()
{
	ui.lnEditMeterNo->clear();
	ui.lnEditVolumn0->clear();
	ui.lnEditHeat0->clear();
	qDebug()<<"���� ��ʼ...";
 	m_meterObj1->askReadMeter(); //�������
}

//���ü춨״̬
void DataTestDlg::on_btnSetVerifyStatus_clicked()
{
	m_meterObj1->askSetVerifyStatus(); //���ý���춨״̬
}

void DataTestDlg::slotFreshMeterNo(const QString& comName, const QString& meterNo)
{
	ui.lnEditMeterNo->setText(meterNo);
	qDebug()<<"��ȡ��� �ɹ�...";
}

void DataTestDlg::slotFreshMeterData(const QString& comName, const QString& flow, const QString& heat)
{
	ui.lnEditVolumn0->setText(flow);
	ui.lnEditHeat0->setText(heat);
	qDebug()<<"��ȡ������ �ɹ�...";
}