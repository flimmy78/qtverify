#include <QtGui/QMessageBox>

#include "serialportset.h"

SerialPortSet::SerialPortSet(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	spsetui.setupUi(this);

	spsetui.btnCloseCom->setEnabled(false); //开始“关闭串口”按钮不可用
	spsetui.btnSendMsg->setEnabled(false);  //开始“发送数据”按钮不可用
	spsetui.btnClearMsg->setEnabled(false); //开始“清除数据”按钮不可用
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
	QString portName = spsetui.portNameComboBox->currentText(); //获取串口名
	myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);//定义串口对象，并传递参数，在构造函数里对其进行初始化
	if (!myCom ->open(QIODevice::ReadWrite))//打开串口失败
	{
		QMessageBox::information(this, "SerialPortSet", QString("Open %1 Failed!").arg(portName), "Ok", "Cancel");	
		return;
	}
	
	//设置波特率
	if(spsetui.baudRateComboBox->currentText()==tr("9600")) //根据组合框内容对串口进行设置
		myCom->setBaudRate(BAUD9600);
	else if(spsetui.baudRateComboBox->currentText()==tr("115200"))
		myCom->setBaudRate(BAUD115200);

	//设置数据位
	if(spsetui.dataBitsComboBox->currentText()==tr("8"))
		myCom->setDataBits(DATA_8);
	else if(spsetui.dataBitsComboBox->currentText()==tr("7"))
		myCom->setDataBits(DATA_7);

	//设置奇偶校验
	if(spsetui.parityComboBox->currentText()==tr("无"))
		myCom->setParity(PAR_NONE);
	else if(spsetui.parityComboBox->currentText()==tr("奇"))
		myCom->setParity(PAR_ODD);
	else if(spsetui.parityComboBox->currentText()==tr("偶"))
		myCom->setParity(PAR_EVEN);

	//设置停止位
	if(spsetui.stopBitsComboBox->currentText()==tr("1"))
		myCom->setStopBits(STOP_1);
	else if(spsetui.stopBitsComboBox->currentText()==tr("2"))
		myCom->setStopBits(STOP_2);

	myCom->setFlowControl(FLOW_OFF); //设置数据流控制，我们使用无数据流控制的默认设置
	myCom->setTimeout(500); //设置延时

	connect(myCom,SIGNAL(readyRead()),this,SLOT(slotReadMyCom()));
	//信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作

	spsetui.btnOpenCom->setEnabled(false); //打开串口后“打开串口”按钮不可用
	spsetui.btnCloseCom->setEnabled(true); //打开串口后“关闭串口”按钮可用
	spsetui.btnSendMsg->setEnabled(true);  //打开串口后“发送数据”按钮可用
	spsetui.btnClearMsg->setEnabled(true); //打开串口后“清除数据”按钮可用
	
	spsetui.baudRateComboBox->setEnabled(false); //设置各个组合框不可用
	spsetui.dataBitsComboBox->setEnabled(false);
	spsetui.parityComboBox->setEnabled(false);
	spsetui.stopBitsComboBox->setEnabled(false);
	spsetui.portNameComboBox->setEnabled(false);


/*
	struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};//定义一个结构体，用来存放串口各个参数
	myCom = new Win_QextSerialPort("com1",myComSetting,QextSerialBase::EventDriven);//定义串口对象，并传递参数，在构造函数里对其进行初始化
	myCom ->open(QIODevice::ReadWrite);//以可读写方式打开串口
	connect(myCom,SIGNAL(readyRead()),this,SLOT(slotReadMyCom()));//信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作

	spsetui.btnOpenCom->setEnabled(false); //打开串口后“打开串口”按钮不可用
	spsetui.btnCloseCom->setEnabled(true); //打开串口后“关闭串口”按钮可用
	spsetui.btnSendMsg->setEnabled(true);	//打开串口后“发送数据”按钮可用
*/
}

void SerialPortSet::on_btnCloseCom_clicked()
{
	myCom->close(); //关闭串口，该函数在win_qextserialport.cpp文件中定义

	spsetui.btnOpenCom->setEnabled(true); //关闭串口后“打开串口”按钮可用
	spsetui.btnCloseCom->setEnabled(false); //关闭串口后“关闭串口”按钮不可用
	spsetui.btnSendMsg->setEnabled(false); //关闭串口后“发送数据”按钮不可用
	spsetui.baudRateComboBox->setEnabled(true); //设置各个组合框可用
	spsetui.dataBitsComboBox->setEnabled(true);
	spsetui.parityComboBox->setEnabled(true);
	spsetui.stopBitsComboBox->setEnabled(true);
	spsetui.portNameComboBox->setEnabled(true);

/*
	spsetui.btnOpenCom->setEnabled(true); //关闭串口后“打开串口”按钮可用
	spsetui.btnCloseCom->setEnabled(false); //关闭串口后“关闭串口”按钮不可用
	spsetui.btnSendMsg->setEnabled(false); //关闭串口后“发送数据”按钮不可用
*/
}

void SerialPortSet::on_btnSendMsg_clicked()
{
	int ret = myCom->write(spsetui.lineEditSendMsg->text().toAscii());//以ASCII码形式将行编辑框中的数据写入串口
	
//  spsetui.textBrowserRecMsg->insertPlainText(QString("send ret=%1\n").arg(ret));
}

void SerialPortSet::on_btnClearMsg_clicked()
{
	spsetui.textBrowserRecMsg->clear();
}

void SerialPortSet::slotReadMyCom()
{
	QByteArray temp = myCom->readAll();
	spsetui.textBrowserRecMsg->insertPlainText(temp);
}
