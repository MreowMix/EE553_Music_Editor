/*List of a midi file
 *Aurthor: Erwei Zhu
 *Date: 05/01/2017
 */

#ifndef MIDI_HH
#define MIDI_HH
#include<vector>
#include<string>
#include <QFile>

using namespace std;


//Because i need to use these paramaters to store the differnet part of a midi file and for printing

//get Header Chunk Data
vector<unsigned char> Head_Data;
//get Track Chunk Data
vector<unsigned char> Track_Data;
//get Track Length
vector<unsigned char> Track_Length;
//get Track Event
vector<unsigned char> Track_event;
//get Meta List
vector<unsigned char> Meta_Type;
//get Meta Length
vector<unsigned char> Meta_Length;
//get Meta Event
vector<unsigned char> Meta_event;
//get Notation
vector<unsigned char> Nota_event;



#endif // MIDI_HH

