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
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlaParamDlgClass
{
public:
    QFrame *frame_2;
    QLabel *label_23;
    QGroupBox *groupBox_8;
    QTableWidget *tableWidget_16;
    QFrame *frame_3;
    QLabel *label_24;
    QLineEdit *lineEdit;
    QLabel *label_26;
    QFrame *frame_5;
    QLabel *label_28;
    QLineEdit *lineEdit_2;
    QLabel *label_29;
    QFrame *frame_6;
    QLabel *label_30;
    QLineEdit *lineEdit_3;
    QLabel *label_31;
    QGroupBox *groupBox_9;
    QTableWidget *tableWidget_17;
    QTableWidget *tableWidget_18;
    QFrame *frame_4;
    QLabel *label_25;
    QFrame *frame;
    QLabel *label;
    QGroupBox *groupBox;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QLabel *label_3;
    QTableWidget *tableWidget_2;
    QLabel *label_4;
    QGroupBox *groupBox_2;
    QLabel *label_5;
    QTableWidget *tableWidget_3;
    QLabel *label_11;
    QTableWidget *tableWidget_4;
    QLabel *label_12;
    QGroupBox *groupBox_7;
    QLabel *label_20;
    QTableWidget *tableWidget_13;
    QLabel *label_21;
    QTableWidget *tableWidget_14;
    QLabel *label_22;
    QPushButton *pushButton_6;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QLabel *label_27;
    QPushButton *pushButton_7;

    void setupUi(QWidget *PlaParamDlgClass)
    {
        if (PlaParamDlgClass->objectName().isEmpty())
            PlaParamDlgClass->setObjectName(QString::fromUtf8("PlaParamDlgClass"));
        PlaParamDlgClass->resize(1415, 731);
        frame_2 = new QFrame(PlaParamDlgClass);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(690, 10, 711, 651));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_23 = new QLabel(frame_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(290, 0, 101, 16));
        groupBox_8 = new QGroupBox(frame_2);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 30, 491, 611));
        tableWidget_16 = new QTableWidget(groupBox_8);
        if (tableWidget_16->columnCount() < 12)
            tableWidget_16->setColumnCount(12);
        QFont font;
        font.setFamily(QString::fromUtf8("AcadEref"));
        font.setPointSize(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        tableWidget_16->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        tableWidget_16->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        tableWidget_16->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        tableWidget_16->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        tableWidget_16->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        tableWidget_16->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font);
        tableWidget_16->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font);
        tableWidget_16->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font);
        tableWidget_16->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font);
        tableWidget_16->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font);
        tableWidget_16->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font);
        tableWidget_16->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        if (tableWidget_16->rowCount() < 16)
            tableWidget_16->setRowCount(16);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(5, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(6, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(7, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(8, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(9, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(10, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(11, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(12, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(13, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(14, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_16->setVerticalHeaderItem(15, __qtablewidgetitem27);
        tableWidget_16->setObjectName(QString::fromUtf8("tableWidget_16"));
        tableWidget_16->setGeometry(QRect(10, 80, 471, 521));
        tableWidget_16->horizontalHeader()->setVisible(true);
        tableWidget_16->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget_16->horizontalHeader()->setDefaultSectionSize(38);
        tableWidget_16->horizontalHeader()->setMinimumSectionSize(10);
        tableWidget_16->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget_16->verticalHeader()->setMinimumSectionSize(10);
        frame_3 = new QFrame(groupBox_8);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(10, 20, 161, 51));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        label_24 = new QLabel(frame_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(40, 0, 61, 20));
        lineEdit = new QLineEdit(frame_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(80, 20, 51, 20));
        label_26 = new QLabel(frame_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(10, 20, 61, 20));
        frame_5 = new QFrame(groupBox_8);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(170, 20, 151, 51));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        label_28 = new QLabel(frame_5);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(40, 0, 61, 20));
        lineEdit_2 = new QLineEdit(frame_5);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(80, 20, 51, 20));
        label_29 = new QLabel(frame_5);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(10, 20, 61, 20));
        frame_6 = new QFrame(groupBox_8);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setGeometry(QRect(320, 20, 151, 51));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        label_30 = new QLabel(frame_6);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(40, 0, 61, 20));
        lineEdit_3 = new QLineEdit(frame_6);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(80, 20, 51, 20));
        label_31 = new QLabel(frame_6);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(10, 20, 61, 20));
        groupBox_9 = new QGroupBox(frame_2);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(510, 30, 191, 611));
        tableWidget_17 = new QTableWidget(groupBox_9);
        if (tableWidget_17->columnCount() < 3)
            tableWidget_17->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_17->setHorizontalHeaderItem(0, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_17->setHorizontalHeaderItem(1, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_17->setHorizontalHeaderItem(2, __qtablewidgetitem30);
        if (tableWidget_17->rowCount() < 1)
            tableWidget_17->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_17->setVerticalHeaderItem(0, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_17->setItem(0, 0, __qtablewidgetitem32);
        tableWidget_17->setObjectName(QString::fromUtf8("tableWidget_17"));
        tableWidget_17->setGeometry(QRect(10, 50, 171, 61));
        tableWidget_17->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_17->horizontalHeader()->setDefaultSectionSize(50);
        tableWidget_17->horizontalHeader()->setMinimumSectionSize(10);
        tableWidget_17->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget_17->verticalHeader()->setMinimumSectionSize(10);
        tableWidget_18 = new QTableWidget(groupBox_9);
        if (tableWidget_18->columnCount() < 3)
            tableWidget_18->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_18->setHorizontalHeaderItem(0, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_18->setHorizontalHeaderItem(1, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_18->setHorizontalHeaderItem(2, __qtablewidgetitem35);
        if (tableWidget_18->rowCount() < 14)
            tableWidget_18->setRowCount(14);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(0, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(1, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(2, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(3, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(4, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(5, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(6, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(7, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(8, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(9, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(10, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(11, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(12, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget_18->setVerticalHeaderItem(13, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget_18->setItem(0, 1, __qtablewidgetitem50);
        tableWidget_18->setObjectName(QString::fromUtf8("tableWidget_18"));
        tableWidget_18->setGeometry(QRect(10, 120, 171, 481));
        tableWidget_18->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_18->horizontalHeader()->setDefaultSectionSize(50);
        tableWidget_18->horizontalHeader()->setMinimumSectionSize(10);
        tableWidget_18->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget_18->verticalHeader()->setMinimumSectionSize(10);
        frame_4 = new QFrame(groupBox_9);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(10, 20, 171, 21));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        label_25 = new QLabel(frame_4);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(60, 0, 71, 20));
        frame = new QFrame(PlaParamDlgClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 661, 651));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(290, 0, 101, 16));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 30, 191, 611));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 20, 81, 16));
        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem52);
        if (tableWidget->rowCount() < 2)
            tableWidget->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem55);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 50, 171, 91));
        tableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget->horizontalHeader()->setDefaultSectionSize(50);
        tableWidget->horizontalHeader()->setMinimumSectionSize(10);
        tableWidget->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget->verticalHeader()->setMinimumSectionSize(10);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 150, 101, 16));
        tableWidget_2 = new QTableWidget(groupBox);
        if (tableWidget_2->columnCount() < 3)
            tableWidget_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem58);
        if (tableWidget_2->rowCount() < 12)
            tableWidget_2->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(0, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(1, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(2, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(3, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(4, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(5, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(6, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(7, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(8, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(9, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(10, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(11, __qtablewidgetitem70);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 1, __qtablewidgetitem71);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(10, 200, 171, 401));
        tableWidget_2->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_2->horizontalHeader()->setDefaultSectionSize(50);
        tableWidget_2->horizontalHeader()->setMinimumSectionSize(10);
        tableWidget_2->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget_2->verticalHeader()->setMinimumSectionSize(10);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 170, 121, 16));
        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(230, 30, 191, 611));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 20, 81, 16));
        tableWidget_3 = new QTableWidget(groupBox_2);
        if (tableWidget_3->columnCount() < 2)
            tableWidget_3->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem73);
        if (tableWidget_3->rowCount() < 2)
            tableWidget_3->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(0, __qtablewidgetitem74);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(1, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 0, __qtablewidgetitem76);
        tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));
        tableWidget_3->setGeometry(QRect(10, 50, 171, 91));
        tableWidget_3->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_3->horizontalHeader()->setDefaultSectionSize(50);
        tableWidget_3->horizontalHeader()->setMinimumSectionSize(10);
        tableWidget_3->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget_3->verticalHeader()->setMinimumSectionSize(10);
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 150, 101, 16));
        tableWidget_4 = new QTableWidget(groupBox_2);
        if (tableWidget_4->columnCount() < 3)
            tableWidget_4->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem77);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem78);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(2, __qtablewidgetitem79);
        if (tableWidget_4->rowCount() < 12)
            tableWidget_4->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(0, __qtablewidgetitem80);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(1, __qtablewidgetitem81);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(2, __qtablewidgetitem82);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(3, __qtablewidgetitem83);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(4, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(5, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(6, __qtablewidgetitem86);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(7, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(8, __qtablewidgetitem88);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(9, __qtablewidgetitem89);
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(10, __qtablewidgetitem90);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(11, __qtablewidgetitem91);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        tableWidget_4->setItem(0, 1, __qtablewidgetitem92);
        tableWidget_4->setObjectName(QString::fromUtf8("tableWidget_4"));
        tableWidget_4->setGeometry(QRect(10, 200, 171, 401));
        tableWidget_4->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_4->horizontalHeader()->setDefaultSectionSize(50);
        tableWidget_4->horizontalHeader()->setMinimumSectionSize(10);
        tableWidget_4->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget_4->verticalHeader()->setMinimumSectionSize(10);
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 170, 121, 16));
        groupBox_7 = new QGroupBox(frame);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(440, 30, 191, 611));
        label_20 = new QLabel(groupBox_7);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(20, 20, 81, 16));
        tableWidget_13 = new QTableWidget(groupBox_7);
        if (tableWidget_13->columnCount() < 2)
            tableWidget_13->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        tableWidget_13->setHorizontalHeaderItem(0, __qtablewidgetitem93);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        tableWidget_13->setHorizontalHeaderItem(1, __qtablewidgetitem94);
        if (tableWidget_13->rowCount() < 2)
            tableWidget_13->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        tableWidget_13->setVerticalHeaderItem(0, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        tableWidget_13->setVerticalHeaderItem(1, __qtablewidgetitem96);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        tableWidget_13->setItem(0, 0, __qtablewidgetitem97);
        tableWidget_13->setObjectName(QString::fromUtf8("tableWidget_13"));
        tableWidget_13->setGeometry(QRect(10, 50, 171, 91));
        tableWidget_13->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_13->horizontalHeader()->setDefaultSectionSize(50);
        tableWidget_13->horizontalHeader()->setMinimumSectionSize(10);
        tableWidget_13->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget_13->verticalHeader()->setMinimumSectionSize(10);
        label_21 = new QLabel(groupBox_7);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(20, 150, 101, 16));
        tableWidget_14 = new QTableWidget(groupBox_7);
        if (tableWidget_14->columnCount() < 3)
            tableWidget_14->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem98 = new QTableWidgetItem();
        tableWidget_14->setHorizontalHeaderItem(0, __qtablewidgetitem98);
        QTableWidgetItem *__qtablewidgetitem99 = new QTableWidgetItem();
        tableWidget_14->setHorizontalHeaderItem(1, __qtablewidgetitem99);
        QTableWidgetItem *__qtablewidgetitem100 = new QTableWidgetItem();
        tableWidget_14->setHorizontalHeaderItem(2, __qtablewidgetitem100);
        if (tableWidget_14->rowCount() < 12)
            tableWidget_14->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem101 = new QTableWidgetItem();
        tableWidget_14->setVerticalHeaderItem(0, __qtablewidgetitem101);
        QTableWidgetItem *__qtablewidgetitem102 = new QTableWidgetItem();
        tableWidget_14->setVerticalHeaderItem(1, __qtablewidgetitem102);
        QTableWidgetItem *__qtablewidgetitem103 = new QTableWidgetItem();
        tableWidget_14->setVerticalHeaderItem(2, __qtablewidgetitem103);
        QTableWidgetItem *__qtablewidgetitem104 = new QTableWidgetItem();
        tableWidget_14->setVerticalHeaderItem(3, __qtablewidgetitem104);
        QTableWidgetItem *__qtablewidgetitem105 = new QTableWidgetItem();
        tableWidget_14->setVerticalHeaderItem(4, __qtablewidgetitem105);
        QTableWidgetItem *__qtablewidgetitem106 = new QTableWidgetItem();
        tableWidget_14->setVerticalHeaderItem(5, __qtablewidgetitem106);
        QTableWidgetItem *__qtablewidgetitem107 = new QTableWidgetItem();
        tableWidget_14->setVerticalHeaderItem(6, __qtablewidgetitem107);
        QTableWidgetItem *__qtablewidgetitem108 = new QTableWidgetItem();
        tableWidget_14->setVerticalHeaderItem(7, __qtablewidgetitem108);
        QTableWidgetItem *__qtablewidgetitem109 = new QTableWidgetItem();
        tableWidget_14->setVerticalHeaderItem(8, __qtablewidgetitem109);
        QTableWidgetItem *__qtablewidgetitem110 = new QTableWidgetItem();
        tableWidget_14->setVerticalHeaderItem(9, __qtablewidgetitem110);
        QTableWidgetItem *__qtablewidgetitem111 = new QTableWidgetItem();
        tableWidget_14->setVerticalHeaderItem(10, __qtablewidgetitem111);
        QTableWidgetItem *__qtablewidgetitem112 = new QTableWidgetItem();
        tableWidget_14->setVerticalHeaderItem(11, __qtablewidgetitem112);
        QTableWidgetItem *__qtablewidgetitem113 = new QTableWidgetItem();
        tableWidget_14->setItem(0, 1, __qtablewidgetitem113);
        tableWidget_14->setObjectName(QString::fromUtf8("tableWidget_14"));
        tableWidget_14->setGeometry(QRect(10, 200, 171, 401));
        tableWidget_14->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_14->horizontalHeader()->setDefaultSectionSize(50);
        tableWidget_14->horizontalHeader()->setMinimumSectionSize(10);
        tableWidget_14->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget_14->verticalHeader()->setMinimumSectionSize(10);
        label_22 = new QLabel(groupBox_7);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(20, 170, 121, 16));
        pushButton_6 = new QPushButton(PlaParamDlgClass);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(1150, 680, 75, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../source/gui/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_6->setIcon(icon);
        pushButton_4 = new QPushButton(PlaParamDlgClass);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(860, 680, 75, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../source/gui/images/calculatorresult.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon1);
        pushButton_5 = new QPushButton(PlaParamDlgClass);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(1010, 680, 75, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../source/gui/images/excel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon2);
        label_27 = new QLabel(PlaParamDlgClass);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(50, 690, 451, 16));
        pushButton_7 = new QPushButton(PlaParamDlgClass);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(1290, 680, 75, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_7->setIcon(icon3);

        retranslateUi(PlaParamDlgClass);

        QMetaObject::connectSlotsByName(PlaParamDlgClass);
    } // setupUi

    void retranslateUi(QWidget *PlaParamDlgClass)
    {
        PlaParamDlgClass->setWindowTitle(QApplication::translate("PlaParamDlgClass", "\351\223\202\347\224\265\351\230\273\345\217\202\346\225\260\346\263\225\346\243\200\346\265\213", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600;\">\346\243\200\346\265\213\346\225\260\346\215\256\350\256\241\347\256\227</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("PlaParamDlgClass", "\345\215\225\346\224\257\350\256\241\347\256\227\347\273\223\346\236\234", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_16->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PlaParamDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_16->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PlaParamDlgClass", "\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_16->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("PlaParamDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_16->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("PlaParamDlgClass", "\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_16->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("PlaParamDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_16->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("PlaParamDlgClass", "\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_16->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("PlaParamDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_16->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("PlaParamDlgClass", "\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_16->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("PlaParamDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_16->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("PlaParamDlgClass", "\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_16->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("PlaParamDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_16->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QApplication::translate("PlaParamDlgClass", "\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("PlaParamDlgClass", "\347\254\254\344\270\200\346\270\251\345\272\246\347\202\271", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("PlaParamDlgClass", "\350\257\257\345\267\256\351\231\220(%)", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("PlaParamDlgClass", "\347\254\254\344\272\214\346\270\251\345\272\246\347\202\271", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("PlaParamDlgClass", "\350\257\257\345\267\256\351\231\220(%)", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("PlaParamDlgClass", "\347\254\254\344\270\211\346\270\251\345\272\246\347\202\271", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("PlaParamDlgClass", "\350\257\257\345\267\256\351\231\220(%)", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("PlaParamDlgClass", "\351\205\215\345\257\271\347\273\223\346\236\234", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_17->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("PlaParamDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_17->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QApplication::translate("PlaParamDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_17->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QApplication::translate("PlaParamDlgClass", "\346\270\251\345\267\256", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget_17->isSortingEnabled();
        tableWidget_17->setSortingEnabled(false);
        tableWidget_17->setSortingEnabled(__sortingEnabled);

        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_18->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QApplication::translate("PlaParamDlgClass", "\350\277\233\345\217\243\n"
"\346\270\251\345\272\246\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_18->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QApplication::translate("PlaParamDlgClass", "\350\277\233\345\217\243\n"
"\346\270\251\345\272\246\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_18->horizontalHeaderItem(2);
        ___qtablewidgetitem17->setText(QApplication::translate("PlaParamDlgClass", "\350\257\257\345\267\256\n"
"(%)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = tableWidget_18->isSortingEnabled();
        tableWidget_18->setSortingEnabled(false);
        tableWidget_18->setSortingEnabled(__sortingEnabled1);

        label_25->setText(QApplication::translate("PlaParamDlgClass", "\350\257\257\345\267\256\351\231\220\342\204\203/%", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600;\">\346\243\200\346\265\213\346\225\260\346\215\256\350\276\223\345\205\245</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("PlaParamDlgClass", "\347\254\254\344\270\200\346\270\251\345\267\256\347\202\271", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">\346\240\207\345\207\206\346\270\251\345\272\246</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem18->setText(QApplication::translate("PlaParamDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem19->setText(QApplication::translate("PlaParamDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem20->setText(QApplication::translate("PlaParamDlgClass", "\347\224\265\351\230\273\345\200\274(\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem21->setText(QApplication::translate("PlaParamDlgClass", "\346\270\251\345\272\246\345\200\274(\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled2 = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled2);

        label_3->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">\350\242\253\346\243\200\346\270\251\345\272\246\344\274\240\346\204\237\345\231\250</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem22->setText(QApplication::translate("PlaParamDlgClass", "\347\274\226\345\217\267", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem23->setText(QApplication::translate("PlaParamDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem24->setText(QApplication::translate("PlaParamDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled3 = tableWidget_2->isSortingEnabled();
        tableWidget_2->setSortingEnabled(false);
        tableWidget_2->setSortingEnabled(__sortingEnabled3);

        label_4->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p>(\344\273\245\344\270\213\350\276\223\345\205\245\351\223\202\347\224\265\351\230\273\345\200\274\316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("PlaParamDlgClass", "\347\254\254\344\272\214\346\270\251\345\267\256\347\202\271", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">\346\240\207\345\207\206\346\270\251\345\272\246</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem25->setText(QApplication::translate("PlaParamDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem26->setText(QApplication::translate("PlaParamDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_3->verticalHeaderItem(0);
        ___qtablewidgetitem27->setText(QApplication::translate("PlaParamDlgClass", "\347\224\265\351\230\273\345\200\274(\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_3->verticalHeaderItem(1);
        ___qtablewidgetitem28->setText(QApplication::translate("PlaParamDlgClass", "\346\270\251\345\272\246\345\200\274(\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled4 = tableWidget_3->isSortingEnabled();
        tableWidget_3->setSortingEnabled(false);
        tableWidget_3->setSortingEnabled(__sortingEnabled4);

        label_11->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">\350\242\253\346\243\200\346\270\251\345\272\246\344\274\240\346\204\237\345\231\250</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem29->setText(QApplication::translate("PlaParamDlgClass", "\347\274\226\345\217\267", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem30->setText(QApplication::translate("PlaParamDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem31->setText(QApplication::translate("PlaParamDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled5 = tableWidget_4->isSortingEnabled();
        tableWidget_4->setSortingEnabled(false);
        tableWidget_4->setSortingEnabled(__sortingEnabled5);

        label_12->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p>(\344\273\245\344\270\213\350\276\223\345\205\245\351\223\202\347\224\265\351\230\273\345\200\274\316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("PlaParamDlgClass", "\347\254\254\344\270\211\346\270\251\345\267\256\347\202\271", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">\346\240\207\345\207\206\346\270\251\345\272\246</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_13->horizontalHeaderItem(0);
        ___qtablewidgetitem32->setText(QApplication::translate("PlaParamDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget_13->horizontalHeaderItem(1);
        ___qtablewidgetitem33->setText(QApplication::translate("PlaParamDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_13->verticalHeaderItem(0);
        ___qtablewidgetitem34->setText(QApplication::translate("PlaParamDlgClass", "\347\224\265\351\230\273\345\200\274(\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_13->verticalHeaderItem(1);
        ___qtablewidgetitem35->setText(QApplication::translate("PlaParamDlgClass", "\346\270\251\345\272\246\345\200\274(\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled6 = tableWidget_13->isSortingEnabled();
        tableWidget_13->setSortingEnabled(false);
        tableWidget_13->setSortingEnabled(__sortingEnabled6);

        label_21->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">\350\242\253\346\243\200\346\270\251\345\272\246\344\274\240\346\204\237\345\231\250</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget_14->horizontalHeaderItem(0);
        ___qtablewidgetitem36->setText(QApplication::translate("PlaParamDlgClass", "\347\274\226\345\217\267", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget_14->horizontalHeaderItem(1);
        ___qtablewidgetitem37->setText(QApplication::translate("PlaParamDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget_14->horizontalHeaderItem(2);
        ___qtablewidgetitem38->setText(QApplication::translate("PlaParamDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled7 = tableWidget_14->isSortingEnabled();
        tableWidget_14->setSortingEnabled(false);
        tableWidget_14->setSortingEnabled(__sortingEnabled7);

        label_22->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p>(\344\273\245\344\270\213\350\276\223\345\205\245\351\223\202\347\224\265\351\230\273\345\200\274\316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("PlaParamDlgClass", "\344\277\235\345\255\230\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("PlaParamDlgClass", "\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("PlaParamDlgClass", "\347\224\237\346\210\220\350\241\250\346\240\274", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" color:#0000ff;\">\346\223\215\344\275\234\346\255\245\351\252\244\357\274\2321.\351\246\226\345\205\210\350\277\233\350\241\214\345\217\202\346\225\260\350\256\276\347\275\256 2.\350\276\223\345\205\245\346\243\200\345\256\232\346\225\260\346\215\256 3.\347\224\237\346\210\220\350\241\250\346\240\274 4.\344\277\235\345\255\230\346\225\260\346\215\256 5.\351\200\200\345\207\272</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("PlaParamDlgClass", "\351\200\200\345\207\272\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlaParamDlgClass: public Ui_PlaParamDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TVERPARAM_H
