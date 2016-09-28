//
//  ViewRight.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef ViewRight_hpp
#define ViewRight_hpp

#include <stdio.h>

#include "View.hpp"

class ViewRight : public View {
public:
    ViewRight(IPlugBase* pPlug, IRECT pR, VoiceManager* voiceManager, ViewManager* viewManager) : View(pPlug, pR, voiceManager, viewManager) {
        bgColor1red = 0.40;
        bgColor1green = 0.45;
        bgColor1blue = 0.35;
    }
    void drawStuff() {
        
    }
    void setColor(float r, float g, float b) {
        bgColor1red = r;
        bgColor1green = g;
        bgColor1blue = b;
    }
};

#endif /* ViewRight_hpp */
