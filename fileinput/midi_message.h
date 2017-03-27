/*midi_message.h
 * The file is about all the character and functions in message
 * Aurthor: ERWEI ZHU
 */


#ifndef _midi_message_HH
#define _midi_message_HH

#include <vector>
#include <string>

using namespace std;

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;

class midi_message : public vector<uchar> {
public:
      midi_message          (void);
      midi_message          (int command);
      midi_message          (int command, int p1);
      midi_message          (int command, int p1, int p2);
      midi_message          (const midi_message& message);
      midi_message          (const vector<uchar>& message);
      midi_message          (const vector<char>& message);
      midi_message          (const vector<int>& message);


      ~midi_message         ();


      midi_message&   operator=            (const midi_message& message);
      midi_message&   operator=            (const vector<uchar>& bytes);
      midi_message&   operator=            (const vector<char>& bytes);
      midi_message&   operator=            (const vector<int>& bytes);


      void           setSize              (int size);
      int            getSize              (void) const;

      int            getTempoMicro        (void) const;
      int            getTempoMicroseconds (void) const;
      double         getTempoSeconds      (void) const;
      double         getTempoBPM          (void) const;
      double         getTempoTPS          (int tpq) const;
      double         getTempoSPT          (int tpq) const;

      int            isMetaMessage        (void) const;
      int            isMeta               (void) const;
      int            isNoteOff            (void) const;
      int            isNoteOn             (void) const;
      int            isNote               (void) const;
      int            isAftertouch         (void) const;
      int            isController         (void) const;
      int            isTimbre             (void) const;
      int            isPatchChange        (void) const;
      int            isPressure           (void) const;
      int            isPitchbend          (void) const;

      int            getP0                (void) const;
      int            getP1                (void) const;
      int            getP2                (void) const;
      int            getP3                (void) const;
      int            getKeyNumber         (void) const;
      int            getVelocity          (void) const;

      int            getCommandNibble     (void) const;
      int            getCommandByte       (void) const;
      int            getChannelNibble     (void) const;
      int            getChannel           (void) const;

      // meta-message related functions:
      int            getMetaType          (void) const;
      int            isTempo              (void) const;
      int            isEndOfTrack         (void) const;

};


#endif



