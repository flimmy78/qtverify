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

	ReadComConfig *m_config;//读取配置信息

	/**************读取配置文件*****************/
	void InstallConfigs();
	void InstallValeConfig();
	void InstallBalanceConfig();
	void InstallTempConfig();
	void InstallStdtmpConfig();
	void InstallMetersConfig();
	void InstallMeterConfigByNum(QGroupBox *gbox);
	/********************************************/

	/**************写入配置文件*****************/
	void WriteValveConfig();//写入阀门配置
	void WriteBalanceConfig();//写入天平配置
	void WriteTempConfig();//写入温度采集配置
	void WriteStdTempConfig();//写入标准温度计配置
	void WriteMetersConfig();//写入被检表配置
	void WriteMeterConfigByNum(int MeterNum);//按表号写入被检表配置
	void WriteConfigById(QGroupBox*);//写入配置
	/********************************************/

private slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();
};

#endif // SETCOMFRM_H