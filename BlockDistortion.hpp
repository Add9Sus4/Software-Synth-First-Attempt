//
//  BlockDistortion.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/20/16.
//
//

#ifndef BlockDistortion_hpp
#define BlockDistortion_hpp

#include <stdio.h>
#include "BlockEffect.hpp"
#include "Distortion.hpp"
#include "SymmetricalSoftClip.hpp"

typedef enum DistortionType {
    DISTORTION,
    SYMMETRICAL_SOFT_CLIP
} DistortionType;

class BlockDistortion : public BlockEffect {
public:
    BlockDistortion(DistortionType distortionType) {
        this->distortionType = distortionType;
        distortionLeft = new Distortion(100.0);
        distortionRight = new Distortion(100.0);
        sscLeft = new SymmetricalSoftClip();
        sscRight = new SymmetricalSoftClip();
    }
    double** process(double** outBlock, int blockSize);
private:
    Distortion* distortionLeft;
    Distortion* distortionRight;
    SymmetricalSoftClip* sscLeft;
    SymmetricalSoftClip* sscRight;
    DistortionType distortionType;
};

#endif /* BlockDistortion_hpp */
