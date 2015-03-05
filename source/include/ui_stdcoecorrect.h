/********************************************************************************
** Form generated from reading UI file 'stdcoecorrect.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STDCOECORRECT_H
#define UI_STDCOECORRECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StdCoeCorrectClass
{
public:
    QLabel *label;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLabel *label_8;
    QWidget *widget1;
    QGridLayout *gridLayout_4;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QLabel *label_9;
    QWidget *widget2;
    QGridLayout *gridLayout_5;
    QLabel *label_7;
    QLineEdit *lineEdit_3;
    QLabel *label_10;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QTableWidget *tableWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_7;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *btnExit;

    void setupUi(QWidget *StdCoeCorrectClass)
    {
        if (StdCoeCorrectClass->objectName().isEmpty())
            StdCoeCorrectClass->setObjectName(QString::fromUtf8("StdCoeCorrectClass"));
        StdCoeCorrectClass->setWindowModality(Qt::ApplicationModal);
        StdCoeCorrectClass->resize(1057, 768);
        label = new QLabel(StdCoeCorrectClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(178, 699, 360, 46));
        groupBox_2 = new QGroupBox(StdCoeCorrectClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(178, 11, 868, 67));
        QPalette palette;
        QBrush brush(QColor(0, 85, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        groupBox_2->setPalette(palette);
        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(580, 27, 141, 28));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(725, 27, 131, 28));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        widget = new QWidget(groupBox_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(12, 27, 171, 28));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QPalette palette1;
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_5->setPalette(palette1);

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(lineEdit, 0, 1, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_8->setPalette(palette2);

        gridLayout_2->addWidget(label_8, 0, 2, 1, 1);

        widget1 = new QWidget(groupBox_2);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(200, 27, 171, 28));
        gridLayout_4 = new QGridLayout(widget1);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(widget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_6->setPalette(palette3);

        gridLayout_4->addWidget(label_6, 0, 0, 1, 1);

        lineEdit_2 = new QLineEdit(widget1);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(lineEdit_2, 0, 1, 1, 1);

        label_9 = new QLabel(widget1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_9->setPalette(palette4);

        gridLayout_4->addWidget(label_9, 0, 2, 1, 1);

        widget2 = new QWidget(groupBox_2);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(390, 27, 181, 28));
        gridLayout_5 = new QGridLayout(widget2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(widget2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_7->setPalette(palette5);

        gridLayout_5->addWidget(label_7, 0, 0, 1, 1);

        lineEdit_3 = new QLineEdit(widget2);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        sizePolicy1.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(lineEdit_3, 0, 1, 1, 1);

        label_10 = new QLabel(widget2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_10->setPalette(palette6);

        gridLayout_5->addWidget(label_10, 0, 2, 1, 1);

        groupBox_3 = new QGroupBox(StdCoeCorrectClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(11, 699, 160, 58));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        groupBox_3->setPalette(palette7);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        radioButton_4 = new QRadioButton(groupBox_3);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_4->setPalette(palette8);

        gridLayout_3->addWidget(radioButton_4, 0, 1, 1, 1);

        radioButton_3 = new QRadioButton(groupBox_3);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_3->setPalette(palette9);

        gridLayout_3->addWidget(radioButton_3, 0, 0, 1, 1);

        groupBox = new QGroupBox(StdCoeCorrectClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(11, 11, 149, 58));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        groupBox->setPalette(palette10);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton->setPalette(palette11);

        gridLayout->addWidget(radioButton, 0, 0, 1, 1);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_2->setPalette(palette12);

        gridLayout->addWidget(radioButton_2, 0, 1, 1, 1);

        tableWidget = new QTableWidget(StdCoeCorrectClass);
        if (tableWidget->columnCount() < 10)
            tableWidget->setColumnCount(10);
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
        if (tableWidget->rowCount() < 18)
            tableWidget->setRowCount(18);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(11, 85, 1041, 601));
        tableWidget->setLineWidth(1);
        tableWidget->setAutoScrollMargin(10);
        tableWidget->setRowCount(18);
        layoutWidget = new QWidget(StdCoeCorrectClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(615, 699, 431, 51));
        gridLayout_7 = new QGridLayout(layoutWidget);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        toolButton = new QToolButton(layoutWidget);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy2);

        gridLayout_7->addWidget(toolButton, 0, 0, 1, 1);

        toolButton_2 = new QToolButton(layoutWidget);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        sizePolicy2.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
        toolButton_2->setSizePolicy(sizePolicy2);

        gridLayout_7->addWidget(toolButton_2, 0, 1, 1, 1);

        toolButton_3 = new QToolButton(layoutWidget);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        sizePolicy2.setHeightForWidth(toolButton_3->sizePolicy().hasHeightForWidth());
        toolButton_3->setSizePolicy(sizePolicy2);

        gridLayout_7->addWidget(toolButton_3, 0, 2, 1, 1);

        btnExit = new QToolButton(layoutWidget);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        sizePolicy2.setHeightForWidth(btnExit->sizePolicy().hasHeightForWidth());
        btnExit->setSizePolicy(sizePolicy2);

        gridLayout_7->addWidget(btnExit, 0, 3, 1, 1);

        layoutWidget->raise();
        label->raise();
        groupBox_2->raise();
        groupBox_3->raise();
        groupBox->raise();
        tableWidget->raise();

        retranslateUi(StdCoeCorrectClass);

        QMetaObject::connectSlotsByName(StdCoeCorrectClass);
    } // setupUi

    void retranslateUi(QWidget *StdCoeCorrectClass)
    {
        StdCoeCorrectClass->setWindowTitle(QApplication::translate("StdCoeCorrectClass", "\346\240\207\345\207\206\350\241\250\347\263\273\346\225\260\346\240\207\345\256\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StdCoeCorrectClass", "<html><head/><body><p><span style=\" color:#ff0000;\">\346\217\220\347\244\272\357\274\232\345\246\202\346\236\234\350\246\201\350\277\233\350\241\214K\347\263\273\346\225\260\346\240\207\345\256\232\357\274\214\350\257\267\351\200\211\346\213\251\346\227\240\344\277\256\346\255\243\347\212\266\346\200\201\357\274\233</span></p><p><span style=\" color:#ff0000;\">\345\246\202\346\236\234\350\246\201\351\252\214\350\257\201\346\240\207\345\207\206\350\241\250\344\277\256\346\255\243\345\220\216\347\244\272\345\200\274\345\207\206\347\241\256\345\272\246\357\274\214\350\257\267\351\200\211\346\213\251\344\277\256\346\255\243\347\212\266\346\200\201</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("StdCoeCorrectClass", "\346\240\207\345\207\206\350\241\250\346\230\276\347\244\272\345\200\274\350\256\241\347\256\227", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("StdCoeCorrectClass", "\345\210\235\345\200\274", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("StdCoeCorrectClass", "\346\234\253\345\200\274", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("StdCoeCorrectClass", "\345\210\235\345\200\274", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("StdCoeCorrectClass", "L", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("StdCoeCorrectClass", "\346\234\253\345\200\274", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("StdCoeCorrectClass", "L", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("StdCoeCorrectClass", "\347\244\272\345\200\274", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("StdCoeCorrectClass", "L", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("StdCoeCorrectClass", "\347\212\266\346\200\201\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        radioButton_4->setText(QApplication::translate("StdCoeCorrectClass", "\344\277\256\346\255\243", 0, QApplication::UnicodeUTF8));
        radioButton_3->setText(QApplication::translate("StdCoeCorrectClass", "\346\227\240\344\277\256\346\255\243", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("StdCoeCorrectClass", "\346\240\207\345\207\206\350\241\250\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("StdCoeCorrectClass", "DN10", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("StdCoeCorrectClass", "DN25", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("StdCoeCorrectClass", "\346\265\201\351\207\217\347\202\271\n"
" (kg)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("StdCoeCorrectClass", "\345\244\251\345\271\263\345\210\235\345\200\274\n"
" (kg)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("StdCoeCorrectClass", "\345\244\251\345\271\263\346\234\253\345\200\274\n"
"\357\274\210kg)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("StdCoeCorrectClass", "\345\244\251\345\271\263\347\244\272\345\200\274\n"
" (kg)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("StdCoeCorrectClass", "\345\257\206\345\272\246\345\200\274\n"
"(kg/L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("StdCoeCorrectClass", "\345\256\236\351\231\205\345\200\274\n"
" (L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("StdCoeCorrectClass", "\346\240\207\345\207\206\350\241\250\345\200\274\n"
" \357\274\210L)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("StdCoeCorrectClass", "\344\273\252\350\241\250\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("StdCoeCorrectClass", "\345\271\263\345\235\207\344\273\252\350\241\250\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("StdCoeCorrectClass", "\351\207\215\345\244\215\346\200\247\n"
" (%)", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("StdCoeCorrectClass", "\346\270\205\351\233\266", 0, QApplication::UnicodeUTF8));
        toolButton_2->setText(QApplication::translate("StdCoeCorrectClass", "\347\224\237\346\210\220\350\241\250\346\240\274", 0, QApplication::UnicodeUTF8));
        toolButton_3->setText(QApplication::translate("StdCoeCorrectClass", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("StdCoeCorrectClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StdCoeCorrectClass: public Ui_StdCoeCorrectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STDCOECORRECT_H
