#include "algorithm.h"
#include "qtexdb.h"
#include "tvercomp.h"

tvercompDlg::tvercompDlg(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	m_PlaCompParamDlg = NULL;
	m_tempObj = NULL;
	m_sendTimer = NULL;
	m_PlaVerifyRecPtr = NULL;

	m_tvercomp_config = new QSettings(getIniFileName("tvercompconfig.ini"), QSettings::IniFormat);
	m_chk_pla_config = new QSettings(getIniFileName("chkplasensor.ini"), QSettings::IniFormat);
	m_readComConfig = new ReadComConfig();

	readConfig();
}

tvercompDlg::~tvercompDlg()
{

}

void tvercompDlg::closeEvent(QCloseEvent * event)
{
	if ( NULL != m_PlaCompParamDlg)
	{
		delete m_PlaCompParamDlg;
		m_PlaCompParamDlg = NULL;
	}

	if ( NULL != m_tvercomp_config)
	{
		delete m_tvercomp_config;
		m_tvercomp_config = NULL;
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

void tvercompDlg::on_btn_param_clicked()
{
	if ( NULL == m_PlaCompParamDlg)
	{
		m_PlaCompParamDlg = new tvercompparamDlg;
	}
	else
	{
		delete m_PlaCompParamDlg;
		m_PlaCompParamDlg = new tvercompparamDlg;
	}

	m_PlaCompParamDlg->show();
}

void tvercompDlg::on_btn_read_1_clicked()
{
	ComInfoStruct tempStruct = m_readComConfig->ReadStdTempConfig();

	if (m_sendTimer == NULL)
	{
		m_sendTimer = new QTimer();
	}
	if (m_sendTimer->isActive())
	{
		m_sendTimer->stop();
	}
	if (m_tempObj == NULL)
	{
		m_tempObj = new Sti1062aComObject();
		m_tempObj->openTemperatureCom(&tempStruct);
		connect(m_tempObj,SIGNAL(temperatureIsReady(const QString&)), this, SLOT(setTblStd1(const QString&)));
	}

	m_readCommand = sti1062aT1;
	connect(m_sendTimer, SIGNAL(timeout()), this, SLOT(sendCommands()));
	connect(this, SIGNAL(commandSendComplete()), m_sendTimer, SLOT(stop()));
	//connect(this, SIGNAL(commandSendComplete()), this, SLOT(clearComObjs()));
	m_sendTimer->start(READ_STI1062A_TIMEOUT);
}

void tvercompDlg::sendCommands()
{
	m_tempObj->writeTemperatureComBuffer(m_readCommand);
}

void tvercompDlg::setTblStd1(const QString &tempStr)
{
	switch(m_readCommand)
	{
		case sti1062aT1:
			ui.tbl_std_1->item(1, 0)->setText(tempStr);
			m_readCommand = sti1062aT2;
			break;
		case sti1062aT2:
			ui.tbl_std_1->item(1, 1)->setText(tempStr);
			m_readCommand = sti1062aR1;
			break;
		case sti1062aR1:
			ui.tbl_std_1->item(0, 0)->setText(tempStr);
			m_readCommand = sti1062aR2;
			break;
		case sti1062aR2:
			ui.tbl_std_1->item(0, 1)->setText(tempStr);
			m_readCommand = sti1062aT1;
			emit commandSendComplete();
			break;
	}
}

void tvercompDlg::on_btn_read_2_clicked()
{

}

void tvercompDlg::on_btn_read_3_clicked()
{

}

void tvercompDlg::on_btn_clear_1_clicked()
{
	ui.tbl_std_1->item(0, 0)->setText("");
	ui.tbl_std_1->item(0, 1)->setText("");
	ui.tbl_std_1->item(1, 0)->setText("");
	ui.tbl_std_1->item(1, 1)->setText("");
	clearComObjs();
}

void tvercompDlg::clearComObjs()
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

void tvercompDlg::on_btn_clear_2_clicked()
{

}

void tvercompDlg::on_btn_clear_3_clicked()
{

}

void tvercompDlg::on_tbl_std_1_cellChanged(int i, int j)
{
	
}

void tvercompDlg::on_tbl_std_2_cellChanged(int, int)
{

}

void tvercompDlg::on_tbl_std_3_cellChanged(int, int)
{

}

void tvercompDlg::on_tbl_in_1_cellChanged(int i, int j)
{
	if (ui.tbl_in_1->item(i, j)->text().isEmpty())
	{
		return;
	}

	float delta, err;
	if (j==1)//温度计进口
	{
		delta = ui.tbl_in_1->item(i, j)->text().trimmed().toFloat() - ui.tbl_std_1->item(1, 0)->text().trimmed().toFloat();
	}
	else if (j==2)//温度计出口
	{
		delta = ui.tbl_in_1->item(i, j)->text().trimmed().toFloat() - ui.tbl_std_1->item(1,1)->text().trimmed().toFloat();
		if (!ui.tbl_in_1->item(i, j-1)->text().trimmed().isEmpty())
		{
			float delta_std = ui.tbl_std_1->item(1, 0)->text().trimmed().toFloat() - ui.tbl_std_1->item(1, 1)->text().trimmed().toFloat();//标准温度计温差
			delta = ui.tbl_in_1->item(i, j)->text().trimmed().toFloat() - ui.tbl_in_1->item(i, j-1)->text().trimmed().toFloat();
			ui.tbl_chkerror_1->item(i, 2)->setText(QString::number(delta/delta_std));
		}
	}
	
	ui.tbl_chkerror_1->item(i, j-1)->setText(QString::number(delta));
}

void tvercompDlg::on_tbl_in_2_cellChanged(int, int)
{

}

void tvercompDlg::on_tbl_in_3_cellChanged(int, int)
{

}

void tvercompDlg::on_btn_excel_clicked()
{
	QTableWidgetItem* item = ui.tbl_std_1->item(0,0);
	item->setText("wocao");
	int count = ui.tbl_chkerror_1->rowCount();
	int col = ui.tbl_chkerror_1->columnCount();
	for (int i=0; i < ui.tbl_chkerror_1->rowCount(); i++)
	{
		item = ui.tbl_stderror_1->item(i,0);
		item->setText("wocao");
		item = ui.tbl_stderror_1->item(i,1);
		item->setText("wocao");
	}
}

void tvercompDlg::on_btn_save_clicked()
{
	insertData();
}

void tvercompDlg::insertData()
{
	if (NULL == m_PlaVerifyRecPtr)
	{
		m_PlaVerifyRecPtr = new T_Platinium_Verify_Record_STR;
		memset(m_PlaVerifyRecPtr, 0, sizeof(T_Platinium_Verify_Record_STR)*VERIFY_NUMBER);
	}

	startdb();

	closedb();
}

void tvercompDlg::readConfig()
{

}

void tvercompDlg::on_btn_exit_clicked()
{
	this->close();
}