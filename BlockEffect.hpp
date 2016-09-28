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
#include <vector>

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include "SOIL.h"

#include "IControl.h"
#include "Modulator.hpp"
#include "Parameter.hpp"

#define LEFT    0
#define RIGHT   1

class BlockEffect {
public:
    
    /*
     The process function for a BlockEffect must first call process() on all of its
     inputs. This will return a double* which can then be manipulated according to the
     specific effect and then returned by this function. Each BlockEffect can have multiple
     inputs, but only one output. Sending the output of a BlockEffect to multiple locations
     should be done by using a Splitter effect, which is a container into which several
     parallel blockEffects can be placed. The input is sent to each BlockEffect, and the
     outputs of these effects are later recombined.
     */
    virtual double** process(double** outBlock, int blockSize) = 0;
    
    virtual void drawSlotView(IRECT rect) = 0;
    
    double** getSamples(double** outBlock, int blockSize) {
        // Get the input data, if applicable
        outBlock = getInputData(outBlock, blockSize);
        // Then process the data
        outBlock = process(outBlock, blockSize);
        return outBlock;
    }
    
    void addInput(BlockEffect* input) {
        inputs.push_back(input);
    }
    
    double** getInputData(double** outBlock, int blockSize) {
        // Add inputs, if applicable. Otherwise, fill outBlock with zeros
        if (inputs.size() > 0) {
            for (int i=0; i<inputs.size(); i++) {
                outBlock = inputs[i]->getSamples(outBlock, blockSize);
            }
        } else {
            for (int i=0; i<blockSize; i++) {
                outBlock[LEFT][i] = 0.0;
                outBlock[RIGHT][i] = 0.0;
            }
        }
        return outBlock;
    }
    
    void setId(int effectId) { this->effectId = effectId; }
    int getId() { return this->effectId; }
    
protected:
    std::vector<BlockEffect*> inputs;
private:
    int effectId;
};

#endif /* BlockEffect_hpp */
