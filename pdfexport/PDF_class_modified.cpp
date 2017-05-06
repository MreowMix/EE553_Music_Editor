#include <QApplication>
#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <QFont>
#include <string>
#include <QtWidgets>
#include <QPrinter>
#include <QPrinterInfo>
#include <vector>
#include <iostream>

#define MEASURE_LEN 240
using namespace std;

struct note {
    string noteName, duration;
    int octave, index;
};

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

 void addPage() {
     printer->newPage();
     drawPage(10,10);
 }

 void addNotes(int xs, int ys, string note, int octave, QString duration, int startIndex) {
   p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
   p->setFont(QFont("Norfolk Std", 14));
   //just dealing with treble clef and notes that fall on treble clef for now
   //if index == 1 we just started a new measure so we should draw a bar line before we start
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

 void completeDrawing() {
     p->end();
 }

 void readVector(vector<note*> notes) {
     int xstart = 10, ystart = 10;
     int maxIndex;
     if(this->timesig=="4/4")
         maxIndex = 16;
     else if(this->timesig=="3/4")
         maxIndex = 12;
     else if(this->timesig == "2/4")
         maxIndex = 8;
     else if(this->timesig=="6/8")
         maxIndex = 12;
     else
         maxIndex = 16;
     drawPage(xstart, ystart);
     bool measure = false;
     for(int i = 0; i < notes.size(); i++) {
         QString duration = QString::fromStdString(notes[i]->duration);
         //don't need to go to new line or new page
         if (((xstart <= 500 && notes[i]->index==1)||(xstart <= 730 && notes[i]->index!=1))&& ystart <= 950) {
             if(notes[i]->index > 1 && !measure){
                 measure = true;
              }
                 //we are now starting a new measure
             else if(notes[i]->index == 1 && measure){
                 xstart = xstart + 180;
                 p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
                 p->drawLine(xstart, ystart, xstart, ystart+20);
             }

             addNotes(xstart+15, ystart, notes[i]->noteName, notes[i]->octave, duration, notes[i]->index);
         }
         else if(ystart > 1000) {
             addPage();
             ystart = 10;
             xstart = 10;
             addNotes(xstart+15, ystart, notes[i]->noteName, notes[i]->octave, duration, notes[i]->index);
         }
         else{
             ystart+=50;
             xstart=10;
             measure = false;
             addNotes(xstart+15, ystart, notes[i]->noteName, notes[i]->octave, duration, notes[i]->index);
           }
     }
     completeDrawing();
 }

};


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    note* n1 = new note;
        n1->duration = "e";
        n1->index = 1;
        n1->noteName = "a";
        n1->octave = 4;
        note* n2 = new note;
        n2->duration = "e";
        n2->index = 5;
        n2->noteName = "b";
        n2->octave = 4;
        note* n3 = new note;
        n3->duration = "e";
        n3->index = 9;
        n3->noteName = "f";
        n3->octave = 4;
        note* n4 = new note;
        n4->duration = "e";
        n4->index = 13;
        n4->noteName = "g";
        n4->octave = 4;
        note* n5 = new note;
        n5->duration = "e";
        n5->index = 1;
        n5->noteName = "a";
        n5->octave = 4;
        note* n6 = new note;
        n6->duration = "e";
        n6->index = 5;
        n6->noteName = "b";
        n6->octave = 4;
        note* n7 = new note;
        n7->duration = "e";
        n7->index = 9;
        n7->noteName = "f";
        n7->octave = 4;
        note* n8 = new note;
        n8->duration = "e";
        n8->index = 16;
        n8->noteName = "g";
        n8->octave = 4;
        note *n9 = new note;
        n9->duration = "e";
        n9->index = 1;
        n9->noteName = "a";
        n9->octave = 4;
        note* n10 = new note;
        n10->duration = "e";
        n10->index = 5;
        n10->noteName = "b";
        n10->octave = 4;
        note* n11 = new note;
        n11->duration = "e";
        n11->index = 9;
        n11->noteName = "f";
        n11->octave = 4;
        note* n12 = new note;
        n12->duration = "e";
        n12->index = 13;
        n12->noteName = "g";
        n12->octave = 4;
        note* n13 = new note;
        n13->duration = "e";
        n13->index = 1;
        n13->noteName = "g";
        n13->octave = 4;
        note *n14 = new note;
        n14->duration = "e";
        n14->index = 5;
        n14->noteName = "a";
        n14->octave = 4;
        note* n15 = new note;
        n15->duration = "e";
        n15->index = 9;
        n15->noteName = "b";
        n15->octave = 4;
        note* n16 = new note;
        n16->duration = "e";
        n16->index = 13;
        n16->noteName = "f";
        n16->octave = 4;
        note* n17 = new note;
        n17->duration = "e";
        n17->index = 1;
        n17->noteName = "g";
        n17->octave = 4;
        note *n18 = new note;
        n18->duration = "e";
        n18->index = 5;
        n18->noteName = "a";
        n18->octave = 4;
        note* n19 = new note;
        n19->duration = "e";
        n19->index = 9;
        n19->noteName = "b";
        n19->octave = 4;
        note* n20 = new note;
        n20->duration = "e";
        n20->index = 13;
        n20->noteName = "f";
        n20->octave = 4;
        vector<note*> notes;
        notes.push_back(n1);
        notes.push_back(n2);
        notes.push_back(n3);
        notes.push_back(n4);
        notes.push_back(n5);
        notes.push_back(n6);
        notes.push_back(n7);
        notes.push_back(n8);
        notes.push_back(n9);
        notes.push_back(n10);
        notes.push_back(n11);
        notes.push_back(n12);
        notes.push_back(n13);
        notes.push_back(n14);
        notes.push_back(n15);
        notes.push_back(n16);
        notes.push_back(n17);
        notes.push_back(n18);
        notes.push_back(n19);
        notes.push_back(n20);

    PDFexport * test = new PDFexport;
    int pos_x = 10, pos_y = 10;
    test->setPenFormat(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
    test->drawPage(pos_x,pos_y);
    test->readVector(notes);
    return 0;
}
