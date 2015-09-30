#ifndef USERMANAGEDLG_H
#define USERMANAGEDLG_H


#ifdef USERMANAGEDLG_DLL
#  ifdef WIN32
#  define USERMANAGE_EXPORT __declspec(dllexport)
#  else
#  define USERMANAGE_EXPORT
#  endif
#else
#  ifdef WIN32
#  define USERMANAGE_EXPORT __declspec(dllimport)
#  else
#  define USERMANAGE_EXPORT
#  endif
#endif


#include <QtGui/QWidget>

#include "ui_usermanagedlg.h"

class USERMANAGE_EXPORT UserManageDlg : public QWidget
{
	Q_OBJECT

public:
	explicit UserManageDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~UserManageDlg();


private slots:
	void on_btnSave_clicked();
	void on_btnExit_clicked();

private:
	Ui::UserManageDlgClass ui;	
};

#endif // USERMANAGEDLG_H