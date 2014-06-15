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

#include "qualitydlg.h"

QualityDlg::QualityDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"QualityDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	m_paraset = new ParaSetDlg();

// 	openTemperatureCom(); //���¶Ȳɼ�����
	openValveControlCom();//�򿪷��ſ��ƴ���
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

void QualityDlg::openTemperatureCom()
{
	ComInfoStruct tempStruct;
	tempStruct.portName = "COM2";
	tempStruct.baudRate = 9600;
	tempStruct.dataBit = 8;
	tempStruct.parity = 2;
	tempStruct.stopBit = STOP_1;
	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->openTemperatureCom(&tempStruct);

	connect(m_tempObj, SIGNAL(tempComIsAnalysed(const QString &)), this, SLOT(slotFreshComTempValue(const QString &)));
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
	ui.lnEditTempIn->setText(tempStr);
}

void QualityDlg::slotSetValveBtnStatus(const int& isOpen )
{
	setValveBtnBackColor(ui.btnWaterIn, isOpen);
}




