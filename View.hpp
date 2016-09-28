//
//  View.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef View_hpp
#define View_hpp

#include "IPlug_include_in_plug_hdr.h"
#include "IControl.h"
#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <stdlib.h>

#include "VoiceManager.hpp"

class ViewManager;

class View : public IControl {
private:
    
    /* Think of a context as an object that holds all of OpenGL; when a context is destroyed, OpenGL is destroyed. */
    // The CGLContextObj type is the fundamental data type for an OpenGL Context on Mac.
    CGLContextObj mGLContext;
    WDL_TypedBuf<unsigned char> mData;
    
protected:
    int height;
    int width;
    float bgColor1red;
    float bgColor1green;
    float bgColor1blue;
    
    int mouseLastPressX;
    int mouseLastPressY;
    
    bool mousePressed;
    
    IRECT currentRect;
    
    IPlugBase* plug;
    ViewManager* viewManager;
    VoiceManager* voiceManager;
    
public:
    View(IPlugBase* pPlug, IRECT pR, VoiceManager* voiceManager, ViewManager* viewManager)
    :	IControl(pPlug, pR, -1)
    {
        this->viewManager = viewManager;
        this->voiceManager = voiceManager;
        this->plug = pPlug;
        bgColor1red = 0.321;
        bgColor1green = 0.4;
        bgColor1blue = 0.478;
        
        width = pR.W();
        height = pR.H();
        currentRect = pR;
        createContext();
        mData.Resize(mRECT.W() * mRECT.H() * 4);
        srand(time(NULL));
        
        mouseLastPressX = width/2;
        mouseLastPressY = height/2;
        mousePressed = false;
    }
    
    ~View()
    {
        destroyContext();
    }
    
    virtual void drawStuff() = 0;
    
    long setContext()
    {
        /* Set the current context. In order for any OpenGL commands to work, a context must be current; all OpenGL commands affect the state of whichever context is current. */
        if(CGLSetCurrentContext(mGLContext))
        {
            DBGMSG("Could not make context current.");
            return 1;
        }
        return 0;
    }
    
   
    void OnMouseDown(int x, int y, IMouseMod *pMod) {
        mouseLastPressX = x - currentRect.L;
        mouseLastPressY = y - currentRect.T;
        mousePressed = true;
    }
    
    void OnMouseUp(int x, int y, IMouseMod *pMod) {
        mousePressed = false;
    }
    
    void restoreContext()
    {
        CGLSetCurrentContext(NULL);
    }
    
    long createContext()
    {
        const GLubyte *glstring;
        
        GLint npix;
        CGLPixelFormatObj PixelFormat;
        
        const CGLPixelFormatAttribute attributes[] =
        {
            //kCGLPFAOffScreen,
            //      kCGLPFAColorSize, (CGLPixelFormatAttribute)8,
            //      kCGLPFADepthSize, (CGLPixelFormatAttribute)16,
            kCGLPFAAccelerated, (CGLPixelFormatAttribute)0
        };
        
        // Create context if none exists
        
        CGLChoosePixelFormat(attributes, &PixelFormat, &npix);
        
        if (PixelFormat == NULL)
        {
            DBGMSG("Could not get pixel format.");
            return 1;
        }
        
        CGLCreateContext(PixelFormat, NULL, &mGLContext);
        
        if (mGLContext == NULL)
        {
            DBGMSG("Could not create rendering context.");
            return 1;
        }
        
        // Set the current context
        
        if(setContext())
            return 1;
        
        // Check OpenGL functionality:
        glstring = glGetString(GL_EXTENSIONS);
        
        if(!gluCheckExtension((const GLubyte *)"GL_EXT_framebuffer_object", glstring))
        {
            DBGMSG("The GL_EXT_framebuffer_object extension is not supported on this system.");
            return 1;
        }
        
        restoreContext();
        
        return 0;
    }
    
    
    void destroyContext()
    {
        if (mGLContext != NULL)
            CGLDestroyContext(mGLContext);
    }
    
    bool Draw(IGraphics* pGraphics)
    {
        
        GLuint framebuffer, renderbuffer;
        
        const int width = mRECT.W();
        const int height = mRECT.H();
        
        // Set context
        if (setContext())
            return false;
        
        // Set up a FBO with one renderbuffer attachment
        glGenFramebuffersEXT(1, &framebuffer);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
        glGenRenderbuffersEXT(1, &renderbuffer);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderbuffer);
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA8, width, height);
        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, renderbuffer);
        
        // Setup OpenGL for 2D drawing with the correct blending
        glViewport(0, 0, width, height);
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        glOrtho (0, width, height, 0, 0, 1);
        glMatrixMode (GL_MODELVIEW);
        
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glEnable( GL_POINT_SMOOTH );
        glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
        glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
        glDisable(GL_TEXTURE_2D);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
        //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        
        //        glClearColor(0., 0., 0., 0.);
        glClearColor(BACKGROUND_COLOR_1_R, BACKGROUND_COLOR_1_G, BACKGROUND_COLOR_1_B, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glLineWidth(1.1);
        glPointSize(2.6);
        
        // ----------------- DRAW ----------------- ALL DRAWING HAPPENS BELOW THIS LINE
        
        drawBackground();
        drawStuff();
        
        // ----------------- END DRAW ----------------- ALL DRAWING HAPPENS ABOVE THIS LINE
        
        
        glFlush();
        glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, mData.Get());
        
        // Delete the renderbuffer attachment
        glDeleteRenderbuffersEXT(1, &renderbuffer);
        
        // Make the window the target
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        glDeleteFramebuffersEXT(1, &framebuffer);
        
        restoreContext();
        
        unsigned char* val = mData.Get();
        
        for(int v=0; v<height; v++)
        {
            for(int h=0; h<width; h++)
            {
                LICE_pixel pix = LICE_RGBA(*val, *(val + 1), *(val + 2), *(val + 3));
                LICE_PutPixel(pGraphics->GetDrawBitmap(), mRECT.L + h, mRECT.B - v, pix, 1., LICE_BLIT_MODE_COPY | LICE_BLIT_USE_ALPHA);
                val += 4;
            }
        }
        
        return true;
    }
    
    bool IsDirty()
    {
        return true;
    }
    
    void drawBackground() {
        glBegin(GL_QUADS);
        //red color
        glColor3f(bgColor1red, bgColor1green, bgColor1blue);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        //blue color
        glColor3f(bgColor1red/3.0, bgColor1green/3.0, bgColor1blue/3.0);
        glVertex2f(width, height);
        glVertex2f(0, height);
        glEnd();
    }
};

#endif /* View_hpp */
