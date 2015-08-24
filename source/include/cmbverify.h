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

enum cmb_table_columns
{
	COL_SN = 0,     //�ȱ����к�
	COL_V0,		    //��ʼ�������
	COL_E0,		    //��ʼ��ֵ
	COL_V1,		    //�����������
	COL_E1,		    //������ֵ
	COL_DELTA_V,	//ģ�����
	COL_DELTA_E,	//ģ����ֵ
	COL_STD_E,	    //��׼��ֵ
	COL_STD_ERR,	//��׼���
	COL_ERR,        //ʾֵ���
	COL_READ_DATA,  //��������
	COL_COUNT       //������
};

#define COL_BTN_NUM		3//��ȡ�����ݵİ�ť����

#define HEAHER_E0_KWH	"E0(kWh)"
#define HEAHER_E1_KWH	"E1(kWh)"
#define HEAHER_DELTAE_KWH	"\316\224E(kWh)"

#define HEAHER_E0_MJ	"E0(MJ)"
#define HEAHER_E1_MJ	"E1(MJ)"
#define HEAHER_DELTAE_MJ	"\316\224E(MJ)"


class CMBVERIFY_EXPORT CmbVerifyDlg : public QWidget
{
	Q_OBJECT

public:
	CmbVerifyDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CmbVerifyDlg();


public slots:
	void showEvent(QShowEvent *);
	void closeEvent(QCloseEvent * event);
	void resizeEvent(QResizeEvent * event);

	void on_btn_collection_clicked();//�ɼ���׼�¶ȼ�����
	void on_btn_stop_clicked();//ֹͣ�ɼ���׼�¶ȼ�

	void on_tableWidget_cellChanged(int row, int col);
	void on_btnPara_clicked();
	void on_btnStart_clicked();
	void on_btnSave_clicked();
	void on_btnExit_clicked();
	void on_lineEdit_min_theta_textChanged(const QString & text);
	void on_lineEdit_std_in_t_textChanged(const QString & text);
	void on_lineEdit_std_out_t_textChanged(const QString & text);
	void on_countdown_timerout();
	void on_btnGroup_unit_clicked(int);
	void on_btnGroup_pos_clicked(int);

private slots:
	void freshCmbParam(void);
	void startVerifySlot(void);

	void sendCommands();
	void clearTempComObjs();
	void setStdTempUi(const QString &tempStr);//��׼�¶ȼƸ����ݶ�ȡ���

	void slotReadData(const int &);//��ȡ������

	void slotSetMeterNumber(const QString& comName, const QString& meterNumber);//��ȡ���
	void slotSetMeterFlow(const QString& comName, const QString& flow);//��ȡ�������
	void slotSetMeterHeat(const QString& portName, const QString& heat);//��ȡ��ֵ
	void slotSetMeterTemp(const QString& portName, const QString& tempIn, const QString& tempOut);//��ȡ�������¶�

signals:
	void verifyCanStart(void);//���Կ�ʼ���
	void tempDiffAchived(void);//���²۴ﵽ�趨���²�

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

	bool m_delta_temp_achieved;//��ǰ���²۴ﵽ�춨�²�

	float m_stdErrLmtByGrade;//���ݱ�ĵȼ��ó���ʾֵ�����
	/*----------�������õ��Ĺؼ�����end--------*/
	Cmb_Verify_Record_PTR m_recPtr; //��Ч�ļ춨��¼
	QString m_timeStamp; //��¼ʱ���

	QSettings* m_param_config;//�������������ļ�


	void initUi();//��ʼ��Ui����
	void initTbl();
	void chkIfCanStartVerify();//����Ƿ���Կ�ʼ���
	void stdTempChanged();//��׼�¶ȼƶ����仯
	float getStdEnergy(float analogV);//���ݱ�׼�¶ȼƼ�������
	float getKCoeByTemper(float inTemper, float outTemper);//����Kϵ��
	/*----------��ȡ��׼�¶ȼ�-----------*/
	QTimer* m_sendTimer;//��ʱ��������
	ComThread m_tempThread; //��׼�¶ȼƲɼ��߳�
	stdTempCommand m_StdCommand;//��ȡ��׼�¶ȼƵ�����
	ReadComConfig* m_readComConfig;//��������
	StdTempComObject* m_tempObj;//��׼�¶ȼƴ��ڶ���
	/*----------��ȡ��׼�¶ȼ�end--------*/

	/*-------------��ȡ������----------*/
	MeterComObject *m_meterObj;
	ComThread *m_meterThread;	//������ͨѶ�߳�
	void initMeterCom();       //��������
	bool *m_vol0_is_read;//������ֵ�ѱ���ȡ
	bool *m_eng0_is_read;//������ֵ�ѱ���ȡ

	/*--------------------------------*/

	//void addNewTblRow(QSignalMapper *);//���һ����λ
	int saveVerifyRecords(); //ͳ����Ч�ļ춨�������

	QTimer *m_timer;
	int m_countdown;

	int m_metercount;
};

#endif //CMBVERIFY_H