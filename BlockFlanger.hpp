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
    BlockFlanger(int length, double modAmount, double frequency, double feedback, WaveType waveType) {
        flangerLeft = new Flanger(length, modAmount, frequency, feedback, waveType);
        flangerRight = new Flanger(length, modAmount, frequency, feedback, waveType);
    }
    double** process(double** outBlock, int blockSize);
    void drawSlotView(IRECT rect) {
        
    }
private:
    Flanger* flangerLeft;
    Flanger* flangerRight;
};

#endif /* BlockFlanger_hpp */
