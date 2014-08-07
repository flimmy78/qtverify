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
    QPushButton *btnParaSet;
    QGroupBox *groupBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelStandard;
    QLineEdit *lnEditStandard;
    QWidget *widget1;
    QGridLayout *gridLayout_5;
    QLabel *label_14;
    QComboBox *cmbAutoPick;
    QLabel *label_15;
    QComboBox *cmbContinue;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_13;
    QSpinBox *spinBoxFrequency;
    QToolButton *btnWaterIn;
    QToolButton *btnWaterOut;
    QToolButton *btnValveBig;
    QToolButton *btnValveMiddle1;
    QToolButton *btnValveMiddle2;
    QToolButton *btnValveSmall;
    QToolButton *btnWaterPumpStart;
    QToolButton *btnWaterPumpStop;
    QTableWidget *tableWidget;
    QPushButton *btnExhaust;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QGroupBox *groupBox_3;
    QLabel *labelHintInfo;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLCDNumber *lcdNumberFlow;
    QLabel *label_6;
    QLabel *label_4;
    QLCDNumber *lcdNumberInTemper;
    QLabel *label_7;
    QLabel *label_5;
    QLCDNumber *lcdNumberOutTemper;
    QLabel *label_8;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_3;
    QLabel *label_9;
    QLineEdit *lnEditBigBalance;
    QLabel *label_11;
    QLabel *label_10;
    QLineEdit *lnEditSmallBalance;
    QLabel *label_12;
    QPushButton *btnNext;
    QWidget *tab2;
    QWidget *tab3;
    QWidget *tab4;
    QWidget *tab5;

    void setupUi(QWidget *WeightMethodClass)
    {
        if (WeightMethodClass->objectName().isEmpty())
            WeightMethodClass->setObjectName(QString::fromUtf8("WeightMethodClass"));
        WeightMethodClass->resize(1284, 838);
        gridLayout = new QGridLayout(WeightMethodClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(WeightMethodClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        btnParaSet = new QPushButton(tab1);
        btnParaSet->setObjectName(QString::fromUtf8("btnParaSet"));
        btnParaSet->setGeometry(QRect(20, 620, 93, 28));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnParaSet->sizePolicy().hasHeightForWidth());
        btnParaSet->setSizePolicy(sizePolicy);
        groupBox = new QGroupBox(tab1);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 660, 261, 121));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 20, 121, 23));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        labelStandard = new QLabel(widget);
        labelStandard->setObjectName(QString::fromUtf8("labelStandard"));

        horizontalLayout_2->addWidget(labelStandard);

        lnEditStandard = new QLineEdit(widget);
        lnEditStandard->setObjectName(QString::fromUtf8("lnEditStandard"));
        lnEditStandard->setEnabled(false);

        horizontalLayout_2->addWidget(lnEditStandard);

        widget1 = new QWidget(groupBox);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(11, 61, 191, 51));
        gridLayout_5 = new QGridLayout(widget1);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(widget1);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_5->addWidget(label_14, 0, 0, 1, 1);

        cmbAutoPick = new QComboBox(widget1);
        cmbAutoPick->setObjectName(QString::fromUtf8("cmbAutoPick"));
        cmbAutoPick->setEnabled(false);

        gridLayout_5->addWidget(cmbAutoPick, 0, 1, 1, 1);

        label_15 = new QLabel(widget1);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_5->addWidget(label_15, 1, 0, 1, 1);

        cmbContinue = new QComboBox(widget1);
        cmbContinue->setObjectName(QString::fromUtf8("cmbContinue"));
        cmbContinue->setEnabled(false);

        gridLayout_5->addWidget(cmbContinue, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(tab1);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(290, 630, 401, 141));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_13);

        spinBoxFrequency = new QSpinBox(groupBox_2);
        spinBoxFrequency->setObjectName(QString::fromUtf8("spinBoxFrequency"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinBoxFrequency->sizePolicy().hasHeightForWidth());
        spinBoxFrequency->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(spinBoxFrequency);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 1);

        btnWaterIn = new QToolButton(groupBox_2);
        btnWaterIn->setObjectName(QString::fromUtf8("btnWaterIn"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnWaterIn->sizePolicy().hasHeightForWidth());
        btnWaterIn->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(btnWaterIn, 0, 1, 3, 1);

        btnWaterOut = new QToolButton(groupBox_2);
        btnWaterOut->setObjectName(QString::fromUtf8("btnWaterOut"));
        sizePolicy3.setHeightForWidth(btnWaterOut->sizePolicy().hasHeightForWidth());
        btnWaterOut->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(btnWaterOut, 0, 2, 3, 1);

        btnValveBig = new QToolButton(groupBox_2);
        btnValveBig->setObjectName(QString::fromUtf8("btnValveBig"));
        sizePolicy3.setHeightForWidth(btnValveBig->sizePolicy().hasHeightForWidth());
        btnValveBig->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(btnValveBig, 0, 3, 3, 1);

        btnValveMiddle1 = new QToolButton(groupBox_2);
        btnValveMiddle1->setObjectName(QString::fromUtf8("btnValveMiddle1"));
        sizePolicy3.setHeightForWidth(btnValveMiddle1->sizePolicy().hasHeightForWidth());
        btnValveMiddle1->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(btnValveMiddle1, 0, 4, 3, 1);

        btnValveMiddle2 = new QToolButton(groupBox_2);
        btnValveMiddle2->setObjectName(QString::fromUtf8("btnValveMiddle2"));
        sizePolicy3.setHeightForWidth(btnValveMiddle2->sizePolicy().hasHeightForWidth());
        btnValveMiddle2->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(btnValveMiddle2, 0, 5, 3, 1);

        btnValveSmall = new QToolButton(groupBox_2);
        btnValveSmall->setObjectName(QString::fromUtf8("btnValveSmall"));
        sizePolicy3.setHeightForWidth(btnValveSmall->sizePolicy().hasHeightForWidth());
        btnValveSmall->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(btnValveSmall, 0, 6, 3, 1);

        btnWaterPumpStart = new QToolButton(groupBox_2);
        btnWaterPumpStart->setObjectName(QString::fromUtf8("btnWaterPumpStart"));
        sizePolicy3.setHeightForWidth(btnWaterPumpStart->sizePolicy().hasHeightForWidth());
        btnWaterPumpStart->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(btnWaterPumpStart, 1, 0, 1, 1);

        btnWaterPumpStop = new QToolButton(groupBox_2);
        btnWaterPumpStop->setObjectName(QString::fromUtf8("btnWaterPumpStop"));
        sizePolicy3.setHeightForWidth(btnWaterPumpStop->sizePolicy().hasHeightForWidth());
        btnWaterPumpStop->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(btnWaterPumpStop, 2, 0, 1, 1);

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
        tableWidget->setGeometry(QRect(20, 20, 1221, 581));
        tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        btnExhaust = new QPushButton(tab1);
        btnExhaust->setObjectName(QString::fromUtf8("btnExhaust"));
        btnExhaust->setGeometry(QRect(1150, 620, 93, 28));
        btnStart = new QPushButton(tab1);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(1150, 660, 93, 28));
        btnStop = new QPushButton(tab1);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(1150, 740, 93, 28));
        groupBox_3 = new QGroupBox(tab1);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(920, 620, 221, 151));
        labelHintInfo = new QLabel(groupBox_3);
        labelHintInfo->setObjectName(QString::fromUtf8("labelHintInfo"));
        labelHintInfo->setGeometry(QRect(20, 20, 151, 121));
        layoutWidget = new QWidget(tab1);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(710, 690, 191, 85));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        lcdNumberFlow = new QLCDNumber(layoutWidget);
        lcdNumberFlow->setObjectName(QString::fromUtf8("lcdNumberFlow"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lcdNumberFlow->sizePolicy().hasHeightForWidth());
        lcdNumberFlow->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(lcdNumberFlow, 0, 1, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_6, 0, 2, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        lcdNumberInTemper = new QLCDNumber(layoutWidget);
        lcdNumberInTemper->setObjectName(QString::fromUtf8("lcdNumberInTemper"));
        sizePolicy4.setHeightForWidth(lcdNumberInTemper->sizePolicy().hasHeightForWidth());
        lcdNumberInTemper->setSizePolicy(sizePolicy4);
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

        gridLayout_2->addWidget(lcdNumberInTemper, 1, 1, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_7, 1, 2, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        lcdNumberOutTemper = new QLCDNumber(layoutWidget);
        lcdNumberOutTemper->setObjectName(QString::fromUtf8("lcdNumberOutTemper"));
        sizePolicy4.setHeightForWidth(lcdNumberOutTemper->sizePolicy().hasHeightForWidth());
        lcdNumberOutTemper->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(lcdNumberOutTemper, 2, 1, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_8, 2, 2, 1, 1);

        layoutWidget1 = new QWidget(tab1);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(710, 620, 191, 51));
        gridLayout_3 = new QGridLayout(layoutWidget1);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_9, 0, 0, 1, 1);

        lnEditBigBalance = new QLineEdit(layoutWidget1);
        lnEditBigBalance->setObjectName(QString::fromUtf8("lnEditBigBalance"));
        sizePolicy2.setHeightForWidth(lnEditBigBalance->sizePolicy().hasHeightForWidth());
        lnEditBigBalance->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(lnEditBigBalance, 0, 1, 1, 1);

        label_11 = new QLabel(layoutWidget1);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_11, 0, 2, 1, 1);

        label_10 = new QLabel(layoutWidget1);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_10, 1, 0, 1, 1);

        lnEditSmallBalance = new QLineEdit(layoutWidget1);
        lnEditSmallBalance->setObjectName(QString::fromUtf8("lnEditSmallBalance"));
        sizePolicy2.setHeightForWidth(lnEditSmallBalance->sizePolicy().hasHeightForWidth());
        lnEditSmallBalance->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(lnEditSmallBalance, 1, 1, 1, 1);

        label_12 = new QLabel(layoutWidget1);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_12, 1, 2, 1, 1);

        btnNext = new QPushButton(tab1);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));
        btnNext->setGeometry(QRect(1150, 700, 93, 28));
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
        WeightMethodClass->setWindowTitle(QApplication::translate("WeightMethodClass", "\350\264\250\351\207\217\346\263\225\346\243\200\345\256\232", 0, QApplication::UnicodeUTF8));
        btnParaSet->setText(QApplication::translate("WeightMethodClass", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("WeightMethodClass", "\345\275\223\345\211\215\345\217\202\346\225\260(\345\205\263\351\224\256\344\277\241\346\201\257)", 0, QApplication::UnicodeUTF8));
        labelStandard->setText(QApplication::translate("WeightMethodClass", "\350\247\204\346\240\274\357\274\232", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("WeightMethodClass", "\351\207\207\351\233\206\346\226\271\345\274\217\357\274\232", 0, QApplication::UnicodeUTF8));
        cmbAutoPick->clear();
        cmbAutoPick->insertItems(0, QStringList()
         << QApplication::translate("WeightMethodClass", "\346\211\213\345\212\250\351\207\207\351\233\206", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WeightMethodClass", "\350\207\252\345\212\250\351\207\207\351\233\206", 0, QApplication::UnicodeUTF8)
        );
        label_15->setText(QApplication::translate("WeightMethodClass", "\346\230\257\345\220\246\350\277\236\347\273\255:", 0, QApplication::UnicodeUTF8));
        cmbContinue->clear();
        cmbContinue->insertItems(0, QStringList()
         << QApplication::translate("WeightMethodClass", "\351\235\236\350\277\236\347\273\255\346\243\200\345\256\232", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WeightMethodClass", "\350\277\236\347\273\255\346\243\200\345\256\232", 0, QApplication::UnicodeUTF8)
        );
        groupBox_2->setTitle(QApplication::translate("WeightMethodClass", "\351\230\200\351\227\250\343\200\201\346\260\264\346\263\265\343\200\201\345\217\230\351\242\221\345\231\250\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("WeightMethodClass", "\351\242\221\347\216\207", 0, QApplication::UnicodeUTF8));
        btnWaterIn->setText(QApplication::translate("WeightMethodClass", "\350\277\233\n"
"\346\260\264\n"
"\351\230\200", 0, QApplication::UnicodeUTF8));
        btnWaterOut->setText(QApplication::translate("WeightMethodClass", "\346\224\276\n"
"\346\260\264\n"
"\351\230\200", 0, QApplication::UnicodeUTF8));
        btnValveBig->setText(QApplication::translate("WeightMethodClass", "\345\244\247\n"
"\346\265\201\n"
"\351\207\217\n"
"\351\230\200", 0, QApplication::UnicodeUTF8));
        btnValveMiddle1->setText(QApplication::translate("WeightMethodClass", "\344\270\255\n"
"\346\265\201\n"
"\344\270\200\n"
"\351\230\200", 0, QApplication::UnicodeUTF8));
        btnValveMiddle2->setText(QApplication::translate("WeightMethodClass", "\344\270\255\n"
"\346\265\201\n"
"\344\272\214\n"
"\351\230\200", 0, QApplication::UnicodeUTF8));
        btnValveSmall->setText(QApplication::translate("WeightMethodClass", "\345\260\217\n"
"\346\265\201\n"
"\351\207\217\n"
"\351\230\200", 0, QApplication::UnicodeUTF8));
        btnWaterPumpStart->setText(QApplication::translate("WeightMethodClass", "\345\220\257\345\212\250\346\260\264\346\263\265", 0, QApplication::UnicodeUTF8));
        btnWaterPumpStop->setText(QApplication::translate("WeightMethodClass", "\345\205\263\351\227\255\346\260\264\346\263\265", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("WeightMethodClass", "\350\241\250\345\217\267", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("WeightMethodClass", "\346\265\201\351\207\217\347\202\271(m\302\263/h)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("WeightMethodClass", "\350\241\250\345\210\235\345\200\274(L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("WeightMethodClass", "\350\241\250\347\273\210\345\200\274(L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("WeightMethodClass", "\345\244\251\345\271\263\345\210\235\345\200\274(kg)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("WeightMethodClass", "\345\244\251\345\271\263\347\273\210\345\200\274(kg)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("WeightMethodClass", "\346\270\251\345\272\246(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("WeightMethodClass", "\345\257\206\345\272\246(kg/L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("WeightMethodClass", "\346\240\207\345\207\206\345\200\274(L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("WeightMethodClass", "\347\244\272\345\200\274\350\257\257\345\267\256(%)", 0, QApplication::UnicodeUTF8));
        btnExhaust->setText(QApplication::translate("WeightMethodClass", "\346\216\222\346\260\224", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("WeightMethodClass", "\345\274\200\345\247\213", 0, QApplication::UnicodeUTF8));
        btnStop->setText(QApplication::translate("WeightMethodClass", "\347\273\210\346\255\242\346\243\200\346\265\213", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("WeightMethodClass", "\346\265\201\347\250\213\346\217\220\347\244\272", 0, QApplication::UnicodeUTF8));
        labelHintInfo->setText(QApplication::translate("WeightMethodClass", "\346\217\220\347\244\272\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("WeightMethodClass", "\346\265\201\351\207\217", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("WeightMethodClass", "m\302\263/h", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("WeightMethodClass", "\345\205\245\345\217\243\346\270\251\345\272\246", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("WeightMethodClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("WeightMethodClass", "\345\207\272\345\217\243\346\270\251\345\272\246", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("WeightMethodClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("WeightMethodClass", "\345\244\247\345\244\251\345\271\263", 0, QApplication::UnicodeUTF8));
        lnEditBigBalance->setText(QString());
        label_11->setText(QApplication::translate("WeightMethodClass", "\343\216\217", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("WeightMethodClass", "\345\260\217\345\244\251\345\271\263", 0, QApplication::UnicodeUTF8));
        lnEditSmallBalance->setText(QString());
        label_12->setText(QApplication::translate("WeightMethodClass", "\343\216\217", 0, QApplication::UnicodeUTF8));
        btnNext->setText(QApplication::translate("WeightMethodClass", "\344\270\213\344\270\200\346\255\245", 0, QApplication::UnicodeUTF8));
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
