/********************************************************************************
** Form generated from reading UI file 'draw.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAW_H
#define UI_DRAW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_drawClass
{
public:

	void setupUi(QWidget *drawClass)
	{
		if (drawClass->objectName().isEmpty())
			drawClass->setObjectName(QStringLiteral("drawClass"));
		drawClass->resize(500, 500);

		retranslateUi(drawClass);

		QMetaObject::connectSlotsByName(drawClass);
	} // setupUi

	void retranslateUi(QWidget *drawClass)
	{
		drawClass->setWindowTitle(QApplication::translate("drawClass", "draw", 0));
	} // retranslateUi

};

namespace Ui {
	class draw : public Ui_drawClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAW_H
