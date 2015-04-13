/********************************************************************************
** Form generated from reading UI file 'tvercomp.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TVERCOMP_H
#define UI_TVERCOMP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlaCompDlgClass
{
public:
    QPushButton *btn_exit;
    QFrame *frame_input;
    QLabel *label;
    QGroupBox *gBox_infirst;
    QLabel *label_2;
    QTableWidget *tbl_std_1;
    QLabel *label_3;
    QTableWidget *tbl_in_1;
    QLabel *label_4;
    QPushButton *btn_read_1;
    QPushButton *btn_clear_1;
    QGroupBox *gBox_insec;
    QLabel *label_5;
    QTableWidget *tbl_std_2;
    QLabel *label_6;
    QLabel *label_8;
    QTableWidget *tbl_in_2;
    QPushButton *btn_clear_2;
    QPushButton *btn_read_2;
    QGroupBox *gBox_inthird;
    QLabel *label_20;
    QTableWidget *tbl_std_3;
    QLabel *label_7;
    QLabel *label_9;
    QTableWidget *tbl_in_3;
    QPushButton *btn_read_3;
    QPushButton *btn_clear_3;
    QLabel *label_27;
    QFrame *frame_result;
    QLabel *label_23;
    QGroupBox *groupBox_8;
    QTableWidget *tbl_stderror_1;
    QTableWidget *tbl_chkerror_1;
    QFrame *frame_3;
    QLabel *label_24;
    QGroupBox *groupBox_9;
    QLabel *label_25;
    QTableWidget *tbl_stderror_2;
    QTableWidget *tbl_chkerror_2;
    QGroupBox *groupBox_10;
    QLabel *label_26;
    QTableWidget *tbl_stderror_3;
    QTableWidget *tbl_chkerror_3;
    QPushButton *btn_param;
    QPushButton *btn_save;
    QPushButton *btn_excel;

    void setupUi(QWidget *PlaCompDlgClass)
    {
        if (PlaCompDlgClass->objectName().isEmpty())
            PlaCompDlgClass->setObjectName(QString::fromUtf8("PlaCompDlgClass"));
        PlaCompDlgClass->resize(1351, 717);
        btn_exit = new QPushButton(PlaCompDlgClass);
        btn_exit->setObjectName(QString::fromUtf8("btn_exit"));
        btn_exit->setGeometry(QRect(1260, 680, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../img/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_exit->setIcon(icon);
        frame_input = new QFrame(PlaCompDlgClass);
        frame_input->setObjectName(QString::fromUtf8("frame_input"));
        frame_input->setGeometry(QRect(10, 10, 661, 651));
        frame_input->setFrameShape(QFrame::StyledPanel);
        frame_input->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_input);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(290, 0, 101, 16));
        gBox_infirst = new QGroupBox(frame_input);
        gBox_infirst->setObjectName(QString::fromUtf8("gBox_infirst"));
        gBox_infirst->setGeometry(QRect(20, 30, 191, 601));
        label_2 = new QLabel(gBox_infirst);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 20, 111, 16));
        tbl_std_1 = new QTableWidget(gBox_infirst);
        if (tbl_std_1->columnCount() < 2)
            tbl_std_1->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbl_std_1->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbl_std_1->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tbl_std_1->rowCount() < 2)
            tbl_std_1->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbl_std_1->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbl_std_1->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbl_std_1->setItem(0, 0, __qtablewidgetitem4);
        tbl_std_1->setObjectName(QString::fromUtf8("tbl_std_1"));
        tbl_std_1->setGeometry(QRect(10, 70, 171, 91));
        tbl_std_1->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_std_1->horizontalHeader()->setDefaultSectionSize(50);
        tbl_std_1->horizontalHeader()->setMinimumSectionSize(10);
        tbl_std_1->verticalHeader()->setCascadingSectionResizes(true);
        tbl_std_1->verticalHeader()->setMinimumSectionSize(10);
        label_3 = new QLabel(gBox_infirst);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 170, 161, 16));
        tbl_in_1 = new QTableWidget(gBox_infirst);
        if (tbl_in_1->columnCount() < 3)
            tbl_in_1->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tbl_in_1->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tbl_in_1->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tbl_in_1->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        if (tbl_in_1->rowCount() < 12)
            tbl_in_1->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(5, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(6, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(7, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(8, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(9, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(10, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(11, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tbl_in_1->setItem(0, 1, __qtablewidgetitem20);
        tbl_in_1->setObjectName(QString::fromUtf8("tbl_in_1"));
        tbl_in_1->setGeometry(QRect(10, 210, 171, 391));
        tbl_in_1->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_in_1->horizontalHeader()->setDefaultSectionSize(50);
        tbl_in_1->horizontalHeader()->setMinimumSectionSize(10);
        tbl_in_1->verticalHeader()->setCascadingSectionResizes(true);
        tbl_in_1->verticalHeader()->setMinimumSectionSize(10);
        label_4 = new QLabel(gBox_infirst);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 190, 111, 16));
        btn_read_1 = new QPushButton(gBox_infirst);
        btn_read_1->setObjectName(QString::fromUtf8("btn_read_1"));
        btn_read_1->setGeometry(QRect(20, 40, 41, 23));
        btn_clear_1 = new QPushButton(gBox_infirst);
        btn_clear_1->setObjectName(QString::fromUtf8("btn_clear_1"));
        btn_clear_1->setGeometry(QRect(120, 40, 41, 23));
        gBox_insec = new QGroupBox(frame_input);
        gBox_insec->setObjectName(QString::fromUtf8("gBox_insec"));
        gBox_insec->setGeometry(QRect(230, 30, 191, 611));
        label_5 = new QLabel(gBox_insec);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 20, 111, 16));
        tbl_std_2 = new QTableWidget(gBox_insec);
        if (tbl_std_2->columnCount() < 2)
            tbl_std_2->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tbl_std_2->setHorizontalHeaderItem(0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tbl_std_2->setHorizontalHeaderItem(1, __qtablewidgetitem22);
        if (tbl_std_2->rowCount() < 2)
            tbl_std_2->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tbl_std_2->setVerticalHeaderItem(0, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tbl_std_2->setVerticalHeaderItem(1, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tbl_std_2->setItem(0, 0, __qtablewidgetitem25);
        tbl_std_2->setObjectName(QString::fromUtf8("tbl_std_2"));
        tbl_std_2->setGeometry(QRect(10, 70, 171, 91));
        tbl_std_2->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_std_2->horizontalHeader()->setDefaultSectionSize(50);
        tbl_std_2->horizontalHeader()->setMinimumSectionSize(10);
        tbl_std_2->verticalHeader()->setCascadingSectionResizes(true);
        tbl_std_2->verticalHeader()->setMinimumSectionSize(10);
        label_6 = new QLabel(gBox_insec);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 170, 161, 16));
        label_8 = new QLabel(gBox_insec);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 190, 111, 16));
        tbl_in_2 = new QTableWidget(gBox_insec);
        if (tbl_in_2->columnCount() < 3)
            tbl_in_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tbl_in_2->setHorizontalHeaderItem(0, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tbl_in_2->setHorizontalHeaderItem(1, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tbl_in_2->setHorizontalHeaderItem(2, __qtablewidgetitem28);
        if (tbl_in_2->rowCount() < 12)
            tbl_in_2->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(0, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(1, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(2, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(3, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(4, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(5, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(6, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(7, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(8, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(9, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(10, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(11, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tbl_in_2->setItem(0, 1, __qtablewidgetitem41);
        tbl_in_2->setObjectName(QString::fromUtf8("tbl_in_2"));
        tbl_in_2->setGeometry(QRect(10, 210, 171, 391));
        tbl_in_2->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_in_2->horizontalHeader()->setDefaultSectionSize(50);
        tbl_in_2->horizontalHeader()->setMinimumSectionSize(10);
        tbl_in_2->verticalHeader()->setCascadingSectionResizes(true);
        tbl_in_2->verticalHeader()->setMinimumSectionSize(10);
        btn_clear_2 = new QPushButton(gBox_insec);
        btn_clear_2->setObjectName(QString::fromUtf8("btn_clear_2"));
        btn_clear_2->setGeometry(QRect(130, 40, 41, 23));
        btn_read_2 = new QPushButton(gBox_insec);
        btn_read_2->setObjectName(QString::fromUtf8("btn_read_2"));
        btn_read_2->setGeometry(QRect(30, 40, 41, 23));
        gBox_inthird = new QGroupBox(frame_input);
        gBox_inthird->setObjectName(QString::fromUtf8("gBox_inthird"));
        gBox_inthird->setGeometry(QRect(440, 30, 191, 611));
        label_20 = new QLabel(gBox_inthird);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(40, 20, 111, 16));
        tbl_std_3 = new QTableWidget(gBox_inthird);
        if (tbl_std_3->columnCount() < 2)
            tbl_std_3->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tbl_std_3->setHorizontalHeaderItem(0, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tbl_std_3->setHorizontalHeaderItem(1, __qtablewidgetitem43);
        if (tbl_std_3->rowCount() < 2)
            tbl_std_3->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tbl_std_3->setVerticalHeaderItem(0, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tbl_std_3->setVerticalHeaderItem(1, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tbl_std_3->setItem(0, 0, __qtablewidgetitem46);
        tbl_std_3->setObjectName(QString::fromUtf8("tbl_std_3"));
        tbl_std_3->setGeometry(QRect(10, 70, 171, 91));
        tbl_std_3->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_std_3->horizontalHeader()->setDefaultSectionSize(50);
        tbl_std_3->horizontalHeader()->setMinimumSectionSize(10);
        tbl_std_3->verticalHeader()->setCascadingSectionResizes(true);
        tbl_std_3->verticalHeader()->setMinimumSectionSize(10);
        label_7 = new QLabel(gBox_inthird);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 170, 161, 16));
        label_9 = new QLabel(gBox_inthird);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 190, 111, 16));
        tbl_in_3 = new QTableWidget(gBox_inthird);
        if (tbl_in_3->columnCount() < 3)
            tbl_in_3->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tbl_in_3->setHorizontalHeaderItem(0, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tbl_in_3->setHorizontalHeaderItem(1, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tbl_in_3->setHorizontalHeaderItem(2, __qtablewidgetitem49);
        if (tbl_in_3->rowCount() < 12)
            tbl_in_3->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(0, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(1, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(2, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(3, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(4, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(5, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(6, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(7, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(8, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(9, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(10, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(11, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        tbl_in_3->setItem(0, 1, __qtablewidgetitem62);
        tbl_in_3->setObjectName(QString::fromUtf8("tbl_in_3"));
        tbl_in_3->setGeometry(QRect(10, 210, 171, 391));
        tbl_in_3->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_in_3->horizontalHeader()->setDefaultSectionSize(50);
        tbl_in_3->horizontalHeader()->setMinimumSectionSize(10);
        tbl_in_3->verticalHeader()->setCascadingSectionResizes(true);
        tbl_in_3->verticalHeader()->setMinimumSectionSize(10);
        btn_read_3 = new QPushButton(gBox_inthird);
        btn_read_3->setObjectName(QString::fromUtf8("btn_read_3"));
        btn_read_3->setGeometry(QRect(20, 40, 41, 23));
        btn_clear_3 = new QPushButton(gBox_inthird);
        btn_clear_3->setObjectName(QString::fromUtf8("btn_clear_3"));
        btn_clear_3->setGeometry(QRect(120, 40, 41, 23));
        label_27 = new QLabel(PlaCompDlgClass);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(40, 670, 501, 16));
        frame_result = new QFrame(PlaCompDlgClass);
        frame_result->setObjectName(QString::fromUtf8("frame_result"));
        frame_result->setGeometry(QRect(690, 10, 651, 651));
        frame_result->setFrameShape(QFrame::StyledPanel);
        frame_result->setFrameShadow(QFrame::Raised);
        label_23 = new QLabel(frame_result);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(290, 0, 101, 16));
        groupBox_8 = new QGroupBox(frame_result);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(20, 30, 191, 611));
        tbl_stderror_1 = new QTableWidget(groupBox_8);
        if (tbl_stderror_1->columnCount() < 3)
            tbl_stderror_1->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        tbl_stderror_1->setHorizontalHeaderItem(0, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        tbl_stderror_1->setHorizontalHeaderItem(1, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        tbl_stderror_1->setHorizontalHeaderItem(2, __qtablewidgetitem65);
        if (tbl_stderror_1->rowCount() < 1)
            tbl_stderror_1->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        tbl_stderror_1->setVerticalHeaderItem(0, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        tbl_stderror_1->setItem(0, 0, __qtablewidgetitem67);
        tbl_stderror_1->setObjectName(QString::fromUtf8("tbl_stderror_1"));
        tbl_stderror_1->setGeometry(QRect(10, 50, 171, 61));
        tbl_stderror_1->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_stderror_1->horizontalHeader()->setDefaultSectionSize(50);
        tbl_stderror_1->horizontalHeader()->setMinimumSectionSize(10);
        tbl_stderror_1->verticalHeader()->setCascadingSectionResizes(true);
        tbl_stderror_1->verticalHeader()->setMinimumSectionSize(10);
        tbl_chkerror_1 = new QTableWidget(groupBox_8);
        if (tbl_chkerror_1->columnCount() < 3)
            tbl_chkerror_1->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        tbl_chkerror_1->setHorizontalHeaderItem(0, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        tbl_chkerror_1->setHorizontalHeaderItem(1, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        tbl_chkerror_1->setHorizontalHeaderItem(2, __qtablewidgetitem70);
        if (tbl_chkerror_1->rowCount() < 12)
            tbl_chkerror_1->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(0, __qtablewidgetitem71);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(1, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(2, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(3, __qtablewidgetitem74);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(4, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(5, __qtablewidgetitem76);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(6, __qtablewidgetitem77);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(7, __qtablewidgetitem78);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(8, __qtablewidgetitem79);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(9, __qtablewidgetitem80);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(10, __qtablewidgetitem81);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(11, __qtablewidgetitem82);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(0, 1, __qtablewidgetitem83);
        tbl_chkerror_1->setObjectName(QString::fromUtf8("tbl_chkerror_1"));
        tbl_chkerror_1->setGeometry(QRect(10, 120, 171, 471));
        tbl_chkerror_1->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_chkerror_1->horizontalHeader()->setDefaultSectionSize(50);
        tbl_chkerror_1->horizontalHeader()->setMinimumSectionSize(10);
        tbl_chkerror_1->verticalHeader()->setCascadingSectionResizes(true);
        tbl_chkerror_1->verticalHeader()->setMinimumSectionSize(10);
        frame_3 = new QFrame(groupBox_8);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(10, 20, 171, 21));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        label_24 = new QLabel(frame_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(30, 0, 121, 20));
        groupBox_9 = new QGroupBox(frame_result);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(230, 30, 191, 611));
        label_25 = new QLabel(groupBox_9);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(30, 20, 121, 20));
        tbl_stderror_2 = new QTableWidget(groupBox_9);
        if (tbl_stderror_2->columnCount() < 3)
            tbl_stderror_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        tbl_stderror_2->setHorizontalHeaderItem(0, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        tbl_stderror_2->setHorizontalHeaderItem(1, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        tbl_stderror_2->setHorizontalHeaderItem(2, __qtablewidgetitem86);
        if (tbl_stderror_2->rowCount() < 1)
            tbl_stderror_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        tbl_stderror_2->setVerticalHeaderItem(0, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        tbl_stderror_2->setItem(0, 0, __qtablewidgetitem88);
        tbl_stderror_2->setObjectName(QString::fromUtf8("tbl_stderror_2"));
        tbl_stderror_2->setGeometry(QRect(10, 50, 171, 61));
        tbl_stderror_2->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_stderror_2->horizontalHeader()->setDefaultSectionSize(50);
        tbl_stderror_2->horizontalHeader()->setMinimumSectionSize(10);
        tbl_stderror_2->verticalHeader()->setCascadingSectionResizes(true);
        tbl_stderror_2->verticalHeader()->setMinimumSectionSize(10);
        tbl_chkerror_2 = new QTableWidget(groupBox_9);
        if (tbl_chkerror_2->columnCount() < 3)
            tbl_chkerror_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        tbl_chkerror_2->setHorizontalHeaderItem(0, __qtablewidgetitem89);
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        tbl_chkerror_2->setHorizontalHeaderItem(1, __qtablewidgetitem90);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        tbl_chkerror_2->setHorizontalHeaderItem(2, __qtablewidgetitem91);
        if (tbl_chkerror_2->rowCount() < 12)
            tbl_chkerror_2->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(0, __qtablewidgetitem92);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(1, __qtablewidgetitem93);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(2, __qtablewidgetitem94);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(3, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(4, __qtablewidgetitem96);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(5, __qtablewidgetitem97);
        QTableWidgetItem *__qtablewidgetitem98 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(6, __qtablewidgetitem98);
        QTableWidgetItem *__qtablewidgetitem99 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(7, __qtablewidgetitem99);
        QTableWidgetItem *__qtablewidgetitem100 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(8, __qtablewidgetitem100);
        QTableWidgetItem *__qtablewidgetitem101 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(9, __qtablewidgetitem101);
        QTableWidgetItem *__qtablewidgetitem102 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(10, __qtablewidgetitem102);
        QTableWidgetItem *__qtablewidgetitem103 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(11, __qtablewidgetitem103);
        QTableWidgetItem *__qtablewidgetitem104 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(0, 1, __qtablewidgetitem104);
        tbl_chkerror_2->setObjectName(QString::fromUtf8("tbl_chkerror_2"));
        tbl_chkerror_2->setGeometry(QRect(10, 120, 171, 471));
        tbl_chkerror_2->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_chkerror_2->horizontalHeader()->setDefaultSectionSize(50);
        tbl_chkerror_2->horizontalHeader()->setMinimumSectionSize(10);
        tbl_chkerror_2->verticalHeader()->setCascadingSectionResizes(true);
        tbl_chkerror_2->verticalHeader()->setMinimumSectionSize(10);
        groupBox_10 = new QGroupBox(frame_result);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setGeometry(QRect(440, 30, 191, 611));
        label_26 = new QLabel(groupBox_10);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(40, 20, 121, 20));
        tbl_stderror_3 = new QTableWidget(groupBox_10);
        if (tbl_stderror_3->columnCount() < 3)
            tbl_stderror_3->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem105 = new QTableWidgetItem();
        tbl_stderror_3->setHorizontalHeaderItem(0, __qtablewidgetitem105);
        QTableWidgetItem *__qtablewidgetitem106 = new QTableWidgetItem();
        tbl_stderror_3->setHorizontalHeaderItem(1, __qtablewidgetitem106);
        QTableWidgetItem *__qtablewidgetitem107 = new QTableWidgetItem();
        tbl_stderror_3->setHorizontalHeaderItem(2, __qtablewidgetitem107);
        if (tbl_stderror_3->rowCount() < 1)
            tbl_stderror_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem108 = new QTableWidgetItem();
        tbl_stderror_3->setVerticalHeaderItem(0, __qtablewidgetitem108);
        QTableWidgetItem *__qtablewidgetitem109 = new QTableWidgetItem();
        tbl_stderror_3->setItem(0, 0, __qtablewidgetitem109);
        tbl_stderror_3->setObjectName(QString::fromUtf8("tbl_stderror_3"));
        tbl_stderror_3->setGeometry(QRect(10, 50, 171, 61));
        tbl_stderror_3->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_stderror_3->horizontalHeader()->setDefaultSectionSize(50);
        tbl_stderror_3->horizontalHeader()->setMinimumSectionSize(10);
        tbl_stderror_3->verticalHeader()->setCascadingSectionResizes(true);
        tbl_stderror_3->verticalHeader()->setMinimumSectionSize(10);
        tbl_chkerror_3 = new QTableWidget(groupBox_10);
        if (tbl_chkerror_3->columnCount() < 3)
            tbl_chkerror_3->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem110 = new QTableWidgetItem();
        tbl_chkerror_3->setHorizontalHeaderItem(0, __qtablewidgetitem110);
        QTableWidgetItem *__qtablewidgetitem111 = new QTableWidgetItem();
        tbl_chkerror_3->setHorizontalHeaderItem(1, __qtablewidgetitem111);
        QTableWidgetItem *__qtablewidgetitem112 = new QTableWidgetItem();
        tbl_chkerror_3->setHorizontalHeaderItem(2, __qtablewidgetitem112);
        if (tbl_chkerror_3->rowCount() < 12)
            tbl_chkerror_3->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem113 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(0, __qtablewidgetitem113);
        QTableWidgetItem *__qtablewidgetitem114 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(1, __qtablewidgetitem114);
        QTableWidgetItem *__qtablewidgetitem115 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(2, __qtablewidgetitem115);
        QTableWidgetItem *__qtablewidgetitem116 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(3, __qtablewidgetitem116);
        QTableWidgetItem *__qtablewidgetitem117 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(4, __qtablewidgetitem117);
        QTableWidgetItem *__qtablewidgetitem118 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(5, __qtablewidgetitem118);
        QTableWidgetItem *__qtablewidgetitem119 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(6, __qtablewidgetitem119);
        QTableWidgetItem *__qtablewidgetitem120 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(7, __qtablewidgetitem120);
        QTableWidgetItem *__qtablewidgetitem121 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(8, __qtablewidgetitem121);
        QTableWidgetItem *__qtablewidgetitem122 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(9, __qtablewidgetitem122);
        QTableWidgetItem *__qtablewidgetitem123 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(10, __qtablewidgetitem123);
        QTableWidgetItem *__qtablewidgetitem124 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(11, __qtablewidgetitem124);
        QTableWidgetItem *__qtablewidgetitem125 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(0, 1, __qtablewidgetitem125);
        tbl_chkerror_3->setObjectName(QString::fromUtf8("tbl_chkerror_3"));
        tbl_chkerror_3->setGeometry(QRect(10, 120, 171, 471));
        tbl_chkerror_3->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_chkerror_3->horizontalHeader()->setDefaultSectionSize(50);
        tbl_chkerror_3->horizontalHeader()->setMinimumSectionSize(10);
        tbl_chkerror_3->verticalHeader()->setCascadingSectionResizes(true);
        tbl_chkerror_3->verticalHeader()->setMinimumSectionSize(10);
        btn_param = new QPushButton(PlaCompDlgClass);
        btn_param->setObjectName(QString::fromUtf8("btn_param"));
        btn_param->setGeometry(QRect(830, 680, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../img/param.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_param->setIcon(icon1);
        btn_save = new QPushButton(PlaCompDlgClass);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        btn_save->setGeometry(QRect(1120, 680, 81, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../img/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_save->setIcon(icon2);
        btn_excel = new QPushButton(PlaCompDlgClass);
        btn_excel->setObjectName(QString::fromUtf8("btn_excel"));
        btn_excel->setGeometry(QRect(980, 680, 75, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../img/excel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_excel->setIcon(icon3);

        retranslateUi(PlaCompDlgClass);

        QMetaObject::connectSlotsByName(PlaCompDlgClass);
    } // setupUi

    void retranslateUi(QWidget *PlaCompDlgClass)
    {
        PlaCompDlgClass->setWindowTitle(QApplication::translate("PlaCompDlgClass", "Comparing method of platinum resistance checking", 0, QApplication::UnicodeUTF8));
        btn_exit->setText(QApplication::translate("PlaCompDlgClass", "Exit", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600;\">Input Data</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        gBox_infirst->setTitle(QApplication::translate("PlaCompDlgClass", "First temperature difference", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">std temperature</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tbl_std_1->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbl_std_1->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tbl_std_1->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("PlaCompDlgClass", "R (\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tbl_std_1->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("PlaCompDlgClass", "T (\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tbl_std_1->isSortingEnabled();
        tbl_std_1->setSortingEnabled(false);
        tbl_std_1->setSortingEnabled(__sortingEnabled);

        label_3->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p><span style=\" font-size:10pt;\">sensor to be checked</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tbl_in_1->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("PlaCompDlgClass", "Serial", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tbl_in_1->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tbl_in_1->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = tbl_in_1->isSortingEnabled();
        tbl_in_1->setSortingEnabled(false);
        tbl_in_1->setSortingEnabled(__sortingEnabled1);

        label_4->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p>(Input R value \316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        btn_read_1->setText(QApplication::translate("PlaCompDlgClass", "Read", 0, QApplication::UnicodeUTF8));
        btn_clear_1->setText(QApplication::translate("PlaCompDlgClass", "Clear", 0, QApplication::UnicodeUTF8));
        gBox_insec->setTitle(QApplication::translate("PlaCompDlgClass", "Second temperature difference", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">std temperature</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tbl_std_2->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tbl_std_2->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tbl_std_2->verticalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("PlaCompDlgClass", "R (\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tbl_std_2->verticalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("PlaCompDlgClass", "T (\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled2 = tbl_std_2->isSortingEnabled();
        tbl_std_2->setSortingEnabled(false);
        tbl_std_2->setSortingEnabled(__sortingEnabled2);

        label_6->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p><span style=\" font-size:10pt;\">sensor to be checked</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p>(Input R value \316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tbl_in_2->horizontalHeaderItem(0);
        ___qtablewidgetitem11->setText(QApplication::translate("PlaCompDlgClass", "Serial", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tbl_in_2->horizontalHeaderItem(1);
        ___qtablewidgetitem12->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tbl_in_2->horizontalHeaderItem(2);
        ___qtablewidgetitem13->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled3 = tbl_in_2->isSortingEnabled();
        tbl_in_2->setSortingEnabled(false);
        tbl_in_2->setSortingEnabled(__sortingEnabled3);

        btn_clear_2->setText(QApplication::translate("PlaCompDlgClass", "Clear", 0, QApplication::UnicodeUTF8));
        btn_read_2->setText(QApplication::translate("PlaCompDlgClass", "Read", 0, QApplication::UnicodeUTF8));
        gBox_inthird->setTitle(QApplication::translate("PlaCompDlgClass", "Third temperature difference", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p><span style=\" font-weight:600;\">std temperature</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tbl_std_3->horizontalHeaderItem(0);
        ___qtablewidgetitem14->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tbl_std_3->horizontalHeaderItem(1);
        ___qtablewidgetitem15->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tbl_std_3->verticalHeaderItem(0);
        ___qtablewidgetitem16->setText(QApplication::translate("PlaCompDlgClass", "R (\316\251)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tbl_std_3->verticalHeaderItem(1);
        ___qtablewidgetitem17->setText(QApplication::translate("PlaCompDlgClass", "T (\342\204\203)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled4 = tbl_std_3->isSortingEnabled();
        tbl_std_3->setSortingEnabled(false);
        tbl_std_3->setSortingEnabled(__sortingEnabled4);

        label_7->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p><span style=\" font-size:10pt;\">sensor to be checked</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p>(Input R value \316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tbl_in_3->horizontalHeaderItem(0);
        ___qtablewidgetitem18->setText(QApplication::translate("PlaCompDlgClass", "Serial", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tbl_in_3->horizontalHeaderItem(1);
        ___qtablewidgetitem19->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tbl_in_3->horizontalHeaderItem(2);
        ___qtablewidgetitem20->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled5 = tbl_in_3->isSortingEnabled();
        tbl_in_3->setSortingEnabled(false);
        tbl_in_3->setSortingEnabled(__sortingEnabled5);

        btn_read_3->setText(QApplication::translate("PlaCompDlgClass", "Read", 0, QApplication::UnicodeUTF8));
        btn_clear_3->setText(QApplication::translate("PlaCompDlgClass", "Clear", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p><span style=\" color:#0000ff;\">Step:1.Configure parameter first 2.Input data 3.Generate Excel 4.Save data 5.Exit</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:11pt; font-weight:600;\">Result</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("PlaCompDlgClass", "First temperature difference", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tbl_stderror_1->horizontalHeaderItem(0);
        ___qtablewidgetitem21->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tbl_stderror_1->horizontalHeaderItem(1);
        ___qtablewidgetitem22->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tbl_stderror_1->horizontalHeaderItem(2);
        ___qtablewidgetitem23->setText(QApplication::translate("PlaCompDlgClass", "\316\224T", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled6 = tbl_stderror_1->isSortingEnabled();
        tbl_stderror_1->setSortingEnabled(false);
        tbl_stderror_1->setSortingEnabled(__sortingEnabled6);

        QTableWidgetItem *___qtablewidgetitem24 = tbl_chkerror_1->horizontalHeaderItem(0);
        ___qtablewidgetitem24->setText(QApplication::translate("PlaCompDlgClass", "In\n"
"T\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tbl_chkerror_1->horizontalHeaderItem(1);
        ___qtablewidgetitem25->setText(QApplication::translate("PlaCompDlgClass", "Out\n"
"T\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tbl_chkerror_1->horizontalHeaderItem(2);
        ___qtablewidgetitem26->setText(QApplication::translate("PlaCompDlgClass", "Error\n"
"(%)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled7 = tbl_chkerror_1->isSortingEnabled();
        tbl_chkerror_1->setSortingEnabled(false);
        tbl_chkerror_1->setSortingEnabled(__sortingEnabled7);

        label_24->setText(QApplication::translate("PlaCompDlgClass", "Limit of error \342\204\203/%", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("PlaCompDlgClass", "Second temperature difference", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("PlaCompDlgClass", "Limit of error \342\204\203/%", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = tbl_stderror_2->horizontalHeaderItem(0);
        ___qtablewidgetitem27->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = tbl_stderror_2->horizontalHeaderItem(1);
        ___qtablewidgetitem28->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = tbl_stderror_2->horizontalHeaderItem(2);
        ___qtablewidgetitem29->setText(QApplication::translate("PlaCompDlgClass", "\316\224T", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled8 = tbl_stderror_2->isSortingEnabled();
        tbl_stderror_2->setSortingEnabled(false);
        tbl_stderror_2->setSortingEnabled(__sortingEnabled8);

        QTableWidgetItem *___qtablewidgetitem30 = tbl_chkerror_2->horizontalHeaderItem(0);
        ___qtablewidgetitem30->setText(QApplication::translate("PlaCompDlgClass", "In\n"
"T\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem31 = tbl_chkerror_2->horizontalHeaderItem(1);
        ___qtablewidgetitem31->setText(QApplication::translate("PlaCompDlgClass", "Out\n"
"T\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = tbl_chkerror_2->horizontalHeaderItem(2);
        ___qtablewidgetitem32->setText(QApplication::translate("PlaCompDlgClass", "Error\n"
"(%)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled9 = tbl_chkerror_2->isSortingEnabled();
        tbl_chkerror_2->setSortingEnabled(false);
        tbl_chkerror_2->setSortingEnabled(__sortingEnabled9);

        groupBox_10->setTitle(QApplication::translate("PlaCompDlgClass", "Third temperature difference", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("PlaCompDlgClass", "Limit of error \342\204\203/%", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem33 = tbl_stderror_3->horizontalHeaderItem(0);
        ___qtablewidgetitem33->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem34 = tbl_stderror_3->horizontalHeaderItem(1);
        ___qtablewidgetitem34->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem35 = tbl_stderror_3->horizontalHeaderItem(2);
        ___qtablewidgetitem35->setText(QApplication::translate("PlaCompDlgClass", "\316\224T", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled10 = tbl_stderror_3->isSortingEnabled();
        tbl_stderror_3->setSortingEnabled(false);
        tbl_stderror_3->setSortingEnabled(__sortingEnabled10);

        QTableWidgetItem *___qtablewidgetitem36 = tbl_chkerror_3->horizontalHeaderItem(0);
        ___qtablewidgetitem36->setText(QApplication::translate("PlaCompDlgClass", "In\n"
"T\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem37 = tbl_chkerror_3->horizontalHeaderItem(1);
        ___qtablewidgetitem37->setText(QApplication::translate("PlaCompDlgClass", "Out\n"
"T\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem38 = tbl_chkerror_3->horizontalHeaderItem(2);
        ___qtablewidgetitem38->setText(QApplication::translate("PlaCompDlgClass", "Error\n"
"(%)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled11 = tbl_chkerror_3->isSortingEnabled();
        tbl_chkerror_3->setSortingEnabled(false);
        tbl_chkerror_3->setSortingEnabled(__sortingEnabled11);

        btn_param->setText(QApplication::translate("PlaCompDlgClass", "Parameter", 0, QApplication::UnicodeUTF8));
        btn_save->setText(QApplication::translate("PlaCompDlgClass", "Save", 0, QApplication::UnicodeUTF8));
        btn_excel->setText(QApplication::translate("PlaCompDlgClass", "Excel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlaCompDlgClass: public Ui_PlaCompDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TVERCOMP_H
