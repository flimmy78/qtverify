/********************************************************************************
** Form generated from reading UI file 'parasetdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARASETDLG_H
#define UI_PARASETDLG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParaSetDlgClass
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    Q3ButtonGroup *buttonGroup_2;
    Q3ButtonGroup *buttonGroup;
    Q3ButtonGroup *buttonGroup_3;
    Q3ButtonGroup *buttonGroup_4;
    Q3ButtonGroup *buttonGroup_5;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *ParaSetDlgClass)
    {
        if (ParaSetDlgClass->objectName().isEmpty())
            ParaSetDlgClass->setObjectName(QString::fromUtf8("ParaSetDlgClass"));
        ParaSetDlgClass->resize(672, 537);
        gridLayout_3 = new QGridLayout(ParaSetDlgClass);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(ParaSetDlgClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));

        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(ParaSetDlgClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));

        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(ParaSetDlgClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));

        gridLayout_3->addWidget(groupBox_3, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        buttonGroup_2 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));

        horizontalLayout->addWidget(buttonGroup_2);

        buttonGroup = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));

        horizontalLayout->addWidget(buttonGroup);

        buttonGroup_3 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_3->setObjectName(QString::fromUtf8("buttonGroup_3"));

        horizontalLayout->addWidget(buttonGroup_3);

        buttonGroup_4 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_4->setObjectName(QString::fromUtf8("buttonGroup_4"));

        horizontalLayout->addWidget(buttonGroup_4);

        buttonGroup_5 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_5->setObjectName(QString::fromUtf8("buttonGroup_5"));

        horizontalLayout->addWidget(buttonGroup_5);


        gridLayout_3->addLayout(horizontalLayout, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox_4 = new QGroupBox(ParaSetDlgClass);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox_4);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 3, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox_4);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout_2->addWidget(lineEdit_2, 0, 4, 1, 1);


        horizontalLayout_2->addWidget(groupBox_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(ParaSetDlgClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(ParaSetDlgClass);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);


        gridLayout_3->addLayout(horizontalLayout_2, 4, 0, 1, 1);


        retranslateUi(ParaSetDlgClass);

        QMetaObject::connectSlotsByName(ParaSetDlgClass);
    } // setupUi

    void retranslateUi(QWidget *ParaSetDlgClass)
    {
        ParaSetDlgClass->setWindowTitle(QApplication::translate("ParaSetDlgClass", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ParaSetDlgClass", "\346\243\200\345\256\232\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ParaSetDlgClass", "\346\216\247\345\210\266\351\230\200\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("ParaSetDlgClass", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        buttonGroup_2->setTitle(QApplication::translate("ParaSetDlgClass", "\350\207\252\345\212\250\351\207\207\351\233\206", 0, QApplication::UnicodeUTF8));
        buttonGroup->setTitle(QApplication::translate("ParaSetDlgClass", "\346\200\273\351\207\217\346\243\200\345\256\232", 0, QApplication::UnicodeUTF8));
        buttonGroup_3->setTitle(QApplication::translate("ParaSetDlgClass", "\350\241\250\346\263\242\347\211\271\347\216\207", 0, QApplication::UnicodeUTF8));
        buttonGroup_4->setTitle(QApplication::translate("ParaSetDlgClass", "\350\257\273\350\204\211\345\206\262\346\225\260", 0, QApplication::UnicodeUTF8));
        buttonGroup_5->setTitle(QApplication::translate("ParaSetDlgClass", "\350\260\203\346\225\264\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("ParaSetDlgClass", "\345\256\211\345\205\250\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ParaSetDlgClass", "\346\265\201\351\207\217", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ParaSetDlgClass", "\346\200\273\351\207\217", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ParaSetDlgClass", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("ParaSetDlgClass", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ParaSetDlgClass: public Ui_ParaSetDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARASETDLG_H
