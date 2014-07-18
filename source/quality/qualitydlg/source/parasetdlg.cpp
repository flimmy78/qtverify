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
#include <QtGui/QMessageBox>

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

	initUiData();//�����ݿ��е�����, ��ʼ��comboBox��ֵ

	char* runhome = getenv( "RUNHOME" );
#ifdef __unix
	sprintf( filename, "%s/ini/qualityParaSet.ini", runhome );
#else
	sprintf( filename, "%s\\ini\\qualityParaSet.ini", runhome );
#endif

	settings = new QSettings(filename, QSettings::IniFormat);
	settings->setIniCodec("GB2312");//�����ini�ļ���д��������

	installLastParams();//�����ϴε�������Ϣ

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
	installHead();
	installFlowPoint();
	installBool();
	installOther();
}

void ParaSetDlg::installHead()
{
	ui.cmbStandard->setCurrentIndex(settings->value("head/standard").toString().split(SEP)[0].toInt());
	ui.cmbCollectCode->setCurrentIndex(settings->value("head/pickcode").toString().split(SEP)[0].toInt());
	ui.cmbManufacture->setCurrentIndex(settings->value("head/manufacture").toString().split(SEP)[0].toInt());
	ui.cmbGrade->setCurrentIndex(settings->value("head/grade").toString().split(SEP)[0].toInt());
	ui.cmbModel->setCurrentIndex(settings->value("head/model").toString().split(SEP)[0].toInt());
	ui.cmbVerifyCompany->setCurrentIndex(settings->value("head/verifycompany").toString().split(SEP)[0].toInt());
	ui.cmbVerifyPerson->setCurrentIndex(settings->value("head/verifyperson").toString().split(SEP)[0].toInt());
	ui.cmbFlow->setCurrentIndex(settings->value("head/nflowpoint").toString().split(SEP)[0].toInt());
}

void ParaSetDlg::installFlowPoint()
{
	qint64 file_tmstp = settings->value("Timestamp/timestamp").toLongLong();
	QStringList heads = settings->childGroups();//�����ļ��е�����
	// ��i������
	for (int i=0; i<VERIFY_POINTS; i++)
	{
		QString head = "FlowPoint_" + QString::number(i);
		if (heads.contains(head))
		{
			if (file_tmstp ==  settings->value(head + "/timestamp").toLongLong())
			{
				lineEdit_uppers[i]->setText(settings->value(head + "/upperflow_"  + QString::number(i)).toString());
				lineEdit_flows[i]->setText(settings->value(head + "/verifyflow_"  + QString::number(i)).toString());
				lineEdit_quantites[i]->setText(settings->value(head + "/flowquantity_"  + QString::number(i)).toString());
				lineEdit_valves[i]->setText(settings->value(head + "/valve_"  + QString::number(i)).toString());
				qDebug()<<settings->value(head + "/flowquantity_"  + QString::number(i)).toInt();
				cBox_seqs[i]->setCurrentIndex(settings->value(head + "/seq_"  + QString::number(i)).toInt());
			}
		}
	}
}

void ParaSetDlg::installBool()
{
	 ui.tBtn_autoPick_true->setChecked(settings->value("Bool/autopick").toBool()) ;
	 ui.tBtn_autoPick_false->setChecked(!(settings->value("Bool/autopick").toBool())) ;

	 ui.tBtn_totalverify_true->setChecked(settings->value("Bool/Tqualitycheck").toBool()) ;
	 ui.tBtn_totalverify_false->setChecked(!(settings->value("Bool/Tqualitycheck").toBool())) ;

	 ui.tBtn_adjustError_true->setChecked(settings->value("Bool/adjusterror").toBool()) ;
	 ui.tBtn_adjustError_false->setChecked(!(settings->value("Bool/adjusterror").toBool())) ;

	 ui.tBtn_writeNum_true->setChecked(settings->value("Bool/writemeternumber").toBool()) ;
	 ui.tBtn_writeNum_false->setChecked(!(settings->value("Bool/writemeternumber").toBool())) ;

	 ui.tBtn_continuous_true->setChecked(settings->value("Bool/continuouscheck").toBool()) ;
	 ui.tBtn_continuous_false->setChecked(!(settings->value("Bool/continuouscheck").toBool())) ;
}

void ParaSetDlg::installOther()
{
	ui.lineEdit_sc_flow->setText(settings->value("Other/flowsafecoefficient").toString());
	ui.lineEdit_sc_thermal->setText(settings->value("Other/thermalsafecoefficient").toString());
	ui.lineEdit_exTime->setText(settings->value("Other/exhausttime").toString());
}

/*������������, ���ƹ��ܵĿؼ���������, ����ʹ��; 
**��ͺñȽ����ϵ�һ��ؼ�����һ����ϵ��(��ϵ�����ݿ�)�е�һ����¼, 
**��ÿ���ؼ������¼�еĲ�ͬ����
*/
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
	settings->setValue("standard", QString::number(ui.cmbStandard->currentIndex()) + SEP + ui.cmbStandard->currentText());
	settings->setValue("metertype", QString::number(ui.cmbCollectCode->currentIndex()) + SEP + ui.cmbCollectCode->currentText());
	settings->setValue("manufacture", QString::number(ui.cmbManufacture->currentIndex()) + SEP + ui.cmbManufacture->currentText());
	settings->setValue("grade", QString::number(ui.cmbGrade->currentIndex()) + SEP + ui.cmbGrade->currentText());
	settings->setValue("model", QString::number(ui.cmbModel->currentIndex()) + SEP + ui.cmbModel->currentText());
	settings->setValue("verifycompany", QString::number(ui.cmbVerifyCompany->currentIndex()) + SEP + ui.cmbVerifyCompany->currentText());
	settings->setValue("verifyperson", QString::number(ui.cmbVerifyPerson->currentIndex()) + SEP + ui.cmbVerifyPerson->currentText());
	settings->setValue("pickcode", QString::number(ui.cmbCollectCode->currentIndex()) + SEP + ui.cmbCollectCode->currentText());
	settings->setValue("nflowpoint", QString::number(ui.cmbFlow->currentIndex()) + SEP + ui.cmbFlow->currentText());
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
	//settings->setValue("resetzero", ui.tBtn_resetzero_true->isChecked() );//�Ƿ��ֵ����
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

	readParamValues();
}

ParaSetReader::~ParaSetReader()
{
	if (settings)
	{
		delete settings;
		settings = NULL;
	}
	if (params)
	{
		delete params;
		params=NULL;
	}
}
/*
* ��ȡ�����ļ�����Ϣ
*/
void ParaSetReader::readParamValues()
{

	QString sep = "#SEP#";
	//��ȡ�ļ�ʱ���
	params->file_timestamp = settings->value("Timestamp/timestamp").toString().toLongLong();
	readHead();
	readBool();
	readOther();
	readFlowPoints();
}

void ParaSetReader::readHead()
{
	if (params->file_timestamp ==  settings->value("head/timestamp").toString().toLongLong())
	{
		//��ȡ������Ϣ
		strcpy(params->m_stand,  settings->value("head/standard").toString().split(SEP)[1].toLocal8Bit());
		strcpy(params->m_type,  settings->value("head/metertype").toString().split(SEP)[1].toLocal8Bit());
		strcpy(params->m_manufac,  settings->value("head/manufacture").toString().split(SEP)[1].toLocal8Bit());	
		strcpy(params->m_model,  settings->value("head/model").toString().split(SEP)[1].toLocal8Bit());
		strcpy(params->m_vcomp,  settings->value("head/verifycompany").toString().split(SEP)[1].toLocal8Bit());
		strcpy(params->m_vperson,  settings->value("head/verifyperson").toString().split(SEP)[1].toLocal8Bit());
		strcpy(params->m_pickcode,  settings->value("head/pickcode").toString().split(SEP)[1].toLocal8Bit());
		params->m_grade = settings->value("head/grade").toString().split(SEP)[0].toInt() + 1;
		params->m_nflowpnt = settings->value("head/nflowpoint").toString().split(SEP)[1].toFloat();
	}
}

void ParaSetReader::readFlowPoints()
{
	params->total_fp = 0;
	QStringList heads = settings->childGroups();//�����ļ��е�����
	// ��i������
	for (int i=0; i<VERIFY_POINTS; i++)
	{
		QString head = "FlowPoint_" + QString::number(i);
		if (heads.contains(head))
		{
			if (params->file_timestamp ==  settings->value(head + "/timestamp").toLongLong())
			{
				params->total_fp++;
				params->fp_info[i].fp_freq =  settings->value(head + "/pumpfrequencey_"  + QString::number(i)).toFloat();
				params->fp_info[i].fp_upperlmt =  settings->value(head + "/upperflow_"  + QString::number(i)).toFloat();
				params->fp_info[i].fp_verify =  settings->value(head + "/verifyflow_"  + QString::number(i)).toFloat();
				params->fp_info[i].fp_quantity =  settings->value(head + "/flowquantity_"  + QString::number(i)).toFloat();
				params->fp_info[i].fp_valve =  settings->value(head + "/valve_"  + QString::number(i)).toInt();
				params->fp_info[i].fp_seq =  settings->value(head + "/seq_"  + QString::number(i)).toInt();
			}
		}
	}
}

void ParaSetReader::readBool()
{
	if (params->file_timestamp ==  settings->value("Bool/timestamp").toString().toLongLong())
	{
		params->bo_adjerror	= settings->value("Bool/adjusterror").toBool();
		params->bo_autopick = settings->value("Bool/autopick").toBool();
		params->bo_converify = settings->value("Bool/continuouscheck").toBool();
		params->bo_total = settings->value("Bool/Tqualitycheck").toBool();
		params->bo_writenum = settings->value("Bool/writemeternumber").toBool();
		params->bo_resetzero = settings->value("Bool/resetzero").toBool();
	}
}

void ParaSetReader::readOther()
{
	if (params->file_timestamp ==  settings->value("Other/timestamp").toString().toLongLong())
	{
		params->sc_flow =  settings->value("Other/flowsafecoefficient").toFloat();
		params->sc_thermal =  settings->value("Other/thermalsafecoefficient").toFloat();
		params->ex_time =  settings->value("Other/exhausttime").toFloat();
	}
}
/*
*�õ�������к�Ϊi����������Ϣ
*/
flow_point_info ParaSetReader::getFpBySeq(int i)
{
	//��������Ч������; �����ǰ������ļ춨����Ϊi, �򷵻ش���������Ϣ
	for (int j=0;j<params->total_fp;j++)
	{
		if (params->fp_info[j].fp_seq == i)
		{
			return params->fp_info[j];
		}
	}
	
	throw i;//�����������Ч�������û��ƥ��ļ춨����,��ô�˼춨���򲻴���
}