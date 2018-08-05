//
//  generativeLight.h
//  abstractions
//
//  Created by Jakob Marsico on 7/12/16.
//
//

#ifndef __abstractions__generativeLight__
#define __abstractions__generativeLight__

#include <stdio.h>
#include "ofMain.h"
#include "ofxPtf.h"
#include "ofxColorGradient.h"

class GenerativeLight{
public:
    GenerativeLight(){};
    void init(int ID, ofxColorGradient<ofColor>* _colors, ofBoxPrimitive* _bBox);
    void update();
    void draw();
    ofFloatColor chooseColor(int color);
    
    
    ofLight light;
    
    ofParameterGroup params;
    ofParameter<bool> bNoiseMotion;
    ofParameter<float> noiseSpeed;
    ofParameter<float> transX;
    ofParameter<float> transY;
    ofParameter<float> transZ;
    ofParameter<float> lookAtX;
    ofParameter<float> lookAtY;
    ofParameter<float> lookAtZ;
    ofParameter<float> spec;
    ofParameter<float> att;
    ofParameter<float> diff;
    ofParameter<float> amb;
    ofParameter<int> col;

    
    float xNoiseCounter;
    float yNoiseCounter;
    float zNoiseCounter;
    
    int width,height;
    ofVboMesh tail;
    ofVec3f lastPos;
    float dist;
    
    ofxPtf ptf;
    
    ofxColorGradient<ofColor>* colors;
    float colorInc;
    
    ofBoxPrimitive* bBox;
    

};



#endif /* defined(__abstractions__generativeLight__) */
