#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QMessageBox>
#include <QFile>
#include <QInputDialog>
#include <QFileDialog>
#include <QTextStream>
#include "QtSerialPort/QSerialPort"
#include "QtSerialPort/QSerialPortInfo"

#include "aboutdialog.h"


//延时，TIME_OUT是串口读写的延时
#define TIME_OUT 10

//连续发送定时器计时间隔,200ms
#define OBO_TIMER_INTERVAL 200

//载入文件时，如果文件大小超过TIP_FILE_SIZE字节则提示文件过大是否继续打开
#define TIP_FILE_SIZE 5000
//载入文件最大长度限制在MAX_FILE_SIZE字节内
#define MAX_FILE_SIZE 10000

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	void startInit();

protected:
	void changeEvent(QEvent *e);
	void setActionsEnabled(bool status);
	void setComboBoxEnabled(bool status);

private:
	Ui::MainWindow *ui;
	AboutDialog aboutdlg;
	QSerialPort *myCom;
	QTimer *obotimer;
	unsigned int timerdly;
	unsigned int obotimerdly;
	QString write2fileName;    //写读取的串口数据到该文件

	QString m_filename;
	QSettings *m_comset;

private slots:
	void on_actionWriteToFile_triggered();
	void on_actionCleanPort_triggered();
	void on_actionLoadfile_triggered();
	void on_delayspinBox_valueChanged(int );
	void on_actionExit_triggered();
	void on_actionSave_triggered();
	void on_obocheckBox_clicked();
	void on_actionClearRecvBytes_triggered();
	void on_actionClearSendBytes_triggered();
	void on_actionAbout_triggered();
	void on_actionClose_triggered();
	void on_actionOpen_triggered();
	void on_clearRecvBtn_clicked();
	void on_clearSendBtn_clicked();
	void on_btnResetRecvLcd_clicked();
	void on_btnResetSendLcd_clicked();
	void on_sendmsgBtn_clicked();
	void readMyCom();
	void sendMsg();
	void saveComDefaultConfig();
	void on_btn1BytesCS_clicked();
	void on_btn2BytesCS_clicked();
	void on_btnCRC_clicked();
	//end by

};

#endif // MAINWINDOW_H
