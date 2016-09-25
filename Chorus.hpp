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
#define CHORUS_MAX_FEEDBACK 0.5

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
    double feedback;
    
public:
    Chorus() {
        Chorus(512, 6, 800, 0.3, 0.1);
    }
    // Create new chorus object
    Chorus(int blockSize, int numDelays, int centerLength, double spread, double feedback) {
        
        if (feedback > (double)CHORUS_MAX_FEEDBACK) {
            this->feedback = (double)CHORUS_MAX_FEEDBACK;
        } else {
            this->feedback = feedback;
        }

        // Store value of blockSize for later use
        this->blockSize = blockSize;
        
        
        // Restrict number of delays to use in chorus
        if (numDelays > 10 || numDelays < 4) {
            std::cout << "Invalid value for 'numDelays' (" << numDelays << "). This must be a value between " << CHORUS_MIN_DELAYS << " and " << CHORUS_MAX_DELAYS << "." << std::endl;
            std::cout << "'numDelays' has been set to " << CHORUS_MIN_DELAYS << "." << std::endl;
            numDelays = CHORUS_MIN_DELAYS;
        }
        
        // If spread is out of range
        if (spread < 0.0 || spread > 1.0) {
            spread = 1.0;
        }
        
        int range = 0;
        // If center length is out of the range
        if (centerLength > CHORUS_MAX_LENGTH-10 || centerLength < CHORUS_MAX_LENGTH+10){
            centerLength = CHORUS_MIN_LENGTH + (CHORUS_MAX_LENGTH - CHORUS_MIN_LENGTH)/2; // Set to center frequency of range
        }
        // Is center length closer to min or max
        if (CHORUS_MAX_LENGTH - centerLength > centerLength - CHORUS_MIN_LENGTH) {
            range = centerLength - CHORUS_MIN_LENGTH;
        } else {
            range = CHORUS_MAX_LENGTH - centerLength;
        }
        
        range = (int)((double)range*spread);
        
        srand (time(NULL));
        
        // Now we have to create numDelays delays between centerLength - range and centerLength + range
        for (int i=0; i<numDelays; i++) {
            int length = rand() % (range*2) + (centerLength - range);
            BlockDelay *delay = new BlockDelay(length, blockSize, this->feedback);
            delays.push_back(delay);
        }
    }
    
    // Process a block of audio
    double** process(double** outBlock, int blockSize) {
        for(std::vector<int>::size_type i = 0; i != delays.size(); i++) {
            outBlock = delays[i]->process(outBlock, blockSize);
        }
        return outBlock;
    }
};

#endif /* Chorus_hpp */
