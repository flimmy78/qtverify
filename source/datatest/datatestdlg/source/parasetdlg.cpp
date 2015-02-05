/***********************************************
**  �ļ���:     parasetdlg.cpp
**  ����:       ������-�����춨-�������ý���
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/12
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
#include <QThread>
#include <QtCore/QSettings>
#include <QTextCodec>
#include <QtGui/QMessageBox>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include <QtCore/QProcessEnvironment>

#include "parasetdlg.h"
#include "commondefine.h"
#include "qtexdb.h"

ParaSetDlg::ParaSetDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"ParaSetDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);
	cBoxData_inited = false;
	
	m_meterStdNum = 0;
	m_meterStdPtr = NULL;
	m_meterTypeNum = 0;
	m_meterTypePtr = NULL;
	m_manuFacNum = 0;
	m_manuFacPtr = NULL;
	initUiData();//�����ݿ��е�����, ��ʼ��comboBox��ֵ

	QString filename;//�����ļ����ļ���
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");
#ifdef __unix
	filename = runhome + "\/ini\/verifyparaset.ini";
#else
	filename = runhome + "\\ini\\verifyparaset.ini";
#endif
	settings = new QSettings(filename, QSettings::IniFormat);
	settings->setIniCodec("GB2312");//�����ini�ļ���д��������

	lastParams = new ParaSetReader();
	flowPointVector();
	installLastParams();//�����ϴε�������Ϣ
}

ParaSetDlg::~ParaSetDlg()
{
	qDebug()<<"!!! ParaSetDlg destructor";
}

void ParaSetDlg::on_btnExit_clicked()
{
	this->close();
}

void ParaSetDlg::showEvent(QShowEvent * event)
{
// 	QMessageBox::warning(this, tr("Warning"), tr("showEvent"));
}

void ParaSetDlg::closeEvent(QCloseEvent * event)
{
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
	if (lastParams)
	{
		delete lastParams;
		lastParams=NULL;
	}

}

void ParaSetDlg::on_cmbStandard_currentIndexChanged()
{
	qDebug()<<"on_cmbStandard_currentIndexChanged is called; currentIndex is :"<< ui.cmbStandard->currentIndex();
	if (cBoxData_inited)
	{
		installDftDBinfo();
	}
}

void ParaSetDlg::installDftDBinfo()
{
	int idx = ui.cmbStandard->currentIndex();//����ĵ�ǰ����ֵ
	int count;//��ѯ���ļ�¼����
	DftDbInfo_PTR dbinfo_ptr;
	if (getDftDBinfo(count, dbinfo_ptr, idx))
	{
		ui.cmbFlow->setCurrentIndex(dbinfo_ptr[0].stand_id);
		for(int i=0; i < VERIFY_POINTS; i++)
		{
			lineEdit_uppers[i]->setText(QString::number(dbinfo_ptr[i].upper_flow));
			lineEdit_flows[i]->setText(QString::number(dbinfo_ptr[i].v_flow));
			lineEdit_quantites[i]->setText(QString::number(dbinfo_ptr[i].v_quan));
			lineEdit_freqs[i]->setText(QString::number(dbinfo_ptr[i].pump_freq));
			cBox_valves[i]->setCurrentIndex(dbinfo_ptr[i].vale_num);
			cBox_seqs[i]->setCurrentIndex(dbinfo_ptr[i].seq);
		}
	}
}

void ParaSetDlg::initUiData()
{
	//����
	getMeterStandard(m_meterStdNum, m_meterStdPtr);
	for (int i=0; i<m_meterStdNum; i++)
	{
		qDebug()<<"id:"<<m_meterStdPtr[i].id<<",name:"<<m_meterStdPtr[i].name;
		ui.cmbStandard->insertItem(i, m_meterStdPtr[i].name);
	}

	//������
	getMeterType(m_meterTypeNum, m_meterTypePtr);
	for (int j=0; j<m_meterTypeNum; j++)
	{
		qDebug()<<"id:"<<m_meterTypePtr[j].id<<",desc:"<<QString::fromLocal8Bit(m_meterTypePtr[j].desc);
		ui.cmbCollectCode->insertItem(j, QString::fromLocal8Bit(m_meterTypePtr[j].desc)); //���ֱ���
	}	

	//���쵥λ
	getManufacture(m_manuFacNum, m_manuFacPtr);
	for (int m=0; m<m_manuFacNum; m++)
	{
		qDebug()<<"id:"<<m_manuFacPtr[m].id<<",desc:"<<QString::fromLocal8Bit(m_manuFacPtr[m].desc);
		ui.cmbManufacture->insertItem(m, QString::fromLocal8Bit(m_manuFacPtr[m].desc)); //���ֱ���
	}

	//�ͼ쵥λ
	int col_id = 0;
	QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);  
	model->setTable("T_Verify_Dept");  
	model->setRelation(col_id, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));  
	//QComboBox��QListWidget������,��Ϊ����һ���ڲ�ģ��ȥ��������������Ŀ,�����������Լ�����ģ�ʹ����Ǹ��Դ���ģ�͡�
	//����QSqlRelationalTableModelʹ�õĹ�ϵģ�ͣ����ģ��������,����ָ����Ͽ�Ӧ����ʾ��һ��   
	QSqlTableModel *relationModel = model->relationModel(col_id); // ����ID   
	ui.cmbVerifyCompany->setModel(relationModel);  
	ui.cmbVerifyCompany->setModelColumn(relationModel->fieldIndex("F_Desc")); // ʹ���ֶ����õ���ȷ�ı�������,��ʹ��Ͽ���ʾ������  

	//���Ա
	int col_id1 = 0;
	QSqlRelationalTableModel *model1 = new QSqlRelationalTableModel(this);  
	model1->setTable("T_User_Def_Tab");  
	model1->setRelation(col_id1, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));  
	QSqlTableModel *relationModel1 = model1->relationModel(col_id1);   
	ui.cmbVerifyPerson->setModel(relationModel1);  
	ui.cmbVerifyPerson->setModelColumn(relationModel1->fieldIndex("F_Desc"));

	//�ͺ�
	int col_id2 = 0;
	QSqlRelationalTableModel *model2 = new QSqlRelationalTableModel(this);  
	model2->setTable("T_Meter_Model");  
	model2->setRelation(col_id2, QSqlRelation("T_Meter_Model","F_ID","F_Desc"));  
	QSqlTableModel *relationModel2 = model2->relationModel(col_id2);   
	ui.cmbModel->setModel(relationModel2);  
	ui.cmbModel->setModelColumn(relationModel2->fieldIndex("F_Desc")); 

	cBoxData_inited = true;//�������ѳ�ʼ�����
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
	ui.cmbStandard->setCurrentIndex(lastParams->m_params->m_stand);
	ui.cmbCollectCode->setCurrentIndex(lastParams->m_params->m_pickcode);
	ui.cmbManufacture->setCurrentIndex(lastParams->m_params->m_manufac);
	ui.cmbGrade->setCurrentIndex(lastParams->m_params->m_grade-1);
	ui.cmbModel->setCurrentIndex(lastParams->m_params->m_model);
	ui.cmbVerifyCompany->setCurrentIndex(lastParams->m_params->m_vcomp);
	ui.cmbVerifyPerson->setCurrentIndex(lastParams->m_params->m_vperson);
	ui.cmbFlow->setCurrentIndex(lastParams->m_params->m_nflowpnt);
}

void ParaSetDlg::installFlowPoint()
{
	// ��i������
	for (int i=0; i<VERIFY_POINTS; i++)
	{
		QString head = "FlowPoint_" + QString::number(i);
		//����춨����Ŵ���0, ��������������
		if (lastParams->m_params->fp_info[i].fp_seq > 0)
		{
				lineEdit_uppers[i]->setText(QString::number(lastParams->m_params->fp_info[i].fp_upperlmt));
				lineEdit_flows[i]->setText(QString::number(lastParams->m_params->fp_info[i].fp_verify));
				lineEdit_quantites[i]->setText(QString::number(lastParams->m_params->fp_info[i].fp_quantity));
				cBox_valves[i]->setCurrentIndex(settings->value(head + "/valve_"  + QString::number(i)).toInt());
				lineEdit_freqs[i]->setText(QString::number(lastParams->m_params->fp_info[i].fp_freq));
				cBox_seqs[i]->setCurrentIndex(lastParams->m_params->fp_info[i].fp_seq);
		}
	}
}

void ParaSetDlg::installBool()
{
	//�Զ��ɼ�
	 ui.tBtn_autoPick_true->setChecked(lastParams->m_params->bo_autopick) ;
	 ui.tBtn_autoPick_false->setChecked(!(lastParams->m_params->bo_autopick)) ;
	 //�������
	 ui.tBtn_adjustError_true->setChecked(lastParams->m_params->bo_adjerror) ;
	 ui.tBtn_adjustError_false->setChecked(!(lastParams->m_params->bo_adjerror)) ;
	 //д���
	 ui.tBtn_writeNum_true->setChecked(lastParams->m_params->bo_writenum) ;
	 ui.tBtn_writeNum_false->setChecked(!(lastParams->m_params->bo_writenum)) ;
	 //�����춨
	 ui.tBtn_continuous_true->setChecked(lastParams->m_params->bo_converify) ;
	 ui.tBtn_continuous_false->setChecked(!(lastParams->m_params->bo_converify)) ;
	 //��ֵ����
	 ui.tBtn_resetzero_true->setChecked(lastParams->m_params->bo_resetzero);
	 ui.tBtn_resetzero_false->setChecked(!(lastParams->m_params->bo_resetzero));
}

void ParaSetDlg::installOther()
{
	ui.lineEdit_sc_flow->setText(QString::number(lastParams->m_params->sc_flow));
	ui.lineEdit_sc_thermal->setText(QString::number(lastParams->m_params->sc_thermal));
	ui.lineEdit_exTime->setText(QString::number(lastParams->m_params->ex_time));
}

/*
** ������������, ���ƹ��ܵĿؼ���������, ����ʹ��; 
   ��ͺñȽ����ϵ�һ��ؼ�����һ����ϵ��(��ϵ�����ݿ�)�е�һ����¼, 
   ��ÿ���ؼ������¼�еĲ�ͬ����
*/
void ParaSetDlg::flowPointVector()
{
	//����������
	lineEdit_uppers.append(ui.lineEdit_Upper_1);
	lineEdit_uppers.append(ui.lineEdit_Upper_2);
	lineEdit_uppers.append(ui.lineEdit_Upper_3);
	lineEdit_uppers.append(ui.lineEdit_Upper_4);
	//���������
	lineEdit_flows.append(ui.lnEdit_Flow1);
	lineEdit_flows.append(ui.lnEdit_Flow2);
	lineEdit_flows.append(ui.lnEdit_Flow3);
	lineEdit_flows.append(ui.lnEdit_Flow4);
	//�춨��
	lineEdit_quantites.append(ui.lineEdit_Quantity_1);
	lineEdit_quantites.append(ui.lineEdit_Quantity_2);
	lineEdit_quantites.append(ui.lineEdit_Quantity_3);
	lineEdit_quantites.append(ui.lineEdit_Quantity_4);
	//���Ʒ�
	cBox_valves.append(ui.cBox_Valve_1);
	cBox_valves.append(ui.cBox_Valve_2);
	cBox_valves.append(ui.cBox_Valve_3);
	cBox_valves.append(ui.cBox_Valve_4);
	//ˮ��Ƶ��
	lineEdit_freqs.append(ui.lineEdit_freq_1);
	lineEdit_freqs.append(ui.lineEdit_freq_2);
	lineEdit_freqs.append(ui.lineEdit_freq_3);
	lineEdit_freqs.append(ui.lineEdit_freq_4);
	//�춨����
	cBox_seqs.append((ui.cBox_seq_1));
	cBox_seqs.append((ui.cBox_seq_2));
	cBox_seqs.append((ui.cBox_seq_3));
	cBox_seqs.append((ui.cBox_seq_4));
}

void ParaSetDlg::on_btnSave_clicked()
{
	//�ȼ��ѡ������ĺϷ���
	if (!chkSeq())
	{
		QMessageBox::warning(this, tr("Warning"), tr("verify sequence is invalid!"));
		return;
	}

	QStringList heads = settings->childGroups();
	timestamp = QDateTime::currentMSecsSinceEpoch();
	if (heads.contains("Timestamp"))
	{
		settings->setValue("Timestamp/timestamp",timestamp);
	} 
	else
	{
		settings->beginGroup("Timestamp");
		settings->setValue("Timestamp/timestamp",timestamp);
		settings->endGroup();
	}

	SaveHead();
	SaveFlowPoint();
	SaveBool();
	SaveOther();
	QMessageBox::information(this, tr("OK"), tr("Saving configurations successfully!"));
	emit saveSuccessSignal();
}

/*
** ��鱻�û�ѡ���ļ춨���к��Ƿ�Ϸ�
   �춨���������Ҫ��1, 
   ������1��ʼ, �м䲻��ϵ���Ȼ������
   ����: [1]; [1, 2]; [1, 2, 3]; ��������.
   ������һ����������
   ��nΪ�����Ԫ��ֵ
   �����������ظ���,
   ��n�����е�Ԫ�ظ������
   ��ô�������һ������1��ʼ,��n��ֹ����Ȼ����
*/
bool ParaSetDlg::chkSeq()
{
	int max_seq = 0;//���Ĵ����
	int total_seqs = 0;//����ļ춨����ŵĸ���
	QVector<int> repeat_seq;//�ѷ��ֵ�Ԫ������

	for (int i=0; i < VERIFY_POINTS; i++)
	{
		int current_seq = cBox_seqs[i]->currentIndex();

		if (current_seq > 0)//�������е���Ȼ�����в�������Ԫ��
		{
			//��������!*����Ԫ��*!�����
			if (max_seq < current_seq)
			{
				max_seq = current_seq;
			}

			total_seqs ++;//����!*����Ԫ��*!�ĸ���
			//�������*�ظ�*��!*����Ԫ��*!, �򷵻�false;���򽫵�ǰԪ�ؼ����ѷ��ֵ�Ԫ������
			if (repeat_seq.contains(current_seq))
			{
				return false;
			}
			else
			{
				repeat_seq.append(current_seq);
			}
		}
	}
	//������Ĵ����Ϊ0, ����Ϊ�û�©ѡ�˼춨����
	if (max_seq == 0)
	{
		return false;
	}

	return (max_seq == total_seqs);
}

void ParaSetDlg::SaveHead()
{
	settings->beginGroup("head");
	settings->setValue("timestamp",timestamp);
	settings->setValue("standard", ui.cmbStandard->currentIndex());
	settings->setValue("metertype", ui.cmbCollectCode->currentIndex());
	settings->setValue("manufacture", ui.cmbManufacture->currentIndex());
	settings->setValue("grade", ui.cmbGrade->currentIndex()+1);
	settings->setValue("model", ui.cmbModel->currentIndex());
	settings->setValue("verifycompany", ui.cmbVerifyCompany->currentIndex());
	settings->setValue("verifyperson", ui.cmbVerifyPerson->currentIndex());
	settings->setValue("pickcode", ui.cmbCollectCode->currentIndex());
	settings->setValue("nflowpoint", ui.cmbFlow->currentIndex());
	settings->endGroup();
}

/*
** �����i���������
** i: �����ϵĵ�i��������, �����Ǽ춨˳�� 
*/
void ParaSetDlg::SaveFlowPoint()
{
	for (int i=0; i < VERIFY_POINTS; i++)
	{
		//ֻ����춨˳�� > 1 ��������
		if(cBox_seqs[i]->currentIndex() > 0)
		{
			settings->beginGroup("FlowPoint_" +  QString::number(i, 10));
			settings->setValue("timestamp",timestamp);
			settings->setValue("upperflow_" +  QString::number(i, 10), lineEdit_uppers[i]->text());//��������ֵ
			settings->setValue("verifyflow_" +  QString::number(i, 10), lineEdit_flows[i]->text());//������
			settings->setValue("flowquantity_" +  QString::number(i, 10), lineEdit_quantites[i]->text());//�춨ˮ��
			settings->setValue("pumpfrequencey_" +  QString::number(i, 10), lineEdit_freqs[i]->text());//��Ƶ��Ƶ��
			settings->setValue("valve_" +  QString::number(i, 10), cBox_valves[i]->currentIndex());//��Ӧ�ķ���
			settings->setValue("seq_" +  QString::number(i, 10), cBox_seqs[i]->currentIndex());//�춨˳��
			settings->endGroup();
		}
	}
}

void ParaSetDlg::SaveBool()
{
	settings->beginGroup("Bool");
	settings->setValue("timestamp",timestamp);
	settings->setValue("autopick", ui.tBtn_autoPick_true->isChecked() );//�Ƿ��Զ��ɼ�
	settings->setValue("adjusterror", ui.tBtn_adjustError_true->isChecked() );//�Ƿ��������
	settings->setValue("writemeternumber", ui.tBtn_writeNum_true->isChecked() );//�Ƿ�д���
	settings->setValue("continuouscheck", ui.tBtn_continuous_true->isChecked() );//�Ƿ������춨
	settings->setValue("resetzero", ui.tBtn_resetzero_true->isChecked() );//�Ƿ��ֵ����
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

/*************************************************************************
************************ParaSetReader Start*************************
**************************************************************************/
ParaSetReader::ParaSetReader()
{
	initValveMap();
	readIniFile();
	m_params =new Verify_Params_STR;
	memset(m_params, 0, sizeof(Verify_Params_PTR));
	readParamValues();
}

ParaSetReader::~ParaSetReader()
{
	if (m_settings)
	{
		delete m_settings;
		m_settings = NULL;
	}
	if (m_params)
	{
		delete m_params;
		m_params=NULL;
	}
}

int ParaSetReader::readIniFile()
{
	QString filename;
	QString runhome = QProcessEnvironment::systemEnvironment().value("RUNHOME");

	//�춨ǰ�Ĳ����ļ�
#ifdef __unix
	filename = runhome + "\/ini\/verifyparaset.ini";
#else
	filename = runhome + "\\ini\\verifyparaset.ini";
#endif
	m_settings = new QSettings(filename, QSettings::IniFormat);
	m_settings->setIniCodec("GB2312");//�����ini�ļ���д��������

	//�˿ںŵ������ļ�
#ifdef __unix
	filename = runhome + "\/ini\/portset.ini";
#else
	filename = runhome + "\\ini\\portset.ini";
#endif
	m_portInfo = new QSettings(filename, QSettings::IniFormat);
	m_portInfo->setIniCodec("GB2312");

	return true;
}

Verify_Params_PTR ParaSetReader::getParams()
{
	readIniFile();
	readParamValues();
	return m_params;
}

/*
** �������ļ������comboBox��������
** �˿��ֶζ�Ӧ
*/
void ParaSetReader::initValveMap()
{
	m_valvePortMap.insert(0,"bigNo");
	m_valvePortMap.insert(1,"middle1No");
	m_valvePortMap.insert(2,"middle2No");
	m_valvePortMap.insert(3,"smallNo");
}

/*
** ��ȡ�����ļ�����Ϣ
*/
void ParaSetReader::readParamValues()
{
	//��ȡ�ļ�ʱ���
	m_params->file_timestamp = m_settings->value("Timestamp/timestamp").toString().toLongLong();
	readHead();
	readBool();
	readOther();
	readFlowPoints();
}

void ParaSetReader::readHead()
{
	if (m_params->file_timestamp ==  m_settings->value("head/timestamp").toString().toLongLong())
	{
		//��ȡ������Ϣ
		m_params->m_timestamp=m_settings->value("head/timestamp").toLongLong();
		m_params->m_stand = m_settings->value("head/standard").toInt();
		/////////////////////��ȡ�������/////////////////////////
		m_params->m_maxMeters = getMaxMeterByIdx(m_params->m_stand);

		///////////////////////////////////////////////////////////////////
		m_params->m_type = m_settings->value("head/metertype").toInt();
		m_params->m_manufac = m_settings->value("head/manufacture").toInt();	
		m_params->m_model = m_settings->value("head/model").toInt();
		m_params->m_vcomp = m_settings->value("head/verifycompany").toInt();
		m_params->m_vperson = m_settings->value("head/verifyperson").toInt();
		m_params->m_pickcode = m_settings->value("head/pickcode").toInt();
		m_params->m_grade = m_settings->value("head/grade").toInt();
		m_params->m_nflowpnt = m_settings->value("head/nflowpoint").toInt();
	}
}

void ParaSetReader::readFlowPoints()
{
	m_params->total_fp = 0;//����������Ŀ��Ϊ��
	QStringList heads = m_settings->childGroups();//�����ļ��е�����
	// ��i������
	for (int i=0; i<VERIFY_POINTS; i++)
	{
		QString head = "FlowPoint_" + QString::number(i);//��ǰ�����������
		//����������е�ǰ����������, ���ȡ����������Ϣ
		if (heads.contains(head))
		{
			//�����ǰ�������ʱ������ļ�����ʱ��ʱ���һ��, ��ô�������ϴα����������Ϣ
			//��֮�����ϴα����(������ʧЧ������), ���䶪��
			if (m_params->file_timestamp ==  m_settings->value(head + "/timestamp").toLongLong())
			{
				m_params->total_fp++;
				m_params->fp_info[i].fp_timestamp = m_params->file_timestamp;
				m_params->fp_info[i].fp_freq =  m_settings->value(head + "/pumpfrequencey_"  + QString::number(i)).toFloat();
				m_params->fp_info[i].fp_upperlmt =  m_settings->value(head + "/upperflow_"  + QString::number(i)).toFloat();
				m_params->fp_info[i].fp_verify =  m_settings->value(head + "/verifyflow_"  + QString::number(i)).toFloat();
				m_params->fp_info[i].fp_quantity =  m_settings->value(head + "/flowquantity_"  + QString::number(i)).toFloat();
				int idx=m_settings->value(head + "/valve_"  + QString::number(i)).toInt();//��ȡ���������ļ��б���ķ���comboBox������
				m_params->fp_info[i].fp_valve =  m_portInfo->value("Relay/" + m_valvePortMap[idx]).toInt();//��ȡ���Ŷ˿ں�
				m_params->fp_info[i].fp_seq =  m_settings->value(head + "/seq_"  + QString::number(i)).toInt();
			}
		}
	}
}

void ParaSetReader::readBool()
{
	if (m_params->file_timestamp ==  m_settings->value("Bool/timestamp").toString().toLongLong())
	{
		m_params->bo_timestamp = m_settings->value("Bool/timestamp").toLongLong();
		m_params->bo_adjerror	= m_settings->value("Bool/adjusterror").toBool();
		m_params->bo_autopick = m_settings->value("Bool/autopick").toBool();
		m_params->bo_converify = m_settings->value("Bool/continuouscheck").toBool();
		m_params->bo_writenum = m_settings->value("Bool/writemeternumber").toBool();
		m_params->bo_resetzero = m_settings->value("Bool/resetzero").toBool();
	}
}

void ParaSetReader::readOther()
{
	if (m_params->file_timestamp ==  m_settings->value("Other/timestamp").toString().toLongLong())
	{
		m_params->oth_timestamp = m_settings->value("Other/timestamp").toLongLong();
		m_params->sc_flow =  m_settings->value("Other/flowsafecoefficient").toFloat();
		m_params->sc_thermal =  m_settings->value("Other/thermalsafecoefficient").toFloat();
		m_params->ex_time =  m_settings->value("Other/exhausttime").toFloat();
	}
}

/*
** �õ�������к�Ϊi����������Ϣ,i��1��ʼ,
** ��m_params->total_fp����
** �쳣: i ����[1...m_params->total_fp]֮��
*/
Flow_Point_Info ParaSetReader::getFpBySeq(int i)
{
	//��������Ч������; �����ǰ������ļ춨����Ϊi, �򷵻ش���������Ϣ
	for (int j=0; j < VERIFY_POINTS; j++)
	{
		if (m_params->fp_info[j].fp_seq == i)
		{
			return m_params->fp_info[j];
		}
	}
	
	throw i;//�����������Ч�������û��ƥ��ļ춨����,��ô�˼춨���򲻴���
}