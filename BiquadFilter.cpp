//
//  BiquadFilter.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/20/16.
//
//

#include "BiquadFilter.hpp"

double** BiquadFilter::process(double** outBlock, int blockSize) {
    for (int i=0; i<blockSize; i++) {
        double currentFreq = frequency->getModulatedValue();
        filterLeft->changeCutoff(currentFreq);
        filterRight->changeCutoff(currentFreq);
        outBlock[LEFT][i] = filterLeft->processSample(outBlock[LEFT][i]);
        outBlock[RIGHT][i] = filterRight->processSample(outBlock[RIGHT][i]);
    }
//    std::cout << outBlock[LEFT][blockSize/2] << std::endl;
    return outBlock;
}