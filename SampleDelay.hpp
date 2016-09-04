//
//  SampleDelay.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#ifndef SampleDelay_hpp
#define SampleDelay_hpp

#include <stdio.h>
#include <iostream>
#include "SampleEffect.hpp"

class SampleDelay : public SampleEffect {
private:
    int length;
    double *data;
    double feedback;
public:
    SampleDelay(int length, double feedback) {
        this->length = length;
        // Make sure feedback is between 0.99 and 0
        if (feedback > 0.99 || feedback < 0) {
            std::cout << "Feedback was set to " << feedback << ". Feedback must be between 0 and 0.99." << std::endl;
            this->feedback = 0;
        }
        this->feedback = feedback;
        data = new double[length];
        for (int i=0; i<length; i++) {
            data[i] = 0.0f;
        }
    };
    double process(double sample);
    void setLength(double length) { this->length = length; }
};


#endif /* SampleDelay_hpp */
