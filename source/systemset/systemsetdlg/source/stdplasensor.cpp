#include "algorithm.h"
#include "stdplasensor.h"

stdplasensorDlg::stdplasensorDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	m_config = new QSettings(getFullIniFileName("stdplasensor.ini"), QSettings::IniFormat);

	readInUse();
	readmodelconfig();
}

stdplasensorDlg::~stdplasensorDlg()
{

}

void stdplasensorDlg::closeEvent(QCloseEvent * event)
{
	if (m_config)
	{
		delete m_config;
		m_config = NULL;
	}
}

void stdplasensorDlg::on_btn_pt25_save_clicked()
{
	m_config->beginGroup("pt25");
	m_config->setValue("in_rtp", ui.lineEdit_pt25_in_rtp->text());
	m_config->setValue("in_a", ui.lineEdit_pt25_in_a->text());
	m_config->setValue("in_b", ui.lineEdit_pt25_in_b->text());
	m_config->setValue("out_rtp", ui.lineEdit_pt25_out_rtp->text());
	m_config->setValue("out_a", ui.lineEdit_pt25_out_a->text());
	m_config->setValue("out_b", ui.lineEdit_pt25_out_b->text());
	m_config->endGroup();
}

void stdplasensorDlg::on_btn_pt25_exit_clicked()
{
	this->close();
}

void stdplasensorDlg::on_btn_pt100_calc_clicked()
{
	calcPt100In();
	calcPt100Out();
}

void stdplasensorDlg::on_btn_pt100_save_clicked()
{
	m_config->beginGroup("pt100");
	m_config->setValue("in_rtp", ui.lineEdit_pt100_in_rtp->text());
	m_config->setValue("in_a", ui.lineEdit_pt100_in_a->text());
	m_config->setValue("in_b", ui.lineEdit_pt100_in_b->text());
	m_config->setValue("out_rtp", ui.lineEdit_pt100_out_rtp->text());
	m_config->setValue("out_a", ui.lineEdit_pt100_out_a->text());
	m_config->setValue("out_b", ui.lineEdit_pt100_out_b->text());
	m_config->endGroup();
}

void stdplasensorDlg::on_btn_pt100_exit_clicked()
{
	this->close();
}

void stdplasensorDlg::on_btn_model_save_clicked()
{
	const QObjectList list=ui.gBox_model->children();
	foreach(QObject *obj, list)
	{
		QString class_name = QString::fromAscii( obj->metaObject()->className() );
		if (class_name == "QRadioButton")
		{
			if (((QRadioButton*)obj)->isChecked())
			{
				m_config->beginGroup("in_use");
				m_config->setValue("model", ((QRadioButton*)obj)->text());
				m_config->endGroup();
			}
		}
	}
}

void stdplasensorDlg::on_gBox_pt25_clicked()
{
	if (ui.gBox_pt25->isChecked())
	{
		ui.gBox_pt100->setChecked(false);
		readpt25config();
	}
}

void stdplasensorDlg::on_gBox_pt100_clicked()
{
	if (ui.gBox_pt100->isChecked())
	{
		ui.gBox_pt25->setChecked(false);
		readpt100config();
	}
}

void stdplasensorDlg::readpt25config()
{
	ui.lineEdit_pt25_in_rtp->setText(m_config->value("pt25/in_rtp").toString());
	ui.lineEdit_pt25_in_a->setText(m_config->value("pt25/in_a").toString());
	ui.lineEdit_pt25_in_b->setText(m_config->value("pt25/in_b").toString());
	ui.lineEdit_pt25_out_rtp->setText(m_config->value("pt25/out_rtp").toString());
	ui.lineEdit_pt25_out_a->setText(m_config->value("pt25/out_a").toString());
	ui.lineEdit_pt25_out_b->setText(m_config->value("pt25/out_b").toString());
}

void stdplasensorDlg::readpt100config()
{
	ui.lineEdit_pt100_in_rtp->setText(m_config->value("pt100/in_rtp").toString());
	ui.lineEdit_pt100_in_a->setText(m_config->value("pt100/in_a").toString());
	ui.lineEdit_pt100_in_b->setText(m_config->value("pt100/in_b").toString());
	ui.lineEdit_pt100_out_rtp->setText(m_config->value("pt100/out_rtp").toString());
	ui.lineEdit_pt100_out_a->setText(m_config->value("pt100/out_a").toString());
	ui.lineEdit_pt100_out_b->setText(m_config->value("pt100/out_b").toString());
}

void stdplasensorDlg::readmodelconfig()
{
	const QObjectList list=ui.gBox_model->children();
	foreach(QObject *obj, list)
	{
		QString class_name = QString::fromAscii( obj->metaObject()->className() );
		if (class_name == "QRadioButton")
		{
			if (((QRadioButton*)obj)->text() == m_config->value("in_use/model").toString())
			{
				((QRadioButton*)obj)->setChecked(true);
			}			
		}
	}
}

void stdplasensorDlg::readInUse()
{
	QString in_user = m_config->value("in_use/pt").toString();
	if (in_user == "pt25")
	{
		readpt25config();
		ui.gBox_pt25->setChecked(true);
		ui.gBox_pt100->setChecked(false);
	}
	else
	{
		readpt100config();
		ui.gBox_pt25->setChecked(false);
		ui.gBox_pt100->setChecked(true);
	}	
}

void stdplasensorDlg::calcPt100In()
{
	pla_T_R_PTR prt = new pla_T_R_STR[3];
	prt[0].tmp = ui.tbl_pt100_in->item(0,0)->text().toFloat();
	prt[1].tmp = ui.tbl_pt100_in->item(0,1)->text().toFloat();
	prt[2].tmp = ui.tbl_pt100_in->item(0,2)->text().toFloat();

	prt[0].resis = ui.tbl_pt100_in->item(1,0)->text().toFloat();
	prt[1].resis = ui.tbl_pt100_in->item(1,1)->text().toFloat();
	prt[2].resis = ui.tbl_pt100_in->item(1,2)->text().toFloat();

	plaParam_PTR m_pla_param = getPlaParam(prt);

	ui.lineEdit_pt100_in_rtp->setText(QString::number(m_pla_param->r0));
	ui.lineEdit_pt100_in_a->setText(QString::number(m_pla_param->a));
	ui.lineEdit_pt100_in_b->setText(QString::number(m_pla_param->b));
	if (prt)
	{
		delete prt;
		prt = NULL;
	}

	if (m_pla_param)
	{
		delete m_pla_param;
		m_pla_param = NULL;
	}
}

void stdplasensorDlg::calcPt100Out()
{
	pla_T_R_PTR prt = new pla_T_R_STR[3];
	prt[0].tmp = ui.tbl_pt100_out->item(0,0)->text().toFloat();
	prt[1].tmp = ui.tbl_pt100_out->item(0,1)->text().toFloat();
	prt[2].tmp = ui.tbl_pt100_out->item(0,2)->text().toFloat();

	prt[0].resis = ui.tbl_pt100_out->item(1,0)->text().toFloat();
	prt[1].resis = ui.tbl_pt100_out->item(1,1)->text().toFloat();
	prt[2].resis = ui.tbl_pt100_out->item(1,2)->text().toFloat();

	plaParam_PTR m_pla_param = getPlaParam(prt);

	ui.lineEdit_pt100_out_rtp->setText(QString::number(m_pla_param->r0));
	ui.lineEdit_pt100_out_a->setText(QString::number(m_pla_param->a));
	ui.lineEdit_pt100_out_b->setText(QString::number(m_pla_param->b));
	if (prt)
	{
		delete prt;
		prt = NULL;
	}

	if (m_pla_param)
	{
		delete m_pla_param;
		m_pla_param = NULL;
	}
}
