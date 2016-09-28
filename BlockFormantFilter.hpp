//
//  BlockFormantFilter.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/20/16.
//
//

#ifndef BlockFormantFilter_hpp
#define BlockFormantFilter_hpp

#include <stdio.h>
#include "BlockEffect.hpp"
#include "FormantFilter.hpp"

class BlockFormantFilter : public BlockEffect {
public:
    BlockFormantFilter(Vowel vowel) {
        formantFilterLeft = new FormantFilter(vowel);
        formantFilterRight = new FormantFilter(vowel);
    }
    double** process(double** outBlock, int blockSize);
    
    void drawSlotView(IRECT rect) {
        
    }
private:
    
    FormantFilter* formantFilterLeft;
    FormantFilter* formantFilterRight;
    
};

#endif /* BlockFormantFilter_hpp */