//
//  AudioWindow.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/19/16.
//
//

#ifndef AudioWindow_hpp
#define AudioWindow_hpp

#define HANNING		0
#define HAMMING 	1
#define BLACKMAN	2
#define RECTANGULAR	3


#include <math.h>
#include <stdio.h>

class AudioWindow {
public:
    static double* blackman(unsigned long length);
    static double* hamming(unsigned long length);
    static double* hanning(unsigned long length); // Sums to 1 with an overlap of 50%
    static double* rectangular(unsigned long length); // always 1
};

#endif /* AudioWindow_hpp */
