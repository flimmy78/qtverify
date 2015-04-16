/********************************************************************************
** Form generated from reading UI file 'chkplasensor.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHKPLASENSOR_H
#define UI_CHKPLASENSOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChkPlaSensorClass
{
public:
    QTableWidget *tbl_t_r;
    QGroupBox *groupBox_6;
    QLineEdit *lineEdit_r0;
    QLineEdit *lineEdit_a;
    QLineEdit *lineEdit_b;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *btn_calc;
    QPushButton *btn_save;
    QPushButton *btn_default;
    QPushButton *btn_exit;

    void setupUi(QWidget *ChkPlaSensorClass)
    {
        if (ChkPlaSensorClass->objectName().isEmpty())
            ChkPlaSensorClass->setObjectName(QString::fromUtf8("ChkPlaSensorClass"));
        ChkPlaSensorClass->resize(505, 179);
        tbl_t_r = new QTableWidget(ChkPlaSensorClass);
        if (tbl_t_r->columnCount() < 3)
            tbl_t_r->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbl_t_r->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbl_t_r->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbl_t_r->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tbl_t_r->rowCount() < 2)
            tbl_t_r->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbl_t_r->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbl_t_r->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tbl_t_r->setItem(0, 0, __qtablewidgetitem5);
        tbl_t_r->setObjectName(QString::fromUtf8("tbl_t_r"));
        tbl_t_r->setGeometry(QRect(20, 20, 191, 91));
        tbl_t_r->horizontalHeader()->setDefaultSectionSize(50);
        groupBox_6 = new QGroupBox(ChkPlaSensorClass);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(240, 20, 251, 61));
        groupBox_6->setCheckable(false);
        lineEdit_r0 = new QLineEdit(groupBox_6);
        lineEdit_r0->setObjectName(QString::fromUtf8("lineEdit_r0"));
        lineEdit_r0->setGeometry(QRect(10, 40, 71, 20));
        lineEdit_a = new QLineEdit(groupBox_6);
        lineEdit_a->setObjectName(QString::fromUtf8("lineEdit_a"));
        lineEdit_a->setGeometry(QRect(90, 40, 71, 20));
        lineEdit_b = new QLineEdit(groupBox_6);
        lineEdit_b->setObjectName(QString::fromUtf8("lineEdit_b"));
        lineEdit_b->setGeometry(QRect(170, 40, 71, 20));
        label_7 = new QLabel(groupBox_6);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 20, 21, 16));
        label_8 = new QLabel(groupBox_6);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(100, 20, 51, 20));
        label_9 = new QLabel(groupBox_6);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(180, 20, 51, 20));
        btn_calc = new QPushButton(ChkPlaSensorClass);
        btn_calc->setObjectName(QString::fromUtf8("btn_calc"));
        btn_calc->setGeometry(QRect(80, 140, 75, 23));
        btn_save = new QPushButton(ChkPlaSensorClass);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        btn_save->setGeometry(QRect(170, 140, 75, 23));
        btn_default = new QPushButton(ChkPlaSensorClass);
        btn_default->setObjectName(QString::fromUtf8("btn_default"));
        btn_default->setGeometry(QRect(260, 140, 75, 23));
        btn_exit = new QPushButton(ChkPlaSensorClass);
        btn_exit->setObjectName(QString::fromUtf8("btn_exit"));
        btn_exit->setGeometry(QRect(350, 140, 75, 23));

        retranslateUi(ChkPlaSensorClass);

        QMetaObject::connectSlotsByName(ChkPlaSensorClass);
    } // setupUi

    void retranslateUi(QWidget *ChkPlaSensorClass)
    {
        ChkPlaSensorClass->setWindowTitle(QApplication::translate("ChkPlaSensorClass", "Checked Platinum Sensor", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tbl_t_r->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ChkPlaSensorClass", "1st", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbl_t_r->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ChkPlaSensorClass", "2nd", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tbl_t_r->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ChkPlaSensorClass", "3rd", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tbl_t_r->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("ChkPlaSensorClass", "T(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tbl_t_r->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("ChkPlaSensorClass", "R(\316\251)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tbl_t_r->isSortingEnabled();
        tbl_t_r->setSortingEnabled(false);
        tbl_t_r->setSortingEnabled(__sortingEnabled);

        groupBox_6->setTitle(QApplication::translate("ChkPlaSensorClass", "Platinum Param", 0, QApplication::UnicodeUTF8));
        lineEdit_r0->setText(QString());
        label_7->setText(QApplication::translate("ChkPlaSensorClass", "<html><head/><body><p>R<span style=\" vertical-align:sub;\">0</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ChkPlaSensorClass", "<html><head/><body><p>ax10<span style=\" vertical-align:super;\">-3</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ChkPlaSensorClass", "<html><head/><body><p>bx10<span style=\" vertical-align:super;\">-7</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btn_calc->setText(QApplication::translate("ChkPlaSensorClass", "Calc", 0, QApplication::UnicodeUTF8));
        btn_save->setText(QApplication::translate("ChkPlaSensorClass", "Save", 0, QApplication::UnicodeUTF8));
        btn_default->setText(QApplication::translate("ChkPlaSensorClass", "Default", 0, QApplication::UnicodeUTF8));
        btn_exit->setText(QApplication::translate("ChkPlaSensorClass", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChkPlaSensorClass: public Ui_ChkPlaSensorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHKPLASENSOR_H
