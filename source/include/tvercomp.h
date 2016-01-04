#ifndef TVERCOMP_H
#define TVERCOMP_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QTimer>
#include "protocol.h"
#include "readcomconfig.h"
#include "comobject.h"
#include "ui_tvercomp.h"
#include "tvercompparamdlg.h"

#define TMP_DIFF_NUMBER			3//�²�����
#define VERIFY_NUMBER			12//���첬�������

class TVERCOMP_EXPORT tvercompDlg : public QWidget
{
	Q_OBJECT

public:
	tvercompDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~tvercompDlg();

signals:
	void commandSendComplete(void);//��ȡ�¶������ѷ������
	void signalClosed();
public slots:
	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent * event);
	void setTblColWidth(QTableWidget*);
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

	void on_tbl_chkerror_1_cellChanged(int, int);
	void on_tbl_chkerror_2_cellChanged(int, int);
	void on_tbl_chkerror_3_cellChanged(int, int);

	void on_btn_param_clicked();
	void on_btn_save_clicked();//���������ݿ�
	void on_btn_exit_clicked();

	void setTblStd1(const QString& tempStr);
	void setTblStd2(const QString& tempStr);
	void setTblStd3(const QString& tempStr);
	void sendCommands();
	void clearComObjs();
	void insertData();
private:
	Ui::PlaCompDlgClass ui;
	tvercompparamDlg *m_PlaCompParamDlg;

	QTimer* m_sendTimer;//��ʱ��������
	stdTempCommand m_readCommand;

	QSettings* m_tvercomp_config;//�¶ȼƱȽϷ���������
	QSettings* m_std_pla_config;//��׼�¶ȼƲ���
	QSettings* m_chk_pla_config;//�����¶ȼƲ���
	ReadComConfig* m_readComConfig;//��������
	StdTempComObject* m_tempObj;//��׼�¶ȼƴ��ڶ���

	T_Platinum_Verify_Record_PTR m_PlaVerifyRecPtr;//�������¼
	QString m_timeStamp; //ʱ���
	int m_rec_num;//��Ҫ����ļ�¼����

	float m_min_delta_tmp;//��С�²�Ħ�min
private:
	void readConfig();//��ȡ��׼�¶ȼơ����첬���衢��������
	void readChkResult();//��ȡ���첬��������
};

#endif//TCHKCOMP_H