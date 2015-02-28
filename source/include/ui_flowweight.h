/********************************************************************************
** Form generated from reading UI file 'flowweight.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLOWWEIGHT_H
#define UI_FLOWWEIGHT_H

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
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FlowWeightClass
{
public:
    QGridLayout *gridLayout_6;
    QTableWidget *tableWidget;
    QGridLayout *gridLayout_5;
    QPushButton *btnParaSet;
    QPushButton *btnReadMeter;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *labelStandard;
    QLineEdit *lnEditStandard;
    QLabel *label_14;
    QComboBox *cmbAutoPick;
    QLabel *label_16;
    QComboBox *cmbResetZero;
    QLabel *label_15;
    QComboBox *cmbContinue;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinBoxFreq;
    QLabel *label_13;
    QToolButton *btnWaterIn;
    QToolButton *btnValveBig;
    QToolButton *btnValveMiddle1;
    QToolButton *btnValveMiddle2;
    QToolButton *btnValveSmall;
    QToolButton *btnWaterOut;
    QToolButton *btnSetFreq;
    QToolButton *btnWaterPump;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_2;
    QLabel *label_9;
    QLCDNumber *lcdBigBalance;
    QLabel *label_11;
    QLabel *label_10;
    QLCDNumber *lcdSmallBalance;
    QLabel *label_12;
    QGridLayout *gridLayout_8;
    QLabel *label_3;
    QLCDNumber *lcdFlowRate;
    QLabel *label_6;
    QLabel *label_4;
    QLCDNumber *lcdInTemper;
    QLabel *label_7;
    QLabel *label_5;
    QLCDNumber *lcdOutTemper;
    QLabel *label_8;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_7;
    QLabel *label;
    QLabel *labelHintPoint;
    QLabel *label_2;
    QLabel *labelHintProcess;
    QGridLayout *gridLayout_4;
    QPushButton *btnExhaust;
    QPushButton *btnStart;
    QPushButton *btnNext;
    QPushButton *btnStop;
    QPushButton *btnExit;

    void setupUi(QWidget *FlowWeightClass)
    {
        if (FlowWeightClass->objectName().isEmpty())
            FlowWeightClass->setObjectName(QString::fromUtf8("FlowWeightClass"));
        FlowWeightClass->resize(1325, 856);
        gridLayout_6 = new QGridLayout(FlowWeightClass);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        tableWidget = new QTableWidget(FlowWeightClass);
        if (tableWidget->columnCount() < 12)
            tableWidget->setColumnCount(12);
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
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhFormattedNumbersOnly|Qt::ImhPreferNumbers);
        tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);

        gridLayout_6->addWidget(tableWidget, 0, 0, 1, 5);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        btnParaSet = new QPushButton(FlowWeightClass);
        btnParaSet->setObjectName(QString::fromUtf8("btnParaSet"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnParaSet->sizePolicy().hasHeightForWidth());
        btnParaSet->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(btnParaSet, 0, 0, 1, 1);

        btnReadMeter = new QPushButton(FlowWeightClass);
        btnReadMeter->setObjectName(QString::fromUtf8("btnReadMeter"));
        sizePolicy.setHeightForWidth(btnReadMeter->sizePolicy().hasHeightForWidth());
        btnReadMeter->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(btnReadMeter, 0, 1, 1, 1);

        groupBox = new QGroupBox(FlowWeightClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        labelStandard = new QLabel(groupBox);
        labelStandard->setObjectName(QString::fromUtf8("labelStandard"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelStandard->sizePolicy().hasHeightForWidth());
        labelStandard->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(labelStandard, 0, 0, 1, 1);

        lnEditStandard = new QLineEdit(groupBox);
        lnEditStandard->setObjectName(QString::fromUtf8("lnEditStandard"));
        lnEditStandard->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lnEditStandard->sizePolicy().hasHeightForWidth());
        lnEditStandard->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(lnEditStandard, 0, 1, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy1.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label_14, 1, 0, 1, 1);

        cmbAutoPick = new QComboBox(groupBox);
        cmbAutoPick->setObjectName(QString::fromUtf8("cmbAutoPick"));
        cmbAutoPick->setEnabled(false);
        sizePolicy2.setHeightForWidth(cmbAutoPick->sizePolicy().hasHeightForWidth());
        cmbAutoPick->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(cmbAutoPick, 1, 1, 1, 1);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy1.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label_16, 2, 0, 1, 1);

        cmbResetZero = new QComboBox(groupBox);
        cmbResetZero->setObjectName(QString::fromUtf8("cmbResetZero"));
        cmbResetZero->setEnabled(false);
        sizePolicy2.setHeightForWidth(cmbResetZero->sizePolicy().hasHeightForWidth());
        cmbResetZero->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(cmbResetZero, 2, 1, 1, 1);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy1.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label_15, 3, 0, 1, 1);

        cmbContinue = new QComboBox(groupBox);
        cmbContinue->setObjectName(QString::fromUtf8("cmbContinue"));
        cmbContinue->setEnabled(false);
        sizePolicy2.setHeightForWidth(cmbContinue->sizePolicy().hasHeightForWidth());
        cmbContinue->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(cmbContinue, 3, 1, 1, 1);


        gridLayout_5->addWidget(groupBox, 1, 0, 1, 2);


        gridLayout_6->addLayout(gridLayout_5, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(FlowWeightClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        spinBoxFreq = new QSpinBox(groupBox_2);
        spinBoxFreq->setObjectName(QString::fromUtf8("spinBoxFreq"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(spinBoxFreq->sizePolicy().hasHeightForWidth());
        spinBoxFreq->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(spinBoxFreq);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy4.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(label_13);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        btnWaterIn = new QToolButton(groupBox_2);
        btnWaterIn->setObjectName(QString::fromUtf8("btnWaterIn"));
        sizePolicy3.setHeightForWidth(btnWaterIn->sizePolicy().hasHeightForWidth());
        btnWaterIn->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(btnWaterIn, 0, 1, 3, 1);

        btnValveBig = new QToolButton(groupBox_2);
        btnValveBig->setObjectName(QString::fromUtf8("btnValveBig"));
        sizePolicy3.setHeightForWidth(btnValveBig->sizePolicy().hasHeightForWidth());
        btnValveBig->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(btnValveBig, 0, 2, 3, 1);

        btnValveMiddle1 = new QToolButton(groupBox_2);
        btnValveMiddle1->setObjectName(QString::fromUtf8("btnValveMiddle1"));
        sizePolicy3.setHeightForWidth(btnValveMiddle1->sizePolicy().hasHeightForWidth());
        btnValveMiddle1->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(btnValveMiddle1, 0, 3, 3, 1);

        btnValveMiddle2 = new QToolButton(groupBox_2);
        btnValveMiddle2->setObjectName(QString::fromUtf8("btnValveMiddle2"));
        sizePolicy3.setHeightForWidth(btnValveMiddle2->sizePolicy().hasHeightForWidth());
        btnValveMiddle2->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(btnValveMiddle2, 0, 4, 3, 1);

        btnValveSmall = new QToolButton(groupBox_2);
        btnValveSmall->setObjectName(QString::fromUtf8("btnValveSmall"));
        sizePolicy3.setHeightForWidth(btnValveSmall->sizePolicy().hasHeightForWidth());
        btnValveSmall->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(btnValveSmall, 0, 5, 3, 1);

        btnWaterOut = new QToolButton(groupBox_2);
        btnWaterOut->setObjectName(QString::fromUtf8("btnWaterOut"));
        sizePolicy3.setHeightForWidth(btnWaterOut->sizePolicy().hasHeightForWidth());
        btnWaterOut->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(btnWaterOut, 0, 6, 3, 1);

        btnSetFreq = new QToolButton(groupBox_2);
        btnSetFreq->setObjectName(QString::fromUtf8("btnSetFreq"));
        sizePolicy4.setHeightForWidth(btnSetFreq->sizePolicy().hasHeightForWidth());
        btnSetFreq->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(btnSetFreq, 1, 0, 1, 1);

        btnWaterPump = new QToolButton(groupBox_2);
        btnWaterPump->setObjectName(QString::fromUtf8("btnWaterPump"));
        sizePolicy4.setHeightForWidth(btnWaterPump->sizePolicy().hasHeightForWidth());
        btnWaterPump->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(btnWaterPump, 2, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_2, 1, 1, 1, 1);

        groupBox_4 = new QGroupBox(FlowWeightClass);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_10 = new QGridLayout(groupBox_4);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_9, 0, 0, 1, 1);

        lcdBigBalance = new QLCDNumber(groupBox_4);
        lcdBigBalance->setObjectName(QString::fromUtf8("lcdBigBalance"));
        sizePolicy2.setHeightForWidth(lcdBigBalance->sizePolicy().hasHeightForWidth());
        lcdBigBalance->setSizePolicy(sizePolicy2);
        lcdBigBalance->setNumDigits(10);
        lcdBigBalance->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_2->addWidget(lcdBigBalance, 0, 1, 1, 1);

        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_11, 0, 2, 1, 1);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_10, 1, 0, 1, 1);

        lcdSmallBalance = new QLCDNumber(groupBox_4);
        lcdSmallBalance->setObjectName(QString::fromUtf8("lcdSmallBalance"));
        sizePolicy2.setHeightForWidth(lcdSmallBalance->sizePolicy().hasHeightForWidth());
        lcdSmallBalance->setSizePolicy(sizePolicy2);
        lcdSmallBalance->setNumDigits(10);
        lcdSmallBalance->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_2->addWidget(lcdSmallBalance, 1, 1, 1, 1);

        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy1.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_12, 1, 2, 1, 1);


        gridLayout_10->addLayout(gridLayout_2, 0, 0, 1, 1);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_3, 0, 0, 1, 1);

        lcdFlowRate = new QLCDNumber(groupBox_4);
        lcdFlowRate->setObjectName(QString::fromUtf8("lcdFlowRate"));
        sizePolicy2.setHeightForWidth(lcdFlowRate->sizePolicy().hasHeightForWidth());
        lcdFlowRate->setSizePolicy(sizePolicy2);
        lcdFlowRate->setNumDigits(7);
        lcdFlowRate->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_8->addWidget(lcdFlowRate, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(label_6, 0, 2, 1, 1);

        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_4, 1, 0, 1, 1);

        lcdInTemper = new QLCDNumber(groupBox_4);
        lcdInTemper->setObjectName(QString::fromUtf8("lcdInTemper"));
        sizePolicy2.setHeightForWidth(lcdInTemper->sizePolicy().hasHeightForWidth());
        lcdInTemper->setSizePolicy(sizePolicy2);
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(100, 10, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        lcdInTemper->setPalette(palette);
        lcdInTemper->setNumDigits(5);
        lcdInTemper->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_8->addWidget(lcdInTemper, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(label_7, 1, 2, 1, 1);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_5, 2, 0, 1, 1);

        lcdOutTemper = new QLCDNumber(groupBox_4);
        lcdOutTemper->setObjectName(QString::fromUtf8("lcdOutTemper"));
        sizePolicy2.setHeightForWidth(lcdOutTemper->sizePolicy().hasHeightForWidth());
        lcdOutTemper->setSizePolicy(sizePolicy2);
        QPalette palette1;
        QBrush brush3(QColor(0, 255, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        lcdOutTemper->setPalette(palette1);
        lcdOutTemper->setSmallDecimalPoint(false);
        lcdOutTemper->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_8->addWidget(lcdOutTemper, 2, 1, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(label_8, 2, 2, 1, 1);


        gridLayout_10->addLayout(gridLayout_8, 1, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_4, 1, 2, 1, 1);

        groupBox_3 = new QGroupBox(FlowWeightClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy3.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy3);
        gridLayout_9 = new QGridLayout(groupBox_3);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_7->addWidget(label, 0, 0, 1, 1);

        labelHintPoint = new QLabel(groupBox_3);
        labelHintPoint->setObjectName(QString::fromUtf8("labelHintPoint"));
        sizePolicy4.setHeightForWidth(labelHintPoint->sizePolicy().hasHeightForWidth());
        labelHintPoint->setSizePolicy(sizePolicy4);
        labelHintPoint->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        labelHintPoint->setWordWrap(true);

        gridLayout_7->addWidget(labelHintPoint, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_7->addWidget(label_2, 1, 0, 1, 1);

        labelHintProcess = new QLabel(groupBox_3);
        labelHintProcess->setObjectName(QString::fromUtf8("labelHintProcess"));
        sizePolicy4.setHeightForWidth(labelHintProcess->sizePolicy().hasHeightForWidth());
        labelHintProcess->setSizePolicy(sizePolicy4);
        labelHintProcess->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        labelHintProcess->setWordWrap(true);

        gridLayout_7->addWidget(labelHintProcess, 1, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout_7, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_3, 1, 3, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        btnExhaust = new QPushButton(FlowWeightClass);
        btnExhaust->setObjectName(QString::fromUtf8("btnExhaust"));
        sizePolicy2.setHeightForWidth(btnExhaust->sizePolicy().hasHeightForWidth());
        btnExhaust->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(btnExhaust, 0, 0, 1, 1);

        btnStart = new QPushButton(FlowWeightClass);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        sizePolicy2.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
        btnStart->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(btnStart, 1, 0, 1, 1);

        btnNext = new QPushButton(FlowWeightClass);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));
        sizePolicy2.setHeightForWidth(btnNext->sizePolicy().hasHeightForWidth());
        btnNext->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(btnNext, 2, 0, 1, 1);

        btnStop = new QPushButton(FlowWeightClass);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        sizePolicy2.setHeightForWidth(btnStop->sizePolicy().hasHeightForWidth());
        btnStop->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(btnStop, 3, 0, 1, 1);

        btnExit = new QPushButton(FlowWeightClass);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        sizePolicy2.setHeightForWidth(btnExit->sizePolicy().hasHeightForWidth());
        btnExit->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(btnExit, 4, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 1, 4, 1, 1);


        retranslateUi(FlowWeightClass);

        QMetaObject::connectSlotsByName(FlowWeightClass);
    } // setupUi

    void retranslateUi(QWidget *FlowWeightClass)
    {
        FlowWeightClass->setWindowTitle(QApplication::translate("FlowWeightClass", "Flow Verify(Weight Method)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("FlowWeightClass", "MeterNo", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("FlowWeightClass", "FlowPoint(m\302\263/h)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("FlowWeightClass", "MeterValue0(L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("FlowWeightClass", "MeterValue1(L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("FlowWeightClass", "BalWeight0(kg)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("FlowWeightClass", "BalWeight1(kg)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("FlowWeightClass", "Temp(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("FlowWeightClass", "Density(kg/L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("FlowWeightClass", "StdValue(L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("FlowWeightClass", "DsipError(%)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("FlowWeightClass", "ModifyNO.", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QApplication::translate("FlowWeightClass", "AdjustError", 0, QApplication::UnicodeUTF8));
        btnParaSet->setText(QApplication::translate("FlowWeightClass", "ParaSet", 0, QApplication::UnicodeUTF8));
        btnReadMeter->setText(QApplication::translate("FlowWeightClass", "ReadMeter", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("FlowWeightClass", "NowPara(KeyInfo)", 0, QApplication::UnicodeUTF8));
        labelStandard->setText(QApplication::translate("FlowWeightClass", "Standard:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("FlowWeightClass", "DA Mode:", 0, QApplication::UnicodeUTF8));
        cmbAutoPick->clear();
        cmbAutoPick->insertItems(0, QStringList()
         << QApplication::translate("FlowWeightClass", "Manual", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FlowWeightClass", "Auto", 0, QApplication::UnicodeUTF8)
        );
        label_16->setText(QApplication::translate("FlowWeightClass", "ResetZero:", 0, QApplication::UnicodeUTF8));
        cmbResetZero->clear();
        cmbResetZero->insertItems(0, QStringList()
         << QApplication::translate("FlowWeightClass", "No", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FlowWeightClass", "Yes", 0, QApplication::UnicodeUTF8)
        );
        label_15->setText(QApplication::translate("FlowWeightClass", "Continuous:", 0, QApplication::UnicodeUTF8));
        cmbContinue->clear();
        cmbContinue->insertItems(0, QStringList()
         << QApplication::translate("FlowWeightClass", "Independent", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FlowWeightClass", "Continuous", 0, QApplication::UnicodeUTF8)
        );
        groupBox_2->setTitle(QApplication::translate("FlowWeightClass", "Controller", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("FlowWeightClass", "Hz", 0, QApplication::UnicodeUTF8));
        btnWaterIn->setText(QApplication::translate("FlowWeightClass", "i\n"
"n\n"
"", 0, QApplication::UnicodeUTF8));
        btnValveBig->setText(QApplication::translate("FlowWeightClass", "b\n"
"i\n"
"g", 0, QApplication::UnicodeUTF8));
        btnValveMiddle1->setText(QApplication::translate("FlowWeightClass", "m\n"
"i\n"
"d\n"
"1", 0, QApplication::UnicodeUTF8));
        btnValveMiddle2->setText(QApplication::translate("FlowWeightClass", "m\n"
"i\n"
"d\n"
"2", 0, QApplication::UnicodeUTF8));
        btnValveSmall->setText(QApplication::translate("FlowWeightClass", "s\n"
"m\n"
"a\n"
"l\n"
"l", 0, QApplication::UnicodeUTF8));
        btnWaterOut->setText(QApplication::translate("FlowWeightClass", "o\n"
"u\n"
"t", 0, QApplication::UnicodeUTF8));
        btnSetFreq->setText(QApplication::translate("FlowWeightClass", "Set Freq", 0, QApplication::UnicodeUTF8));
        btnWaterPump->setText(QApplication::translate("FlowWeightClass", "Start Pump", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("FlowWeightClass", "DataAcquisition", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FlowWeightClass", "Big Bal:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("FlowWeightClass", "\343\216\217", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("FlowWeightClass", "Small Bal:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("FlowWeightClass", "\343\216\217", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FlowWeightClass", "FlowRate:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FlowWeightClass", "m\302\263/h", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FlowWeightClass", "In Temp:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FlowWeightClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FlowWeightClass", "Out Temp:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FlowWeightClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("FlowWeightClass", "Process Hint", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FlowWeightClass", "FlowPnt:", 0, QApplication::UnicodeUTF8));
        labelHintPoint->setText(QString());
        label_2->setText(QApplication::translate("FlowWeightClass", "Process:", 0, QApplication::UnicodeUTF8));
        labelHintProcess->setText(QString());
        btnExhaust->setText(QApplication::translate("FlowWeightClass", "Exhaust", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("FlowWeightClass", "Start", 0, QApplication::UnicodeUTF8));
        btnNext->setText(QApplication::translate("FlowWeightClass", "Next", 0, QApplication::UnicodeUTF8));
        btnStop->setText(QApplication::translate("FlowWeightClass", "Stop", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("FlowWeightClass", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FlowWeightClass: public Ui_FlowWeightClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLOWWEIGHT_H
