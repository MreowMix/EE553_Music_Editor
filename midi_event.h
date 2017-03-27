
#ifndef _midi_event_HH
#define _midi_event_HH

#include "midi_message.h"
#include <vector>

using namespace std;
typedef unsigned char  uchar;


class midi_event : public midi_message {
public:
      midi_event     (void);
      midi_event     (int command);
      midi_event     (int command, int param1);
      midi_event     (int command, int param1, int param2);
      midi_event     (int aTime, int aTrack, vector<uchar>& message);
      midi_event     (const midi_message& message);

      ~midi_event     ();

      midi_event& operator=     (const midi_event& mfevent);
      midi_event& operator=     (const midi_message& message);
      midi_event& operator=     (const vector<char>& bytes);
      midi_event& operator=     (const vector<int>& bytes);

      midi_event* getLinkedEvent(void);
      int        getTickDuration(void);
      double     getDurationInSeconds(void);

      int       tick;
      int       track;
      double    seconds;
      int       seq;

};


#endif



