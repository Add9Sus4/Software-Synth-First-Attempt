//
//  ViewBottom.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef ViewBottom_hpp
#define ViewBottom_hpp

#define SLOT_PADDING_LEFT   5
#define SLOT_PADDING_RIGHT  5
#define SLOT_PADDING_TOP    10
#define SLOT_PADDING_BOTTOM 30
#define SLOT_WIDTH          160
#define SLOT_HEIGHT         160

#include <iostream>
#include <stdio.h>
#include <vector>

#include "SOIL.h"
#include "View.hpp"

typedef enum SlotMode {
    EMPTY,
    HIGHLIGHTED,
    HOVER,
    ACTIVE
} SlotMode;

class ViewBottom : public View {
public:
    ViewBottom(IPlugBase* pPlug, IRECT pR, VoiceManager* voiceManager, ViewManager* viewManager) : View(pPlug, pR, voiceManager, viewManager) {
        
        scrollbar = new Scrollbar();
        scrollbar->setLength(currentRect.R - SLOT_PADDING_RIGHT - SLOT_PADDING_LEFT - 10);
        
        bgColor1red = 0.40;
        bgColor1green = 0.35;
        bgColor1blue = 0.45;
        
        for (int i=0; i<16; i++) {
            Slot* slot = new Slot(i, pR);
            slot->r = 0.2;
            slot->g = 0.0;
            slot->b = 0.0;
            slots.push_back(slot);
        }

        ratioOfWindowWidthToTotalSlotWidth = (double)940/(double)(SLOT_WIDTH*slots.size());
        
        
    }

    void drawStuff() {
        
        glColor3f(1.0, 0.0, 0.0);
        
        ratioOfWindowWidthToTotalSlotWidth = (double)940/(double)(SLOT_WIDTH*slots.size());
        
        double slotOffset = calculateSlotOffset();
        // Slots
        for (int i=0; i<slots.size(); i++) {
            glBegin(GL_QUADS);
            glColor3f(slots[i]->r, slots[i]->g, slots[i]->b);
            glVertex2f(slots[i]->L - slotOffset, slots[i]->T);
            glVertex2f(slots[i]->R - slotOffset, slots[i]->T);
            glVertex2f(slots[i]->R - slotOffset, slots[i]->B);
            glVertex2i(slots[i]->L - slotOffset, slots[i]->B);
            glEnd();
        }
        
        // Scroll bar area
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
        glVertex2i(SLOT_PADDING_LEFT, currentRect.H() - 5); // Left bottom
        glVertex2i(currentRect.R - SLOT_PADDING_RIGHT, currentRect.H() - 5); // Right bottom
        glVertex2i(currentRect.R - SLOT_PADDING_RIGHT, currentRect.H() - 25); // Right top
        glVertex2i(SLOT_PADDING_LEFT, currentRect.H() - 25); // Left top
        glEnd();
        
        // Scroll bar
        int rightBound = currentRect.R - 10;
        int leftBound = 10;
        int maxWidth = rightBound - leftBound;
        int length = (int)((double)maxWidth*ratioOfWindowWidthToTotalSlotWidth);
        scrollbar->setLength(length);
        scrollbar->setRightBound(length + leftBound);
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_QUADS);
        glVertex2i(leftBound + scrollbar->getOffset(), currentRect.H() - 10); // Left bottom
        glVertex2i(scrollbar->getRightBound() + scrollbar->getOffset(), currentRect.H() - 10); // Right bottom
        glVertex2i(scrollbar->getRightBound() + scrollbar->getOffset(), currentRect.H() - 20); // Right top
        glVertex2i(leftBound + scrollbar->getOffset(), currentRect.H() - 20); // Left top
        glEnd();
        
        glColor3f(0.8, 0.7, 0.6);
        // SOIL
        for (int i=0; i<16; i++) {
            slots[i]->drawSlotView();
        }
    }
    
    void highlightNextSlot(SlotMode slotMode) {
        slots.back()->slotMode = slotMode;
        switch (slotMode) {
            case EMPTY:
                slots.back()->r = 0.2;
                break;
            case HIGHLIGHTED:
                slots.back()->r = 0.4;
                break;
            case HOVER:
                slots.back()->r = 0.6;
                break;
            case ACTIVE:
                slots.back()->r = 0.8;
                break;
            default:
                break;
        }
    }
    
    void highlightSlot(int index, SlotMode slotMode) {
        slots[index]->slotMode = slotMode;
        switch (slotMode) {
            case EMPTY:
                slots[index]->r = 0.2;
                break;
            case HIGHLIGHTED:
                slots[index]->r = 0.4;
                break;
            case HOVER:
                slots[index]->r = 0.6;
                break;
            case ACTIVE:
                slots[index]->r = 0.6;
                break;
            default:
                break;
        }
    }
    
    SlotMode getSlotMode(int index) {
        return slots[index]->slotMode;
    }
    
    double calculateSlotOffset() {
        return (double)scrollbar->getOffset()/ratioOfWindowWidthToTotalSlotWidth;
    }
    
    void OnMouseOut() {
        for (int i=0; i<slots.size(); i++) {
            if (getSlotMode(i) != SlotMode::ACTIVE) {
                highlightSlot(i, SlotMode::EMPTY);
            }
        }
    }
    
    
    void OnMouseOver(int x, int y, IMouseMod *pMod) {
        int index = mouseIsInSlotArea(x + calculateSlotOffset(),y);
        
        if (index != -1 && getSlotMode(index) != ACTIVE && !scrollbar->isBeingDragged()) {
            highlightSlot(index, SlotMode::HOVER);
            for (int i=0; i<slots.size(); i++) {
                if (getSlotMode(i) != ACTIVE && i != index) {
                    highlightSlot(i, SlotMode::EMPTY);
                }
            }
            
//            std::cout << "You clicked slot " << index << std::endl;
//            if (plug->GetParam(23)->Value() == 1) {
//                highlightSlot(index, SlotMode::ACTIVE);
//                plug->GetParam(23)->Set(0);
//                plug->GetGUI()->GetControl(5)->Hide(true);
//                std::cout << "Oscillator set to slot " << index << std::endl;
//            }
        } else {
            for (int i=0; i<slots.size(); i++) {
                if (getSlotMode(i) != ACTIVE) {
                    highlightSlot(i, SlotMode::EMPTY);
                }
            }
        }
    }
    
    void OnMouseDrag(int x, int y, int dX, int dY, IMouseMod *pMod) {
        dX = x - mouseLastPressX;
        dY = y - mouseLastPressY;
        
        if (scrollbar->isBeingDragged()) {

            scrollbar->setOffset(scrollbar->getLastOffset() + dX);
            if (scrollbar->getOffset() < 0) {
                scrollbar->setOffset(0);
            }
            if (scrollbar->getOffset() > currentRect.W() - 20 - scrollbar->getLength()) {
                scrollbar->setOffset(currentRect.W() - 20 - scrollbar->getLength());
            }
        } else {
        
            int index = mouseIsInSlotArea(x + calculateSlotOffset(),y);
            if (index != -1) {
            highlightSlot(index, SlotMode::HOVER);
            } else {
                for (int i=0; i<slots.size(); i++) {
                    if (getSlotMode(i) != ACTIVE) {
                    highlightSlot(i, SlotMode::EMPTY);
                    }
                }
            }
        }
        
    }
    
    void OnMouseDown(int x, int y, IMouseMod *pMod) {
        mouseLastPressX = x - currentRect.L;
        mouseLastPressY = y - currentRect.T;
        if (mouseLastPressX > 10 && mouseLastPressX < 950 && mouseLastPressY > 140 && mouseLastPressY < 150 && ratioOfWindowWidthToTotalSlotWidth <= 1.0) {
            scrollbar->setDragging(true);
        }
    }
    
    void OnMouseUp(int x, int y, IMouseMod *pMod);
    
    int mouseIsInSlotArea(int x, int y) {
        for (int i=0; i<slots.size(); i++) {
            if (x > slots[i]->L && x < slots[i]->R && y - currentRect.T > slots[i]->T && y - currentRect.T < slots[i]->B) {
                return i;
            }
        }
        return -1;
    }
    
private:
    class Scrollbar {
    public:
        Scrollbar() {
            dragging = false;
            offset = 0;
            lastOffset = 0;
        }
        void setLength(int length) { this->length = length; }
        int getLength() { return length; }
        void setRightBound(int rightBound) {this->rightBound = rightBound; }
        int getRightBound() { return rightBound; }
        int getOffset() { return offset; }
        bool isBeingDragged() { return dragging; }
        void setDragging(bool dragging) { this->dragging = dragging; }
        void setOffset(int offset) { this->offset = offset; }
        int getLastOffset() { return lastOffset; }
        void setLastOffset(int offset) { lastOffset = offset; }
    private:
        int length;
        int rightBound;
        int leftBound;
        bool dragging;
        int offset;
        int lastOffset;
    };
    
    Scrollbar* scrollbar;
    double ratioOfWindowWidthToTotalSlotWidth;
    
    class Slot {
    public:
        Slot(int index, IRECT pR) {
            this->index = index;
            L = SLOT_WIDTH*index + SLOT_PADDING_LEFT;
            T = SLOT_PADDING_TOP;
            R = SLOT_WIDTH*(index + 1) - SLOT_PADDING_RIGHT;
            B = pR.H() - SLOT_PADDING_BOTTOM;
            currentEffect = 0;
        }
        void drawSlotView() {
            if (currentEffect != 0) {
                currentEffect->drawSlotView(IRECT(L,T,R,B));
            }
        }
        void setCurrentEffect(BlockEffect* effect) { currentEffect = effect; }
        SlotMode slotMode;
        int L;
        int T;
        int R;
        int B;
        float r;
        float g;
        float b;
    private:
        BlockEffect* currentEffect;
        int index;
        
    };
    std::vector<Slot*> slots;
};

#endif /* ViewBottom_hpp */
