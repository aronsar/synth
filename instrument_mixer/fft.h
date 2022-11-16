#ifndef FFT_H
#define FFT_H

#include "Stk.h"
using namespace stk;

class FFT
{
public:
    FFT(int _input_buffer_length, int _output_buffer_length);
    void calculate();

    int input_buffer_length;
    int output_buffer_length;

    StkFloat *input_buffer;
    StkFloat *output_buffer;
};

#endif // FFT_H
