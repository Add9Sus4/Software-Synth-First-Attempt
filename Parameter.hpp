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
        bufferSize = 10;
        buffer = new double[bufferSize];
        for (int i=0; i<bufferSize; i++) {
            buffer[i] = value;
        }
    };
    Parameter(double value, int bufferSize) {
        this->value = value;
        this->bufferSize = bufferSize;
        buffer = new double[bufferSize];
        for (int i=0; i<bufferSize; i++) {
            buffer[i] = value;
        }
    }
    void setValue(double value) { this->value = value; }
    double getValue() {
        double sum = 0.0;
        for (int i=0; i<bufferSize; i++) {
            sum += buffer[i];
        }
        
        // shift buffer
        for (int i=0; i<bufferSize-1; i++) {
            buffer[i] = buffer[i + 1];
        }
        buffer[bufferSize - 1] = value;
        
        return sum/(double)bufferSize;
    }
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
    double* buffer;
    int bufferSize;
    std::vector<Modulator* > modulators;
};

#endif /* Parameter_hpp */
