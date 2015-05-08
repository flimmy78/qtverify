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
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlaCompDlgClass
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_27;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_param;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btn_save;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btn_exit;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_4;
    QFrame *frame_input;
    QLabel *label;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout;
    QGroupBox *gBox_infirst;
    QWidget *layoutWidget4;
    QGridLayout *gridLayout;
    QPushButton *btn_read_1;
    QTableWidget *tbl_std_1;
    QPushButton *btn_clear_1;
    QLabel *label_2;
    QWidget *layoutWidget5;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLabel *label_4;
    QTableWidget *tbl_in_1;
    QSpacerItem *horizontalSpacer;
    QGroupBox *gBox_insec;
    QWidget *layoutWidget6;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QPushButton *btn_read_2;
    QPushButton *btn_clear_2;
    QTableWidget *tbl_std_2;
    QWidget *layoutWidget7;
    QGridLayout *gridLayout_4;
    QLabel *label_6;
    QLabel *label_8;
    QTableWidget *tbl_in_2;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *gBox_inthird;
    QWidget *layoutWidget8;
    QGridLayout *gridLayout_5;
    QLabel *label_20;
    QPushButton *btn_read_3;
    QPushButton *btn_clear_3;
    QTableWidget *tbl_std_3;
    QWidget *layoutWidget9;
    QGridLayout *gridLayout_6;
    QLabel *label_7;
    QLabel *label_9;
    QTableWidget *tbl_in_3;
    QFrame *frame_result;
    QLabel *label_23;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_8;
    QTableWidget *tbl_chkerror_1;
    QTableWidget *tbl_stderror_1;
    QLabel *label_28;
    QGroupBox *groupBox_9;
    QLabel *label_25;
    QTableWidget *tbl_stderror_2;
    QTableWidget *tbl_chkerror_2;
    QGroupBox *groupBox_10;
    QLabel *label_26;
    QTableWidget *tbl_stderror_3;
    QTableWidget *tbl_chkerror_3;

    void setupUi(QWidget *PlaCompDlgClass)
    {
        if (PlaCompDlgClass->objectName().isEmpty())
            PlaCompDlgClass->setObjectName(QString::fromUtf8("PlaCompDlgClass"));
        PlaCompDlgClass->resize(1354, 764);
        PlaCompDlgClass->setMinimumSize(QSize(1354, 764));
        PlaCompDlgClass->setMaximumSize(QSize(1354, 764));
        layoutWidget = new QWidget(PlaCompDlgClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 710, 1331, 43));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_27 = new QLabel(layoutWidget);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        horizontalLayout_2->addWidget(label_27);

        horizontalSpacer_3 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        btn_param = new QPushButton(layoutWidget);
        btn_param->setObjectName(QString::fromUtf8("btn_param"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("qtverify/source/tvercomp/img/param.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_param->setIcon(icon);

        horizontalLayout_2->addWidget(btn_param);

        horizontalSpacer_4 = new QSpacerItem(50, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        btn_save = new QPushButton(layoutWidget);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("qtverify/source/tvercomp/img/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_save->setIcon(icon1);

        horizontalLayout_2->addWidget(btn_save);

        horizontalSpacer_5 = new QSpacerItem(50, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        btn_exit = new QPushButton(layoutWidget);
        btn_exit->setObjectName(QString::fromUtf8("btn_exit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("qtverify/source/tvercomp/img/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_exit->setIcon(icon2);

        horizontalLayout_2->addWidget(btn_exit);

        layoutWidget1 = new QWidget(PlaCompDlgClass);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        layoutWidget2 = new QWidget(PlaCompDlgClass);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(PlaCompDlgClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget1 = new QWidget(PlaCompDlgClass);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_4 = new QVBoxLayout(widget1);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        widget2 = new QWidget(PlaCompDlgClass);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(10, 10, 1331, 691));
        horizontalLayout_4 = new QHBoxLayout(widget2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        frame_input = new QFrame(widget2);
        frame_input->setObjectName(QString::fromUtf8("frame_input"));
        frame_input->setMinimumSize(QSize(600, 500));
        frame_input->setFrameShape(QFrame::StyledPanel);
        frame_input->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_input);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(290, 0, 101, 16));
        layoutWidget3 = new QWidget(frame_input);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 30, 602, 641));
        horizontalLayout = new QHBoxLayout(layoutWidget3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gBox_infirst = new QGroupBox(layoutWidget3);
        gBox_infirst->setObjectName(QString::fromUtf8("gBox_infirst"));
        layoutWidget4 = new QWidget(gBox_infirst);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 20, 171, 141));
        gridLayout = new QGridLayout(layoutWidget4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btn_read_1 = new QPushButton(layoutWidget4);
        btn_read_1->setObjectName(QString::fromUtf8("btn_read_1"));

        gridLayout->addWidget(btn_read_1, 1, 0, 1, 1);

        tbl_std_1 = new QTableWidget(layoutWidget4);
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
        __qtablewidgetitem4->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_1->setItem(0, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_1->setItem(0, 1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_1->setItem(1, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_1->setItem(1, 1, __qtablewidgetitem7);
        tbl_std_1->setObjectName(QString::fromUtf8("tbl_std_1"));
        tbl_std_1->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_std_1->horizontalHeader()->setDefaultSectionSize(50);
        tbl_std_1->horizontalHeader()->setMinimumSectionSize(10);
        tbl_std_1->verticalHeader()->setCascadingSectionResizes(true);
        tbl_std_1->verticalHeader()->setMinimumSectionSize(10);

        gridLayout->addWidget(tbl_std_1, 2, 0, 1, 2);

        btn_clear_1 = new QPushButton(layoutWidget4);
        btn_clear_1->setObjectName(QString::fromUtf8("btn_clear_1"));

        gridLayout->addWidget(btn_clear_1, 1, 1, 1, 1);

        label_2 = new QLabel(layoutWidget4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        layoutWidget5 = new QWidget(gBox_infirst);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(10, 170, 171, 461));
        gridLayout_2 = new QGridLayout(layoutWidget5);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget5);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_4 = new QLabel(layoutWidget5);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        tbl_in_1 = new QTableWidget(layoutWidget5);
        if (tbl_in_1->columnCount() < 3)
            tbl_in_1->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tbl_in_1->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tbl_in_1->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tbl_in_1->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        if (tbl_in_1->rowCount() < 12)
            tbl_in_1->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(4, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(5, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(6, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(7, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(8, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(9, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(10, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tbl_in_1->setVerticalHeaderItem(11, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tbl_in_1->setItem(0, 0, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tbl_in_1->setItem(0, 1, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tbl_in_1->setItem(0, 2, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tbl_in_1->setItem(1, 0, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tbl_in_1->setItem(1, 1, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tbl_in_1->setItem(1, 2, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tbl_in_1->setItem(2, 0, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tbl_in_1->setItem(2, 1, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tbl_in_1->setItem(2, 2, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tbl_in_1->setItem(3, 0, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tbl_in_1->setItem(3, 1, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tbl_in_1->setItem(3, 2, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tbl_in_1->setItem(4, 0, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tbl_in_1->setItem(4, 1, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tbl_in_1->setItem(4, 2, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tbl_in_1->setItem(5, 0, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tbl_in_1->setItem(5, 1, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tbl_in_1->setItem(5, 2, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tbl_in_1->setItem(6, 0, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tbl_in_1->setItem(6, 1, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tbl_in_1->setItem(6, 2, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tbl_in_1->setItem(7, 0, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tbl_in_1->setItem(7, 1, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tbl_in_1->setItem(7, 2, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tbl_in_1->setItem(8, 0, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tbl_in_1->setItem(8, 1, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tbl_in_1->setItem(8, 2, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tbl_in_1->setItem(9, 0, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tbl_in_1->setItem(9, 1, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tbl_in_1->setItem(9, 2, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tbl_in_1->setItem(10, 0, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tbl_in_1->setItem(10, 1, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tbl_in_1->setItem(10, 2, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tbl_in_1->setItem(11, 0, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tbl_in_1->setItem(11, 1, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tbl_in_1->setItem(11, 2, __qtablewidgetitem58);
        tbl_in_1->setObjectName(QString::fromUtf8("tbl_in_1"));
        tbl_in_1->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_in_1->horizontalHeader()->setDefaultSectionSize(50);
        tbl_in_1->horizontalHeader()->setMinimumSectionSize(10);
        tbl_in_1->verticalHeader()->setCascadingSectionResizes(true);
        tbl_in_1->verticalHeader()->setMinimumSectionSize(10);

        gridLayout_2->addWidget(tbl_in_1, 2, 0, 1, 1);


        horizontalLayout->addWidget(gBox_infirst);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        gBox_insec = new QGroupBox(layoutWidget3);
        gBox_insec->setObjectName(QString::fromUtf8("gBox_insec"));
        layoutWidget6 = new QWidget(gBox_insec);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(10, 20, 171, 141));
        gridLayout_3 = new QGridLayout(layoutWidget6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget6);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 2);

        btn_read_2 = new QPushButton(layoutWidget6);
        btn_read_2->setObjectName(QString::fromUtf8("btn_read_2"));
        btn_read_2->setEnabled(true);

        gridLayout_3->addWidget(btn_read_2, 1, 0, 1, 1);

        btn_clear_2 = new QPushButton(layoutWidget6);
        btn_clear_2->setObjectName(QString::fromUtf8("btn_clear_2"));
        btn_clear_2->setEnabled(true);

        gridLayout_3->addWidget(btn_clear_2, 1, 1, 1, 1);

        tbl_std_2 = new QTableWidget(layoutWidget6);
        if (tbl_std_2->columnCount() < 2)
            tbl_std_2->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tbl_std_2->setHorizontalHeaderItem(0, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        tbl_std_2->setHorizontalHeaderItem(1, __qtablewidgetitem60);
        if (tbl_std_2->rowCount() < 2)
            tbl_std_2->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        tbl_std_2->setVerticalHeaderItem(0, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        tbl_std_2->setVerticalHeaderItem(1, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        __qtablewidgetitem63->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_2->setItem(0, 0, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        __qtablewidgetitem64->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_2->setItem(0, 1, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        __qtablewidgetitem65->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_2->setItem(1, 0, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        __qtablewidgetitem66->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_2->setItem(1, 1, __qtablewidgetitem66);
        tbl_std_2->setObjectName(QString::fromUtf8("tbl_std_2"));
        tbl_std_2->setEnabled(true);
        tbl_std_2->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_std_2->horizontalHeader()->setDefaultSectionSize(50);
        tbl_std_2->horizontalHeader()->setMinimumSectionSize(10);
        tbl_std_2->verticalHeader()->setCascadingSectionResizes(true);
        tbl_std_2->verticalHeader()->setMinimumSectionSize(10);

        gridLayout_3->addWidget(tbl_std_2, 2, 0, 1, 2);

        layoutWidget7 = new QWidget(gBox_insec);
        layoutWidget7->setObjectName(QString::fromUtf8("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(10, 170, 171, 461));
        gridLayout_4 = new QGridLayout(layoutWidget7);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget7);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 0, 0, 1, 1);

        label_8 = new QLabel(layoutWidget7);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_4->addWidget(label_8, 1, 0, 1, 1);

        tbl_in_2 = new QTableWidget(layoutWidget7);
        if (tbl_in_2->columnCount() < 3)
            tbl_in_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        tbl_in_2->setHorizontalHeaderItem(0, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        tbl_in_2->setHorizontalHeaderItem(1, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        tbl_in_2->setHorizontalHeaderItem(2, __qtablewidgetitem69);
        if (tbl_in_2->rowCount() < 12)
            tbl_in_2->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(0, __qtablewidgetitem70);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(1, __qtablewidgetitem71);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(2, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(3, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(4, __qtablewidgetitem74);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(5, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(6, __qtablewidgetitem76);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(7, __qtablewidgetitem77);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(8, __qtablewidgetitem78);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(9, __qtablewidgetitem79);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(10, __qtablewidgetitem80);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        tbl_in_2->setVerticalHeaderItem(11, __qtablewidgetitem81);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        tbl_in_2->setItem(0, 0, __qtablewidgetitem82);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        tbl_in_2->setItem(0, 1, __qtablewidgetitem83);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        tbl_in_2->setItem(0, 2, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        tbl_in_2->setItem(1, 0, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        tbl_in_2->setItem(1, 1, __qtablewidgetitem86);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        tbl_in_2->setItem(1, 2, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        tbl_in_2->setItem(2, 0, __qtablewidgetitem88);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        tbl_in_2->setItem(2, 1, __qtablewidgetitem89);
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        tbl_in_2->setItem(2, 2, __qtablewidgetitem90);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        tbl_in_2->setItem(3, 0, __qtablewidgetitem91);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        tbl_in_2->setItem(3, 1, __qtablewidgetitem92);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        tbl_in_2->setItem(3, 2, __qtablewidgetitem93);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        tbl_in_2->setItem(4, 0, __qtablewidgetitem94);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        tbl_in_2->setItem(4, 1, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        tbl_in_2->setItem(4, 2, __qtablewidgetitem96);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        tbl_in_2->setItem(5, 0, __qtablewidgetitem97);
        QTableWidgetItem *__qtablewidgetitem98 = new QTableWidgetItem();
        tbl_in_2->setItem(5, 1, __qtablewidgetitem98);
        QTableWidgetItem *__qtablewidgetitem99 = new QTableWidgetItem();
        tbl_in_2->setItem(5, 2, __qtablewidgetitem99);
        QTableWidgetItem *__qtablewidgetitem100 = new QTableWidgetItem();
        tbl_in_2->setItem(6, 0, __qtablewidgetitem100);
        QTableWidgetItem *__qtablewidgetitem101 = new QTableWidgetItem();
        tbl_in_2->setItem(6, 1, __qtablewidgetitem101);
        QTableWidgetItem *__qtablewidgetitem102 = new QTableWidgetItem();
        tbl_in_2->setItem(6, 2, __qtablewidgetitem102);
        QTableWidgetItem *__qtablewidgetitem103 = new QTableWidgetItem();
        tbl_in_2->setItem(7, 0, __qtablewidgetitem103);
        QTableWidgetItem *__qtablewidgetitem104 = new QTableWidgetItem();
        tbl_in_2->setItem(7, 1, __qtablewidgetitem104);
        QTableWidgetItem *__qtablewidgetitem105 = new QTableWidgetItem();
        tbl_in_2->setItem(7, 2, __qtablewidgetitem105);
        QTableWidgetItem *__qtablewidgetitem106 = new QTableWidgetItem();
        tbl_in_2->setItem(8, 0, __qtablewidgetitem106);
        QTableWidgetItem *__qtablewidgetitem107 = new QTableWidgetItem();
        tbl_in_2->setItem(8, 1, __qtablewidgetitem107);
        QTableWidgetItem *__qtablewidgetitem108 = new QTableWidgetItem();
        tbl_in_2->setItem(8, 2, __qtablewidgetitem108);
        QTableWidgetItem *__qtablewidgetitem109 = new QTableWidgetItem();
        tbl_in_2->setItem(9, 0, __qtablewidgetitem109);
        QTableWidgetItem *__qtablewidgetitem110 = new QTableWidgetItem();
        tbl_in_2->setItem(9, 1, __qtablewidgetitem110);
        QTableWidgetItem *__qtablewidgetitem111 = new QTableWidgetItem();
        tbl_in_2->setItem(9, 2, __qtablewidgetitem111);
        QTableWidgetItem *__qtablewidgetitem112 = new QTableWidgetItem();
        tbl_in_2->setItem(10, 0, __qtablewidgetitem112);
        QTableWidgetItem *__qtablewidgetitem113 = new QTableWidgetItem();
        tbl_in_2->setItem(10, 1, __qtablewidgetitem113);
        QTableWidgetItem *__qtablewidgetitem114 = new QTableWidgetItem();
        tbl_in_2->setItem(10, 2, __qtablewidgetitem114);
        QTableWidgetItem *__qtablewidgetitem115 = new QTableWidgetItem();
        tbl_in_2->setItem(11, 0, __qtablewidgetitem115);
        QTableWidgetItem *__qtablewidgetitem116 = new QTableWidgetItem();
        tbl_in_2->setItem(11, 1, __qtablewidgetitem116);
        QTableWidgetItem *__qtablewidgetitem117 = new QTableWidgetItem();
        tbl_in_2->setItem(11, 2, __qtablewidgetitem117);
        tbl_in_2->setObjectName(QString::fromUtf8("tbl_in_2"));
        tbl_in_2->setEnabled(true);
        tbl_in_2->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_in_2->horizontalHeader()->setDefaultSectionSize(50);
        tbl_in_2->horizontalHeader()->setMinimumSectionSize(10);
        tbl_in_2->verticalHeader()->setCascadingSectionResizes(true);
        tbl_in_2->verticalHeader()->setMinimumSectionSize(10);

        gridLayout_4->addWidget(tbl_in_2, 2, 0, 1, 1);


        horizontalLayout->addWidget(gBox_insec);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        gBox_inthird = new QGroupBox(layoutWidget3);
        gBox_inthird->setObjectName(QString::fromUtf8("gBox_inthird"));
        layoutWidget8 = new QWidget(gBox_inthird);
        layoutWidget8->setObjectName(QString::fromUtf8("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(10, 20, 171, 141));
        gridLayout_5 = new QGridLayout(layoutWidget8);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        label_20 = new QLabel(layoutWidget8);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_5->addWidget(label_20, 0, 0, 1, 2);

        btn_read_3 = new QPushButton(layoutWidget8);
        btn_read_3->setObjectName(QString::fromUtf8("btn_read_3"));
        btn_read_3->setEnabled(true);

        gridLayout_5->addWidget(btn_read_3, 1, 0, 1, 1);

        btn_clear_3 = new QPushButton(layoutWidget8);
        btn_clear_3->setObjectName(QString::fromUtf8("btn_clear_3"));
        btn_clear_3->setEnabled(true);

        gridLayout_5->addWidget(btn_clear_3, 1, 1, 1, 1);

        tbl_std_3 = new QTableWidget(layoutWidget8);
        if (tbl_std_3->columnCount() < 2)
            tbl_std_3->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem118 = new QTableWidgetItem();
        tbl_std_3->setHorizontalHeaderItem(0, __qtablewidgetitem118);
        QTableWidgetItem *__qtablewidgetitem119 = new QTableWidgetItem();
        tbl_std_3->setHorizontalHeaderItem(1, __qtablewidgetitem119);
        if (tbl_std_3->rowCount() < 2)
            tbl_std_3->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem120 = new QTableWidgetItem();
        tbl_std_3->setVerticalHeaderItem(0, __qtablewidgetitem120);
        QTableWidgetItem *__qtablewidgetitem121 = new QTableWidgetItem();
        tbl_std_3->setVerticalHeaderItem(1, __qtablewidgetitem121);
        QTableWidgetItem *__qtablewidgetitem122 = new QTableWidgetItem();
        __qtablewidgetitem122->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_3->setItem(0, 0, __qtablewidgetitem122);
        QTableWidgetItem *__qtablewidgetitem123 = new QTableWidgetItem();
        __qtablewidgetitem123->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_3->setItem(0, 1, __qtablewidgetitem123);
        QTableWidgetItem *__qtablewidgetitem124 = new QTableWidgetItem();
        __qtablewidgetitem124->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_3->setItem(1, 0, __qtablewidgetitem124);
        QTableWidgetItem *__qtablewidgetitem125 = new QTableWidgetItem();
        __qtablewidgetitem125->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tbl_std_3->setItem(1, 1, __qtablewidgetitem125);
        tbl_std_3->setObjectName(QString::fromUtf8("tbl_std_3"));
        tbl_std_3->setEnabled(true);
        tbl_std_3->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_std_3->horizontalHeader()->setDefaultSectionSize(50);
        tbl_std_3->horizontalHeader()->setMinimumSectionSize(10);
        tbl_std_3->verticalHeader()->setCascadingSectionResizes(true);
        tbl_std_3->verticalHeader()->setMinimumSectionSize(10);

        gridLayout_5->addWidget(tbl_std_3, 2, 0, 1, 2);

        layoutWidget9 = new QWidget(gBox_inthird);
        layoutWidget9->setObjectName(QString::fromUtf8("layoutWidget9"));
        layoutWidget9->setGeometry(QRect(10, 170, 171, 461));
        gridLayout_6 = new QGridLayout(layoutWidget9);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget9);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_6->addWidget(label_7, 0, 0, 1, 1);

        label_9 = new QLabel(layoutWidget9);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_6->addWidget(label_9, 1, 0, 1, 1);

        tbl_in_3 = new QTableWidget(layoutWidget9);
        if (tbl_in_3->columnCount() < 3)
            tbl_in_3->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem126 = new QTableWidgetItem();
        tbl_in_3->setHorizontalHeaderItem(0, __qtablewidgetitem126);
        QTableWidgetItem *__qtablewidgetitem127 = new QTableWidgetItem();
        tbl_in_3->setHorizontalHeaderItem(1, __qtablewidgetitem127);
        QTableWidgetItem *__qtablewidgetitem128 = new QTableWidgetItem();
        tbl_in_3->setHorizontalHeaderItem(2, __qtablewidgetitem128);
        if (tbl_in_3->rowCount() < 12)
            tbl_in_3->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem129 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(0, __qtablewidgetitem129);
        QTableWidgetItem *__qtablewidgetitem130 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(1, __qtablewidgetitem130);
        QTableWidgetItem *__qtablewidgetitem131 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(2, __qtablewidgetitem131);
        QTableWidgetItem *__qtablewidgetitem132 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(3, __qtablewidgetitem132);
        QTableWidgetItem *__qtablewidgetitem133 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(4, __qtablewidgetitem133);
        QTableWidgetItem *__qtablewidgetitem134 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(5, __qtablewidgetitem134);
        QTableWidgetItem *__qtablewidgetitem135 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(6, __qtablewidgetitem135);
        QTableWidgetItem *__qtablewidgetitem136 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(7, __qtablewidgetitem136);
        QTableWidgetItem *__qtablewidgetitem137 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(8, __qtablewidgetitem137);
        QTableWidgetItem *__qtablewidgetitem138 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(9, __qtablewidgetitem138);
        QTableWidgetItem *__qtablewidgetitem139 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(10, __qtablewidgetitem139);
        QTableWidgetItem *__qtablewidgetitem140 = new QTableWidgetItem();
        tbl_in_3->setVerticalHeaderItem(11, __qtablewidgetitem140);
        QTableWidgetItem *__qtablewidgetitem141 = new QTableWidgetItem();
        tbl_in_3->setItem(0, 0, __qtablewidgetitem141);
        QTableWidgetItem *__qtablewidgetitem142 = new QTableWidgetItem();
        tbl_in_3->setItem(0, 1, __qtablewidgetitem142);
        QTableWidgetItem *__qtablewidgetitem143 = new QTableWidgetItem();
        tbl_in_3->setItem(0, 2, __qtablewidgetitem143);
        QTableWidgetItem *__qtablewidgetitem144 = new QTableWidgetItem();
        tbl_in_3->setItem(1, 0, __qtablewidgetitem144);
        QTableWidgetItem *__qtablewidgetitem145 = new QTableWidgetItem();
        tbl_in_3->setItem(1, 1, __qtablewidgetitem145);
        QTableWidgetItem *__qtablewidgetitem146 = new QTableWidgetItem();
        tbl_in_3->setItem(1, 2, __qtablewidgetitem146);
        QTableWidgetItem *__qtablewidgetitem147 = new QTableWidgetItem();
        tbl_in_3->setItem(2, 0, __qtablewidgetitem147);
        QTableWidgetItem *__qtablewidgetitem148 = new QTableWidgetItem();
        tbl_in_3->setItem(2, 1, __qtablewidgetitem148);
        QTableWidgetItem *__qtablewidgetitem149 = new QTableWidgetItem();
        tbl_in_3->setItem(2, 2, __qtablewidgetitem149);
        QTableWidgetItem *__qtablewidgetitem150 = new QTableWidgetItem();
        tbl_in_3->setItem(3, 0, __qtablewidgetitem150);
        QTableWidgetItem *__qtablewidgetitem151 = new QTableWidgetItem();
        tbl_in_3->setItem(3, 1, __qtablewidgetitem151);
        QTableWidgetItem *__qtablewidgetitem152 = new QTableWidgetItem();
        tbl_in_3->setItem(3, 2, __qtablewidgetitem152);
        QTableWidgetItem *__qtablewidgetitem153 = new QTableWidgetItem();
        tbl_in_3->setItem(4, 0, __qtablewidgetitem153);
        QTableWidgetItem *__qtablewidgetitem154 = new QTableWidgetItem();
        tbl_in_3->setItem(4, 1, __qtablewidgetitem154);
        QTableWidgetItem *__qtablewidgetitem155 = new QTableWidgetItem();
        tbl_in_3->setItem(4, 2, __qtablewidgetitem155);
        QTableWidgetItem *__qtablewidgetitem156 = new QTableWidgetItem();
        tbl_in_3->setItem(5, 0, __qtablewidgetitem156);
        QTableWidgetItem *__qtablewidgetitem157 = new QTableWidgetItem();
        tbl_in_3->setItem(5, 1, __qtablewidgetitem157);
        QTableWidgetItem *__qtablewidgetitem158 = new QTableWidgetItem();
        tbl_in_3->setItem(5, 2, __qtablewidgetitem158);
        QTableWidgetItem *__qtablewidgetitem159 = new QTableWidgetItem();
        tbl_in_3->setItem(6, 0, __qtablewidgetitem159);
        QTableWidgetItem *__qtablewidgetitem160 = new QTableWidgetItem();
        tbl_in_3->setItem(6, 1, __qtablewidgetitem160);
        QTableWidgetItem *__qtablewidgetitem161 = new QTableWidgetItem();
        tbl_in_3->setItem(6, 2, __qtablewidgetitem161);
        QTableWidgetItem *__qtablewidgetitem162 = new QTableWidgetItem();
        tbl_in_3->setItem(7, 0, __qtablewidgetitem162);
        QTableWidgetItem *__qtablewidgetitem163 = new QTableWidgetItem();
        tbl_in_3->setItem(7, 1, __qtablewidgetitem163);
        QTableWidgetItem *__qtablewidgetitem164 = new QTableWidgetItem();
        tbl_in_3->setItem(7, 2, __qtablewidgetitem164);
        QTableWidgetItem *__qtablewidgetitem165 = new QTableWidgetItem();
        tbl_in_3->setItem(8, 0, __qtablewidgetitem165);
        QTableWidgetItem *__qtablewidgetitem166 = new QTableWidgetItem();
        tbl_in_3->setItem(8, 1, __qtablewidgetitem166);
        QTableWidgetItem *__qtablewidgetitem167 = new QTableWidgetItem();
        tbl_in_3->setItem(8, 2, __qtablewidgetitem167);
        QTableWidgetItem *__qtablewidgetitem168 = new QTableWidgetItem();
        tbl_in_3->setItem(9, 0, __qtablewidgetitem168);
        QTableWidgetItem *__qtablewidgetitem169 = new QTableWidgetItem();
        tbl_in_3->setItem(9, 1, __qtablewidgetitem169);
        QTableWidgetItem *__qtablewidgetitem170 = new QTableWidgetItem();
        tbl_in_3->setItem(9, 2, __qtablewidgetitem170);
        QTableWidgetItem *__qtablewidgetitem171 = new QTableWidgetItem();
        tbl_in_3->setItem(10, 0, __qtablewidgetitem171);
        QTableWidgetItem *__qtablewidgetitem172 = new QTableWidgetItem();
        tbl_in_3->setItem(10, 1, __qtablewidgetitem172);
        QTableWidgetItem *__qtablewidgetitem173 = new QTableWidgetItem();
        tbl_in_3->setItem(10, 2, __qtablewidgetitem173);
        QTableWidgetItem *__qtablewidgetitem174 = new QTableWidgetItem();
        tbl_in_3->setItem(11, 0, __qtablewidgetitem174);
        QTableWidgetItem *__qtablewidgetitem175 = new QTableWidgetItem();
        tbl_in_3->setItem(11, 1, __qtablewidgetitem175);
        QTableWidgetItem *__qtablewidgetitem176 = new QTableWidgetItem();
        tbl_in_3->setItem(11, 2, __qtablewidgetitem176);
        tbl_in_3->setObjectName(QString::fromUtf8("tbl_in_3"));
        tbl_in_3->setEnabled(true);
        tbl_in_3->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_in_3->horizontalHeader()->setDefaultSectionSize(50);
        tbl_in_3->horizontalHeader()->setMinimumSectionSize(10);
        tbl_in_3->verticalHeader()->setCascadingSectionResizes(true);
        tbl_in_3->verticalHeader()->setMinimumSectionSize(10);

        gridLayout_6->addWidget(tbl_in_3, 2, 0, 1, 1);


        horizontalLayout->addWidget(gBox_inthird);


        horizontalLayout_4->addWidget(frame_input);

        frame_result = new QFrame(widget2);
        frame_result->setObjectName(QString::fromUtf8("frame_result"));
        frame_result->setFrameShape(QFrame::StyledPanel);
        frame_result->setFrameShadow(QFrame::Raised);
        label_23 = new QLabel(frame_result);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(290, 40, 101, 16));
        widget3 = new QWidget(frame_result);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        widget3->setGeometry(QRect(20, 90, 590, 581));
        horizontalLayout_3 = new QHBoxLayout(widget3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox_8 = new QGroupBox(widget3);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        tbl_chkerror_1 = new QTableWidget(groupBox_8);
        if (tbl_chkerror_1->columnCount() < 3)
            tbl_chkerror_1->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem177 = new QTableWidgetItem();
        tbl_chkerror_1->setHorizontalHeaderItem(0, __qtablewidgetitem177);
        QTableWidgetItem *__qtablewidgetitem178 = new QTableWidgetItem();
        tbl_chkerror_1->setHorizontalHeaderItem(1, __qtablewidgetitem178);
        QTableWidgetItem *__qtablewidgetitem179 = new QTableWidgetItem();
        tbl_chkerror_1->setHorizontalHeaderItem(2, __qtablewidgetitem179);
        if (tbl_chkerror_1->rowCount() < 12)
            tbl_chkerror_1->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem180 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(0, __qtablewidgetitem180);
        QTableWidgetItem *__qtablewidgetitem181 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(1, __qtablewidgetitem181);
        QTableWidgetItem *__qtablewidgetitem182 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(2, __qtablewidgetitem182);
        QTableWidgetItem *__qtablewidgetitem183 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(3, __qtablewidgetitem183);
        QTableWidgetItem *__qtablewidgetitem184 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(4, __qtablewidgetitem184);
        QTableWidgetItem *__qtablewidgetitem185 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(5, __qtablewidgetitem185);
        QTableWidgetItem *__qtablewidgetitem186 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(6, __qtablewidgetitem186);
        QTableWidgetItem *__qtablewidgetitem187 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(7, __qtablewidgetitem187);
        QTableWidgetItem *__qtablewidgetitem188 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(8, __qtablewidgetitem188);
        QTableWidgetItem *__qtablewidgetitem189 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(9, __qtablewidgetitem189);
        QTableWidgetItem *__qtablewidgetitem190 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(10, __qtablewidgetitem190);
        QTableWidgetItem *__qtablewidgetitem191 = new QTableWidgetItem();
        tbl_chkerror_1->setVerticalHeaderItem(11, __qtablewidgetitem191);
        QTableWidgetItem *__qtablewidgetitem192 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(0, 0, __qtablewidgetitem192);
        QTableWidgetItem *__qtablewidgetitem193 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(0, 1, __qtablewidgetitem193);
        QTableWidgetItem *__qtablewidgetitem194 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(0, 2, __qtablewidgetitem194);
        QTableWidgetItem *__qtablewidgetitem195 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(1, 0, __qtablewidgetitem195);
        QTableWidgetItem *__qtablewidgetitem196 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(1, 1, __qtablewidgetitem196);
        QTableWidgetItem *__qtablewidgetitem197 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(1, 2, __qtablewidgetitem197);
        QTableWidgetItem *__qtablewidgetitem198 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(2, 0, __qtablewidgetitem198);
        QTableWidgetItem *__qtablewidgetitem199 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(2, 1, __qtablewidgetitem199);
        QTableWidgetItem *__qtablewidgetitem200 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(2, 2, __qtablewidgetitem200);
        QTableWidgetItem *__qtablewidgetitem201 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(3, 0, __qtablewidgetitem201);
        QTableWidgetItem *__qtablewidgetitem202 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(3, 1, __qtablewidgetitem202);
        QTableWidgetItem *__qtablewidgetitem203 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(3, 2, __qtablewidgetitem203);
        QTableWidgetItem *__qtablewidgetitem204 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(4, 0, __qtablewidgetitem204);
        QTableWidgetItem *__qtablewidgetitem205 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(4, 1, __qtablewidgetitem205);
        QTableWidgetItem *__qtablewidgetitem206 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(4, 2, __qtablewidgetitem206);
        QTableWidgetItem *__qtablewidgetitem207 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(5, 0, __qtablewidgetitem207);
        QTableWidgetItem *__qtablewidgetitem208 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(5, 1, __qtablewidgetitem208);
        QTableWidgetItem *__qtablewidgetitem209 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(5, 2, __qtablewidgetitem209);
        QTableWidgetItem *__qtablewidgetitem210 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(6, 0, __qtablewidgetitem210);
        QTableWidgetItem *__qtablewidgetitem211 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(6, 1, __qtablewidgetitem211);
        QTableWidgetItem *__qtablewidgetitem212 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(6, 2, __qtablewidgetitem212);
        QTableWidgetItem *__qtablewidgetitem213 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(7, 0, __qtablewidgetitem213);
        QTableWidgetItem *__qtablewidgetitem214 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(7, 1, __qtablewidgetitem214);
        QTableWidgetItem *__qtablewidgetitem215 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(7, 2, __qtablewidgetitem215);
        QTableWidgetItem *__qtablewidgetitem216 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(8, 0, __qtablewidgetitem216);
        QTableWidgetItem *__qtablewidgetitem217 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(8, 1, __qtablewidgetitem217);
        QTableWidgetItem *__qtablewidgetitem218 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(8, 2, __qtablewidgetitem218);
        QTableWidgetItem *__qtablewidgetitem219 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(9, 0, __qtablewidgetitem219);
        QTableWidgetItem *__qtablewidgetitem220 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(9, 1, __qtablewidgetitem220);
        QTableWidgetItem *__qtablewidgetitem221 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(9, 2, __qtablewidgetitem221);
        QTableWidgetItem *__qtablewidgetitem222 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(10, 0, __qtablewidgetitem222);
        QTableWidgetItem *__qtablewidgetitem223 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(10, 1, __qtablewidgetitem223);
        QTableWidgetItem *__qtablewidgetitem224 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(10, 2, __qtablewidgetitem224);
        QTableWidgetItem *__qtablewidgetitem225 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(11, 0, __qtablewidgetitem225);
        QTableWidgetItem *__qtablewidgetitem226 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(11, 1, __qtablewidgetitem226);
        QTableWidgetItem *__qtablewidgetitem227 = new QTableWidgetItem();
        tbl_chkerror_1->setItem(11, 2, __qtablewidgetitem227);
        tbl_chkerror_1->setObjectName(QString::fromUtf8("tbl_chkerror_1"));
        tbl_chkerror_1->setEnabled(false);
        tbl_chkerror_1->setGeometry(QRect(11, 119, 171, 441));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tbl_chkerror_1->sizePolicy().hasHeightForWidth());
        tbl_chkerror_1->setSizePolicy(sizePolicy);
        tbl_chkerror_1->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_chkerror_1->horizontalHeader()->setDefaultSectionSize(50);
        tbl_chkerror_1->horizontalHeader()->setMinimumSectionSize(10);
        tbl_chkerror_1->verticalHeader()->setCascadingSectionResizes(true);
        tbl_chkerror_1->verticalHeader()->setMinimumSectionSize(10);
        tbl_stderror_1 = new QTableWidget(groupBox_8);
        if (tbl_stderror_1->columnCount() < 3)
            tbl_stderror_1->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem228 = new QTableWidgetItem();
        tbl_stderror_1->setHorizontalHeaderItem(0, __qtablewidgetitem228);
        QTableWidgetItem *__qtablewidgetitem229 = new QTableWidgetItem();
        tbl_stderror_1->setHorizontalHeaderItem(1, __qtablewidgetitem229);
        QTableWidgetItem *__qtablewidgetitem230 = new QTableWidgetItem();
        tbl_stderror_1->setHorizontalHeaderItem(2, __qtablewidgetitem230);
        if (tbl_stderror_1->rowCount() < 1)
            tbl_stderror_1->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem231 = new QTableWidgetItem();
        tbl_stderror_1->setVerticalHeaderItem(0, __qtablewidgetitem231);
        QTableWidgetItem *__qtablewidgetitem232 = new QTableWidgetItem();
        tbl_stderror_1->setItem(0, 0, __qtablewidgetitem232);
        QTableWidgetItem *__qtablewidgetitem233 = new QTableWidgetItem();
        tbl_stderror_1->setItem(0, 1, __qtablewidgetitem233);
        QTableWidgetItem *__qtablewidgetitem234 = new QTableWidgetItem();
        tbl_stderror_1->setItem(0, 2, __qtablewidgetitem234);
        tbl_stderror_1->setObjectName(QString::fromUtf8("tbl_stderror_1"));
        tbl_stderror_1->setEnabled(false);
        tbl_stderror_1->setGeometry(QRect(10, 50, 171, 61));
        tbl_stderror_1->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_stderror_1->horizontalHeader()->setDefaultSectionSize(50);
        tbl_stderror_1->horizontalHeader()->setMinimumSectionSize(10);
        tbl_stderror_1->verticalHeader()->setCascadingSectionResizes(true);
        tbl_stderror_1->verticalHeader()->setMinimumSectionSize(10);
        label_28 = new QLabel(groupBox_8);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(30, 30, 121, 20));

        horizontalLayout_3->addWidget(groupBox_8);

        groupBox_9 = new QGroupBox(widget3);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        label_25 = new QLabel(groupBox_9);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(30, 30, 121, 20));
        tbl_stderror_2 = new QTableWidget(groupBox_9);
        if (tbl_stderror_2->columnCount() < 3)
            tbl_stderror_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem235 = new QTableWidgetItem();
        tbl_stderror_2->setHorizontalHeaderItem(0, __qtablewidgetitem235);
        QTableWidgetItem *__qtablewidgetitem236 = new QTableWidgetItem();
        tbl_stderror_2->setHorizontalHeaderItem(1, __qtablewidgetitem236);
        QTableWidgetItem *__qtablewidgetitem237 = new QTableWidgetItem();
        tbl_stderror_2->setHorizontalHeaderItem(2, __qtablewidgetitem237);
        if (tbl_stderror_2->rowCount() < 1)
            tbl_stderror_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem238 = new QTableWidgetItem();
        tbl_stderror_2->setVerticalHeaderItem(0, __qtablewidgetitem238);
        QTableWidgetItem *__qtablewidgetitem239 = new QTableWidgetItem();
        tbl_stderror_2->setItem(0, 0, __qtablewidgetitem239);
        QTableWidgetItem *__qtablewidgetitem240 = new QTableWidgetItem();
        tbl_stderror_2->setItem(0, 1, __qtablewidgetitem240);
        QTableWidgetItem *__qtablewidgetitem241 = new QTableWidgetItem();
        tbl_stderror_2->setItem(0, 2, __qtablewidgetitem241);
        tbl_stderror_2->setObjectName(QString::fromUtf8("tbl_stderror_2"));
        tbl_stderror_2->setEnabled(false);
        tbl_stderror_2->setGeometry(QRect(10, 50, 171, 61));
        tbl_stderror_2->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_stderror_2->horizontalHeader()->setDefaultSectionSize(50);
        tbl_stderror_2->horizontalHeader()->setMinimumSectionSize(10);
        tbl_stderror_2->verticalHeader()->setCascadingSectionResizes(true);
        tbl_stderror_2->verticalHeader()->setMinimumSectionSize(10);
        tbl_chkerror_2 = new QTableWidget(groupBox_9);
        if (tbl_chkerror_2->columnCount() < 3)
            tbl_chkerror_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem242 = new QTableWidgetItem();
        tbl_chkerror_2->setHorizontalHeaderItem(0, __qtablewidgetitem242);
        QTableWidgetItem *__qtablewidgetitem243 = new QTableWidgetItem();
        tbl_chkerror_2->setHorizontalHeaderItem(1, __qtablewidgetitem243);
        QTableWidgetItem *__qtablewidgetitem244 = new QTableWidgetItem();
        tbl_chkerror_2->setHorizontalHeaderItem(2, __qtablewidgetitem244);
        if (tbl_chkerror_2->rowCount() < 12)
            tbl_chkerror_2->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem245 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(0, __qtablewidgetitem245);
        QTableWidgetItem *__qtablewidgetitem246 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(1, __qtablewidgetitem246);
        QTableWidgetItem *__qtablewidgetitem247 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(2, __qtablewidgetitem247);
        QTableWidgetItem *__qtablewidgetitem248 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(3, __qtablewidgetitem248);
        QTableWidgetItem *__qtablewidgetitem249 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(4, __qtablewidgetitem249);
        QTableWidgetItem *__qtablewidgetitem250 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(5, __qtablewidgetitem250);
        QTableWidgetItem *__qtablewidgetitem251 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(6, __qtablewidgetitem251);
        QTableWidgetItem *__qtablewidgetitem252 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(7, __qtablewidgetitem252);
        QTableWidgetItem *__qtablewidgetitem253 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(8, __qtablewidgetitem253);
        QTableWidgetItem *__qtablewidgetitem254 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(9, __qtablewidgetitem254);
        QTableWidgetItem *__qtablewidgetitem255 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(10, __qtablewidgetitem255);
        QTableWidgetItem *__qtablewidgetitem256 = new QTableWidgetItem();
        tbl_chkerror_2->setVerticalHeaderItem(11, __qtablewidgetitem256);
        QTableWidgetItem *__qtablewidgetitem257 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(0, 0, __qtablewidgetitem257);
        QTableWidgetItem *__qtablewidgetitem258 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(0, 1, __qtablewidgetitem258);
        QTableWidgetItem *__qtablewidgetitem259 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(0, 2, __qtablewidgetitem259);
        QTableWidgetItem *__qtablewidgetitem260 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(1, 0, __qtablewidgetitem260);
        QTableWidgetItem *__qtablewidgetitem261 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(1, 1, __qtablewidgetitem261);
        QTableWidgetItem *__qtablewidgetitem262 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(1, 2, __qtablewidgetitem262);
        QTableWidgetItem *__qtablewidgetitem263 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(2, 0, __qtablewidgetitem263);
        QTableWidgetItem *__qtablewidgetitem264 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(2, 1, __qtablewidgetitem264);
        QTableWidgetItem *__qtablewidgetitem265 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(2, 2, __qtablewidgetitem265);
        QTableWidgetItem *__qtablewidgetitem266 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(3, 0, __qtablewidgetitem266);
        QTableWidgetItem *__qtablewidgetitem267 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(3, 1, __qtablewidgetitem267);
        QTableWidgetItem *__qtablewidgetitem268 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(3, 2, __qtablewidgetitem268);
        QTableWidgetItem *__qtablewidgetitem269 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(4, 0, __qtablewidgetitem269);
        QTableWidgetItem *__qtablewidgetitem270 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(4, 1, __qtablewidgetitem270);
        QTableWidgetItem *__qtablewidgetitem271 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(4, 2, __qtablewidgetitem271);
        QTableWidgetItem *__qtablewidgetitem272 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(5, 0, __qtablewidgetitem272);
        QTableWidgetItem *__qtablewidgetitem273 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(5, 1, __qtablewidgetitem273);
        QTableWidgetItem *__qtablewidgetitem274 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(5, 2, __qtablewidgetitem274);
        QTableWidgetItem *__qtablewidgetitem275 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(6, 0, __qtablewidgetitem275);
        QTableWidgetItem *__qtablewidgetitem276 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(6, 1, __qtablewidgetitem276);
        QTableWidgetItem *__qtablewidgetitem277 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(6, 2, __qtablewidgetitem277);
        QTableWidgetItem *__qtablewidgetitem278 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(7, 0, __qtablewidgetitem278);
        QTableWidgetItem *__qtablewidgetitem279 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(7, 1, __qtablewidgetitem279);
        QTableWidgetItem *__qtablewidgetitem280 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(7, 2, __qtablewidgetitem280);
        QTableWidgetItem *__qtablewidgetitem281 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(8, 0, __qtablewidgetitem281);
        QTableWidgetItem *__qtablewidgetitem282 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(8, 1, __qtablewidgetitem282);
        QTableWidgetItem *__qtablewidgetitem283 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(8, 2, __qtablewidgetitem283);
        QTableWidgetItem *__qtablewidgetitem284 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(9, 0, __qtablewidgetitem284);
        QTableWidgetItem *__qtablewidgetitem285 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(9, 1, __qtablewidgetitem285);
        QTableWidgetItem *__qtablewidgetitem286 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(9, 2, __qtablewidgetitem286);
        QTableWidgetItem *__qtablewidgetitem287 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(10, 0, __qtablewidgetitem287);
        QTableWidgetItem *__qtablewidgetitem288 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(10, 1, __qtablewidgetitem288);
        QTableWidgetItem *__qtablewidgetitem289 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(10, 2, __qtablewidgetitem289);
        QTableWidgetItem *__qtablewidgetitem290 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(11, 0, __qtablewidgetitem290);
        QTableWidgetItem *__qtablewidgetitem291 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(11, 1, __qtablewidgetitem291);
        QTableWidgetItem *__qtablewidgetitem292 = new QTableWidgetItem();
        tbl_chkerror_2->setItem(11, 2, __qtablewidgetitem292);
        tbl_chkerror_2->setObjectName(QString::fromUtf8("tbl_chkerror_2"));
        tbl_chkerror_2->setEnabled(false);
        tbl_chkerror_2->setGeometry(QRect(10, 120, 171, 441));
        tbl_chkerror_2->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_chkerror_2->horizontalHeader()->setDefaultSectionSize(50);
        tbl_chkerror_2->horizontalHeader()->setMinimumSectionSize(10);
        tbl_chkerror_2->verticalHeader()->setCascadingSectionResizes(true);
        tbl_chkerror_2->verticalHeader()->setMinimumSectionSize(10);

        horizontalLayout_3->addWidget(groupBox_9);

        groupBox_10 = new QGroupBox(widget3);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        label_26 = new QLabel(groupBox_10);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(40, 30, 121, 20));
        tbl_stderror_3 = new QTableWidget(groupBox_10);
        if (tbl_stderror_3->columnCount() < 3)
            tbl_stderror_3->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem293 = new QTableWidgetItem();
        tbl_stderror_3->setHorizontalHeaderItem(0, __qtablewidgetitem293);
        QTableWidgetItem *__qtablewidgetitem294 = new QTableWidgetItem();
        tbl_stderror_3->setHorizontalHeaderItem(1, __qtablewidgetitem294);
        QTableWidgetItem *__qtablewidgetitem295 = new QTableWidgetItem();
        tbl_stderror_3->setHorizontalHeaderItem(2, __qtablewidgetitem295);
        if (tbl_stderror_3->rowCount() < 1)
            tbl_stderror_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem296 = new QTableWidgetItem();
        tbl_stderror_3->setVerticalHeaderItem(0, __qtablewidgetitem296);
        QTableWidgetItem *__qtablewidgetitem297 = new QTableWidgetItem();
        tbl_stderror_3->setItem(0, 0, __qtablewidgetitem297);
        QTableWidgetItem *__qtablewidgetitem298 = new QTableWidgetItem();
        tbl_stderror_3->setItem(0, 1, __qtablewidgetitem298);
        QTableWidgetItem *__qtablewidgetitem299 = new QTableWidgetItem();
        tbl_stderror_3->setItem(0, 2, __qtablewidgetitem299);
        tbl_stderror_3->setObjectName(QString::fromUtf8("tbl_stderror_3"));
        tbl_stderror_3->setEnabled(false);
        tbl_stderror_3->setGeometry(QRect(10, 50, 171, 61));
        tbl_stderror_3->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_stderror_3->horizontalHeader()->setDefaultSectionSize(50);
        tbl_stderror_3->horizontalHeader()->setMinimumSectionSize(10);
        tbl_stderror_3->verticalHeader()->setCascadingSectionResizes(true);
        tbl_stderror_3->verticalHeader()->setMinimumSectionSize(10);
        tbl_chkerror_3 = new QTableWidget(groupBox_10);
        if (tbl_chkerror_3->columnCount() < 3)
            tbl_chkerror_3->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem300 = new QTableWidgetItem();
        tbl_chkerror_3->setHorizontalHeaderItem(0, __qtablewidgetitem300);
        QTableWidgetItem *__qtablewidgetitem301 = new QTableWidgetItem();
        tbl_chkerror_3->setHorizontalHeaderItem(1, __qtablewidgetitem301);
        QTableWidgetItem *__qtablewidgetitem302 = new QTableWidgetItem();
        tbl_chkerror_3->setHorizontalHeaderItem(2, __qtablewidgetitem302);
        if (tbl_chkerror_3->rowCount() < 12)
            tbl_chkerror_3->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem303 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(0, __qtablewidgetitem303);
        QTableWidgetItem *__qtablewidgetitem304 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(1, __qtablewidgetitem304);
        QTableWidgetItem *__qtablewidgetitem305 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(2, __qtablewidgetitem305);
        QTableWidgetItem *__qtablewidgetitem306 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(3, __qtablewidgetitem306);
        QTableWidgetItem *__qtablewidgetitem307 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(4, __qtablewidgetitem307);
        QTableWidgetItem *__qtablewidgetitem308 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(5, __qtablewidgetitem308);
        QTableWidgetItem *__qtablewidgetitem309 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(6, __qtablewidgetitem309);
        QTableWidgetItem *__qtablewidgetitem310 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(7, __qtablewidgetitem310);
        QTableWidgetItem *__qtablewidgetitem311 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(8, __qtablewidgetitem311);
        QTableWidgetItem *__qtablewidgetitem312 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(9, __qtablewidgetitem312);
        QTableWidgetItem *__qtablewidgetitem313 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(10, __qtablewidgetitem313);
        QTableWidgetItem *__qtablewidgetitem314 = new QTableWidgetItem();
        tbl_chkerror_3->setVerticalHeaderItem(11, __qtablewidgetitem314);
        QTableWidgetItem *__qtablewidgetitem315 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(0, 0, __qtablewidgetitem315);
        QTableWidgetItem *__qtablewidgetitem316 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(0, 1, __qtablewidgetitem316);
        QTableWidgetItem *__qtablewidgetitem317 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(0, 2, __qtablewidgetitem317);
        QTableWidgetItem *__qtablewidgetitem318 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(1, 0, __qtablewidgetitem318);
        QTableWidgetItem *__qtablewidgetitem319 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(1, 1, __qtablewidgetitem319);
        QTableWidgetItem *__qtablewidgetitem320 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(1, 2, __qtablewidgetitem320);
        QTableWidgetItem *__qtablewidgetitem321 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(2, 0, __qtablewidgetitem321);
        QTableWidgetItem *__qtablewidgetitem322 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(2, 1, __qtablewidgetitem322);
        QTableWidgetItem *__qtablewidgetitem323 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(2, 2, __qtablewidgetitem323);
        QTableWidgetItem *__qtablewidgetitem324 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(3, 0, __qtablewidgetitem324);
        QTableWidgetItem *__qtablewidgetitem325 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(3, 1, __qtablewidgetitem325);
        QTableWidgetItem *__qtablewidgetitem326 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(3, 2, __qtablewidgetitem326);
        QTableWidgetItem *__qtablewidgetitem327 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(4, 0, __qtablewidgetitem327);
        QTableWidgetItem *__qtablewidgetitem328 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(4, 1, __qtablewidgetitem328);
        QTableWidgetItem *__qtablewidgetitem329 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(4, 2, __qtablewidgetitem329);
        QTableWidgetItem *__qtablewidgetitem330 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(5, 0, __qtablewidgetitem330);
        QTableWidgetItem *__qtablewidgetitem331 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(5, 1, __qtablewidgetitem331);
        QTableWidgetItem *__qtablewidgetitem332 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(5, 2, __qtablewidgetitem332);
        QTableWidgetItem *__qtablewidgetitem333 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(6, 0, __qtablewidgetitem333);
        QTableWidgetItem *__qtablewidgetitem334 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(6, 1, __qtablewidgetitem334);
        QTableWidgetItem *__qtablewidgetitem335 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(6, 2, __qtablewidgetitem335);
        QTableWidgetItem *__qtablewidgetitem336 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(7, 0, __qtablewidgetitem336);
        QTableWidgetItem *__qtablewidgetitem337 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(7, 1, __qtablewidgetitem337);
        QTableWidgetItem *__qtablewidgetitem338 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(7, 2, __qtablewidgetitem338);
        QTableWidgetItem *__qtablewidgetitem339 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(8, 0, __qtablewidgetitem339);
        QTableWidgetItem *__qtablewidgetitem340 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(8, 1, __qtablewidgetitem340);
        QTableWidgetItem *__qtablewidgetitem341 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(8, 2, __qtablewidgetitem341);
        QTableWidgetItem *__qtablewidgetitem342 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(9, 0, __qtablewidgetitem342);
        QTableWidgetItem *__qtablewidgetitem343 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(9, 1, __qtablewidgetitem343);
        QTableWidgetItem *__qtablewidgetitem344 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(9, 2, __qtablewidgetitem344);
        QTableWidgetItem *__qtablewidgetitem345 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(10, 0, __qtablewidgetitem345);
        QTableWidgetItem *__qtablewidgetitem346 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(10, 1, __qtablewidgetitem346);
        QTableWidgetItem *__qtablewidgetitem347 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(10, 2, __qtablewidgetitem347);
        QTableWidgetItem *__qtablewidgetitem348 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(11, 0, __qtablewidgetitem348);
        QTableWidgetItem *__qtablewidgetitem349 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(11, 1, __qtablewidgetitem349);
        QTableWidgetItem *__qtablewidgetitem350 = new QTableWidgetItem();
        tbl_chkerror_3->setItem(11, 2, __qtablewidgetitem350);
        tbl_chkerror_3->setObjectName(QString::fromUtf8("tbl_chkerror_3"));
        tbl_chkerror_3->setEnabled(false);
        tbl_chkerror_3->setGeometry(QRect(10, 120, 171, 441));
        tbl_chkerror_3->horizontalHeader()->setCascadingSectionResizes(true);
        tbl_chkerror_3->horizontalHeader()->setDefaultSectionSize(50);
        tbl_chkerror_3->horizontalHeader()->setMinimumSectionSize(10);
        tbl_chkerror_3->verticalHeader()->setCascadingSectionResizes(true);
        tbl_chkerror_3->verticalHeader()->setMinimumSectionSize(10);

        horizontalLayout_3->addWidget(groupBox_10);


        horizontalLayout_4->addWidget(frame_result);


        retranslateUi(PlaCompDlgClass);

        QMetaObject::connectSlotsByName(PlaCompDlgClass);
    } // setupUi

    void retranslateUi(QWidget *PlaCompDlgClass)
    {
        PlaCompDlgClass->setWindowTitle(QApplication::translate("PlaCompDlgClass", "Comparing method of platinum resistance checking", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p><span style=\" color:#0000ff;\">Step:1.Configure parameter first 2.Input data 3.Generate Excel 4.Save data 5.Exit</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btn_param->setText(QApplication::translate("PlaCompDlgClass", "Parameter", 0, QApplication::UnicodeUTF8));
        btn_save->setText(QApplication::translate("PlaCompDlgClass", "Save", 0, QApplication::UnicodeUTF8));
        btn_exit->setText(QApplication::translate("PlaCompDlgClass", "Exit", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600;\">Input Data</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        gBox_infirst->setTitle(QApplication::translate("PlaCompDlgClass", "First temperature difference", 0, QApplication::UnicodeUTF8));
        btn_read_1->setText(QApplication::translate("PlaCompDlgClass", "Read", 0, QApplication::UnicodeUTF8));
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

        btn_clear_1->setText(QApplication::translate("PlaCompDlgClass", "Clear", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">std temperature</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt;\">sensor to be checked</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\">(Input R value \316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tbl_in_1->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("PlaCompDlgClass", "Serial", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tbl_in_1->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tbl_in_1->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = tbl_in_1->isSortingEnabled();
        tbl_in_1->setSortingEnabled(false);
        tbl_in_1->setSortingEnabled(__sortingEnabled1);

        gBox_insec->setTitle(QApplication::translate("PlaCompDlgClass", "Second temperature difference", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">std temperature</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btn_read_2->setText(QApplication::translate("PlaCompDlgClass", "Read", 0, QApplication::UnicodeUTF8));
        btn_clear_2->setText(QApplication::translate("PlaCompDlgClass", "Clear", 0, QApplication::UnicodeUTF8));
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

        label_6->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt;\">sensor to be checked</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\">(Input R value \316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tbl_in_2->horizontalHeaderItem(0);
        ___qtablewidgetitem11->setText(QApplication::translate("PlaCompDlgClass", "Serial", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tbl_in_2->horizontalHeaderItem(1);
        ___qtablewidgetitem12->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tbl_in_2->horizontalHeaderItem(2);
        ___qtablewidgetitem13->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled3 = tbl_in_2->isSortingEnabled();
        tbl_in_2->setSortingEnabled(false);
        tbl_in_2->setSortingEnabled(__sortingEnabled3);

        gBox_inthird->setTitle(QApplication::translate("PlaCompDlgClass", "Third temperature difference", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">std temperature</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btn_read_3->setText(QApplication::translate("PlaCompDlgClass", "Read", 0, QApplication::UnicodeUTF8));
        btn_clear_3->setText(QApplication::translate("PlaCompDlgClass", "Clear", 0, QApplication::UnicodeUTF8));
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

        label_7->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt;\">sensor to be checked</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\">(Input R value \316\251)</p></body></html>", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tbl_in_3->horizontalHeaderItem(0);
        ___qtablewidgetitem18->setText(QApplication::translate("PlaCompDlgClass", "Serial", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tbl_in_3->horizontalHeaderItem(1);
        ___qtablewidgetitem19->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tbl_in_3->horizontalHeaderItem(2);
        ___qtablewidgetitem20->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled5 = tbl_in_3->isSortingEnabled();
        tbl_in_3->setSortingEnabled(false);
        tbl_in_3->setSortingEnabled(__sortingEnabled5);

        label_23->setText(QApplication::translate("PlaCompDlgClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:11pt; font-weight:600;\">Result</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("PlaCompDlgClass", "First temperature difference", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tbl_chkerror_1->horizontalHeaderItem(0);
        ___qtablewidgetitem21->setText(QApplication::translate("PlaCompDlgClass", "In\n"
"T\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tbl_chkerror_1->horizontalHeaderItem(1);
        ___qtablewidgetitem22->setText(QApplication::translate("PlaCompDlgClass", "Out\n"
"T\n"
"(\342\204\203)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tbl_chkerror_1->horizontalHeaderItem(2);
        ___qtablewidgetitem23->setText(QApplication::translate("PlaCompDlgClass", "Error\n"
"(%)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled6 = tbl_chkerror_1->isSortingEnabled();
        tbl_chkerror_1->setSortingEnabled(false);
        tbl_chkerror_1->setSortingEnabled(__sortingEnabled6);

        QTableWidgetItem *___qtablewidgetitem24 = tbl_stderror_1->horizontalHeaderItem(0);
        ___qtablewidgetitem24->setText(QApplication::translate("PlaCompDlgClass", "In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tbl_stderror_1->horizontalHeaderItem(1);
        ___qtablewidgetitem25->setText(QApplication::translate("PlaCompDlgClass", "Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tbl_stderror_1->horizontalHeaderItem(2);
        ___qtablewidgetitem26->setText(QApplication::translate("PlaCompDlgClass", "\316\224T", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled7 = tbl_stderror_1->isSortingEnabled();
        tbl_stderror_1->setSortingEnabled(false);
        tbl_stderror_1->setSortingEnabled(__sortingEnabled7);

        label_28->setText(QApplication::translate("PlaCompDlgClass", "Limit of error \342\204\203/%", 0, QApplication::UnicodeUTF8));
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

    } // retranslateUi

};

namespace Ui {
    class PlaCompDlgClass: public Ui_PlaCompDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TVERCOMP_H
