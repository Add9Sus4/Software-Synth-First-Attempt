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
    BlockFormantFilter() {
        formantFilterLeft = new FormantFilter(Vowel::O);
        formantFilterRight = new FormantFilter(Vowel::O);
    }
    BlockFormantFilter(Vowel vowel) {
        formantFilterLeft = new FormantFilter(vowel);
        formantFilterRight = new FormantFilter(vowel);
    }
    double** process(double** outBlock, int blockSize);
private:
    
    FormantFilter* formantFilterLeft;
    FormantFilter* formantFilterRight;
    
};

#endif /* BlockFormantFilter_hpp */