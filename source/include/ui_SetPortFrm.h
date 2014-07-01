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
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetPortFrm
{
public:
    QGroupBox *gBox_Valve;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *cBox_Inlet;
    QComboBox *cBox_Outlet;
    QComboBox *cBox_Rate_1;
    QComboBox *cBox_Rate_2;
    QComboBox *cBox_Rate_3;
    QComboBox *cBox_Rate_4;
    QPushButton *btn_Save;
    QGroupBox *gBox_Dev;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QComboBox *cBox_Pump;
    QComboBox *cBox_Regulate_1;
    QComboBox *cBox_Regulate_2;
    QComboBox *cBox_Regulate_3;
    QComboBox *cBox_Regulate_4;
    QLabel *label_10;
    QLabel *label_11;
    QPushButton *btn_Exit;

    void setupUi(QWidget *SetPortFrm)
    {
        if (SetPortFrm->objectName().isEmpty())
            SetPortFrm->setObjectName(QString::fromUtf8("SetPortFrm"));
        SetPortFrm->resize(399, 260);
        gBox_Valve = new QGroupBox(SetPortFrm);
        gBox_Valve->setObjectName(QString::fromUtf8("gBox_Valve"));
        gBox_Valve->setGeometry(QRect(10, 10, 171, 211));
        label = new QLabel(gBox_Valve);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 54, 12));
        label_2 = new QLabel(gBox_Valve);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 54, 12));
        label_3 = new QLabel(gBox_Valve);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 90, 54, 12));
        label_4 = new QLabel(gBox_Valve);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 120, 61, 16));
        label_5 = new QLabel(gBox_Valve);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 150, 61, 16));
        label_6 = new QLabel(gBox_Valve);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 180, 54, 12));
        cBox_Inlet = new QComboBox(gBox_Valve);
        cBox_Inlet->setObjectName(QString::fromUtf8("cBox_Inlet"));
        cBox_Inlet->setGeometry(QRect(90, 20, 69, 22));
        cBox_Outlet = new QComboBox(gBox_Valve);
        cBox_Outlet->setObjectName(QString::fromUtf8("cBox_Outlet"));
        cBox_Outlet->setGeometry(QRect(90, 50, 69, 22));
        cBox_Rate_1 = new QComboBox(gBox_Valve);
        cBox_Rate_1->setObjectName(QString::fromUtf8("cBox_Rate_1"));
        cBox_Rate_1->setGeometry(QRect(90, 80, 69, 22));
        cBox_Rate_2 = new QComboBox(gBox_Valve);
        cBox_Rate_2->setObjectName(QString::fromUtf8("cBox_Rate_2"));
        cBox_Rate_2->setGeometry(QRect(90, 110, 69, 22));
        cBox_Rate_3 = new QComboBox(gBox_Valve);
        cBox_Rate_3->setObjectName(QString::fromUtf8("cBox_Rate_3"));
        cBox_Rate_3->setGeometry(QRect(90, 140, 69, 22));
        cBox_Rate_4 = new QComboBox(gBox_Valve);
        cBox_Rate_4->setObjectName(QString::fromUtf8("cBox_Rate_4"));
        cBox_Rate_4->setGeometry(QRect(90, 170, 69, 22));
        btn_Save = new QPushButton(SetPortFrm);
        btn_Save->setObjectName(QString::fromUtf8("btn_Save"));
        btn_Save->setGeometry(QRect(50, 220, 75, 23));
        gBox_Dev = new QGroupBox(SetPortFrm);
        gBox_Dev->setObjectName(QString::fromUtf8("gBox_Dev"));
        gBox_Dev->setGeometry(QRect(210, 10, 171, 181));
        label_7 = new QLabel(gBox_Dev);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 30, 54, 12));
        label_8 = new QLabel(gBox_Dev);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 60, 54, 12));
        label_9 = new QLabel(gBox_Dev);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 90, 54, 12));
        cBox_Pump = new QComboBox(gBox_Dev);
        cBox_Pump->setObjectName(QString::fromUtf8("cBox_Pump"));
        cBox_Pump->setGeometry(QRect(90, 20, 69, 22));
        cBox_Regulate_1 = new QComboBox(gBox_Dev);
        cBox_Regulate_1->setObjectName(QString::fromUtf8("cBox_Regulate_1"));
        cBox_Regulate_1->setGeometry(QRect(90, 50, 69, 22));
        cBox_Regulate_2 = new QComboBox(gBox_Dev);
        cBox_Regulate_2->setObjectName(QString::fromUtf8("cBox_Regulate_2"));
        cBox_Regulate_2->setGeometry(QRect(90, 80, 69, 22));
        cBox_Regulate_3 = new QComboBox(gBox_Dev);
        cBox_Regulate_3->setObjectName(QString::fromUtf8("cBox_Regulate_3"));
        cBox_Regulate_3->setGeometry(QRect(90, 110, 69, 22));
        cBox_Regulate_4 = new QComboBox(gBox_Dev);
        cBox_Regulate_4->setObjectName(QString::fromUtf8("cBox_Regulate_4"));
        cBox_Regulate_4->setGeometry(QRect(90, 140, 69, 22));
        label_10 = new QLabel(gBox_Dev);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 120, 54, 12));
        label_11 = new QLabel(gBox_Dev);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 150, 54, 12));
        btn_Exit = new QPushButton(SetPortFrm);
        btn_Exit->setObjectName(QString::fromUtf8("btn_Exit"));
        btn_Exit->setGeometry(QRect(310, 220, 75, 23));

        retranslateUi(SetPortFrm);

        QMetaObject::connectSlotsByName(SetPortFrm);
    } // setupUi

    void retranslateUi(QWidget *SetPortFrm)
    {
        SetPortFrm->setWindowTitle(QApplication::translate("SetPortFrm", "SetPortFrm", 0, QApplication::UnicodeUTF8));
        gBox_Valve->setTitle(QApplication::translate("SetPortFrm", "\351\230\200\351\227\250", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SetPortFrm", "\350\277\233\346\260\264\346\200\273\351\230\200", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SetPortFrm", "\346\224\276\346\260\264\346\200\273\351\230\200", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SetPortFrm", "\345\244\247\346\265\201\351\207\217\351\230\200", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SetPortFrm", "\344\270\255\344\272\214\346\265\201\351\207\217\351\230\200", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SetPortFrm", "\344\270\255\344\270\200\346\265\201\351\207\217\351\230\200", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SetPortFrm", "\345\260\217\346\265\201\351\207\217\351\230\200", 0, QApplication::UnicodeUTF8));
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
        btn_Save->setText(QApplication::translate("SetPortFrm", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        gBox_Dev->setTitle(QApplication::translate("SetPortFrm", "\350\256\276\345\244\207", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SetPortFrm", "\346\260\264\346\263\265", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("SetPortFrm", "\350\260\203\350\212\202\351\230\2001", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("SetPortFrm", "\350\260\203\350\212\202\351\230\2002", 0, QApplication::UnicodeUTF8));
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
        label_10->setText(QApplication::translate("SetPortFrm", "\350\260\203\350\212\202\351\230\2003", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("SetPortFrm", "\350\260\203\350\212\202\351\230\2004", 0, QApplication::UnicodeUTF8));
        btn_Exit->setText(QApplication::translate("SetPortFrm", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetPortFrm: public Ui_SetPortFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPORTFRM_H
