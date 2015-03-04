/********************************************************************************
** Form generated from reading UI file 'calcverify.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCVERIFY_H
#define UI_CALCVERIFY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CalcDlgClass
{
public:
    QGroupBox *groupBox_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QGroupBox *groupBox_3;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QGroupBox *groupBox_4;
    QLineEdit *lineEdit;
    QLabel *label;
    QGroupBox *groupBox_5;
    QTableWidget *tableWidget;
    QLabel *label_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QLabel *label_3;
    QLabel *label_4;
    QFrame *line_6;
    QFrame *line_7;
    QGroupBox *groupBox_6;
    QTableWidget *tableWidget_2;
    QGroupBox *groupBox_7;
    QTableWidget *tableWidget_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;

    void setupUi(QDialog *CalcDlgClass)
    {
        if (CalcDlgClass->objectName().isEmpty())
            CalcDlgClass->setObjectName(QString::fromUtf8("CalcDlgClass"));
        CalcDlgClass->resize(1273, 738);
        groupBox_2 = new QGroupBox(CalcDlgClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 10, 131, 51));
        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(10, 30, 51, 16));
        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(80, 30, 51, 16));
        groupBox_3 = new QGroupBox(CalcDlgClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(280, 10, 131, 51));
        radioButton_3 = new QRadioButton(groupBox_3);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(10, 30, 51, 16));
        radioButton_4 = new QRadioButton(groupBox_3);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setGeometry(QRect(80, 30, 51, 16));
        groupBox_4 = new QGroupBox(CalcDlgClass);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(530, 10, 131, 51));
        lineEdit = new QLineEdit(groupBox_4);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(70, 20, 51, 20));
        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 31, 16));
        groupBox_5 = new QGroupBox(CalcDlgClass);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 90, 1241, 251));
        groupBox_5->setProperty("toolTipDuration", QVariant(0));
        tableWidget = new QTableWidget(groupBox_5);
        if (tableWidget->columnCount() < 13)
            tableWidget->setColumnCount(13);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        if (tableWidget->rowCount() < 4)
            tableWidget->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem16);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 60, 1221, 181));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(7);
        tableWidget->setFont(font);
        tableWidget->horizontalHeader()->setDefaultSectionSize(90);
        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(220, 40, 54, 12));
        line_3 = new QFrame(groupBox_5);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(60, 10, 1171, 41));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(groupBox_5);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(760, 30, 20, 31));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(groupBox_5);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(1220, 30, 16, 31));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(570, 40, 54, 12));
        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(970, 40, 71, 20));
        line_6 = new QFrame(groupBox_5);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setGeometry(QRect(400, 30, 16, 31));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(groupBox_5);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setGeometry(QRect(50, 30, 16, 31));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);
        groupBox_6 = new QGroupBox(CalcDlgClass);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(20, 340, 1241, 161));
        groupBox_6->setProperty("toolTipDuration", QVariant(0));
        tableWidget_2 = new QTableWidget(groupBox_6);
        if (tableWidget_2->columnCount() < 15)
            tableWidget_2->setColumnCount(15);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(7, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(8, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(9, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(10, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(11, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(12, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(13, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(14, __qtablewidgetitem31);
        if (tableWidget_2->rowCount() < 3)
            tableWidget_2->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(0, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(1, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(2, __qtablewidgetitem34);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(10, 20, 1221, 121));
        tableWidget_2->setFont(font);
        tableWidget_2->horizontalHeader()->setDefaultSectionSize(80);
        groupBox_7 = new QGroupBox(CalcDlgClass);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(20, 500, 1241, 171));
        groupBox_7->setProperty("toolTipDuration", QVariant(0));
        tableWidget_3 = new QTableWidget(groupBox_7);
        if (tableWidget_3->columnCount() < 15)
            tableWidget_3->setColumnCount(15);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(3, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(4, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(5, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(6, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(7, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(8, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(9, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(10, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(11, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(12, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(13, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(14, __qtablewidgetitem49);
        if (tableWidget_3->rowCount() < 3)
            tableWidget_3->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(0, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(1, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(2, __qtablewidgetitem52);
        tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));
        tableWidget_3->setGeometry(QRect(10, 20, 1221, 141));
        tableWidget_3->setFont(font);
        tableWidget_3->horizontalHeader()->setDefaultSectionSize(80);
        pushButton_4 = new QPushButton(CalcDlgClass);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(730, 690, 75, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../source/gui/images/calculatorresult.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon);
        pushButton_5 = new QPushButton(CalcDlgClass);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(880, 690, 75, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../source/gui/images/excel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon1);
        pushButton_6 = new QPushButton(CalcDlgClass);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(1020, 690, 75, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../source/gui/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_6->setIcon(icon2);
        pushButton_7 = new QPushButton(CalcDlgClass);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(1160, 690, 75, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_7->setIcon(icon3);

        retranslateUi(CalcDlgClass);

        QMetaObject::connectSlotsByName(CalcDlgClass);
    } // setupUi

    void retranslateUi(QDialog *CalcDlgClass)
    {
        CalcDlgClass->setWindowTitle(QApplication::translate("CalcDlgClass", "\350\256\241\347\256\227\345\231\250\346\243\200\346\265\213", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("CalcDlgClass", "\345\256\211\350\243\205\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("CalcDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("CalcDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("CalcDlgClass", "\347\203\255\351\207\217\345\215\225\344\275\215", 0, QApplication::UnicodeUTF8));
        radioButton_3->setText(QApplication::translate("CalcDlgClass", "MJ", 0, QApplication::UnicodeUTF8));
        radioButton_4->setText(QApplication::translate("CalcDlgClass", "kWh", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("CalcDlgClass", "\346\234\200\345\260\217\346\270\251\345\267\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270min", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("CalcDlgClass", "\345\207\272\345\217\243\346\270\251\345\272\246: \316\270min\342\211\244\316\270d\342\211\244\316\270min+5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CalcDlgClass", "\350\277\233\345\217\243\347\224\265\351\230\273\n"
"(\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CalcDlgClass", "\345\207\272\345\217\243\347\224\265\351\230\273\n"
"(\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("CalcDlgClass", "\345\273\272\350\256\256\345\200\274\n"
"(\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("CalcDlgClass", "\344\275\223\347\247\257\n"
"(L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("CalcDlgClass", "\350\277\233\345\217\243\346\270\251\345\272\246\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("CalcDlgClass", "\345\207\272\345\217\243\346\270\251\345\272\246\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("CalcDlgClass", "K\347\263\273\346\225\260\n"
"(kWh/x)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("CalcDlgClass", "\347\220\206\350\256\272\347\203\255\351\207\217\n"
"(kWh)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("CalcDlgClass", "E0\n"
"(kWh)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("CalcDlgClass", "E1\n"
"(kWh)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("CalcDlgClass", "\347\203\255\351\207\217\347\244\272\345\200\274\n"
"(kWh)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QApplication::translate("CalcDlgClass", "\347\244\272\345\200\274\350\257\257\345\267\256\n"
"(%)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->horizontalHeaderItem(12);
        ___qtablewidgetitem12->setText(QApplication::translate("CalcDlgClass", "\346\212\200\346\234\257\350\246\201\346\261\202\n"
"(%)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem13->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270min", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem14->setText(QApplication::translate("CalcDlgClass", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem15->setText(QApplication::translate("CalcDlgClass", "20", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem16->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270ref", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CalcDlgClass", "\346\250\241\346\213\237\350\276\223\345\205\245", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CalcDlgClass", "\346\240\207\345\207\206\345\200\274", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("CalcDlgClass", "\347\244\272\345\200\274\345\217\212\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("CalcDlgClass", "\345\207\272\345\217\243\346\270\251\345\272\246: \316\270d = \316\270ref\302\2615", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_2->verticalHeaderItem(0);
        ___qtablewidgetitem17->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270min", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_2->verticalHeaderItem(1);
        ___qtablewidgetitem18->setText(QApplication::translate("CalcDlgClass", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_2->verticalHeaderItem(2);
        ___qtablewidgetitem19->setText(QApplication::translate("CalcDlgClass", "20", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("CalcDlgClass", "\350\277\233\345\217\243\346\270\251\345\272\246:  \316\270max-5\342\211\244\316\270d \342\211\244 \316\270max", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_3->verticalHeaderItem(0);
        ___qtablewidgetitem20->setText(QApplication::translate("CalcDlgClass", "20", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_3->verticalHeaderItem(1);
        ___qtablewidgetitem21->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270ref", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_3->verticalHeaderItem(2);
        ___qtablewidgetitem22->setText(QApplication::translate("CalcDlgClass", "\316\224\316\270max-5", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("CalcDlgClass", "\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("CalcDlgClass", "\347\224\237\346\210\220\350\241\250\346\240\274", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("CalcDlgClass", "\344\277\235\345\255\230\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("CalcDlgClass", "\351\200\200\345\207\272\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CalcDlgClass: public Ui_CalcDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCVERIFY_H
