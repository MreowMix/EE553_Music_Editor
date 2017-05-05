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
  QPainter * p;
  QPrinter * printer;
  QTextDocument doc;

public:
  //ideally, we will be passing in a file created by notation class
  PDFexport(string clef = "treble", string timesig = "4/4", string keysig = "C", string title = "title") {
      //this just assigns a name to the file
      this->clef = clef;
      this->timesig = timesig;
      this->keysig = keysig;
      this->title = title;
      filename = QFileDialog::getSaveFileName((QWidget* )0, "DefaultPDF", QString(), "*pdf");
      if (QFileInfo(filename).suffix().isEmpty()) { filename.append(".pdf");}
      printer = new QPrinter();
      printer->setOutputFormat(QPrinter::PdfFormat);
      printer->setPaperSize(QPrinter::Letter);
      printer->setOutputFileName(filename);
      p = new QPainter();
      p->begin(printer);
     }
 ~PDFexport(){
    delete p;
    delete printer;
 }

  void setPenFormat(QPen pen){
      p->setPen(pen);
  }

  void drawStaffLine(int xs, int ys) {
      p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
      p->drawLine(xs, ys, xs, ys+20);
      p->setFont(QFont("Norfolk Std", 12));
      p->drawText(xs+2, ys+14, "&");
      p->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
      p->drawLine(xs,ys,xs+750,ys);
      p->drawLine(xs,ys+5,xs+750,ys+5);
      p->drawLine(xs,ys+10,xs+750,ys+10);
      p->drawLine(xs,ys+15,xs+750,ys+15);
      p->drawLine(xs,ys+20,xs+750,ys+20);
      p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
      p->drawLine(xs+750, ys, xs+750, ys+20);
  }

  void addTimeSig(int xs, int ys){
      p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
      p->setFont(QFont("Norfolk Std", 15));
      if(this->timesig=="4/4"){
          p->drawText(xs+14,ys+4,"4");
          p->drawText(xs+14,ys+15,"4");
      }
      else if(this->timesig=="3/4"){
          p->drawText(xs+14,ys+4,"3");
          p->drawText(xs+14,ys+15,"4");
        }
      else if(this->timesig == "2/4"){
          p->drawText(xs+14,ys+4,"2");
          p->drawText(xs+14,ys+15,"4");
        }
      else if(this->timesig=="6/8"){
          p->drawText(xs+14,ys+4,"6");
          p->drawText(xs+14,ys+15,"4");
        }
      else {
          p->drawText(xs+14,ys+4,"4");
          p->drawText(xs+14,ys+15,"4");
        }
  }

 void addKeySig(int xs, int ys){

 }

 void drawPage(int pos_x, int pos_y){
   drawStaffLine(pos_x, pos_y);
   addTimeSig(pos_x,pos_y);
   drawStaffLine(pos_x,pos_y+50);
   addTimeSig(pos_x,pos_y+50);
   drawStaffLine(pos_x,pos_y+100);
   addTimeSig(pos_x,pos_y+100);
   drawStaffLine(pos_x,pos_y+150);
   addTimeSig(pos_x,pos_y+150);
   drawStaffLine(pos_x,pos_y+200);
   addTimeSig(pos_x,pos_y+200);
   drawStaffLine(pos_x,pos_y+250);
   addTimeSig(pos_x,pos_y+250);
   drawStaffLine(pos_x,pos_y+300);
   addTimeSig(pos_x,pos_y+300);
   drawStaffLine(pos_x,pos_y+350);
   addTimeSig(pos_x,pos_y+350);
   drawStaffLine(pos_x,pos_y+400);
   addTimeSig(pos_x,pos_y+400);
   drawStaffLine(pos_x,pos_y+450);
   addTimeSig(pos_x,pos_y+450);
   drawStaffLine(pos_x,pos_y+500);
   addTimeSig(pos_x,pos_y+500);
   drawStaffLine(pos_x,pos_y+550);
   addTimeSig(pos_x,pos_y+550);
   drawStaffLine(pos_x,pos_y+600);
   addTimeSig(pos_x,pos_y+600);
   drawStaffLine(pos_x,pos_y+650);
   addTimeSig(pos_x,pos_y+650);
   drawStaffLine(pos_x,pos_y+700);
   addTimeSig(pos_x,pos_y+700);
   drawStaffLine(pos_x,pos_y+750);
   addTimeSig(pos_x,pos_y+750);
   drawStaffLine(pos_x,pos_y+800);
   addTimeSig(pos_x,pos_y+800);
   drawStaffLine(pos_x,pos_y+850);
   addTimeSig(pos_x,pos_y+850);
   drawStaffLine(pos_x,pos_y+900);
   addTimeSig(pos_x,pos_y+900);
   drawStaffLine(pos_x,pos_y+950);
   addTimeSig(pos_x,pos_y+950);
   drawStaffLine(pos_x,pos_y+1000);
   addTimeSig(pos_x,pos_y+1000);
 }

 void addNotes(int xs, int ys, char note, int octave, char duration, int startIndex) {
   p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
   p->setFont(QFont("Norfolk Std", 12));
   int index = 50 + startIndex*40;
   if(clef == "treble"){
       if(note=='a'){
           if(octave == 4){
               //a that falls on staff
               p->drawText(xs+index,ys+15,"q");
             }
         }
     }

 }
 void addPage() {
     printer->newPage();
     drawPage(10,10);
 }

  void completeDrawing() {
      p->end();
  }
};


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PDFexport * test = new PDFexport;
    int pos_x = 10, pos_y = 10;
    test->setPenFormat(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
    test->drawPage(pos_x,pos_y);
    test->addNotes(pos_x, pos_y, 'a', 4, 'q', 1);
    test->addPage();
    test->addNotes(pos_x, pos_y, 'a', 4, 'q', 1);
    test->completeDrawing();

    return 0;
}
