//
//  BiquadFilter.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/20/16.
//
//

#ifndef BiquadFilter_hpp
#define BiquadFilter_hpp

#include <stdio.h>
#include "BlockEffect.hpp"
#include "Filter.hpp"
#include "LFO.hpp"
#include "Parameter.hpp"

typedef enum FilterParam {
    FREQUENCY
} FilterParam;

class BiquadFilter : public BlockEffect {
public:
    BiquadFilter(int type, double dbGain, double freq,
                 double srate, double bandwidth) {
        
        frequency = new Parameter(freq);

        filterLeft = new Filter(type, dbGain, freq, srate, bandwidth);
        filterRight = new Filter(type, dbGain, freq, srate, bandwidth);
    }
    double** process(double** outBlock, int blockSize);
    Parameter* getParam(FilterParam filterParam) {
        switch (filterParam) {
            case FREQUENCY:
                return frequency;
                break;
                
            default:
                break;
        }
    }
private:
    Parameter* frequency;
    Filter* filterLeft;
    Filter* filterRight;
    LFO* lfo;
};

#endif /* BiquadFilter_hpp */
