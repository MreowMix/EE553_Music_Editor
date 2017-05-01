/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_MIDI;
    QAction *actionSave_MIDI;
    QWidget *centralWidget;
    QPushButton *quitButton;
    QTextEdit *textEdit;
    QPushButton *generateButton;
    QPushButton *displayButton;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(700, 500);
        MainWindow->setStyleSheet(QStringLiteral("MainWindow{background-color: black}"));
        actionOpen_MIDI = new QAction(MainWindow);
        actionOpen_MIDI->setObjectName(QStringLiteral("actionOpen_MIDI"));
        actionSave_MIDI = new QAction(MainWindow);
        actionSave_MIDI->setObjectName(QStringLiteral("actionSave_MIDI"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        quitButton = new QPushButton(centralWidget);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(10, 190, 268, 32));
        quitButton->setStyleSheet(QStringLiteral("QPushButton#quitButton { background-color: blue; font: 87 14pt \"Arial Black\";}"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(375, 40, 171, 111));
        generateButton = new QPushButton(centralWidget);
        generateButton->setObjectName(QStringLiteral("generateButton"));
        generateButton->setGeometry(QRect(10, 150, 268, 32));
        generateButton->setStyleSheet(QLatin1String("QPushButton#generateButton { background-color: blue; font: 87 14pt \"Arial Black\"; }\n"
""));
        displayButton = new QPushButton(centralWidget);
        displayButton->setObjectName(QStringLiteral("displayButton"));
        displayButton->setGeometry(QRect(10, 110, 268, 32));
        displayButton->setStyleSheet(QStringLiteral("QPushButton#displayButton {background-color: blue; font: 87 14pt \"Arial Black\";}"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 20, 181, 41));
        label->setStyleSheet(QLatin1String("QLabel#label {color: white;font: 75 13pt \"American Typewriter\"; }\n"
""));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen_MIDI);
        menuFile->addAction(actionSave_MIDI);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen_MIDI->setText(QApplication::translate("MainWindow", "Open MIDI", 0));
        actionSave_MIDI->setText(QApplication::translate("MainWindow", "Save MIDI", 0));
        quitButton->setText(QApplication::translate("MainWindow", "Quit", 0));
        generateButton->setText(QApplication::translate("MainWindow", "Generate New Staff", 0));
        displayButton->setText(QApplication::translate("MainWindow", "Display Track List", 0));
        label->setText(QApplication::translate("MainWindow", "MUSIC EDITOR Vers. 0.2", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
