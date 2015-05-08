/********************************************************************************
** Form generated from reading UI file 'tvercomp_param.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TVERCOMP_PARAM_H
#define UI_TVERCOMP_PARAM_H

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
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlaCompParamDlgClass
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QComboBox *cBox_stand;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *cBox_model;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *cBox_manu;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *cBox_inst;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *cBox_chk;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_6;
    QComboBox *cBox_verify;
    QGroupBox *groupBox_2;
    QLabel *label_7;
    QLineEdit *lineEdit_tempe;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btn_save;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *btn_exit;

    void setupUi(QWidget *PlaCompParamDlgClass)
    {
        if (PlaCompParamDlgClass->objectName().isEmpty())
            PlaCompParamDlgClass->setObjectName(QString::fromUtf8("PlaCompParamDlgClass"));
        PlaCompParamDlgClass->resize(411, 190);
        PlaCompParamDlgClass->setMinimumSize(QSize(411, 190));
        PlaCompParamDlgClass->setMaximumSize(QSize(16777215, 190));
        gridLayout_2 = new QGridLayout(PlaCompParamDlgClass);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(PlaCompParamDlgClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cBox_stand = new QComboBox(groupBox);
        cBox_stand->setObjectName(QString::fromUtf8("cBox_stand"));

        horizontalLayout->addWidget(cBox_stand);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        cBox_model = new QComboBox(groupBox);
        cBox_model->setObjectName(QString::fromUtf8("cBox_model"));

        horizontalLayout_4->addWidget(cBox_model);


        gridLayout->addLayout(horizontalLayout_4, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        cBox_manu = new QComboBox(groupBox);
        cBox_manu->setObjectName(QString::fromUtf8("cBox_manu"));

        horizontalLayout_2->addWidget(cBox_manu);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        cBox_inst = new QComboBox(groupBox);
        cBox_inst->setObjectName(QString::fromUtf8("cBox_inst"));

        horizontalLayout_5->addWidget(cBox_inst);


        gridLayout->addLayout(horizontalLayout_5, 1, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        cBox_chk = new QComboBox(groupBox);
        cBox_chk->setObjectName(QString::fromUtf8("cBox_chk"));

        horizontalLayout_3->addWidget(cBox_chk);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        cBox_verify = new QComboBox(groupBox);
        cBox_verify->setObjectName(QString::fromUtf8("cBox_verify"));

        horizontalLayout_6->addWidget(cBox_verify);


        gridLayout->addLayout(horizontalLayout_6, 2, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(PlaCompParamDlgClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 20, 191, 20));
        lineEdit_tempe = new QLineEdit(groupBox_2);
        lineEdit_tempe->setObjectName(QString::fromUtf8("lineEdit_tempe"));
        lineEdit_tempe->setGeometry(QRect(210, 20, 31, 20));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(250, 20, 16, 16));

        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        btn_save = new QPushButton(PlaCompParamDlgClass);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));

        horizontalLayout_7->addWidget(btn_save);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        btn_exit = new QPushButton(PlaCompParamDlgClass);
        btn_exit->setObjectName(QString::fromUtf8("btn_exit"));

        horizontalLayout_7->addWidget(btn_exit);


        gridLayout_2->addLayout(horizontalLayout_7, 2, 0, 1, 1);


        retranslateUi(PlaCompParamDlgClass);

        QMetaObject::connectSlotsByName(PlaCompParamDlgClass);
    } // setupUi

    void retranslateUi(QWidget *PlaCompParamDlgClass)
    {
        PlaCompParamDlgClass->setWindowTitle(QApplication::translate("PlaCompParamDlgClass", "Parameter", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p align=\"right\">Standard</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p>Model</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p align=\"right\">Manufactory</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p>Institution</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p>Checker</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p>Verify</p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        label_7->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p>Minimum temperature head: \316\224\316\270min</p></body></html>", 0, QApplication::UnicodeUTF8));
        lineEdit_tempe->setText(QApplication::translate("PlaCompParamDlgClass", "3", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p>K</p></body></html>", 0, QApplication::UnicodeUTF8));
        btn_save->setText(QApplication::translate("PlaCompParamDlgClass", "Save", 0, QApplication::UnicodeUTF8));
        btn_exit->setText(QApplication::translate("PlaCompParamDlgClass", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlaCompParamDlgClass: public Ui_PlaCompParamDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TVERCOMP_PARAM_H
