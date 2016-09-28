//
//  ViewBottom.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#include "ViewManager.hpp"
#include "ViewBottom.hpp"

void ViewBottom::OnMouseUp(int x, int y, IMouseMod *pMod) {
    mousePressed = false;
    if (scrollbar->isBeingDragged()) {
        scrollbar->setLastOffset(scrollbar->getOffset());
        scrollbar->setDragging(false);
    } else {
        IControl* icon = viewManager->getSelectedIcon();
        if (icon != 0) {
            if (mouseIsInSlotArea(x + calculateSlotOffset(),y) != -1) {
                int index = mouseIsInSlotArea(x + calculateSlotOffset(),y);
                std::cout << "You clicked slot " << index << std::endl;
                highlightSlot(index, SlotMode::ACTIVE);
                
                icon->move(-100, -100); // Move it so it is no longer in the drawing area and cannot be clicked on accidentally
                icon->Hide(true);
                std::cout << "Oscillator set to slot " << index << std::endl;
                
                voiceManager->getEffectByControlParamIdx(icon->ParamIdx());
                
                BlockEffect* currentEffect = voiceManager->getEffectByControlParamIdx(icon->ParamIdx());
//
                slots[index]->setCurrentEffect(currentEffect);
                
                voiceManager->addEffect(icon->ParamIdx());
                //                    plug->GetGUI()->GetControl(kOscillator1SlotDisplay)->move(x, y);
                //                    plug->GetGUI()->GetControl(kOscillator1SlotDisplay)->Hide(false);
                //                  voiceManager->addEffect(EffectID::kOscillatorGroup1);
                viewManager->setSelectedIcon(0);
            } else {
                viewManager->resetSelectedIconPosition();
            }
        }
        
    }
}