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
	QSqlTableModel *m_manudeptModel;
	QSqlTableModel *m_verifydeptModel;
	QSqlTableModel *m_modelModel;
	QSqlTableModel *m_deviceModel;

	void initUserList();
	void initManuDept();
	void initVerifyDept();
	void initMeterModel();
	void initDeviceInfo();
public slots:
	void closeEvent(QCloseEvent *);
signals:
	void signalClosed();
private slots:
	void on_btnExit_clicked();

	//T_User_Def_Tab
	void on_btnSubmit_clicked();
	void on_btnRevert_clicked();
	void on_btnAdd_clicked();
	void on_btnDelete_clicked();
	void on_userTableView_clicked(const QModelIndex &);

	//T_Manufacture_Dept
	void on_btnSubmit_2_clicked();
	void on_btnRevert_2_clicked();
	void on_btnAdd_2_clicked();
	void on_btnDelete_2_clicked();

	//T_Verify_Dept
	void on_btnSubmit_3_clicked();
	void on_btnRevert_3_clicked();
	void on_btnAdd_3_clicked();
	void on_btnDelete_3_clicked();

	//T_Meter_Model
	void on_btnSubmit_4_clicked();
	void on_btnRevert_4_clicked();
	void on_btnAdd_4_clicked();
	void on_btnDelete_4_clicked();

	//T_Verify_Device_Info
	void on_btnSubmit_5_clicked();
	void on_btnRevert_5_clicked();
	void on_btnAdd_5_clicked();
	void on_btnDelete_5_clicked();

private:
	Ui::UserManageDlgClass ui;	
};

#endif // USERMANAGEDLG_H