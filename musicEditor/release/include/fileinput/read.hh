#ifndef READ_HH
#define READ_HH

#include <iostream>
#include <fstream>
#include <math.h>
#include <map>
#include <string>
#include <vector>
#include <QtGlobal>
#include <sstream>

#include "include/fileinput/midi.hh"
#include "include/fileinput/chartostring.hh"


using namespace std;

//get head data，because i need to use the track number
extern vector<unsigned char> Head_Data;

//get track data, because i need to get the notation
extern vector<unsigned char> Track_Data;

//get track length,because i need to set the size for store the notation
extern vector<unsigned char> Track_Length;

//get track event, because i need to seperate the notation
extern vector<unsigned char> Track_event;

//get meta type, becuase i need to get the meta for the furture use
extern vector<unsigned char> Meta_Type;

//get meta length,because i need to get the size for store the meta
extern vector<unsigned char> Meta_Length;

//get meta event, becuase i need to print out the meta
extern vector<unsigned char> Meta_event;

//get notation event,because i need to print out the notation
extern vector<unsigned char> Nota_event;

//read filename and file size,because i need to get which file to read
extern void Read(const char* temp,int file_size);

//transfer char to printout,because the data is read as byte and print out as the char
char CharTrans(int n);

//transfer byte to string,because i need to combined the chars as a string
string ByteToString(unsigned char n);

//transfer int to string, because i need to read the length as int and print out as string
string intTostring(int n);



//This class is for reading the data in byte of a midi file
class MidifileREAD{
private:
      long size;
      char *buffer;
      void swap(MidifileREAD& orig){
          long temp =size;
          size=orig.size;
          orig.size=temp;

          char* temp2=buffer;
          buffer=orig.buffer;
          orig.buffer=temp2;
      }
public:
      MidifileREAD(const char* file,int file_size):size(file_size),buffer(new char[size]){
          for(int i=0;i<size;i++){
              buffer[i]=file[i];
          }
      }

      ~MidifileREAD(){
          delete []buffer;
      }

      MidifileREAD(const MidifileREAD& orig):size(orig.size),buffer(new char[size]){
          for(int i=0;i<size;i++)
              buffer[i]=orig.buffer[i];
      }

      MidifileREAD& operator=(MidifileREAD orig){
          swap(orig);
          return *this;
      }

      //get data, because i need to use this data to get different parts of the data
      vector<unsigned char> Getdata(){
          vector<unsigned char> data;
          for(int i=0;i<size;i++){
              data.push_back(buffer[i]);
          }
          return data;
      }

      //get size, because i need to know the size for check
      int Getsize(){
          return size;
      }

};

//This class is for reading the Header Chunk data of a midi file
//A Header Chunk is structured as: MThd + Header length + Format + Track Number + Tick Speed
//Seperate the data with the mark "\r\n"
class Header:public MidifileREAD{
private:
    unsigned char *ff_ff;
    unsigned char *nn_nn;
    unsigned char *dd_dd;
    int track_num;
    int tick;
    void swap(Header& orig){
        unsigned char* temp1=ff_ff;
        ff_ff=orig.ff_ff;
        orig.ff_ff=temp1;

        unsigned char* temp2=nn_nn;
        nn_nn=orig.nn_nn;
        orig.nn_nn=temp2;

        unsigned char* temp3=dd_dd;
        dd_dd=orig.dd_dd;
        orig.dd_dd=temp3;

        int temp4 =track_num;
        track_num=orig.track_num;
        orig.track_num=temp4;
    }
public:
    Header(const char* f,int s):MidifileREAD(f,s),ff_ff(new unsigned char[2]),nn_nn(new unsigned char[2]),dd_dd(new unsigned char[2]){
        vector<unsigned char> Head;
        Head=Getdata();
        int i=0;
        while((Head[i]=='M')&&(Head[i+2]=='h')){
            i=i+8;
            for(int j=0;j<2;j++){
                ff_ff[j]=Head[i++];
            }
            for(int j=0;j<2;j++){
                nn_nn[j]=Head[i++];
            }
            track_num= int(nn_nn[0])*16+int(nn_nn[1]);
            for(int j=0;j<2;j++){
                dd_dd[j]=Head[i++];
            }
            tick= int(dd_dd[0])*16+int(dd_dd[1]);
            break;
        }
    }

    ~Header(){
        delete []ff_ff;
        delete []nn_nn;
        delete []dd_dd;

    }

    Header& operator=(Header orig){
        swap(orig);
        return *this;
    }

    //get Format,because i need to know the format
    vector<unsigned char> GetFormat(){
        vector<unsigned char> format;
        for(int i=0;i<2;i++){
            format.push_back(ff_ff[i]);
        }
        format.push_back('\r');
        format.push_back('\n');
        return format;
    }

     //get track number in byte,because i need to know the numbers of track for checking
    vector<unsigned char> GetTrackNumChar(){
        vector<unsigned char> Num;
        for(int i=0;i<2;i++){
            Num.push_back(nn_nn[i]);
        }
        Num.push_back('\r');
        Num.push_back('\n');
        return Num;
    }

    //get speed in byte,because i need to know the speed for checking
    vector<unsigned char> GetDIV(){
        vector<unsigned char> DIV;
        for(int i=0;i<2;i++){
            DIV.push_back(dd_dd[i]);
        }
        DIV.push_back('\r');
        DIV.push_back('\n');
        return DIV;
    }

    //get head data in byte, for seperating the head data
    vector<unsigned char> GetHead(){
        vector<unsigned char> buffer;
        for(int i=0;i<2;i++){
            buffer.push_back(ff_ff[i]);
        }
        buffer.push_back('\r');
        buffer.push_back('\n');

        for(int i=0;i<2;i++){
            buffer.push_back(nn_nn[i]);
        }
        buffer.push_back('\r');
        buffer.push_back('\n');

        for(int i=0;i<2;i++){
            buffer.push_back(dd_dd[i]);
        }
        buffer.push_back('\r');
        buffer.push_back('\n');
        return buffer;
    }

    //get track number in int,because i need to know the numbers of track for printing
    int GetTrackNum(){
        return track_num;
    }

    //get tick speed in int,because i need to print out the speed
    int GetTick(){
        return tick;
    }
};

//This class is for reading the Track Chunk data of a midi file
//A Track Chunk is structured as: MTrk + Track length + Track Event
//Seperate the each status with the mark "\r\n"
class Track:public Header{
private:
    long length;
    unsigned char *track_length;
    unsigned char *track_event;
    vector<unsigned char> Event;
    vector<unsigned char> track_length_char;
    vector<unsigned char> track;
    void swap(Track& orig){

        long temp1 =length;
        length=orig.length;
        orig.length=temp1;

        unsigned char* temp2=track_length;
        track_length=orig.track_length;
        orig.track_length=temp2;

        unsigned char* temp3=track_event;
        track_event=orig.track_event;
        orig.track_event=temp3;
    }

public:
    Track(const char* f,int s):Header(f,s),track_length(new unsigned char[4]){
        vector<unsigned char> Track;
        Track=Getdata();

        for(int i=0;i<Track.size();i++){

            if((Track[i]=='M')&&(Track[i+2]=='r')){
                i=i+4;

                length=0;
                for(int j=0;j<4;j++){
                    track_length[j]=Track[i];
                    track_length_char.push_back(track_length[j]);
                    length=length+long(Track[i++])*pow(16,((3-j)*2));
                }

                track_length_char.push_back('|');

                track_event= new unsigned char[length];
                long Truck_lenght= length;
                for(int j=0;j<Truck_lenght;j++){
                    Event.push_back(Track[i]);
                    track.push_back(Track[i++]);
                }
                Event.push_back('\r');
                Event.push_back('\n');

                i--;
            }
        }
    }

    ~Track(){
        delete []track_length;
        delete []track_event;
        track_length_char.clear();
        Event.clear();
        track.clear();
    }

    Track& operator=(Track orig){
        swap(orig);
        return *this;
    }

     //get track length in byte,because i need to know the length for checking
    vector<unsigned char> GetTrackLengthChar(){
        return track_length_char;
    }

   //get track event in byte
    vector<unsigned char> GetTrackEvent(){
        return Event;
    }

    //get track data in byte,because i need to use the track data to get the notation
    vector<unsigned char> GetTrack(){
        return track;
    }

    //get track length in int, becuase i need to know the size to get the notation
    int GetTrackLength(){
        return length;
    }


};

//This class is for reading the Notation of a midi file
//A Notation is structured as: Speed + command nibble + Data
//Speed is determined as VLV:80~8F + length or length
//command nibble: 80~FF
//Seperate each status with the mark "\r\n"
//Seperate tracks with the mark"00 2F FF 00"
class Notation_Event:public Track{
private:
    long nota_size;
    unsigned int tick;
    unsigned int delta;
    string end_flag;
    vector<string> tracknotas;
public:
       Notation_Event(const char* f,int s):Track(f,s){
           nota_size=GetTrack().size();
           vector<unsigned char> track_nota=GetTrack();

           tick=0;
           int i=0;

           while(i<nota_size){

               // Judege the length, because the speed is stored as VLV form
               // Judege the end of a track, because i need to seperate different tracks
               if((track_nota[i]==0x00)&&(track_nota[i+1]==0xFF)&&(track_nota[i+2]==0x2F)&&(track_nota[i+3]==0x00)){
                   end_flag = intTostring(tick)+'\t'+"ff 2f 00"+"\r\n";
                   tracknotas.push_back(end_flag);
                   i=i+4;
                   tick=0;
                   continue;
               }
               else if((track_nota[i]==0x0D)&&(track_nota[i+1]==0x0A)){
                   i=i+2;
                   continue;
               }
               else if((track_nota[i]>=0x80)&&((track_nota[i]<=0x8F))){

                   int time = track_nota[i]-0x80;
                   int add =128*time;
                   unsigned char start = track_nota[i];

                   int j=0;
                   while(start>=0x80){
                       j++;
                       start = track_nota[i+j];
                   }
                   for(int l=j;l>0;l--){
                       delta = delta+(pow(add,(l-1))*(track_nota[i+1]));
                   }
                   delta=delta+add;
                   tick =tick+delta;
                   i=i+j;
               }
               else{
                   delta = track_nota[i];
                   tick = tick+delta;
               }

               //Judge the status, because each status should be printed out as one line
               //The rule of different status are different , so i need to follow the certain rule to print out
               if((track_nota[i+1]>=0xB0)&&(track_nota[i+1]<0xC0)){
                   if((track_nota[i+2]>=0x66)&&(track_nota[i+2]<=0x77)){

                       string note = ByteToString(track_nota[i+1]);
                       string pitch = ByteToString(track_nota[i+2]);

                       string nota = intTostring(tick)+'\t'+note+' '+pitch+"\r\n";
                       tracknotas.push_back(nota);
                       i=i+3;
                   }
                   else{

                       string note = ByteToString(track_nota[i+1]);
                       string pitch = ByteToString(track_nota[i+2]);
                       string loudness = ByteToString(track_nota[i+3]);

                       string nota = intTostring(tick)+'\t'+note+' '+pitch+' '+loudness+"\r\n";
                       tracknotas.push_back(nota);
                       i=i+4;
                   }
               }
               else if((track_nota[i+1]>=0xC0)&&(track_nota[i+1]<0xE0)){


                   string note = ByteToString(track_nota[i+1]);
                   string pitch = ByteToString(track_nota[i+2]);

                   string nota = intTostring(tick)+'\t'+note+' '+pitch+"\r\n";
                   tracknotas.push_back(nota);
                   i=i+3;
               }
               else if((track_nota[i+1]>=0xF0)&&(track_nota[i+1]<0xFF)){
                   if((track_nota[i+1]==0xF3)||(track_nota[i+1]==0xF1)){



                       string note = ByteToString(track_nota[i+1]);
                       string pitch = ByteToString(track_nota[i+2]);

                       string nota = intTostring(tick)+'\t'+note+' '+pitch+"\r\n";
                       tracknotas.push_back(nota);
                       i=i+3;
                   }
                   else if((track_nota[i+1]==0xF2)){

                       string note = ByteToString(track_nota[i+1]);
                       string pitch = ByteToString(track_nota[i+2]);
                       string loudness = ByteToString(track_nota[i+3]);

                       string nota = intTostring(tick)+'\t'+note+' '+pitch+' '+loudness+"\r\n";
                       tracknotas.push_back(nota);
                       i=i+4;
                   }
                   else if((track_nota[i+1]==0xF0)){

                       string note = ByteToString(track_nota[i+1]);
                       int length = track_nota[i+2];
                       string nota =intTostring(tick)+'\t'+note+' ';
                       int start =i+3;
                       for(int j=0;j<length;j++){
                           nota = nota + ByteToString(track_nota[start+j])+' ';
                       }
                       nota=nota+"\r\n";
                       tracknotas.push_back(nota);
                       i=i+length+3;
                   }
                   else{

                       string note = ByteToString(track_nota[i+1]);

                       string nota = intTostring(tick)+'\t'+note+"\r\n";
                       tracknotas.push_back(nota);
                       i=i+2;
                   }
               }
               else if(track_nota[i+1]==0xFF){
                   string note = ByteToString(track_nota[i+1]);
                   string type = ByteToString(track_nota[i+2]);


                   int length = track_nota[i+3];
                   string l= ByteToString(length);

                   string nota =intTostring(tick)+'\t'+note+' '+type+' '+l+' ';
                   int start =i+4;
                   for(int j=0;j<length;j++){
                       nota = nota + ByteToString(track_nota[start+j])+' ';
                   }
                   nota=nota+"\r\n";
                   tracknotas.push_back(nota);
                   i=i+length+4;
               }
               else{
                   string note = ByteToString(track_nota[i+1]);
                   string pitch = ByteToString(track_nota[i+2]);
                   string loudness = ByteToString(track_nota[i+3]);

                   string nota = intTostring(tick)+'\t'+note+' '+pitch+' '+loudness+"\r\n";
                   tracknotas.push_back(nota);
                   i=i+4;
               }
           }
       }

    ~Notation_Event(){
        tracknotas.clear();
        end_flag.empty();
    }

    // get the notation ,because i need to print out the notation
    vector<string> GetNotation(){
        return tracknotas;
    }

};


//This class is for reading the Meta data of a midi file
//A Meata is structured as: Speed + FF + Meta type + Meta length + Meta Event
//Seperate the data with the mark "|"
class Seperate_Event:public Track{
private:
    unsigned char meta_type;
    unsigned char *data;
    vector<unsigned char> meta_char;
    void swap(Seperate_Event& orig){
        unsigned char* temp1=data;
        data=orig.data;
        orig.data=temp1;

        unsigned char temp2=meta_type;
        meta_type=orig.meta_type;
        orig.meta_type=temp2;
    }
public:


    Seperate_Event(const char* f,int s):Track(f,s){
        vector<unsigned char> track_midi_event =GetTrackEvent();
        for(int i=0;i<track_midi_event.size();i++){
           if((track_midi_event[i+1]==255)&&(track_midi_event[i+2]!=47)){
              i+=2;
              meta_type=track_midi_event[i++];

              meta_char.push_back(meta_type);
              meta_char.push_back(meta_type);

              int meta_length = int(track_midi_event[i]);
              meta_char.push_back(track_midi_event[i++]);
              meta_char.push_back(meta_type);

              data = new unsigned char[meta_length];

              for(int j=0;j<meta_length;j++){
                  data[j]=track_midi_event[i++];
                  meta_char.push_back(data[j]);
                  meta_char.push_back(meta_type);
              }

              meta_char.push_back('|');
              i--;
           }
        }
    }

    ~Seperate_Event(){
        delete []data;
         meta_char.clear();
    }

    Seperate_Event& operator=(Seperate_Event orig){
        swap(orig);
        return *this;
    }

     // get Meta Data in byte, because i nened to know the Meta data for checking
    vector<unsigned char> GetMetaListChar(){
        return meta_char;
    }
};

//write Header Chunk in Header.hex file, because i need to store the header data
void WriteHeader(vector<unsigned char> data){
    ofstream file("Header.hex",ios::binary);
    for(int i=0;i<data.size();i++){
        file.write((char*)&data[i],sizeof(data[i]));
    }
    file.close();
}

//write Track Chunk in Track.hex file,because i need to store the Track data
void WriteTrack(vector<unsigned char> data){
    ofstream file("Track.hex",ios::binary);
    for(long i=0;i<data.size();i++){
        file.write((char*)&data[i],sizeof(data[i]));
    }
    file.close();
}

//write Meta Data in Meta.hex file, because i need to store the meta data
void WriteMeta(vector<unsigned char> data){
    ofstream file("Meta.hex",ios::binary);
    for(int i=0;i<data.size();i++){
        file.write((char*)&data[i],sizeof(data[i]));
    }
    file.close();
}

//Read the notation and write in the Notation.txt file
//Format:
//      Tick speed
//      Track Number
//      Track Event
//      End flag
// Because i need to print out the notation for editing
void ReadNota(string tick,int tracks,vector<string> notation){
    ofstream file("Notation.txt");

    file<<"TPQ: "<<tick<<endl;

    string track_s=intTostring(tracks);

        file<<"Tracks: "<<track_s<<endl;



       file<<"\nTrack " << intTostring(0)<<endl;

    int track=1,n=0;
    while((track<=tracks)&&(n<notation.size())){
       string s=notation[n];
       string::size_type idx =s.find("ff 2f 00");
       if((idx!=string::npos)){
           file<<notation[n];
           if(track<tracks){
             file<<"\nTrack " << intTostring(track++)<<endl;
           }
           n++;
       }
       else{
           file<<notation[n];
           n++;
       }
    }
    file.close();
}

//Because i know the filename and the file size, i should read the data to print out the notation
void Readmidi(const char* temp,int file_size){

        Header h1(temp,file_size);

        Head_Data =h1.GetHead();
        WriteHeader(Head_Data);

        Track t1(temp,file_size);

        Track_Data =t1.GetTrackEvent();

        WriteTrack(Track_Data);

        Track_Length=t1.GetTrackLengthChar();

        Seperate_Event m(temp,file_size);
        Meta_event = m.GetMetaListChar();
        WriteMeta(Meta_event);

        Notation_Event n(temp,file_size);
        vector<string> nota=n.GetNotation();


        string tick=intTostring(h1.GetTick());
        int tracks =h1.GetTrackNum();
        ReadNota(tick, tracks,nota);
}

#endif // READ_HH
