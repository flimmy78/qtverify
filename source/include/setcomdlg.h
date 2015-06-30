#ifndef SETCOMFRM_H
#define SETCOMFRM_H

#include <QtGui/QWidget>
#include <QtXml/QtXml>
#include <QSettings>

#include "ui_setcomDlg.h"
#include "systemsetdlg_global.h"

class ReadComConfig;

class SYSTEMSETDLG_EXPORT SetComDlg : public QWidget
{
	Q_OBJECT

public slots:
	void showEvent(QShowEvent *);
	void closeEvent(QCloseEvent *);

public:
	SetComDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SetComDlg();

private:
	Ui::SetComDlgClass gui;
	QSettings *m_com_settings;
	QButtonGroup *btnGroupBalanceType; //��ƽ����
	ReadComConfig *m_config;//��ȡ������Ϣ

	/**************��ȡ�����ļ�*****************/
	void InstallConfigs();
	void InstallValeConfig();
	void InstallBalanceConfig();
	void InstallBalanceTypeConfig();
	void InstallTempConfig();
	void InstallStdtmpConfig();
	void InstallInstStdConfig();
	void InstallAccumStdConfig();
	void InstallMetersConfig();
	void InstallMeterConfigByNum(QGroupBox *gbox);
	/********************************************/

	/**************д�������ļ�*****************/
	void WriteValveConfig();//д�뷧������
	void WriteBalanceConfig();//д����ƽ����
	void WriteBalanceTypeConfig();//д����ƽ��������
	void WriteTempConfig();//д���¶Ȳɼ�����
	void WriteStdTempConfig();//д���׼�¶ȼ�����
	void WriteInstStdConfig();//д��ɼ�˲ʱ����ģ������
	void WriteAccumStdConfig();//д��ɼ��ۻ�����ģ������
	void WriteMetersConfig();//д�뱻�������
	void WriteMeterConfigByNum(int MeterNum);//�����д�뱻�������
	void WriteConfigById(QGroupBox*);//д������
	/********************************************/

private slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();
};

#endif // SETCOMFRM_H