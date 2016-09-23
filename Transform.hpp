//
//  Transform.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/19/16.
//
//

#ifndef Transform_hpp
#define Transform_hpp

#define cmp_abs(x) ( sqrt( (x).re * (x).re + (x).im * (x).im ) )
#define FFT_FORWARD 1
#define FFT_INVERSE 0
#define PI	(4.*atan( 1. ))
#define TWOPI	(8.*atan( 1. ))

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>

class Transform {
public:
    static void rfft(double* x, long N, unsigned int forward);
    static std::vector<double> rfft(std::vector<double> audio, unsigned int forward);
private:
    static void cfft(double* x, long NC, unsigned int forward);
    static void bit_reverse(double* x, long N);
};

#endif /* Transform_hpp */
