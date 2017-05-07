#ifndef CHARTOSTRING_HH
#define CHARTOSTRING_HH

#include<string>
using namespace std;


//Transfer the char for printing out
char CharTrans(int n){

     switch(n){
         case 0:{return '0';break;}
         case 1:{return '1';break;}
         case 2:{return '2';break;}
         case 3:{return '3';break;}
         case 4:{return '4';break;}
         case 5:{return '5';break;}
         case 6:{return '6';break;}
         case 7:{return '7';break;}
         case 8:{return '8';break;}
         case 9:{return '9';break;}
         case 10:{return 'a';break;}
         case 11:{return 'b';break;}
         case 12:{return 'c';break;}
         case 13:{return 'd';break;}
         case 14:{return 'e';break;}
         case 15:{return 'f';break;}
     }
}


//Transfer byte into string
string ByteToString(unsigned char n){
    int first= n/16;
    int second = n%16;
    char a = CharTrans(first);
    char b = CharTrans(second);
    char c[2]={a,b};
    string buffer(&c[0],&c[strlen(c)]);
    buffer=buffer.erase(2);
    return buffer;
}

//transfer int to string
string intTostring(int n){
    int j=1,i=0;
    vector<char> newstring;
    string buffer;

    while(j!=0)
    {
        j =n/10;
        newstring.push_back(n%10);
        n = j;
    }

    for(i=newstring.size()-1;i>=0;i--)
    {
        char x = newstring[i]%10+'0';
        buffer=buffer+x;
    }

    return buffer;

}


#endif // CHARTOSTRING_HH
