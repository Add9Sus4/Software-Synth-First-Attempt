//
//  AudioChannel.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 8/28/16.
//
//

#ifndef AudioChannel_hpp
#define AudioChannel_hpp

#include <stdio.h>

enum AudioChannel {
    LEFT,
    RIGHT
};

enum NumChannels {
    MONO,
    STEREO
};

enum WavePhase {
    SYNC,
    FREE
};

const double C_0 = 16.35;
const double Db_0 = 17.32;
const double D_0 = 18.35;
const double Eb_0 = 19.45;
const double E_0 = 20.60;
const double F_0 = 21.83;
const double Gb_0 = 23.12;
const double G_0 = 24.50;
const double Ab_0 = 25.96;
const double A_0 = 27.50;
const double Bb_0 = 29.14;
const double B_0 = 30.87;
const double C_1 = 32.70;
const double Db_1 = 34.65;
const double D_1 = 36.71;
const double Eb_1 = 38.89;
const double E_1 = 41.20;
const double F_1 = 43.65;
const double Gb_1 = 46.25;
const double G_1 = 49.00;
const double Ab_1 = 51.91;
const double A_1 = 55.00;
const double Bb_1 = 58.27;
const double B_1 = 61.74;
const double C_2 = 65.41;
const double Db_2 = 69.30;
const double D_2 = 73.42;
const double Eb_2 = 77.78;
const double E_2 = 82.41;
const double F_2 = 87.31;
const double Gb_2 = 92.50;
const double G_2 = 98.00;
const double Ab_2 = 103.83;
const double A_2 = 110.00;
const double Bb_2 = 116.54;
const double B_2 = 123.47;
const double C_3 = 130.81;
const double Db_3 = 138.59;
const double D_3 = 146.83;
const double Eb_3 = 155.56;
const double E_3 = 164.81;
const double F_3 = 174.61;
const double Gb_3 = 185.00;
const double G_3 = 196.00;
const double Ab_3 = 207.65;
const double A_3 = 220.00;
const double Bb_3 = 233.08;
const double B_3 = 246.94;
const double C_4 = 261.63;
const double Db_4 = 277.18;
const double D_4 = 293.66;
const double Eb_4 = 311.13;
const double E_4 = 329.63;
const double F_4 = 349.23;
const double Gb_4 = 369.99;
const double G_4 = 392.00;
const double Ab_4 = 415.30;
const double A_4 = 440.00;
const double Bb_4 = 466.16;
const double B_4 = 493.88;
const double C_5 = 523.25;
const double Db_5 = 554.37;
const double D_5 = 587.33;
const double Eb_5 = 622.25;
const double E_5 = 659.25;
const double F_5 = 698.46;
const double Gb_5 = 739.99;
const double G_5 = 783.99;
const double Ab_5 = 830.61;
const double A_5 = 880.00;
const double Bb_5 = 923.33;
const double B_5 = 987.77;
const double C_6 = 1046.50;
const double Db_6 = 1108.73;
const double D_6 = 1174.66;
const double Eb_6 = 1244.51;
const double E_6 = 1318.51;
const double F_6 = 1396.91;
const double Gb_6 = 1479.98;
const double G_6 = 1567.98;
const double Ab_6 = 1661.22;
const double A_6 = 1760.00;
const double Bb_6 = 1864.66;
const double B_6 = 1975.53;
const double C_7 = 2093.00;
const double Db_7 = 2217.46;
const double D_7 = 2349.32;
const double Eb_7 = 2489.02;
const double E_7 = 2637.02;
const double F_7 = 2793.83;
const double Gb_7 = 2959.96;
const double G_7 = 3135.96;
const double Ab_7 = 3322.44;
const double A_7 = 3520.00;
const double Bb_7 = 3729.31;
const double B_7 = 3951.07;
const double C_8 = 4186.01;
const double Db_8 = 4434.92;
const double D_8 = 4698.63;
const double Eb_8 = 4978.03;
const double E_8 = 5274.04;
const double F_8 = 5587.65;
const double Gb_8 = 5919.91;
const double G_8 = 6271.93;
const double Ab_8 = 6644.88;
const double A_8 = 7040.00;
const double Bb_8 = 7458.62;
const double B_8 = 7902.13;



#endif /* AudioChannel_hpp */
