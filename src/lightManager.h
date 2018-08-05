//
//  lightMananger.h
//  abstractions
//
//  Created by Jakob Marsico on 7/12/16.
//
//

#ifndef __abstractions__lightMananger__
#define __abstractions__lightMananger__

#include <stdio.h>
#include "ofMain.h"
#include "generativeLight.h"
#include "ofxJSON.h"
//#include "ofxColorGradient.h"

class LightManager {
public:
    LightManager(){};
    void init(ofxColorGradient<ofColor>* _colors, ofBoxPrimitive* _bBox);
    void update();
    void draw();
    void enableLights();
    void disableLights();
    ofFloatColor chooseColor(int color);
    
    
    
    vector<GenerativeLight> lights;
    
    ofLight ambientLight;
    
    ofLight directLight0;
    ofLight directLight1;
    
    
    //lightGui
    ofParameterGroup lightGui;
    ofParameter<float> ambient;
    ofParameter<bool> bShowLightdebug;
    ofParameter<float> spec;
    ofParameter<float> att;
    ofParameter<float> diff;
    ofParameter<float> amb;
    ofParameter<int> col;
    ofParameter<ofVec3f> dLightLook0;
    ofParameter<ofVec3f> dLightLook1;
    

    

    
};

#endif /* defined(__abstractions__lightMananger__) */
