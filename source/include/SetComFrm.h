#ifndef SETCOMFRM_H
#define SETCOMFRM_H

#include <QtGui/QWidget>
#include <QtXml/QtXml>

#include "ui_SetComFrm.h"
#include "comsetdlg_global.h"

class COMSETDLG_EXPORT SetComFrm : public QWidget
{
	Q_OBJECT

public slots:

public:
	SetComFrm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SetComFrm();
	/************读取配置文件****************/
	QString ReadConfigByName();
	QString ReadValeConfig();
	QString ReadBalanceConfig();
	QString ReadTempConfig();
	QString ReadStdTempConfig();
	QString ReadMeterConfigByNum();
	/***************************************************/

private:
	Ui::SetComFrm gui;
	QString ConfigFileName;
	QDomDocument m_doc;
	/***********读取窗体中的配置****************/
	QVector<QString> ReadSetByName();
	QVector<QString> ReadValeSet();//读取阀门控制配置
	QVector<QString> ReadBalanceSet();
	QVector<QString> ReadTempSet();
	QVector<QString> ReadStdTempSet();
	QVector<QString> ReadMeterSetByNum(QString MeterNum);
	QVector<QString> ReadGBoxSet(QGroupBox *gBox);
	/***************************************************/

	/**************写入配置文件*****************/
	bool WriteValveConfig(QVector<QString> ValveConfigs);
	bool WriteBalanceConfig(QVector<QString> BalanceConfigs);
	bool WriteTempConfig(QVector<QString> TempConfigs);
	bool WriteStdTempConfig(QVector<QString> StdTempConfigs);
	bool WriteMetersConfig();
	bool WriteMeterConfigByNum(QString MeterNum, QVector<QString> MeterConfigs);
	bool WriteConfigById(QString ConfigId, QVector<QString> Configs);
	bool OpenConfigFile();
	/***************************************************/

private slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();
};

#endif // SETCOMFRM_H