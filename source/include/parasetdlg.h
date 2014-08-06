#ifndef PARASETDLG_H
#define PARASETDLG_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QDateTime>

#include "ui_parasetdlg.h"
#include "qtexdb.h"
#include "parasetdlg_global.h"
#include "basedef.h"

/*
** �������ļ��е�����������Ϣ�������ṹQParams_PTR��
*/
class PARASETDLG_EXPORT ParaSetReader
{
public:
		
	QMap<int,QString> m_valvePortMap;//�������ŵ�����ֵ����˿ںŵ�˫���ϵ
	ParaSetReader();
	~ParaSetReader();

	Quality_Params_PTR getParams();
	Quality_Params_PTR m_params;
	int readIniFile();
	Flow_Point_Info getFpBySeq(int i);//ȡ���춨����Ϊi����������Ϣ

private:
	QSettings *m_settings;
	QSettings *m_portInfo;//���Ŷ˿������ļ�


	void initValveMap();
	void readParamValues();//��ȡ�����ļ����е���Ϣ

	void readHead();//��ȡ�����ļ���[head]�����Ϣ
	void readFlowPoints();//��ȡ�����ļ���[FlowPoint_i]�����Ϣ
	void readBool();//��ȡ�����ļ���[Bool]�����Ϣ
	void readOther();//��ȡ�����ļ���[Other]�����Ϣ
};


class PARASETDLG_EXPORT ParaSetDlg : public QWidget
{
	Q_OBJECT

public:
	ParaSetDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ParaSetDlg();

	int m_meterStdNum;	//��������
	MeterStandard_PTR m_meterStdPtr;

	int m_meterTypeNum;	//����������
	MeterType_PTR m_meterTypePtr;

	int m_manuFacNum;	//���쵥λ
	Manufacture_PTR m_manuFacPtr;

	CBaseExdb m_basedb;

	void initUiData(); //�����ݿ��ȡ��¼�����combox��
	void closeEvent(QCloseEvent * event);
//  void showEvent(QShowEvent *event);

signals:
	void saveSuccessSignal();

public slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();
	void on_cmbStandard_currentIndexChanged();
	void showEvent(QShowEvent * event);

private:
	Ui::ParaSetDlgClass ui;
	bool cBoxData_inited;//���, ������������Ѿ������ݿ��ж�ȡ������
	
	QSettings *settings;//�����ļ�
	Quality_Params_PTR params;//���ε����ò���
	ParaSetReader *lastParams;//�ϴε����ò���
	qint64 timestamp;//ʱ���

	QVector<QLineEdit*> lineEdit_uppers;//����������ؼ�����
	QVector<QLineEdit*> lineEdit_flows;//�춨������ؼ�����
	QVector<QLineEdit*> lineEdit_quantites;//�춨ˮ���ؼ�����
	QVector<QComboBox*> cBox_valves;//�������Ӧ�ķ��ſؼ�����
	QVector<QLineEdit*> lineEdit_freqs;//ˮ��Ƶ�ʿؼ�����
	QVector<QComboBox*> cBox_seqs;//�춨����ؼ�����

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
