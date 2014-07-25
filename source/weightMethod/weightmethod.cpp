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

#include "weightmethod.h"
#include "commondefine.h"

WeightMethodDlg::WeightMethodDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"WeightMethodDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	ui.tabWidget->setTabsClosable(true);
	connect(ui.tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));

	/////////////////////////////////////////////////////////
	ui.lcdNumberInTemper->display("27.8");
	QString inTemper = QString("%1").arg(ui.lcdNumberInTemper->value(), 4);
	float iii = inTemper.toFloat();

	m_balTimer = new QTimer(this);
	connect(m_balTimer, SIGNAL(timeout()), this, SLOT(freshBigBalaceValue()));
	m_balTimer->start(200); //ģ����ƽÿ200�������һ��
	m_balValue = 0.0;
	m_tempValue = 20.0;

	m_readComConfig = NULL;
	m_readComConfig = new ReadComConfig();

	m_balanceObj = NULL;
	initBalanceCom();		//��ʼ����ƽ����

	m_tempObj = NULL;
	m_tempTimer = NULL;
	initTemperatureCom();	//��ʼ���¶Ȳɼ�����


/*	for (int i=0; i<4; i++)
	{
		ui.tabWidget->removeTab(1);
	}*/
	////////////////////////////////////////////////////////

	m_meterNumMap[0] = 16; //DN15������춨16��
	m_meterNumMap[1] = 16; //DN20������춨16��
    m_meterNumMap[2] = 12; //DN25������춨12��

	m_paraSetReader = new ParaSetReader();

	m_exaustTimer = new QTimer(this); //������ʱ��
	connect(m_exaustTimer, SIGNAL(timeout()), this, SLOT(slotExaustFinished()));



	m_continueVerify = true;
	m_resetZero = false;
	m_flowPointNum = 0;
	m_exaustSecond = 45;
	m_meterStartValue = NULL;
	m_meterEndValue = NULL;
	m_balStartV = 0;
	m_balEndV = 0;
	if (!readParaConfig())
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

	if (NULL == m_paraSetReader) //���춨����
	{
		delete []m_paraSetReader;
		m_paraSetReader = NULL;
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


/***************************************
	�¶Ȳɼ����� ��λ��ֱ�Ӳɼ�
	��������
****************************************/
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
// 	connect(m_tempTimer, SIGNAL(timeout()), this, SLOT(slotFreshFlow()));
	
	m_tempTimer->start(TIMEOUT_TEMPER); //���������¶�
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

/************************************************************************/
/* ����˲ʱ����(���Ľ�����Ҫʵ����֤)                                   */
/************************************************************************/
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

//�����������ļ�
int WeightMethodDlg::readParaConfig()
{
	m_continueVerify = m_paraSetReader->params->bo_converify; //�����춨
	m_resetZero = m_paraSetReader->params->bo_resetzero; //��ֵ����
	m_flowPointNum = m_paraSetReader->params->total_fp;  //��Ч������ĸ��� 
	m_exaustSecond = m_paraSetReader->params->ex_time;   //����ʱ��


	int standard = m_paraSetReader->params->m_stand; //����
	m_meterNum = m_meterNumMap[standard]; //��ͬ�����Ӧ�����������
	m_meterStartValue = new float[m_meterNum]; 
	memset(m_meterStartValue, 0, sizeof(float)*m_meterNum);
	m_meterStartValue[0] = 111.111;
	m_meterEndValue = new float[m_meterNum];
	memset(m_meterEndValue, 0, sizeof(float)*m_meterNum);
	ui.tableWidget->setRowCount(m_meterNum);

	return true;
}

/*
**	���"������ť"����ʼ�춨
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

	m_exaustTimer->start(m_exaustSecond*1000);//��ʼ��������ʱ

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
	m_exaustTimer->stop(); //ֹͣ������ʱ

	if (!closeAllFlowPointValves()) //�ر����������㷧�� ʧ��
	{
		if (!closeAllFlowPointValves()) //�ٳ��Թر�һ��
		{
			qWarning()<<"�춨����";
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

//��ȡ���
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
	while (ui.lnEditBigBalance->text().toFloat() < v)
	{
		qDebug()<<"��ƽ���� ="<<ui.lnEditBigBalance->text().toFloat()<<", С��Ҫ������� "<<v;
		QTest::qWait(1000);
	}

	return true;
}

//�ж��������ѽ���춨״̬
int WeightMethodDlg::isAllMeterInVerifyStatus()
{
	return true;
}

//���"��ʼ"��ť
void WeightMethodDlg::on_btnStart_clicked()
{
	startVerify();
}

//���"��һ��"��ť
void WeightMethodDlg::on_btnNext_clicked()
{
	startVerifyFlowPoint(2); // ��ʼ������һ��������ļ춨
}


//��ʼ�춨
void WeightMethodDlg::startVerify()
{
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
			startVerifyFlowPoint(j+1);
		}
	}

	////////////////////////////////�������춨
	if (!m_continueVerify)
	{
		if (startVerifyFlowPoint(1)) //��һ��������춨
		{
			ui.btnNext->show();
			ui.btnNext->setDefault(true);
		}
	}
	//������
}

//ˢ����ƽ��ֵ ��������
void WeightMethodDlg::freshBigBalaceValue()
{
	if (m_balValue > 10)
	{
		m_balValue = 0;
	}
	m_balValue += 0.01;
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

//����������ļ춨,order��1��ʼ
int WeightMethodDlg::startVerifyFlowPoint(int order)
{
	if (!m_continueVerify) //�������춨��ÿ�μ춨��ʼ֮ǰ��Ҫ�ж���ƽ����
	{
		if (!judgeBalanceCapacitySingle(order)) //�ж���ƽ�����Ƿ��ܹ����㵥�μ춨����
		{
			openWaterOutValve();
		}
		while (!judgeBalanceCapacitySingle(order))
		{ 
			QTest::qWait(1000);
		}
		closeWaterOutValve(); //������춨��������رշ�ˮ��
		QTest::qWait(3000); //�ȴ�3���ӣ��ȴ�ˮ���ȶ�
	}

	if (m_resetZero) //��ֵ����
	{
		QTest::qWait(18000); //�ȴ�18�룬�ȴ�������ֵ����
		memset(m_meterStartValue, 0, sizeof(float)*m_meterNum);
	}
	else //��ֵ������
	{
		for (int i=0; i<m_meterNum; i++)
		{
			m_meterStartValue[i] = 0.66;  //��ȡ������ֵ
		}		
	}

	m_balStartV = ui.lnEditBigBalance->text().toFloat(); //��¼��ƽ��ֵ
	m_pipeInTemper = ui.lcdNumberInTemper->value();
	m_pipeOutTemper = ui.lcdNumberOutTemper->value();

	int portNo = m_paraSetReader->getFpBySeq(order).fp_valve;  //order��Ӧ�ķ��Ŷ˿ں�
	float verifyQuantity = m_paraSetReader->getFpBySeq(order).fp_quantity; //��order�μ춨��Ӧ�ļ춨��
	if (openValve(portNo))
	{
		if (judgeBalanceInitValue(m_balStartV + verifyQuantity))
		{
			closeValve(portNo); //�ر�order��Ӧ�ķ���
			m_balEndV = ui.lnEditBigBalance->text().toFloat(); //��¼��ƽ��ֵ
			memset(m_meterEndValue, 50.5, sizeof(float)*m_meterNum); //��¼����ֵ

			//����ÿ���������¶�
			//����ÿ���������ܶ�
			//����ÿ�������ı�׼ֵ
			//����ÿ��������ڽ�����ʾ
			//���������ݿ�
		}
	}

	return true;
}

//�򿪷���
int WeightMethodDlg::openValve(int portno)
{
	return true;
}

//�رշ���
int WeightMethodDlg::closeValve(int portno)
{
	return true;
}
