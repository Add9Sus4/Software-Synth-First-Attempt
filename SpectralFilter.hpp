//
//  SpectralFilter.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/19/16.
//
//

#ifndef SpectralFilter_hpp
#define SpectralFilter_hpp

#include <stdio.h>

#include "AudioWindow.hpp"
#include "BlockEffect.hpp"
#include "Transform.hpp"


class SpectralFilter : public BlockEffect {
public:
    SpectralFilter(int blockSize) {
        this->blockSize = blockSize;
        bufferLeft = new double[blockSize*2];
        bufferRight = new double[blockSize*2];
        processingBufferLeft = new double[blockSize*2];
        processingBufferRight = new double[blockSize*2];
        for (int i=0; i<blockSize*2; i++) {
            bufferLeft[i] = 0.0;
            bufferRight[i] = 0.0;
            processingBufferLeft[i] = 0.0;
            processingBufferRight[i] = 0.0;
        }
        window = AudioWindow::hanning(blockSize*2);
    }
    
    void shiftBuffers() {
        for (int i=0; i<blockSize; i++) {
            bufferLeft[i] = bufferLeft[i + blockSize];
            bufferRight[i] = bufferRight[i + blockSize];
            processingBufferLeft[i] = processingBufferLeft[i + blockSize];
            processingBufferRight[i] = processingBufferRight[i + blockSize];
        }
    }
    
    void checkBufferSize(int blockSize) {
        if (this->blockSize != blockSize) {
            
            // Store current buffers in temp variables
            double *tempBufferLeft = bufferLeft;
            double *tempBufferRight = bufferRight;
            double *tempProcessingBufferLeft = processingBufferLeft;
            double *tempProcessingBufferRight = processingBufferRight;
            double *tempWindow = window;
            
            // Allocate new memory for buffers according to new block size
            bufferLeft = new double[blockSize*2];
            bufferRight = new double[blockSize*2];
            processingBufferLeft = new double[blockSize*2];
            processingBufferRight = new double[blockSize*2];
            for (int i=0; i<blockSize*2; i++) {
                bufferLeft[i] = 0.0;
                bufferRight[i] = 0.0;
                processingBufferLeft[i] = 0.0;
                processingBufferRight[i] = 0.0;
            }
            window = AudioWindow::hanning(blockSize*2);
            
            // Free old buffers
            delete[] tempBufferLeft;
            delete[] tempBufferRight;
            delete[] tempProcessingBufferLeft;
            delete[] tempProcessingBufferRight;
            delete[] tempWindow;
            
            // Update blockSize
            this->blockSize = blockSize;
        }
    }
    
    void drawSlotView(IRECT rect) {
        
    }
    
    // Process a block of audio
    double** process(double** outBlock, int blockSize) {
        
        checkBufferSize(blockSize);
        
        // Copy inBlock to the back half of the buffer
        for (int i=0; i<blockSize; i++) {
            bufferLeft[i + blockSize] = outBlock[LEFT][i];
            bufferRight[i + blockSize] = outBlock[RIGHT][i];
        }
        
        // Create temp buffer to store results of spectral processing
        double *tempBufferLeft = new double[blockSize*2];
        double *tempBufferRight = new double[blockSize*2];
        
        // Copy buffer to temp buffer
        for (int i=0; i<blockSize*2; i++) {
            tempBufferLeft[i] = bufferLeft[i];
            tempBufferRight[i] = bufferRight[i];
        }
        
        // Take FFT of temp buffer
        Transform::rfft(tempBufferLeft, blockSize, FFT_FORWARD);
        Transform::rfft(tempBufferRight, blockSize, FFT_FORWARD);
        
        // Remove bins
        for (int i=0; i<blockSize; i++) {
            if (i >= blockSize/38) {
                tempBufferLeft[2*i] = 0.0;
                tempBufferRight[2*i] = 0.0;
                tempBufferLeft[2*i + 1] = 0.0;
                tempBufferRight[2*i + 1] = 0.0;
            }
            
        }
        
        // Take IFFT of temp buffer
        Transform::rfft(tempBufferLeft, blockSize, FFT_INVERSE);
        Transform::rfft(tempBufferRight, blockSize, FFT_INVERSE);
        
        // Window the temp buffer
        for (int i=0; i<blockSize*2; i++) {
            tempBufferLeft[i] *= window[i];
            tempBufferRight[i] *= window[i];
        }
        
        // Place temp buffer in processing buffer
        for (int i=0; i<blockSize*2; i++) {
            processingBufferLeft[i] += tempBufferLeft[i];
            processingBufferRight[i] += tempBufferRight[i];
        }
        
        // Place first half of processing buffer in the out block
        for (int i=0; i<blockSize; i++) {
            outBlock[LEFT][i] = processingBufferLeft[i];
            outBlock[RIGHT][i] = processingBufferRight[i];
        }
        
        // Shift the buffers
        shiftBuffers();
        
        // Clear the second half of the processing buffer
        for (int i=0; i<blockSize; i++) {
            processingBufferLeft[i + blockSize] = 0.0;
            processingBufferRight[i + blockSize] = 0.0;
        }
        
        // free memory for temp buffer
        delete[] tempBufferLeft;
        delete[] tempBufferRight;
        
        // Return outBlock
        return outBlock;
    }
private:
    int blockSize;
    double *bufferLeft;
    double *bufferRight;
    double *processingBufferLeft;
    double *processingBufferRight;
    double *window;
};

#endif /* SpectralFilter_hpp */
