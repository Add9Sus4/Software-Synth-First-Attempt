//
//  ViewLeft.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#include "ViewManager.hpp"

#include "ViewLeft.hpp"

void ViewLeft::drawStuff() {
    int offset = 0;
    for (int i=0; i<kNumIcons; i++) {
        IControl* control = plug->GetGUI()->GetControl(i+6);
        if (control == viewManager->getSelectedIcon() || control->IsHidden()) {
            offset++;
        } else {
            int x = ((i - offset) % 4)*60 + 20;
            int y = HEIGHT_OF_VIEW_TOP + 15 + floor((i-offset)/4)*50;
            control->move(x,y);
        }
    }
}

void ViewLeft::OnMouseDrag(int x, int y, int dX, int dY, IMouseMod *pMod) {
    if (viewManager->getSelectedIcon() != 0) {
        viewManager->moveSelectedIcon(x, y);
        viewManager->viewBottom->OnMouseDrag(x, y, dX, dY, pMod);
    }
}

void ViewLeft::OnMouseDown(int x, int y, IMouseMod *pMod) {
    
    // Check if mouse was clicked in the vicinity of an icon
    int numControls = plug->GetGUI()->GetNControls();
    for (int i=0; i<numControls; i++) {
        IControl* currentControl = plug->GetGUI()->GetControl(i);
        IRECT* controlRect = currentControl->GetRECT();
        viewManager->setIconOriginalPosition(controlRect->L, controlRect->T);
        if (controlRect->L - x < 25 && controlRect->L - x > 0 && y - controlRect->T < 40 && y - controlRect->T > 0) {
            std::cout << "Selected control: " << i << std::endl;
            viewManager->setSelectedIcon(currentControl);
            std::cout<< "Control param index: " << currentControl->ParamIdx() << std::endl;
            return;
        }
    }
}

void ViewLeft::OnMouseUp(int x, int y, IMouseMod *pMod) {
    //        chainArea->OnMouseUp(x, y, pMod);
    if (viewManager->getSelectedIcon() != 0) {
        viewManager->viewBottom->OnMouseUp(x, y, pMod);
        viewManager->resetSelectedIconPosition();
        //            chainArea->setSelectedControl(0, original_x, original_y);
    }
}