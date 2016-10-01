//
//  ViewManager.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/27/16.
//
//

#ifndef ViewManager_hpp
#define ViewManager_hpp

#include <stdio.h>

#include "ViewBottom.hpp"
#include "ViewCenter.hpp"
#include "ViewLeft.hpp"
#include "ViewRight.hpp"
#include "ViewTop.hpp"
#include "VoiceManager.hpp"

class ViewManager {
public:
    ViewManager(IPlugBase* pPlug, VoiceManager* voiceManager) {
        
        // Create views
        viewTop = new ViewTop(pPlug, IRECT(kViewTopL, kViewTopT, kViewTopR, kViewTopB), voiceManager, this);
        viewBottom = new ViewBottom(pPlug, IRECT(kViewBottomL, kViewBottomT, kViewBottomR, kViewBottomB), voiceManager, this);
        viewLeft = new ViewLeft(pPlug, IRECT(kViewLeftL, kViewLeftT, kViewLeftR, kViewLeftB), voiceManager, this);
        viewRight = new ViewRight(pPlug, IRECT(kViewRightL, kViewRightT, kViewRightR, kViewRightB), voiceManager, this);
        viewCenter = new ViewCenter(pPlug, IRECT(kViewCenterL, kViewCenterT, kViewCenterR, kViewCenterB), voiceManager, this);
        
        // No icon initially selected
        selectedIcon = 0;
        iconOriginalX = 0;
        iconOriginalY = 0;
    }
    
    // Add the views to the screen
    void attachControls(IGraphics* pGraphics) {
        pGraphics->AttachControl(viewTop);
        pGraphics->AttachControl(viewLeft);
        pGraphics->AttachControl(viewRight);
        pGraphics->AttachControl(viewBottom);
        pGraphics->AttachControl(viewCenter);
    }
    
    void setSelectedIcon(IControl* selectedIcon) {
        this->selectedIcon = selectedIcon;
    }
    
    IControl* getSelectedIcon() { return selectedIcon; }
    
    void setIconOriginalPosition(int x, int y) {
        iconOriginalX = x;
        iconOriginalY = y;
    }
    
    void resetSelectedIconPosition() {
        if(selectedIcon != 0) {
            selectedIcon->move(iconOriginalX, iconOriginalY);
            setSelectedIcon(0);
        }
    }
    
    void moveSelectedIcon(int x, int y) {
        selectedIcon->move(x, y);
    }
    
    ViewBottom* viewBottom;
    ViewCenter* viewCenter;
    ViewLeft* viewLeft;
    ViewRight* viewRight;
    ViewTop* viewTop;
    
private:
    IControl* selectedIcon;
    int iconOriginalX; // Original x position of selected icon (used to revert on failed drag/drop)
    int iconOriginalY; // Original y position of selected icon (used to revert on failed drag/drop)
};

#endif /* ViewManager_hpp */