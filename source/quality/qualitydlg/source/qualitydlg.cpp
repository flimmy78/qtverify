#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QThread>
#include "qualitydlg.h"

QualityDlg::QualityDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"QualityDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	m_ComTemp = NULL;
	openTemperatureCom(); 
	m_paraset = new ParaSetDlg();
}

QualityDlg::~QualityDlg()
{
	if(m_ComTemp != NULL)
	{
		if(m_ComTemp->isOpen())
		{
			m_ComTemp->close();
		}
		delete m_ComTemp;
	}


	if (m_paraset)
	{
		delete m_paraset;
		m_paraset = NULL;
	}
}

void QualityDlg::on_btnWaterIn_clicked()
{
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

void QualityDlg::openTemperatureCom()
{
	QString portName = "COM7";//��ȡ������
#ifdef Q_OS_LINUX
	m_ComTemp = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_ComTemp = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_ComTemp, SIGNAL(readyRead()), this, SLOT(readTemperatureComBuffer()));

	m_ComTemp->setBaudRate(BAUD9600); //���ò�����  
	m_ComTemp->setDataBits(DATA_8); //��������λ
	m_ComTemp->setParity(PAR_EVEN); //����У��λ
	m_ComTemp->setStopBits(STOP_1); //����ֹͣλ
	m_ComTemp->setFlowControl(FLOW_OFF); //��������������  
	m_ComTemp->setTimeout(TIME_OUT);     //������ʱ

	if(m_ComTemp->open(QIODevice::ReadWrite))
	{
		QMessageBox::information(this, tr("Open Success"), tr("Open SerialPort ") + portName + tr(" Success!"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::critical(this, tr("Open Failed"), tr("Can't Open SerialPort ") + portName + tr("\nDevice isn't exist or is occupied!"), QMessageBox::Ok);
	}
}

void QualityDlg::readTemperatureComBuffer()
{
	qDebug()<<"readWaterTemperature:";
}

