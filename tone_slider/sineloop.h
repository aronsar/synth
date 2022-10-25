#ifndef SINELOOP_H
#define SINELOOP_H

#include "SineWave.h"
#include "RtWvOut.h"
#include <thread>

using namespace stk;

class SineLoop
{
//static const int AUDIO_BUFFER_SIZE = 512;
static const int SAMPLE_RATE = 44100;

public:
    SineLoop();
    ~SineLoop();
    void start_audio(void);
    void stop_audio(void);
    void set_frequency(int frequency);

private:
    void __audio_worker(void);
    bool continue_looping = false;
    int sine_frequency = 340;
    RtWvOut *dac = 0;
    SineWave sine;
    std::thread thread_object;
    int counter = 0;
};

#endif // SINELOOP_H
