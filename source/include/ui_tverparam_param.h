/********************************************************************************
** Form generated from reading UI file 'tverparam_param.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TVERPARAM_PARAM_H
#define UI_TVERPARAM_PARAM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlaParamParamDlgClass
{
public:
    QGroupBox *groupBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QComboBox *cBox_stand;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *cBox_manu;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *cBox_chk;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *cBox_chanel;
    QWidget *widget4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *cBox_verify;
    QWidget *widget5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_6;
    QComboBox *cBox_inst;
    QWidget *widget6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_7;
    QComboBox *cBox_model;
    QWidget *widget7;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *btn_save;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btn_exit;

    void setupUi(QWidget *PlaParamParamDlgClass)
    {
        if (PlaParamParamDlgClass->objectName().isEmpty())
            PlaParamParamDlgClass->setObjectName(QString::fromUtf8("PlaParamParamDlgClass"));
        PlaParamParamDlgClass->resize(411, 233);
        PlaParamParamDlgClass->setMinimumSize(QSize(411, 233));
        PlaParamParamDlgClass->setMaximumSize(QSize(411, 233));
        groupBox = new QGroupBox(PlaParamParamDlgClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 391, 171));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 20, 171, 22));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cBox_stand = new QComboBox(widget);
        cBox_stand->setObjectName(QString::fromUtf8("cBox_stand"));

        horizontalLayout->addWidget(cBox_stand);

        widget1 = new QWidget(groupBox);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(10, 60, 181, 22));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        cBox_manu = new QComboBox(widget1);
        cBox_manu->setObjectName(QString::fromUtf8("cBox_manu"));

        horizontalLayout_2->addWidget(cBox_manu);

        widget2 = new QWidget(groupBox);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(20, 100, 171, 22));
        horizontalLayout_3 = new QHBoxLayout(widget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        cBox_chk = new QComboBox(widget2);
        cBox_chk->setObjectName(QString::fromUtf8("cBox_chk"));

        horizontalLayout_3->addWidget(cBox_chk);

        widget3 = new QWidget(groupBox);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        widget3->setGeometry(QRect(10, 140, 181, 22));
        horizontalLayout_4 = new QHBoxLayout(widget3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(widget3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_4->addWidget(label_7);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        cBox_chanel = new QComboBox(widget3);
        cBox_chanel->setObjectName(QString::fromUtf8("cBox_chanel"));

        horizontalLayout_4->addWidget(cBox_chanel);

        widget4 = new QWidget(groupBox);
        widget4->setObjectName(QString::fromUtf8("widget4"));
        widget4->setGeometry(QRect(210, 100, 151, 22));
        horizontalLayout_5 = new QHBoxLayout(widget4);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(widget4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        cBox_verify = new QComboBox(widget4);
        cBox_verify->setObjectName(QString::fromUtf8("cBox_verify"));

        horizontalLayout_5->addWidget(cBox_verify);

        widget5 = new QWidget(groupBox);
        widget5->setObjectName(QString::fromUtf8("widget5"));
        widget5->setGeometry(QRect(200, 60, 161, 22));
        horizontalLayout_6 = new QHBoxLayout(widget5);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget5);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        cBox_inst = new QComboBox(widget5);
        cBox_inst->setObjectName(QString::fromUtf8("cBox_inst"));

        horizontalLayout_6->addWidget(cBox_inst);

        widget6 = new QWidget(groupBox);
        widget6->setObjectName(QString::fromUtf8("widget6"));
        widget6->setGeometry(QRect(220, 20, 141, 22));
        horizontalLayout_7 = new QHBoxLayout(widget6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget6);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_7->addWidget(label_4);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        cBox_model = new QComboBox(widget6);
        cBox_model->setObjectName(QString::fromUtf8("cBox_model"));

        horizontalLayout_7->addWidget(cBox_model);

        widget7 = new QWidget(PlaParamParamDlgClass);
        widget7->setObjectName(QString::fromUtf8("widget7"));
        widget7->setGeometry(QRect(20, 200, 371, 25));
        horizontalLayout_8 = new QHBoxLayout(widget7);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        btn_save = new QPushButton(widget7);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));

        horizontalLayout_8->addWidget(btn_save);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);

        btn_exit = new QPushButton(widget7);
        btn_exit->setObjectName(QString::fromUtf8("btn_exit"));

        horizontalLayout_8->addWidget(btn_exit);


        retranslateUi(PlaParamParamDlgClass);

        QMetaObject::connectSlotsByName(PlaParamParamDlgClass);
    } // setupUi

    void retranslateUi(QWidget *PlaParamParamDlgClass)
    {
        PlaParamParamDlgClass->setWindowTitle(QApplication::translate("PlaParamParamDlgClass", "Parameter", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("PlaParamParamDlgClass", "<html><head/><body><p align=\"right\">Standard</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PlaParamParamDlgClass", "<html><head/><body><p align=\"right\">Manufactory</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("PlaParamParamDlgClass", "<html><head/><body><p align=\"right\">Checker</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("PlaParamParamDlgClass", "<html><head/><body><p align=\"right\">Chanel Used</p></body></html>", 0, QApplication::UnicodeUTF8));
        cBox_chanel->clear();
        cBox_chanel->insertItems(0, QStringList()
         << QApplication::translate("PlaParamParamDlgClass", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlaParamParamDlgClass", "2", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("PlaParamParamDlgClass", "<html><head/><body><p align=\"right\">Verify</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PlaParamParamDlgClass", "<html><head/><body><p align=\"right\">Institution</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("PlaParamParamDlgClass", "<html><head/><body><p align=\"right\">Model</p></body></html>", 0, QApplication::UnicodeUTF8));
        btn_save->setText(QApplication::translate("PlaParamParamDlgClass", "Save", 0, QApplication::UnicodeUTF8));
        btn_exit->setText(QApplication::translate("PlaParamParamDlgClass", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlaParamParamDlgClass: public Ui_PlaParamParamDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TVERPARAM_PARAM_H
