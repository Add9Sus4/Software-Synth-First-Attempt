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
    
    WaveType waveType;
    
    double detune;
    double pan; // 0 (mono) to 1 (full width)
    
    Parameter* frequencyParam;
    LFO* lfo;
    
public:
    // Create a new oscillator group with specified number of oscillators, frequency, and wave type
    OscillatorGroup(int numOscillators, double frequency, WaveType waveType) {
        frequencyParam = new Parameter(frequency);
        this->waveType = waveType;
        detune = 1.0;
        pan = 1.0;
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
        for(std::vector<int>::size_type j = 0; j != oscillators.size(); j++) {
            double *oscSamplesLeft = oscillators[j]->getSamplesLeft(blockSize);
            double *oscSamplesRight = oscillators[j]->getSamplesRight(blockSize);
            for (int i=0; i<blockSize; i++) {
                outBlock[LEFT][i] += oscSamplesLeft[i]/(double)oscillators.size();
                outBlock[RIGHT][i] += oscSamplesRight[i]/(double)oscillators.size();
            }
            delete[] oscSamplesLeft;
            delete[] oscSamplesRight;
        }
        return outBlock;
    }
    
    void drawSlotView(IRECT rect) {
        GLuint tex_2d = SOIL_load_OGL_texture ("/Users/aarondawson/Dev/AudioPlugins/wdl-ol/IPlugExamples/AudioComponents/Oscillator1SlotDisplay.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
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
    }
    
    // Sets the pulse width for the oscillators. This only has an effect if the wave type is a pulse wave.
    void setPulseWidth(double pulseWidth);
    
    // Sets the frequency for the oscillators;
    void setFrequency(double frequency);
    
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
