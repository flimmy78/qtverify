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
	/************��ȡ�����ļ�****************/
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
	/***********��ȡ�����е�����****************/
	QVector<QString> ReadSetByName();
	QVector<QString> ReadValeSet();//��ȡ���ſ�������
	QVector<QString> ReadBalanceSet();
	QVector<QString> ReadTempSet();
	QVector<QString> ReadStdTempSet();
	QVector<QString> ReadMeterSetByNum(QString MeterNum);
	QVector<QString> ReadGBoxSet(QGroupBox *gBox);
	/***************************************************/

	/**************д�������ļ�*****************/
	bool WriteValveConfig(QVector<QString> ValveConfigs);
	bool WriteBalanceConfig(QVector<QString> BalanceConfigs);
	bool WriteTempConfig(QVector<QString> TempConfigs);
	bool WriteStdTempConfig(QVector<QString> StdTempConfigs);
	bool WriteMeterConfigByNum();
	bool WriteConfigById(QString ConfigId, QVector<QString> Configs);
	bool OpenConfigFile();
	/***************************************************/

private slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();
};

#endif // SETCOMFRM_H