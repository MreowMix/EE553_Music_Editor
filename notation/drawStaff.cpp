#include <QApplication>
#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <QFont>
#include <string>
#include <iostream>
using namespace std;

#define MEASURE_LEN 210

class drawStaff{
private:
    string clef, timesig, keysig;
    int pos_x, pos_y;
    QLabel l;
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

    // Add notes blank measure created by newMeasure method
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

        index = (startIndex * ind_mod) - MEASURE_LEN;
        if (note == 'a') {
            if (octave == 3) {
                if (duration == 'q') {
                    p.setFont(QFont("Norfolk Std", 26));
                    p.drawText(pos_x + index, pos_y+25 , "q");
                }   
            }
        }
        else if (note == 'c') {

        }
        else if (note == 'd') {

        }
        else if (note == 'e') {

        }
        else if (note == 'f') {

        }
        else if (note == 'g') {

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
    staff.newMeasure(true, false);
    // Draws notes on the previously created staff
    staff.drawNotes('a', 3, 'q', 1);
    staff.drawNotes('a', 3, 'q', 5);
    staff.drawNotes('a', 3, 'q', 9);
    staff.drawNotes('a', 3, 'q', 13);
    for (int i = 0; i < 20; i++) {
        staff.newMeasure(false, false);
        staff.drawNotes('a', 3, 'q', 1);
        staff.drawNotes('a', 3, 'q', 5);
        staff.drawNotes('a', 3, 'q', 9);
        staff.drawNotes('a', 3, 'q', 13);
    }
    staff.newMeasure(false, true);
    staff.drawNotes('a', 3, 'q', 1);
    staff.drawNotes('a', 3, 'q', 5);
    staff.drawNotes('a', 3, 'q', 9);
    staff.drawNotes('a', 3, 'q', 13);
    staff.display();
    return a.exec();
}
