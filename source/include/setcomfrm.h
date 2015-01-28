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
	ReadComConfig *m_config;//��ȡ������Ϣ

	void InstallConfigs();
	void InstallValeConfig();
	void InstallBalanceConfig();
	void InstallTempConfig();
	void InstallStdtmpConfig();
	void InstallMetersConfig();
	void InstallMeterConfigByNum(QGroupBox *gbox);
	/***********��ȡ�����е�����****************/
	QVector<QString> ReadValeSet();//��ȡ���ſ�������
	QVector<QString> ReadBalanceSet();
	QVector<QString> ReadTempSet();
	QVector<QString> ReadStdTempSet();
	QVector<QString> ReadMeterSetByNum(QString MeterNum);
	QVector<QString> ReadGBoxSet(QGroupBox *gBox);
	/***************************************************/

	/**************д�������ļ�*****************/
	bool WriteValveConfig(QVector<QString> ValveConfigs);//д�뷧������
	bool WriteBalanceConfig(QVector<QString> BalanceConfigs);//д����ƽ����
	bool WriteTempConfig(QVector<QString> TempConfigs);//д���¶Ȳɼ�����
	bool WriteStdTempConfig(QVector<QString> StdTempConfigs);//д���׼�¶ȼ�����
	bool WriteMetersConfig();//д�뱻�������
	bool WriteMeterConfigByNum(QString MeterNum, QVector<QString> MeterConfigs);//�����д�뱻�������
	bool WriteConfigById(QString ConfigId, QVector<QString> Configs);//д������
	bool OpenConfigFile();//�������ļ�
	bool WriteConfigFile();//���������ļ��ַ������
	/***************************************************/

private slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();
};

#endif // SETCOMFRM_H