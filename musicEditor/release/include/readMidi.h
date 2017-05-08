// Required includes to use Craig Sapp's "midifile" library
#include "midifile/MidiFile.h"
#include "midifile/MidiFile.cpp"
#include "midifile/MidiEvent.h"
#include "midifile/MidiEvent.cpp"
#include "midifile/MidiEventList.h"
#include "midifile/MidiEventList.cpp"
#include "midifile/MidiMessage.h"
#include "midifile/MidiMessage.cpp"
#include "midifile/Binasc.h"
#include "midifile/Binasc.cpp"
// End of "midifile" includes

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;


// Structs defining a note (ready to be used in drawStaff) and a pitch (used to
// convert from midi pitch value to a note name and octave)
struct note {
    string noteName, duration;
    int octave, index;
};

struct pitch {
    string noteName;
    int octave;
};

/*
This class iterates through note events in the midi file to output an array
of notes in sequential order to be used by drawStaff to render notation to the
GUI and used by pdfedport to render to PDF
*/
class readMidi {
private:
    int tpq;
    string file;
    MidiFile midifile;
    vector<pitch> pitchTable;
    vector<pitch> pitchTableGen( bool flatOrSharp = 1 ) {
        // this just generates a standard table of midi pitches
        vector<pitch> pitchTable(128);
        for (int c = 0; c < 121; c+=12){
            pitchTable[c].noteName = "c";
            pitchTable[c].octave = (c/12) - 1;
        }

        int oct = -1;
        for (int csh = 1; csh < 122; csh+=12){
            if (flatOrSharp == 1) {pitchTable[csh].noteName = "csh";}
            else if (flatOrSharp == 0) {pitchTable[csh].noteName = "dfl";}
            pitchTable[csh].octave = oct;
        oct += 1;
        }

        oct = -1;
        for (int d = 2; d < 123; d+=12){
            pitchTable[d].noteName = "d";
            pitchTable[d].octave = oct;
        oct += 1;
        }


        oct = -1;
        for (int dsh = 3; dsh < 124; dsh+=12){
            if (flatOrSharp == 1) {pitchTable[dsh].noteName = "dsh";}
            else if (flatOrSharp == 0) {pitchTable[dsh].noteName = "efl";}
            pitchTable[dsh].octave = oct;
        oct += 1;
        }

        oct = -1;
        for (int e = 4; e < 125; e+=12){
            pitchTable[e].noteName = "e";
            pitchTable[e].octave = oct;
        oct += 1;
        }

        oct = -1;
        for (int f = 5; f < 126; f+=12){
            pitchTable[f].noteName = "f";
            pitchTable[f].octave = oct;
        oct += 1;
        }

        oct = -1;
        for (int fsh = 6; fsh < 127; fsh+=12){
            if (flatOrSharp == 1) {pitchTable[fsh].noteName = "fsh";}
            else if (flatOrSharp == 0) {pitchTable[fsh].noteName = "gfl";}
            pitchTable[fsh].octave = oct;
        oct += 1;
        }


        oct = -1;
        for (int g = 7; g < 128; g+=12){
            pitchTable[g].noteName = "g";
            pitchTable[g].octave = oct;
        oct += 1;
        }

        oct = -1;
        for (int gsh = 8; gsh < 117; gsh+=12){
            if (flatOrSharp == 1) {pitchTable[gsh].noteName = "gsh";}
            else if (flatOrSharp == 0) {pitchTable[gsh].noteName = "afl";}
            pitchTable[gsh].octave = oct;
        oct += 1;
        }

        oct = -1;
        for (int a = 9; a < 118; a+=12){
            pitchTable[a].noteName = "a";
            pitchTable[a].octave = oct;
        oct += 1;
        }

        oct = -1;
        for (int ash = 10; ash < 119; ash+=12){
            if (flatOrSharp == 1) {pitchTable[ash].noteName = "ash";}
            else if (flatOrSharp == 0) {pitchTable[ash].noteName = "bfl";}
            pitchTable[ash].octave = oct;
        oct += 1;
        }

        oct = -1;
        for (int b = 11; b < 120; b+=12){
            pitchTable[b].noteName = "b";
            pitchTable[b].octave = oct;
        oct += 1;
        }
        return pitchTable;    
    }

public:
    int keysig;
    string timesig;

    // gets in useful header data from the midifile
    readMidi (string f = "hyruleField_museri_edit.mid") : file(f) {
        midifile.read(file);
        tpq = midifile.getTicksPerQuarterNote();
        keysig = getKeySig();
        timesig = getTimeSig();
        midifile.linkNotePairs();
        pitchTable = pitchTableGen();
    }

    // gets the key signature integer from the MIDI file (currently unused)
    int getKeySig() {
        int ks = 0;
        for (int event = 0; event < midifile[0].size() ; event++){
            // Detect keysignature from header / control messages
            if ((midifile[0][event][0] == 0xff) && 
                (midifile[0][event][1] == 0x59) && 
                (midifile[0][event][2] == 0x02)) {
                unsigned char keychar = midifile[0][event][3];
                ks = keychar;
                return ks;
            }
        }
    }

    // gets the time signature from the MIDI file
    string getTimeSig() {
        for (int event = 0; event < midifile[0].size() ; event++){
            if ((midifile[0][event][0] == 0xff) && 
                (midifile[0][event][1] == 0x58) && 
                (midifile[0][event][2] == 0x04)) {
                
                int num = midifile[0][event][3];
                int den = pow(midifile[0][event][4], 2);
                string ts = to_string(num) + '/' + to_string(den);

                return ts;
            }
        }   
    }

    // logic to figure out the horizontal index position of a note or rest
    int getNotePos(int startTime){
        int qpm, pos = 0;
        if (timesig == "4/4") {qpm = 4;}
        else if (timesig == "6/8") {qpm = 3;}
        else if (timesig == "3/4") {qpm = 3;}
        else if (timesig == "5/4") {qpm = 5;}
        if (startTime > 0) {
            pos = round((double)startTime / (double)(tpq / qpm)) + 1;
        }
        else {
            pos = 0;
        }
        return pos;
    }

    // determines the rhythmtype of a note (ex: quarter note, eigth note, etc.)
    string rhythmType(double duration) {
        duration = duration / (double)tpq;
        duration = floor(duration * 100) / 100;
        //cout << duration << endl;
        if ((duration > 0.85) && (duration < 1.15)) {return "q";}
        else if ((duration > 1.85) && (duration < 2.15)) {return "h";}
        else if ((duration > 3.85) && (duration < 4.15)) {return "w";}
        else if ((duration > 2.85) && (duration < 3.15)) {return "dh";}
        else if ((duration > 0.40) && (duration < 0.60)) {return "e";}
        else if ((duration > 0.20) && (duration < 0.30)) {return "s";}
        else if ((duration > 0.65) && (duration < 0.85)) {return "de";}
        else if ((duration > 1.35) && (duration < 1.65)) {return "dq";}
        //else {return "q";}
        //return duration;   
    }

    // iterates through the events in the midifile to return a vector of notes
    vector<note> buildArray(){
        vector<note> noteArray;
        double curTime, curDuration;
        int measureIndexTot;
        int qpm;
        int curMeasure = 0;
        if (timesig == "4/4") {measureIndexTot = 16; qpm = 4;}
        else if (timesig == "6/8") {measureIndexTot = 12; qpm = 3;}
        else if (timesig == "3/4") {measureIndexTot = 12; qpm = 3;}
        else if (timesig == "5/4") {measureIndexTot = 20; qpm = 5;}
        int curIndexMax = measureIndexTot;
        // iterate through all events 
        for (int event = 0; event < midifile[0].size() ; event++){
            if (midifile[0][event].isNoteOn() == 1) {
            note restTemp, noteTemp;
                if (((midifile[0][event-1].isNoteOff() == 1) && ((int)midifile[0][event].tick - (int)midifile[0][event-1].tick > tpq/(qpm/2) - 1)) || 
                   ((midifile[0][event].isNoteOn() == 1) && (midifile[0][event-1].isNoteOff() == 0) && ((int)midifile[0][event-1].tick == 0))) {
                    int restTickDuration, restIndex;
                    
                    if ((midifile[0][event].isNoteOn() == 1) && (midifile[0][event-1].isNoteOff() == 0) && ((int)midifile[0][event-1].tick == 0)) {
                        restTickDuration = (int)midifile[0][event].tick;
                        restIndex = 1;
                    }
                    else {
                        restIndex = getNotePos((int)midifile[0][event-1].tick);
                        restTickDuration = (int)midifile[0][event].tick - (int)midifile[0][event-1].tick;
                    }
                    string restDuration = rhythmType(restTickDuration);

                    if (restIndex > curIndexMax) {
                        curMeasure += 1;
                        curIndexMax = curIndexMax + measureIndexTot;
                    }
                    restIndex = restIndex - (measureIndexTot * curMeasure);

                    restTemp.noteName = "r";
                    restTemp.octave = 0;
                    restTemp.duration = restDuration;
                    restTemp.index = restIndex;

                    noteArray.push_back(restTemp); 
                }
                
                
                int curNote, curIndex;
                curNote = (int)midifile[0][event][1];
                curTime = (int)midifile[0][event].tick;
                curIndex = getNotePos(curTime);

                if (curIndex > curIndexMax) {
                    curMeasure += 1;
                    curIndexMax = curIndexMax + measureIndexTot;
                }

                curIndex = curIndex - (measureIndexTot * curMeasure);

                curDuration = (int)midifile[0][event].getTickDuration();
                string noteRhythm = rhythmType(curDuration);
                noteTemp.noteName = pitchTable[curNote].noteName;
                noteTemp.octave = pitchTable[curNote].octave;
                noteTemp.duration = noteRhythm;
                noteTemp.index = curIndex;

                noteArray.push_back(noteTemp);
            }
        }
        return noteArray;
    }


};
