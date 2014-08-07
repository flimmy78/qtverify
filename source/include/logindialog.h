#ifndef LOGINDIALOGDLG_H
#define LOGINDIALOGDLG_H


#ifdef LOGINDIALOG_DLL
#  ifdef WIN32
#  define LOGINDIALOG_EXPORT __declspec(dllexport)
#  else
#  define LOGINDIALOG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define LOGINDIALOG_EXPORT __declspec(dllimport)
#  else
#  define LOGINDIALOG_EXPORT
#  endif
#endif


#include <QtGui/QWidget>

#include "ui_logindialog.h"
#include "qtexdb.h"

class LOGINDIALOG_EXPORT LoginDialog : public QDialog
{
	Q_OBJECT

public:
	explicit LoginDialog(QWidget *parent = 0);
	~LoginDialog();

	void initUserComboBox();

private slots:
	void on_loginButton_clicked();
	void on_quitButton_clicked();

private:
	Ui::LoginDialogClass ui;	
};

#endif // LOGINDIALOGDLG_H