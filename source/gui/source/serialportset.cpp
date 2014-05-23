#include <QtGui/QMessageBox>

#include "serialportset.h"

SerialPortSet::SerialPortSet(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	spsetui.setupUi(this);

	spsetui.btnCloseCom->setEnabled(false); //��ʼ���رմ��ڡ���ť������
	spsetui.btnSendMsg->setEnabled(false);  //��ʼ���������ݡ���ť������
	spsetui.btnClearMsg->setEnabled(false); //��ʼ��������ݡ���ť������
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
	QString portName = spsetui.portNameComboBox->currentText(); //��ȡ������
	myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);//���崮�ڶ��󣬲����ݲ������ڹ��캯���������г�ʼ��
	if (!myCom ->open(QIODevice::ReadWrite))//�򿪴���ʧ��
	{
		QMessageBox::information(this, "SerialPortSet", QString("Open %1 Failed!").arg(portName), "Ok", "Cancel");	
		return;
	}
	
	//���ò�����
	if(spsetui.baudRateComboBox->currentText()==tr("9600")) //������Ͽ����ݶԴ��ڽ�������
		myCom->setBaudRate(BAUD9600);
	else if(spsetui.baudRateComboBox->currentText()==tr("115200"))
		myCom->setBaudRate(BAUD115200);

	//��������λ
	if(spsetui.dataBitsComboBox->currentText()==tr("8"))
		myCom->setDataBits(DATA_8);
	else if(spsetui.dataBitsComboBox->currentText()==tr("7"))
		myCom->setDataBits(DATA_7);

	//������żУ��
	if(spsetui.parityComboBox->currentText()==tr("��"))
		myCom->setParity(PAR_NONE);
	else if(spsetui.parityComboBox->currentText()==tr("��"))
		myCom->setParity(PAR_ODD);
	else if(spsetui.parityComboBox->currentText()==tr("ż"))
		myCom->setParity(PAR_EVEN);

	//����ֹͣλ
	if(spsetui.stopBitsComboBox->currentText()==tr("1"))
		myCom->setStopBits(STOP_1);
	else if(spsetui.stopBitsComboBox->currentText()==tr("2"))
		myCom->setStopBits(STOP_2);

	myCom->setFlowControl(FLOW_OFF); //�������������ƣ�����ʹ�������������Ƶ�Ĭ������
	myCom->setTimeout(500); //������ʱ

	connect(myCom,SIGNAL(readyRead()),this,SLOT(slotReadMyCom()));
	//�źźͲۺ��������������ڻ�����������ʱ�����ж����ڲ���

	spsetui.btnOpenCom->setEnabled(false); //�򿪴��ں󡰴򿪴��ڡ���ť������
	spsetui.btnCloseCom->setEnabled(true); //�򿪴��ں󡰹رմ��ڡ���ť����
	spsetui.btnSendMsg->setEnabled(true);  //�򿪴��ں󡰷������ݡ���ť����
	spsetui.btnClearMsg->setEnabled(true); //�򿪴��ں�������ݡ���ť����
	
	spsetui.baudRateComboBox->setEnabled(false); //���ø�����Ͽ򲻿���
	spsetui.dataBitsComboBox->setEnabled(false);
	spsetui.parityComboBox->setEnabled(false);
	spsetui.stopBitsComboBox->setEnabled(false);
	spsetui.portNameComboBox->setEnabled(false);


/*
	struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};//����һ���ṹ�壬������Ŵ��ڸ�������
	myCom = new Win_QextSerialPort("com1",myComSetting,QextSerialBase::EventDriven);//���崮�ڶ��󣬲����ݲ������ڹ��캯���������г�ʼ��
	myCom ->open(QIODevice::ReadWrite);//�Կɶ�д��ʽ�򿪴���
	connect(myCom,SIGNAL(readyRead()),this,SLOT(slotReadMyCom()));//�źźͲۺ��������������ڻ�����������ʱ�����ж����ڲ���

	spsetui.btnOpenCom->setEnabled(false); //�򿪴��ں󡰴򿪴��ڡ���ť������
	spsetui.btnCloseCom->setEnabled(true); //�򿪴��ں󡰹رմ��ڡ���ť����
	spsetui.btnSendMsg->setEnabled(true);	//�򿪴��ں󡰷������ݡ���ť����
*/
}

void SerialPortSet::on_btnCloseCom_clicked()
{
	myCom->close(); //�رմ��ڣ��ú�����win_qextserialport.cpp�ļ��ж���

	spsetui.btnOpenCom->setEnabled(true); //�رմ��ں󡰴򿪴��ڡ���ť����
	spsetui.btnCloseCom->setEnabled(false); //�رմ��ں󡰹رմ��ڡ���ť������
	spsetui.btnSendMsg->setEnabled(false); //�رմ��ں󡰷������ݡ���ť������
	spsetui.baudRateComboBox->setEnabled(true); //���ø�����Ͽ����
	spsetui.dataBitsComboBox->setEnabled(true);
	spsetui.parityComboBox->setEnabled(true);
	spsetui.stopBitsComboBox->setEnabled(true);
	spsetui.portNameComboBox->setEnabled(true);

/*
	spsetui.btnOpenCom->setEnabled(true); //�رմ��ں󡰴򿪴��ڡ���ť����
	spsetui.btnCloseCom->setEnabled(false); //�رմ��ں󡰹رմ��ڡ���ť������
	spsetui.btnSendMsg->setEnabled(false); //�رմ��ں󡰷������ݡ���ť������
*/
}

void SerialPortSet::on_btnSendMsg_clicked()
{
	int ret = myCom->write(spsetui.lineEditSendMsg->text().toAscii());//��ASCII����ʽ���б༭���е�����д�봮��
	
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
