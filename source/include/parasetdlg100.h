#ifndef PARASETDLG100_H
#define PARASETDLG100_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QDateTime>

#include "ui_parasetdlg100.h"
#include "systemsetdlg_global.h"
#include "basedef.h"

class QSqlTableModel;

/*
** �������ļ��е�����������Ϣ�������ṹQParams_PTR��
*/
class SYSTEMSETDLG_EXPORT ParaSetReader100
{
public:
		
	QMap<int,QString> m_valvePortMap;//�������ŵ�����ֵ����˿ںŵ�˫���ϵ
	QMap<int,QString> m_regPortMap;//�������ڷ�������ֵ����˿ںŵ�˫���ϵ
	ParaSetReader100();
	~ParaSetReader100();

	Verify_Params_PTR getParams();
	Verify_Params_PTR m_params;
	
	int readIniFile();
	Flow_Point_Info getFpBySeq(int i);//ȡ���춨����Ϊi����������Ϣ

	int getBigSmallBySeq(int i);//ȡ���춨����Ϊi�Ľ���ؼ�������

private:
	QSettings *m_settings;
	QSettings *m_port_config;//���Ŷ˿������ļ�

	void initValveMap();
	void readParamValues();//��ȡ�����ļ����е���Ϣ

	void readHead();//��ȡ�����ļ���[head]�����Ϣ
	void readFlowPoints();//��ȡ�����ļ���[FlowPoints]�����Ϣ
	void readBool();//��ȡ�����ļ���[Bool]�����Ϣ
	void readOther();//��ȡ�����ļ���[Other]�����Ϣ
	void readWaterPara();
};

class SYSTEMSETDLG_EXPORT ParaSetDlg100 : public QWidget
{
	Q_OBJECT

public:
	ParaSetDlg100(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ParaSetDlg100();

	int m_meterStdNum;	//��������
	MeterStandard_PTR m_meterStdPtr;

	int m_manuFacNum;	//���쵥λ
	Manufacture_PTR m_manuFacPtr;

	void initUiData(); //�����ݿ��ȡ��¼�����combox��
	void initBtnGroup();//��ʼ��ButtonGroup

	void mapPickCodeModel(); //�ɼ�����ģ��
	QSqlTableModel *m_pickCodeModel;
	int m_curPickCodeIdx; //��ǰ�ɼ����������

	void mapVfDeptModel(); //�ͼ쵥λģ��
	QSqlTableModel *m_vfDeptModel;
	int m_curVfDeptIdx; //��ǰ�ͼ쵥λ������

	void mapManuDeptModel(); //���쵥λģ��
	QSqlTableModel *m_manuDeptModel;
	int m_curManuDeptIdx; //��ǰ���쵥λ������

	void mapUserModel(); //�ͼ�Ա�ͺ���Աģ��
	QSqlTableModel *m_userModel;
	int m_curVerifyPersonIdx; //��ǰ�ͼ�Ա������
	int m_curCheckPersonIdx;  //��ǰ����Ա������

	void mapMeterModelModel(); //���ͺ�ģ��
	QSqlTableModel *m_modelModel;
	int m_curModelIdx; //��ǰ���ͺŵ�����

	void showWaterPara();

signals:
	void saveSuccessSignal();

public slots:
	void showEvent(QShowEvent * event);
	void closeEvent(QCloseEvent * event);
	void on_btnExit_clicked();
	void on_btnSave_clicked();
	void on_cmbStandard_currentIndexChanged();
	void slot_autopick_clicked(int);

	void onVerifyFlowChanged(QString vFlow, int num);
	void on_lnEdit_Flow1_textChanged(const QString & text);
	void on_lnEdit_Flow2_textChanged(const QString & text);
	void on_lnEdit_Flow3_textChanged(const QString & text);
	void on_lnEdit_Flow4_textChanged(const QString & text);

	void onUpperFlowChanged();
	void on_lineEdit_Upper_1_textChanged(const QString & text);
	void on_lineEdit_Upper_2_textChanged(const QString & text);
	void on_lineEdit_Upper_3_textChanged(const QString & text);
	void on_lineEdit_Upper_4_textChanged(const QString & text);

private:
	Ui::ParaSetDlgClass100 ui;
	bool cBoxData_inited;//���, ������������Ѿ������ݿ��ж�ȡ������
	
	QSettings *settings;//�����ļ�
	Verify_Params_PTR params;//���ε����ò���
	ParaSetReader100 *lastParams;//�ϴε����ò���
	qint64 timestamp;//ʱ���

	QVector<QLineEdit*> lineEdit_uppers;//����������ؼ�����
	QVector<QLineEdit*> lineEdit_flows;//�춨������ؼ�����
	QVector<QLineEdit*> lineEdit_quantites;//�춨ˮ���ؼ�����
	QVector<QComboBox*> cBox_valves;//�������Ӧ�ķ��ſؼ�����
	QVector<QLineEdit*> lineEdit_freqs;//ˮ��Ƶ�ʿؼ�����
	QVector<QComboBox*> cBox_seqs;//�춨����ؼ�����
	QVector<QLineEdit*> lineEdit_Openings;//�������Ӧ�ĵ��ڷ����ȿ�������

	QButtonGroup *m_btnGroup_autopick; //�Զ��ɼ�
	QButtonGroup *m_btnGroup_adjustError; //�������
	QButtonGroup *m_btnGroup_writeNum; //�������

	void flowPointVector();//������������, ���ƹ��ܵĿؼ���������, ����ʹ��
	void installLastParams();//װ���ϴεĲ�������
	void installHead();//���������ļ���[head]�����Ϣ
	void installFlowPoint();//���������ļ���[FlowPoint_i]�����Ϣ
	void installBool();//���������ļ���[Bool]�����Ϣ
	void installOther();//���������ļ���[Other]�����Ϣ
	void installWaterPara();

	void installDftDBinfo();//�������ݿ���Ĭ�ϵĲ���

	bool chkSeq();//���ѡ���ļ춨�����Ƿ�����Ҫ��
	bool chkTotalQuantity();//����趨�ļ춨��֮���Ƿ񳬳���ƽ�����Χ
	void SaveHead();//���������Ϣ
	void SaveFlowPoint();//������������Ϣ
	void SaveBool();//���沼��ֵ
	void SaveOther();//����������Ϣ
	void SaveWaterPara();//����ˮ�����

	void Update_T_Meter_Default_Params();

private slots:

};

#endif // PARASETDLG100_H
