/********************************************************************************
** Form generated from reading UI file 'setportfrm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETPORTFRM_H
#define UI_SETPORTFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetPortFrm
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *gBox_Valve;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *cBox_Inlet;
    QLabel *label_2;
    QComboBox *cBox_Outlet;
    QLabel *label_3;
    QComboBox *cBox_Rate_1;
    QLabel *label_4;
    QComboBox *cBox_Rate_2;
    QLabel *label_5;
    QComboBox *cBox_Rate_3;
    QLabel *label_6;
    QComboBox *cBox_Rate_4;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *gBox_Dev;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QComboBox *cBox_Pump;
    QLabel *label_8;
    QComboBox *cBox_Regulate_1;
    QLabel *label_9;
    QComboBox *cBox_Regulate_2;
    QLabel *label_10;
    QComboBox *cBox_Regulate_3;
    QLabel *label_11;
    QComboBox *cBox_Regulate_4;
    QGridLayout *gridLayout_3;
    QLabel *label_12;
    QComboBox *cBox_Version;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_Save;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_Exit;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *SetPortFrm)
    {
        if (SetPortFrm->objectName().isEmpty())
            SetPortFrm->setObjectName(QString::fromUtf8("SetPortFrm"));
        SetPortFrm->setWindowModality(Qt::ApplicationModal);
        SetPortFrm->resize(446, 270);
        gridLayout_4 = new QGridLayout(SetPortFrm);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gBox_Valve = new QGroupBox(SetPortFrm);
        gBox_Valve->setObjectName(QString::fromUtf8("gBox_Valve"));
        gridLayout = new QGridLayout(gBox_Valve);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(gBox_Valve);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cBox_Inlet = new QComboBox(gBox_Valve);
        cBox_Inlet->setObjectName(QString::fromUtf8("cBox_Inlet"));

        gridLayout->addWidget(cBox_Inlet, 0, 1, 1, 1);

        label_2 = new QLabel(gBox_Valve);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        cBox_Outlet = new QComboBox(gBox_Valve);
        cBox_Outlet->setObjectName(QString::fromUtf8("cBox_Outlet"));

        gridLayout->addWidget(cBox_Outlet, 1, 1, 1, 1);

        label_3 = new QLabel(gBox_Valve);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        cBox_Rate_1 = new QComboBox(gBox_Valve);
        cBox_Rate_1->setObjectName(QString::fromUtf8("cBox_Rate_1"));

        gridLayout->addWidget(cBox_Rate_1, 2, 1, 1, 1);

        label_4 = new QLabel(gBox_Valve);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        cBox_Rate_2 = new QComboBox(gBox_Valve);
        cBox_Rate_2->setObjectName(QString::fromUtf8("cBox_Rate_2"));

        gridLayout->addWidget(cBox_Rate_2, 3, 1, 1, 1);

        label_5 = new QLabel(gBox_Valve);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        cBox_Rate_3 = new QComboBox(gBox_Valve);
        cBox_Rate_3->setObjectName(QString::fromUtf8("cBox_Rate_3"));

        gridLayout->addWidget(cBox_Rate_3, 4, 1, 1, 1);

        label_6 = new QLabel(gBox_Valve);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        cBox_Rate_4 = new QComboBox(gBox_Valve);
        cBox_Rate_4->setObjectName(QString::fromUtf8("cBox_Rate_4"));

        gridLayout->addWidget(cBox_Rate_4, 5, 1, 1, 1);


        gridLayout_4->addWidget(gBox_Valve, 0, 0, 2, 1);

        horizontalSpacer_4 = new QSpacerItem(8, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 0, 1, 1, 1);

        gBox_Dev = new QGroupBox(SetPortFrm);
        gBox_Dev->setObjectName(QString::fromUtf8("gBox_Dev"));
        gridLayout_2 = new QGridLayout(gBox_Dev);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_7 = new QLabel(gBox_Dev);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        cBox_Pump = new QComboBox(gBox_Dev);
        cBox_Pump->setObjectName(QString::fromUtf8("cBox_Pump"));

        gridLayout_2->addWidget(cBox_Pump, 0, 1, 1, 1);

        label_8 = new QLabel(gBox_Dev);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        cBox_Regulate_1 = new QComboBox(gBox_Dev);
        cBox_Regulate_1->setObjectName(QString::fromUtf8("cBox_Regulate_1"));

        gridLayout_2->addWidget(cBox_Regulate_1, 1, 1, 1, 1);

        label_9 = new QLabel(gBox_Dev);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 2, 0, 1, 1);

        cBox_Regulate_2 = new QComboBox(gBox_Dev);
        cBox_Regulate_2->setObjectName(QString::fromUtf8("cBox_Regulate_2"));

        gridLayout_2->addWidget(cBox_Regulate_2, 2, 1, 1, 1);

        label_10 = new QLabel(gBox_Dev);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 3, 0, 1, 1);

        cBox_Regulate_3 = new QComboBox(gBox_Dev);
        cBox_Regulate_3->setObjectName(QString::fromUtf8("cBox_Regulate_3"));

        gridLayout_2->addWidget(cBox_Regulate_3, 3, 1, 1, 1);

        label_11 = new QLabel(gBox_Dev);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 4, 0, 1, 1);

        cBox_Regulate_4 = new QComboBox(gBox_Dev);
        cBox_Regulate_4->setObjectName(QString::fromUtf8("cBox_Regulate_4"));

        gridLayout_2->addWidget(cBox_Regulate_4, 4, 1, 1, 1);


        gridLayout_4->addWidget(gBox_Dev, 0, 2, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_12 = new QLabel(SetPortFrm);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 0, 0, 1, 1);

        cBox_Version = new QComboBox(SetPortFrm);
        cBox_Version->setObjectName(QString::fromUtf8("cBox_Version"));

        gridLayout_3->addWidget(cBox_Version, 0, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 1, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btn_Save = new QPushButton(SetPortFrm);
        btn_Save->setObjectName(QString::fromUtf8("btn_Save"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_Save->sizePolicy().hasHeightForWidth());
        btn_Save->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(btn_Save);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_Exit = new QPushButton(SetPortFrm);
        btn_Exit->setObjectName(QString::fromUtf8("btn_Exit"));
        sizePolicy.setHeightForWidth(btn_Exit->sizePolicy().hasHeightForWidth());
        btn_Exit->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(btn_Exit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout_4->addLayout(horizontalLayout, 2, 0, 1, 3);


        retranslateUi(SetPortFrm);

        QMetaObject::connectSlotsByName(SetPortFrm);
    } // setupUi

    void retranslateUi(QWidget *SetPortFrm)
    {
        SetPortFrm->setWindowTitle(QApplication::translate("SetPortFrm", "SetPortFrm", 0, QApplication::UnicodeUTF8));
        gBox_Valve->setTitle(QApplication::translate("SetPortFrm", "Valve", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SetPortFrm", "Valve In", 0, QApplication::UnicodeUTF8));
        cBox_Inlet->clear();
        cBox_Inlet->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "port1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port20", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("SetPortFrm", "Valve Out", 0, QApplication::UnicodeUTF8));
        cBox_Outlet->clear();
        cBox_Outlet->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "port1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port20", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("SetPortFrm", "Valve Big", 0, QApplication::UnicodeUTF8));
        cBox_Rate_1->clear();
        cBox_Rate_1->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "port1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port20", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("SetPortFrm", "Valve Mid2", 0, QApplication::UnicodeUTF8));
        cBox_Rate_2->clear();
        cBox_Rate_2->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "port1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port20", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("SetPortFrm", "Valve Mid1", 0, QApplication::UnicodeUTF8));
        cBox_Rate_3->clear();
        cBox_Rate_3->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "port1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port20", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("SetPortFrm", "Valve Small", 0, QApplication::UnicodeUTF8));
        cBox_Rate_4->clear();
        cBox_Rate_4->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "port1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port20", 0, QApplication::UnicodeUTF8)
        );
        gBox_Dev->setTitle(QApplication::translate("SetPortFrm", "Device", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SetPortFrm", "Pump", 0, QApplication::UnicodeUTF8));
        cBox_Pump->clear();
        cBox_Pump->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "port1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port20", 0, QApplication::UnicodeUTF8)
        );
        label_8->setText(QApplication::translate("SetPortFrm", "Regulator1", 0, QApplication::UnicodeUTF8));
        cBox_Regulate_1->clear();
        cBox_Regulate_1->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "port1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port20", 0, QApplication::UnicodeUTF8)
        );
        label_9->setText(QApplication::translate("SetPortFrm", "Regulator2", 0, QApplication::UnicodeUTF8));
        cBox_Regulate_2->clear();
        cBox_Regulate_2->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "port1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port20", 0, QApplication::UnicodeUTF8)
        );
        label_10->setText(QApplication::translate("SetPortFrm", "Regulator3", 0, QApplication::UnicodeUTF8));
        cBox_Regulate_3->clear();
        cBox_Regulate_3->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "port1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port20", 0, QApplication::UnicodeUTF8)
        );
        label_11->setText(QApplication::translate("SetPortFrm", "Regulator4", 0, QApplication::UnicodeUTF8));
        cBox_Regulate_4->clear();
        cBox_Regulate_4->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "port1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "port20", 0, QApplication::UnicodeUTF8)
        );
        label_12->setText(QApplication::translate("SetPortFrm", "ProtVersion:", 0, QApplication::UnicodeUTF8));
        cBox_Version->clear();
        cBox_Version->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "NewCtrlBoard", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "OldCtrlBoard", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "LichCtrlBoard", 0, QApplication::UnicodeUTF8)
        );
        btn_Save->setText(QApplication::translate("SetPortFrm", "Save", 0, QApplication::UnicodeUTF8));
        btn_Exit->setText(QApplication::translate("SetPortFrm", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetPortFrm: public Ui_SetPortFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPORTFRM_H
