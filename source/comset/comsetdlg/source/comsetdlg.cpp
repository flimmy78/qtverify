#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

#include "comsetdlg.h"
#include "commondefine.h"

ComSetDlg::ComSetDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	ui.btnCloseCom->setEnabled(false); //开始“关闭串口”按钮不可用
	ui.btnSendMsg->setEnabled(false);  //开始“发送数据”按钮不可用
	ui.btnClearMsg->setEnabled(false); //开始“清除数据”按钮不可用
}

ComSetDlg::~ComSetDlg()
{

}

void ComSetDlg::sp_anyfunc()
{
	QMessageBox::information(this, "SerialPortSet", "sp_anyfunc", "Ok", "Cancel");	
	qDebug("%s, %d, SerialPortSet::sp_anyfunc \n", __FILE__, __LINE__);
}

void ComSetDlg::on_btnOpenCom_clicked()
{
	QString portName = ui.portNameComboBox->currentText(); //获取串口名
	myCom = new QextSerialPort(portName,QextSerialPort::EventDriven);//定义串口对象，并传递参数，在构造函数里对其进行初始化
	if (!myCom ->open(QIODevice::ReadWrite))//打开串口失败
	{
		QMessageBox::information(this, "SerialPortSet", QString("Open %1 Failed!").arg(portName), "Ok", "Cancel");	
		return;
	}
	
	//设置波特率
	if(ui.baudRateComboBox->currentText()==tr("9600")) //根据组合框内容对串口进行设置
		myCom->setBaudRate(BAUD9600);
	else if(ui.baudRateComboBox->currentText()==tr("115200"))
		myCom->setBaudRate(BAUD115200);

	//设置数据位
	if(ui.dataBitsComboBox->currentText()==tr("8"))
		myCom->setDataBits(DATA_8);
	else if(ui.dataBitsComboBox->currentText()==tr("7"))
		myCom->setDataBits(DATA_7);

	//设置奇偶校验
	if(ui.parityComboBox->currentText()==tr("无"))
		myCom->setParity(PAR_NONE);
	else if(ui.parityComboBox->currentText()==tr("奇"))
		myCom->setParity(PAR_ODD);
	else if(ui.parityComboBox->currentText()==tr("偶"))
		myCom->setParity(PAR_EVEN);

	//设置停止位
	if(ui.stopBitsComboBox->currentText()==tr("1"))
		myCom->setStopBits(STOP_1);
	else if(ui.stopBitsComboBox->currentText()==tr("2"))
		myCom->setStopBits(STOP_2);

	myCom->setFlowControl(FLOW_OFF); //设置数据流控制，我们使用无数据流控制的默认设置
	myCom->setTimeout(500); //设置延时

	connect(myCom,SIGNAL(readyRead()),this,SLOT(slotReadMyCom()));
	//信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作

	ui.btnOpenCom->setEnabled(false); //打开串口后“打开串口”按钮不可用
	ui.btnCloseCom->setEnabled(true); //打开串口后“关闭串口”按钮可用
	ui.btnSendMsg->setEnabled(true);  //打开串口后“发送数据”按钮可用
	ui.btnClearMsg->setEnabled(true); //打开串口后“清除数据”按钮可用
	
	ui.baudRateComboBox->setEnabled(false); //设置各个组合框不可用
	ui.dataBitsComboBox->setEnabled(false);
	ui.parityComboBox->setEnabled(false);
	ui.stopBitsComboBox->setEnabled(false);
	ui.portNameComboBox->setEnabled(false);


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

void ComSetDlg::on_btnCloseCom_clicked()
{
	myCom->close(); //关闭串口，该函数在win_qextserialport.cpp文件中定义

	ui.btnOpenCom->setEnabled(true); //关闭串口后“打开串口”按钮可用
	ui.btnCloseCom->setEnabled(false); //关闭串口后“关闭串口”按钮不可用
	ui.btnSendMsg->setEnabled(false); //关闭串口后“发送数据”按钮不可用
	ui.baudRateComboBox->setEnabled(true); //设置各个组合框可用
	ui.dataBitsComboBox->setEnabled(true);
	ui.parityComboBox->setEnabled(true);
	ui.stopBitsComboBox->setEnabled(true);
	ui.portNameComboBox->setEnabled(true);

/*
	spsetui.btnOpenCom->setEnabled(true); //关闭串口后“打开串口”按钮可用
	spsetui.btnCloseCom->setEnabled(false); //关闭串口后“关闭串口”按钮不可用
	spsetui.btnSendMsg->setEnabled(false); //关闭串口后“发送数据”按钮不可用
*/
}

void ComSetDlg::on_btnSendMsg_clicked()
{
	int ret = myCom->write(ui.lineEditSendMsg->text().toAscii());//以ASCII码形式将行编辑框中的数据写入串口
	qDebug()<<"write:"<<ui.lineEditSendMsg->text().toAscii().length()<<"bytes";//<<sizeof(ui.lineEditSendMsg->text())<<ui.lineEditSendMsg->text().length();
}

void ComSetDlg::on_btnClearMsg_clicked()
{
	ui.textBrowserRecMsg->clear();
}

void ComSetDlg::slotReadMyCom()
{
// 	if (myCom->bytesAvailable() >= 8)
// 	{
		qDebug()<<"read:"<<myCom->bytesAvailable()<<"bytes";
		QByteArray temp = myCom->readAll();
		ui.textBrowserRecMsg->insertPlainText(temp);
// 	}
}
