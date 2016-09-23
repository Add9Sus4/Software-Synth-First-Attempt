//
//  Filter.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "Filter.hpp"
/* Simple implementation of Biquad filters -- Tom St Denis
 *
 * Based on the work
 
 Cookbook formulae for audio EQ biquad filter coefficients
 ---------------------------------------------------------
 by Robert Bristow-Johnson, pbjrbj@viconet.com  a.k.a. robert@audioheads.com
 
 * Available on the web at
 
 http://www.smartelectronix.com/musicdsp/text/filters005.txt
 
 * Enjoy.
 *
 * This work is hereby placed in the public domain for all purposes, whether
 * commercial, free [as in speech] or educational, etc.  Use the code and please
 * give me credit if you wish.
 *
 * Tom St Denis -- http://tomstdenis.home.dhs.org
 */

/* this would be biquad.h */
#include <math.h>
#include <stdlib.h>

#ifndef M_LN2
#define M_LN2	   0.69314718055994530942
#endif

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

Filter::Filter(int type, double dbGain, double freq,
               double srate, double bandwidth) {
    
    centerFreqChangeIncrement = 0.0;
    centerFreqChangeCount = 0;
    changingFreq = false;
    
    this->type = type;
    this->dbGain = dbGain;
    this->freq = freq;
    this->srate = srate;
    this->bandwidth = bandwidth;
    currentOffset = 0.0;
    centerFreq = freq;
    
    double A, omega, sn, cs, alpha, beta;
    double a0, a1, a2, b0, b1, b2;
    
    /* setup variables */
    A = pow(10, dbGain /40);
    omega = 2 * M_PI * freq /srate;
    sn = sin(omega);
    cs = cos(omega);
    alpha = sn * sinh(M_LN2 /2 * bandwidth * omega /sn);
    beta = sqrt(A + A);
    
    switch (type) {
        case LPF:
            b0 = (1 - cs) /2;
            b1 = 1 - cs;
            b2 = (1 - cs) /2;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;
        case HPF:
            b0 = (1 + cs) /2;
            b1 = -(1 + cs);
            b2 = (1 + cs) /2;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;
        case BPF:
            b0 = alpha;
            b1 = 0;
            b2 = -alpha;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;
        case NOTCH:
            b0 = 1;
            b1 = -2 * cs;
            b2 = 1;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;
        case PEQ:
            b0 = 1 + (alpha * A);
            b1 = -2 * cs;
            b2 = 1 - (alpha * A);
            a0 = 1 + (alpha /A);
            a1 = -2 * cs;
            a2 = 1 - (alpha /A);
            break;
        case LSH:
            b0 = A * ((A + 1) - (A - 1) * cs + beta * sn);
            b1 = 2 * A * ((A - 1) - (A + 1) * cs);
            b2 = A * ((A + 1) - (A - 1) * cs - beta * sn);
            a0 = (A + 1) + (A - 1) * cs + beta * sn;
            a1 = -2 * ((A - 1) + (A + 1) * cs);
            a2 = (A + 1) + (A - 1) * cs - beta * sn;
            break;
        case HSH:
            b0 = A * ((A + 1) + (A - 1) * cs + beta * sn);
            b1 = -2 * A * ((A - 1) + (A + 1) * cs);
            b2 = A * ((A + 1) + (A - 1) * cs - beta * sn);
            a0 = (A + 1) - (A - 1) * cs + beta * sn;
            a1 = 2 * ((A - 1) - (A + 1) * cs);
            a2 = (A + 1) - (A - 1) * cs - beta * sn;
            break;
        default:
            break;
    }
    
    /* precompute the coefficients */
    filter_a0 = b0 /a0;
    filter_a1 = b1 /a0;
    filter_a2 = b2 /a0;
    filter_a3 = a1 /a0;
    filter_a4 = a2 /a0;
    
    /* zero initial samples */
    filter_x1 = filter_x2 = 0;
    filter_y1 = filter_y2 = 0;
};

void Filter::updateCoefficients(double freqOffset) {
    double A, omega, sn, cs, alpha, beta;
    double a0, a1, a2, b0, b1, b2;
    
    currentOffset = freqOffset;
    freq = centerFreq + freqOffset;
    
    if (freq >= FILTER_FREQ_MAX) {
        freq = FILTER_FREQ_MAX;
    }
    
    if (freq <= FILTER_FREQ_MIN) {
        freq = FILTER_FREQ_MIN;
    }
    
    /* setup variables */
    A = pow(10, dbGain /40);
    omega = 2 * M_PI * freq /srate;
    sn = sin(omega);
    cs = cos(omega);
    alpha = sn * sinh(M_LN2 /2 * bandwidth * omega /sn);
    beta = sqrt(A + A);
    
    switch (type) {
        case LPF:
            b0 = (1 - cs) /2;
            b1 = 1 - cs;
            b2 = (1 - cs) /2;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;
        case HPF:
            b0 = (1 + cs) /2;
            b1 = -(1 + cs);
            b2 = (1 + cs) /2;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;
        case BPF:
            b0 = alpha;
            b1 = 0;
            b2 = -alpha;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;
        case NOTCH:
            b0 = 1;
            b1 = -2 * cs;
            b2 = 1;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;
        case PEQ:
            b0 = 1 + (alpha * A);
            b1 = -2 * cs;
            b2 = 1 - (alpha * A);
            a0 = 1 + (alpha /A);
            a1 = -2 * cs;
            a2 = 1 - (alpha /A);
            break;
        case LSH:
            b0 = A * ((A + 1) - (A - 1) * cs + beta * sn);
            b1 = 2 * A * ((A - 1) - (A + 1) * cs);
            b2 = A * ((A + 1) - (A - 1) * cs - beta * sn);
            a0 = (A + 1) + (A - 1) * cs + beta * sn;
            a1 = -2 * ((A - 1) + (A + 1) * cs);
            a2 = (A + 1) + (A - 1) * cs - beta * sn;
            break;
        case HSH:
            b0 = A * ((A + 1) + (A - 1) * cs + beta * sn);
            b1 = -2 * A * ((A - 1) + (A + 1) * cs);
            b2 = A * ((A + 1) + (A - 1) * cs - beta * sn);
            a0 = (A + 1) - (A - 1) * cs + beta * sn;
            a1 = 2 * ((A - 1) - (A + 1) * cs);
            a2 = (A + 1) - (A - 1) * cs - beta * sn;
            break;
        default:
            break;
    }
    
    /* precompute the coefficients */
    filter_a0 = b0 /a0;
    filter_a1 = b1 /a0;
    filter_a2 = b2 /a0;
    filter_a3 = a1 /a0;
    filter_a4 = a2 /a0;
    
    /* zero initial samples */
//    filter_x1 = filter_x2 = 0;
//    filter_y1 = filter_y2 = 0;

}

/* Computes a BiQuad filter on a sample */
double Filter::processSample(double sample)
{
    // Change freq, if applicable
    if (changingFreq) {
        
        // Update freq
        centerFreq += centerFreqChangeIncrement;
        
        // Update coefficients
        updateCoefficients(currentOffset);
        
        // Increment the counter
        centerFreqChangeCount++;
        
        // If the limit is reached, stop changing, reset values
        if (centerFreqChangeCount >= FILTER_CUTOFF_CHANGE_LENGTH) {
            centerFreqChangeCount = 0;
            centerFreqChangeIncrement = 0.0;
            changingFreq = false;
        }
    }
    
    double result;
    
    /* compute result */
    result = filter_a0 * sample + filter_a1 * filter_x1 + filter_a2 * filter_x2 - filter_a3 * filter_y1 - filter_a4 * filter_y2;

    /* shift x1 to x2, sample to x1 */
    filter_x2 = filter_x1;
    filter_x1 = sample;
    
    /* shift y1 to y2, result to y1 */
    filter_y2 = filter_y1;
    filter_y1 = result;
    return result;
}
