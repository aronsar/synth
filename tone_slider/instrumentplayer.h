#ifndef INSTRUMENTPLAYER_H
#define INSTRUMENTPLAYER_H

#include <unordered_map>
#include "Voicer.h"
#include "RtAudio.h"
//#include "Saxofony.h"
#include "Instrmnt.h"
#include <QString>
#include <thread>

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
    void start_audio();
    void stop_audio();
    void set_frequency(int frequency);
    void set_volume(float volume);
    void set_bpm(int bpm);
    void play_duration_note();


private:
    RtAudio dac;
    Instrmnt *instrument;
    int frequency;
    float volume;
    int bpm;
    std::thread audio_worker_thread;
    bool audio_playing;

    void __audio_worker();
};

#endif // INSTRUMENTPLAYER_H
