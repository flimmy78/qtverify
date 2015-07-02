#ifndef TVERPARAM_H
#define TVERPARAM_H

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>
#include <QSettings>
#include <QTimer>
#include <QTreeWidgetItem>
#include "ui_tverparam.h"
#include "protocol.h"
#include "comobject.h"

#include "readcomconfig.h"
#include "tverparamparamdlg.h"

#define TMP_DIFF_NUMBER			3//温度点个数
#define VERIFY_NUMBER			12//被检铂电阻对数
#define VERIFY_TIMES			3//每对铂电阻重复检定次数

class TVERPARAM_EXPORT tverparamDlg : public QWidget
{
	Q_OBJECT

public:
	tverparamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~tverparamDlg();

public:

signals:
	void commandSendComplete(void);//读取温度命令已发送完毕

	void firstTmpVerOk(void);//第一温度点检测完毕
	void secondTmpVerOk(void);//第二温度点检测完毕
	void thirdTmpVerOk(void);//第三温度点检测完毕

	void allTmpVerOk(void);//所有的温度点都检测完毕

	public slots:
		void closeEvent(QCloseEvent * event);
		void showEvent(QShowEvent * event);

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

		//void on_tbl_in_1_currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous);
		//void on_tbl_in_1_itemChanged( QTreeWidgetItem * item, int column);

		/******被检铂电阻温度值*******/
		void on_tbl_result_cellChanged(int, int);

		void on_btn_param_clicked();//设置参数
		void on_btn_save_clicked();//保存至数据库
		void on_btn_exit_clicked();//退出

		void disableConfigBtn();
		void disableAllWdg();//禁用所有温度点相关部件
		void disable1stWdg();//禁用第一温度点相关部件
		void disable2ndWdg();//禁用第二温度点相关部件
		void disable3rdWdg();//禁用第三温度点相关部件
		void enable1stWdg();//启用第一温度点相关部件
		void enable2ndWdg();//启用第二温度点相关部件
		void enable3rdWdg();//启用第三温度点相关部件

		void firstTmpVerOk_slot();
		void secondTmpVerOk_slot();
		void thirdTmpVerOk_slot();

		void setTblStd1(const QString& tempStr);
		void setTblStd2(const QString& tempStr);
		void setTblStd3(const QString& tempStr);
		void sendCommands();
		void clearComObjs();

		void calcBasicErr();//计算全部表的铂电阻的基本误差
private:
	Ui::PlaParamDlgClass ui;
	tverparamparamDlg *m_PlaParamParamDlg;

	QTimer* m_sendTimer;//定时发送命令
	sti1062Acommand m_readCommand;

	QSettings* m_tverparam_config;//读取参数法的配置, 型号, 标准, 检验员等
	QSettings* m_std_pla_config;//标准温度计参数
	QSettings* m_chk_pla_config;//被检温度计参数

	ReadComConfig* m_readComConfig;//串口设置
	Sti1062aComObject* m_tempObj;//标准温度计串口对象

	T_Platinum_Verify_Record_PTR m_PlaVerifyRecPtr;//检测结果记录
	QString m_timeStamp; //时间戳
	int m_rec_num;//需要保存的记录个数
	int m_chanel;//使用的标准温度计的通道号
	int m_saved_times;//存数据库次数, 作为检测次数的索引
	int m_temp_index;//检测温度点的索引

	int m_current_temp_seq;//当前温度点
	int m_current_chk_seq;//当前检测点

	bool m_tbl_inited;//表格初始化完毕
private:
	void initTbls();
	void initTbl(QTableWidget*);//初始化表格
	void insertData();
	void readConfig();//读取标准温度计、被检铂电阻、检测参数等
	void readChkResult();//读取被检铂电阻检测结果
	
	void calcBasicErrPerMeter(int);//计算但支热表的进出口铂电阻的基本误差
	float* getTmpPntBasicErr(int, QString);
};

#endif//TVERPARAM_H