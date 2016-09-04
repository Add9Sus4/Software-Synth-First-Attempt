//
//  Chorus.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/31/16.
//
//  Ideally, this should be implemented in block form to reduce computational cost

#ifndef Chorus_hpp
#define Chorus_hpp

#define CHORUS_MAX_LENGTH   1102
#define CHORUS_MIN_LENGTH   441
#define CHORUS_MAX_DELAYS   10
#define CHORUS_MIN_DELAYS   4

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include "BlockEffect.hpp"
#include "BlockDelay.hpp"

class Chorus : public BlockEffect {
private:
    // This vector stores a variable number of BlockDelay objects
    std::vector<BlockDelay *> delays;
    
    // The size of the audio processing block
    int blockSize;
    
public:
    // Create new chorus object
    Chorus(int blockSize, int numDelays, int centerLength, double spread, double feedback);
    
    // Process a block of audio
    void process(double *inBlock, double *outBlock, int blockSize);
};

#endif /* Chorus_hpp */
