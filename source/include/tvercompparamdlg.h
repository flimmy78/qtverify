#ifndef TVERCOMPPARAMDLG_H
#define TVERCOMPPARAMDLG_H

#ifdef TVERCOMPPARAMDLG_DLL
#  ifdef WIN32
#  define TVERCOMPPARAMDLG_EXPORT __declspec(dllexport)
#  else
#  define TVERCOMPPARAMDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define TVERCOMPPARAMDLG_EXPORT __declspec(dllimport)
#  else
#  define TVERCOMPPARAMDLG_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QSettings>
#include "ui_tvercomp_param.h"
#include "qtexdb.h"
#include "basedef.h"

class TVERCOMPPARAMDLG_EXPORT tvercompparamDlg : public QWidget
{
	Q_OBJECT

public:
	tvercompparamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~tvercompparamDlg();

	public slots:
		void closeEvent(QCloseEvent * event);
		void showEvent(QShowEvent * event);
		void on_btn_save_clicked();
		void on_btn_exit_clicked();
private:
	Ui::PlaCompParamDlgClass ui;

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

#endif//TVERCOMPPARAMDLG_H