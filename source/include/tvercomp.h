#ifndef TVERCOMP_H
#define TVERCOMP_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QTimer>
#include "protocol.h"
#include "readcomconfig.h"
#include "comobject.h"
#include "ui_tvercomp.h"
#include "tvercompparamdlg.h"

#define TMP_DIFF_NUMBER			3//温差点个数
#define VERIFY_NUMBER			12//被检铂电阻对数

class TVERCOMP_EXPORT tvercompDlg : public QWidget
{
	Q_OBJECT

public:
	tvercompDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~tvercompDlg();

signals:
	void commandSendComplete(void);//读取温度命令已发送完毕

public slots:
	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent * event);
	void setTblColWidth(QTableWidget*);
	/******采集标准温度计数值*********/
	void on_btn_read_1_clicked();
	void on_btn_read_2_clicked();
	void on_btn_read_3_clicked();

	/******清空标准温度计数值*********/
	void on_btn_clear_1_clicked();
	void on_btn_clear_2_clicked();
	void on_btn_clear_3_clicked();

	/******标准温度计数值*********/
	void on_tbl_std_1_cellChanged(int, int);
	void on_tbl_std_2_cellChanged(int, int);
	void on_tbl_std_3_cellChanged(int, int);

	/******被检铂电阻数值*********/
	void on_tbl_in_1_cellChanged(int, int);
	void on_tbl_in_2_cellChanged(int, int);
	void on_tbl_in_3_cellChanged(int, int);

	void on_tbl_chkerror_1_cellChanged(int, int);
	void on_tbl_chkerror_2_cellChanged(int, int);
	void on_tbl_chkerror_3_cellChanged(int, int);

	void on_btn_param_clicked();
	void on_btn_save_clicked();//保存至数据库
	void on_btn_exit_clicked();

	void setTblStd1(const QString& tempStr);
	void setTblStd2(const QString& tempStr);
	void setTblStd3(const QString& tempStr);
	void sendCommands();
	void clearComObjs();
	void insertData();
private:
	Ui::PlaCompDlgClass ui;
	tvercompparamDlg *m_PlaCompParamDlg;

	QTimer* m_sendTimer;//定时发送命令
	stdTempCommand m_readCommand;

	QSettings* m_tvercomp_config;//温度计比较法参数设置
	QSettings* m_std_pla_config;//标准温度计参数
	QSettings* m_chk_pla_config;//被检温度计参数
	ReadComConfig* m_readComConfig;//串口设置
	StdTempComObject* m_tempObj;//标准温度计串口对象

	T_Platinum_Verify_Record_PTR m_PlaVerifyRecPtr;//检测结果记录
	QString m_timeStamp; //时间戳
	int m_rec_num;//需要保存的记录个数

	float m_min_delta_tmp;//最小温差δΘmin
private:
	void readConfig();//读取标准温度计、被检铂电阻、检测参数等
	void readChkResult();//读取被检铂电阻检测结果
};

#endif//TCHKCOMP_H