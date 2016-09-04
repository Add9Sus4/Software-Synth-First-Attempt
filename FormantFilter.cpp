//
//  FormantFilter.cpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#include "FormantFilter.hpp"
/*
 Public source code by alex@smartelectronix.com
 Simple example of implementation of formant filter
 Vowelnum can be 0,1,2,3,4 <=> A,E,I,O,U
 Good for spectral rich input like saw or square
 */
//-------------------------------------------------------------VOWEL COEFFICIENTS

//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
double FormantFilter::process(double sample)
{
    double res = (double) (coeff[vowel][0]  *sample +
                  coeff[vowel][1]  *memory[0] +
                  coeff[vowel][2]  *memory[1] +
                  coeff[vowel][3]  *memory[2] +
                  coeff[vowel][4]  *memory[3] +
                  coeff[vowel][5]  *memory[4] +
                  coeff[vowel][6]  *memory[5] +
                  coeff[vowel][7]  *memory[6] +
                  coeff[vowel][8]  *memory[7] +
                  coeff[vowel][9]  *memory[8] +
                  coeff[vowel][10] *memory[9] );
    
    memory[9]= memory[8];
    memory[8]= memory[7];
    memory[7]= memory[6];
    memory[6]= memory[5];
    memory[5]= memory[4];
    memory[4]= memory[3];
    memory[3]= memory[2];
    memory[2]= memory[1];
    memory[1]= memory[0];
    memory[0]=(double) res;
    return (double) res/10;
}
