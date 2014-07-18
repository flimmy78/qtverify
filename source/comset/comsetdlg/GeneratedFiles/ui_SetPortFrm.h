/********************************************************************************
** Form generated from reading UI file 'SetPortFrm.ui'
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
    QGridLayout *gridLayout_3;
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
    QSpacerItem *verticalSpacer;
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
        SetPortFrm->resize(399, 260);
        gridLayout_3 = new QGridLayout(SetPortFrm);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
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


        gridLayout_3->addWidget(gBox_Valve, 0, 0, 2, 1);

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


        gridLayout_3->addWidget(gBox_Dev, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 19, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btn_Save = new QPushButton(SetPortFrm);
        btn_Save->setObjectName(QString::fromUtf8("btn_Save"));

        horizontalLayout->addWidget(btn_Save);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_Exit = new QPushButton(SetPortFrm);
        btn_Exit->setObjectName(QString::fromUtf8("btn_Exit"));

        horizontalLayout->addWidget(btn_Exit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 2);


        retranslateUi(SetPortFrm);

        QMetaObject::connectSlotsByName(SetPortFrm);
    } // setupUi

    void retranslateUi(QWidget *SetPortFrm)
    {
        SetPortFrm->setWindowTitle(QApplication::translate("SetPortFrm", "SetPortFrm", 0, QApplication::UnicodeUTF8));
        gBox_Valve->setTitle(QApplication::translate("SetPortFrm", "\351\230\200\351\227\250", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SetPortFrm", "\350\277\233\346\260\264\346\200\273\351\230\200", 0, QApplication::UnicodeUTF8));
        cBox_Inlet->clear();
        cBox_Inlet->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2431", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2432", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2433", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2434", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2435", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2436", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2437", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2438", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2439", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24310", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24311", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24312", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24313", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24314", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24315", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24316", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24317", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24318", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24319", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24320", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("SetPortFrm", "\346\224\276\346\260\264\346\200\273\351\230\200", 0, QApplication::UnicodeUTF8));
        cBox_Outlet->clear();
        cBox_Outlet->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2431", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2432", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2433", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2434", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2435", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2436", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2437", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2438", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2439", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24310", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24311", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24312", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24313", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24314", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24315", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24316", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24317", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24318", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24319", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24320", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("SetPortFrm", "\345\244\247\346\265\201\351\207\217\351\230\200", 0, QApplication::UnicodeUTF8));
        cBox_Rate_1->clear();
        cBox_Rate_1->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2431", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2432", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2433", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2434", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2435", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2436", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2437", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2438", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2439", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24310", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24311", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24312", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24313", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24314", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24315", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24316", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24317", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24318", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24319", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24320", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("SetPortFrm", "\344\270\255\344\272\214\346\265\201\351\207\217\351\230\200", 0, QApplication::UnicodeUTF8));
        cBox_Rate_2->clear();
        cBox_Rate_2->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2431", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2432", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2433", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2434", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2435", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2436", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2437", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2438", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2439", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24310", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24311", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24312", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24313", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24314", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24315", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24316", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24317", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24318", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24319", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24320", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("SetPortFrm", "\344\270\255\344\270\200\346\265\201\351\207\217\351\230\200", 0, QApplication::UnicodeUTF8));
        cBox_Rate_3->clear();
        cBox_Rate_3->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2431", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2432", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2433", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2434", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2435", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2436", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2437", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2438", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2439", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24310", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24311", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24312", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24313", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24314", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24315", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24316", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24317", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24318", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24319", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24320", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("SetPortFrm", "\345\260\217\346\265\201\351\207\217\351\230\200", 0, QApplication::UnicodeUTF8));
        cBox_Rate_4->clear();
        cBox_Rate_4->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2431", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2432", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2433", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2434", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2435", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2436", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2437", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2438", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2439", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24310", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24311", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24312", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24313", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24314", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24315", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24316", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24317", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24318", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24319", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24320", 0, QApplication::UnicodeUTF8)
        );
        gBox_Dev->setTitle(QApplication::translate("SetPortFrm", "\350\256\276\345\244\207", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SetPortFrm", "\346\260\264\346\263\265", 0, QApplication::UnicodeUTF8));
        cBox_Pump->clear();
        cBox_Pump->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2431", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2432", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2433", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2434", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2435", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2436", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2437", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2438", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2439", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24310", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24311", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24312", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24313", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24314", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24315", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24316", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24317", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24318", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24319", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24320", 0, QApplication::UnicodeUTF8)
        );
        label_8->setText(QApplication::translate("SetPortFrm", "\350\260\203\350\212\202\351\230\2001", 0, QApplication::UnicodeUTF8));
        cBox_Regulate_1->clear();
        cBox_Regulate_1->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2431", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2432", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2433", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2434", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2435", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2436", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2437", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2438", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2439", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24310", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24311", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24312", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24313", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24314", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24315", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24316", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24317", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24318", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24319", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24320", 0, QApplication::UnicodeUTF8)
        );
        label_9->setText(QApplication::translate("SetPortFrm", "\350\260\203\350\212\202\351\230\2002", 0, QApplication::UnicodeUTF8));
        cBox_Regulate_2->clear();
        cBox_Regulate_2->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2431", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2432", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2433", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2434", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2435", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2436", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2437", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2438", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2439", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24310", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24311", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24312", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24313", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24314", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24315", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24316", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24317", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24318", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24319", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24320", 0, QApplication::UnicodeUTF8)
        );
        label_10->setText(QApplication::translate("SetPortFrm", "\350\260\203\350\212\202\351\230\2003", 0, QApplication::UnicodeUTF8));
        cBox_Regulate_3->clear();
        cBox_Regulate_3->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2431", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2432", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2433", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2434", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2435", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2436", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2437", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2438", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2439", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24310", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24311", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24312", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24313", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24314", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24315", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24316", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24317", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24318", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24319", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24320", 0, QApplication::UnicodeUTF8)
        );
        label_11->setText(QApplication::translate("SetPortFrm", "\350\260\203\350\212\202\351\230\2004", 0, QApplication::UnicodeUTF8));
        cBox_Regulate_4->clear();
        cBox_Regulate_4->insertItems(0, QStringList()
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2431", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2432", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2433", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2434", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2435", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2436", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2437", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2438", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\2439", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24310", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24311", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24312", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24313", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24314", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24315", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24316", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24317", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24318", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24319", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetPortFrm", "\347\253\257\345\217\24320", 0, QApplication::UnicodeUTF8)
        );
        btn_Save->setText(QApplication::translate("SetPortFrm", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        btn_Exit->setText(QApplication::translate("SetPortFrm", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetPortFrm: public Ui_SetPortFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPORTFRM_H
