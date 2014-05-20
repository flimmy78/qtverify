/********************************************************************************
** Form generated from reading UI file 'dbshow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBSHOW_H
#define UI_DBSHOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DBShowClass
{
public:
    QGridLayout *gridLayout;
    QTextEdit *display;
    QVBoxLayout *verticalLayout;
    QPushButton *conMySqlBtn;
    QSpacerItem *verticalSpacer;
    QPushButton *QueryBtn;

    void setupUi(QWidget *DBShowClass)
    {
        if (DBShowClass->objectName().isEmpty())
            DBShowClass->setObjectName(QString::fromUtf8("DBShowClass"));
        DBShowClass->resize(468, 331);
        gridLayout = new QGridLayout(DBShowClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        display = new QTextEdit(DBShowClass);
        display->setObjectName(QString::fromUtf8("display"));

        gridLayout->addWidget(display, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        conMySqlBtn = new QPushButton(DBShowClass);
        conMySqlBtn->setObjectName(QString::fromUtf8("conMySqlBtn"));

        verticalLayout->addWidget(conMySqlBtn);

        verticalSpacer = new QSpacerItem(20, 218, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        QueryBtn = new QPushButton(DBShowClass);
        QueryBtn->setObjectName(QString::fromUtf8("QueryBtn"));

        verticalLayout->addWidget(QueryBtn);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);


        retranslateUi(DBShowClass);

        QMetaObject::connectSlotsByName(DBShowClass);
    } // setupUi

    void retranslateUi(QWidget *DBShowClass)
    {
        DBShowClass->setWindowTitle(QApplication::translate("DBShowClass", "DBShow", 0, QApplication::UnicodeUTF8));
        conMySqlBtn->setText(QApplication::translate("DBShowClass", "Connect", 0, QApplication::UnicodeUTF8));
        QueryBtn->setText(QApplication::translate("DBShowClass", "Query", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DBShowClass: public Ui_DBShowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBSHOW_H
