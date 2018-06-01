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
    pointIndex = 0;
}


void SleepDataPoint::addNewPoint(ofPoint newPoint){

    
    points.push_back(newPoint);
    
//    ofLog() << previousPoint << " | " << nextPoint;
    
    
}

void SleepDataPoint::update(){
    
    int endTime = initTime + transitionMillis;
    int now = ofGetElapsedTimeMillis();
    
    currentPoint.x = ofxeasing::map_clamp(now, initTime, endTime, previousPoint.x, nextPoint.x, &ofxeasing::linear::easeIn );
    currentPoint.y = ofxeasing::map_clamp(now, initTime, endTime, previousPoint.y, nextPoint.y, &ofxeasing::linear::easeIn );
    currentPoint.z = ofxeasing::map_clamp(now, initTime, endTime, previousPoint.z, nextPoint.z, &ofxeasing::linear::easeIn );

//    ofLog() << previousPoint << " | " << nextPoint << " | " << currentPoint;
    
    if(currentPoint.x >= nextPoint.x - 5 && currentPoint.x <= nextPoint.x + 5) {
        pointIndex ++;
        previousPoint = currentPoint;
        if(pointIndex < points.size()) nextPoint = points[pointIndex];
        initTime = ofGetElapsedTimeMillis();
        bReadyForNextPoint = false;
    }
    
}
