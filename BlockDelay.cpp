//
//  BlockDelay.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "BlockDelay.hpp"
double** BlockDelay::process(double**outBlock, int blockSize) {
    
    // Store incoming audio block in buffer at appropriate delay time
    for (int i=0; i<blockSize; i++) {
        dataLeft[length + i] = outBlock[LEFT][i];
        dataRight[length + i] = outBlock[RIGHT][i];
    }
    // Put beginning of buffer into outgoing audio block
    for (int i=0; i<blockSize; i++) {
        outBlock[LEFT][i] = dataLeft[i];
        outBlock[RIGHT][i] = dataRight[i];
    }
    // Put beginning of buffer into end of buffer, scaled by feedback
    for (int i=0; i<blockSize; i++) {
        dataLeft[length + i] += dataLeft[i]*feedback;
        dataRight[length + i] += dataRight[i]*feedback;
    }
    // Shift the buffer by blockSize samples
    for (int i=0; i<length; i++) {
        dataLeft[i] = dataLeft[i+blockSize];
        dataRight[i] = dataRight[i+blockSize];
    }
    return outBlock;
}