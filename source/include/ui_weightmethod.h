/********************************************************************************
** Form generated from reading UI file 'weightmethod.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEIGHTMETHOD_H
#define UI_WEIGHTMETHOD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WeightMethodClass
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    QToolButton *btnWaterPumpStop;
    QToolButton *btnWaterPumpStart;
    QToolButton *btnValveSmall;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinBoxFrequency;
    QLabel *label_13;
    QToolButton *btnWaterIn;
    QToolButton *btnWaterOut;
    QToolButton *btnValveBig;
    QToolButton *btnValveMiddle1;
    QToolButton *btnValveMiddle2;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_7;
    QLabel *labelHintInfo;
    QLabel *labelHint;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_5;
    QPushButton *btnParaSet;
    QPushButton *btnReadMeter;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *labelStandard;
    QLineEdit *lnEditStandard;
    QLabel *label_14;
    QComboBox *cmbAutoPick;
    QLabel *label_15;
    QComboBox *cmbContinue;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_4;
    QPushButton *btnExhaust;
    QPushButton *btnStart;
    QPushButton *btnNext;
    QPushButton *btnStop;
    QPushButton *btnExit;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_2;
    QLabel *label_9;
    QLineEdit *lnEditBigBalance;
    QLabel *label_11;
    QLabel *label_10;
    QLineEdit *lnEditSmallBalance;
    QLabel *label_12;
    QLabel *label_3;
    QLCDNumber *lcdNumberFlow;
    QLabel *label_6;
    QLabel *label_4;
    QLCDNumber *lcdNumberInTemper;
    QLabel *label_7;
    QLabel *label_5;
    QLCDNumber *lcdNumberOutTemper;
    QLabel *label_8;
    QWidget *tab2;
    QWidget *tab3;
    QWidget *tab4;
    QWidget *tab5;

    void setupUi(QWidget *WeightMethodClass)
    {
        if (WeightMethodClass->objectName().isEmpty())
            WeightMethodClass->setObjectName(QString::fromUtf8("WeightMethodClass"));
        WeightMethodClass->resize(1330, 867);
        gridLayout = new QGridLayout(WeightMethodClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(WeightMethodClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setTabsClosable(false);
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        groupBox_2 = new QGroupBox(tab1);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(270, 640, 451, 171));
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        btnWaterPumpStop = new QToolButton(groupBox_2);
        btnWaterPumpStop->setObjectName(QString::fromUtf8("btnWaterPumpStop"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnWaterPumpStop->sizePolicy().hasHeightForWidth());
        btnWaterPumpStop->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(btnWaterPumpStop, 2, 0, 1, 1);

        btnWaterPumpStart = new QToolButton(groupBox_2);
        btnWaterPumpStart->setObjectName(QString::fromUtf8("btnWaterPumpStart"));
        sizePolicy.setHeightForWidth(btnWaterPumpStart->sizePolicy().hasHeightForWidth());
        btnWaterPumpStart->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(btnWaterPumpStart, 1, 0, 1, 1);

        btnValveSmall = new QToolButton(groupBox_2);
        btnValveSmall->setObjectName(QString::fromUtf8("btnValveSmall"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnValveSmall->sizePolicy().hasHeightForWidth());
        btnValveSmall->setSizePolicy(sizePolicy1);

        gridLayout_6->addWidget(btnValveSmall, 0, 6, 3, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        spinBoxFrequency = new QSpinBox(groupBox_2);
        spinBoxFrequency->setObjectName(QString::fromUtf8("spinBoxFrequency"));
        sizePolicy.setHeightForWidth(spinBoxFrequency->sizePolicy().hasHeightForWidth());
        spinBoxFrequency->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(spinBoxFrequency);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_13);


        gridLayout_6->addLayout(horizontalLayout, 0, 0, 1, 1);

        btnWaterIn = new QToolButton(groupBox_2);
        btnWaterIn->setObjectName(QString::fromUtf8("btnWaterIn"));
        sizePolicy1.setHeightForWidth(btnWaterIn->sizePolicy().hasHeightForWidth());
        btnWaterIn->setSizePolicy(sizePolicy1);

        gridLayout_6->addWidget(btnWaterIn, 0, 1, 3, 1);

        btnWaterOut = new QToolButton(groupBox_2);
        btnWaterOut->setObjectName(QString::fromUtf8("btnWaterOut"));
        sizePolicy1.setHeightForWidth(btnWaterOut->sizePolicy().hasHeightForWidth());
        btnWaterOut->setSizePolicy(sizePolicy1);

        gridLayout_6->addWidget(btnWaterOut, 0, 2, 3, 1);

        btnValveBig = new QToolButton(groupBox_2);
        btnValveBig->setObjectName(QString::fromUtf8("btnValveBig"));
        sizePolicy1.setHeightForWidth(btnValveBig->sizePolicy().hasHeightForWidth());
        btnValveBig->setSizePolicy(sizePolicy1);

        gridLayout_6->addWidget(btnValveBig, 0, 3, 3, 1);

        btnValveMiddle1 = new QToolButton(groupBox_2);
        btnValveMiddle1->setObjectName(QString::fromUtf8("btnValveMiddle1"));
        sizePolicy1.setHeightForWidth(btnValveMiddle1->sizePolicy().hasHeightForWidth());
        btnValveMiddle1->setSizePolicy(sizePolicy1);

        gridLayout_6->addWidget(btnValveMiddle1, 0, 4, 3, 1);

        btnValveMiddle2 = new QToolButton(groupBox_2);
        btnValveMiddle2->setObjectName(QString::fromUtf8("btnValveMiddle2"));
        sizePolicy1.setHeightForWidth(btnValveMiddle2->sizePolicy().hasHeightForWidth());
        btnValveMiddle2->setSizePolicy(sizePolicy1);

        gridLayout_6->addWidget(btnValveMiddle2, 0, 5, 3, 1);

        tableWidget = new QTableWidget(tab1);
        if (tableWidget->columnCount() < 10)
            tableWidget->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(11, 11, 1281, 611));
        tableWidget->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhFormattedNumbersOnly);
        tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        groupBox_3 = new QGroupBox(tab1);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(968, 630, 221, 181));
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        gridLayout_7 = new QGridLayout(groupBox_3);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        labelHintInfo = new QLabel(groupBox_3);
        labelHintInfo->setObjectName(QString::fromUtf8("labelHintInfo"));
        sizePolicy1.setHeightForWidth(labelHintInfo->sizePolicy().hasHeightForWidth());
        labelHintInfo->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(labelHintInfo, 0, 0, 1, 1);

        labelHint = new QLabel(groupBox_3);
        labelHint->setObjectName(QString::fromUtf8("labelHint"));
        sizePolicy1.setHeightForWidth(labelHint->sizePolicy().hasHeightForWidth());
        labelHint->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(labelHint, 1, 0, 1, 1);

        layoutWidget = new QWidget(tab1);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 652, 254, 161));
        gridLayout_5 = new QGridLayout(layoutWidget);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        btnParaSet = new QPushButton(layoutWidget);
        btnParaSet->setObjectName(QString::fromUtf8("btnParaSet"));
        sizePolicy.setHeightForWidth(btnParaSet->sizePolicy().hasHeightForWidth());
        btnParaSet->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(btnParaSet, 0, 0, 1, 1);

        btnReadMeter = new QPushButton(layoutWidget);
        btnReadMeter->setObjectName(QString::fromUtf8("btnReadMeter"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnReadMeter->sizePolicy().hasHeightForWidth());
        btnReadMeter->setSizePolicy(sizePolicy2);

        gridLayout_5->addWidget(btnReadMeter, 0, 1, 1, 1);

        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        labelStandard = new QLabel(groupBox);
        labelStandard->setObjectName(QString::fromUtf8("labelStandard"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelStandard->sizePolicy().hasHeightForWidth());
        labelStandard->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(labelStandard, 0, 0, 1, 1);

        lnEditStandard = new QLineEdit(groupBox);
        lnEditStandard->setObjectName(QString::fromUtf8("lnEditStandard"));
        lnEditStandard->setEnabled(false);
        sizePolicy2.setHeightForWidth(lnEditStandard->sizePolicy().hasHeightForWidth());
        lnEditStandard->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(lnEditStandard, 0, 1, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy3.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(label_14, 1, 0, 1, 1);

        cmbAutoPick = new QComboBox(groupBox);
        cmbAutoPick->setObjectName(QString::fromUtf8("cmbAutoPick"));
        cmbAutoPick->setEnabled(false);
        sizePolicy2.setHeightForWidth(cmbAutoPick->sizePolicy().hasHeightForWidth());
        cmbAutoPick->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(cmbAutoPick, 1, 1, 1, 1);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy3.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(label_15, 2, 0, 1, 1);

        cmbContinue = new QComboBox(groupBox);
        cmbContinue->setObjectName(QString::fromUtf8("cmbContinue"));
        cmbContinue->setEnabled(false);
        sizePolicy2.setHeightForWidth(cmbContinue->sizePolicy().hasHeightForWidth());
        cmbContinue->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(cmbContinue, 2, 1, 1, 1);


        gridLayout_5->addWidget(groupBox, 1, 0, 1, 2);

        layoutWidget1 = new QWidget(tab1);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(1197, 637, 95, 170));
        gridLayout_4 = new QGridLayout(layoutWidget1);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        btnExhaust = new QPushButton(layoutWidget1);
        btnExhaust->setObjectName(QString::fromUtf8("btnExhaust"));
        sizePolicy2.setHeightForWidth(btnExhaust->sizePolicy().hasHeightForWidth());
        btnExhaust->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(btnExhaust, 0, 0, 1, 1);

        btnStart = new QPushButton(layoutWidget1);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        sizePolicy2.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
        btnStart->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(btnStart, 1, 0, 1, 1);

        btnNext = new QPushButton(layoutWidget1);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));
        sizePolicy2.setHeightForWidth(btnNext->sizePolicy().hasHeightForWidth());
        btnNext->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(btnNext, 2, 0, 1, 1);

        btnStop = new QPushButton(layoutWidget1);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        sizePolicy2.setHeightForWidth(btnStop->sizePolicy().hasHeightForWidth());
        btnStop->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(btnStop, 3, 0, 1, 1);

        btnExit = new QPushButton(layoutWidget1);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        sizePolicy2.setHeightForWidth(btnExit->sizePolicy().hasHeightForWidth());
        btnExit->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(btnExit, 4, 0, 1, 1);

        layoutWidget2 = new QWidget(tab1);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(730, 640, 231, 171));
        gridLayout_2 = new QGridLayout(layoutWidget2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy3.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_9, 0, 0, 1, 1);

        lnEditBigBalance = new QLineEdit(layoutWidget2);
        lnEditBigBalance->setObjectName(QString::fromUtf8("lnEditBigBalance"));
        sizePolicy2.setHeightForWidth(lnEditBigBalance->sizePolicy().hasHeightForWidth());
        lnEditBigBalance->setSizePolicy(sizePolicy2);
        lnEditBigBalance->setReadOnly(true);

        gridLayout_2->addWidget(lnEditBigBalance, 0, 1, 1, 1);

        label_11 = new QLabel(layoutWidget2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy3.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_11, 0, 2, 1, 1);

        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy3.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_10, 1, 0, 1, 1);

        lnEditSmallBalance = new QLineEdit(layoutWidget2);
        lnEditSmallBalance->setObjectName(QString::fromUtf8("lnEditSmallBalance"));
        sizePolicy2.setHeightForWidth(lnEditSmallBalance->sizePolicy().hasHeightForWidth());
        lnEditSmallBalance->setSizePolicy(sizePolicy2);
        lnEditSmallBalance->setInputMethodHints(Qt::ImhNone);
        lnEditSmallBalance->setReadOnly(false);

        gridLayout_2->addWidget(lnEditSmallBalance, 1, 1, 1, 1);

        label_12 = new QLabel(layoutWidget2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy3.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_12, 1, 2, 1, 1);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        lcdNumberFlow = new QLCDNumber(layoutWidget2);
        lcdNumberFlow->setObjectName(QString::fromUtf8("lcdNumberFlow"));
        sizePolicy2.setHeightForWidth(lcdNumberFlow->sizePolicy().hasHeightForWidth());
        lcdNumberFlow->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(lcdNumberFlow, 2, 1, 1, 1);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_6, 2, 2, 1, 1);

        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy3.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy3);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        lcdNumberInTemper = new QLCDNumber(layoutWidget2);
        lcdNumberInTemper->setObjectName(QString::fromUtf8("lcdNumberInTemper"));
        sizePolicy2.setHeightForWidth(lcdNumberInTemper->sizePolicy().hasHeightForWidth());
        lcdNumberInTemper->setSizePolicy(sizePolicy2);
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        lcdNumberInTemper->setPalette(palette);
        lcdNumberInTemper->setNumDigits(5);

        gridLayout_2->addWidget(lcdNumberInTemper, 3, 1, 1, 1);

        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy3.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_7, 3, 2, 1, 1);

        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy3.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy3);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        lcdNumberOutTemper = new QLCDNumber(layoutWidget2);
        lcdNumberOutTemper->setObjectName(QString::fromUtf8("lcdNumberOutTemper"));
        sizePolicy2.setHeightForWidth(lcdNumberOutTemper->sizePolicy().hasHeightForWidth());
        lcdNumberOutTemper->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(lcdNumberOutTemper, 4, 1, 1, 1);

        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy3.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_8, 4, 2, 1, 1);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        tabWidget->addTab(tab2, QString());
        tab3 = new QWidget();
        tab3->setObjectName(QString::fromUtf8("tab3"));
        tabWidget->addTab(tab3, QString());
        tab4 = new QWidget();
        tab4->setObjectName(QString::fromUtf8("tab4"));
        tabWidget->addTab(tab4, QString());
        tab5 = new QWidget();
        tab5->setObjectName(QString::fromUtf8("tab5"));
        tabWidget->addTab(tab5, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(WeightMethodClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WeightMethodClass);
    } // setupUi

    void retranslateUi(QWidget *WeightMethodClass)
    {
        WeightMethodClass->setWindowTitle(QApplication::translate("WeightMethodClass", "WeightMethod Verify", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("WeightMethodClass", "Controller", 0, QApplication::UnicodeUTF8));
        btnWaterPumpStop->setText(QApplication::translate("WeightMethodClass", "Stop Pump", 0, QApplication::UnicodeUTF8));
        btnWaterPumpStart->setText(QApplication::translate("WeightMethodClass", "Start Pump", 0, QApplication::UnicodeUTF8));
        btnValveSmall->setText(QApplication::translate("WeightMethodClass", "s\n"
"m\n"
"a\n"
"l\n"
"l", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("WeightMethodClass", "Hz", 0, QApplication::UnicodeUTF8));
        btnWaterIn->setText(QApplication::translate("WeightMethodClass", "i\n"
"n\n"
"", 0, QApplication::UnicodeUTF8));
        btnWaterOut->setText(QApplication::translate("WeightMethodClass", "o\n"
"u\n"
"t", 0, QApplication::UnicodeUTF8));
        btnValveBig->setText(QApplication::translate("WeightMethodClass", "b\n"
"i\n"
"g", 0, QApplication::UnicodeUTF8));
        btnValveMiddle1->setText(QApplication::translate("WeightMethodClass", "m\n"
"i\n"
"d\n"
"1", 0, QApplication::UnicodeUTF8));
        btnValveMiddle2->setText(QApplication::translate("WeightMethodClass", "m\n"
"i\n"
"d\n"
"2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("WeightMethodClass", "MeterNo", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("WeightMethodClass", "FlowPoint(m\302\263/h)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("WeightMethodClass", "MeterValue0(L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("WeightMethodClass", "MeterValue1(L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("WeightMethodClass", "BalWeight0(kg)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("WeightMethodClass", "BalWeight1(kg)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("WeightMethodClass", "Temp(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("WeightMethodClass", "Density(kg/L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("WeightMethodClass", "StdValue(L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("WeightMethodClass", "DsipError(%)", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("WeightMethodClass", "Process Hint", 0, QApplication::UnicodeUTF8));
        labelHintInfo->setText(QApplication::translate("WeightMethodClass", "Hint Info", 0, QApplication::UnicodeUTF8));
        labelHint->setText(QString());
        btnParaSet->setText(QApplication::translate("WeightMethodClass", "ParaSet", 0, QApplication::UnicodeUTF8));
        btnReadMeter->setText(QApplication::translate("WeightMethodClass", "ReadMeter", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("WeightMethodClass", "NowPara(KeyInfo)", 0, QApplication::UnicodeUTF8));
        labelStandard->setText(QApplication::translate("WeightMethodClass", "Standard:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("WeightMethodClass", "DA Mode:", 0, QApplication::UnicodeUTF8));
        cmbAutoPick->clear();
        cmbAutoPick->insertItems(0, QStringList()
         << QApplication::translate("WeightMethodClass", "manual", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WeightMethodClass", "auto", 0, QApplication::UnicodeUTF8)
        );
        label_15->setText(QApplication::translate("WeightMethodClass", "Continuous:", 0, QApplication::UnicodeUTF8));
        cmbContinue->clear();
        cmbContinue->insertItems(0, QStringList()
         << QApplication::translate("WeightMethodClass", "Not Cotinuous", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WeightMethodClass", "Continuous", 0, QApplication::UnicodeUTF8)
        );
        btnExhaust->setText(QApplication::translate("WeightMethodClass", "Exhaust", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("WeightMethodClass", "Start", 0, QApplication::UnicodeUTF8));
        btnNext->setText(QApplication::translate("WeightMethodClass", "Next", 0, QApplication::UnicodeUTF8));
        btnStop->setText(QApplication::translate("WeightMethodClass", "Stop", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("WeightMethodClass", "Exit", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("WeightMethodClass", "Big Bal:", 0, QApplication::UnicodeUTF8));
        lnEditBigBalance->setText(QString());
        label_11->setText(QApplication::translate("WeightMethodClass", "\343\216\217", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("WeightMethodClass", "Small Bal:", 0, QApplication::UnicodeUTF8));
        lnEditSmallBalance->setText(QString());
        label_12->setText(QApplication::translate("WeightMethodClass", "\343\216\217", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("WeightMethodClass", "Flow:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("WeightMethodClass", "m\302\263/h", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("WeightMethodClass", "In Temp:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("WeightMethodClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("WeightMethodClass", "Out Temp:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("WeightMethodClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("WeightMethodClass", "Tab1", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("WeightMethodClass", "Tab2", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab3), QApplication::translate("WeightMethodClass", "Tab3", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab4), QApplication::translate("WeightMethodClass", "Tab4", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab5), QApplication::translate("WeightMethodClass", "Tab5", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WeightMethodClass: public Ui_WeightMethodClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEIGHTMETHOD_H
