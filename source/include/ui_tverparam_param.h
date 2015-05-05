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
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlaParamParamDlgClass
{
public:
    QGroupBox *groupBox;
    QComboBox *cBox_stand;
    QLabel *label;
    QLabel *label_2;
    QComboBox *cBox_manu;
    QComboBox *cBox_chk;
    QLabel *label_3;
    QComboBox *cBox_model;
    QLabel *label_4;
    QComboBox *cBox_inst;
    QLabel *label_5;
    QComboBox *cBox_verify;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *cBox_chanel;
    QPushButton *btn_save;
    QPushButton *btn_exit;

    void setupUi(QWidget *PlaParamParamDlgClass)
    {
        if (PlaParamParamDlgClass->objectName().isEmpty())
            PlaParamParamDlgClass->setObjectName(QString::fromUtf8("PlaParamParamDlgClass"));
        PlaParamParamDlgClass->resize(411, 233);
        groupBox = new QGroupBox(PlaParamParamDlgClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 391, 171));
        cBox_stand = new QComboBox(groupBox);
        cBox_stand->setObjectName(QString::fromUtf8("cBox_stand"));
        cBox_stand->setGeometry(QRect(100, 20, 69, 22));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 61, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 60, 71, 20));
        cBox_manu = new QComboBox(groupBox);
        cBox_manu->setObjectName(QString::fromUtf8("cBox_manu"));
        cBox_manu->setGeometry(QRect(100, 60, 69, 22));
        cBox_chk = new QComboBox(groupBox);
        cBox_chk->setObjectName(QString::fromUtf8("cBox_chk"));
        cBox_chk->setGeometry(QRect(100, 100, 69, 22));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 100, 54, 12));
        cBox_model = new QComboBox(groupBox);
        cBox_model->setObjectName(QString::fromUtf8("cBox_model"));
        cBox_model->setGeometry(QRect(290, 20, 69, 22));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(220, 20, 54, 12));
        cBox_inst = new QComboBox(groupBox);
        cBox_inst->setObjectName(QString::fromUtf8("cBox_inst"));
        cBox_inst->setGeometry(QRect(290, 60, 69, 22));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(200, 60, 71, 16));
        cBox_verify = new QComboBox(groupBox);
        cBox_verify->setObjectName(QString::fromUtf8("cBox_verify"));
        cBox_verify->setGeometry(QRect(290, 100, 69, 22));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(210, 100, 54, 16));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 140, 71, 20));
        cBox_chanel = new QComboBox(groupBox);
        cBox_chanel->setObjectName(QString::fromUtf8("cBox_chanel"));
        cBox_chanel->setGeometry(QRect(100, 140, 69, 22));
        btn_save = new QPushButton(PlaParamParamDlgClass);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        btn_save->setGeometry(QRect(60, 200, 75, 23));
        btn_exit = new QPushButton(PlaParamParamDlgClass);
        btn_exit->setObjectName(QString::fromUtf8("btn_exit"));
        btn_exit->setGeometry(QRect(270, 200, 75, 23));

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
        label_4->setText(QApplication::translate("PlaParamParamDlgClass", "<html><head/><body><p align=\"right\">Model</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PlaParamParamDlgClass", "<html><head/><body><p align=\"right\">Institution</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("PlaParamParamDlgClass", "<html><head/><body><p align=\"right\">Verify</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("PlaParamParamDlgClass", "<html><head/><body><p align=\"right\">Chanel Used</p></body></html>", 0, QApplication::UnicodeUTF8));
        cBox_chanel->clear();
        cBox_chanel->insertItems(0, QStringList()
         << QApplication::translate("PlaParamParamDlgClass", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlaParamParamDlgClass", "2", 0, QApplication::UnicodeUTF8)
        );
        btn_save->setText(QApplication::translate("PlaParamParamDlgClass", "Save", 0, QApplication::UnicodeUTF8));
        btn_exit->setText(QApplication::translate("PlaParamParamDlgClass", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlaParamParamDlgClass: public Ui_PlaParamParamDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TVERPARAM_PARAM_H
