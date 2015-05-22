#ifndef CMBPARAM_H
#define CMBPARAM_H

#ifdef CMBVERIFY_DLL
#  ifdef WIN32
#  define CMBVERIFY_EXPORT __declspec(dllexport)
#  else
#  define CMBVERIFY_EXPORT
#  endif
#else
#  ifdef WIN32
#  define CMBVERIFY_EXPORT __declspec(dllimport)
#  else
#  define CMBVERIFY_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>
#include <QtCore/QSettings>
#include "ui_cmbparam.h"

#define NOT_USE	0//温度点没有使用标志
#define VERIFY_POINTS 3//温差点数量

class CMBVERIFY_EXPORT CmbParamDlg : public QWidget
{
	Q_OBJECT

public:
	CmbParamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CmbParamDlg();


public slots:
	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent * event);

	void on_btn_save_clicked();
	void on_btn_exit_clicked();


private slots:

signals:
	void saveSuccessfully(void);
private:
	Ui::CmbParamDlgClass ui;
	
	QSettings *m_param_config;

	bool cBoxData_inited;//标记, 界面的下拉条已经从数据库中读取了数据

	void initCmbBox();//初始化comboBox
	void initStand();//初始化热表规格
	void initModel();//初始化热表型号
	void initCollCode();//初始化热表采集代码
	void initManufac();//初始化热表制造厂商
	void initInst();//初始化送检单位
	void initChker();//初始化检定员
	void readConfig();//读取上次设置参数
	void saveConfig();//保存本次设置参数
};

#endif //CMBPARAM_H