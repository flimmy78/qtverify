#ifndef TVERPARAMPARAMDLG_H
#define TVERPARAMPARAMDLG_H

#ifdef TVERPARAMPARAMDLG_DLL
#  ifdef WIN32
#  define TVERPARAMPARAMDLG_EXPORT __declspec(dllexport)
#  else
#  define TVERPARAMPARAMDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define TVERPARAMPARAMDLG_EXPORT __declspec(dllimport)
#  else
#  define TVERPARAMPARAMDLG_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QSettings>
#include "ui_tverparam_param.h"
#include "qtexdb.h"
#include "basedef.h"

class TVERPARAMPARAMDLG_EXPORT tverparamparamDlg : public QWidget
{
	Q_OBJECT

public:
	tverparamparamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~tverparamparamDlg();
signals:
	void configureOk(void);//���ò������
	public slots:
		void closeEvent(QCloseEvent * event);

		void on_btn_exit_clicked();
		void on_btn_save_clicked();
private:
	Ui::PlaParamParamDlgClass ui;

	bool cBoxData_inited;//���, ������������Ѿ������ݿ��ж�ȡ������

	int m_meterStdNum;	//��������
	MeterStandard_PTR m_meterStdPtr;//��������

	int m_meterTypeNum;	//����������
	MeterType_PTR m_meterTypePtr;//��������������

	int m_manuFacNum;	//���쵥λ
	Manufacture_PTR m_manuFacPtr;//���쵥λ����

	QSettings* m_config;//��ȡ�����������ļ�
private:
	void initCmbBox();//��ʼ��comboBox
	void readConfig();//��ȡ�ϴ����ò���
	void saveConfig();//���汾�����ò���
};

#endif//TVERPARAMPARAMDLG_H