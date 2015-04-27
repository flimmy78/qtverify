#include "tverparam.h"

tverparamDlg::tverparamDlg(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	m_PlaCompParamDlg = NULL;
}

tverparamDlg::~tverparamDlg()
{

}


void tverparamDlg::on_btn_param_clicked()
{
	if ( NULL == m_PlaCompParamDlg)
	{
		m_PlaCompParamDlg = new tverparamparamDlg;
	}
	else
	{
		delete m_PlaCompParamDlg;
		m_PlaCompParamDlg = new tverparamparamDlg;
	}

	m_PlaCompParamDlg->show();
}

void tverparamDlg::on_btn_excel_clicked()
{

}

void tverparamDlg::on_btn_save_clicked()
{

}

void tverparamDlg::on_btn_exit_clicked()
{
	this->close();
}

void tverparamDlg::closeEvent(QCloseEvent * event)
{
	if ( NULL != m_PlaCompParamDlg)
	{
		delete m_PlaCompParamDlg;
		m_PlaCompParamDlg = NULL;
	}
}