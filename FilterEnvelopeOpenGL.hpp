////
////  FilterEnvelopeOpenGL.hpp
////  AudioComponents
////
////  Created by Aaron Dawson on 9/12/16.
////
////
//
//#ifndef FilterEnvelopeOpenGL_hpp
//#define FilterEnvelopeOpenGL_hpp
//
//#include "IPlug_include_in_plug_hdr.h"
//#include "IControl.h"
//#include <stdio.h>
//#include <OpenGL/OpenGL.h>
//#include <OpenGL/glu.h>
//#include <stdlib.h>
//#include "time.h"
//#include "WaveForm.hpp"
//
//class FilterEnvelopeOpenGL : public IControl {
//private:
//    
//    /* Think of a context as an object that holds all of OpenGL; when a context is destroyed, OpenGL is destroyed. */
//    // The CGLContextObj type is the fundamental data type for an OpenGL Context on Mac.
//    CGLContextObj mGLContext;
//    WDL_TypedBuf<unsigned char> mData;
//    int height;
//    int width;
//    int currentPosition;
//    int leftBound;
//    int rightBound;
//    float mRotateTri, mRotateQuad;
//    IRECT currentRect;
//    int counter;
//    
//public:
//    FilterEnvelopeOpenGL(IPlugBase* pPlug, IRECT pR)
//    :	IControl(pPlug, pR, -1)
//    {
//        //        currentfilter = filter;
//        currentRect = pR;
//        leftBound = 0;
//        mRotateTri = mRotateQuad = 0.f;
//        createContext();
//        mData.Resize(mRECT.W() * mRECT.H() * 4);
//        counter = 0;
//        srand(time(NULL));
//    }
//    
//    ~FilterEnvelopeOpenGL()
//    {
//        destroyContext();
//    }
//    
//    int getStartingSample() {
//        return leftBound;
//    }
//    
//    int getEndingSample() {
//        return rightBound;
//    }
//    
//    void updatePosition(int position) {
//        currentPosition = position;
//    }
//    
//    long setContext()
//    {
//        /* Set the current context. In order for any OpenGL commands to work, a context must be current; all OpenGL commands affect the state of whichever context is current. */
//        if(CGLSetCurrentContext(mGLContext))
//        {
//            DBGMSG("Could not make context current.");
//            return 1;
//        }
//        
//        return 0;
//    }
//    
//    
//    
//    void restoreContext()
//    {
//        CGLSetCurrentContext(NULL);
//    }
//    
//    long createContext()
//    {
//        const GLubyte *glstring;
//        
//        GLint npix;
//        CGLPixelFormatObj PixelFormat;
//        
//        const CGLPixelFormatAttribute attributes[] =
//        {
//            //kCGLPFAOffScreen,
//            //      kCGLPFAColorSize, (CGLPixelFormatAttribute)8,
//            //      kCGLPFADepthSize, (CGLPixelFormatAttribute)16,
//            kCGLPFAAccelerated, (CGLPixelFormatAttribute)0
//        };
//        
//        // Create context if none exists
//        
//        CGLChoosePixelFormat(attributes, &PixelFormat, &npix);
//        
//        if (PixelFormat == NULL)
//        {
//            DBGMSG("Could not get pixel format.");
//            return 1;
//        }
//        
//        CGLCreateContext(PixelFormat, NULL, &mGLContext);
//        
//        if (mGLContext == NULL)
//        {
//            DBGMSG("Could not create rendering context.");
//            return 1;
//        }
//        
//        // Set the current context
//        
//        if(setContext())
//            return 1;
//        
//        // Check OpenGL functionality:
//        glstring = glGetString(GL_EXTENSIONS);
//        
//        if(!gluCheckExtension((const GLubyte *)"GL_EXT_framebuffer_object", glstring))
//        {
//            DBGMSG("The GL_EXT_framebuffer_object extension is not supported on this system.");
//            return 1;
//        }
//        
//        restoreContext();
//        
//        return 0;
//    }
//    
//    
//    void destroyContext()
//    {
//        if (mGLContext != NULL)
//            CGLDestroyContext(mGLContext);
//    }
//    
//    bool Draw(IGraphics* pGraphics)
//    {
//        
//        GLuint framebuffer, renderbuffer;
//        
//        const int width = mRECT.W();
//        const int height = mRECT.H();
//        
//        // Set context
//        if (setContext())
//            return false;
//        
//        // Set up a FBO with one renderbuffer attachment
//        glGenFramebuffersEXT(1, &framebuffer);
//        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
//        glGenRenderbuffersEXT(1, &renderbuffer);
//        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderbuffer);
//        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA8, width, height);
//        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, renderbuffer);
//        
//        //        glViewport(0,0,width,height);						// Reset The Current Viewport
//        //
//        //        glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
//        //        glLoadIdentity();									// Reset The Projection Matrix
//        
//        // Calculate The Aspect Ratio Of The Window
//        //        gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
//        //
//        //        glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
//        //        glLoadIdentity();									// Reset The Modelview Matrix
//        //        glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
//        //        glClearColor(0.0f, 0.0f, 0.0f, 1.f);				// Black Background
//        //        glClearDepth(1.0f);									// Depth Buffer Setup
//        //        glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
//        //        glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
//        //        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
//        //        glEnable(GL_CULL_FACE);
//        //        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
//        //        glLoadIdentity();									// Reset The Current Modelview Matrix
//        
//        //        glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
//        //        glRotatef(mRotateTri,0.0f,1.0f,0.0f);						// Rotate The Triangle On The Y axis ( NEW )
//        //        glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
//        //        glColor3f(1.0f,0.0f,0.0f);						// Red
//        //        glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Front)
//        //        glColor3f(0.0f,1.0f,0.0f);						// Green
//        //        glVertex3f(-1.0f,-1.0f, 1.0f);					// Left Of Triangle (Front)
//        //        glColor3f(0.0f,0.0f,1.0f);						// Blue
//        //        glVertex3f( 1.0f,-1.0f, 1.0f);					// Right Of Triangle (Front)
//        //        glColor3f(1.0f,0.0f,0.0f);						// Red
//        //        glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Right)
//        //        glColor3f(0.0f,0.0f,1.0f);						// Blue
//        //        glVertex3f( 1.0f,-1.0f, 1.0f);					// Left Of Triangle (Right)
//        //        glColor3f(0.0f,1.0f,0.0f);						// Green
//        //        glVertex3f( 1.0f,-1.0f, -1.0f);					// Right Of Triangle (Right)
//        //        glColor3f(1.0f,0.0f,0.0f);						// Red
//        //        glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Back)
//        //        glColor3f(0.0f,1.0f,0.0f);						// Green
//        //        glVertex3f( 1.0f,-1.0f, -1.0f);					// Left Of Triangle (Back)
//        //        glColor3f(0.0f,0.0f,1.0f);						// Blue
//        //        glVertex3f(-1.0f,-1.0f, -1.0f);					// Right Of Triangle (Back)
//        //        glColor3f(1.0f,0.0f,0.0f);						// Red
//        //        glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Left)
//        //        glColor3f(0.0f,0.0f,1.0f);						// Blue
//        //        glVertex3f(-1.0f,-1.0f,-1.0f);					// Left Of Triangle (Left)
//        //        glColor3f(0.0f,1.0f,0.0f);						// Green
//        //        glVertex3f(-1.0f,-1.0f, 1.0f);					// Right Of Triangle (Left)
//        //        glEnd();											// Done Drawing The Pyramid
//        //
//        //        glLoadIdentity();									// Reset The Current Modelview Matrix
//        //        glTranslatef(1.5f,0.0f,-7.0f);						// Move Right 1.5 Units And Into The Screen 7.0
//        //        glRotatef(mRotateQuad,1.0f,1.0f,1.0f);					// Rotate The Quad On The X axis ( NEW )
//        //        glBegin(GL_QUADS);									// Draw A Quad
//        //        glColor3f(0.0f,1.0f,0.0f);						// Set The Color To Green
//        //        glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Right Of The Quad (Top)
//        //        glVertex3f(-1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Top)
//        //        glVertex3f(-1.0f, 1.0f, 1.0f);					// Bottom Left Of The Quad (Top)
//        //        glVertex3f( 1.0f, 1.0f, 1.0f);					// Bottom Right Of The Quad (Top)
//        //        glColor3f(1.0f,0.5f,0.0f);						// Set The Color To Orange
//        //        glVertex3f( 1.0f,-1.0f, 1.0f);					// Top Right Of The Quad (Bottom)
//        //        glVertex3f(-1.0f,-1.0f, 1.0f);					// Top Left Of The Quad (Bottom)
//        //        glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Left Of The Quad (Bottom)
//        //        glVertex3f( 1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Bottom)
//        //        glColor3f(1.0f,0.0f,0.0f);						// Set The Color To Red
//        //        glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Front)
//        //        glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Front)
//        //        glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Front)
//        //        glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Front)
//        //        glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Yellow
//        //        glVertex3f( 1.0f,-1.0f,-1.0f);					// Top Right Of The Quad (Back)
//        //        glVertex3f(-1.0f,-1.0f,-1.0f);					// Top Left Of The Quad (Back)
//        //        glVertex3f(-1.0f, 1.0f,-1.0f);					// Bottom Left Of The Quad (Back)
//        //        glVertex3f( 1.0f, 1.0f,-1.0f);					// Bottom Right Of The Quad (Back)
//        //        glColor3f(0.0f,0.0f,1.0f);						// Set The Color To Blue
//        //        glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Left)
//        //        glVertex3f(-1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Left)
//        //        glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Left Of The Quad (Left)
//        //        glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Left)
//        //        glColor3f(1.0f,0.0f,1.0f);						// Set The Color To Violet
//        //        glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Right Of The Quad (Right)
//        //        glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Right)
//        //        glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Right)
//        //        glVertex3f( 1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Right)
//        //        glEnd();											// Done Drawing The Quad
//        //
//        //        mRotateTri+=1.5f;											// Increase The Rotation Variable For The Triangle ( NEW )
//        //        mRotateQuad-=1.65f;										// Decrease The Rotation Variable For The Quad ( NEW )
//        
//        // Setup OpenGL for 2D drawing with the correct blending
//        glViewport(0, 0, width, height);
//        glMatrixMode (GL_PROJECTION);
//        glLoadIdentity ();
//        glOrtho (0, width, height, 0, 0, 1);
//        glMatrixMode (GL_MODELVIEW);
//        
//        glDepthMask(GL_FALSE);
//        glEnable(GL_BLEND);
//        glEnable(GL_LINE_SMOOTH);
//        glEnable( GL_POINT_SMOOTH );
//        glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
//        glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
//        glDisable(GL_TEXTURE_2D);
//        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
//        //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//        
//        //        glClearColor(0., 0., 0., 0.);
//        glClearColor(BACKGROUND_COLOR_1_R, BACKGROUND_COLOR_1_G, BACKGROUND_COLOR_1_B, 1.0);
//        glClear(GL_COLOR_BUFFER_BIT);
//        
//        glLineWidth(1.1);
//        glPointSize(2.6);
//        
//        // ----------------- DRAW ----------------- ALL DRAWING HAPPENS BELOW THIS LINE
//        
//        // Calculate the total length of the envelope
//        int totalEnvLength = symphony->getFilterEnvLength();
//        
//        // Calculate the percent length of each stage of the envelope
//        double percentAttack = (double)symphony->getFilterEnvAttack()/(double)totalEnvLength;
//        double percentDecay = (double)symphony->getFilterEnvDecay()/(double)totalEnvLength;
//        double percentRelease = (double)symphony->getFilterEnvRelease()/(double)totalEnvLength;
//        
//        // Calculate scaled length of each envelope stage, relative to the window width
//        int scaledAttackLength = percentAttack*width*0.9;
//        int scaledDecayLength = percentDecay*width*0.9;
//        int scaledReleaseLength = percentRelease*width*0.9;
//        
//        // Get sustain of envelope
//        double sustain = symphony->getFilterEnvSustain();
//        
//        int currentIndex = 0;
//        
//        int envBottom = height*0.9;
//        
//        int x_indices[] = {0.0 + width*0.05,
//            scaledAttackLength + width*0.05,
//            currentIndex + scaledAttackLength + scaledDecayLength + width*0.05,
//            currentIndex + scaledAttackLength + scaledDecayLength + scaledReleaseLength + width*0.05};
//        int y_indices[] = {envBottom + height*0.05,
//            height*0.05,
//            (1.0-sustain)*envBottom + height*0.05,
//            envBottom + height*0.05};
//        
//        // Draw envelope
//        glBegin(GL_POLYGON);
//        glColor4f(0.75, 0.25, 1.0, 0.2);
//        glVertex2d(x_indices[0], y_indices[0]); // Start of envelope
//        glVertex2d(x_indices[1], y_indices[1]); // Attack stage over
//        glVertex2d(x_indices[2], y_indices[2]); // Decay stage over
//        glVertex2d(x_indices[3], y_indices[3]); // Release stage over
//        glEnd();
//        
//        // Draw envelope outline
//        glBegin(GL_LINE_STRIP);
//        glColor4f(0.75, 0.25, 1.0, 1.0);
//        glVertex2d(x_indices[0], y_indices[0]); // Start of envelope
//        glVertex2d(x_indices[1], y_indices[1]); // Attack stage over
//        glVertex2d(x_indices[2], y_indices[2]); // Decay stage over
//        glVertex2d(x_indices[3], y_indices[3]); // Release stage over
//        glEnd();
//        
//        // Draw envelope points
//        glPointSize(5.0);
//        glBegin(GL_POINTS);
//        glColor4f(0.75, 0.25, 1.0, 1.0);
//        glVertex2d(x_indices[0], y_indices[0]); // Start of envelope
//        glVertex2d(x_indices[1], y_indices[1]); // Attack stage over
//        glVertex2d(x_indices[2], y_indices[2]); // Decay stage over
//        glVertex2d(x_indices[3], y_indices[3]); // Release stage over
//        glEnd();
//        
//        // Draw the waveform associated with the current wave type
//        //        glBegin(GL_LINE_STRIP);
//        //        for (int i=0; i<WAVETABLE_SIZE; i++) {
//        //            double x_value = ((double)(width*0.9*i)/(double)WAVETABLE_SIZE) + width*0.05;
//        //            double y_value = (1.0 - ((symphony->getWaveTableValueAtIndex(i) + 1.0)/2.0))*height*0.9 + height*0.05;
//        //            double distFromCenter = fabs(y_value - height/2);
//        //            glColor4f(0.0, 1.0, 0.0, 1.0*distFromCenter*2.0/(double)height);
//        //            glVertex2d(x_value, y_value);
//        //        }
//        //        glEnd();
//        
//        // Draw the line in the center of the waveform
//        //        glBegin(GL_LINE_STRIP);
//        //        glColor4f(0.0, 1.0, 0.0, 0.25);
//        //        glVertex2d(0, height/2);
//        //        glVertex2d(width, height/2);
//        //        glEnd();
//        
//        // Draw vertical lines from the waveform to the center
//        //        glColor4f(0.0, 1.0, 0.0, 0.25);
//        //        for (int i=0; i<WAVETABLE_SIZE; i += 100) {
//        //            glBegin(GL_LINE_STRIP);
//        //            double waveform_y = (1.0 - ((symphony->getWaveTableValueAtIndex(i) + 1.0)/2.0))*height*0.9 + height*0.05;
//        //            double center_y = height/2;
//        //            double offset_y = waveform_y - center_y;
//        //            int numSegs = 5;
//        //            double inc_y = offset_y/(double)numSegs;
//        //            double waveform_x = ((double)(width*0.9*i)/(double)WAVETABLE_SIZE) + width*0.05;
//        //            for (int j=0; j<numSegs+1; j++) {
//        //                glColor4f(0.0, 1.0, 0.0, 1.0*(double)j/(double)numSegs);
//        //                glVertex2d(waveform_x, center_y + inc_y*(double)j);
//        //            }
//        //            glEnd();
//        //        }
//        
//        // ----------------- END DRAW ----------------- ALL DRAWING HAPPENS ABOVE THIS LINE
//        
//        
//        glFlush();
//        glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
//        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, mData.Get());
//        
//        // Delete the renderbuffer attachment
//        glDeleteRenderbuffersEXT(1, &renderbuffer);
//        
//        // Make the window the target
//        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
//        glDeleteFramebuffersEXT(1, &framebuffer);
//        
//        restoreContext();
//        
//        unsigned char* val = mData.Get();
//        
//        for(int v=0; v<height; v++)
//        {
//            for(int h=0; h<width; h++)
//            {
//                LICE_pixel pix = LICE_RGBA(*val, *(val + 1), *(val + 2), *(val + 3));
//                LICE_PutPixel(pGraphics->GetDrawBitmap(), mRECT.L + h, mRECT.B - v, pix, 1., LICE_BLIT_MODE_COPY | LICE_BLIT_USE_ALPHA);
//                val += 4;
//            }
//        }
//        
//        return true;
//    }
//    
//    bool IsDirty()
//    {
//        return true;
//    }
//};
//
//#endif /* FilterEnvelopeOpenGL_hpp */
