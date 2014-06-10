/********************************************************************************
** Form generated from reading UI file 'qualitydlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUALITYDLG_H
#define UI_QUALITYDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QualityDlgClass
{
public:

    void setupUi(QWidget *QualityDlgClass)
    {
        if (QualityDlgClass->objectName().isEmpty())
            QualityDlgClass->setObjectName(QString::fromUtf8("QualityDlgClass"));
        QualityDlgClass->resize(400, 300);

        retranslateUi(QualityDlgClass);

        QMetaObject::connectSlotsByName(QualityDlgClass);
    } // setupUi

    void retranslateUi(QWidget *QualityDlgClass)
    {
        QualityDlgClass->setWindowTitle(QApplication::translate("QualityDlgClass", "QulityMethod", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QualityDlgClass: public Ui_QualityDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUALITYDLG_H
