#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "ofxTSNE.h"
#include "ofxSyphon.h"
#include "ofxGui.h"
#include "ofxMidiFighterTwister.h"
#include "ofxDOF.h"
#include "sleepDataPoint.hpp"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void reset();
    void setFocalPoint(ofVec3f _point);
    
    void onEncoderUpdate(ofxMidiFighterTwister::EncoderEventArgs &);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxTSNE tsne;
    ofxCsv csvLoader;
    

    
    ofxPanel gui;
    ofParameter<int> distanceThresh;
    ofParameter<float> rad;
    ofParameter<ofColor> meshCol;
    ofParameter<float> transitionMillis;
    ofParameter<float> camDistance;
    ofParameter<float> camRotSpeedLat;
    ofParameter<float> camRotSpeedLon;
    ofParameter<float> fov;
    ofParameter<float> ambAmb;
    ofParameter<float> ambDiff;
    ofParameter<float> pointAmb;
    ofParameter<float> pointDiff;
    
    
    ofParameter<bool> bAutoFocus;
    ofParameter<float> focusDistance;
    ofParameter<float> aperture;
    ofParameter<float> blurAmount;
    ofParameter<ofColor> bgColor;
    ofParameter<ofColor> col1;
    ofParameter<ofColor> col2;
    ofParameter<ofColor> col3;
    ofParameter<ofColor> col4;
    
    ofColor prevCol1, prevCol2, prevCol3, prevCol4;
    
    ofParameter<ofColor> light1;
    
    
    float camLat;
    float camLon;
    
    vector<SleepDataPoint> dataPoints;
    vector<vector<double>> tsnePoints;
    
    
    ofMesh mesh;
    
    bool runManually;
    
    ofLight light;
    ofLight light2;
    
    ofxSyphonServer syphon;
    
    ofCamera cam;
    
    ofxMidiFighterTwister twister;
    
    ofxDOF depthOfField;
    
    
};
