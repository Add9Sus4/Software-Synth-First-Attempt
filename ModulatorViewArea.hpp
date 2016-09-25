//
//  ModulatorViewArea.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef ModulatorViewArea_hpp
#define ModulatorViewArea_hpp

#include <stdio.h>

#include "View.hpp"

class ModulatorViewArea : public View {
public:
    ModulatorViewArea(IPlugBase* pPlug, IRECT pR) : View(pPlug, pR) {
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

#endif /* ModulatorViewArea_hpp */
