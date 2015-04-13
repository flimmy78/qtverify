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
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlaCompParamDlgClass
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
    QGroupBox *groupBox_2;
    QLabel *label_7;
    QLineEdit *lineEdit_tempe;
    QLabel *label_8;
    QPushButton *btn_save;
    QPushButton *btn_exit;

    void setupUi(QWidget *PlaCompParamDlgClass)
    {
        if (PlaCompParamDlgClass->objectName().isEmpty())
            PlaCompParamDlgClass->setObjectName(QString::fromUtf8("PlaCompParamDlgClass"));
        PlaCompParamDlgClass->resize(411, 263);
        groupBox = new QGroupBox(PlaCompParamDlgClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 391, 141));
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
        groupBox_2 = new QGroupBox(PlaCompParamDlgClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 160, 391, 51));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 20, 251, 20));
        lineEdit_tempe = new QLineEdit(groupBox_2);
        lineEdit_tempe->setObjectName(QString::fromUtf8("lineEdit_tempe"));
        lineEdit_tempe->setGeometry(QRect(270, 20, 31, 20));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(310, 20, 16, 16));
        btn_save = new QPushButton(PlaCompParamDlgClass);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        btn_save->setGeometry(QRect(60, 220, 75, 23));
        btn_exit = new QPushButton(PlaCompParamDlgClass);
        btn_exit->setObjectName(QString::fromUtf8("btn_exit"));
        btn_exit->setGeometry(QRect(270, 220, 75, 23));

        retranslateUi(PlaCompParamDlgClass);

        QMetaObject::connectSlotsByName(PlaCompParamDlgClass);
    } // setupUi

    void retranslateUi(QWidget *PlaCompParamDlgClass)
    {
        PlaCompParamDlgClass->setWindowTitle(QApplication::translate("PlaCompParamDlgClass", "Parameter", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p align=\"right\">Standard</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p align=\"right\">Manufactory</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p align=\"right\">Checker</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p align=\"right\">Model</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p align=\"right\">Institution</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p align=\"right\">Verify</p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        label_7->setText(QApplication::translate("PlaCompParamDlgClass", "<html><head/><body><p align=\"right\">Minimum difference in temperature: \316\224\316\270min</p></body></html>", 0, QApplication::UnicodeUTF8));
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
