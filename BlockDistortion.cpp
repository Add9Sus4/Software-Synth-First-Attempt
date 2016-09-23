//
//  BlockDistortion.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/20/16.
//
//

#include "BlockDistortion.hpp"

double** BlockDistortion::process(double** outBlock, int blockSize) {
    
    if (distortionType == DistortionType::DISTORTION) {
        for (int i=0; i<blockSize; i++ ) {
            outBlock[LEFT][i] = distortionLeft->process(outBlock[LEFT][i]);
            outBlock[RIGHT][i] = distortionRight->process(outBlock[RIGHT][i]);
        }
    } else if (distortionType == DistortionType::SYMMETRICAL_SOFT_CLIP) {
        for (int i=0; i<blockSize; i++ ) {
            outBlock[LEFT][i] = sscLeft->process(outBlock[LEFT][i]);
            outBlock[RIGHT][i] = sscRight->process(outBlock[RIGHT][i]);
        }
    }
    return outBlock;
}