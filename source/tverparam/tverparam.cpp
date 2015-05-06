#include <QtGui/QTreeWidget>
#include "algorithm.h"
#include "qtexdb.h"
#include "tverparam.h"

tverparamDlg::tverparamDlg(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	m_PlaParamParamDlg = NULL;
	connect(m_PlaParamParamDlg, SIGNAL(configureOk()), this,SLOT(disableConfigBtn()));
	connect(this, SIGNAL(firstTmpVerOk()), this, SLOT(firstTmpVerOk_slot()));
	connect(this, SIGNAL(secondTmpVerOk()), this, SLOT(secondTmpVerOk_slot()));
	connect(this, SIGNAL(thirdTmpVerOk()), this, SLOT(thirdTmpVerOk_slot()));
	connect(this, SIGNAL(allTmpVerOk()), this, SLOT(calcBasicErr()));
	m_tempObj = NULL;
	m_sendTimer = NULL;
	m_PlaVerifyRecPtr = NULL;

	m_rec_num = TMP_DIFF_NUMBER*VERIFY_NUMBER;
	m_tverparam_config = new QSettings(getFullIniFileName("tverparamconfig.ini"), QSettings::IniFormat);
	m_std_pla_config = new QSettings(getFullIniFileName("stdplasensor.ini"), QSettings::IniFormat);
	m_chk_pla_config = new QSettings(getFullIniFileName("chkplasensor.ini"), QSettings::IniFormat);
	m_readComConfig = new ReadComConfig();

	m_timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"); //��¼ʱ���

	m_tbl_inited = false;

	m_saved_times = 0;
	m_temp_index = 0;
	//initTbls();
}

tverparamDlg::~tverparamDlg()
{

}

//void tverparamDlg::initTbls()
//{
//	initTbl(ui.tbl_in_1);
//	initTbl(ui.tbl_in_2);
//	initTbl(ui.tbl_in_3);
//	m_tbl_inited = true;
//}
//
//void tverparamDlg::initTbl(QTreeWidget* tbl)
//{
//
//	QTreeWidgetItem* topItem = NULL;
//	topItem = tbl->takeTopLevelItem(0);
//	int k = topItem->columnCount();
//	//topItem->setText(0, "init");
//	//topItem = ui.tbl_in_2->takeTopLevelItem(9);
//	//topItem->setText(0, "init");
//	//topItem = ui.tbl_in_3->takeTopLevelItem(9);
//
//
//	//int k = ui.tbl_in_2->topLevelItemCount();
//	for (int i=0; i<VERIFY_NUMBER;i++)
//	{
//		QTreeWidgetItem *top_item = new QTreeWidgetItem(tbl);
//		top_item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
//		//int col = top_item->columnCount();
//		//top_item->setText(0, "serial");
//		for(int j=0;j<VERIFY_TIMES;j++)
//		{
//			QTreeWidgetItem *button_item = new QTreeWidgetItem(top_item);
//			button_item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
//			//button_item->setText(0, "serial");
//		}
//	}
//}

void tverparamDlg::closeEvent(QCloseEvent * event)
{
	if ( NULL != m_PlaParamParamDlg)
	{
		delete m_PlaParamParamDlg;
		m_PlaParamParamDlg = NULL;
	}

	if ( NULL != m_tverparam_config)
	{
		delete m_tverparam_config;
		m_tverparam_config = NULL;
	}

	if ( NULL != m_chk_pla_config)
	{
		delete m_chk_pla_config;
		m_chk_pla_config = NULL;
	}

	if ( NULL != m_readComConfig)
	{
		delete m_readComConfig;
		m_readComConfig = NULL;
	}

	if (NULL != m_PlaVerifyRecPtr)
	{
		delete []m_PlaVerifyRecPtr;
		m_PlaVerifyRecPtr = NULL;
	}

	clearComObjs();
}
void tverparamDlg::disableConfigBtn()
{
	ui.btn_param->setEnabled(false);
}

void tverparamDlg::disableAllWdg()
{
	disable1stWdg();
	disable2ndWdg();
	disable3rdWdg();
}

void tverparamDlg::disable1stWdg()
{
	ui.btn_read_1->setEnabled(false);
	ui.btn_clear_1->setEnabled(false);
	ui.tbl_in_1->setEnabled(false);
}
void tverparamDlg::disable2ndWdg()
{
	ui.btn_read_2->setEnabled(false);
	ui.btn_clear_2->setEnabled(false);
	ui.tbl_in_2->setEnabled(false);
}

void tverparamDlg::disable3rdWdg()
{
	ui.btn_read_3->setEnabled(false);
	ui.btn_clear_3->setEnabled(false);
	ui.tbl_in_3->setEnabled(false);
}

void tverparamDlg::enable1stWdg()
{
	ui.btn_read_1->setEnabled(true);
	ui.btn_clear_1->setEnabled(true);
	ui.tbl_in_1->setEnabled(true);
}

void tverparamDlg::enable2ndWdg()
{
	ui.btn_read_2->setEnabled(true);
	ui.btn_clear_2->setEnabled(true);
	ui.tbl_in_2->setEnabled(true);
}

void tverparamDlg::enable3rdWdg()
{
	ui.btn_read_3->setEnabled(true);
	ui.btn_clear_3->setEnabled(true);
	ui.tbl_in_3->setEnabled(true);
}

void tverparamDlg::on_btn_read_1_clicked()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadStdTempConfig();
	m_saved_times = 0;
	m_temp_index = 0;
	clearComObjs();
	m_sendTimer = new QTimer();
	m_tempObj = new Sti1062aComObject();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj,SIGNAL(temperatureIsReady(const QString&)), this, SLOT(setTblStd1(const QString&)));

	m_chanel = m_tverparam_config->value("chkinfo/chanel").toInt();
	m_readCommand = (m_chanel ==0) ? sti1062aT1:sti1062aT2;
	connect(m_sendTimer, SIGNAL(timeout()), this, SLOT(sendCommands()));
	//connect(this, SIGNAL(commandSendComplete()), m_sendTimer, SLOT(stop()));
	m_sendTimer->start(READ_STI1062A_TIMEOUT);
}

void tverparamDlg::sendCommands()
{
	m_tempObj->writeTemperatureComBuffer(m_readCommand);
}

void tverparamDlg::setTblStd1(const QString &tempStr)
{
	switch(m_readCommand)
	{
	case sti1062aT1:
		ui.tbl_std_1->item(1, 0)->setText(tempStr);
		m_readCommand = sti1062aR1;
		break;
	case sti1062aT2:
		ui.tbl_std_1->item(1, 0)->setText(tempStr);
		m_readCommand = sti1062aR2;
		break;
	case sti1062aR1:
		ui.tbl_std_1->item(0, 0)->setText(tempStr);
		m_readCommand = sti1062aT1;
		emit commandSendComplete();
		break;
	case sti1062aR2:
		ui.tbl_std_1->item(0, 0)->setText(tempStr);
		m_readCommand = sti1062aT2;
		emit commandSendComplete();
		break;
	}
}

void tverparamDlg::clearComObjs()
{
	if (NULL != m_sendTimer)
	{
		if (m_sendTimer->isActive())
		{
			m_sendTimer->stop();
		}

		delete m_sendTimer;
		m_sendTimer = NULL;
	}

	if (NULL != m_tempObj)
	{
		m_tempObj->close();
		delete m_tempObj;
		m_tempObj = NULL;
	}
}

void tverparamDlg::on_btn_read_2_clicked()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadStdTempConfig();
	m_saved_times = 0;
	m_temp_index = 1;
	clearComObjs();
	m_sendTimer = new QTimer();
	m_tempObj = new Sti1062aComObject();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj,SIGNAL(temperatureIsReady(const QString&)), this, SLOT(setTblStd2(const QString&)));

	m_chanel = m_tverparam_config->value("chkinfo/chanel").toInt();
	m_readCommand = (m_chanel ==0) ? sti1062aT1:sti1062aT2;
	connect(m_sendTimer, SIGNAL(timeout()), this, SLOT(sendCommands()));
	//connect(this, SIGNAL(commandSendComplete()), m_sendTimer, SLOT(stop()));
	m_sendTimer->start(READ_STI1062A_TIMEOUT);
}

void tverparamDlg::setTblStd2(const QString& tempStr)
{
	switch(m_readCommand)
	{
	case sti1062aT1:
		ui.tbl_std_2->item(1, 0)->setText(tempStr);
		m_readCommand = sti1062aR1;
		break;
	case sti1062aT2:
		ui.tbl_std_2->item(1, 0)->setText(tempStr);
		m_readCommand = sti1062aR2;
		break;
	case sti1062aR1:
		ui.tbl_std_2->item(0, 0)->setText(tempStr);
		m_readCommand = sti1062aT1;
		emit commandSendComplete();
		break;
	case sti1062aR2:
		ui.tbl_std_2->item(0, 0)->setText(tempStr);
		m_readCommand = sti1062aT2;
		emit commandSendComplete();
		break;
	}
}

void tverparamDlg::on_btn_read_3_clicked()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadStdTempConfig();
	m_saved_times = 0;
	m_temp_index = 2;
	clearComObjs();
	m_sendTimer = new QTimer();
	m_tempObj = new Sti1062aComObject();
	m_tempObj->openTemperatureCom(&tempStruct);
	connect(m_tempObj,SIGNAL(temperatureIsReady(const QString&)), this, SLOT(setTblStd3(const QString&)));

	m_chanel = m_tverparam_config->value("chkinfo/chanel").toInt();
	m_readCommand = (m_chanel ==0) ? sti1062aT1:sti1062aT2;
	connect(m_sendTimer, SIGNAL(timeout()), this, SLOT(sendCommands()));
	//connect(this, SIGNAL(commandSendComplete()), m_sendTimer, SLOT(stop()));
	m_sendTimer->start(READ_STI1062A_TIMEOUT);
}

void tverparamDlg::setTblStd3(const QString& tempStr)
{
	switch(m_readCommand)
	{
	case sti1062aT1:
		ui.tbl_std_3->item(1, 0)->setText(tempStr);
		m_readCommand = sti1062aR1;
		break;
	case sti1062aT2:
		ui.tbl_std_3->item(1, 0)->setText(tempStr);
		m_readCommand = sti1062aR2;
		break;
	case sti1062aR1:
		ui.tbl_std_3->item(0, 0)->setText(tempStr);
		m_readCommand = sti1062aT1;
		emit commandSendComplete();
		break;
	case sti1062aR2:
		ui.tbl_std_3->item(0, 0)->setText(tempStr);
		m_readCommand = sti1062aT2;
		emit commandSendComplete();
		break;
	}
}
/******��ձ�׼�¶ȼ���ֵ*********/
void tverparamDlg::on_btn_clear_1_clicked()
{
	ui.tbl_std_1->item(0, 0)->setText("");
	ui.tbl_std_1->item(1, 0)->setText("");
	clearComObjs();
}

void tverparamDlg::on_btn_clear_2_clicked()
{
	ui.tbl_std_2->item(0, 0)->setText("");
	ui.tbl_std_2->item(1, 0)->setText("");
	clearComObjs();
}

void tverparamDlg::on_btn_clear_3_clicked()
{
	ui.tbl_std_3->item(0, 0)->setText("");
	ui.tbl_std_3->item(1, 0)->setText("");
	clearComObjs();
}

/******��׼�¶ȼ���ֵ*********/
void tverparamDlg::on_tbl_std_1_cellChanged(int i, int j)
{
	if (i==0 || ui.tbl_std_1->item(1,0)->text().isEmpty())
	{
		return;
	}
	
	float err;//�¶�����
	float std_t;//��׼�¶ȼƵ��¶�ֵ��

	std_t = ui.tbl_std_1->item(1,0)->text().trimmed().toFloat();
	err	  = getSingleTmpErr(std_t);

	ui.lineEdit_1->setText(QString::number(err));
}

void tverparamDlg::on_tbl_std_2_cellChanged(int i, int j)
{
	if (i==0 || ui.tbl_std_2->item(1,0)->text().isEmpty())
	{
		return;
	}

	float err;//�¶�����
	float std_t;//��׼�¶ȼƵ��¶�ֵ��

	std_t = ui.tbl_std_2->item(1,0)->text().trimmed().toFloat();
	err	  = getSingleTmpErr(std_t);

	ui.lineEdit_2->setText(QString::number(err));
}

void tverparamDlg::on_tbl_std_3_cellChanged(int i, int j)
{
	if (i==0 || ui.tbl_std_3->item(1,0)->text().isEmpty())
	{
		return;
	}

	float err;//�¶�����
	float std_t;//��׼�¶ȼƵ��¶�ֵ��

	std_t = ui.tbl_std_3->item(1,0)->text().trimmed().toFloat();
	err	  = getSingleTmpErr(std_t);

	ui.lineEdit_3->setText(QString::number(err));
}

/******���첬������ֵ*********/
//void tverparamDlg::on_tbl_in_1_currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous)
//{
//
//}
//
//void tverparamDlg::on_tbl_in_1_itemChanged(QTreeWidgetItem * item, int column)
//{
//	if (!m_tbl_inited)
//	{
//		return;
//	}
//
//	int test;
//	test = test ^ test;
//	test = ~test;
//	int idx = ui.tbl_in_1->indexOfTopLevelItem(item);
//	bool eq = (idx == test);
//
//	if (eq)//�ڶ����ڵ�
//	{
//	}
//	else//��һ��ڵ�
//	{
//		//ͬ���޸Ĳ��������к�
//		QString sn = item->text(column);
//		QTreeWidgetItem* topItem = NULL;
//		topItem = ui.tbl_in_2->takeTopLevelItem(idx);
//		topItem->setText(column, sn);
//		topItem = ui.tbl_in_3->takeTopLevelItem(idx);
//		topItem->setText(column, sn);
//	}
//}


void tverparamDlg::on_tbl_in_1_cellChanged(int i, int j)
{
	if (ui.tbl_in_1->item(i, j)->text().isEmpty())
	{
		return;
	}

	float pla_a, pla_b, pla_r0;//���첬����ĵ�������
	pla_a	= m_chk_pla_config->value("setting/a").toFloat();
	pla_b	= m_chk_pla_config->value("setting/b").toFloat();
	pla_r0	= m_chk_pla_config->value("setting/r0").toFloat();

	float std_t, std_r;//��׼�¶ȼƵ��¶�ֵ����ֵ
	float in_t, out_t, in_r, out_r;//���첬����Ľ������¶�ֵ����ֵ
	float err;//���첬�������׼�¶ȼƵ��¶Ȳ�

	if (j==0)
	{
		//ͬ���޸Ĳ��������к�
		QString sn = ui.tbl_in_1->item(i,j)->text();
		ui.tbl_in_2->item(i,j)->setText(sn);
		ui.tbl_in_3->item(i,j)->setText(sn);
	}
	else if (j==1)//�¶ȼƽ�����ֵ
	{
		std_t = ui.tbl_std_1->item(1, 0)->text().trimmed().toFloat();
		in_r = ui.tbl_in_1->item(i, j)->text().trimmed().toFloat();
		in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);
		ui.tbl_result->item(i, 4*0 + j-1)->setText(QString::number(in_t));//д�������ı��첬������¶�ֵ
		err = qAbs(in_t - std_t);
		ui.tbl_result->item(i, 4*0 + j)->setText(QString::number(err));//д�����������׼�¶ȼƵ��¶Ȳ�
	}
	else if (j==2)//�¶ȼƽ�����ֵ
	{
		std_t = ui.tbl_std_1->item(1, 0)->text().trimmed().toFloat();
		in_r = ui.tbl_in_1->item(i, j)->text().trimmed().toFloat();
		in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);
		ui.tbl_result->item(i, 4*0 + j)->setText(QString::number(in_t));//д�������ı��첬������¶�ֵ
		err = qAbs(in_t - std_t);
		ui.tbl_result->item(i, 4*0 + j+1)->setText(QString::number(err));//д�����������׼�¶ȼƵ��¶Ȳ�
	}
}

void tverparamDlg::on_tbl_in_2_cellChanged(int i, int j)
{
	if (ui.tbl_in_2->item(i, j)->text().isEmpty())
	{
		return;
	}

	float pla_a, pla_b, pla_r0;//���첬����ĵ�������
	pla_a	= m_chk_pla_config->value("setting/a").toFloat();
	pla_b	= m_chk_pla_config->value("setting/b").toFloat();
	pla_r0	= m_chk_pla_config->value("setting/r0").toFloat();

	float std_t, std_r;//��׼�¶ȼƵ��¶�ֵ����ֵ
	float in_t, out_t, in_r, out_r;//���첬����Ľ������¶�ֵ����ֵ
	float err;//���첬�������׼�¶ȼƵ��¶Ȳ�

	if (j==0)
	{
		//ͬ���޸Ĳ��������к�
		QString sn = ui.tbl_in_2->item(i,j)->text();
		ui.tbl_in_1->item(i,j)->setText(sn);
		ui.tbl_in_3->item(i,j)->setText(sn);
	}
	else if (j==1)//�¶ȼƽ�����ֵ
	{
		std_t = ui.tbl_std_2->item(1, 0)->text().trimmed().toFloat();
		in_r = ui.tbl_in_2->item(i, j)->text().trimmed().toFloat();
		in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);
		ui.tbl_result->item(i, 4*1 + j-1)->setText(QString::number(in_t));//д�������ı��첬������¶�ֵ
		err = qAbs(in_t - std_t);
		ui.tbl_result->item(i, 4*1 + j)->setText(QString::number(err));//д�����������׼�¶ȼƵ��¶Ȳ�
	}
	else if (j==2)//�¶ȼƽ�����ֵ
	{
		std_t = ui.tbl_std_2->item(1, 0)->text().trimmed().toFloat();
		in_r = ui.tbl_in_2->item(i, j)->text().trimmed().toFloat();
		in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);
		ui.tbl_result->item(i, 4*1 + j)->setText(QString::number(in_t));//д�������ı��첬������¶�ֵ
		err = qAbs(in_t - std_t);
		ui.tbl_result->item(i, 4*1 + j+1)->setText(QString::number(err));//д�����������׼�¶ȼƵ��¶Ȳ�
	}
}

void tverparamDlg::on_tbl_in_3_cellChanged(int i, int j)
{
	if (ui.tbl_in_3->item(i, j)->text().isEmpty())
	{
		return;
	}

	float pla_a, pla_b, pla_r0;//���첬����ĵ�������
	pla_a	= m_chk_pla_config->value("setting/a").toFloat();
	pla_b	= m_chk_pla_config->value("setting/b").toFloat();
	pla_r0	= m_chk_pla_config->value("setting/r0").toFloat();

	float std_t, std_r;//��׼�¶ȼƵ��¶�ֵ����ֵ
	float in_t, out_t, in_r, out_r;//���첬����Ľ������¶�ֵ����ֵ
	float err;//���첬�������׼�¶ȼƵ��¶Ȳ�

	if (j==0)
	{
		//ͬ���޸Ĳ��������к�
		QString sn = ui.tbl_in_3->item(i,j)->text();
		ui.tbl_in_1->item(i,j)->setText(sn);
		ui.tbl_in_2->item(i,j)->setText(sn);
	}
	else if (j==1)//�¶ȼƽ�����ֵ
	{
		std_t = ui.tbl_std_3->item(1, 0)->text().trimmed().toFloat();
		in_r = ui.tbl_in_3->item(i, j)->text().trimmed().toFloat();
		in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);
		ui.tbl_result->item(i, 4*2 + j-1)->setText(QString::number(in_t));//д�������ı��첬������¶�ֵ
		err = qAbs(in_t - std_t);
		ui.tbl_result->item(i, 4*2 + j)->setText(QString::number(err));//д�����������׼�¶ȼƵ��¶Ȳ�
	}
	else if (j==2)//�¶ȼƽ�����ֵ
	{
		std_t = ui.tbl_std_3->item(1, 0)->text().trimmed().toFloat();
		in_r = ui.tbl_in_3->item(i, j)->text().trimmed().toFloat();
		in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);
		ui.tbl_result->item(i, 4*2 + j)->setText(QString::number(in_t));//д�������ı��첬������¶�ֵ
		err = qAbs(in_t - std_t);
		ui.tbl_result->item(i, 4*2 + j+1)->setText(QString::number(err));//д�����������׼�¶ȼƵ��¶Ȳ�
	}
}

/******���첬�����¶�ֵ*******/
void tverparamDlg::on_tbl_result_cellChanged(int i, int j)
{
	QLineEdit* line;
	
	if(j<4)
	{
		line = ui.lineEdit_1;
	}
	else if (j<8 && j>3)
	{
		line = ui.lineEdit_2;
	}
	else
	{
		line = ui.lineEdit_3;
	}
	float err = line->text().trimmed().toFloat();

	if ((j%2) == 0)//ż����Ϊ�¶�ֵ
	{

	}
	else//������Ϊ���ֵ
	{
		float pla_err = ui.tbl_result->item(i, j)->text().trimmed().toFloat();

		ui.tbl_result->item(i, j)->setTextColor((pla_err>err) ? QColor(250,0,0) : QColor(0,0,0));
		ui.tbl_result->item(i, j-1)->setTextColor((pla_err>err) ? QColor(250,0,0) : QColor(0,0,0));	
	}
}

void tverparamDlg::on_btn_param_clicked()
{
	if ( NULL == m_PlaParamParamDlg)
	{
		m_PlaParamParamDlg = new tverparamparamDlg;
	}
	else
	{
		delete m_PlaParamParamDlg;
		m_PlaParamParamDlg = new tverparamparamDlg;
	}

	m_PlaParamParamDlg->show();
}

void tverparamDlg::on_btn_save_clicked()
{
	if (m_saved_times < VERIFY_TIMES)
	{
		m_saved_times++;
		insertData();
	}

	if (m_saved_times == VERIFY_TIMES)
	{
		switch(m_temp_index)
		{
			case 0:
				emit firstTmpVerOk();
				break;
			case 1:
				emit secondTmpVerOk();
				break;
			case 2:
				emit thirdTmpVerOk();
				break;
		}
	}
}

void tverparamDlg::calcBasicErr()
{
	for (int i=0;i<VERIFY_NUMBER;i++)
		calcBasicErrPerMeter(i);
}

void tverparamDlg::calcBasicErrPerMeter(int i)
{
	//��ǰ���ʱ��� m_timeStamp
	//��ǰ�¶ȵ����� m_temp_index
	//��ǰ�ȱ����к� sn
	QString sn = ui.tbl_in_1->item(i, 0)->text();
	float basicErr_perTmpIdx[2][3];//ÿ���¶ȵ�Ļ������, 2: �����ڲ����裬0-����, 1-����; 3: �¶ȵ����
	float basicErr[2];//��ǰ�ȱ�Ľ����ڻ������, 2: �����ڲ����裬0-����, 1-����

	for (int tmp_idx=0;tmp_idx<3;tmp_idx++)//��ȡ��ǰ�ȱ��ÿ���¶ȵ�Ļ������
	{
		basicErr_perTmpIdx[0][tmp_idx] = getTmpPntBasicErr(tmp_idx, sn)[0];
		basicErr_perTmpIdx[1][tmp_idx] = getTmpPntBasicErr(tmp_idx, sn)[1];
	}

	basicErr[0] = qMax(qMax(basicErr_perTmpIdx[0][0], basicErr_perTmpIdx[0][1]), basicErr_perTmpIdx[0][2]);
	basicErr[1] = qMax(qMax(basicErr_perTmpIdx[1][0], basicErr_perTmpIdx[1][1]), basicErr_perTmpIdx[1][2]);

	ui.tbl_maxerr->item(i, 0)->setText(QString::number(basicErr[0]));
	ui.tbl_maxerr->item(i, 1)->setText(QString::number(basicErr[1]));
}

float* tverparamDlg::getTmpPntBasicErr(int tmp_idx, QString sn)
{
	float basicErr[2];
	QString sql = "select avg(F_InErr), avg(F_OutErr) from T_Platinum_Verify_Record where F_CompOrParam = 1 and F_TimeStamp = ";
	sql.append(QString("\'%1\' and ").arg(m_timeStamp, 0, 10));//F_TimeStamp
	sql.append(QString("F_PlaSerial = \'%1\' and ").arg(sn, 0, 10));//F_PlaSerial
	sql.append(QString("F_TmpIndex = %1").arg(tmp_idx, 0, 10));//F_TmpIndex
	
	startdb();
	QSqlQuery query;
	query.exec(sql);
	query.first();
	basicErr[0] = query.value(0).toFloat();
	basicErr[1] = query.value(1).toFloat();
	closedb();
	return basicErr;
}

void tverparamDlg::on_btn_exit_clicked()
{
	this->close();
}

void tverparamDlg::insertData()
{
	if (NULL != m_PlaVerifyRecPtr)
	{
		delete []m_PlaVerifyRecPtr;
	}
	m_PlaVerifyRecPtr = new T_Platinium_Verify_Record_STR[VERIFY_NUMBER];
	memset(m_PlaVerifyRecPtr, 0, sizeof(T_Platinium_Verify_Record_STR)*VERIFY_NUMBER);
	readConfig();
	readChkResult();
	startdb();
	insertPlatinumVerifyRec(m_PlaVerifyRecPtr, VERIFY_NUMBER);
	closedb();
}

void tverparamDlg::readConfig()
{
	int std, model, manufac, inst, checker, verify;//��������

	std		= m_tverparam_config->value("chkinfo/stand").toInt();
	model	= m_tverparam_config->value("chkinfo/model").toInt();
	manufac = m_tverparam_config->value("chkinfo/manufac").toInt();
	inst	= m_tverparam_config->value("chkinfo/inst").toInt();
	checker = m_tverparam_config->value("chkinfo/chker").toInt();
	verify	= m_tverparam_config->value("chkinfo/verifyer").toInt();
	
	float pla_a, pla_b, pla_r0;//���첬�����������
	pla_a	= m_chk_pla_config->value("setting/a").toFloat();
	pla_b	= m_chk_pla_config->value("setting/b").toFloat();
	pla_r0	= m_chk_pla_config->value("setting/r0").toFloat();
	QString std_model = m_std_pla_config->value("in_use/model").toString();
	for(int i=0; i<VERIFY_NUMBER; i++)
	{
		m_PlaVerifyRecPtr[i].F_CompOrParam	= 1;
		m_PlaVerifyRecPtr[i].F_Standard		= std;
		m_PlaVerifyRecPtr[i].F_Model		= model;
		m_PlaVerifyRecPtr[i].F_ManufactDept	= manufac;
		m_PlaVerifyRecPtr[i].F_VerifyDept	= inst;
		m_PlaVerifyRecPtr[i].F_CheckPerson	= checker;
		m_PlaVerifyRecPtr[i].F_VerifyPerson = verify;

		m_PlaVerifyRecPtr[i].F_PlaCoeA		= pla_a;
		m_PlaVerifyRecPtr[i].F_PlaCoeB		= pla_b;
		m_PlaVerifyRecPtr[i].F_PlaParamR0	= pla_r0;
		strcpy_s(m_PlaVerifyRecPtr[i].timestamp, m_timeStamp.toAscii());
		strcpy_s(m_PlaVerifyRecPtr[i].F_StdModel, std_model.toAscii());
	}
}

void tverparamDlg::readChkResult()
{
	float std_t, std_r;//��׼�¶ȼƵ��¶�ֵ����ֵ
	float lmt_err;//��׼���¶������
	QTableWidget* std_tbl_wdg = NULL;//��ǰ�õ��ı�׼�¶ȼƱ��
	QTableWidget* chk_tbl_wdg = NULL;//��ǰ�õ��ı��첬������
	QLineEdit* lmt_err_lnEd   = NULL;//��ǰ�¶ȵ���¶������
	//for (int i=0; i<TMP_DIFF_NUMBER; i++)//�²�����
	//{
		switch(m_temp_index)
		{
		case 0://��һ�²��
			std_tbl_wdg  = ui.tbl_std_1;
			chk_tbl_wdg  = ui.tbl_in_1;
			lmt_err_lnEd = ui.lineEdit_1;
			break;
		case 1://�ڶ��²��
			std_tbl_wdg  = ui.tbl_std_2;
			chk_tbl_wdg  = ui.tbl_in_2;
			lmt_err_lnEd = ui.lineEdit_2;
			break;
		case 2://�����²��
			std_tbl_wdg  = ui.tbl_std_3;
			chk_tbl_wdg  = ui.tbl_in_3;
			lmt_err_lnEd = ui.lineEdit_3;
			break;
		}

		std_t   = std_tbl_wdg->item(1,0)->text().trimmed().toFloat();
		std_r   = std_tbl_wdg->item(0,0)->text().trimmed().toFloat();
		lmt_err	= lmt_err_lnEd->text().trimmed().toFloat();

		for (int j=0; j<VERIFY_NUMBER; j++)//���첬�������
		{
			m_PlaVerifyRecPtr[j].F_TmpDiff		= std_t;//�¶ȵ��ֵ
			m_PlaVerifyRecPtr[j].F_StdInRresis	= std_r;
			m_PlaVerifyRecPtr[j].F_StdInTmp		= std_t;
			strcpy_s(m_PlaVerifyRecPtr[j].F_PlaSerial, chk_tbl_wdg->item(j, 0)->text().toAscii());
			m_PlaVerifyRecPtr[j].F_PlaInRresis	= chk_tbl_wdg->item(j, 1)->text().trimmed().toFloat();
			m_PlaVerifyRecPtr[j].F_PlaOutRresis	= chk_tbl_wdg->item(j, 2)->text().trimmed().toFloat();
							  
			m_PlaVerifyRecPtr[j].F_PlaInTmp		= ui.tbl_result->item(j, 4*m_temp_index+0)->text().trimmed().toFloat();
			m_PlaVerifyRecPtr[j].F_PlaOutTmp	= ui.tbl_result->item(j, 4*m_temp_index+2)->text().trimmed().toFloat();
							  
			m_PlaVerifyRecPtr[j].F_InErrLimit	= lmt_err;
			m_PlaVerifyRecPtr[j].F_OutErrLimit	= lmt_err;
							  
			m_PlaVerifyRecPtr[j].F_InErr		= m_PlaVerifyRecPtr[j].F_PlaInTmp - std_t;
			m_PlaVerifyRecPtr[j].F_OutErr		= m_PlaVerifyRecPtr[j].F_PlaOutTmp - std_t;
							  
			m_PlaVerifyRecPtr[j].F_verify_seq	= m_saved_times;
			m_PlaVerifyRecPtr[j].F_TmpIndex		= m_temp_index;
		}
	//}
}

void tverparamDlg::firstTmpVerOk_slot()
{
	disable1stWdg();
	enable2ndWdg();
}

void tverparamDlg::secondTmpVerOk_slot()
{
	disable2ndWdg();
	enable3rdWdg();
}

void tverparamDlg::thirdTmpVerOk_slot()
{
	disable3rdWdg();
	ui.btn_save->setEnabled(false);
	emit allTmpVerOk();
}