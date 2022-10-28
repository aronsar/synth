#ifndef INSTRUMENTPLAYER_H
#define INSTRUMENTPLAYER_H

#include <unordered_map>
#include "Voicer.h"
#include "RtAudio.h"
//#include "Saxofony.h"
#include "Instrmnt.h"
#include <QString>

using namespace stk;

//std::unordered_map<QString, *Instrmnt> available_instruments =
//{
//    {"Saxofony", Saxofony}
//}

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
    RtAudio dac;
    Instrmnt *instrument;
    int frequency;
};

#endif // INSTRUMENTPLAYER_H
