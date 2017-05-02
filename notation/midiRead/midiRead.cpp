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

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main() {
    // tpq --> Ticks per quarter note
    int tpq = 0;
    // midi tracks
    int tracks = 0;
    MidiFile midifile;
    midifile.read("hyruleField_museri.mid");

    tpq = midifile.getTicksPerQuarterNote();
    tracks = midifile.getTrackCount();

    cout << "TPQ: " << tpq << endl;
    cout << "Tracks: " << tracks << endl;

    midifile.linkNotePairs();

    // So midifile[track].size() represents the num. of elements in the
    // array of events for that track
    int track = 0;
    int tickTime = 0;
    for ( int event = 0; event < midifile[track].size(); event++){
        tickTime = midifile[track][event].tick;
        
        cout << dec << tickTime;
        cout << '\t' << hex;


        
        for (int i = 0; i < midifile[track][event].size(); i++){
            cout << (int)midifile[track][event][i] << ' ';
        }

        // Detect time signature from header / control messages
        // Return timesig as string of form '4/4', '6/8', '5/4', etc.
        if ((midifile[track][event][0] == 0xff) && 
            (midifile[track][event][1] == 0x58) && 
            (midifile[track][event][2] == 0x04)) {
            
            int num = midifile[track][event][3];
            int den = pow(midifile[track][event][4], 2);
            string timesig = to_string(num) + '/' + to_string(den);

            cout << "timesig == " << timesig;
        }

        // Detect keysignature from header / control messages
        // Return key signarture as signed int between -7 and 7 representing
        // the number of flats(negative) or sharps(positive)
        if ((midifile[track][event][0] == 0xff) && 
            (midifile[track][event][1] == 0x59) && 
            (midifile[track][event][2] == 0x02)) {
            signed char keychar = midifile[track][event][3];
            int keysig = keychar;
            cout << dec << "KeySig == " << keysig;
        }

        if ((midifile[track][event][0] == 0xff) && 
            (midifile[track][event][1] == 0x2f) && 
            (midifile[track][event][2] == 0x00)) {
            cout << "End of Track";
        }

        //cout << endl;

        
        if (midifile[track][event].isNoteOn() == 1) {
            cout << midifile[track][event].getTickDuration() << endl;
        }
        else{
            cout << endl;
        }
        
    }

    return 0;
}