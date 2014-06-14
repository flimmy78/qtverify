#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

#include "SetComFrm.h"

SetComFrm::SetComFrm(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	gui.setupUi(this);
}

SetComFrm::~SetComFrm()
{

}
void SetComFrm::on_btnExit_clicked()
{
	close();
}

void SetComFrm::on_btnSave_clicked()
{

}