#ifndef MASTERSLAVESET_H
#define MASTERSLAVESET_H

#ifdef MASTERSLAVESET_DLL
#  ifdef WIN32
#  define MASTERSLAVE_EXPORT __declspec(dllexport)
#  else
#  define MASTERSLAVE_EXPORT
#  endif
#else
#  ifdef WIN32
#  define MASTERSLAVE_EXPORT __declspec(dllimport)
#  else
#  define MASTERSLAVE_EXPORT
#  endif
#endif


#include <QtGui/QWidget>
#include <QCloseEvent>
#include <QtCore/QSettings>
#include <QtGui/QButtonGroup>

#include "ui_masterslaveset.h"
#include "basedef.h"

class MASTERSLAVE_EXPORT CMasterSlave : public QWidget
{
	Q_OBJECT

public:
	CMasterSlave(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CMasterSlave();

	MasterSlave_Ini_STR m_masterslaveIni; //主机-从机配置
	QSettings *m_settings;
	QButtonGroup *btnGrpHostFlag;

public slots:
	void closeEvent(QCloseEvent* event);
signals:
	void signalClosed();
private:
	Ui::MasterSlaveClass ui;

private slots:
	void initSettingsInfo();

	void on_btnSave_clicked();
	void on_btnExit_clicked();
	void on_checkBoxNetMode_stateChanged(int state);
	void on_btnGrpHostFlag_clicked(int id);
};

#endif //MASTERSLAVESET_H