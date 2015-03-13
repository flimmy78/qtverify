/********************************************************************************
** Form generated from reading UI file 'datatestdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATATESTDLG_H
#define UI_DATATESTDLG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataTestDlgClass
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    Q3ButtonGroup *buttonGroup;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    Q3ButtonGroup *buttonGroup_2;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEdit;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QLabel *label_7;
    QGroupBox *groupBox_heatmeter;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_7;
    QLabel *label_25;
    QLineEdit *lnEditMeterNo;
    QLabel *label_26;
    QLineEdit *lnEditMeterTempIn;
    QLabel *label_27;
    QLineEdit *lnEditMeterTempOut;
    QLabel *label_28;
    QLineEdit *lnEditMeterTotalFlow;
    QLabel *label_29;
    QLineEdit *lnEditMeterHeat;
    QLabel *label_31;
    QDateEdit *dateEditMeter;
    QLabel *label_32;
    QLineEdit *lnEditNewMeterNo;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_13;
    QGridLayout *gridLayout_12;
    QComboBox *parityComboBox;
    QLabel *label_23;
    QLabel *label_21;
    QComboBox *baudRateComboBox;
    QComboBox *dataBitsComboBox;
    QComboBox *stopBitsComboBox;
    QLabel *label_19;
    QLabel *label_22;
    QLabel *label_20;
    QComboBox *portNameComboBox;
    QPushButton *btnCloseCom;
    QPushButton *btnOpenCom;
    QPushButton *btnSetVerifyStatus;
    QPushButton *btnReadMeterData;
    QPushButton *btnModifyMeterNo;
    QPushButton *btnModifyFlowCoe;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_8;
    QLabel *label_24;
    QLabel *label_30;
    QLabel *label_37;
    QLabel *label_33;
    QLineEdit *lnEditBigNewError;
    QLineEdit *lnEditBigOldError;
    QLineEdit *lnEditBigOldCoe;
    QLabel *label_34;
    QLineEdit *lnEditMid2NewError;
    QLineEdit *lnEditMid2OldError;
    QLineEdit *lnEditMid2OldCoe;
    QLabel *label_35;
    QLineEdit *lnEditMid1NewError;
    QLineEdit *lnEditMid1OldError;
    QLineEdit *lnEditMid1OldCoe;
    QLabel *label_36;
    QLineEdit *lnEditSmallNewError;
    QLineEdit *lnEditSmallOldError;
    QLineEdit *lnEditSmallOldCoe;
    QGroupBox *groupBox_2;
    QPushButton *btnWaterIn;
    QPushButton *btnValveBig;
    QPushButton *btnValveMiddle1;
    QPushButton *btnWaterOut;
    QPushButton *btnWaterPump;
    QPushButton *btnValveMiddle2;
    QPushButton *btnValveSmall;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_15;
    QGridLayout *gridLayout_11;
    QLabel *label_18;
    QSpinBox *spinBoxFreq;
    QPushButton *btnSetFreq;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout_14;
    QPushButton *btnRegulate1;
    QPushButton *btnQueryStatus;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    QLabel *label_8;
    QLineEdit *lnEditBigBalance;
    QLabel *label_13;
    QLabel *label_9;
    QLineEdit *lnEditSmallBalance;
    QLabel *label_14;
    QLabel *label_10;
    QLineEdit *lnEditFlowRate;
    QLabel *label_15;
    QLabel *label_11;
    QLineEdit *lnEditTempIn;
    QLabel *label_16;
    QLabel *label_12;
    QLineEdit *lnEditTempOut;
    QLabel *label_17;
    QPushButton *btnParaSet;
    QPushButton *btnExit;

    void setupUi(QWidget *DataTestDlgClass)
    {
        if (DataTestDlgClass->objectName().isEmpty())
            DataTestDlgClass->setObjectName(QString::fromUtf8("DataTestDlgClass"));
        DataTestDlgClass->setWindowModality(Qt::ApplicationModal);
        DataTestDlgClass->resize(782, 707);
        groupBox = new QGroupBox(DataTestDlgClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(11, 11, 761, 173));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        buttonGroup = new Q3ButtonGroup(groupBox);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->setColumnLayout(0, Qt::Vertical);
        gridLayout_2 = new QGridLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(buttonGroup->layout());
        if (boxlayout)
            boxlayout->addLayout(gridLayout_2);
        gridLayout_2->setAlignment(Qt::AlignTop);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButton = new QRadioButton(buttonGroup);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        gridLayout_2->addWidget(radioButton, 0, 0, 1, 1);

        radioButton_2 = new QRadioButton(buttonGroup);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        gridLayout_2->addWidget(radioButton_2, 0, 1, 1, 1);


        gridLayout_5->addWidget(buttonGroup, 0, 0, 1, 1);

        buttonGroup_2 = new Q3ButtonGroup(groupBox);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
        buttonGroup_2->setColumnLayout(0, Qt::Vertical);
        gridLayout = new QGridLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(buttonGroup_2->layout());
        if (boxlayout1)
            boxlayout1->addLayout(gridLayout);
        gridLayout->setAlignment(Qt::AlignTop);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioButton_3 = new QRadioButton(buttonGroup_2);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        gridLayout->addWidget(radioButton_3, 0, 0, 1, 1);

        radioButton_4 = new QRadioButton(buttonGroup_2);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        gridLayout->addWidget(radioButton_4, 0, 1, 1, 1);


        gridLayout_5->addWidget(buttonGroup_2, 0, 1, 1, 1);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lineEdit = new QLineEdit(groupBox_4);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(lineEdit, 0, 0, 1, 1);

        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 1, 1, 1);


        gridLayout_5->addWidget(groupBox_4, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(190, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 0, 3, 1, 1);

        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButton = new QPushButton(groupBox_5);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_4->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox_5);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_4->addWidget(pushButton_2, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 0, 2, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox_5);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(lineEdit_2, 0, 3, 1, 1);

        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 0, 4, 1, 1);

        lineEdit_3 = new QLineEdit(groupBox_5);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(lineEdit_3, 0, 5, 1, 1);

        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 0, 6, 1, 1);

        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 0, 7, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox_5);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        sizePolicy.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(lineEdit_4, 0, 8, 1, 1);

        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 0, 9, 1, 1);

        lineEdit_5 = new QLineEdit(groupBox_5);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(lineEdit_5, 0, 10, 1, 1);

        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 0, 11, 1, 1);


        gridLayout_5->addWidget(groupBox_5, 1, 0, 1, 4);

        groupBox_heatmeter = new QGroupBox(DataTestDlgClass);
        groupBox_heatmeter->setObjectName(QString::fromUtf8("groupBox_heatmeter"));
        groupBox_heatmeter->setGeometry(QRect(0, 420, 771, 241));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_heatmeter->sizePolicy().hasHeightForWidth());
        groupBox_heatmeter->setSizePolicy(sizePolicy1);
        groupBox_heatmeter->setFlat(false);
        groupBox_9 = new QGroupBox(groupBox_heatmeter);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(220, 10, 251, 221));
        gridLayout_7 = new QGridLayout(groupBox_9);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_25 = new QLabel(groupBox_9);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy2);

        gridLayout_7->addWidget(label_25, 0, 0, 1, 1);

        lnEditMeterNo = new QLineEdit(groupBox_9);
        lnEditMeterNo->setObjectName(QString::fromUtf8("lnEditMeterNo"));
        lnEditMeterNo->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditMeterNo->sizePolicy().hasHeightForWidth());
        lnEditMeterNo->setSizePolicy(sizePolicy);
        lnEditMeterNo->setReadOnly(true);

        gridLayout_7->addWidget(lnEditMeterNo, 0, 1, 1, 1);

        label_26 = new QLabel(groupBox_9);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_7->addWidget(label_26, 1, 0, 1, 1);

        lnEditMeterTempIn = new QLineEdit(groupBox_9);
        lnEditMeterTempIn->setObjectName(QString::fromUtf8("lnEditMeterTempIn"));
        lnEditMeterTempIn->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditMeterTempIn->sizePolicy().hasHeightForWidth());
        lnEditMeterTempIn->setSizePolicy(sizePolicy);
        lnEditMeterTempIn->setReadOnly(true);

        gridLayout_7->addWidget(lnEditMeterTempIn, 1, 1, 1, 1);

        label_27 = new QLabel(groupBox_9);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_7->addWidget(label_27, 2, 0, 1, 1);

        lnEditMeterTempOut = new QLineEdit(groupBox_9);
        lnEditMeterTempOut->setObjectName(QString::fromUtf8("lnEditMeterTempOut"));
        lnEditMeterTempOut->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditMeterTempOut->sizePolicy().hasHeightForWidth());
        lnEditMeterTempOut->setSizePolicy(sizePolicy);
        lnEditMeterTempOut->setReadOnly(true);

        gridLayout_7->addWidget(lnEditMeterTempOut, 2, 1, 1, 1);

        label_28 = new QLabel(groupBox_9);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_7->addWidget(label_28, 3, 0, 1, 1);

        lnEditMeterTotalFlow = new QLineEdit(groupBox_9);
        lnEditMeterTotalFlow->setObjectName(QString::fromUtf8("lnEditMeterTotalFlow"));
        lnEditMeterTotalFlow->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditMeterTotalFlow->sizePolicy().hasHeightForWidth());
        lnEditMeterTotalFlow->setSizePolicy(sizePolicy);
        lnEditMeterTotalFlow->setReadOnly(true);

        gridLayout_7->addWidget(lnEditMeterTotalFlow, 3, 1, 1, 1);

        label_29 = new QLabel(groupBox_9);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_7->addWidget(label_29, 4, 0, 1, 1);

        lnEditMeterHeat = new QLineEdit(groupBox_9);
        lnEditMeterHeat->setObjectName(QString::fromUtf8("lnEditMeterHeat"));
        lnEditMeterHeat->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditMeterHeat->sizePolicy().hasHeightForWidth());
        lnEditMeterHeat->setSizePolicy(sizePolicy);
        lnEditMeterHeat->setReadOnly(true);

        gridLayout_7->addWidget(lnEditMeterHeat, 4, 1, 1, 1);

        label_31 = new QLabel(groupBox_9);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_7->addWidget(label_31, 5, 0, 1, 1);

        dateEditMeter = new QDateEdit(groupBox_9);
        dateEditMeter->setObjectName(QString::fromUtf8("dateEditMeter"));
        dateEditMeter->setEnabled(false);
        dateEditMeter->setReadOnly(true);

        gridLayout_7->addWidget(dateEditMeter, 5, 1, 1, 1);

        label_32 = new QLabel(groupBox_9);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_7->addWidget(label_32, 6, 0, 1, 1);

        lnEditNewMeterNo = new QLineEdit(groupBox_9);
        lnEditNewMeterNo->setObjectName(QString::fromUtf8("lnEditNewMeterNo"));
        sizePolicy.setHeightForWidth(lnEditNewMeterNo->sizePolicy().hasHeightForWidth());
        lnEditNewMeterNo->setSizePolicy(sizePolicy);
        lnEditNewMeterNo->setAutoFillBackground(true);

        gridLayout_7->addWidget(lnEditNewMeterNo, 6, 1, 1, 1);

        layoutWidget = new QWidget(groupBox_heatmeter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 195, 211));
        gridLayout_13 = new QGridLayout(layoutWidget);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_13->setContentsMargins(0, 0, 0, 0);
        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        parityComboBox = new QComboBox(layoutWidget);
        parityComboBox->setObjectName(QString::fromUtf8("parityComboBox"));

        gridLayout_12->addWidget(parityComboBox, 3, 1, 1, 1);

        label_23 = new QLabel(layoutWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        sizePolicy.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy);

        gridLayout_12->addWidget(label_23, 4, 0, 1, 1);

        label_21 = new QLabel(layoutWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy);

        gridLayout_12->addWidget(label_21, 2, 0, 1, 1);

        baudRateComboBox = new QComboBox(layoutWidget);
        baudRateComboBox->setObjectName(QString::fromUtf8("baudRateComboBox"));

        gridLayout_12->addWidget(baudRateComboBox, 1, 1, 1, 1);

        dataBitsComboBox = new QComboBox(layoutWidget);
        dataBitsComboBox->setObjectName(QString::fromUtf8("dataBitsComboBox"));

        gridLayout_12->addWidget(dataBitsComboBox, 2, 1, 1, 1);

        stopBitsComboBox = new QComboBox(layoutWidget);
        stopBitsComboBox->setObjectName(QString::fromUtf8("stopBitsComboBox"));

        gridLayout_12->addWidget(stopBitsComboBox, 4, 1, 1, 1);

        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy);

        gridLayout_12->addWidget(label_19, 0, 0, 1, 1);

        label_22 = new QLabel(layoutWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy);

        gridLayout_12->addWidget(label_22, 3, 0, 1, 1);

        label_20 = new QLabel(layoutWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        sizePolicy.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy);

        gridLayout_12->addWidget(label_20, 1, 0, 1, 1);

        portNameComboBox = new QComboBox(layoutWidget);
        portNameComboBox->setObjectName(QString::fromUtf8("portNameComboBox"));

        gridLayout_12->addWidget(portNameComboBox, 0, 1, 1, 1);


        gridLayout_13->addLayout(gridLayout_12, 0, 0, 1, 2);

        btnCloseCom = new QPushButton(layoutWidget);
        btnCloseCom->setObjectName(QString::fromUtf8("btnCloseCom"));

        gridLayout_13->addWidget(btnCloseCom, 1, 1, 1, 1);

        btnOpenCom = new QPushButton(layoutWidget);
        btnOpenCom->setObjectName(QString::fromUtf8("btnOpenCom"));

        gridLayout_13->addWidget(btnOpenCom, 1, 0, 1, 1);

        btnSetVerifyStatus = new QPushButton(groupBox_heatmeter);
        btnSetVerifyStatus->setObjectName(QString::fromUtf8("btnSetVerifyStatus"));
        btnSetVerifyStatus->setGeometry(QRect(490, 170, 61, 61));
        sizePolicy1.setHeightForWidth(btnSetVerifyStatus->sizePolicy().hasHeightForWidth());
        btnSetVerifyStatus->setSizePolicy(sizePolicy1);
        btnReadMeterData = new QPushButton(groupBox_heatmeter);
        btnReadMeterData->setObjectName(QString::fromUtf8("btnReadMeterData"));
        btnReadMeterData->setGeometry(QRect(560, 170, 61, 61));
        sizePolicy1.setHeightForWidth(btnReadMeterData->sizePolicy().hasHeightForWidth());
        btnReadMeterData->setSizePolicy(sizePolicy1);
        btnModifyMeterNo = new QPushButton(groupBox_heatmeter);
        btnModifyMeterNo->setObjectName(QString::fromUtf8("btnModifyMeterNo"));
        btnModifyMeterNo->setGeometry(QRect(630, 170, 61, 61));
        sizePolicy1.setHeightForWidth(btnModifyMeterNo->sizePolicy().hasHeightForWidth());
        btnModifyMeterNo->setSizePolicy(sizePolicy1);
        btnModifyFlowCoe = new QPushButton(groupBox_heatmeter);
        btnModifyFlowCoe->setObjectName(QString::fromUtf8("btnModifyFlowCoe"));
        btnModifyFlowCoe->setGeometry(QRect(700, 170, 61, 61));
        sizePolicy1.setHeightForWidth(btnModifyFlowCoe->sizePolicy().hasHeightForWidth());
        btnModifyFlowCoe->setSizePolicy(sizePolicy1);
        layoutWidget1 = new QWidget(groupBox_heatmeter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(490, 20, 271, 141));
        gridLayout_8 = new QGridLayout(layoutWidget1);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        label_24 = new QLabel(layoutWidget1);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_8->addWidget(label_24, 0, 1, 1, 1);

        label_30 = new QLabel(layoutWidget1);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_8->addWidget(label_30, 0, 2, 1, 1);

        label_37 = new QLabel(layoutWidget1);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        gridLayout_8->addWidget(label_37, 0, 3, 1, 1);

        label_33 = new QLabel(layoutWidget1);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_8->addWidget(label_33, 1, 0, 1, 1);

        lnEditBigNewError = new QLineEdit(layoutWidget1);
        lnEditBigNewError->setObjectName(QString::fromUtf8("lnEditBigNewError"));
        sizePolicy.setHeightForWidth(lnEditBigNewError->sizePolicy().hasHeightForWidth());
        lnEditBigNewError->setSizePolicy(sizePolicy);
        lnEditBigNewError->setAutoFillBackground(true);

        gridLayout_8->addWidget(lnEditBigNewError, 1, 1, 1, 1);

        lnEditBigOldError = new QLineEdit(layoutWidget1);
        lnEditBigOldError->setObjectName(QString::fromUtf8("lnEditBigOldError"));
        lnEditBigOldError->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditBigOldError->sizePolicy().hasHeightForWidth());
        lnEditBigOldError->setSizePolicy(sizePolicy);
        lnEditBigOldError->setAutoFillBackground(true);

        gridLayout_8->addWidget(lnEditBigOldError, 1, 2, 1, 1);

        lnEditBigOldCoe = new QLineEdit(layoutWidget1);
        lnEditBigOldCoe->setObjectName(QString::fromUtf8("lnEditBigOldCoe"));
        lnEditBigOldCoe->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditBigOldCoe->sizePolicy().hasHeightForWidth());
        lnEditBigOldCoe->setSizePolicy(sizePolicy);
        lnEditBigOldCoe->setAutoFillBackground(true);

        gridLayout_8->addWidget(lnEditBigOldCoe, 1, 3, 1, 1);

        label_34 = new QLabel(layoutWidget1);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        gridLayout_8->addWidget(label_34, 2, 0, 1, 1);

        lnEditMid2NewError = new QLineEdit(layoutWidget1);
        lnEditMid2NewError->setObjectName(QString::fromUtf8("lnEditMid2NewError"));
        sizePolicy.setHeightForWidth(lnEditMid2NewError->sizePolicy().hasHeightForWidth());
        lnEditMid2NewError->setSizePolicy(sizePolicy);
        lnEditMid2NewError->setAutoFillBackground(true);

        gridLayout_8->addWidget(lnEditMid2NewError, 2, 1, 1, 1);

        lnEditMid2OldError = new QLineEdit(layoutWidget1);
        lnEditMid2OldError->setObjectName(QString::fromUtf8("lnEditMid2OldError"));
        lnEditMid2OldError->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditMid2OldError->sizePolicy().hasHeightForWidth());
        lnEditMid2OldError->setSizePolicy(sizePolicy);
        lnEditMid2OldError->setAutoFillBackground(true);

        gridLayout_8->addWidget(lnEditMid2OldError, 2, 2, 1, 1);

        lnEditMid2OldCoe = new QLineEdit(layoutWidget1);
        lnEditMid2OldCoe->setObjectName(QString::fromUtf8("lnEditMid2OldCoe"));
        lnEditMid2OldCoe->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditMid2OldCoe->sizePolicy().hasHeightForWidth());
        lnEditMid2OldCoe->setSizePolicy(sizePolicy);
        lnEditMid2OldCoe->setAutoFillBackground(true);

        gridLayout_8->addWidget(lnEditMid2OldCoe, 2, 3, 1, 1);

        label_35 = new QLabel(layoutWidget1);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout_8->addWidget(label_35, 3, 0, 1, 1);

        lnEditMid1NewError = new QLineEdit(layoutWidget1);
        lnEditMid1NewError->setObjectName(QString::fromUtf8("lnEditMid1NewError"));
        sizePolicy.setHeightForWidth(lnEditMid1NewError->sizePolicy().hasHeightForWidth());
        lnEditMid1NewError->setSizePolicy(sizePolicy);
        lnEditMid1NewError->setAutoFillBackground(true);

        gridLayout_8->addWidget(lnEditMid1NewError, 3, 1, 1, 1);

        lnEditMid1OldError = new QLineEdit(layoutWidget1);
        lnEditMid1OldError->setObjectName(QString::fromUtf8("lnEditMid1OldError"));
        lnEditMid1OldError->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditMid1OldError->sizePolicy().hasHeightForWidth());
        lnEditMid1OldError->setSizePolicy(sizePolicy);
        lnEditMid1OldError->setAutoFillBackground(true);

        gridLayout_8->addWidget(lnEditMid1OldError, 3, 2, 1, 1);

        lnEditMid1OldCoe = new QLineEdit(layoutWidget1);
        lnEditMid1OldCoe->setObjectName(QString::fromUtf8("lnEditMid1OldCoe"));
        lnEditMid1OldCoe->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditMid1OldCoe->sizePolicy().hasHeightForWidth());
        lnEditMid1OldCoe->setSizePolicy(sizePolicy);
        lnEditMid1OldCoe->setAutoFillBackground(true);

        gridLayout_8->addWidget(lnEditMid1OldCoe, 3, 3, 1, 1);

        label_36 = new QLabel(layoutWidget1);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        gridLayout_8->addWidget(label_36, 4, 0, 1, 1);

        lnEditSmallNewError = new QLineEdit(layoutWidget1);
        lnEditSmallNewError->setObjectName(QString::fromUtf8("lnEditSmallNewError"));
        sizePolicy.setHeightForWidth(lnEditSmallNewError->sizePolicy().hasHeightForWidth());
        lnEditSmallNewError->setSizePolicy(sizePolicy);
        lnEditSmallNewError->setAutoFillBackground(true);

        gridLayout_8->addWidget(lnEditSmallNewError, 4, 1, 1, 1);

        lnEditSmallOldError = new QLineEdit(layoutWidget1);
        lnEditSmallOldError->setObjectName(QString::fromUtf8("lnEditSmallOldError"));
        lnEditSmallOldError->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditSmallOldError->sizePolicy().hasHeightForWidth());
        lnEditSmallOldError->setSizePolicy(sizePolicy);
        lnEditSmallOldError->setAutoFillBackground(true);

        gridLayout_8->addWidget(lnEditSmallOldError, 4, 2, 1, 1);

        lnEditSmallOldCoe = new QLineEdit(layoutWidget1);
        lnEditSmallOldCoe->setObjectName(QString::fromUtf8("lnEditSmallOldCoe"));
        lnEditSmallOldCoe->setEnabled(false);
        sizePolicy.setHeightForWidth(lnEditSmallOldCoe->sizePolicy().hasHeightForWidth());
        lnEditSmallOldCoe->setSizePolicy(sizePolicy);
        lnEditSmallOldCoe->setAutoFillBackground(true);

        gridLayout_8->addWidget(lnEditSmallOldCoe, 4, 3, 1, 1);

        groupBox_2 = new QGroupBox(DataTestDlgClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 190, 421, 151));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        btnWaterIn = new QPushButton(groupBox_2);
        btnWaterIn->setObjectName(QString::fromUtf8("btnWaterIn"));
        btnWaterIn->setGeometry(QRect(21, 27, 40, 100));
        sizePolicy2.setHeightForWidth(btnWaterIn->sizePolicy().hasHeightForWidth());
        btnWaterIn->setSizePolicy(sizePolicy2);
        btnWaterIn->setMaximumSize(QSize(40, 100));
        btnWaterIn->setLayoutDirection(Qt::LeftToRight);
        btnWaterIn->setAutoFillBackground(false);
        btnWaterIn->setAutoDefault(false);
        btnWaterIn->setDefault(false);
        btnWaterIn->setFlat(false);
        btnValveBig = new QPushButton(groupBox_2);
        btnValveBig->setObjectName(QString::fromUtf8("btnValveBig"));
        btnValveBig->setGeometry(QRect(77, 27, 40, 100));
        sizePolicy2.setHeightForWidth(btnValveBig->sizePolicy().hasHeightForWidth());
        btnValveBig->setSizePolicy(sizePolicy2);
        btnValveBig->setMaximumSize(QSize(40, 100));
        btnValveBig->setLayoutDirection(Qt::LeftToRight);
        btnValveBig->setAutoFillBackground(false);
        btnValveBig->setAutoDefault(false);
        btnValveBig->setDefault(false);
        btnValveBig->setFlat(false);
        btnValveMiddle1 = new QPushButton(groupBox_2);
        btnValveMiddle1->setObjectName(QString::fromUtf8("btnValveMiddle1"));
        btnValveMiddle1->setGeometry(QRect(133, 27, 40, 100));
        sizePolicy2.setHeightForWidth(btnValveMiddle1->sizePolicy().hasHeightForWidth());
        btnValveMiddle1->setSizePolicy(sizePolicy2);
        btnValveMiddle1->setMaximumSize(QSize(40, 100));
        btnValveMiddle1->setLayoutDirection(Qt::LeftToRight);
        btnValveMiddle1->setAutoFillBackground(false);
        btnValveMiddle1->setAutoDefault(false);
        btnValveMiddle1->setDefault(false);
        btnValveMiddle1->setFlat(false);
        btnWaterOut = new QPushButton(groupBox_2);
        btnWaterOut->setObjectName(QString::fromUtf8("btnWaterOut"));
        btnWaterOut->setGeometry(QRect(301, 27, 40, 100));
        sizePolicy2.setHeightForWidth(btnWaterOut->sizePolicy().hasHeightForWidth());
        btnWaterOut->setSizePolicy(sizePolicy2);
        btnWaterOut->setMaximumSize(QSize(40, 100));
        btnWaterOut->setLayoutDirection(Qt::LeftToRight);
        btnWaterOut->setAutoFillBackground(false);
        btnWaterOut->setAutoDefault(false);
        btnWaterOut->setDefault(false);
        btnWaterOut->setFlat(false);
        btnWaterPump = new QPushButton(groupBox_2);
        btnWaterPump->setObjectName(QString::fromUtf8("btnWaterPump"));
        btnWaterPump->setGeometry(QRect(357, 27, 40, 100));
        sizePolicy2.setHeightForWidth(btnWaterPump->sizePolicy().hasHeightForWidth());
        btnWaterPump->setSizePolicy(sizePolicy2);
        btnWaterPump->setMaximumSize(QSize(40, 100));
        btnWaterPump->setLayoutDirection(Qt::LeftToRight);
        btnWaterPump->setAutoFillBackground(false);
        btnWaterPump->setAutoDefault(false);
        btnWaterPump->setDefault(false);
        btnWaterPump->setFlat(false);
        btnValveMiddle2 = new QPushButton(groupBox_2);
        btnValveMiddle2->setObjectName(QString::fromUtf8("btnValveMiddle2"));
        btnValveMiddle2->setGeometry(QRect(189, 27, 40, 100));
        sizePolicy2.setHeightForWidth(btnValveMiddle2->sizePolicy().hasHeightForWidth());
        btnValveMiddle2->setSizePolicy(sizePolicy2);
        btnValveMiddle2->setMaximumSize(QSize(40, 100));
        btnValveMiddle2->setLayoutDirection(Qt::LeftToRight);
        btnValveMiddle2->setAutoFillBackground(false);
        btnValveMiddle2->setAutoDefault(false);
        btnValveMiddle2->setDefault(false);
        btnValveMiddle2->setFlat(false);
        btnValveSmall = new QPushButton(groupBox_2);
        btnValveSmall->setObjectName(QString::fromUtf8("btnValveSmall"));
        btnValveSmall->setGeometry(QRect(245, 27, 40, 100));
        sizePolicy2.setHeightForWidth(btnValveSmall->sizePolicy().hasHeightForWidth());
        btnValveSmall->setSizePolicy(sizePolicy2);
        btnValveSmall->setMaximumSize(QSize(40, 100));
        btnValveSmall->setLayoutDirection(Qt::LeftToRight);
        btnValveSmall->setAutoFillBackground(false);
        btnValveSmall->setAutoDefault(false);
        btnValveSmall->setDefault(false);
        btnValveSmall->setFlat(false);
        layoutWidget2 = new QWidget(DataTestDlgClass);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 360, 422, 32));
        gridLayout_15 = new QGridLayout(layoutWidget2);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_15->setContentsMargins(0, 0, 0, 0);
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        label_18 = new QLabel(layoutWidget2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy2.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy2);

        gridLayout_11->addWidget(label_18, 0, 0, 1, 1);

        spinBoxFreq = new QSpinBox(layoutWidget2);
        spinBoxFreq->setObjectName(QString::fromUtf8("spinBoxFreq"));
        sizePolicy.setHeightForWidth(spinBoxFreq->sizePolicy().hasHeightForWidth());
        spinBoxFreq->setSizePolicy(sizePolicy);
        spinBoxFreq->setMaximum(9999);

        gridLayout_11->addWidget(spinBoxFreq, 0, 1, 1, 1);

        btnSetFreq = new QPushButton(layoutWidget2);
        btnSetFreq->setObjectName(QString::fromUtf8("btnSetFreq"));
        sizePolicy.setHeightForWidth(btnSetFreq->sizePolicy().hasHeightForWidth());
        btnSetFreq->setSizePolicy(sizePolicy);

        gridLayout_11->addWidget(btnSetFreq, 0, 2, 1, 1);


        gridLayout_15->addLayout(gridLayout_11, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        gridLayout_14 = new QGridLayout();
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        btnRegulate1 = new QPushButton(layoutWidget2);
        btnRegulate1->setObjectName(QString::fromUtf8("btnRegulate1"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnRegulate1->sizePolicy().hasHeightForWidth());
        btnRegulate1->setSizePolicy(sizePolicy3);

        gridLayout_14->addWidget(btnRegulate1, 0, 0, 1, 1);

        btnQueryStatus = new QPushButton(layoutWidget2);
        btnQueryStatus->setObjectName(QString::fromUtf8("btnQueryStatus"));
        sizePolicy3.setHeightForWidth(btnQueryStatus->sizePolicy().hasHeightForWidth());
        btnQueryStatus->setSizePolicy(sizePolicy3);

        gridLayout_14->addWidget(btnQueryStatus, 0, 1, 1, 1);


        gridLayout_15->addLayout(gridLayout_14, 0, 2, 1, 1);

        groupBox_3 = new QGroupBox(DataTestDlgClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(460, 190, 311, 201));
        sizePolicy3.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy3);
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_6->addWidget(label_8, 0, 0, 1, 1);

        lnEditBigBalance = new QLineEdit(groupBox_3);
        lnEditBigBalance->setObjectName(QString::fromUtf8("lnEditBigBalance"));
        sizePolicy.setHeightForWidth(lnEditBigBalance->sizePolicy().hasHeightForWidth());
        lnEditBigBalance->setSizePolicy(sizePolicy);
        lnEditBigBalance->setReadOnly(true);

        gridLayout_6->addWidget(lnEditBigBalance, 0, 1, 1, 1);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_6->addWidget(label_13, 0, 2, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_6->addWidget(label_9, 1, 0, 1, 1);

        lnEditSmallBalance = new QLineEdit(groupBox_3);
        lnEditSmallBalance->setObjectName(QString::fromUtf8("lnEditSmallBalance"));
        sizePolicy.setHeightForWidth(lnEditSmallBalance->sizePolicy().hasHeightForWidth());
        lnEditSmallBalance->setSizePolicy(sizePolicy);
        lnEditSmallBalance->setReadOnly(true);

        gridLayout_6->addWidget(lnEditSmallBalance, 1, 1, 1, 1);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_6->addWidget(label_14, 1, 2, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_6->addWidget(label_10, 2, 0, 1, 1);

        lnEditFlowRate = new QLineEdit(groupBox_3);
        lnEditFlowRate->setObjectName(QString::fromUtf8("lnEditFlowRate"));
        sizePolicy.setHeightForWidth(lnEditFlowRate->sizePolicy().hasHeightForWidth());
        lnEditFlowRate->setSizePolicy(sizePolicy);
        lnEditFlowRate->setReadOnly(true);

        gridLayout_6->addWidget(lnEditFlowRate, 2, 1, 1, 1);

        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_6->addWidget(label_15, 2, 2, 1, 1);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_6->addWidget(label_11, 3, 0, 1, 1);

        lnEditTempIn = new QLineEdit(groupBox_3);
        lnEditTempIn->setObjectName(QString::fromUtf8("lnEditTempIn"));
        sizePolicy.setHeightForWidth(lnEditTempIn->sizePolicy().hasHeightForWidth());
        lnEditTempIn->setSizePolicy(sizePolicy);
        lnEditTempIn->setReadOnly(true);

        gridLayout_6->addWidget(lnEditTempIn, 3, 1, 1, 1);

        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_6->addWidget(label_16, 3, 2, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_6->addWidget(label_12, 4, 0, 1, 1);

        lnEditTempOut = new QLineEdit(groupBox_3);
        lnEditTempOut->setObjectName(QString::fromUtf8("lnEditTempOut"));
        sizePolicy.setHeightForWidth(lnEditTempOut->sizePolicy().hasHeightForWidth());
        lnEditTempOut->setSizePolicy(sizePolicy);
        lnEditTempOut->setReadOnly(true);

        gridLayout_6->addWidget(lnEditTempOut, 4, 1, 1, 1);

        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_6->addWidget(label_17, 4, 2, 1, 1);

        btnParaSet = new QPushButton(DataTestDlgClass);
        btnParaSet->setObjectName(QString::fromUtf8("btnParaSet"));
        btnParaSet->setGeometry(QRect(392, 670, 181, 28));
        btnParaSet->setAutoFillBackground(true);
        btnExit = new QPushButton(DataTestDlgClass);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        btnExit->setGeometry(QRect(582, 670, 191, 28));

        retranslateUi(DataTestDlgClass);

        baudRateComboBox->setCurrentIndex(0);
        dataBitsComboBox->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(DataTestDlgClass);
    } // setupUi

    void retranslateUi(QWidget *DataTestDlgClass)
    {
        DataTestDlgClass->setWindowTitle(QApplication::translate("DataTestDlgClass", "DA and Test", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DataTestDlgClass", "Total Verify Data", 0, QApplication::UnicodeUTF8));
        buttonGroup->setTitle(QApplication::translate("DataTestDlgClass", "Install Position", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("DataTestDlgClass", "In", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("DataTestDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        buttonGroup_2->setTitle(QApplication::translate("DataTestDlgClass", "Heat Unit", 0, QApplication::UnicodeUTF8));
        radioButton_3->setText(QApplication::translate("DataTestDlgClass", "KWH", 0, QApplication::UnicodeUTF8));
        radioButton_4->setText(QApplication::translate("DataTestDlgClass", "MJ", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("DataTestDlgClass", "Min Temp Diff", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DataTestDlgClass", "K", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("DataTestDlgClass", "Std  Thermometer", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("DataTestDlgClass", "Collect", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("DataTestDlgClass", "Stop", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DataTestDlgClass", "In", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DataTestDlgClass", "\316\251", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("DataTestDlgClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("DataTestDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("DataTestDlgClass", "\316\251", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("DataTestDlgClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        groupBox_heatmeter->setTitle(QApplication::translate("DataTestDlgClass", "Heat Meter", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("DataTestDlgClass", "MeterInfo:", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("DataTestDlgClass", "MeterNO.", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("DataTestDlgClass", "T In(\342\204\203)", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("DataTestDlgClass", "T Out(\342\204\203)", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("DataTestDlgClass", "Flow(m\302\263)", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("DataTestDlgClass", "Heat(kwh)", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("DataTestDlgClass", "Date", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("DataTestDlgClass", "New NO.", 0, QApplication::UnicodeUTF8));
        parityComboBox->clear();
        parityComboBox->insertItems(0, QStringList()
         << QApplication::translate("DataTestDlgClass", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "Odd", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "Even", 0, QApplication::UnicodeUTF8)
        );
        label_23->setText(QApplication::translate("DataTestDlgClass", "StopBits:", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("DataTestDlgClass", "DataBits:", 0, QApplication::UnicodeUTF8));
        baudRateComboBox->clear();
        baudRateComboBox->insertItems(0, QStringList()
         << QApplication::translate("DataTestDlgClass", "2400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "4800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "14400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "38400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "56000", 0, QApplication::UnicodeUTF8)
        );
        dataBitsComboBox->clear();
        dataBitsComboBox->insertItems(0, QStringList()
         << QApplication::translate("DataTestDlgClass", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "8", 0, QApplication::UnicodeUTF8)
        );
        stopBitsComboBox->clear();
        stopBitsComboBox->insertItems(0, QStringList()
         << QApplication::translate("DataTestDlgClass", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "1.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "2", 0, QApplication::UnicodeUTF8)
        );
        label_19->setText(QApplication::translate("DataTestDlgClass", "Com:", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("DataTestDlgClass", "Parity:", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("DataTestDlgClass", "BaudRate:", 0, QApplication::UnicodeUTF8));
        portNameComboBox->clear();
        portNameComboBox->insertItems(0, QStringList()
         << QApplication::translate("DataTestDlgClass", "COM1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataTestDlgClass", "COM20", 0, QApplication::UnicodeUTF8)
        );
        btnCloseCom->setText(QApplication::translate("DataTestDlgClass", "CloseCom", 0, QApplication::UnicodeUTF8));
        btnOpenCom->setText(QApplication::translate("DataTestDlgClass", "OpenCom", 0, QApplication::UnicodeUTF8));
        btnSetVerifyStatus->setText(QApplication::translate("DataTestDlgClass", "Verify\n"
"Status", 0, QApplication::UnicodeUTF8));
        btnReadMeterData->setText(QApplication::translate("DataTestDlgClass", "Read\n"
"Data", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnModifyMeterNo->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btnModifyMeterNo->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        btnModifyMeterNo->setText(QApplication::translate("DataTestDlgClass", "Modify\n"
"MeterNo", 0, QApplication::UnicodeUTF8));
        btnModifyFlowCoe->setText(QApplication::translate("DataTestDlgClass", "Modify\n"
"Coe", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("DataTestDlgClass", "err(%)", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("DataTestDlgClass", "olderr(%)", 0, QApplication::UnicodeUTF8));
        label_37->setText(QApplication::translate("DataTestDlgClass", "oldCoe(%)", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("DataTestDlgClass", "big", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("DataTestDlgClass", "mid2", 0, QApplication::UnicodeUTF8));
        lnEditMid2NewError->setText(QString());
        lnEditMid2OldError->setText(QString());
        lnEditMid2OldCoe->setText(QString());
        label_35->setText(QApplication::translate("DataTestDlgClass", "mid1", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("DataTestDlgClass", "small", 0, QApplication::UnicodeUTF8));
        lnEditSmallNewError->setText(QString());
        lnEditSmallOldError->setText(QString());
        lnEditSmallOldCoe->setText(QString());
        groupBox_2->setTitle(QApplication::translate("DataTestDlgClass", "Valve Control", 0, QApplication::UnicodeUTF8));
        btnWaterIn->setText(QApplication::translate("DataTestDlgClass", "i\n"
"n", 0, QApplication::UnicodeUTF8));
        btnValveBig->setText(QApplication::translate("DataTestDlgClass", "b\n"
"i\n"
"g", 0, QApplication::UnicodeUTF8));
        btnValveMiddle1->setText(QApplication::translate("DataTestDlgClass", "m\n"
"i\n"
"d\n"
"1", 0, QApplication::UnicodeUTF8));
        btnWaterOut->setText(QApplication::translate("DataTestDlgClass", "o\n"
"u\n"
"t", 0, QApplication::UnicodeUTF8));
        btnWaterPump->setText(QApplication::translate("DataTestDlgClass", "p\n"
"u\n"
"m\n"
"p", 0, QApplication::UnicodeUTF8));
        btnValveMiddle2->setText(QApplication::translate("DataTestDlgClass", "m\n"
"i\n"
"d\n"
"2", 0, QApplication::UnicodeUTF8));
        btnValveSmall->setText(QApplication::translate("DataTestDlgClass", "s\n"
"m\n"
"a\n"
"l\n"
"l", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("DataTestDlgClass", "Freq:", 0, QApplication::UnicodeUTF8));
        btnSetFreq->setText(QApplication::translate("DataTestDlgClass", "SetFreq", 0, QApplication::UnicodeUTF8));
        btnRegulate1->setText(QApplication::translate("DataTestDlgClass", "Regulater", 0, QApplication::UnicodeUTF8));
        btnQueryStatus->setText(QApplication::translate("DataTestDlgClass", "Query Status", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("DataTestDlgClass", "Data Acquisition", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("DataTestDlgClass", "Big Balance:", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("DataTestDlgClass", "kg", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("DataTestDlgClass", "Small Balance:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("DataTestDlgClass", "kg", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("DataTestDlgClass", "Flow Rate:", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("DataTestDlgClass", "m\302\263/h", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("DataTestDlgClass", "In Temp:", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("DataTestDlgClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("DataTestDlgClass", "Out Temp:", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("DataTestDlgClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        btnParaSet->setText(QApplication::translate("DataTestDlgClass", "ParaSet", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("DataTestDlgClass", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DataTestDlgClass: public Ui_DataTestDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATATESTDLG_H
