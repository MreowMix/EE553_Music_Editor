#include <iostream>
#include <string>
using namespace std;

int main(){

struct note {
    string noteName;
    string duration;
    int octave;
};

note pitchTable[128];

for (int c = 0; c < 121; c+=12){
    pitchTable[c].noteName = "c";
    pitchTable[c].octave = (c/12) - 1;
}

int oct = -1;
for (int csh = 1; csh < 122; csh+=12){
    pitchTable[csh].noteName = "csh";
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
    pitchTable[dsh].noteName = "dsh";
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
    pitchTable[fsh].noteName = "fsh";
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
    pitchTable[gsh].noteName = "gsh";
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
    pitchTable[ash].noteName = "ash";
    pitchTable[ash].octave = oct;
    oct += 1;
}

oct = -1;
for (int b = 11; b < 120; b+=12){
    pitchTable[b].noteName = "b";
    pitchTable[b].octave = oct;
    oct += 1;
}

for ( int i = 0; i < 128; i++ ) {
    cout << i << " Note Name: " << pitchTable[i].noteName << " " << "Octave: " << pitchTable[i].octave << endl;
}

}
