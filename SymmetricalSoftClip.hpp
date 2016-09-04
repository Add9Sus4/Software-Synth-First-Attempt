//
//  SymmetricalSoftClip.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/31/16.
//
//

#ifndef SymmetricalSoftClip_hpp
#define SymmetricalSoftClip_hpp

#include <stdio.h>
#include <math.h>
#include "SampleEffect.hpp"

class SymmetricalSoftClip : public SampleEffect {
    
public:
    double process(double sample);
};

#endif /* SymmetricalSoftClip_hpp */
