#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//declaration of classes and functions used in our instance of Main Window

class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void open();
    void save();

private:
    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QLabel *notationLabel;
};

#endif
