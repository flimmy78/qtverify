#ifndef CMBVERIFY_H
#define CMBVERIFY_H

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

#include "ui_cmbverify.h"
#include "protocol.h"
#include "comobject.h"
#include "readcomconfig.h"
#include "algorithm.h"
#include "cmbparam.h"

#define POS_IN 0
#define POS_OUT 1

#define UNIT_KWH 0
#define UNIT_MJ 1

#define READ_STI1062A_TIMEOUT	200//��ʱ�����

#define COL_NUM		11//������
#define COL_SN		0//�ȱ����к�
#define COL_E0		1//��ʼ��ֵ
#define COL_V0		2//��ʼ�������
#define COL_V1		3//�����������
#define COL_E1		4//������ֵ
#define COL_IN_T	5//�����¶�ֵ
#define COL_OUT_T	6//�����¶�ֵ
#define COL_DELTA_E 7//ģ����ֵ
#define COL_DELTA_V 8//ģ�����
#define COL_STD_E	9//��׼��ֵ
#define COL_ERR		10//ʾֵ���

#define MAX_METER_NUM	20//�������

class CMBVERIFY_EXPORT CmbVerifyDlg : public QWidget
{
	Q_OBJECT

public:
	CmbVerifyDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CmbVerifyDlg();


public slots:
	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent *);

	void on_btn_collection_clicked();//�ɼ���׼�¶ȼ�����
	void on_btn_stop_clicked();//ֹͣ�ɼ���׼�¶ȼ�

	void on_tableWidget_cellChanged(int row, int col);
	void on_btnPara_clicked();
	void on_btnStart_clicked();
	void on_btnSave_clicked();
	void on_btnExit_clicked();
	void on_lineEdit_min_theta_textEdited(const QString & text);
private slots:
	void freshCmbParam(void);
	void startVefifySlot(void);
	void on_btnGroup_unit_clicked(int);
	void on_btnGroup_pos_clicked(int);

	void sendCommands();
	void clearTempComObjs();
	void setStdTempUi(const QString &tempStr);//��׼�¶ȼƸ����ݶ�ȡ���
signals:
	void vefifyCanStart(void);
private:
	Ui::CmbVerifyClass ui;
	CmbParamDlg* m_CmbParamDlg;//�������ô���
	CAlgorithm* m_algo;//������ֵ
	QButtonGroup *m_btnGroup_unit; //��װλ�� 0:���ڣ�1:����
	QButtonGroup *m_btnGroup_pos; //������λ 0:MJ;1:kwh

	/*----------�������õ��Ĺؼ�����-----------*/
	int m_current_pos;//��װλ��
	bool m_pos_selected;//��װλ����ѡ��
	int m_current_unit;//������λ
	bool m_unit_selected;//������λ��ѡ��

	float m_std_temperate_in;//��׼�¶ȼƽ����¶�
	float m_std_temperate_out;//��׼�¶ȼƳ����¶�

	float m_min_tempdiff;//��С�²�
	bool m_min_tempdiff_set;//��С�²�������
	/*----------�������õ��Ĺؼ�����end--------*/
	//Calc_Verify_Record_PTR m_recPtr; //��Ч�ļ춨��¼
	QString m_timeStamp; //��¼ʱ���

	QSettings* m_param_config;//�������������ļ�


	void initUi();//��ʼ��Ui����
	void chkIfCanStartVerify();//����Ƿ���Կ�ʼ���
	float getEnthalpyDiffByTemper(float inT, float outT); //���ݽ����¶Ⱥͳ����¶Ȼ�ȡ�ʲ�
	float getEnergyByEnthalpy(float analogV, float inTemper, float outTemper);//�ʲ������������
	float getStdEnergy(float analogV);//���ݱ�׼�¶ȼƼ�������
	/*----------��ȡ��׼�¶ȼ�-----------*/
	QTimer* m_sendTimer;//��ʱ��������
	ComThread m_tempThread; //��׼�¶ȼƲɼ��߳�
	sti1062Acommand m_StdCommand;//��ȡ��׼�¶ȼƵ�����
	ReadComConfig* m_readComConfig;//��������
	Sti1062aComObject* m_tempObj;//��׼�¶ȼƴ��ڶ���
	/*----------��ȡ��׼�¶ȼ�end--------*/
	void addNewTblRow();
	int saveVerifyRecords(); //ͳ����Ч�ļ춨�������


};

#endif //CMBVERIFY_H