/***********************************************
**  �ļ���:     weightmethod.cpp
**  ����:       �������춨������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/7/15
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/07 ��һ��
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


#include "weightmethod.h"
#include "commondefine.h"
#include "algorithm.h"
#include "math.h"

WeightMethodDlg::WeightMethodDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"WeightMethodDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);
 	ui.btnNext->hide(); //����"��һ��"��ť
	ui.btnStart->hide();
	m_inputStartValue = false;
	m_inputEndValue = false;

	//��ͬ�ȼ����������Ӧ�ı�׼���
	m_gradeErr[1] = 0.01;
	m_gradeErr[2] = 0.02;
	m_gradeErr[3] = 0.03;
/*	
	ui.tabWidget->setTabsClosable(true);
	connect(ui.tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));
	for (int i=0; i<4; i++)
	{
		ui.tabWidget->removeTab(1);
	}
*/

/*********************************************************/
	m_balTimer = new QTimer(this);
	connect(m_balTimer, SIGNAL(timeout()), this, SLOT(freshBigBalaceValue()));
	m_balTimer->start(200); //ģ����ƽÿ200�������һ��
	m_balValue = 0.0;
	m_tempValue = 20.0;
/*********************************************************/
	m_stopFlag = false; //�˳�����󣬲��ټ����ƽ����

	m_readComConfig = new ReadComConfig(); //���������ýӿ�

	m_balanceObj = NULL;
	initBalanceCom();		//��ʼ����ƽ����

	m_tempObj = NULL;
	m_tempTimer = NULL;
	initTemperatureCom();	//��ʼ���¶Ȳɼ�����

	m_controlObj = NULL;
	initControlCom();		//��ʼ�����ƴ���


	m_chkAlg = new CAlgorithm();//������ӿ�

	if (!getPortSetIni(&m_portsetinfo)) //��ȡ��λ���˿ں�������Ϣ
	{
		QMessageBox::warning(this, tr("Warning"), tr("��ȡ��λ���˿ں�������Ϣʧ��!���������ã�"));
	}

	initValveStatus();      //ӳ���ϵ����ʼ������״̬

	m_exaustTimer = new QTimer(this); //������ʱ��
	connect(m_exaustTimer, SIGNAL(timeout()), this, SLOT(slotExaustFinished()));

	m_tempCount = 1; //����ƽ���¶��õ��ۼӼ�����
	m_nowOrder = 0;  //��ǰ���еļ춨���

	m_nowParams = new Quality_Params_STR;
	memset(m_nowParams, 0, sizeof(Quality_Params_STR));
	m_continueVerify = true; //�����춨
	m_resetZero = false;     //��ֵ����
	m_autopick = false;      //�Զ��ɼ�
	m_flowPointNum = 0;      //���������
	m_rowNum = 0;            //ĳ�������֧�ֵļ�����
	m_meterNum = 0;          //ʵ�ʼ�����
	m_exaustSecond = 45;     //Ĭ������ʱ��45��
	m_totalFlag = 0;         //Ĭ�Ϸ����춨
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

	m_recNum = 0;
	m_recPtr = NULL;

	QSqlTableModel *model = new QSqlTableModel(this);  
	model->setTable(tr("T_Meter_Standard"));  
	model->select();  
	m_mapper = new QDataWidgetMapper(this);
	m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	m_mapper->setModel(model);
	m_mapper->addMapping(ui.lnEditStandard, 1); //ӳ���"T_Meter_Standard"�ĵڶ����ֶ�

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

	if (!isWaterOutValveOpen())
	{
		qDebug()<<"��ˮ����δ��";
		openWaterOutValve();
	}
}

WeightMethodDlg::~WeightMethodDlg()
{
}

void WeightMethodDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^WeightMethodDlg::closeEvent";

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

}

//�رձ�ǩҳ
void WeightMethodDlg::removeSubTab(int index) 
{ 
	ui.tabWidget->removeTab(index); 
} 

//��ƽ�ɼ����� ��λ��ֱ�Ӳɼ�
void WeightMethodDlg::initBalanceCom()
{
	ComInfoStruct balanceStruct = m_readComConfig->ReadBalanceConfig();
	m_balanceObj = new BalanceComObject();
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

	//��ƽ��ֵ����λ��ֱ��ͨ����ƽ���ڲɼ�
	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const QString &)), this, SLOT(slotFreshBalanceValue(const QString &)));
}


/*
** �¶Ȳɼ����� ��λ��ֱ�Ӳɼ�
** ��������
*/
void WeightMethodDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadTempConfig();
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer();
	connect(m_tempTimer, SIGNAL(timeout()), m_tempObj, SLOT(writeTemperatureComBuffer()));
// 	connect(m_tempTimer, SIGNAL(timeout()), this, SLOT(slotFreshFlow())); //��������
	
	m_tempTimer->start(TIMEOUT_TEMPER); //���������¶�
}

//���ư�ͨѶ����
void WeightMethodDlg::initControlCom()
{
	ComInfoStruct valveStruct = m_readComConfig->ReadValveConfig();
	m_controlObj = new ControlComObject();
	m_controlObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_controlObj->openControlCom(&valveStruct);

	connect(m_controlObj, SIGNAL(controlRelayIsOk(const UINT8 &, const bool &)), this, SLOT(slotSetValveBtnStatus(const UINT8 &, const bool &)));
	connect(m_controlObj, SIGNAL(controlRegulateIsOk()), this, SLOT(slotSetRegulateOk()));

	//��ƽ��ֵ�ӿ��ư��ȡ
// 	connect(m_controlObj, SIGNAL(controlGetBalanceValueIsOk(const QString&)), this, SLOT(slotFreshBalanceValue(const QString &)));
}

/*
** �˿ں�-����ӳ���ϵ����ʼ������״̬
** ��Ҫ�Ľ��ø������
*/
void WeightMethodDlg::initValveStatus()
{
	m_nowPortNo = 0;

	//�˿ں�-���Ű�ť ӳ���ϵ
	m_valveBtn[m_portsetinfo.bigNo] = ui.btnValveBig;
	m_valveBtn[m_portsetinfo.smallNo] = ui.btnValveSmall;
	m_valveBtn[m_portsetinfo.middle1No] = ui.btnValveMiddle1;
	m_valveBtn[m_portsetinfo.middle2No] = ui.btnValveMiddle2;
	m_valveBtn[m_portsetinfo.waterInNo] = ui.btnWaterIn;
	m_valveBtn[m_portsetinfo.waterOutNo] = ui.btnWaterOut;

	//��ʼ�� ȫ������״̬Ϊ�ر�
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



//�ڽ���ˢ����ƽ��ֵ
void WeightMethodDlg::slotFreshBalanceValue(const QString& Str)
{
	ui.lnEditBigBalance->setText(Str);
}

//�ڽ���ˢ������¶Ⱥͳ����¶�ֵ
void WeightMethodDlg::slotFreshComTempValue(const QString& tempStr)
{
	ui.lcdNumberInTemper->display(tempStr.left(DATA_WIDTH).toFloat());   //����¶� PV
	ui.lcdNumberOutTemper->display(tempStr.right(DATA_WIDTH).toFloat()); //�����¶� SV
}

/*
** ����˲ʱ����(���Ľ�����Ҫʵ����֤)
*/
void WeightMethodDlg::slotFreshFlow()
{
 	qDebug()<<"slotFreshFlow thread:"<<QThread::currentThreadId(); //

}

//��⴮�ڡ��˿������Ƿ���ȷ
int WeightMethodDlg::isComAndPortNormal()
{
	return true;
}

//����ˮ�����Ƿ�� ��:true���ر�:false
int WeightMethodDlg::isWaterOutValveOpen()
{
	return true;
}

//��ȡ��ǰ�춨����
int WeightMethodDlg::readNowParaConfig()
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
	m_totalFlag = m_nowParams->bo_total;	 //�����춨��־(1:�����춨  0:�����춨)
	m_standard = m_nowParams->m_stand;       //����
	m_model = m_nowParams->m_model;   //���ͺ�
	m_meterType = m_nowParams->m_type;//������
	m_rowNum = m_nowParams->m_maxMeters;     //��ͬ�����Ӧ�����������

	setTableRowCount();
	showNowKeyParaConfig();

	return true;
}

//���ñ������
void WeightMethodDlg::setTableRowCount()
{
	if (m_rowNum <= 0)
	{
		return;
	}

	ui.tableWidget->setRowCount(m_rowNum); //���ñ������
	QStringList vLabels;
	for (int i=1; i<= m_rowNum; i++)
	{
		vLabels<<QString("��λ��%1").arg(i);
	}
	ui.tableWidget->setVerticalHeaderLabels(vLabels);
}

//��ʾ��ǰ�ؼ�����������Ϣ
void WeightMethodDlg::showNowKeyParaConfig()
{
	if (NULL == m_nowParams)
	{
		return;
	}

	ui.cmbAutoPick->setCurrentIndex(m_nowParams->bo_autopick);
	ui.cmbContinue->setCurrentIndex(m_nowParams->bo_converify);

	m_mapper->setCurrentIndex(m_nowParams->m_stand);
// 	ui.labelStandard->setText();
}

/*
** ���"������ť"����ʼ�춨
*/
void WeightMethodDlg::on_btnExhaust_clicked()
{
	if (!isDataCollectNormal())
	{
		qWarning()<<"���ݲɼ�������������";
		return;
	}

	if (!openAllValuesAndPump())
	{
		qWarning()<<"�����з��ź�ˮ�� ʧ��!";
		return;
	}
	m_stopFlag = false;
	clearTableContents();
	m_meterNum = 0;

	m_exaustSecond = m_nowParams->ex_time;
	m_exaustTimer->start(1000);//��ʼ��������ʱ

	readMeterNumber();

	setMeterVerifyStatus();
	
	return;
}

//������ݲɼ��Ƿ�������������ƽ���¶ȡ����������
int WeightMethodDlg::isDataCollectNormal()
{
	return true;
}

//�����з��ź�ˮ��
int WeightMethodDlg::openAllValuesAndPump()
{
	return true;
}

/*
** ����ʱ���������Ӧ����
*/
void WeightMethodDlg::slotExaustFinished()
{
	m_exaustSecond --;
	ui.labelHintInfo->setText(QString("��������ʱ��%1 ��").arg(m_exaustSecond));
	qDebug()<<"��������ʱ:"<<m_exaustSecond<<"��";

	if (m_exaustSecond > 1)
	{
		return;
	}
	m_exaustTimer->stop(); //ֹͣ������ʱ
	ui.labelHintInfo->setText(QString("��������ʱ ������"));
	if (!closeAllFlowPointValves()) //�ر����������㷧�� ʧ��
	{
		if (!closeAllFlowPointValves()) //�ٳ��Թر�һ��
		{
			qWarning()<<"�ر����������㷧��ʧ�ܣ��춨����";
			return;
		}
	}

	//�жϲ��ȴ���ƽ����,����Ҫ��ĳ�ʼ����(2kg)
	if (judgeBalanceInitValue(BALANCE_START_VALUE))
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

	//�жϲ��ȴ���ƽ���������ڳ�ʼ����(2kg)+3kg
	if (judgeBalanceInitValue(BALANCE_START_VALUE + 3))
	{
		if (!closeBigFlowValve())
		{
			qWarning()<<"�رմ�������ʧ��";
		}
	}

	if (isAllMeterInVerifyStatus()) //�������ѽ���춨״̬
	{
		startVerify();
	}

}

/*
** ��ȡ��� �Զ���ȡ���ֶ���д
*/
int WeightMethodDlg::readMeterNumber()
{

	return true;
}

//�������������춨״̬
int WeightMethodDlg::setMeterVerifyStatus()
{
	return true;
}

//�ر����������㷧��
int WeightMethodDlg::closeAllFlowPointValves()
{
	return true;
}

//�رշ�ˮ����
int WeightMethodDlg::closeWaterOutValve()
{
	return true;
}

//�򿪷�ˮ����
int WeightMethodDlg::openWaterOutValve()
{
	return true;
}

//�򿪴������㷧��
int WeightMethodDlg::openBigFlowValve()
{
	return true;
}

//�رմ������㷧��
int WeightMethodDlg::closeBigFlowValve()
{
	return true;
}

//��Ӧ������ƽ�����ı仯
int WeightMethodDlg::judgeBalanceInitValue(float v)
{
	while (!m_stopFlag && (ui.lnEditBigBalance->text().toFloat() < v))
	{
		qDebug()<<"��ƽ���� ="<<ui.lnEditBigBalance->text().toFloat()<<", С��Ҫ������� "<<v;
		QTest::qWait(1000);
	}

	return true;
}

int WeightMethodDlg::judgeBalanceAndCalcTemper(float targetV)
{
	int second;
	float nowFlow =m_paraSetReader->getFpBySeq(m_nowOrder).fp_verify;;
	while (!m_stopFlag && (ui.lnEditBigBalance->text().toFloat() < targetV))
	{
		qDebug()<<"��ƽ���� ="<<ui.lnEditBigBalance->text().toFloat()<<", С��Ҫ������� "<<targetV;
		m_pipeInTemper += ui.lcdNumberInTemper->value();
		m_pipeOutTemper += ui.lcdNumberOutTemper->value();
		m_tempCount++;

		second = 3.6*(targetV - ui.lnEditBigBalance->text().toFloat())/nowFlow;
		ui.labelHintInfo->setText(QString("��%1������: %2 m3/h\nʣ��ʱ�� %3 ��").arg(m_nowOrder).arg(nowFlow).arg(second));
		QTest::qWait(1000);
	}

	m_pipeInTemper = m_pipeInTemper/m_tempCount;   //���ƽ���¶�
	m_pipeOutTemper = m_pipeOutTemper/m_tempCount; //����ƽ���¶�
	ui.labelHintInfo->setText(QString("��%1������: %2 m3/h\n�춨���!").arg(m_nowOrder).arg(nowFlow));
	return true;
}

//�ж��������ѽ���춨״̬
int WeightMethodDlg::isAllMeterInVerifyStatus()
{
	return true;
}

void WeightMethodDlg::clearTableContents()
{
	for (int i=0; i<m_rowNum; i++)
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
// 	ui.tableWidget->clearContents();
}

//���"��ʼ"��ť
void WeightMethodDlg::on_btnStart_clicked()
{
	startVerify();
}

//���"��һ��"��ť
void WeightMethodDlg::on_btnNext_clicked()
{
	if (m_nowOrder >= m_flowPointNum)
	{
		QMessageBox::warning(this, "warning", "�����������Ѿ��춨���!");
		return;
	}

	clearTableContents();

	m_nowOrder ++;
	prepareVerifyFlowPoint(m_nowOrder); // ��ʼ������һ��������ļ춨
}

//���"��ֹ���"��ť
void WeightMethodDlg::on_btnStop_clicked()
{
	m_stopFlag = true;
}

//��ʼ�춨
void WeightMethodDlg::startVerify()
{
	m_nowOrder = 1;

	//�ж�ʵ�ʼ��ĸ���(���ݻ�ȡ���ı�Ÿ���)
	if (getValidMeterNum() <= 0)
	{
		QMessageBox::warning(this, tr("Warning"), tr("�������ţ�"));
		return;
	}

	m_flowPoint = m_paraSetReader->getFpBySeq(1).fp_verify;//��һ��������
	for (int m=0; m<m_meterNum; m++) //
	{
		ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_FLOW_POINT, new QTableWidgetItem(QString::number(m_flowPoint, 'f', 2)));//������
	}


	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //��¼ʱ���
	m_nowDate = QDateTime::currentDateTime().toString("yyyy-MM-dd"); //��ǰ����'2014-08-07'
	m_validDate = QDateTime::currentDateTime().addYears(VALID_YEAR).toString("yyyy-MM-dd"); //��Ч��

	m_meterStartValue = new float[m_meterNum]; //���ֵ 
	memset(m_meterStartValue, 0, sizeof(float)*m_meterNum);

	m_meterEndValue = new float[m_meterNum];   //����ֵ
	memset(m_meterEndValue, 0, sizeof(float)*m_meterNum);

	m_meterTemper = new float[m_meterNum];     //���¶�
	memset(m_meterTemper, 0, sizeof(float)*m_meterNum);

	m_meterDensity = new float[m_meterNum];    //���ܶ�
	memset(m_meterDensity, 0, sizeof(float)*m_meterNum);

	m_meterStdValue = new float[m_meterNum];   //�����ı�׼ֵ
	memset(m_meterStdValue, 0, sizeof(float)*m_meterNum);

	m_meterError = new float[m_meterNum];      //���������
	memset(m_meterError, 0, sizeof(float)*m_meterNum);
	

	if (m_continueVerify) //�����춨
	{
		if (!judgeBalanceCapacity()) //�ж���ƽ�����Ƿ��ܹ�����춨����
		{
			openWaterOutValve();
		}
		while (!judgeBalanceCapacity())
		{ 
			QTest::qWait(1000);
		}
		closeWaterOutValve(); //������춨��������رշ�ˮ��
		QTest::qWait(3000); //�ȴ�3����(�ȴ�ˮ���ȶ�)
	}


	////////////////////////////////�����춨
	if (m_continueVerify)
	{
		for (int j=0; j<m_flowPointNum; j++)
		{
			prepareVerifyFlowPoint(j+1);
		}
	}

	////////////////////////////////�������춨
	if (!m_continueVerify)
	{
		if (prepareVerifyFlowPoint(1)) //��һ��������춨
		{
			ui.btnNext->show();
			ui.btnNext->setDefault(true);
		}
	}
	//������
}

int WeightMethodDlg::getValidMeterNum()
{
	bool ok;
	for (int i=0; i<m_rowNum; i++)
	{
		if (NULL == ui.tableWidget->item(i, 0)) //"���"��Ԫ��Ϊ��
		{
			continue;
		}
		ui.tableWidget->item(i, 0)->text().toInt(&ok, 10);
		if (!ok) //���ת��ʧ��(������)
		{
			continue;
		}

		m_meterPosMap[m_meterNum] = i+1; //��λ�Ŵ�1��ʼ
		m_meterNum++;
	}
	return m_meterNum;
}

//ˢ����ƽ���¶���ֵ ��������
void WeightMethodDlg::freshBigBalaceValue()
{
// 	if (m_balValue > 100)
// 	{
// 		m_balValue = 0;
// 	}
	m_balValue += 0.2;
	ui.lnEditBigBalance->setText(QString("%1").arg(m_balValue));

	if (m_tempValue > 90)
	{
		m_tempValue = 20;
	}
	m_tempValue += 0.2;
	ui.lcdNumberInTemper->display(m_tempValue);
	ui.lcdNumberOutTemper->display(m_tempValue+0.12);

}

/*
** �ж���ƽ�����Ƿ�����춨����
** �����춨ʱ�������ܼ춨����
*/
int WeightMethodDlg::judgeBalanceCapacity()
{
	return true;
}

/*
** �ж���ƽ�����Ƿ�����춨����
** �������춨ʱ�����㵥�μ춨����
*/
int WeightMethodDlg::judgeBalanceCapacitySingle(int order)
{
	return true;
}

/*
** ׼������������ļ춨�����б�Ҫ�ļ��
** ע�⣺order��1��ʼ
*/
int WeightMethodDlg::prepareVerifyFlowPoint(int order)
{
	if (order < 1)
	{
		return false;
	}
	if (m_meterNum <= 0)
	{
		QMessageBox::warning(this, tr("Warning"), tr("�������ţ�"));
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

	if (m_resetZero) //��ֵ����
	{
		QTest::qWait(18000); //�ȴ�18�룬�ȴ�������ֵ����
		memset(m_meterStartValue, 0, sizeof(float)*m_meterNum);
	}
	else //��ֵ������
	{
		if (order >= 2) //�ڶ����춨��֮��
		{
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
int WeightMethodDlg::startVerifyFlowPoint(int order)
{
	m_balStartV = ui.lnEditBigBalance->text().toFloat(); //��¼��ƽ��ֵ
	m_pipeInTemper = ui.lcdNumberInTemper->value();
	m_pipeOutTemper = ui.lcdNumberOutTemper->value();

	m_flowPoint = m_paraSetReader->getFpBySeq(order).fp_verify;//order��Ӧ��������
	int portNo = m_paraSetReader->getFpBySeq(order).fp_valve;  //order��Ӧ�ķ��Ŷ˿ں�
	float verifyQuantity = m_paraSetReader->getFpBySeq(order).fp_quantity; //��order�μ춨��Ӧ�ļ춨��
	if (openValve(portNo)) //�򿪷��ţ���ʼ������
	{
		if (judgeBalanceAndCalcTemper(m_balStartV + verifyQuantity)) //����춨��������ι��̵�ƽ���¶�
		{
			closeValve(portNo); //�ر�order��Ӧ�ķ���
			m_balEndV = ui.lnEditBigBalance->text().toFloat(); //��¼��ƽ��ֵ

			for (int m=0; m<m_meterNum; m++) //
			{
				m_meterTemper[m] = m_chkAlg->getMeterTempByPos(m_pipeInTemper, m_pipeOutTemper, m_meterPosMap[m]);//����ÿ���������¶�
				m_meterDensity[m] = m_chkAlg->getDensityByQuery(m_meterTemper[m]);//����ÿ���������ܶ�
				m_meterStdValue[m] = m_chkAlg->getStdVolByPos((m_balEndV-m_balStartV), m_pipeInTemper, m_pipeOutTemper, m_meterPosMap[m]); //����ÿ�������������׼ֵ

				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_FLOW_POINT, new QTableWidgetItem(QString::number(m_flowPoint, 'f', 2)));//������
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_BAL_START, new QTableWidgetItem(QString::number(m_balStartV, 'f', 2)));//��ƽ��ֵ
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_BAL_END, new QTableWidgetItem(QString::number(m_balEndV, 'f', 2)));    //��ƽ��ֵ
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_TEMPER, new QTableWidgetItem(QString::number(m_meterTemper[m], 'f', 2)));  //�¶�
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_DENSITY, new QTableWidgetItem(QString::number(m_meterDensity[m], 'f', 2)));//�ܶ�
				ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_STD_VALUE, new QTableWidgetItem(QString::number(m_meterStdValue[m], 'f', 2)));//��׼ֵ
			}


			if (!getMeterEndValue()) //��ȡ����ֵ
			{
				return false;
			}
			calcMeterErrorAndSaveDb();
		}
	}
	return true;
}

int WeightMethodDlg::calcMeterErrorAndSaveDb()
{
	for (int m=0; m<m_meterNum; m++) //
	{
		m_meterError[m] = (m_meterEndValue[m] - m_meterStartValue[m] - m_meterStdValue[m])/m_meterStdValue[m];//����ÿ��������
		ui.tableWidget->setItem(m_meterPosMap[m]-1, COLUMN_ERROR, new QTableWidgetItem(QString::number(m_meterError[m], 'f', 6))); //���
	}

	QString meterNoStr;
	m_recNum = m_meterNum;
	m_recPtr = new Record_Quality_STR[m_recNum];
	memset(m_recPtr, 0, sizeof(Record_Quality_STR)*m_recNum);
	for (int i=0; i<m_recNum; i++)
	{
		strncpy(m_recPtr[i].timestamp, m_timeStamp.toAscii(), TIMESTAMP_LEN);
		m_recPtr[i].flowPoint = m_flowPoint;
		meterNoStr = METERNO_PREFIX + QString("%1").arg(ui.tableWidget->item(m_meterPosMap[i]-1, 0)->text(), 8, '0');
		strcpy(m_recPtr[i].meterNo, meterNoStr.toAscii());
		m_recPtr[i].flowPointIdx = m_nowOrder; //
		m_recPtr[i].totalFlag = m_totalFlag;
		m_recPtr[i].meterValue0 = m_meterStartValue[i];
		m_recPtr[i].meterValue1 = m_meterEndValue[i];
		m_recPtr[i].meterDeltaV = m_recPtr[i].meterValue1 - m_recPtr[i].meterValue0;
		m_recPtr[i].balWeight0 = m_balStartV;
		m_recPtr[i].balWeight1 = m_balEndV;
		m_recPtr[i].balDeltaW = m_recPtr[i].balWeight1 - m_recPtr[i].balWeight0;
		m_recPtr[i].inSlotTemper = m_pipeInTemper;
		m_recPtr[i].outSlotTemper = m_pipeOutTemper;
		m_recPtr[i].pipeTemper = m_meterTemper[i]; 
		m_recPtr[i].density = m_meterDensity[i];
		m_recPtr[i].stdValue = m_meterStdValue[i];
		m_recPtr[i].dispError = m_meterError[i];
		m_recPtr[i].grade = m_nowParams->m_grade;
		m_recPtr[i].stdError = m_gradeErr[m_nowParams->m_grade]; //������ ��׼���
		m_recPtr[i].result = (fabs(m_recPtr[i].dispError) <= fabs(m_recPtr[i].stdError)) ? 1 : 0;
		m_recPtr[i].meterPosNo = m_meterPosMap[i];
		m_recPtr[i].standard = m_standard;
		m_recPtr[i].model = m_model;
		m_recPtr[i].meterType = m_meterType; //������
		m_recPtr[i].manufactDept = m_nowParams->m_manufac;
		m_recPtr[i].verifyDept = m_nowParams->m_vcomp;
		m_recPtr[i].verifyPerson = m_nowParams->m_vperson;
		strncpy(m_recPtr[i].date, m_nowDate.toAscii(), DATE_LEN);
		strncpy(m_recPtr[i].validDate, m_validDate.toAscii(), DATE_LEN);

	}

	saveVerifyRecord(); //���������ݿ�


	if (!m_continueVerify)
	{
		ui.btnNext->show();
	}
	else
	{
		ui.btnNext->hide();
	}

	return true; 
}

//�򿪷���
int WeightMethodDlg::openValve(UINT8 portno)
{
	m_controlObj->makeRelaySendBuf(portno, VALVE_OPEN);
	return true;
}

//�رշ���
int WeightMethodDlg::closeValve(UINT8 portno)
{
	m_controlObj->makeRelaySendBuf(portno, VALVE_CLOSE);
	return true;
}

//��Ӧ����״̬���óɹ�
void WeightMethodDlg::slotSetValveBtnStatus(const UINT8 &portno, const bool &status)
{
	m_valveStatus[portno] = status;
	setValveBtnBackColor(m_valveBtn[portno], m_valveStatus[portno]);
}

//��Ӧ���ڷ����ڳɹ�
void WeightMethodDlg::slotSetRegulateOk()
{
// 	setRegBtnBackColor(m_regBtn[m_nowRegIdx], true);
}


//���÷��Ű�ť����ɫ
void WeightMethodDlg::setValveBtnBackColor(QToolButton *btn, bool status)
{
	if (NULL == btn)
	{
		return;
	}
	if (status) //���Ŵ� ��ɫ
	{
		btn->setStyleSheet("background:green;border:0px;");  
// 		btn->setIcon(QIcon("open.png"));
	}
	else //���Źر� ��ɫ
	{
		btn->setStyleSheet( "background-color:rgb(160,0,0);border:0px;"
			"border-radius: 10px;"
		);
// 		btn->setIcon(QIcon("close.png"));
	}
}

//���õ��ڷ���ť����ɫ
void WeightMethodDlg::setRegBtnBackColor(QPushButton *btn, bool status)
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
void WeightMethodDlg::on_btnParaSet_clicked()
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
void WeightMethodDlg::on_btnWaterIn_clicked() //��ˮ��
{
	m_nowPortNo = m_portsetinfo.waterInNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void WeightMethodDlg::on_btnWaterOut_clicked() //��ˮ��
{
	m_nowPortNo = m_portsetinfo.waterOutNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void WeightMethodDlg::on_btnValveBig_clicked() //��������
{
	m_nowPortNo = m_portsetinfo.bigNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void WeightMethodDlg::on_btnValveMiddle1_clicked() //����һ��
{
	m_nowPortNo = m_portsetinfo.middle1No;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);

}

void WeightMethodDlg::on_btnValveMiddle2_clicked() //��������
{
	m_nowPortNo = m_portsetinfo.middle2No;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}

void WeightMethodDlg::on_btnValveSmall_clicked() //С������
{
	m_nowPortNo = m_portsetinfo.smallNo;
	m_controlObj->makeRelaySendBuf(m_nowPortNo, !m_valveStatus[m_nowPortNo]);
}


/*
** ����ˮ��
*/
void WeightMethodDlg::on_btnWaterPumpStart_clicked()
{
	if (ui.spinBoxFrequency->value() <= 0)
	{
		QMessageBox::warning(this, tr("Warning"), tr("�����ñ�Ƶ��Ƶ�ʣ�"));
		ui.spinBoxFrequency->setFocus();
	}
	m_controlObj->makeRegulateSendBuf(m_portsetinfo.pumpNo, ui.spinBoxFrequency->value());
}

/*
** ֹͣˮ��
*/
void WeightMethodDlg::on_btnWaterPumpStop_clicked()
{
	m_controlObj->makeRegulateSendBuf(m_portsetinfo.pumpNo, 0);
}

//��ȡ���ֵ
int WeightMethodDlg::getMeterStartValue()
{
	if (m_autopick) //�Զ��ɼ�
	{
		for (int i=0; i<m_meterNum; i++)
		{
			m_meterStartValue[i] = 0.66;  //��ȡ������ֵ
		}
		return true;
	}
	else //�ֶ�����
	{
		QMessageBox::information(this, tr("Hint"), tr("�������������ֵ��"));
		ui.tableWidget->setCurrentCell(m_meterPosMap[0]-1, COLUMN_METER_START); //��λ����һ����Ҫ�����ֵ�ĵط�
		m_inputStartValue = true; //���������ֵ
		return false;
	}
}

//��һ�ε���ֵ��Ϊ���εĳ�ֵ
void WeightMethodDlg::makeStartValueByLastEndValue()
{
	float flow = m_paraSetReader->getFpBySeq(m_nowOrder).fp_verify;
	for (int i=0; i<m_meterNum; i++)
	{
		m_meterStartValue[i] = m_meterEndValue[i];
		ui.tableWidget->item(m_meterPosMap[i]-1, COLUMN_METER_START)->setText(QString("%1").arg(m_meterStartValue[i]));
 		ui.tableWidget->item(m_meterPosMap[i]-1, COLUMN_FLOW_POINT)->setText(QString("%1").arg(flow));
	}
}

//��ȡ����ֵ
int WeightMethodDlg::getMeterEndValue()
{
	if (m_autopick) //�Զ��ɼ�
	{
		for (int i=0; i<m_meterNum; i++)
		{
			m_meterEndValue[i] = 10.88;  //��ȡ�������ֵ
		}
		return true;
	}
	else //�ֶ�����
	{
		QMessageBox::information(this, tr("Hint"), tr("��������������ֵ��"));
		ui.tableWidget->setCurrentCell(m_meterPosMap[0]-1, COLUMN_METER_END); //��λ����һ����Ҫ������ֵ�ĵط�
		m_inputEndValue = true; //����������ֵ
		return false;
	}
}

//��Ӧ�����û���������ֵ������ֵ
void WeightMethodDlg::on_tableWidget_cellChanged(int row, int column)
{
	if (m_autopick) //�Զ��ɼ�
	{
		return;
	}

	int idx = -1;

	if (column==COLUMN_METER_START && m_inputStartValue) //���ֵ�� �� ���������ֵ
	{
		idx = isMeterPosValid(row);
		if (idx < 0)
		{
			return;
		}
		else
		{
			m_meterStartValue[idx] = ui.tableWidget->item(row, column)->text().toFloat();
		}

		if (row == (m_meterPosMap[m_meterNum-1]-1)) //�������һ�����ֵ
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
		idx = isMeterPosValid(row);
		if (idx < 0)
		{
			return;
		}
		else
		{
			m_meterEndValue[idx] = ui.tableWidget->item(row, column)->text().toFloat();
		}

		if (row == (m_meterPosMap[m_meterNum-1]-1)) //�������һ������ֵ
		{
			m_inputEndValue = false;
			calcMeterErrorAndSaveDb();
		}
		else //�������һ������ֵ,�Զ���λ����һ��
		{
			ui.tableWidget->setCurrentCell(m_meterPosMap[idx+1]-1, column);
		}
	}

}

/*
** �жϱ�λ���Ƿ���Ч(�ñ�λ�Ƿ���Ҫ���)
** ���ش�������������
*/
int WeightMethodDlg::isMeterPosValid(int row)
{
	for (int i=0; i<m_meterNum; i++)
	{
		if ((m_meterPosMap[i]-1) == row)
		{
			return i;
		}
	}
	return -1;
}

//����춨��¼
int WeightMethodDlg::saveVerifyRecord()
{
 	insertVerifyRec(m_recPtr, m_recNum);
	return true;
}
