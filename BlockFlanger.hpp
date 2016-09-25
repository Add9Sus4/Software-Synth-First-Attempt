//
//  BlockFlanger.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/20/16.
//
//

#ifndef BlockFlanger_hpp
#define BlockFlanger_hpp

#include <stdio.h>
#include "BlockEffect.hpp"
#include "Flanger.hpp"

class BlockFlanger : public BlockEffect {
    
public:
    BlockFlanger() {
        BlockFlanger(75, 0.5, 0.3, 0.85, WaveType::SINE);
    }
    BlockFlanger(int length, double modAmount, double frequency, double feedback, WaveType waveType) {
        flangerLeft = new Flanger(length, modAmount, frequency, feedback, waveType);
        flangerRight = new Flanger(length, modAmount, frequency, feedback, waveType);
    }
    double** process(double** outBlock, int blockSize);
private:
    Flanger* flangerLeft;
    Flanger* flangerRight;
};

#endif /* BlockFlanger_hpp */
