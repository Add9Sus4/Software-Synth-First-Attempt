//
//  BlockFormantFilter.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/20/16.
//
//

#include "BlockFormantFilter.hpp"

double** BlockFormantFilter::process(double** outBlock, int blockSize) {
    for (int i=0; i<blockSize; i++) {
        outBlock[LEFT][i] = formantFilterLeft->process(outBlock[LEFT][i]);
        outBlock[RIGHT][i] = formantFilterRight->process(outBlock[RIGHT][i]);
    }
    return outBlock;
}