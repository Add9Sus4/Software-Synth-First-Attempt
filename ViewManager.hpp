//
//  ViewManager.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/27/16.
//
//

#ifndef ViewManager_hpp
#define ViewManager_hpp

#define TOP_SECTION_HEIGHT      80
#define MID_SECTION_HEIGHT      400
#define BOTTOM_SECTION_HEIGHT   160
#define LEFT_SECTION_WIDTH      240
#define CENTER_SECTION_WIDTH    480
#define RIGHT_SECTION_WIDTH     240

#define WIDTH_OF_VIEW_TOP       GUI_WIDTH
#define HEIGHT_OF_VIEW_TOP      TOP_SECTION_HEIGHT
#define WIDTH_OF_VIEW_LEFT      LEFT_SECTION_WIDTH
#define HEIGHT_OF_VIEW_LEFT     MID_SECTION_HEIGHT
#define WIDTH_OF_VIEW_CENTER    CENTER_SECTION_WIDTH
#define HEIGHT_OF_VIEW_CENTER   MID_SECTION_HEIGHT
#define WIDTH_OF_VIEW_RIGHT     RIGHT_SECTION_WIDTH
#define HEIGHT_OF_VIEW_RIGHT    MID_SECTION_HEIGHT
#define WIDTH_OF_VIEW_BOTTOM    GUI_WIDTH
#define HEIGHT_OF_VIEW_BOTTOM   BOTTOM_SECTION_HEIGHT

#include <stdio.h>

#include "ViewBottom.hpp"
#include "ViewCenter.hpp"
#include "ViewLeft.hpp"
#include "ViewRight.hpp"
#include "ViewTop.hpp"
#include "VoiceManager.hpp"

enum ViewLayout {
    kViewTopL = 0,
    kViewTopT = 0,
    kViewTopR = WIDTH_OF_VIEW_TOP,
    kViewTopB = HEIGHT_OF_VIEW_TOP,
    
    kViewLeftL = 0,
    kViewLeftT = HEIGHT_OF_VIEW_TOP,
    kViewLeftR = WIDTH_OF_VIEW_LEFT,
    kViewLeftB = HEIGHT_OF_VIEW_TOP + HEIGHT_OF_VIEW_LEFT,
    
    kViewCenterL = WIDTH_OF_VIEW_LEFT,
    kViewCenterT = HEIGHT_OF_VIEW_TOP,
    kViewCenterR = WIDTH_OF_VIEW_LEFT + WIDTH_OF_VIEW_CENTER,
    kViewCenterB = HEIGHT_OF_VIEW_TOP + HEIGHT_OF_VIEW_CENTER,
    
    kViewRightL = WIDTH_OF_VIEW_LEFT + WIDTH_OF_VIEW_CENTER,
    kViewRightT = HEIGHT_OF_VIEW_TOP,
    kViewRightR = WIDTH_OF_VIEW_LEFT + WIDTH_OF_VIEW_CENTER + WIDTH_OF_VIEW_RIGHT,
    kViewRightB = HEIGHT_OF_VIEW_TOP + HEIGHT_OF_VIEW_RIGHT,
    
    kViewBottomL = 0,
    kViewBottomT = HEIGHT_OF_VIEW_TOP + HEIGHT_OF_VIEW_LEFT,
    kViewBottomR = WIDTH_OF_VIEW_BOTTOM,
    kViewBottomB = HEIGHT_OF_VIEW_TOP + HEIGHT_OF_VIEW_RIGHT + HEIGHT_OF_VIEW_BOTTOM
};

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