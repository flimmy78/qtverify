/***********************************************
**  �ļ���:     parasetdlg.cpp
**  ����:       ������-�����춨-�������ý���
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/12
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:
**  ���¼�¼:
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QThread>
#include <QtCore/QSettings>
#include <QTextCodec>

#include "parasetdlg.h"
#include "commondefine.h"

ParaSetDlg::ParaSetDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"ParaSetDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);
	flowPointVector();


	m_basedb.startdb();

	m_meterStdNum = 0;
	m_meterStdPtr = NULL;

	m_meterTypeNum = 0;
	m_meterTypePtr = NULL;

	m_manuFacNum = 0;
	m_manuFacPtr = NULL;

	initUiData();
	sep="#SEP#";
	installLastParams();
	char* runhome = getenv( "RUNHOME" );
#ifdef __unix
	sprintf( filename, "%s/ini/qualityParaSet.ini", runhome );
#else
	sprintf( filename, "%s\\ini\\qualityParaSet.ini", runhome );
#endif

	settings = new QSettings(filename, QSettings::IniFormat);
	settings->setIniCodec("GB2312");//�����ini�ļ���д��������

	ui.lnEdit_Flow1->setStyleSheet("border: 2px solid gray;"
		"border-radius: 10px;"
		"padding: 0 8px;"
		"background: yellow;"
		"selection-background-color:darkgray;");
}

ParaSetDlg::~ParaSetDlg()
{
	qDebug()<<"!!! ParaSetDlg destructor";
}

void ParaSetDlg::closeEvent(QCloseEvent * event)
{
	qDebug()<<"&&& ParaSetDlg closeEvent";

	if (m_meterStdPtr)
	{
		delete []m_meterStdPtr;
		m_meterStdPtr = NULL;
	}

	if (m_meterTypePtr)
	{
		delete []m_meterTypePtr;
		m_meterTypePtr = NULL;
	}

	if (m_manuFacPtr)
	{
		delete []m_manuFacPtr;
		m_manuFacPtr = NULL;
	}
	if (settings)
	{
		delete settings;
		settings = NULL;
	}
	m_basedb.closedb();
}

void ParaSetDlg::on_btnExit_clicked()
{
	this->close();
}

void ParaSetDlg::initUiData()
{
	//����
	m_basedb.getMeterStandard(m_meterStdNum, m_meterStdPtr);
	for (int i=0; i<m_meterStdNum; i++)
	{
		qDebug()<<"id:"<<m_meterStdPtr[i].id<<",name:"<<m_meterStdPtr[i].name;
		ui.cmbStandard->insertItem(i, m_meterStdPtr[i].name);
	}

	//������
	m_basedb.getMeterType(m_meterTypeNum, m_meterTypePtr);
	for (int j=0; j<m_meterTypeNum; j++)
	{
		qDebug()<<"id:"<<m_meterTypePtr[j].id<<",desc:"<<QString::fromLocal8Bit(m_meterTypePtr[j].desc);
		ui.cmbCollectCode->insertItem(j, QString::fromLocal8Bit(m_meterTypePtr[j].desc)); //���ֱ���
	}	

	//���쵥λ
	m_basedb.getManufacture(m_manuFacNum, m_manuFacPtr);
	for (int m=0; m<m_manuFacNum; m++)
	{
		qDebug()<<"id:"<<m_manuFacPtr[m].id<<",desc:"<<QString::fromLocal8Bit(m_manuFacPtr[m].desc);
		ui.cmbManufacture->insertItem(m, QString::fromLocal8Bit(m_manuFacPtr[m].desc)); //���ֱ���
	}	


}

void ParaSetDlg::installLastParams()
{

}

void ParaSetDlg::flowPointVector()
{
	
	lineEdit_uppers.append(ui.lineEdit_Upper_1);
	lineEdit_uppers.append(ui.lineEdit_Upper_2);
	lineEdit_uppers.append(ui.lineEdit_Upper_3);
	lineEdit_uppers.append(ui.lineEdit_Upper_4);
	
	lineEdit_flows.append(ui.lnEdit_Flow1);
	lineEdit_flows.append(ui.lnEdit_Flow2);
	lineEdit_flows.append(ui.lnEdit_Flow3);
	lineEdit_flows.append(ui.lnEdit_Flow4);
	
	lineEdit_quantites.append(ui.lineEdit_Quantity_1);
	lineEdit_quantites.append(ui.lineEdit_Quantity_2);
	lineEdit_quantites.append(ui.lineEdit_Quantity_3);
	lineEdit_quantites.append(ui.lineEdit_Quantity_4);
	
	lineEdit_valves.append(ui.lineEdit_Valve_1);
	lineEdit_valves.append(ui.lineEdit_Valve_2);
	lineEdit_valves.append(ui.lineEdit_Valve_3);
	lineEdit_valves.append(ui.lineEdit_Valve_4);
	
	cBox_seqs.append((ui.cBox_seq_1));
	cBox_seqs.append((ui.cBox_seq_2));
	cBox_seqs.append((ui.cBox_seq_3));
	cBox_seqs.append((ui.cBox_seq_4));
}

void ParaSetDlg::on_btnSave_clicked()
{
	timestamp = QDateTime::currentMSecsSinceEpoch();
	settings->beginGroup("Timestamp");
	settings->setValue("timestamp",timestamp);
	settings->endGroup();
	SaveHead();
	for (int i=0; i<4; i++)
	{
		SaveFlowPoint(i);
	}
	
	SaveBool();
	SaveOther();
}

void ParaSetDlg::SaveHead()
{
	settings->beginGroup("head");
	settings->setValue("timestamp",timestamp);
	settings->setValue("standard", QString::number(ui.cmbStandard->currentIndex()) + sep + ui.cmbStandard->currentText());
	settings->setValue("metertype", QString::number(ui.cmbCollectCode->currentIndex()) + sep + ui.cmbCollectCode->currentText());
	settings->setValue("manufacture", QString::number(ui.cmbManufacture->currentIndex()) + sep + ui.cmbManufacture->currentText());
	settings->setValue("grade", QString::number(ui.cmbGrade->currentIndex()) + sep + ui.cmbGrade->currentText());
	settings->setValue("model", QString::number(ui.cmbModel->currentIndex()) + sep + ui.cmbModel->currentText());
	settings->setValue("verifycompany", QString::number(ui.cmbVerifyCompany->currentIndex()) + sep + ui.cmbVerifyCompany->currentText());
	settings->setValue("verifyperson", QString::number(ui.cmbVerifyPerson->currentIndex()) + sep + ui.cmbVerifyPerson->currentText());
	settings->setValue("pickcode", QString::number(ui.cmbCollectCode->currentIndex()) + sep + ui.cmbCollectCode->currentText());
	settings->setValue("nflowpoint", QString::number(ui.cmbFlow->currentIndex()) + sep + ui.cmbFlow->currentText());
	settings->endGroup();
}

/*
* �����i���������
* i: �����ϵĵ�i��������, �����Ǽ춨˳�� 
*/
void ParaSetDlg::SaveFlowPoint(int i)
{
	//ֻ����춨˳�� > 1 ��������
	if(cBox_seqs[i]->currentIndex() > 0)
	{
		settings->beginGroup("FlowPoint_" +  QString::number(i, 10));
		settings->setValue("timestamp",timestamp);
		settings->setValue("upperflow_" +  QString::number(i, 10), lineEdit_uppers[i]->text());//��������ֵ
		settings->setValue("verifyflow_" +  QString::number(i, 10), lineEdit_flows[i]->text());//������
		settings->setValue("flowquantity_" +  QString::number(i, 10), lineEdit_quantites[i]->text());//�춨ˮ��
		settings->setValue("pumpfrequencey_" +  QString::number(i, 10), lineEdit_valves[i]->text());//��Ƶ��Ƶ��
		settings->setValue("valve_" +  QString::number(i, 10), lineEdit_valves[i]->text());//��Ӧ�ķ���
		settings->setValue("seq_" +  QString::number(i, 10), cBox_seqs[i]->currentIndex());//�춨˳��
		settings->endGroup();
	}
}

void ParaSetDlg::SaveBool()
{
	settings->beginGroup("Bool");
	settings->setValue("timestamp",timestamp);
	settings->setValue("autopick", ui.tBtn_autoPick_true->isChecked() );//�Ƿ��Զ��ɼ�
	settings->setValue("Tqualitycheck", ui.tBtn_totalverify_true->isChecked() );//�Ƿ������춨
	settings->setValue("adjusterror", ui.tBtn_adjustError_true->isChecked() );//�Ƿ��������
	settings->setValue("writemeternumber", ui.tBtn_writeNum_true->isChecked() );//�Ƿ�д���
	settings->setValue("continuouscheck", ui.tBtn_continuous_true->isChecked() );//�Ƿ������춨
	settings->endGroup();
}

void ParaSetDlg::SaveOther()
{
	settings->beginGroup("Other");
	settings->setValue("timestamp",timestamp);
	settings->setValue("flowsafecoefficient", ui.lineEdit_sc_flow->text());//������ȫϵ��
	settings->setValue("thermalsafecoefficient", ui.lineEdit_sc_thermal->text());//������ȫϵ��
	settings->setValue("exhausttime", ui.lineEdit_exTime->text());//����ʱ��
	settings->endGroup();
}

ParaSetReader::ParaSetReader()
{

	char filename[255];
	char* runhome = getenv( "RUNHOME" );
#ifdef __unix
	sprintf( filename, "%s/ini/qualityParaSet.ini", runhome );
#else
	sprintf( filename, "%s\\ini\\qualityParaSet.ini", runhome );
#endif

	settings = new QSettings(filename, QSettings::IniFormat);
	settings->setIniCodec("GB2312");//�����ini�ļ���д��������

		params =new Quality_Params;
		memset(params, 0, sizeof(QParams_PTR));
}
ParaSetReader::~ParaSetReader()
{
	if (params)
	{
		delete params;
		params=NULL;
	}
}
/*
* ��ȡ�����ļ�����Ϣ
* index: �����ַ������ָ�����Ϻ������ֵ
*/
QParams_PTR ParaSetReader::readParamValues()
{

	QString sep = "#SEP#";
	//�ļ�ʱ���
	params->file_timestamp = settings->value("Timestamp/timestamp").toString().toLongLong();
	//��ȡ������Ϣ
	strcpy(params->m_stand,  settings->value("head/standard").toString().split(sep)[1].toLocal8Bit());
	strcpy(params->m_type,  settings->value("head/metertype").toString().split(sep)[1].toLocal8Bit());
	strcpy(params->m_manufac,  settings->value("head/manufacture").toString().split(sep)[1].toLocal8Bit());	
	strcpy(params->m_model,  settings->value("head/model").toString().split(sep)[1].toLocal8Bit());
	strcpy(params->m_model,  settings->value("head/verifycompany").toString().split(sep)[1].toLocal8Bit());
	strcpy(params->m_vperson,  settings->value("head/verifyperson").toString().split(sep)[1].toLocal8Bit());
	strcpy(params->m_pickcode,  settings->value("head/pickcode").toString().split(sep)[1].toLocal8Bit());
	params->m_grade = settings->value("head/grade").toString().split(sep)[1].toInt();
	params->m_nflowpnt = settings->value("head/nflowpoint").toString().split(sep)[1].toFloat();


	return params;
}