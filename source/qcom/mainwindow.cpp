#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	startInit();
	myCom = NULL;

// 	ui->qter->setText(tr("<a href=\"http://www.sdm.com.cn\">www.shm.com.cn</a>"));
#ifdef Q_OS_LINUX
	ui->portNameComboBox->addItem( "ttyUSB0");
	ui->portNameComboBox->addItem( "ttyUSB1");
	ui->portNameComboBox->addItem( "ttyUSB2");
	ui->portNameComboBox->addItem( "ttyUSB3");
	ui->portNameComboBox->addItem( "ttyS0");
	ui->portNameComboBox->addItem( "ttyS1");
	ui->portNameComboBox->addItem( "ttyS2");
	ui->portNameComboBox->addItem( "ttyS3");
	ui->portNameComboBox->addItem( "ttyS4");
	ui->portNameComboBox->addItem( "ttyS5");
	ui->portNameComboBox->addItem( "ttyS6");
#elif defined (Q_OS_WIN)
	ui->portNameComboBox->addItem("COM1");
	ui->portNameComboBox->addItem("COM2");
	ui->portNameComboBox->addItem("COM3");
	ui->portNameComboBox->addItem("COM4");
	ui->portNameComboBox->addItem("COM5");
	ui->portNameComboBox->addItem("COM6");
	ui->portNameComboBox->addItem("COM7");
	ui->portNameComboBox->addItem("COM8");
	ui->portNameComboBox->addItem("COM9");
	ui->portNameComboBox->addItem("COM10");
	ui->portNameComboBox->addItem("COM11");
	ui->portNameComboBox->addItem("COM12");
	ui->portNameComboBox->addItem("COM13");
	ui->portNameComboBox->addItem("COM14");
	ui->portNameComboBox->addItem("COM15");
	ui->portNameComboBox->addItem("COM16");
	ui->portNameComboBox->addItem("COM17");
	ui->portNameComboBox->addItem("COM18");
	ui->portNameComboBox->addItem("COM19");
	ui->portNameComboBox->addItem("COM20");

#endif

	ui->statusBar->showMessage(QObject::tr("Welcome Using QCom!"));
	ui->btnRecv->hide();

	//�����ϴα���Ĵ��ڲ���
	QString path = QProcessEnvironment::systemEnvironment().value("RUNHOME");
	m_filename = path + "\\ini\\comdebugger.ini";
	m_comset = new QSettings(m_filename, QSettings::IniFormat);
	if (m_comset)
	{
		ui->portNameComboBox->setCurrentIndex(m_comset->value("ComSettings/ComName").toInt());
		ui->baudRateComboBox->setCurrentIndex(m_comset->value("ComSettings/BaudRate").toInt());
		ui->dataBitsComboBox->setCurrentIndex(m_comset->value("ComSettings/DataBit").toInt());
		ui->parityComboBox->setCurrentIndex(m_comset->value("ComSettings/Parity").toInt());
		ui->stopBitsComboBox->setCurrentIndex(m_comset->value("ComSettings/StopBit").toInt());
	}
	
}

MainWindow::~MainWindow()
{
	if(myCom != NULL)
	{
		if(myCom->isOpen())
		{
			myCom->close();
		}
		delete myCom;
	}
	delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) 
	{
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void MainWindow::startInit()
{
	setActionsEnabled(false);
	ui->delayspinBox->setEnabled(false);
	ui->sendmsgBtn->setEnabled(false);
	ui->textEditSend->setEnabled(false);
	ui->obocheckBox->setEnabled(false);

	//��ʼ���������ͼ�ʱ����ʱ���
	obotimerdly = OBO_TIMER_INTERVAL;

	//�����������ͼ�ʱ��
	obotimer = new QTimer(this);
	connect(obotimer, SIGNAL(timeout()), this, SLOT(sendMsg()));
}

void MainWindow::setActionsEnabled(bool status)
{
	ui->actionSave->setEnabled(status);
	ui->actionClose->setEnabled(status);
	ui->actionLoadfile->setEnabled(status);
	ui->actionCleanPort->setEnabled(status);
	ui->actionWriteToFile->setEnabled(status);
}

void MainWindow::setComboBoxEnabled(bool status)
{
	ui->portNameComboBox->setEnabled(status);
	ui->baudRateComboBox->setEnabled(status);
	ui->dataBitsComboBox->setEnabled(status);
	ui->parityComboBox->setEnabled(status);
	ui->stopBitsComboBox->setEnabled(status);
}

//�򿪴���
void MainWindow::on_actionOpen_triggered()
{
	QString portName = ui->portNameComboBox->currentText();   //��ȡ������
#ifdef Q_OS_LINUX
	myCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	myCom = new QextSerialPort(portName);
#endif
	connect(myCom, SIGNAL(readyRead()), this, SLOT(readMyCom()));

	//���ò�����
	myCom->setBaudRate((BaudRateType)ui->baudRateComboBox->currentText().toInt());

	//��������λ
	myCom->setDataBits((DataBitsType)ui->dataBitsComboBox->currentText().toInt());

	//����У��
	switch(ui->parityComboBox->currentIndex())
	{
	case 0:
		myCom->setParity(PAR_NONE);
		break;
	case 1:
		myCom->setParity(PAR_ODD);
		break;
	case 2:
		myCom->setParity(PAR_EVEN);
		break;
	default:
		myCom->setParity(PAR_NONE);
		qDebug("set to default : PAR_NONE");
		break;
	}

	//����ֹͣλ
	switch(ui->stopBitsComboBox->currentIndex())
	{
	case 0:
		myCom->setStopBits(STOP_1);
		break;
	case 1:
#ifdef Q_OS_WIN
		myCom->setStopBits(STOP_1_5);
#endif
		break;
	case 2:
		myCom->setStopBits(STOP_2);
		break;
	default:
		myCom->setStopBits(STOP_1);
		qDebug("set to default : STOP_1");
		break;
	}    

	//��������������
	myCom->setFlowControl(FLOW_OFF);
	//������ʱ
	myCom->setTimeout(TIME_OUT);

	if (myCom->open(QIODevice::ReadWrite))
	{
		QMessageBox::information(this, tr("OK"), tr("open ") + portName + tr(" success!"), QMessageBox::Ok);
		//�������
		ui->sendmsgBtn->setEnabled(true);
		setComboBoxEnabled(false);

		ui->textEditSend->setEnabled(true);

		ui->actionOpen->setEnabled(false);
		ui->textEditSend->setFocus();
		ui->obocheckBox->setEnabled(true);

		setActionsEnabled(true);
	}
	else
	{
		QMessageBox::critical(this, tr("Error"), tr("can't open ") + portName + tr("\ndevice is occupied or isn't exist!"), QMessageBox::Ok);
		return;
	}

	saveComDefaultConfig();
	ui->statusBar->showMessage(tr("Open Com Success"));
}


//�رմ���
void MainWindow::on_actionClose_triggered()
{

	myCom->close();
	delete myCom;
	myCom = NULL;

	ui->sendmsgBtn->setEnabled(false);

	setComboBoxEnabled(true);

	ui->actionOpen->setEnabled(true);
	ui->textEditSend->setEnabled(false);
	ui->obocheckBox->setEnabled(false);

	setActionsEnabled(false);

	ui->actionWriteToFile->setChecked(false);
	ui->statusBar->showMessage(tr("Com is closed"));
}

//����
void MainWindow::on_actionAbout_triggered()
{
	aboutdlg.show();
	// ���������м���ʾ
	int x =this->x() + (this->width() - aboutdlg.width()) / 2;
	int y =this->y() + (this->height() - aboutdlg.height()) / 2;
	aboutdlg.move(x, y);
	ui->statusBar->showMessage(tr("About QCom"));
}

//��ȡ����
void MainWindow::readMyCom()
{
	QByteArray temp = myCom->readAll();
	QString buf;

	if(!temp.isEmpty())
	{
		ui->textBrowserRecv->setTextColor(Qt::black);
		if (ui->ccradioButton->isChecked()) //ʮ����
		{
			buf = temp;
		}
		else if (ui->chradioButton->isChecked()) //ʮ������
		{
			QString str;
			for (int i = 0; i < temp.count(); i++)
			{
				QString s;
				s.sprintf("0x%02x, ", (unsigned char)temp.at(i));
				buf += s;
			}
		}

		if (!write2fileName.isEmpty())
		{
			QFile file(write2fileName);
			//�����ʧ���������ʾ���˳�����
			if (!file.open(QFile::Append | QIODevice::Text)) //Append:��׷�ӷ�ʽд��; WriteOnly:���Ƿ�ʽ
			{
				QMessageBox::warning(this, tr("Write File"), tr("open file %1 failed, can't write\n%2").arg(write2fileName).arg(file.errorString()), QMessageBox::Ok);
				return;
			}
			QTextStream out(&file);
			out<<buf;
			file.close();
		}

		ui->textBrowserRecv->setText(ui->textBrowserRecv->document()->toPlainText() + buf);
		QTextCursor cursor = ui->textBrowserRecv->textCursor();
		cursor.movePosition(QTextCursor::End);
		ui->textBrowserRecv->setTextCursor(cursor);

		ui->recvBytesLcdNumber->display(ui->recvBytesLcdNumber->value() + temp.size());
		ui->statusBar->showMessage(tr("read %1 bytes data success").arg(temp.size()));
	}
}

//��������
void MainWindow::sendMsg()
{
	QByteArray buf;
	if (ui->chradioButton2->isChecked()) //ʮ������
	{
		QString str;
		bool ok;
		char data;
		QStringList list;
		str = ui->textEditSend->toPlainText();
		list = str.split(" "); //�Կո���ָ�
		for (int i = 0; i < list.count(); i++)
		{
			if (list.at(i) == " ")
				continue;
			if (list.at(i).isEmpty())
				continue;
			data = (char)list.at(i).toInt(&ok, 16);
			if (!ok)
			{
				QMessageBox::information(this, tr("Hint"), tr("data format error��"), QMessageBox::Ok);
				if(obotimer != NULL)
					obotimer->stop();
				ui->sendmsgBtn->setText(tr("send"));
				ui->sendmsgBtn->setIcon(QIcon(":new/prefix1/src/send.png"));
				return;
			}
			buf.append(data);
		}
	}
	else //ʮ����
	{
#if QT_VERSION < 0x050000
		buf = ui->textEditSend->toPlainText().toAscii();
#else
		buf = ui->textEditSend->text().toLocal8Bit();
#endif
	}
	//��������
	myCom->write(buf);
	ui->sendBytesLcdNumber->display(ui->sendBytesLcdNumber->value() + buf.size());
	ui->statusBar->showMessage(tr("send data success"));
	//�������
	ui->textBrowserRecv->setTextColor(Qt::lightGray);
}

//�������ݰ�ť
void MainWindow::on_sendmsgBtn_clicked()
{
	//�����ǰ���������������ݣ���ͣ����
	if (ui->sendmsgBtn->text() == tr("pause"))
	{
		obotimer->stop();
		ui->sendmsgBtn->setText(tr("send"));
		ui->sendmsgBtn->setIcon(QIcon(":new/prefix1/src/send.png"));
		return;
	}
	//�����������Ϊ�գ�������ʾ������
	if (ui->textEditSend->toPlainText().isEmpty())
	{
		QMessageBox::information(this, tr("Hint"), tr("no data need to send"), QMessageBox::Ok);
		return;
	}

	//���������������
	if (!ui->obocheckBox->isChecked())
	{
		ui->textEditSend->setFocus();
		//��������
		sendMsg();
	}
	else
	{ //��������
		obotimer->start(obotimerdly);
		ui->sendmsgBtn->setText(tr("pause"));
		ui->sendmsgBtn->setIcon(QIcon(":new/prefix1/src/pause.png"));
	}
}
//��ս��ռ�¼
void MainWindow::on_clearRecvBtn_clicked()
{
	ui->textBrowserRecv->clear();
	ui->statusBar->showMessage(tr("receive record is cleared"));
}

//��շ��ͼ�¼
void MainWindow::on_clearSendBtn_clicked()
{
	ui->textEditSend->clear();
	ui->statusBar->showMessage(tr("send record is cleared"));
}

//���ռ���������
void MainWindow::on_btnResetRecvLcd_clicked()
{
	if (ui->recvBytesLcdNumber->value()==0)
	{
		QMessageBox::information(this, tr("Hint"), tr("already cleared"), QMessageBox::Ok);
	}
	else
	{
		ui->recvBytesLcdNumber->display(0);
		ui->statusBar->showMessage(tr("receive LCD already cleared"));
	}
}

//���ͼ���������
void MainWindow::on_btnResetSendLcd_clicked()
{
	if (ui->sendBytesLcdNumber->value()==0)
	{
		QMessageBox::information(this, tr("Hint"), tr("already cleared"), QMessageBox::Ok);
	}
	else
	{
		ui->sendBytesLcdNumber->display(0);
		ui->statusBar->showMessage(tr("send LCD already cleared"));
	}
}

//���������+���ռ���������
void MainWindow::on_actionClearRecvBytes_triggered()
{
	on_clearRecvBtn_clicked();
	on_btnResetRecvLcd_clicked();
}

//���������+���ͼ���������
void MainWindow::on_actionClearSendBytes_triggered()
{
	on_clearSendBtn_clicked();
	on_btnResetSendLcd_clicked();
}

//������������checkBox
void MainWindow::on_obocheckBox_clicked()
{
	if (ui->obocheckBox->isChecked())
	{
		ui->delayspinBox->setEnabled(true);
		//����Ƿ������ݣ�������������ʱ��
		ui->statusBar->showMessage(tr("start send continuously"));
	}
	else
	{
		ui->delayspinBox->setEnabled(false);
		//����ʱ���Ѿ�������ر���
		ui->statusBar->showMessage(tr("stop send continuously"));
	}
}

//���淢�Ϳ��е�����
void MainWindow::on_actionSave_triggered()
{
	if (ui->textEditSend->toPlainText().isEmpty())
	{
		QMessageBox::information(this, tr("Hint"), tr("no data need save! please input data in the sending area"), QMessageBox::Ok);
		return;
	}

	QString filename = QFileDialog::getSaveFileName(this, tr("Save As"), tr("noname.txt"));
	QFile file(filename);
	//����û�ȡ���˱�����ֱ���˳�����
	if (file.fileName().isEmpty())
	{
		return;
	}
	//�����ʧ���������ʾ���˳�����
	if (!file.open(QFile::WriteOnly | QIODevice::Text))
	{
		QMessageBox::warning(this, tr("Save File"), tr("open file %1 failed, can't save\n%2").arg(filename).arg(file.errorString()), QMessageBox::Ok);
		return;
	}
	//д���ݵ��ļ�
	QTextStream out(&file);
	out<<ui->textEditSend->toPlainText();
	file.close();
	//�޸Ĵ��ڱ���Ϊ�����ļ�·��
	setWindowTitle("saved: " + QFileInfo(filename).canonicalFilePath());
}

//�˳�����
void MainWindow::on_actionExit_triggered()
{
	this->close();
}

//������������ʱ����
void MainWindow::on_delayspinBox_valueChanged(int )
{
	obotimerdly = ui->delayspinBox->value();
}

//�����ⲿ�ļ�
void MainWindow::on_actionLoadfile_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Read File"), 0, tr("save as (*.txt *.log)"));  //��Ӹ�����ļ�����
	QFile file(filename);

	//���ȡ�������˳�����
	if (file.fileName().isEmpty())
	{
		return;
	}

	//�����ʧ������ʾ���˳�����
	if (!file.open(QFile::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(this, tr("Open Failed"),
			tr("Sorry! QCom can't open this file, maybe no right. you can try chmod to modify right."),
			QMessageBox::Ok);
		return;
	}

	//�ļ���С��������
	if (file.size() > MAX_FILE_SIZE)
	{
		QMessageBox::critical(this, tr("Load Failed"), tr("file size is %1 bytes, the limit is 10000 bytes").arg(file.size()), QMessageBox::Ok);
		return;
	}
	//�ļ�̫��ʱ��ʾ�Ƿ������
	if (file.size() > TIP_FILE_SIZE)
	{
		if (QMessageBox::question(this, tr("Hint"), tr("the file is too large, it will use more time, open continue?"),
			QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
		{
				return;
		}
	}

	//��ȡ���ݲ����뵽�������ݱ༭��
	QTextStream text(&file);
	QString line;
	while (!text.atEnd())
	{
		line = text.readLine();
		ui->textEditSend->setText(ui->textEditSend->toPlainText() + line + "\n");
	}
	file.close();
	ui->statusBar->showMessage(tr("read data of the file successfully!"));
}

//��մ����е�I/O����
void MainWindow::on_actionCleanPort_triggered()
{
	myCom->flush();
}

//д���ļ��˵�
void MainWindow::on_actionWriteToFile_triggered()
{
	if (ui->actionWriteToFile->isChecked())
	{
		QString filename = QFileDialog::getSaveFileName(this, tr("Write File"), 0, tr("save as (*.*)"));  //��Ӹ�����ļ�����
		if (filename.isEmpty())
		{
			ui->actionWriteToFile->setChecked(false);
		}
		else
		{
			write2fileName = filename;
			ui->actionWriteToFile->setToolTip(tr("stop write file"));
		}
	}
	else
	{
		write2fileName.clear();
		ui->actionWriteToFile->setToolTip(tr("write the reading data to file"));
	}
}

//���洮��Ĭ�ϲ���
void MainWindow::saveComDefaultConfig()
{
	if (m_comset)
	{
		m_comset->setValue("ComSettings/ComName", ui->portNameComboBox->currentIndex());
		m_comset->setValue("ComSettings/BaudRate", ui->baudRateComboBox->currentIndex());
		m_comset->setValue("ComSettings/DataBit", ui->dataBitsComboBox->currentIndex());
		m_comset->setValue("ComSettings/Parity", ui->parityComboBox->currentIndex());
		m_comset->setValue("ComSettings/StopBit", ui->stopBitsComboBox->currentIndex());
	}	
}