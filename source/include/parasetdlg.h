#ifndef PARASETDLG_H
#define PARASETDLG_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QDateTime>

#include "ui_parasetdlg.h"
#include "systemsetdlg_global.h"
#include "basedef.h"

class QSqlTableModel;

/*
** �������ļ��е�����������Ϣ�������ṹQParams_PTR��
*/
class SYSTEMSETDLG_EXPORT ParaSetReader
{
public:
		
	QMap<int,QString> m_valvePortMap;//�������ŵ�����ֵ����˿ںŵ�˫���ϵ
	ParaSetReader();
	~ParaSetReader();

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
};


class SYSTEMSETDLG_EXPORT ParaSetDlg : public QWidget
{
	Q_OBJECT

public:
	ParaSetDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ParaSetDlg();

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


signals:
	void saveSuccessSignal();

public slots:
	void showEvent(QShowEvent * event);
	void closeEvent(QCloseEvent * event);
	void on_btnExit_clicked();
	void on_btnSave_clicked();
	void on_cmbStandard_currentIndexChanged();
	void slot_autopick_clicked(int);

private:
	Ui::ParaSetDlgClass ui;
	bool cBoxData_inited;//���, ������������Ѿ������ݿ��ж�ȡ������
	
	QSettings *settings;//�����ļ�
	Verify_Params_PTR params;//���ε����ò���
	ParaSetReader *lastParams;//�ϴε����ò���
	qint64 timestamp;//ʱ���

	QVector<QLineEdit*> lineEdit_uppers;//����������ؼ�����
	QVector<QLineEdit*> lineEdit_flows;//�춨������ؼ�����
	QVector<QLineEdit*> lineEdit_quantites;//�춨ˮ���ؼ�����
	QVector<QComboBox*> cBox_valves;//�������Ӧ�ķ��ſؼ�����
	QVector<QLineEdit*> lineEdit_freqs;//ˮ��Ƶ�ʿؼ�����
	QVector<QComboBox*> cBox_seqs;//�춨����ؼ�����

	QButtonGroup *m_btnGroup_autopick; //�Զ��ɼ�
	QButtonGroup *m_btnGroup_adjustError; //�������
	QButtonGroup *m_btnGroup_writeNum; //�������

	void flowPointVector();//������������, ���ƹ��ܵĿؼ���������, ����ʹ��
	void installLastParams();//װ���ϴεĲ�������
	void installHead();//���������ļ���[head]�����Ϣ
	void installFlowPoint();//���������ļ���[FlowPoint_i]�����Ϣ
	void installBool();//���������ļ���[Bool]�����Ϣ
	void installOther();//���������ļ���[Other]�����Ϣ

	void installDftDBinfo();//�������ݿ���Ĭ�ϵĲ���

	bool chkSeq();//���ѡ���ļ춨�����Ƿ�����Ҫ��
	void SaveHead();//���������Ϣ
	void SaveFlowPoint();//������������Ϣ
	void SaveBool();//���沼��ֵ
	void SaveOther();//����������Ϣ

private slots:

};

#endif // PARASETDLG_H
