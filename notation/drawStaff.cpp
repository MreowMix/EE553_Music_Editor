#include <QApplication>
#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <QFont>
#include <QDebug>
#include <string>
#include <iostream>
#include <sstream>

#include "include/readMidi.h"
using namespace std;

#define MEASURE_LEN 240


QDebug operator<<(QDebug out, const std::string& str)
{
    out << QString::fromStdString(str);
    return out;
}


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

    void renderNote(int xpos, int ypos, int ind, int yoff, string dur, int sharpOrFlat = 0) {
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
        QString noteChar;
        if (dur == "q"){
            if (yoff <= 20) {noteChar = "Q";}
            else {noteChar = "q";} 
            p.setFont(QFont("Norfolk Std", 26));
            p.drawText(xpos + ind, ypos+yoff , noteChar);
            if (sharpOrFlat == 1) {p.drawText(xpos + ind - 10, ypos+yoff , "#");}
            else if (sharpOrFlat == 2) {p.drawText(xpos + ind - 10, ypos+yoff , "b");}
        }
        else if (dur == "e"){
            if (yoff <= 20) {noteChar = "E";}
            else {noteChar = "e";} 
            p.setFont(QFont("Norfolk Std", 26));
            p.drawText(xpos + ind, ypos+yoff , noteChar);
            if (sharpOrFlat == 1) {p.drawText(xpos + ind - 10, ypos+yoff , "#");}
            else if (sharpOrFlat == 2) {p.drawText(xpos + ind - 10, ypos+yoff , "b");}
        }
        else if (dur == "s"){
            if (yoff <= 20) {noteChar = "X";}
            else {noteChar = "x";} 
            p.setFont(QFont("Norfolk Std", 26));
            p.drawText(xpos + ind, ypos+yoff , noteChar);
            if (sharpOrFlat == 1) {p.drawText(xpos + ind - 10, ypos+yoff , "#");}
            else if (sharpOrFlat == 2) {p.drawText(xpos + ind - 10, ypos+yoff , "b");}
        }
        else if (dur == "h") {
            if (yoff <= 20) {noteChar = "H";}
            else {noteChar = "h";} 
            p.setFont(QFont("Norfolk Std", 26));
            p.drawText(xpos + ind, ypos+yoff , noteChar);
            if (sharpOrFlat == 1) {p.drawText(xpos + ind - 10, ypos+yoff , "#");}
            else if (sharpOrFlat == 2) {p.drawText(xpos + ind - 10, ypos+yoff , "b");}
        }
        else if (dur == "w") {
            noteChar = "w";
            p.setFont(QFont("Norfolk Std", 26));
            p.drawText(xpos + ind, ypos+yoff , noteChar);
            if (sharpOrFlat == 1) {p.drawText(xpos + ind - 10, ypos+yoff , "#");}
            else if (sharpOrFlat == 2) {p.drawText(xpos + ind - 10, ypos+yoff , "b");}    
        }
        else if (dur == "dq") {
            if (yoff <= 20) {noteChar = "Q";}
            else {noteChar = "q";} 
            p.setFont(QFont("Norfolk Std", 26));
            p.drawText(xpos + ind, ypos+yoff , noteChar);
            p.setFont(QFont("Norfolk Std", 34));
            p.drawText(xpos + ind + 14, ypos+yoff , ".");
            p.setFont(QFont("Norfolk Std", 26));
            if (sharpOrFlat == 1) {p.drawText(xpos + ind - 10, ypos+yoff , "#");}
            else if (sharpOrFlat == 2) {p.drawText(xpos + ind - 10, ypos+yoff , "b");}        
        }
        else if (dur == "dh") {
            if (yoff <= 20) {noteChar = "H";}
            else {noteChar = "h";} 
            p.setFont(QFont("Norfolk Std", 26));
            p.drawText(xpos + ind, ypos+yoff , noteChar);
            p.setFont(QFont("Norfolk Std", 34));
            p.drawText(xpos + ind + 14, ypos+yoff , ".");
            p.setFont(QFont("Norfolk Std", 26));
            if (sharpOrFlat == 1) {p.drawText(xpos + ind - 10, ypos+yoff , "#");}
            else if (sharpOrFlat == 2) {p.drawText(xpos + ind - 10, ypos+yoff , "b");}    
        }
        else if (dur == "de") {
            if (yoff <= 20) {noteChar = "E";}
            else {noteChar = "e";} 
            p.setFont(QFont("Norfolk Std", 26));
            p.drawText(xpos + ind, ypos+yoff , noteChar);
            p.setFont(QFont("Norfolk Std", 34));
            p.drawText(xpos + ind + 14, ypos+yoff , ".");
            p.setFont(QFont("Norfolk Std", 26));
            if (sharpOrFlat == 1) {p.drawText(xpos + ind - 10, ypos+yoff , "#");}
            else if (sharpOrFlat == 2) {p.drawText(xpos + ind - 10, ypos+yoff , "b");}  
        }

    }

    // Add notes to blank measure created by newMeasure method
    void drawNotes(string note, int octave, string duration, int startIndex) {
        bool temp_pos = false;
        int y_offset;
        if (pos_y > 0 && pos_x == 0) {
            pos_y = pos_y - 80;
            pos_x = MEASURE_LEN*5+100;
            temp_pos = true;
        }
        
        double ind_mod = 0.0;
        int index = 0;
        
        if (timesig == "4/4") {
            ind_mod = (double)MEASURE_LEN / (double)(16 + 2);
        }

        else if (timesig == "3/4") {
            ind_mod = (double)MEASURE_LEN / (double)(12 + 2);
        }

        index = (startIndex * ind_mod) - MEASURE_LEN;
        if (clef == "treble") {

            if (note == "a") {
                if (octave == 4) {
                    y_offset = 25;
                    renderNote(pos_x, pos_y, index, y_offset, duration);
                } 
            }
            else if (note == "ash") {
                if (octave == 4) {
                    y_offset = 25;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 1);
                }
            }
            else if (note == "afl") {
                if (octave == 4) {
                    y_offset = 25;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 2);
                }
            }

            else if (note == "b") {
                if (octave == 4) {
                    y_offset = 20;
                    renderNote(pos_x, pos_y, index, y_offset, duration);
                }
            }
            else if (note == "bfl") {
                if (octave == 4) {
                    y_offset = 20;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 2);  
                }
            }


            else if (note == "c") {
                if (octave == 4) {
                    y_offset = 50;
                    renderNote(pos_x, pos_y, index, y_offset, duration);
                    p.drawLine(pos_x + index - 2, pos_y+50,
                                pos_x + index + 16, pos_y+50);
                }
                else if (octave == 5) {
                    y_offset = 15;
                    renderNote(pos_x, pos_y, index, y_offset, duration);
                }
            }
            else if (note == "csh") {
                if (octave == 4) {
                    y_offset = 50;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 1);
                    p.drawLine(pos_x + index - 2, pos_y+50,
                                pos_x + index + 16, pos_y+50);
                }
                else if (octave == 5) {
                    y_offset = 15;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 1);
                }
            }

            else if (note == "d") {
                if (octave == 4) {
                    y_offset = 45;
                    renderNote(pos_x, pos_y, index, y_offset, duration);
                }
                else if (octave == 5) {
                    y_offset = 10;
                    renderNote(pos_x, pos_y, index, y_offset, duration);
                }
            }
            else if (note == "dsh") {
                if (octave == 4) {
                    y_offset = 45;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 1);
                }
                else if (octave == 5) {
                    y_offset = 10;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 1);
                }
            }
            else if (note == "dfl") {
                if (octave == 4) {
                    y_offset = 45;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 2);
                }
                else if (octave == 5) {
                    y_offset = 10;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 2);
                }
            }

            else if (note == "e") {
                if (octave == 4) {
                    y_offset = 40;
                    renderNote(pos_x, pos_y, index, y_offset, duration);
                }
                else if (octave == 5) {
                    y_offset = 5;
                    renderNote(pos_x, pos_y, index, y_offset, duration);
                }
            }
            else if (note == "efl") {
                if (octave == 4) {
                    y_offset = 40;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 2);
                }
                else if (octave == 5) {
                    y_offset = 5;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 2);
                }
            }

            else if (note == "f") {
                if (octave == 4) {
                    y_offset = 35;
                    renderNote(pos_x, pos_y, index, y_offset, duration);
                }
                else if (octave == 5) {
                    y_offset = 0;
                    renderNote(pos_x, pos_y, index, y_offset, duration);    
                }
            }
            else if (note == "fsh") {
                if (octave == 4) {
                    y_offset = 35;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 1);
                }
                else if (octave == 5) {
                    y_offset = 0;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 1);    
                }
            }

            else if (note == "g") {
                if (octave == 4) {
                    y_offset = 30;
                    renderNote(pos_x, pos_y, index, y_offset, duration);
                }
                else if (octave == 5) {
                    y_offset = -5;
                    renderNote(pos_x, pos_y, index, y_offset, duration);  
                }
            }
            else if (note == "gsh") {
                if (octave == 4) {
                    y_offset = 30;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 1);
                }
                else if (octave == 5) {
                    y_offset = -5;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 1);  
                }
            }
            else if (note == "gfl") {
                if (octave == 4) {
                    y_offset = 30;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 2);
                }
                else if (octave == 5) {
                    y_offset = -5;
                    renderNote(pos_x, pos_y, index, y_offset, duration, 2);  
                }
            }

            else if (note == "r") {
                if (duration == "q"){
                    p.setFont(QFont("Norfolk Std", 34));
                    // this square is a  quarter rest, character code 0xce
                    p.drawText(pos_x + index, pos_y+20 , "");   
                }
                else if (duration == "e") {
                    p.setFont(QFont("Norfolk Std", 34));
                    // this is an eigth rest
                    p.drawText(pos_x + index, pos_y+20 , "");
                }
                else if (duration == "h") {
                    // this is a half rest
                    p.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::SquareCap));
                    p.drawLine(pos_x+index-3, pos_y+18, pos_x+index+3, pos_y+18);
                }
                else if (duration == "w") {
                    // this is a half rest
                    p.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::SquareCap));
                    p.drawLine(pos_x+index-3, pos_y+12, pos_x+index+3, pos_y+12);
                }
                else if (duration == "dh"){
                    p.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::SquareCap));
                    p.drawLine(pos_x+index-3, pos_y+18, pos_x+index+3, pos_y+18);
                    p.setFont(QFont("Norfolk Std", 34));
                    p.drawText(pos_x + index + 8, pos_y+19 , ".");
                    p.setFont(QFont("Norfolk Std", 26));    
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



    /*
    // create first measure , isBegin = true isEnd = false
    staff.newMeasure(true, false);
    // Draws notes on the previously created staff
    // displays an a3 quarter note on the treble clef
    // the index values correspond to the position left-right on the measure
    staff.drawNotes("a", 4, "s", 1);
    staff.drawNotes("gsh", 4, "dh", 5);
    staff.drawNotes("gfl", 5, "dq", 9);
    staff.drawNotes("r", 4, "dh", 13);    
    staff.display();
    */

    readMidi myMidi("vivaldiSpring.mid");
    drawStaff staff("treble", myMidi.timesig);
    vector<note> noteArray = myMidi.buildArray();
    //qDebug() << "KeySig: " << test.keysig;
    //qDebug() << "TimeSig: " <<test.getTimeSig();

    
    for (int i = 0; i < noteArray.size(); i++) {
        //qDebug() << "Note " << i << ": " << noteTest[i].noteName << "RhythmType: " << noteTest[i].duration << "Index: " << noteTest[i].index;
        if (noteArray[i].index == 1) {
            if (i == 0) {staff.newMeasure(true, false);}
            else {staff.newMeasure(false, false);}    
        }
        staff.drawNotes(noteArray[i].noteName, noteArray[i].octave, noteArray[i].duration, noteArray[i].index);
    }
    staff.display();

    //return 0;

    return a.exec();
}
