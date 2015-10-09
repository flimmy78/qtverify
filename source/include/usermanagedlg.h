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
#include <QSqlRelationalTableModel>

#include "ui_usermanagedlg.h"

class USERMANAGE_EXPORT UserManageDlg : public QWidget
{
	Q_OBJECT

public:
	explicit UserManageDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~UserManageDlg();

	QSqlRelationalTableModel *m_userModel;

	void initUserList();

private slots:
	void on_btnSubmit_clicked();
	void on_btnRevert_clicked();
	void on_btnAdd_clicked();
	void on_btnDelete_clicked();
	void on_btnExit_clicked();

	void on_userTableView_clicked(const QModelIndex &);

private:
	Ui::UserManageDlgClass ui;	
};

#endif // USERMANAGEDLG_H