#ifndef TVERCOMP_H
#define TVERCOMP_H

#ifdef TVERCOMP_DLL
#  ifdef WIN32
#  define TVERCOMP_EXPORT __declspec(dllexport)
#  else
#  define TVERCOMP_EXPORT
#  endif
#else
#  ifdef WIN32
#  define TVERCOMP_EXPORT __declspec(dllimport)
#  else
#  define TVERCOMP_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QSettings>
#include <QTimer>
#include "protocol.h"
#include "readcomconfig.h"
#include "comobject.h"
#include "ui_tvercomp.h"
#include "tvercompparamdlg.h"

#define READ_STI1062A_TIMEOUT	200//��ʱ�����
#define VERIFY_NUMBER			12//���첬�������

class TVERCOMP_EXPORT tvercompDlg : public QWidget
{
	Q_OBJECT

public:
	tvercompDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~tvercompDlg();

public:
	float readStdTmp();//
signals:
	void commandSendComplete(void);//��ȡ�¶������ѷ������
	public slots:
		void closeEvent(QCloseEvent * event);

		/******�ɼ���׼�¶ȼ���ֵ*********/
		void on_btn_read_1_clicked();
		void on_btn_read_2_clicked();
		void on_btn_read_3_clicked();

		/******��ձ�׼�¶ȼ���ֵ*********/
		void on_btn_clear_1_clicked();
		void on_btn_clear_2_clicked();
		void on_btn_clear_3_clicked();

		/******��׼�¶ȼ���ֵ*********/
		void on_tbl_std_1_cellChanged(int, int);
		void on_tbl_std_2_cellChanged(int, int);
		void on_tbl_std_3_cellChanged(int, int);

		/******���첬������ֵ*********/
		void on_tbl_in_1_cellChanged(int, int);
		void on_tbl_in_2_cellChanged(int, int);
		void on_tbl_in_3_cellChanged(int, int);

		void on_btn_param_clicked();
		void on_btn_excel_clicked();//������Excel
		void on_btn_save_clicked();//���������ݿ�
		void on_btn_exit_clicked();

		void setTblStd1(const QString& tempStr);
		void sendCommands();
		void clearComObjs();
		void insertData();
private:
	Ui::PlaCompDlgClass ui;
	tvercompparamDlg *m_PlaCompParamDlg;

	QTimer* m_sendTimer;//��ʱ��������
	sti1062Acommand m_readCommand;
	QSettings* m_tvercomp_config;//�¶ȼƱȽϷ���������
	QSettings* m_chk_pla_config;//�����¶ȼƲ���
	ReadComConfig* m_readComConfig;//��������
	Sti1062aComObject* m_tempObj;//��׼�¶ȼƴ��ڶ���

	T_Platinium_Verify_Record_PTR m_PlaVerifyRecPtr;//�������¼
private:
	void readConfig();//��ȡ��׼�¶ȼơ����첬���衢��������
};

#endif//TCHKCOMP_H