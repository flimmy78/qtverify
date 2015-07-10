#ifndef SETCOMFRM_H
#define SETCOMFRM_H

#include <QtGui/QWidget>
#include <QtXml/QtXml>
#include <QSettings>
#include <QtSql/QSqlTableModel>

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
	QButtonGroup *btnGroupBalanceType; //天平类型
	ReadComConfig *m_config;//读取配置信息
	QSqlTableModel *m_model;

	/**************读取配置文件*****************/
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

	/**************写入配置文件*****************/
	void WriteValveConfig();//写入阀门配置
	void WriteBalanceConfig();//写入天平配置
	void WriteBalanceTypeConfig();//写入天平类型配置
	void WriteTempConfig();//写入温度采集配置
	void WriteStdTempConfig();//写入标准温度计配置
	void WriteInstStdConfig();//写入采集瞬时流量模块配置
	void WriteAccumStdConfig();//写入采集累积流量模块配置
	void WriteMetersConfig();//写入被检表配置
	void WriteMeterConfigByNum(int MeterNum);//按表号写入被检表配置
	void WriteConfigById(QGroupBox*);//写入配置
	/********************************************/

private slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();
};

#endif // SETCOMFRM_H