#ifndef SETCOMFRM_H
#define SETCOMFRM_H

#include <QtGui/QWidget>
#include <QtXml/QtXml>

#include "ui_setcomfrm.h"
#include "comsetdlg_global.h"

class ReadComConfig;

class COMSETDLG_EXPORT SetComFrm : public QWidget
{
	Q_OBJECT

public slots:

public:
	SetComFrm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SetComFrm();

private:
	Ui::SetComFrm gui;
	QString ConfigFileName;
	QDomDocument m_doc;
	ReadComConfig *m_config;//读取配置信息

	void InstallConfigs();
	void InstallValeConfig();
	void InstallBalanceConfig();
	void InstallTempConfig();
	void InstallStdtmpConfig();
	void InstallMetersConfig();
	void InstallMeterConfigByNum(QGroupBox *gbox);
	/***********读取窗体中的配置****************/
	QVector<QString> ReadValeSet();//读取阀门控制配置
	QVector<QString> ReadBalanceSet();
	QVector<QString> ReadTempSet();
	QVector<QString> ReadStdTempSet();
	QVector<QString> ReadMeterSetByNum(QString MeterNum);
	QVector<QString> ReadGBoxSet(QGroupBox *gBox);
	/***************************************************/

	/**************写入配置文件*****************/
	bool WriteValveConfig(QVector<QString> ValveConfigs);//写入阀门配置
	bool WriteBalanceConfig(QVector<QString> BalanceConfigs);//写入天平配置
	bool WriteTempConfig(QVector<QString> TempConfigs);//写入温度采集配置
	bool WriteStdTempConfig(QVector<QString> StdTempConfigs);//写入标准温度计配置
	bool WriteMetersConfig();//写入被检表配置
	bool WriteMeterConfigByNum(QString MeterNum, QVector<QString> MeterConfigs);//按表号写入被检表配置
	bool WriteConfigById(QString ConfigId, QVector<QString> Configs);//写入配置
	bool OpenConfigFile();//打开配置文件
	bool WriteConfigFile();//设置配置文件字符编码等
	/***************************************************/

private slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();
};

#endif // SETCOMFRM_H