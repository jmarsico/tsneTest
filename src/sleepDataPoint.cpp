//
//  sleepDataPoint.cpp
//  tsneTest
//
//  Created by Ultra Low Res Studuio on 5/30/18.
//
//

#include "sleepDataPoint.hpp"


void SleepDataPoint::init(){
    bReadyForNextPoint = true;
    transitionMillis = 1000;
    initTime = 0;
    nextPoint.set(0,0,0);
    previousPoint = nextPoint;
    currentPoint = nextPoint;
}


void SleepDataPoint::addNewPoint(ofPoint newPoint){
    previousPoint = currentPoint;
    nextPoint = newPoint;
    initTime = ofGetElapsedTimeMillis();
    
}

void SleepDataPoint::update(){
    
    auto endTime = initTime + transitionMillis;
    auto now = ofGetElapsedTimeMillis();
    
    currentPoint.x = ofxeasing::map_clamp(now, initTime, endTime, previousPoint.x, nextPoint.x, &ofxeasing::linear::easeIn );
    currentPoint.y = ofxeasing::map_clamp(now, initTime, endTime, previousPoint.y, nextPoint.y, &ofxeasing::linear::easeIn );
    currentPoint.z = ofxeasing::map_clamp(now, initTime, endTime, previousPoint.z, nextPoint.z, &ofxeasing::linear::easeIn );

    
    if(currentPoint == nextPoint) {
        bReadyForNextPoint = true;
    } else {
        bReadyForNextPoint = false;
    }
    
}
