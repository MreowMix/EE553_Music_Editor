/*#include <QApplication>
#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <QFont>
#include <string>
#include <QPrinter>
using namespace std;

#define MEASURE_LEN 240

class drawStaff{
private:
    string clef, timesig, keysig;
    int pos_x, pos_y;
    QLabel l;
    QPrinter printer;
    QPicture pi;
    QPainter p;
public:

    drawStaff(string c = "treble", string t = "4/4",
              string k = "C", int x = 0, int y = 0) :
              clef(c), timesig(t), keysig(k), pos_x(x), pos_y(y), p(&pi){}
    // Create a new blank measure, with flags for begin/end
    void newMeasure(bool isBegin = false, bool isEnd = false) {
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));

        if (isBegin || pos_x == 0) {
            p.drawLine(pos_x, pos_y, pos_x+100, pos_y);
            p.drawLine(pos_x, pos_y+10, pos_x+100, pos_y+10);
            p.drawLine(pos_x, pos_y+20, pos_x+100, pos_y+20);
            p.drawLine(pos_x, pos_y+30, pos_x+100, pos_y+30);
            p.drawLine(pos_x, pos_y+40, pos_x+100, pos_y+40);
            p.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
            p.drawLine(pos_x, pos_y, pos_x, pos_y+40);
            p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
            if (clef == "treble"){
                // Draw a treble clef a the beginning of the staff
                p.setFont(QFont("Norfolk Std", 30));
                // Positioning depends on what is being drawn
                p.drawText(pos_x+2, pos_y+28 , "&");
            }
            else if (clef == "bass") {

            }
            // will add keysignatures later
            //if keysig

            if (timesig == "4/4") {
                p.setFont(QFont("Norfolk Std", 30));
                p.drawText(pos_x+80, pos_y+10 , "4");
                p.drawText(pos_x+80, pos_y+30 , "4");
            }
            else if (timesig == "3/4") {
                p.setFont(QFont("Norfolk Std", 30));
                p.drawText(pos_x+82, pos_y+9 , "3");
                p.drawText(pos_x+80, pos_y+30 , "4");
            }
        pos_x = pos_x + 100;
        }

        //expand for note grids
        p.drawLine(pos_x, pos_y, pos_x+MEASURE_LEN, pos_y);
        p.drawLine(pos_x, pos_y+10, pos_x+MEASURE_LEN, pos_y+10);
        p.drawLine(pos_x, pos_y+20, pos_x+MEASURE_LEN, pos_y+20);
        p.drawLine(pos_x, pos_y+30, pos_x+MEASURE_LEN, pos_y+30);
        p.drawLine(pos_x, pos_y+40, pos_x+MEASURE_LEN, pos_y+40);


        pos_x = pos_x + MEASURE_LEN;
        if (isEnd) {
            p.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::SquareCap));
            p.drawLine(pos_x, pos_y+1, pos_x, pos_y+39);
            p.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
            p.drawLine(pos_x-4, pos_y, pos_x-4, pos_y+40);
        }
        else {
            p.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
            p.drawLine(pos_x, pos_y, pos_x, pos_y+40);
            p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
        }

        if (pos_x >= MEASURE_LEN*5+100) {
            pos_x = 0;
            pos_y = pos_y + 80;
        }
    }

    // Add notes to blank measure created by newMeasure method
    void drawNotes(char note, int octave, char duration, int startIndex) {
        bool temp_pos = false;
        if (pos_y > 0 && pos_x == 0) {
            pos_y = pos_y - 80;
            pos_x = MEASURE_LEN*5+100;
            temp_pos = true;
        }

        double ind_mod = 0.0;
        int index = 0;
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));

        if (timesig == "4/4") {
            ind_mod = (double)MEASURE_LEN / (double)(16 + 2);
        }

        else if (timesig == "3/4") {
            ind_mod = (double)MEASURE_LEN / (double)(12 + 2);
        }

        index = (startIndex * ind_mod) - MEASURE_LEN;
        if (clef == "treble") {
            if (note == 'a') {
                if (octave == 4) {
                    if (duration == 'q') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+25 , "q");
                    }
                    else if (duration == 'e') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+25 , "e");
                    }
                }
            }
            else if (note == 'b') {
                if (octave == 4) {
                    if (duration == 'q') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+20 , "Q");
                    }
                    else if (duration == 'e') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+20 , "E");
                    }
                }
            }
            else if (note == 'c') {
                if (octave == 4) {
                    if (duration == 'q') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+50 , "q");
                        // draw ledger line
                        p.drawLine(pos_x + index - 2, pos_y+50,
                                   pos_x + index + 16, pos_y+50);
                    }
                    else if (duration == 'e') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+50 , "e");
                        // draw ledger line
                        p.drawLine(pos_x + index - 2, pos_y+50,
                                   pos_x + index + 16, pos_y+50);
                    }
                }
                else if (octave == 5) {
                    if (duration == 'q') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+15 , "Q");
                    }
                    else if (duration == 'e') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+15 , "E");
                    }
                }
            }
            else if (note == 'd') {
                if (octave == 4) {
                    if (duration == 'q') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+45 , "q");
                    }
                    else if (duration == 'e') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+45 , "e");
                    }
                }
                else if (octave == 5) {
                    if (duration == 'q') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+10 , "Q");
                    }
                    else if (duration == 'e') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+10 , "E");
                    }
                }
            }
            else if (note == 'e') {
                if (octave == 4) {
                    if (duration == 'q') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+40 , "q");
                    }
                    else if (duration == 'e') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+40 , "e");
                    }
                }
                else if (octave == 5) {
                    if (duration == 'q') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+5 , "Q");
                    }
                    else if (duration == 'e') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+5 , "E");
                    }
                }
            }
            else if (note == 'f') {
                if (octave == 4) {
                    if (duration == 'q') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+35 , "q");
                    }
                    else if (duration == 'e') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+35 , "e");
                    }
                }
                else if (octave == 5) {
                    if (duration == 'q') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+0 , "Q");
                    }
                    else if (duration == 'e') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+0 , "E");
                    }
                }
            }
            else if (note == 'g') {
                if (octave == 4) {
                    if (duration == 'q') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+30 , "q");
                    }
                    else if (duration == 'e') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y+30 , "e");
                    }
                }
                else if (octave == 5) {
                    if (duration == 'q') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y-5 , "Q");
                    }
                    if (duration == 'e') {
                        p.setFont(QFont("Norfolk Std", 26));
                        p.drawText(pos_x + index, pos_y-5 , "E");
                    }
                }
            }
        }
        if (temp_pos) {
            pos_y = pos_y + 80;
            pos_x = 0;
        }
    }

    // Add additional markings - to be added last
    // void addOrnamentation() {}
    void display() {
        p.end();
        l.setAlignment(Qt::AlignCenter);
        l.setPicture(pi);
        l.show();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    drawStaff staff;
    // create first measure , isBegin = true isEnd = false
    staff.newMeasure(true, false);
    // Draws notes on the previously created staff
    // displays an a3 quarter note on the treble clef
    // the index values correspond to the position left-right on the measure
    staff.drawNotes('c', 4, 'q', 1);
    staff.drawNotes('d', 4, 'q', 5);
    staff.drawNotes('e', 4, 'q', 9);
    staff.drawNotes('f', 4, 'q', 13);
    staff.newMeasure(false, false);
    staff.drawNotes('g', 4, 'q', 1);
    staff.drawNotes('a', 4, 'q', 5);
    staff.drawNotes('b', 4, 'q', 9);
    staff.drawNotes('c', 5, 'q', 13);
    staff.newMeasure(false, false);
    staff.drawNotes('c', 5, 'q', 1);
    staff.drawNotes('b', 4, 'q', 5);
    staff.drawNotes('a', 4, 'q', 9);
    staff.drawNotes('g', 4, 'q', 13);
    staff.newMeasure(false, false);
    staff.drawNotes('f', 4, 'q', 1);
    staff.drawNotes('e', 4, 'q', 5);
    staff.drawNotes('d', 4, 'q', 9);
    staff.drawNotes('c', 4, 'q', 13);


    staff.newMeasure(false, false);
    staff.drawNotes('c', 4, 'e', 1);
    staff.drawNotes('d', 4, 'e', 3);
    staff.drawNotes('e', 4, 'e', 5);
    staff.drawNotes('f', 4, 'e', 7);
    staff.drawNotes('g', 4, 'e', 9);
    staff.drawNotes('a', 4, 'e', 11);
    staff.drawNotes('b', 4, 'e', 13);
    staff.drawNotes('c', 5, 'e', 15);

    staff.newMeasure(false, true);
    staff.drawNotes('c', 5, 'e', 1);
    staff.drawNotes('b', 4, 'e', 3);
    staff.drawNotes('a', 4, 'e', 5);
    staff.drawNotes('g', 4, 'e', 7);
    staff.drawNotes('f', 4, 'e', 9);
    staff.drawNotes('e', 4, 'e', 11);
    staff.drawNotes('d', 4, 'e', 13);
    staff.drawNotes('c', 4, 'e', 15);
    //staff.newMeasure(false, true);
    staff.display();
    return a.exec();
}*/
#include <QApplication>
#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <QFont>
#include <string>
#include <QtWidgets>
#include <QPrinter>
#include <QPrinterInfo>
#include <iostream>

#define MEASURE_LEN 240
using namespace std;

class PDFexport {
private:
  string clef, timesig, keysig, title;
  int numPages;
  QLabel l;
  QString filename;
  QPicture pi;
  QPainter p;
  QPrinter printer;
  QTextDocument doc;

public:
  //ideally, we will be passing in a file created by notation class
  //reading to it, creating staff, then printing notes to staff
  //start off by asking user for filename, then do the rest of the creation
  PDFexport(string clef = "treble", string timesig = "4/4", string keysig = "", string title = "title") {
      //this just assigns a name to the file
      filename = QFileDialog::getSaveFileName((QWidget* )0, "DefaultPDF", QString(), "*pdf");
      if (QFileInfo(filename).suffix().isEmpty()) { filename.append(".pdf");}
      //QPrinter(QPrinter::PrinterResolution);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setPaperSize(QPrinter::A4);
      printer.setOutputFileName(filename);
     }
 ~PDFexport(){
 }
  //add title to first page and other pages if necessary
  void addTitle(QString str){
      QString htmltest = "<h1>" + str + "</h1> <p> <b>bold</b> text";
      doc.setHtml(str);
      doc.setHtml(htmltest);
      //doc.setPageSize(this->printer.pageRect().size());
      doc.print(&this->printer);
  }
  //define page size, margins, staff size
  void setLayout() {

  }
};
int main(int argc, char *argv[]) {
   /*QApplication app(argc, argv);

   PDFexport a;
   a.addTitle("This is tester code. In the actual project, we will only be writing a title as text");
*/
    QApplication app(argc, argv);
    foreach(QPrinterInfo printerInfo, QPrinterInfo::availablePrinters()) {
        if (printerInfo.state() == QPrinter::PrinterState::Error)
            continue;

        // Look for the virtual printer device that generates a pdf.
        if (printerInfo.printerName() == "Microsoft Print to PDF")
        {

            int pos_x = 100, pos_y = 100;
            QPrinter * qPrinter = new QPrinter(printerInfo, QPrinter::HighResolution);
            QPainter * qPainter = new QPainter();
            qPrinter->setPaperSize(QPrinter::Letter);
            qPrinter->pageRect(QPrinter::Inch);
            // This statement pops up a file selection dialog.
            // When it is cancelled, the application crashes ...
            qPainter->begin(qPrinter);

            // ... and this statement is never reached.
            cout << "Starting printing on the pdf file." << endl;
            qPainter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
            qPainter->drawLine(pos_x, pos_y, pos_x+1000, pos_y);
            qPainter->drawLine(pos_x, pos_y+100, pos_x+1000, pos_y+100);
            qPainter->drawLine(pos_x, pos_y+200, pos_x+1000, pos_y+200);
            qPainter->drawLine(pos_x, pos_y+300, pos_x+1000, pos_y+300);
            qPainter->drawLine(pos_x, pos_y+400, pos_x+1000, pos_y+400);
            qPainter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
            qPainter->drawLine(pos_x, pos_y, pos_x, pos_y+400);
            // Draw a treble clef a the beginning of the staff
            qPainter->setFont(QFont("Norfolk Std", 30));
            // Positioning depends on what is being drawn
            qPainter->drawText(pos_x+20, pos_y+280 , "&");
            qPainter->setFont(QFont("Norfolk Std", 30));
            qPainter->drawText(pos_x+180, pos_y+100 , "4");
            qPainter->drawText(pos_x+180, pos_y+300 , "4");
            pos_x = pos_x + 100;

            //expand for note grids
            qPainter->drawLine(pos_x, pos_y, pos_x+MEASURE_LEN, pos_y);
            qPainter->drawLine(pos_x, pos_y+100, pos_x+MEASURE_LEN, pos_y+100);
            qPainter->drawLine(pos_x, pos_y+200, pos_x+MEASURE_LEN, pos_y+200);
            qPainter->drawLine(pos_x, pos_y+300, pos_x+MEASURE_LEN, pos_y+300);
            qPainter->drawLine(pos_x, pos_y+400, pos_x+MEASURE_LEN, pos_y+400);
            // We print some text in the PDF file.
            /*qPainter->drawText(100, 100, "Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
            qPrinter->newPage();
            qPainter->drawText(100, 100, "Mauris ut urna eget dui eleifend placerat.");
            qPrinter->newPage();*/

            // Close the printer and clean-up.
            qPainter->end();
            delete qPrinter;
            delete qPainter;
        }
    }

    return 0;
}
