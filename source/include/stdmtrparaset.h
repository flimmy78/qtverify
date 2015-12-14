#ifndef STDPARASET_H
#define STDPARASET_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QDateTime>
#include <QMap>

#include "ui_stdmtrparaset.h"
#include "systemsetdlg_global.h"
#include "basedef.h"

#define FLOW_K_NUM 10//����-Kϵ����ĸ���
#define DIAMETER_NUM 4//һ�������˼����ܾ��ı�׼��

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
	QSettings* m_stdParam;
	//��������ؼ�����
	QVector<QLineEdit*> m_vecflowPointSmall;
	QVector<QLineEdit*> m_vecflowPointMid1;
	QVector<QLineEdit*> m_vecflowPointMid2;
	QVector<QLineEdit*> m_vecflowPointBig;
	//��Kϵ���ؼ�����	
	QVector<QLineEdit*> m_vecKCoeSmall;
	QVector<QLineEdit*> m_vecKCoeMid1;
	QVector<QLineEdit*> m_vecKCoeMid2;
	QVector<QLineEdit*> m_vecKCoeBig;
	//���ھ�������������ؼ�����
	QMap<flow_rate_wdg, QLineEdit*> m_mapPulseWdg;
	QMap<flow_rate_wdg, QLineEdit*> m_mapUpperFlowWdg;
	QMap<flow_rate_wdg, QLineEdit*> m_mapAdjustWdg;
	QMap<flow_rate_wdg, QComboBox*> m_mapInstRouteWdg;
	QMap<flow_rate_wdg, QComboBox*> m_mapAccumRouteWdg;

private slots:
	void initWdgVec();

	void writeStdMeter();
	void writeFlowKCoe();
	void writePulse();
	void writeUpperFlow();
	void writeRoute();

	void installStdMeter();
	void installFlowKCoe();
	void installPulse();
	void installFlowRate();
	void installRoute();
};

#endif // STDPARASET_H
