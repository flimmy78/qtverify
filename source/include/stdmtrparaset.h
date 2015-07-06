#ifndef STDPARASET_H
#define STDPARASET_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QDateTime>

#include "ui_stdmtrparaset.h"
#include "systemsetdlg_global.h"
#include "basedef.h"

#define FLOW_K_NUM 10//流量-K系数点的个数
#define DIAMETER_NUM 4//一共设置了几个管径的标准表

enum diam_seq//口径与序列号对应
{
	DN3_STD = 0,
	DN5_STD,
	DN10_STD,
	DN25_STD
};
class SYSTEMSETDLG_EXPORT StdMtrParaSet : public QWidget
{
	Q_OBJECT

public:
	StdMtrParaSet(QWidget *parent = 0, Qt::WFlags flags = 0);
	~StdMtrParaSet();

signals:

public slots:
	void showEvent(QShowEvent *);
	void closeEvent(QCloseEvent *);

	void on_btnSave_clicked();
	void on_btnExit_clicked();

private:
	Ui::StdMtrParaSetClass ui;
	//各流量点控件序列
	QVector<QLineEdit*> m_vecflowPointDN3;
	QVector<QLineEdit*> m_vecflowPointDN5;
	QVector<QLineEdit*> m_vecflowPointDN10;
	QVector<QLineEdit*> m_vecflowPointDN25;
	//各K系数控件序列	
	QVector<QLineEdit*> m_vecKCoeDN3;
	QVector<QLineEdit*> m_vecKCoeDN5;
	QVector<QLineEdit*> m_vecKCoeDN10;
	QVector<QLineEdit*> m_vecKCoeDN25;
	//各口径表的其他参数控件序列
	QVector<QLineEdit*> m_vecPulse;
	QVector<QLineEdit*> m_vecUpperFlow;
	QVector<QLineEdit*> m_vecAdjust;
	//各检测流量点的控件序列
	QVector<QComboBox*> m_vecRouteDN;
	QVector<QComboBox*> m_vecInstRoute;
	QVector<QComboBox*> m_vecAccumRoute;

	QSettings* m_stdParam;
private slots:
	void initWdgVec();

	void writeStdMeter();
	void writeFlowKCoe();
	void writePulse();
	void writeFlowRate();
	void writeRoute();

	void installStdMeter();
	void installFlowKCoe();
	void installPulse();
	void installFlowRate();
	void installRoute();
};

#endif // STDPARASET_H
