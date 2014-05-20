/********************************************************************************
** Form generated from reading UI file 'qtverify.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTVERIFY_H
#define UI_QTVERIFY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtVerifyClass
{
public:
    QAction *action_spset;
    QAction *action_2;
    QAction *action_dataquery;
    QAction *action_database;
    QAction *action_sql;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QGroupBox *groupBox_4;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout;
    QPushButton *pushButton_Para;
    QPushButton *pushButton_2;
    QPushButton *pushButton_Start;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Exit;
    QMenuBar *menuBar;
    QMenu *menuSystemSet;
    QMenu *menu;
    QMenu *menuDataQuery;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qtVerifyClass)
    {
        if (qtVerifyClass->objectName().isEmpty())
            qtVerifyClass->setObjectName(QString::fromUtf8("qtVerifyClass"));
        qtVerifyClass->resize(868, 584);
        action_spset = new QAction(qtVerifyClass);
        action_spset->setObjectName(QString::fromUtf8("action_spset"));
        action_2 = new QAction(qtVerifyClass);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_dataquery = new QAction(qtVerifyClass);
        action_dataquery->setObjectName(QString::fromUtf8("action_dataquery"));
        action_database = new QAction(qtVerifyClass);
        action_database->setObjectName(QString::fromUtf8("action_database"));
        action_sql = new QAction(qtVerifyClass);
        action_sql->setObjectName(QString::fromUtf8("action_sql"));
        centralWidget = new QWidget(qtVerifyClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));

        gridLayout_2->addWidget(groupBox, 0, 0, 1, 2);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(groupBox_2, 1, 0, 3, 1);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(groupBox_3, 1, 1, 1, 1);

        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy1.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(groupBox_4, 2, 1, 1, 1);

        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy2);
        gridLayout = new QGridLayout(groupBox_5);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_Para = new QPushButton(groupBox_5);
        pushButton_Para->setObjectName(QString::fromUtf8("pushButton_Para"));

        gridLayout->addWidget(pushButton_Para, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox_5);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_Start = new QPushButton(groupBox_5);
        pushButton_Start->setObjectName(QString::fromUtf8("pushButton_Start"));

        gridLayout->addWidget(pushButton_Start, 0, 2, 1, 1);

        pushButton_Save = new QPushButton(groupBox_5);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));

        gridLayout->addWidget(pushButton_Save, 0, 3, 1, 1);

        pushButton_Exit = new QPushButton(groupBox_5);
        pushButton_Exit->setObjectName(QString::fromUtf8("pushButton_Exit"));

        gridLayout->addWidget(pushButton_Exit, 0, 4, 1, 1);


        gridLayout_2->addWidget(groupBox_5, 3, 1, 1, 1);

        qtVerifyClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qtVerifyClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 868, 23));
        menuSystemSet = new QMenu(menuBar);
        menuSystemSet->setObjectName(QString::fromUtf8("menuSystemSet"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuDataQuery = new QMenu(menuBar);
        menuDataQuery->setObjectName(QString::fromUtf8("menuDataQuery"));
        qtVerifyClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qtVerifyClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qtVerifyClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qtVerifyClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qtVerifyClass->setStatusBar(statusBar);
        QWidget::setTabOrder(pushButton_Save, pushButton_Exit);

        menuBar->addAction(menuSystemSet->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuDataQuery->menuAction());
        menuSystemSet->addAction(action_spset);
        menuSystemSet->addAction(action_database);
        menuSystemSet->addAction(action_sql);
        menu->addAction(action_2);
        menuDataQuery->addAction(action_dataquery);

        retranslateUi(qtVerifyClass);
        QObject::connect(pushButton_Exit, SIGNAL(clicked()), qtVerifyClass, SLOT(close()));

        QMetaObject::connectSlotsByName(qtVerifyClass);
    } // setupUi

    void retranslateUi(QMainWindow *qtVerifyClass)
    {
        qtVerifyClass->setWindowTitle(QApplication::translate("qtVerifyClass", "qtVerify", 0, QApplication::UnicodeUTF8));
        action_spset->setText(QApplication::translate("qtVerifyClass", "spset", 0, QApplication::UnicodeUTF8));
        action_2->setText(QApplication::translate("qtVerifyClass", "\346\265\201\351\207\217\344\274\240\346\204\237\345\231\250-\350\264\250\351\207\217\346\263\225", 0, QApplication::UnicodeUTF8));
        action_dataquery->setText(QApplication::translate("qtVerifyClass", "\346\265\201\351\207\217\344\274\240\346\204\237\345\231\250-\350\264\250\351\207\217\346\263\225", 0, QApplication::UnicodeUTF8));
        action_database->setText(QApplication::translate("qtVerifyClass", "database", 0, QApplication::UnicodeUTF8));
        action_sql->setText(QApplication::translate("qtVerifyClass", "sql", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("qtVerifyClass", "\346\200\273\346\243\200\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("qtVerifyClass", "\347\203\255\351\207\217\350\241\250", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("qtVerifyClass", "\351\230\200\351\227\250\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("qtVerifyClass", "\346\225\260\346\215\256\351\207\207\351\233\206", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("qtVerifyClass", "\346\223\215\344\275\234\346\255\245\351\252\244", 0, QApplication::UnicodeUTF8));
        pushButton_Para->setText(QApplication::translate("qtVerifyClass", "Para", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("qtVerifyClass", " Air-Out", 0, QApplication::UnicodeUTF8));
        pushButton_Start->setText(QApplication::translate("qtVerifyClass", "Start", 0, QApplication::UnicodeUTF8));
        pushButton_Save->setText(QApplication::translate("qtVerifyClass", "Save", 0, QApplication::UnicodeUTF8));
        pushButton_Exit->setText(QApplication::translate("qtVerifyClass", "Exit", 0, QApplication::UnicodeUTF8));
        menuSystemSet->setTitle(QApplication::translate("qtVerifyClass", "SystemSet", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("qtVerifyClass", "VerifyItem", 0, QApplication::UnicodeUTF8));
        menuDataQuery->setTitle(QApplication::translate("qtVerifyClass", "DataQuery", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qtVerifyClass: public Ui_qtVerifyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTVERIFY_H
