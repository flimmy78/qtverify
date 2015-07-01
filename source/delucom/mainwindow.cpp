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
	ui->portNameComboBox->addItem("COM21");
	ui->portNameComboBox->addItem("COM22");
	ui->portNameComboBox->addItem("COM23");
	ui->portNameComboBox->addItem("COM24");
	ui->portNameComboBox->addItem("COM25");
	ui->portNameComboBox->addItem("COM26");
	ui->portNameComboBox->addItem("COM27");
	ui->portNameComboBox->addItem("COM28");
	ui->portNameComboBox->addItem("COM29");
	ui->portNameComboBox->addItem("COM30");
#endif

	ui->statusBar->showMessage(QObject::tr("Welcome Using QCom!"));
	ui->btnRecv->hide();

	//加载上次保存的串口参数
	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
	m_filename = adehome + "\\ini\\comdebugger.ini";
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

	//初始化连续发送计时器计时间隔
	obotimerdly = OBO_TIMER_INTERVAL;

	//设置连续发送计时器
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

//打开串口
void MainWindow::on_actionOpen_triggered()
{
	QString portName = ui->portNameComboBox->currentText();   //获取串口名
#ifdef Q_OS_LINUX
	myCom = new QextSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	myCom = new QextSerialPort(portName);
#endif
	connect(myCom, SIGNAL(readyRead()), this, SLOT(readMyCom()));

	//设置波特率
	myCom->setBaudRate((BaudRateType)ui->baudRateComboBox->currentText().toInt());

	//设置数据位
	myCom->setDataBits((DataBitsType)ui->dataBitsComboBox->currentText().toInt());

	//设置校验
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

	//设置停止位
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

	//设置数据流控制
	myCom->setFlowControl(FLOW_OFF);
	//设置延时
	myCom->setTimeout(TIME_OUT);

	if (myCom->open(QIODevice::ReadWrite))
	{
		QMessageBox::information(this, tr("OK"), tr("open ") + portName + tr(" success!"), QMessageBox::Ok);
		//界面控制
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


//关闭串口
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

//关于
void MainWindow::on_actionAbout_triggered()
{
	aboutdlg.show();
	// 在主窗口中间显示
	int x =this->x() + (this->width() - aboutdlg.width()) / 2;
	int y =this->y() + (this->height() - aboutdlg.height()) / 2;
	aboutdlg.move(x, y);
	ui->statusBar->showMessage(tr("About QCom"));
}

//读取数据
void MainWindow::readMyCom()
{
	QByteArray temp = myCom->readAll();
	QString buf;

	if(!temp.isEmpty())
	{
		ui->textBrowserRecv->setTextColor(Qt::black);
		if (ui->ccradioButton->isChecked()) //十进制
		{
			buf = temp;
		}
		else if (ui->chradioButton->isChecked()) //十六进制
		{
			QString str;
			int length = temp.count();
			for (int i = 0; i < temp.count(); i++)
			{
				QString s;
				s.sprintf("0x%02X ", (unsigned char)temp.at(i));
				buf += s;
			}
		}

		if (!write2fileName.isEmpty())
		{
			QFile file(write2fileName);
			//如果打开失败则给出提示并退出函数
			if (!file.open(QFile::Append | QIODevice::Text)) //Append:以追加方式写入; WriteOnly:覆盖方式
			{
				QMessageBox::warning(this, tr("Write File"), tr("open file %1 failed, can't write\n%2").arg(write2fileName).arg(file.errorString()), QMessageBox::Ok);
				return;
			}
			QTextStream out(&file);
			out<<buf;
			file.close();
		}

		ui->textBrowserRecv->setText(ui->textBrowserRecv->document()->toPlainText() + buf +"\n");
		QTextCursor cursor = ui->textBrowserRecv->textCursor();
		cursor.movePosition(QTextCursor::End);
		ui->textBrowserRecv->setTextCursor(cursor);

		ui->recvBytesLcdNumber->display(ui->recvBytesLcdNumber->value() + temp.size());
		ui->statusBar->showMessage(tr("read %1 bytes data success").arg(temp.size()));
	}
}

//发送数据
void MainWindow::sendMsg()
{
	QByteArray buf;
	if (ui->chradioButton2->isChecked()) //十六进制
	{
		QString str;
		bool ok;
		char data;
		QStringList list;
		str = ui->textEditSend->toPlainText();
		list = str.split(" "); //以空格符分割
		for (int i = 0; i < list.count(); i++)
		{
			if (list.at(i) == " ")
				continue;
			if (list.at(i).isEmpty())
				continue;
			data = (char)list.at(i).toInt(&ok, 16);
			if (!ok)
			{
				QMessageBox::information(this, tr("Hint"), tr("data format error！"), QMessageBox::Ok);
				if(obotimer != NULL)
					obotimer->stop();
				ui->sendmsgBtn->setText(tr("send"));
				ui->sendmsgBtn->setIcon(QIcon(":new/prefix1/src/send.png"));
				return;
			}
			buf.append(data);
		}
	}
	else //十进制
	{
#if QT_VERSION < 0x050000
		buf = ui->textEditSend->toPlainText().toAscii();
#else
		buf = ui->textEditSend->text().toLocal8Bit();
#endif
	}
	//发送数据
	myCom->write(buf);
	ui->sendBytesLcdNumber->display(ui->sendBytesLcdNumber->value() + buf.size());
	ui->statusBar->showMessage(tr("send data success"));
	//界面控制
	ui->textBrowserRecv->setTextColor(Qt::lightGray);
}

//发送数据按钮
void MainWindow::on_sendmsgBtn_clicked()
{
	//如果当前正在连续发送数据，暂停发送
	if (ui->sendmsgBtn->text() == tr("pause"))
	{
		obotimer->stop();
		ui->sendmsgBtn->setText(tr("send"));
		ui->sendmsgBtn->setIcon(QIcon(":new/prefix1/src/send.png"));
		return;
	}
	//如果发送数据为空，给出提示并返回
	if (ui->textEditSend->toPlainText().isEmpty())
	{
		QMessageBox::information(this, tr("Hint"), tr("no data need to send"), QMessageBox::Ok);
		return;
	}

	//如果不是连续发送
	if (!ui->obocheckBox->isChecked())
	{
		ui->textEditSend->setFocus();
		//发送数据
		sendMsg();
	}
	else
	{ //连续发送
		obotimer->start(obotimerdly);
		ui->sendmsgBtn->setText(tr("pause"));
		ui->sendmsgBtn->setIcon(QIcon(":new/prefix1/src/pause.png"));
	}
}
//清空接收记录
void MainWindow::on_clearRecvBtn_clicked()
{
	ui->textBrowserRecv->clear();
	ui->statusBar->showMessage(tr("receive record is cleared"));
	on_btnResetRecvLcd_clicked();
}

//清空发送记录
void MainWindow::on_clearSendBtn_clicked()
{
	ui->textEditSend->clear();
	ui->statusBar->showMessage(tr("send record is cleared"));
}

//接收计数器清零
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

//发送计数器清零
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

//接收区清空+接收计数器清零
void MainWindow::on_actionClearRecvBytes_triggered()
{
	on_clearRecvBtn_clicked();
	on_btnResetRecvLcd_clicked();
}

//发送区清空+发送计数器清零
void MainWindow::on_actionClearSendBytes_triggered()
{
	on_clearSendBtn_clicked();
	on_btnResetSendLcd_clicked();
}

//单击连续发送checkBox
void MainWindow::on_obocheckBox_clicked()
{
	if (ui->obocheckBox->isChecked())
	{
		ui->delayspinBox->setEnabled(true);
		//检查是否有数据，如有则启动定时器
		ui->statusBar->showMessage(tr("start send continuously"));
	}
	else
	{
		ui->delayspinBox->setEnabled(false);
		//若定时器已经启动则关闭它
		ui->statusBar->showMessage(tr("stop send continuously"));
	}
}

//保存发送框中的内容
void MainWindow::on_actionSave_triggered()
{
	if (ui->textEditSend->toPlainText().isEmpty())
	{
		QMessageBox::information(this, tr("Hint"), tr("no data need save! please input data in the sending area"), QMessageBox::Ok);
		return;
	}

	QString filename = QFileDialog::getSaveFileName(this, tr("Save As"), tr("noname.txt"));
	QFile file(filename);
	//如果用户取消了保存则直接退出函数
	if (file.fileName().isEmpty())
	{
		return;
	}
	//如果打开失败则给出提示并退出函数
	if (!file.open(QFile::WriteOnly | QIODevice::Text))
	{
		QMessageBox::warning(this, tr("Save File"), tr("open file %1 failed, can't save\n%2").arg(filename).arg(file.errorString()), QMessageBox::Ok);
		return;
	}
	//写数据到文件
	QTextStream out(&file);
	out<<ui->textEditSend->toPlainText();
	file.close();
	//修改窗口标题为保存文件路径
	setWindowTitle("saved: " + QFileInfo(filename).canonicalFilePath());
}

//退出程序
void MainWindow::on_actionExit_triggered()
{
	this->close();
}

//调整连续发送时间间隔
void MainWindow::on_delayspinBox_valueChanged(int )
{
	obotimerdly = ui->delayspinBox->value();
}

//载入外部文件
void MainWindow::on_actionLoadfile_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Read File"), 0, tr("save as (*.txt *.log)"));  //添加更多的文件类型
	QFile file(filename);

	//如果取消打开则退出函数
	if (file.fileName().isEmpty())
	{
		return;
	}

	//如果打开失败则提示并退出函数
	if (!file.open(QFile::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(this, tr("Open Failed"),
			tr("Sorry! QCom can't open this file, maybe no right. you can try chmod to modify right."),
			QMessageBox::Ok);
		return;
	}

	//文件大小超过限制
	if (file.size() > MAX_FILE_SIZE)
	{
		QMessageBox::critical(this, tr("Load Failed"), tr("file size is %1 bytes, the limit is 10000 bytes").arg(file.size()), QMessageBox::Ok);
		return;
	}
	//文件太大时提示是否继续打开
	if (file.size() > TIP_FILE_SIZE)
	{
		if (QMessageBox::question(this, tr("Hint"), tr("the file is too large, it will use more time, open continue?"),
			QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
		{
				return;
		}
	}

	//读取数据并加入到发送数据编辑框
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

//清空串口中的I/O数据
void MainWindow::on_actionCleanPort_triggered()
{
	myCom->flush();
}

//写入文件菜单
void MainWindow::on_actionWriteToFile_triggered()
{
	if (ui->actionWriteToFile->isChecked())
	{
		QString filename = QFileDialog::getSaveFileName(this, tr("Write File"), 0, tr("save as (*.*)"));  //添加更多的文件类型
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

//保存串口默认参数
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