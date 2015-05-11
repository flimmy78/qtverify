#ifndef TVERPARAM_H
#define TVERPARAM_H

#ifdef TVERPARAM_DLL
#  ifdef WIN32
#  define TVERPARAM_EXPORT __declspec(dllexport)
#  else
#  define TVERPARAM_EXPORT
#  endif
#else
#  ifdef WIN32
#  define TVERPARAM_EXPORT __declspec(dllimport)
#  else
#  define TVERPARAM_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>
#include <QSettings>
#include <QTimer>
#include <QTreeWidgetItem>
#include "ui_tverparam.h"
#include "protocol.h"
#include "comobject.h"

#include "readcomconfig.h"
#include "tverparamparamdlg.h"

#define READ_STI1062A_TIMEOUT	200//��ʱ�����
#define TMP_DIFF_NUMBER			3//�¶ȵ����
#define VERIFY_NUMBER			12//���첬�������
#define VERIFY_TIMES			3//ÿ�Բ������ظ��춨����

class TVERPARAM_EXPORT tverparamDlg : public QWidget
{
	Q_OBJECT

public:
	tverparamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~tverparamDlg();

public:

signals:
	void commandSendComplete(void);//��ȡ�¶������ѷ������

	void firstTmpVerOk(void);//��һ�¶ȵ������
	void secondTmpVerOk(void);//�ڶ��¶ȵ������
	void thirdTmpVerOk(void);//�����¶ȵ������

	void allTmpVerOk(void);//���е��¶ȵ㶼������

	public slots:
		void closeEvent(QCloseEvent * event);
		void showEvent(QShowEvent * event);

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

		//void on_tbl_in_1_currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous);
		//void on_tbl_in_1_itemChanged( QTreeWidgetItem * item, int column);

		/******���첬�����¶�ֵ*******/
		void on_tbl_result_cellChanged(int, int);

		void on_btn_param_clicked();//���ò���
		void on_btn_save_clicked();//���������ݿ�
		void on_btn_exit_clicked();//�˳�

		void disableConfigBtn();
		void disableAllWdg();//���������¶ȵ���ز���
		void disable1stWdg();//���õ�һ�¶ȵ���ز���
		void disable2ndWdg();//���õڶ��¶ȵ���ز���
		void disable3rdWdg();//���õ����¶ȵ���ز���
		void enable1stWdg();//���õ�һ�¶ȵ���ز���
		void enable2ndWdg();//���õڶ��¶ȵ���ز���
		void enable3rdWdg();//���õ����¶ȵ���ز���

		void firstTmpVerOk_slot();
		void secondTmpVerOk_slot();
		void thirdTmpVerOk_slot();

		void setTblStd1(const QString& tempStr);
		void setTblStd2(const QString& tempStr);
		void setTblStd3(const QString& tempStr);
		void sendCommands();
		void clearComObjs();

		void calcBasicErr();//����ȫ����Ĳ�����Ļ������
private:
	Ui::PlaParamDlgClass ui;
	tverparamparamDlg *m_PlaParamParamDlg;

	QTimer* m_sendTimer;//��ʱ��������
	sti1062Acommand m_readCommand;

	QSettings* m_tverparam_config;//��ȡ������������, �ͺ�, ��׼, ����Ա��
	QSettings* m_std_pla_config;//��׼�¶ȼƲ���
	QSettings* m_chk_pla_config;//�����¶ȼƲ���

	ReadComConfig* m_readComConfig;//��������
	Sti1062aComObject* m_tempObj;//��׼�¶ȼƴ��ڶ���

	T_Platinum_Verify_Record_PTR m_PlaVerifyRecPtr;//�������¼
	QString m_timeStamp; //ʱ���
	int m_rec_num;//��Ҫ����ļ�¼����
	int m_chanel;//ʹ�õı�׼�¶ȼƵ�ͨ����
	int m_saved_times;//�����ݿ����, ��Ϊ������������
	int m_temp_index;//����¶ȵ������

	int m_current_temp_seq;//��ǰ�¶ȵ�
	int m_current_chk_seq;//��ǰ����

	bool m_tbl_inited;//����ʼ�����
private:
	void initTbls();
	void initTbl(QTableWidget*);//��ʼ�����
	void insertData();
	void readConfig();//��ȡ��׼�¶ȼơ����첬���衢��������
	void readChkResult();//��ȡ���첬��������
	
	void calcBasicErrPerMeter(int);//���㵫֧�ȱ�Ľ����ڲ�����Ļ������
	float* getTmpPntBasicErr(int, QString);
};

#endif//TVERPARAM_H