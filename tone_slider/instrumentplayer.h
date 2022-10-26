#ifndef INSTRUMENTPLAYER_H
#define INSTRUMENTPLAYER_H

#include <unordered_map>
#include "Voicer.h"
#include "BeeThree.h"
#include "RtAudio.h"
#include "Saxofony.h"
#include "Instrmnt.h"
#include <QString>

using namespace stk;

std::unordered_map<QString, *Instrmnt> available_instruments =
{
    {"Saxofony", Saxofony}
}

struct TickData {
  Instrmnt *instrument;
  StkFloat frequency;
  StkFloat scaler;
  long counter;
  bool done;

  // Default constructor.
  TickData()
    : instrument(0), scaler(1.0), counter(0), done( false ) {}
};

class InstrumentPlayer
{
public:
    InstrumentPlayer();
    ~InstrumentPlayer();
    void set_voicer(Voicer *_voicer);
    void start_audio();
    void stop_audio();
    void set_frequency(int frequency);
    void set_bpm(int bpm);


private:
    TickData data;
    RtAudio dac;
    Voicer *voicer;
};

#endif // INSTRUMENTPLAYER_H
