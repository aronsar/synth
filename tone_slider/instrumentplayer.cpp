#include "instrumentplayer.h"
#include "BeeThree.h"

using namespace stk;

// This tick() function handles sample computation only.  It will be
// called automatically when the system needs a new buffer of audio
// samples.

//int tick_counter = 0;

int tick( void *_outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
    Instrmnt *instrument = (Instrmnt *) userData;
    StkFloat *outputBuffer = (StkFloat *) _outputBuffer;

    for ( unsigned int i=0; i<nBufferFrames; i++ ) {
//        if (tick_counter++ % 44100 == 0)
//        {
//            std::cout << "tick" << std::endl;
//        }
        *outputBuffer++ = instrument->tick();
    }
    return 0;
}


InstrumentPlayer::InstrumentPlayer()
{
    Stk::setSampleRate(44100);
    Stk::setRawwavePath( "../../stk/rawwaves/" );

    //RtAudio dac;

    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 1;
    RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;
    instrument = new BeeThree();
    this->frequency = 440;
    //instrument->setFrequency(this->frequency);

    try
    {
        dac.openStream( &parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)instrument );
    }
    catch ( RtAudioError& error )
    {
        error.printMessage();
    }
}

void InstrumentPlayer::set_voicer(Voicer *_voicer)
{
//    if (_voicer)
//        this->voicer = _voicer;
//    else
//        this->voicer = new Voicer();
}

void InstrumentPlayer::start_audio(void)
{
    try
    {
        instrument->noteOn(220.0, 0.5);
        dac.startStream();
    }
    catch ( RtAudioError &error )
    {
        error.printMessage();
    }
}

void InstrumentPlayer::stop_audio(void)
{
    try
    {
        instrument->noteOff(0.5);
        dac.stopStream();
    }
      catch ( RtAudioError &error )
    {
        error.printMessage();
    }
}

void InstrumentPlayer::set_frequency(int frequency)
{
    this->frequency = frequency;
    instrument->setFrequency(frequency);
}

void InstrumentPlayer::set_bpm(int bpm)
{

}


InstrumentPlayer::~InstrumentPlayer()
{
    delete instrument;
}
