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

QT_BEGIN_NAMESPACE

class Ui_CalcDlgClass
{
public:
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBoxInstallPos;
    QGridLayout *gridLayout_3;
    QRadioButton *radioButtonPosIn;
    QRadioButton *radioButtonPosOut;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBoxEnergyUnit;
    QGridLayout *gridLayout;
    QRadioButton *radioButtonMJ;
    QRadioButton *radioButtonKwh;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBoxAlgorithm;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButtonEnthalpy;
    QRadioButton *radioButtonKCoe;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *grpBoxMinDeltaT;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QLineEdit *lnEditMinDeltaT;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_7;
    QLabel *hintLabel;
    QGridLayout *gridLayout_6;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btnPara;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnStart;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnSave;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnExit;
    QSpacerItem *horizontalSpacer_7;

    void setupUi(QDialog *CalcDlgClass)
    {
        if (CalcDlgClass->objectName().isEmpty())
            CalcDlgClass->setObjectName(QString::fromUtf8("CalcDlgClass"));
        CalcDlgClass->resize(1350, 728);
        gridLayout_8 = new QGridLayout(CalcDlgClass);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBoxInstallPos = new QGroupBox(CalcDlgClass);
        groupBoxInstallPos->setObjectName(QString::fromUtf8("groupBoxInstallPos"));
        gridLayout_3 = new QGridLayout(groupBoxInstallPos);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        radioButtonPosIn = new QRadioButton(groupBoxInstallPos);
        radioButtonPosIn->setObjectName(QString::fromUtf8("radioButtonPosIn"));
        radioButtonPosIn->setChecked(false);

        gridLayout_3->addWidget(radioButtonPosIn, 0, 0, 1, 1);

        radioButtonPosOut = new QRadioButton(groupBoxInstallPos);
        radioButtonPosOut->setObjectName(QString::fromUtf8("radioButtonPosOut"));
        radioButtonPosOut->setChecked(true);

        gridLayout_3->addWidget(radioButtonPosOut, 0, 1, 1, 1);


        gridLayout_5->addWidget(groupBoxInstallPos, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 0, 1, 1, 1);

        groupBoxEnergyUnit = new QGroupBox(CalcDlgClass);
        groupBoxEnergyUnit->setObjectName(QString::fromUtf8("groupBoxEnergyUnit"));
        gridLayout = new QGridLayout(groupBoxEnergyUnit);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioButtonMJ = new QRadioButton(groupBoxEnergyUnit);
        radioButtonMJ->setObjectName(QString::fromUtf8("radioButtonMJ"));

        gridLayout->addWidget(radioButtonMJ, 0, 0, 1, 1);

        radioButtonKwh = new QRadioButton(groupBoxEnergyUnit);
        radioButtonKwh->setObjectName(QString::fromUtf8("radioButtonKwh"));
        radioButtonKwh->setChecked(true);

        gridLayout->addWidget(radioButtonKwh, 0, 1, 1, 1);


        gridLayout_5->addWidget(groupBoxEnergyUnit, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        groupBoxAlgorithm = new QGroupBox(CalcDlgClass);
        groupBoxAlgorithm->setObjectName(QString::fromUtf8("groupBoxAlgorithm"));
        gridLayout_2 = new QGridLayout(groupBoxAlgorithm);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButtonEnthalpy = new QRadioButton(groupBoxAlgorithm);
        radioButtonEnthalpy->setObjectName(QString::fromUtf8("radioButtonEnthalpy"));

        gridLayout_2->addWidget(radioButtonEnthalpy, 0, 0, 1, 1);

        radioButtonKCoe = new QRadioButton(groupBoxAlgorithm);
        radioButtonKCoe->setObjectName(QString::fromUtf8("radioButtonKCoe"));
        radioButtonKCoe->setChecked(true);

        gridLayout_2->addWidget(radioButtonKCoe, 0, 1, 1, 1);


        gridLayout_5->addWidget(groupBoxAlgorithm, 0, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 0, 5, 1, 1);

        grpBoxMinDeltaT = new QGroupBox(CalcDlgClass);
        grpBoxMinDeltaT->setObjectName(QString::fromUtf8("grpBoxMinDeltaT"));
        gridLayout_4 = new QGridLayout(grpBoxMinDeltaT);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label = new QLabel(grpBoxMinDeltaT);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        lnEditMinDeltaT = new QLineEdit(grpBoxMinDeltaT);
        lnEditMinDeltaT->setObjectName(QString::fromUtf8("lnEditMinDeltaT"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
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


        gridLayout_8->addLayout(gridLayout_5, 0, 0, 1, 1);

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

        gridLayout_8->addWidget(tableWidget, 1, 0, 1, 1);

        groupBox_5 = new QGroupBox(CalcDlgClass);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy1);
        groupBox_5->setProperty("toolTipDuration", QVariant(0));
        gridLayout_7 = new QGridLayout(groupBox_5);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        hintLabel = new QLabel(groupBox_5);
        hintLabel->setObjectName(QString::fromUtf8("hintLabel"));
        sizePolicy1.setHeightForWidth(hintLabel->sizePolicy().hasHeightForWidth());
        hintLabel->setSizePolicy(sizePolicy1);
        hintLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_7->addWidget(hintLabel, 0, 0, 1, 1);


        gridLayout_8->addWidget(groupBox_5, 2, 0, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalSpacer_8 = new QSpacerItem(718, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_8, 0, 0, 1, 1);

        btnPara = new QPushButton(CalcDlgClass);
        btnPara->setObjectName(QString::fromUtf8("btnPara"));
        sizePolicy1.setHeightForWidth(btnPara->sizePolicy().hasHeightForWidth());
        btnPara->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../source/gui/images/calculatorresult.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPara->setIcon(icon);

        gridLayout_6->addWidget(btnPara, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        btnStart = new QPushButton(CalcDlgClass);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        sizePolicy1.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
        btnStart->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../source/gui/images/excel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnStart->setIcon(icon1);

        gridLayout_6->addWidget(btnStart, 0, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_5, 0, 4, 1, 1);

        btnSave = new QPushButton(CalcDlgClass);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        sizePolicy1.setHeightForWidth(btnSave->sizePolicy().hasHeightForWidth());
        btnSave->setSizePolicy(sizePolicy1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../source/gui/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSave->setIcon(icon2);

        gridLayout_6->addWidget(btnSave, 0, 5, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_6, 0, 6, 1, 1);

        btnExit = new QPushButton(CalcDlgClass);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        sizePolicy1.setHeightForWidth(btnExit->sizePolicy().hasHeightForWidth());
        btnExit->setSizePolicy(sizePolicy1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnExit->setIcon(icon3);

        gridLayout_6->addWidget(btnExit, 0, 7, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(88, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_7, 0, 8, 1, 1);


        gridLayout_8->addLayout(gridLayout_6, 3, 0, 1, 1);

        QWidget::setTabOrder(lnEditMinDeltaT, tableWidget);
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
        groupBoxInstallPos->setTitle(QApplication::translate("CalcDlgClass", "InstallPos", 0, QApplication::UnicodeUTF8));
        radioButtonPosIn->setText(QApplication::translate("CalcDlgClass", "In", 0, QApplication::UnicodeUTF8));
        radioButtonPosOut->setText(QApplication::translate("CalcDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        groupBoxEnergyUnit->setTitle(QApplication::translate("CalcDlgClass", "EnergyUnit", 0, QApplication::UnicodeUTF8));
        radioButtonMJ->setText(QApplication::translate("CalcDlgClass", "MJ", 0, QApplication::UnicodeUTF8));
        radioButtonKwh->setText(QApplication::translate("CalcDlgClass", "kWh", 0, QApplication::UnicodeUTF8));
        groupBoxAlgorithm->setTitle(QApplication::translate("CalcDlgClass", "Algorithm", 0, QApplication::UnicodeUTF8));
        radioButtonEnthalpy->setText(QApplication::translate("CalcDlgClass", "EnthalpyDiff", 0, QApplication::UnicodeUTF8));
        radioButtonKCoe->setText(QApplication::translate("CalcDlgClass", "KCoe", 0, QApplication::UnicodeUTF8));
        grpBoxMinDeltaT->setTitle(QApplication::translate("CalcDlgClass", "MinDeltaT", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270min:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CalcDlgClass", "K", 0, QApplication::UnicodeUTF8));
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

        groupBox_5->setTitle(QApplication::translate("CalcDlgClass", "HintInfo", 0, QApplication::UnicodeUTF8));
        hintLabel->setText(QApplication::translate("CalcDlgClass", "Hint: Please set para first!", 0, QApplication::UnicodeUTF8));
        btnPara->setText(QApplication::translate("CalcDlgClass", "Para", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("CalcDlgClass", "Start", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("CalcDlgClass", "Save", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("CalcDlgClass", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CalcDlgClass: public Ui_CalcDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCVERIFY_H
