//
//  BlockEffect.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/1/16.
//
//

#include "BlockEffect.hpp"

void BlockEffect::process(double *inBlock, double *outBlock, int blockSize) {
    for (int i=0; i<blockSize; i++) {
        outBlock[i] = inBlock[i];
    }
}