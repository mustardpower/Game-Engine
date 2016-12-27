/********************************************************************************
** Form generated from reading UI file 'QtGLWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGLWIDGET_H
#define UI_QTGLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QOpenGLWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGLWidget
{
public:

    void setupUi(QOpenGLWidget *QtGLWidget)
    {
        if (QtGLWidget->objectName().isEmpty())
            QtGLWidget->setObjectName(QStringLiteral("QtGLWidget"));
        QtGLWidget->resize(407, 304);

        retranslateUi(QtGLWidget);

        QMetaObject::connectSlotsByName(QtGLWidget);
    } // setupUi

    void retranslateUi(QOpenGLWidget *QtGLWidget)
    {
        QtGLWidget->setWindowTitle(QApplication::translate("QtGLWidget", "QtGLWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGLWidget: public Ui_QtGLWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGLWIDGET_H
