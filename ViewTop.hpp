//
//  ViewTop.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef ViewTop_hpp
#define ViewTop_hpp

#include <stdio.h>

#include "View.hpp"

class ViewTop : public View {
    
public:
    ViewTop(IPlugBase* pPlug, IRECT pR, VoiceManager* voiceManager, ViewManager* viewManager) : View(pPlug, pR, voiceManager, viewManager) {
        bgColor1red = 0.35;
        bgColor1green = 0.40;
        bgColor1blue = 0.45;
    }
    void drawStuff() {
    }
    
private:
};

#endif /* ViewTop_hpp */
