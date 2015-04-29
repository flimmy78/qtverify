/********************************************************************************
** Form generated from reading UI file 'calcpara.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCPARA_H
#define UI_CALCPARA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_CalcParaClass
{
public:
    QGridLayout *gridLayout_8;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *lnEditMeterNO;
    QLabel *label_2;
    QComboBox *cmbModel;
    QLabel *label_3;
    QComboBox *cmbManufact;
    QLabel *label_4;
    QComboBox *cmbVerifyDept;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QComboBox *cmbStandard;
    QLabel *label_6;
    QComboBox *cmbGrade;
    QLabel *label_7;
    QComboBox *cmbVerifyPerson;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QLabel *label_8;
    QLineEdit *lnEditMaxT;
    QLabel *label_10;
    QLineEdit *lnEditMinT;
    QLabel *label_12;
    QLabel *label_9;
    QLineEdit *lnEditMaxDeltaT;
    QLabel *label_11;
    QLineEdit *lnEditMinDeltaT;
    QLabel *label_13;
    QGridLayout *gridLayout_4;
    QPushButton *btnOK;
    QPushButton *btnExit;

    void setupUi(QDialog *CalcParaClass)
    {
        if (CalcParaClass->objectName().isEmpty())
            CalcParaClass->setObjectName(QString::fromUtf8("CalcParaClass"));
        CalcParaClass->setWindowModality(Qt::ApplicationModal);
        CalcParaClass->resize(516, 283);
        gridLayout_8 = new QGridLayout(CalcParaClass);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        groupBox = new QGroupBox(CalcParaClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lnEditMeterNO = new QLineEdit(groupBox);
        lnEditMeterNO->setObjectName(QString::fromUtf8("lnEditMeterNO"));

        gridLayout_2->addWidget(lnEditMeterNO, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        cmbModel = new QComboBox(groupBox);
        cmbModel->setObjectName(QString::fromUtf8("cmbModel"));
        cmbModel->setEditable(false);

        gridLayout_2->addWidget(cmbModel, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        cmbManufact = new QComboBox(groupBox);
        cmbManufact->setObjectName(QString::fromUtf8("cmbManufact"));
        cmbManufact->setEditable(false);

        gridLayout_2->addWidget(cmbManufact, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        cmbVerifyDept = new QComboBox(groupBox);
        cmbVerifyDept->setObjectName(QString::fromUtf8("cmbVerifyDept"));
        cmbVerifyDept->setEditable(false);

        gridLayout_2->addWidget(cmbVerifyDept, 3, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        cmbStandard = new QComboBox(groupBox);
        cmbStandard->setObjectName(QString::fromUtf8("cmbStandard"));

        gridLayout->addWidget(cmbStandard, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        cmbGrade = new QComboBox(groupBox);
        cmbGrade->setObjectName(QString::fromUtf8("cmbGrade"));

        gridLayout->addWidget(cmbGrade, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        cmbVerifyPerson = new QComboBox(groupBox);
        cmbVerifyPerson->setObjectName(QString::fromUtf8("cmbVerifyPerson"));
        cmbVerifyPerson->setEditable(false);

        gridLayout->addWidget(cmbVerifyPerson, 2, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 1, 1, 1);


        gridLayout_8->addWidget(groupBox, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer, 1, 0, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        groupBox_2 = new QGroupBox(CalcParaClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_5->addWidget(label_8, 0, 0, 1, 1);

        lnEditMaxT = new QLineEdit(groupBox_2);
        lnEditMaxT->setObjectName(QString::fromUtf8("lnEditMaxT"));
        lnEditMaxT->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lnEditMaxT, 0, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_5->addWidget(label_10, 0, 2, 1, 1);

        lnEditMinT = new QLineEdit(groupBox_2);
        lnEditMinT->setObjectName(QString::fromUtf8("lnEditMinT"));
        lnEditMinT->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lnEditMinT, 0, 3, 1, 1);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_5->addWidget(label_12, 0, 4, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_5->addWidget(label_9, 1, 0, 1, 1);

        lnEditMaxDeltaT = new QLineEdit(groupBox_2);
        lnEditMaxDeltaT->setObjectName(QString::fromUtf8("lnEditMaxDeltaT"));
        lnEditMaxDeltaT->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lnEditMaxDeltaT, 1, 1, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_5->addWidget(label_11, 1, 2, 1, 1);

        lnEditMinDeltaT = new QLineEdit(groupBox_2);
        lnEditMinDeltaT->setObjectName(QString::fromUtf8("lnEditMinDeltaT"));
        lnEditMinDeltaT->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lnEditMinDeltaT, 1, 3, 1, 1);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_5->addWidget(label_13, 1, 4, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_2, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        btnOK = new QPushButton(CalcParaClass);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        gridLayout_4->addWidget(btnOK, 0, 0, 1, 1);

        btnExit = new QPushButton(CalcParaClass);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));

        gridLayout_4->addWidget(btnExit, 1, 0, 1, 1);


        gridLayout_7->addLayout(gridLayout_4, 0, 1, 1, 1);


        gridLayout_8->addLayout(gridLayout_7, 2, 0, 1, 1);


        retranslateUi(CalcParaClass);

        QMetaObject::connectSlotsByName(CalcParaClass);
    } // setupUi

    void retranslateUi(QDialog *CalcParaClass)
    {
        groupBox->setTitle(QApplication::translate("CalcParaClass", "Verify Para", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CalcParaClass", "MeterNO(14bit):", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CalcParaClass", "Model:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CalcParaClass", "ManuFact:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("CalcParaClass", "VerifyDept:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("CalcParaClass", "Standard:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("CalcParaClass", "Grade:", 0, QApplication::UnicodeUTF8));
        cmbGrade->clear();
        cmbGrade->insertItems(0, QStringList()
         << QApplication::translate("CalcParaClass", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CalcParaClass", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CalcParaClass", "3", 0, QApplication::UnicodeUTF8)
        );
        label_7->setText(QApplication::translate("CalcParaClass", "VerifyPerson:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("CalcParaClass", "Heat Para", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("CalcParaClass", "\316\270max", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("CalcParaClass", "\316\270min", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("CalcParaClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("CalcParaClass", "\316\224\316\270max", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("CalcParaClass", "\316\224\316\270min", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("CalcParaClass", "K", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("CalcParaClass", "OK", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("CalcParaClass", "Exit", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CalcParaClass);
    } // retranslateUi

};

namespace Ui {
    class CalcParaClass: public Ui_CalcParaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCPARA_H
