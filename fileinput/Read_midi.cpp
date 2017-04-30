#include "midi.hh"
#include <iostream>
#include <fstream>
#include <math.h>
#include <map>


using namespace std;


int TRACK_NUMBER=0;

class Midifile{
private:
      long size;
      char *buffer;
      void swap(Midifile& orig){
          long temp =size;
          size=orig.size;
          orig.size=temp;

          char* temp2=buffer;
          buffer=orig.buffer;
          orig.buffer=temp2;
      }
public:
      Midifile(const char* filename){
          ifstream  in(filename,ios::in|ios::binary|ios::ate);
          size = in.tellg();
          in.seekg(0,ios::beg);
          buffer = new char[size];
          in.read(buffer,size);
          in.close();
      }

      ~Midifile(){
          delete []buffer;
      }

      Midifile(const Midifile& orig):size(orig.size),buffer(new char[size]){
          for(int i=0;i<size;i++)
              buffer[i]=orig.buffer[i];
      }

      Midifile& operator=(Midifile orig){
          swap(orig);
          return *this;
      }

      vector<unsigned char> Getdata(){
          vector<unsigned char> data;
          for(int i=0;i<size;i++){
              data.push_back(buffer[i]);
          }
          return data;
      }

      int Getsize(){
          return size;
      }



};

class Header:public Midifile{
private:
    unsigned char *ff_ff;
    unsigned char *nn_nn;
    unsigned char *dd_dd;
    int track_num;
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
    Header(const char* f):Midifile(f),ff_ff(new unsigned char[2]),nn_nn(new unsigned char[2]),dd_dd(new unsigned char[2]){
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

    vector<unsigned char> GetFormat(){
        vector<unsigned char> format;
        for(int i=0;i<2;i++){
            format.push_back(ff_ff[i]);
        }
        format.push_back('\r');
        format.push_back('\n');
        return format;
    }

    vector<unsigned char> GetTrackNumChar(){
        vector<unsigned char> Num;
        for(int i=0;i<2;i++){
            Num.push_back(nn_nn[i]);
        }
        Num.push_back('\r');
        Num.push_back('\n');
        return Num;
    }

    vector<unsigned char> GetDIV(){
        vector<unsigned char> DIV;
        for(int i=0;i<2;i++){
            DIV.push_back(dd_dd[i]);
        }
        DIV.push_back('\r');
        DIV.push_back('\n');
        return DIV;
    }

    int GetTrackNum(){
        return track_num;
    }
};

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
    Track(const char* f):Header(f),track_length(new unsigned char[4]){
        vector<unsigned char> Track;
        Track=Getdata();
        for(int i=0;i<Track.size();i++){
            if((Track[i]=='M')&&(Track[i+2]=='r')){
                i=i+4;

                length=0;
                for(int j=0;j<4;j++){
                    track_length[j]=Track[i];
                    track_length_char.push_back(track_length[j]);
                    track.push_back(track_length[j]);
                    length=length+long(Track[i++])*pow(16,((3-j)*2));
                }
                track_length_char.push_back('|');
                track.push_back('|');

                track_event= new unsigned char[length];
                long Truck_lenght= length-4;
                for(int j=0;j<Truck_lenght;j++){
                    Event.push_back(Track[i]);
                    track.push_back(Track[i++]);
                }
                Event.push_back('\r');
                Event.push_back('\n');
                track.push_back('\r');
                track.push_back('\n');
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

    vector<unsigned char> GetTrackLengthChar(){
        return track_length_char;
    }

    vector<unsigned char> GetTrackEvent(){
        return Event;
    }

    vector<unsigned char> GetTrack(){
        return track;
    }

    int GetTrackLength(){
        return length;
    }


};


class MetaEvent{
private:
    unsigned char meta_type;
    unsigned char *data;
    vector<string> meta;
    vector<unsigned char> meta_type_list;
    vector<unsigned char> meta_L;
    vector<unsigned char> notation;
    void swap(MetaEvent& orig){
        unsigned char* temp1=data;
        data=orig.data;
        orig.data=temp1;

        unsigned char temp2=meta_type;
        meta_type=orig.meta_type;
        orig.meta_type=temp2;
    }
public:


    MetaEvent(vector<unsigned char> Event){
        vector<unsigned char> track_midi_event = Event;

        for(int i=0;i<track_midi_event.size();i++){
           if((track_midi_event[i]==0)&&(track_midi_event[i+1]==255)){
              i+=2;
              meta_type=track_midi_event[i++];
              meta_type_list.push_back(meta_type);
              meta_type_list.push_back('|');
              int meta_length = int(track_midi_event[i]);
              meta_L.push_back(track_midi_event[i++]);
              data = new unsigned char[meta_length+2];

              for(int j=0;j<meta_length;j++){
                  data[j]=track_midi_event[i++];
              }

              data[meta_length]='\r';
              data[meta_length+1]='\n';


              string meta_string= (char*)data;
              meta_string=meta_string.substr(0,meta_length+2);
              meta.push_back(meta_string);

              i--;
           }
           else{
               if((track_midi_event[i]=='\r')&&(track_midi_event[i+1]=='\n')){
                   notation.push_back('|');
                   i=i+1;
               }
               else{
                   notation.push_back(track_midi_event[i]);
               }
           }
        }
    }

    ~MetaEvent(){
        delete []data;
         meta.clear();
         meta_type_list.clear();\
         meta_L.clear();
         notation.clear();
    }

    MetaEvent& operator=(MetaEvent orig){
        swap(orig);
        return *this;
    }

    vector<unsigned char> GetMetaTypeList(){
        return meta_type_list;
    }

    vector<unsigned char> GetMetaTypeLength(){
        return meta_L;
    }

    vector<string> GetMetaEvent(){
          return meta;
    }

    vector<unsigned char> GetNotation(){
        return notation;
    }


};

void WriteHeader(vector<unsigned char> data){
    ofstream file("MThd.txt",ios::binary);
    for(int i=0;i<data.size();i++){
        file.write((char*)&data[i],sizeof(data[i]));
    }
    file.close();
}

void WriteHeaderApp(vector<unsigned char> data){
    ofstream file("MThd.txt",ios::binary|ios::app);
    for(int i=0;i<data.size();i++){
        file.write((char*)&data[i],sizeof(data[i]));
    }
    file.close();
}

void WriteTrack(vector<unsigned char> data){
    ofstream file("Track.txt",ios::binary);
    for(long i=0;i<data.size();i++){
        file.write((char*)&data[i],sizeof(data[i]));
    }
    file.close();
}

void WriteMap(vector<unsigned char> key, vector<string> e){
    ofstream file("Meta.txt",ios::binary);
    for(int i=0;i<key.size();i+=2){
        file.write((char*)&key[i],sizeof(key[i]));
        file.write((char*)&key[i+1],sizeof(key[i+1]));
        string s= e[i/2];
        const char* buffer=s.c_str();
        file.write((char*)buffer,s.size());
    }
    file.close();
}

void WriteNota(vector<unsigned char> data){
    ofstream file("Notation.txt",ios::binary);
    for(long i=0;i<data.size();i++){
        file.write((char*)&data[i],sizeof(data[i]));
    }
    file.close();
}


int main(){


    const char * filename= "Martin.mid";
    Header h1(filename);

    Format =h1.GetFormat();
    WriteHeader(Format);

    Num =h1.GetTrackNumChar();
    TRACK_NUMBER=h1.GetTrackNum();
    WriteHeaderApp(Num);

    DIV =h1.GetDIV();
    WriteHeaderApp(DIV);


    Track t1(filename);

    Track_Data =t1.GetTrackEvent();

    WriteTrack(Track_Data);

    Track_Length=t1.GetTrackLengthChar();

    Track_event =t1.GetTrackEvent();

    MetaEvent m(Track_event);
    Meta_Type = m.GetMetaTypeList();
    Meta_Length=m.GetMetaTypeLength();

    Meta_Event = m.GetMetaEvent();
    WriteMap(Meta_Type,Meta_Event);

    Nota =m.GetNotation();
    WriteNota(Nota);

    int a=0;
}
