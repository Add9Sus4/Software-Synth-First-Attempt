//
//  BlockDelay.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#ifndef BlockDelay_hpp
#define BlockDelay_hpp

#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include "BlockEffect.hpp"

class BlockDelay : public BlockEffect {
private:
    int length;
    double* dataLeft;
    double* dataRight;
    int blockSize;
    double feedback;
    
public:
    BlockDelay(int length, int blockSize, double feedback) {
        if (length < blockSize) {
            std::cout << "Length was " << length << ". It must be equal to or greater than the block size. Set length to " << blockSize << "." << std::endl;
            length = blockSize;
        }
        this->length = length;
        this->blockSize = blockSize;
        // Make sure feedback is between 0.99 and 0
        if (feedback > 0.99 || feedback < 0) {
            std::cout << "Feedback was set to " << feedback << ". Feedback must be between 0 and 0.99." << std::endl;
            this->feedback = 0;
        }
        this->feedback = feedback;
        dataLeft = new double[length + blockSize]; // Need to have at least one block past the delay length
        dataRight = new double[length + blockSize]; // Need to have at least one block past the delay length
        for (int i=0; i<length + blockSize; i++) {
            dataLeft[i] = 0.0f;
            dataRight[i] = 0.0f;
        }
    }
    
    void drawSlotView(IRECT rect) {
        
    }
    
    double** process(double** outBlock, int blockSize);
};

#endif /* BlockDelay_hpp */
