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
    void setId(int id) { this->id = id; }
    int getId() { return id; }
    virtual double modulate(double value) = 0;
private:
    int id;
};

#endif /* Modulator_hpp */
