#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
// Action functions for Main Window ///////////

//action for quit button press
void MainWindow::on_quitButton_clicked()
{
    QCoreApplication::quit(); //adds quit slot to quitButton widget
}

//action for Open Midi file option
void MainWindow::on_actionOpen_MIDI_triggered()
{
    //displaying modal file dialog (tr marks user visible strings)
   QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
       tr("Text Files (*.txt);;C++ Files (*.cpp *.h)")); //returns selected file path

   //set Qfile to given file name
   if(!fileName.isEmpty()) {
       QFile file(fileName);
       //if file cannot be opened throw error
       if(!file.open(QIODevice::ReadOnly)) {
           //display error message box
           QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
           return;
       }
       //read in contents of file as Qstring
       QTextStream in(&file);
       ui->textEdit->setText(in.readAll());
       file.close();
   }

}

//action for Save Midi file option
void MainWindow::on_actionSave_MIDI_triggered()
{
    //as above stringify fileName
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly)) {
            //error
            QMessageBox::critical(this, tr("Error"), tr("Could not fave file"));
            return;
        } else {
            //handles saving of text stream
            QTextStream stream(&file);
            stream << ui -> textEdit -> toPlainText();
            stream.flush();
            file.close();
        }
    }
}
