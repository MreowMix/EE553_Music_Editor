QT += widgets
QT += printsupport
HEADERS       = mainWindow.h \
				include/drawStaff.h \
    include/pdfexport.h \
    include/notationeditor.h \
    include/read.h
INCLUDEPATH += include
SOURCES       = mainwindow.cpp \
                main.cpp

CONFIG +=C++11
