#ifndef PARASETDLG_H
#define PARASETDLG_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QDateTime>

#include "ui_parasetdlg.h"
#include "qtexdb.h"
#include "parasetdlg_global.h"
#include "basedef.h"
class PARASETDLG_EXPORT ParaSetReader;
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

public slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();

private:
	Ui::ParaSetDlgClass ui;
	char filename[255];
	
	QSettings *settings;//�����ļ�
	QParams_PTR params;//���ε����ò���
	ParaSetReader *lastParams;//�ϴε����ò���
	QString sep;//�ָ���
	qint64 timestamp;//ʱ���

	QVector<QLineEdit*> lineEdit_uppers;
	QVector<QLineEdit*> lineEdit_flows;
	QVector<QLineEdit*> lineEdit_quantites;
	QVector<QLineEdit*> lineEdit_valves;
	QVector<QComboBox*> cBox_seqs;

	void flowPointVector();
	void installLastParams();//װ���ϴεĲ�������
	void SaveHead();//���������Ϣ
	void SaveFlowPoint(int i);//������������Ϣ
	void SaveBool();//���沼��ֵ
	void SaveOther();//����������Ϣ
private slots:

};

class PARASETDLG_EXPORT ParaSetReader
{
	public:
		QSettings *settings;
		QParams_PTR params;

		ParaSetReader();
		~ParaSetReader();

		QParams_PTR readParamValues();
		int* readParamIndexes();
private:
	void readHead();
	void readFlowPoints();
	void readFlowPoint(int i);
	void readBool();
	void readOther();
};
#endif // PARASETDLG_H
