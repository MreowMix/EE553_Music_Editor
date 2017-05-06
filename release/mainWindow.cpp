#include <QtWidgets>
#include <string>

#include "include/drawStaff.h"
#include "mainWindow.h"
MainWindow::MainWindow()
{
    createActions();
    createMenus();

    statusBar()->showMessage("No file currently open");

    setWindowTitle(tr("EE553 Midi Display"));
    setMinimumSize(160, 160);
    resize(1280, 720);
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Midi File"), QDir::currentPath(), tr("Midi files (*.mid)"));
    std::string fileNameStr = fileName.toStdString().c_str();

    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    drawStaff staff(fileNameStr, "treble");
    vector<note> noteArray = staff.buildNoteArray();

    for (int i = 0; i < noteArray.size(); i++) {
        if (noteArray[i].index == 1) {
            if (i == 0) {staff.newMeasure(true, false);}
            else {staff.newMeasure(false, false);}    
        }
        staff.drawNotes(noteArray[i].noteName, noteArray[i].octave, noteArray[i].duration, noteArray[i].index);
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

void MainWindow::save()
{
}


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

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(exitAct);

}