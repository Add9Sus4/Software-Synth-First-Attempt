//
//  BlockFlanger.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/20/16.
//
//

#include "BlockFlanger.hpp"

double** BlockFlanger::process(double **outBlock, int blockSize ) {
    for (int i=0; i<blockSize; i++) {
        outBlock[LEFT][i] = flangerLeft->process(outBlock[LEFT][i]);
        outBlock[RIGHT][i] = flangerRight->process(outBlock[RIGHT][i]);
    }
    return outBlock;
}