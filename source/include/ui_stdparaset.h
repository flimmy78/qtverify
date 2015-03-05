/********************************************************************************
** Form generated from reading UI file 'stdparaset.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STDPARASET_H
#define UI_STDPARASET_H

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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StdParaSetClass
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_14;
    QLineEdit *lineEdit_16;
    QLineEdit *lineEdit_12;
    QLineEdit *lineEdit_13;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_15;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_20;
    QLineEdit *lineEdit_18;
    QLineEdit *lineEdit_17;
    QLineEdit *lineEdit_19;
    QLabel *label_4;
    QLineEdit *lineEdit_21;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lineEdit_26;
    QLineEdit *lineEdit_27;
    QLineEdit *lineEdit_28;
    QLineEdit *lineEdit_29;
    QLineEdit *lineEdit_30;
    QLineEdit *lineEdit_31;
    QLineEdit *lineEdit_32;
    QLineEdit *lineEdit_33;
    QLineEdit *lineEdit_34;
    QLineEdit *lineEdit_35;
    QLineEdit *lineEdit_36;
    QLineEdit *lineEdit_37;
    QLineEdit *lineEdit_38;
    QLineEdit *lineEdit_39;
    QLineEdit *lineEdit_40;
    QLineEdit *lineEdit_41;
    QLineEdit *lineEdit_42;
    QLineEdit *lineEdit_43;
    QLineEdit *lineEdit_44;
    QLineEdit *lineEdit_45;
    QLabel *label_11;
    QLineEdit *lineEdit_46;
    QLabel *label;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_22;
    QLineEdit *lineEdit_23;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit_24;
    QLineEdit *lineEdit_25;
    QPushButton *pushButton;
    QPushButton *btnExit;

    void setupUi(QWidget *StdParaSetClass)
    {
        if (StdParaSetClass->objectName().isEmpty())
            StdParaSetClass->setObjectName(QString::fromUtf8("StdParaSetClass"));
        StdParaSetClass->setWindowModality(Qt::ApplicationModal);
        StdParaSetClass->resize(570, 591);
        gridLayout_5 = new QGridLayout(StdParaSetClass);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox = new QGroupBox(StdParaSetClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QPalette palette;
        QBrush brush(QColor(0, 85, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        groupBox->setPalette(palette);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        QPalette palette1;
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_2->setPalette(palette1);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_3->setPalette(palette2);

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 2);

        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 2, 0, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 2, 1, 1, 2);

        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        gridLayout->addWidget(lineEdit_5, 3, 0, 1, 1);

        lineEdit_7 = new QLineEdit(groupBox);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        gridLayout->addWidget(lineEdit_7, 3, 1, 1, 2);

        lineEdit_8 = new QLineEdit(groupBox);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));

        gridLayout->addWidget(lineEdit_8, 4, 0, 1, 1);

        lineEdit_6 = new QLineEdit(groupBox);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        gridLayout->addWidget(lineEdit_6, 4, 1, 1, 2);

        lineEdit_11 = new QLineEdit(groupBox);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));

        gridLayout->addWidget(lineEdit_11, 5, 0, 1, 1);

        lineEdit_14 = new QLineEdit(groupBox);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));

        gridLayout->addWidget(lineEdit_14, 5, 1, 1, 2);

        lineEdit_16 = new QLineEdit(groupBox);
        lineEdit_16->setObjectName(QString::fromUtf8("lineEdit_16"));

        gridLayout->addWidget(lineEdit_16, 6, 0, 1, 1);

        lineEdit_12 = new QLineEdit(groupBox);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));

        gridLayout->addWidget(lineEdit_12, 6, 1, 1, 2);

        lineEdit_13 = new QLineEdit(groupBox);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));

        gridLayout->addWidget(lineEdit_13, 7, 0, 1, 1);

        lineEdit_10 = new QLineEdit(groupBox);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));

        gridLayout->addWidget(lineEdit_10, 7, 1, 1, 2);

        lineEdit_15 = new QLineEdit(groupBox);
        lineEdit_15->setObjectName(QString::fromUtf8("lineEdit_15"));

        gridLayout->addWidget(lineEdit_15, 8, 0, 1, 1);

        lineEdit_9 = new QLineEdit(groupBox);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));

        gridLayout->addWidget(lineEdit_9, 8, 1, 1, 2);

        lineEdit_20 = new QLineEdit(groupBox);
        lineEdit_20->setObjectName(QString::fromUtf8("lineEdit_20"));

        gridLayout->addWidget(lineEdit_20, 9, 0, 1, 1);

        lineEdit_18 = new QLineEdit(groupBox);
        lineEdit_18->setObjectName(QString::fromUtf8("lineEdit_18"));

        gridLayout->addWidget(lineEdit_18, 9, 1, 1, 2);

        lineEdit_17 = new QLineEdit(groupBox);
        lineEdit_17->setObjectName(QString::fromUtf8("lineEdit_17"));

        gridLayout->addWidget(lineEdit_17, 10, 0, 1, 1);

        lineEdit_19 = new QLineEdit(groupBox);
        lineEdit_19->setObjectName(QString::fromUtf8("lineEdit_19"));

        gridLayout->addWidget(lineEdit_19, 10, 1, 1, 2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_4->setPalette(palette3);

        gridLayout->addWidget(label_4, 11, 0, 1, 2);

        lineEdit_21 = new QLineEdit(groupBox);
        lineEdit_21->setObjectName(QString::fromUtf8("lineEdit_21"));

        gridLayout->addWidget(lineEdit_21, 11, 2, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_4 = new QGroupBox(StdParaSetClass);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        groupBox_4->setPalette(palette4);
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_9->setPalette(palette5);

        gridLayout_4->addWidget(label_9, 0, 0, 1, 1);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_10->setPalette(palette6);

        gridLayout_4->addWidget(label_10, 0, 1, 1, 1);

        lineEdit_26 = new QLineEdit(groupBox_4);
        lineEdit_26->setObjectName(QString::fromUtf8("lineEdit_26"));

        gridLayout_4->addWidget(lineEdit_26, 1, 0, 1, 1);

        lineEdit_27 = new QLineEdit(groupBox_4);
        lineEdit_27->setObjectName(QString::fromUtf8("lineEdit_27"));

        gridLayout_4->addWidget(lineEdit_27, 1, 1, 1, 2);

        lineEdit_28 = new QLineEdit(groupBox_4);
        lineEdit_28->setObjectName(QString::fromUtf8("lineEdit_28"));

        gridLayout_4->addWidget(lineEdit_28, 2, 0, 1, 1);

        lineEdit_29 = new QLineEdit(groupBox_4);
        lineEdit_29->setObjectName(QString::fromUtf8("lineEdit_29"));

        gridLayout_4->addWidget(lineEdit_29, 2, 1, 1, 2);

        lineEdit_30 = new QLineEdit(groupBox_4);
        lineEdit_30->setObjectName(QString::fromUtf8("lineEdit_30"));

        gridLayout_4->addWidget(lineEdit_30, 3, 0, 1, 1);

        lineEdit_31 = new QLineEdit(groupBox_4);
        lineEdit_31->setObjectName(QString::fromUtf8("lineEdit_31"));

        gridLayout_4->addWidget(lineEdit_31, 3, 1, 1, 2);

        lineEdit_32 = new QLineEdit(groupBox_4);
        lineEdit_32->setObjectName(QString::fromUtf8("lineEdit_32"));

        gridLayout_4->addWidget(lineEdit_32, 4, 0, 1, 1);

        lineEdit_33 = new QLineEdit(groupBox_4);
        lineEdit_33->setObjectName(QString::fromUtf8("lineEdit_33"));

        gridLayout_4->addWidget(lineEdit_33, 4, 1, 1, 2);

        lineEdit_34 = new QLineEdit(groupBox_4);
        lineEdit_34->setObjectName(QString::fromUtf8("lineEdit_34"));

        gridLayout_4->addWidget(lineEdit_34, 5, 0, 1, 1);

        lineEdit_35 = new QLineEdit(groupBox_4);
        lineEdit_35->setObjectName(QString::fromUtf8("lineEdit_35"));

        gridLayout_4->addWidget(lineEdit_35, 5, 1, 1, 2);

        lineEdit_36 = new QLineEdit(groupBox_4);
        lineEdit_36->setObjectName(QString::fromUtf8("lineEdit_36"));

        gridLayout_4->addWidget(lineEdit_36, 6, 0, 1, 1);

        lineEdit_37 = new QLineEdit(groupBox_4);
        lineEdit_37->setObjectName(QString::fromUtf8("lineEdit_37"));

        gridLayout_4->addWidget(lineEdit_37, 6, 1, 1, 2);

        lineEdit_38 = new QLineEdit(groupBox_4);
        lineEdit_38->setObjectName(QString::fromUtf8("lineEdit_38"));

        gridLayout_4->addWidget(lineEdit_38, 7, 0, 1, 1);

        lineEdit_39 = new QLineEdit(groupBox_4);
        lineEdit_39->setObjectName(QString::fromUtf8("lineEdit_39"));

        gridLayout_4->addWidget(lineEdit_39, 7, 1, 1, 2);

        lineEdit_40 = new QLineEdit(groupBox_4);
        lineEdit_40->setObjectName(QString::fromUtf8("lineEdit_40"));

        gridLayout_4->addWidget(lineEdit_40, 8, 0, 1, 1);

        lineEdit_41 = new QLineEdit(groupBox_4);
        lineEdit_41->setObjectName(QString::fromUtf8("lineEdit_41"));

        gridLayout_4->addWidget(lineEdit_41, 8, 1, 1, 2);

        lineEdit_42 = new QLineEdit(groupBox_4);
        lineEdit_42->setObjectName(QString::fromUtf8("lineEdit_42"));

        gridLayout_4->addWidget(lineEdit_42, 9, 0, 1, 1);

        lineEdit_43 = new QLineEdit(groupBox_4);
        lineEdit_43->setObjectName(QString::fromUtf8("lineEdit_43"));

        gridLayout_4->addWidget(lineEdit_43, 9, 1, 1, 2);

        lineEdit_44 = new QLineEdit(groupBox_4);
        lineEdit_44->setObjectName(QString::fromUtf8("lineEdit_44"));

        gridLayout_4->addWidget(lineEdit_44, 10, 0, 1, 1);

        lineEdit_45 = new QLineEdit(groupBox_4);
        lineEdit_45->setObjectName(QString::fromUtf8("lineEdit_45"));

        gridLayout_4->addWidget(lineEdit_45, 10, 1, 1, 2);

        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_11->setPalette(palette7);

        gridLayout_4->addWidget(label_11, 11, 0, 1, 2);

        lineEdit_46 = new QLineEdit(groupBox_4);
        lineEdit_46->setObjectName(QString::fromUtf8("lineEdit_46"));

        gridLayout_4->addWidget(lineEdit_46, 11, 2, 1, 1);


        gridLayout_5->addWidget(groupBox_4, 0, 1, 1, 1);

        label = new QLabel(StdParaSetClass);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_5->addWidget(label, 1, 0, 1, 2);

        groupBox_2 = new QGroupBox(StdParaSetClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        groupBox_2->setPalette(palette8);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_5->setPalette(palette9);

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_6->setPalette(palette10);

        gridLayout_2->addWidget(label_6, 0, 1, 1, 1);

        lineEdit_22 = new QLineEdit(groupBox_2);
        lineEdit_22->setObjectName(QString::fromUtf8("lineEdit_22"));

        gridLayout_2->addWidget(lineEdit_22, 1, 0, 1, 1);

        lineEdit_23 = new QLineEdit(groupBox_2);
        lineEdit_23->setObjectName(QString::fromUtf8("lineEdit_23"));

        gridLayout_2->addWidget(lineEdit_23, 1, 1, 1, 1);


        gridLayout_5->addWidget(groupBox_2, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(StdParaSetClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        groupBox_3->setPalette(palette11);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_7->setPalette(palette12);

        gridLayout_3->addWidget(label_7, 0, 0, 1, 1);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette13.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette13.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_8->setPalette(palette13);

        gridLayout_3->addWidget(label_8, 0, 1, 1, 1);

        lineEdit_24 = new QLineEdit(groupBox_3);
        lineEdit_24->setObjectName(QString::fromUtf8("lineEdit_24"));

        gridLayout_3->addWidget(lineEdit_24, 1, 0, 1, 1);

        lineEdit_25 = new QLineEdit(groupBox_3);
        lineEdit_25->setObjectName(QString::fromUtf8("lineEdit_25"));

        gridLayout_3->addWidget(lineEdit_25, 1, 1, 1, 1);


        gridLayout_5->addWidget(groupBox_3, 2, 1, 1, 1);

        pushButton = new QPushButton(StdParaSetClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_5->addWidget(pushButton, 3, 0, 1, 1);

        btnExit = new QPushButton(StdParaSetClass);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));

        gridLayout_5->addWidget(btnExit, 3, 1, 1, 1);


        retranslateUi(StdParaSetClass);

        QMetaObject::connectSlotsByName(StdParaSetClass);
    } // setupUi

    void retranslateUi(QWidget *StdParaSetClass)
    {
        StdParaSetClass->setWindowTitle(QApplication::translate("StdParaSetClass", "\346\240\207\345\207\206\350\241\250\345\217\202\346\225\260\350\256\276\345\256\232", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("StdParaSetClass", "DN10\350\241\250\344\275\223\347\247\257\344\273\252\350\241\250\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("StdParaSetClass", "\346\265\201\351\207\217\347\202\271(m\302\263/h)", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("StdParaSetClass", "K\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("StdParaSetClass", "\350\204\211\345\206\262\345\275\223\351\207\217(\345\215\207/\350\204\211\345\206\262):", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("StdParaSetClass", "DN25\350\241\250\344\275\223\347\247\257\344\273\252\350\241\250\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("StdParaSetClass", "\346\265\201\351\207\217\347\202\271(m\302\263/h)", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("StdParaSetClass", "K\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("StdParaSetClass", "\350\204\211\345\206\262\345\275\223\351\207\217(\345\215\207/\350\204\211\345\206\262):", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StdParaSetClass", "<html><head/><body><p><span style=\" color:#ff0000;\">\346\263\250:\346\265\201\351\207\217\344\273\216\345\260\217\345\210\260\345\244\247\350\276\223\345\205\245\357\274\214\346\234\200\345\244\247\346\265\201\351\207\217\345\217\257\344\270\216\344\270\212\351\231\220\346\265\201\351\207\217\347\233\270\345\220\214\343\200\202\344\270\244\344\270\252\346\265\201\351\207\217\347\202\271\344\271\213\351\227\264\344\270\215\350\203\275\346\234\211\347\251\272\346\240\274\357\274\201</span></p><p><span style=\" color:#ff0000;\">K\347\263\273\346\225\260\344\270\272\357\274\232\346\240\207\345\207\206\345\200\274/\346\230\276\347\244\272\345\200\274</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("StdParaSetClass", "DN10\350\241\250\346\265\201\351\200\237\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("StdParaSetClass", "\344\270\212\351\231\220\346\265\201\351\207\217(m\302\263/h)", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("StdParaSetClass", "\344\277\256\346\255\243\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("StdParaSetClass", "DN25\350\241\250\346\265\201\351\200\237\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("StdParaSetClass", "\344\270\212\351\231\220\346\265\201\351\207\217(m\302\263/h)", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("StdParaSetClass", "\344\277\256\346\255\243\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("StdParaSetClass", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("StdParaSetClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StdParaSetClass: public Ui_StdParaSetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STDPARASET_H
