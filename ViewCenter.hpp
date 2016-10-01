//
//  ViewCenter.hpp
//  AudioComponents
//
//  Created by Aaron Dawson on 9/23/16.
//
//

#ifndef ViewCenter_hpp
#define ViewCenter_hpp

#define NUM_PAST_VALS   100

#include <stdio.h>
#include <vector>
#include "time.h"

#include "View.hpp"

class ViewCenter : public View {
public:
    ViewCenter(IPlugBase* pPlug, IRECT pR, VoiceManager* voiceManager, ViewManager* viewManager) : View(pPlug, pR, voiceManager, viewManager) {
        width = pR.W();
        height = pR.H();
        
        bgColor1red = 0.45/3.0;
        bgColor1green = 0.40/3.0;
        bgColor1blue = 0.35/3.0;
        
        numParticles = 50;
        
        srand(time(NULL));
        
        for (int i=0; i<numParticles; i++) {
            double x_sign = 1.0;
            double y_sign = 1.0;
            
            if (rand()%2 == 0) {
                x_sign = -1.0;
            }
            if (rand()%2 == 0) {
                y_sign = -1.0;
            }
            
            particles.push_back(new Particle((float)(rand()%1000)/1000., (float)(rand()%1000)/1000., (float)(rand()%1000)/1000., rand()%(pR.W()/2)+ pR.W()/4, rand()%(pR.H()/2) + pR.H()/4, x_sign*((double)(rand()%1000)/1000.), y_sign*((double)(rand()%1000)/1000.), 0, 0, pR.W(), pR.H()));
        }
    }
    void drawStuff() {
        
        double pointSize = 500.0/(double)numParticles;
        if (pointSize > 10) {
            pointSize = 10;
        }
        for (int i=0; i<particles.size(); i++) {
            for (int j=0; j<NUM_PAST_VALS; j++) {
                glPointSize((double)(NUM_PAST_VALS-j)*pointSize*pow((double)(NUM_PAST_VALS-j)/(double)NUM_PAST_VALS, 4)/(double)NUM_PAST_VALS);
                glBegin(GL_POINTS);
                double factor = 1.0;
                if (j!=0) {
                    factor = 3.0;
                }
                glColor4f(particles[i]->r/factor, particles[i]->g/factor, particles[i]->b/factor, (double)(NUM_PAST_VALS-j)*pow((double)(NUM_PAST_VALS-j)/(double)NUM_PAST_VALS, 2)/(double)NUM_PAST_VALS);
                glVertex2d(particles[i]->past_x[j], particles[i]->past_y[j]);
                glEnd();
            }
            glPointSize(pointSize);
            glBegin(GL_POINTS);
            glColor4f(particles[i]->r, particles[i]->g, particles[i]->b, 1.0);
            glVertex2d(particles[i]->x, particles[i]->y);
            glEnd();
        }
        
        double center_of_mass_x = 0;
        double center_of_mass_y = 0;
        for (int i=0; i<particles.size(); i++) {
            center_of_mass_x += particles[i]->x;
            center_of_mass_y += particles[i]->y;
            particles[i]->move();
        }
        center_of_mass_x /= (double)particles.size();
        center_of_mass_y /= (double)particles.size();
//        center_of_mass_x = width/2;
//        center_of_mass_y = height/2;
        center_of_mass_x = mouseLastPressX;
        center_of_mass_y = mouseLastPressY;
        glPointSize(20.0);
        glBegin(GL_POINTS);
        glColor4f(1.0, 0.0, 0.0, 0.1);
        glVertex2d(center_of_mass_x, center_of_mass_y);
        glEnd();
        for (int i=0; i<particles.size(); i++) {
            particles[i]->applyGravity(center_of_mass_x, center_of_mass_y);
        }
    }
    
private:
    int width;
    int height;
    class Particle {
    public:
        Particle(float r, float g, float b, double x, double y, double x_inc, double y_inc, int leftBound, int upperBound, int rightBound, int lowerBound) {
            this->x = x;
            this->y = y;
            this->x_inc = x_inc;
            this->y_inc = y_inc;
            this->leftBound = leftBound;
            this->upperBound = upperBound;
            this->rightBound = rightBound;
            this->lowerBound = lowerBound;
            this->r = r;
            this->g = g;
            this->b = b;
            for (int i=0; i<NUM_PAST_VALS; i++) {
                past_x[i] = x;
                past_y[i] = y;
            }
        };
        double x;
        double y;
        double x_inc;
        double y_inc;
        int leftBound;
        int upperBound;
        int rightBound;
        int lowerBound;
        float r;
        float g;
        float b;
        double past_x[NUM_PAST_VALS];
        double past_y[NUM_PAST_VALS];
        
        void applyGravity(double center_of_mass_x, double center_of_mass_y) {
            
            double x_distance = (double)(center_of_mass_x - x);
            double y_distance = (double)(center_of_mass_y - y);
            
            double distance = sqrt(pow(x_distance, 2) + pow(y_distance,2));
            
            if (distance == 0.00000) {
                distance = 0.00001;
            }
            
            double gravitationalForce = 100.0;
            
            double force = gravitationalForce/pow((double)(distance), 2);
            
            double x_force = force*x_distance/distance;
            double y_force = force*y_distance/distance;

            x_inc += x_force;
            y_inc += y_force;
        }
        void resetVelocity(double x_sign, double y_sign) {
            if (x_inc > 50 || y_inc > 50) {
                x_inc = 5*x_sign;
                y_inc = 5*y_sign;
            }
        }
        
        void move() {
            x += x_inc;
            y += y_inc;
            for (int i=NUM_PAST_VALS-1; i>0; i--) {
                past_x[i] = past_x[i-1];
                past_y[i] = past_y[i-1];
            }
            past_x[0] = x;
            past_y[0] = y;
            
//            if (x < leftBound) {
//                x = leftBound;
//                x_inc *= -1.0;
//                resetVelocity(1, 1);
//            }
//            if (x > rightBound) {
//                x = rightBound;
//                x_inc *= -1.0;
//                resetVelocity(-1, 1);
//            }
//            if (y < upperBound) {
//                y = upperBound;
//                y_inc *= -1.0;
//                resetVelocity(1, 1);
//            }
//            if (y > lowerBound) {
//                y = lowerBound;
//                y_inc *= -1.0;
//                resetVelocity(1, -1);
//            }
            
        }
    };
    int numParticles;
    std::vector<Particle*> particles;
    
    
};

#endif /* ViewCenter_hpp */
