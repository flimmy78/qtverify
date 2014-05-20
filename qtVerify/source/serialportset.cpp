#include <QtGui/QMessageBox>

#include "serialportset.h"

SerialPortSet::SerialPortSet(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	spsetui.setupUi(this);

	spsetui.closeMyComBtn->setEnabled(false); //开始“关闭串口”按钮不可用
	spsetui.sendMsgBtn->setEnabled(false); //开始“发送数据”按钮不可用
}

SerialPortSet::~SerialPortSet()
{

}

void SerialPortSet::anyfunc()
{
	QMessageBox::information(this, "SerialPortSet", "anyfunc", "Ok", "Cancel");	
	qDebug("%s, %d, SerialPortSet::anyfunc \n", __FILE__, __LINE__);
}

void SerialPortSet::on_openMyComBtn_clicked()
{
	struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};//定义一个结构体，用来存放串口各个参数
	myCom = new Win_QextSerialPort("com1",myComSetting,QextSerialBase::EventDriven);//定义串口对象，并传递参数，在构造函数里对其进行初始化
	myCom ->open(QIODevice::ReadWrite);//以可读写方式打开串口
	connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));//信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作

	spsetui.openMyComBtn->setEnabled(false); //打开串口后“打开串口”按钮不可用
	spsetui.closeMyComBtn->setEnabled(true); //打开串口后“关闭串口”按钮可用
	spsetui.sendMsgBtn->setEnabled(true);	//打开串口后“发送数据”按钮可用
}

void SerialPortSet::on_closeMyComBtn_clicked()
{
	myCom->close(); //关闭串口，该函数在win_qextserialport.cpp文件中定义

	spsetui.openMyComBtn->setEnabled(true); //关闭串口后“打开串口”按钮可用
	spsetui.closeMyComBtn->setEnabled(false); //关闭串口后“关闭串口”按钮不可用
	spsetui.sendMsgBtn->setEnabled(false); //关闭串口后“发送数据”按钮不可用
}

void SerialPortSet::on_sendMsgBtn_clicked()
{
	myCom->write(spsetui.sendMsgLineEdit->text().toAscii());//以ASCII码形式将行编辑框中的数据写入串口
	spsetui.textBrowser->insertPlainText("sp data is :\n");
}

void SerialPortSet::readMyCom()
{
	QByteArray temp = myCom->readAll();
	spsetui.textBrowser->insertPlainText(temp);
}
