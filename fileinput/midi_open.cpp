/*midi_open.cpp
 * Aurthor: ERWEI ZHU
 */

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int hexCharToInt(char c)
{
        return int(c);
}

int main()
{

    const int SIZE1 =120;
    char filename[SIZE1];
    long file_size;
    char buffer_char;
    int buffer_int;
    vector<char> message_char;
    vector<int> message_int;
    ifstream open_file;
    ifstream get_size;
    ifstream read_file;

    cout << "Enter The Name of Data File: ";

    while(!cin.eof()){
        cin.getline(filename,SIZE1);
        open_file.open(filename);
        if(!open_file.is_open())
        {
            cout << "Could not open the file,Please check again!!"<<'\n';
            break;
        }
        else
        {
           ifstream get_size(filename);
           get_size.seekg(0,ios::end);
           file_size=get_size.tellg();
           get_size.close();

           ifstream read_file(filename,std::ios::binary);
            for(int i=0;i<file_size;i++)
            {
                read_file.get(buffer_char);
                message_char.push_back(buffer_char);
                buffer_int = hexCharToInt(buffer_char);
                message_int.push_back(buffer_int);
            }
            cout <<endl;
        }
        return 0;
    }
}

