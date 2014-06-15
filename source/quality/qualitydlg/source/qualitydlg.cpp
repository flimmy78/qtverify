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
串口操作类
功能：打开串口；设置串口参数；关闭串口；
      读取串口缓冲区数据；根据协议解析等
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

	QString portName = "COM2";//获取串口名
#ifdef Q_OS_LINUX
	m_tempCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_tempCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
#endif
	connect(m_tempCom, SIGNAL(readyRead()), this, SLOT(readTemperatureComBuffer()));

	m_tempCom->setBaudRate(BAUD9600); //设置波特率  
	m_tempCom->setDataBits(DATA_8);   //设置数据位
	m_tempCom->setParity(PAR_EVEN);   //设置校验位
	m_tempCom->setStopBits(STOP_1);   //设置停止位
	m_tempCom->setFlowControl(FLOW_OFF); //设置数据流控制  
	m_tempCom->setTimeout(TIME_OUT);     //设置延时

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


