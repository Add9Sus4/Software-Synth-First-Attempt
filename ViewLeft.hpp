//
//  ViewLeft.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef ViewLeft_hpp
#define ViewLeft_hpp

#include <math.h>
#include <stdio.h>
#include <vector>

#include "View.hpp"

class ViewLeft : public View {
public:
    ViewLeft(IPlugBase* pPlug, IRECT pR, VoiceManager* voiceManager, ViewManager* viewManager) : View(pPlug, pR, voiceManager, viewManager) {
        bgColor1red = 0.35;
        bgColor1green = 0.45;
        bgColor1blue = 0.40;
    }
    void drawStuff() {

    }
    
    void OnMouseDrag(int x, int y, int dX, int dY, IMouseMod *pMod);
    
    void OnMouseDown(int x, int y, IMouseMod *pMod);
    
    void OnMouseUp(int x, int y, IMouseMod *pMod);

private:
};

#endif /* ViewLeft_hpp */
