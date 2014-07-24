/***********************************************
**  �ļ���:     weightmethod.cpp
**  ����:       �������춨������
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/7/15
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/07 ��һ��
**  ���ݰ���:
**  ˵��:		
**  ���¼�¼:   
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QTest>

#include "weightmethod.h"
#include "commondefine.h"

WeightMethodDlg::WeightMethodDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"WeightMethodDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	ui.tabWidget->setTabsClosable(true);
	connect(ui.tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));

	/////////////////////////////////////////////////////////
	ui.lcdNumberInTemper->display("27.8");
	QString inTemper = QString("%1").arg(ui.lcdNumberInTemper->value(), 4);
	float iii = inTemper.toFloat();

/*	for (int i=0; i<4; i++)
	{
		ui.tabWidget->removeTab(1);
	}*/
	////////////////////////////////////////////////////////


	m_exaustTimer = new QTimer(this); //������ʱ��
	connect(m_exaustTimer, SIGNAL(timeout()), this, SLOT(slotExaustFinished()));
	m_exaustSecond = 10; //����ʱ��Ĭ��45��

	m_balTimer = new QTimer(this);
	connect(m_balTimer, SIGNAL(timeout()), this, SLOT(freshBigBalaceValue()));
	m_balTimer->start(200); //ģ����ƽÿ200�������һ��
	m_balValue = 0.0;

	if (!isComAndPortNormal())
	{
		qWarning()<<"���ڡ��˿����ô���!";
	}

	if (!isWaterOutValveOpen())
	{
		qWarning()<<"��ˮ����δ��";
	}

	if (!readParaConfig())
	{
		qWarning()<<"��ȡ���������ļ�ʧ��!";
	}
}

WeightMethodDlg::~WeightMethodDlg()
{
}

void WeightMethodDlg::closeEvent( QCloseEvent * event)
{
	qDebug()<<"^^^^^WeightMethodDlg::closeEvent";

}

//�رձ�ǩҳ
void WeightMethodDlg::removeSubTab(int index) 
{ 
	ui.tabWidget->removeTab(index); 
} 

//��⴮�ڡ��˿������Ƿ���ȷ
int WeightMethodDlg::isComAndPortNormal()
{
	return true;
}

//����ˮ�����Ƿ�� ��:true���ر�:false
int WeightMethodDlg::isWaterOutValveOpen()
{
	return true;
}

//�����������ļ�
int WeightMethodDlg::readParaConfig()
{
	return true;
}

/*
**	���"������ť"����ʼ�춨
*/
int WeightMethodDlg::on_btnExhaust_clicked()
{
	if (!isDataCollectNormal())
	{
		qWarning()<<"���ݲɼ�������������";
		return false;
	}

	if (!openAllValuesAndPump())
	{
		qWarning()<<"�����з��ź�ˮ�� ʧ��!";
		return false;
	}

	m_exaustTimer->start(m_exaustSecond*1000);//��ʼ��������ʱ

	readMeterNumber();

	setMeterVerifyStatus();

	return true;
}

//������ݲɼ��Ƿ�������������ƽ���¶ȡ����������
int WeightMethodDlg::isDataCollectNormal()
{
	return true;
}

//�����з��ź�ˮ��
int WeightMethodDlg::openAllValuesAndPump()
{
	return true;
}

/*
** ����ʱ���������Ӧ����
*/
void WeightMethodDlg::slotExaustFinished()
{
	m_exaustTimer->stop(); //ֹͣ������ʱ

	if (!closeAllFlowPointValves()) //�ر����������㷧�� ʧ��
	{
		if (!closeAllFlowPointValves()) //�ٳ��Թر�һ��
		{
			qWarning()<<"�춨����";
			return;
		}
	}

	//�жϲ��ȴ���ƽ����,����Ҫ��ĳ�ʼ����(2kg)
	if (judgeBalanceInitValue(BALANCE_START_VALUE))
	{
		if (!closeWaterOutValve())
		{
			qWarning()<<"�رշ�ˮ��ʧ��";
		}

		if (!openBigFlowValve())
		{
			qWarning()<<"�򿪴�������ʧ��";
		}
	}

	//�жϲ��ȴ���ƽ���������ڳ�ʼ����(2kg)+3kg
	if (judgeBalanceInitValue(BALANCE_START_VALUE + 3))
	{
		if (!closeBigFlowValve())
		{
			qWarning()<<"�رմ�������ʧ��";
		}
	}

	if (isAllMeterInVerifyStatus()) //�������ѽ���춨״̬
	{
		startVerify();
	}

}

//��ȡ���
int WeightMethodDlg::readMeterNumber()
{
	return true;
}

//�������������춨״̬
int WeightMethodDlg::setMeterVerifyStatus()
{
	return true;
}

//�ر����������㷧��
int WeightMethodDlg::closeAllFlowPointValves()
{
	return true;
}

//�رշ�ˮ����
int WeightMethodDlg::closeWaterOutValve()
{
	return true;
}

//�򿪴������㷧��
int WeightMethodDlg::openBigFlowValve()
{
	return true;
}

//�رմ������㷧��
int WeightMethodDlg::closeBigFlowValve()
{
	return true;
}

//��Ӧ������ƽ�����ı仯
int WeightMethodDlg::judgeBalanceInitValue(float v)
{
	while (ui.lnEditBigBalance->text().toFloat() < v)
	{
		qDebug()<<"��ƽ���� ="<<ui.lnEditBigBalance->text().toFloat()<<", С��Ҫ������� "<<v;
		QTest::qWait(1000);
	}

	return true;
}

//�ж��������ѽ���춨״̬
int WeightMethodDlg::isAllMeterInVerifyStatus()
{
	return true;
}

void WeightMethodDlg::on_btnStart_clicked()
{
	startVerify();
}

//��ʼ�춨
void WeightMethodDlg::startVerify()
{
	
}


void WeightMethodDlg::freshBigBalaceValue()
{
	if (m_balValue > 10)
	{
		m_balValue = 0;
	}
	m_balValue += 0.01;
	ui.lnEditBigBalance->setText(QString("%1").arg(m_balValue));
}