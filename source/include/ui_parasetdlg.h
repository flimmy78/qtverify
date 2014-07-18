/********************************************************************************
** Form generated from reading UI file 'parasetdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARASETDLG_H
#define UI_PARASETDLG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParaSetDlgClass
{
public:
    QGridLayout *gridLayout_12;
    QGroupBox *gBox_Head;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QComboBox *cmbStandard;
    QLabel *label_4;
    QComboBox *cmbModel;
    QGridLayout *gridLayout_4;
    QLabel *label_5;
    QComboBox *cmbFlow;
    QLabel *label_6;
    QComboBox *cmbCollectCode;
    QGridLayout *gridLayout_6;
    QLabel *label_9;
    QComboBox *cmbManufacture;
    QLabel *label_10;
    QComboBox *cmbVerifyCompany;
    QGridLayout *gridLayout_5;
    QComboBox *cmbVerifyPerson;
    QLabel *label_7;
    QLabel *label_8;
    QComboBox *cmbGrade;
    QGroupBox *gBox_UpperFlowLmt;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_11;
    QLineEdit *lineEdit_Upper_1;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEdit_Upper_2;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEdit_Upper_3;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *lineEdit_Upper_4;
    QGroupBox *gBox_FlowPnt;
    QGridLayout *gridLayout_10;
    QLabel *label_12;
    QGridLayout *gridLayout_9;
    QSpacerItem *horizontalSpacer_13;
    QLineEdit *lineEdit_Valve_2;
    QSpacerItem *horizontalSpacer_12;
    QLineEdit *lineEdit_Valve_1;
    QLineEdit *lineEdit_Quantity_4;
    QSpacerItem *horizontalSpacer_11;
    QLineEdit *lineEdit_Quantity_3;
    QSpacerItem *horizontalSpacer_10;
    QLineEdit *lineEdit_Quantity_2;
    QSpacerItem *horizontalSpacer_9;
    QLineEdit *lineEdit_Quantity_1;
    QLineEdit *lnEdit_Flow4;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *lnEdit_Flow3;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *lnEdit_Flow2;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *lnEdit_Flow1;
    QComboBox *cBox_seq_4;
    QComboBox *cBox_seq_3;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *horizontalSpacer_16;
    QComboBox *cBox_seq_2;
    QSpacerItem *horizontalSpacer_15;
    QComboBox *cBox_seq_1;
    QLineEdit *lineEdit_Valve_4;
    QSpacerItem *horizontalSpacer_14;
    QLineEdit *lineEdit_Valve_3;
    QLabel *label_16;
    QLabel *label_13;
    QLabel *label_17;
    QLabel *label_14;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_10;
    Q3ButtonGroup *buttonGroup_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *tBtn_autoPick_true;
    QRadioButton *tBtn_autoPick_false;
    QSpacerItem *horizontalSpacer_22;
    Q3ButtonGroup *buttonGroup;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *tBtn_totalverify_true;
    QRadioButton *tBtn_totalverify_false;
    QSpacerItem *horizontalSpacer_23;
    Q3ButtonGroup *buttonGroup_4;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *tBtn_adjustError_true;
    QRadioButton *tBtn_adjustError_false;
    QSpacerItem *horizontalSpacer_24;
    Q3ButtonGroup *buttonGroup_5;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *tBtn_writeNum_true;
    QRadioButton *tBtn_writeNum_false;
    QHBoxLayout *horizontalLayout_4;
    Q3ButtonGroup *buttonGroup_6;
    QGridLayout *gridLayout;
    QRadioButton *tBtn_continuous_true;
    QRadioButton *tBtn_continuous_false;
    QSpacerItem *horizontalSpacer_18;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_sc_flow;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *lineEdit_sc_thermal;
    QSpacerItem *horizontalSpacer_19;
    Q3ButtonGroup *buttonGroup_7;
    QGridLayout *gridLayout_11;
    QLabel *label_19;
    QLineEdit *lineEdit_exTime;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnSave;
    QPushButton *btnExit;

    void setupUi(QWidget *ParaSetDlgClass)
    {
        if (ParaSetDlgClass->objectName().isEmpty())
            ParaSetDlgClass->setObjectName(QString::fromUtf8("ParaSetDlgClass"));
        ParaSetDlgClass->resize(761, 597);
        gridLayout_12 = new QGridLayout(ParaSetDlgClass);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gBox_Head = new QGroupBox(ParaSetDlgClass);
        gBox_Head->setObjectName(QString::fromUtf8("gBox_Head"));
        gridLayout_7 = new QGridLayout(gBox_Head);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_3 = new QLabel(gBox_Head);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        cmbStandard = new QComboBox(gBox_Head);
        cmbStandard->setObjectName(QString::fromUtf8("cmbStandard"));

        gridLayout_3->addWidget(cmbStandard, 0, 1, 1, 1);

        label_4 = new QLabel(gBox_Head);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        cmbModel = new QComboBox(gBox_Head);
        cmbModel->setObjectName(QString::fromUtf8("cmbModel"));

        gridLayout_3->addWidget(cmbModel, 1, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_3, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_5 = new QLabel(gBox_Head);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(label_5, 0, 0, 1, 1);

        cmbFlow = new QComboBox(gBox_Head);
        cmbFlow->setObjectName(QString::fromUtf8("cmbFlow"));

        gridLayout_4->addWidget(cmbFlow, 0, 1, 1, 1);

        label_6 = new QLabel(gBox_Head);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(label_6, 1, 0, 1, 1);

        cmbCollectCode = new QComboBox(gBox_Head);
        cmbCollectCode->setObjectName(QString::fromUtf8("cmbCollectCode"));

        gridLayout_4->addWidget(cmbCollectCode, 1, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_4, 0, 1, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_9 = new QLabel(gBox_Head);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(label_9, 0, 0, 1, 1);

        cmbManufacture = new QComboBox(gBox_Head);
        cmbManufacture->setObjectName(QString::fromUtf8("cmbManufacture"));

        gridLayout_6->addWidget(cmbManufacture, 0, 1, 1, 1);

        label_10 = new QLabel(gBox_Head);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(label_10, 1, 0, 1, 1);

        cmbVerifyCompany = new QComboBox(gBox_Head);
        cmbVerifyCompany->setObjectName(QString::fromUtf8("cmbVerifyCompany"));

        gridLayout_6->addWidget(cmbVerifyCompany, 1, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_6, 0, 2, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        cmbVerifyPerson = new QComboBox(gBox_Head);
        cmbVerifyPerson->setObjectName(QString::fromUtf8("cmbVerifyPerson"));

        gridLayout_5->addWidget(cmbVerifyPerson, 1, 1, 1, 1);

        label_7 = new QLabel(gBox_Head);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_7, 0, 0, 1, 1);

        label_8 = new QLabel(gBox_Head);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_8, 1, 0, 1, 1);

        cmbGrade = new QComboBox(gBox_Head);
        cmbGrade->setObjectName(QString::fromUtf8("cmbGrade"));

        gridLayout_5->addWidget(cmbGrade, 0, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_5, 0, 3, 1, 1);


        gridLayout_12->addWidget(gBox_Head, 0, 0, 1, 1);

        gBox_UpperFlowLmt = new QGroupBox(ParaSetDlgClass);
        gBox_UpperFlowLmt->setObjectName(QString::fromUtf8("gBox_UpperFlowLmt"));
        gridLayout_8 = new QGridLayout(gBox_UpperFlowLmt);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_11 = new QLabel(gBox_UpperFlowLmt);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_3->addWidget(label_11);

        lineEdit_Upper_1 = new QLineEdit(gBox_UpperFlowLmt);
        lineEdit_Upper_1->setObjectName(QString::fromUtf8("lineEdit_Upper_1"));

        horizontalLayout_3->addWidget(lineEdit_Upper_1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        lineEdit_Upper_2 = new QLineEdit(gBox_UpperFlowLmt);
        lineEdit_Upper_2->setObjectName(QString::fromUtf8("lineEdit_Upper_2"));
        QPalette palette;
        QBrush brush(QColor(85, 85, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        lineEdit_Upper_2->setPalette(palette);

        horizontalLayout_3->addWidget(lineEdit_Upper_2);

        horizontalSpacer_4 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        lineEdit_Upper_3 = new QLineEdit(gBox_UpperFlowLmt);
        lineEdit_Upper_3->setObjectName(QString::fromUtf8("lineEdit_Upper_3"));

        horizontalLayout_3->addWidget(lineEdit_Upper_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        lineEdit_Upper_4 = new QLineEdit(gBox_UpperFlowLmt);
        lineEdit_Upper_4->setObjectName(QString::fromUtf8("lineEdit_Upper_4"));

        horizontalLayout_3->addWidget(lineEdit_Upper_4);


        gridLayout_8->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        gridLayout_12->addWidget(gBox_UpperFlowLmt, 1, 0, 1, 1);

        gBox_FlowPnt = new QGroupBox(ParaSetDlgClass);
        gBox_FlowPnt->setObjectName(QString::fromUtf8("gBox_FlowPnt"));
        gridLayout_10 = new QGridLayout(gBox_FlowPnt);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        label_12 = new QLabel(gBox_FlowPnt);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_10->addWidget(label_12, 0, 0, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        horizontalSpacer_13 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_13, 2, 3, 1, 1);

        lineEdit_Valve_2 = new QLineEdit(gBox_FlowPnt);
        lineEdit_Valve_2->setObjectName(QString::fromUtf8("lineEdit_Valve_2"));
        lineEdit_Valve_2->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lineEdit_Valve_2, 2, 2, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(13, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_12, 2, 1, 1, 1);

        lineEdit_Valve_1 = new QLineEdit(gBox_FlowPnt);
        lineEdit_Valve_1->setObjectName(QString::fromUtf8("lineEdit_Valve_1"));
        lineEdit_Valve_1->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lineEdit_Valve_1, 2, 0, 1, 1);

        lineEdit_Quantity_4 = new QLineEdit(gBox_FlowPnt);
        lineEdit_Quantity_4->setObjectName(QString::fromUtf8("lineEdit_Quantity_4"));
        lineEdit_Quantity_4->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lineEdit_Quantity_4, 1, 6, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_11, 1, 5, 1, 1);

        lineEdit_Quantity_3 = new QLineEdit(gBox_FlowPnt);
        lineEdit_Quantity_3->setObjectName(QString::fromUtf8("lineEdit_Quantity_3"));
        lineEdit_Quantity_3->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lineEdit_Quantity_3, 1, 4, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_10, 1, 3, 1, 1);

        lineEdit_Quantity_2 = new QLineEdit(gBox_FlowPnt);
        lineEdit_Quantity_2->setObjectName(QString::fromUtf8("lineEdit_Quantity_2"));
        lineEdit_Quantity_2->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lineEdit_Quantity_2, 1, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(13, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_9, 1, 1, 1, 1);

        lineEdit_Quantity_1 = new QLineEdit(gBox_FlowPnt);
        lineEdit_Quantity_1->setObjectName(QString::fromUtf8("lineEdit_Quantity_1"));
        lineEdit_Quantity_1->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lineEdit_Quantity_1, 1, 0, 1, 1);

        lnEdit_Flow4 = new QLineEdit(gBox_FlowPnt);
        lnEdit_Flow4->setObjectName(QString::fromUtf8("lnEdit_Flow4"));
        lnEdit_Flow4->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lnEdit_Flow4, 0, 6, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_8, 0, 5, 1, 1);

        lnEdit_Flow3 = new QLineEdit(gBox_FlowPnt);
        lnEdit_Flow3->setObjectName(QString::fromUtf8("lnEdit_Flow3"));
        lnEdit_Flow3->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lnEdit_Flow3, 0, 4, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_7, 0, 3, 1, 1);

        lnEdit_Flow2 = new QLineEdit(gBox_FlowPnt);
        lnEdit_Flow2->setObjectName(QString::fromUtf8("lnEdit_Flow2"));
        lnEdit_Flow2->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lnEdit_Flow2, 0, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(13, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        lnEdit_Flow1 = new QLineEdit(gBox_FlowPnt);
        lnEdit_Flow1->setObjectName(QString::fromUtf8("lnEdit_Flow1"));
        lnEdit_Flow1->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lnEdit_Flow1, 0, 0, 1, 1);

        cBox_seq_4 = new QComboBox(gBox_FlowPnt);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../none.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cBox_seq_4->addItem(icon, QString());
        cBox_seq_4->addItem(QString());
        cBox_seq_4->addItem(QString());
        cBox_seq_4->addItem(QString());
        cBox_seq_4->addItem(QString());
        cBox_seq_4->setObjectName(QString::fromUtf8("cBox_seq_4"));

        gridLayout_9->addWidget(cBox_seq_4, 3, 6, 1, 1);

        cBox_seq_3 = new QComboBox(gBox_FlowPnt);
        cBox_seq_3->addItem(icon, QString());
        cBox_seq_3->addItem(QString());
        cBox_seq_3->addItem(QString());
        cBox_seq_3->addItem(QString());
        cBox_seq_3->addItem(QString());
        cBox_seq_3->setObjectName(QString::fromUtf8("cBox_seq_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cBox_seq_3->sizePolicy().hasHeightForWidth());
        cBox_seq_3->setSizePolicy(sizePolicy1);

        gridLayout_9->addWidget(cBox_seq_3, 3, 4, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(18, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_17, 3, 5, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(18, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_16, 3, 3, 1, 1);

        cBox_seq_2 = new QComboBox(gBox_FlowPnt);
        cBox_seq_2->addItem(icon, QString());
        cBox_seq_2->addItem(QString());
        cBox_seq_2->addItem(QString());
        cBox_seq_2->addItem(QString());
        cBox_seq_2->addItem(QString());
        cBox_seq_2->setObjectName(QString::fromUtf8("cBox_seq_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cBox_seq_2->sizePolicy().hasHeightForWidth());
        cBox_seq_2->setSizePolicy(sizePolicy2);

        gridLayout_9->addWidget(cBox_seq_2, 3, 2, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(13, 17, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_15, 3, 1, 1, 1);

        cBox_seq_1 = new QComboBox(gBox_FlowPnt);
        cBox_seq_1->addItem(icon, QString());
        cBox_seq_1->addItem(QString());
        cBox_seq_1->addItem(QString());
        cBox_seq_1->addItem(QString());
        cBox_seq_1->addItem(QString());
        cBox_seq_1->setObjectName(QString::fromUtf8("cBox_seq_1"));
        sizePolicy1.setHeightForWidth(cBox_seq_1->sizePolicy().hasHeightForWidth());
        cBox_seq_1->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        font.setKerning(false);
        cBox_seq_1->setFont(font);
        cBox_seq_1->setAcceptDrops(false);
        cBox_seq_1->setLayoutDirection(Qt::LeftToRight);
        cBox_seq_1->setAutoFillBackground(false);
        cBox_seq_1->setFrame(true);

        gridLayout_9->addWidget(cBox_seq_1, 3, 0, 1, 1);

        lineEdit_Valve_4 = new QLineEdit(gBox_FlowPnt);
        lineEdit_Valve_4->setObjectName(QString::fromUtf8("lineEdit_Valve_4"));
        lineEdit_Valve_4->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lineEdit_Valve_4, 2, 6, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_14, 2, 5, 1, 1);

        lineEdit_Valve_3 = new QLineEdit(gBox_FlowPnt);
        lineEdit_Valve_3->setObjectName(QString::fromUtf8("lineEdit_Valve_3"));
        lineEdit_Valve_3->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lineEdit_Valve_3, 2, 4, 1, 1);


        gridLayout_10->addLayout(gridLayout_9, 0, 1, 4, 1);

        label_16 = new QLabel(gBox_FlowPnt);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_10->addWidget(label_16, 0, 2, 1, 1);

        label_13 = new QLabel(gBox_FlowPnt);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_10->addWidget(label_13, 1, 0, 1, 1);

        label_17 = new QLabel(gBox_FlowPnt);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_10->addWidget(label_17, 1, 2, 1, 1);

        label_14 = new QLabel(gBox_FlowPnt);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_10->addWidget(label_14, 2, 0, 1, 1);

        label_15 = new QLabel(gBox_FlowPnt);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_10->addWidget(label_15, 3, 0, 1, 1);


        gridLayout_12->addWidget(gBox_FlowPnt, 2, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        buttonGroup_2 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
        buttonGroup_2->setColumnLayout(0, Qt::Vertical);
        horizontalLayout = new QHBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(buttonGroup_2->layout());
        if (boxlayout)
            boxlayout->addLayout(horizontalLayout);
        horizontalLayout->setAlignment(Qt::AlignTop);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tBtn_autoPick_true = new QRadioButton(buttonGroup_2);
        tBtn_autoPick_true->setObjectName(QString::fromUtf8("tBtn_autoPick_true"));
        tBtn_autoPick_true->setChecked(true);

        horizontalLayout->addWidget(tBtn_autoPick_true);

        tBtn_autoPick_false = new QRadioButton(buttonGroup_2);
        tBtn_autoPick_false->setObjectName(QString::fromUtf8("tBtn_autoPick_false"));

        horizontalLayout->addWidget(tBtn_autoPick_false);


        horizontalLayout_10->addWidget(buttonGroup_2);

        horizontalSpacer_22 = new QSpacerItem(28, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_22);

        buttonGroup = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->setColumnLayout(0, Qt::Vertical);
        horizontalLayout_6 = new QHBoxLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(buttonGroup->layout());
        if (boxlayout1)
            boxlayout1->addLayout(horizontalLayout_6);
        horizontalLayout_6->setAlignment(Qt::AlignTop);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        tBtn_totalverify_true = new QRadioButton(buttonGroup);
        tBtn_totalverify_true->setObjectName(QString::fromUtf8("tBtn_totalverify_true"));
        tBtn_totalverify_true->setChecked(true);

        horizontalLayout_6->addWidget(tBtn_totalverify_true);

        tBtn_totalverify_false = new QRadioButton(buttonGroup);
        tBtn_totalverify_false->setObjectName(QString::fromUtf8("tBtn_totalverify_false"));

        horizontalLayout_6->addWidget(tBtn_totalverify_false);


        horizontalLayout_10->addWidget(buttonGroup);

        horizontalSpacer_23 = new QSpacerItem(28, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_23);

        buttonGroup_4 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_4->setObjectName(QString::fromUtf8("buttonGroup_4"));
        buttonGroup_4->setColumnLayout(0, Qt::Vertical);
        horizontalLayout_8 = new QHBoxLayout();
        QBoxLayout *boxlayout2 = qobject_cast<QBoxLayout *>(buttonGroup_4->layout());
        if (boxlayout2)
            boxlayout2->addLayout(horizontalLayout_8);
        horizontalLayout_8->setAlignment(Qt::AlignTop);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        tBtn_adjustError_true = new QRadioButton(buttonGroup_4);
        tBtn_adjustError_true->setObjectName(QString::fromUtf8("tBtn_adjustError_true"));
        tBtn_adjustError_true->setChecked(true);

        horizontalLayout_8->addWidget(tBtn_adjustError_true);

        tBtn_adjustError_false = new QRadioButton(buttonGroup_4);
        tBtn_adjustError_false->setObjectName(QString::fromUtf8("tBtn_adjustError_false"));

        horizontalLayout_8->addWidget(tBtn_adjustError_false);


        horizontalLayout_10->addWidget(buttonGroup_4);

        horizontalSpacer_24 = new QSpacerItem(28, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_24);

        buttonGroup_5 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_5->setObjectName(QString::fromUtf8("buttonGroup_5"));
        buttonGroup_5->setColumnLayout(0, Qt::Vertical);
        horizontalLayout_7 = new QHBoxLayout();
        QBoxLayout *boxlayout3 = qobject_cast<QBoxLayout *>(buttonGroup_5->layout());
        if (boxlayout3)
            boxlayout3->addLayout(horizontalLayout_7);
        horizontalLayout_7->setAlignment(Qt::AlignTop);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        tBtn_writeNum_true = new QRadioButton(buttonGroup_5);
        tBtn_writeNum_true->setObjectName(QString::fromUtf8("tBtn_writeNum_true"));
        tBtn_writeNum_true->setChecked(true);

        horizontalLayout_7->addWidget(tBtn_writeNum_true);

        tBtn_writeNum_false = new QRadioButton(buttonGroup_5);
        tBtn_writeNum_false->setObjectName(QString::fromUtf8("tBtn_writeNum_false"));

        horizontalLayout_7->addWidget(tBtn_writeNum_false);


        horizontalLayout_10->addWidget(buttonGroup_5);


        gridLayout_12->addLayout(horizontalLayout_10, 3, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        buttonGroup_6 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_6->setObjectName(QString::fromUtf8("buttonGroup_6"));
        buttonGroup_6->setColumnLayout(0, Qt::Vertical);
        gridLayout = new QGridLayout();
        QBoxLayout *boxlayout4 = qobject_cast<QBoxLayout *>(buttonGroup_6->layout());
        if (boxlayout4)
            boxlayout4->addLayout(gridLayout);
        gridLayout->setAlignment(Qt::AlignTop);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tBtn_continuous_true = new QRadioButton(buttonGroup_6);
        tBtn_continuous_true->setObjectName(QString::fromUtf8("tBtn_continuous_true"));
        tBtn_continuous_true->setChecked(true);

        gridLayout->addWidget(tBtn_continuous_true, 0, 0, 1, 1);

        tBtn_continuous_false = new QRadioButton(buttonGroup_6);
        tBtn_continuous_false->setObjectName(QString::fromUtf8("tBtn_continuous_false"));

        gridLayout->addWidget(tBtn_continuous_false, 0, 1, 1, 1);


        horizontalLayout_4->addWidget(buttonGroup_6);

        horizontalSpacer_18 = new QSpacerItem(53, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_18);

        groupBox_4 = new QGroupBox(ParaSetDlgClass);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy2.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy2);
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lineEdit_sc_flow = new QLineEdit(groupBox_4);
        lineEdit_sc_flow->setObjectName(QString::fromUtf8("lineEdit_sc_flow"));

        gridLayout_2->addWidget(lineEdit_sc_flow, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 3, 1, 1);

        lineEdit_sc_thermal = new QLineEdit(groupBox_4);
        lineEdit_sc_thermal->setObjectName(QString::fromUtf8("lineEdit_sc_thermal"));

        gridLayout_2->addWidget(lineEdit_sc_thermal, 0, 4, 1, 1);


        horizontalLayout_4->addWidget(groupBox_4);

        horizontalSpacer_19 = new QSpacerItem(90, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_19);

        buttonGroup_7 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_7->setObjectName(QString::fromUtf8("buttonGroup_7"));
        buttonGroup_7->setColumnLayout(0, Qt::Vertical);
        gridLayout_11 = new QGridLayout();
        QBoxLayout *boxlayout5 = qobject_cast<QBoxLayout *>(buttonGroup_7->layout());
        if (boxlayout5)
            boxlayout5->addLayout(gridLayout_11);
        gridLayout_11->setAlignment(Qt::AlignTop);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        label_19 = new QLabel(buttonGroup_7);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        QPalette palette1;
        QBrush brush1(QColor(170, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        label_19->setPalette(palette1);

        gridLayout_11->addWidget(label_19, 0, 0, 1, 1);

        lineEdit_exTime = new QLineEdit(buttonGroup_7);
        lineEdit_exTime->setObjectName(QString::fromUtf8("lineEdit_exTime"));

        gridLayout_11->addWidget(lineEdit_exTime, 0, 1, 1, 1);


        horizontalLayout_4->addWidget(buttonGroup_7);


        gridLayout_12->addLayout(horizontalLayout_4, 4, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(13, 28, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnSave = new QPushButton(ParaSetDlgClass);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        sizePolicy2.setHeightForWidth(btnSave->sizePolicy().hasHeightForWidth());
        btnSave->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(btnSave);

        btnExit = new QPushButton(ParaSetDlgClass);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        sizePolicy2.setHeightForWidth(btnExit->sizePolicy().hasHeightForWidth());
        btnExit->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(btnExit);


        gridLayout_12->addLayout(horizontalLayout_2, 5, 0, 1, 1);


        retranslateUi(ParaSetDlgClass);

        cBox_seq_4->setCurrentIndex(0);
        cBox_seq_3->setCurrentIndex(0);
        cBox_seq_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ParaSetDlgClass);
    } // setupUi

    void retranslateUi(QWidget *ParaSetDlgClass)
    {
        ParaSetDlgClass->setWindowTitle(QApplication::translate("ParaSetDlgClass", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        gBox_Head->setTitle(QApplication::translate("ParaSetDlgClass", "\346\243\200\345\256\232\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ParaSetDlgClass", "\350\247\204\346\240\274", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ParaSetDlgClass", "\345\236\213\345\217\267", 0, QApplication::UnicodeUTF8));
        cmbModel->clear();
        cmbModel->insertItems(0, QStringList()
         << QApplication::translate("ParaSetDlgClass", "\345\236\213\345\217\2671", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "\345\236\213\345\217\2672", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "\345\236\213\345\217\2673", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("ParaSetDlgClass", "\345\270\270\347\224\250\346\265\201\351\207\217", 0, QApplication::UnicodeUTF8));
        cmbFlow->clear();
        cmbFlow->insertItems(0, QStringList()
         << QApplication::translate("ParaSetDlgClass", "2.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "0.75", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "0.25", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "0.05", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("ParaSetDlgClass", "\351\207\207\351\233\206\344\273\243\347\240\201", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ParaSetDlgClass", "\345\210\266\351\200\240\345\215\225\344\275\215", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ParaSetDlgClass", "\351\200\201\346\243\200\345\215\225\344\275\215", 0, QApplication::UnicodeUTF8));
        cmbVerifyCompany->clear();
        cmbVerifyCompany->insertItems(0, QStringList()
         << QApplication::translate("ParaSetDlgClass", "\345\261\261\344\270\234\350\256\241\351\207\217\351\231\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "\347\203\237\345\217\260\350\256\241\351\207\217\351\231\242", 0, QApplication::UnicodeUTF8)
        );
        cmbVerifyPerson->clear();
        cmbVerifyPerson->insertItems(0, QStringList()
         << QApplication::translate("ParaSetDlgClass", "\346\243\200\346\265\213\345\221\2301", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "\346\243\200\346\265\213\345\221\2302", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "\346\243\200\346\265\213\345\221\2303", 0, QApplication::UnicodeUTF8)
        );
        label_7->setText(QApplication::translate("ParaSetDlgClass", "\350\256\241\351\207\217\347\255\211\347\272\247", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ParaSetDlgClass", "\346\243\200\346\265\213\345\221\230", 0, QApplication::UnicodeUTF8));
        cmbGrade->clear();
        cmbGrade->insertItems(0, QStringList()
         << QApplication::translate("ParaSetDlgClass", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "3", 0, QApplication::UnicodeUTF8)
        );
        gBox_UpperFlowLmt->setTitle(QApplication::translate("ParaSetDlgClass", "\346\216\247\345\210\266\351\230\200\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("ParaSetDlgClass", "\344\270\212\351\231\220\346\265\201\351\207\217\345\200\274", 0, QApplication::UnicodeUTF8));
        gBox_FlowPnt->setTitle(QApplication::translate("ParaSetDlgClass", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("ParaSetDlgClass", "\346\265\201\351\207\217\347\202\271", 0, QApplication::UnicodeUTF8));
        lineEdit_Valve_2->setText(QApplication::translate("ParaSetDlgClass", "\344\270\255\344\270\200", 0, QApplication::UnicodeUTF8));
        lineEdit_Valve_1->setText(QApplication::translate("ParaSetDlgClass", "\345\244\247", 0, QApplication::UnicodeUTF8));
        lineEdit_Quantity_4->setText(QApplication::translate("ParaSetDlgClass", "5", 0, QApplication::UnicodeUTF8));
        lineEdit_Quantity_3->setText(QApplication::translate("ParaSetDlgClass", "10", 0, QApplication::UnicodeUTF8));
        lineEdit_Quantity_2->setText(QApplication::translate("ParaSetDlgClass", "20", 0, QApplication::UnicodeUTF8));
        lineEdit_Quantity_1->setText(QApplication::translate("ParaSetDlgClass", "50", 0, QApplication::UnicodeUTF8));
        lnEdit_Flow4->setText(QApplication::translate("ParaSetDlgClass", "0.05", 0, QApplication::UnicodeUTF8));
        lnEdit_Flow3->setText(QApplication::translate("ParaSetDlgClass", "0.25", 0, QApplication::UnicodeUTF8));
        lnEdit_Flow2->setText(QApplication::translate("ParaSetDlgClass", "0.75", 0, QApplication::UnicodeUTF8));
        lnEdit_Flow1->setText(QApplication::translate("ParaSetDlgClass", "2.5", 0, QApplication::UnicodeUTF8));
        cBox_seq_4->setItemText(0, QApplication::translate("ParaSetDlgClass", "\346\227\240", 0, QApplication::UnicodeUTF8));
        cBox_seq_4->setItemText(1, QApplication::translate("ParaSetDlgClass", "      1", 0, QApplication::UnicodeUTF8));
        cBox_seq_4->setItemText(2, QApplication::translate("ParaSetDlgClass", "      2", 0, QApplication::UnicodeUTF8));
        cBox_seq_4->setItemText(3, QApplication::translate("ParaSetDlgClass", "      3", 0, QApplication::UnicodeUTF8));
        cBox_seq_4->setItemText(4, QApplication::translate("ParaSetDlgClass", "      4", 0, QApplication::UnicodeUTF8));

        cBox_seq_3->setItemText(0, QApplication::translate("ParaSetDlgClass", "\346\227\240", 0, QApplication::UnicodeUTF8));
        cBox_seq_3->setItemText(1, QApplication::translate("ParaSetDlgClass", "      1", 0, QApplication::UnicodeUTF8));
        cBox_seq_3->setItemText(2, QApplication::translate("ParaSetDlgClass", "      2", 0, QApplication::UnicodeUTF8));
        cBox_seq_3->setItemText(3, QApplication::translate("ParaSetDlgClass", "      3", 0, QApplication::UnicodeUTF8));
        cBox_seq_3->setItemText(4, QApplication::translate("ParaSetDlgClass", "      4", 0, QApplication::UnicodeUTF8));

        cBox_seq_2->setItemText(0, QApplication::translate("ParaSetDlgClass", "\346\227\240", 0, QApplication::UnicodeUTF8));
        cBox_seq_2->setItemText(1, QApplication::translate("ParaSetDlgClass", "      1", 0, QApplication::UnicodeUTF8));
        cBox_seq_2->setItemText(2, QApplication::translate("ParaSetDlgClass", "      2", 0, QApplication::UnicodeUTF8));
        cBox_seq_2->setItemText(3, QApplication::translate("ParaSetDlgClass", "      3", 0, QApplication::UnicodeUTF8));
        cBox_seq_2->setItemText(4, QApplication::translate("ParaSetDlgClass", "      4", 0, QApplication::UnicodeUTF8));

        cBox_seq_1->setItemText(0, QApplication::translate("ParaSetDlgClass", "\346\227\240", 0, QApplication::UnicodeUTF8));
        cBox_seq_1->setItemText(1, QApplication::translate("ParaSetDlgClass", "      1", 0, QApplication::UnicodeUTF8));
        cBox_seq_1->setItemText(2, QApplication::translate("ParaSetDlgClass", "      2", 0, QApplication::UnicodeUTF8));
        cBox_seq_1->setItemText(3, QApplication::translate("ParaSetDlgClass", "      3", 0, QApplication::UnicodeUTF8));
        cBox_seq_1->setItemText(4, QApplication::translate("ParaSetDlgClass", "      4", 0, QApplication::UnicodeUTF8));

        lineEdit_Valve_4->setText(QApplication::translate("ParaSetDlgClass", "\345\260\217", 0, QApplication::UnicodeUTF8));
        lineEdit_Valve_3->setText(QApplication::translate("ParaSetDlgClass", "\344\270\255\344\272\214", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("ParaSetDlgClass", "m\302\263/h", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("ParaSetDlgClass", "\346\243\200\345\256\232\351\207\217", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("ParaSetDlgClass", "L", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("ParaSetDlgClass", "\346\216\247\345\210\266\351\230\200", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("ParaSetDlgClass", "\346\243\200\345\256\232\346\254\241\345\272\217", 0, QApplication::UnicodeUTF8));
        buttonGroup_2->setTitle(QApplication::translate("ParaSetDlgClass", "\350\207\252\345\212\250\351\207\207\351\233\206", 0, QApplication::UnicodeUTF8));
        tBtn_autoPick_true->setText(QApplication::translate("ParaSetDlgClass", "\346\230\257", 0, QApplication::UnicodeUTF8));
        tBtn_autoPick_false->setText(QApplication::translate("ParaSetDlgClass", "\345\220\246", 0, QApplication::UnicodeUTF8));
        buttonGroup->setTitle(QApplication::translate("ParaSetDlgClass", "\346\200\273\351\207\217\346\243\200\345\256\232", 0, QApplication::UnicodeUTF8));
        tBtn_totalverify_true->setText(QApplication::translate("ParaSetDlgClass", "\346\230\257", 0, QApplication::UnicodeUTF8));
        tBtn_totalverify_false->setText(QApplication::translate("ParaSetDlgClass", "\345\220\246", 0, QApplication::UnicodeUTF8));
        buttonGroup_4->setTitle(QApplication::translate("ParaSetDlgClass", "\350\260\203\346\225\264\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        tBtn_adjustError_true->setText(QApplication::translate("ParaSetDlgClass", "\346\230\257", 0, QApplication::UnicodeUTF8));
        tBtn_adjustError_false->setText(QApplication::translate("ParaSetDlgClass", "\345\220\246", 0, QApplication::UnicodeUTF8));
        buttonGroup_5->setTitle(QApplication::translate("ParaSetDlgClass", "\345\206\231\350\241\250\345\217\267", 0, QApplication::UnicodeUTF8));
        tBtn_writeNum_true->setText(QApplication::translate("ParaSetDlgClass", "\346\230\257", 0, QApplication::UnicodeUTF8));
        tBtn_writeNum_false->setText(QApplication::translate("ParaSetDlgClass", "\345\220\246", 0, QApplication::UnicodeUTF8));
        buttonGroup_6->setTitle(QApplication::translate("ParaSetDlgClass", "\346\243\200\345\256\232\350\277\207\347\250\213", 0, QApplication::UnicodeUTF8));
        tBtn_continuous_true->setText(QApplication::translate("ParaSetDlgClass", "\345\244\232\347\202\271\350\277\236\347\273\255", 0, QApplication::UnicodeUTF8));
        tBtn_continuous_false->setText(QApplication::translate("ParaSetDlgClass", "\345\220\204\347\202\271\347\213\254\347\253\213", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("ParaSetDlgClass", "\345\256\211\345\205\250\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ParaSetDlgClass", "\346\265\201\351\207\217", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ParaSetDlgClass", "\346\200\273\351\207\217", 0, QApplication::UnicodeUTF8));
        buttonGroup_7->setTitle(QApplication::translate("ParaSetDlgClass", "\346\216\222\346\260\224", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("ParaSetDlgClass", "\346\216\222\346\260\224\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("ParaSetDlgClass", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("ParaSetDlgClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ParaSetDlgClass: public Ui_ParaSetDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARASETDLG_H
