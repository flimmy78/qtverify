/********************************************************************************
** Form generated from reading UI file 'calcverify.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCVERIFY_H
#define UI_CALCVERIFY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalcDlgClass
{
public:
    QGroupBox *groupBox_5;
    QLabel *hintLabel;
    QPushButton *btnPara;
    QPushButton *btnStart;
    QPushButton *btnSave;
    QPushButton *btnExit;
    QTableWidget *tableWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_5;
    QGroupBox *grpBoxInstallPos;
    QGridLayout *gridLayout;
    QRadioButton *radioButtonPosIn;
    QRadioButton *radioButtonPosOut;
    QSpacerItem *horizontalSpacer;
    QGroupBox *grpBoxEnergyUnit;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButtonMJ;
    QRadioButton *radioButtonKwh;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *grpBoxAlgorithm;
    QGridLayout *gridLayout_3;
    QRadioButton *radioButtonEnthalpy;
    QRadioButton *radioButtonKCoe;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *grpBoxMinDeltaT;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QLineEdit *lnEditMinDeltaT;
    QLabel *label_2;

    void setupUi(QDialog *CalcDlgClass)
    {
        if (CalcDlgClass->objectName().isEmpty())
            CalcDlgClass->setObjectName(QString::fromUtf8("CalcDlgClass"));
        CalcDlgClass->resize(1365, 858);
        groupBox_5 = new QGroupBox(CalcDlgClass);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 700, 1341, 91));
        groupBox_5->setProperty("toolTipDuration", QVariant(0));
        hintLabel = new QLabel(groupBox_5);
        hintLabel->setObjectName(QString::fromUtf8("hintLabel"));
        hintLabel->setGeometry(QRect(30, 36, 441, 20));
        hintLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        btnPara = new QPushButton(CalcDlgClass);
        btnPara->setObjectName(QString::fromUtf8("btnPara"));
        btnPara->setGeometry(QRect(740, 810, 75, 41));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnPara->sizePolicy().hasHeightForWidth());
        btnPara->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../source/gui/images/calculatorresult.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPara->setIcon(icon);
        btnStart = new QPushButton(CalcDlgClass);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(890, 810, 75, 41));
        sizePolicy.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
        btnStart->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../source/gui/images/excel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnStart->setIcon(icon1);
        btnSave = new QPushButton(CalcDlgClass);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(1030, 810, 75, 41));
        sizePolicy.setHeightForWidth(btnSave->sizePolicy().hasHeightForWidth());
        btnSave->setSizePolicy(sizePolicy);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../source/gui/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSave->setIcon(icon2);
        btnExit = new QPushButton(CalcDlgClass);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        btnExit->setGeometry(QRect(1170, 810, 75, 41));
        sizePolicy.setHeightForWidth(btnExit->sizePolicy().hasHeightForWidth());
        btnExit->setSizePolicy(sizePolicy);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnExit->setIcon(icon3);
        tableWidget = new QTableWidget(CalcDlgClass);
        if (tableWidget->columnCount() < 14)
            tableWidget->setColumnCount(14);
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
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(13, __qtablewidgetitem13);
        if (tableWidget->rowCount() < 15)
            tableWidget->setRowCount(15);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(11, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(12, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(13, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(14, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        __qtablewidgetitem29->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(0, 0, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        __qtablewidgetitem30->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget->setItem(0, 1, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        __qtablewidgetitem32->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(1, 0, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        __qtablewidgetitem33->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget->setItem(1, 1, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        __qtablewidgetitem35->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(2, 0, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        __qtablewidgetitem37->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(3, 0, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget->setItem(3, 2, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        __qtablewidgetitem39->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(4, 0, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget->setItem(4, 2, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        __qtablewidgetitem41->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(5, 0, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget->setItem(5, 2, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        __qtablewidgetitem43->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(6, 0, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget->setItem(6, 2, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        __qtablewidgetitem45->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(7, 0, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget->setItem(7, 2, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget->setItem(8, 2, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget->setItem(9, 2, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget->setItem(10, 2, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget->setItem(11, 2, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidget->setItem(12, 2, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidget->setItem(13, 2, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidget->setItem(14, 2, __qtablewidgetitem53);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 110, 1341, 581));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(7);
        tableWidget->setFont(font);
        tableWidget->setLayoutDirection(Qt::LeftToRight);
        tableWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableWidget->setTextElideMode(Qt::ElideMiddle);
        tableWidget->horizontalHeader()->setDefaultSectionSize(90);
        layoutWidget = new QWidget(CalcDlgClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(12, 10, 1341, 62));
        gridLayout_5 = new QGridLayout(layoutWidget);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        grpBoxInstallPos = new QGroupBox(layoutWidget);
        grpBoxInstallPos->setObjectName(QString::fromUtf8("grpBoxInstallPos"));
        gridLayout = new QGridLayout(grpBoxInstallPos);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioButtonPosIn = new QRadioButton(grpBoxInstallPos);
        radioButtonPosIn->setObjectName(QString::fromUtf8("radioButtonPosIn"));
        radioButtonPosIn->setChecked(true);

        gridLayout->addWidget(radioButtonPosIn, 0, 0, 1, 1);

        radioButtonPosOut = new QRadioButton(grpBoxInstallPos);
        radioButtonPosOut->setObjectName(QString::fromUtf8("radioButtonPosOut"));

        gridLayout->addWidget(radioButtonPosOut, 0, 1, 1, 1);


        gridLayout_5->addWidget(grpBoxInstallPos, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 0, 1, 1, 1);

        grpBoxEnergyUnit = new QGroupBox(layoutWidget);
        grpBoxEnergyUnit->setObjectName(QString::fromUtf8("grpBoxEnergyUnit"));
        gridLayout_2 = new QGridLayout(grpBoxEnergyUnit);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButtonMJ = new QRadioButton(grpBoxEnergyUnit);
        radioButtonMJ->setObjectName(QString::fromUtf8("radioButtonMJ"));

        gridLayout_2->addWidget(radioButtonMJ, 0, 0, 1, 1);

        radioButtonKwh = new QRadioButton(grpBoxEnergyUnit);
        radioButtonKwh->setObjectName(QString::fromUtf8("radioButtonKwh"));
        radioButtonKwh->setChecked(true);

        gridLayout_2->addWidget(radioButtonKwh, 0, 1, 1, 1);


        gridLayout_5->addWidget(grpBoxEnergyUnit, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        grpBoxAlgorithm = new QGroupBox(layoutWidget);
        grpBoxAlgorithm->setObjectName(QString::fromUtf8("grpBoxAlgorithm"));
        gridLayout_3 = new QGridLayout(grpBoxAlgorithm);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        radioButtonEnthalpy = new QRadioButton(grpBoxAlgorithm);
        radioButtonEnthalpy->setObjectName(QString::fromUtf8("radioButtonEnthalpy"));

        gridLayout_3->addWidget(radioButtonEnthalpy, 0, 0, 1, 1);

        radioButtonKCoe = new QRadioButton(grpBoxAlgorithm);
        radioButtonKCoe->setObjectName(QString::fromUtf8("radioButtonKCoe"));
        radioButtonKCoe->setChecked(true);

        gridLayout_3->addWidget(radioButtonKCoe, 0, 1, 1, 1);


        gridLayout_5->addWidget(grpBoxAlgorithm, 0, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 0, 5, 1, 1);

        grpBoxMinDeltaT = new QGroupBox(layoutWidget);
        grpBoxMinDeltaT->setObjectName(QString::fromUtf8("grpBoxMinDeltaT"));
        gridLayout_4 = new QGridLayout(grpBoxMinDeltaT);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label = new QLabel(grpBoxMinDeltaT);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        lnEditMinDeltaT = new QLineEdit(grpBoxMinDeltaT);
        lnEditMinDeltaT->setObjectName(QString::fromUtf8("lnEditMinDeltaT"));
        sizePolicy.setHeightForWidth(lnEditMinDeltaT->sizePolicy().hasHeightForWidth());
        lnEditMinDeltaT->setSizePolicy(sizePolicy);
        lnEditMinDeltaT->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 231, 201);"));
        lnEditMinDeltaT->setAlignment(Qt::AlignCenter);
        lnEditMinDeltaT->setReadOnly(true);

        gridLayout_4->addWidget(lnEditMinDeltaT, 0, 1, 1, 1);

        label_2 = new QLabel(grpBoxMinDeltaT);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 0, 2, 1, 1);


        gridLayout_5->addWidget(grpBoxMinDeltaT, 0, 6, 1, 1);

        QWidget::setTabOrder(radioButtonPosIn, radioButtonPosOut);
        QWidget::setTabOrder(radioButtonPosOut, radioButtonMJ);
        QWidget::setTabOrder(radioButtonMJ, radioButtonKwh);
        QWidget::setTabOrder(radioButtonKwh, lnEditMinDeltaT);
        QWidget::setTabOrder(lnEditMinDeltaT, radioButtonEnthalpy);
        QWidget::setTabOrder(radioButtonEnthalpy, radioButtonKCoe);
        QWidget::setTabOrder(radioButtonKCoe, tableWidget);
        QWidget::setTabOrder(tableWidget, btnPara);
        QWidget::setTabOrder(btnPara, btnStart);
        QWidget::setTabOrder(btnStart, btnSave);
        QWidget::setTabOrder(btnSave, btnExit);

        retranslateUi(CalcDlgClass);

        QMetaObject::connectSlotsByName(CalcDlgClass);
    } // setupUi

    void retranslateUi(QDialog *CalcDlgClass)
    {
        CalcDlgClass->setWindowTitle(QApplication::translate("CalcDlgClass", "\350\256\241\347\256\227\345\231\250\346\243\200\346\265\213", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("CalcDlgClass", "HintInfo", 0, QApplication::UnicodeUTF8));
        hintLabel->setText(QApplication::translate("CalcDlgClass", "Hint: Please set para first!", 0, QApplication::UnicodeUTF8));
        btnPara->setText(QApplication::translate("CalcDlgClass", "Para", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("CalcDlgClass", "Start", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("CalcDlgClass", "Save", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("CalcDlgClass", "Exit", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CalcDlgClass", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CalcDlgClass", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("CalcDlgClass", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270min", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("CalcDlgClass", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("CalcDlgClass", "20", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270ref    ", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem7->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270min", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem8->setText(QApplication::translate("CalcDlgClass", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem9->setText(QApplication::translate("CalcDlgClass", "20", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem10->setText(QApplication::translate("CalcDlgClass", "20", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem11->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270ref", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(14);
        ___qtablewidgetitem12->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270max-5", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        grpBoxInstallPos->setTitle(QApplication::translate("CalcDlgClass", "InstallPos", 0, QApplication::UnicodeUTF8));
        radioButtonPosIn->setText(QApplication::translate("CalcDlgClass", "In", 0, QApplication::UnicodeUTF8));
        radioButtonPosOut->setText(QApplication::translate("CalcDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        grpBoxEnergyUnit->setTitle(QApplication::translate("CalcDlgClass", "EnergyUnit", 0, QApplication::UnicodeUTF8));
        radioButtonMJ->setText(QApplication::translate("CalcDlgClass", "MJ", 0, QApplication::UnicodeUTF8));
        radioButtonKwh->setText(QApplication::translate("CalcDlgClass", "kWh", 0, QApplication::UnicodeUTF8));
        grpBoxAlgorithm->setTitle(QApplication::translate("CalcDlgClass", "Algorithm", 0, QApplication::UnicodeUTF8));
        radioButtonEnthalpy->setText(QApplication::translate("CalcDlgClass", "EnthalpyDiff", 0, QApplication::UnicodeUTF8));
        radioButtonKCoe->setText(QApplication::translate("CalcDlgClass", "KCoe", 0, QApplication::UnicodeUTF8));
        grpBoxMinDeltaT->setTitle(QApplication::translate("CalcDlgClass", "MinDeltaT", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270min:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CalcDlgClass", "K", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CalcDlgClass: public Ui_CalcDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCVERIFY_H
