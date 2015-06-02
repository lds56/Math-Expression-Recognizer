/********************************************************************************
** Form generated from reading UI file 'mathmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATHMAINWINDOW_H
#define UI_MATHMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MathMainWindowClass
{
public:

    void setupUi(QWidget *MathMainWindowClass)
    {
        if (MathMainWindowClass->objectName().isEmpty())
            MathMainWindowClass->setObjectName(QStringLiteral("MathMainWindowClass"));
        MathMainWindowClass->resize(600, 400);

        retranslateUi(MathMainWindowClass);

        QMetaObject::connectSlotsByName(MathMainWindowClass);
    } // setupUi

    void retranslateUi(QWidget *MathMainWindowClass)
    {
        MathMainWindowClass->setWindowTitle(QApplication::translate("MathMainWindowClass", "MathMainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class MathMainWindowClass: public Ui_MathMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATHMAINWINDOW_H
