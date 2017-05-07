#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>
#include <QFile>
using namespace std;



//The same use as the Read_midi.cpp
extern int TRACK_NUMBER;
extern vector<unsigned char> Head_Data;
extern vector<unsigned char> Track_Data;
extern vector<unsigned char> Track_Length;
extern vector<unsigned char> Track_event;
extern vector<unsigned char> Meta_Type;
extern vector<unsigned char> Meta_Length;
extern vector<unsigned char> Meta_event;
extern vector<unsigned char> Nota_event;
extern void Create(const char* filename);
extern char CharTrans(int n);
extern string CharToString(char first ,char second);

//Create a new Header Chunk
//A Header Chunk is structured as: MThd + Header length + Format + Track Number + Tick Speed
//Default as 1 Track , Speed as 120
class Header{
private:
    string Head="MThd";
    char* standard;
    char* format;
    char* Num;
    char* Speed;
public:
    Header():standard(new char[4]),format(new char[2]),Num(new char[2]),Speed(new char[2]){
        standard[0]=0x00;
        standard[1]=0x00;
        standard[2]=0x00;
        standard[3]=0x06;
        format[0]=0x00;
        format[1]=0x01;
        Num[0]=0x00;
        Num[1]=0x01;
        Speed[0]=0x00;
        Speed[1]=0x78;
    }

    ~Header(){
        delete []standard;
        delete []format;
        delete []Num;
        delete []Speed;
    }

    // set Header Trunck
    vector<unsigned char> setHead(){
        vector<unsigned char> buffer;
        const char *buffer1;
        buffer1=Head.c_str();
        for(int i=0;i<Head.size();i++){
            buffer.push_back(buffer1[i]);
        }
        for(int i=0;i<4;i++){
            buffer.push_back(standard[i]);
        }
        return buffer;
    }

    //set Format
    vector<unsigned char> setFormat(){
        vector<unsigned char> buffer;
        for(int i=0;i<2;i++){
            buffer.push_back(format[i]);
        }
        return buffer;
    }
   
    //set Track number
    vector<unsigned char> setNum(){
        vector<unsigned char> buffer;
        for(int i=0;i<2;i++){
            buffer.push_back(Num[i]);
        }
        return buffer;
    }

    //set Tick Speed
    vector<unsigned char> setSpeed(){
        vector<unsigned char> buffer;
        for(int i=0;i<2;i++){
            buffer.push_back(Speed[i]);
        }
        return buffer;
    }
};


//Create a new Track Chunk
//A Track Chunk is structured as: MTrk + Track length + Track Event
//Defalut as 1 Meta Event and no notation
class Track{
private:
    string Track_head="MTrk";
    string title ="NEW";
    char* length;
    char* meta_event;
    char* notation;
public:
    Track():length(new char[4]),meta_event(new char[11]){
        length[0]=0x00;
        length[1]=0x00;
        length[2]=0x00;
        length[3]=0x0B;

        meta_event[0]=0x00;
        meta_event[1]=0xFF;
        meta_event[2]=0x03;
        meta_event[3]=0x03;

        const char *buffer;
        buffer=title.c_str();

        meta_event[4]=buffer[0];
        meta_event[5]=buffer[1];
        meta_event[6]=buffer[2];


        meta_event[7]=0x00;
        meta_event[8]=0xFF;
        meta_event[9]=0x2F;
        meta_event[10]=0x00;
    }

    //set Track Data
    vector<unsigned char> setTrack(){
        vector<unsigned char> buffer;
        const char *buffer1;
        buffer1=Track_head.c_str();
        for(int i=0;i<Track_head.size();i++){
            buffer.push_back(buffer1[i]);
        }
        return buffer;
    }

    //set Track length
    vector<unsigned char> setTrackLength(){
        vector<unsigned char> buffer;
        for(int i=0;i<4;i++){
            buffer.push_back(length[i]);
        }
        return buffer;
    }

    //set Track Event
    vector<unsigned char> setTrackEvent(){
        vector<unsigned char> buffer;
        for(int i=0;i<11;i++){
            buffer.push_back(meta_event[i]);
        }
        return buffer;
    }
};

//Write a new midi file
void WriteHeader1(vector<unsigned char> data){
    ofstream file("New.midi",ios::binary);
    for(int i=0;i<data.size();i++){
        file.write((char*)&data[i],sizeof(data[i]));
    }
    file.close();
}

//Append new data into the midi file
void WriteHeaderApp1(vector<unsigned char> data){
    ofstream file("New.midi",ios::binary|ios::app);
    for(int i=0;i<data.size();i++){
        file.write((char*)&data[i],sizeof(data[i]));
    }
    file.close();
}

//wait for use
void Create(const char* filename){

}
