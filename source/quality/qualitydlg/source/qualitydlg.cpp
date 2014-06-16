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

	m_paraset = new ParaSetDlg();

	m_tempObj = NULL;
	initTemperatureCom(); //��ʼ���¶Ȳɼ�����

	m_valveObj = NULL;
// 	openValveControlCom();//�򿪷��ſ��ƴ���
}

QualityDlg::~QualityDlg()
{
	if (m_paraset)
	{
		delete m_paraset;
		m_paraset = NULL;
	}
	if (m_tempObj)
	{
		delete m_tempObj;
		m_tempObj = NULL;
	}
	if (m_valveObj)
	{
		delete m_valveObj;
		m_valveObj = NULL;
	}
}

void QualityDlg::initTemperatureCom()
{
	ComInfoStruct tempStruct;
	tempStruct.portName = "COM2";
	tempStruct.baudRate = 9600;
	tempStruct.dataBit = 8;
	tempStruct.parity = 0;
	tempStruct.stopBit = 0;
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj, SIGNAL(temperatureIsReady(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));

	m_tempTimer = new QTimer();
	connect(m_tempTimer, SIGNAL(timeout()), m_tempObj, SLOT(writeTemperatureComBuffer()));
	m_tempTimer->start(TIMEOUT_TEMPER);
}

void QualityDlg::openValveControlCom()
{
	ComInfoStruct valveStruct;
	valveStruct.portName = "COM2";
	valveStruct.baudRate = 9600;
	valveStruct.dataBit = 8;
	valveStruct.parity = 2;
	valveStruct.stopBit = STOP_1;
	m_valveObj = new ValveComObject();
	m_valveObj->moveToThread(&m_valveThread);
	m_valveThread.start();
	m_valveObj->openValveControlCom(&valveStruct);

	connect(m_valveObj, SIGNAL(valveComIsAnalysed(const int &)), this, SLOT(slotSetValveBtnStatus(const int &)));
}

void QualityDlg::on_btnWaterIn_clicked()
{
	m_valveObj->writeValveControlComBuffer();
	setValveBtnBackColor(ui.btnWaterIn, true);
}

void QualityDlg::setValveBtnBackColor(QPushButton *btn, bool isOpen)
{
	if (isOpen)
	{
		btn->setStyleSheet("background:green;border:0px;");  
	}
	else
	{
		btn->setStyleSheet("background:red;border:0px;");  
	}
}

void QualityDlg::on_btnParaSet_clicked()
{
	m_paraset->show();
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

void QualityDlg::slotSetValveBtnStatus(const int& isOpen )
{
	setValveBtnBackColor(ui.btnWaterIn, isOpen);
}




