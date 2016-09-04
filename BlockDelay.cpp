//
//  BlockDelay.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "BlockDelay.hpp"
void BlockDelay::process(double *inBlock, double *outBlock, int blockSize) {
    // Store incoming audio block in buffer at appropriate delay time
    for (int i=0; i<blockSize; i++) {
        data[length + i] = inBlock[i];
    }
    // Put beginning of buffer into outgoing audio block
    for (int i=0; i<blockSize; i++) {
        outBlock[i] = data[i] + inBlock[i];
    }
    // Put beginning of buffer into end of buffer, but at 1/2 volume
    for (int i=0; i<blockSize; i++) {
        data[length + i] += data[i]*feedback;
    }
    // Shift the buffer by blockSize samples
    for (int i=0; i<length; i++) {
        data[i] = data[i+blockSize];
    }
}