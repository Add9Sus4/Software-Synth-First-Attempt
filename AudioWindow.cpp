//
//  AudioWindow.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/19/16.
//
//

#include "AudioWindow.hpp"


double* AudioWindow::blackman(unsigned long length)
{
    double* window = new double[length];
    unsigned long i;
    double pi, phase = 0, delta;
    
    pi = 4.*atan(1.0);
    delta = 2 * pi / (double) length;
    
    for( i = 0; i < length; i++ )
    {
        window[i] = (float)(0.42 - .5*cos(phase) + .08*cos(2*phase));
        phase += delta;
    }
    return window;
}

double* AudioWindow::hamming(unsigned long length)
{
    
    double* window = new double[length];
    unsigned long i;
    double pi, phase = 0, delta;
    
    pi = 4.*atan(1.0);
    delta = 2 * pi / (double) length;
    
    for( i = 0; i < length; i++ )
    {
        window[i] = (float)(0.54 - .46*cos(phase));
        phase += delta;
    }
    return window;
}

double* AudioWindow::hanning(unsigned long length)
{
    double* window = new double[length];
    unsigned long i;
    double pi, phase = 0, delta;
    
    pi = 4.*atan(1.0);
    delta = 2 * pi / (double) length;
    
    for( i = 0; i < length; i++ )
    {
        window[i] = (float)(0.5 * (1.0 - cos(phase)));
        phase += delta;
    }
    return window;
}

double* AudioWindow::rectangular(unsigned long length)
{
    double* window = new double[length];
    for (int i=0; i<length; i++) {
        window[i] = 1.0;
    }
    return window;
}
