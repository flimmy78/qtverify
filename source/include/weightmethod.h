#ifndef WEIGHTMETHOD_H
#define WEIGHTMETHOD_H

#ifdef WEIGHTMETHOD_DLL
#  ifdef WIN32
#  define WEIGHTMETHOD_EXPORT __declspec(dllexport)
#  else
#  define WEIGHTMETHOD_EXPORT
#  endif
#else
#  ifdef WIN32
#  define WEIGHTMETHOD_EXPORT __declspec(dllimport)
#  else
#  define WEIGHTMETHOD_EXPORT
#  endif
#endif

#define VALID_YEAR	2 //�����Ч�� 2��
#define BALANCE_START_VALUE		2 //��ƽ��ֵ

#define TIMEOUT_TEMPER		500 //ÿ0.5��������һ���¶�ֵ

/*
** �����
*/
#define COLUMN_METER_NUMBER 0 //�����
#define COLUMN_FLOW_POINT	1 //������
#define COLUMN_METER_START	2 //���ֵ��
#define COLUMN_METER_END	3 //����ֵ��
#define COLUMN_BAL_START	4 //��ƽ��ֵ
#define COLUMN_BAL_END		5 //��ƽ��ֵ
#define COLUMN_TEMPER		6 //�¶���
#define COLUMN_DENSITY		7 //�ܶ���
#define COLUMN_STD_VALUE	8 //��׼ֵ
#define COLUMN_ERROR		9 //ʾֵ�����


#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>
#include <QtGui/QItemDelegate>

#include "ui_weightmethod.h"
#include "parasetdlg.h"
#include "comobject.h"
#include "readcomconfig.h"
#include "algorithm.h"


//ID�У�ֻ������1��12������   
//����QLineEditί�к�������ʽ�������������   
class UserIDDelegate : public QItemDelegate  
{  
	Q_OBJECT  
public:  
	UserIDDelegate(QObject *parent = 0): QItemDelegate(parent) { }  
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,  
		const QModelIndex &index) const  
	{  
		QLineEdit *editor = new QLineEdit(parent);  
		QRegExp regExp("[0-9]{0,10}");  
		editor->setValidator(new QRegExpValidator(regExp, parent));  
		return editor;  
	}  
	void setEditorData(QWidget *editor, const QModelIndex &index) const  
	{  
		QString text = index.model()->data(index, Qt::EditRole).toString();  
		QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);  
		lineEdit->setText(text);  
	}  
	void setModelData(QWidget *editor, QAbstractItemModel *model,  
		const QModelIndex &index) const  
	{  
		QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);  
		QString text = lineEdit->text();  
		model->setData(index, text, Qt::EditRole);  
	}  
	void updateEditorGeometry(QWidget *editor,  
		const QStyleOptionViewItem &option, const QModelIndex &index) const  
	{  
		editor->setGeometry(option.rect);  
	}  
};  


class WEIGHTMETHOD_EXPORT WeightMethodDlg : public QWidget
{
	Q_OBJECT

public:
	WeightMethodDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~WeightMethodDlg();

	QDataWidgetMapper *m_mapper;

	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;


	QTimer *m_exaustTimer; //������ʱ��

	QTimer *m_balTimer; //ģ����ƽ��ʱˢ���� �����ڲ���
	float m_balValue;   //ģ����ƽֵ
	float m_tempValue;  //ģ���¶�ֵ

	ComThread m_balanceThread; //��ƽ�ɼ��߳�
	BalanceComObject *m_balanceObj;

	ComThread m_tempThread;  //�¶Ȳɼ��߳�
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

	ComThread m_valveThread;   //���ſ����߳�
	ControlComObject *m_controlObj;
	QMap<int, bool> m_valveStatus; //���ź��뷧��״̬��ӳ���ϵ
	QMap<int, QToolButton*> m_valveBtn;	
	int m_nowPortNo;	//��ǰ���Ʒ��Ŷ˿ں�

	ComThread *m_meterThread;	//������ͨѶ�߳�
	MeterComObject *m_meterObj;	//


	CAlgorithm *m_chkAlg;//�춨�����õ��ļ��㷽��

	bool m_stopFlag;     //�رս�����˳�

	//�춨������صĿ��Ʋ��� begin
	Quality_Params_PTR m_nowParams; //��ǰ�춨����
	bool m_continueVerify;    //�Ƿ������춨
	bool m_resetZero;         //�Ƿ��ֵ����
	bool m_autopick;          //�Ƿ��Զ��ɼ�
	int m_flowPointNum;       //������ĸ���
	int m_exaustSecond;		  //����ʱ��
	INT16 m_totalFlag;        //1:�����춨��2:�����춨
	int m_standard;           //����
	int m_model;              //���ͺ�
	int m_meterType;          //������
	int m_manufac;			  //���쳧��(��³����, ���)

	int m_tempCount;		  //����ƽ���¶��õ��ۼӼ�����
	int m_maxMeterNum;        //������������������������
	int m_validMeterNum;          //ʵ�ʼ��ĸ���
	QMap<int, int> m_meterPosMap; //��������λ�ŵ�ӳ���ϵ
	QMap<int, float> m_gradeErr;  //��ͬ�ȼ��ȱ��Ӧ�ı�׼���

	float *m_meterStartValue; //�����ĳ�ֵ
	float *m_meterEndValue;   //��������ֵ
	float *m_meterTemper;	  //�������¶�
	float *m_meterDensity;    //�������ܶ�
	float *m_meterStdValue;   //�����ı�׼ֵ
	float *m_meterError;	  //���������
	float m_balStartV;        //��ƽ��ֵ
	float m_balEndV;          //��ƽ��ֵ
	double m_pipeInTemper;    //����¶�
	double m_pipeOutTemper;   //�����¶�
	//�춨������صĿ��Ʋ��� end

	Record_Quality_PTR m_recPtr; //��Ч�ļ춨��¼
	QString m_timeStamp; //ʱ��� ����
	QString m_nowDate;  
	QString m_validDate;

	float m_flowPoint;
	int m_nowOrder;				//��ǰ�춨����

	bool m_inputStartValue; //�ȴ������ֵ״̬
	bool m_inputEndValue;   //�ȴ�������ֵ״̬

	bool m_startValueFlag;

	ReadComConfig *m_readComConfig; //����������
	PortSet_Ini_STR m_portsetinfo;  //�˿�����

	void initBalanceCom();     //��ƽ����
	void initTemperatureCom(); //�¶Ȳɼ�����
	void initControlCom();     //���ſ��ƴ���
	void initMeterCom();       //��������
	void initValveStatus();	   //��ʼ������״̬

	int isComAndPortNormal();   //���ڡ��˿������Ƿ�����
	int isWaterOutValveOpen();  //����ˮ�����Ƿ��
	int isDataCollectNormal();	//������ݲɼ��Ƿ���������ƽ���¶ȡ���������Ƶȣ�
	int isAllMeterInVerifyStatus(); //�ж��������ѽ���춨״̬
	int isMeterPosValid(int row);   //�жϱ�λ���Ƿ���Ч(�ñ�λ�Ƿ���Ҫ���)


public slots:
	void closeEvent(QCloseEvent * event);
	void removeSubTab(int index);

	int readNowParaConfig();	 //��ȡ��ǰ�춨����
	void showNowKeyParaConfig(); //��ʾ��ǰ�ؼ�����������Ϣ
	void setTableRowCount();     //���ñ������

	void on_btnExhaust_clicked(); //���"����"��ť
	void on_btnStart_clicked();   //���"��ʼ"��ť
	void on_btnNext_clicked();    //���"��һ��"��ť
	void on_btnStop_clicked();    //���"��ֹ���"��ť
	int openAllValuesAndPump();   //�����з��ź�ˮ��
	void slotExaustFinished();    //����ʱ�����
	int readMeterNumber();        //��ȡ���
	int setMeterVerifyStatus();   //�������������춨״̬
	int closeAllFlowPointValves();//�ر����������㷧��
	int closeWaterOutValve();     //�رշ�ˮ��
	int openWaterOutValve();      //�򿪷�ˮ��
	int openBigFlowValve();       //�򿪴������㷧��
	int closeBigFlowValve();      //�رմ������㷧��
	int judgeBalanceInitValue(float v);    //�ж���ƽ����
	int judgeBalanceAndCalcTemper(float targetV); //�ж���ƽ���������ۼӽ������¶ȣ�ÿ���ۼ�һ�Σ����ڼ��������ƽ���¶�
	void startVerify();           //��ʼ�춨
	int getValidMeterNum();       //��ȡ��Ч�ļ�����()
	int judgeBalanceCapacity();   //�ж���ƽ�����Ƿ��ܹ�����춨���� �����춨
	int judgeBalanceCapacitySingle(int order); //�ж���ƽ�����Ƿ��ܹ�����춨���� �������춨
	int prepareVerifyFlowPoint(int order);     //׼������������ļ춨
	int startVerifyFlowPoint(int order);       //��ʼ����������ļ춨
	int openValve(UINT8 portno);    //�򿪿��Ʒ�
	int closeValve(UINT8 portno);   //�رտ��Ʒ�
	int getMeterStartValue();     //��ȡ���ֵ
	void makeStartValueByLastEndValue(); //��һ�ε���ֵ��Ϊ���εĳ�ֵ
	int getMeterEndValue();       //��ȡ����ֵ
	int calcAllMeterError();//�������б��������
	int calcMeterError(int idx); //����ĳ��������

	void slotFreshBalanceValue(const QString& Str);     //ˢ����ƽ��ֵ
	void slotFreshComTempValue(const QString& tempStr); //ˢ���¶�ֵ
	void slotFreshFlow(); //��������

	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //�̵������سɹ���Ӧ�Ĳۺ���
	void slotSetRegulateOk();     //���ڷ����سɹ���Ӧ�Ĳۺ���

	void slotSetMeterNumber(const QString& comName, const QString& meterNumber);
	void slotSetMeterData(const QString& comName, const QString& flow, const QString& heat);
	void setValveBtnBackColor(QToolButton *btn, bool status); //���÷��Ű�ť����ɫ
	void setRegBtnBackColor(QPushButton *btn, bool status);	  //���õ��ڷ���ť����ɫ

	void on_btnParaSet_clicked();	   //��������
	void on_btnWaterIn_clicked();      //��ˮ��
	void on_btnWaterOut_clicked();     //��ˮ��
	void on_btnValveBig_clicked();     //��������
	void on_btnValveMiddle1_clicked(); //����һ
	void on_btnValveMiddle2_clicked(); //������
	void on_btnValveSmall_clicked();   //С������

	void on_btnWaterPumpStart_clicked(); //����ˮ��
	void on_btnWaterPumpStop_clicked();  //ֹͣˮ��

	void on_tableWidget_cellChanged(int row, int column);
	int saveAllVerifyRecords(); //�������б����ļ춨��¼
	void clearTableContents();

	void freshBigBalaceValue();   //ˢ�´���ƽ��ֵ �����ڲ��� ģ����ƽ��ֵ�仯

	void on_btnReadMeter_clicked(); //����ť
	void on_btnExit_clicked();//�˳���ť
	

private slots:

signals:

private:
	Ui::WeightMethodClass ui;

};

#endif //WEIGHTMETHOD_H