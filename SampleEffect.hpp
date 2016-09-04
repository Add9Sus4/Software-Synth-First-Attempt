//
//  SampleEffect.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/30/16.
//
//  A SampleEffect is any effect that processes samples one at a time. SampleEffects are
//  grouped together in a ProcessingChain.

#ifndef SampleEffect_hpp
#define SampleEffect_hpp

#include <stdio.h>

class SampleEffect {
private:
    
public:
    virtual double process(double sample);
};

#endif /* SampleEffect_hpp */
