#include "tvercomp.h"

tvercompDlg::tvercompDlg(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	m_PlaCompParamDlg = NULL;
}

tvercompDlg::~tvercompDlg()
{

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

}

void tvercompDlg::on_btn_read_2_clicked()
{

}

void tvercompDlg::on_btn_read_3_clicked()
{

}

void tvercompDlg::on_btn_clear_1_clicked()
{

}

void tvercompDlg::on_btn_clear_2_clicked()
{

}

void tvercompDlg::on_btn_clear_3_clicked()
{

}

void tvercompDlg::on_tbl_std_1_cellChanged(int, int)
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

}

void tvercompDlg::on_btn_exit_clicked()
{
	this->close();
}

void tvercompDlg::closeEvent(QCloseEvent * event)
{
	if ( NULL != m_PlaCompParamDlg)
	{
		delete m_PlaCompParamDlg;
		m_PlaCompParamDlg = NULL;
	}
}