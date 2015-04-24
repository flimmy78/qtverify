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

	m_rec_num = TMP_DIFF_NUMBER*VERIFY_NUMBER;
	m_tvercomp_config = new QSettings(getIniFileName("tvercompconfig.ini"), QSettings::IniFormat);
	m_std_pla_config = new QSettings(getIniFileName("stdplasensor.ini"), QSettings::IniFormat);
	m_chk_pla_config = new QSettings(getIniFileName("chkplasensor.ini"), QSettings::IniFormat);
	m_readComConfig = new ReadComConfig();

	m_min_delta_tmp = m_tvercomp_config->value("theoinfo/mintmphead").toFloat();
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
		connect(m_tempObj,SIGNAL(temperatureIsReady(const QString&)), this, SLOT(setTblStd2(const QString&)));
	}

	m_readCommand = sti1062aT1;
	connect(m_sendTimer, SIGNAL(timeout()), this, SLOT(sendCommands()));
	connect(this, SIGNAL(commandSendComplete()), m_sendTimer, SLOT(stop()));
	m_sendTimer->start(READ_STI1062A_TIMEOUT);
}

void tvercompDlg::setTblStd2(const QString &tempStr)
{
	switch(m_readCommand)
	{
	case sti1062aT1:
		ui.tbl_std_2->item(1, 0)->setText(tempStr);
		m_readCommand = sti1062aT2;
		break;
	case sti1062aT2:
		ui.tbl_std_2->item(1, 1)->setText(tempStr);
		m_readCommand = sti1062aR1;
		break;
	case sti1062aR1:
		ui.tbl_std_2->item(0, 0)->setText(tempStr);
		m_readCommand = sti1062aR2;
		break;
	case sti1062aR2:
		ui.tbl_std_2->item(0, 1)->setText(tempStr);
		m_readCommand = sti1062aT1;
		emit commandSendComplete();
		break;
	}
}

void tvercompDlg::on_btn_read_3_clicked()
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
		connect(m_tempObj,SIGNAL(temperatureIsReady(const QString&)), this, SLOT(setTblStd3(const QString&)));
	}

	m_readCommand = sti1062aT1;
	connect(m_sendTimer, SIGNAL(timeout()), this, SLOT(sendCommands()));
	connect(this, SIGNAL(commandSendComplete()), m_sendTimer, SLOT(stop()));
	m_sendTimer->start(READ_STI1062A_TIMEOUT);
}

void tvercompDlg::setTblStd3(const QString &tempStr)
{
	switch(m_readCommand)
	{
	case sti1062aT1:
		ui.tbl_std_3->item(1, 0)->setText(tempStr);
		m_readCommand = sti1062aT2;
		break;
	case sti1062aT2:
		ui.tbl_std_3->item(1, 1)->setText(tempStr);
		m_readCommand = sti1062aR1;
		break;
	case sti1062aR1:
		ui.tbl_std_3->item(0, 0)->setText(tempStr);
		m_readCommand = sti1062aR2;
		break;
	case sti1062aR2:
		ui.tbl_std_3->item(0, 1)->setText(tempStr);
		m_readCommand = sti1062aT1;
		emit commandSendComplete();
		break;
	}
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
	ui.tbl_std_2->item(0, 0)->setText("");
	ui.tbl_std_2->item(0, 1)->setText("");
	ui.tbl_std_2->item(1, 0)->setText("");
	ui.tbl_std_2->item(1, 1)->setText("");
	clearComObjs();
}

void tvercompDlg::on_btn_clear_3_clicked()
{
	ui.tbl_std_3->item(0, 0)->setText("");
	ui.tbl_std_3->item(0, 1)->setText("");
	ui.tbl_std_3->item(1, 0)->setText("");
	ui.tbl_std_3->item(1, 1)->setText("");
	clearComObjs();
}

void tvercompDlg::on_tbl_std_1_cellChanged(int i, int j)
{
	if (i==0)
	{
		return;
	}

	if (ui.tbl_std_1->item(1,0)->text().isEmpty() || ui.tbl_std_1->item(1,1)->text().isEmpty())
	{
		return;
	}
	float in_err, out_err, delta_err;

	float in_t, out_t;
	in_t = ui.tbl_std_1->item(1,0)->text().trimmed().toFloat();
	out_t = ui.tbl_std_1->item(1,1)->text().trimmed().toFloat();
	in_err = getSingleTmpErr(in_t);
	out_err = getSingleTmpErr(out_t);
	//��֧���
	ui.tbl_stderror_1->item(0,0)->setText(QString::number(in_err));
	ui.tbl_stderror_1->item(0,1)->setText(QString::number(out_err));
	//�²������
	float std_delta = in_t - out_t;
	delta_err = getDeltaTmpErr(std_delta, m_min_delta_tmp);
	ui.tbl_stderror_1->item(0,2)->setText(QString::number(delta_err));
}

void tvercompDlg::on_tbl_std_2_cellChanged(int i, int j)
{
	if (ui.tbl_std_2->item(1,0)->text().isEmpty() || ui.tbl_std_2->item(1,1)->text().isEmpty())
	{
		return;
	}
	float in_err, out_err, delta_err;

	float in_t, out_t;
	in_t = ui.tbl_std_2->item(1,0)->text().trimmed().toFloat();
	out_t = ui.tbl_std_2->item(1,1)->text().trimmed().toFloat();
	in_err = getSingleTmpErr(in_t);
	out_err = getSingleTmpErr(out_t);
	//��֧�����
	ui.tbl_stderror_2->item(0,0)->setText(QString::number(in_err));
	ui.tbl_stderror_2->item(0,1)->setText(QString::number(out_err));
	//�²������
	float std_delta = in_t - out_t;
	delta_err = getDeltaTmpErr(std_delta, m_min_delta_tmp);
	ui.tbl_stderror_2->item(0,2)->setText(QString::number(delta_err));
}

void tvercompDlg::on_tbl_std_3_cellChanged(int i, int j)
{
	if (ui.tbl_std_3->item(1,0)->text().isEmpty() || ui.tbl_std_3->item(1,1)->text().isEmpty())
	{
		return;
	}
	float in_err, out_err, delta_err;

	float in_t, out_t;
	in_t = ui.tbl_std_3->item(1,0)->text().trimmed().toFloat();
	out_t = ui.tbl_std_3->item(1,1)->text().trimmed().toFloat();
	in_err = getSingleTmpErr(in_t);
	out_err = getSingleTmpErr(out_t);
	//��֧�����
	ui.tbl_stderror_3->item(0,0)->setText(QString::number(in_err));
	ui.tbl_stderror_3->item(0,1)->setText(QString::number(out_err));
	//�²������
	float std_delta = in_t - out_t;
	delta_err = getDeltaTmpErr(std_delta, m_min_delta_tmp);
	ui.tbl_stderror_3->item(0,2)->setText(QString::number(delta_err));
}

void tvercompDlg::on_tbl_in_1_cellChanged(int i, int j)
{
	if (ui.tbl_in_1->item(i, j)->text().isEmpty())
	{
		return;
	}

	float pla_a, pla_b, pla_r0;//���첬����ĵ�������
	pla_a	= m_chk_pla_config->value("setting/a").toFloat();
	pla_b	= m_chk_pla_config->value("setting/b").toFloat();
	pla_r0	= m_chk_pla_config->value("setting/r0").toFloat();

	float std_in_t, std_out_t, std_in_r, std_out_r;//��׼�¶ȼƵĽ������¶�ֵ����ֵ
	float in_t, out_t, in_r, out_r;//���첬����Ľ������¶�ֵ����ֵ
	float delta;//���첬�������׼�¶ȼƵ��¶Ȳ�
	float delta_std;//��׼�¶ȼ����׼�¶ȼƵ��¶Ȳ�
	float err;//���첬����������¶Ȳ����׼�¶ȼƽ������²�����

	if (j==0)
	{
		//ͬ���޸Ĳ��������к�
		QString sn = ui.tbl_in_1->item(i,j)->text();
		ui.tbl_in_2->item(i,j)->setText(sn);
		ui.tbl_in_3->item(i,j)->setText(sn);
	}
	else if (j==1)//�¶ȼƽ�����ֵ
	{
		std_in_t = ui.tbl_std_1->item(1, 0)->text().trimmed().toFloat();
		in_r = ui.tbl_in_1->item(i, j)->text().trimmed().toFloat();
		in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);
		ui.tbl_chkerror_1->item(i, j-1)->setText(QString::number(in_t));//д�����������׼�¶ȼƵ��¶Ȳ�
		if (!ui.tbl_in_1->item(i, j+1)->text().trimmed().isEmpty())//д�����
		{
			std_in_t = ui.tbl_std_1->item(1, 0)->text().trimmed().toFloat();
			std_out_t = ui.tbl_std_1->item(1, 1)->text().trimmed().toFloat();
			delta_std = std_in_t - std_out_t;//��׼�¶ȼ��²�

			in_r = ui.tbl_in_1->item(i, j)->text().trimmed().toFloat();//������ֵ
			out_r = ui.tbl_in_1->item(i, j+1)->text().trimmed().toFloat();//������ֵ
			in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);//�����¶�ֵ
			out_t = getPlaTr(pla_r0, pla_a, pla_b, out_r);//�����¶�ֵ
			delta = in_t - out_t;//���첬�����²�

			err = qAbs(qAbs(delta/delta_std) - 1);//��� = (���첬�����²�/��׼�¶ȼ��²�) - 1
			ui.tbl_chkerror_1->item(i, 2)->setText(QString::number(err*100));//���%
		}
	}
	else if (j==2)//�¶ȼƳ�����ֵ
	{
		std_out_t = ui.tbl_std_1->item(1,1)->text().trimmed().toFloat();
		out_r = ui.tbl_in_1->item(i, j)->text().trimmed().toFloat();
		out_t = getPlaTr(pla_r0, pla_a, pla_b, out_r);
		ui.tbl_chkerror_1->item(i, j-1)->setText(QString::number(out_t));//д�����������׼�¶ȼƵ��¶Ȳ�
		if (!ui.tbl_in_1->item(i, j-1)->text().trimmed().isEmpty())//д�����
		{
			std_in_t = ui.tbl_std_1->item(1, 0)->text().trimmed().toFloat();
			std_out_t = ui.tbl_std_1->item(1, 1)->text().trimmed().toFloat();
			delta_std = std_in_t - std_out_t;//��׼�¶ȼ��²�

			in_r = ui.tbl_in_1->item(i, j-1)->text().trimmed().toFloat();//������ֵ
			out_r = ui.tbl_in_1->item(i, j)->text().trimmed().toFloat();//������ֵ
			in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);//�����¶�ֵ
			out_t = getPlaTr(pla_r0, pla_a, pla_b, out_r);//�����¶�ֵ
			delta = in_t - out_t;//���첬�����²�

			err = qAbs(qAbs(delta/delta_std) - 1);//���
			ui.tbl_chkerror_1->item(i, 2)->setText(QString::number(err*100));//���%
		}
	}
}

void tvercompDlg::on_tbl_in_2_cellChanged(int i, int j)
{
	if (ui.tbl_in_2->item(i, j)->text().isEmpty())
	{
		return;
	}

	float pla_a, pla_b, pla_r0;//���첬����ĵ�������
	pla_a	= m_chk_pla_config->value("setting/a").toFloat();
	pla_b	= m_chk_pla_config->value("setting/b").toFloat();
	pla_r0	= m_chk_pla_config->value("setting/r0").toFloat();

	float std_in_t, std_out_t, std_in_r, std_out_r;//��׼�¶ȼƵĽ������¶�ֵ����ֵ
	float in_t, out_t, in_r, out_r;//���첬����Ľ������¶�ֵ����ֵ
	float delta;//���첬�������׼�¶ȼƵ��¶Ȳ�
	float delta_std;//��׼�¶ȼ����׼�¶ȼƵ��¶Ȳ�
	float err;//���첬����������¶Ȳ����׼�¶ȼƽ������²�����
	if (j==0)
	{
		//ͬ���޸Ĳ��������к�
		QString sn = ui.tbl_in_2->item(i,j)->text();
		ui.tbl_in_1->item(i,j)->setText(sn);
		ui.tbl_in_3->item(i,j)->setText(sn);
	}
	else if (j==1)//�¶ȼƽ�����ֵ
	{
		std_in_t = ui.tbl_std_2->item(1, 0)->text().trimmed().toFloat();
		in_r = ui.tbl_in_2->item(i, j)->text().trimmed().toFloat();
		in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);
		ui.tbl_chkerror_2->item(i, j-1)->setText(QString::number(in_t));//д�����������׼�¶ȼƵ��¶Ȳ�
		if (!ui.tbl_in_2->item(i, j+1)->text().trimmed().isEmpty())//д�����
		{
			std_in_t = ui.tbl_std_2->item(1, 0)->text().trimmed().toFloat();
			std_out_t = ui.tbl_std_2->item(1, 1)->text().trimmed().toFloat();
			delta_std = std_in_t - std_out_t;//��׼�¶ȼ��²�

			in_r = ui.tbl_in_2->item(i, j)->text().trimmed().toFloat();//������ֵ
			out_r = ui.tbl_in_2->item(i, j+1)->text().trimmed().toFloat();//������ֵ
			in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);//�����¶�ֵ
			out_t = getPlaTr(pla_r0, pla_a, pla_b, out_r);//�����¶�ֵ
			delta = in_t - out_t;//���첬�����²�

			err = qAbs(qAbs(delta/delta_std) - 1);//��� = (���첬�����²�/��׼�¶ȼ��²�) - 1
			ui.tbl_chkerror_2->item(i, 2)->setText(QString::number(err*100));//���%
		}
	}
	else if (j==2)//�¶ȼƳ�����ֵ
	{
		std_out_t = ui.tbl_std_2->item(1,1)->text().trimmed().toFloat();
		out_r = ui.tbl_in_2->item(i, j)->text().trimmed().toFloat();
		out_t = getPlaTr(pla_r0, pla_a, pla_b, out_r);
		ui.tbl_chkerror_2->item(i, j-1)->setText(QString::number(out_t));//д�����������׼�¶ȼƵ��¶Ȳ�
		if (!ui.tbl_in_2->item(i, j-1)->text().trimmed().isEmpty())//д�����
		{
			std_in_t = ui.tbl_std_2->item(1, 0)->text().trimmed().toFloat();
			std_out_t = ui.tbl_std_2->item(1, 1)->text().trimmed().toFloat();
			delta_std = std_in_t - std_out_t;//��׼�¶ȼ��²�

			in_r = ui.tbl_in_2->item(i, j-1)->text().trimmed().toFloat();//������ֵ
			out_r = ui.tbl_in_2->item(i, j)->text().trimmed().toFloat();//������ֵ
			in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);//�����¶�ֵ
			out_t = getPlaTr(pla_r0, pla_a, pla_b, out_r);//�����¶�ֵ
			delta = in_t - out_t;//���첬�����²�

			err = qAbs(qAbs(delta/delta_std) - 1);//���
			ui.tbl_chkerror_2->item(i, 2)->setText(QString::number(err*100));//���%
		}
	}
}

void tvercompDlg::on_tbl_in_3_cellChanged(int i, int j)
{
	if (ui.tbl_in_3->item(i, j)->text().isEmpty())
	{
		return;
	}

	float pla_a, pla_b, pla_r0;//���첬����ĵ�������
	pla_a	= m_chk_pla_config->value("setting/a").toFloat();
	pla_b	= m_chk_pla_config->value("setting/b").toFloat();
	pla_r0	= m_chk_pla_config->value("setting/r0").toFloat();

	float std_in_t, std_out_t, std_in_r, std_out_r;//��׼�¶ȼƵĽ������¶�ֵ����ֵ
	float in_t, out_t, in_r, out_r;//���첬����Ľ������¶�ֵ����ֵ
	float delta;//���첬�������׼�¶ȼƵ��¶Ȳ�
	float delta_std;//��׼�¶ȼ����׼�¶ȼƵ��¶Ȳ�
	float err;//���첬����������¶Ȳ����׼�¶ȼƽ������²�����
	if (j==0)
	{
		//ͬ���޸Ĳ��������к�
		QString sn = ui.tbl_in_3->item(i,j)->text();
		ui.tbl_in_2->item(i,j)->setText(sn);
		ui.tbl_in_1->item(i,j)->setText(sn);
	}
	else if (j==1)//�¶ȼƽ�����ֵ
	{
		std_in_t = ui.tbl_std_3->item(1, 0)->text().trimmed().toFloat();
		in_r = ui.tbl_in_3->item(i, j)->text().trimmed().toFloat();
		in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);
		ui.tbl_chkerror_3->item(i, j-1)->setText(QString::number(in_t));//д�����������׼�¶ȼƵ��¶Ȳ�
		if (!ui.tbl_in_3->item(i, j+1)->text().trimmed().isEmpty())//д�����
		{
			std_in_t = ui.tbl_std_3->item(1, 0)->text().trimmed().toFloat();
			std_out_t = ui.tbl_std_3->item(1, 1)->text().trimmed().toFloat();
			delta_std = std_in_t - std_out_t;//��׼�¶ȼ��²�

			in_r = ui.tbl_in_3->item(i, j)->text().trimmed().toFloat();//������ֵ
			out_r = ui.tbl_in_3->item(i, j+1)->text().trimmed().toFloat();//������ֵ
			in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);//�����¶�ֵ
			out_t = getPlaTr(pla_r0, pla_a, pla_b, out_r);//�����¶�ֵ
			delta = in_t - out_t;//���첬�����²�

			err = qAbs(qAbs(delta/delta_std) - 1);//��� = (���첬�����²�/��׼�¶ȼ��²�) - 1
			ui.tbl_chkerror_3->item(i, 2)->setText(QString::number(err*100));//���%
		}
	}
	else if (j==2)//�¶ȼƳ�����ֵ
	{
		std_out_t = ui.tbl_std_3->item(1,1)->text().trimmed().toFloat();
		out_r = ui.tbl_in_3->item(i, j)->text().trimmed().toFloat();
		out_t = getPlaTr(pla_r0, pla_a, pla_b, out_r);
		ui.tbl_chkerror_3->item(i, j-1)->setText(QString::number(out_t));//д�����������׼�¶ȼƵ��¶Ȳ�
		if (!ui.tbl_in_3->item(i, j-1)->text().trimmed().isEmpty())//д�����
		{
			std_in_t = ui.tbl_std_3->item(1, 0)->text().trimmed().toFloat();
			std_out_t = ui.tbl_std_3->item(1, 1)->text().trimmed().toFloat();
			delta_std = std_in_t - std_out_t;//��׼�¶ȼ��²�

			in_r = ui.tbl_in_3->item(i, j-1)->text().trimmed().toFloat();//������ֵ
			out_r = ui.tbl_in_3->item(i, j)->text().trimmed().toFloat();//������ֵ
			in_t = getPlaTr(pla_r0, pla_a, pla_b, in_r);//�����¶�ֵ
			out_t = getPlaTr(pla_r0, pla_a, pla_b, out_r);//�����¶�ֵ
			delta = in_t - out_t;//���첬�����²�

			err = qAbs(qAbs(delta/delta_std) - 1);//���
			ui.tbl_chkerror_3->item(i, 2)->setText(QString::number(err*100));//���%
		}
	}
}

void tvercompDlg::on_tbl_chkerror_1_cellChanged(int i, int j)
{
	if (j==0||j==1)//��֧���������
	{
		float std_delta_err = ui.tbl_stderror_1->item(0,j)->text().trimmed().toFloat();//���׼�¶ȼƵ��²�����
		float current_tmp = ui.tbl_chkerror_1->item(i, j)->text().trimmed().toFloat();//��ǰ�¶�ֵ
		float std_tmp = ui.tbl_std_1->item(1, j)->text().trimmed().toFloat();//��׼�¶�ֵ
		float delta_tmp = qAbs(current_tmp - std_tmp);
		ui.tbl_chkerror_1->item(i, j)->setTextColor(delta_tmp > std_delta_err ? QColor(250,0,0) : QColor(0,0,0));
	}
	if (j==2)//������
	{
		float delta_err		= qAbs(ui.tbl_chkerror_1->item(i, j)->text().trimmed().toFloat());
		float std_delta_err = qAbs(ui.tbl_stderror_1->item(0, j)->text().trimmed().toFloat());
		ui.tbl_chkerror_1->item(i, j)->setTextColor(delta_err > std_delta_err ? QColor(250,0,0) : QColor(0,0,0));
	}
}

void tvercompDlg::on_tbl_chkerror_2_cellChanged(int i, int j)
{
	if (j==0||j==1)//��֧���������
	{
		float std_delta_err = ui.tbl_stderror_2->item(0,j)->text().trimmed().toFloat();//���׼�¶ȼƵ��²�����
		float current_tmp = ui.tbl_chkerror_2->item(i, j)->text().trimmed().toFloat();//��ǰ�¶�ֵ
		float std_tmp = ui.tbl_std_1->item(1, j)->text().trimmed().toFloat();//��׼�¶�ֵ
		float delta_tmp = qAbs(current_tmp - std_tmp);
		ui.tbl_chkerror_2->item(i, j)->setTextColor(delta_tmp > std_delta_err ? QColor(250,0,0) : QColor(0,0,0));
	}
	if (j==2)//������
	{
		float delta_err		= qAbs(ui.tbl_chkerror_2->item(i, j)->text().trimmed().toFloat());
		float std_delta_err = qAbs(ui.tbl_stderror_2->item(0, j)->text().trimmed().toFloat());
		ui.tbl_chkerror_2->item(i, j)->setTextColor(delta_err > std_delta_err ? QColor(250,0,0) : QColor(0,0,0));
	}
}

void tvercompDlg::on_tbl_chkerror_3_cellChanged(int i, int j)
{
	if (j==0||j==1)//��֧���������
	{
		float std_delta_err = ui.tbl_stderror_3->item(0,j)->text().trimmed().toFloat();//���׼�¶ȼƵ��²�����
		float current_tmp = ui.tbl_chkerror_3->item(i, j)->text().trimmed().toFloat();//��ǰ�¶�ֵ
		float std_tmp = ui.tbl_std_1->item(1, j)->text().trimmed().toFloat();//��׼�¶�ֵ
		float delta_tmp = qAbs(current_tmp - std_tmp);
		ui.tbl_chkerror_3->item(i, j)->setTextColor(delta_tmp > std_delta_err ? QColor(250,0,0) : QColor(0,0,0));
	}
	if (j==2)//������
	{
		float delta_err		= qAbs(ui.tbl_chkerror_3->item(i, j)->text().trimmed().toFloat());
		float std_delta_err = qAbs(ui.tbl_stderror_3->item(0, j)->text().trimmed().toFloat());
		ui.tbl_chkerror_3->item(i, j)->setTextColor(delta_err > std_delta_err ? QColor(250,0,0) : QColor(0,0,0));
	}
}


void tvercompDlg::on_btn_save_clicked()
{
	insertData();
}

void tvercompDlg::insertData()
{
	if (NULL != m_PlaVerifyRecPtr)
	{
		delete []m_PlaVerifyRecPtr;
 	}
	m_PlaVerifyRecPtr = new T_Platinium_Verify_Record_STR[m_rec_num];
	memset(m_PlaVerifyRecPtr, 0, sizeof(T_Platinium_Verify_Record_STR)*m_rec_num);
	readConfig();
	readChkResult();
	startdb();
	insertPlatiniumVerifyRec(m_PlaVerifyRecPtr, m_rec_num);
	closedb();
}

void tvercompDlg::readConfig()
{
	int std, model, manufac, inst, checker, verify;//��������
	float min_dT;//��С�²�
	std		= m_tvercomp_config->value("chkinfo/stand").toInt();
	model	= m_tvercomp_config->value("chkinfo/model").toInt();
	manufac = m_tvercomp_config->value("chkinfo/manufac").toInt();
	inst	= m_tvercomp_config->value("chkinfo/inst").toInt();
	checker = m_tvercomp_config->value("chkinfo/chker").toInt();
	verify	= m_tvercomp_config->value("chkinfo/verifyer").toInt();
	min_dT	= m_tvercomp_config->value("theoinfo/mintmphead").toFloat();
	float pla_a, pla_b, pla_r0;//���첬�����������
	pla_a	= m_chk_pla_config->value("setting/a").toFloat();
	pla_b	= m_chk_pla_config->value("setting/b").toFloat();
	pla_r0	= m_chk_pla_config->value("setting/r0").toFloat();
	QString std_model = m_std_pla_config->value("in_use/model").toString();
	for(int i=0; i<m_rec_num; i++)
	{
		m_PlaVerifyRecPtr[i].F_CompOrParam	= 0;
		m_PlaVerifyRecPtr[i].F_Standard		= std;
		m_PlaVerifyRecPtr[i].F_Model		= model;
		m_PlaVerifyRecPtr[i].F_ManufactDept	= manufac;
		m_PlaVerifyRecPtr[i].F_VerifyDept	= inst;
		m_PlaVerifyRecPtr[i].F_CheckPerson	= checker;
		m_PlaVerifyRecPtr[i].F_VerifyPerson = verify;
		m_PlaVerifyRecPtr[i].F_MinTmpDiff	= min_dT;

		m_PlaVerifyRecPtr[i].F_PlaCoeA		= pla_a;
		m_PlaVerifyRecPtr[i].F_PlaCoeB		= pla_b;
		m_PlaVerifyRecPtr[i].F_PlaParamR0	= pla_r0;

		strcpy_s(m_PlaVerifyRecPtr[i].F_StdModel, std_model.toAscii());
	}
}

void tvercompDlg::readChkResult()
{
	float std_in_t, std_out_t, std_in_r, std_out_r;//��׼�¶ȼƵĽ������¶�ֵ����ֵ
	QTableWidget* std_tbl_wdg = NULL;//��ǰ�õ��ı�׼�¶ȼƱ��
	QTableWidget* chk_tbl_wdg = NULL;//��ǰ�õ��ı��첬������
	for (int i=0; i<TMP_DIFF_NUMBER; i++)//�²�����
	{
		switch(i)
		{
			case 0://��һ�²��
				std_tbl_wdg = ui.tbl_std_1;
				chk_tbl_wdg = ui.tbl_in_1;
				break;
			case 1://�ڶ��²��
				std_tbl_wdg = ui.tbl_std_2;
				chk_tbl_wdg = ui.tbl_in_2;
				break;
			case 2://�����²��
				std_tbl_wdg = ui.tbl_std_3;
				chk_tbl_wdg = ui.tbl_in_3;
				break;
		}

		std_in_t  = std_tbl_wdg->item(1,0)->text().trimmed().toFloat();
		std_out_t = std_tbl_wdg->item(1,1)->text().trimmed().toFloat();
		std_in_r  = std_tbl_wdg->item(0,0)->text().trimmed().toFloat();
		std_out_r = std_tbl_wdg->item(0,1)->text().trimmed().toFloat();
		for (int j=0; j<VERIFY_NUMBER; j++)//���첬�������
		{
			int idx = i*VERIFY_NUMBER + j;
			m_PlaVerifyRecPtr[idx].F_TmpDiff		= std_in_t - std_out_t;//�²���ֵ
			m_PlaVerifyRecPtr[idx].F_StdInRresis	= std_in_r;
			m_PlaVerifyRecPtr[idx].F_StdOutRresis	= std_out_r;
			m_PlaVerifyRecPtr[idx].F_StdInTmp		= std_in_t;
			m_PlaVerifyRecPtr[idx].F_StdOutTmp		= std_out_t;
			m_PlaVerifyRecPtr[idx].F_PlaSerial		= chk_tbl_wdg->item(j, 0)->text().trimmed().toFloat();
			m_PlaVerifyRecPtr[idx].F_PlaInRresis	= chk_tbl_wdg->item(j, 1)->text().trimmed().toFloat();
			m_PlaVerifyRecPtr[idx].F_PlaOutRresis	= chk_tbl_wdg->item(j, 2)->text().trimmed().toFloat();
		}
	}
	std_tbl_wdg = NULL;
	chk_tbl_wdg = NULL;
}

void tvercompDlg::on_btn_exit_clicked()
{
	this->close();
}