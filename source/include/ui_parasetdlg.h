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
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParaSetDlgClass
{
public:
    QGridLayout *gridLayout_8;
    QGroupBox *groupBox;
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
    QComboBox *cmbManuCompany;
    QLabel *label_10;
    QComboBox *cmbVerifyCompany;
    QGridLayout *gridLayout_5;
    QComboBox *cmbVerifyPerson;
    QLabel *label_7;
    QLabel *label_8;
    QComboBox *cmbGrade;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    Q3ButtonGroup *buttonGroup_2;
    Q3ButtonGroup *buttonGroup;
    Q3ButtonGroup *buttonGroup_3;
    Q3ButtonGroup *buttonGroup_4;
    Q3ButtonGroup *buttonGroup_5;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QPushButton *btnSave;
    QPushButton *btnExit;

    void setupUi(QWidget *ParaSetDlgClass)
    {
        if (ParaSetDlgClass->objectName().isEmpty())
            ParaSetDlgClass->setObjectName(QString::fromUtf8("ParaSetDlgClass"));
        ParaSetDlgClass->resize(672, 537);
        gridLayout_8 = new QGridLayout(ParaSetDlgClass);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        groupBox = new QGroupBox(ParaSetDlgClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_7 = new QGridLayout(groupBox);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        cmbStandard = new QComboBox(groupBox);
        cmbStandard->setObjectName(QString::fromUtf8("cmbStandard"));

        gridLayout_3->addWidget(cmbStandard, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        cmbModel = new QComboBox(groupBox);
        cmbModel->setObjectName(QString::fromUtf8("cmbModel"));

        gridLayout_3->addWidget(cmbModel, 1, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_3, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(label_5, 0, 0, 1, 1);

        cmbFlow = new QComboBox(groupBox);
        cmbFlow->setObjectName(QString::fromUtf8("cmbFlow"));

        gridLayout_4->addWidget(cmbFlow, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(label_6, 1, 0, 1, 1);

        cmbCollectCode = new QComboBox(groupBox);
        cmbCollectCode->setObjectName(QString::fromUtf8("cmbCollectCode"));

        gridLayout_4->addWidget(cmbCollectCode, 1, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_4, 0, 1, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(label_9, 0, 0, 1, 1);

        cmbManuCompany = new QComboBox(groupBox);
        cmbManuCompany->setObjectName(QString::fromUtf8("cmbManuCompany"));

        gridLayout_6->addWidget(cmbManuCompany, 0, 1, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(label_10, 1, 0, 1, 1);

        cmbVerifyCompany = new QComboBox(groupBox);
        cmbVerifyCompany->setObjectName(QString::fromUtf8("cmbVerifyCompany"));

        gridLayout_6->addWidget(cmbVerifyCompany, 1, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_6, 0, 2, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        cmbVerifyPerson = new QComboBox(groupBox);
        cmbVerifyPerson->setObjectName(QString::fromUtf8("cmbVerifyPerson"));

        gridLayout_5->addWidget(cmbVerifyPerson, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_7, 0, 0, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_8, 1, 0, 1, 1);

        cmbGrade = new QComboBox(groupBox);
        cmbGrade->setObjectName(QString::fromUtf8("cmbGrade"));

        gridLayout_5->addWidget(cmbGrade, 0, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_5, 0, 3, 1, 1);


        gridLayout_8->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(ParaSetDlgClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));

        gridLayout_8->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(ParaSetDlgClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));

        gridLayout_8->addWidget(groupBox_3, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        buttonGroup_2 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));

        horizontalLayout->addWidget(buttonGroup_2);

        buttonGroup = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));

        horizontalLayout->addWidget(buttonGroup);

        buttonGroup_3 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_3->setObjectName(QString::fromUtf8("buttonGroup_3"));

        horizontalLayout->addWidget(buttonGroup_3);

        buttonGroup_4 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_4->setObjectName(QString::fromUtf8("buttonGroup_4"));

        horizontalLayout->addWidget(buttonGroup_4);

        buttonGroup_5 = new Q3ButtonGroup(ParaSetDlgClass);
        buttonGroup_5->setObjectName(QString::fromUtf8("buttonGroup_5"));

        horizontalLayout->addWidget(buttonGroup_5);


        gridLayout_8->addLayout(horizontalLayout, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox_4 = new QGroupBox(ParaSetDlgClass);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox_4);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 3, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox_4);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout_2->addWidget(lineEdit_2, 0, 4, 1, 1);


        horizontalLayout_2->addWidget(groupBox_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnSave = new QPushButton(ParaSetDlgClass);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        gridLayout->addWidget(btnSave, 0, 0, 1, 1);

        btnExit = new QPushButton(ParaSetDlgClass);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));

        gridLayout->addWidget(btnExit, 0, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);


        gridLayout_8->addLayout(horizontalLayout_2, 4, 0, 1, 1);


        retranslateUi(ParaSetDlgClass);

        QMetaObject::connectSlotsByName(ParaSetDlgClass);
    } // setupUi

    void retranslateUi(QWidget *ParaSetDlgClass)
    {
        ParaSetDlgClass->setWindowTitle(QApplication::translate("ParaSetDlgClass", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ParaSetDlgClass", "\346\243\200\345\256\232\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ParaSetDlgClass", "\350\247\204\346\240\274", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ParaSetDlgClass", "\345\236\213\345\217\267", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ParaSetDlgClass", "\345\270\270\347\224\250\346\265\201\351\207\217", 0, QApplication::UnicodeUTF8));
        cmbFlow->clear();
        cmbFlow->insertItems(0, QStringList()
         << QApplication::translate("ParaSetDlgClass", "2.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "0.25", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("ParaSetDlgClass", "\351\207\207\351\233\206\344\273\243\347\240\201", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ParaSetDlgClass", "\345\210\266\351\200\240\345\215\225\344\275\215", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ParaSetDlgClass", "\351\200\201\346\243\200\345\215\225\344\275\215", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ParaSetDlgClass", "\350\256\241\351\207\217\347\255\211\347\272\247", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ParaSetDlgClass", "\346\243\200\346\265\213\345\221\230", 0, QApplication::UnicodeUTF8));
        cmbGrade->clear();
        cmbGrade->insertItems(0, QStringList()
         << QApplication::translate("ParaSetDlgClass", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParaSetDlgClass", "3", 0, QApplication::UnicodeUTF8)
        );
        groupBox_2->setTitle(QApplication::translate("ParaSetDlgClass", "\346\216\247\345\210\266\351\230\200\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("ParaSetDlgClass", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        buttonGroup_2->setTitle(QApplication::translate("ParaSetDlgClass", "\350\207\252\345\212\250\351\207\207\351\233\206", 0, QApplication::UnicodeUTF8));
        buttonGroup->setTitle(QApplication::translate("ParaSetDlgClass", "\346\200\273\351\207\217\346\243\200\345\256\232", 0, QApplication::UnicodeUTF8));
        buttonGroup_3->setTitle(QApplication::translate("ParaSetDlgClass", "\350\241\250\346\263\242\347\211\271\347\216\207", 0, QApplication::UnicodeUTF8));
        buttonGroup_4->setTitle(QApplication::translate("ParaSetDlgClass", "\350\257\273\350\204\211\345\206\262\346\225\260", 0, QApplication::UnicodeUTF8));
        buttonGroup_5->setTitle(QApplication::translate("ParaSetDlgClass", "\350\260\203\346\225\264\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("ParaSetDlgClass", "\345\256\211\345\205\250\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ParaSetDlgClass", "\346\265\201\351\207\217", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ParaSetDlgClass", "\346\200\273\351\207\217", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("ParaSetDlgClass", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("ParaSetDlgClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ParaSetDlgClass: public Ui_ParaSetDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARASETDLG_H
