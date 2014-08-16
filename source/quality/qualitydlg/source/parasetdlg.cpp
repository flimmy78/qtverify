/***********************************************
**  文件名:     parasetdlg.cpp
**  功能:       质量法-分量检定-参数设置界面
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/12
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/07 第一版
**  内容包含:
**  说明:
**  更新记录:
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QThread>
#include <QtCore/QSettings>
#include <QTextCodec>
#include <QtGui/QMessageBox>

#include "parasetdlg.h"
#include "commondefine.h"

/*************************************************************************
************************ParaSetDlg Start******************************
**************************************************************************/
ParaSetDlg::ParaSetDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"ParaSetDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);
	cBoxData_inited = false;
/**************************初始化数据库*****************************************/
	m_meterStdNum = 0;
	m_meterStdPtr = NULL;
	m_meterTypeNum = 0;
	m_meterTypePtr = NULL;
	m_manuFacNum = 0;
	m_manuFacPtr = NULL;
	initUiData();//以数据库中的数据, 初始化comboBox的值
/**************************初始化settings*****************************************/
	char filename[255];//配置文件的文件名
#ifdef __unix
	sprintf_s( filename, "%s/ini/qualityParaSet.ini", getenv( "RUNHOME" ) );
#else
	sprintf_s( filename, "%s\\ini\\qualityParaSet.ini", getenv( "RUNHOME" ) );
#endif
	settings = new QSettings(filename, QSettings::IniFormat);
	settings->setIniCodec("GB2312");//解决向ini文件中写汉字乱码
/**************************初始化lastParams*************************************/
	lastParams = new ParaSetReader();
	flowPointVector();
	
	installLastParams();//加载上次的配置信息

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

void ParaSetDlg::on_btnExit_clicked()
{
	this->close();
}

void ParaSetDlg::showEvent(QShowEvent * event)
{
// 	QMessageBox::warning(this, "warning", "showEvent");
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
	int idx = ui.cmbStandard->currentIndex();//表规格的当前索引值
	int count;//查询到的记录个数
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
	//表规格
	getMeterStandard(m_meterStdNum, m_meterStdPtr);
	for (int i=0; i<m_meterStdNum; i++)
	{
		qDebug()<<"id:"<<m_meterStdPtr[i].id<<",name:"<<m_meterStdPtr[i].name;
		ui.cmbStandard->insertItem(i, m_meterStdPtr[i].name);
	}

	//表类型
	getMeterType(m_meterTypeNum, m_meterTypePtr);
	for (int j=0; j<m_meterTypeNum; j++)
	{
		qDebug()<<"id:"<<m_meterTypePtr[j].id<<",desc:"<<QString::fromLocal8Bit(m_meterTypePtr[j].desc);
		ui.cmbCollectCode->insertItem(j, QString::fromLocal8Bit(m_meterTypePtr[j].desc)); //汉字编码
	}	

	//制造单位
	getManufacture(m_manuFacNum, m_manuFacPtr);
	for (int m=0; m<m_manuFacNum; m++)
	{
		qDebug()<<"id:"<<m_manuFacPtr[m].id<<",desc:"<<QString::fromLocal8Bit(m_manuFacPtr[m].desc);
		ui.cmbManufacture->insertItem(m, QString::fromLocal8Bit(m_manuFacPtr[m].desc)); //汉字编码
	}
	cBoxData_inited = true;//下拉条已初始化完毕
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
	// 第i流量点
	for (int i=0; i<VERIFY_POINTS; i++)
	{
		QString head = "FlowPoint_" + QString::number(i);
		//如果检定次序号大于0, 则此流量点参与检测
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
	//自动采集
	 ui.tBtn_autoPick_true->setChecked(lastParams->m_params->bo_autopick) ;
	 ui.tBtn_autoPick_false->setChecked(!(lastParams->m_params->bo_autopick)) ;
	 //总量检定
	 ui.tBtn_totalverify_true->setChecked(lastParams->m_params->bo_total) ;
	 ui.tBtn_totalverify_false->setChecked(!(lastParams->m_params->bo_total)) ;
	 //调整误差
	 ui.tBtn_adjustError_true->setChecked(lastParams->m_params->bo_adjerror) ;
	 ui.tBtn_adjustError_false->setChecked(!(lastParams->m_params->bo_adjerror)) ;
	 //写表号
	 ui.tBtn_writeNum_true->setChecked(lastParams->m_params->bo_writenum) ;
	 ui.tBtn_writeNum_false->setChecked(!(lastParams->m_params->bo_writenum)) ;
	 //连续检定
	 ui.tBtn_continuous_true->setChecked(lastParams->m_params->bo_converify) ;
	 ui.tBtn_continuous_false->setChecked(!(lastParams->m_params->bo_converify)) ;
	 //初值回零
	 ui.tBtn_resetzero_true->setChecked(lastParams->m_params->bo_resetzero);
	 ui.tBtn_resetzero_false->setChecked(!(lastParams->m_params->bo_resetzero));
}

void ParaSetDlg::installOther()
{
	ui.lineEdit_sc_flow->setText(QString::number(lastParams->m_params->sc_flow));
	ui.lineEdit_sc_thermal->setText(QString::number(lastParams->m_params->sc_thermal));
	ui.lineEdit_exTime->setText(QString::number(lastParams->m_params->ex_time));
}

/*将各流量点中, 相似功能的控件加入数组, 便于使用; 
**这就好比界面上的一组控件代表一个关系表(关系型数据库)中的一条记录, 
**而每个控件代表记录中的不同的域
*/
void ParaSetDlg::flowPointVector()
{
	//上限流量点
	lineEdit_uppers.append(ui.lineEdit_Upper_1);
	lineEdit_uppers.append(ui.lineEdit_Upper_2);
	lineEdit_uppers.append(ui.lineEdit_Upper_3);
	lineEdit_uppers.append(ui.lineEdit_Upper_4);
	//检测流量点
	lineEdit_flows.append(ui.lnEdit_Flow1);
	lineEdit_flows.append(ui.lnEdit_Flow2);
	lineEdit_flows.append(ui.lnEdit_Flow3);
	lineEdit_flows.append(ui.lnEdit_Flow4);
	//检定量
	lineEdit_quantites.append(ui.lineEdit_Quantity_1);
	lineEdit_quantites.append(ui.lineEdit_Quantity_2);
	lineEdit_quantites.append(ui.lineEdit_Quantity_3);
	lineEdit_quantites.append(ui.lineEdit_Quantity_4);
	//控制阀
	cBox_valves.append(ui.cBox_Valve_1);
	cBox_valves.append(ui.cBox_Valve_2);
	cBox_valves.append(ui.cBox_Valve_3);
	cBox_valves.append(ui.cBox_Valve_4);
	//水泵频率
	lineEdit_freqs.append(ui.lineEdit_freq_1);
	lineEdit_freqs.append(ui.lineEdit_freq_2);
	lineEdit_freqs.append(ui.lineEdit_freq_3);
	lineEdit_freqs.append(ui.lineEdit_freq_4);
	//检定次序
	cBox_seqs.append((ui.cBox_seq_1));
	cBox_seqs.append((ui.cBox_seq_2));
	cBox_seqs.append((ui.cBox_seq_3));
	cBox_seqs.append((ui.cBox_seq_4));
}

void ParaSetDlg::on_btnSave_clicked()
{
	//先检查选定次序的合法性
	if (!chkSeq())
	{
		QMessageBox::about(NULL, "illegal", "verify sequence is invalid!");
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
	QMessageBox::about(NULL, "OK", "Saving configurations successfully!");
	emit saveSuccessSignal();
}

/*
* 检查被用户选定的检定序列号是否合法
* 检定序列里必须要有1, 
* 且是以1起始, 中间不间断的自然数序列
* 比如: [1]; [1, 2]; [1, 2, 3]; 依此类推.
* 假设有一正整数序列
* 设n为其最大元素值
* 若此序列无重复项,
* 且n与序列的元素个数相等
* 那么这个序列一定是以1起始,以n终止的自然数列
*/
bool ParaSetDlg::chkSeq()
{
	int max_seq = 0;//最大的次序号
	int total_seqs = 0;//非零的检定次序号的个数
	QVector<int> repeat_seq;//已发现的元素序列

	for (int i=0; i < VERIFY_POINTS; i++)
	{
		int current_seq = cBox_seqs[i]->currentIndex();
		//挑出最大的次序号
		if (max_seq < current_seq)
		{
			max_seq = current_seq;
		}
		
		if (current_seq > 0)
		{
			total_seqs ++;//计算非0元素的个数
			//如果存在*重复*的!*非零元素*!, 则返回false;否则将当前元素加入已发现的元素序列
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
	//如果最大的次序号为0, 则认为用户漏选了检定次序
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
* 保存第i流量点参数
* i: 界面上的第i个流量点, 而不是检定顺序 
*/
void ParaSetDlg::SaveFlowPoint()
{
	for (int i=0; i < VERIFY_POINTS; i++)
	{
		//只保存检定顺序 > 1 的流量点
		if(cBox_seqs[i]->currentIndex() > 0)
		{
			settings->beginGroup("FlowPoint_" +  QString::number(i, 10));
			settings->setValue("timestamp",timestamp);
			settings->setValue("upperflow_" +  QString::number(i, 10), lineEdit_uppers[i]->text());//上限流量值
			settings->setValue("verifyflow_" +  QString::number(i, 10), lineEdit_flows[i]->text());//流量点
			settings->setValue("flowquantity_" +  QString::number(i, 10), lineEdit_quantites[i]->text());//检定水量
			settings->setValue("pumpfrequencey_" +  QString::number(i, 10), lineEdit_freqs[i]->text());//变频器频率
			settings->setValue("valve_" +  QString::number(i, 10), cBox_valves[i]->currentIndex());//对应的阀门
			settings->setValue("seq_" +  QString::number(i, 10), cBox_seqs[i]->currentIndex());//检定顺序
			settings->endGroup();
		}
	}
}

void ParaSetDlg::SaveBool()
{
	settings->beginGroup("Bool");
	settings->setValue("timestamp",timestamp);
	settings->setValue("autopick", ui.tBtn_autoPick_true->isChecked() );//是否自动采集
	settings->setValue("Tqualitycheck", ui.tBtn_totalverify_true->isChecked() );//是否总量检定
	settings->setValue("adjusterror", ui.tBtn_adjustError_true->isChecked() );//是否修正误差
	settings->setValue("writemeternumber", ui.tBtn_writeNum_true->isChecked() );//是否写表号
	settings->setValue("continuouscheck", ui.tBtn_continuous_true->isChecked() );//是否连续检定
	settings->setValue("resetzero", ui.tBtn_resetzero_true->isChecked() );//是否初值回零
	settings->endGroup();
}

void ParaSetDlg::SaveOther()
{
	settings->beginGroup("Other");
	settings->setValue("timestamp",timestamp);
	settings->setValue("flowsafecoefficient", ui.lineEdit_sc_flow->text());//流量安全系数
	settings->setValue("thermalsafecoefficient", ui.lineEdit_sc_thermal->text());//热量安全系数
	settings->setValue("exhausttime", ui.lineEdit_exTime->text());//排气时间
	settings->endGroup();
}
/*************************************************************************
************************ParaSetDlg End*******************************
**************************************************************************/

/*************************************************************************
************************ParaSetReader Start*************************
**************************************************************************/
ParaSetReader::ParaSetReader()
{
	initValveMap();
	readIniFile();
	m_params =new Quality_Params_STR;
	memset(m_params, 0, sizeof(Quality_Params_PTR));
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
	char filename[255];
	char* runhome = getenv( "RUNHOME" );

	//检定前的参数文件
#ifdef __unix
	sprintf_s( filename, "%s/ini/qualityParaSet.ini", runhome );
#else
	sprintf_s( filename, "%s\\ini\\qualityParaSet.ini", runhome );
#endif
	m_settings = new QSettings(filename, QSettings::IniFormat);
	m_settings->setIniCodec("GB2312");//解决向ini文件中写汉字乱码

	//端口号的配置文件
#ifdef __unix
	sprintf_s( filename, "%s/ini/portset.ini", runhome );
#else
	sprintf_s( filename, "%s\\ini\\portset.ini", runhome );
#endif
	m_portInfo = new QSettings(filename, QSettings::IniFormat);
	m_portInfo->setIniCodec("GB2312");

	return true;
}

Quality_Params_PTR ParaSetReader::getParams()
{
	readIniFile();
	readParamValues();
	return m_params;
}

/*
* 将配置文件保存的comboBox索引号与
* 端口字段对应
*/
void ParaSetReader::initValveMap()
{
	m_valvePortMap.insert(0,"bigNo");
	m_valvePortMap.insert(1,"middle1No");
	m_valvePortMap.insert(2,"middle2No");
	m_valvePortMap.insert(3,"smallNo");
}

/*
* 读取配置文件的信息
*/
void ParaSetReader::readParamValues()
{
	//读取文件时间戳
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
		//读取基本信息
		m_params->m_timestamp=m_settings->value("head/timestamp").toLongLong();
		m_params->m_stand = m_settings->value("head/standard").toInt();
		/////////////////////读取最大检表数/////////////////////////
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
	m_params->total_fp = 0;//将流量点数目置为零
	QStringList heads = m_settings->childGroups();//配置文件中的组名
	// 第i流量点
	for (int i=0; i<VERIFY_POINTS; i++)
	{
		QString head = "FlowPoint_" + QString::number(i);//当前流量点的名字
		//如果组名中有当前检测的流量点, 则读取它的其他信息
		if (heads.contains(head))
		{
			//如果当前流量点的时间戳与文件保存时的时间戳一样, 那么它就是上次被保存过的信息
			//反之则不是上次保存的(可能是失效的配置), 将其丢弃
			if (m_params->file_timestamp ==  m_settings->value(head + "/timestamp").toLongLong())
			{
				m_params->total_fp++;
				m_params->fp_info[i].fp_timestamp = m_params->file_timestamp;
				m_params->fp_info[i].fp_freq =  m_settings->value(head + "/pumpfrequencey_"  + QString::number(i)).toFloat();
				m_params->fp_info[i].fp_upperlmt =  m_settings->value(head + "/upperflow_"  + QString::number(i)).toFloat();
				m_params->fp_info[i].fp_verify =  m_settings->value(head + "/verifyflow_"  + QString::number(i)).toFloat();
				m_params->fp_info[i].fp_quantity =  m_settings->value(head + "/flowquantity_"  + QString::number(i)).toFloat();
				int idx=m_settings->value(head + "/valve_"  + QString::number(i)).toInt();//获取参数配置文件中保存的阀门comboBox的索引
				m_params->fp_info[i].fp_valve =  m_portInfo->value("Relay/" + m_valvePortMap[idx]).toInt();//获取阀门端口号
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
		m_params->bo_total = m_settings->value("Bool/Tqualitycheck").toBool();
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
*得到检测序列号为i的流量点信息,i从1开始？
*/
Flow_Point_Info ParaSetReader::getFpBySeq(int i)
{
	//遍历各有效流量点; 如果当前流量点的检定次序为i, 则返回此流量点信息
	for (int j=0;j<m_params->total_fp;j++)
	{
		if (m_params->fp_info[j].fp_seq == i)
		{
			return m_params->fp_info[j];
		}
	}
	
	throw i;//如果遍历各有效流量点后没有匹配的检定次序,那么此检定次序不存在
}
/*************************************************************************
************************ParaSetReader End**************************
**************************************************************************/