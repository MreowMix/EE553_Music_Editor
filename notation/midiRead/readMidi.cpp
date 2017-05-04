// Required includes to use Craig Sapp's "midifile" library
#include "midifile-include/MidiFile.h"
#include "midifile-include/MidiFile.cpp"
#include "midifile-include/MidiEvent.h"
#include "midifile-include/MidiEvent.cpp"
#include "midifile-include/MidiEventList.h"
#include "midifile-include/MidiEventList.cpp"
#include "midifile-include/MidiMessage.h"
#include "midifile-include/MidiMessage.cpp"
#include "midifile-include/Binasc.h"
#include "midifile-include/Binasc.cpp"
// End of "midifile" includes

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

struct note {
    string noteName, duration;
    int octave, index;
};

struct pitch {
    string noteName;
    int octave;
};

class readMidi {
private:
    int tpq;
    string file;
    MidiFile midifile;
    vector<pitch> pitchTable;
    vector<pitch> pitchTableGen( bool flatOrSharp = 1 ) {
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

    readMidi (string f = "hyruleField_museri.mid") : file(f) {
        midifile.read(file);
        tpq = midifile.getTicksPerQuarterNote();
        keysig = getKeySig();
        timesig = getTimeSig();
        midifile.linkNotePairs();
        pitchTable = pitchTableGen();
    }

    int getKeySig() {
        int ks = 0;
        for (int event = 0; event < midifile[0].size() ; event++){
            // Detect keysignature from header / control messages
            if ((midifile[0][event][0] == 0xff) && 
                (midifile[0][event][1] == 0x59) && 
                (midifile[0][event][2] == 0x02)) {
                signed char keychar = midifile[0][event][3];
                ks = keychar;
            }
        }
        return ks;
    }

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

    int getTPQ(){
        return tpq;
    }

    int getNotePos(int startTime){
    int qpm, pos = 0;
        if (timesig == "4/4"){
            qpm = 4;       
        }
        if (startTime > 0) {
            pos = round((double)startTime / (double)(tpq / qpm)) + 1;
        }
        else {
            pos = 0;
        }
        return pos;
    }

    void buildArray(){
        double curTime, curDuration;
        int measureIndexTot;
        int curMeasure = 0;
        if (timesig == "4/4") {measureIndexTot = 16;}
        int curIndexMax = measureIndexTot;
        // iterate through all events 
        for (int event = 0; event < midifile[0].size() ; event++){
            if (midifile[0][event].isNoteOn() == 1) {
                int curNote, curIndex;

                curNote = (int)midifile[0][event][1];
                curTime = (int)midifile[0][event].tick;
                curIndex = getNotePos(curTime);

                if (curIndex > curIndexMax) {
                    curMeasure += 1;
                    curIndexMax = curIndexMax + measureIndexTot;
                }

                curIndex = curIndex - (16 * curMeasure);

                curDuration = (int)midifile[0][event].getTickDuration();
                cout << pitchTable[curNote].noteName << " @ " << curTime << " for: " << curDuration << " Index: "<< curIndex << endl;
            }
        }
    }


};


int main(){
    readMidi test;

    cout << dec << test.keysig << endl;
    cout << test.getTPQ() << endl;
    cout << test.getTimeSig() << endl;
    test.buildArray();
    return 0;
}