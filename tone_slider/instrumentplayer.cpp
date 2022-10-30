#include "instrumentplayer.h"
#include "BeeThree.h"

using namespace stk;

// This tick() function handles sample computation only.  It will be
// called automatically when the system needs a new buffer of audio
// samples.
int tick( void *_outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
    Instrmnt *instrument = (Instrmnt *) userData;
    StkFloat *outputBuffer = (StkFloat *) _outputBuffer;

    for ( unsigned int i=0; i<nBufferFrames; i++ ) {
        *outputBuffer++ = instrument->tick();
    }
    return 0;
}


InstrumentPlayer::InstrumentPlayer()
{
    Stk::setSampleRate(44100);
    Stk::setRawwavePath( "../../stk/rawwaves/" );

    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 1;
    RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;
    instrument = new BeeThree();


    this->frequency = 440;
    this->volume = 1.0;
    this->audio_playing = false;
    this->bpm = 60;

    //instrument->

    dac.openStream( &parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)instrument );
    dac.startStream();
}

void InstrumentPlayer::start_audio(void)
{
    this->audio_playing = true;
    this->audio_worker_thread = std::thread( [this] { __audio_worker(); } );
}

void InstrumentPlayer::stop_audio(void)
{
    this->audio_playing = false;
    this->audio_worker_thread.join();
}

void InstrumentPlayer::__audio_worker(void)
{
    while (this->audio_playing)
    {
        play_duration_note();
    }
}

void InstrumentPlayer::set_frequency(int frequency)
{
    this->frequency = frequency;
    instrument->setFrequency(frequency);
}

void InstrumentPlayer::set_volume(float volume)
{
    this->volume = volume;
}

void InstrumentPlayer::set_bpm(int bpm)
{
    this->bpm = bpm;
}

void InstrumentPlayer::play_duration_note()
{
    int duration_ms = 1000 * 60 / this->bpm - 100; // integer division
    instrument->noteOn(this->frequency, this->volume);
    Stk::sleep(duration_ms);
    instrument->noteOff(1.0);
    Stk::sleep(100);
}


InstrumentPlayer::~InstrumentPlayer()
{
    dac.stopStream();
    delete instrument;
}
