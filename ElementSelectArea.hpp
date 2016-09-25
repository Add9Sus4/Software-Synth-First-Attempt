//
//  ElementSelectArea.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef ElementSelectArea_hpp
#define ElementSelectArea_hpp

#include <stdio.h>
#include <vector>

#include "View.hpp"

class ElementSelectArea : public View {
public:
    ElementSelectArea(IPlugBase* pPlug, IRECT pR) : View(pPlug, pR) {
        bgColor1red = 0.35;
        bgColor1green = 0.45;
        bgColor1blue = 0.40;
    }
    void drawStuff() {
        
    }
private:

};

#endif /* ElementSelectArea_hpp */
