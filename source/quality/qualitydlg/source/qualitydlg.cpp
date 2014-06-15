#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

#include "qualitydlg.h"

QualityDlg::QualityDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"QualityDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	m_paraset = new ParaSetDlg();

	m_tempObj = new TempComObject();
	m_tempObj->moveToThread(&m_tempThread);
	m_tempThread.start();
	m_tempObj->myslot();

	connect(m_tempObj, SIGNAL(tempValueIsReady(const QString &)), this, SLOT(freshComTempValue(const QString &)));
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

void QualityDlg::freshComTempValue(const QString& tempStr)
{
	ui.lnEditTempIn->setText(tempStr);
}



/************************************************
���ڲ�����
���ܣ��򿪴��ڣ����ô��ڲ������رմ��ڣ�
      ��ȡ���ڻ��������ݣ�����Э�������
*************************************************/
TempComObject::TempComObject() : QObject()
{
	m_tempCom = NULL;
}

TempComObject::~TempComObject()
{
	if(m_tempCom != NULL)
	{
		if(m_tempCom->isOpen())
		{
			m_tempCom->close();
		}
		delete m_tempCom;
	}
}

void TempComObject::myslot()
{    
	qDebug()<<"myslot thread:" <<QThread::currentThreadId();
	openTemperatureCom();
}   

void TempComObject::openTemperatureCom()
{
	qDebug()<<"openTemperatureCom thread:"<<QThread::currentThreadId();

	QString portName = "COM2";//��ȡ������
#ifdef Q_OS_LINUX
	m_tempCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_tempCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_tempCom, SIGNAL(readyRead()), this, SLOT(readTemperatureComBuffer()));

	m_tempCom->setBaudRate(BAUD9600); //���ò�����  
	m_tempCom->setDataBits(DATA_8);   //��������λ
	m_tempCom->setParity(PAR_EVEN);   //����У��λ
	m_tempCom->setStopBits(STOP_1);   //����ֹͣλ
	m_tempCom->setFlowControl(FLOW_OFF); //��������������  
	m_tempCom->setTimeout(TIME_OUT);     //������ʱ

	if(m_tempCom->open(QIODevice::ReadWrite))
	{
// 		QMessageBox::information(this, tr("Open Success"), tr("Open SerialPort ") + portName + tr(" Success!"), QMessageBox::Ok);
		qDebug()<<"Open SerialPort:"<<portName<<"Success!";
	}
	else
	{
// 		QMessageBox::critical(this, tr("Open Failed"), tr("Can't Open SerialPort ") + portName + tr("\nDevice isn't exist or is occupied!"), QMessageBox::Ok);
		qDebug()<<"Open SerialPort:"<<portName<<"Failed!";
		return;
	}

	m_tempCom->write("0xA8yangshen");
}

void TempComObject::readTemperatureComBuffer()
{
	QByteArray temp = m_tempCom->readAll();
	qDebug()<<"readTemperatureComBuffer thread:"<<QThread::currentThreadId()<<", Read data is:"<<temp;
	float tempValue = 66.68;
	QString tempStr;
	tempStr.setNum(tempValue, 'f', 2);
	emit tempValueIsReady(tempStr);
}


