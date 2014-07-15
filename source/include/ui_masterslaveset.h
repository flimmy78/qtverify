/********************************************************************************
** Form generated from reading UI file 'masterslaveset.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASTERSLAVESET_H
#define UI_MASTERSLAVESET_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MasterSlaveClass
{
public:
    QPushButton *btnExit;
    QPushButton *btnSave;
    QCheckBox *checkBoxNetMode;
    Q3ButtonGroup *btnGrpHostFlag;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *hostFlag;
    QSpacerItem *horizontalSpacer_6;
    QRadioButton *slaveFlag;
    QGroupBox *grpBoxSlave;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lnEditIpSlave1;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_8;
    QLineEdit *lnEditHostnameSlave1;
    QLabel *label_2;
    QLineEdit *lnEditIpSlave2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_9;
    QLineEdit *lnEditHostnameSlave2;
    QLabel *label_3;
    QLineEdit *lnEditIpSlave3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_10;
    QLineEdit *lnEditHostnameSlave3;
    QLabel *label_4;
    QLineEdit *lnEditIpSlave4;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_7;
    QLineEdit *lnEditHostnameSlave4;
    QGroupBox *grpBoxMaster;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QLineEdit *lnEditIpMaster;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QLineEdit *lnEditHostnameMaster;

    void setupUi(QWidget *MasterSlaveClass)
    {
        if (MasterSlaveClass->objectName().isEmpty())
            MasterSlaveClass->setObjectName(QString::fromUtf8("MasterSlaveClass"));
        MasterSlaveClass->resize(532, 473);
        btnExit = new QPushButton(MasterSlaveClass);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        btnExit->setGeometry(QRect(340, 430, 93, 28));
        btnSave = new QPushButton(MasterSlaveClass);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(90, 430, 93, 28));
        checkBoxNetMode = new QCheckBox(MasterSlaveClass);
        checkBoxNetMode->setObjectName(QString::fromUtf8("checkBoxNetMode"));
        checkBoxNetMode->setGeometry(QRect(50, 50, 91, 19));
        btnGrpHostFlag = new Q3ButtonGroup(MasterSlaveClass);
        btnGrpHostFlag->setObjectName(QString::fromUtf8("btnGrpHostFlag"));
        btnGrpHostFlag->setGeometry(QRect(230, 40, 233, 47));
        btnGrpHostFlag->setColumnLayout(0, Qt::Vertical);
        horizontalLayout_2 = new QHBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(btnGrpHostFlag->layout());
        if (boxlayout)
            boxlayout->addLayout(horizontalLayout_2);
        horizontalLayout_2->setAlignment(Qt::AlignTop);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        hostFlag = new QRadioButton(btnGrpHostFlag);
        hostFlag->setObjectName(QString::fromUtf8("hostFlag"));

        horizontalLayout_2->addWidget(hostFlag);

        horizontalSpacer_6 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        slaveFlag = new QRadioButton(btnGrpHostFlag);
        slaveFlag->setObjectName(QString::fromUtf8("slaveFlag"));

        horizontalLayout_2->addWidget(slaveFlag);

        grpBoxSlave = new QGroupBox(MasterSlaveClass);
        grpBoxSlave->setObjectName(QString::fromUtf8("grpBoxSlave"));
        grpBoxSlave->setGeometry(QRect(20, 120, 501, 152));
        gridLayout = new QGridLayout(grpBoxSlave);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(grpBoxSlave);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lnEditIpSlave1 = new QLineEdit(grpBoxSlave);
        lnEditIpSlave1->setObjectName(QString::fromUtf8("lnEditIpSlave1"));

        gridLayout->addWidget(lnEditIpSlave1, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        label_8 = new QLabel(grpBoxSlave);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 3, 1, 1);

        lnEditHostnameSlave1 = new QLineEdit(grpBoxSlave);
        lnEditHostnameSlave1->setObjectName(QString::fromUtf8("lnEditHostnameSlave1"));

        gridLayout->addWidget(lnEditHostnameSlave1, 0, 4, 1, 1);

        label_2 = new QLabel(grpBoxSlave);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lnEditIpSlave2 = new QLineEdit(grpBoxSlave);
        lnEditIpSlave2->setObjectName(QString::fromUtf8("lnEditIpSlave2"));

        gridLayout->addWidget(lnEditIpSlave2, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        label_9 = new QLabel(grpBoxSlave);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 1, 3, 1, 1);

        lnEditHostnameSlave2 = new QLineEdit(grpBoxSlave);
        lnEditHostnameSlave2->setObjectName(QString::fromUtf8("lnEditHostnameSlave2"));

        gridLayout->addWidget(lnEditHostnameSlave2, 1, 4, 1, 1);

        label_3 = new QLabel(grpBoxSlave);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lnEditIpSlave3 = new QLineEdit(grpBoxSlave);
        lnEditIpSlave3->setObjectName(QString::fromUtf8("lnEditIpSlave3"));

        gridLayout->addWidget(lnEditIpSlave3, 2, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 2, 1, 1);

        label_10 = new QLabel(grpBoxSlave);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 2, 3, 1, 1);

        lnEditHostnameSlave3 = new QLineEdit(grpBoxSlave);
        lnEditHostnameSlave3->setObjectName(QString::fromUtf8("lnEditHostnameSlave3"));

        gridLayout->addWidget(lnEditHostnameSlave3, 2, 4, 1, 1);

        label_4 = new QLabel(grpBoxSlave);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lnEditIpSlave4 = new QLineEdit(grpBoxSlave);
        lnEditIpSlave4->setObjectName(QString::fromUtf8("lnEditIpSlave4"));

        gridLayout->addWidget(lnEditIpSlave4, 3, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 2, 1, 1);

        label_7 = new QLabel(grpBoxSlave);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 3, 1, 1);

        lnEditHostnameSlave4 = new QLineEdit(grpBoxSlave);
        lnEditHostnameSlave4->setObjectName(QString::fromUtf8("lnEditHostnameSlave4"));

        gridLayout->addWidget(lnEditHostnameSlave4, 3, 4, 1, 1);

        grpBoxMaster = new QGroupBox(MasterSlaveClass);
        grpBoxMaster->setObjectName(QString::fromUtf8("grpBoxMaster"));
        grpBoxMaster->setGeometry(QRect(20, 340, 501, 62));
        horizontalLayout = new QHBoxLayout(grpBoxMaster);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_5 = new QLabel(grpBoxMaster);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        lnEditIpMaster = new QLineEdit(grpBoxMaster);
        lnEditIpMaster->setObjectName(QString::fromUtf8("lnEditIpMaster"));

        horizontalLayout->addWidget(lnEditIpMaster);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_6 = new QLabel(grpBoxMaster);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        lnEditHostnameMaster = new QLineEdit(grpBoxMaster);
        lnEditHostnameMaster->setObjectName(QString::fromUtf8("lnEditHostnameMaster"));

        horizontalLayout->addWidget(lnEditHostnameMaster);


        retranslateUi(MasterSlaveClass);

        QMetaObject::connectSlotsByName(MasterSlaveClass);
    } // setupUi

    void retranslateUi(QWidget *MasterSlaveClass)
    {
        MasterSlaveClass->setWindowTitle(QApplication::translate("MasterSlaveClass", "\344\270\273\346\234\272-\344\273\216\346\234\272\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("MasterSlaveClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("MasterSlaveClass", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        checkBoxNetMode->setText(QApplication::translate("MasterSlaveClass", "\347\275\221\347\273\234\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        btnGrpHostFlag->setTitle(QString());
        hostFlag->setText(QApplication::translate("MasterSlaveClass", "\350\256\276\344\270\272\344\273\216\346\234\272", 0, QApplication::UnicodeUTF8));
        slaveFlag->setText(QApplication::translate("MasterSlaveClass", "\350\256\276\344\270\272\344\270\273\346\234\272", 0, QApplication::UnicodeUTF8));
        grpBoxSlave->setTitle(QApplication::translate("MasterSlaveClass", "\344\273\216\346\234\272\345\234\260\345\235\200\350\256\276\347\275\256\357\274\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MasterSlaveClass", "\344\273\216\346\234\272\344\270\200 IP:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MasterSlaveClass", "\346\234\272\345\231\250\345\220\215:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MasterSlaveClass", "\344\273\216\346\234\272\344\272\214 IP:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MasterSlaveClass", "\346\234\272\345\231\250\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MasterSlaveClass", "\344\273\216\346\234\272\344\270\211 IP:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MasterSlaveClass", "\346\234\272\345\231\250\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MasterSlaveClass", "\344\273\216\346\234\272\345\233\233 IP:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MasterSlaveClass", "\346\234\272\345\231\250\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        grpBoxMaster->setTitle(QApplication::translate("MasterSlaveClass", "\344\270\273\346\234\272\345\234\260\345\235\200\350\256\276\347\275\256\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MasterSlaveClass", "\344\270\273\346\234\272 IP:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MasterSlaveClass", "\346\234\272\345\231\250\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MasterSlaveClass: public Ui_MasterSlaveClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASTERSLAVESET_H
