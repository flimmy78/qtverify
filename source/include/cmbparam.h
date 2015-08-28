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

#define NOT_USE  0  //�¶ȵ�û��ʹ�ñ�־

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
	void saveSuccessfully();

private:
	Ui::CmbParamDlgClass ui;
	
	QSettings *m_param_config;

	bool cBoxData_inited;//���, ������������Ѿ������ݿ��ж�ȡ������

	void initCmbBox();//��ʼ��comboBox
	void initStand();//��ʼ���ȱ���
	void initModel();//��ʼ���ȱ��ͺ�
	void initCollCode();//��ʼ���ȱ�ɼ�����
	void initManufac();//��ʼ���ȱ����쳧��
	void initInst();//��ʼ���ͼ쵥λ
	void initChker();//��ʼ���춨Ա
	void readConfig();//��ȡ�ϴ����ò���
	void saveConfig();//���汾�����ò���
};

#endif //CMBPARAM_H