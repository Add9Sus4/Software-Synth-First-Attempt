//
//  BlockEffect.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/1/16.
//
//

#ifndef BlockEffect_hpp
#define BlockEffect_hpp

#include <stdio.h>

class BlockEffect {
    
public:
    virtual void process(double *inBlock, double *outBlock, int blockSize);
};

#endif /* BlockEffect_hpp */
