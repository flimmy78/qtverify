/********************************************************************************
** Form generated from reading UI file 'serialportset.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALPORTSET_H
#define UI_SERIALPORTSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialPortSetClass
{
public:
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;
    QPushButton *openMyComBtn;
    QLabel *label;
    QLineEdit *sendMsgLineEdit;
    QPushButton *sendMsgBtn;
    QLabel *label_2;
    QPushButton *closeMyComBtn;

    void setupUi(QWidget *SerialPortSetClass)
    {
        if (SerialPortSetClass->objectName().isEmpty())
            SerialPortSetClass->setObjectName(QString::fromUtf8("SerialPortSetClass"));
        SerialPortSetClass->resize(477, 338);
        gridLayout = new QGridLayout(SerialPortSetClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowser = new QTextBrowser(SerialPortSetClass);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout->addWidget(textBrowser, 1, 0, 1, 1);

        openMyComBtn = new QPushButton(SerialPortSetClass);
        openMyComBtn->setObjectName(QString::fromUtf8("openMyComBtn"));

        gridLayout->addWidget(openMyComBtn, 1, 1, 1, 1);

        label = new QLabel(SerialPortSetClass);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        sendMsgLineEdit = new QLineEdit(SerialPortSetClass);
        sendMsgLineEdit->setObjectName(QString::fromUtf8("sendMsgLineEdit"));

        gridLayout->addWidget(sendMsgLineEdit, 6, 0, 1, 1);

        sendMsgBtn = new QPushButton(SerialPortSetClass);
        sendMsgBtn->setObjectName(QString::fromUtf8("sendMsgBtn"));

        gridLayout->addWidget(sendMsgBtn, 6, 1, 1, 1);

        label_2 = new QLabel(SerialPortSetClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        closeMyComBtn = new QPushButton(SerialPortSetClass);
        closeMyComBtn->setObjectName(QString::fromUtf8("closeMyComBtn"));

        gridLayout->addWidget(closeMyComBtn, 2, 1, 1, 1);


        retranslateUi(SerialPortSetClass);

        QMetaObject::connectSlotsByName(SerialPortSetClass);
    } // setupUi

    void retranslateUi(QWidget *SerialPortSetClass)
    {
        SerialPortSetClass->setWindowTitle(QApplication::translate("SerialPortSetClass", "SerialPortSet", 0, QApplication::UnicodeUTF8));
        openMyComBtn->setText(QApplication::translate("SerialPortSetClass", "\346\211\223\345\274\200\344\270\262\345\217\243", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SerialPortSetClass", "<html><head/><body><p>\344\270\262\345\217\243\346\216\245\346\224\266\345\210\260\347\232\204\346\225\260\346\215\256\357\274\232</p></body></html>", 0, QApplication::UnicodeUTF8));
        sendMsgBtn->setText(QApplication::translate("SerialPortSetClass", "\345\217\221\351\200\201\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SerialPortSetClass", "\350\246\201\345\217\221\351\200\201\345\210\260\344\270\262\345\217\243\347\232\204\346\225\260\346\215\256\357\274\232", 0, QApplication::UnicodeUTF8));
        closeMyComBtn->setText(QApplication::translate("SerialPortSetClass", "\345\205\263\351\227\255\344\270\262\345\217\243", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SerialPortSetClass: public Ui_SerialPortSetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALPORTSET_H
