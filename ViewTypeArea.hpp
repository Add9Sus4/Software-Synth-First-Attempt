//
//  ViewTypeArea.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef ViewTypeArea_hpp
#define ViewTypeArea_hpp

#include <stdio.h>

#include "View.hpp"

class ViewTypeArea : public View {
    
public:
    ViewTypeArea(IPlugBase* pPlug, IRECT pR) : View(pPlug, pR) {
        bgColor1red = 0.35;
        bgColor1green = 0.40;
        bgColor1blue = 0.45;
    }
    void drawStuff() {
    }
    
private:
};

#endif /* ViewTypeArea_hpp */
