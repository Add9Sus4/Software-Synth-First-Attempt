//
//  Parameter.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/22/16.
//
//

#ifndef Parameter_hpp
#define Parameter_hpp

#include <stdio.h>
#include <vector>

#include "Modulator.hpp"

class Parameter {
public:
    Parameter(double value) {
        this->value = value;
    };
    void setValue(double value) { this->value = value; }
    double getValue() { return value; }
    void addModulator(Modulator* modulator) { modulators.push_back(modulator); }
    double getModulatedValue() {
        double modulatedValue = value;
        for (std::vector<int>::size_type i = 0; i != modulators.size(); i++) {
            modulatedValue = modulators[i]->modulate(modulatedValue);
        }
        return modulatedValue;
    }
    
private:
    double value;
    std::vector<Modulator* > modulators;
};

#endif /* Parameter_hpp */
