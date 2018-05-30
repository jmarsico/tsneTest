//
//  sleepDataPoint.hpp
//  tsneTest
//
//  Created by Ultra Low Res Studuio on 5/30/18.
//
//

#ifndef sleepDataPoint_hpp
#define sleepDataPoint_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxEasing.h"

class SleepDataPoint {
public:
    
    SleepDataPoint(){};
    void init();
    void addNewPoint(ofPoint newPoint);
    void update();
    
    int numChildren;
    int watchTV;
    int drinkAlcohol;
    int read;
    int bath;
    int sleepQuality;
    ofPoint nextPoint;
    ofPoint previousPoint;
    ofPoint currentPoint;
    int color;
    float tsneTransparency;
    
    bool bReadyForNextPoint;
    int transitionMillis;
    
    int initTime;
};


#endif /* sleepDataPoint_hpp */
