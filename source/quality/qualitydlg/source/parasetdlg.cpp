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

ParaSetDlg::ParaSetDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"ParaSetDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);

	flowPointVector();

	if (!m_basedb.startdb())
	{
		qFatal("数据库未打开");
	}
	m_meterStdNum = 0;
	m_meterStdPtr = NULL;
	m_meterTypeNum = 0;
	m_meterTypePtr = NULL;
	m_manuFacNum = 0;
	m_manuFacPtr = NULL;

	initUiData();//以数据库中的数据, 初始化comboBox的值

	char* runhome = getenv( "RUNHOME" );
#ifdef __unix
	sprintf( filename, "%s/ini/qualityParaSet.ini", runhome );
#else
	sprintf( filename, "%s\\ini\\qualityParaSet.ini", runhome );
#endif

	settings = new QSettings(filename, QSettings::IniFormat);
	settings->setIniCodec("GB2312");//解决向ini文件中写汉字乱码

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
	//表规格
	m_basedb.getMeterStandard(m_meterStdNum, m_meterStdPtr);
	for (int i=0; i<m_meterStdNum; i++)
	{
		qDebug()<<"id:"<<m_meterStdPtr[i].id<<",name:"<<m_meterStdPtr[i].name;
		ui.cmbStandard->insertItem(i, m_meterStdPtr[i].name);
	}

	//表类型
	m_basedb.getMeterType(m_meterTypeNum, m_meterTypePtr);
	for (int j=0; j<m_meterTypeNum; j++)
	{
		qDebug()<<"id:"<<m_meterTypePtr[j].id<<",desc:"<<QString::fromLocal8Bit(m_meterTypePtr[j].desc);
		ui.cmbCollectCode->insertItem(j, QString::fromLocal8Bit(m_meterTypePtr[j].desc)); //汉字编码
	}	

	//制造单位
	m_basedb.getManufacture(m_manuFacNum, m_manuFacPtr);
	for (int m=0; m<m_manuFacNum; m++)
	{
		qDebug()<<"id:"<<m_manuFacPtr[m].id<<",desc:"<<QString::fromLocal8Bit(m_manuFacPtr[m].desc);
		ui.cmbManufacture->insertItem(m, QString::fromLocal8Bit(m_manuFacPtr[m].desc)); //汉字编码
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
	qint64 file_tmstp = settings->value("Timestamp/timestamp").toLongLong();//读取文件时间戳
	QStringList heads = settings->childGroups();//配置文件中的组名
	// 第i流量点
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
				cBox_valves[i]->setCurrentIndex(settings->value(head + "/valve_"  + QString::number(i)).toInt());
				lineEdit_freqs[i]->setText(settings->value(head + "/pumpfrequencey_"  + QString::number(i)).toString());
				cBox_seqs[i]->setCurrentIndex(settings->value(head + "/seq_"  + QString::number(i)).toInt());
			}
		}
	}
}

void ParaSetDlg::installBool()
{
	//自动采集
	 ui.tBtn_autoPick_true->setChecked(settings->value("Bool/autopick").toBool()) ;
	 ui.tBtn_autoPick_false->setChecked(!(settings->value("Bool/autopick").toBool())) ;
	 //总量检定
	 ui.tBtn_totalverify_true->setChecked(settings->value("Bool/Tqualitycheck").toBool()) ;
	 ui.tBtn_totalverify_false->setChecked(!(settings->value("Bool/Tqualitycheck").toBool())) ;
	 //调整误差
	 ui.tBtn_adjustError_true->setChecked(settings->value("Bool/adjusterror").toBool()) ;
	 ui.tBtn_adjustError_false->setChecked(!(settings->value("Bool/adjusterror").toBool())) ;
	 //写表号
	 ui.tBtn_writeNum_true->setChecked(settings->value("Bool/writemeternumber").toBool()) ;
	 ui.tBtn_writeNum_false->setChecked(!(settings->value("Bool/writemeternumber").toBool())) ;
	 //连续检定
	 ui.tBtn_continuous_true->setChecked(settings->value("Bool/continuouscheck").toBool()) ;
	 ui.tBtn_continuous_false->setChecked(!(settings->value("Bool/continuouscheck").toBool())) ;
	 //初值回零
	 ui.tBtn_resetzero_true->setChecked(settings->value("Bool/resetzero").toBool());
	 ui.tBtn_resetzero_false->setChecked(!(settings->value("Bool/resetzero").toBool()));
}

void ParaSetDlg::installOther()
{
	ui.lineEdit_sc_flow->setText(settings->value("Other/flowsafecoefficient").toString());
	ui.lineEdit_sc_thermal->setText(settings->value("Other/thermalsafecoefficient").toString());
	ui.lineEdit_exTime->setText(settings->value("Other/exhausttime").toString());
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
* 保存第i流量点参数
* i: 界面上的第i个流量点, 而不是检定顺序 
*/
void ParaSetDlg::SaveFlowPoint(int i)
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
	settings->setIniCodec("GB2312");//解决向ini文件中写汉字乱码

	params =new Quality_Params;
	memset(params, 0, sizeof(QParams_PTR));
	initValveMap();
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

void ParaSetReader::initValveMap()
{
	valve_port_map.insert(0,"bigNo");
	valve_port_map.insert(1,"middle1No");
	valve_port_map.insert(2,"middle2No");
	valve_port_map.insert(3,"smallNo");
}

/*
* 读取配置文件的信息
*/
void ParaSetReader::readParamValues()
{
	//读取文件时间戳
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
		//读取基本信息
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
	params->total_fp = 0;//将流量点数目置为零
	QStringList heads = settings->childGroups();//配置文件中的组名
	// 第i流量点
	for (int i=0; i<VERIFY_POINTS; i++)
	{
		QString head = "FlowPoint_" + QString::number(i);//当前流量点的名字
		//如果组名中有当前检测的流量点, 则读取它的其他信息
		if (heads.contains(head))
		{
			//如果当前流量点的时间戳与文件保存时的时间戳一样, 那么它就是上次被保存过的信息
			//反之则不是上次保存的(可能是失效的配置), 将其丢弃
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
*得到检测序列号为i的流量点信息
*/
flow_point_info ParaSetReader::getFpBySeq(int i)
{
	//遍历各有效流量点; 如果当前流量点的检定次序为i, 则返回此流量点信息
	for (int j=0;j<params->total_fp;j++)
	{
		if (params->fp_info[j].fp_seq == i)
		{
			return params->fp_info[j];
		}
	}
	
	throw i;//如果遍历各有效流量点后没有匹配的检定次序,那么此检定次序不存在
}