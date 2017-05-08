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

 void addNotes(int xs, int ys, string note, int octave, QString duration, int startIndex, int sharpOrFlat = 0) {
   p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
   p->setFont(QFont("Norfolk Std", 14));
   if(note=="r"){
      //if we have a rest we don't care what clef we are in
       if(duration=="w"){
           p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
           p->drawLine(xs+((startIndex -1)*10),ys+12,xs+((startIndex -1)*10)+5,ys+12);
         }
       else if(duration=="h"){
           p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
           p->drawLine(xs+((startIndex -1)*10),ys+8,xs+((startIndex -1)*10)+5,ys+8);
         }
       else if(duration =="dh"){
           p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
           p->drawLine(xs+((startIndex -1)*10),ys+8,xs+((startIndex -1)*10)+5,ys+8);
           p->setFont(QFont("Norfolk Std", 16));
           p->drawText(xs+((startIndex -1)*10)+8,ys+8,".");
           p->setFont(QFont("Norfolk Std", 14));
         }
       else if(duration=="q"){
           p->drawText(xs+((startIndex -1)*10),ys+10, "");
         }
       else if(duration=="e"){
           p->drawText(xs+((startIndex -1)*10),ys+10, "");
          }
    }

   //just dealing with treble clef and notes that fall on treble clef for now
   //if index == 1 we just started a new measure so we should draw a bar line before we start
   if(clef == "treble"){
       if(octave == 4){
             if(note=="d"){
                 p->drawText(xs+((startIndex -1)*10),ys+22.5,duration);
               }
             else if(note=="dsh"){
                 p->drawText(xs+((startIndex -1)*10),ys+22.5,duration);
                 p->drawText(xs-5+((startIndex -1)*10),ys+22.5,"#");
               }
             else if(note=="dfl"){
                 p->drawText(xs+((startIndex -1)*10),ys+22.5,duration);
                 p->drawText(xs-5+((startIndex -1)*10),ys+22.5,"b");
               }
             else if(note=="e"){
                 p->drawText(xs+((startIndex -1)*10),ys+20,duration);
             }
             else if(note=="esh"){
                 p->drawText(xs+((startIndex -1)*10),ys+20,duration);
                 p->drawText(xs-5+((startIndex -1)*10),ys+20,"#");
               }
             else if(note == "efl"){
                 p->drawText(xs+((startIndex -1)*10),ys+20,duration);
                 p->drawText(xs-5+((startIndex -1)*10),ys+20,"b");
               }
             else if(note=="f"){
                 p->drawText(xs+((startIndex -1)*10),ys+17.5,duration);
               }
             else if(note=="fsh"){
                 p->drawText(xs+((startIndex -1)*10),ys+17.5,duration);
                 p->drawText(xs-5+((startIndex -1)*10),ys+17.5,"#");
               }
             else if(note=="ffl"){
                 p->drawText(xs+((startIndex -1)*10),ys+17.5,duration);
                 p->drawText(xs-5+((startIndex -1)*10),ys+17.5,"b");
               }
             else if(note=="g"){
                 p->drawText(xs+((startIndex -1)*10),ys+15,duration);
               }
             else if(note=="gsh"){
                 p->drawText(xs+((startIndex -1)*10),ys+15,duration);
                 p->drawText(xs-5+((startIndex -1)*10),ys+15,"#");
               }
             else if(note=="gfl"){
                 p->drawText(xs+((startIndex -1)*10),ys+15,duration);
                 p->drawText(xs-5+((startIndex -1)*10),ys+15,"b");
               }
             else if(note=="a"){
                     p->drawText(xs+((startIndex -1)*10),ys+12.5,duration);
               }
             else if(note=="ash"){
                     p->drawText(xs+((startIndex -1)*10),ys+12.5,duration);
                     p->drawText(xs-5+((startIndex -1)*10),ys+12.5,"#");
               }
             else if(note=="afl"){
                     p->drawText(xs+((startIndex -1)*10),ys+12.5,duration);
                     p->drawText(xs-5+((startIndex -1)*10),ys+12.5,"b");
               }
             else if(note=="b"){
                 p->drawText(xs+((startIndex -1)*10),ys+10,duration);
               }
             else if(note=="bsh"){
                 p->drawText(xs+((startIndex -1)*10),ys+10,duration);
                 p->drawText(xs-5+((startIndex -1)*10),ys+10,"#");

               }
             else if(note=="bfl"){
                 p->drawText(xs-5+((startIndex -1)*10),ys+10,duration);
                 p->drawText(xs-5+((startIndex -1)*10),ys+10,"b");

               }
           }
     else if(octave == 5){
        if(note =="c"){
            p->drawText(xs+((startIndex -1)*10),ys + 7.5,duration);
          }
        else if (note=="csh"){
            p->drawText(xs+((startIndex -1)*10),ys + 7.5,duration);
            p->drawText(xs-5+((startIndex -1)*10),ys + 7.5,"#");
          }
        else if(note=="d"){
            p->drawText(xs+((startIndex -1)*10),ys + 5,duration);
          }
        else if(note=="dsh"){
            p->drawText(xs+((startIndex -1)*10),ys + 5,duration);
            p->drawText(xs-5+((startIndex -1)*10),ys + 5,"#");
          }
        else if(note=="dfl"){
            p->drawText(xs+((startIndex -1)*10),ys + 5,duration);
            p->drawText(xs-5+((startIndex -1)*10),ys + 5,"b");
          }
        else if(note=="e"){
            p->drawText(xs+((startIndex -1)*10),ys + 2.5,duration);
          }
        else if(note=="esh"){
            p->drawText(xs+((startIndex -1)*10),ys + 2.5,duration);
            p->drawText(xs-5+((startIndex -1)*10),ys + 2.5,"#");
          }
        else if(note=="efl"){
            p->drawText(xs+((startIndex -1)*10),ys + 2.5,duration);
            p->drawText(xs-5+((startIndex -1)*10),ys + 2.5,"b");
          }
        else if(note=="f"){
            p->drawText(xs+((startIndex -1)*10),ys,duration);
          }
        else if(note=="fsh"){
            p->drawText(xs+((startIndex -1)*10),ys,duration);
            p->drawText(xs-5+((startIndex -1)*10),ys,"#");
          }
        else if(note=="g"){
            p->drawText(xs+((startIndex -1)*10),ys-2.5,duration);
          }
        else if(note=="gsh"){
            p->drawText(xs+((startIndex -1)*10),ys-2.5,duration);
            p->drawText(xs+((startIndex -1)*10),ys-2.5, "#");
          }
        else if(note=="gfl"){
            p->drawText(xs+((startIndex -1)*10),ys-2.5,duration);
            p->drawText(xs+((startIndex -1)*10),ys-2.5, "b");
          }
     }
 }
 }

 void completeDrawing() {
     p->end();
 }

 void readVector(vector<note> notes) {
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
         QString duration = QString::fromStdString(notes[i].duration);
         //don't need to go to new line or new page
         if (((xstart <= 440 && notes[i].index==1)||(xstart <= 640 && notes[i].index!=1))&& ystart <= 950) {
             if(notes[i].index == 1 && !measure){
                 xstart = xstart + 20;
               }
             else if(notes[i].index > 1 && !measure){
                 measure = true;
              }
                 //we are now starting a new measure
             else if(notes[i].index == 1 && measure){
                 xstart = xstart + 180;
                 p->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap));
                 p->drawLine(xstart, ystart, xstart, ystart+20);
             }

             addNotes(xstart+15, ystart, notes[i].noteName, notes[i].octave, duration, notes[i].index);
         }
         else if(ystart > 1000) {
             addPage();
             ystart = 10;
             xstart = 30;
             addNotes(xstart+15, ystart, notes[i].noteName, notes[i].octave, duration, notes[i].index);
         }
         else{
             ystart+=50;
             xstart=30;
             measure = false;
             addNotes(xstart+15, ystart, notes[i].noteName, notes[i].octave, duration, notes[i].index);
           }
     }
     completeDrawing();
 }

};

