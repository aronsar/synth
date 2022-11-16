#include "fft.h"

FFT::FFT(int _input_buffer_length, int _output_buffer_length) :
        input_buffer_length(_input_buffer_length),
        output_buffer_length(_output_buffer_length),
        input_buffer(new StkFloat[input_buffer_length]),
        output_buffer(new StkFloat[output_buffer_length])
{
}

void FFT::calculate()
{
    for (int i = 0; i < output_buffer_length; i++)
    {
        output_buffer[i] = input_buffer[i];
    }
}
