QT += widgets
QT += printsupport
HEADERS       = mainWindow.h \
				include/drawStaff.h \
				include/readMidi.h \
    include/pdfexport.h
INCLUDEPATH += include
SOURCES       = mainwindow.cpp \
                main.cpp
