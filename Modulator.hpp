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
    void setId(int modulatorId) { this->modulatorId = modulatorId; }
    int getId() { return modulatorId; }
    virtual double modulate(double value) = 0;
private:
    int modulatorId;
};

#endif /* Modulator_hpp */
