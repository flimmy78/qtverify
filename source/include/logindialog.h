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

class LOGINDIALOG_EXPORT LoginDialog : public QDialog
{
	Q_OBJECT

public:
	explicit LoginDialog(QWidget *parent = 0);
	~LoginDialog();

	void initUserComboBox();
	int getCurUserID();
	int getCurRoleID();

private slots:
	void on_loginButton_clicked();
	void on_quitButton_clicked();

private:
	Ui::LoginDialogClass ui;	
	int m_curUserID;
	int m_curRoleID;
};

#endif // LOGINDIALOGDLG_H