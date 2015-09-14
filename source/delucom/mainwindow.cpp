#include <QDebug>
#include <intsafe.h>

#include "mainwindow.h"
#include "algorithm.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	startInit();
	myCom = NULL;

	foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) 
	{  
		qDebug() << "Name        : " << info.portName();
		qDebug() << "Description : " << info.description();
		qDebug() << "Manufacturer: " << info.manufacturer();
		ui->portNameComboBox->addItem(info.portName());
	}

	QLabel *permanent = new QLabel(this);
//	permanent->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	permanent->setText(tr("<u>Author:bmeyang QQ:157764165</u>"));
// 	permanent->setTextFormat(Qt::RichText);
// 	permanent->setOpenExternalLinks(true);
	ui->statusBar->addPermanentWidget(permanent);
	ui->statusBar->showMessage(QObject::tr("Welcome Using DeluCom!"));
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
	myCom = new QSerialPort();
#endif
	connect(myCom, SIGNAL(readyRead()), this, SLOT(readMyCom()));

	//设置串口名
	myCom->setPortName(portName);
	//设置波特率
	myCom->setBaudRate((QSerialPort::BaudRate)(ui->baudRateComboBox->currentText().toInt()));

	//设置数据位
	myCom->setDataBits((QSerialPort::DataBits)(ui->dataBitsComboBox->currentText().toInt()));

	//设置校验
	switch(ui->parityComboBox->currentIndex())
	{
	case 0:
		myCom->setParity(QSerialPort::NoParity);
		break;
	case 1:
		myCom->setParity(QSerialPort::OddParity);
		break;
	case 2:
		myCom->setParity(QSerialPort::EvenParity);
		break;
	default:
		myCom->setParity(QSerialPort::NoParity);
		qDebug("set to default : NoParity");
		break;
	}

	//设置停止位
	switch(ui->stopBitsComboBox->currentIndex())
	{
	case 0:
		myCom->setStopBits(QSerialPort::OneStop);
		break;
	case 1:
#ifdef Q_OS_WIN
		myCom->setStopBits(QSerialPort::OneAndHalfStop);
#endif
		break;
	case 2:
		myCom->setStopBits(QSerialPort::TwoStop);
		break;
	default:
		myCom->setStopBits(QSerialPort::OneStop);
		qDebug("set to default : OneStop");
		break;
	}

	//设置数据流控制
	myCom->setFlowControl(QSerialPort::NoFlowControl);

	if (myCom->open(QIODevice::ReadWrite))
	{
//		QMessageBox::information(this, tr("OK"), tr("open ") + portName + tr(" success!"), QMessageBox::Ok);
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
	ui->statusBar->showMessage(tr("About DeluCom"));
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
//	on_btnResetRecvLcd_clicked();
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
			tr("Sorry! DeluCom can't open this file, maybe no right. you can try chmod to modify right."),
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

void MainWindow::on_btn1BytesCS_clicked()
{
	ui->lineEdit1BytesCS->clear();
	UINT8 cs = 0x00;
	if (ui->chradioButton2->isChecked()) //十六进制
	{
		QString str;
		bool ok;
		UINT8 data;
		QStringList list;
		str = ui->textEditSend->toPlainText();
		list = str.split(" "); //以空格符分割
		for (int i = 0; i < list.count(); i++)
		{
			if (list.at(i) == " ")
				continue;
			if (list.at(i).isEmpty())
				continue;
			data = list.at(i).toUInt(&ok, 16);
			if (!ok)
			{
				QMessageBox::information(this, tr("Hint"), tr("data format error！"), QMessageBox::Ok);
				if(obotimer != NULL)
					obotimer->stop();
				ui->sendmsgBtn->setText(tr("send"));
				ui->sendmsgBtn->setIcon(QIcon(":new/prefix1/src/send.png"));
				return;
			}
			cs += data;
		}
	}
	else //十进制
	{

	}
	ui->lineEdit1BytesCS->setText("0x" + QString::number(cs, 16).rightJustified(2, '0').toUpper());
}

void MainWindow::on_btn2BytesCS_clicked()
{
	ui->lineEdit2BytesCS->clear();
	UINT16 cs = 0x0000;
	if (ui->chradioButton2->isChecked()) //十六进制
	{
		QString str;
		bool ok;
		UINT8 data;
		QStringList list;
		str = ui->textEditSend->toPlainText();
		list = str.split(" "); //以空格符分割
		for (int i = 0; i < list.count(); i++)
		{
			if (list.at(i) == " ")
				continue;
			if (list.at(i).isEmpty())
				continue;
			data = list.at(i).toUInt(&ok, 16);
			if (!ok)
			{
				QMessageBox::information(this, tr("Hint"), tr("data format error！"), QMessageBox::Ok);
				if(obotimer != NULL)
					obotimer->stop();
				ui->sendmsgBtn->setText(tr("send"));
				ui->sendmsgBtn->setIcon(QIcon(":new/prefix1/src/send.png"));
				return;
			}
			cs += data;
		}
	}
	else //十进制
	{

	}
	ui->lineEdit2BytesCS->setText("0x" + QString::number(cs,16).rightJustified(4, '0').toUpper());
}

void MainWindow::on_btnCRC_clicked()
{
	ui->lineEditCRCResult->clear();
	QString input = ui->lineEditCRCInput->text();
	QByteArray buf;
	QStringList list;
	UINT16 calc_crc;
	QString s, output;
	if (!input.isEmpty())
	{
		bool ok;
		char data;
		list = input.split(" "); //以空格符分割
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
				return;
			}
			buf.append(data);
		}
		calc_crc = calcModRtuCRC((uchar *)buf.data(), buf.length());
		output.append(s.sprintf("%02X", (uchar)calc_crc));
		output.append(" ");
		output.append(s.sprintf("%02X", (uchar)(calc_crc>>BYTE_LENGTH)));
		ui->lineEditCRCResult->setText(output);
	}
}