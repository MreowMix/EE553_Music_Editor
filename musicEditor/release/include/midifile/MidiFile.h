// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Mon Feb 16 12:26:32 PST 2015 Adapted from binasc program.
// Last Modified: Wed Feb 18 14:48:21 PST 2015
// Filename:      midifile/include/MidiFile.h
// Website:       http://midifile.sapp.org
// Syntax:        C++11
// vim:           ts=3 expandtab
//
// Description:   A class which can read/write Standard MIDI files.
//                MIDI data is stored by track in an array.
//

#ifndef _MIDIFILE_H_INCLUDED
#define _MIDIFILE_H_INCLUDED

#include "MidiEventList.h"

#include <vector>
#include <istream>
#include <fstream>

using namespace std;

#define TIME_STATE_DELTA       0
#define TIME_STATE_ABSOLUTE    1

#define TRACK_STATE_SPLIT      0
#define TRACK_STATE_JOINED     1

class _TickTime {
   public:
      int    tick;
      double seconds;
};


class MidiFile {
   public:
                MidiFile                  (void);
                MidiFile                  (const char* aFile);
                MidiFile                  (const string& aFile);
                MidiFile                  (istream& input);
                MidiFile                  (const MidiFile& other);
                MidiFile                  (MidiFile&& other);
               ~MidiFile                  ();

      // reading/writing functions:
      int       read                      (const char* aFile);
      int       read                      (const string& aFile);
      int       read                      (istream& istream);
      int       write                     (const char* aFile);
      int       write                     (const string& aFile);
      int       write                     (ostream& out);
      int       writeHex                  (const char* aFile,   int width = 25);
      int       writeHex                  (const string& aFile, int width = 25);
      int       writeHex                  (ostream& out,        int width = 25);
      int       writeBinasc               (const char* aFile);
      int       writeBinasc               (const string& aFile);
      int       writeBinasc               (ostream& out);
      int       writeBinascWithComments   (const char* aFile);
      int       writeBinascWithComments   (const string& aFile);
      int       writeBinascWithComments   (ostream& out);
      int       status                    (void);

      // track-related functions:
      MidiEventList& operator[]           (int aTrack);
      const MidiEventList& operator[]     (int aTrack) const;
      int       getTrackCount             (void) const;
      int       getNumTracks              (void) const;
      int       size                      (void) const;

      // join/split track functionality:
      void      markSequence              (void);
      void      clearSequence             (void);
      void      joinTracks                (void);
      void      splitTracks               (void);
      void      splitTracksByChannel      (void);
      int       getTrackState             (void);
      int       hasJoinedTracks           (void);
      int       hasSplitTracks            (void);
      int       getSplitTrack             (int track, int index);
      int       getSplitTrack             (int index);

      void      sortTrack                 (MidiEventList& trackData);
      void      sortTracks                (void);

      int       addTrack                  (void);
      int       addTrack                  (int count);
      int       addTracks(int count) { return addTrack(count); }
      void      deleteTrack               (int aTrack);
      void      mergeTracks               (int aTrack1, int aTrack2);
      int       getTrackCountAsType1      (void);

      int       getEventCount             (int aTrack);
      void      allocateEvents            (int track, int aSize);
      int       getNumEvents              (int aTrack);

      // tick-related functions:
      void      deltaTicks                (void);
      void      absoluteTicks             (void);
      int       getTickState              (void);
      int       isDeltaTicks              (void);
      int       isAbsoluteTicks           (void);

      // ticks-per-quarter related functions:
      void      setMillisecondTicks       (void);
      int       getTicksPerQuarterNote    (void);
      int       getTPQ                    (void);
      void      setTicksPerQuarterNote    (int ticks);
      void      setTPQ                    (int ticks);

      // physical-time analysis functions:
      void      doTimeAnalysis            (void);
      double    getTimeInSeconds          (int aTrack, int anIndex);
      double    getTimeInSeconds          (int tickvalue);
      int       getAbsoluteTickTime       (double starttime);

      double    getTotalTimeInSeconds     (void);
      int       getTotalTimeInTicks       (void);
      double    getTotalTimeInQuarters    (void);

      // note-analysis functions:
      int       linkNotePairs             (void);
      int       linkEventPairs            (void);
      void      clearLinks                (void);

      // filename functions:
      void      setFilename               (const char* aname);
      void      setFilename               (const string& aname);
      const char* getFilename             (void);

      int       addEvent                  (int aTrack, int aTick,
                                           vector<uchar>& midiData);
      int       addEvent                  (MidiEvent& mfevent);

      // MIDI message adding convenience functions:
      int       addNoteOn                 (int aTrack, int aTick,
                                           int aChannel, int key, int vel);
      int       addNoteOff                (int aTrack, int aTick,
                                           int aChannel, int key, int vel);
      int       addNoteOff                (int aTrack, int aTick,
                                           int aChannel, int key);
      int       addController             (int aTrack, int aTick,
                                           int aChannel, int num, int value);
      int       addPatchChange            (int aTrack, int aTick,
                                           int aChannel, int patchnum);
      int       addTimbre                 (int aTrack, int aTick,
                                           int aChannel, int patchnum);
      int       addPitchBend              (int aTrack, int aTick,
                                           int aChannel, double amount);

      // Meta-event adding convenience functions:
      int       addMetaEvent              (int aTrack, int aTick, int aType,
                                             vector<uchar>& metaData);
      int       addMetaEvent              (int aTrack, int aTick, int aType,
                                           const char* metaData);
      int       addCopyright              (int aTrack, int aTick,
                                           const string& text);
      int       addTrackName              (int aTrack, int aTick,
                                           const string& name);
      int       addInstrumentName         (int aTrack, int aTick,
                                           const string& name);
      int       addLyric                  (int aTrack, int aTick,
                                           const string& text);
      int       addMarker                 (int aTrack, int aTick,
                                           const string& text);
      int       addCue                    (int aTrack, int aTick,
                                           const string& text);
      int       addTempo                  (int aTrack, int aTick,
                                           double aTempo);
      int       addTimeSignature          (int aTrack, int aTick,
                                           int top, int bottom,
	                                   int clocksPerClick = 24,
                                           int num32dsPerQuarter = 8);
      int       addCompoundTimeSignature  (int aTrack, int aTick,
                                           int top, int bottom,
	                                   int clocksPerClick = 36,
                                           int num32dsPerQuarter = 8);

      void      erase                     (void);
      void      clear                     (void);
      void      clear_no_deallocate       (void);
      MidiEvent&  getEvent                (int aTrack, int anIndex);

      MidiFile& operator=(MidiFile other);

      // static functions:
      static uchar    readByte                (istream& input);
      static ushort   readLittleEndian2Bytes  (istream& input);
      static ulong    readLittleEndian4Bytes  (istream& input);
      static ostream& writeLittleEndianUShort (ostream& out, ushort value);
      static ostream& writeBigEndianUShort    (ostream& out, ushort value);
      static ostream& writeLittleEndianShort  (ostream& out, short  value);
      static ostream& writeBigEndianShort     (ostream& out, short  value);
      static ostream& writeLittleEndianULong  (ostream& out, ulong  value);
      static ostream& writeBigEndianULong     (ostream& out, ulong  value);
      static ostream& writeLittleEndianLong   (ostream& out, long   value);
      static ostream& writeBigEndianLong      (ostream& out, long   value);
      static ostream& writeLittleEndianFloat  (ostream& out, float  value);
      static ostream& writeBigEndianFloat     (ostream& out, float  value);
      static ostream& writeLittleEndianDouble (ostream& out, double value);
      static ostream& writeBigEndianDouble    (ostream& out, double value);

   protected:
      vector<MidiEventList*> events;             // MIDI file events
      int              ticksPerQuarterNote;      // time base of file
      int              trackCount;               // # of tracks in file
      int              theTrackState;            // joined or split
      int              theTimeState;             // absolute or delta
      vector<char>     readFileName;             // read file name

      int               timemapvalid;
      vector<_TickTime> timemap;
      int               rwstatus;                // read/write success flag

   private:
      int        extractMidiData  (istream& inputfile, vector<uchar>& array,
                                       uchar& runningCommand);
      ulong      readVLValue      (istream& inputfile);
      ulong      unpackVLV        (uchar a = 0, uchar b = 0, uchar c = 0,
                                   uchar d = 0);
      void       writeVLValue     (long aValue, vector<uchar>& data);
      int        makeVLV          (uchar *buffer, int number);
      static int ticksearch       (const void* A, const void* B);
      static int secondsearch     (const void* A, const void* B);
      void       buildTimeMap     (void);
      int        linearTickInterpolationAtSecond  (double seconds);
      double     linearSecondInterpolationAtTick  (int ticktime);
};


int eventcompare(const void* a, const void* b);
ostream& operator<<(ostream& out, MidiFile& aMidiFile);

#endif /* _MIDIFILE_H_INCLUDED */



