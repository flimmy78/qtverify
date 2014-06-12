/********************************************************************************
** Form generated from reading UI file 'comsetdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMSETDLG_H
#define UI_COMSETDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComSetDlgClass
{
public:
    QGridLayout *gridLayout_5;
    QLabel *label;
    QGridLayout *gridLayout_4;
    QTextBrowser *textBrowserRecMsg;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QComboBox *portNameComboBox;
    QLabel *label_4;
    QComboBox *baudRateComboBox;
    QLabel *label_5;
    QComboBox *dataBitsComboBox;
    QLabel *label_6;
    QComboBox *parityComboBox;
    QLabel *label_7;
    QComboBox *stopBitsComboBox;
    QGridLayout *gridLayout_3;
    QPushButton *btnOpenCom;
    QPushButton *btnCloseCom;
    QPushButton *btnClearMsg;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QGridLayout *gridLayout;
    QLineEdit *lineEditSendMsg;
    QPushButton *btnSendMsg;

    void setupUi(QWidget *ComSetDlgClass)
    {
        if (ComSetDlgClass->objectName().isEmpty())
            ComSetDlgClass->setObjectName(QString::fromUtf8("ComSetDlgClass"));
        ComSetDlgClass->setWindowModality(Qt::ApplicationModal);
        ComSetDlgClass->resize(450, 355);
        gridLayout_5 = new QGridLayout(ComSetDlgClass);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label = new QLabel(ComSetDlgClass);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        textBrowserRecMsg = new QTextBrowser(ComSetDlgClass);
        textBrowserRecMsg->setObjectName(QString::fromUtf8("textBrowserRecMsg"));

        gridLayout_4->addWidget(textBrowserRecMsg, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(ComSetDlgClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        portNameComboBox = new QComboBox(ComSetDlgClass);
        portNameComboBox->setObjectName(QString::fromUtf8("portNameComboBox"));

        gridLayout_2->addWidget(portNameComboBox, 0, 1, 1, 1);

        label_4 = new QLabel(ComSetDlgClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        baudRateComboBox = new QComboBox(ComSetDlgClass);
        baudRateComboBox->setObjectName(QString::fromUtf8("baudRateComboBox"));

        gridLayout_2->addWidget(baudRateComboBox, 1, 1, 1, 1);

        label_5 = new QLabel(ComSetDlgClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        dataBitsComboBox = new QComboBox(ComSetDlgClass);
        dataBitsComboBox->setObjectName(QString::fromUtf8("dataBitsComboBox"));

        gridLayout_2->addWidget(dataBitsComboBox, 2, 1, 1, 1);

        label_6 = new QLabel(ComSetDlgClass);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        parityComboBox = new QComboBox(ComSetDlgClass);
        parityComboBox->setObjectName(QString::fromUtf8("parityComboBox"));

        gridLayout_2->addWidget(parityComboBox, 3, 1, 1, 1);

        label_7 = new QLabel(ComSetDlgClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 4, 0, 1, 1);

        stopBitsComboBox = new QComboBox(ComSetDlgClass);
        stopBitsComboBox->setObjectName(QString::fromUtf8("stopBitsComboBox"));

        gridLayout_2->addWidget(stopBitsComboBox, 4, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 1, 0, 1, 2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        btnOpenCom = new QPushButton(ComSetDlgClass);
        btnOpenCom->setObjectName(QString::fromUtf8("btnOpenCom"));
        sizePolicy.setHeightForWidth(btnOpenCom->sizePolicy().hasHeightForWidth());
        btnOpenCom->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(btnOpenCom, 0, 0, 1, 1);

        btnCloseCom = new QPushButton(ComSetDlgClass);
        btnCloseCom->setObjectName(QString::fromUtf8("btnCloseCom"));
        sizePolicy.setHeightForWidth(btnCloseCom->sizePolicy().hasHeightForWidth());
        btnCloseCom->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(btnCloseCom, 0, 1, 1, 1);

        btnClearMsg = new QPushButton(ComSetDlgClass);
        btnClearMsg->setObjectName(QString::fromUtf8("btnClearMsg"));
        sizePolicy.setHeightForWidth(btnClearMsg->sizePolicy().hasHeightForWidth());
        btnClearMsg->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(btnClearMsg, 0, 2, 1, 1);


        gridLayout_5->addLayout(gridLayout_3, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(184, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 2, 1, 1, 1);

        label_2 = new QLabel(ComSetDlgClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_2, 3, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditSendMsg = new QLineEdit(ComSetDlgClass);
        lineEditSendMsg->setObjectName(QString::fromUtf8("lineEditSendMsg"));

        gridLayout->addWidget(lineEditSendMsg, 0, 0, 1, 1);

        btnSendMsg = new QPushButton(ComSetDlgClass);
        btnSendMsg->setObjectName(QString::fromUtf8("btnSendMsg"));
        sizePolicy.setHeightForWidth(btnSendMsg->sizePolicy().hasHeightForWidth());
        btnSendMsg->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btnSendMsg, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout, 4, 0, 1, 2);


        retranslateUi(ComSetDlgClass);

        QMetaObject::connectSlotsByName(ComSetDlgClass);
    } // setupUi

    void retranslateUi(QWidget *ComSetDlgClass)
    {
        ComSetDlgClass->setWindowTitle(QApplication::translate("ComSetDlgClass", "ComSetDlg", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ComSetDlgClass", "<html><head/><body><p>\344\270\262\345\217\243\346\216\245\346\224\266\345\210\260\347\232\204\346\225\260\346\215\256\357\274\232</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ComSetDlgClass", "\344\270\262\345\217\243", 0, QApplication::UnicodeUTF8));
        portNameComboBox->clear();
        portNameComboBox->insertItems(0, QStringList()
         << QApplication::translate("ComSetDlgClass", "COM1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "COM2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "COM3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "COM4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "COM5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "COM6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "COM7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "COM8", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("ComSetDlgClass", "\346\263\242\347\211\271\347\216\207", 0, QApplication::UnicodeUTF8));
        baudRateComboBox->clear();
        baudRateComboBox->insertItems(0, QStringList()
         << QApplication::translate("ComSetDlgClass", "2400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "4800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "14400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "38400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "56000", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("ComSetDlgClass", "\346\225\260\346\215\256\344\275\215", 0, QApplication::UnicodeUTF8));
        dataBitsComboBox->clear();
        dataBitsComboBox->insertItems(0, QStringList()
         << QApplication::translate("ComSetDlgClass", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "8", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("ComSetDlgClass", "\346\240\241\351\252\214\344\275\215", 0, QApplication::UnicodeUTF8));
        parityComboBox->clear();
        parityComboBox->insertItems(0, QStringList()
         << QApplication::translate("ComSetDlgClass", "\346\227\240", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "\345\245\207", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "\345\201\266", 0, QApplication::UnicodeUTF8)
        );
        label_7->setText(QApplication::translate("ComSetDlgClass", "\345\201\234\346\255\242\344\275\215", 0, QApplication::UnicodeUTF8));
        stopBitsComboBox->clear();
        stopBitsComboBox->insertItems(0, QStringList()
         << QApplication::translate("ComSetDlgClass", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ComSetDlgClass", "2", 0, QApplication::UnicodeUTF8)
        );
        btnOpenCom->setText(QApplication::translate("ComSetDlgClass", "\346\211\223\345\274\200\344\270\262\345\217\243", 0, QApplication::UnicodeUTF8));
        btnCloseCom->setText(QApplication::translate("ComSetDlgClass", "\345\205\263\351\227\255\344\270\262\345\217\243", 0, QApplication::UnicodeUTF8));
        btnClearMsg->setText(QApplication::translate("ComSetDlgClass", "\346\270\205\351\231\244\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ComSetDlgClass", "\350\246\201\345\217\221\351\200\201\345\210\260\344\270\262\345\217\243\347\232\204\346\225\260\346\215\256\357\274\232", 0, QApplication::UnicodeUTF8));
        btnSendMsg->setText(QApplication::translate("ComSetDlgClass", "\345\217\221\351\200\201\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ComSetDlgClass: public Ui_ComSetDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMSETDLG_H
