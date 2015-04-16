/********************************************************************************
** Form generated from reading UI file 'stdplasensor.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STDPLASENSOR_H
#define UI_STDPLASENSOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StdPlaSensorDlgClass
{
public:
    QGroupBox *gBox_pt25;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit_pt25_in_rtp;
    QLineEdit *lineEdit_pt25_in_a;
    QLineEdit *lineEdit_pt25_in_b;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *groupBox_3;
    QLineEdit *lineEdit_pt25_out_rtp;
    QLineEdit *lineEdit_pt25_out_a;
    QLineEdit *lineEdit_pt25_out_b;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *btn_pt25_save;
    QPushButton *btn_pt25_exit;
    QGroupBox *gBox_pt100;
    QGroupBox *groupBox_6;
    QLineEdit *lineEdit_pt100_in_rtp;
    QLineEdit *lineEdit_pt100_in_a;
    QLineEdit *lineEdit_pt100_in_b;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QGroupBox *groupBox_7;
    QLineEdit *lineEdit_pt100_out_rtp;
    QLineEdit *lineEdit_pt100_out_a;
    QLineEdit *lineEdit_pt100_out_b;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QPushButton *btn_pt100_save;
    QPushButton *btn_pt100_exit;
    QTableWidget *tbl_pt100_in;
    QLabel *label_13;
    QLabel *label_14;
    QTableWidget *tbl_pt100_out;
    QPushButton *btn_pt100_calc;
    QGroupBox *gBox_model;
    QRadioButton *rbtn_inst;
    QRadioButton *rbtn_weili;
    QRadioButton *rbtn_huayi;
    QPushButton *btn_model_save;

    void setupUi(QWidget *StdPlaSensorDlgClass)
    {
        if (StdPlaSensorDlgClass->objectName().isEmpty())
            StdPlaSensorDlgClass->setObjectName(QString::fromUtf8("StdPlaSensorDlgClass"));
        StdPlaSensorDlgClass->resize(563, 479);
        gBox_pt25 = new QGroupBox(StdPlaSensorDlgClass);
        gBox_pt25->setObjectName(QString::fromUtf8("gBox_pt25"));
        gBox_pt25->setGeometry(QRect(10, 10, 551, 131));
        gBox_pt25->setCheckable(true);
        groupBox_2 = new QGroupBox(gBox_pt25);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 20, 251, 61));
        groupBox_2->setCheckable(false);
        lineEdit_pt25_in_rtp = new QLineEdit(groupBox_2);
        lineEdit_pt25_in_rtp->setObjectName(QString::fromUtf8("lineEdit_pt25_in_rtp"));
        lineEdit_pt25_in_rtp->setGeometry(QRect(10, 40, 71, 20));
        lineEdit_pt25_in_a = new QLineEdit(groupBox_2);
        lineEdit_pt25_in_a->setObjectName(QString::fromUtf8("lineEdit_pt25_in_a"));
        lineEdit_pt25_in_a->setGeometry(QRect(90, 40, 71, 20));
        lineEdit_pt25_in_b = new QLineEdit(groupBox_2);
        lineEdit_pt25_in_b->setObjectName(QString::fromUtf8("lineEdit_pt25_in_b"));
        lineEdit_pt25_in_b->setGeometry(QRect(170, 40, 71, 20));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 21, 16));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 20, 51, 20));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(180, 20, 51, 20));
        groupBox_3 = new QGroupBox(gBox_pt25);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(290, 20, 251, 61));
        lineEdit_pt25_out_rtp = new QLineEdit(groupBox_3);
        lineEdit_pt25_out_rtp->setObjectName(QString::fromUtf8("lineEdit_pt25_out_rtp"));
        lineEdit_pt25_out_rtp->setGeometry(QRect(10, 40, 71, 20));
        lineEdit_pt25_out_a = new QLineEdit(groupBox_3);
        lineEdit_pt25_out_a->setObjectName(QString::fromUtf8("lineEdit_pt25_out_a"));
        lineEdit_pt25_out_a->setGeometry(QRect(90, 40, 71, 20));
        lineEdit_pt25_out_b = new QLineEdit(groupBox_3);
        lineEdit_pt25_out_b->setObjectName(QString::fromUtf8("lineEdit_pt25_out_b"));
        lineEdit_pt25_out_b->setGeometry(QRect(170, 40, 71, 20));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 20, 21, 16));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(100, 20, 51, 20));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(180, 20, 51, 20));
        btn_pt25_save = new QPushButton(gBox_pt25);
        btn_pt25_save->setObjectName(QString::fromUtf8("btn_pt25_save"));
        btn_pt25_save->setGeometry(QRect(60, 100, 75, 23));
        btn_pt25_exit = new QPushButton(gBox_pt25);
        btn_pt25_exit->setObjectName(QString::fromUtf8("btn_pt25_exit"));
        btn_pt25_exit->setGeometry(QRect(420, 100, 75, 23));
        gBox_pt100 = new QGroupBox(StdPlaSensorDlgClass);
        gBox_pt100->setObjectName(QString::fromUtf8("gBox_pt100"));
        gBox_pt100->setGeometry(QRect(10, 150, 551, 261));
        gBox_pt100->setCheckable(true);
        gBox_pt100->setChecked(false);
        groupBox_6 = new QGroupBox(gBox_pt100);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(280, 20, 251, 61));
        groupBox_6->setCheckable(false);
        lineEdit_pt100_in_rtp = new QLineEdit(groupBox_6);
        lineEdit_pt100_in_rtp->setObjectName(QString::fromUtf8("lineEdit_pt100_in_rtp"));
        lineEdit_pt100_in_rtp->setGeometry(QRect(10, 40, 71, 20));
        lineEdit_pt100_in_a = new QLineEdit(groupBox_6);
        lineEdit_pt100_in_a->setObjectName(QString::fromUtf8("lineEdit_pt100_in_a"));
        lineEdit_pt100_in_a->setGeometry(QRect(90, 40, 71, 20));
        lineEdit_pt100_in_b = new QLineEdit(groupBox_6);
        lineEdit_pt100_in_b->setObjectName(QString::fromUtf8("lineEdit_pt100_in_b"));
        lineEdit_pt100_in_b->setGeometry(QRect(170, 40, 71, 20));
        label_7 = new QLabel(groupBox_6);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 20, 21, 16));
        label_8 = new QLabel(groupBox_6);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(100, 20, 51, 20));
        label_9 = new QLabel(groupBox_6);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(180, 20, 51, 20));
        groupBox_7 = new QGroupBox(gBox_pt100);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(280, 100, 251, 61));
        lineEdit_pt100_out_rtp = new QLineEdit(groupBox_7);
        lineEdit_pt100_out_rtp->setObjectName(QString::fromUtf8("lineEdit_pt100_out_rtp"));
        lineEdit_pt100_out_rtp->setGeometry(QRect(10, 40, 71, 20));
        lineEdit_pt100_out_a = new QLineEdit(groupBox_7);
        lineEdit_pt100_out_a->setObjectName(QString::fromUtf8("lineEdit_pt100_out_a"));
        lineEdit_pt100_out_a->setGeometry(QRect(90, 40, 71, 20));
        lineEdit_pt100_out_b = new QLineEdit(groupBox_7);
        lineEdit_pt100_out_b->setObjectName(QString::fromUtf8("lineEdit_pt100_out_b"));
        lineEdit_pt100_out_b->setGeometry(QRect(170, 40, 71, 20));
        label_10 = new QLabel(groupBox_7);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 20, 21, 16));
        label_11 = new QLabel(groupBox_7);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(100, 20, 51, 20));
        label_12 = new QLabel(groupBox_7);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(180, 20, 51, 20));
        btn_pt100_save = new QPushButton(gBox_pt100);
        btn_pt100_save->setObjectName(QString::fromUtf8("btn_pt100_save"));
        btn_pt100_save->setGeometry(QRect(350, 210, 75, 23));
        btn_pt100_exit = new QPushButton(gBox_pt100);
        btn_pt100_exit->setObjectName(QString::fromUtf8("btn_pt100_exit"));
        btn_pt100_exit->setGeometry(QRect(440, 210, 75, 23));
        tbl_pt100_in = new QTableWidget(gBox_pt100);
        if (tbl_pt100_in->columnCount() < 3)
            tbl_pt100_in->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbl_pt100_in->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbl_pt100_in->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbl_pt100_in->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tbl_pt100_in->rowCount() < 2)
            tbl_pt100_in->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbl_pt100_in->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbl_pt100_in->setVerticalHeaderItem(1, __qtablewidgetitem4);
        tbl_pt100_in->setObjectName(QString::fromUtf8("tbl_pt100_in"));
        tbl_pt100_in->setGeometry(QRect(30, 50, 191, 91));
        tbl_pt100_in->horizontalHeader()->setDefaultSectionSize(50);
        tbl_pt100_in->horizontalHeader()->setMinimumSectionSize(10);
        label_13 = new QLabel(gBox_pt100);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(40, 30, 21, 16));
        label_14 = new QLabel(gBox_pt100);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(40, 140, 21, 16));
        tbl_pt100_out = new QTableWidget(gBox_pt100);
        if (tbl_pt100_out->columnCount() < 3)
            tbl_pt100_out->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tbl_pt100_out->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tbl_pt100_out->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tbl_pt100_out->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        if (tbl_pt100_out->rowCount() < 2)
            tbl_pt100_out->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tbl_pt100_out->setVerticalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tbl_pt100_out->setVerticalHeaderItem(1, __qtablewidgetitem9);
        tbl_pt100_out->setObjectName(QString::fromUtf8("tbl_pt100_out"));
        tbl_pt100_out->setGeometry(QRect(30, 160, 191, 91));
        tbl_pt100_out->horizontalHeader()->setDefaultSectionSize(50);
        tbl_pt100_out->horizontalHeader()->setMinimumSectionSize(10);
        btn_pt100_calc = new QPushButton(gBox_pt100);
        btn_pt100_calc->setObjectName(QString::fromUtf8("btn_pt100_calc"));
        btn_pt100_calc->setGeometry(QRect(260, 210, 75, 23));
        gBox_model = new QGroupBox(StdPlaSensorDlgClass);
        gBox_model->setObjectName(QString::fromUtf8("gBox_model"));
        gBox_model->setGeometry(QRect(20, 420, 531, 51));
        rbtn_inst = new QRadioButton(gBox_model);
        rbtn_inst->setObjectName(QString::fromUtf8("rbtn_inst"));
        rbtn_inst->setGeometry(QRect(20, 20, 161, 16));
        rbtn_weili = new QRadioButton(gBox_model);
        rbtn_weili->setObjectName(QString::fromUtf8("rbtn_weili"));
        rbtn_weili->setGeometry(QRect(200, 20, 89, 16));
        rbtn_huayi = new QRadioButton(gBox_model);
        rbtn_huayi->setObjectName(QString::fromUtf8("rbtn_huayi"));
        rbtn_huayi->setGeometry(QRect(330, 20, 89, 16));
        btn_model_save = new QPushButton(gBox_model);
        btn_model_save->setObjectName(QString::fromUtf8("btn_model_save"));
        btn_model_save->setGeometry(QRect(430, 20, 75, 23));

        retranslateUi(StdPlaSensorDlgClass);

        QMetaObject::connectSlotsByName(StdPlaSensorDlgClass);
    } // setupUi

    void retranslateUi(QWidget *StdPlaSensorDlgClass)
    {
        StdPlaSensorDlgClass->setWindowTitle(QApplication::translate("StdPlaSensorDlgClass", "Standard Platinium Sensor", 0, QApplication::UnicodeUTF8));
        gBox_pt25->setTitle(QApplication::translate("StdPlaSensorDlgClass", "Pt25 standard Platinum Resistance", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("StdPlaSensorDlgClass", "In Sensor Param", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StdPlaSensorDlgClass", "Rtp", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("StdPlaSensorDlgClass", "<html><head/><body><p>a8x10<span style=\" vertical-align:super;\">-5</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("StdPlaSensorDlgClass", "<html><head/><body><p>b8x10<span style=\" vertical-align:super;\">-5</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("StdPlaSensorDlgClass", "Out Sensor Param", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("StdPlaSensorDlgClass", "Rtp", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("StdPlaSensorDlgClass", "<html><head/><body><p>a8x10<span style=\" vertical-align:super;\">-5</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("StdPlaSensorDlgClass", "<html><head/><body><p>b8x10<span style=\" vertical-align:super;\">-5</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btn_pt25_save->setText(QApplication::translate("StdPlaSensorDlgClass", "Save", 0, QApplication::UnicodeUTF8));
        btn_pt25_exit->setText(QApplication::translate("StdPlaSensorDlgClass", "Exit", 0, QApplication::UnicodeUTF8));
        gBox_pt100->setTitle(QApplication::translate("StdPlaSensorDlgClass", "Pt100 standard Platinum Resistance", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("StdPlaSensorDlgClass", "In Sensor Param", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("StdPlaSensorDlgClass", "Rtp", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("StdPlaSensorDlgClass", "<html><head/><body><p>a8x10<span style=\" vertical-align:super;\">-5</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("StdPlaSensorDlgClass", "<html><head/><body><p>b8x10<span style=\" vertical-align:super;\">-5</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("StdPlaSensorDlgClass", "Out Sensor Param", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("StdPlaSensorDlgClass", "Rtp", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("StdPlaSensorDlgClass", "<html><head/><body><p>a8x10<span style=\" vertical-align:super;\">-5</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("StdPlaSensorDlgClass", "<html><head/><body><p>b8x10<span style=\" vertical-align:super;\">-5</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btn_pt100_save->setText(QApplication::translate("StdPlaSensorDlgClass", "Save", 0, QApplication::UnicodeUTF8));
        btn_pt100_exit->setText(QApplication::translate("StdPlaSensorDlgClass", "Exit", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tbl_pt100_in->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("StdPlaSensorDlgClass", "1st", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbl_pt100_in->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("StdPlaSensorDlgClass", "2nd", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tbl_pt100_in->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("StdPlaSensorDlgClass", "3rd", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tbl_pt100_in->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("StdPlaSensorDlgClass", "T(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tbl_pt100_in->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("StdPlaSensorDlgClass", "R(\316\251)", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("StdPlaSensorDlgClass", "In", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("StdPlaSensorDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tbl_pt100_out->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("StdPlaSensorDlgClass", "1st", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tbl_pt100_out->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("StdPlaSensorDlgClass", "2nd", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tbl_pt100_out->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("StdPlaSensorDlgClass", "3rd", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tbl_pt100_out->verticalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("StdPlaSensorDlgClass", "T(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tbl_pt100_out->verticalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("StdPlaSensorDlgClass", "R(\316\251)", 0, QApplication::UnicodeUTF8));
        btn_pt100_calc->setText(QApplication::translate("StdPlaSensorDlgClass", "Calc", 0, QApplication::UnicodeUTF8));
        gBox_model->setTitle(QApplication::translate("StdPlaSensorDlgClass", "Model", 0, QApplication::UnicodeUTF8));
        rbtn_inst->setText(QApplication::translate("StdPlaSensorDlgClass", "Institute of Metrology", 0, QApplication::UnicodeUTF8));
        rbtn_weili->setText(QApplication::translate("StdPlaSensorDlgClass", "WeiLi", 0, QApplication::UnicodeUTF8));
        rbtn_huayi->setText(QApplication::translate("StdPlaSensorDlgClass", "HuaYi", 0, QApplication::UnicodeUTF8));
        btn_model_save->setText(QApplication::translate("StdPlaSensorDlgClass", "Save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StdPlaSensorDlgClass: public Ui_StdPlaSensorDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STDPLASENSOR_H
