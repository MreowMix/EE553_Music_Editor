#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT //this macro must come first in the class declaration

public:
    explicit MainWindow(QWidget *parent = 0); //value of 0 says that there is no parent widget
    ~MainWindow(); //virtual destructor

private slots: //slot is a function call triggered by an event signal on the UI

    //function to exit application upon click
    void on_quitButton_clicked();

    void on_actionOpen_MIDI_triggered();

    void on_actionSave_MIDI_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
