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
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WeightMethodClass
{
public:
    QTabWidget *tabWidget;
    QWidget *tab1;
    QPushButton *pushButton_3;
    QWidget *tab2;
    QWidget *tab3;
    QWidget *tab4;
    QWidget *tab5;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QPushButton *pushButton;
    QPushButton *btnExit;

    void setupUi(QWidget *WeightMethodClass)
    {
        if (WeightMethodClass->objectName().isEmpty())
            WeightMethodClass->setObjectName(QString::fromUtf8("WeightMethodClass"));
        WeightMethodClass->resize(1178, 825);
        tabWidget = new QTabWidget(WeightMethodClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 1161, 691));
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        pushButton_3 = new QPushButton(tab1);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(920, 610, 93, 28));
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
        groupBox = new QGroupBox(WeightMethodClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 730, 311, 80));
        groupBox_2 = new QGroupBox(WeightMethodClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(350, 730, 461, 80));
        pushButton = new QPushButton(WeightMethodClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(930, 750, 93, 28));
        btnExit = new QPushButton(WeightMethodClass);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        btnExit->setGeometry(QRect(1050, 750, 93, 28));

        retranslateUi(WeightMethodClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WeightMethodClass);
    } // setupUi

    void retranslateUi(QWidget *WeightMethodClass)
    {
        WeightMethodClass->setWindowTitle(QApplication::translate("WeightMethodClass", "\350\264\250\351\207\217\346\263\225\346\243\200\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("WeightMethodClass", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("WeightMethodClass", "Tab1", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("WeightMethodClass", "Tab2", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab3), QApplication::translate("WeightMethodClass", "Tab3", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab4), QApplication::translate("WeightMethodClass", "Tab4", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab5), QApplication::translate("WeightMethodClass", "Tab5", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("WeightMethodClass", "\345\275\223\345\211\215\345\217\202\346\225\260(\345\205\263\351\224\256\344\277\241\346\201\257)", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("WeightMethodClass", "\351\230\200\351\227\250\343\200\201\346\260\264\346\263\265\343\200\201\345\217\230\351\242\221\345\231\250\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QString());
        btnExit->setText(QApplication::translate("WeightMethodClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WeightMethodClass: public Ui_WeightMethodClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEIGHTMETHOD_H
