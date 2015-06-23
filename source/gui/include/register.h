#ifndef REGISTER_H
#define REGISTER_H

#include <QtGui/QWidget>

#include "ui_register.h"

class RegisterDlg : public QWidget
{
	Q_OBJECT

public:
	RegisterDlg(QString code="", QWidget *parent = 0, Qt::WFlags flags = 0);
	~RegisterDlg();


	void closeEvent(QCloseEvent * event);

public slots:

private:
	Ui::RegisterDlgClass ui;

private slots:
	void on_btnRegister_clicked();
	void on_btnExit_clicked();

};

#endif // REGISTER_H
