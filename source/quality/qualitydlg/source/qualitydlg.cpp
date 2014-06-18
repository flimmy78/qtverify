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
// 	initTemperatureCom(); //��ʼ���¶Ȳɼ�����

	m_controlObj = NULL;
	initControlCom();//�򿪿��ƴ���
	m_valveWaterInStatus = false;//��ˮ����״̬ false���ر�״̬; true:��״̬ 
	setBtnBackColor(ui.btnWaterIn, m_valveWaterInStatus);
	m_Valve1Status = false; //�������㷧��״̬
	setBtnBackColor(ui.btnWaterValve1, m_Valve1Status);

	m_balanceObj = NULL;
// 	initBalanceCom();
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
}

void QualityDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadTempConfig();
// 	tempStruct.portName = "COM2";
// 	tempStruct.baudRate = 9600;
// 	tempStruct.dataBit = 8;
// 	tempStruct.parity = 0;
// 	tempStruct.stopBit = 0;
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer(this);
	connect(m_tempTimer, SIGNAL(timeout()), m_tempObj, SLOT(writeTemperatureComBuffer()));
	m_tempTimer->start(TIMEOUT_TEMPER); //���������¶�
}

void QualityDlg::initControlCom()
{
	ComInfoStruct valveStruct = m_readComConfig->ReadValeConfig();
	m_controlObj = new ControlComObject();
	m_controlObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_controlObj->openControlCom(&valveStruct);

	connect(m_controlObj, SIGNAL(controlComIsAnalysed(const bool &)), this, SLOT(slotSetValveBtnStatus(const bool &)));
}

void QualityDlg::initBalanceCom()
{
	ComInfoStruct balanceStruct = m_readComConfig->ReadBalanceConfig();
	m_balanceObj = new BalanceComObject();
	m_balanceObj->moveToThread(&m_balanceThread);
	m_balanceThread.start();
	m_balanceObj->openBalanceCom(&balanceStruct);

 	connect(m_balanceObj, SIGNAL(balanceValueIsReady(const QString &)), this, SLOT(slotFreshBalanceValue(const QString &)));
}

void QualityDlg::on_btnWaterIn_clicked()
{
	int portno = 1; //����˿ں�Ϊ1
	m_controlObj->writeControlComBuffer(portno, !m_valveWaterInStatus);
	m_valveWaterInStatus = !m_valveWaterInStatus; //ֻ������
	setBtnBackColor(ui.btnWaterIn, m_valveWaterInStatus); //ֻ������
}

void QualityDlg::on_btnWaterOut_clicked()
{
//	m_balanceObj->writeBalanceComBuffer(); //ֻΪ������ д��ƽ���ڻ�����
}

void QualityDlg::on_btnWaterValve1_clicked()
{
	int portno = 2; //����˿ں�Ϊ1
	m_controlObj->writeControlComBuffer(portno, !m_Valve1Status);
	m_Valve1Status = !m_Valve1Status; //ֻ������
	setBtnBackColor(ui.btnWaterValve1, m_Valve1Status); //ֻ������
}

void QualityDlg::setBtnBackColor(QPushButton *btn, bool status)
{
	if (status)
	{
		btn->setStyleSheet("background:red;border:0px;");  
	}
	else
	{
		btn->setStyleSheet("background:green;border:0px;");  
	}
}

void QualityDlg::on_btnParaSet_clicked()
{
	m_paraset->show();
}

void QualityDlg::on_btnSave_clicked()
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

void QualityDlg::slotSetValveBtnStatus(const bool& status )
{
	m_valveWaterInStatus = status;
	setBtnBackColor(ui.btnWaterIn, m_valveWaterInStatus);
}




