#include <QApplication>

#include "mainwindow.h"

// very basic & standard main function that runs the application
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}