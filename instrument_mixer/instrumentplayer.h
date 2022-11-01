#ifndef INSTRUMENTPLAYER_H
#define INSTRUMENTPLAYER_H

#include "RtAudio.h"
#include "Instrmnt.h"
#include <QString>
#include <thread>

using namespace stk;

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
    void set_instrument(int idx);


private:
    RtAudio dac;
    Instrmnt *instruments[9];
    Instrmnt *instrument;
    int frequency;
    float volume;
    int bpm;
    std::thread audio_worker_thread;
    bool audio_playing;

    void __audio_worker();
};

#endif // INSTRUMENTPLAYER_H
