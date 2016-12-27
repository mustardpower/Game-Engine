/********************************************************************************
** Form generated from reading UI file 'QtPhysicsEngine.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTPHYSICSENGINE_H
#define UI_QTPHYSICSENGINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qtglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_QtPhysicsEngineClass
{
public:
    QAction *actionNew;
    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QtGLWidget *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtPhysicsEngineClass)
    {
        if (QtPhysicsEngineClass->objectName().isEmpty())
            QtPhysicsEngineClass->setObjectName(QStringLiteral("QtPhysicsEngineClass"));
        QtPhysicsEngineClass->resize(882, 593);
        actionNew = new QAction(QtPhysicsEngineClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionLoad = new QAction(QtPhysicsEngineClass);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionSave = new QAction(QtPhysicsEngineClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionExit = new QAction(QtPhysicsEngineClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(QtPhysicsEngineClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        openGLWidget = new QtGLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        gridLayout->addWidget(openGLWidget, 0, 0, 1, 1);

        QtPhysicsEngineClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtPhysicsEngineClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 882, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        QtPhysicsEngineClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtPhysicsEngineClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtPhysicsEngineClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtPhysicsEngineClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtPhysicsEngineClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);

        retranslateUi(QtPhysicsEngineClass);

        QMetaObject::connectSlotsByName(QtPhysicsEngineClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtPhysicsEngineClass)
    {
        QtPhysicsEngineClass->setWindowTitle(QApplication::translate("QtPhysicsEngineClass", "QtPhysicsEngine", Q_NULLPTR));
        actionNew->setText(QApplication::translate("QtPhysicsEngineClass", "New...", Q_NULLPTR));
        actionLoad->setText(QApplication::translate("QtPhysicsEngineClass", "Load...", Q_NULLPTR));
        actionSave->setText(QApplication::translate("QtPhysicsEngineClass", "Save...", Q_NULLPTR));
        actionExit->setText(QApplication::translate("QtPhysicsEngineClass", "Quit", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("QtPhysicsEngineClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtPhysicsEngineClass: public Ui_QtPhysicsEngineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPHYSICSENGINE_H
