// Skeleton file with very basic classes & descriptions for notation system

class midiDisplay {
// Class to display notation from MIDI data
// Uses internal data structure / file format provided by MIDI I/O team
// Will probably create an internal file format for notation data
private:

public: 
    // Function to read from internal data structure and then use that in 
    // rendering the notation
    void readData(){}

    // Function to render notation, possibly taking type of notation as an
    // argument -- ex: which instrument
    // Might need to use another graphics system (opengl?) to render over
    // standard Qt libraries
    void renderNotation() {}
};


class noteEdit {
// Class for editing displayed notation (moving, adding, changing notes)
// Likely to also be used for creating new files to save to midi
private:

public: 
    // Probably come up with a better name, but this logs changes to the
    // displayed notation to then record them in the local data structure
    void userInput() {}

    // Changes the notation data structure to reflect user changes
    void changeData() {}
};

class midiPlay {
// Class to play displayed midi file, will show position on notation display
private:

public:
    //function to show which note(s) are behing played (highlight in real-time)
    void displayPlaying() {}

    // function to output sound to system
    // might need to use different systems for different operating systems
    // ex: ALSA/pulse on Linux, whatever Windows uses
    void audioOutput() {}
};