#include <QtGui/QMessageBox>

#include "serialportset.h"

SerialPortSet::SerialPortSet(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	spsetui.setupUi(this);

	spsetui.closeMyComBtn->setEnabled(false); //��ʼ���رմ��ڡ���ť������
	spsetui.sendMsgBtn->setEnabled(false); //��ʼ���������ݡ���ť������
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
	struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};//����һ���ṹ�壬������Ŵ��ڸ�������
	myCom = new Win_QextSerialPort("com1",myComSetting,QextSerialBase::EventDriven);//���崮�ڶ��󣬲����ݲ������ڹ��캯���������г�ʼ��
	myCom ->open(QIODevice::ReadWrite);//�Կɶ�д��ʽ�򿪴���
	connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));//�źźͲۺ��������������ڻ�����������ʱ�����ж����ڲ���

	spsetui.openMyComBtn->setEnabled(false); //�򿪴��ں󡰴򿪴��ڡ���ť������
	spsetui.closeMyComBtn->setEnabled(true); //�򿪴��ں󡰹رմ��ڡ���ť����
	spsetui.sendMsgBtn->setEnabled(true);	//�򿪴��ں󡰷������ݡ���ť����
}

void SerialPortSet::on_closeMyComBtn_clicked()
{
	myCom->close(); //�رմ��ڣ��ú�����win_qextserialport.cpp�ļ��ж���

	spsetui.openMyComBtn->setEnabled(true); //�رմ��ں󡰴򿪴��ڡ���ť����
	spsetui.closeMyComBtn->setEnabled(false); //�رմ��ں󡰹رմ��ڡ���ť������
	spsetui.sendMsgBtn->setEnabled(false); //�رմ��ں󡰷������ݡ���ť������
}

void SerialPortSet::on_sendMsgBtn_clicked()
{
	myCom->write(spsetui.sendMsgLineEdit->text().toAscii());//��ASCII����ʽ���б༭���е�����д�봮��
	spsetui.textBrowser->insertPlainText("sp data is :\n");
}

void SerialPortSet::readMyCom()
{
	QByteArray temp = myCom->readAll();
	spsetui.textBrowser->insertPlainText(temp);
}
