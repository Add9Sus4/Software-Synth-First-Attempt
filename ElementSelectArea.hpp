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

#include "ElementChainArea.hpp"
#include "View.hpp"

class ElementSelectArea : public View {
public:
    ElementSelectArea(IPlugBase* pPlug, IRECT pR, VoiceManager* voiceManager, ElementChainArea* chainArea) : View(pPlug, pR, voiceManager) {
        bgColor1red = 0.35;
        bgColor1green = 0.45;
        bgColor1blue = 0.40;
        
        this->chainArea = chainArea;
    }
    void drawStuff() {
        
    }
    
    void OnMouseDrag(int x, int y, int dX, int dY, IMouseMod *pMod) {
        std::cout << "Dragging" << std::endl;
        plug->GetGUI()->GetControl(6)->move(x, y);
    }
    
    void OnMouseDown(int x, int y, IMouseMod *pMod) {
        std::cout << "Mouse clicked" << std::endl;
        dragging = true;
    }
    
    void OnMouseUp(int x, int y, IMouseMod *pMod) {
        dragging = false;
        chainArea->OnMouseUp(x, y, pMod);
    }
private:
    ElementChainArea* chainArea;
    bool dragging;
};

#endif /* ElementSelectArea_hpp */
