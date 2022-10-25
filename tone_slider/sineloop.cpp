#include "sineloop.h"
#include "SineWave.h"
#include "RtWvOut.h"

#include <thread>

using namespace stk;

SineLoop::SineLoop()
{
    Stk::setSampleRate( SAMPLE_RATE );
    Stk::showWarnings( true );

    // Define and open the default realtime output device for one-channel playback
    dac = new RtWvOut(1, Stk::sampleRate(), 0, RT_BUFFER_SIZE, 2 );
    sine.setFrequency(sine_frequency);
}

SineLoop::~SineLoop()
{
    delete dac;
}


void SineLoop::start_audio(void)
{
    if (!this->continue_looping)
    {
        this->continue_looping = true;
        thread_object = std::thread( [this] { __audio_worker(); } );
    }
}

void SineLoop::stop_audio(void)
{
    if (this->continue_looping)
    {
        this->continue_looping = false;
        thread_object.join();
    }
}

void SineLoop::set_frequency(int frequency)
{
    sine_frequency = frequency;
    sine.setFrequency(sine_frequency);
}

void SineLoop::__audio_worker(void)
{
    while(this->continue_looping)
    {
        try
        {
            dac->tick(sine.tick());
            if (counter++ % 441 == 0)
                std::cout << sine_frequency << std::endl;
        }
        catch(StkError&)
        {
            std::cout << "stk error inside thread" << std::endl;
        }
    }

    dac->stop();
}
