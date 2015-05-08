/********************************************************************************
** Form generated from reading UI file 'tverparam.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TVERPARAM_H
#define UI_TVERPARAM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlaParamDlgClass
{
public:
    QFrame *frame_2;
    QLabel *label_23;
    QGroupBox *groupBox_8;
    QTableWidget *tbl_result;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_6;
    QFrame *frame_3;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_24;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_26;
    QLineEdit *lineEdit_1;
    QFrame *frame_5;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_28;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_29;
    QLineEdit *lineEdit_2;
    QFrame *frame_6;
    QWidget *widget3;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_30;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_31;
    QLineEdit *lineEdit_3;
    QGroupBox *groupBox_9;
    QTableWidget *tbl_maxerr;
    QFrame *frame;
    QLabel *label;
    QGroupBox *groupBox;
    QLabel *label_2;
    QTableWidget *tbl_std_1;
    QWidget *widget4;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_read_1;
    QSpacerItem *verticalSpacer;
    QPushButton *btn_clear_1;
    QWidget *widget5;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLabel *label_4;
    QTableWidget *tbl_in_1;
    QGroupBox *groupBox_2;
    QLabel *label_5;
    QTableWidget *tbl_std_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_8;
    QPushButton *btn_read_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btn_clear_2;
    QWidget *widget6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_11;
    QLabel *label_12;
    QTableWidget *tbl_in_2;
    QGroupBox *groupBox_7;
    QLabel *label_20;
    QTableWidget *tbl_std_3;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_9;
    QPushButton *btn_read_3;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btn_clear_3;
    QWidget *widget7;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_21;
    QLabel *label_22;
    QTableWidget *tbl_in_3;
    QWidget *widget8;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget9;
    QGridLayout *gridLayout;
    QWidget *widget10;
    QHBoxLayout *horizontalLayout;
    QLabel *label_27;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_param;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_save;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_exit;

    void setupUi(QWidget *PlaParamDlgClass)
    {
        if (PlaParamDlgClass->objectName().isEmpty())
            PlaParamDlgClass->setObjectName(QString::fromUtf8("PlaParamDlgClass"));
        PlaParamDlgClass->resize(1320, 715);
        PlaParamDlgClass->setMinimumSize(QSize(1320, 715));
        PlaParamDlgClass->setMaximumSize(QSize(1320, 715));
        frame_2 = new QFrame(PlaParamDlgClass);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(650, 10, 661, 651));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_23 = new QLabel(frame_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(290, 0, 101, 16));
        groupBox_8 = new QGroupBox(frame_2);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 130, 491, 511));
        tbl_result = new QTableWidget(groupBox_8);
        if (tbl_result->columnCount() < 12)
            tbl_result->setColumnCount(12);
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        tbl_result->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(8);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        tbl_result->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font1);
        tbl_result->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font1);
        tbl_result->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font1);
        tbl_result->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font1);
        tbl_result->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font1);
        tbl_result->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font1);
        tbl_result->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font1);
        tbl_result->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font1);
        tbl_result->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font1);
        tbl_result->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font1);
        tbl_result->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        if (tbl_result->rowCount() < 12)
            tbl_result->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(5, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(6, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(7, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(8, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(9, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(10, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(11, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tbl_result->setItem(0, 0, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tbl_result->setItem(0, 1, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tbl_result->setItem(0, 2, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tbl_result->setItem(0, 3, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tbl_result->setItem(0, 4, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tbl_result->setItem(0, 5, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tbl_result->setItem(0, 6, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tbl_result->setItem(0, 7, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tbl_result->setItem(0, 8, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tbl_result->setItem(0, 9, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tbl_result->setItem(0, 10, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tbl_result->setItem(0, 11, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tbl_result->setItem(1, 0, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tbl_result->setItem(1, 1, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tbl_result->setItem(1, 2, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tbl_result->setItem(1, 3, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tbl_result->setItem(1, 4, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tbl_result->setItem(1, 5, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tbl_result->setItem(1, 6, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tbl_result->setItem(1, 7, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tbl_result->setItem(1, 8, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tbl_result->setItem(1, 9, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tbl_result->setItem(1, 10, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tbl_result->setItem(1, 11, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tbl_result->setItem(2, 0, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tbl_result->setItem(2, 1, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tbl_result->setItem(2, 2, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tbl_result->setItem(2, 3, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tbl_result->setItem(2, 4, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tbl_result->setItem(2, 5, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tbl_result->setItem(2, 6, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tbl_result->setItem(2, 7, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tbl_result->setItem(2, 8, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tbl_result->setItem(2, 9, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tbl_result->setItem(2, 10, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tbl_result->setItem(2, 11, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        tbl_result->setItem(3, 0, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        tbl_result->setItem(3, 1, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        tbl_result->setItem(3, 2, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        tbl_result->setItem(3, 3, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        tbl_result->setItem(3, 4, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        tbl_result->setItem(3, 5, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        tbl_result->setItem(3, 6, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        tbl_result->setItem(3, 7, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        tbl_result->setItem(3, 8, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        tbl_result->setItem(3, 9, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        tbl_result->setItem(3, 10, __qtablewidgetitem70);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        tbl_result->setItem(3, 11, __qtablewidgetitem71);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        tbl_result->setItem(4, 0, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        tbl_result->setItem(4, 1, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        tbl_result->setItem(4, 2, __qtablewidgetitem74);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        tbl_result->setItem(4, 3, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        tbl_result->setItem(4, 4, __qtablewidgetitem76);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        tbl_result->setItem(4, 5, __qtablewidgetitem77);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        tbl_result->setItem(4, 6, __qtablewidgetitem78);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        tbl_result->setItem(4, 7, __qtablewidgetitem79);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        tbl_result->setItem(4, 8, __qtablewidgetitem80);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        tbl_result->setItem(4, 9, __qtablewidgetitem81);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        tbl_result->setItem(4, 10, __qtablewidgetitem82);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        tbl_result->setItem(4, 11, __qtablewidgetitem83);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        tbl_result->setItem(5, 0, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        tbl_result->setItem(5, 1, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        tbl_result->setItem(5, 2, __qtablewidgetitem86);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        tbl_result->setItem(5, 3, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        tbl_result->setItem(5, 4, __qtablewidgetitem88);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        tbl_result->setItem(5, 5, __qtablewidgetitem89);
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        tbl_result->setItem(5, 6, __qtablewidgetitem90);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        tbl_result->setItem(5, 7, __qtablewidgetitem91);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        tbl_result->setItem(5, 8, __qtablewidgetitem92);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        tbl_result->setItem(5, 9, __qtablewidgetitem93);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        tbl_result->setItem(5, 10, __qtablewidgetitem94);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        tbl_result->setItem(5, 11, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        tbl_result->setItem(6, 0, __qtablewidgetitem96);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        tbl_result->setItem(6, 1, __qtablewidgetitem97);
        QTableWidgetItem *__qtablewidgetitem98 = new QTableWidgetItem();
        tbl_result->setItem(6, 2, __qtablewidgetitem98);
        QTableWidgetItem *__qtablewidgetitem99 = new QTableWidgetItem();
        tbl_result->setItem(6, 3, __qtablewidgetitem99);
        QTableWidgetItem *__qtablewidgetitem100 = new QTableWidgetItem();
        tbl_result->setItem(6, 4, __qtablewidgetitem100);
        QTableWidgetItem *__qtablewidgetitem101 = new QTableWidgetItem();
        tbl_result->setItem(6, 5, __qtablewidgetitem101);
        QTableWidgetItem *__qtablewidgetitem102 = new QTableWidgetItem();
        tbl_result->setItem(6, 6, __qtablewidgetitem102);
        QTableWidgetItem *__qtablewidgetitem103 = new QTableWidgetItem();
        tbl_result->setItem(6, 7, __qtablewidgetitem103);
        QTableWidgetItem *__qtablewidgetitem104 = new QTableWidgetItem();
        tbl_result->setItem(6, 8, __qtablewidgetitem104);
        QTableWidgetItem *__qtablewidgetitem105 = new QTableWidgetItem();
        tbl_result->setItem(6, 9, __qtablewidgetitem105);
        QTableWidgetItem *__qtablewidgetitem106 = new QTableWidgetItem();
        tbl_result->setItem(6, 10, __qtablewidgetitem106);
        QTableWidgetItem *__qtablewidgetitem107 = new QTableWidgetItem();
        tbl_result->setItem(6, 11, __qtablewidgetitem107);
        QTableWidgetItem *__qtablewidgetitem108 = new QTableWidgetItem();
        tbl_result->setItem(7, 0, __qtablewidgetitem108);
        QTableWidgetItem *__qtablewidgetitem109 = new QTableWidgetItem();
        tbl_result->setItem(7, 1, __qtablewidgetitem109);
        QTableWidgetItem *__qtablewidgetitem110 = new QTableWidgetItem();
        tbl_result->setItem(7, 2, __qtablewidgetitem110);
        QTableWidgetItem *__qtablewidgetitem111 = new QTableWidgetItem();
        tbl_result->setItem(7, 3, __qtablewidgetitem111);
        QTableWidgetItem *__qtablewidgetitem112 = new QTableWidgetItem();
        tbl_result->setItem(7, 4, __qtablewidgetitem112);
        QTableWidgetItem *__qtablewidgetitem113 = new QTableWidgetItem();
        tbl_result->setItem(7, 5, __qtablewidgetitem113);
        QTableWidgetItem *__qtablewidgetitem114 = new QTableWidgetItem();
        tbl_result->setItem(7, 6, __qtablewidgetitem114);
        QTableWidgetItem *__qtablewidgetitem115 = new QTableWidgetItem();
        tbl_result->setItem(7, 7, __qtablewidgetitem115);
        QTableWidgetItem *__qtablewidgetitem116 = new QTableWidgetItem();
        tbl_result->setItem(7, 8, __qtablewidgetitem116);
        QTableWidgetItem *__qtablewidgetitem117 = new QTableWidgetItem();
        tbl_result->setItem(7, 9, __qtablewidgetitem117);
        QTableWidgetItem *__qtablewidgetitem118 = new QTableWidgetItem();
        tbl_result->setItem(7, 10, __qtablewidgetitem118);
        QTableWidgetItem *__qtablewidgetitem119 = new QTableWidgetItem();
        tbl_result->setItem(7, 11, __qtablewidgetitem119);
        QTableWidgetItem *__qtablewidgetitem120 = new QTableWidgetItem();
        tbl_result->setItem(8, 0, __qtablewidgetitem120);
        QTableWidgetItem *__qtablewidgetitem121 = new QTableWidgetItem();
        tbl_result->setItem(8, 1, __qtablewidgetitem121);
        QTableWidgetItem *__qtablewidgetitem122 = new QTableWidgetItem();
        tbl_result->setItem(8, 2, __qtablewidgetitem122);
        QTableWidgetItem *__qtablewidgetitem123 = new QTableWidgetItem();
        tbl_result->setItem(8, 3, __qtablewidgetitem123);
        QTableWidgetItem *__qtablewidgetitem124 = new QTableWidgetItem();
        tbl_result->setItem(8, 4, __qtablewidgetitem124);
        QTableWidgetItem *__qtablewidgetitem125 = new QTableWidgetItem();
        tbl_result->setItem(8, 5, __qtablewidgetitem125);
        QTableWidgetItem *__qtablewidgetitem126 = new QTableWidgetItem();
        tbl_result->setItem(8, 6, __qtablewidgetitem126);
        QTableWidgetItem *__qtablewidgetitem127 = new QTableWidgetItem();
        tbl_result->setItem(8, 7, __qtablewidgetitem127);
        QTableWidgetItem *__qtablewidgetitem128 = new QTableWidgetItem();
        tbl_result->setItem(8, 8, __qtablewidgetitem128);
        QTableWidgetItem *__qtablewidgetitem129 = new QTableWidgetItem();
        tbl_result->setItem(8, 9, __qtablewidgetitem129);
        QTableWidgetItem *__qtablewidgetitem130 = new QTableWidgetItem();
        tbl_result->setItem(8, 10, __qtablewidgetitem130);
        QTableWidgetItem *__qtablewidgetitem131 = new QTableWidgetItem();
        tbl_result->setItem(8, 11, __qtablewidgetitem131);
        QTableWidgetItem *__qtablewidgetitem132 = new QTableWidgetItem();
        tbl_result->setItem(9, 0, __qtablewidgetitem132);
        QTableWidgetItem *__qtablewidgetitem133 = new QTableWidgetItem();
        tbl_result->setItem(9, 1, __qtablewidgetitem133);
        QTableWidgetItem *__qtablewidgetitem134 = new QTableWidgetItem();
        tbl_result->setItem(9, 2, __qtablewidgetitem134);
        QTableWidgetItem *__qtablewidgetitem135 = new QTableWidgetItem();
        tbl_result->setItem(9, 3, __qtablewidgetitem135);
        QTableWidgetItem *__qtablewidgetitem136 = new QTableWidgetItem();
        tbl_result->setItem(9, 4, __qtablewidgetitem136);
        QTableWidgetItem *__qtablewidgetitem137 = new QTableWidgetItem();
        tbl_result->setItem(9, 5, __qtablewidgetitem137);
        QTableWidgetItem *__qtablewidgetitem138 = new QTableWidgetItem();
        tbl_result->setItem(9, 6, __qtablewidgetitem138);
        QTableWidgetItem *__qtablewidgetitem139 = new QTableWidgetItem();
        tbl_result->setItem(9, 7, __qtablewidgetitem139);
        QTableWidgetItem *__qtablewidgetitem140 = new QTableWidgetItem();
        tbl_result->setItem(9, 8, __qtablewidgetitem140);
        QTableWidgetItem *__qtablewidgetitem141 = new QTableWidgetItem();
        tbl_result->setItem(9, 9, __qtablewidgetitem141);
        QTableWidgetItem *__qtablewidgetitem142 = new QTableWidgetItem();
        tbl_result->setItem(9, 10, __qtablewidgetitem142);
        QTableWidgetItem *__qtablewidgetitem143 = new QTableWidgetItem();
        tbl_result->setItem(9, 11, __qtablewidgetitem143);
        QTableWidgetItem *__qtablewidgetitem144 = new QTableWidgetItem();
        tbl_result->setItem(10, 0, __qtablewidgetitem144);
        QTableWidgetItem *__qtablewidgetitem145 = new QTableWidgetItem();
        tbl_result->setItem(10, 1, __qtablewidgetitem145);
        QTableWidgetItem *__qtablewidgetitem146 = new QTableWidgetItem();
        tbl_result->setItem(10, 2, __qtablewidgetitem146);
        QTableWidgetItem *__qtablewidgetitem147 = new QTableWidgetItem();
        tbl_result->setItem(10, 3, __qtablewidgetitem147);
        QTableWidgetItem *__qtablewidgetitem148 = new QTableWidgetItem();
        tbl_result->setItem(10, 4, __qtablewidgetitem148);
        QTableWidgetItem *__qtablewidgetitem149 = new QTableWidgetItem();
        tbl_result->setItem(10, 5, __qtablewidgetitem149);
        QTableWidgetItem *__qtablewidgetitem150 = new QTableWidgetItem();
        tbl_result->setItem(10, 6, __qtablewidgetitem150);
        QTableWidgetItem *__qtablewidgetitem151 = new QTableWidgetItem();
        tbl_result->setItem(10, 7, __qtablewidgetitem151);
        QTableWidgetItem *__qtablewidgetitem152 = new QTableWidgetItem();
        tbl_result->setItem(10, 8, __qtablewidgetitem152);
        QTableWidgetItem *__qtablewidgetitem153 = new QTableWidgetItem();
        tbl_result->setItem(10, 9, __qtablewidgetitem153);
        QTableWidgetItem *__qtablewidgetitem154 = new QTableWidgetItem();
        tbl_result->setItem(10, 10, __qtablewidgetitem154);
        QTableWidgetItem *__qtablewidgetitem155 = new QTableWidgetItem();
        tbl_result->setItem(10, 11, __qtablewidgetitem155);
        QTableWidgetItem *__qtablewidgetitem156 = new QTableWidgetItem();
        tbl_result->setItem(11, 0, __qtablewidgetitem156);
        QTableWidgetItem *__qtablewidgetitem157 = new QTableWidgetItem();
        tbl_result->setItem(11, 1, __qtablewidgetitem157);
        QTableWidgetItem *__qtablewidgetitem158 = new QTableWidgetItem();
        tbl_result->setItem(11, 2, __qtablewidgetitem158);
        QTableWidgetItem *__qtablewidgetitem159 = new QTableWidgetItem();
        tbl_result->setItem(11, 3, __qtablewidgetitem159);
        QTableWidgetItem *__qtablewidgetitem160 = new QTableWidgetItem();
        tbl_result->setItem(11, 4, __qtablewidgetitem160);
        QTableWidgetItem *__qtablewidgetitem161 = new QTableWidgetItem();
        tbl_result->setItem(11, 5, __qtablewidgetitem161);
        QTableWidgetItem *__qtablewidgetitem162 = new QTableWidgetItem();
        tbl_result->setItem(11, 6, __qtablewidgetitem162);
        QTableWidgetItem *__qtablewidgetitem163 = new QTableWidgetItem();
        tbl_result->setItem(11, 7, __qtablewidgetitem163);
        QTableWidgetItem *__qtablewidgetitem164 = new QTableWidgetItem();
        tbl_result->setItem(11, 8, __qtablewidgetitem164);
        QTableWidgetItem *__qtablewidgetitem165 = new QTableWidgetItem();
        tbl_result->setItem(11, 9, __qtablewidgetitem165);
        QTableWidgetItem *__qtablewidgetitem166 = new QTableWidgetItem();
        tbl_result->setItem(11, 10, __qtablewidgetitem166);
        QTableWidgetItem *__qtablewidgetitem167 = new QTableWidgetItem();
        tbl_result->setItem(11, 11, __qtablewidgetitem167);
        tbl_result->setObjectName(QString::fromUtf8("tbl_result"));
        tbl_result->setEnabled(false);
        tbl_result->setGeometry(QRect(10, 100, 471, 401));
        tbl_result->horizontalHeader()->setVisible(true);
        tbl_result->horizontalHeader()->setCascadingSectionResizes(false);
        tbl_result->horizontalHeader()->setDefaultSectionSize(38);
        tbl_result->horizontalHeader()->setMinimumSectionSize(10);
        tbl_result->verticalHeader()->setCascadingSectionResizes(true);
        tbl_result->verticalHeader()->setMinimumSectionSize(10);
        widget = new QWidget(groupBox_8);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 30, 451, 51));
        horizontalLayout_6 = new QHBoxLayout(widget);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        frame_3 = new QFrame(widget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        widget1 = new QWidget(frame_3);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(0, 0, 141, 43));
        verticalLayout_5 = new QVBoxLayout(widget1);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_24 = new QLabel(widget1);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        verticalLayout_5->addWidget(label_24);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_26 = new QLabel(widget1);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        horizontalLayout_2->addWidget(label_26);

        lineEdit_1 = new QLineEdit(widget1);
        lineEdit_1->setObjectName(QString::fromUtf8("lineEdit_1"));
        lineEdit_1->setEnabled(false);
        sizePolicy.setHeightForWidth(lineEdit_1->sizePolicy().hasHeightForWidth());
        lineEdit_1->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEdit_1);


        verticalLayout_5->addLayout(horizontalLayout_2);


        horizontalLayout_6->addWidget(frame_3);

        frame_5 = new QFrame(widget);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        widget2 = new QWidget(frame_5);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(0, 0, 141, 41));
        verticalLayout_6 = new QVBoxLayout(widget2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_28 = new QLabel(widget2);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        verticalLayout_6->addWidget(label_28);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_29 = new QLabel(widget2);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        horizontalLayout_3->addWidget(label_29);

        lineEdit_2 = new QLineEdit(widget2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setEnabled(false);
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(lineEdit_2);


        verticalLayout_6->addLayout(horizontalLayout_3);


        horizontalLayout_6->addWidget(frame_5);

        frame_6 = new QFrame(widget);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        widget3 = new QWidget(frame_6);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        widget3->setGeometry(QRect(0, 0, 141, 41));
        verticalLayout_7 = new QVBoxLayout(widget3);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_30 = new QLabel(widget3);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        verticalLayout_7->addWidget(label_30);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_31 = new QLabel(widget3);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        horizontalLayout_4->addWidget(label_31);

        lineEdit_3 = new QLineEdit(widget3);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setEnabled(false);
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(lineEdit_3);


        verticalLayout_7->addLayout(horizontalLayout_4);


        horizontalLayout_6->addWidget(frame_6);

        groupBox_9 = new QGroupBox(frame_2);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(510, 190, 141, 451));
        tbl_maxerr = new QTableWidget(groupBox_9);
        if (tbl_maxerr->columnCount() < 2)
            tbl_maxerr->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem168 = new QTableWidgetItem();
        tbl_maxerr->setHorizontalHeaderItem(0, __qtablewidgetitem168);
        QTableWidgetItem *__qtablewidgetitem169 = new QTableWidgetItem();
        tbl_maxerr->setHorizontalHeaderItem(1, __qtablewidgetitem169);
        if (tbl_maxerr->rowCount() < 12)
            tbl_maxerr->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem170 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(0, __qtablewidgetitem170);
        QTableWidgetItem *__qtablewidgetitem171 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(1, __qtablewidgetitem171);
        QTableWidgetItem *__qtablewidgetitem172 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(2, __qtablewidgetitem172);
        QTableWidgetItem *__qtablewidgetitem173 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(3, __qtablewidgetitem173);
        QTableWidgetItem *__qtablewidgetitem174 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(4, __qtablewidgetitem174);
        QTableWidgetItem *__qtablewidgetitem175 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(5, __qtablewidgetitem175);
        QTableWidgetItem *__qtablewidgetitem176 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(6, __qtablewidgetitem176);
        QTableWidgetItem *__qtablewidgetitem177 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(7, __qtablewidgetitem177);
        QTableWidgetItem *__qtablewidgetitem178 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(8, __qtablewidgetitem178);
        QTableWidgetItem *__qtablewidgetitem179 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(9, __qtablewidgetitem179);
        QTableWidgetItem *__qtablewidgetitem180 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(10, __qtablewidgetitem180);
        QTableWidgetItem *__qtablewidgetitem181 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(11, __qtablewidgetitem181);
        QTableWidgetItem *__qtablewidgetitem182 = new QTableWidgetItem();
        tbl_maxerr->setItem(0, 0, __qtablewidgetitem182);
        QTableWidgetItem *__qtablewidgetitem183 = new QTableWidgetItem();
        tbl_maxerr->setItem(0, 1, __qtablewidgetitem183);
        QTableWidgetItem *__qtablewidgetitem184 = new QTableWidgetItem();
        tbl_maxerr->setItem(1, 0, __qtablewidgetitem184);
        QTableWidgetItem *__qtablewidgetitem185 = new QTableWidgetItem();
        tbl_maxerr->setItem(1, 1, __qtablewidgetitem185);
        QTableWidgetItem *__qtablewidgetitem186 = new QTableWidgetItem();
        tbl_maxerr->setItem(2, 0, __qtablewidgetitem186);
        QTableWidgetItem *__qtablewidgetitem187 = new QTableWidgetItem();
        tbl_maxerr->setItem(2, 1, __qtablewidgetitem187);
        QTableWidgetItem *__qtablewidgetitem188 = new QTableWidgetItem();
        tbl_maxerr->setItem(3, 0, __qtablewidgetitem188);
        QTableWidgetItem *__qtablewidgetitem189 = new QTableWidgetItem();
        tbl_maxerr->setItem(3, 1, __qtablewidgetitem189);
        QTableWidgetItem *__qtablewidgetitem190 = new QTableWidgetItem();
        tbl_maxerr->setItem(4, 0, __qtablewidgetitem190);
        QTableWidgetItem *__qtablewidgetitem191 = new QTableWidgetItem();
        tbl_maxerr->setItem(4, 1, __qtablewidgetitem191);
        QTableWidgetItem *__qtablewidgetitem192 = new QTableWidgetItem();
        tbl_maxerr->setItem(5, 0, __qtablewidgetitem192);
        QTableWidgetItem *__qtablewidgetitem193 = new QTableWidgetItem();
        tbl_maxerr->setItem(5, 1, __qtablewidgetitem193);
        QTableWidgetItem *__qtablewidgetitem194 = new QTableWidgetItem();
        tbl_maxerr->setItem(6, 0, __qtablewidgetitem194);
        QTableWidgetItem *__qtablewidgetitem195 = new QTableWidgetItem();
        tbl_maxerr->setItem(6, 1, __qtablewidgetitem195);
        QTableWidgetItem *__qtablewidgetitem196 = new QTableWidgetItem();
        tbl_maxerr->setItem(7, 0, __qtablewidgetitem196);
        QTableWidgetItem *__qtablewidgetitem197 = new QTableWidgetItem();
        tbl_maxerr->setItem(7, 1, __qtablewidgetitem197);
        QTableWidgetItem *__qtablewidgetitem198 = new QTableWidgetItem();
        tbl_maxerr->setItem(8, 0, __qtablewidgetitem198);
        QTableWidgetItem *__qtablewidgetitem199 = new QTableWidgetItem();
        tbl_maxerr->setItem(8, 1, __qtablewidgetitem199);
        QTableWidgetItem *__qtablewidgetitem200 = new QTableWidgetItem();
        tbl_maxerr->setItem(9, 0, __qtablewidgetitem200);
        QTableWidgetItem *__qtablewidgetitem201 = new QTableWidgetItem();
        tbl_maxerr->setItem(9, 1, __qtablewidgetitem201);
        QTableWidgetItem *__qtablewidgetitem202 = new QTableWidgetItem();
        tbl_maxerr->setItem(10, 0, __qtablewidgetitem202);
        QTableWidgetItem *__qtablewidgetitem203 = new QTableWidgetItem();
        tbl_maxerr->setItem(10, 1, __qtablewidgetitem203);
        QTableWidgetItem *__qtablewidgetitem204 = new QTableWidgetItem();
        tbl_maxerr->setItem(11, 0, __qtablewidgetitem204);
        QTableWidgetItem *__qtablewidgetitem205 = new QTableWidgetItem();
        tbl_maxerr->setItem(11, 1, __qtablewidgetitem205);
        tbl_maxerr->setObjectName(QString::fromUtf8("tbl_maxerr"));
        tbl_maxerr->setEnabled(false);
        tbl_maxerr->setGeometry(QRect(10, 20, 121, 421));
        tbl_maxerr->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_maxerr->horizontalHeader()->setDefaultSectionSize(50);
        tbl_maxerr->horizontalHeader()->setMinimumSectionSize(10);
        tbl_maxerr->verticalHeader()->setCascadingSectionResizes(true);
        tbl_maxerr->verticalHeader()->setMinimumSectionSize(10);
        frame = new QFrame(PlaParamDlgClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 631, 651));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(290, 0, 101, 16));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 30, 191, 611));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 20, 121, 16));
        tbl_std_1 = new QTableWidget(groupBox);
        if (tbl_std_1->columnCount() < 1)
            tbl_std_1->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem206 = new QTableWidgetItem();
        tbl_std_1->setHorizontalHeaderItem(0, __qtablewidgetitem206);
        if (tbl_std_1->rowCount() < 2)
            tbl_std_1->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem207 = new QTableWidgetItem();
        tbl_std_1->setVerticalHeaderItem(0, __qtablewidgetitem207);
        QTableWidgetItem *__qtablewidgetitem208 = new QTableWidgetItem();
        tbl_std_1->setVerticalHeaderItem(1, __qtablewidgetitem208);
        QTableWidgetItem *__qtablewidgetitem209 = new QTableWidgetItem();
        __qtablewidgetitem209->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_1->setItem(0, 0, __qtablewidgetitem209);
        QTableWidgetItem *__qtablewidgetitem210 = new QTableWidgetItem();
        __qtablewidgetitem210->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_1->setItem(1, 0, __qtablewidgetitem210);
        tbl_std_1->setObjectName(QString::fromUtf8("tbl_std_1"));
        tbl_std_1->setEnabled(false);
        tbl_std_1->setGeometry(QRect(10, 50, 91, 91));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tbl_std_1->sizePolicy().hasHeightForWidth());
        tbl_std_1->setSizePolicy(sizePolicy1);
        tbl_std_1->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_std_1->horizontalHeader()->setDefaultSectionSize(50);
        tbl_std_1->horizontalHeader()->setMinimumSectionSize(10);
        tbl_std_1->verticalHeader()->setCascadingSectionResizes(true);
        tbl_std_1->verticalHeader()->setMinimumSectionSize(10);
        widget4 = new QWidget(groupBox);
        widget4->setObjectName(QString::fromUtf8("widget4"));
        widget4->setGeometry(QRect(120, 50, 51, 91));
        verticalLayout = new QVBoxLayout(widget4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btn_read_1 = new QPushButton(widget4);
        btn_read_1->setObjectName(QString::fromUtf8("btn_read_1"));
        btn_read_1->setEnabled(true);

        verticalLayout->addWidget(btn_read_1);

        verticalSpacer = new QSpacerItem(10, 5, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer);

        btn_clear_1 = new QPushButton(widget4);
        btn_clear_1->setObjectName(QString::fromUtf8("btn_clear_1"));
        btn_clear_1->setEnabled(true);

        verticalLayout->addWidget(btn_clear_1);

        widget5 = new QWidget(groupBox);
        widget5->setObjectName(QString::fromUtf8("widget5"));
        widget5->setGeometry(QRect(10, 150, 171, 461));
        verticalLayout_2 = new QVBoxLayout(widget5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget5);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(widget5);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        tbl_in_1 = new QTableWidget(widget5);
        if (tbl_in_1->columnCount() < 3)
            tbl_in_1->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem211 = new QTableWidgetItem();
        tbl_in_1->setHorizontalHeaderItem(0, __qtablewidgetitem211);
        QTableWidgetItem *__qtablewidgetitem212 = new QTableWidgetItem();
        tbl_in_1->setHorizontalHeaderItem(1, __qtablewidgetitem212);
        QTableWidgetItem *__qtablewidgetitem213 = new QTableWidgetItem();
        tbl_in_1->setHorizontalHeaderItem(2, __qtablewidgetitem213);
        if (tbl_in_1->rowCount() < 12)
            tbl_in_1->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem214 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(0, __qtablewidgetitem214);
        QTableWidgetItem *__qtablewidgetitem215 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(1, __qtablewidgetitem215);
        QTableWidgetItem *__qtablewidgetitem216 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(2, __qtablewidgetitem216);
        QTableWidgetItem *__qtablewidgetitem217 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(3, __qtablewidgetitem217);
        QTableWidgetItem *__qtablewidgetitem218 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(4, __qtablewidgetitem218);
        QTableWidgetItem *__qtablewidgetitem219 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(5, __qtablewidgetitem219);
        QTableWidgetItem *__qtablewidgetitem220 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(6, __qtablewidgetitem220);
        QTableWidgetItem *__qtablewidgetitem221 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(7, __qtablewidgetitem221);
        QTableWidgetItem *__qtablewidgetitem222 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(8, __qtablewidgetitem222);
        QTableWidgetItem *__qtablewidgetitem223 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(9, __qtablewidgetitem223);
        QTableWidgetItem *__qtablewidgetitem224 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(10, __qtablewidgetitem224);
        QTableWidgetItem *__qtablewidgetitem225 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(11, __qtablewidgetitem225);
        QTableWidgetItem *__qtablewidgetitem226 = new QTableWidgetItem();
        tbl_in_1->setItem(0, 0, __qtablewidgetitem226);
        QTableWidgetItem *__qtablewidgetitem227 = new QTableWidgetItem();
        tbl_in_1->setItem(0, 1, __qtablewidgetitem227);
        QTableWidgetItem *__qtablewidgetitem228 = new QTableWidgetItem();
        tbl_in_1->setItem(0, 2, __qtablewidgetitem228);
        QTableWidgetItem *__qtablewidgetitem229 = new QTableWidgetItem();
        tbl_in_1->setItem(1, 0, __qtablewidgetitem229);
        QTableWidgetItem *__qtablewidgetitem230 = new QTableWidgetItem();
        tbl_in_1->setItem(1, 1, __qtablewidgetitem230);
        QTableWidgetItem *__qtablewidgetitem231 = new QTableWidgetItem();
        tbl_in_1->setItem(1, 2, __qtablewidgetitem231);
        QTableWidgetItem *__qtablewidgetitem232 = new QTableWidgetItem();
        tbl_in_1->setItem(2, 0, __qtablewidgetitem232);
        QTableWidgetItem *__qtablewidgetitem233 = new QTableWidgetItem();
        tbl_in_1->setItem(2, 1, __qtablewidgetitem233);
        QTableWidgetItem *__qtablewidgetitem234 = new QTableWidgetItem();
        tbl_in_1->setItem(2, 2, __qtablewidgetitem234);
        QTableWidgetItem *__qtablewidgetitem235 = new QTableWidgetItem();
        tbl_in_1->setItem(3, 0, __qtablewidgetitem235);
        QTableWidgetItem *__qtablewidgetitem236 = new QTableWidgetItem();
        tbl_in_1->setItem(3, 1, __qtablewidgetitem236);
        QTableWidgetItem *__qtablewidgetitem237 = new QTableWidgetItem();
        tbl_in_1->setItem(3, 2, __qtablewidgetitem237);
        QTableWidgetItem *__qtablewidgetitem238 = new QTableWidgetItem();
        tbl_in_1->setItem(4, 0, __qtablewidgetitem238);
        QTableWidgetItem *__qtablewidgetitem239 = new QTableWidgetItem();
        tbl_in_1->setItem(4, 1, __qtablewidgetitem239);
        QTableWidgetItem *__qtablewidgetitem240 = new QTableWidgetItem();
        tbl_in_1->setItem(4, 2, __qtablewidgetitem240);
        QTableWidgetItem *__qtablewidgetitem241 = new QTableWidgetItem();
        tbl_in_1->setItem(5, 0, __qtablewidgetitem241);
        QTableWidgetItem *__qtablewidgetitem242 = new QTableWidgetItem();
        tbl_in_1->setItem(5, 1, __qtablewidgetitem242);
        QTableWidgetItem *__qtablewidgetitem243 = new QTableWidgetItem();
        tbl_in_1->setItem(5, 2, __qtablewidgetitem243);
        QTableWidgetItem *__qtablewidgetitem244 = new QTableWidgetItem();
        tbl_in_1->setItem(6, 0, __qtablewidgetitem244);
        QTableWidgetItem *__qtablewidgetitem245 = new QTableWidgetItem();
        tbl_in_1->setItem(6, 1, __qtablewidgetitem245);
        QTableWidgetItem *__qtablewidgetitem246 = new QTableWidgetItem();
        tbl_in_1->setItem(6, 2, __qtablewidgetitem246);
        QTableWidgetItem *__qtablewidgetitem247 = new QTableWidgetItem();
        tbl_in_1->setItem(7, 0, __qtablewidgetitem247);
        QTableWidgetItem *__qtablewidgetitem248 = new QTableWidgetItem();
        tbl_in_1->setItem(7, 1, __qtablewidgetitem248);
        QTableWidgetItem *__qtablewidgetitem249 = new QTableWidgetItem();
        tbl_in_1->setItem(7, 2, __qtablewidgetitem249);
        QTableWidgetItem *__qtablewidgetitem250 = new QTableWidgetItem();
        tbl_in_1->setItem(8, 0, __qtablewidgetitem250);
        QTableWidgetItem *__qtablewidgetitem251 = new QTableWidgetItem();
        tbl_in_1->setItem(8, 1, __qtablewidgetitem251);
        QTableWidgetItem *__qtablewidgetitem252 = new QTableWidgetItem();
        tbl_in_1->setItem(8, 2, __qtablewidgetitem252);
        QTableWidgetItem *__qtablewidgetitem253 = new QTableWidgetItem();
        tbl_in_1->setItem(9, 0, __qtablewidgetitem253);
        QTableWidgetItem *__qtablewidgetitem254 = new QTableWidgetItem();
        tbl_in_1->setItem(9, 1, __qtablewidgetitem254);
        QTableWidgetItem *__qtablewidgetitem255 = new QTableWidgetItem();
        tbl_in_1->setItem(9, 2, __qtablewidgetitem255);
        QTableWidgetItem *__qtablewidgetitem256 = new QTableWidgetItem();
        tbl_in_1->setItem(10, 0, __qtablewidgetitem256);
        QTableWidgetItem *__qtablewidgetitem257 = new QTableWidgetItem();
        tbl_in_1->setItem(10, 1, __qtablewidgetitem257);
        QTableWidgetItem *__qtablewidgetitem258 = new QTableWidgetItem();
        tbl_in_1->setItem(10, 2, __qtablewidgetitem258);
        QTableWidgetItem *__qtablewidgetitem259 = new QTableWidgetItem();
        tbl_in_1->setItem(11, 0, __qtablewidgetitem259);
        QTableWidgetItem *__qtablewidgetitem260 = new QTableWidgetItem();
        tbl_in_1->setItem(11, 1, __qtablewidgetitem260);
        QTableWidgetItem *__qtablewidgetitem261 = new QTableWidgetItem();
        tbl_in_1->setItem(11, 2, __qtablewidgetitem261);
        tbl_in_1->setObjectName(QString::fromUtf8("tbl_in_1"));
        tbl_in_1->setEnabled(true);
        tbl_in_1->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_in_1->horizontalHeader()->setDefaultSectionSize(50);
        tbl_in_1->horizontalHeader()->setMinimumSectionSize(10);
        tbl_in_1->verticalHeader()->setCascadingSectionResizes(true);
        tbl_in_1->verticalHeader()->setMinimumSectionSize(10);

        verticalLayout_2->addWidget(tbl_in_1);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(220, 30, 191, 611));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 20, 121, 16));
        tbl_std_2 = new QTableWidget(groupBox_2);
        if (tbl_std_2->columnCount() < 1)
            tbl_std_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem262 = new QTableWidgetItem();
        tbl_std_2->setHorizontalHeaderItem(0, __qtablewidgetitem262);
        if (tbl_std_2->rowCount() < 2)
            tbl_std_2->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem263 = new QTableWidgetItem();
        tbl_std_2->setVerticalHeaderItem(0, __qtablewidgetitem263);
        QTableWidgetItem *__qtablewidgetitem264 = new QTableWidgetItem();
        tbl_std_2->setVerticalHeaderItem(1, __qtablewidgetitem264);
        QTableWidgetItem *__qtablewidgetitem265 = new QTableWidgetItem();
        tbl_std_2->setItem(0, 0, __qtablewidgetitem265);
        QTableWidgetItem *__qtablewidgetitem266 = new QTableWidgetItem();
        tbl_std_2->setItem(1, 0, __qtablewidgetitem266);
        tbl_std_2->setObjectName(QString::fromUtf8("tbl_std_2"));
        tbl_std_2->setEnabled(false);
        tbl_std_2->setGeometry(QRect(20, 50, 91, 91));
        tbl_std_2->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_std_2->horizontalHeader()->setDefaultSectionSize(50);
        tbl_std_2->horizontalHeader()->setMinimumSectionSize(10);
        tbl_std_2->verticalHeader()->setCascadingSectionResizes(true);
        tbl_std_2->verticalHeader()->setMinimumSectionSize(10);
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(120, 50, 51, 91));
        verticalLayout_8 = new QVBoxLayout(layoutWidget);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        btn_read_2 = new QPushButton(layoutWidget);
        btn_read_2->setObjectName(QString::fromUtf8("btn_read_2"));
        btn_read_2->setEnabled(false);

        verticalLayout_8->addWidget(btn_read_2);

        verticalSpacer_2 = new QSpacerItem(10, 5, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_8->addItem(verticalSpacer_2);

        btn_clear_2 = new QPushButton(layoutWidget);
        btn_clear_2->setObjectName(QString::fromUtf8("btn_clear_2"));
        btn_clear_2->setEnabled(false);

        verticalLayout_8->addWidget(btn_clear_2);

        widget6 = new QWidget(groupBox_2);
        widget6->setObjectName(QString::fromUtf8("widget6"));
        widget6->setGeometry(QRect(0, 150, 171, 461));
        verticalLayout_3 = new QVBoxLayout(widget6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(widget6);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_3->addWidget(label_11);

        label_12 = new QLabel(widget6);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout_3->addWidget(label_12);

        tbl_in_2 = new QTableWidget(widget6);
        if (tbl_in_2->columnCount() < 3)
            tbl_in_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem267 = new QTableWidgetItem();
        tbl_in_2->setHorizontalHeaderItem(0, __qtablewidgetitem267);
        QTableWidgetItem *__qtablewidgetitem268 = new QTableWidgetItem();
        tbl_in_2->setHorizontalHeaderItem(1, __qtablewidgetitem268);
        QTableWidgetItem *__qtablewidgetitem269 = new QTableWidgetItem();
        tbl_in_2->setHorizontalHeaderItem(2, __qtablewidgetitem269);
        if (tbl_in_2->rowCount() < 12)
            tbl_in_2->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem270 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(0, __qtablewidgetitem270);
        QTableWidgetItem *__qtablewidgetitem271 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(1, __qtablewidgetitem271);
        QTableWidgetItem *__qtablewidgetitem272 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(2, __qtablewidgetitem272);
        QTableWidgetItem *__qtablewidgetitem273 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(3, __qtablewidgetitem273);
        QTableWidgetItem *__qtablewidgetitem274 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(4, __qtablewidgetitem274);
        QTableWidgetItem *__qtablewidgetitem275 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(5, __qtablewidgetitem275);
        QTableWidgetItem *__qtablewidgetitem276 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(6, __qtablewidgetitem276);
        QTableWidgetItem *__qtablewidgetitem277 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(7, __qtablewidgetitem277);
        QTableWidgetItem *__qtablewidgetitem278 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(8, __qtablewidgetitem278);
        QTableWidgetItem *__qtablewidgetitem279 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(9, __qtablewidgetitem279);
        QTableWidgetItem *__qtablewidgetitem280 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(10, __qtablewidgetitem280);
        QTableWidgetItem *__qtablewidgetitem281 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(11, __qtablewidgetitem281);
        QTableWidgetItem *__qtablewidgetitem282 = new QTableWidgetItem();
        tbl_in_2->setItem(0, 0, __qtablewidgetitem282);
        QTableWidgetItem *__qtablewidgetitem283 = new QTableWidgetItem();
        tbl_in_2->setItem(0, 1, __qtablewidgetitem283);
        QTableWidgetItem *__qtablewidgetitem284 = new QTableWidgetItem();
        tbl_in_2->setItem(0, 2, __qtablewidgetitem284);
        QTableWidgetItem *__qtablewidgetitem285 = new QTableWidgetItem();
        tbl_in_2->setItem(1, 0, __qtablewidgetitem285);
        QTableWidgetItem *__qtablewidgetitem286 = new QTableWidgetItem();
        tbl_in_2->setItem(1, 1, __qtablewidgetitem286);
        QTableWidgetItem *__qtablewidgetitem287 = new QTableWidgetItem();
        tbl_in_2->setItem(1, 2, __qtablewidgetitem287);
        QTableWidgetItem *__qtablewidgetitem288 = new QTableWidgetItem();
        tbl_in_2->setItem(2, 0, __qtablewidgetitem288);
        QTableWidgetItem *__qtablewidgetitem289 = new QTableWidgetItem();
        tbl_in_2->setItem(2, 1, __qtablewidgetitem289);
        QTableWidgetItem *__qtablewidgetitem290 = new QTableWidgetItem();
        tbl_in_2->setItem(2, 2, __qtablewidgetitem290);
        QTableWidgetItem *__qtablewidgetitem291 = new QTableWidgetItem();
        tbl_in_2->setItem(3, 0, __qtablewidgetitem291);
        QTableWidgetItem *__qtablewidgetitem292 = new QTableWidgetItem();
        tbl_in_2->setItem(3, 1, __qtablewidgetitem292);
        QTableWidgetItem *__qtablewidgetitem293 = new QTableWidgetItem();
        tbl_in_2->setItem(3, 2, __qtablewidgetitem293);
        QTableWidgetItem *__qtablewidgetitem294 = new QTableWidgetItem();
        tbl_in_2->setItem(4, 0, __qtablewidgetitem294);
        QTableWidgetItem *__qtablewidgetitem295 = new QTableWidgetItem();
        tbl_in_2->setItem(4, 1, __qtablewidgetitem295);
        QTableWidgetItem *__qtablewidgetitem296 = new QTableWidgetItem();
        tbl_in_2->setItem(4, 2, __qtablewidgetitem296);
        QTableWidgetItem *__qtablewidgetitem297 = new QTableWidgetItem();
        tbl_in_2->setItem(5, 0, __qtablewidgetitem297);
        QTableWidgetItem *__qtablewidgetitem298 = new QTableWidgetItem();
        tbl_in_2->setItem(5, 1, __qtablewidgetitem298);
        QTableWidgetItem *__qtablewidgetitem299 = new QTableWidgetItem();
        tbl_in_2->setItem(5, 2, __qtablewidgetitem299);
        QTableWidgetItem *__qtablewidgetitem300 = new QTableWidgetItem();
        tbl_in_2->setItem(6, 0, __qtablewidgetitem300);
        QTableWidgetItem *__qtablewidgetitem301 = new QTableWidgetItem();
        tbl_in_2->setItem(6, 1, __qtablewidgetitem301);
        QTableWidgetItem *__qtablewidgetitem302 = new QTableWidgetItem();
        tbl_in_2->setItem(6, 2, __qtablewidgetitem302);
        QTableWidgetItem *__qtablewidgetitem303 = new QTableWidgetItem();
        tbl_in_2->setItem(7, 0, __qtablewidgetitem303);
        QTableWidgetItem *__qtablewidgetitem304 = new QTableWidgetItem();
        tbl_in_2->setItem(7, 1, __qtablewidgetitem304);
        QTableWidgetItem *__qtablewidgetitem305 = new QTableWidgetItem();
        tbl_in_2->setItem(7, 2, __qtablewidgetitem305);
        QTableWidgetItem *__qtablewidgetitem306 = new QTableWidgetItem();
        tbl_in_2->setItem(8, 0, __qtablewidgetitem306);
        QTableWidgetItem *__qtablewidgetitem307 = new QTableWidgetItem();
        tbl_in_2->setItem(8, 1, __qtablewidgetitem307);
        QTableWidgetItem *__qtablewidgetitem308 = new QTableWidgetItem();
        tbl_in_2->setItem(8, 2, __qtablewidgetitem308);
        QTableWidgetItem *__qtablewidgetitem309 = new QTableWidgetItem();
        tbl_in_2->setItem(9, 0, __qtablewidgetitem309);
        QTableWidgetItem *__qtablewidgetitem310 = new QTableWidgetItem();
        tbl_in_2->setItem(9, 1, __qtablewidgetitem310);
        QTableWidgetItem *__qtablewidgetitem311 = new QTableWidgetItem();
        tbl_in_2->setItem(9, 2, __qtablewidgetitem311);
        QTableWidgetItem *__qtablewidgetitem312 = new QTableWidgetItem();
        tbl_in_2->setItem(10, 0, __qtablewidgetitem312);
        QTableWidgetItem *__qtablewidgetitem313 = new QTableWidgetItem();
        tbl_in_2->setItem(10, 1, __qtablewidgetitem313);
        QTableWidgetItem *__qtablewidgetitem314 = new QTableWidgetItem();
        tbl_in_2->setItem(10, 2, __qtablewidgetitem314);
        QTableWidgetItem *__qtablewidgetitem315 = new QTableWidgetItem();
        tbl_in_2->setItem(11, 0, __qtablewidgetitem315);
        QTableWidgetItem *__qtablewidgetitem316 = new QTableWidgetItem();
        tbl_in_2->setItem(11, 1, __qtablewidgetitem316);
        QTableWidgetItem *__qtablewidgetitem317 = new QTableWidgetItem();
        tbl_in_2->setItem(11, 2, __qtablewidgetitem317);
        tbl_in_2->setObjectName(QString::fromUtf8("tbl_in_2"));
        tbl_in_2->setEnabled(false);
        tbl_in_2->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_in_2->horizontalHeader()->setDefaultSectionSize(50);
        tbl_in_2->horizontalHeader()->setMinimumSectionSize(10);
        tbl_in_2->verticalHeader()->setCascadingSectionResizes(true);
        tbl_in_2->verticalHeader()->setMinimumSectionSize(10);

        verticalLayout_3->addWidget(tbl_in_2);

        groupBox_7 = new QGroupBox(frame);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(430, 30, 191, 611));
        label_20 = new QLabel(groupBox_7);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(40, 20, 121, 16));
        tbl_std_3 = new QTableWidget(groupBox_7);
        if (tbl_std_3->columnCount() < 1)
            tbl_std_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem318 = new QTableWidgetItem();
        tbl_std_3->setHorizontalHeaderItem(0, __qtablewidgetitem318);
        if (tbl_std_3->rowCount() < 2)
            tbl_std_3->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem319 = new QTableWidgetItem();
        tbl_std_3->setVerticalHeaderItem(0, __qtablewidgetitem319);
        QTableWidgetItem *__qtablewidgetitem320 = new QTableWidgetItem();
        tbl_std_3->setVerticalHeaderItem(1, __qtablewidgetitem320);
        QTableWidgetItem *__qtablewidgetitem321 = new QTableWidgetItem();
        tbl_std_3->setItem(0, 0, __qtablewidgetitem321);
        QTableWidgetItem *__qtablewidgetitem322 = new QTableWidgetItem();
        tbl_std_3->setItem(1, 0, __qtablewidgetitem322);
        tbl_std_3->setObjectName(QString::fromUtf8("tbl_std_3"));
        tbl_std_3->setEnabled(false);
        tbl_std_3->setGeometry(QRect(20, 50, 91, 91));
        tbl_std_3->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_std_3->horizontalHeader()->setDefaultSectionSize(50);
        tbl_std_3->horizontalHeader()->setMinimumSectionSize(10);
        tbl_std_3->verticalHeader()->setCascadingSectionResizes(true);
        tbl_std_3->verticalHeader()->setMinimumSectionSize(10);
        layoutWidget_2 = new QWidget(groupBox_7);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(120, 50, 61, 91));
        verticalLayout_9 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        btn_read_3 = new QPushButton(layoutWidget_2);
        btn_read_3->setObjectName(QString::fromUtf8("btn_read_3"));
        btn_read_3->setEnabled(false);

        verticalLayout_9->addWidget(btn_read_3);

        verticalSpacer_3 = new QSpacerItem(10, 5, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_9->addItem(verticalSpacer_3);

        btn_clear_3 = new QPushButton(layoutWidget_2);
        btn_clear_3->setObjectName(QString::fromUtf8("btn_clear_3"));
        btn_clear_3->setEnabled(false);

        verticalLayout_9->addWidget(btn_clear_3);

        widget7 = new QWidget(groupBox_7);
        widget7->setObjectName(QString::fromUtf8("widget7"));
        widget7->setGeometry(QRect(20, 150, 171, 461));
        verticalLayout_4 = new QVBoxLayout(widget7);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_21 = new QLabel(widget7);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        verticalLayout_4->addWidget(label_21);

        label_22 = new QLabel(widget7);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        verticalLayout_4->addWidget(label_22);

        tbl_in_3 = new QTableWidget(widget7);
        if (tbl_in_3->columnCount() < 3)
            tbl_in_3->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem323 = new QTableWidgetItem();
        tbl_in_3->setHorizontalHeaderItem(0, __qtablewidgetitem323);
        QTableWidgetItem *__qtablewidgetitem324 = new QTableWidgetItem();
        tbl_in_3->setHorizontalHeaderItem(1, __qtablewidgetitem324);
        QTableWidgetItem *__qtablewidgetitem325 = new QTableWidgetItem();
        tbl_in_3->setHorizontalHeaderItem(2, __qtablewidgetitem325);
        if (tbl_in_3->rowCount() < 12)
            tbl_in_3->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem326 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(0, __qtablewidgetitem326);
        QTableWidgetItem *__qtablewidgetitem327 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(1, __qtablewidgetitem327);
        QTableWidgetItem *__qtablewidgetitem328 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(2, __qtablewidgetitem328);
        QTableWidgetItem *__qtablewidgetitem329 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(3, __qtablewidgetitem329);
        QTableWidgetItem *__qtablewidgetitem330 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(4, __qtablewidgetitem330);
        QTableWidgetItem *__qtablewidgetitem331 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(5, __qtablewidgetitem331);
        QTableWidgetItem *__qtablewidgetitem332 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(6, __qtablewidgetitem332);
        QTableWidgetItem *__qtablewidgetitem333 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(7, __qtablewidgetitem333);
        QTableWidgetItem *__qtablewidgetitem334 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(8, __qtablewidgetitem334);
        QTableWidgetItem *__qtablewidgetitem335 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(9, __qtablewidgetitem335);
        QTableWidgetItem *__qtablewidgetitem336 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(10, __qtablewidgetitem336);
        QTableWidgetItem *__qtablewidgetitem337 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(11, __qtablewidgetitem337);
        QTableWidgetItem *__qtablewidgetitem338 = new QTableWidgetItem();
        tbl_in_3->setItem(0, 0, __qtablewidgetitem338);
        QTableWidgetItem *__qtablewidgetitem339 = new QTableWidgetItem();
        tbl_in_3->setItem(0, 1, __qtablewidgetitem339);
        QTableWidgetItem *__qtablewidgetitem340 = new QTableWidgetItem();
        tbl_in_3->setItem(0, 2, __qtablewidgetitem340);
        QTableWidgetItem *__qtablewidgetitem341 = new QTableWidgetItem();
        tbl_in_3->setItem(1, 0, __qtablewidgetitem341);
        QTableWidgetItem *__qtablewidgetitem342 = new QTableWidgetItem();
        tbl_in_3->setItem(1, 1, __qtablewidgetitem342);
        QTableWidgetItem *__qtablewidgetitem343 = new QTableWidgetItem();
        tbl_in_3->setItem(1, 2, __qtablewidgetitem343);
        QTableWidgetItem *__qtablewidgetitem344 = new QTableWidgetItem();
        tbl_in_3->setItem(2, 0, __qtablewidgetitem344);
        QTableWidgetItem *__qtablewidgetitem345 = new QTableWidgetItem();
        tbl_in_3->setItem(2, 1, __qtablewidgetitem345);
        QTableWidgetItem *__qtablewidgetitem346 = new QTableWidgetItem();
        tbl_in_3->setItem(2, 2, __qtablewidgetitem346);
        QTableWidgetItem *__qtablewidgetitem347 = new QTableWidgetItem();
        tbl_in_3->setItem(3, 0, __qtablewidgetitem347);
        QTableWidgetItem *__qtablewidgetitem348 = new QTableWidgetItem();
        tbl_in_3->setItem(3, 1, __qtablewidgetitem348);
        QTableWidgetItem *__qtablewidgetitem349 = new QTableWidgetItem();
        tbl_in_3->setItem(3, 2, __qtablewidgetitem349);
        QTableWidgetItem *__qtablewidgetitem350 = new QTableWidgetItem();
        tbl_in_3->setItem(4, 0, __qtablewidgetitem350);
        QTableWidgetItem *__qtablewidgetitem351 = new QTableWidgetItem();
        tbl_in_3->setItem(4, 1, __qtablewidgetitem351);
        QTableWidgetItem *__qtablewidgetitem352 = new QTableWidgetItem();
        tbl_in_3->setItem(4, 2, __qtablewidgetitem352);
        QTableWidgetItem *__qtablewidgetitem353 = new QTableWidgetItem();
        tbl_in_3->setItem(5, 0, __qtablewidgetitem353);
        QTableWidgetItem *__qtablewidgetitem354 = new QTableWidgetItem();
        tbl_in_3->setItem(5, 1, __qtablewidgetitem354);
        QTableWidgetItem *__qtablewidgetitem355 = new QTableWidgetItem();
        tbl_in_3->setItem(5, 2, __qtablewidgetitem355);
        QTableWidgetItem *__qtablewidgetitem356 = new QTableWidgetItem();
        tbl_in_3->setItem(6, 0, __qtablewidgetitem356);
        QTableWidgetItem *__qtablewidgetitem357 = new QTableWidgetItem();
        tbl_in_3->setItem(6, 1, __qtablewidgetitem357);
        QTableWidgetItem *__qtablewidgetitem358 = new QTableWidgetItem();
        tbl_in_3->setItem(6, 2, __qtablewidgetitem358);
        QTableWidgetItem *__qtablewidgetitem359 = new QTableWidgetItem();
        tbl_in_3->setItem(7, 0, __qtablewidgetitem359);
        QTableWidgetItem *__qtablewidgetitem360 = new QTableWidgetItem();
        tbl_in_3->setItem(7, 1, __qtablewidgetitem360);
        QTableWidgetItem *__qtablewidgetitem361 = new QTableWidgetItem();
        tbl_in_3->setItem(7, 2, __qtablewidgetitem361);
        QTableWidgetItem *__qtablewidgetitem362 = new QTableWidgetItem();
        tbl_in_3->setItem(8, 0, __qtablewidgetitem362);
        QTableWidgetItem *__qtablewidgetitem363 = new QTableWidgetItem();
        tbl_in_3->setItem(8, 1, __qtablewidgetitem363);
        QTableWidgetItem *__qtablewidgetitem364 = new QTableWidgetItem();
        tbl_in_3->setItem(8, 2, __qtablewidgetitem364);
        QTableWidgetItem *__qtablewidgetitem365 = new QTableWidgetItem();
        tbl_in_3->setItem(9, 0, __qtablewidgetitem365);
        QTableWidgetItem *__qtablewidgetitem366 = new QTableWidgetItem();
        tbl_in_3->setItem(9, 1, __qtablewidgetitem366);
        QTableWidgetItem *__qtablewidgetitem367 = new QTableWidgetItem();
        tbl_in_3->setItem(9, 2, __qtablewidgetitem367);
        QTableWidgetItem *__qtablewidgetitem368 = new QTableWidgetItem();
        tbl_in_3->setItem(10, 0, __qtablewidgetitem368);
        QTableWidgetItem *__qtablewidgetitem369 = new QTableWidgetItem();
        tbl_in_3->setItem(10, 1, __qtablewidgetitem369);
        QTableWidgetItem *__qtablewidgetitem370 = new QTableWidgetItem();
        tbl_in_3->setItem(10, 2, __qtablewidgetitem370);
        QTableWidgetItem *__qtablewidgetitem371 = new QTableWidgetItem();
        tbl_in_3->setItem(11, 0, __qtablewidgetitem371);
        QTableWidgetItem *__qtablewidgetitem372 = new QTableWidgetItem();
        tbl_in_3->setItem(11, 1, __qtablewidgetitem372);
        QTableWidgetItem *__qtablewidgetitem373 = new QTableWidgetItem();
        tbl_in_3->setItem(11, 2, __qtablewidgetitem373);
        tbl_in_3->setObjectName(QString::fromUtf8("tbl_in_3"));
        tbl_in_3->setEnabled(false);
        tbl_in_3->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_in_3->horizontalHeader()->setDefaultSectionSize(50);
        tbl_in_3->horizontalHeader()->setMinimumSectionSize(10);
        tbl_in_3->verticalHeader()->setCascadingSectionResizes(true);
        tbl_in_3->verticalHeader()->setMinimumSectionSize(10);

        verticalLayout_4->addWidget(tbl_in_3);

        widget8 = new QWidget(PlaParamDlgClass);
        widget8->setObjectName(QString::fromUtf8("widget8"));
        widget8->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_5 = new QHBoxLayout(widget8);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget9 = new QWidget(PlaParamDlgClass);
        widget9->setObjectName(QString::fromUtf8("widget9"));
        widget9->setGeometry(QRect(0, 0, 2, 2));
        gridLayout = new QGridLayout(widget9);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget10 = new QWidget(PlaParamDlgClass);
        widget10->setObjectName(QString::fromUtf8("widget10"));
        widget10->setGeometry(QRect(30, 680, 1261, 26));
        horizontalLayout = new QHBoxLayout(widget10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_27 = new QLabel(widget10);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        horizontalLayout->addWidget(label_27);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_param = new QPushButton(widget10);
        btn_param->setObjectName(QString::fromUtf8("btn_param"));
        btn_param->setEnabled(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../img/param.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_param->setIcon(icon);

        horizontalLayout->addWidget(btn_param);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btn_save = new QPushButton(widget10);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        btn_save->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../img/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_save->setIcon(icon1);

        horizontalLayout->addWidget(btn_save);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btn_exit = new QPushButton(widget10);
        btn_exit->setObjectName(QString::fromUtf8("btn_exit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../img/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_exit->setIcon(icon2);

        horizontalLayout->addWidget(btn_exit);


        retranslateUi(PlaParamDlgClass);

        QMetaObject::connectSlotsByName(PlaParamDlgClass);
    } // setupUi

    void retranslateUi(QWidget *PlaParamDlgClass)
    {
        PlaParamDlgClass->setWindowTitle(QApplication::translate("PlaParamDlgClass", "Parameter method of platinum resistance checking", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600;\">Calculation</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("PlaParamDlgClass", "Result for single sensor", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tbl_result->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PlaParamDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbl_result->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PlaParamDlgClass", "Err", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tbl_result->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("PlaParamDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tbl_result->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("PlaParamDlgClass", "Err", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tbl_result->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("PlaParamDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tbl_result->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("PlaParamDlgClass", "Err", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tbl_result->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("PlaParamDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tbl_result->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("PlaParamDlgClass", "Err", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tbl_result->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("PlaParamDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tbl_result->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("PlaParamDlgClass", "Err", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tbl_result->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("PlaParamDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tbl_result->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QApplication::translate("PlaParamDlgClass", "Err", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tbl_result->isSortingEnabled();
        tbl_result->setSortingEnabled(false);
        tbl_result->setSortingEnabled(__sortingEnabled);

        label_24->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-size:8pt;\">1st temperature point</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("PlaParamDlgClass", "Err Lim(\342\204\203)", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-size:8pt;\">2nd temperature point</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("PlaParamDlgClass", "Err Lim(\342\204\203)", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-size:8pt;\">3rd temperature point</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("PlaParamDlgClass", "Err Lim(\342\204\203)", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("PlaParamDlgClass", "Basic Error", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tbl_maxerr->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("PlaParamDlgClass", "In\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tbl_maxerr->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QApplication::translate("PlaParamDlgClass", "Out\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = tbl_maxerr->isSortingEnabled();
        tbl_maxerr->setSortingEnabled(false);
        tbl_maxerr->setSortingEnabled(__sortingEnabled1);

        label->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600;\">Data Input</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("PlaParamDlgClass", "1st temperature point", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Stand temperature</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tbl_std_1->verticalHeaderItem(0);
        ___qtablewidgetitem14->setText(QApplication::translate("PlaParamDlgClass", "R(\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tbl_std_1->verticalHeaderItem(1);
        ___qtablewidgetitem15->setText(QApplication::translate("PlaParamDlgClass", "T(\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled2 = tbl_std_1->isSortingEnabled();
        tbl_std_1->setSortingEnabled(false);
        tbl_std_1->setSortingEnabled(__sortingEnabled2);

        btn_read_1->setText(QApplication::translate("PlaParamDlgClass", "read", 0, QApplication::UnicodeUTF8));
        btn_clear_1->setText(QApplication::translate("PlaParamDlgClass", "clear", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">Checked Sensor</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p>(Input R following \316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tbl_in_1->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QApplication::translate("PlaParamDlgClass", "Serial", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tbl_in_1->horizontalHeaderItem(1);
        ___qtablewidgetitem17->setText(QApplication::translate("PlaParamDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tbl_in_1->horizontalHeaderItem(2);
        ___qtablewidgetitem18->setText(QApplication::translate("PlaParamDlgClass", "Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled3 = tbl_in_1->isSortingEnabled();
        tbl_in_1->setSortingEnabled(false);
        tbl_in_1->setSortingEnabled(__sortingEnabled3);

        groupBox_2->setTitle(QApplication::translate("PlaParamDlgClass", "2ndt temperature point", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Stand temperature</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tbl_std_2->verticalHeaderItem(0);
        ___qtablewidgetitem19->setText(QApplication::translate("PlaParamDlgClass", "R(\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tbl_std_2->verticalHeaderItem(1);
        ___qtablewidgetitem20->setText(QApplication::translate("PlaParamDlgClass", "T(\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled4 = tbl_std_2->isSortingEnabled();
        tbl_std_2->setSortingEnabled(false);
        tbl_std_2->setSortingEnabled(__sortingEnabled4);

        btn_read_2->setText(QApplication::translate("PlaParamDlgClass", "read", 0, QApplication::UnicodeUTF8));
        btn_clear_2->setText(QApplication::translate("PlaParamDlgClass", "clear", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">Checked Sensor</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p>(Input R following \316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tbl_in_2->horizontalHeaderItem(0);
        ___qtablewidgetitem21->setText(QApplication::translate("PlaParamDlgClass", "Serial", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tbl_in_2->horizontalHeaderItem(1);
        ___qtablewidgetitem22->setText(QApplication::translate("PlaParamDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tbl_in_2->horizontalHeaderItem(2);
        ___qtablewidgetitem23->setText(QApplication::translate("PlaParamDlgClass", "Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled5 = tbl_in_2->isSortingEnabled();
        tbl_in_2->setSortingEnabled(false);
        tbl_in_2->setSortingEnabled(__sortingEnabled5);

        groupBox_7->setTitle(QApplication::translate("PlaParamDlgClass", "3rd temperature point", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Stand temperature</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = tbl_std_3->verticalHeaderItem(0);
        ___qtablewidgetitem24->setText(QApplication::translate("PlaParamDlgClass", "R(\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tbl_std_3->verticalHeaderItem(1);
        ___qtablewidgetitem25->setText(QApplication::translate("PlaParamDlgClass", "T(\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled6 = tbl_std_3->isSortingEnabled();
        tbl_std_3->setSortingEnabled(false);
        tbl_std_3->setSortingEnabled(__sortingEnabled6);

        btn_read_3->setText(QApplication::translate("PlaParamDlgClass", "read", 0, QApplication::UnicodeUTF8));
        btn_clear_3->setText(QApplication::translate("PlaParamDlgClass", "clear", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">Checked Sensor</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p>(Input R following \316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tbl_in_3->horizontalHeaderItem(0);
        ___qtablewidgetitem26->setText(QApplication::translate("PlaParamDlgClass", "Serial", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = tbl_in_3->horizontalHeaderItem(1);
        ___qtablewidgetitem27->setText(QApplication::translate("PlaParamDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = tbl_in_3->horizontalHeaderItem(2);
        ___qtablewidgetitem28->setText(QApplication::translate("PlaParamDlgClass", "Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled7 = tbl_in_3->isSortingEnabled();
        tbl_in_3->setSortingEnabled(false);
        tbl_in_3->setSortingEnabled(__sortingEnabled7);

        label_27->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" color:#0000ff;\">Step\357\274\2321.Configurate 2.Input Data 3.Save Data 4.Exit</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btn_param->setText(QApplication::translate("PlaParamDlgClass", "Config", 0, QApplication::UnicodeUTF8));
        btn_save->setText(QApplication::translate("PlaParamDlgClass", "Save", 0, QApplication::UnicodeUTF8));
        btn_exit->setText(QApplication::translate("PlaParamDlgClass", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlaParamDlgClass: public Ui_PlaParamDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TVERPARAM_H
