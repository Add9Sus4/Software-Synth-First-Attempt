//
//  Modulator.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/22/16.
//
//

#ifndef Modulator_hpp
#define Modulator_hpp

#include <stdio.h>

class Modulator {
public:
    virtual double modulate(double value) = 0;
};

#endif /* Modulator_hpp */
