#include <QtWidgets>
#include <string>
#include <QFileDialog>
#include <QFile>
#include "include/readHex.h"
#include "include/drawStaff.h"
#include "include/pdfexport.h"
#include "mainWindow.h"
#include <QMessageBox>

std::string globalFile;

// Sets up the main qt window
MainWindow::MainWindow()
{
    createActions();
    createMenus();

    statusBar()->showMessage("No file currently open");

    setWindowTitle(tr("EE553 Midi Display"));
    setMinimumSize(400, 160);
    resize(1280, 720);
}

// Function executed after opening a file from the menu
// uses the drawStaff and readMidi classes to render notation
void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, 
    tr("Open Midi File"), QDir::currentPath(), tr("Midi files (*.mid)"));


    if(!fileName.isEmpty()&& !fileName.isNull()){

        // Block to read midi to hex data (Peter)
        QFile file(fileName);

        if(!file.open(QIODevice::ReadOnly)) {
            //display error message box
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);

        char* temp =new char[file.size()];
        file.read(temp,file.size());
        midiToHex(temp,file.size());
        file.close();
        // End block to read midi to hex data
        

        std::string fileNameStr = fileName.toStdString().c_str();
        globalFile = fileNameStr;
        QWidget *widget = new QWidget;
        setCentralWidget(widget);

        drawStaff staff(fileNameStr, "treble");
        vector<note> noteArray = staff.buildNoteArray();

        for (int i = 0; i < noteArray.size(); i++) {
            if (noteArray[i].index == 1) {
                if (i == 0) {staff.newMeasure(true, false);}
                else {staff.newMeasure(false, false);}
            }
            staff.drawNotes(noteArray[i].noteName, noteArray[i].octave, 
                            noteArray[i].duration, noteArray[i].index);
        }

        QPicture pi;
        pi = staff.display();
        notationLabel = new QLabel(this);
        notationLabel->setPicture(pi);
        notationLabel->setAlignment(Qt::AlignCenter);
        statusBar()->showMessage(fileName);

        QVBoxLayout *layout = new QVBoxLayout;
        layout->setMargin(5);
        layout->addWidget(notationLabel);
        widget->setLayout(layout);
    }
}

// Saves the rendered notation to a PDF using the pdf export class
void MainWindow::save()
{

    //avoiding crash if user clicks save before MIDI file is opened
    if(globalFile == ""){
     QMessageBox msgBox;
     msgBox.setText("No MIDI file has been opened yet.");
     msgBox.setInformativeText("Do you want to choose a file to convert to PDF?");
     msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
     int ret = msgBox.exec();
     if(ret==QMessageBox::Yes){
         QString fileName = QFileDialog::getOpenFileName(this, tr("Open Midi File"), QDir::currentPath(), tr("Midi files (*.mid)"));
         std::string fileNameStr = fileName.toStdString().c_str();
         globalFile = fileNameStr;
      }
    }
    if(! (globalFile=="")){
        drawStaff staff(globalFile, "treble");
        vector<note> noteArray = staff.buildNoteArray();
        PDFexport * saveFile = new PDFexport;
        saveFile->readVector(noteArray);
        QString mes = QString::fromStdString(globalFile + " saved.");
        statusBar()->showMessage(mes);
    }
}

// creates QActions for open, save, and exit
void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);


    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
}

// creates the menus with behaviors defined above
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);

}
