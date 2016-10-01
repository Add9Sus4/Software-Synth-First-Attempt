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
#include "resource.h"

#define LEFT    0
#define RIGHT   1

#define TOP_SECTION_HEIGHT      80
#define MID_SECTION_HEIGHT      400
#define BOTTOM_SECTION_HEIGHT   160
#define LEFT_SECTION_WIDTH      240
#define CENTER_SECTION_WIDTH    480
#define RIGHT_SECTION_WIDTH     240

#define WIDTH_OF_VIEW_TOP       GUI_WIDTH
#define HEIGHT_OF_VIEW_TOP      TOP_SECTION_HEIGHT
#define WIDTH_OF_VIEW_LEFT      LEFT_SECTION_WIDTH
#define HEIGHT_OF_VIEW_LEFT     MID_SECTION_HEIGHT
#define WIDTH_OF_VIEW_CENTER    CENTER_SECTION_WIDTH
#define HEIGHT_OF_VIEW_CENTER   MID_SECTION_HEIGHT
#define WIDTH_OF_VIEW_RIGHT     RIGHT_SECTION_WIDTH
#define HEIGHT_OF_VIEW_RIGHT    MID_SECTION_HEIGHT
#define WIDTH_OF_VIEW_BOTTOM    GUI_WIDTH
#define HEIGHT_OF_VIEW_BOTTOM   BOTTOM_SECTION_HEIGHT

enum ViewLayout {
    kViewTopL = 0,
    kViewTopT = 0,
    kViewTopR = WIDTH_OF_VIEW_TOP,
    kViewTopB = HEIGHT_OF_VIEW_TOP,
    
    kViewLeftL = 0,
    kViewLeftT = HEIGHT_OF_VIEW_TOP,
    kViewLeftR = WIDTH_OF_VIEW_LEFT,
    kViewLeftB = HEIGHT_OF_VIEW_TOP + HEIGHT_OF_VIEW_LEFT,
    
    kViewCenterL = WIDTH_OF_VIEW_LEFT,
    kViewCenterT = HEIGHT_OF_VIEW_TOP,
    kViewCenterR = WIDTH_OF_VIEW_LEFT + WIDTH_OF_VIEW_CENTER,
    kViewCenterB = HEIGHT_OF_VIEW_TOP + HEIGHT_OF_VIEW_CENTER,
    
    kViewRightL = WIDTH_OF_VIEW_LEFT + WIDTH_OF_VIEW_CENTER,
    kViewRightT = HEIGHT_OF_VIEW_TOP,
    kViewRightR = WIDTH_OF_VIEW_LEFT + WIDTH_OF_VIEW_CENTER + WIDTH_OF_VIEW_RIGHT,
    kViewRightB = HEIGHT_OF_VIEW_TOP + HEIGHT_OF_VIEW_RIGHT,
    
    kViewBottomL = 0,
    kViewBottomT = HEIGHT_OF_VIEW_TOP + HEIGHT_OF_VIEW_LEFT,
    kViewBottomR = WIDTH_OF_VIEW_BOTTOM,
    kViewBottomB = HEIGHT_OF_VIEW_TOP + HEIGHT_OF_VIEW_RIGHT + HEIGHT_OF_VIEW_BOTTOM
};

class BlockEffect {
public:
    BlockEffect() {
        active = false;
    }
    
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
    
    void setActive(bool active) { this->active = active; }
    bool isActive() { return active; }
    
protected:
    std::vector<BlockEffect*> inputs;
private:
    // Is this effect currently active?
    bool active;
    
    int effectId;
};

#endif /* BlockEffect_hpp */
