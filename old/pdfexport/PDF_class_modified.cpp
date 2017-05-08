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
  //add title to first page and other pages if necessary
  void addTitle(QString str){
      QString htmltest = "<h1>" + str + "</h1> <p> <b>bold</b> text";
      doc.setHtml(str);
      doc.setHtml(htmltest);
      //doc.setPageSize(this->printer.pageRect().size());
      //doc.print(&this->printer);
  }
  //define page size, margins, staff size
  void setLayout() {

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
   drawStaffLine(pos_x,pos_y+300);
   drawStaffLine(pos_x,pos_y+350);
   drawStaffLine(pos_x,pos_y+400);
   drawStaffLine(pos_x,pos_y+450);
   drawStaffLine(pos_x,pos_y+500);
   drawStaffLine(pos_x,pos_y+550);
   drawStaffLine(pos_x,pos_y+600);
   drawStaffLine(pos_x,pos_y+650);
   drawStaffLine(pos_x,pos_y+700);
   drawStaffLine(pos_x,pos_y+750);
   drawStaffLine(pos_x,pos_y+800);
   drawStaffLine(pos_x,pos_y+850);
   drawStaffLine(pos_x,pos_y+900);
   drawStaffLine(pos_x,pos_y+950);
   drawStaffLine(pos_x,pos_y+1000);
 }

 void addNotes(int xs, int ys, string note, int octave, QString duration, int startIndex) {
   p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
   p->setFont(QFont("Norfolk Std", 14));
   //just dealing with treble clef and notes that fall on treble clef for now
   //if index == 1 we just started a new measure so we should draw a bar line before we start
   p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
   p->drawLine(xs, ys, xs, ys+20);
   xs+=5;
   if(clef == "treble"){
       if(octave == 4){
             if(note=="d"){
                 p->drawText(xs+(startIndex*10),ys+22.5,duration);
               }
             else if(note=="e"){
                 p->drawText(xs+(startIndex*10),ys+20,duration);
             }
             else if(note=="f"){
                 p->drawText(xs+(startIndex*10),ys+17.5,duration);
               }
             else if(note=="g"){
                 p->drawText(xs+(startIndex*10),ys+15,duration);

               }
             else if(note=="a"){
                     p->drawText(xs+(startIndex*10),ys+12.5,duration);
               }
             else if(note=="b"){
                 p->drawText(xs+(startIndex*10),ys+10,duration);
               }
           }
     else if(octave == 5){
        if(note =="c"){
            p->drawText(xs+(startIndex*10),ys + 7.5,duration);
          }
        else if(note=="d"){
            p->drawText(xs+(startIndex*10),ys + 5,duration);
          }
        else if(note=="e"){
            p->drawText(xs+(startIndex*10),ys + 2.5,duration);
          }
        else if(note=="f"){
            p->drawText(xs+(startIndex*10),ys,duration);
          }
        else if(note=="g"){
            p->drawText(xs+(startIndex*10),ys-2.5,duration);
          }
     }
 }
 }

 void readVector(){
   //draw page
   //add notes
   //go to new measure
   //go to new line

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
    test->completeDrawing();

    return 0;
}
