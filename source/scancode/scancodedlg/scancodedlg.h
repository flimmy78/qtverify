#ifndef SCANCODEDLG_H
#define SCANCODEDLG_H

#ifdef SCANCODEDLG_DLL
#  ifdef WIN32
#  define SCANCODEDLG_EXPORT __declspec(dllexport)
#  else
#  define SCANCODEDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define SCANCODEDLG_EXPORT __declspec(dllimport)
#  else
#  define SCANCODEDLG_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>

#include "ui_scancodedlg.h"
#include "comobject.h"

enum col_num_def
{
	COL_NEW_METER_NO = 0,
	COL_OLD_METER_NO,	
	COL_READ_METER_NO,	
	COL_MODIFY_METER_NO,
	COL_COUNT
};

class CAlgorithm;
class ParaSetDlg;
class ParaSetReader;
class ReadComConfig;

class SCANCODEDLG_EXPORT ScanCodeDlg : public QWidget
{
	Q_OBJECT

public:
	ScanCodeDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ScanCodeDlg();

	int m_maxMeterNum;    //������������
	int m_oldMaxMeterNum; //�ϴα�����������
	int m_pickcode;		  //�ɼ�����(�ȱ�ͨѶЭ��汾��)
	QString m_numPrefix;      //���ǰ׺(14λ��ŵ�ǰ6λ��

	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;
	Verify_Params_PTR m_nowParams; //��ǰ�춨����

	ComThread *m_meterThread; //������ͨѶ�߳�
	MeterComObject *m_meterObj;	
	ReadComConfig *m_readComConfig; //����������

	void initMeterCom(); //��������
	void showEvent(QShowEvent * event);
	void closeEvent(QCloseEvent * event);
	void resizeEvent(QResizeEvent * event);

public slots:
	int readNowParaConfig(); //��ȡ��ǰ�춨����
	void initTableWidget();  //���ñ������
	void on_tableWidget_cellChanged(int row, int column);
	void clearTableContents();

	void on_btnExit_clicked();    //���"�˳�"��ť
	void on_btnParaSet_clicked(); //��������

	void on_btnAllReadNO_clicked();   //�����(���б�
	void on_btnAllModifyNO_clicked(); //�޸ı��(���б�
	void slotModifyMeterNO(const int &row); //�޸ı��
	void slotReadNO(const int &row);        //�����
	void slotSetMeterNumber(const QString& comName, const QString& meterNumber);

private slots:

signals:

private:
	Ui::ScanCodeDlgClass ui;
};

#endif //SCANCODEDLG_H