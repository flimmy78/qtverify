#include <QtGui/QMessageBox>

#include "serialportset.h"

SerialPortSet::SerialPortSet(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	spsetui.setupUi(this);

// 	connect(spsetui.btnOpenCom, SIGNAL(clicked()), this, SLOT(on_btnOpenCom_clicked()));
// 	connect(spsetui.btnCloseCom, SIGNAL(clicked()), this, SLOT(on_btnCloseCom_clicked()));
// 	connect(spsetui.btnSendMsg, SIGNAL(clicked()), this, SLOT(on_btnSendMsg_clicked()));

	spsetui.btnCloseCom->setEnabled(false); //开始“关闭串口”按钮不可用
	spsetui.btnSendMsg->setEnabled(false); //开始“发送数据”按钮不可用
}

SerialPortSet::~SerialPortSet()
{

}

void SerialPortSet::sp_anyfunc()
{
	QMessageBox::information(this, "SerialPortSet", "sp_anyfunc", "Ok", "Cancel");	
	qDebug("%s, %d, SerialPortSet::sp_anyfunc \n", __FILE__, __LINE__);
}

void SerialPortSet::on_btnOpenCom_clicked()
{
	struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};//定义一个结构体，用来存放串口各个参数
	myCom = new Win_QextSerialPort("com1",myComSetting,QextSerialBase::EventDriven);//定义串口对象，并传递参数，在构造函数里对其进行初始化
	myCom ->open(QIODevice::ReadWrite);//以可读写方式打开串口
	connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));//信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作

	spsetui.btnOpenCom->setEnabled(false); //打开串口后“打开串口”按钮不可用
	spsetui.btnCloseCom->setEnabled(true); //打开串口后“关闭串口”按钮可用
	spsetui.btnSendMsg->setEnabled(true);	//打开串口后“发送数据”按钮可用
}

void SerialPortSet::on_btnCloseCom_clicked()
{
	myCom->close(); //关闭串口，该函数在win_qextserialport.cpp文件中定义

	spsetui.btnOpenCom->setEnabled(true); //关闭串口后“打开串口”按钮可用
	spsetui.btnCloseCom->setEnabled(false); //关闭串口后“关闭串口”按钮不可用
	spsetui.btnSendMsg->setEnabled(false); //关闭串口后“发送数据”按钮不可用
}

void SerialPortSet::on_btnSendMsg_clicked()
{
	myCom->write(spsetui.lineEditSendMsg->text().toAscii());//以ASCII码形式将行编辑框中的数据写入串口
	spsetui.textBrowserRecMsg->insertPlainText("sp data is :\n");
}

void SerialPortSet::readMyCom()
{
	QByteArray temp = myCom->readAll();
	spsetui.textBrowserRecMsg->insertPlainText(temp);
}
