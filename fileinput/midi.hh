#ifndef MIDI_HH
#define MIDI_HH
#include<vector>
#include<string>
using namespace std;

vector<unsigned char> Format;
vector<unsigned char> Num;
vector<unsigned char> DIV;

vector<unsigned char> Track_Data;
vector<unsigned char> Track_Length;
vector<unsigned char> Track_event;
vector<unsigned char> Meta_Type;
vector<unsigned char> Meta_Length;
vector<string>Meta_Event;
vector<unsigned char> Nota;


#endif // MIDI_HH

