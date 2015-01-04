#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QMessageBox>
#include <QFile>
#include <QInputDialog>
#include <QFileDialog>
#include <QTextStream>

#include "qextserialport.h"
#include "aboutdialog.h"


//��ʱ��TIME_OUT�Ǵ��ڶ�д����ʱ
#define TIME_OUT 10

//�������Ͷ�ʱ����ʱ���,200ms
#define OBO_TIMER_INTERVAL 200

//�����ļ�ʱ������ļ���С����TIP_FILE_SIZE�ֽ�����ʾ�ļ������Ƿ������
#define TIP_FILE_SIZE 5000
//�����ļ���󳤶�������MAX_FILE_SIZE�ֽ���
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
	QextSerialPort *myCom;
	QTimer *obotimer;
	unsigned int timerdly;
	unsigned int obotimerdly;
	QString write2fileName;    //д��ȡ�Ĵ������ݵ����ļ�

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
		//end by

};

#endif // MAINWINDOW_H
