#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //creates Qt application object
    MainWindow w;
    w.show(); //note: widgets are not visible by default

    return a.exec(); //enters QtApplication event loop
}
