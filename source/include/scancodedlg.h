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

#define COL_NOW_METER_NO	0
#define COL_NEW_METER_NO	1
#define COL_READ_METER_NO	2
#define COL_MODIFY_METER_NO	3

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

	int m_maxMeterNum;    //被检表的最大个数
	int m_oldMaxMeterNum; //上次被检表的最大个数
	int m_pickcode;		  //采集代码(热表通讯协议版本号)
	QString m_numPrefix;      //表号前缀(14位表号的前6位）

	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;
	Verify_Params_PTR m_nowParams; //当前检定参数

	ComThread *m_meterThread; //热量表通讯线程
	MeterComObject *m_meterObj;	
	ReadComConfig *m_readComConfig; //读串口设置

	void initMeterCom(); //热量表串口
	void showEvent(QShowEvent * event);
	void closeEvent(QCloseEvent * event);
	void resizeEvent(QResizeEvent * event);

public slots:
	int readNowParaConfig(); //获取当前检定参数
	void initTableWidget();  //设置表格行数
	void on_tableWidget_cellChanged(int row, int column);

	void on_btnExit_clicked();    //点击"退出"按钮
	void on_btnParaSet_clicked(); //参数设置

	void on_btnAllReadNO_clicked();   //读表号(所有表）
	void on_btnAllModifyNO_clicked(); //修改表号(所有表）
	void slotModifyMeterNO(const int &row); //修改表号
	void slotReadNO(const int &row);        //读表号
	void slotSetMeterNumber(const QString& comName, const QString& meterNumber);

private slots:

signals:

private:
	Ui::ScanCodeDlgClass ui;
};

#endif //SCANCODEDLG_H