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
    QTableWidget *tbl_result;
    QFrame *frame_3;
    QLabel *label_24;
    QLineEdit *lineEdit_1;
    QLabel *label_26;
    QFrame *frame_5;
    QLineEdit *lineEdit_2;
    QLabel *label_29;
    QLabel *label_28;
    QFrame *frame_6;
    QLineEdit *lineEdit_3;
    QLabel *label_31;
    QLabel *label_30;
    QGroupBox *groupBox_9;
    QTableWidget *tbl_errlim;
    QTableWidget *tbl_maxerr;
    QFrame *frame_4;
    QLabel *label_25;
    QFrame *frame;
    QLabel *label;
    QGroupBox *groupBox;
    QLabel *label_2;
    QTableWidget *tbl_std_1;
    QLabel *label_3;
    QTableWidget *tbl_in_1;
    QLabel *label_4;
    QGroupBox *groupBox_2;
    QLabel *label_5;
    QLabel *label_11;
    QLabel *label_12;
    QTableWidget *tbl_std_2;
    QTableWidget *tbl_in_2;
    QGroupBox *groupBox_7;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QTableWidget *tbl_std_3;
    QTableWidget *tbl_in_3;
    QPushButton *btn_save;
    QPushButton *btn_param;
    QPushButton *btn_excel;
    QLabel *label_27;
    QPushButton *btn_exit;

    void setupUi(QWidget *PlaParamDlgClass)
    {
        if (PlaParamDlgClass->objectName().isEmpty())
            PlaParamDlgClass->setObjectName(QString::fromUtf8("PlaParamDlgClass"));
        PlaParamDlgClass->resize(1386, 731);
        frame_2 = new QFrame(PlaParamDlgClass);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(660, 10, 711, 651));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_23 = new QLabel(frame_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(290, 0, 101, 16));
        groupBox_8 = new QGroupBox(frame_2);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 30, 491, 611));
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
        if (tbl_result->rowCount() < 16)
            tbl_result->setRowCount(16);
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
        tbl_result->setVerticalHeaderItem(12, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(13, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(14, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tbl_result->setVerticalHeaderItem(15, __qtablewidgetitem27);
        tbl_result->setObjectName(QString::fromUtf8("tbl_result"));
        tbl_result->setGeometry(QRect(10, 80, 471, 521));
        tbl_result->horizontalHeader()->setVisible(true);
        tbl_result->horizontalHeader()->setCascadingSectionResizes(false);
        tbl_result->horizontalHeader()->setDefaultSectionSize(38);
        tbl_result->horizontalHeader()->setMinimumSectionSize(10);
        tbl_result->verticalHeader()->setCascadingSectionResizes(true);
        tbl_result->verticalHeader()->setMinimumSectionSize(10);
        frame_3 = new QFrame(groupBox_8);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(10, 20, 161, 51));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        label_24 = new QLabel(frame_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(0, 0, 161, 20));
        lineEdit_1 = new QLineEdit(frame_3);
        lineEdit_1->setObjectName(QString::fromUtf8("lineEdit_1"));
        lineEdit_1->setGeometry(QRect(80, 20, 51, 20));
        label_26 = new QLabel(frame_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(10, 20, 61, 20));
        frame_5 = new QFrame(groupBox_8);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(170, 20, 151, 51));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        lineEdit_2 = new QLineEdit(frame_5);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(80, 20, 51, 20));
        label_29 = new QLabel(frame_5);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(10, 20, 61, 20));
        label_28 = new QLabel(frame_5);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(10, 0, 131, 20));
        frame_6 = new QFrame(groupBox_8);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setGeometry(QRect(330, 20, 151, 51));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        lineEdit_3 = new QLineEdit(frame_6);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(80, 20, 51, 20));
        label_31 = new QLabel(frame_6);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(10, 20, 61, 20));
        label_30 = new QLabel(frame_6);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(0, 0, 151, 20));
        groupBox_9 = new QGroupBox(frame_2);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(510, 30, 191, 611));
        tbl_errlim = new QTableWidget(groupBox_9);
        if (tbl_errlim->columnCount() < 3)
            tbl_errlim->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tbl_errlim->setHorizontalHeaderItem(0, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tbl_errlim->setHorizontalHeaderItem(1, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tbl_errlim->setHorizontalHeaderItem(2, __qtablewidgetitem30);
        if (tbl_errlim->rowCount() < 1)
            tbl_errlim->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tbl_errlim->setVerticalHeaderItem(0, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tbl_errlim->setItem(0, 0, __qtablewidgetitem32);
        tbl_errlim->setObjectName(QString::fromUtf8("tbl_errlim"));
        tbl_errlim->setGeometry(QRect(10, 50, 171, 61));
        tbl_errlim->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_errlim->horizontalHeader()->setDefaultSectionSize(50);
        tbl_errlim->horizontalHeader()->setMinimumSectionSize(10);
        tbl_errlim->verticalHeader()->setCascadingSectionResizes(true);
        tbl_errlim->verticalHeader()->setMinimumSectionSize(10);
        tbl_maxerr = new QTableWidget(groupBox_9);
        if (tbl_maxerr->columnCount() < 3)
            tbl_maxerr->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tbl_maxerr->setHorizontalHeaderItem(0, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tbl_maxerr->setHorizontalHeaderItem(1, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tbl_maxerr->setHorizontalHeaderItem(2, __qtablewidgetitem35);
        if (tbl_maxerr->rowCount() < 14)
            tbl_maxerr->setRowCount(14);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(0, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(1, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(2, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(3, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(4, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(5, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(6, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(7, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(8, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(9, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(10, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(11, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(12, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tbl_maxerr->setVerticalHeaderItem(13, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tbl_maxerr->setItem(0, 1, __qtablewidgetitem50);
        tbl_maxerr->setObjectName(QString::fromUtf8("tbl_maxerr"));
        tbl_maxerr->setGeometry(QRect(10, 120, 171, 481));
        tbl_maxerr->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_maxerr->horizontalHeader()->setDefaultSectionSize(50);
        tbl_maxerr->horizontalHeader()->setMinimumSectionSize(10);
        tbl_maxerr->verticalHeader()->setCascadingSectionResizes(true);
        tbl_maxerr->verticalHeader()->setMinimumSectionSize(10);
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
        frame->setGeometry(QRect(10, 10, 641, 651));
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
        label_2->setGeometry(QRect(20, 20, 121, 16));
        tbl_std_1 = new QTableWidget(groupBox);
        if (tbl_std_1->columnCount() < 1)
            tbl_std_1->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tbl_std_1->setHorizontalHeaderItem(0, __qtablewidgetitem51);
        if (tbl_std_1->rowCount() < 2)
            tbl_std_1->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tbl_std_1->setVerticalHeaderItem(0, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tbl_std_1->setVerticalHeaderItem(1, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tbl_std_1->setItem(0, 0, __qtablewidgetitem54);
        tbl_std_1->setObjectName(QString::fromUtf8("tbl_std_1"));
        tbl_std_1->setGeometry(QRect(10, 50, 121, 91));
        tbl_std_1->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_std_1->horizontalHeader()->setDefaultSectionSize(50);
        tbl_std_1->horizontalHeader()->setMinimumSectionSize(10);
        tbl_std_1->verticalHeader()->setCascadingSectionResizes(true);
        tbl_std_1->verticalHeader()->setMinimumSectionSize(10);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 150, 101, 16));
        tbl_in_1 = new QTableWidget(groupBox);
        if (tbl_in_1->columnCount() < 3)
            tbl_in_1->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tbl_in_1->setHorizontalHeaderItem(0, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tbl_in_1->setHorizontalHeaderItem(1, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tbl_in_1->setHorizontalHeaderItem(2, __qtablewidgetitem57);
        if (tbl_in_1->rowCount() < 12)
            tbl_in_1->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(0, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(1, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(2, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(3, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(4, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(5, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(6, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(7, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(8, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(9, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(10, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(11, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        tbl_in_1->setItem(0, 1, __qtablewidgetitem70);
        tbl_in_1->setObjectName(QString::fromUtf8("tbl_in_1"));
        tbl_in_1->setGeometry(QRect(10, 200, 171, 401));
        tbl_in_1->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_in_1->horizontalHeader()->setDefaultSectionSize(50);
        tbl_in_1->horizontalHeader()->setMinimumSectionSize(10);
        tbl_in_1->verticalHeader()->setCascadingSectionResizes(true);
        tbl_in_1->verticalHeader()->setMinimumSectionSize(10);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 170, 141, 16));
        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(230, 30, 191, 611));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 20, 121, 16));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 150, 101, 16));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 170, 131, 16));
        tbl_std_2 = new QTableWidget(groupBox_2);
        if (tbl_std_2->columnCount() < 1)
            tbl_std_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        tbl_std_2->setHorizontalHeaderItem(0, __qtablewidgetitem71);
        if (tbl_std_2->rowCount() < 2)
            tbl_std_2->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        tbl_std_2->setVerticalHeaderItem(0, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        tbl_std_2->setVerticalHeaderItem(1, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        tbl_std_2->setItem(0, 0, __qtablewidgetitem74);
        tbl_std_2->setObjectName(QString::fromUtf8("tbl_std_2"));
        tbl_std_2->setGeometry(QRect(30, 50, 121, 91));
        tbl_std_2->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_std_2->horizontalHeader()->setDefaultSectionSize(50);
        tbl_std_2->horizontalHeader()->setMinimumSectionSize(10);
        tbl_std_2->verticalHeader()->setCascadingSectionResizes(true);
        tbl_std_2->verticalHeader()->setMinimumSectionSize(10);
        tbl_in_2 = new QTableWidget(groupBox_2);
        if (tbl_in_2->columnCount() < 3)
            tbl_in_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        tbl_in_2->setHorizontalHeaderItem(0, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        tbl_in_2->setHorizontalHeaderItem(1, __qtablewidgetitem76);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        tbl_in_2->setHorizontalHeaderItem(2, __qtablewidgetitem77);
        if (tbl_in_2->rowCount() < 12)
            tbl_in_2->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(0, __qtablewidgetitem78);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(1, __qtablewidgetitem79);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(2, __qtablewidgetitem80);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(3, __qtablewidgetitem81);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(4, __qtablewidgetitem82);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(5, __qtablewidgetitem83);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(6, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(7, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(8, __qtablewidgetitem86);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(9, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(10, __qtablewidgetitem88);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(11, __qtablewidgetitem89);
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        tbl_in_2->setItem(0, 1, __qtablewidgetitem90);
        tbl_in_2->setObjectName(QString::fromUtf8("tbl_in_2"));
        tbl_in_2->setGeometry(QRect(20, 200, 171, 401));
        tbl_in_2->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_in_2->horizontalHeader()->setDefaultSectionSize(50);
        tbl_in_2->horizontalHeader()->setMinimumSectionSize(10);
        tbl_in_2->verticalHeader()->setCascadingSectionResizes(true);
        tbl_in_2->verticalHeader()->setMinimumSectionSize(10);
        groupBox_7 = new QGroupBox(frame);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(440, 30, 191, 611));
        label_20 = new QLabel(groupBox_7);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(20, 20, 121, 16));
        label_21 = new QLabel(groupBox_7);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(20, 150, 101, 16));
        label_22 = new QLabel(groupBox_7);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(20, 170, 141, 16));
        tbl_std_3 = new QTableWidget(groupBox_7);
        if (tbl_std_3->columnCount() < 1)
            tbl_std_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        tbl_std_3->setHorizontalHeaderItem(0, __qtablewidgetitem91);
        if (tbl_std_3->rowCount() < 2)
            tbl_std_3->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        tbl_std_3->setVerticalHeaderItem(0, __qtablewidgetitem92);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        tbl_std_3->setVerticalHeaderItem(1, __qtablewidgetitem93);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        tbl_std_3->setItem(0, 0, __qtablewidgetitem94);
        tbl_std_3->setObjectName(QString::fromUtf8("tbl_std_3"));
        tbl_std_3->setGeometry(QRect(20, 50, 121, 91));
        tbl_std_3->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_std_3->horizontalHeader()->setDefaultSectionSize(50);
        tbl_std_3->horizontalHeader()->setMinimumSectionSize(10);
        tbl_std_3->verticalHeader()->setCascadingSectionResizes(true);
        tbl_std_3->verticalHeader()->setMinimumSectionSize(10);
        tbl_in_3 = new QTableWidget(groupBox_7);
        if (tbl_in_3->columnCount() < 3)
            tbl_in_3->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        tbl_in_3->setHorizontalHeaderItem(0, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        tbl_in_3->setHorizontalHeaderItem(1, __qtablewidgetitem96);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        tbl_in_3->setHorizontalHeaderItem(2, __qtablewidgetitem97);
        if (tbl_in_3->rowCount() < 12)
            tbl_in_3->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem98 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(0, __qtablewidgetitem98);
        QTableWidgetItem *__qtablewidgetitem99 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(1, __qtablewidgetitem99);
        QTableWidgetItem *__qtablewidgetitem100 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(2, __qtablewidgetitem100);
        QTableWidgetItem *__qtablewidgetitem101 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(3, __qtablewidgetitem101);
        QTableWidgetItem *__qtablewidgetitem102 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(4, __qtablewidgetitem102);
        QTableWidgetItem *__qtablewidgetitem103 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(5, __qtablewidgetitem103);
        QTableWidgetItem *__qtablewidgetitem104 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(6, __qtablewidgetitem104);
        QTableWidgetItem *__qtablewidgetitem105 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(7, __qtablewidgetitem105);
        QTableWidgetItem *__qtablewidgetitem106 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(8, __qtablewidgetitem106);
        QTableWidgetItem *__qtablewidgetitem107 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(9, __qtablewidgetitem107);
        QTableWidgetItem *__qtablewidgetitem108 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(10, __qtablewidgetitem108);
        QTableWidgetItem *__qtablewidgetitem109 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(11, __qtablewidgetitem109);
        QTableWidgetItem *__qtablewidgetitem110 = new QTableWidgetItem();
        tbl_in_3->setItem(0, 1, __qtablewidgetitem110);
        tbl_in_3->setObjectName(QString::fromUtf8("tbl_in_3"));
        tbl_in_3->setGeometry(QRect(10, 200, 171, 401));
        tbl_in_3->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_in_3->horizontalHeader()->setDefaultSectionSize(50);
        tbl_in_3->horizontalHeader()->setMinimumSectionSize(10);
        tbl_in_3->verticalHeader()->setCascadingSectionResizes(true);
        tbl_in_3->verticalHeader()->setMinimumSectionSize(10);
        btn_save = new QPushButton(PlaParamDlgClass);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        btn_save->setGeometry(QRect(1150, 680, 75, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../img/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_save->setIcon(icon);
        btn_param = new QPushButton(PlaParamDlgClass);
        btn_param->setObjectName(QString::fromUtf8("btn_param"));
        btn_param->setGeometry(QRect(860, 680, 75, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../img/param.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_param->setIcon(icon1);
        btn_excel = new QPushButton(PlaParamDlgClass);
        btn_excel->setObjectName(QString::fromUtf8("btn_excel"));
        btn_excel->setGeometry(QRect(1010, 680, 75, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../img/excel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_excel->setIcon(icon2);
        label_27 = new QLabel(PlaParamDlgClass);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(50, 690, 401, 16));
        btn_exit = new QPushButton(PlaParamDlgClass);
        btn_exit->setObjectName(QString::fromUtf8("btn_exit"));
        btn_exit->setGeometry(QRect(1290, 680, 75, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../img/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_exit->setIcon(icon3);

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
        label_24->setText(QApplication::translate("PlaParamDlgClass", "1st temperature head", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("PlaParamDlgClass", "Err Lim(%)", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("PlaParamDlgClass", "Err Lim(%)", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("PlaParamDlgClass", "2nd temperature head", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("PlaParamDlgClass", "Err Lim(%)", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("PlaParamDlgClass", "3rd temperature head", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("PlaParamDlgClass", "Result", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tbl_errlim->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("PlaParamDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tbl_errlim->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QApplication::translate("PlaParamDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tbl_errlim->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QApplication::translate("PlaParamDlgClass", "\316\264T", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tbl_errlim->isSortingEnabled();
        tbl_errlim->setSortingEnabled(false);
        tbl_errlim->setSortingEnabled(__sortingEnabled);

        QTableWidgetItem *___qtablewidgetitem15 = tbl_maxerr->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QApplication::translate("PlaParamDlgClass", "In\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tbl_maxerr->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QApplication::translate("PlaParamDlgClass", "Out\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tbl_maxerr->horizontalHeaderItem(2);
        ___qtablewidgetitem17->setText(QApplication::translate("PlaParamDlgClass", "\316\264T\n"
"(%)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = tbl_maxerr->isSortingEnabled();
        tbl_maxerr->setSortingEnabled(false);
        tbl_maxerr->setSortingEnabled(__sortingEnabled1);

        label_25->setText(QApplication::translate("PlaParamDlgClass", "Err Lim\342\204\203/%", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600;\">Data Input</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("PlaParamDlgClass", "1st temperature head", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">Stand temperature</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tbl_std_1->verticalHeaderItem(0);
        ___qtablewidgetitem18->setText(QApplication::translate("PlaParamDlgClass", "R(\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tbl_std_1->verticalHeaderItem(1);
        ___qtablewidgetitem19->setText(QApplication::translate("PlaParamDlgClass", "T(\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled2 = tbl_std_1->isSortingEnabled();
        tbl_std_1->setSortingEnabled(false);
        tbl_std_1->setSortingEnabled(__sortingEnabled2);

        label_3->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">Checked Sensor</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tbl_in_1->horizontalHeaderItem(0);
        ___qtablewidgetitem20->setText(QApplication::translate("PlaParamDlgClass", "Serial", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tbl_in_1->horizontalHeaderItem(1);
        ___qtablewidgetitem21->setText(QApplication::translate("PlaParamDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tbl_in_1->horizontalHeaderItem(2);
        ___qtablewidgetitem22->setText(QApplication::translate("PlaParamDlgClass", "Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled3 = tbl_in_1->isSortingEnabled();
        tbl_in_1->setSortingEnabled(false);
        tbl_in_1->setSortingEnabled(__sortingEnabled3);

        label_4->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p>(Input R following \316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("PlaParamDlgClass", "2ndt temperature head", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">Stand temperature</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">Checked Sensor</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p>(Input R following \316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tbl_std_2->verticalHeaderItem(0);
        ___qtablewidgetitem23->setText(QApplication::translate("PlaParamDlgClass", "R(\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = tbl_std_2->verticalHeaderItem(1);
        ___qtablewidgetitem24->setText(QApplication::translate("PlaParamDlgClass", "T(\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled4 = tbl_std_2->isSortingEnabled();
        tbl_std_2->setSortingEnabled(false);
        tbl_std_2->setSortingEnabled(__sortingEnabled4);

        QTableWidgetItem *___qtablewidgetitem25 = tbl_in_2->horizontalHeaderItem(0);
        ___qtablewidgetitem25->setText(QApplication::translate("PlaParamDlgClass", "Serial", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tbl_in_2->horizontalHeaderItem(1);
        ___qtablewidgetitem26->setText(QApplication::translate("PlaParamDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = tbl_in_2->horizontalHeaderItem(2);
        ___qtablewidgetitem27->setText(QApplication::translate("PlaParamDlgClass", "Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled5 = tbl_in_2->isSortingEnabled();
        tbl_in_2->setSortingEnabled(false);
        tbl_in_2->setSortingEnabled(__sortingEnabled5);

        groupBox_7->setTitle(QApplication::translate("PlaParamDlgClass", "3rd temperature head", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">Stand temperature</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">Checked Sensor</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p>(Input R following \316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = tbl_std_3->verticalHeaderItem(0);
        ___qtablewidgetitem28->setText(QApplication::translate("PlaParamDlgClass", "R(\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = tbl_std_3->verticalHeaderItem(1);
        ___qtablewidgetitem29->setText(QApplication::translate("PlaParamDlgClass", "T(\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled6 = tbl_std_3->isSortingEnabled();
        tbl_std_3->setSortingEnabled(false);
        tbl_std_3->setSortingEnabled(__sortingEnabled6);

        QTableWidgetItem *___qtablewidgetitem30 = tbl_in_3->horizontalHeaderItem(0);
        ___qtablewidgetitem30->setText(QApplication::translate("PlaParamDlgClass", "Serial", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem31 = tbl_in_3->horizontalHeaderItem(1);
        ___qtablewidgetitem31->setText(QApplication::translate("PlaParamDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = tbl_in_3->horizontalHeaderItem(2);
        ___qtablewidgetitem32->setText(QApplication::translate("PlaParamDlgClass", "Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled7 = tbl_in_3->isSortingEnabled();
        tbl_in_3->setSortingEnabled(false);
        tbl_in_3->setSortingEnabled(__sortingEnabled7);

        btn_save->setText(QApplication::translate("PlaParamDlgClass", "Save", 0, QApplication::UnicodeUTF8));
        btn_param->setText(QApplication::translate("PlaParamDlgClass", "Config", 0, QApplication::UnicodeUTF8));
        btn_excel->setText(QApplication::translate("PlaParamDlgClass", "Excel", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("PlaParamDlgClass", "<html><head/><body><p><span style=\" color:#0000ff;\">Step\357\274\2321.Configurate 2.Input Data 3.Out to excel 4.Save Data 5.Exit</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btn_exit->setText(QApplication::translate("PlaParamDlgClass", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlaParamDlgClass: public Ui_PlaParamDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TVERPARAM_H
