#ifndef MIDI_HH
#define MIDI_HH
#include<vector>
#include<string>
#include <QFile>

using namespace std;



vector<unsigned char> Head_Data;


vector<unsigned char> Track_Data;
vector<unsigned char> Track_Length;
vector<unsigned char> Track_event;
vector<unsigned char> Meta_Type;
vector<unsigned char> Meta_Length;
vector<unsigned char> Meta_event;
vector<unsigned char> Nota_event;



#endif // MIDI_HH

