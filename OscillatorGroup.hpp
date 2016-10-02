//
//  OscillatorGroup.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#ifndef OscillatorGroup_hpp
#define OscillatorGroup_hpp

#include <stdio.h>
#include <vector>
#include "AudioChannel.hpp"
#include "BlockEffect.hpp"
#include "Filter.hpp"
#include "FormantFilter.hpp"
#include "LFO.hpp"
#include "Oscillator.hpp"
#include "Parameter.hpp"

class OscillatorGroup : public BlockEffect {
    
    // Vector containging all the oscillators for this group
    std::vector<Oscillator *> oscillators;
    
    // Wave type (Saw, Square, Sine, etc)
    WaveType waveType;
    
    // Parameters
    double detune;
    double pan; // 0 (mono) to 1 (full width)
    Parameter* volumeParam;
    Parameter* frequencyParam;
    
public:
    // IControls
    IKnobMultiControl* knobControl;
    IKnobMultiControl* panControl;
    IKnobMultiControl* volumeFader;
    // Create a new oscillator group with specified number of oscillators, frequency, and wave type
    OscillatorGroup(int numOscillators, double frequency, WaveType waveType) : BlockEffect() {
        frequencyParam = new Parameter(frequency);
        this->waveType = waveType;
        detune = 1.0;
        pan = 1.0;
        volumeParam = new Parameter(1.0, 25);
        // Panning for the oscillators (used for stereo spread)
        double *pans = new double[numOscillators];
        
        // Frequencies for the oscillators (used for detuning)
        double *frequencies = new double[numOscillators];
        
        /* Calculate the panning interval between each oscillator (oscillators are equidistant from
         each other; in the future different spread algorithms will be available, like in Serum).
         Scaled by the number of oscillators so that all pan values stay in the interval (-1.0)..(1.0) */
        double panInterval = 2.0/((double)numOscillators-1.0);
        
        /* Calculate the detune amount (scaled by number of oscillators so that the min/max frequency
         remains the same. */
        double detuneAmt = 2.0/(double)numOscillators;
        
        /* Sum of all frequencies. Needed for calculation of average frequency later, which is needed to shift
         frequencies so that their average is equal to the frequency passed into the constructor (otherwise,
         the average frequency would be too high) */
        double frequencySum = 0.0;
        
        // Calculate pan and frequency values for each oscillator in the group
        for (int i=0; i<numOscillators; i++) {
            pans[i] = -1.0 + panInterval*(double)i; // pans go from -1.0 to 1.0
            if (pans[i] < -1.0) pans[i] = -1.0; // set pan to -1.0 if too low
            if (pans[i] > 1.0) pans[i] = 1.0; // set pan to 1.0 if too high
            frequencies[i] = frequency + (double)i*detuneAmt*detune; // frequencies offset by detune amount
            frequencySum += frequencies[i]; // Add to frequency sum
        }
        
        // Calculate average frequency of all oscillators
        double avgFrequency = frequencySum/(double)numOscillators;
        
        // Adjust all frequencies so that their average is the correct value
        for (int i=0; i<numOscillators; i++) {
            frequencies[i] -= (avgFrequency - frequency); // avgFrequency will always be higher than frequency at this point
        }
        
        // Create and initialize all the oscillators
        for (int i=0; i<numOscillators; i++) {
            oscillators.push_back(new Oscillator(frequencies[i], pans[i]*pan, waveType));
        }
        
        // free pointers
        delete[] pans;
        delete[] frequencies;
    }
    
    // Get combined output samples from oscillators
    // Get combined output samples from oscillators (left channel only)
    double** process(double** outBlock, int blockSize) {
        double currentVolume = volumeParam->getValue();
        std::cout << "Current volume: " << currentVolume << std::endl;
        for(std::vector<int>::size_type j = 0; j != oscillators.size(); j++) {
            double *oscSamplesLeft = oscillators[j]->getSamplesLeft(blockSize);
            double *oscSamplesRight = oscillators[j]->getSamplesRight(blockSize);
            for (int i=0; i<blockSize; i++) {
                outBlock[LEFT][i] += oscSamplesLeft[i]*currentVolume/(double)oscillators.size();
                outBlock[RIGHT][i] += oscSamplesRight[i]*currentVolume/(double)oscillators.size();
            }
            delete[] oscSamplesLeft;
            delete[] oscSamplesRight;
        }
        return outBlock;
    }
    
    void drawSlotView(IRECT rect) {
        
        // Background image
        GLuint tex_2d = SOIL_load_OGL_texture ("/Users/aarondawson/Dev/AudioPlugins/wdl-ol/IPlugExamples/AudioComponents/Oscillator1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                               SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
        glBindTexture(GL_TEXTURE_2D, tex_2d);
        
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2d(0,0);
        glVertex2d(rect.L,rect.T);
        glTexCoord2d(0,1);
        glVertex2d(rect.L,rect.B);
        glTexCoord2d(1,1);
        glVertex2d(rect.R,rect.B);
        glTexCoord2d(1,0);
        glVertex2d(rect.R,rect.T);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        
        glDeleteTextures(1, &tex_2d);
        
        // Knobs, fader
        if (isActive()) {
            knobControl->Hide(false);
            knobControl->move(rect.L + kViewBottomL + 46, rect.T + kViewBottomT + 83);
            panControl->Hide(false);
            panControl->move(rect.L + kViewBottomL - 2, rect.T + kViewBottomT + 83);
            volumeFader->Hide(false);
            volumeFader->move(rect.L + kViewBottomL + 117, rect.T + kViewBottomT + 35);
        } else {
            knobControl->Hide(true);
            knobControl->move(-100, -100);
            panControl->Hide(true);
            panControl->move(-100, -100);
            volumeFader->Hide(true);
            volumeFader->move(-100, -100);
        }
        
        // Waveform background
        glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.0);
        glVertex2d(7 + rect.L, 25 + rect.T);
        glVertex2d(7 + rect.L, 73 + rect.T);
        glVertex2d(97 + rect.L, 73 + rect.T);
        glVertex2d(97 + rect.L, 25 + rect.T);
        glEnd();
        
        int waveformWidth = 103-13;
        int waveformHeight = 83-35;
        
        int leftPadding = 7;
        int topPadding = 25;
        
        // Waveform
        glBegin(GL_LINE_STRIP);
        for (int i=0; i<WAVETABLE_SIZE; i++) {
            double x_value = ((double)(waveformWidth*0.9*i)/(double)WAVETABLE_SIZE) + waveformWidth*0.05;
            double y_value = (1.0 - ((getWaveTableValueAtIndex(i) + 1.0)/2.0))*waveformHeight*0.9 + waveformHeight*0.05;
            double distFromCenter = fabs(y_value - waveformHeight/2);
            glColor4f(0.0, 1.0, 0.0, 1.0*distFromCenter*2.0/(double)waveformHeight);
            glVertex2d(x_value + leftPadding + rect.L, y_value + topPadding + rect.T);
        }
        glEnd();
        
//      Draw the line in the center of the waveform
        glBegin(GL_LINE_STRIP);
        glColor4f(0.0, 1.0, 0.0, 0.25);
        glVertex2d(0 + leftPadding + rect.L + kViewBottomL, waveformHeight/2 + topPadding + rect.T);
        glVertex2d(waveformWidth + leftPadding + rect.L, waveformHeight/2 + topPadding + rect.T);
        glEnd();
    
        // Draw vertical lines from the waveform to the center
        glColor4f(0.0, 1.0, 0.0, 0.25);
        for (int i=0; i<WAVETABLE_SIZE; i += 100) {
            glBegin(GL_LINE_STRIP);
            double waveform_y = (1.0 - ((getWaveTableValueAtIndex(i) + 1.0)/2.0))*waveformHeight*0.9 + waveformHeight*0.05;
            double center_y = waveformHeight/2;
            double offset_y = waveform_y - center_y;
            int numSegs = 5;
            double inc_y = offset_y/(double)numSegs;
            double waveform_x = ((double)(waveformWidth*0.9*i)/(double)WAVETABLE_SIZE) + waveformWidth*0.05;
            for (int j=0; j<numSegs+1; j++) {
                glColor4f(0.0, 1.0, 0.0, 1.0*(double)j/(double)numSegs);
                glVertex2d(waveform_x + leftPadding + rect.L, center_y + inc_y*(double)j + topPadding + rect.T);
            }
            glEnd();
        }
        
    }
    
    // Sets the pulse width for the oscillators. This only has an effect if the wave type is a pulse wave.
    void setPulseWidth(double pulseWidth);
    
    // Sets the frequency for the oscillators;
    void setFrequency(double frequency);
    
    void changeVolume(double volume) { volumeParam->setValue(volume); }
    
    void changeWaveType(WaveType waveType) {
        for(std::vector<int>::size_type i = 0; i != oscillators.size(); i++) {
            oscillators[i]->changeWaveType(waveType);
        }
        this->waveType = waveType;
    }
    
    WaveType getWaveType() { return waveType; }
    
    void changeDetuneAmt(double newDetune) {
        detune = newDetune;
        setFrequency(frequencyParam->getValue());
    }
    
    void changePanAmt(double newPan) {
        pan = newPan;
        // Panning for the oscillators (used for stereo spread)
        double *pans = new double[oscillators.size()];
        /* Calculate the panning interval between each oscillator (oscillators are equidistant from
         each other; in the future different spread algorithms will be available, like in Serum).
         Scaled by the number of oscillators so that all pan values stay in the interval (-1.0)..(1.0) */
        double panInterval = 2.0/((double)oscillators.size()-1.0);
        // Calculate pan and frequency values for each oscillator in the group
        for (int i=0; i<oscillators.size(); i++) {
            pans[i] = -1.0 + panInterval*(double)i; // pans go from -1.0 to 1.0
            if (pans[i] < -1.0) pans[i] = -1.0; // set pan to -1.0 if too low
            if (pans[i] > 1.0) pans[i] = 1.0; // set pan to 1.0 if too high
        }
        for(std::vector<int>::size_type i = 0; i != oscillators.size(); i++) {
            oscillators[i]->setPan(pans[i]*pan);
        }
        delete[] pans;
    }
    
    void changePhaseMode(WavePhase wavePhase) {
        for(std::vector<int>::size_type i = 0; i != oscillators.size(); i++) {
            oscillators[i]->setPhaseMode(wavePhase);
        }
    }
    
    double getWaveTableValueAtIndex(int i) {
        return oscillators[0]->getWaveTableValueAtIndex(i);
    }
    
};

#endif /* OscillatorGroup_hpp */
